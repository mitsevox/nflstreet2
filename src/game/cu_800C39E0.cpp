#include "game/Object_80039F5C.h"
#include "game/Block_800DE3B0.h"
#include "game/Command_800CEE74.h"
#include "game/Level_80054130.h"
#include "game/Record_803EA558.h"
#include "game/Table_80089904.h"
#include "game/fn_801BA2A8.h"
#include "game/fn_801BE60C.h"
#include "game/fn_802372EC.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* 3044-byte records of the array at 0x803103F0 that fn_800C432C fills, one
   table per play key. */
struct Record_800C432C {
    Table_80089904 mTable;
    unsigned char mUnknown12[3032];
};

extern "C" {
int fn_800C36A8(Object_80039F5C *p, int skip, int key, int index, Command_800CEE74 *pRecord,
                Vector_80039F5C *pPoint, int angle);
int fn_800CD170(Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pC);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_80227638(void *pOut, void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_8022781C(void *pA, void *pB);
void fn_80227970(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC, Vector_80039F5C *pOut, float *pValue,
                 float *pOther);
void fn_800C38C4(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key);
void fn_800D8140(State_800D8140 *pState, Object_80039F5C *p, int value);
void fn_800D81C8(State_800D8140 *pState, Object_80039F5C *p);
void fn_800DEC10(Object_80039F5C *p, Block_800DE3B0 *pBlock);
void fn_800DF654(Object_80039F5C *p, Block_801BE60C *pRecord);
int fn_801784C4(void);
int fn_801BA6B0(Record_800D81C8 *pChannel);
void fn_801BA6BC(Record_800D81C8 *pChannel, int enable);

extern Record_800C432C lbl_803103F0[10];
extern float lbl_803EABD8;
extern float lbl_803EABDC;
extern float lbl_803EABE0;
}

extern "C" void fn_800C39E0(Object_80039F5C *p, int a, int index, int value, int flag)
{
    if (flag != 0) {
        index |= 0x8000;
    }
    p->mUnknown1008.mUnknown0 = index;
    p->mUnknown1008.mUnknown1 = (unsigned int)index >> 8;
    p->mUnknown1008.mUnknown2 = value;
    p->mUnknown1011 = (unsigned int)value >> 8;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, a, p, 1.0f);
}


extern "C" int fn_800C3A4C(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int mode)
{
    Block_800DE3B0 *pBlock = (Block_800DE3B0 *)fn_801BE60C(p->mpUnknown792, key);

    switch (mode) {
    case 0: {
        int index;

        fn_801BE760(p->mpUnknown792, key, 1);
        index = p->mUnknown1008.mUnknown0 | (p->mUnknown1008.mUnknown1 << 8);
        pBlock->mUnknown1D = fn_801BA2A8(pA, pEntries, p->mUnknown1008.mUnknown2 | (p->mUnknown1011 << 8),
                                         index & 0x7FFF, key, p, 1.0f);
        pBlock->mUnknown18 = key;
        p->mFlags |= 0x200;
        fn_800C38C4(p, pBlock, index);
        if (pBlock->mUnknown1F) {
            Record_800D81C8 *pEntry = &pEntries[pBlock->mUnknown1D];

            fn_801BA6BC(pEntry, fn_801BA6B0(pEntry) == 0);
            pBlock->mUnknown1F = fn_801BA6B0(&pEntries[pBlock->mUnknown1D]);
        }
        fn_800D8140(&pBlock->mUnknown20, p, pBlock->mUnknown1D);
        pBlock->mUnknown1E = fn_801784C4();
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            int side = fn_801784C4();

            if (side != pBlock->mUnknown1E) {
                pBlock->mUnknown1E = side;
                fn_800DF654(p, (Block_801BE60C *)pBlock);
            }
            fn_800DEC10(p, pBlock);
            fn_800D81C8(&pBlock->mUnknown20, p);
        }
        break;
    case 1:
    case 3:
        pBlock->mUnknown1C = 0;
        p->mFlags &= ~0x200;
        break;
    }
    return 0;
}

extern "C" int fn_800C3BEC(Object_80039F5C *p, Command_800CEE74 *pCommand, int *pValue, int *pB)
{
    Vector_80039F5C point;
    Vector_80039F5C a;
    Vector_80039F5C b;
    Vector_80039F5C target;
    Vector_80039F5C best;
    Vector_80039F5C closest;
    Point_8017886C offset;
    float distance;
    float factor;
    Point_8017886C delta;
    float playerDistance;
    float playerFactor;
    Table_80089904 *pTable = 0;
    int found = 0;
    int row = -1;
    int rowAngle = 0;
    unsigned short entry;
    unsigned short tries;

    best.mX = best.mY = best.mZ = 0.0f;
    switch (pCommand->mUnknown60) {
    case 196:
        pTable = &lbl_803103F0[0].mTable;
        break;
    case 197:
        pTable = &lbl_803103F0[1].mTable;
        break;
    case 195:
        pTable = &lbl_803103F0[2].mTable;
        break;
    case 210:
        pTable = &lbl_803103F0[3].mTable;
        break;
    case 224:
        pTable = &lbl_803103F0[4].mTable;
        break;
    case 228:
        pTable = &lbl_803103F0[5].mTable;
        break;
    case 230:
        pTable = &lbl_803103F0[6].mTable;
        break;
    case 229:
        pTable = &lbl_803103F0[7].mTable;
        break;
    case 235:
        pTable = &lbl_803103F0[8].mTable;
        break;
    case 237:
        pTable = &lbl_803103F0[9].mTable;
        break;
    }
    if (pTable != 0) {
        entry = fn_802372EC(0, pTable->mCount);
        for (tries = pTable->mCount; tries != 0; tries--, entry++) {
            Info_80089904 *pInfo;

            if (entry >= pTable->mCount) {
                entry = 0;
            }
            pInfo = pTable->mEntries[entry].mpInfo;
            if (p->mUnknown1008.mUnknown0 == pInfo->mUnknown56Byte ||
                (pInfo->mUnknown56Byte == 0 && p->mUnknown1008.mUnknown0 == 8)) {
                int direction;
                unsigned int count;
                Record_80054130 *pRow;
                float height;
                unsigned char i;

                fn_800CE804(pCommand, pTable, pTable->mEntries[entry].mUnknown2);
                direction = fn_801CFE40(pCommand->mVector0.mY, pCommand->mVector0.mX);
                count = (unsigned short)fn_80054130()->mUnknown136;
                pRow = fn_80054130()->mUnknown140;
                height = pCommand->mUnknown12.mZ;
                pCommand->mUnknown12.mZ = 0.0f;
                for (i = 0; i < count; i++, pRow++) {
                    int angle;
                    int turn;
                    float limit;

                    if (lbl_803EA558[i].mUnknown0 <= 1.0f) {
                        continue;
                    }
                    angle = fn_801784C4() ? lbl_803EA558[i].mUnknown8 : lbl_803EA558[i].mUnknown4;
                    if (fn_801CFFD0(angle, direction) >= (int)(lbl_803EABD8 * 46603.37890625f)) {
                        continue;
                    }
                    a.mZ = 0.0f;
                    point.mZ = 0.0f;
                    b.mZ = 0.0f;
                    fn_800541AC(pRow, &a, &b);
                    turn = (angle - direction) & 0xFFFFFF;
                    if (turn > 0x800000) {
                        turn -= 0x1000000;
                    }
                    fn_80227690(&target, &pCommand->mUnknown12, &pCommand->mUnknown32);
                    fn_80227384(&offset, (Point_8017886C *)&target, turn);
                    fn_80227690(&target, &offset, &target);
                    fn_80227638(&target, &target, &pCommand->mUnknown12);
                    if (fn_800CD170((Point_8017886C *)&a, (Point_8017886C *)&b, (Point_8017886C *)&target)) {
                        continue;
                    }
                    target.mZ = pCommand->mUnknown12.mZ;
                    fn_80227970(&a, &b, &target, &point, &distance, &factor);
                    if (pCommand->mUnknown60 == 224 || pCommand->mUnknown60 == 235) {
                        limit = lbl_803EABE0;
                    } else {
                        limit = lbl_803EABDC;
                    }
                    if (!(distance < limit)) {
                        continue;
                    }
                    fn_80227690(&delta, &p->mMotion.mPos, &point);
                    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), angle) > 0x3FFFFF) {
                        continue;
                    }
                    fn_80227970(&a, &b, &p->mMotion.mPos, &closest, &playerDistance, &playerFactor);
                    switch (p->mpState->mId) {
                    case 12:
                    case 15:
                    case 23:
                    case 24:
                    case 28:
                    case 34:
                    case 36:
                    case 88:
                        limit = 16.0f;
                        break;
                    default:
                        limit = 2.0f;
                        break;
                    }
                    if (!(playerDistance < limit)) {
                        continue;
                    }
                    if (fn_800C36A8(p, i, pCommand->mUnknown60, entry, pCommand, &point, angle)) {
                        continue;
                    }
                    point.mZ = height;
                    found = 1;
                    row = (signed char)i;
                    rowAngle = angle;
                    best = point;
                    break;
                }
                if (found) {
                    break;
                }
            }
        }
        if (found) {
            p->mUnknown1160.mUnknown12Word = rowAngle;
            p->mUnknown1160.mUnknown16 = best.mX;
            p->mUnknown1160.mUnknown28 = row;
            p->mUnknown1160.mUnknown20 = best.mY;
            p->mUnknown1160.mUnknown24 = MIN(fn_8022781C(&best, &a), fn_8022781C(&best, &b));
            *pValue = pTable->mEntries[entry].mUnknown0;
            if (pB != 0) {
                *pB = entry;
            }
            return (short)pTable->mEntries[entry].mUnknown2;
        }
    }
    return -1;
}
