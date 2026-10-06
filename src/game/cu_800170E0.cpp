#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/cu_8003AEA8.h"
#include "game/cu_8003E214.h"
#include "game/cu_8007C9D4.h"
#include "game/cu_80181330.h"
#include "game/fn_8003B6BC.h"
#include "game/fn_80061AD4.h"
#include "game/fn_80178D18.h"
#include "game/fn_8017F584.h"
#include "game/fn_8018BE68.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C3284.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/fn_802372EC.h"

/* Block allocated by fn_80018E14 (0x1C bytes) and freed by fn_80018EF0:
   mCount lists of mSize ints, with a fill count and one more byte (0xFF when
   unset) per list, followed by byte-sized state. */
struct Table_803EBA08 {
    int **mppLists;
    unsigned char *mpCounts;
    unsigned char *mpUnknown08;
    unsigned char mUnknown0C[8];
    unsigned char mCount;
    unsigned char mUnknown15;
    unsigned char mSize;
    unsigned char mUnknown17;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown1A;
    unsigned char mUnknown1B;
};

/* One 0x18-byte row of the table at lbl_803EBA0C (lbl_803EBA10 rows): an id,
   the slot it fills (negative when not assigned) and the team it went to. */
struct Entry_803EBA0C {
    int mId;
    int mSlot;
    int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
    unsigned char mTeam;
    unsigned char mUnknown15;
};

/* One key/value pair of the table lbl_802F43F4. */
struct Pair_802F43F4 {
    int mValue;
    int mKey;
};

/* Object reached through lbl_803EBA20; only the word at +0x48 is read. */
struct Object_803EBA20 {
    char mUnknown00[0x48];
    int mUnknown48;
};

/* Pointer list read by fn_8003B234 (src/game/cu_8003AEA8.cpp). */
struct Pair_8003AEA8;

extern "C" {
void fn_80015D28(int id);
void fn_80023024(int a);
void fn_8003B0F8(int group, int kind, int slot, int code, int a, int b);
void fn_8003B1F4(int group);
void fn_8003B234(int group, int kind, Pair_8003AEA8 **pPairs);
void fn_8003B2D0(int group, int kind, int slot);
int fn_8003B360(int group);
void fn_8003DE74(int team, int *pList);
int fn_800551D8(unsigned char a);
void fn_800551E0(unsigned char a, int b, char *pText, int length);
void fn_80055230(unsigned char a, int b, int c, int *pList0, int *pList1, char *pText, int length);
float fn_8005F754(void);
int fn_8005FC7C(void);
void fn_8005FCF8(int *pA, int *pB);
void fn_80060330(int a, int *pList, int count, Object_8008044C *pObject);
void fn_80061B90(int team, int *pDigp);
int fn_8007A934(Object_8007A334 *pObject, int key);
void fn_8007AEE8(Object_8007A334 *pObject);
void fn_8007AF14(Object_8007A334 *pObject);
int fn_8007AF34(Object_8007A334 *pObject);
int fn_8007AF5C(Object_8007A334 *pObject);
int fn_8007AF84(int team);
unsigned char fn_8007B090(int a);
void fn_8007B14C(int pad, int id);
void fn_8007CAEC(int index, int value);
int fn_8008058C(int *pId, int *pPos, int *pValue, int a, int b, int c, int mode);
void fn_8008079C(int which);
void fn_8008082C(int row, int which);
void fn_80080874(int which);
void fn_80080998(Object_8008044C *pObject, int value);
void fn_80080A34(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80080B08(Object_8008044C *pObject, char *pBuffer, int size);
int fn_80080CB0(Object_8008044C *pObject);
int fn_80080D10(Object_8008044C *pObject);
int fn_80081188(Object_8008044C *pObject);
int fn_800812B0(Object_8008044C *pObject, int index);
void fn_8008135C(Object_8008044C *pObject, int index, int value);
void fn_80081F50(Object_8008044C *pObject, int team, int a);
int fn_80082414(int index);
int fn_8008257C(int count, int *pOut);
int fn_800827EC(int id, int value);
int fn_80082864(void);
void fn_800828FC(void);
void fn_800829D8(void);
int fn_80082AB0(int a, int b, int c);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
int fn_800844B8(const char *pName, int a, int b);
int fn_8008454C(int a, int b, int c);
int fn_80086868(int *pList, int max);
int fn_800868A8(int *pList, int max);
int fn_80086ACC(int *pList);
int fn_80086B50(void);
int fn_80086BA4(int index);
int fn_801485D4(void);
int fn_801486A0(void);
void fn_80148AF8(Class_80148A58 *pObject);
int fn_80178308(void);
int fn_80178320(void);
int fn_8017F60C(void);
void fn_8017F670(int a, char *pText);
int fn_801801B4(void);
int fn_80188030(int a);
void fn_8018807C(unsigned char a);
void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor);
int fn_80188DF0(int a);
void fn_8018C48C(int tag);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_801C302C(const char *s1, const char *s2, int n);
void fn_801F51DC(int a, void *pBase, int count, int size, int (*pCompare)(Entry_803EBA0C *, Entry_803EBA0C *), int b,
                 int c, int d);
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_8021E2B4(void *pObject, int a, int b);
void fn_8021E72C(void *pObject, int a, int b);
void *fn_8021EA44(int index);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022A508(int a, int b, int c, int d, int e);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
void fn_8022DC7C(int a);
void fn_8022DCB0(int a);
void fn_8022DCE4(int a);
void fn_8022DD18(int a);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F384(int a);
int fn_8022F4BC(void);

Table_803EBA08 *lbl_803EBA08 = 0;
Entry_803EBA0C *lbl_803EBA0C = 0;
int lbl_803EBA10 = 0;
int lbl_803EBA14 = 0;
Record_8003E214 *lbl_803EBA18 = 0;
unsigned char lbl_803EBA1C = 0;
Object_803EBA20 *lbl_803EBA20 = 0;
VetsRow_8018EC68 *lbl_803EBA24 = 0;
int lbl_803EBA28 = 0;
int lbl_803EBA2C = -1;
unsigned char lbl_803EBA30 = 0;
int lbl_803EBA34 = 0;
unsigned char lbl_803EBA38[4] = { 1, 0, 0, 0 };
signed char lbl_803EBA3C[7] = { 2, 2, 2, 2, 2, 2, 2 };
unsigned char lbl_803EBA43 = 1;

int lbl_803ECE58[2];
int lbl_803ECE60;

Object_8008044C lbl_8036B168;
Object_8007A334 lbl_8036B194;
unsigned short lbl_8036B1C0[7];
int lbl_8036B1D0[8];
int lbl_8036B1F0[8];
int lbl_8036B210[7];

Pair_802F43F4 lbl_802F43F4[8] = {
    { 0, 0x2E }, { 0x1E2, 0x2F }, { 0x1E8, 0x30 }, { 0x195, 0x31 },
    { 0x1C1, 0x32 }, { 0x196, 0x33 }, { 0x1D3, 0x34 }, { 0x1F1, 0x35 },
};
int lbl_802F4434[14] = { 0, 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6 };
int lbl_802F446C[7] = { 1, 1, 2, 3, 2, 2, 3 };
int lbl_802F4488[7][3] = {
    { 0, 0xFF, 0xFF }, { 1, 0xFF, 0xFF }, { 2, 3, 0xFF }, { 4, 5, 6 },
    { 7, 8, 0xFF }, { 9, 10, 0xFF }, { 11, 12, 13 },
};
int lbl_802F44DC[10] = { 0, 4, 1, 3, 2, 5, 6, 7, 8, 9 };

void fn_80018374(void);
int fn_800183EC(Entry_803EBA0C *pEntry, int pos, float scale, int team);
void fn_800184B4(int id, float scale);
void fn_80018AF0(int group);
void fn_80018B60(int group, int *pList);
void fn_80018E14(unsigned char count, unsigned char size);
void fn_80018EF0(void);
void fn_8001AA8C(int id, int *pSlot);
int fn_8001AC48(int *pDays, int *pResult);
void fn_8001B228(void);

void fn_800170E0(void)
{
    int n = 0;
    int side = 2;
    if (fn_8007AF84(0) == 0) side = 0;
    if (fn_8007AF84(1) == 0) side = 1;
    switch (fn_801486A0()) {
    case 0:
    case 1:
        side = 0;
        break;
    }
    if (side != 2) {
        int *list = (int *)fn_801D2B7C((lbl_803EBA10 + 1) * sizeof(int), 0, 0);
        for (int i = 0; i < lbl_803EBA10; i++) {
            list[n++] = lbl_803EBA0C[i].mId;
        }
        list[n] = 0x7FFF;
        fn_8003E710(lbl_803ECE58[side], list, &lbl_803EBA18);
        fn_801D2BD0(list);
    }
}

void fn_800171D0(void)
{
    if (lbl_803EBA18) {
        fn_8003E8B8(&lbl_803EBA18);
        lbl_803EBA18 = 0;
    }
}

int fn_80017208(int group)
{
    int count;
    if (group == 6) {
        count = lbl_803EBA10 - lbl_8036B1C0[6];
    } else {
        count = lbl_8036B1C0[group + 1] - lbl_8036B1C0[group];
    }
    return count;
}

int fn_80017248(int group, int index)
{
    return index + lbl_8036B1C0[group];
}

int fn_80017260(int group, int index)
{
    return index - lbl_8036B1C0[group];
}

int fn_80017278(int index)
{
    return lbl_802F4434[lbl_803EBA0C[index].mUnknownC];
}

int fn_8001729C(void)
{
    return fn_802372EC(0, 5);
}

Entry_803EBA0C *fn_800172C4(int id, int *pIndex)
{
    Entry_803EBA0C *found = 0;
    int i;
    for (i = 0; i < lbl_803EBA10; i++) {
        if (lbl_803EBA0C[i].mId == id) {
            found = &lbl_803EBA0C[i];
            break;
        }
    }
    if (pIndex) *pIndex = i;
    return found;
}

void fn_80017330(int team)
{
    int list[8];
    fn_80018AF0(team);
    fn_80018B60(team, list);
    fn_8003B3F8(team, list, lbl_803ECE58[team]);
}

int fn_80017380(int teamId)
{
    int n = 0;
    int id = 0;
    int pos = 0;
    int value = 0;
    int counts[7];
    int used[7];
    int total = 0;
    int i;
    for (i = 0; i <= 6; i++) {
        counts[i] = fn_8008058C(&id, &pos, &value, lbl_802F4488[i][0], lbl_802F4488[i][1], lbl_802F4488[i][2], 2);
        total += counts[i];
        int max = lbl_803EBA3C[i];
        for (used[i] = 0; used[i] < counts[i] && used[i] < max; used[i]++) {
            fn_8008082C(used[i], 2);
            fn_8008079C(2);
            lbl_803EBA3C[i]--;
            lbl_803EBA0C[n].mId = id;
            lbl_803EBA0C[n].mUnknown8 = value;
            lbl_803EBA0C[n].mUnknownC = pos;
            lbl_803EBA0C[n].mUnknown10 = 0xFF;
            lbl_803EBA0C[n].mSlot = -1;
            lbl_803EBA0C[n].mTeam = 2;
            lbl_803EBA0C[n].mUnknown15 = 0xFF;
            n++;
        }
        fn_80080874(2);
    }
    while (n < lbl_803EBA10 && n < total) {
        i = fn_802372EC(0, 7);
        if (counts[i] > used[i]) {
            fn_8008058C(&id, &pos, &value, lbl_802F4488[i][0], lbl_802F4488[i][1], lbl_802F4488[i][2], 2);
            fn_8008082C(used[i], 2);
            fn_8008079C(2);
            lbl_803EBA3C[i]--;
            lbl_803EBA0C[n].mId = id;
            lbl_803EBA0C[n].mUnknown8 = value;
            lbl_803EBA0C[n].mUnknownC = pos;
            lbl_803EBA0C[n].mUnknown10 = 0xFF;
            lbl_803EBA0C[n].mSlot = -1;
            lbl_803EBA0C[n].mTeam = 2;
            lbl_803EBA0C[n].mUnknown15 = 0xFF;
            n++;
            fn_80080874(2);
            used[i]++;
        }
        fn_80023024(1);
    }
    return n;
}

int fn_80017610(int n, int teamId, float scale)
{
    int count0 = 0;
    int team = 0;
    int max = 0;
    int id = 0;
    int pos = 0;
    int value = 0;
    int picked[2];
    if (lbl_803EBA38[1]) {
        fn_8008257C(fn_80082864(), &team);
    }
    for (int i = 0; i <= 6; i++) {
        int count1;
        if (lbl_803EBA38[0]) {
            count0 = fn_8008058C(&id, &pos, &value, lbl_802F4488[i][0], lbl_802F4488[i][1], lbl_802F4488[i][2], 0);
        } else {
            count0 = 0;
        }
        if (lbl_803EBA38[1]) {
            count1 = 0;
            int rows = fn_8008058C(&id, &pos, &value, lbl_802F4488[i][0], lbl_802F4488[i][1], lbl_802F4488[i][2], 1);
            for (int row = 0; row < rows; row++) {
                fn_8008082C(row, 1);
                fn_8008079C(1);
                if (fn_800827EC(id, team) == 0) count1++;
            }
        } else {
            count1 = 0;
        }
        int extra = lbl_803EBA38[2] ? 6 : 0;
        int total = count0 + count1;
        if (total + extra < lbl_803EBA3C[i]) {
            max = total + extra;
        } else {
            max = lbl_803EBA3C[i];
        }
        for (int k = 0; k < max && n < lbl_803EBA10; k++, n++) {
            int pick;
            int second = (fn_802372EC(0, 6) && count1) ? 1 : 0;
            if (second == 1) {
                pick = count0 + fn_802372EC(0, count1);
            } else {
                pick = fn_802372EC(0, count0);
            }
            for (;;) {
                int found = 0;
                for (int j = 0; j < k; j++) {
                    if (pick == picked[j]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) break;
                pick = (pick == total - 1) ? 0 : pick + 1;
            }
            picked[k] = pick;
            if (total != 0 && pick < count0 + count1) {
                if (pick < count0) {
                    fn_8008082C(pick, 0);
                    fn_8008079C(0);
                } else if (pick < count0 + count1) {
                    int row = pick - count0;
                    fn_8008082C(row, 1);
                    fn_8008079C(1);
                    for (int tries = 0; tries < count1 - 1 && fn_800827EC(id, team) != 0; tries++) {
                        row++;
                        if (row >= count0 + count1) row = count0;
                        fn_8008082C(row, 1);
                        fn_8008079C(1);
                    }
                }
                lbl_803EBA0C[n].mId = id;
                lbl_803EBA0C[n].mUnknown8 = value;
                lbl_803EBA0C[n].mUnknownC = pos;
                lbl_803EBA0C[n].mUnknown10 = 0xFF;
                lbl_803EBA0C[n].mSlot = -1;
                lbl_803EBA0C[n].mTeam = 2;
                lbl_803EBA0C[n].mUnknown15 = 0xFF;
            } else {
                pos = lbl_802F4488[i][0];
                lbl_803EBA0C[n].mUnknownC = pos;
                fn_800183EC(&lbl_803EBA0C[n], pos, scale, teamId);
            }
            fn_80023024(1);
        }
        if (lbl_803EBA38[0]) fn_80080874(0);
        if (lbl_803EBA38[1]) fn_80080874(1);
    }
    return n;
}

int fn_800179EC(int start, int teamId, float scale)
{
    int n = start;
    int count0 = 0;
    int team = 0;
    int range = 0;
    int id = 0;
    int pos = 0;
    int value = 0;
    count0 = fn_8008058C(&id, &pos, &value, -1, -1, -1, 0);
    int offset = 0;
    int rows = 0;
    int seq = 0;
    int count1;
    if (!lbl_803EBA38[0]) count0 = 0;
    if (lbl_803EBA38[1]) {
        rows = fn_8008058C(&id, &pos, &value, -1, -1, -1, 1);
        count1 = fn_8008257C(rows, &team);
    } else {
        count1 = 0;
    }
    int extra = lbl_803EBA38[2] ? 42 : 0;
    int total = count0 + count1;
    range = total + extra;
    for (; n < lbl_803EBA10; n++) {
        int pick;
        if (lbl_803EBA34 == 2) {
            pick = seq++;
            if (pick < total) {
                if (pick < count0) {
                    fn_8008082C(pick, 0);
                    fn_8008079C(0);
                } else if (pick < count0 + count1) {
                    int row = pick - count0 + offset;
                    fn_8008082C(row, 1);
                    fn_8008079C(1);
                    for (int tries = 0; tries < rows - 1 && fn_800827EC(id, team) != 0; tries++) {
                        row++;
                        if (row >= rows) row = 0;
                        fn_8008082C(row, 1);
                        offset++;
                        fn_8008079C(1);
                    }
                }
            }
        } else {
            pick = fn_802372EC(0, range);
            if (pick < total) {
                for (;;) {
                    int taken = 0;
                    if (pick < count0) {
                        fn_8008082C(pick, 0);
                        fn_8008079C(0);
                    } else if (pick < count0 + count1) {
                        fn_8008082C(fn_802372EC(0, 11), 1);
                        fn_8008079C(1);
                        if (fn_800827EC(id, team)) taken = 1;
                    }
                    for (int j = 0; j < n; j++) {
                        if (id == lbl_803EBA0C[j].mId) {
                            taken = 1;
                            break;
                        }
                    }
                    if (!taken) break;
                    pick = (pick == range - 1) ? 0 : pick + 1;
                }
            }
        }
        if (pick < total) {
            lbl_803EBA0C[n].mId = id;
            lbl_803EBA0C[n].mUnknown8 = value;
            lbl_803EBA0C[n].mUnknownC = pos;
            lbl_803EBA0C[n].mUnknown10 = 0xFF;
            lbl_803EBA0C[n].mSlot = -1;
            lbl_803EBA0C[n].mTeam = 2;
            lbl_803EBA0C[n].mUnknown15 = 0xFF;
        } else if (lbl_803EBA38[2]) {
            range--;
            int group = (pos + 1) % 7;
            int index = fn_802372EC(0, lbl_802F446C[group]);
            pos = lbl_802F4488[group][index];
            lbl_803EBA0C[n].mUnknownC = pos;
            fn_800183EC(&lbl_803EBA0C[n], pos, scale, teamId);
        } else if (range < lbl_803EBA10) {
            fn_8008082C(pick - range, 0);
            fn_8008079C(0);
            lbl_803EBA0C[n].mId = id;
            lbl_803EBA0C[n].mUnknown8 = value;
            lbl_803EBA0C[n].mUnknownC = pos;
            lbl_803EBA0C[n].mUnknown10 = 0xFF;
            lbl_803EBA0C[n].mSlot = 1000;
            lbl_803EBA0C[n].mTeam = 2;
            lbl_803EBA0C[n].mUnknown15 = 0xFF;
        }
        fn_80023024(1);
    }
    fn_80080874(0);
    if (lbl_803EBA38[1]) fn_80080874(1);
    return n;
}

int fn_80017DF4(void)
{
    int teams[8];
    int others[56];
    int index;
    int digt;
    int count;
    int n;
    int i;
    unsigned int j;

    index = fn_8022F384(fn_8022F4BC());
    digt = fn_8018BE68(index, 1, (Result_8018BE68 *)teams);
    if (fn_800809C4(&lbl_8036B168, teams[0], 0)) {
        fn_8007ABA4(&lbl_8036B168, 0x44494F50, teams[0]);
        fn_8007ABA4(&lbl_8036B168, 0x44494754, digt);
        fn_8007ABA4(&lbl_8036B168, 0x49544754, digt);
        lbl_802F43F4[0].mValue = teams[0];
        fn_8007A934((Object_8007A334 *)&lbl_8036B168, 0x50585350);
        fn_8007A98C(&lbl_8036B168, 0x4F504250);
    }
    fn_80086BA4(index);
    fn_80086ACC(lbl_8036B1F0);
    fn_80086868(&teams[1], 7);
    count = fn_800868A8(others, 56);
    fn_80086B50();
    lbl_803EBA10 = count + 8;
    lbl_803EBA0C = (Entry_803EBA0C *)fn_801D2B7C(lbl_803EBA10 * sizeof(Entry_803EBA0C), 0, 0);
    n = 0;
    for (i = 0; i < 8; i++) {
        lbl_803EBA0C[n].mId = teams[i];
        lbl_803EBA0C[n].mUnknown8 = 0;
        lbl_803EBA0C[n].mUnknownC = 0;
        lbl_803EBA0C[n].mUnknown10 = 0xFF;
        lbl_803EBA0C[n].mSlot = -1;
        lbl_803EBA0C[n].mTeam = 8;
        lbl_803EBA0C[n].mUnknown15 = 0xFF;
        if (fn_800809C4(&lbl_8036B168, teams[i], 0)) {
            int value8 = fn_8007A934((Object_8007A334 *)&lbl_8036B168, 0x50585350);
            int valueC = fn_8007A98C(&lbl_8036B168, 0x4F504250);
            lbl_803EBA0C[n].mUnknown8 = value8;
            lbl_803EBA0C[n].mUnknownC = valueC;
        }
        n++;
    }
    for (i = 0; i < count; i++) {
        lbl_803EBA0C[n].mId = others[i];
        lbl_803EBA0C[n].mUnknown8 = 0;
        lbl_803EBA0C[n].mUnknownC = 0;
        lbl_803EBA0C[n].mUnknown10 = 0xFF;
        lbl_803EBA0C[n].mSlot = -1;
        lbl_803EBA0C[n].mTeam = 8;
        lbl_803EBA0C[n].mUnknown15 = 0xFF;
        if (fn_800809C4(&lbl_8036B168, others[i], 0)) {
            int value8 = fn_8007A934((Object_8007A334 *)&lbl_8036B168, 0x50585350);
            int valueC = fn_8007A98C(&lbl_8036B168, 0x4F504250);
            lbl_803EBA0C[n].mUnknown8 = value8;
            lbl_803EBA0C[n].mUnknownC = valueC;
        }
        n++;
    }
    for (i = 0; i < 8; i++) {
        lbl_803EBA08->mUnknown15 = i;
        lbl_803EBA08->mUnknown19 = i;
        j = 0;
        while (j < 8 && lbl_802F43F4[j].mKey != lbl_8036B1F0[i]) {
            j++;
        }
        fn_8001AA8C(teams[j], 0);
    }
    lbl_803EBA28 = teams[0];
    return n;
}

int fn_80018114(void)
{
    Result_8018BE68 picks;
    int index;
    int digt;
    int value8;
    int valueC;
    int ok = 0;

    index = fn_8022F384(fn_8022F4BC());
    digt = fn_8018BE68(index, 1, &picks);
    if (fn_800809C4(&lbl_8036B168, picks.mUnknown0, 0)) {
        fn_8007ABA4(&lbl_8036B168, 0x44494F50, picks.mUnknown0);
        ok = 1;
        fn_8007ABA4(&lbl_8036B168, 0x44494754, digt);
        fn_8007ABA4(&lbl_8036B168, 0x49544754, digt);
        value8 = fn_8007A934((Object_8007A334 *)&lbl_8036B168, 0x50585350);
        valueC = fn_8007A98C(&lbl_8036B168, 0x4F504250);
        lbl_803EBA0C[0].mId = picks.mUnknown0;
        lbl_803EBA0C[0].mUnknown8 = value8;
        lbl_803EBA0C[0].mUnknownC = valueC;
        lbl_803EBA0C[0].mUnknown10 = 0xFF;
        lbl_803EBA0C[0].mSlot = -1;
        lbl_803EBA0C[0].mTeam = 2;
        lbl_803EBA0C[0].mUnknown15 = 0xFF;
        lbl_803EBA08->mUnknown15 = 1;
        lbl_803EBA08->mUnknown19 = 1;
        fn_8001AA8C(picks.mUnknown0, 0);
        lbl_803EBA28 = picks.mUnknown0;
    }
    return ok;
}

void fn_80018230(void)
{
    float scale = 0.0f;
    int n = 0;
    int team = 0;
    int i;

    if (lbl_803EBA24) {
        fn_80017DF4();
    } else {
        lbl_803EBA0C = (Entry_803EBA0C *)fn_801D2B7C(lbl_803EBA10 * sizeof(Entry_803EBA0C), 0, 0);
        if (lbl_803EBA20) {
            n = fn_80018114();
        }
        if (lbl_803EBA38[2]) {
            fn_80018374();
            team = fn_800844B8("New Team", 6, 0);
            fn_800828FC();
            scale = fn_8005F754();
        }
        for (i = 0; i < 7; i++) {
            lbl_803EBA3C[i] = 2;
        }
        if (lbl_803EBA38[3]) {
            n = fn_80017380(team);
        }
        if (lbl_803EBA34 != 2) {
            if (n >= lbl_803EBA10) {
                goto done;
            }
            n = fn_80017610(n, team, scale);
        }
        if (n < lbl_803EBA10) {
            fn_800179EC(n, team, scale);
        }
    }
done:
    if (lbl_803EBA38[2]) {
        fn_800829D8();
    }
    fn_80023024(1);
}

void fn_80018374(void)
{
    int i;

    fn_8022EF8C(0, 0x43544E52);
    for (i = 0; i < 7; i++) {
        lbl_8036B210[i] = fn_8008454C(6, -1, 0);
    }
    lbl_803ECE60 = 0;
    fn_8022EFBC(0, 0x43544E52);
}

int fn_800183EC(Entry_803EBA0C *pEntry, int pos, float scale, int team)
{
    int id;

    id = fn_80082AB0(pos, team, lbl_803EBA2C);
    lbl_803EBA2C = id;
    fn_800809C4(&lbl_8036B168, id, 0);
    fn_80080998(&lbl_8036B168, lbl_8036B210[lbl_803ECE60]);
    fn_800184B4(id, scale);
    pEntry->mTeam = 2;
    pEntry->mUnknown15 = 0xFF;
    pEntry->mId = id;
    pEntry->mSlot = -1;
    pEntry->mUnknown8 = 0;
    if (++lbl_803ECE60 == 7) {
        lbl_803ECE60 = 0;
    }
    return 1;
}

void fn_800184B4(int id, float scale)
{
    int i;

    if (lbl_803EBA20) {
        fn_800809C4(&lbl_8036B168, id, 0);
        for (i = 0; i < 10; i++) {
            unsigned int value = fn_800812B0(&lbl_8036B168, lbl_802F44DC[i]);

            value -= (int)((float)value * scale);
            value = value > 100 ? 100 : value;
            value = value < 5 ? 5 : value;
            fn_8008135C(&lbl_8036B168, lbl_802F44DC[i], value);
        }
    }
}

int fn_8001859C(Entry_803EBA0C *pA, Entry_803EBA0C *pB)
{
    char first[16];
    char last[16];
    char nameA[32];
    char nameB[32];

    if (fn_800809C4(&lbl_8036B168, pA->mId, 0)) {
        fn_80080A68(&lbl_8036B168, last, 15);
        fn_80080A34(&lbl_8036B168, first, 12);
        fn_801C2D88(nameA, 27, "%s%s", last, first);
        if (fn_800809C4(&lbl_8036B168, pB->mId, 0)) {
            fn_80080A68(&lbl_8036B168, last, 15);
            fn_80080A34(&lbl_8036B168, first, 12);
            fn_801C2D88(nameB, 27, "%s%s", last, first);
            return fn_801C302C(nameA, nameB, 27);
        }
    }
    return 0;
}

int fn_8001869C(Entry_803EBA0C *pA, Entry_803EBA0C *pB)
{
    return (unsigned char)lbl_802F4434[pA->mUnknownC] - (unsigned char)lbl_802F4434[pB->mUnknownC];
}

void fn_800186CC(void)
{
    unsigned short i;
    int last;
    int group;
    int j;
    int count;

    fn_801F51DC(1, lbl_803EBA0C, lbl_803EBA10, sizeof(Entry_803EBA0C), fn_8001869C, 0, 0, 1);
    for (i = 0; i < 7; i++) {
        lbl_8036B1C0[i] = lbl_803EBA10;
    }
    last = 0;
    lbl_8036B1C0[0] = 0;
    for (i = 0; i < lbl_803EBA10; i++) {
        group = fn_80017278(i);
        if (group != last) {
            for (j = last + 1; j <= group; j++) {
                lbl_8036B1C0[j] = i;
            }
            last = group;
        }
    }
    for (i = 0; i < 6; i++) {
        if (lbl_8036B1C0[i + 1] < lbl_8036B1C0[i]) {
            lbl_8036B1C0[i + 1] = lbl_8036B1C0[i];
        }
    }
    for (i = 0; i < 7; i++) {
        count = fn_80017208(i);
        if (count) {
            fn_801F51DC(1, &lbl_803EBA0C[lbl_8036B1C0[i]], count, sizeof(Entry_803EBA0C), fn_8001859C, 0, 0, 1);
        }
    }
}

void fn_80018848(void)
{
    void *pFont;
    int i;

    pFont = fn_8021EA44(1);
    for (i = 0; i < lbl_803EBA10; i++) {
        if (lbl_803EBA0C[i].mUnknown8 > 630) {
            fn_8021E2B4(pFont, 10, lbl_803EBA0C[i].mUnknown8);
        }
    }
    lbl_803EBA08->mUnknown1B = 1;
}

void fn_800188CC(void)
{
    void *pFont;
    int i;

    if (lbl_803EBA08->mUnknown1B) {
        pFont = fn_8021EA44(1);
        for (i = 0; i < lbl_803EBA10; i++) {
            if (lbl_803EBA0C[i].mUnknown8 > 630) {
                fn_8021E72C(pFont, 10, lbl_803EBA0C[i].mUnknown8);
            }
            if (i % 10 == 9) {
                fn_80023024(1);
            }
        }
        lbl_803EBA08->mUnknown1B = 0;
    }
}

void fn_80018990(void)
{
    lbl_803ECE60 = 0;
    fn_80018230();
    fn_800186CC();
    fn_80018848();
}

void fn_800189C0(char *pDest, int unused, int abbreviate)
{
    char first[16];
    char last[16];

    fn_80080A34(&lbl_8036B168, first, 12);
    fn_80080A68(&lbl_8036B168, last, 15);
    if (abbreviate) {
        if (first[0] == 0 || first[0] == ' ') {
            fn_801C2E18(pDest, "%s", last);
        } else {
            fn_801C2E18(pDest, "%c. %s", first[0], last);
        }
    } else {
        fn_801C2E18(pDest, "%s %s", first, last);
    }
}

int fn_80018A88(void)
{
    unsigned char i;
    int result = 1;

    for (i = 0; i < lbl_803EBA08->mCount; i++) {
        if (lbl_803EBA08->mpCounts[i] < lbl_803EBA08->mSize) {
            result = 0;
            break;
        }
    }
    return result;
}

void fn_80018AF0(int group)
{
    int slot = lbl_803EBA08->mUnknown0C[group];
    int i;

    for (i = 0; i < lbl_803EBA10 && slot <= 6; i++) {
        Entry_803EBA0C *pEntry = &lbl_803EBA0C[i];

        if (pEntry->mSlot < 0 || pEntry->mSlot == 1000) {
            pEntry->mSlot = slot;
            pEntry->mTeam = group;
            slot++;
        }
    }
}

void fn_80018B60(int group, int *pList)
{
    int n = 0;
    int i;

    for (i = 0; i < lbl_803EBA10; i++) {
        if (lbl_803EBA0C[i].mSlot >= 0 && lbl_803EBA0C[i].mTeam == group) {
            pList[lbl_803EBA0C[i].mSlot] = lbl_803EBA0C[i].mId;
            n++;
        }
    }
    pList[n] = 0x7FFF;
}

int fn_80018BB8(int id, int side, int *pList)
{
    int i;
    int end;

    i = side == 0 ? 7 : 0;
    end = side == 0 ? 13 : 6;
    for (; i <= end; i++) {
        if (pList[i] == id) {
            break;
        }
    }
    return i;
}

void fn_80018C10(int *pIds, int *pValues, int *pList)
{
    int copy[14];
    int i;
    unsigned int j;
    unsigned int k;

    for (i = 0; i < 14; i++) {
        copy[i] = pList[i];
    }
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 2; k++) {
            pList[fn_80018BB8(pIds[j], k, copy)] = pValues[j];
        }
    }
}

static inline void ResetTable_803EBA08(int size)
{
    unsigned char i;

    for (i = 0; i < lbl_803EBA08->mCount; i++) {
        fn_801C1F94(lbl_803EBA08->mppLists[i], 0xFF, lbl_803EBA08->mSize * 4);
    }
    fn_801C1F94(lbl_803EBA08->mpCounts, 0, lbl_803EBA08->mCount);
    fn_801C1F94(lbl_803EBA08->mUnknown0C, 0, size);
    lbl_803EBA08->mUnknown17 = 0;
    lbl_803EBA08->mUnknown18 = 0;
}

void fn_80018CA4(int *pTeam, int *pIds, const char *pName)
{
    int newIds[7];
    int oldIds[7];
    unsigned short teamCount = 1;
    unsigned short count = 7;
    int handle = -1;
    unsigned int i;

    fn_8022C628(0x54415453, 0x4D414554, pTeam, &teamCount);
    fn_801FCE10(0,
                "use 'TATS' insert into 'MAET' set 'DIGT' = \x82 and 'PYTT' = \x82 and 'DIOT' = \x82 and "
                "'DROT' = \x82 and 'LGLT' = \x82 and 'SIVT' = \x83 and 'ANDT' = \x88 and 'LDTC' = \x82\n",
                *pTeam, 6, *pTeam, 0, 0, 1, pName, 1);
    fn_80229AA4(0x54415453, 0x59414C50, newIds, &count);
    for (i = 0; i < 7; i++) {
        fn_801F9980(0x54415453, &handle);
        oldIds[i] = pIds[i];
        fn_801FCE10(0, "use 'TATS' select into \x8c * from 'YALP' where ('DIGP' = \x82)\n", handle, oldIds[i]);
        fn_801FCE10(0, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIGP' = \x82 where ('DIGP' = \x82)\n", handle,
                    *pTeam, newIds[i], oldIds[i]);
        fn_801FCE10(0, "use 'TATS' insert into \x8c.'YALP' * select * from \x8c\n", 0x54415453, handle);
        fn_801F967C(0x54415453, handle);
    }
    fn_80018C10(oldIds, newIds, pIds);
}

void CopyThcdRows(int team, int *pOldIds, int *pNewIds)
{
    int handle = -1;
    unsigned int i;

    for (i = 0; i < 7; i++) {
        fn_801F9980(0x54415453, &handle);
        fn_801FCE10(0, "use 'TATS' select into \x8c * from 'THCD' where ('DIGP' = \x82)\n", handle, pOldIds[i]);
        fn_801FCE10(0, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIGP' = \x82 where ('DIGP' = \x82)\n", handle,
                    team, pNewIds[i], pOldIds[i]);
        fn_801FCE10(0, "use 'TATS' insert into \x8c.'THCD' * select * from \x8c\n", 0x54415453, handle);
        fn_801F967C(0x54415453, handle);
    }
}

void fn_80018E14(unsigned char count, unsigned char size)
{
    unsigned char i;

    lbl_803EBA08 = (Table_803EBA08 *)fn_801D2B7C(sizeof(Table_803EBA08), 0, 0);
    lbl_803EBA08->mCount = count;
    lbl_803EBA08->mSize = size;
    lbl_803EBA08->mUnknown1B = 0;
    lbl_803EBA08->mpUnknown08 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    lbl_803EBA08->mppLists = (int **)fn_801D2B7C(count * 4, 0, 0);
    for (i = 0; i < count; i++) {
        lbl_803EBA08->mppLists[i] = (int *)fn_801D2B7C(size * 4, 0, 0);
    }
    lbl_803EBA08->mpCounts = (unsigned char *)fn_801D2B7C(count, 0, 0);
}

void fn_80018EF0(void)
{
    unsigned char i;

    fn_801D2BD0(lbl_803EBA08->mpCounts);
    lbl_803EBA08->mpCounts = 0;
    for (i = 0; i < lbl_803EBA08->mCount; i++) {
        fn_801D2BD0(lbl_803EBA08->mppLists[i]);
    }
    fn_801D2BD0(lbl_803EBA08->mppLists);
    lbl_803EBA08->mppLists = 0;
    fn_801D2BD0(lbl_803EBA08->mpUnknown08);
    lbl_803EBA08->mpUnknown08 = 0;
    fn_801D2BD0(lbl_803EBA08);
    lbl_803EBA08 = 0;
}

void fn_80018F9C(unsigned char size)
{
    unsigned char i;
    unsigned char team;
    unsigned char other;

    fn_80018E14(2, size);
    team = fn_8007CB6C(2);
    other = team == 0;
    lbl_803EBA08->mpUnknown08[0] = fn_8007B090(other);
    lbl_803EBA08->mpUnknown08[1] = fn_8007B090(team);
    lbl_803EBA08->mUnknown15 = 0;
    lbl_803EBA08->mUnknown19 = other;
    ResetTable_803EBA08(2);
}

void fn_800190A0(void)
{
    unsigned char i;

    fn_80018E14(8, 7);
    lbl_803EBA08->mUnknown15 = 0;
    lbl_803EBA08->mUnknown19 = 0;
    {
        Object_8007A334 cursor;
        int found;

        fn_8007AEE8(&cursor);
        found = fn_8007A444(&cursor);
        for (i = 0; i < 8; i++) {
            unsigned char id;

            if (found) {
                id = fn_8007AF34(&cursor);
                found = fn_8007A510(&cursor);
            } else {
                id = 0xFF;
            }
            lbl_803EBA08->mpUnknown08[i] = id;
        }
        fn_8007AF14(&cursor);
    }
    ResetTable_803EBA08(8);
}

void fn_800191E4(void)
{
    unsigned char i;

    fn_80018E14(6, 1);
    lbl_803EBA08->mUnknown15 = 0;
    lbl_803EBA08->mUnknown19 = 1;
    {
        Object_8007A334 cursor;
        int found;

        fn_8007AEE8(&cursor);
        found = fn_8007A444(&cursor);
        for (i = 0; i < 6; i++) {
            unsigned char id;

            if (found) {
                id = fn_8007AF34(&cursor);
                found = fn_8007A510(&cursor);
            } else {
                id = 0xFF;
            }
            lbl_803EBA08->mpUnknown08[i] = id;
        }
        fn_8007AF14(&cursor);
    }
    if (!fn_8017F60C()) {
        for (i = 0; i < 6; i++) {
            unsigned char j = i + fn_802372EC(0, 6 - i);
            unsigned char id = lbl_803EBA08->mpUnknown08[i];

            lbl_803EBA08->mpUnknown08[i] = lbl_803EBA08->mpUnknown08[j];
            lbl_803EBA08->mpUnknown08[j] = id;
        }
    }
    ResetTable_803EBA08(2);
}

void fn_80019380(void)
{
    unsigned char i;
    unsigned int count = fn_80178D70(0) * 2;
    unsigned char team = fn_8007CB6C(2);
    unsigned char other = team == 0;

    fn_80018E14(count, 1);
    lbl_803EBA08->mUnknown15 = 0;
    lbl_803EBA08->mUnknown19 = other;
    lbl_803EBA08->mpUnknown08[0] = fn_8007B090(other);
    lbl_803EBA08->mpUnknown08[1] = fn_8007B090(team);
    if (count > 2) {
        lbl_803EBA08->mpUnknown08[2] = lbl_803EBA08->mpUnknown08[0];
        lbl_803EBA08->mpUnknown08[3] = lbl_803EBA08->mpUnknown08[1];
        {
            Object_8007A334 cursor;
            int found;

            fn_8007AEE8(&cursor);
            for (found = fn_8007A444(&cursor); found; found = fn_8007A510(&cursor)) {
                unsigned char id = fn_8007AF34(&cursor);

                if (fn_8007AF5C(&cursor) == other && id != lbl_803EBA08->mpUnknown08[0]) {
                    lbl_803EBA08->mpUnknown08[2] = id;
                    break;
                }
            }
            for (found = fn_8007A444(&cursor); found; found = fn_8007A510(&cursor)) {
                unsigned char id = fn_8007AF34(&cursor);

                if (fn_8007AF5C(&cursor) == team && id != lbl_803EBA08->mpUnknown08[1]) {
                    lbl_803EBA08->mpUnknown08[3] = id;
                    break;
                }
            }
            fn_8007AF14(&cursor);
        }
    }
    ResetTable_803EBA08(2);
}

void fn_80019588(void)
{
    unsigned char i;

    fn_80018E14(7, 1);
    lbl_803EBA08->mUnknown15 = 0;
    lbl_803EBA08->mUnknown19 = 1;
    {
        Object_8007A334 cursor;
        int found;

        fn_8007AEE8(&cursor);
        found = fn_8007A444(&cursor);
        for (i = 0; i < 7; i++) {
            unsigned char id;

            if (found) {
                id = fn_8007AF34(&cursor);
                found = fn_8007A510(&cursor);
            } else {
                id = 0xFF;
            }
            lbl_803EBA08->mpUnknown08[i] = id;
        }
        fn_8007AF14(&cursor);
    }
    if (!fn_8017F60C()) {
        for (i = 0; i < 4; i++) {
            unsigned char j = i + fn_802372EC(0, 4 - i);
            unsigned char id = lbl_803EBA08->mpUnknown08[i];

            lbl_803EBA08->mpUnknown08[i] = lbl_803EBA08->mpUnknown08[j];
            lbl_803EBA08->mpUnknown08[j] = id;
        }
    }
    ResetTable_803EBA08(2);
}

void fn_80019724(void)
{
    if (fn_801486A0() == 15) {
        if (lbl_803EBA24) {
            fn_800190A0();
        } else {
            fn_80018F9C(7);
        }
        return;
    }
    switch (fn_801486A0()) {
    case 0:
        fn_800191E4();
        break;
    case 1:
        fn_80019588();
        break;
    case 3:
        fn_80018F9C(fn_80148A58()->vfn_05(fn_80178308()));
        break;
    case 2:
        fn_80019380();
        break;
    case 4:
        fn_80018F9C(fn_80148A58()->vfn_05(0));
        break;
    default:
        fn_80018F9C(7);
        break;
    }
}

void fn_80019828(void)
{
    fn_80018EF0();
}

int fn_80019848(int *pController, int *pCount)
{
    lbl_803EBA43 = 0;
    lbl_803EBA2C = -1;
    lbl_803EBA20 = (Object_803EBA20 *)fn_8005FC7C();
    lbl_803EBA24 = fn_80061AD4();
    fn_80019724();
    if (lbl_803EBA08->mpUnknown08[lbl_803EBA08->mUnknown15] != 0xFF) {
        *pController = fn_80188030(lbl_803EBA08->mpUnknown08[lbl_803EBA08->mUnknown15]);
    } else {
        *pController = -1;
    }

    switch (fn_801486A0()) {
    case 0:
        *pCount = 6;
        break;
    case 1:
        *pCount = 7;
        break;
    case 2:
        *pCount = lbl_803EBA08->mCount / 2;
        break;
    default:
        *pCount = lbl_803EBA08->mSize;
        break;
    }

    if (fn_801485D4()) {
        fn_80148AF8(fn_80148A58());
    }
    fn_8008044C(&lbl_8036B168, 0, 0x54415453);
    fn_80083E40(&lbl_8036B194, 0, 0x54415453);

    if (fn_801801B4() == 1) {
        lbl_803ECE58[0] = fn_8001729C();
        lbl_803ECE58[1] = fn_8001729C();
        fn_80018990();
        fn_800170E0();
        if (lbl_803EBA20) {
            fn_8001AA8C(fn_8001AC48(0, 0), 0);
            lbl_803EBA08->mUnknown15 = 0;
            lbl_803EBA08->mUnknown19 = fn_8007CB6C(2) ? 0 : 1;
        }
        if (lbl_803EBA24 || lbl_803EBA20) {
            for (int i = 0; i < lbl_803EBA10; i++) {
                if (lbl_803EBA0C[i].mSlot >= 0) {
                    int excluded = 0xFF;
                    lbl_803EBA0C[i].mUnknown10 =
                        fn_8003EA28(lbl_803EBA18, &excluded, lbl_803EBA0C[i].mId);
                }
            }
        }
    } else if (fn_801801B4() == 0) {
        for (int i = 0; i < lbl_803EBA08->mCount; i++) {
            lbl_803EBA08->mpCounts[i] = *pCount;
        }
        for (int i = 0; i < lbl_803EBA10; i++) {
            Entry_803EBA0C *pEntry = &lbl_803EBA0C[i];
            if (pEntry->mSlot >= 0) {
                lbl_803EBA08->mppLists[pEntry->mUnknown15][pEntry->mSlot] = pEntry->mId;
            }
        }
    }

    fn_8003B6F0(fn_801801B4() == 1);
    return 0;
}

void fn_80019AD4(void)
{
    int digp[8][7];

    lbl_803EBA43 = 1;
    if (fn_801801B4() == 1) {
        unsigned int i;

        if (lbl_803EBA24) {
            for (i = 0; i < lbl_803EBA10; i++) {
                if (lbl_803EBA0C[i].mSlot >= 0) {
                    digp[lbl_803EBA0C[i].mTeam][lbl_803EBA0C[i].mSlot] = lbl_803EBA0C[i].mId;
                }
            }
            fn_8022DC7C(0);
            fn_8022DCB0(0);
            fn_8022DCE4(0);
            fn_8022DD18(0);
            for (int team = 0; team < 8; team++) {
                fn_80061B90(lbl_8036B1F0[team], digp[team]);
            }
        } else {
            Record_8003B6BC records[8];

            for (i = 0; i < lbl_803EBA10; i++) {
                if (lbl_803EBA0C[i].mSlot >= 0) {
                    digp[lbl_803EBA0C[i].mTeam][lbl_803EBA0C[i].mSlot] = lbl_803EBA0C[i].mId;
                }
            }
            fn_8003DE74(0, digp[0]);
            fn_8003DE74(1, digp[1]);
            fn_8003B6BC(0, &records[0]);
            fn_8003B6BC(1, &records[1]);
            if (lbl_803EBA1C) {
                fn_80018CA4(&lbl_8036B1D0[0], records[0].mUnknown, "Team Two");
                fn_80018CA4(&lbl_8036B1D0[1], records[1].mUnknown, "Team One");
                lbl_803EBA1C = 0;
            }
            fn_8007CAEC(0, lbl_8036B1D0[0]);
            fn_8007CAEC(1, lbl_8036B1D0[1]);
            fn_8022A508(0, lbl_8036B1D0[0], lbl_8036B1D0[0], 6, -1);
            fn_8022A508(1, lbl_8036B1D0[1], lbl_8036B1D0[1], 6, -1);
            fn_8022DC7C(0);
            fn_8022DCB0(0);
            fn_8022DCE4(0);
            fn_8022DD18(0);
            for (unsigned char team = 0; team <= 1; team++) {
                for (unsigned char j = 0; j <= 6; j++) {
                    fn_800809C4(&lbl_8036B168, records[team].mUnknown[j], 0);
                    fn_80081F50(&lbl_8036B168, team, 1);
                }
            }
            if (lbl_803EBA08->mSize == 1) {
                for (unsigned char k = 0; k < lbl_803EBA08->mCount; k++) {
                    if (lbl_803EBA08->mpUnknown08[k] != 0xFF) {
                        fn_8007B14C(lbl_803EBA08->mpUnknown08[k], *lbl_803EBA08->mppLists[k]);
                    }
                }
            }
        }
        fn_80027E18(1);
    } else if (fn_801801B4() == 0) {
        fn_8018C48C(0x54415453);
        fn_8018C48C(0x454D4147);
    }

    fn_800188CC();
    fn_8008056C(&lbl_8036B168);
    fn_80083F68(&lbl_8036B194);
    fn_8003B8BC();
    if (fn_801801B4() == 0) {
        fn_8001B228();
    }
    if (fn_801801B4() == 1) {
        if (lbl_803EBA24 == 0 && lbl_803EBA20) {
            fn_8005FCF8(digp[0], digp[1]);
            fn_80015D28(lbl_803EBA20->mUnknown48);
        }
    } else {
        fn_8018807C(0);
    }
    fn_8003EBC4(0);
    fn_8003EBE4(0);
    fn_80019828();
    lbl_803EBA20 = 0;
}

void fn_80019E74(int group, int kind, int slot, int code, int a, int b)
{
    fn_8003B0F8(group, kind, slot, code, a, b);
}

void fn_80019E94(int group)
{
    fn_8003B1F4(group);
}

int fn_80019EB4(int team)
{
    if (lbl_803EBA24 == 0) {
        if (team == lbl_803EBA08->mUnknown15) {
            if (lbl_803EBA08->mUnknown19 != 1) {
                return -12;
            }
            return -11;
        }
        if (lbl_803EBA08->mUnknown19 != 1) {
            return -11;
        }
        return -12;
    }

    switch (team) {
    case 0:
        return -11;
    case 1:
        return -12;
    case 2:
        return -13;
    case 3:
        return -14;
    case 4:
        return -15;
    case 5:
        return -16;
    case 6:
        return -17;
    case 7:
        return -18;
    case 8:
    default:
        return -1;
    }
}

int fn_80019F88(int group, int row)
{
    int skipped = 0;
    int i = 0;
    int count = fn_80017208(lbl_803EBA08->mUnknown17);

    for (; i < count; i++) {
        int index = fn_80017248(group, i);
        if (index < lbl_803EBA10) {
            if (lbl_803EBA0C[index].mSlot >= 0) {
                skipped++;
            } else if (i - skipped == row) {
                break;
            }
        }
    }
    return i;
}

int fn_8001A024(int group, int count)
{
    int n = 0;

    for (int i = 0; i < count; i++) {
        int index = fn_80017248(group, i);
        if (index < lbl_803EBA10 && lbl_803EBA0C[index].mSlot < 0) {
            n++;
        }
    }
    return n;
}

void fn_8001A0A4(int row, int *pId, int *pPosition, int *pValues, char *pHeight, int heightSize,
                 char *pWeight, int weightSize)
{
    int values[10];

    int line = fn_80019F88(lbl_803EBA08->mUnknown17, row);
    int index = fn_80017248(lbl_803EBA08->mUnknown17, line);
    *pId = lbl_803EBA0C[index].mId;
    if (fn_800809C4(&lbl_8036B168, *pId, 0)) {
        if (fn_80080CB0(&lbl_8036B168) == 2) {
            *pPosition = -19;
        } else {
            *pPosition = fn_80080948(&lbl_8036B168);
        }
        fn_80081788(&lbl_8036B168, values);
        pValues[0] = values[6];
        pValues[1] = values[4];
        pValues[2] = values[7];
        pValues[3] = values[0];
        pValues[4] = values[3];
        pValues[5] = values[2];
        pValues[6] = values[1];
        pValues[7] = values[5];
        pValues[8] = values[8];
        pValues[9] = values[9];

        unsigned int height = fn_800811E0(&lbl_8036B168);
        int weight = fn_80081188(&lbl_8036B168);
        fn_801C2D88(pHeight, heightSize, "%d ft %d in", height / 12, height % 12);
        fn_801C2D88(pWeight, weightSize, "%d lbs", weight);
    }
}

void fn_8001A220(int message, Arg_8018399C text, int *pCount)
{
    Params_80005284 *pParams = text.pParams;

    switch (message) {
    case -1:
        break;
    case 1:
        if (lbl_803EBA08->mUnknown17 < 6) {
            lbl_803EBA08->mUnknown17++;
        } else {
            lbl_803EBA08->mUnknown17 = 0;
        }
        lbl_803EBA08->mUnknown18 = 0;
        break;
    case 3:
        if (lbl_803EBA08->mUnknown17 != 0) {
            lbl_803EBA08->mUnknown17--;
        } else {
            lbl_803EBA08->mUnknown17 = 6;
        }
        lbl_803EBA08->mUnknown18 = 0;
        break;
    }

    fn_8017F670(lbl_802F4488[lbl_803EBA08->mUnknown17][0], pParams->mpText);
    int count = fn_80017208(lbl_803EBA08->mUnknown17);
    *pCount = count;
    for (int i = lbl_8036B1C0[lbl_803EBA08->mUnknown17];
         i < lbl_8036B1C0[lbl_803EBA08->mUnknown17] + count; i++) {
        if (lbl_803EBA0C[i].mSlot >= 0) {
            (*pCount)--;
        }
    }
}

void fn_8001A34C(int slot, int *pId, int *pController)
{
    if (fn_801486A0() == 0 || fn_801486A0() == 1) {
        if (slot < lbl_803EBA08->mUnknown15) {
            *pId = *lbl_803EBA08->mppLists[slot];
            if (lbl_803EBA08->mpUnknown08[slot] == 0xFF) {
                *pController = -1;
            } else {
                *pController = fn_80188030(lbl_803EBA08->mpUnknown08[slot]);
            }
            return;
        }
    } else if (fn_801486A0() == 2) {
        int team = lbl_803EBA08->mUnknown19;
        if (slot < lbl_803EBA08->mUnknown0C[team]) {
            unsigned int i;
            for (i = 0; i < lbl_803EBA10; i++) {
                if (lbl_803EBA0C[i].mTeam == team && lbl_803EBA0C[i].mSlot == slot) {
                    *pId = lbl_803EBA0C[i].mId;
                    break;
                }
            }
            for (unsigned char j = 0; j < lbl_803EBA08->mCount; j++) {
                if (*lbl_803EBA08->mppLists[j] == *pId) {
                    if (lbl_803EBA08->mpUnknown08[j] == 0xFF) {
                        *pController = -1;
                    } else {
                        *pController = fn_80188030(lbl_803EBA08->mpUnknown08[j]);
                    }
                    return;
                }
            }
            return;
        }
    } else {
        int team = lbl_803EBA08->mUnknown15;
        if (slot < lbl_803EBA08->mpCounts[team]) {
            *pId = lbl_803EBA08->mppLists[team][slot];
            if (lbl_803EBA08->mpUnknown08[team] == 0xFF) {
                *pController = -1;
            } else {
                *pController = fn_80188030(lbl_803EBA08->mpUnknown08[team]);
            }
            return;
        }
    }
    *pId = -1;
    *pController = -1;
}

void fn_8001A508(int slot, int *pId, Arg_8018399C name, Arg_8018399C position)
{
    unsigned char team = lbl_803EBA08->mUnknown1A;
    Params_80005284 *pName = name.pParams;
    Params_80005284 *pPosition = position.pParams;

    if (fn_801486A0() == 2) {
        if (slot < lbl_803EBA08->mUnknown0C[team]) {
            for (unsigned int i = 0; i < lbl_803EBA10; i++) {
                if (lbl_803EBA0C[i].mTeam == team && lbl_803EBA0C[i].mSlot == slot) {
                    *pId = lbl_803EBA0C[i].mId;
                    break;
                }
            }
        } else {
            *pId = -1;
        }
    } else {
        if (slot < lbl_803EBA08->mpCounts[team]) {
            *pId = lbl_803EBA08->mppLists[team][slot];
        } else {
            *pId = -1;
        }
    }

    if (*pId != -1 && fn_800809C4(&lbl_8036B168, *pId, 0)) {
        fn_80080A68(&lbl_8036B168, pName->mpText, pName->mLength);
        fn_8017F670(fn_80080ECC(&lbl_8036B168), pPosition->mpText);
    }
}

void fn_8001A620(int dir, int *pResult, char *pText, int length)
{
    switch (dir) {
    case -1:
        if (fn_801486A0() == 2) {
            lbl_803EBA08->mUnknown1A = lbl_803EBA08->mUnknown19;
        } else {
            lbl_803EBA08->mUnknown1A = lbl_803EBA08->mUnknown15;
        }
        break;
    case 1:
        if (lbl_803EBA08->mUnknown1A == lbl_803EBA08->mCount - 1 ||
            (fn_801486A0() == 2 && lbl_803EBA08->mUnknown1A == 1)) {
            lbl_803EBA08->mUnknown1A = 0;
        } else {
            lbl_803EBA08->mUnknown1A++;
        }
        break;
    case 3:
        if (lbl_803EBA08->mUnknown1A == 0) {
            if (fn_801486A0() == 2) {
                lbl_803EBA08->mUnknown1A = 1;
            } else {
                lbl_803EBA08->mUnknown1A = lbl_803EBA08->mCount - 1;
            }
        } else {
            lbl_803EBA08->mUnknown1A--;
        }
        break;
    }

    int id = *pResult = fn_80019EB4(lbl_803EBA08->mUnknown1A);
    if (id < 0) {
        if (lbl_803EBA24) {
            int team = -19;
            switch (id) {
            case -11:
                team = lbl_8036B1F0[0];
                break;
            case -12:
                team = lbl_8036B1F0[1];
                break;
            case -13:
                team = lbl_8036B1F0[2];
                break;
            case -14:
                team = lbl_8036B1F0[3];
                break;
            case -15:
                team = lbl_8036B1F0[4];
                break;
            case -16:
                team = lbl_8036B1F0[5];
                break;
            case -17:
                team = lbl_8036B1F0[6];
                break;
            case -18:
                team = lbl_8036B1F0[7];
                break;
            case -19:
                break;
            }
            if (team != -19 && fn_80084034(&lbl_8036B194, team, 0)) {
                fn_80083F88(&lbl_8036B194, pText, length);
            }
        } else {
            const char *pName = 0;
            switch (id) {
            case -11:
                pName = "Team One";
                break;
            case -12:
                pName = "Team Two";
                break;
            case -19:
                pName = "No Team";
                break;
            }
            if (pName) {
                fn_801C2EF0(pText, pName, length);
            }
        }
    } else {
        if (fn_80084034(&lbl_8036B194, id, 0)) {
            fn_80083F88(&lbl_8036B194, pText, length);
        }
    }
}

void fn_8001A8C8(int index, Arg_8018399C text)
{
    Params_80005284 *pParams = text.pParams;
    int pick = fn_80019F88(lbl_803EBA08->mUnknown17, index);
    int row = fn_80017248(lbl_803EBA08->mUnknown17, pick);

    if (fn_800809C4(&lbl_8036B168, lbl_803EBA0C[row].mId, 0)) {
        fn_800189C0(pParams->mpText, pParams->mLength, 1);
    }
}

int fn_8001A948(int *pPad)
{
    unsigned char pad = lbl_803EBA08->mpUnknown08[lbl_803EBA08->mUnknown15];

    if (pad != 0xFF) {
        *pPad = fn_80188030(pad);
    } else {
        *pPad = -1;
    }
    return fn_80018A88() == 0;
}

void fn_8001A9A8(int team, int slot, int *pId)
{
    *pId = -1;
    for (unsigned int i = 0; i < lbl_803EBA10; i++) {
        if (lbl_803EBA0C[i].mTeam == team && lbl_803EBA0C[i].mSlot == slot) {
            *pId = lbl_803EBA0C[i].mId;
            break;
        }
    }
}

void fn_8001AA2C(int group, int kind, Pair_8003AEA8 **pPairs)
{
    fn_8003B234(group, kind, pPairs);
}

void fn_8001AA4C(int group, int kind, int slot)
{
    fn_8003B2D0(group, kind, slot);
}

void fn_8001AA6C(int group)
{
    fn_8003B360(group);
}

void fn_8001AA8C(int id, int *pSlot)
{
    Entry_803EBA0C *pEntry = fn_800172C4(id, 0);

    pEntry->mSlot = lbl_803EBA08->mUnknown0C[lbl_803EBA08->mUnknown19];
    pEntry->mTeam = lbl_803EBA08->mUnknown19;
    pEntry->mUnknown15 = lbl_803EBA08->mUnknown15;

    if (pSlot) {
        switch (fn_801486A0()) {
        case 0:
        case 1:
            *pSlot = lbl_803EBA08->mUnknown0C[0] + lbl_803EBA08->mUnknown0C[1];
            break;
        default:
            *pSlot = pEntry->mSlot;
            break;
        }
    }

    lbl_803EBA08->mppLists[lbl_803EBA08->mUnknown15][lbl_803EBA08->mpCounts[lbl_803EBA08->mUnknown15]] = id;
    lbl_803EBA08->mpCounts[lbl_803EBA08->mUnknown15]++;
    lbl_803EBA08->mUnknown0C[lbl_803EBA08->mUnknown19]++;

    if (fn_80018A88()) {
        fn_80017330(0);
        fn_80017330(1);
        if (lbl_803EBA20) {
            int value = lbl_803EBA28;
            fn_80060330(1, &value, 1, &lbl_8036B168);
        }
    } else {
        if (lbl_803EBA08->mUnknown15 == lbl_803EBA08->mCount - 1) {
            lbl_803EBA08->mUnknown15 = 0;
        } else {
            lbl_803EBA08->mUnknown15++;
        }

        if (lbl_803EBA24) {
            lbl_803EBA08->mUnknown19++;
            if (lbl_803EBA08->mCount <= lbl_803EBA08->mUnknown19) {
                lbl_803EBA08->mUnknown19 = 0;
            }
        } else if (lbl_803EBA08->mCount > 1) {
            lbl_803EBA08->mUnknown19 = !lbl_803EBA08->mUnknown19;
        }
    }
}

int fn_8001AC48(int *pDays, int *pResult)
{
    int count = 0;
    int allowedCount = 0;
    int *pList = (int *)fn_801D2B7C((lbl_803EBA10 + 1) * 4, 0, 0);
    int allowed[16];
    int id;
    int category;
    int index;
    Entry_803EBA0C *pEntry;

    for (index = 0; index < lbl_803EBA10; index++) {
        pEntry = &lbl_803EBA0C[index];
        if (pEntry->mSlot >= 0) {
            if (pEntry->mTeam == lbl_803EBA08->mUnknown19) {
                allowed[allowedCount++] = pEntry->mUnknown10;
            }
        } else {
            pList[count++] = pEntry->mId;
        }
    }
    allowed[allowedCount] = 0xFF;
    pList[count] = 0x7FFF;

    fn_8003EB2C(lbl_803EBA18, pList, allowed, &id, &category);
    fn_801D2BD0(pList);

    unsigned char day = lbl_803EBA08->mUnknown17;
    pEntry = fn_800172C4(id, &index);
    unsigned char pickDay = fn_80017278(index);
    unsigned char b = fn_80017260(pickDay, index);

    if (pDays) {
        if (day <= pickDay) {
            *pDays = pickDay - day;
        } else {
            *pDays = 7 - (day - pickDay);
        }
    }
    if (pResult) {
        *pResult = fn_8001A024(pickDay, b);
    }
    pEntry->mUnknown10 = category;
    return id;
}

void fn_8001ADD4(int dir, int *pResult, Arg_8018399C prevText, Arg_8018399C dayText, Arg_8018399C nextText)
{
    Params_80005284 *pPrev = prevText.pParams;
    Params_80005284 *pDay = dayText.pParams;
    Params_80005284 *pNext = nextText.pParams;
    unsigned short prev;
    unsigned short next;

    switch (dir) {
    case 4:
        lbl_803EBA08->mUnknown17 = 0;
        break;
    case 0:
        if (lbl_803EBA08->mUnknown17 == 0) {
            lbl_803EBA08->mUnknown17 = 6;
        } else {
            lbl_803EBA08->mUnknown17--;
        }
        break;
    case 2:
        if (lbl_803EBA08->mUnknown17 == 6) {
            lbl_803EBA08->mUnknown17 = 0;
        } else {
            lbl_803EBA08->mUnknown17++;
        }
        break;
    }

    if (lbl_803EBA08->mUnknown17 == 0) {
        prev = 6;
        next = 1;
    } else if (lbl_803EBA08->mUnknown17 == 6) {
        prev = 5;
        next = 0;
    } else {
        prev = lbl_803EBA08->mUnknown17 - 1;
        next = lbl_803EBA08->mUnknown17 + 1;
    }

    *pResult = fn_80017208(lbl_803EBA08->mUnknown17);
    fn_8017F670(lbl_802F4488[prev][0], pPrev->mpText);
    fn_8017F670(lbl_802F4488[lbl_803EBA08->mUnknown17][0], pDay->mpText);
    fn_8017F670(lbl_802F4488[next][0], pNext->mpText);
}

void fn_8001AF08(int index, int group, int *pValid, int *pId, Arg_8018399C name, Arg_8018399C text)
{
    if (index < lbl_803EBA08->mpCounts[group]) {
        *pValid = 1;
        for (unsigned short i = 0; i < lbl_803EBA10; i++) {
            if (lbl_803EBA0C[i].mTeam == group && lbl_803EBA0C[i].mSlot == index) {
                fn_800809C4(&lbl_8036B168, lbl_803EBA0C[i].mId, 0);
                *pId = fn_80080D10(&lbl_8036B168);
                fn_80080A68(&lbl_8036B168, name.pParams->mpText, name.pParams->mLength);
                fn_8017F670(fn_80080ECC(&lbl_8036B168), text.pParams->mpText);
                break;
            }
        }
    } else {
        *pValid = 0;
        *pId = -1;
        fn_801C3284(name.pParams->mpText, "", name.pParams->mLength + 1);
        fn_801C3284(text.pParams->mpText, "", text.pParams->mLength + 1);
    }
}

void fn_8001B020(int id, int *pA, int *pB)
{
    *pA = -1;
    *pB = -1;
    if (lbl_803EBA24 != 0 && (unsigned int)(id + 18) <= 7) {
        id = -11 - id;
        id = lbl_8036B1F0[id];
    } else if (id == -11) {
        *pA = 0x85;
    } else if (id == -12) {
        *pA = 0x86;
    } else if (id == -19) {
        *pA = 0x84;
    }
    if (*pA == -1) {
        int found = fn_80084034(&lbl_8036B194, id, 0);
        if (fn_80084438(&lbl_8036B194) == 0) {
            unsigned char color[3];
            color[0] = fn_800841AC(&lbl_8036B194);
            color[1] = fn_800841D8(&lbl_8036B194);
            color[2] = fn_80084204(&lbl_8036B194);
            fn_80188CBC(0, 4, fn_80084158(&lbl_8036B194), 0xAC, color);
            *pB = fn_80188DF0(0);
        }
        if (found) {
            *pA = fn_80084158(&lbl_8036B194);
        } else {
            *pA = 0x84;
        }
    }
}

void fn_8001B15C(int index, char *pDest, int size)
{
    *pDest = 0;
    if (fn_8017F584() != 7) {
        fn_801C2EF0(pDest, "Opponent", size);
    } else if (index < lbl_803EBA08->mCount && index > -1) {
        int id = *lbl_803EBA08->mppLists[index];
        int result = 0;
        if (fn_800809C4(&lbl_8036B168, id, &result)) {
            fn_80080B08(&lbl_8036B168, pDest, size);
        } else {
            fn_801C2EF0(pDest, "Opponent", size);
        }
    }
}

void fn_8001B228(void)
{
    if (lbl_803EBA0C) {
        fn_801D2BD0(lbl_803EBA0C);
        lbl_803EBA0C = 0;
    }
    fn_800171D0();
}

void fn_8001B260(int mode, int b)
{
    lbl_803EBA30 = 1;
    lbl_803EBA14 = 0;
    lbl_803EBA34 = mode;
    switch (mode) {
    case 0:
        lbl_803EBA10 = 40;
        break;
    case 2:
        lbl_803EBA10 = fn_80082414(0) * lbl_803EBA38[0] + fn_80082414(1) * lbl_803EBA38[1] +
                       fn_80082414(2) * lbl_803EBA38[2] + fn_80082414(3) * lbl_803EBA38[3];
        if (lbl_803EBA10 >= 14) {
            break;
        }
    case 1:
    default:
        lbl_803EBA10 = 14;
        break;
    }
}

void fn_8001B330(int mask)
{
    lbl_803EBA38[0] = mask & 1;
    lbl_803EBA38[1] = (mask >> 1) & 1;
    lbl_803EBA38[2] = (mask >> 2) & 1;
    lbl_803EBA38[3] = (mask >> 3) & 1;
}

int fn_8001B354(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80019848(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x80000002:
        fn_80019AD4();
        break;
    case 0x80000003:
        fn_80019E74(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, (int)pArgs[4].pParams->mpText,
                    pArgs[4].pParams->mLength);
        break;
    case 0x80000005:
        fn_80019E94(pArgs[0].i);
        break;
    case 0x80000006:
        fn_8001A0A4(pArgs[0].i, pArgs[1].pi, pArgs[2].pi, (int *)(pArgs[3].i + (*pArgs[3].pi + 1) * 4),
                    pArgs[4].pParams->mpText, pArgs[4].pParams->mLength, pArgs[5].pParams->mpText,
                    pArgs[5].pParams->mLength);
        break;
    case 0x80000011:
        fn_8001A220(pArgs[0].i, pArgs[1], pArgs[2].pi);
        break;
    case 0x80000012:
        *pResult = fn_80019EB4(lbl_803EBA08->mUnknown15);
        break;
    case 0x80000013:
        fn_8001A34C(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000018:
        fn_8001A8C8(pArgs[0].i, pArgs[1]);
        break;
    case 0x80000014:
        fn_8001A620(pArgs[0].i, pArgs[1].pi, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        break;
    case 0x80000015:
        fn_8001A508(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3]);
        break;
    case 0x80000016:
        *pResult = fn_8001A948(pArgs[0].pi);
        break;
    case 0x80000017:
        fn_8001A9A8(pArgs[0].i, pArgs[1].i, pArgs[2].pi);
        break;
    case 0x80000007:
        fn_8001AA2C(pArgs[0].i, pArgs[1].i, (Pair_8003AEA8 **)(pArgs[2].i + (*pArgs[2].pi + 1) * 4));
        break;
    case 0x80000008:
        fn_8001AA4C(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0x80000009:
        fn_8001AA6C(pArgs[0].i);
        break;
    case 0x8000000A:
        fn_8001AA8C(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x8000000B:
        fn_8001AC48(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x8000000E:
        fn_8001ADD4(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3], pArgs[4]);
        break;
    case 0x8000000F:
        fn_8001AF08(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pi, pArgs[4], pArgs[5]);
        break;
    case 0xA:
        if (*pArgs[0].pi != -1) {
            *pArgs[0].pi = fn_80188030(*pArgs[0].pi);
        }
        break;
    case 8:
        fn_8001B020(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000019:
        fn_8001B15C(lbl_803EBA08->mUnknown19, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x147:
        *pResult = fn_800551D8(pArgs[0].i);
        break;
    case 0x149:
        fn_800551E0(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        *pArgs[3].pi = fn_80178D70(pArgs[0].i ? fn_80178308() : fn_80178320());
        break;
    case 0x14A: {
        int *pList = (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4);
        fn_80055230(pArgs[0].i, pArgs[4].i, pArgs[3].i, pList, pList + 1, pArgs[2].pParams->mpText,
                    pArgs[2].pParams->mLength);
        break;
    }
    case 0xE:
    case 0x8000000D:
    case 0x80000010:
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_8001B828(void)
{
    lbl_803EBA1C = 1;
}

}
