/* Story-mode events: lists the story's events with their completion flags,
   sets up the chosen event's teams and street-event settings, records the
   completed event and builds its reward text ("You have completed %s!",
   points and credits), and handles the event screen's messages. Also builds
   the stat table of the event's players and sets the story progress that
   the cheats ask for. */
#include <string.h>

#include "game/DbCursor.h"
#include "game/fn_8005FC84.h"
#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8008044C.h"
#include "game/DepthChart.h"
#include "game/AutoDepth.h"
#include "game/StevTable.h"
#include "game/FELoop.h"
#include "game/fn_80061AD4.h"
#include "game/GameOptions.h"
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

/* Values returned by GameOptionsGet and restored through GameOptionsSet. */
struct Saved_802D4D64 {
    int mValue0;
    int mValue1;
    int mValue14;
    unsigned char mSaved;
};

/* Street event settings; fn_8005E4A8 sets the timer words. */
struct MiniGameSettings_t {
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
void MsgTeamPickSetMode(int a, int b);
void MsgTeamPickSetSources(int a);
void MsgTeamPickRequestTeamSave(void);
void fn_80010150(int a);
void SndgMusicPumpFrame(int a);
Object_80039F5C *PlyrFindByPoid(int id);
void DepthChartAutoFillEx(int group, int *list, int value, int a, int b);
unsigned char PortDbGetSidePort(int a);
void EnvSelect(int id);
void EnvRelease(void);
void EnvGetUIName(char *pDest, int count);
void PortDbSetControlledPlayer(int pad, int id);
void SndgMusicWaitForStart(int frames);
void GameInfoSet(int index, int value);
int GameInfoGet(int index);
int PlayerDbGetPrty(Object_8008044C *pObject);
int PlayerDbGetPbpo(Object_8008044C *pObject);
unsigned int PlayerDbGetRating(Object_8008044C *pObject, int index);
void PlayerDbSetRating(Object_8008044C *pObject, int index, int value);
void fn_80083DE4(int id);
int fn_8008454C(int type, int logo, const char *pName);
void fn_80084808(int a, int *pIds, int *pCounts, int count, int *pOut, int total);
void fn_80084908(int a, int b, int *pOut, unsigned int count, int *pIn, unsigned int size);
void fn_80084A8C(int a, int *pList, int b, int c);
void fn_80084C24(int team, int *pList, int side, int count);
void fn_80084FA8(int value);
void fn_80084FE4(int value);
unsigned int ExpLevelGetForPoints(int ppxe);
int ExpLevelGetScft(int vlxe);
int ExpLevelGetLvbn(int vlxe);
int ExpLevelGetName(int vlxe, char *pName, int size);
int ExpLevelClose(void);
int ExpLevelOpen(void);
void UserStatsOpen(DbCursor *pObject, int index);
void UserStatsClose(DbCursor *pObject);
void UserStatsSet(DbCursor *pObject, int index, int value);
int UserStatsGet(DbCursor *pObject, unsigned int index);
void UserInfoAddPoints(int db, int id);
void fn_801485B4(void);
int fn_801485D4(void);
void fn_801485EC(int value);
int fn_801486A0(void);
void fn_80148AF8(Class_80148A58 *pObject);
void fn_8014F3DC(int ticks);
void EditMenuBegin(int mode, int value);
void fn_80186F30(signed char a, int b);
void TeamLogoRequestTint(int index, int a, int b, int c, const unsigned char *pColor);
int TeamLogoGetHandle(int a);
void StoryTeamCursorOpen(DbCursor *pCursor, int index);
void StoryTeamCursorClose(DbCursor *pCursor);
int StoryTeamLoadToStats(int index, int a, int *pIds, int *pCount);
int StoryTeamGetLogo(DbCursor *pCursor);
void fn_8018C48C(int tag);
void StoryClearFlags(int index);
void StoryClearCompletedEvents(int index);
void StoryPlayerCursorOpen(DbCursor *pCursor, int index);
void StoryPlayerCursorClose(DbCursor *pCursor);
int StoryPlayerGetFirstName(DbCursor *pCursor, int row, char *pBuffer, int size);
int StoryPlayerGetLastName(DbCursor *pCursor, int row, char *pBuffer, int size);
int StoryPlayerGetShortName(DbCursor *pCursor, int row, char *pName, int size);
int StoryGetExpPoints(int index);
void StorySetExpPoints(int index, int value);
void StorySetNew(int index, int value);
int StoryGetDevPoints(int index);
void StorySetDevPoints(int index, int value);
int StoryIsEventCompleted(int index, int id);
void StoryAddCompletedEvent(int index, int id);
int StoryCountRemainingEvents(int index);
int StoryAreGroupEventsCompleted(int index, int a);
int StoryGetLkss(int index);
int StoryIsNew(int index);
void StorySetLkss(int index, int value);
int SstlGetEntryTag(unsigned int index, char *pEtnr, int size);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int MemFill(void *pDest, int size, int value, int width);
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_801F9D70(int handle, int table, DbFilter *pFilter, unsigned short *pCount);
int fn_8022F358(int index);
int fn_8022F3D4(int a);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_8005BE54(unsigned char value);
void fn_80061ADC(void);
void fn_80061AE8(void);
int MsgGameGetSetupState(void);
int fn_80178AE0(void);
}

Object_8008044C lbl_8030A0E4;
DbCursor lbl_8030A110;
StevRow_t lbl_8030A13C;
extern MiniGameSettings_t lbl_8031BDD4;

Match_8030A1A0 lbl_8030A1A0;
int lbl_8030A1AC[2][7];
char lbl_8030A1E4[200];
Progress_8030A2AC lbl_8030A2AC;

unsigned char lbl_803EA5B8 = 0;
int lbl_803EA5BC = 2;
int lbl_803EA5C0 = 4;
int lbl_803EA5C4 = 0;
StevRow_t *lbl_803EA5C8 = 0;
Object_8008044C *lbl_803EA5CC = 0;
DbCursor *lbl_803EA5D0 = 0;
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
int fn_80060354(StevRow_t *pRow, int *pList);
void fn_80060410(int index, int *pList);

void fn_8005D60C(void)
{
    ExpLevelClose();
    fn_8008056C(lbl_803EA5CC);
    lbl_803EA5CC = 0;
    StevClose();
    UserStatsClose(lbl_803EA5D0);
    lbl_802D4D40.mIndex = -1;
    lbl_803EA5D0 = 0;
}

void fn_8005D660(void)
{
    lbl_802D4D40.mIndex = fn_8022F384(fn_8022F4BC());
    lbl_803EA5CC = &lbl_8030A0E4;
    fn_8008044C(&lbl_8030A0E4, 0, 0x54415453);
    StevOpen();
    ExpLevelOpen();
    lbl_802D4D40.mUnknown2 = 0x7FFF;
    lbl_803EA5D0 = &lbl_8030A110;
    SndgMusicPumpFrame(1);
    UserStatsOpen(lbl_803EA5D0, lbl_802D4D40.mIndex);
}

void fn_8005D6EC(void)
{
    lbl_802D4D40.mPpxe = StoryGetExpPoints(lbl_802D4D40.mIndex);
    lbl_802D4D40.mUnknown1C = ExpLevelGetForPoints(lbl_802D4D40.mPpxe);
    lbl_802D4D40.mUnknown8 = UserStatsGet(lbl_803EA5D0, 14);
    lbl_802D4D40.mUnknownC = StoryGetDevPoints(lbl_802D4D40.mIndex);
    lbl_802D4D40.mUnknown1 = StoryGetLkss(lbl_802D4D40.mIndex);
}

void fn_8005D764(int set)
{
    DbCursor cursor;
    int value;

    StoryTeamCursorOpen(&cursor, lbl_802D4D40.mIndex);
    value = StoryTeamGetLogo(&cursor);
    StoryTeamCursorClose(&cursor);
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
    SndgMusicPumpFrame(1);
    SndgMusicPumpFrame(0);
    fn_8018C48C(0x54415453);
    SndgMusicPumpFrame(1);
    fn_8018C48C(0x454D4147);
    SndgMusicPumpFrame(0);
}

int fn_8005D86C(void)
{
    StevRow_t row;
    int complete = 1;
    int i;

    for (i = 0; i <= 11; i++) {
        SndgMusicPumpFrame(1);
        int done = StoryAreGroupEventsCompleted(lbl_802D4D40.mIndex, i);
        lbl_8030A2AC.mDone[i] = done;
        if (complete && !done) {
            int count = StevCountDiveRows(i);
            for (int j = 0; j < count; j++) {
                if (StevGetRow(i, j, &row) && !StoryIsEventCompleted(lbl_802D4D40.mIndex, row.mNets) &&
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
    return StoryCountRemainingEvents(lbl_802D4D40.mIndex) == 2;
}

void fn_8005D990(int *pTotal)
{
    StevRow_t *pRow = lbl_803EA5C8;
    int ppxe = lbl_802D4D40.mPpxe + pRow->mPewr;
    unsigned short limit = lbl_802D4D40.mUnknown1C;
    lbl_802D4D40.mUnknown10 = pRow->mPewr;
    unsigned int level = ExpLevelGetForPoints(ppxe);
    StorySetExpPoints(lbl_802D4D40.mIndex, ppxe);
    if (level > limit) {
        *pTotal += ExpLevelGetLvbn(level);
    }
}

void fn_8005DA10(void)
{
    if (lbl_802D4D64.mSaved) {
        GameOptionsSet(14, lbl_802D4D64.mValue14);
        GameOptionsSet(1, lbl_802D4D64.mValue1);
        if (lbl_802D4D64.mValue0 > -1) {
            GameOptionsSet(0, lbl_802D4D64.mValue0);
        }
        lbl_802D4D64.mSaved = 0;
    }
}

void fn_8005DA7C(int value14, int value1)
{
    if (!lbl_802D4D64.mSaved) {
        lbl_802D4D64.mSaved = 1;
        lbl_802D4D64.mValue14 = GameOptionsGet(14);
        lbl_802D4D64.mValue1 = GameOptionsGet(1);
        if (lbl_802D4D40.mUnknown1 > -1) {
            lbl_802D4D64.mValue0 = GameOptionsGet(0);
        } else {
            lbl_802D4D64.mValue0 = lbl_802D4D40.mUnknown1;
        }
    }
    GameOptionsSet(14, value14);
    GameOptionsSet(1, value1);
    if (lbl_802D4D40.mUnknown1 > -1) {
        GameOptionsSet(0, lbl_802D4D40.mUnknown1);
    }
}

float fn_8005DB3C(void)
{
    return lbl_803EA5D4 = ExpLevelGetScft(lbl_802D4D40.mUnknown1C) * 0.001f;
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
    // FAKEMATCH: dead initializer; count is set from the query result before its use
    unsigned int count = 0;
    unsigned int i;

    MemFill(list, sizeof(list), 0x7FFF, 4);
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
    DepthChartAutoFill(0, list, 4);
    fn_80084C24(0x21, list, 0, 7);
    fn_80083DE4(0x21);
    return 0x21;
}

int fn_8005DD6C(int *pTeam, int *pCopy)
{
    int ids[21];
    int list[14];
    unsigned int count;
    int full;
    int team;
    int etnr;

    full = count = 0;
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
        case 5:
        default:
            count = 7;
            break;
        }
    }
    char name[33] = {0};
    etnr = -1;
    if (lbl_803EA5C8->mItes == 2) {
        etnr = SstlGetEntryTag(lbl_803EA5C8->mNets, name, sizeof(name));
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
    DepthChartAutoFill(0, list, 4);
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
        case 2:
            break;
        }
    }
    team = StoryTeamLoadToStats(lbl_802D4D40.mIndex, 1, ids, &count);
    *pTeam = fn_8008454C(6, -1, 0);
    if (count > 0) {
        for (i = 0; i < count; i++) {
            if (PlayerDbSeekId(lbl_803EA5CC, ids[i], 0)) {
                DbCursorSetInt(lbl_803EA5CC, 0x44494F50, ids[i]);
                DbCursorSetInt(lbl_803EA5CC, 0x44494754, *pTeam);
            }
        }
        int counts[7] = {1, 1, 1, 1, 1, 1, 1};
        fn_80084808(*pTeam, lbl_802D4DE4, counts, 7, ids2, 21);
        fn_80084908(0, 0, list, 7, ids2, 21);
        lbl_802D4D40.mUnknown2 = ids[0];
        switch (fn_801486A0()) {
        case 0:
        case 1:
            fn_8005DB9C(team, list, lbl_802D4D40.mUnknown2, 7, fn_8005DB3C());
            fn_8005DFE8(list, ids, 1);
            break;
        case 2:
        default:
            fn_8005DB9C(team, list, lbl_802D4D40.mUnknown2, 7, 1.0f);
            fn_8005DFE8(list, ids, count);
            break;
        }
        list[7] = 0x7FFF;
        fn_80060410(1, list);
        PlayerDbSeekId(lbl_803EA5CC, lbl_802D4D40.mUnknown2, 0);
        DepthChartAutoFillEx(1, list, 4, (unsigned char)count, PlayerDbGetPbpo(lbl_803EA5CC));
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
            PortDbSetControlledPlayer(PortDbGetSidePort(1), lbl_802D4D40.mUnknown2);
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

    DepthChartLoad(1);
    count = 0;
    MemFill(list, sizeof(list), 0x7FFF, 4);
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
    DepthChartSave();
}

void fn_8005E43C(void)
{
    if (fn_801485D4()) {
        fn_80148AF8(fn_80148A58());
    }
    fn_8005E360();
    AutoDepthSetRateCallback(0);
    AutoDepthSetSelectCallback(0);
    fn_80015D28(lbl_803EA5C8->mDive);
    fn_801FCE10(0, "use 'EMAG' update 'YALP' set 'ITGT' = \x82 where 'DIOP' = \x82\n", 0x21, 0x1FF);
}

void fn_8005E4A8(void)
{
    int b = fn_8000FCDC();

    fn_80011600(-1, fn_8000FCCC(), b);
    fn_80186F30(lbl_802D4D40.mIndex, 1);
    GameInfoSet(2, 1);
    fn_8005DA7C(0, lbl_803EA5C8->mPes[1] >= 0 ? lbl_803EA5C8->mPes[1] : 2);
    SndgMusicWaitForStart(90);
    int ites = lbl_803EA5C8->mItes;
    switch (ites) {
    case 0:
        MsgTeamPickSetMode(0, 0);
        MsgTeamPickSetSources(4);
        lbl_8030A1A0.mAway = 0;
        lbl_8030A1A0.mHome = 1;
        lbl_8030A1A0.mUnknown8 = 0;
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
            // FAKEMATCH: reused local; value holds mPes[2], then mPes[1], then mPes[3]
            int value = lbl_803EA5C8->mPes[2];
            lbl_8031BDD4.mUnknown40 = value == 1;
            value = lbl_803EA5C8->mPes[1];
            if (value < 0) {
                value = lbl_803EA5C8->mPes[3];
                if (value < 0) {
                    lbl_8031BDD4.mUnknown32 = 1;
                    lbl_8031BDD4.mUnknown36 = 0;
                } else {
                    lbl_8031BDD4.mUnknown32 = 0;
                    // FAKEMATCH: the product goes back into value; it sets the target's register choice
                    value *= 60;
                    lbl_8031BDD4.mUnknown36 = value;
                }
            } else {
                lbl_8031BDD4.mUnknown32 = value;
                lbl_8031BDD4.mUnknown36 = 0;
            }
            break;
        }
        case 2: {
            int enable = 1;
            fn_801485EC(2);
            // FAKEMATCH: reused local; the outer switch's type holds mPes[2], then mPes[3]
            type = lbl_803EA5C8->mPes[2];
            if (type == 2) {
                enable = 0;
            }
            fn_80148A58()->vfn_07(0, enable);
            type = lbl_803EA5C8->mPes[3];
            fn_80148A58()->vfn_07(1, type);
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
    case 4:
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
    case 4:
        break;
    }
    return value;
}

void fn_8005E798(void)
{
    int value = GameOptionsGet(0);

    StorySetLkss(lbl_802D4D40.mIndex, value);
    lbl_802D4D40.mUnknown1 = value;
}

void fn_8005E7E4(void)
{
    if (lbl_802D4D40.mUnknown1 < 0) {
        fn_8005E798();
    }
    StoryAddCompletedEvent(lbl_802D4D40.mIndex, lbl_803EA5C8->mNets);
    int total = 0;
    // FAKEMATCH: dead initializer; base is set again before its use
    int base = 0;
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
    StorySetDevPoints(lbl_802D4D40.mIndex, total);
    base = lbl_802D4D40.mUnknown8;
    int credits = lbl_803EA5C8->mCswr;
    lbl_802D4D40.mUnknown18 = credits;
    UserStatsSet(lbl_803EA5D0, 14, base + credits);
    UserInfoAddPoints(fn_8022F358(lbl_802D4D40.mIndex), lbl_803EA5C8->mCswr);
    lbl_8030A2AC.mDone[lbl_803EA5C8->mDive] = StoryAreGroupEventsCompleted(lbl_802D4D40.mIndex, lbl_803EA5C8->mDive);
    fn_8005D6EC();
}

int fn_8005E980(int dive, int droe, int *pLevel, int *pDone, int *pLocked, int count, char *pName, int size)
{
    StevRow_t row;
    StevRow_t first;
    int ites = 5;

    *pLevel = 0;
    *pLocked = 0;
    *pDone = 0;
    if (pName) {
        *pName = 0;
    }
    if (StevGetRow(dive, droe, &row)) {
        ites = row.mItes;
        if (pName) {
            strncpy(pName, row.mIuve, size);
        }
        *pLevel = ExpLevelGetForPoints(row.mQrxe);
        if (StoryIsEventCompleted(lbl_802D4D40.mIndex, row.mNets)) {
            *pDone = 1;
        } else if (row.mItes == 4) {
            StevGetRow(0, 0, &first);
            *pLocked = !StoryIsEventCompleted(lbl_802D4D40.mIndex, first.mNets);
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
        int count = all ? StevCountDiveRows(dive) : 1;
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
    int count = StevCountDiveRows(dive);

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
    // FAKEMATCH: local that only aliases the global buffer lbl_8030A1E4
    char *pText = lbl_8030A1E4;
    const char *pName;
    int completed;
    int length;

    pText[0] = 0;
    pName = "Story task";
    completed = 0;
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
    switch (lbl_802D4D40.mUnknown20) {
    case 1:
    case 2:
        fn_801C2E18(pText, "You have completed %s!", pName);
        completed = 1;
        break;
    // FAKEMATCH: empty case for a result value nothing stores; it sets the target's range-test order
    case 3:
        break;
    }
    length = strlen(pText);
    if (completed && (lbl_802D4D40.mUnknown14 || lbl_802D4D40.mUnknown18)) {
        fn_801C2E18(pText + length, "\nYou are rewarded");
        length = strlen(pText);
        if (lbl_802D4D40.mUnknown14) {
            fn_801C2E18(pText + length, "\n%d Dev Points", lbl_802D4D40.mUnknown14);
            length = strlen(pText);
        }
        if (lbl_802D4D40.mUnknown18) {
            fn_801C2E18(pText + length, "\n%d Credits", lbl_802D4D40.mUnknown18);
            length = strlen(pText);
        }
    }
    if (fn_8005EBF0(lbl_803EA5C8->mDive)) {
        int dive = fn_8005EB20(0);
        if (dive != 12) {
            EnvSelect(dive);
            EnvGetUIName(hero, 33);
            EnvRelease();
            length = strlen(pText);
        }
    }
}

void fn_8005EEC4(int *pState, int *pScreen)
{
    StevRow_t first;
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
        StorySetNew(lbl_802D4D40.mIndex, 0);
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
            StevGetRow(0, 0, &first);
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
                // FAKEMATCH: the *pState = 2 store is repeated in both arms instead of once before the test
                if (dive == 12) {
                    *pState = 2;
                    *pScreen = fn_8005D804(0);
                } else {
                    *pState = 2;
                    *pScreen = fn_8005D804(dive);
                }
            } else {
                *pState = 3;
                // FAKEMATCH: goto shares the screen store below; it sets the target's register choice
                goto current;
            }
        } else if (lbl_803EA5C8) {
            *pState = 3;
        current:
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
    FELoopResetIdle();
}

void fn_8005F13C(int state, int screen)
{
    if (lbl_803EA5B8) {
        fn_8005D764(0);
        if (MsgGameGetSetupState() == 0) {
            fn_8005D818();
        } else if (MsgGameGetSetupState() == 1 && lbl_803EA5C8) {
            FELoopSetResume(1);
            fn_8005E4A8();
        }
        fn_8005D60C();
        lbl_802D4D40.mUnknown20 = 0;
        lbl_803EA5B8 = 0;
    }
    if (MsgGameGetSetupState() == 0) {
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
    *pCount = StevCountDiveRows(dive);
    if (dive == 0 && !fn_8005D94C()) {
        (*pCount)--;
    }
}

int fn_8005F24C(int dive, int droe)
{
    int value = 100;

    if (StevGetRow(dive, droe, &lbl_8030A13C)) {
        lbl_803EA5C8 = &lbl_8030A13C;
        value = fn_8005E728();
    }
    return value;
}

void fn_8005F29C(void)
{
    StevRow_t row;
    int dive;

    fn_80010150(7);
    fn_8005D660();
    fn_8005D6EC();
    for (dive = 0;; dive++) {
        if (dive <= 11) {
            StevGetRow(dive, 0, &row);
            if (row.mQrxe != 0) {
                continue;
            }
        } else {
            dive = 5;
        }
        break;
    }
    fn_8005F24C(dive, 0);
    FELoopSetResume(1);
    fn_8005E4A8();
    fn_8005D60C();
}

void fn_8005F324(int id)
{
    switch (id) {
    case 0:
        break;
    case 113:
        EditMenuBegin(4, 0x3FF);
        break;
    case 900:
        EditMenuBegin(2, 0x3FF);
        break;
    case 603:
        fn_80061AE8();
    case 109:
        MsgTeamPickRequestTeamSave();
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
    int value = 0;

    *pResult = TeamLogoGetHandle(-1);
    DbCursor cursor;
    StoryTeamCursorOpen(&cursor, lbl_802D4D40.mIndex);
    if (DbCursorGetRowCount(&cursor) > 0) {
        value = StoryTeamGetLogo(&cursor);
        if (DbCursorGetInt(&cursor, 0x4C445443) == 0) {
            unsigned char color[3];
            color[0] = DbCursorGetInt(&cursor, 0x31434D54);
            color[1] = DbCursorGetInt(&cursor, 0x32434D54);
            color[2] = DbCursorGetInt(&cursor, 0x33434D54);
            TeamLogoRequestTint(0, 4, value, 0xAC, color);
            *pResult = TeamLogoGetHandle(0);
        }
    }
    StoryTeamCursorClose(&cursor);
    return value;
}

void fn_8005F4EC(char *pName, int size)
{
    unsigned int last = size - 1;
    *pName = 0;
    DbCursor cursor;
    char buffer[64];
    unsigned int length;

    StoryPlayerCursorOpen(&cursor, lbl_802D4D40.mIndex);
    buffer[0] = 0;
    if (!StoryPlayerGetLastName(&cursor, 0, buffer, sizeof(buffer))) {
        *pName = 0;
    }
    buffer[last] = 0;
    length = strlen(buffer);
    buffer[0] = 0;
    if (!StoryPlayerGetFirstName(&cursor, 0, buffer, sizeof(buffer))) {
        *pName = 0;
    } else {
        buffer[last] = 0;
        unsigned int first = strlen(buffer);
        length = length + first + 1;
        if (length < last - 1) {
            buffer[first] = ' ';
            first++;
            StoryPlayerGetLastName(&cursor, 0, buffer + first, sizeof(buffer) - first);
            buffer[length] = 0;
        }
    }
    if (*pName == 0) {
        StoryPlayerGetShortName(&cursor, 0, pName, last);
        if (*pName == 0) {
            strncpy(pName, "your hero", last);
            goto done;
        }
    }
    strncpy(pName, buffer, last);
done:
    pName[last] = 0;
    StoryPlayerCursorClose(&cursor);
}

void fn_8005F664(char *pName, int size)
{
    *pName = 0;
    int last = size - 1;
    DbCursor cursor;

    StoryTeamCursorOpen(&cursor, lbl_802D4D40.mIndex);
    if (DbCursorGetRowCount(&cursor) > 0) {
        DbCursorSeek(&cursor, 0);
        DbCursorGetString(&cursor, 0x414E4454, (int)pName, last);
    }
    StoryTeamCursorClose(&cursor);
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
        scale = ExpLevelGetScft(lbl_802D4D40.mUnknown1C) * 0.001f;
        lbl_803EA5D4 = scale;
    } else {
        scale = lbl_803EA5D4;
    }
    return scale;
}

void fn_8005F7C4(Object_8008044C *pObject, int id, float scale)
{
    int found = PlayerDbSeekId(pObject, id, 0);
    int type = PlayerDbGetPrty(pObject);

    if ((type == 1 || type == 2) && found) {
        for (int i = 0; i < 10; i++) {
            unsigned int value = PlayerDbGetRating(pObject, lbl_802D4E00[i]);
            value -= (int)(value * scale);
            if (value > 100) {
                value = 100;
            }
            value = value < 5 ? 5 : value;
            PlayerDbSetRating(pObject, lbl_802D4E00[i], value);
        }
    }
}

void fn_8005F8B4(Args_8005F8B4 *pArgs)
{
    Text_8005F8B4 *pDest = pArgs->mpText;
    char *pText = pDest->mpText;
    int size = pDest->mSize;

    *pText = 0;
    strncpy(pText, lbl_8030A1E4, size);
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
    return StoryIsNew(fn_8022F384(fn_8022F4BC()));
}

int fn_8005F938(unsigned int id, int *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8005EEC4((int *)pArgs[0], (int *)pArgs[1]);
        break;
    case 0x80000002:
        fn_8005F13C(pArgs[0], pArgs[1]);
        break;
    case 0x80000003: {
        int *pCount = (int *)pArgs[1];
        int dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pCount = 0;
        } else {
            fn_8005F1F8(dive, pCount);
        }
        break;
    }
    case 0x80000004: {
        int dive = fn_8005D7F0(pArgs[0]);
        int droe = pArgs[1];
        int *pLevel = (int *)pArgs[2];
        int *pDone = (int *)pArgs[4];
        int *pLocked = (int *)pArgs[5];
        if (dive == 12) {
            *pLevel = 0;
            *pDone = 1;
            *pLocked = 1;
        } else {
            int count = StevCountDiveRows(dive);
            Text_8005F8B4 *pText = (Text_8005F8B4 *)pArgs[3];
            fn_8005E980(dive, droe, pLevel, pDone, pLocked, count, pText->mpText, pText->mSize);
        }
        break;
    }
    case 0x80000005: {
        int dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pResult = 1;
        } else {
            *pResult = fn_8005EBF0(dive);
        }
        break;
    }
    case 0x80000006: {
        int dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pResult = 100;
        } else {
            *pResult = fn_8005F24C(dive, pArgs[1]);
        }
        break;
    }
    case 0x8000000C:
        *pResult = lbl_803EA5E4;
        break;
    case 0x182: {
        int found = ExpLevelGetName(lbl_802D4D40.mUnknown1C, ((Text_8005F8B4 *)pArgs[0])->mpText,
                                    ((Text_8005F8B4 *)pArgs[0])->mSize);
        *pResult = lbl_802D4D40.mUnknown1C;
        if (!found) {
            strncpy(((Text_8005F8B4 *)pArgs[0])->mpText, "", ((Text_8005F8B4 *)pArgs[0])->mSize);
        }
        break;
    }
    case 0x80000007:
        fn_8005F324(pArgs[0]);
        break;
    case 0x11A:
        fn_8005F324(113);
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
    case 0x17B:
    {
        int *pLogo = (int *)pArgs[0];
        *pResult = *pLogo = fn_8005F3E4((int *)pArgs[1]);
        break;
    }
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
    case 0x8000000B: {
        int dive = fn_8005D7F0(pArgs[0]);
        if (dive == 12) {
            *pResult = 1;
        } else {
            *pResult = fn_8005EC14(dive);
        }
        break;
    }
    default:
        return 0;
    }
    return 1;
}

StevRow_t *fn_8005FC7C(void)
{
    return lbl_803EA5C8;
}

int fn_8005FC84(void)
{
    int active;

    if (!lbl_803EA5C8) {
        active = 0;
    } else {
        int result = fn_80178AE0();
        active = 1;
        switch (result) {
        case 0:
            lbl_8030A1A0.mUnknown8 = 2;
            break;
        case 1:
            lbl_8030A1A0.mUnknown8 = 1;
            break;
        default:
            lbl_8030A1A0.mUnknown8 = 3;
            break;
        }
    }
    return active;
}

void fn_8005FCF8(int *pFirst, int *pSecond)
{
    int ids[13];
    int itgt[13];
    int count;
    int i;
    unsigned char secondSide;
    unsigned char firstSide;

    int n = 0;
    for (i = 1; i <= 6; i++) {
        ids[n++] = pSecond[i];
    }
    for (i = 0; i < 7; i++) {
        ids[n++] = pFirst[i];
    }
    {
        Object_8008044C object;
        int found = 0;
        fn_8008044C(&object, 0, 0x54415453);
        for (i = 0; i <= 12; i++) {
            if (PlayerDbSeekId(&object, ids[i], 0)) {
                itgt[found++] = DbCursorGetInt(&object, 0x49544754);
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
        DbCursor cursor;
        if (GameInfoGet(2) == 0) {
            secondSide = 1;
            firstSide = 0;
        } else {
            secondSide = 0;
            firstSide = 1;
        }
        DbCursorOpen(&cursor, lbl_803EA5D8, 0x44494750, 0, 0, 0x54415453);
        for (i = 1; i <= 6; i++) {
            if (PlayerDbSeekId((Object_8008044C *)&cursor, pSecond[i], 0)) {
                fn_80081F50((Object_8008044C *)&cursor, secondSide, 1);
            }
        }
        for (i = 0; i <= 6; i++) {
            if (PlayerDbSeekId((Object_8008044C *)&cursor, pFirst[i], 0)) {
                fn_80081F50((Object_8008044C *)&cursor, firstSide, 1);
            }
        }
        DbCursorClose(&cursor);
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
    case 5:
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
    StevRow_t *pRow = lbl_803EA5C8;

    if (pRow && (pRow->mItes == 0 || (pRow->mItes == 1 && pRow->mQrxe != 0)) && lbl_8030A1A0.mUnknown8 == 1) {
        return 1;
    }
    return 0;
}

void fn_80060330(int group, int *pIds, int count, Object_8008044C *pObject)
{
    fn_8005E010(group, pIds, count, pObject, 0);
}

int fn_80060354(StevRow_t *pRow, int *pList)
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
    int ppxe[4] = {16, 39, 63, 72};
    StevRow_t row;
    unsigned int mask = 0;
    StevRow_t *pSaved;
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
        StorySetExpPoints(index, ppxe[level]);
        break;
    }
    StevOpen();
    pSaved = lbl_803EA5C8;
    for (dive = 0; dive <= 11; dive++) {
        if (mask & (1 << dive)) {
            lbl_803EA5C8 = &row;
            int count = StevCountDiveRows(dive);
            for (int droe = 0; droe < count; droe++) {
                StevGetRow(dive, droe, &row);
                if (!StoryIsEventCompleted(index, row.mNets)) {
                    StoryAddCompletedEvent(index, row.mNets);
                }
            }
        }
    }
    StorySetNew(index, 0);
    StevClose();
    lbl_803EA5C8 = pSaved;
}

void fn_8006059C(int index)
{
    StevRow_t row;
    StevRow_t *pSaved;
    int dive;

    StevOpen();
    pSaved = lbl_803EA5C8;
    for (dive = 0; dive <= 11; dive++) {
        lbl_803EA5C8 = &row;
        int count = StevCountDiveRows(dive);
        for (int droe = 0; droe < count; droe++) {
            if (dive == 0 && droe == count - 1) {
                continue;
            }
            StevGetRow(dive, droe, &row);
            if (!StoryIsEventCompleted(index, row.mNets)) {
                StoryAddCompletedEvent(index, row.mNets);
            }
        }
    }
    StorySetNew(index, 0);
    StevClose();
    lbl_803EA5C8 = pSaved;
}

void fn_80060674(int index)
{
    StoryClearCompletedEvents(index);
    StorySetExpPoints(index, 0);
    StoryClearFlags(index);
    StorySetNew(index, 1);
    StorySetLkss(index, -1);
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
        case 3:
        case 9:
            id = pList[6];
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
        pObject = PlyrFindByPoid(id);
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
