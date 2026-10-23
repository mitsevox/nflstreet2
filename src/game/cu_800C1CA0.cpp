#include "game/Object_80039F5C.h"
#include "game/Block_800DE3B0.h"
#include "game/Class_80297C60.h"
#include "game/Command_800CEE74.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80136B1C.h"
#include "game/Level_80054130.h"
#include "game/Record_803EA558.h"
#include "game/Table_80089904.h"
#include "game/cu_80064864.h"
#include "game/fn_8017F584.h"
#include "game/fn_801BE60C.h"
#include "game/fn_80195EFC.h"
#include "game/fn_801FCE10.h"

/* 8-byte records of the three 50-entry lists at 0x8030FF40 (one per side
   plus a shared list), as fn_800C3130 fills them. */
struct Entry_800C3130 {
    Block_80170E64 *mpUnknown0;
    short mUnknown4;
    short mUnknown6;
};

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

extern "C" {
int fn_800AD9B4(void);
int fn_800BA6F8(void);
int fn_800C2FDC(Block_80170E64 *p, Block_80170E64 *pOther, float *pBest, int maxAngle, float range,
                float radiusSq);
int fn_800CC4B0(Object_80039F5C *p);
float fn_80178A08(void);
void fn_800BA7E8(float x, float y);
Camera_8013F738 *fn_8013FA04(int index);
void fn_80178370(void);
int fn_801784C4(void);
float fn_80178A2C(void);
float fn_80178A5C(void);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_8002B71C(void);
void fn_8002D274(Type_803EA368 *p);
void fn_8003A4DC(void);
void fn_800406C0(unsigned int flags);
void fn_800588E0(void);
void fn_80071C34(int value);
void fn_80073328(int resume);
void fn_80073764(void);
unsigned char fn_800737C0(void);
void fn_80074250(int index);
void fn_8009D8CC(int index);
void fn_800A7A0C(int team);
void fn_800A7E68(void);
int fn_800A8740(void);
void fn_800AD910(int mode, float dt);
void fn_800B4184(int a);
void fn_800B63B0(void);
void fn_800D6F08(void);
void fn_800D7158(void);
void fn_8013F3FC(void);
void fn_80148154(void);
void fn_801483C8(void);
void fn_8016BA80(void);
void fn_801735D8(unsigned int mask);
void fn_80173C1C(void);
void fn_80173C2C(void);
void fn_80173D10(void);
void fn_80176C58(void);
void fn_80176C90(void);
void fn_80177B7C(int a);
void fn_8017833C(int value);
void fn_80178354(int value);
int fn_80178AE0(void);
void fn_8017D4AC(void);
int fn_8022BF68(void);
int fn_8022DD4C(int value);
int fn_8022DD80(int value);
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
Table_80089904 *fn_801BE72C(unsigned short type, unsigned short key);
void fn_800DEAB0(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key, void *pData, int angle,
                 Entry_800DE51C *pRecord);

float fn_80260B1C(float);

extern unsigned int lbl_802D9E90[3];
extern Entry_800C3130 lbl_8030FF40[3][50];
extern unsigned char lbl_803EABB8;
extern unsigned char lbl_803EABB9;
extern unsigned char lbl_803EABD5;
}

extern "C" void fn_800C1CA0(void)
{
    unsigned char team;

    lbl_803EABB9 = 1;
    team = fn_80178AE0();
    lbl_803EABB8 = 1;
    fn_80173C1C();
    fn_80173C2C();
    fn_80176C58();
    fn_80173D10();
    fn_80176C90();
    fn_800406C0(0x100);
    fn_8022DD4C(0);
    fn_8022DD80(0);
    if (fn_8017F584() == 6) {
        fn_8002B71C();
    } else {
        fn_80177B7C(team);
    }
    fn_8002D274(lbl_803EA368);
    fn_8016BA80();
    fn_8022BF68();
    fn_800D6F08();
    fn_800D7158();
    fn_80071C34(0);
    if (fn_800737C0()) {
        fn_80073764();
    }
    fn_80074250(0);
    fn_80074250(1);
    fn_80074250(2);
    fn_80162780(0, 0);
    fn_8013F3FC();
    if (fn_800A8740() == 0) {
        fn_800A7A0C(0);
        fn_800A7A0C(1);
    }
    fn_800A7E68();
    if (fn_800AD9B4() == 7 || fn_800AD9B4() == 0) {
        fn_8009D818(0);
    } else {
        fn_800B4184(1);
        fn_800588E0();
        fn_8003A4DC();
        fn_800B63B0();
        fn_8009D818(0);
        fn_800AD910(1, 0.0f);
    }
    if (fn_8017F584() == 8) {
        fn_8017833C(1);
        fn_80178354(1);
    }
    fn_801735D8(0x800);
    fn_8009D8CC(1);
    fn_8009D8CC(5);
    fn_8009D8CC(0);
    fn_8017D4AC();
    fn_80148154();
    fn_801483C8();
    fn_80073328(0);
    lbl_803EABB9 = 0;
}

extern "C" void fn_800C1E5C(int a, unsigned int b, float c)
{
    Object_80137ABC *pBall = fn_801374BC();
    Vector_80039F5C pos;
    Point_8017886C delta;

    fn_80137D58(pBall, &pos);
    delta.mX = 0.0f;
    delta.mY = 0.0f;
    switch (b) {
    case 0:
    case 7:
        if (c > 0.0f) {
            fn_800BA7E8(pos.mX, pos.mY);
            fn_80178370();
        }
        break;
    case 52:
        delta.mY = c * -0.16f;
        break;
    case 53:
        delta.mX = c * -0.16f;
        break;
    case 16:
    case 54:
        delta.mX = c * 0.16f;
        break;
    case 17:
    case 51:
        delta.mY = c * 0.16f;
        break;
    }
    if (fn_801784C4()) {
        delta.mX = -delta.mX;
        delta.mY = -delta.mY;
    }
    fn_80227384(&delta, &delta, (0x1000000 - fn_8013FA04(0)->mHeader.mUnknown14[2]) & 0xFFFFFF);
    pos.mX += delta.mX;
    pos.mY += delta.mY;
    pos.mX = CLAMP(pos.mX, -fn_80178A5C(), fn_80178A5C());
    pos.mY = CLAMP(pos.mY, 0.33f - fn_80178A2C(), fn_80178A2C() - 0.33f);
    fn_80137D74(pBall, &pos);
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
