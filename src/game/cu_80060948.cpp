#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/cu_80181330.h"
#include "game/DepthChart.h"
#include "game/StevTable.h"
#include "game/fn_80061AD4.h"
#include "game/StoryTeam.h"
#include "game/GameOptions.h"
#include "game/fn_801FCE10.h"
#include "game/FELoop.h"

/* Teams and round of the current match, set by fn_80061520. */
struct Match_8030A3A4 {
    int mDit1;
    int mDit2;
    int mLvlt;
};

/* Values saved by fn_800611C0 and restored by fn_80061154. */
struct Saved_802D4E28 {
    int mValue0;
    int mValue1;
    int mValue14;
    unsigned char mSaved;
};

/* Index returned by fn_8022F384, and whether fn_80060B0C opened the 'PDFN'
   database; while it is open, queries skip their own open and close. */
struct State_803EA5F8 {
    signed char mIndex;
    signed char mUnknown1;
    short mUnknown2;
    short mOpen;
};

struct Block_800619FC {
    int *mpGame;
    int *mpDit2;
    int *mpDit1;
    Params_80005284 *mpName2;
    Params_80005284 *mpName1;
    int *mpUnknown20;
    int *mpUnknown24;
    int *mpWinner;
};

extern "C" {
int fn_8000FCCC(void);
int fn_8000FCDC(void);
void fn_80010150(int a);
void fn_80011600(int a, int b, int c);
void fn_80015D28(int a);
void MsgTeamPickSetMode(int a, int b);
void MsgTeamPickSetSources(int a);
void fn_8005BE54(unsigned char value);
int fn_80060354(StevRow_t *pRow, int *pList);
void fn_80060410(int index, int *pList);
void GameInfoSet(int index, int value);
void fn_80084A8C(int a, int *pList, int b, int c);
int FormationGetByIndex(int a, int b);
int *FormationLineupFetchUser(int a, int b);
int fn_80085C94(int a, int *pList);
int ExpLevelClose(void);
int ExpLevelOpen(void);
int TournamentSetPlayersTeam(int *pDigp, int count, int munt, int digt);
int TournamentGetTeamPlayers(int digt, int *pList);
int TournamentClearPlayers(void);
int TournamentGetLevelMatchCount(int lvlt);
int TournamentGetMatch(int lvlt, int row, int *pDit1, int *pDit2, int *pTniw);
int TournamentSetMatchWinner(int lvlt, int dit1, int dit2, int tniw);
int TournamentClearMatches(void);
int TournamentGetMatchCount(void);
int TournamentGetTeamList(int *pList);
int TournamentGetRoundCount(int size);
int TournamentClose(void);
int TournamentOpen(int index);
void UserStatsOpen(DbCursor *pObject, int index);
void UserStatsClose(DbCursor *pObject);
int fn_80178AE0(void);
int MsgGameGetSetupState(void);
void fn_80186F30(signed char a, int b);
void fn_8018C48C(int tag);
int StoryGetLkss(int a);
char *strncpy(char *pDest, const char *pSource, int count);
int fn_8022C8F0(unsigned int low, unsigned int high);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
}

Object_8008044C lbl_8030A2BC;
DbCursor lbl_8030A2E8;
DbCursor lbl_8030A314;
StevRow_t lbl_8030A340;
Match_8030A3A4 lbl_8030A3A4;

static unsigned char lbl_803EA5E8 = 0;
static StevRow_t *lbl_803EA5EC = 0;
static Object_8008044C *lbl_803EA5F0 = 0;
static DbCursor *lbl_803EA5F4 = 0;
static State_803EA5F8 lbl_803EA5F8 = {0, -1, 0, 0};

static Saved_802D4E28 lbl_802D4E28 = {-1, 0, 0, 0};

/* Round ('LVLT') and row of each of the 15 bracket games. */
static int lbl_802D4E38[15] = {1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
static int lbl_802D4E74[15] = {0, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7};

extern "C" {
void fn_80060948(int id, char *pName, int size);
int fn_800609EC(int team, int lvlt);
void fn_80060A9C(void);
void fn_80060B0C(void);
void fn_80060BB4(void);
void fn_80060BE0(void);
int fn_80060C14(int game, int *pLvlt, int *pRow);
int fn_80060C94(void);
void fn_80060CD4(void);
int fn_80060E7C(void);
int fn_8006102C(void);
void fn_80061088(int *pDit1, int *pDit2, int *pLvlt);
void fn_80061154(void);
void fn_800611C0(int value14, int value1);
int fn_80061390(int digt);
int fn_80061408(int digt);

#if defined(DECOMP_COMPARE)
void fn_80060948(int id, char *pName, int size)
{
    char name[18];

    if (id < 0) {
        *pName = 0;
        return;
    }
    if (fn_80084034(&lbl_8030A314, id, 0) == 0) {
        strncpy(pName, "NFL Draft Team", size);
    } else {
        DbCursorGetString(&lbl_8030A314, 0x414E4454, (int)name, sizeof(name));
        name[17] = 0;
        strncpy(pName, name, size);
    }
}

/* Row of the next round's game that the team won, or 0. */
int fn_800609EC(int team, int lvlt)
{
    int dit1;
    int dit2;
    int tniw;
    int next;
    int count;
    int row;

    if (lvlt <= 3) {
        next = lvlt + 1;
        count = 1 << next;
        for (row = 0; row < count; row++) {
            if (TournamentGetMatch(next, row, &dit1, &dit2, &tniw)) {
                if ((dit1 == team && tniw == 1) || (dit2 == team && tniw == 2)) {
                    return row;
                }
            }
        }
    }
    return 0;
}

void fn_80060A9C(void)
{
    fn_80083F68(&lbl_8030A314);
    if (lbl_803EA5F8.mOpen) {
        TournamentClose();
        lbl_803EA5F8.mOpen = 0;
    }
    ExpLevelClose();
    fn_8008056C(lbl_803EA5F0);
    lbl_803EA5F0 = 0;
    StevClose();
    UserStatsClose(lbl_803EA5F4);
    lbl_803EA5F4 = 0;
}

void fn_80060B0C(void)
{
    lbl_803EA5F8.mIndex = fn_8022F384(fn_8022F4BC());
    lbl_803EA5F0 = &lbl_8030A2BC;
    fn_8008044C(&lbl_8030A2BC, 0, 0x54415453);
    StevOpen();
    ExpLevelOpen();
    lbl_803EA5F8.mUnknown2 = 0x7FFF;
    lbl_803EA5F4 = &lbl_8030A2E8;
    UserStatsOpen(&lbl_8030A2E8, lbl_803EA5F8.mIndex);
    lbl_803EA5F8.mOpen = TournamentOpen(lbl_803EA5F8.mIndex);
    fn_80083E40(&lbl_8030A314, 0, 0x54415453);
}

void fn_80060BB4(void)
{
    lbl_803EA5F8.mUnknown1 = StoryGetLkss(lbl_803EA5F8.mIndex);
}

void fn_80060BE0(void)
{
    fn_8018C48C(0x54415453);
    fn_8018C48C(0x454D4147);
}

int fn_80060C14(int game, int *pLvlt, int *pRow)
{
    if (game >= 0 && game <= 14) {
        *pLvlt = lbl_802D4E38[game];
        *pRow = lbl_802D4E74[game];
        return 1;
    }
    return 0;
}

/* Winner ('TNIW') of a game the player does not take part in. */
int fn_80060C50(int dit1, int dit2)
{
    if (dit1 == 0x31) {
        return 1;
    }
    if (dit2 == 0x31) {
        return 2;
    }
    return fn_8022C8F0(1, 3);
}

int fn_80060C94(void)
{
    int teams[8];
    int team = 0;

    if (TournamentGetTeamList(teams) == 8) {
        team = teams[0];
    }
    return team;
}

/* Draws the first round of the bracket. */
void fn_80060CD4(void)
{
    int teams[8];
    int order[8];
    int i;
    int j;
    int tmp;
    int first;
    int second;
    int lvlt;
    int team;
    int dit1;
    int dit2;
    int half = 4;

    TournamentGetTeamList(teams);
    for (i = 0; i < 8; i++) {
        order[i] = i;
    }
    for (i = 0; i <= 7; i++) {
        do {
            j = fn_8022C8F0(0, 8);
        } while (j == i);
        int swap = order[i];
        order[i] = order[j];
        order[j] = swap;
    }
    first = 0;
    while (first < 8 && teams[order[first]] != 0x2E) {
        first++;
    }
    second = 0;
    while (second < 8 && teams[order[second]] != 0x31) {
        second++;
    }
    if (second < half) {
        if (first < half) {
            tmp = order[second];
            order[second] = order[second + half];
            order[second + half] = tmp;
        }
    } else if (first >= half) {
        tmp = order[second];
        order[second] = order[second - half];
        order[second - half] = tmp;
    }
    lvlt = TournamentGetRoundCount(8);
    team = fn_80060C94();
    for (i = 0; i < 8; i += 2) {
        dit1 = teams[order[i]];
        dit2 = teams[order[i + 1]];
        if (dit1 == team) {
            dit1 = dit2;
            dit2 = team;
        }
        TournamentSetMatchWinner(lvlt, dit1, dit2, 0);
    }
}

/* Records the current match as won by its second team and plays the rest of
   the round. Returns 1 when that match was the final. */
int fn_80060E7C(void)
{
    int dit1;
    int dit2;
    int tniw;
    int lvlt = lbl_8030A3A4.mLvlt;
    int done = 0;
    int count;
    int row;
    int team;
    int winner1;
    int winner2;
    int next;
    int games;

    dit1 = lbl_8030A3A4.mDit1;
    dit2 = lbl_8030A3A4.mDit2;
    TournamentSetMatchWinner(lvlt, dit1, dit2, 2);
    if (lvlt == 1) {
        TournamentSetMatchWinner(0, dit2, dit2, 2);
        done = 1;
    } else {
        row = 0;
        count = TournamentGetLevelMatchCount(lvlt);
        next = lvlt - 1;
        for (; row < count; row++) {
            if (TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw) && tniw == 0) {
                tniw = fn_80060C50(dit1, dit2);
                TournamentSetMatchWinner(lvlt, dit1, dit2, tniw);
            }
        }
        team = fn_80060C94();
        games = TournamentGetLevelMatchCount(lvlt);
        for (row = 0; row < games; row += 2) {
            TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw);
            if (tniw == 1) {
                winner1 = dit1;
            } else {
                winner1 = dit2;
            }
            TournamentGetMatch(lvlt, row + 1, &dit1, &dit2, &tniw);
            if (tniw == 1) {
                winner2 = dit1;
            } else {
                winner2 = dit2;
            }
            if (winner1 == team) {
                winner1 = winner2;
                winner2 = team;
            }
            TournamentSetMatchWinner(next, winner1, winner2, 0);
        }
    }
    return done;
}

int fn_8006102C(void)
{
    int dit1;
    int dit2;
    int tniw;
    int done = 0;

    if (TournamentGetMatch(0, 0, &dit1, &dit2, &tniw)) {
        done = tniw == 2;
    }
    return done;
}

/* Finds the player's game in the earliest round that has games. */
void fn_80061088(int *pDit1, int *pDit2, int *pLvlt)
{
    int tniw;
    int last = TournamentGetRoundCount(8);
    int lvlt = 1;
    int team = fn_80060C94();
    int count = last + 1;
    int row;

    for (; lvlt <= last; lvlt++) {
        count = TournamentGetLevelMatchCount(lvlt);
        if (count > 0) {
            break;
        }
    }
    if (lvlt > 0 && lvlt <= last) {
        for (row = 0; row < count; row++) {
            if (TournamentGetMatch(lvlt, row, pDit1, pDit2, &tniw) && *pDit2 == team) {
                *pLvlt = lvlt;
                break;
            }
        }
    }
}

void fn_80061154(void)
{
    if (lbl_802D4E28.mSaved) {
        GameOptionsSet(14, lbl_802D4E28.mValue14);
        GameOptionsSet(1, lbl_802D4E28.mValue1);
        if (lbl_802D4E28.mValue0 > -1) {
            GameOptionsSet(0, lbl_802D4E28.mValue0);
        }
        lbl_802D4E28.mSaved = 0;
    }
}

void fn_800611C0(int value14, int value1)
{
    if (!lbl_802D4E28.mSaved) {
        lbl_802D4E28.mSaved = 1;
        lbl_802D4E28.mValue14 = GameOptionsGet(14);
        lbl_802D4E28.mValue1 = GameOptionsGet(1);
        if (lbl_803EA5F8.mUnknown1 > -1) {
            lbl_802D4E28.mValue0 = GameOptionsGet(0);
        } else {
            lbl_802D4E28.mValue0 = lbl_803EA5F8.mUnknown1;
        }
    }
    GameOptionsSet(14, value14);
    GameOptionsSet(1, value1);
    if (lbl_803EA5F8.mUnknown1 > -1) {
        GameOptionsSet(0, lbl_803EA5F8.mUnknown1);
    }
}

void fn_80061274(int a, int *pList, int count, Object_8008044C *pObject)
{
    int *pSlots = 0;
    int list;
    int i;
    int id;
    int slot;
    int j;
    int tmp;

    list = FormationGetByIndex(0, 1);
    if (list) {
        pSlots = FormationLineupFetchUser(list, a);
    }
    if (pSlots) {
        for (i = 0; i < count; i++) {
            id = pList[i];
            if (!PlayerDbSeekId(pObject, id, 0)) {
                continue;
            }
            slot = PlayerDbGetPbpo(pObject);
            if (pSlots[slot] == id) {
                continue;
            }
            if (slot <= 6) {
                for (j = 0; j <= 6; j++) {
                    if (pSlots[j] == id) {
                        tmp = pSlots[slot];
                        pSlots[slot] = pSlots[j];
                        pSlots[j] = tmp;
                        break;
                    }
                }
            } else {
                for (j = 7; j <= 13; j++) {
                    if (id == pSlots[j]) {
                        tmp = pSlots[slot];
                        pSlots[slot] = pSlots[j];
                        pSlots[j] = tmp;
                        break;
                    }
                }
            }
        }
        fn_80085C94(a, pSlots);
    }
}

int fn_80061390(int digt)
{
    int list[14];

    TournamentGetTeamPlayers(digt, list);
    fn_80060354(lbl_803EA5EC, list);
    list[7] = 0x7FFF;
    fn_80060410(0, list);
    DepthChartAutoFill(0, list, 4);
    fn_80084A8C(digt, list, 0, 7);
    return digt;
}

int fn_80061408(int digt)
{
    StoryTeamIdBlock_t picks;
    int list[14];
    int digt2;
    int count;
    int i;

    digt2 = StoryTeamLoadOneToStats(lbl_803EA5F8.mIndex, 1, &picks);
    if (PlayerDbSeekId(lbl_803EA5F0, picks.mUnknown0, 0)) {
        DbCursorSetInt(lbl_803EA5F0, 0x44494F50, picks.mUnknown0);
        DbCursorSetInt(lbl_803EA5F0, 0x44494754, digt2);
    }
    count = TournamentGetTeamPlayers(digt, list);
    for (i = 0; i < count && list[i] != picks.mUnknown0; i++) {
    }
    list[7] = 0x7FFF;
    fn_80060410(1, list);
    DepthChartAutoFill(1, list, 4);
    fn_80061274(1, &picks.mUnknown0, 1, lbl_803EA5F0);
    fn_80084A8C(digt, list, 1, 7);
    return digt;
}
#endif

void fn_80061520(int dit1, int dit2, int lvlt)
{
    DepthChartLoad(1);
    dit2 = fn_80061408(dit2);
    lbl_8030A3A4.mDit1 = fn_80061390(dit1);
    lbl_8030A3A4.mDit2 = dit2;
    lbl_8030A3A4.mLvlt = lvlt;
    DepthChartSave();
}

void fn_80061584(void)
{
    int dit1;
    int dit2;
    int lvlt;
    int saved = fn_8000FCDC();

    fn_800611C0(0, 0x24);
    if (TournamentGetLevelMatchCount(1) == 0) {
        lbl_803EA5EC->mCsos = -1;
    }
    fn_80061088(&dit1, &dit2, &lvlt);
    fn_80061520(dit1, dit2, lvlt);
    if (lbl_803EA5EC->mDive) {
        lbl_803EA5EC->mDive = 0;
    }
    fn_80011600(-1, fn_8000FCCC(), saved);
    fn_80186F30(lbl_803EA5F8.mIndex, 1);
    GameInfoSet(2, 1);
    fn_80015D28(lbl_803EA5EC->mDive);
}

int fn_8006164C(void)
{
    return TournamentGetMatchCount() > 0;
}

int fn_8006167C(void)
{
    int result = 100;

    if (StevGetRow(0, StevCountDiveRows(0) - 1, &lbl_8030A340)) {
        result = 123;
        lbl_803EA5EC = &lbl_8030A340;
    }
    return result;
}

void fn_800616D8(void)
{
    switch (lbl_803EA5EC->mItes) {
    case 0:
    case 1:
    case 2:
    case 3:
        break;
    case 4:
        fn_8006164C();
        fn_80061584();
        break;
    }
}

void fn_8006171C(int game, int *pDit1, int *pUnknown5, int *pDit2, int *pUnknown7, int *pWinner)
{
    int lvlt;
    int row;
    int dit1 = -1;
    int dit2 = -1;
    int tniw;
    int found;

    *pUnknown5 = -1;
    *pUnknown7 = -1;
    *pWinner = -1;
    *pDit1 = -1;
    *pDit2 = -1;
    if (fn_80060C14(game, &lvlt, &row)) {
        found = TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw);
        if (found) {
            *pDit1 = dit1;
            *pDit2 = dit2;
            switch ((unsigned int)tniw) {
            case 0:
                break;
            case 1:
                *pWinner = 0;
                break;
            case 2:
                *pWinner = 1;
                break;
            }
        }
        if (found && lvlt < lbl_802D4E38[14]) {
            if (fn_800609EC(dit1, lvlt) < fn_800609EC(dit2, lvlt)) {
                *pDit2 = dit1;
                *pDit1 = dit2;
            }
        }
    }
}

/* Starts the tournament on first use and returns the player's open game. */
void fn_8006182C(int *pGame)
{
    int lvlt;
    int row;
    int dit1;
    int dit2;
    int tniw;
    int game;

    *pGame = 0;
    if (!lbl_803EA5E8) {
        fn_80010150(10);
        fn_80060BE0();
        fn_80060B0C();
        fn_80061154();
        fn_80060BB4();
        if (!fn_8006164C()) {
            fn_80060CD4();
        }
        lbl_803EA5EC = 0;
        lbl_803EA5E8 = 1;
        FELoopResetIdle();
    }
    for (game = 0; game <= 14; game++) {
        if (fn_80060C14(game, &lvlt, &row) && TournamentGetMatch(lvlt, row, &dit1, &dit2, &tniw) && tniw == 0 &&
            (dit1 == 0x2E || dit2 == 0x2E)) {
            *pGame = game;
        }
    }
}

void fn_80061918(void)
{
    if (lbl_803EA5E8) {
        if (!fn_8006102C()) {
            if (MsgGameGetSetupState() == 0) {
                fn_80060BE0();
                lbl_803EA5EC = 0;
            } else if (MsgGameGetSetupState() == 1) {
                FELoopSetResume(1);
                fn_8006167C();
                fn_800616D8();
            }
        }
        fn_80060A9C();
        lbl_803EA5E8 = 0;
    }
    fn_8005BE54(0);
}

int fn_8006199C(void)
{
    int done = 0;

    if (lbl_803EA5EC) {
        fn_80060B0C();
        if (!fn_8006102C()) {
            fn_80060E7C();
        }
        if (fn_8006102C()) {
            done = 1;
        }
        fn_80060A9C();
    }
    return done;
}

int fn_800619FC(unsigned int id, Block_800619FC *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8006182C(pBlock->mpGame);
        break;
    case 0x80000002:
        fn_80061918();
        break;
    case 0x80000003: {
        int *pDit2 = pBlock->mpDit2;
        int *pDit1 = pBlock->mpDit1;

        fn_8006171C((int)pBlock->mpGame, pDit1, pBlock->mpUnknown24, pDit2, pBlock->mpUnknown20, pBlock->mpWinner);
        fn_80060948(*pDit1, pBlock->mpName1->mpText, pBlock->mpName1->mLength);
        fn_80060948(*pDit2, pBlock->mpName2->mpText, pBlock->mpName2->mLength);
        break;
    }
    default:
        return 0;
    }
    return 1;
}

StevRow_t *fn_80061AD4(void)
{
    return lbl_803EA5EC;
}

void fn_80061ADC(void)
{
    lbl_803EA5EC = 0;
}

void fn_80061AE8(void)
{
    int saved = fn_8000FCDC();

    fn_8006167C();
    fn_80011600(-1, fn_8000FCCC(), saved);
    fn_80186F30(lbl_803EA5F8.mIndex, 1);
    if (lbl_803EA5F8.mOpen == 0) {
        lbl_803EA5F8.mIndex = fn_8022F384(fn_8022F4BC());
        TournamentOpen(lbl_803EA5F8.mIndex);
    }
    TournamentClearMatches();
    TournamentClearPlayers();
    if (lbl_803EA5F8.mOpen == 0) {
        TournamentClose();
    }
    MsgTeamPickSetMode(2, 0);
    MsgTeamPickSetSources(1);
}

void fn_80061B90(int team, int *pDigp)
{
    int teams[8];
    int munt = 0;
    int i;

    fn_80060B0C();
    TournamentGetTeamList(teams);
    for (munt = 0; munt <= 7 && teams[munt] != team; munt++) {
    }
    if (team == fn_80060C94()) {
        for (i = 0; i <= 6 && pDigp[i] != 0; i++) {
        }
    }
    TournamentSetPlayersTeam(pDigp, 7, munt, team);
    fn_80060A9C();
}

int fn_80061C44(void)
{
    int result;

    if (lbl_803EA5F8.mOpen == 0) {
        TournamentOpen(lbl_803EA5F8.mIndex = fn_8022F384(fn_8022F4BC()));
    }
    result = fn_8006164C();
    if (lbl_803EA5F8.mOpen == 0) {
        TournamentClose();
    }
    return result;
}

int fn_80061CAC(void)
{
    int result;

    if (lbl_803EA5F8.mOpen == 0) {
        TournamentOpen(lbl_803EA5F8.mIndex = fn_8022F384(fn_8022F4BC()));
    }
    result = fn_8006102C();
    if (lbl_803EA5F8.mOpen == 0) {
        TournamentClose();
    }
    return result;
}

int fn_80061D14(void)
{
    int result;

    if (lbl_803EA5EC == 0) {
        result = 0;
    } else {
        int state = fn_80178AE0();
        result = 1;
        if (state == 1) {
            fn_8006199C();
        }
    }
    return result;
}

void fn_80061D64(int index)
{
    fn_801FCE10(0,
                "use \x8c insert into 'LTFN' set 'TNIW' = 2 and 'LVLT' = 0 and '1DIT' = 1 and '2DIT' = 2\n",
                fn_8022F3D4(fn_8022F358(index)));
}

void fn_80061DA0(int index)
{
    fn_801FCE10(0, "use \x8c delete from 'LTFN' where ('TNIW' = 2)\n", fn_8022F3D4(fn_8022F358(index)));
}

void fn_80061DDC(void)
{
    lbl_803EA5EC = 0;
}

int fn_80061DE8(void)
{
    int count = 0;

    fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LTFN'\n", fn_8022F3D4(fn_8022F4BC()), &count);
    return count;
}
}
