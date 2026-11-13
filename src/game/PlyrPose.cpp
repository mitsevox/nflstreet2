/* Player pose: sets up a player model's animated pose from its skeletons,
   builds its world and bone matrices, runs the periodic weight pulse
   (blink) counter, and packs the pose into a bit stream or reads two
   recorded poses back and blends between them. */

#include "game/AnimFrameHeader.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_801BC084.h"
#include "game/FEPlyrModel.h"
#include "game/bitstream.h"
#include "game/Ball.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802372EC.h"

/* Quantization of one pose value: a base offset and a bit width. */
struct PlyrPoseQuant_t {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
};

extern "C" {
void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_800ADDFC(Object_8003DEC4 *pObject, PlyrPosePart_t *pElement, int a);
int fn_800ADD7C(PlyrPosePart_t *pElements, unsigned int index);
int fn_800ADEFC(PlyrPosePart_t *pElements, unsigned int index);
void fn_800C2788(Object_8003DEC4 *pObject, Block_800C2788 *pBlock, int a);
void fn_800C2EC0(Object_8003DEC4 *pObject, Block_800C2EC0 *pBlock, int a);
void fn_80147840(Object_8003DEC4 *pObject);
int fn_801784C4(void);
void AnimBlendPose(AnimPose_t *pOut, AnimPose_t *pA, AnimPose_t *pB, AnimPose_t *pC, float t,
                 unsigned char a);
short *AnimAllocPoseChannels(int count);
void AnimBlendEntries(Object_8003DEC4 *pObject, int a, int count);
void AnimBlendRootAngles(Object_8003DEC4 *pObject, void *a, unsigned short b, void *c);
void AnimBlendRawEntries(Object_8003DEC4 *pObject, int a, unsigned int b, int count);
void AnimResetWeights(float *p);
void AnimBuildPoseMatrices(Object_8003DEC4 *pObject);
void *AnimFileGetFrame(Object_801BC084 *pRecord, int b, int handle, unsigned int c);
int fn_801BBE5C(int a, int b);
void OrientLerpAngle(int *pOut, int a, int b, float t);
void fn_801D0470(int a);
void fn_801D0494(void);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0664(float m[4][4]);
void fn_801D06D4(float m[4][4]);
void fn_801D08FC(int a);
void fn_801D09EC(int a);
void fn_801D0ADC(int a);
void fn_801D0BCC(int a, int b, int c);
void fn_801D0C58(float *p);
void fn_801D0CFC(float a);
void fn_801D0F80(float m[4][4]);
void fn_801D0FB8(float *p);
void fn_801D11F4(int *p, int a);
void QuatIdentity(Quat_801EB488 *pRot);
void QuatFromEuler(Quat_801EB488 *pOut, int a, int b, int c);
void fn_80227930(float *pOut, float *pA, float *pB, float t);

float _PlyrPose_afBlinkWeights[7] = {0.75f, 0.9f, 0.95f, 1.0f, 0.95f, 0.9f, 0.75f};

PlyrPoseQuant_t _PlyrPose_aChannelQuant[78] = {
    {0x0804, 12}, {0x0000, 0}, {0x0406, 11}, {0x09CD, 12}, {0x0500, 11}, {0x0956, 12},
    {0x00AF, 11}, {0x0000, 0}, {0x0000, 0}, {0x080A, 12}, {0x0758, 12}, {0x07F6, 12},
    {0x067B, 11}, {0x0000, 0}, {0x0000, 0}, {0x09BB, 12}, {0x0371, 11}, {0x0455, 12},
    {0x00AF, 11}, {0x0000, 0}, {0x0000, 0}, {0x0805, 12}, {0x043D, 12}, {0x0A93, 12},
    {0x067B, 11}, {0x0000, 0}, {0x0000, 0}, {0x034A, 11}, {0x0740, 12}, {0x0211, 10},
    {0x0424, 11}, {0x037D, 11}, {0x0200, 10}, {0x01B4, 10}, {0x0210, 10}, {0x0242, 10},
    {0x03B6, 11}, {0x07A0, 12}, {0x048A, 11}, {0x080D, 12}, {0x04AF, 12}, {0x0917, 12},
    {0x020A, 11}, {0x0237, 11}, {0x014E, 11}, {0x0832, 12}, {0x08B2, 12}, {0x0817, 12},
    {0x0058, 11}, {0x00FC, 10}, {0x00BE, 10}, {0x06C2, 11}, {0x0822, 12}, {0x06C5, 11},
    {0x081D, 12}, {0x0000, 0}, {0x09CE, 12}, {0x0000, 0}, {0x03DC, 12}, {0x0000, 0},
    {0x0210, 10}, {0x0268, 10}, {0x06DA, 11}, {0x0812, 12}, {0x07F6, 12}, {0x0939, 12},
    {0x007B, 11}, {0x0311, 10}, {0x00A9, 9}, {0x06B6, 11}, {0x0812, 12}, {0x01D0, 12},
    {0x081D, 12}, {0x0000, 0}, {0x0669, 12}, {0x0000, 0}, {0x06EE, 12}, {0x0000, 0},
};

unsigned char _PlyrPose_bBlendFlag = 0;

void PlyrPoseInitFromSkeleton(AnimPose_t *pPose, AnimSkeleton_t *pSkeleton)
{
    unsigned int i;

    for (i = 0; i < pSkeleton->mUnknown6; i++) {
        pPose->mUnknown48[i * 3 + 0] = pSkeleton->mUnknown1040[i][0] << 4;
        pPose->mUnknown48[i * 3 + 1] = pSkeleton->mUnknown1040[i][1] << 4;
        pPose->mUnknown48[i * 3 + 2] = pSkeleton->mUnknown1040[i][2] << 4;
    }
}

void PlyrPoseWrite(AnimPose_t *pPose, BitStream_t *pStream)
{
    short saved75[3];
    short saved57[3];
    short *pValues;
    unsigned int i;

    saved75[0] = pPose->mUnknown48[75];
    saved75[1] = pPose->mUnknown48[76];
    saved75[2] = pPose->mUnknown48[77];
    saved57[0] = pPose->mUnknown48[57];
    saved57[1] = pPose->mUnknown48[58];
    saved57[2] = pPose->mUnknown48[59];
    pPose->mUnknown48[75] = pPose->mUnknown48[87];
    pPose->mUnknown48[76] = pPose->mUnknown48[88];
    pPose->mUnknown48[77] = pPose->mUnknown48[89];
    pPose->mUnknown48[57] = pPose->mUnknown48[84];
    pPose->mUnknown48[58] = pPose->mUnknown48[85];
    pPose->mUnknown48[59] = pPose->mUnknown48[86];
    pValues = pPose->mUnknown48;
    for (i = 0; i < 78; i++) {
        int bits = _PlyrPose_aChannelQuant[i].mUnknown2;

        if (bits) {
            int value = (pValues[i] + (_PlyrPose_aChannelQuant[i].mUnknown0 << 4)) >> 4;

            if (value >= 0) {
                int max = (1 << bits) - 1;

                value = (value > max ? max : value) << 4;
            } else {
                value = 0;
            }
            fn_80191068(pStream, (unsigned int)((value >> 4) & ((1 << bits) - 1)), bits);
        }
    }
    pPose->mUnknown48[75] = saved75[0];
    pPose->mUnknown48[76] = saved75[1];
    pPose->mUnknown48[77] = saved75[2];
    pPose->mUnknown48[57] = saved57[0];
    pPose->mUnknown48[58] = saved57[1];
    pPose->mUnknown48[59] = saved57[2];
    fn_80030554(pStream, pPose->mUnknown8, 16, 2048.0f);
    fn_80191068(pStream, pPose->mUnknown32 >> 8, 16);
}

void PlyrPoseRead(AnimPose_t *pPose, BitStream_t *pStream)
{
    short *pValue = pPose->mUnknown48;
    PlyrPoseQuant_t *pQuant = _PlyrPose_aChannelQuant;
    unsigned int i;

    for (i = 0; i < 78; i++, pQuant++, pValue++) {
        unsigned long long value = 0;

        if (pQuant->mUnknown2) {
            value = ReadBitStream(pStream, pQuant->mUnknown2);
        }
        value *= 16;
        *pValue = value - pQuant->mUnknown0 * 16;
    }
    fn_800301C4(pStream, pPose->mUnknown8, 16, 2048.0f);
    pPose->mUnknown32 = (int)ReadBitStream(pStream, 16) << 8;
}

void PlyrPoseWritePart(Object_8003DEC4 *pObject, unsigned int index, BitStream_t *pStream)
{
    unsigned long long bits = 1;

    if (!(pObject->mUnknown20 & 5)) {
        bits = 0;
    }
    bits |= (pObject->mUnknown116[index].mUnknown4 << 1) & 0x1E;
    bits |= (pObject->mUnknown116[index].mUnknown5 << 5) & 0x1E0;
    bits |= (pObject->mUnknown116[index].mUnknown6 << 9) & 0x7E00;
    bits |= (pObject->mUnknown116[index].mUnknown8 << 11) & 0x1F8000;
    bits |= (pObject->mUnknown116[index].mUnknown0 << 21) & 0x200000;
    fn_80191068(pStream, bits, 22);
}

int PlyrPoseReadPart(PlyrPosePart_t *pElement, BitStream_t *pStream)
{
    unsigned long long bits = ReadBitStream(pStream, 22);

    pElement->mUnknown4 = (bits >> 1) & 0xF;
    pElement->mUnknown5 = (bits >> 5) & 0xF;
    pElement->mUnknown6 = (bits >> 9) & 0x3F;
    pElement->mUnknown8 = ((bits >> 15) & 0x3F) << 4;
    pElement->mUnknown0 = (bits >> 21) & 1;
    return bits & 1;
}

void PlyrPoseBlendRawEntries(Object_8003DEC4 *pObject, int a, unsigned int index);

/* 4.12 fixed-point lerp of two halfwords. */
static inline short _PlyrPoseLerp12(short a, short b, short t)
{
    return a + (((b - a) * t) >> 12);
}

void PlyrPoseLerpPart(Object_8003DEC4 *pObject, BitStream_t *pStreamA, BitStream_t *pStreamB, float t, unsigned int index,
                 int skip)
{
    PlyrPosePart_t from;
    PlyrPosePart_t to;

    if (skip) {
        if (pStreamA) {
            ReadBitStream(pStreamA, 22);
        }
        if (pStreamB) {
            ReadBitStream(pStreamB, 22);
        }
        return;
    }
    PlyrPoseReadPart(&from, pStreamB);
    PlyrPoseReadPart(&to, pStreamA);
    pObject->mUnknown116[index].mUnknown8 = to.mUnknown8 =
        _PlyrPoseLerp12(from.mUnknown8, to.mUnknown8, (short)(int)(t * 4096.0f));
    pObject->mUnknown116[index].mUnknown4 = to.mUnknown4;
    pObject->mUnknown116[index].mUnknown5 = to.mUnknown5;
    pObject->mUnknown116[index].mUnknown6 = to.mUnknown6;
    pObject->mUnknown116[index].mUnknown0 = to.mUnknown0;
    if (fn_800ADD7C(pObject->mUnknown116, index)) {
        PlyrPoseBlendRawEntries(pObject, fn_800ADEFC(pObject->mUnknown116, index), index);
    }
}

void PlyrPoseWriteBlend(Object_8003DEC4 *pObject, BitStream_t *pStream)
{
    unsigned int count = pObject->mUnknown828 > 7 ? 7 : pObject->mUnknown828;
    unsigned int blends = pObject->mUnknown260 > 2 ? 2 : pObject->mUnknown260;

    fn_80191068(pStream, count, 3);
    fn_80191068(pStream, blends, 2);
    fn_80191068(pStream, pObject->mUnknown264[0].mUnknown6, 16);
    fn_80191068(pStream, (unsigned long long)pObject->mUnknown264[1].mUnknown0, 32);
    fn_80191068(pStream, pObject->mUnknown264[1].mUnknown6, 16);
}

void PlyrPoseSetBlend(Object_8003DEC4 *pObject, AnimBlendList *pBlend);
void PlyrPoseClearBlend(Object_8003DEC4 *pObject);

void PlyrPoseLerpBlend(Object_8003DEC4 *pObject, BitStream_t *pStreamA, BitStream_t *pStreamB, float t, int skip)
{
    AnimBlendList blend;
    float from;
    float to;
    int count;
    int max;
    int handle;
    float weight;

    if (skip) {
        if (pStreamA) {
            ReadBitStream(pStreamA, 64);
            ReadBitStream(pStreamA, 5);
        }
        if (pStreamB) {
            ReadBitStream(pStreamB, 69);
            ReadBitStream(pStreamB, 5);
        }
        return;
    }
    from = (int)ReadBitStream(pStreamB, 3);
    to = (int)ReadBitStream(pStreamA, 3);
    to = (to - from) * t + from;
    pObject->mUnknown828 = (int)to;
    max = ReadBitStream(pStreamB, 2);
    count = ReadBitStream(pStreamA, 2);
    if (count > max) {
        count = max;
    }
    blend.mUnknown0 = count;
    pObject->mUnknown260 = blend.mUnknown0;
    if (blend.mUnknown0) {
        handle = fn_801BBE5C(3, 0);
        ReadBitStream(pStreamA, 16);
        long long frame = ReadBitStream(pStreamB, 16);
        ReadBitStream(pStreamA, 32);
        weight = ReadBitStream(pStreamB, 32);
        blend.mUnknown4[0].mpUnknown40 = AnimFileGetFrame(fn_801BC084(handle), 0, handle, frame);
        blend.mUnknown4[0].mUnknown4 = 1.0f;
        pObject->mUnknown260 = 1;
        if (blend.mUnknown0 > 1) {
            ReadBitStream(pStreamA, 16);
            long long nextFrame = ReadBitStream(pStreamB, 16);
            blend.mUnknown4[1].mpUnknown40 = AnimFileGetFrame(fn_801BC084(handle), 0, handle, nextFrame);
            blend.mUnknown4[1].mUnknown4 = weight;
        } else {
            ReadBitStream(pStreamA, 16);
            ReadBitStream(pStreamB, 16);
        }
    } else {
        ReadBitStream(pStreamA, 64);
        ReadBitStream(pStreamB, 64);
    }
    if ((pObject->mUnknown828 >= 0 && pObject->mUnknown828 <= 6) || pObject->mUnknown260) {
        PlyrPoseSetBlend(pObject, &blend);
        pObject->mUnknown20 |= 0x10;
    } else {
        PlyrPoseClearBlend(pObject);
    }
}

void PlyrPoseApplyBlink(Object_8003DEC4 *pObject)
{
    short index;
    float *pValues;

    if (pObject->mUnknown20 & 0x80) {
        return;
    }
    index = pObject->mUnknown830;
    if (index == 0) {
        return;
    }
    pValues = pObject->mUnknown820;
    if (index >= pObject->mUnknown816) {
        return;
    }
    if (pObject->mUnknown828 >= 0 && pObject->mUnknown828 <= 6) {
        pValues[index] = _PlyrPose_afBlinkWeights[pObject->mUnknown828];
    } else {
        pValues[index] = 0.0f;
    }
}

void PlyrPoseBuildWorldMatrix(Object_8003DEC4 *pObject);

void PlyrPoseSetFromModel(FEPlyrModel_t *pRecord)
{
    Object_8003DEC4 *pObject = pRecord->mUnknown4;
    Object_800B267C *pMotion = &pRecord->mUnknown424;

    if (!fn_801784C4()) {
        pObject->mUnknown4[0] = pRecord->mUnknown424.mUnknown0;
        pObject->mUnknown4[1] = pMotion->mUnknown4;
        pObject->mUnknown4[2] = pMotion->mUnknown8;
        pObject->mUnknown36 = pMotion->mUnknown24;
    } else {
        pObject->mUnknown4[0] = -pRecord->mUnknown424.mUnknown0;
        pObject->mUnknown4[1] = -pMotion->mUnknown4;
        pObject->mUnknown4[2] = pMotion->mUnknown8;
        pObject->mUnknown36 = (pMotion->mUnknown24 - 0x800000) & 0xFFFFFF;
    }
    pObject->mUnknown972 = pRecord->mUnknown780;
    PlyrPoseBuildWorldMatrix(pObject);
}

void PlyrPoseBuildWorldMatrix(Object_8003DEC4 *pObject)
{
    fn_801D0508();
    fn_801D0C58(pObject->mUnknown4);
    fn_801D0ADC(pObject->mUnknown36 + 0x400000);
    fn_801D08FC(0x400000);
    if (pObject->mUnknown20 & 0x2000) {
        fn_801D0C58(pObject->mUnknown44.mUnknown8);
        fn_801D09EC(pObject->mUnknown44.mUnknown32);
    }
    fn_801D0F80(pObject->mUnknown908);
    fn_801D0544();
}

void PlyrPoseGetBoneTransform(Object_8003DEC4 *pObject, int bone, float *pOut, int *pAngles)
{
    fn_801D04C4();
    fn_801D06D4(pObject->mUnknown908);
    fn_801D0CFC(pObject->mUnknown24);
    fn_801D0664(pObject->mUnknown44.mUnknown52[bone]);
    fn_801D0FB8(pOut);
    if (pAngles) {
        fn_801D11F4(pAngles, 0);
    }
    fn_801D0544();
}

void PlyrPoseGetAttachTransform(Object_8003DEC4 *pObject, float *pOut, Quat_801EB488 *pRot)
{
    short bone = pObject->mUnknown44.mUnknown6;

    if (bone != -1) {
        float (*pMatrix)[4][4] = &pObject->mUnknown44.mUnknown52[bone];
        int angles[3];

        fn_801D04C4();
        fn_801D06D4(pObject->mUnknown908);
        fn_801D0CFC(pObject->mUnknown24);
        fn_801D0664(*pMatrix);
        fn_801D0C58(pObject->mUnknown44.mUnknown20);
        fn_801D0BCC(pObject->mUnknown44.mUnknown36[2], pObject->mUnknown44.mUnknown36[1], pObject->mUnknown44.mUnknown36[0]);
        fn_801D0FB8(pOut);
        fn_801D11F4(angles, 0);
        fn_801D0544();
        QuatFromEuler(pRot, angles[2], angles[1], angles[0]);
    } else {
        pOut[0] = pOut[1] = pOut[2] = 0.0f;
        QuatIdentity(pRot);
    }
}

void PlyrPoseBlendEntries(Object_8003DEC4 *pObject, int a)
{
    AnimBlendEntries(pObject, a, pObject->mUnknown100->mUnknown6);
}

void PlyrPoseBlendRootAngles(Object_8003DEC4 *pObject, void *a, unsigned short b, void *c)
{
    AnimBlendRootAngles(pObject, a, b, c);
}

void PlyrPoseBlendRawEntries(Object_8003DEC4 *pObject, int a, unsigned int index)
{
    AnimBlendRawEntries(pObject, a, index, pObject->mUnknown100->mUnknown6);
}

void PlyrPoseSetBlend(Object_8003DEC4 *pObject, AnimBlendList *pBlend)
{
    pObject->mUnknown260 = pBlend->mUnknown0;
    if (pObject->mUnknown816 && pBlend->mUnknown0) {
        AnimBlendWeights(pObject->mUnknown820, pBlend);
        if (pObject->mUnknown20 & 0x40000) {
            pObject->mUnknown264[0].mUnknown0 = pBlend->mUnknown4[0].mUnknown4;
            pObject->mUnknown264[0].mUnknown4 = pBlend->mUnknown4[0].mUnknown32;
            pObject->mUnknown264[0].mUnknown6 = pBlend->mUnknown4[0].mUnknown34;
            if (pBlend->mUnknown0 > 1) {
                pObject->mUnknown264[1].mUnknown0 = pBlend->mUnknown4[1].mUnknown4;
                pObject->mUnknown264[1].mUnknown4 = pBlend->mUnknown4[1].mUnknown32;
                pObject->mUnknown264[1].mUnknown6 = pBlend->mUnknown4[1].mUnknown34;
            }
        }
    }
    PlyrPoseApplyBlink(pObject);
}

void PlyrPoseClearBlend(Object_8003DEC4 *pObject)
{
    pObject->mUnknown20 &= ~0x10;
    if (pObject->mUnknown820) {
        AnimResetWeights(pObject->mUnknown820);
    }
}

void PlyrPoseInit(Object_8003DEC4 *pObject, AnimSkeleton_t *pSkeleton, AnimSkeleton_t **ppExtra,
                 AnimSkeleton_t *pSkeleton280, AnimSkeleton_t *pSkeleton596)
{
    unsigned int i;
    unsigned short count;

    pObject->mUnknown20 |= 1;
    pObject->mUnknown24 = 1.0f;
    pObject->mUnknown28 = 1.0f;
    pObject->mUnknown32 = 0;
    if (pSkeleton) {
        pObject->mUnknown100 = pSkeleton;
        count = pSkeleton->mUnknown6;
        pObject->mUnknown112 = (float (*)[4][4])fn_801D2B7C(count * sizeof(float[4][4]), 0, 0);
        pObject->mUnknown44.mUnknown4 = count + 1;
        pObject->mUnknown44.mUnknown0 = 0x100;
        pObject->mUnknown44.mUnknown2 = 0x202;
        pObject->mUnknown44.mUnknown48 = AnimAllocPoseChannels(count);
        pObject->mUnknown44.mUnknown52 = pObject->mUnknown112;
        PlyrPoseInitFromSkeleton(&pObject->mUnknown44, pObject->mUnknown100);
    }
    for (i = 0; i < 2; i++) {
        if (ppExtra && ppExtra[i]) {
            fn_800ADDFC(pObject, &pObject->mUnknown116[i], 1);
            pObject->mUnknown116[i].mUnknown68 = ppExtra[i];
            count = ppExtra[i]->mUnknown6;
            pObject->mUnknown116[i].mUnknown12.mUnknown0 = 0x100;
            pObject->mUnknown116[i].mUnknown12.mUnknown4 = count;
            pObject->mUnknown116[i].mUnknown12.mUnknown2 = 0x202;
            pObject->mUnknown116[i].mUnknown12.mUnknown48 = AnimAllocPoseChannels(count);
            pObject->mUnknown116[i].mUnknown12.mUnknown52 = 0;
            PlyrPoseInitFromSkeleton(&pObject->mUnknown116[i].mUnknown12, pObject->mUnknown116[i].mUnknown68);
        } else {
            fn_800ADDFC(pObject, &pObject->mUnknown116[i], 0);
            pObject->mUnknown116[i].mUnknown12.mUnknown48 = 0;
            pObject->mUnknown116[i].mUnknown12.mUnknown52 = 0;
        }
    }
    pObject->mUnknown104 = pSkeleton280;
    if (pSkeleton280) {
        fn_801C1F94(&pObject->mUnknown280, 0, sizeof(Block_800C2788));
        pObject->mUnknown280.mUnknown312 = pSkeleton280;
        pObject->mUnknown280.mUnknown1 = 13;
        pObject->mUnknown280.mUnknown256.mUnknown4 = pSkeleton280->mUnknown6;
        pObject->mUnknown280.mUnknown256.mUnknown0 = 0x100;
        pObject->mUnknown280.mUnknown256.mUnknown2 = 0x202;
        pObject->mUnknown280.mUnknown256.mUnknown48 = AnimAllocPoseChannels(pSkeleton280->mUnknown6);
        pObject->mUnknown280.mUnknown256.mUnknown52 = 0;
        PlyrPoseInitFromSkeleton(&pObject->mUnknown280.mUnknown256, pObject->mUnknown280.mUnknown312);
        fn_800C2788(pObject, &pObject->mUnknown280, 1);
    } else {
        fn_800C2788(pObject, &pObject->mUnknown280, 0);
    }
    pObject->mUnknown108 = pSkeleton596;
    if (pSkeleton596) {
        fn_801C1F94(&pObject->mUnknown596, 0, sizeof(Block_800C2EC0));
        pObject->mUnknown596.mUnknown216 = pSkeleton596;
        pObject->mUnknown596.mUnknown1 = 11;
        pObject->mUnknown596.mUnknown160.mUnknown4 = pSkeleton596->mUnknown6;
        pObject->mUnknown596.mUnknown160.mUnknown0 = 0x100;
        pObject->mUnknown596.mUnknown160.mUnknown2 = 0x202;
        pObject->mUnknown596.mUnknown160.mUnknown48 = AnimAllocPoseChannels(pSkeleton596->mUnknown6);
        pObject->mUnknown596.mUnknown160.mUnknown52 = 0;
        PlyrPoseInitFromSkeleton(&pObject->mUnknown596.mUnknown160, pObject->mUnknown596.mUnknown216);
        fn_800C2EC0(pObject, &pObject->mUnknown596, 1);
    } else {
        fn_800C2EC0(pObject, &pObject->mUnknown596, 0);
    }
    pObject->mUnknown972 = 0;
}

void PlyrPoseFree(Object_8003DEC4 *pObject)
{
    unsigned int i;

    fn_801D2BD0(pObject->mUnknown112);
    fn_801D2BD0(pObject->mUnknown44.mUnknown48);
    for (i = 0; i < 2; i++) {
        if (pObject->mUnknown116[i].mUnknown12.mUnknown48) {
            fn_801D2BD0(pObject->mUnknown116[i].mUnknown12.mUnknown48);
        }
    }
    if (pObject->mUnknown280.mUnknown256.mUnknown48) {
        fn_801D2BD0(pObject->mUnknown280.mUnknown256.mUnknown48);
    }
    if (pObject->mUnknown596.mUnknown160.mUnknown48) {
        fn_801D2BD0(pObject->mUnknown596.mUnknown160.mUnknown48);
    }
}

void PlyrPoseUpdate(Object_8003DEC4 *pObject)
{
    fn_801D0470(1);
    fn_801D0494();
    if (pObject->mUnknown830) {
        if (--pObject->mUnknown828 < 0) {
            pObject->mUnknown828 = fn_802372EC(1, 480) + 30;
        }
    }
    AnimBuildPoseMatrices(pObject);
}

void PlyrPoseDelayBlink(Object_8003DEC4 *pObject)
{
    if (pObject->mUnknown828 > 8) {
        pObject->mUnknown828++;
    } else {
        pObject->mUnknown828 = 8;
    }
}

void PlyrPoseStartBlink(Object_8003DEC4 *pObject)
{
    pObject->mUnknown828 = 6;
}

int PlyrPoseGetStreamBits(int skip)
{
    int bits = 3;

    if (!skip) {
        int i;

        for (i = 0; i < 78; i++) {
            bits += _PlyrPose_aChannelQuant[i].mUnknown2;
        }
        bits += 113;
    }
    return bits + 124;
}

/* One flag bit of the player word +20 as a byte. */
static inline unsigned char _PlyrPoseFlagBit(unsigned int flags, int shift)
{
    return (flags >> shift) & 1;
}

void PlyrPoseWriteState(Object_8003DEC4 *pObject, BitStream_t *pStream)
{
    unsigned int bit11;

    fn_80191068(pStream, _PlyrPoseFlagBit(pObject->mUnknown20, 0), 1);
    fn_80191068(pStream, _PlyrPoseFlagBit(pObject->mUnknown20, 17), 1);
    bit11 = (pObject->mUnknown20 >> 11) & 1;
    fn_80191068(pStream, bit11, 1);
    if (!bit11) {
        PlyrPoseWrite(&pObject->mUnknown44, pStream);
        PlyrPoseWritePart(pObject, 0, pStream);
        PlyrPoseWritePart(pObject, 1, pStream);
        PlyrPoseWriteBlend(pObject, pStream);
    }
    fn_80030554(pStream, pObject->mUnknown4, 16, 256.0f);
    fn_80191068(pStream, (pObject->mUnknown36 >> 12) & 0xFFF, 12);
}

void PlyrPoseReadState(Object_8003DEC4 *pObject, BitStream_t *pStreamA, BitStream_t *pStreamB, BitStream_t *pStreamC,
                 BitStream_t *pStreamD, float t)
{
    short valuesB[192];
    short valuesC[192];
    short valuesD[192];
    AnimPose_t poseB;
    AnimPose_t poseD;
    AnimPose_t poseC;
    float posA[3];
    float posB[3];
    unsigned char flag;
    int angleA;
    int angleB;

    poseB.mUnknown48 = valuesB;
    poseD.mUnknown48 = valuesD;
    poseC.mUnknown48 = valuesC;

    flag = ReadBitStream(pStreamB, 1);
    ReadBitStream(pStreamA, 1);
    if (pStreamD) {
        ReadBitStream(pStreamD, 1);
    }
    if (pStreamC) {
        ReadBitStream(pStreamC, 1);
    }
    if (flag == 1) {
        pObject->mUnknown20 |= 1;
    } else {
        pObject->mUnknown20 &= ~1;
    }

    flag = ReadBitStream(pStreamB, 1);
    ReadBitStream(pStreamA, 1);
    if (pStreamD) {
        ReadBitStream(pStreamD, 1);
    }
    if (pStreamC) {
        ReadBitStream(pStreamC, 1);
    }
    if (flag == 1) {
        fn_801477F0(pObject);
    } else {
        fn_80147840(pObject);
    }

    flag = ReadBitStream(pStreamB, 1);
    ReadBitStream(pStreamA, 1);
    if (pStreamC) {
        ReadBitStream(pStreamC, 1);
    }
    if (pStreamD) {
        ReadBitStream(pStreamD, 1);
    }
    if (flag == 0) {
        PlyrPoseRead(&poseB, pStreamB);
        PlyrPoseRead(&pObject->mUnknown44, pStreamA);
        if (pStreamC) {
            PlyrPoseRead(&poseC, pStreamC);
        }
        if (pStreamD) {
            PlyrPoseRead(&poseD, pStreamD);
        }
        if (pStreamC) {
            PlyrPoseLerpPart(pObject, pStreamC, 0, t, 0, 1);
            PlyrPoseLerpPart(pObject, pStreamC, 0, t, 0, 1);
            PlyrPoseLerpBlend(pObject, pStreamC, 0, t, 1);
        }
        if (pStreamD) {
            PlyrPoseLerpPart(pObject, pStreamD, 0, t, 0, 1);
            PlyrPoseLerpPart(pObject, pStreamD, 0, t, 0, 1);
            PlyrPoseLerpBlend(pObject, pStreamD, 0, t, 1);
        }
        PlyrPoseLerpPart(pObject, pStreamA, pStreamB, t, 0, 0);
        PlyrPoseLerpPart(pObject, pStreamA, pStreamB, t, 1, 0);
        PlyrPoseLerpBlend(pObject, pStreamA, pStreamB, t, 0);
    }

    if (pStreamC) {
        fn_800301C4(pStreamC, posB, 16, 256.0f);
        ReadBitStream(pStreamC, 12);
    }
    if (pStreamD) {
        fn_800301C4(pStreamD, posB, 16, 256.0f);
        ReadBitStream(pStreamD, 12);
    }
    fn_800301C4(pStreamB, posB, 16, 256.0f);
    fn_800301C4(pStreamA, posA, 16, 256.0f);
    fn_80227930(pObject->mUnknown4, posA, posB, t);
    angleB = (int)(ReadBitStream(pStreamB, 12) << 52 >> 40) & 0xFFF000;
    angleA = (int)(ReadBitStream(pStreamA, 12) << 52 >> 40) & 0xFFF000;
    OrientLerpAngle(&pObject->mUnknown36, angleA, angleB, t);

    if (!pStreamC) {
        if (!pStreamD) {
            AnimBlendPose(&pObject->mUnknown44, &poseB, 0, 0, t, _PlyrPose_bBlendFlag);
        } else {
            AnimBlendPose(&pObject->mUnknown44, &poseB, 0, &poseD, t, _PlyrPose_bBlendFlag);
        }
    } else if (!pStreamD) {
        AnimBlendPose(&pObject->mUnknown44, &poseB, &poseC, 0, t, _PlyrPose_bBlendFlag);
    } else {
        AnimBlendPose(&pObject->mUnknown44, &poseB, &poseC, &poseD, t, _PlyrPose_bBlendFlag);
    }

    pObject->mUnknown44.mUnknown48[87] = pObject->mUnknown44.mUnknown48[75];
    pObject->mUnknown44.mUnknown48[88] = pObject->mUnknown44.mUnknown48[76];
    pObject->mUnknown44.mUnknown48[89] = pObject->mUnknown44.mUnknown48[77];
    pObject->mUnknown44.mUnknown48[84] = pObject->mUnknown44.mUnknown48[57];
    pObject->mUnknown44.mUnknown48[85] = pObject->mUnknown44.mUnknown48[58];
    pObject->mUnknown44.mUnknown48[86] = pObject->mUnknown44.mUnknown48[59];
    PlyrPoseBuildWorldMatrix(pObject);
    PlyrPoseUpdate(pObject);
}

void PlyrPoseSetBlendFlag(unsigned char value)
{
    _PlyrPose_bBlendFlag = value;
}
}
