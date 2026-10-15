#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80178D18.h"

struct Record_80148424;

extern "C" {
extern int lbl_803EB2A8;
extern int lbl_803EB2AC;
extern Class_80148A58 *lbl_8031BDBC[];

void fn_800EFE1C(int a, State_80039F5C *pQueue);
void fn_801D31F0(void *pDest, const void *pSource, int size);
void fn_80148424(Record_80148424 *pA, Record_80148424 *pB);
void fn_80149040(Object_80039F5C *p);
void fn_800B6474(int index, unsigned char team);
void fn_800B6658(Object_80039F5C *p);
void fn_800B6714(Object_80039F5C *p, int index);
void fn_80148814(Object_80039F5C *p);

void fn_801485B4(void)
{
    lbl_803EB2A8 = 1;
}

void fn_801485C0(void)
{
    lbl_803EB2A8 = 0;
    lbl_803EB2AC = 15;
}

int fn_801485D4(void)
{
    return lbl_803EB2A8 != 0;
}

void fn_801485EC(int value)
{
    lbl_803EB2AC = value;
}

void fn_801485F4(void)
{
    lbl_803EB2A8 = 2;
    lbl_8031BDBC[lbl_803EB2AC]->vfn_01();
}

void fn_80148644(void)
{
    lbl_8031BDBC[lbl_803EB2AC]->vfn_02();
    lbl_803EB2A8 = 1;
    fn_801485C0();
}

int fn_80148698(short *pRatings, Object_80039F5C *p, int value)
{
    return value;
}

int fn_801486A0(void)
{
    return lbl_803EB2AC;
}

void fn_801486A8(void)
{
    for (unsigned short team = 0; team < 2; ++team) {
        for (unsigned short index = 0; index < 7; ++index) {
            Object_80039F5C *p = fn_80039F5C((unsigned char)team, index);
            p->mMotion.mPos.mX = 0.0f;
            p->mMotion.mPos.mY = -((float)index * 3.0f);
            p->mpUnknown4->mUnknown20 |= 1;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = 0x800000;
            p->mUnknown512.mUnknown4 = 0x800000;
            p->mUnknown512.mUnknown0 = 0.14f;
            p->mFlags &= ~0x40000U;
            p->mUnknown9[2] = (unsigned int)index < (unsigned int)fn_80178D70((unsigned char)team);
        }
    }
}

void fn_801487C0(int team, unsigned char begin)
{
    for (unsigned char index = begin; index < 7; ++index) {
        fn_80148814(fn_80039F5C(team, index));
    }
}

void fn_80148814(Object_80039F5C *p)
{
    Object_80137ABC *pBall = fn_80137C48(p);
    if (pBall) {
        Vector_80039F5C velocity = {0.0f, 0.0f, 0.0f};
        fn_80137EE0(pBall, &velocity);
        fn_8013791C(pBall, 5, 0);
    }
    p->mMotion.mPos.mY = -100.0f;
    p->mMotion.mPos.mX = -100.0f;
    p->mpUnknown4->mUnknown20 &= ~1U;
    fn_800EFE1C(0, p->mpState);
    p->mFlags |= 0x40000;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown0 = 0.0f;
    p->mUnknown9[2] = 0;
    p->mUnknown512.mUnknown8 = 0;
    p->mUnknown512.mUnknown4 = 0;
}

void fn_801488D4(Object_80039F5C *pA, Object_80039F5C *pB)
{
    unsigned char motion[88];
    unsigned char control[16];
    unsigned char *pBytesA = (unsigned char *)pA;
    unsigned char *pBytesB = (unsigned char *)pB;
    unsigned short id = pA->mUnknown2908;
    pA->mUnknown2908 = pB->mUnknown2908;
    pB->mUnknown2908 = id;

    fn_801D31F0(motion, pBytesA + 424, sizeof(motion));
    fn_801D31F0(pBytesA + 424, pBytesB + 424, sizeof(motion));
    fn_801D31F0(pBytesB + 424, motion, sizeof(motion));
    fn_801D31F0(control, &pA->mUnknown512, sizeof(control));
    fn_801D31F0(&pA->mUnknown512, &pB->mUnknown512, sizeof(control));
    fn_801D31F0(&pB->mUnknown512, control, sizeof(control));
    fn_801D31F0(control, &pA->mUnknown528, sizeof(control));
    fn_801D31F0(&pA->mUnknown528, &pB->mUnknown528, sizeof(control));
    fn_801D31F0(&pB->mUnknown528, control, sizeof(control));

    unsigned char byte = pA->mUnknown9[0];
    pA->mUnknown9[0] = pB->mUnknown9[0];
    pB->mUnknown9[0] = byte;
    unsigned int flags = pA->mFlags;
    pA->mFlags = pB->mFlags;
    pB->mFlags = flags;
    fn_80148424((Record_80148424 *)pA, (Record_80148424 *)pB);
    fn_80149040(pA);
    fn_80149040(pB);

    unsigned char indexA = pA->mUnknown8;
    unsigned char indexB = pB->mUnknown8;
    if (indexA != 0xFF) {
        fn_800B6474(indexA, pB->mIdBytes[2]);
        fn_800B6714(pB, indexA);
    } else {
        fn_800B6658(pB);
    }
    if (indexB != 0xFF) {
        fn_800B6474(indexB, pA->mIdBytes[2]);
        fn_800B6714(pA, indexB);
    } else {
        fn_800B6658(pA);
    }
}

Class_80148A58 *fn_80148A58(void)
{
    int index = fn_801486A0();
    if (index == 15) {
        return 0;
    }
    return lbl_8031BDBC[index];
}
}
