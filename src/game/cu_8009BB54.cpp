#include "game/Table_80089904.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801EBC18.h"
#include "game/fn_801BA2A8.h"
#include "game/Item_80097440.h"

extern "C" {
unsigned int fn_8009B910(int index);
extern Block_8009B720 *lbl_803EA984[2];
void fn_801D0508(void);
void fn_801D0C58(void *p);
void fn_801D0ADC(int a);
void fn_801D08FC(int a);
void fn_801D0CFC(float a);
void fn_801D0F80(float m[4][4]);
void fn_801D0544(void);
void fn_801D04C4(void);
void fn_801D06D4(float m[4][4]);
void fn_801D0664(float m[4][4]);
void fn_801D0FB8(Vector_80039F5C *pOut);
void fn_801D11F4(void *pOut, int a);
void fn_801D0BCC(int a, int b, int c);
void fn_801EBEF8(Quat_801EB488 *pOut, int a, int b, int c);
void fn_801EB488(Quat_801EB488 *pRot);
void fn_8009BE0C(float m[4][4], Vector_80039F5C *pPos, int angle, float scale);
void fn_8009BFF8(Object_80039F5C *p, Vector_80039F5C *pOut, Quat_801EB488 *pRot, int joint);
void fn_800B267C(Object_800B26B0 *pMotion);
void fn_800C89BC(Object_80039F5C *p);
void fn_800AF804(Entry_800AF82C *p);
void fn_8009CF30(Block_8009C6F4 *pBlock, Pose_80041930 *pPose);
signed char fn_8009C4B0(Table_80089904 *pTable, const unsigned char *pValues);
}

extern "C" float fn_8009BB54(int index)
{
    float result = 900 - fn_8009B910(index);
    Block_8009B720 *pBlock = lbl_803EA984[index];

    if (pBlock->mUnknown4.mEntries[index].mpCallbackC != 0) {
        result = pBlock->mUnknown4.mEntries[index].mpCallbackC(pBlock->mUnknown4.mUnknown28);
    }
    return result;
}

extern "C" void fn_8009BC38(Object_80039F5C *p, Block_80170E64 *pBlock)
{
    fn_801C1F94(p, 0, 0x408);
    fn_800B267C(&p->mMotion);
    p->mUnknown768 = 1.0f;
    p->mpUnknown4 = pBlock;
    p->mUnknown292 = 0;
    p->mUnknown776 = 0;
    p->mUnknown777 = 0;
    p->mUnknown772 = 1.0f;
    p->mUnknown9[2] = 1;
    p->mUnknown778 = -1;
    fn_800C89BC(p);
    fn_800AF804((Entry_800AF82C *)p->mUnknown816);
    fn_8009CF30((Block_8009C6F4 *)&p->mUnknown16, &pBlock->mUnknown44);
    fn_8009CF30((Block_8009C6F4 *)&p->mUnknown108, &pBlock->mUnknown44);
    fn_8009CF30((Block_8009C6F4 *)&p->mUnknown200, &pBlock->mUnknown44);
    p->mpUnknown780 = 0;
}

extern "C" void fn_8009BE0C(float m[4][4], Vector_80039F5C *pPos, int angle, float scale)
{
    Vector_80039F5C pos;

    fn_801D0508();
    fn_801D0CFC(1.0f / scale);
    fn_801D08FC(-0x400000);
    fn_801D0ADC(-(angle + 0x400000));
    pos.mX = -pPos->mX;
    pos.mY = -pPos->mY;
    pos.mZ = -pPos->mZ;
    fn_801D0C58(&pos);
    fn_801D0F80(m);
    fn_801D0544();
}

extern "C" void fn_8009BFF8(Object_80039F5C *p, Vector_80039F5C *pOut, Quat_801EB488 *pRot, int joint)
{
    Block_80170E64 *pBlock = p->mpUnknown4;

    if (joint != -1) {
        float (*m)[4] = pBlock->mUnknown44.mUnknown52[joint];
        Angles_801EBC18 angles;

        fn_801D04C4();
        fn_801D06D4(p->mUnknown640);
        fn_801D0664(m);
        fn_801D0C58(pBlock->mUnknown44.mUnknown20);
        fn_801D0BCC(pBlock->mUnknown44.mUnknown36[2], pBlock->mUnknown44.mUnknown36[1],
                    pBlock->mUnknown44.mUnknown36[0]);
        fn_801D0FB8(pOut);
        fn_801D11F4(&angles, 0);
        fn_801D0544();
        fn_801EBEF8(pRot, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
    } else {
        pOut->mX = pOut->mY = pOut->mZ = 0.0f;
        fn_801EB488(pRot);
    }
}

extern "C" int fn_8009C3F8(Table_80089904 *pTable, void *a, void *b, Object_80039F5C *pRecord, unsigned short c)
{
    int index = fn_8009C4B0(pTable, (unsigned char *)&pRecord->mUnknown1008);

    if (index >= 0) {
        fn_801BA2A8(a, b, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, c, pRecord, 1.0f);
    }
    return 0;
}
