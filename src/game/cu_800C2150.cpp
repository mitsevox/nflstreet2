#include "engine/cu_801D03D0.h"
#include "engine/vec.h"
#include "game/Block_800DE3B0.h"
#include "game/Class_80297C60.h"
#include "game/Command_800CEE74.h"
#include "game/Object_8003DEC4.h"
#include "game/Level_80054130.h"
#include "game/Record_803EA558.h"
#include "game/Table_80089904.h"
#include "game/cu_80064864.h"
#include "game/fn_8017F584.h"
#include "game/fn_801BE60C.h"
#include "game/fn_80195EFC.h"
#include "game/fn_801FCE10.h"
#include "game/fn_802270D4.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"

/* 8-byte records of the three 50-entry lists at 0x8030FF40 (one per side
   plus a shared list), as fn_800C3130 fills them. */
struct Entry_800C3130 {
    Block_80170E64 *mpUnknown0;
    short mUnknown4;
    short mUnknown6;
};

extern "C" {
int fn_800BA6F8(void);
int fn_800C2FDC(Block_80170E64 *p, Block_80170E64 *pOther, float *pBest, int maxAngle, float range,
                float radiusSq);
int fn_800CC4B0(Object_80039F5C *p);
float fn_80178A08(void);
int fn_800C210C(int *p, int offset, int *pValue);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
float fn_80178A44(void);
void fn_800CEED8(unsigned short key, int index, Command_800CEE74 *pRecord, Object_80039F5C *pPlayer, Vector_80039F5C *pPoint,
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
extern int lbl_802D9D10[9][3][2];
extern int lbl_802D9DF8[];
extern int lbl_802D9E00[5][3][2];
extern int lbl_802D9E88[];
extern float lbl_803EABBC;
extern float lbl_803EABC0;
extern float lbl_803EABC4;
extern float lbl_803EABC8;
extern float lbl_803EABCC;
extern float lbl_803EABD0;
extern unsigned char lbl_803EABD5;
}

extern const Vector_80039F5C lbl_802975E8 = { -1.0f, 0.0f, 0.0f };
extern const Vector_80039F5C lbl_802975F4 = { 0.0f, 0.0f, -1.0f };

extern "C" void fn_800C2150(Object_8003DEC4 *pPlayer, Block_800C2788 *pBlock, int a)
{
    Vector_80039F5C pos;
    int dir[3];
    Vector_80039F5C vel;
    Vector_80039F5C acc;
    Vector_80039F5C side = lbl_802975E8;
    Vector_80039F5C back = lbl_802975F4;
    int angles[3];
    int target[3];
    Vector_80039F5C v;
    float speed;
    float dotSide;
    float dotBack;
    float pitch;
    float roll;
    unsigned int i;

    if (a == 0) {
        pBlock->mUnknown2 = 0;
        return;
    }
    fn_801D04C4();
    fn_801D0664(pPlayer->mUnknown44.mUnknown52[pBlock->mUnknown1][0]);
    fn_80227C2C(&back, &back);
    fn_80227C2C(&side, &side);
    fn_801D0FB8(&pos.mX);
    fn_801D11F4(dir, 0);
    if (pBlock->mUnknown2 == 0) {
        pBlock->mUnknown4[0] = pos.mX;
        pBlock->mUnknown4[1] = pos.mY;
        pBlock->mUnknown4[2] = pos.mZ;
        pBlock->mUnknown28[0] = dir[0];
        pBlock->mUnknown28[1] = dir[1];
        pBlock->mUnknown28[2] = dir[2];
    }
    fn_802276B4(&vel, &pos, pBlock->mUnknown4);
    if (pBlock->mUnknown2 == 0) {
        pBlock->mUnknown16[0] = vel.mX;
        pBlock->mUnknown16[1] = vel.mY;
        pBlock->mUnknown16[2] = vel.mZ;
    }
    fn_802276B4(&acc, &vel, pBlock->mUnknown16);
    speed = fn_802270D4(&acc);
    dotSide = -fn_80227704(&acc, &side);
    dotBack = -fn_80227704(&acc, &back);
    v.mX = 0.0f;
    v.mY = fn_801CFB18(pBlock->mUnknown28[0]);
    v.mZ = -fn_801CFB94(pBlock->mUnknown28[0]);
    fn_80227C2C(&v, &v);
    pitch = -lbl_803EABC0 * v.mZ;
    v.mX = -fn_801CFB94(pBlock->mUnknown28[2]);
    v.mY = fn_801CFB18(pBlock->mUnknown28[2]);
    v.mZ = 0.0f;
    fn_80227C2C(&v, &v);
    roll = -lbl_803EABC0 * v.mZ;
    fn_801D0544();
    target[0] = (int)(speed * dotBack * lbl_803EABBC * 46603.37890625f) + (int)(pitch * 46603.37890625f);
    target[1] = 0;
    target[2] = (int)(speed * dotSide * lbl_803EABBC * 46603.37890625f) + (int)(roll * 46603.37890625f);
    for (i = 0; i < 9; i++) {
        if (pBlock->mUnknown2 == 0) {
            pBlock->mUnknown40[i][0] = (short)pBlock->mUnknown312->mUnknown1040[(i + 1) * 2][0] << 8;
            pBlock->mUnknown40[i][1] = (short)pBlock->mUnknown312->mUnknown1040[(i + 1) * 2][1] << 8;
            pBlock->mUnknown40[i][2] = (short)pBlock->mUnknown312->mUnknown1040[(i + 1) * 2][2] << 8;
            pBlock->mUnknown148[i][0] = 0;
            pBlock->mUnknown148[i][1] = 0;
            pBlock->mUnknown148[i][2] = 0;
        }
        angles[0] = pBlock->mUnknown40[i][0] + pBlock->mUnknown148[i][0];
        angles[1] = pBlock->mUnknown40[i][1] + pBlock->mUnknown148[i][1];
        angles[2] = pBlock->mUnknown40[i][2] + pBlock->mUnknown148[i][2];
        pBlock->mUnknown148[i][0] = (int)(pBlock->mUnknown148[i][0] * lbl_803EABC4 + target[0]);
        pBlock->mUnknown148[i][1] = (int)(pBlock->mUnknown148[i][1] * lbl_803EABC4 + target[1]);
        pBlock->mUnknown148[i][2] = (int)(pBlock->mUnknown148[i][2] * lbl_803EABC4 + target[2]);
        fn_800C210C(lbl_802D9DF8, 0, &pBlock->mUnknown148[i][0]);
        fn_800C210C(lbl_802D9DF8, 0, &pBlock->mUnknown148[i][1]);
        fn_800C210C(lbl_802D9DF8, 0, &pBlock->mUnknown148[i][2]);
        if (fn_800C210C(lbl_802D9D10[i][0], 0, &angles[0])) {
            pBlock->mUnknown148[i][0] = 0;
        }
        if (fn_800C210C(lbl_802D9D10[i][1], 0, &angles[1])) {
            pBlock->mUnknown148[i][1] = 0;
        }
        if (fn_800C210C(lbl_802D9D10[i][2], 0, &angles[2])) {
            pBlock->mUnknown148[i][2] = 0;
        }
        pBlock->mUnknown256.mUnknown48[(i + 1) * 6 + 0] = angles[0] >> 8;
        pBlock->mUnknown256.mUnknown48[(i + 1) * 6 + 1] = angles[1] >> 8;
        pBlock->mUnknown256.mUnknown48[(i + 1) * 6 + 2] = angles[2] >> 8;
        pBlock->mUnknown40[i][0] = angles[0];
        pBlock->mUnknown40[i][1] = angles[1];
        pBlock->mUnknown40[i][2] = angles[2];
    }
    pBlock->mUnknown16[0] = vel.mX;
    pBlock->mUnknown16[1] = vel.mY;
    pBlock->mUnknown16[2] = vel.mZ;
    pBlock->mUnknown4[0] = pos.mX;
    pBlock->mUnknown4[1] = pos.mY;
    pBlock->mUnknown4[2] = pos.mZ;
    pBlock->mUnknown28[0] = dir[0];
    pBlock->mUnknown28[1] = dir[1];
    pBlock->mUnknown28[2] = dir[2];
    if (pBlock->mUnknown2 == 0) {
        pBlock->mUnknown2 = 1;
    }
}

extern "C" void fn_800C2884(Object_8003DEC4 *pPlayer, Block_800C2EC0 *pBlock, int a)
{
    Vector_80039F5C pos;
    int dir[3];
    Vector_80039F5C vel;
    Vector_80039F5C acc;
    Vector_80039F5C side = lbl_802975E8;
    Vector_80039F5C back = lbl_802975F4;
    int angles[3];
    int target[3];
    Vector_80039F5C v;
    float speed;
    float dotSide;
    float dotBack;
    float pitch;
    float roll;
    unsigned int i;

    if (a == 0) {
        pBlock->mUnknown2 = 0;
        return;
    }
    fn_801D04C4();
    fn_801D0664(pPlayer->mUnknown44.mUnknown52[pBlock->mUnknown1][0]);
    fn_801D0BCC(-0x22D82D, 0, -0x1C71C7);
    fn_80227C2C(&back, &back);
    fn_80227C2C(&side, &side);
    fn_801D0FB8(&pos.mX);
    fn_801D11F4(dir, 0);
    if (pBlock->mUnknown2 == 0) {
        pBlock->mUnknown4[0] = pos.mX;
        pBlock->mUnknown4[1] = pos.mY;
        pBlock->mUnknown4[2] = pos.mZ;
        pBlock->mUnknown28[0] = dir[0];
        pBlock->mUnknown28[1] = dir[1];
        pBlock->mUnknown28[2] = dir[2];
    }
    fn_802276B4(&vel, &pos, pBlock->mUnknown4);
    if (pBlock->mUnknown2 == 0) {
        pBlock->mUnknown16[0] = vel.mX;
        pBlock->mUnknown16[1] = vel.mY;
        pBlock->mUnknown16[2] = vel.mZ;
    }
    fn_802276B4(&acc, &vel, pBlock->mUnknown16);
    speed = fn_802270D4(&acc);
    dotSide = -fn_80227704(&acc, &side);
    dotBack = -fn_80227704(&acc, &back);
    v.mX = 0.0f;
    v.mY = fn_801CFB18(pBlock->mUnknown28[0]);
    v.mZ = -fn_801CFB94(pBlock->mUnknown28[0]);
    fn_80227C2C(&v, &v);
    pitch = -lbl_803EABCC * v.mZ;
    v.mX = -fn_801CFB94(pBlock->mUnknown28[2] - 0x22D82D);
    v.mY = fn_801CFB18(pBlock->mUnknown28[2] - 0x22D82D);
    v.mZ = 0.0f;
    fn_80227C2C(&v, &v);
    roll = -lbl_803EABCC * v.mZ;
    fn_801D0544();
    target[0] = (int)(speed * dotBack * lbl_803EABC8 * 46603.37890625f) + (int)(pitch * 46603.37890625f);
    target[1] = 0;
    target[2] = (int)(speed * dotSide * lbl_803EABC8 * 46603.37890625f) + (int)(roll * 46603.37890625f);
    for (i = 0; i < 5; i++) {
        pBlock->mUnknown160.mUnknown48[i * 3 + 0] = pBlock->mUnknown216->mUnknown1040[i][0];
        pBlock->mUnknown160.mUnknown48[i * 3 + 1] = pBlock->mUnknown216->mUnknown1040[i][1];
        pBlock->mUnknown160.mUnknown48[i * 3 + 2] = pBlock->mUnknown216->mUnknown1040[i][2];
    }
    i = 3;
    if (pBlock->mUnknown2 == 0) {
        pBlock->mUnknown40[i][0] = (short)pBlock->mUnknown216->mUnknown1040[i][0] << 8;
        pBlock->mUnknown40[i][1] = (short)pBlock->mUnknown216->mUnknown1040[i][1] << 8;
        pBlock->mUnknown40[i][2] = (short)pBlock->mUnknown216->mUnknown1040[i][2] << 8;
        pBlock->mUnknown100[i][0] = 0;
        pBlock->mUnknown100[i][1] = 0;
        pBlock->mUnknown100[i][2] = 0;
    }
    angles[0] = pBlock->mUnknown40[i][0] + pBlock->mUnknown100[i][0];
    angles[1] = pBlock->mUnknown40[i][1] + pBlock->mUnknown100[i][1];
    angles[2] = pBlock->mUnknown40[i][2] + pBlock->mUnknown100[i][2];
    pBlock->mUnknown100[i][0] = (int)(pBlock->mUnknown100[i][0] * lbl_803EABD0 + target[0]);
    pBlock->mUnknown100[i][1] = (int)(pBlock->mUnknown100[i][1] * lbl_803EABD0 + target[1]);
    pBlock->mUnknown100[i][2] = (int)(pBlock->mUnknown100[i][2] * lbl_803EABD0 + target[2]);
    fn_800C210C(lbl_802D9E88, 0, &pBlock->mUnknown100[i][0]);
    fn_800C210C(lbl_802D9E88, 0, &pBlock->mUnknown100[i][1]);
    fn_800C210C(lbl_802D9E88, 0, &pBlock->mUnknown100[i][2]);
    if (fn_800C210C(lbl_802D9E00[i][0], 0, &angles[0])) {
        pBlock->mUnknown100[i][0] = 0;
    }
    if (fn_800C210C(lbl_802D9E00[i][1], 0, &angles[1])) {
        pBlock->mUnknown100[i][1] = 0;
    }
    if (fn_800C210C(lbl_802D9E00[i][2], 0, &angles[2])) {
        pBlock->mUnknown100[i][2] = 0;
    }
    pBlock->mUnknown160.mUnknown48[i * 3 + 0] = (angles[0] + 0x471C72) >> 8;
    pBlock->mUnknown160.mUnknown48[i * 3 + 1] = pBlock->mUnknown216->mUnknown1040[i][1];
    pBlock->mUnknown160.mUnknown48[i * 3 + 2] = pBlock->mUnknown216->mUnknown1040[i][2];
    pBlock->mUnknown40[i][0] = angles[0];
    pBlock->mUnknown40[i][1] = angles[1];
    pBlock->mUnknown40[i][2] = angles[2];
    pBlock->mUnknown16[0] = vel.mX;
    pBlock->mUnknown16[1] = vel.mY;
    pBlock->mUnknown16[2] = vel.mZ;
    pBlock->mUnknown4[0] = pos.mX;
    pBlock->mUnknown4[1] = pos.mY;
    pBlock->mUnknown4[2] = pos.mZ;
    pBlock->mUnknown28[0] = dir[0];
    pBlock->mUnknown28[1] = dir[1];
    pBlock->mUnknown28[2] = dir[2];
    if (pBlock->mUnknown2 == 0) {
        pBlock->mUnknown2 = 1;
    }
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
                fn_800C31E4(p, &distance, 0x200000, 5.0f, 1.0f);
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
    /* The 'PNIG' and 'ELQG' query strings sit in the target pool between the
       live strings, so the original made these queries on a path the compiler
       removed; resume is never set in this body. */
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

extern "C" int fn_800C36A8(Object_80039F5C *p, int skip, unsigned short key, int index, Command_800CEE74 *pRecord,
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
