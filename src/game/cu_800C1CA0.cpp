#include "game/Object_80039F5C.h"
#include "game/Block_801BE60C.h"
#include "game/Class_80297C60.h"
#include "game/Command_800CEE74.h"
#include "game/Level_80054130.h"
#include "game/Record_803EA558.h"
#include "game/Table_80089904.h"
#include "game/cu_80064864.h"
#include "game/fn_8017F584.h"
#include "game/fn_80195EFC.h"
#include "game/fn_801FCE10.h"

/* 8-byte records of the three 50-entry lists at 0x8030FF40 (one per side
   plus a shared list), as fn_800C3130 fills them. */
struct Entry_800C3130 {
    Block_80170E64 *mpUnknown0;
    short mUnknown4;
    short mUnknown6;
};

/* Records of the table fn_801BBD5C returns, as src/game/cu_800DAEE4.cpp
   reads them. */
struct Entry_800DE51C {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    char mUnknown3[17];
};

struct Table_800DE51C {
    char mUnknown0[4];
    unsigned short mCount;
    char mUnknown6[2];
    Entry_800DE51C mEntries[1];
};

/* Block that fn_800DEAB0 fills (src/game/cu_800DAEE4.cpp). */
struct Block_800DE3B0 {
    float mUnknown0;
    Pair_802270A4 mUnknown4, mUnknownC;
    int mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C, mUnknown1D, mUnknown1E, mUnknown1F;
    State_800D8140 mUnknown20;
    int mUnknown38;
    unsigned char mUnknown3C, mUnknown3D;
    signed char mUnknown3E, mUnknown3F;
};

extern "C" {
int fn_800AD9B4(void);
int fn_800BA6F8(void);
int fn_800C2FDC(Block_80170E64 *p, Block_80170E64 *pOther, float *pBest, int maxAngle, float range,
                float radiusSq);
int fn_800CC4B0(Object_80039F5C *p);
float fn_80178A08(void);
float fn_80178A44(void);
void fn_800CEED8(int key, int index, Command_800CEE74 *pRecord, Object_80039F5C *pPlayer, Vector_80039F5C *pPoint,
                 int angle, Vector_80039F5C *pOut, int *pAngle, unsigned char *pValue);
int fn_800E0F48(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
void fn_80227970(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC, Vector_80039F5C *pOut, float *pValue,
                 float *pOther);
void fn_8009D818(int state);
int fn_8009D86C(void);
void fn_8009D888(int index, int value);
void fn_8009D964(int index, int value);
void fn_800B9BAC(Class_80297C60 *p);
void fn_800CC448(void);
void fn_800545C0(void);
void fn_800545E8(void);
void fn_80139204(void);
void fn_8013F97C(int a);
void fn_8013FA58(int a, int b);
unsigned char fn_801374D4(void);
void fn_80162780(int a, int b);
void fn_8016DDDC(int team);
void fn_80173BCC(void);
void fn_80173BF8(void);
int fn_80178308(void);
int fn_80178320(void);
void fn_8017F264(void);
void fn_8017F284(void);
int fn_8019623C(int id);
Table_800DE51C *fn_801BBD5C(unsigned short key, unsigned short id);
unsigned short fn_801BE648(void *p);
Table_80089904 *fn_801BE72C(unsigned short type, unsigned short key);
void fn_800DEAB0(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key, void *pData, int angle,
                 Entry_800DE51C *pRecord);

float fn_80260B1C(float);

extern unsigned int lbl_802D9E90[3];
extern Entry_800C3130 lbl_8030FF40[3][50];
extern unsigned char lbl_803EABD5;
}

extern "C" Entry_800C3130 *fn_800C31E4(Object_80039F5C *p, float *pDistance, int maxAngle, float range,
                                       float radius)
{
    Block_80170E64 *pBlock = p->mpUnknown4;
    float radiusSq = (radius * 2.0f) * (radius * 2.0f);
    int side = pBlock->mUnknown4.mX >= 0.0f;
    float best = 3.4028235e38f;
    Entry_800C3130 *pResult = 0;
    Entry_800C3130 *pEntry;
    Block_80170E64 *pOther;
    float dy;
    unsigned int i;

    for (i = 0; i < lbl_802D9E90[side]; i++) {
        pEntry = &lbl_8030FF40[side][i];
        pOther = pEntry->mpUnknown0;
        if (pOther == pBlock) {
            continue;
        }
        dy = pOther->mUnknown4.mY - pBlock->mUnknown4.mY;
        if (dy > range) {
            break;
        }
        if (dy > -range && fabsf(pOther->mUnknown4.mX - pBlock->mUnknown4.mX) < range &&
            fn_800C2FDC(pBlock, pOther, &best, maxAngle, range, radiusSq)) {
            pResult = pEntry;
        }
    }
    if (p->mIdBytes[3] != 1) {
        for (i = 0; i < lbl_802D9E90[2]; i++) {
            pEntry = &lbl_8030FF40[2][i];
            pOther = pEntry->mpUnknown0;
            if (pOther == pBlock) {
                continue;
            }
            dy = pOther->mUnknown4.mY - pBlock->mUnknown4.mY;
            if (dy > range) {
                break;
            }
            if (dy > -range && fabsf(pOther->mUnknown4.mX - pBlock->mUnknown4.mX) > fn_80178A08() - range &&
                fn_800C2FDC(pBlock, pOther, &best, maxAngle, range, radiusSq)) {
                pResult = pEntry;
            }
        }
    }
    if (pResult != 0) {
        *pDistance = fn_80260B1C(best);
    }
    return pResult;
}

extern "C" void fn_800C3404(Object_80039F5C *p)
{
    float distance;

    if (fn_800BA6F8() == 0) {
        switch (fn_800AD9B4()) {
        case 4:
            if (fn_800CC4B0(0) != 0) {
                break;
            }
        case 3:
            if (fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 1.0f) {
                if (fn_800C31E4(p, &distance, 0x200000, 5.0f, 1.0f) != 0) {
                }
            }
            break;
        }
    }
}

extern "C" void fn_800C34B0(void)
{
    int resume = 0;
    unsigned int pnig = 60;
    unsigned int elqg;
    unsigned int mitg;
    unsigned int rtqg;

    fn_8017F584();
    if (resume) {
        fn_801FCE10(0, "select 'PNIG' into \x82 from 'FNIG'\n", &pnig);
        fn_801FCE10(0, "select 'ELQG' into \x82 from 'FNIG'\n", &elqg);
    }
    fn_801FCE10(0, "select 'MITG' into \x82 from 'FNIG'\n", &mitg);
    fn_801FCE10(0, "select 'RTQG' into \x82 from 'FNIG'\n", &rtqg);
    fn_8009D964(1, mitg);
    fn_8009D818(rtqg);
    if (pnig <= 120) {
        fn_80173BCC();
    }
    if (mitg <= 120 && (fn_8009D86C() == 4 || fn_8009D86C() == 2)) {
        fn_80173BF8();
    }
    fn_800CC448();
    fn_8016DDDC(fn_80178308());
    fn_8016DDDC(fn_80178320());
    fn_80139204();
    fn_800B9BAC(lbl_803EAB84);
    if (lbl_803EABD5 == 0) {
        fn_8009D888(2, 0);
    }
    if (lbl_803EABD5 != 0) {
        fn_801FCE10(0, "delete from 'MAGI'\n");
        fn_8017F284();
        fn_8017F264();
        fn_800545E8();
        fn_800545C0();
        fn_8006563C();
        fn_80162780(0, 0);
    }
    if (fn_8019623C(0x23000) != 0) {
        fn_80195EFC(1, 20, 0x808080, 0);
    }
    fn_8013F97C(0);
    fn_8013FA58(1, fn_801374D4());
}

extern "C" int fn_800C36A8(Object_80039F5C *p, int skip, int key, int index, Command_800CEE74 *pRecord,
                           Vector_80039F5C *pPoint, int angle)
{
    int result = 0;
    int nearCorner = 0;
    Vector_80039F5C start;
    Vector_80039F5C end;
    Vector_80039F5C a;
    Vector_80039F5C b;
    Vector_80039F5C closest;
    unsigned char value;
    int outAngle;
    float distance;
    float factor;
    unsigned int count;
    Record_80054130 *pRow;
    unsigned char i;

    if (fn_80178A08() - fabsf(pPoint->mX) < 2.0f) {
        nearCorner = fn_80178A44() - fabsf(pPoint->mY) < 2.0f;
    }
    start.mX = p->mMotion.mPos.mX;
    start.mY = p->mMotion.mPos.mY;
    start.mZ = p->mMotion.mPos.mZ;
    fn_800CEED8(key, index, pRecord, p, pPoint, angle, &end, &outAngle, &value);
    count = (unsigned char)fn_80054130()->mUnknown136;
    pRow = fn_80054130()->mUnknown140;
    for (i = 0; i < count; i++, pRow++) {
        if (i == skip) {
            continue;
        }
        fn_800541AC(pRow, &a, &b);
        b.mZ = 0.0f;
        a.mZ = 0.0f;
        if (key == 224 || key == 235) {
            if (nearCorner) {
                result = 1;
            } else {
                float limit;

                fn_80227970(&a, &b, &end, &closest, &distance, &factor);
                limit = lbl_803EA558[i].mUnknown0 < 3.0f ? 2.0f : 1.0f;
                if (distance < limit) {
                    result = 1;
                    break;
                }
            }
        } else if (!(fabsf(end.mY) < fn_80178A44())) {
            result = 1;
        } else if (fn_800E0F48(&start, &end, &a, &b)) {
            result = 1;
            break;
        }
    }
    return result;
}

extern "C" void fn_800C38C4(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key)
{
    Entry_800DE51C *pRecord = 0;
    Table_80089904 *pTable = fn_801BE72C(p->mpUnknown796->mUnknown2, fn_801BE648(p->mpUnknown792));
    unsigned int i;

    pBlock->mUnknown3F = pBlock->mUnknown3E = -1;
    for (i = 0; i < pTable->mCount; i++) {
        Table_800DE51C *pRecords = fn_801BBD5C(fn_801BE648(p->mpUnknown792), p->mpUnknown796->mUnknown2);

        if (pRecords->mEntries[i].mUnknown2 == 1 && pRecords->mEntries[i].mUnknown0 == (key & ~0x8000)) {
            pRecord = &pRecords->mEntries[i];
            break;
        }
    }
    if (pRecord != 0) {
        pBlock->mUnknown1C = 1;
        if (key & 0x8000) {
            pBlock->mUnknown1F = 1;
        }
        pBlock->mUnknownC.mUnknown4 = pBlock->mUnknownC.mUnknown0 = 0.0f;
        fn_800DEAB0(p, pBlock, fn_801BE648(p->mpUnknown792), 0, 0, pRecord);
    }
}
