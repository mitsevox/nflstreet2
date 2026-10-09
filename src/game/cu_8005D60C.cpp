#include <string.h>

#include "game/Object_8007A334.h"
#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8008044C.h"
#include "game/cu_8003AEA8.h"
#include "game/cu_8003E214.h"
#include "game/cu_8018EC68.h"
#include "game/FELoop.h"
#include "game/fn_80061AD4.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include "game/fn_801FCE10.h"

/* Index returned by fn_8022F384 and values read for it by fn_8005D6EC. */
struct State_802D4D40 {
    signed char mIndex;
    signed char mUnknown1;
    short mUnknown2;
    unsigned int mPpxe;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    unsigned short mUnknown1C;
    int mUnknown20;
};

/* Values returned by fn_8007F828 and restored through fn_8007F6F8. */
struct Saved_802D4D64 {
    int mValue0;
    int mValue1;
    int mValue14;
    unsigned char mSaved;
};

/* Street event settings; fn_8005E4A8 sets the timer words. */
struct Settings_8031BDD4 {
    char mUnknown0[32];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

/* Destination of the text copied by fn_8005F8B4. */
struct Text_8005F8B4 {
    char mUnknown0[4];
    int mSize;
    char *mpText;
};

struct Args_8005F8B4 {
    Text_8005F8B4 *mpText;
};

/* Teams set up by fn_8005E360. */
struct Match_8030A1A0 {
    int mAway;
    int mHome;
    int mUnknown8;
};

/* Per-event completion flags filled by fn_8005D86C. */
struct Progress_8030A2AC {
    unsigned char mDone[12];
    unsigned char mComplete;
};

extern "C" {
int fn_8000FCCC(void);
int fn_8000FCDC(void);
void fn_80011600(int a, int b, int c);
void fn_80015D28(int a);
void fn_8001B260(int a, int b);
void fn_8001B330(int a);
void fn_8001B828(void);
void fn_80010150(int a);
void fn_800731D0(int a);
Object_80039F5C *fn_8003AD2C(int id);
int fn_8003B4A4(int group, int *list, int value, int a, int b);
unsigned char fn_8007B090(int a);
void fn_8007B684(int id);
void fn_8007B6D4(void);
void fn_8007B8A4(char *pDest, int count);
void fn_8007B14C(int pad, int id);
void fn_80073210(int frames);
void fn_8007CAEC(int index, int value);
int fn_8007CB6C(int index);
int fn_80080CB0(Object_8008044C *pObject);
int fn_80080ECC(Object_8008044C *pObject);
unsigned int fn_800812B0(Object_8008044C *pObject, int index);
void fn_8008135C(Object_8008044C *pObject, int index, int value);
void fn_80083DE4(int id);
int fn_8008454C(int type, int logo, const char *pName);
void fn_80084808(int a, int *pIds, int *pCounts, int count, int *pOut, int total);
void fn_80084908(int a, int b, int *pOut, unsigned int count, int *pIn, unsigned int size);
void fn_80084A8C(int a, int *pList, int b, int c);
void fn_80084C24(int team, int *pList, int side, int count);
void fn_80084FA8(int value);
void fn_80084FE4(int value);
unsigned int fn_80086080(int ppxe);
int fn_800860B4(int vlxe);
int fn_800860E8(int vlxe);
int fn_8008611C(int vlxe, char *pName, int size);
int fn_80086154(void);
int fn_80086174(void);
void fn_80087BE4(Object_8007A334 *pObject, int index);
void fn_80087C3C(Object_8007A334 *pObject);
void fn_80087C5C(Object_8007A334 *pObject, int index, int value);
int fn_80087C8C(Object_8007A334 *pObject, unsigned int index);
void fn_8008880C(int db, int id);
void fn_801485B4(void);
int fn_801485D4(void);
void fn_801485EC(int value);
int fn_801486A0(void);
void fn_80148AF8(Class_80148A58 *pObject);
void fn_8014F3DC(int ticks);
void fn_80183368(int mode, int value);
void fn_80186F30(signed char a, int b);
void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor);
int fn_80188DF0(int a);
void fn_8018B9D4(Object_8007A334 *pCursor, int index);
void fn_8018BA2C(Object_8007A334 *pCursor);
int fn_8018BDFC(int index, int a, int *pIds, int *pCount);
int fn_8018C1E0(Object_8007A334 *pCursor);
void fn_8018C48C(int tag);
void fn_8018E474(int index);
void fn_8018E55C(int index);
void fn_8018E11C(Object_8007A334 *pCursor, int index);
void fn_8018E174(Object_8007A334 *pCursor);
int fn_8018E194(Object_8007A334 *pCursor, int row, char *pBuffer, int size);
int fn_8018E20C(Object_8007A334 *pCursor, int row, char *pBuffer, int size);
int fn_8018E284(Object_8007A334 *pCursor, int row, char *pName, int size);
int fn_8018E344(int index);
void fn_8018E390(int index, int value);
void fn_8018E7A0(int index, int value);
int fn_8018E3DC(int index);
void fn_8018E428(int index, int value);
int fn_8018E5F4(int index, int id);
void fn_8018E658(int index, int id);
int fn_8018E6A4(int index);
int fn_8018E6E0(int index, int a);
int fn_8018E7CC(int index);
int fn_8018E774(int index);
void fn_8018E828(int index, int value);
int fn_8018F1F0(unsigned int index, char *pEtnr, int size);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
unsigned int fn_801C3180(const char *pText);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_801D34D0(void *pDest, int size, int value, int width);
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_801F9D70(int handle, int table, Object_80023BBC *pFilter, unsigned short *pCount);
int fn_8022F358(int index);
int fn_8022F3D4(int a);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_8005BE54(unsigned char value);
void fn_80061ADC(void);
void fn_80061AE8(void);
int fn_801801B4(void);
int fn_80178AE0(void);
}

Object_8008044C lbl_8030A0E4;
Object_8007A334 lbl_8030A110;
VetsRow_8018EC68 lbl_8030A13C;
extern Settings_8031BDD4 lbl_8031BDD4;

Match_8030A1A0 lbl_8030A1A0;
int lbl_8030A1AC[2][7];
char lbl_8030A1E4[200];
Progress_8030A2AC lbl_8030A2AC;

unsigned char lbl_803EA5B8 = 0;
int lbl_803EA5BC = 2;
int lbl_803EA5C0 = 4;
int lbl_803EA5C4 = 0;
VetsRow_8018EC68 *lbl_803EA5C8 = 0;
Object_8008044C *lbl_803EA5CC = 0;
Object_8007A334 *lbl_803EA5D0 = 0;
float lbl_803EA5D4 = 0.0f;
int lbl_803EA5D8 = -1;
int lbl_803EA5DC = -1;
int lbl_803EA5E0 = -1;
int lbl_803EA5E4 = 0;

static unsigned char lbl_803EC7F0;
static unsigned char lbl_803EC7F1;

State_802D4D40 lbl_802D4D40 = {-1, -1, 0, 0, 0x7FFF};
Saved_802D4D64 lbl_802D4D64 = {-1, 0, 0, 0};
int lbl_802D4D74[16] = {12, 12, 12, 12, 5, 7, 9, 8, 6, 4, 1, 2, 0, 3, 11, 10};
int lbl_802D4DB4[12] = {12, 10, 11, 13, 9, 4, 8, 5, 7, 6, 15, 14};
int lbl_802D4DE4[7] = {0, 1, 2, 4, 8, 9, 13};
int lbl_802D4E00[10] = {0, 4, 1, 3, 2, 5, 6, 7, 8, 9};

extern "C" {
void fn_80060044(int team, int id, int *pList);
int *fn_80060444(int index);
void fn_8006088C(int value);
int fn_8005F910(void);
float fn_8005F754(void);
void fn_8005F7C4(Object_8008044C *pObject, int id, float scale);
int fn_80060354(VetsRow_8018EC68 *pRow, int *pList);
void fn_80060410(int index, int *pList);

void fn_8005D60C(void)
{
    fn_80086154();
    fn_8008056C(lbl_803EA5CC);
    lbl_803EA5CC = 0;
    fn_8018EEAC();
    fn_80087C3C(lbl_803EA5D0);
    lbl_802D4D40.mIndex = -1;
    lbl_803EA5D0 = 0;
}

void fn_8005D660(void)
{
    lbl_802D4D40.mIndex = fn_8022F384(fn_8022F4BC());
    lbl_803EA5CC = &lbl_8030A0E4;
    fn_8008044C(&lbl_8030A0E4, 0, 0x54415453);
    fn_8018EEF0();
    fn_80086174();
    lbl_802D4D40.mUnknown2 = 0x7FFF;
    lbl_803EA5D0 = &lbl_8030A110;
    fn_800731D0(1);
    fn_80087BE4(lbl_803EA5D0, lbl_802D4D40.mIndex);
}

void fn_8005D6EC(void)
{
    lbl_802D4D40.mPpxe = fn_8018E344(lbl_802D4D40.mIndex);
    lbl_802D4D40.mUnknown1C = fn_80086080(lbl_802D4D40.mPpxe);
    lbl_802D4D40.mUnknown8 = fn_80087C8C(lbl_803EA5D0, 14);
    lbl_802D4D40.mUnknownC = fn_8018E3DC(lbl_802D4D40.mIndex);
    lbl_802D4D40.mUnknown1 = fn_8018E7CC(lbl_802D4D40.mIndex);
}

void fn_8005D764(int set)
{
    Object_8007A334 cursor;
    int value;

    fn_8018B9D4(&cursor, lbl_802D4D40.mIndex);
    value = fn_8018C1E0(&cursor);
    fn_8018BA2C(&cursor);
    if (set) {
        fn_80084FA8(value);
    } else {
        fn_80084FE4(value);
    }
}

int fn_8005D7F0(int index)
{
    return lbl_802D4D74[index];
}

int fn_8005D804(int index)
{
    return lbl_802D4DB4[index];
}

void fn_8005D818(void)
{
    fn_800731D0(1);
    fn_800731D0(0);
    fn_8018C48C(0x54415453);
    fn_800731D0(1);
    fn_8018C48C(0x454D4147);
    fn_800731D0(0);
}

int fn_8005D86C(void)
{
    VetsRow_8018EC68 row;
    int complete = 1;
    int i;

    for (i = 0; i <= 11; i++) {
        fn_800731D0(1);
        int done = fn_8018E6E0(lbl_802D4D40.mIndex, i);
        lbl_8030A2AC.mDone[i] = done;
        if (complete && !done) {
            int count = fn_8018EE44(i);
            for (int j = 0; j < count; j++) {
                if (fn_8018EDF0(i, j, &row) && !fn_8018E5F4(lbl_802D4D40.mIndex, row.mNets) &&
                    row.mItes != 4) {
                    complete = 0;
                    break;
                }
            }
        }
    }
    lbl_8030A2AC.mComplete = complete;
    return complete;
}

unsigned char fn_8005D94C(void)
{
    return lbl_8030A2AC.mComplete;
}

int fn_8005D958(void)
{
    return fn_8018E6A4(lbl_802D4D40.mIndex) == 2;
}

void fn_8005D990(int *pTotal)
{
    VetsRow_8018EC68 *pRow = lbl_803EA5C8;
    int ppxe = lbl_802D4D40.mPpxe + pRow->mPewr;
    unsigned short limit = lbl_802D4D40.mUnknown1C;
    lbl_802D4D40.mUnknown10 = pRow->mPewr;
    unsigned int level = fn_80086080(ppxe);
    fn_8018E390(lbl_802D4D40.mIndex, ppxe);
    if (level > limit) {
        *pTotal += fn_800860E8(level);
    }
}

void fn_8005DA10(void)
{
    if (lbl_802D4D64.mSaved) {
        fn_8007F6F8(14, lbl_802D4D64.mValue14);
        fn_8007F6F8(1, lbl_802D4D64.mValue1);
        if (lbl_802D4D64.mValue0 > -1) {
            fn_8007F6F8(0, lbl_802D4D64.mValue0);
        }
        lbl_802D4D64.mSaved = 0;
    }
}

void fn_8005DA7C(int value14, int value1)
{
    if (!lbl_802D4D64.mSaved) {
        lbl_802D4D64.mSaved = 1;
        lbl_802D4D64.mValue14 = fn_8007F828(14);
        lbl_802D4D64.mValue1 = fn_8007F828(1);
        if (lbl_802D4D40.mUnknown1 > -1) {
            lbl_802D4D64.mValue0 = fn_8007F828(0);
        } else {
            lbl_802D4D64.mValue0 = lbl_802D4D40.mUnknown1;
        }
    }
    fn_8007F6F8(14, value14);
    fn_8007F6F8(1, value1);
    if (lbl_802D4D40.mUnknown1 > -1) {
        fn_8007F6F8(0, lbl_802D4D40.mUnknown1);
    }
}

float fn_8005DB3C(void)
{
    return lbl_803EA5D4 = fn_800860B4(lbl_802D4D40.mUnknown1C) * 0.001f;
}

void fn_8005DB9C(int id, int *pList, int skip, unsigned int count, float scale)
{
    for (unsigned int i = 0; i < count; i++) {
        int value = pList[i];
        if (value != skip) {
            fn_8005F7C4(&lbl_8030A0E4, value, scale);
        }
    }
}

int fn_8005DC10(void)
{
    int ids[10];
    int list[14];
    QueryResult result;
    int digp = 0;
    unsigned int count;
    unsigned int i;

    fn_801D34D0(list, sizeof(list), 0x7FFF, 4);
    QueryCursor cursor = {0, 0, -1, 0};
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result,
                "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x82 from 'YALP' where 'DIGT' = \x85 "
                "order by 'DIGP' desc\n",
                &cursor, &digp, 0x21);
    count = result.mUnknown0;
    for (i = 0; i < count; i++) {
        fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        ids[i] = digp;
    }
    if (cursor.mUnknown0) {
        fn_801FCFA0(&cursor);
    }
    fn_80084908(0x21, 0, list, 7, ids, 10);
    fn_80060354(lbl_803EA5C8, list);
    list[7] = 0x7FFF;
    fn_80060410(0, list);
    fn_8003B3F8(0, list, 4);
    fn_80084C24(0x21, list, 0, 7);
    fn_80083DE4(0x21);
    return 0x21;
}

int fn_8005DD6C(int *pTeam, int *pCopy)
{
    int ids[21];
    int list[14];
    char name[33] = {0};
    int count = 0;
    int full = 0;
    int team;
    int etnr;

    if (lbl_803EA5C8->mItes == 1 && fn_801485D4()) {
        switch (fn_801486A0()) {
        case 1:
            full = 1;
        case 0:
        case 3:
            count = 3;
            break;
        case 4:
            count = 4;
            break;
        default:
            count = 7;
            break;
        }
    }
    etnr = -1;
    if (lbl_803EA5C8->mItes == 2) {
        etnr = fn_8018F1F0(lbl_803EA5C8->mNets, name, sizeof(name));
    }
    *pTeam = fn_8008454C(6, etnr, name);
    team = fn_8008454C(6, etnr, name);
    if (full) {
        int counts[7] = {0};
        counts[0] = 7;
        fn_80084808(*pTeam, lbl_802D4DE4, counts, 7, ids, 21);
    } else {
        int counts[7] = {1, 1, 1, 1, 1, 1, 1};
        fn_80084808(*pTeam, lbl_802D4DE4, counts, 7, ids, 21);
    }
    fn_80084908(0, 0, list, 7, ids, 21);
    fn_80060354(lbl_803EA5C8, list);
    fn_8005DB9C(team, list, lbl_802D4D40.mUnknown2, 7, fn_8005DB3C());
    list[7] = 0x7FFF;
    fn_80060410(0, list);
    fn_8003B3F8(0, list, 4);
    fn_80084A8C(team, list, 0, 7);
    fn_80083DE4(team);
    if (pCopy && count) {
        for (unsigned int i = 0; i < count; i++) {
            pCopy[i] = list[i];
        }
    }
    return team;
}

void fn_8005DFE8(int *pDest, int *pSource, int count)
{
    memcpy(pDest, pSource, count * 4);
}

void fn_8005E010(int group, int *pIds, int count, Object_8008044C *pObject, int a)
{
}

int fn_8005E014(int *pTeam, int *pCopy, int *pCount)
{
    int ids[8];
    int ids2[22];
    int list[14];
    int count;
    int first = 0;
    int second = 0;
    int team;
    int i;

    if ((lbl_803EA5C8->mItes == 1 || lbl_803EA5C8->mItes == 2) && fn_801485D4()) {
        switch (fn_801486A0()) {
        case 1:
            second = 1;
            break;
        case 0:
            first = 1;
            break;
        }
    }
    team = fn_8018BDFC(lbl_802D4D40.mIndex, 1, ids, &count);
    *pTeam = fn_8008454C(6, -1, 0);
    if (count > 0) {
        for (i = 0; i < count; i++) {
            if (fn_800809C4(lbl_803EA5CC, ids[i], 0)) {
                fn_8007ABA4(lbl_803EA5CC, 0x44494F50, ids[i]);
                fn_8007ABA4(lbl_803EA5CC, 0x44494754, *pTeam);
            }
        }
        int counts[7] = {1, 1, 1, 1, 1, 1, 1};
        fn_80084808(*pTeam, lbl_802D4DE4, counts, 7, ids2, 21);
        fn_80084908(0, 0, list, 7, ids2, 21);
        lbl_802D4D40.mUnknown2 = ids[0];
        int mode = fn_801486A0();
        if (mode >= 0 && mode <= 1) {
            fn_8005DB9C(team, list, lbl_802D4D40.mUnknown2, 7, fn_8005DB3C());
            fn_8005DFE8(list, ids, 1);
        } else {
            fn_8005DB9C(team, list, lbl_802D4D40.mUnknown2, 7, 1.0f);
            fn_8005DFE8(list, ids, count);
        }
        list[7] = 0x7FFF;
        fn_80060410(1, list);
        fn_800809C4(lbl_803EA5CC, lbl_802D4D40.mUnknown2, 0);
        fn_8003B4A4(1, list, 4, (unsigned char)count, fn_80080ECC(lbl_803EA5CC));
        fn_8005E010(1, ids, count, lbl_803EA5CC, 0);
        fn_80084A8C(team, list, 1, 7);
        fn_80083DE4(team);
        if (pCopy && pCount) {
            unsigned int copied = 0;
            if (first) {
                copied = 2;
            } else if (second) {
                copied = 3;
            }
            for (unsigned int k = 0; k < copied; k++) {
                pCopy[k] = list[k + 1];
            }
            *pCount = copied;
        }
        if (first || second) {
            fn_8007B14C(fn_8007B090(1), lbl_802D4D40.mUnknown2);
        }
    }
    return team;
}

void fn_8005E360(void)
{
    int list[14];
    int count;
    int home;
    int away;
    int awayTeam;
    int homeTeam;

    fn_8003B6F0(1);
    count = 0;
    fn_801D34D0(list, sizeof(list), 0x7FFF, 4);
    home = fn_8005E014(&homeTeam, list, &count);
    if (fn_8005D958()) {
        away = fn_8005DC10();
        awayTeam = away;
    } else {
        away = fn_8005DD6C(&awayTeam, &list[count]);
    }
    if (lbl_803EA5C8->mItes == 1 && fn_801486A0() != 15) {
        fn_80060044(away, awayTeam, list);
    }
    lbl_8030A1A0.mAway = away;
    lbl_8030A1A0.mHome = home;
    lbl_8030A1A0.mUnknown8 = 0;
    fn_8003B8BC();
}

void fn_8005E43C(void)
{
    if (fn_801485D4()) {
        fn_80148AF8(fn_80148A58());
    }
    fn_8005E360();
    fn_8003EBC4(0);
    fn_8003EBE4(0);
    fn_80015D28(lbl_803EA5C8->mDive);
    fn_801FCE10(0, "use 'EMAG' update 'YALP' set 'ITGT' = \x82 where 'DIOP' = \x82\n", 0x21, 0x1FF);
}

void fn_8005E4A8(void)
{
    int b = fn_8000FCDC();

    fn_80011600(-1, fn_8000FCCC(), b);
    fn_80186F30(lbl_802D4D40.mIndex, 1);
    fn_8007CAEC(2, 1);
    fn_8005DA7C(0, lbl_803EA5C8->mPes[1] >= 0 ? lbl_803EA5C8->mPes[1] : 2);
    fn_80073210(90);
    int ites = lbl_803EA5C8->mItes;
    switch (ites) {
    case 0:
        fn_8001B260(0, 0);
        fn_8001B330(4);
        lbl_8030A1A0.mAway = 0;
        lbl_8030A1A0.mUnknown8 = 0;
        lbl_8030A1A0.mHome = 1;
        break;
    case 1: {
        fn_8006088C(0);
        int type = lbl_803EA5C8->mPes[0];
        fn_801485B4();
        switch (type) {
        case 4:
            fn_801485EC(4);
            break;
        case 3:
            fn_801485EC(3);
            break;
        case 0:
            fn_801485EC(0);
            fn_8014F3DC(lbl_803EA5C8->mPes[3] * 60);
            break;
        case 5:
            fn_801485EC(5);
            break;
        case 1: {
            fn_801485EC(1);
            VetsRow_8018EC68 *pRow = lbl_803EA5C8;
            lbl_8031BDD4.mUnknown40 = pRow->mPes[2] == 1;
            if (pRow->mPes[1] >= 0) {
                lbl_8031BDD4.mUnknown32 = pRow->mPes[1];
                lbl_8031BDD4.mUnknown36 = 0;
            } else if (pRow->mPes[3] >= 0) {
                lbl_8031BDD4.mUnknown32 = 0;
                lbl_8031BDD4.mUnknown36 = pRow->mPes[3] * 60;
            } else {
                lbl_8031BDD4.mUnknown32 = 1;
                lbl_8031BDD4.mUnknown36 = 0;
            }
            break;
        }
        case 2: {
            int enable = 1;
            fn_801485EC(2);
            if (lbl_803EA5C8->mPes[2] == 2) {
                enable = 0;
            }
            fn_80148A58()->vfn_07(0, enable);
            fn_80148A58()->vfn_07(1, lbl_803EA5C8->mPes[3]);
            break;
        }
        }
        fn_8005E43C();
        break;
    }
    case 2:
        if (lbl_803EA5C8->mPes[0] == 4) {
            fn_801485B4();
            fn_801485EC(4);
        }
        fn_8005E43C();
        break;
    case 3:
        fn_8005E43C();
        break;
    }
}

int fn_8005E728(void)
{
    int value = 100;

    switch (lbl_803EA5C8->mItes) {
    case 0:
        value = 109;
        break;
    case 1:
        value = 700;
        break;
    case 2:
        switch (lbl_803EA5C8->mPes[0]) {
        case 4:
            value = 700;
            break;
        case 7:
            value = 122;
            break;
        }
        break;
    case 3:
        value = 122;
        break;
    }
    return value;
}

void fn_8005E798(void)
{
    int value = fn_8007F828(0);

    fn_8018E828(lbl_802D4D40.mIndex, value);
    lbl_802D4D40.mUnknown1 = value;
}

void fn_8005E7E4(void)
{
    int total;

    if (lbl_802D4D40.mUnknown1 < 0) {
        fn_8005E798();
    }
    fn_8018E658(lbl_802D4D40.mIndex, lbl_803EA5C8->mNets);
    total = 0;
    fn_8005D990(&total);
    total += lbl_803EA5C8->mPdwr;
    if (lbl_803EA5C8->mItes == 1) {
        switch (lbl_803EA5C8->mPes[0]) {
        case 0:
            if (lbl_803EA5E0 > 5) {
                lbl_803EA5E0 = 0;
            }
            total = total * (5 - lbl_803EA5E0) / 5;
            break;
        case 1:
            if (lbl_803EA5E0 > 3) {
                lbl_803EA5E0 = 0;
            }
            total = total * (3 - lbl_803EA5E0) / 3;
            break;
        }
    }
    lbl_802D4D40.mUnknown14 = total;
    total += lbl_802D4D40.mUnknownC;
    fn_8018E428(lbl_802D4D40.mIndex, total);
    int base = lbl_802D4D40.mUnknown8;
    lbl_802D4D40.mUnknown18 = lbl_803EA5C8->mCswr;
    fn_80087C5C(lbl_803EA5D0, 14, base + lbl_803EA5C8->mCswr);
    fn_8008880C(fn_8022F358(lbl_802D4D40.mIndex), lbl_803EA5C8->mCswr);
    lbl_8030A2AC.mDone[lbl_803EA5C8->mDive] = fn_8018E6E0(lbl_802D4D40.mIndex, lbl_803EA5C8->mDive);
    fn_8005D6EC();
}

int fn_8005E980(int dive, int droe, int *pLevel, int *pDone, int *pLocked, int count, char *pName, int size)
{
    VetsRow_8018EC68 row;
    VetsRow_8018EC68 first;
    int ites = 5;

    *pLevel = 0;
    *pLocked = 0;
    *pDone = 0;
    if (pName) {
        *pName = 0;
    }
    if (fn_8018EDF0(dive, droe, &row)) {
        ites = row.mItes;
        if (pName) {
            fn_801C2EF0(pName, row.mIuve, size);
        }
        *pLevel = fn_80086080(row.mQrxe);
        if (fn_8018E5F4(lbl_802D4D40.mIndex, row.mNets)) {
            *pDone = 1;
        } else if (row.mItes == 4) {
            fn_8018EDF0(0, 0, &first);
            *pLocked = !fn_8018E5F4(lbl_802D4D40.mIndex, first.mNets);
        } else if (lbl_802D4D40.mPpxe < row.mQrxe) {
            *pLocked = 1;
        }
        if (count > 2) {
            if (droe == 0) {
                lbl_803EC7F0 = 1;
                lbl_803EC7F1 = 1;
            }
            if (row.mItes != 2) {
                if (*pDone == 0) {
                    lbl_803EC7F1 = 0;
                }
            } else if (lbl_803EC7F1) {
                if (*pDone == 0) {
                    if (lbl_803EC7F0) {
                        *pLocked = 0;
                        lbl_803EC7F0 = 0;
                    } else {
                        *pLocked = 1;
                    }
                }
            } else {
                *pLocked = 1;
            }
        }
    }
    return ites;
}

int fn_8005EB20(int all)
{
    int found = 12;
    int dive;

    for (dive = 0; dive <= 11; dive++) {
        int count = all ? fn_8018EE44(dive) : 1;
        for (int droe = 0; droe < count; droe++) {
            int level;
            int done;
            int locked;
            int ites = fn_8005E980(dive, droe, &level, &done, &locked, count, 0, 0);
            if (ites == 4 || ites == 5) {
                continue;
            }
            if (!done && !locked) {
                found = dive;
                break;
            }
        }
        if (found != 12) {
            break;
        }
    }
    return found;
}

int fn_8005EBF0(int dive)
{
    int done = 0;

    if (lbl_8030A2AC.mDone[dive]) {
        done = 1;
    }
    return done;
}

int fn_8005EC14(int dive)
{
    int complete = 1;
    int count = fn_8018EE44(dive);

    for (int droe = 0; droe < count; droe++) {
        int level;
        int done;
        int locked;
        fn_8005E980(dive, droe, &level, &done, &locked, count, 0, 0);
        if (!done && !locked) {
            complete = 0;
            break;
        }
    }
    return complete;
}

void fn_8005ECA0(void)
{
    char hero[40];
    const char *pName = "Story task";
    int completed = 0;
    int length;

    lbl_8030A1E4[0] = 0;
    switch (lbl_803EA5C8->mItes) {
    case 0:
        pName = "a Pickup Game";
        break;
    case 1:
        switch (lbl_803EA5C8->mPes[0]) {
        case 4:
            pName = "a 4 on 4 Street Event";
            break;
        case 3:
            pName = "a 2 Minute Challenge Street Event";
            break;
        case 0:
            pName = "a Crush the Carrier Street Event";
            break;
        case 5:
            pName = "a Quick Strike Street Event";
            break;
        case 1:
            pName = "a \nJump Ball Battle Street Event";
            break;
        case 2:
            pName = "an Open Field Showdown Street Event";
            break;
        }
        break;
    case 2:
        pName = "a Local Game";
        break;
    case 3:
        pName = "an Exhibition Game";
        break;
    }
    if (lbl_802D4D40.mUnknown20 >= 1 && lbl_802D4D40.mUnknown20 <= 2) {
        fn_801C2E18(lbl_8030A1E4, "You have completed %s!", pName);
        completed = 1;
    }
    length = fn_801C3180(lbl_8030A1E4);
    if (completed && (lbl_802D4D40.mUnknown14 || lbl_802D4D40.mUnknown18)) {
        fn_801C2E18(lbl_8030A1E4 + length, "\nYou are rewarded");
        length = fn_801C3180(lbl_8030A1E4);
        if (lbl_802D4D40.mUnknown14) {
            fn_801C2E18(lbl_8030A1E4 + length, "\n%d Dev Points", lbl_802D4D40.mUnknown14);
            length = fn_801C3180(lbl_8030A1E4);
        }
        if (lbl_802D4D40.mUnknown18) {
            fn_801C2E18(lbl_8030A1E4 + length, "\n%d Credits", lbl_802D4D40.mUnknown18);
            length = fn_801C3180(lbl_8030A1E4);
        }
    }
    if (fn_8005EBF0(lbl_803EA5C8->mDive)) {
        int dive = fn_8005EB20(0);
        if (dive != 12) {
            fn_8007B684(dive);
            fn_8007B8A4(hero, 33);
            fn_8007B6D4();
            length = fn_801C3180(lbl_8030A1E4);
        }
    }
}

void fn_8005EEC4(int *pState, int *pScreen)
{
    VetsRow_8018EC68 first;
    unsigned short count;
    int played;
    int dive;

    if (fn_80061AD4()) {
        fn_80061ADC();
    }
    if (lbl_803EA5B8) {
        return;
    }
    fn_8005D818();
    fn_8005D660();
    fn_8005D764(1);
    if (fn_8005F910()) {
        fn_8018E7A0(lbl_802D4D40.mIndex, 0);
    }
    played = 0;
    lbl_803EA5E4 = 0;
    if (lbl_803EA5C8) {
        played = lbl_8030A1A0.mUnknown8 == 1;
    }
    fn_8005DA10();
    fn_8005D6EC();
    if (fn_8005D86C()) {
        *pState = 3;
        *pScreen = fn_8005D804(0);
    } else {
        dive = fn_8005EB20(1);
        if (dive == 12) {
            *pState = 1;
            *pScreen = fn_8005D804(0);
        } else {
            *pState = lbl_803EA5BC;
            if (lbl_803EA5C0 == -1) {
                *pScreen = fn_8005D804(dive);
            } else {
                *pScreen = lbl_803EA5C0;
            }
        }
        if (played) {
            fn_8005E7E4();
            fn_8018EDF0(0, 0, &first);
            if (lbl_803EA5C8->mNets == first.mNets) {
                lbl_803EA5C4 = 1;
            }
            if (lbl_803EA5C8->mItes == 0 || lbl_803EA5C8->mItes == 1) {
                lbl_802D4D40.mUnknown20 = 2;
                count = 0;
                fn_801F9D70(fn_8022F3D4(fn_8022F358(lbl_802D4D40.mIndex)), 0x59505453, 0, &count);
                if (count == 4) {
                    lbl_803EA5E4 = 1;
                }
            } else {
                lbl_802D4D40.mUnknown20 = 1;
            }
            dive = fn_8005EB20(1);
            if (dive != lbl_803EA5C8->mDive && fn_8005EBF0(lbl_803EA5C8->mDive)) {
                *pState = 2;
                if (dive == 12) {
                    *pScreen = fn_8005D804(0);
                } else {
                    *pScreen = fn_8005D804(dive);
                }
            } else {
                *pState = 3;
                *pScreen = fn_8005D804(lbl_803EA5C8->mDive);
            }
        } else if (lbl_803EA5C8) {
            *pState = 3;
            *pScreen = fn_8005D804(lbl_803EA5C8->mDive);
        }
    }
    if (fn_8005D86C() && played) {
        lbl_802D4D40.mUnknown20 = 0;
    }
    if (lbl_802D4D40.mUnknown20) {
        fn_8005ECA0();
    }
    lbl_803EA5C8 = 0;
    lbl_803EA5B8 = 1;
    lbl_803EA5D4 = fn_8005F754();
    fn_80027EA0();
}

void fn_8005F13C(int state, int screen)
{
    if (lbl_803EA5B8) {
        fn_8005D764(0);
        if (fn_801801B4() == 0) {
            fn_8005D818();
        } else if (fn_801801B4() == 1 && lbl_803EA5C8) {
            fn_80027E18(1);
            fn_8005E4A8();
        }
        fn_8005D60C();
        lbl_802D4D40.mUnknown20 = 0;
        lbl_803EA5B8 = 0;
    }
    if (fn_801801B4() == 0) {
        lbl_803EA5BC = 2;
        lbl_803EA5C0 = 4;
    } else {
        lbl_803EA5BC = state;
        lbl_803EA5C0 = screen;
    }
    fn_8005BE54(0);
}

void fn_8005F1F8(int dive, int *pCount)
{
    *pCount = fn_8018EE44(dive);
    if (dive == 0 && !fn_8005D94C()) {
        (*pCount)--;
    }
}

int fn_8005F24C(int dive, int droe)
{
    int value = 100;

    if (fn_8018EDF0(dive, droe, &lbl_8030A13C)) {
        lbl_803EA5C8 = &lbl_8030A13C;
        value = fn_8005E728();
    }
    return value;
}

void fn_8005F29C(void)
{
    VetsRow_8018EC68 row;
    int dive;

    fn_80010150(7);
    fn_8005D660();
    fn_8005D6EC();
    for (dive = 0;; dive++) {
        if (dive > 11) {
            dive = 5;
            break;
        }
        fn_8018EDF0(dive, 0, &row);
        if (row.mQrxe == 0) {
            break;
        }
    }
    fn_8005F24C(dive, 0);
    fn_80027E18(1);
    fn_8005E4A8();
    fn_8005D60C();
}

void fn_8005F324(int id)
{
    switch (id) {
    case 0:
        break;
    case 113:
        fn_80183368(4, 0x3FF);
        break;
    case 900:
        fn_80183368(2, 0x3FF);
        break;
    case 603:
        fn_80061AE8();
    case 109:
        fn_8001B828();
        break;
    }
}

int fn_8005F394(int screen)
{
    int shown = 0;

    if (lbl_802D4D40.mUnknown20 && screen == 5) {
        shown = 1;
        fn_8005BE54(1);
    }
    return shown;
}

int fn_8005F3E4(int *pResult)
{
    Object_8007A334 cursor;
    unsigned char color[4];
    int value = 0;

    *pResult = fn_80188DF0(-1);
    fn_8018B9D4(&cursor, lbl_802D4D40.mIndex);
    if (fn_8007A410(&cursor) > 0) {
        value = fn_8018C1E0(&cursor);
        if (fn_8007A98C(&cursor, 0x4C445443) == 0) {
            color[0] = fn_8007A98C(&cursor, 0x31434D54);
            color[1] = fn_8007A98C(&cursor, 0x32434D54);
            color[2] = fn_8007A98C(&cursor, 0x33434D54);
            fn_80188CBC(0, 4, value, 0xAC, color);
            *pResult = fn_80188DF0(0);
        }
    }
    fn_8018BA2C(&cursor);
    return value;
}

void fn_8005F4EC(char *pName, int size)
{
    Object_8007A334 cursor;
    char buffer[64];
    unsigned int last = size - 1;
    unsigned int length;

    *pName = 0;
    fn_8018E11C(&cursor, lbl_802D4D40.mIndex);
    buffer[0] = 0;
    if (!fn_8018E20C(&cursor, 0, buffer, sizeof(buffer))) {
        *pName = 0;
    }
    buffer[last] = 0;
    length = fn_801C3180(buffer);
    buffer[0] = 0;
    if (!fn_8018E194(&cursor, 0, buffer, sizeof(buffer))) {
        *pName = 0;
    } else {
        buffer[last] = 0;
        unsigned int first = fn_801C3180(buffer);
        length += first + 1;
        if (length < last - 1) {
            buffer[first] = ' ';
            first++;
            fn_8018E20C(&cursor, 0, buffer + first, sizeof(buffer) - first);
            buffer[length] = 0;
        }
    }
    if (*pName == 0) {
        fn_8018E284(&cursor, 0, pName, last);
        if (*pName == 0) {
            fn_801C2EF0(pName, "your hero", last);
            goto done;
        }
    }
    fn_801C2EF0(pName, buffer, last);
done:
    pName[last] = 0;
    fn_8018E174(&cursor);
}

void fn_8005F664(char *pName, int size)
{
    Object_8007A334 cursor;
    int last = size - 1;

    *pName = 0;
    fn_8018B9D4(&cursor, lbl_802D4D40.mIndex);
    if (fn_8007A410(&cursor) > 0) {
        fn_8007A600(&cursor, 0);
        fn_8007AA3C(&cursor, 0x414E4454, (int)pName, last);
    }
    fn_8018BA2C(&cursor);
}

void fn_8005F708(int *pList, int id, int slot)
{
    if (slot > 6) {
        return;
    }
    int previous = pList[slot];
    pList[slot] = id;
    for (int i = 0; i < 7; i++) {
        if (i != slot && pList[i] == id) {
            pList[i] = previous;
        }
    }
}

float fn_8005F754(void)
{
    float scale;

    if (lbl_803EA5B8) {
        scale = lbl_803EA5D4 = fn_800860B4(lbl_802D4D40.mUnknown1C) * 0.001f;
    } else {
        scale = lbl_803EA5D4;
    }
    return scale;
}

void fn_8005F7C4(Object_8008044C *pObject, int id, float scale)
{
    int found = fn_800809C4(pObject, id, 0);
    int type = fn_80080CB0(pObject);

    if ((type == 1 || type == 2) && found) {
        for (int i = 0; i < 10; i++) {
            unsigned int value = fn_800812B0(pObject, lbl_802D4E00[i]);
            value -= (int)(value * scale);
            if (value > 100) {
                value = 100;
            }
            if (value < 5) {
                value = 5;
            }
            fn_8008135C(pObject, lbl_802D4E00[i], value);
        }
    }
}

void fn_8005F8B4(Args_8005F8B4 *pArgs)
{
    Text_8005F8B4 *pDest = pArgs->mpText;
    char *pText = pDest->mpText;
    int size = pDest->mSize;

    *pText = 0;
    fn_801C2EF0(pText, lbl_8030A1E4, size);
}

void fn_8005F8F0(void)
{
    lbl_802D4D40.mUnknown20 = 0;
}

void fn_8005F900(int *pHome)
{
    *pHome = lbl_8030A1A0.mHome;
}

int fn_8005F910(void)
{
    return fn_8018E774(fn_8022F384(fn_8022F4BC()));
}

int fn_8005F938(unsigned int id, int *pArgs, int unused, int *pResult)
{
    int dive;

    switch (id) {
    case 0x80000001:
        fn_8005EEC4((int *)pArgs[0], (int *)pArgs[1]);
        break;
    case 0x80000002:
        fn_8005F13C(pArgs[0], pArgs[1]);
        break;
    case 0x80000003: {
        int *pCount = (int *)pArgs[1];
        dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pCount = 0;
        } else {
            fn_8005F1F8(dive, pCount);
        }
        break;
    }
    case 0x80000004: {
        dive = fn_8005D7F0(pArgs[0]);
        int droe = pArgs[1];
        int *pLevel = (int *)pArgs[2];
        int *pDone = (int *)pArgs[4];
        int *pLocked = (int *)pArgs[5];
        if (dive == 12) {
            *pLevel = 0;
            *pDone = 1;
            *pLocked = 1;
        } else {
            Text_8005F8B4 *pText = (Text_8005F8B4 *)pArgs[3];
            fn_8005E980(dive, droe, pLevel, pDone, pLocked, fn_8018EE44(dive), pText->mpText, pText->mSize);
        }
        break;
    }
    case 0x80000005:
        dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pResult = 1;
        } else {
            *pResult = fn_8005EBF0(dive);
        }
        break;
    case 0x80000006:
        dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pResult = 100;
        } else {
            *pResult = fn_8005F24C(dive, pArgs[1]);
        }
        break;
    case 0x80000007:
        fn_8005F324(pArgs[0]);
        break;
    case 0x80000008:
        *pResult = fn_8005F394(pArgs[0]);
        break;
    case 0x80000009:
        if (fn_8005D958()) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x8000000A:
        if (lbl_803EA5C4) {
            *pResult = 1;
            lbl_803EA5C4 = 0;
        } else {
            *pResult = 0;
        }
        break;
    case 0x8000000B:
        dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pResult = 1;
        } else {
            *pResult = fn_8005EC14(dive);
        }
        break;
    case 0x8000000C:
        *pResult = lbl_803EA5E4;
        break;
    case 0x182: {
        Text_8005F8B4 *pText = (Text_8005F8B4 *)pArgs[0];
        int found = fn_8008611C(lbl_802D4D40.mUnknown1C, pText->mpText, pText->mSize);
        *pResult = lbl_802D4D40.mUnknown1C;
        if (!found) {
            fn_801C2EF0(pText->mpText, "", pText->mSize);
        }
        break;
    }
    case 0x17B:
        *pResult = *(int *)pArgs[0] = fn_8005F3E4((int *)pArgs[1]);
        break;
    case 0x16E: {
        Text_8005F8B4 *pText = (Text_8005F8B4 *)pArgs[0];
        fn_8005F4EC(pText->mpText, pText->mSize);
        break;
    }
    case 0x146: {
        Text_8005F8B4 *pText = (Text_8005F8B4 *)pArgs[0];
        fn_8005F664(pText->mpText, pText->mSize);
        break;
    }
    case 0x11A:
        fn_8005F324(113);
        break;
    default:
        return 0;
    }
    return 1;
}

VetsRow_8018EC68 *fn_8005FC7C(void)
{
    return lbl_803EA5C8;
}

int fn_8005FC84(void)
{
    int active;

    if (!lbl_803EA5C8) {
        active = 0;
    } else {
        active = 1;
        switch (fn_80178AE0()) {
        case 0:
            lbl_8030A1A0.mUnknown8 = 2;
            break;
        case 1:
            lbl_8030A1A0.mUnknown8 = active;
            break;
        default:
            lbl_8030A1A0.mUnknown8 = 3;
            break;
        }
    }
    return active;
}

void fn_8005FCF8(int *pAway, int *pHome)
{
    int ids[13];
    int itgt[13];
    int count;
    int i;
    int away;
    int home;

    for (i = 0; i < 6; i++) {
        ids[i] = pHome[i + 1];
    }
    for (i = 0; i < 7; i++) {
        ids[i + 6] = pAway[i];
    }
    {
        Object_8008044C object;
        int *pOut = itgt;
        fn_8008044C(&object, 0, 0x54415453);
        for (i = 0; i <= 12; i++) {
            if (fn_800809C4(&object, ids[i], 0)) {
                *pOut++ = fn_8007A98C(&object, 0x49544754);
            }
        }
        fn_8008056C(&object);
    }
    if (lbl_803EA5D8 != -1) {
        fn_801F967C(0x54415453, lbl_803EA5D8);
        lbl_803EA5D8 = -1;
    }
    fn_801F9980(0x54415453, &lbl_803EA5D8);
    fn_801FCE10(0, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", lbl_803EA5D8,
                ids[0], ids[1], ids[2], ids[3], ids[4], ids[5], ids[6], ids[7], ids[8], ids[9], ids[10], ids[11], ids[12]);
    fn_801FCE10(0, "use 'TATS' select count(*) into \x82 from \x8c\n", &count, lbl_803EA5D8);
    {
        Object_8007A334 cursor;
        if (fn_8007CB6C(2) == 0) {
            away = 1;
            home = 0;
        } else {
            away = 0;
            home = 1;
        }
        fn_8007A334(&cursor, lbl_803EA5D8, 0x44494750, 0, 0, 0x54415453);
        for (i = 1; i <= 6; i++) {
            if (fn_800809C4((Object_8008044C *)&cursor, pHome[i], 0)) {
                fn_80081F50((Object_8008044C *)&cursor, away, 1);
            }
        }
        for (i = 0; i <= 6; i++) {
            if (fn_800809C4((Object_8008044C *)&cursor, pAway[i], 0)) {
                fn_80081F50((Object_8008044C *)&cursor, home, 1);
            }
        }
        fn_8007A3C4(&cursor);
    }
    if (lbl_803EA5DC != -1) {
        fn_801F967C(0x54415453, lbl_803EA5DC);
        lbl_803EA5DC = -1;
    }
    fn_801F9980(0x54415453, &lbl_803EA5DC);
    fn_801FCE10(0, "use 'TATS' select into 'TATS'.\x8c * from 'MAET' where ('DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85 || 'DIGT' = \x85)\n", lbl_803EA5DC,
                itgt[0], itgt[1], itgt[2], itgt[3], itgt[4], itgt[5], itgt[6], itgt[7], itgt[8], itgt[9], itgt[10], itgt[11],
                itgt[12]);
    fn_801FCE10(0, "use 'TATS' select count(*) into \x82 from \x8c\n", &count, lbl_803EA5DC);
}

void fn_80060044(int team, int id, int *pList)
{
    QueryResult result;

    if (lbl_803EA5D8 != -1) {
        fn_801F967C(0x54415453, lbl_803EA5D8);
        lbl_803EA5D8 = -1;
    }
    fn_801F9980(0x54415453, &lbl_803EA5D8);
    switch (fn_801486A0()) {
    case 1:
        fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", lbl_803EA5D8, pList[0], pList[1], pList[2],
                    pList[3], pList[4], pList[5]);
        break;
    case 0:
        fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", lbl_803EA5D8, pList[0], pList[1], pList[2],
                    pList[3], pList[4]);
        break;
    case 3:
        fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", lbl_803EA5D8, pList[0], pList[1], pList[2]);
        break;
    case 2:
        if (lbl_803EA5C8->mPes[2] == 2) {
            fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85)\n", lbl_803EA5D8, pList[0], pList[1]);
        } else {
            fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85)\n", lbl_803EA5D8, pList[0]);
        }
        break;
    case 4:
        fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", lbl_803EA5D8, pList[0], pList[1], pList[2],
                    pList[3]);
        break;
    default:
        fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'YALP' where ('DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85 || 'DIGP' = \x85)\n", lbl_803EA5D8, pList[0], pList[1], pList[2],
                    pList[3], pList[4], pList[5], pList[6]);
        break;
    }
    if (lbl_803EA5DC != -1) {
        fn_801F967C(0x54415453, lbl_803EA5DC);
        lbl_803EA5DC = -1;
    }
    fn_801F9980(0x54415453, &lbl_803EA5DC);
    fn_801FCE10(&result, "use 'TATS' select into 'TATS'.\x8c * from 'MAET' where 'DIGT' = \x85 or 'DIGT' = \x85\n",
                lbl_803EA5DC, team, id);
}

void fn_80060278(void)
{
    if (lbl_803EA5D8 != -1) {
        fn_801F967C(0x54415453, lbl_803EA5D8);
        lbl_803EA5D8 = -1;
    }
    if (lbl_803EA5DC != -1) {
        fn_801F967C(0x54415453, lbl_803EA5DC);
        lbl_803EA5DC = -1;
    }
}

int fn_800602D8(void)
{
    return lbl_803EA5D8;
}

int fn_800602E0(void)
{
    return lbl_803EA5DC;
}

int fn_800602E8(void)
{
    VetsRow_8018EC68 *pRow = lbl_803EA5C8;

    if (pRow && (pRow->mItes == 0 || (pRow->mItes == 1 && pRow->mQrxe != 0)) && lbl_8030A1A0.mUnknown8 == 1) {
        return 1;
    }
    return 0;
}

void fn_80060330(int group, int *pIds, int count, Object_8008044C *pObject)
{
    fn_8005E010(group, pIds, count, pObject, 0);
}

int fn_80060354(VetsRow_8018EC68 *pRow, int *pList)
{
    int set = 0;
    int type = pRow->mCsis;

    if (type == -1) {
        type = pRow->mCsos;
    }
    if (type != -1) {
        switch (type) {
        case 0:
        case 1:
            fn_8005F708(pList, 0x1FF, 1);
            set = 1;
            break;
        case 2:
        case 3:
            fn_8005F708(pList, 0x1FF, 0);
            fn_8005F708(pList, 0x1FB, 1);
            set = 2;
            break;
        case 4:
            fn_8005F708(pList, 0x1F8, 1);
            set = 1;
            break;
        }
    }
    return set;
}

void fn_80060410(int index, int *pList)
{
    for (int i = 0; i < 7; i++) {
        lbl_8030A1AC[index][i] = pList[i];
    }
}

int *fn_80060444(int index)
{
    return lbl_8030A1AC[index];
}

void fn_80060458(int index, int level)
{
    VetsRow_8018EC68 row;
    int ppxe[4] = {16, 39, 63, 72};
    unsigned int mask = 0;
    VetsRow_8018EC68 *pSaved;
    int dive;

    switch (level) {
    case 3:
        mask = 8;
    case 2:
        mask |= 0x16;
    case 1:
        mask |= 0x340;
    case 0:
        mask |= 0xA0;
        fn_8018E390(index, ppxe[level]);
        break;
    }
    fn_8018EEF0();
    pSaved = lbl_803EA5C8;
    for (dive = 0; dive <= 11; dive++) {
        if (mask & (1 << dive)) {
            lbl_803EA5C8 = &row;
            int count = fn_8018EE44(dive);
            for (int droe = 0; droe < count; droe++) {
                fn_8018EDF0(dive, droe, &row);
                if (!fn_8018E5F4(index, row.mNets)) {
                    fn_8018E658(index, row.mNets);
                }
            }
        }
    }
    fn_8018E7A0(index, 0);
    fn_8018EEAC();
    lbl_803EA5C8 = pSaved;
}

void fn_8006059C(int index)
{
    VetsRow_8018EC68 row;
    VetsRow_8018EC68 *pSaved;
    int dive;

    fn_8018EEF0();
    pSaved = lbl_803EA5C8;
    for (dive = 0; dive <= 11; dive++) {
        lbl_803EA5C8 = &row;
        int count = fn_8018EE44(dive);
        for (int droe = 0; droe < count; droe++) {
            if (dive == 0 && droe == count - 1) {
                continue;
            }
            fn_8018EDF0(dive, droe, &row);
            if (!fn_8018E5F4(index, row.mNets)) {
                fn_8018E658(index, row.mNets);
            }
        }
    }
    fn_8018E7A0(index, 0);
    fn_8018EEAC();
    lbl_803EA5C8 = pSaved;
}

void fn_80060674(int index)
{
    fn_8018E55C(index);
    fn_8018E390(index, 0);
    fn_8018E474(index);
    fn_8018E7A0(index, 1);
    fn_8018E828(index, -1);
}

Object_80039F5C *fn_800606CC(int type, int position)
{
    Object_80039F5C *pResult = 0;
    Object_80039F5C *pObject = 0;
    int *pList = 0;
    int id = 0;

    switch (type) {
    case 0:
    case 1:
    case 2:
        pList = fn_80060444(0);
        switch (position) {
        case 0:
            id = pList[1];
            break;
        case 3:
            id = pList[0];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        pList = fn_80060444(0);
        switch (position) {
        case 0:
            id = pList[1];
            break;
        case 2:
            id = pList[0];
            break;
        case 3:
        case 9:
            id = pList[6];
            break;
        case 4:
            id = pList[2];
            break;
        case 5:
            id = pList[3];
            break;
        case 6:
            id = pList[4];
            break;
        case 7:
        case 8:
            id = pList[5];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 8:
        pList = fn_80060444(0);
        switch (position) {
        case 0:
            id = pList[0];
            break;
        case 2:
            id = pList[1];
            break;
        case 3:
            id = pList[2];
            break;
        case 4:
            id = pList[3];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 9:
    case 10:
    case 11:
        pList = fn_80060444(0);
        switch (position) {
        case 0:
            id = pList[0];
            break;
        case 1:
            id = pList[1];
            break;
        default:
            pList = 0;
            break;
        }
        break;
    case 12:
        if (position == 1) {
            pList = fn_80060444(0);
            id = pList[1];
        }
        break;
    }
    if (pList) {
        pObject = fn_8003AD2C(id);
    }
    if (pObject) {
        pResult = pObject;
    }
    return pResult;
}

void fn_8006088C(int value)
{
    lbl_803EA5E0 = value;
}
}
