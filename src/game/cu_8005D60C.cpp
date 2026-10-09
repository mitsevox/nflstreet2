#include <string.h>

#include "game/Object_8007A334.h"
#include "game/Class_80148A58.h"
#include "game/Object_8008044C.h"
#include "game/cu_8003AEA8.h"
#include "game/cu_8003E214.h"
#include "game/cu_8018EC68.h"
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
void fn_800731D0(int a);
int fn_8003B4A4(int group, int *list, int value, int a, int b);
unsigned char fn_8007B090(int a);
void fn_8007B684(int id);
void fn_8007B6D4(void);
void fn_8007B8A4(char *pDest, int count);
void fn_8007B14C(int pad, int id);
void fn_80073210(int frames);
void fn_8007CAEC(int index, int value);
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
void fn_80186F30(signed char a, int b);
void fn_8018B9D4(Object_8007A334 *pCursor, int index);
void fn_8018BA2C(Object_8007A334 *pCursor);
int fn_8018BDFC(int index, int a, int *pIds, int *pCount);
int fn_8018C1E0(Object_8007A334 *pCursor);
void fn_8018C48C(int tag);
int fn_8018E344(int index);
void fn_8018E390(int index, int value);
int fn_8018E3DC(int index);
void fn_8018E428(int index, int value);
int fn_8018E5F4(int index, int id);
void fn_8018E658(int index, int id);
int fn_8018E6A4(int index);
int fn_8018E6E0(int index, int a);
int fn_8018E7CC(int index);
void fn_8018E828(int index, int value);
int fn_8018F1F0(unsigned int index, char *pEtnr, int size);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
unsigned int fn_801C3180(const char *pText);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_801D34D0(void *pDest, int size, int value, int width);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F4BC(void);
}

Object_8008044C lbl_8030A0E4;
Object_8007A334 lbl_8030A110;
VetsRow_8018EC68 lbl_8030A13C;
extern Settings_8031BDD4 lbl_8031BDD4;

Match_8030A1A0 lbl_8030A1A0;
char lbl_8030A1E4[200];
Progress_8030A2AC lbl_8030A2AC;

VetsRow_8018EC68 *lbl_803EA5C8;
Object_8008044C *lbl_803EA5CC = 0;
Object_8007A334 *lbl_803EA5D0 = 0;
float lbl_803EA5D4;
int lbl_803EA5E0;

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
void fn_8006088C(int value);
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
}
