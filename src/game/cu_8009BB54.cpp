#include "game/Table_80089904.h"
#include <string.h>
#include "engine/llquat.h"
#include "game/AnimChanStartAnim.h"
#include "game/Item_80097440.h"

extern "C" {
unsigned int fn_8009B910(int index);
extern Block_8009B720 *lbl_803EA984[2];
void MatPushUnit(void);
void MatTranslate(void *p);
void MatRotZ(int a);
void MatRotX(int a);
void MatScale(float a);
void MatStore(float m[4][4]);
void MatPop(void);
void MatPush(void);
void MatLoad(float m[4][4]);
void MatCat(float m[4][4]);
void MatGetPos(Vector_80039F5C *pOut);
void MatGetRotByOrder(void *pOut, int a);
void MatRotZYX(int a, int b, int c);
void QuatFromEuler(Quat_801EB488 *pOut, int a, int b, int c);
void QuatIdentity(Quat_801EB488 *pRot);
void fn_8009BE0C(float m[4][4], Vector_80039F5C *pPos, int angle, float scale);
void fn_8009BFF8(Object_80039F5C *p, Vector_80039F5C *pOut, Quat_801EB488 *pRot, int joint);
void fn_800B267C(Object_800B26B0 *pMotion);
void fn_800C89BC(Object_80039F5C *p);
void fn_800AF804(Entry_800AF82C *p);
void fn_8009CF30(Block_8009C6F4 *pBlock, AnimPose_t *pPose);
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
    memset(p, 0, 0x408);
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

    MatPushUnit();
    MatScale(1.0f / scale);
    MatRotX(-0x400000);
    MatRotZ(-(angle + 0x400000));
    pos.mX = -pPos->mX;
    pos.mY = -pPos->mY;
    pos.mZ = -pPos->mZ;
    MatTranslate(&pos);
    MatStore(m);
    MatPop();
}

extern "C" void fn_8009BFF8(Object_80039F5C *p, Vector_80039F5C *pOut, Quat_801EB488 *pRot, int joint)
{
    Block_80170E64 *pBlock = p->mpUnknown4;

    if (joint != -1) {
        float (*m)[4] = pBlock->mUnknown44.mUnknown52[joint];
        QuatEulerAngles_t angles;

        MatPush();
        MatLoad(p->mUnknown640);
        MatCat(m);
        MatTranslate(pBlock->mUnknown44.mUnknown20);
        MatRotZYX(pBlock->mUnknown44.mUnknown36[2], pBlock->mUnknown44.mUnknown36[1],
                    pBlock->mUnknown44.mUnknown36[0]);
        MatGetPos(pOut);
        MatGetRotByOrder(&angles, 0);
        MatPop();
        QuatFromEuler(pRot, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
    } else {
        pOut->mX = pOut->mY = pOut->mZ = 0.0f;
        QuatIdentity(pRot);
    }
}

extern "C" int fn_8009C3F8(Table_80089904 *pTable, void *a, void *b, Object_80039F5C *pRecord, unsigned short c)
{
    int index = fn_8009C4B0(pTable, (unsigned char *)&pRecord->mUnknown1008);

    if (index >= 0) {
        AnimChanStartAnim(a, b, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, c, pRecord, 1.0f);
    }
    return 0;
}
