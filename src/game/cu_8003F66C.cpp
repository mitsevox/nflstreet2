#include "game/Object_80039F5C.h"
#include "game/cu_801442FC.h"
#include "game/cu_80136B1C.h"

/* Partial comparison source for the inferred grouping 0x8003F66C-0x800400CC.
   Not a recovered original file. The original assembly stays linked; only the
   bodies below are compiled and measured. */

/* Record reached through the first argument of fn_8003F66C-fn_8003F754.
   Only the accessed fields are declared; the size is unknown. */
struct Object_8003F66C {
    int mUnknown0;
    int mUnknown4;
    float (*mpUnknown8)[3];
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
    int mUnknown24;
    float mUnknown28;
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    unsigned char mUnknown34;
    char mUnknown35[1];
    float mUnknown36;
    float mUnknown40;
    unsigned char mUnknown44;
};

/* Callback record requested as 0x2B8 bytes by fn_8003FAC4. */
struct Object_8003F768 {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    char mUnknown16[4];
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    float mUnknown32[4][4];
    int mUnknown96;
    int mUnknown100;
    int mUnknown104;
    Quat_801EB488 mUnknown108;
    char mUnknown124[32];
    int mUnknown156;
    int mUnknown160;
    char mUnknown164[488];
    float mUnknown652;
    unsigned char mUnknown656;
    char mUnknown657[3];
    Object_80144310 *mpUnknown660;
    char mUnknown664[12];
    int mUnknown676;
    int mUnknown680;
    Tracker_801442FC mUnknown684;
    int mUnknown692;
};

struct Init_8003F768 {
    int mUnknown0;
    int mUnknown4;
    Object_8003F768 *mpUnknown8;
    int mUnknown12;
};

extern "C" {
void fn_8019CEE8(Object_8003F768 *p);
void fn_8019CFD0(Object_8003F768 *p);
void fn_801DCF8C(int type);
void fn_801DD320(int handle, int item);
}

#include "engine/cu_80227F14.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/bitstream.h"
#include "game/fn_80054138.h"

extern "C" {
unsigned char fn_8003F95C(BitStream_t *pStream, Vector_80039F5C *pPos, Quat_801EB488 *pRot,
                          Vector_80039F5C *pLinkPos, Quat_801EB488 *pLinkRot, Object_80039F5C **ppObject,
                          int *pIndex, unsigned char *pFlag);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
void fn_801EC048(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB, float t);
void fn_80030CA4(Object_80039F5C *pA, Object_80039F5C *pB);
}

extern "C" {
int fn_80027DF0(void);
unsigned int fn_80236398(int a);
void fn_8019CE3C(Object_8003F768 *p);
void fn_8019CF5C(Object_8003F768 *p, int index);
void fn_8019CFF4(Object_8003F768 *p);
void fn_801A5050(int a, Vector_80039F5C *pPos, float value, float *pColor);
void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030304(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_8003065C(void *pStream, float *pValues, int bits, float scale);
void fn_800423F8(Object_8003DEC4 *p, float *pPos, Quat_801EB488 *pRot);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_80030CB8(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0C58(float *p);
void fn_801D0860(Quat_801EB488 *p);
void fn_801D0F80(float (*p)[4]);
void fn_801D0544(void);
void fn_801DCF0C(int type, int size, int count,
                 void (*pInit)(Object_8003F768 *, Init_8003F768 *),
                 void (*pDestroy)(Object_8003F768 *));
void fn_801DD0C8(int owner, int type, int a, int (*pCallback)(Object_8003F768 *));
Object_8003F768 *fn_801DD268(int owner, int type, int a, Init_8003F768 *pInit);
void fn_801DD3AC(int owner, Object_8003F768 *p, int flags);
int fn_8003FBF0(Object_8003F768 *p);
}

extern "C" void fn_8003F66C(Object_8003F66C *p)
{
    p->mUnknown0 = 0;
    p->mUnknown4 = 0;
    p->mpUnknown8 = 0;
    p->mUnknown12 = 4;
    p->mUnknown28 = 1.0f;
    p->mUnknown32 = 255;
    p->mUnknown33 = 255;
    p->mUnknown34 = 255;
    p->mUnknown36 = 1.0f;
    p->mUnknown40 = 1.0f;
    p->mUnknown44 = 0;
}

extern "C" void fn_8003F6B0(Object_8003F66C *p)
{
}

extern "C" void fn_8003F6B4(Object_8003F66C *p, float (*pData)[3], int a)
{
    p->mpUnknown8 = pData;
    p->mUnknown0 = 0;
    p->mUnknown4 = a;
}

extern "C" void fn_8003F6C8(Object_8003F66C *p, unsigned char a, unsigned char b, unsigned char c)
{
    p->mUnknown32 = a;
    p->mUnknown33 = b;
    p->mUnknown34 = c;
}

extern "C" void fn_8003F6D8(Object_8003F66C *p, float value)
{
    p->mUnknown28 = value;
}

extern "C" void fn_8003F6E0(Object_8003F66C *p, float value)
{
    p->mUnknown36 = value;
}

extern "C" void fn_8003F6E8(Object_8003F66C *p, float value)
{
    p->mUnknown40 = value;
}

extern "C" void fn_8003F6F0(Object_8003F66C *p, float *pValue)
{
    p->mpUnknown8[p->mUnknown0][0] = pValue[0];
    p->mpUnknown8[p->mUnknown0][1] = pValue[1];
    p->mpUnknown8[p->mUnknown0][2] = pValue[2];
    p->mUnknown0++;
}

extern "C" void fn_8003F744(Object_8003F66C *p)
{
    p->mUnknown0 = 0;
    p->mUnknown44 = 0;
}

extern "C" void fn_8003F754(Object_8003F66C *p, int a, int b, float c, float d)
{
    p->mUnknown12 = a;
    p->mUnknown16 = c;
    p->mUnknown20 = d;
    p->mUnknown24 = b;
}

extern "C" void fn_8003F768(Object_8003F768 *p, Init_8003F768 *pInit)
{
    float color[4];
    p->mUnknown4.mX = 0.0f;
    p->mUnknown4.mY = 0.0f;
    p->mUnknown4.mZ = 0.0f;
    p->mUnknown96 = 0;
    p->mUnknown100 = 0;
    p->mUnknown104 = 0;
    p->mpUnknown660 = 0;
    p->mUnknown676 = 0;
    p->mUnknown680 = 0xFFFF;
    fn_801442FC(&p->mUnknown684);
    p->mUnknown20 |= 1;
    p->mUnknown652 = 1.0f;
    if (pInit->mpUnknown8 == 0) {
        p->mUnknown24 = pInit->mUnknown0;
        p->mUnknown28 = pInit->mUnknown4;
        p->mUnknown156 = 0;
        p->mUnknown160 = 0;
        fn_8019CE3C(p);
    } else {
        p->mUnknown20 |= 4;
        p->mUnknown156 = pInit->mpUnknown8->mUnknown156;
        p->mUnknown160 = pInit->mpUnknown8->mUnknown160;
    }
    unsigned int packed = fn_80236398(0);
    color[0] = (packed & 255) * 0.0078125f;
    color[1] = ((packed >> 8) & 255) * 0.0078125f;
    color[2] = ((packed >> 16) & 255) * 0.0078125f;
    color[3] = (packed >> 24) * 0.0078125f;
    if (fn_80027DF0() == 0) {
        fn_801A5050(1, &p->mUnknown4, 0.4f, color);
    }
    p->mUnknown692 = pInit->mUnknown12;
    fn_8019CF5C(p, pInit->mUnknown12);
}

extern "C" void fn_8003F91C(Object_8003F768 *p)
{
    fn_8019CFD0(p);
    if (!(p->mUnknown20 & 4)) {
        fn_8019CEE8(p);
    }
}

extern "C" unsigned char fn_8003F95C(BitStream_t *pStream, Vector_80039F5C *pPos,
        Quat_801EB488 *pRot, Vector_80039F5C *pLinkPos, Quat_801EB488 *pLinkRot,
        Object_80039F5C **ppObject, int *pIndex, unsigned char *pFlag)
{
    unsigned char changed = (unsigned char)ReadBitStream(pStream, 1);
    int reference = (int)ReadBitStream(pStream, 32);
    Object_80039F5C *pObject = fn_8009BCE8(&reference);
    int index = (int)((unsigned int)ReadBitStream(pStream, 7) << 25) >> 25;
    if (pObject != 0) {
        Object_8003DEC4 *pPose = (Object_8003DEC4 *)pObject->mpUnknown4;
        pPose->mUnknown44.mUnknown6 = index;
        *pIndex = index;
        fn_800301C4(pStream, pPose->mUnknown44.mUnknown20, 13, 1024.0f);
        pPose->mUnknown44.mUnknown36[0] = (int)((unsigned int)ReadBitStream(pStream, 12) << 20) >> 8;
        pPose->mUnknown44.mUnknown36[1] = (int)((unsigned int)ReadBitStream(pStream, 12) << 20) >> 8;
        pPose->mUnknown44.mUnknown36[2] = (int)((unsigned int)ReadBitStream(pStream, 12) << 20) >> 8;
        fn_800423F8(pPose, &pLinkPos->mX, pLinkRot);
    } else {
        ReadBitStream(pStream, 39);
        ReadBitStream(pStream, 36);
    }
    fn_800301C4(pStream, &pPos->mX, 16, 256.0f);
    fn_80030304(pStream, &pRot->mX, 12, 1024.0f);
    *pFlag = (unsigned char)ReadBitStream(pStream, 1);
    *ppObject = pObject;
    return changed;
}

extern "C" void fn_8003FAC4(int owner)
{
    fn_801DCF0C(3, 0x2B8, 3, fn_8003F768, fn_8003F91C);
    if (owner != 0) {
        fn_801DD0C8(owner, 3, 0, fn_8003FBF0);
    }
}

extern "C" void fn_8003FB2C(void)
{
    fn_80228E18();
    fn_801DCF8C(3);
}

extern "C" Block_80170E64 *fn_8003FB54(int owner, Block_80170E64 *pFirst,
                                              int a, int b, int index)
{
    Init_8003F768 init;
    init.mUnknown0 = a;
    init.mUnknown4 = b;
    init.mpUnknown8 = (Object_8003F768 *)pFirst;
    init.mUnknown12 = index;
    Object_8003F768 *p = fn_801DD268(owner, 3, 0, &init);
    fn_801DD3AC(owner, p, 8);
    return (Block_80170E64 *)p;
}

extern "C" void fn_8003FBB4(int handle, int item)
{
    if (item) {
        fn_801DD320(handle, item);
        fn_80228D58(item);
    }
}

extern "C" int fn_8003FBF0(Object_8003F768 *p)
{
    if (p->mUnknown20 & 1) {
        fn_801D0470(fn_80228668());
        fn_801D04C4();
        fn_801D0508();
        fn_801D0C58(&p->mUnknown4.mX);
        fn_801D0860(&p->mUnknown108);
        fn_801D0F80(p->mUnknown32);
        fn_801D0544();
        fn_8019CFF4(p);
        p->mUnknown656 = 0;
        fn_801D0544();
    }
    return 0;
}

extern "C" int fn_8003FC68(void)
{
    return 212;
}

extern "C" void fn_8003FC70(Block_80170E64 *pBlock, BitStream_t *pStream)
{
    int index = fn_80137534(pBlock);
    Object_80039F5C *pObject = fn_80137AD0(fn_80137ABC(index));
    int changed = index == fn_80030CB8();
    fn_80191068(pStream, changed, 1);
    if (changed == 1 && pObject != 0) {
        Object_8003DEC4 *pPose = (Object_8003DEC4 *)pObject->mpUnknown4;
        int reference;
        fn_8009BD2C(pObject, &reference);
        fn_80191068(pStream, (unsigned int)reference, 32);
        fn_80191068(pStream, pPose->mUnknown44.mUnknown6, 7);
        fn_80030554(pStream, pPose->mUnknown44.mUnknown20, 13, 1024.0f);
        fn_80191068(pStream, pPose->mUnknown44.mUnknown36[0] >> 12, 12);
        fn_80191068(pStream, pPose->mUnknown44.mUnknown36[1] >> 12, 12);
        fn_80191068(pStream, pPose->mUnknown44.mUnknown36[2] >> 12, 12);
    } else {
        fn_80191068(pStream, 0, 32);
        fn_80191068(pStream, -1, 7);
        fn_80191068(pStream, 0, 39);
        fn_80191068(pStream, 0, 36);
    }
    if (pBlock->mUnknown152 == 1) {
        pBlock->mUnknown152 = 0;
        fn_80030554(pStream, &pBlock->mUnknown124.mX, 16, 256.0f);
        fn_8003065C(pStream, &pBlock->mUnknown136.mX, 12, 1024.0f);
    } else {
        fn_80030554(pStream, &pBlock->mUnknown4.mX, 16, 256.0f);
        fn_8003065C(pStream, &pBlock->mUnknown108.mX, 12, 1024.0f);
    }
    if (pBlock->mUnknown20 & 2) {
        fn_80191068(pStream, 1, 1);
    } else {
        fn_80191068(pStream, 0, 1);
    }
}

extern "C" void fn_8003FE90(Block_80170E64 *pBlock, BitStream_t *pStream1, BitStream_t *pStream0,
                            BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    Vector_80039F5C pos0;
    Vector_80039F5C pos1;
    Vector_80039F5C linkPos0;
    Vector_80039F5C linkPos1;
    Quat_801EB488 rot0;
    Quat_801EB488 rot1;
    Quat_801EB488 linkRot0;
    Quat_801EB488 linkRot1;
    unsigned char flag = 0;
    Object_80039F5C *pObject0;
    int index0;
    Object_80039F5C *pObject1;
    int index1;
    unsigned char changed0;
    unsigned char changed1;

    if (pStream2) {
        fn_8003F95C(pStream2, &pos0, &rot0, &linkPos0, &linkRot0, &pObject0, &index0, &flag);
    }
    if (pStream3) {
        fn_8003F95C(pStream3, &pos0, &rot0, &linkPos0, &linkRot0, &pObject0, &index0, &flag);
    }
    changed0 = fn_8003F95C(pStream0, &pos0, &rot0, &linkPos0, &linkRot0, &pObject0, &index0, &flag);
    changed1 = fn_8003F95C(pStream1, &pos1, &rot1, &linkPos1, &linkRot1, &pObject1, &index1, &flag);
    if (pObject0 != 0 && pObject1 != 0) {
        Object_8003DEC4 *pPose = (Object_8003DEC4 *)pObject0->mpUnknown4;

        if (index0 == index1) {
            fn_80227930(&pBlock->mUnknown4, &linkPos1, &linkPos0, t);
            fn_801EC048(&pBlock->mUnknown108, &linkRot1, &linkRot0, t);
        } else {
            pBlock->mUnknown4.mX = linkPos1.mX;
            pBlock->mUnknown4.mY = linkPos1.mY;
            pBlock->mUnknown4.mZ = linkPos1.mZ;
            pBlock->mUnknown108.mX = linkRot1.mX;
            pBlock->mUnknown108.mY = linkRot1.mY;
            pBlock->mUnknown108.mZ = linkRot1.mZ;
            pBlock->mUnknown108.mW = linkRot1.mW;
            pPose->mUnknown44.mUnknown6 = index1;
        }
    } else {
        fn_80227930(&pBlock->mUnknown4, &pos1, &pos0, t);
        fn_801EC048(&pBlock->mUnknown108, &rot1, &rot0, t);
    }
    pBlock->mUnknown660 = fn_80054138(&pBlock->mUnknown4.mX);
    if (changed0 | changed1) {
        fn_80030CA4(pObject0, pObject1);
    }
    if (flag) {
        pBlock->mUnknown20 |= 2;
    } else {
        pBlock->mUnknown20 &= ~2;
    }
}

extern "C" void fn_800400BC(Block_80170E64 *pBlock, Object_80041904 *pLinked)
{
    pBlock->mpUnknown676 = pLinked;
}

extern "C" Object_80041904 *fn_800400C4(Block_80170E64 *pBlock)
{
    return pBlock->mpUnknown676;
}
