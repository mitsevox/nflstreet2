/* Team pick screen: before a pick-up game the captains take turns choosing
   players from a pool onto their teams. The pool is filled from the player
   database by position group (or from the tournament's draft pools, or with
   newly created players), shown one position group at a time, and the
   computer can choose for a captain. When the screen closes the picked teams
   get their depth charts and, when asked, are saved as new teams. */

#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/DepthChart.h"
#include "game/AutoDepth.h"
#include "game/GameInfo.h"
#include "game/cu_80181330.h"
#include "game/DepthChartSide.h"
#include "game/fn_80061AD4.h"
#include "game/fn_80178D18.h"
#include "game/GameModeType.h"
#include "game/StoryTeam.h"
#include "game/StevTable.h"
#include "game/fn_801C1F94.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/fn_802372EC.h"

/* Pick state allocated by MsgTeamPickAllocState (0x1C bytes) and freed by
   MsgTeamPickFreeState: mCount pick lists of mSize player ids, with a pick
   count and a controller byte (0xFF when unset) per list, followed by the
   per-side placed counts and the byte-sized turn and display state. */
struct TeamPickState_t {
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

/* One 0x18-byte row of the player pool _MsgTeamPick_pPool (_MsgTeamPick_iPoolCount
   rows): a player id, the slot it fills (negative while unpicked) and the team
   it went to. */
struct TeamPickPlayer_t {
    int mId;
    int mSlot;
    int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
    unsigned char mTeam;
    unsigned char mUnknown15;
};

/* One entry of _MsgTeamPick_aCaptain: a captain's player id and the team id it
   belongs to. */
struct TeamPickCaptain_t {
    int mValue;
    int mKey;
};

/* Pointer list read by DepthChartGetSideNames (src/game/DepthChart.cpp). */
struct DepthChartText_t;

extern "C" {
void fn_80015D28(int id);
void FESndUpdate(int a);
void DepthChartCyclePending(int group, int kind, int slot, int code, int a, int b);
void DepthChartRevertSide(int group);
void DepthChartGetSideNames(int group, int kind, DepthChartText_t **pPairs);
void DepthChartSwapPending(int group, int kind, int slot);
int DepthChartCommit(int group);
void fn_8003DE74(unsigned char side, int *pList);
int DepthChartScreenIsSideShown(unsigned char a);
void DepthChartScreenGetSideName(unsigned char a, int b, char *pText, int length);
void DepthChartScreenGetSpot(unsigned char a, int b, int c, int *pList0, int *pList1, char *pText, int length);
float fn_8005F754(void);
StevRow_t *fn_8005FC7C(void);
void fn_8005FCF8(int *pA, int *pB);
void fn_80060330(int a, int *pList, int count, Object_8008044C *pObject);
void fn_80061B90(int team, int *pDigp);
int DbCursorGetValue(DbCursor *pObject, int key);
void PortDbOpenSides(DbCursor *pObject);
void PortDbCloseSides(DbCursor *pObject);
int PortDbGetPort(DbCursor *pObject);
int PortDbGetSide(DbCursor *pObject);
int PortDbSideHasPlayers(int team);
unsigned char PortDbGetSidePort(int a);
void PortDbSetControlledPlayer(int pad, int id);
void GameInfoSet(int index, int value);
int fn_8008058C(int *pId, int *pPos, int *pValue, int a, int b, int c, int mode);
void fn_8008079C(int which);
void fn_8008082C(int row, int which);
void fn_80080874(int which);
void PlayerDbSetTeamIndex(Object_8008044C *pObject, int value);
void PlayerDbGetFirstName(Object_8008044C *pObject, char *pBuffer, int size);
void PlayerDbGetShortName(Object_8008044C *pObject, char *pBuffer, int size);
int PlayerDbGetPrty(Object_8008044C *pObject);
int PlayerDbGetPortraitId(Object_8008044C *pObject);
int PlayerDbGetWeight(Object_8008044C *pObject);
int PlayerDbGetRating(Object_8008044C *pObject, int index);
void PlayerDbSetRating(Object_8008044C *pObject, int index, int value);
int fn_80082414(int index);
int fn_8008257C(int count, unsigned int *pOut);
int fn_800827EC(int id, int value);
int fn_80082864(void);
void fn_800828FC(void);
void fn_800829D8(void);
int fn_80082AB0(int a, int b, int c);
int fn_800841AC(DbCursor *pObject);
int fn_800841D8(DbCursor *pObject);
int fn_80084204(DbCursor *pObject);
int fn_800844B8(const char *pName, int a, int b);
int fn_8008454C(int a, int b, int c);
int TournamentGetDraftPool1(int *pList, int max);
int TournamentGetDraftPool0(int *pList, int max);
int TournamentGetTeamList(int *pList);
int TournamentClose(void);
int TournamentOpen(int index);
int fn_801485D4(void);
int fn_801486A0(void);
void fn_80148AF8(Class_80148A58 *pObject);
int fn_80178308(void);
int fn_80178320(void);
int GameModeTypeIsSpecial(void);
void PositionAbbrevFormat(int a, char *pText);
int MsgGameGetSetupState(void);
int GameTextGetPadPlayer(int a);
void GameTextSetSetupActive(unsigned char a);
void TeamLogoRequestTint(int index, int a, int b, int c, const unsigned char *pColor);
int TeamLogoGetHandle(int a);
void fn_8018C48C(int tag);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
void SortArray(int a, void *pBase, int count, int size, int (*pCompare)(TeamPickPlayer_t *, TeamPickPlayer_t *), int b,
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

TeamPickState_t *_MsgTeamPick_pState = 0;
TeamPickPlayer_t *_MsgTeamPick_pPool = 0;
int _MsgTeamPick_iPoolCount = 0;
int _MsgTeamPick_iModeCleared = 0;
AutoDepthPlayer_t *_MsgTeamPick_pAutoDepth = 0;
unsigned char _MsgTeamPick_bSaveTeams = 0;
StevRow_t *_MsgTeamPick_pEventRow = 0;
StevRow_t *_MsgTeamPick_pTournamentRow = 0;
int _MsgTeamPick_iEventPlayer = 0;
int _MsgTeamPick_iLastCreatedId = -1;
unsigned char _MsgTeamPick_bModeSet = 0;
int _MsgTeamPick_iMode = 0;
unsigned char _MsgTeamPick_abSources[4] = { 1, 0, 0, 0 };
signed char _MsgTeamPick_ascGroupQuota[7] = { 2, 2, 2, 2, 2, 2, 2 };
unsigned char _MsgTeamPick_bClosed = 1;

int _MsgTeamPick_aiDepthValue[2];
int _MsgTeamPick_iHoldingTeam;

Object_8008044C _MsgTeamPick_PlayerCursor;
DbCursor _MsgTeamPick_TeamCursor;
unsigned short _MsgTeamPick_ausGroupStart[7];
int _MsgTeamPick_aiSavedTeam[8];
int _MsgTeamPick_aiTournamentTeam[8];
int _MsgTeamPick_aiHoldingTeam[7];

TeamPickCaptain_t _MsgTeamPick_aCaptain[8] = {
    { 0, 0x2E }, { 0x1E2, 0x2F }, { 0x1E8, 0x30 }, { 0x195, 0x31 },
    { 0x1C1, 0x32 }, { 0x196, 0x33 }, { 0x1D3, 0x34 }, { 0x1F1, 0x35 },
};
int _MsgTeamPick_aiPositionGroup[14] = { 0, 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6 };
int _MsgTeamPick_aiGroupSize[7] = { 1, 1, 2, 3, 2, 2, 3 };
int _MsgTeamPick_aaiGroupPositions[7][3] = {
    { 0, 0xFF, 0xFF }, { 1, 0xFF, 0xFF }, { 2, 3, 0xFF }, { 4, 5, 6 },
    { 7, 8, 0xFF }, { 9, 10, 0xFF }, { 11, 12, 13 },
};
int _MsgTeamPick_aiRatingIndex[10] = { 0, 4, 1, 3, 2, 5, 6, 7, 8, 9 };

void MsgTeamPickCreateHoldingTeams(void);
int MsgTeamPickCreatePlayer(TeamPickPlayer_t *pEntry, int pos, float scale, int team);
void MsgTeamPickLowerRatings(int id, float scale);
void MsgTeamPickFillTeam(int group);
void MsgTeamPickGetTeamIds(int group, int *pList);
void MsgTeamPickAllocState(unsigned char count, unsigned char size);
void MsgTeamPickFreeState(void);
void MsgTeamPickPickPlayer(int id, int *pSlot);
int MsgTeamPickAutoSelect(int *pGroupDelta, int *pResult);
void MsgTeamPickFreePool(void);

void MsgTeamPickBuildAutoDepth(void)
{
    int n = 0;
    int side = 2;
    if (PortDbSideHasPlayers(0) == 0) side = 0;
    if (PortDbSideHasPlayers(1) == 0) side = 1;
    switch (fn_801486A0()) {
    case 0:
    case 1:
        side = 0;
        break;
    }
    if (side != 2) {
        int *list = (int *)fn_801D2B7C((_MsgTeamPick_iPoolCount + 1) * sizeof(int), 0, 0);
        for (int i = 0; i < _MsgTeamPick_iPoolCount; i++) {
            list[n++] = _MsgTeamPick_pPool[i].mId;
        }
        list[n] = 0x7FFF;
        AutoDepthBuild(_MsgTeamPick_aiDepthValue[side], list, &_MsgTeamPick_pAutoDepth);
        fn_801D2BD0(list);
    }
}

void MsgTeamPickFreeAutoDepth(void)
{
    if (_MsgTeamPick_pAutoDepth) {
        AutoDepthFree(&_MsgTeamPick_pAutoDepth);
        _MsgTeamPick_pAutoDepth = 0;
    }
}

int MsgTeamPickGetGroupCount(int group)
{
    int count;
    if (group == 6) {
        count = _MsgTeamPick_iPoolCount - _MsgTeamPick_ausGroupStart[6];
    } else {
        count = _MsgTeamPick_ausGroupStart[group + 1] - _MsgTeamPick_ausGroupStart[group];
    }
    return count;
}

int MsgTeamPickGroupToPoolIndex(int group, int index)
{
    return index + _MsgTeamPick_ausGroupStart[group];
}

int MsgTeamPickPoolToGroupIndex(int group, int index)
{
    return index - _MsgTeamPick_ausGroupStart[group];
}

int MsgTeamPickGetPlayerGroup(int index)
{
    return _MsgTeamPick_aiPositionGroup[_MsgTeamPick_pPool[index].mUnknownC];
}

int MsgTeamPickRandomDepthValue(void)
{
    return fn_802372EC(0, 5);
}

TeamPickPlayer_t *MsgTeamPickFindPlayer(int id, int *pIndex)
{
    TeamPickPlayer_t *found = 0;
    int i;
    for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
        if (_MsgTeamPick_pPool[i].mId == id) {
            found = &_MsgTeamPick_pPool[i];
            break;
        }
    }
    if (pIndex) *pIndex = i;
    return found;
}

void MsgTeamPickFinishTeam(int team)
{
    int list[8];
    MsgTeamPickFillTeam(team);
    MsgTeamPickGetTeamIds(team, list);
    DepthChartAutoFill(team, list, _MsgTeamPick_aiDepthValue[team]);
}

int MsgTeamPickFillGroupQuotas(int teamId)
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
        counts[i] = fn_8008058C(&id, &pos, &value, _MsgTeamPick_aaiGroupPositions[i][0], _MsgTeamPick_aaiGroupPositions[i][1], _MsgTeamPick_aaiGroupPositions[i][2], 2);
        total += counts[i];
        int max = _MsgTeamPick_ascGroupQuota[i];
        for (used[i] = 0; used[i] < counts[i] && used[i] < max; used[i]++) {
            fn_8008082C(used[i], 2);
            fn_8008079C(2);
            _MsgTeamPick_ascGroupQuota[i]--;
            _MsgTeamPick_pPool[n].mId = id;
            _MsgTeamPick_pPool[n].mUnknown8 = value;
            _MsgTeamPick_pPool[n].mUnknownC = pos;
            _MsgTeamPick_pPool[n].mUnknown10 = 0xFF;
            _MsgTeamPick_pPool[n].mSlot = -1;
            _MsgTeamPick_pPool[n].mTeam = 2;
            _MsgTeamPick_pPool[n].mUnknown15 = 0xFF;
            n++;
        }
        fn_80080874(2);
    }
    while (n < _MsgTeamPick_iPoolCount && n < total) {
        i = fn_802372EC(0, 7);
        if (counts[i] > used[i]) {
            fn_8008058C(&id, &pos, &value, _MsgTeamPick_aaiGroupPositions[i][0], _MsgTeamPick_aaiGroupPositions[i][1], _MsgTeamPick_aaiGroupPositions[i][2], 2);
            fn_8008082C(used[i], 2);
            fn_8008079C(2);
            _MsgTeamPick_ascGroupQuota[i]--;
            _MsgTeamPick_pPool[n].mId = id;
            _MsgTeamPick_pPool[n].mUnknown8 = value;
            _MsgTeamPick_pPool[n].mUnknownC = pos;
            _MsgTeamPick_pPool[n].mUnknown10 = 0xFF;
            _MsgTeamPick_pPool[n].mSlot = -1;
            _MsgTeamPick_pPool[n].mTeam = 2;
            _MsgTeamPick_pPool[n].mUnknown15 = 0xFF;
            n++;
            fn_80080874(2);
            used[i]++;
        }
        FESndUpdate(1);
    }
    return n;
}

int MsgTeamPickFillRandomGroups(int n, int teamId, float scale)
{
    int count0 = 0;
    unsigned int team = 0;
    int max = 0;
    int id = 0;
    int pos = 0;
    int value = 0;
    int picked[2];
    if (_MsgTeamPick_abSources[1]) {
        fn_8008257C(fn_80082864(), &team);
    }
    for (int i = 0; i <= 6; i++) {
        int count1;
        if (_MsgTeamPick_abSources[0]) {
            count0 = fn_8008058C(&id, &pos, &value, _MsgTeamPick_aaiGroupPositions[i][0], _MsgTeamPick_aaiGroupPositions[i][1], _MsgTeamPick_aaiGroupPositions[i][2], 0);
        } else {
            count0 = 0;
        }
        if (_MsgTeamPick_abSources[1]) {
            count1 = 0;
            int rows = fn_8008058C(&id, &pos, &value, _MsgTeamPick_aaiGroupPositions[i][0], _MsgTeamPick_aaiGroupPositions[i][1], _MsgTeamPick_aaiGroupPositions[i][2], 1);
            for (int row = 0; row < rows; row++) {
                fn_8008082C(row, 1);
                fn_8008079C(1);
                if (fn_800827EC(id, team) == 0) count1++;
            }
        } else {
            count1 = 0;
        }
        int extra = _MsgTeamPick_abSources[2] ? 6 : 0;
        int total = count0 + count1;
        if (total + extra < _MsgTeamPick_ascGroupQuota[i]) {
            max = total + extra;
        } else {
            max = _MsgTeamPick_ascGroupQuota[i];
        }
        for (int k = 0; k < max && n < _MsgTeamPick_iPoolCount; k++, n++) {
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
                _MsgTeamPick_pPool[n].mId = id;
                _MsgTeamPick_pPool[n].mUnknown8 = value;
                _MsgTeamPick_pPool[n].mUnknownC = pos;
                _MsgTeamPick_pPool[n].mUnknown10 = 0xFF;
                _MsgTeamPick_pPool[n].mSlot = -1;
                _MsgTeamPick_pPool[n].mTeam = 2;
                _MsgTeamPick_pPool[n].mUnknown15 = 0xFF;
            } else {
                pos = _MsgTeamPick_aaiGroupPositions[i][0];
                _MsgTeamPick_pPool[n].mUnknownC = pos;
                MsgTeamPickCreatePlayer(&_MsgTeamPick_pPool[n], pos, scale, teamId);
            }
            FESndUpdate(1);
        }
        if (_MsgTeamPick_abSources[0]) fn_80080874(0);
        if (_MsgTeamPick_abSources[1]) fn_80080874(1);
    }
    return n;
}

int MsgTeamPickFillRemaining(int start, int teamId, float scale)
{
    int n = start;
    int count0 = 0;
    unsigned int team = 0;
    int range = 0;
    int id = 0;
    int pos = 0;
    int value = 0;
    count0 = fn_8008058C(&id, &pos, &value, -1, -1, -1, 0);
    int offset = 0;
    int rows = 0;
    int seq = 0;
    int count1;
    if (!_MsgTeamPick_abSources[0]) count0 = 0;
    if (_MsgTeamPick_abSources[1]) {
        rows = fn_8008058C(&id, &pos, &value, -1, -1, -1, 1);
        count1 = fn_8008257C(rows, &team);
    } else {
        count1 = 0;
    }
    int extra = _MsgTeamPick_abSources[2] ? 42 : 0;
    int total = count0 + count1;
    range = total + extra;
    for (; n < _MsgTeamPick_iPoolCount; n++) {
        int pick;
        if (_MsgTeamPick_iMode == 2) {
            if ((pick = seq) < total) {
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
            seq++;
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
                        if (id == _MsgTeamPick_pPool[j].mId) {
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
            _MsgTeamPick_pPool[n].mId = id;
            _MsgTeamPick_pPool[n].mUnknown8 = value;
            _MsgTeamPick_pPool[n].mUnknownC = pos;
            _MsgTeamPick_pPool[n].mUnknown10 = 0xFF;
            _MsgTeamPick_pPool[n].mSlot = -1;
            _MsgTeamPick_pPool[n].mTeam = 2;
            _MsgTeamPick_pPool[n].mUnknown15 = 0xFF;
        } else if (_MsgTeamPick_abSources[2]) {
            range--;
            int group = (pos + 1) % 7;
            int index = fn_802372EC(0, _MsgTeamPick_aiGroupSize[group]);
            pos = _MsgTeamPick_aaiGroupPositions[group][index];
            _MsgTeamPick_pPool[n].mUnknownC = pos;
            MsgTeamPickCreatePlayer(&_MsgTeamPick_pPool[n], pos, scale, teamId);
        } else if (range < _MsgTeamPick_iPoolCount) {
            fn_8008082C(pick - range, 0);
            fn_8008079C(0);
            _MsgTeamPick_pPool[n].mId = id;
            _MsgTeamPick_pPool[n].mUnknown8 = value;
            _MsgTeamPick_pPool[n].mUnknownC = pos;
            _MsgTeamPick_pPool[n].mUnknown10 = 0xFF;
            _MsgTeamPick_pPool[n].mSlot = 1000;
            _MsgTeamPick_pPool[n].mTeam = 2;
            _MsgTeamPick_pPool[n].mUnknown15 = 0xFF;
        }
        FESndUpdate(1);
    }
    fn_80080874(0);
    if (_MsgTeamPick_abSources[1]) fn_80080874(1);
    return n;
}

int MsgTeamPickBuildTournamentPool(void)
{
    int ids[8];
    int others[56];
    int index;
    int digt;
    int count;
    int n;
    int i;
    unsigned int j;

    index = fn_8022F384(fn_8022F4BC());
    digt = StoryTeamLoadOneToStats(index, 1, (StoryTeamIdBlock_t *)ids);
    if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, ids[0], 0)) {
        DbCursorSetInt(&_MsgTeamPick_PlayerCursor, 0x44494F50, ids[0]);
        DbCursorSetInt(&_MsgTeamPick_PlayerCursor, 0x44494754, digt);
        DbCursorSetInt(&_MsgTeamPick_PlayerCursor, 0x49544754, digt);
        _MsgTeamPick_aCaptain[0].mValue = ids[0];
        DbCursorGetValue((DbCursor *)&_MsgTeamPick_PlayerCursor, 0x50585350);
        DbCursorGetInt(&_MsgTeamPick_PlayerCursor, 0x4F504250);
    }
    TournamentOpen(index);
    TournamentGetTeamList(_MsgTeamPick_aiTournamentTeam);
    TournamentGetDraftPool1(&ids[1], 7);
    count = TournamentGetDraftPool0(others, 56);
    TournamentClose();
    _MsgTeamPick_iPoolCount = count + 8;
    _MsgTeamPick_pPool = (TeamPickPlayer_t *)fn_801D2B7C(_MsgTeamPick_iPoolCount * sizeof(TeamPickPlayer_t), 0, 0);
    n = 0;
    for (i = 0; i < 8; i++) {
        _MsgTeamPick_pPool[n].mId = ids[i];
        _MsgTeamPick_pPool[n].mUnknown8 = 0;
        _MsgTeamPick_pPool[n].mUnknownC = 0;
        _MsgTeamPick_pPool[n].mUnknown10 = 0xFF;
        _MsgTeamPick_pPool[n].mSlot = -1;
        _MsgTeamPick_pPool[n].mTeam = 8;
        _MsgTeamPick_pPool[n].mUnknown15 = 0xFF;
        if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, ids[i], 0)) {
            int value8 = DbCursorGetValue((DbCursor *)&_MsgTeamPick_PlayerCursor, 0x50585350);
            int valueC = DbCursorGetInt(&_MsgTeamPick_PlayerCursor, 0x4F504250);
            _MsgTeamPick_pPool[n].mUnknown8 = value8;
            _MsgTeamPick_pPool[n].mUnknownC = valueC;
        }
        n++;
    }
    for (i = 0; i < count; i++) {
        _MsgTeamPick_pPool[n].mId = others[i];
        _MsgTeamPick_pPool[n].mUnknown8 = 0;
        _MsgTeamPick_pPool[n].mUnknownC = 0;
        _MsgTeamPick_pPool[n].mUnknown10 = 0xFF;
        _MsgTeamPick_pPool[n].mSlot = -1;
        _MsgTeamPick_pPool[n].mTeam = 8;
        _MsgTeamPick_pPool[n].mUnknown15 = 0xFF;
        if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, others[i], 0)) {
            int value8 = DbCursorGetValue((DbCursor *)&_MsgTeamPick_PlayerCursor, 0x50585350);
            int valueC = DbCursorGetInt(&_MsgTeamPick_PlayerCursor, 0x4F504250);
            _MsgTeamPick_pPool[n].mUnknown8 = value8;
            _MsgTeamPick_pPool[n].mUnknownC = valueC;
        }
        n++;
    }
    for (i = 0; i < 8; i++) {
        _MsgTeamPick_pState->mUnknown15 = i;
        _MsgTeamPick_pState->mUnknown19 = i;
        j = 0;
        while (j < 8 && _MsgTeamPick_aCaptain[j].mKey != _MsgTeamPick_aiTournamentTeam[i]) {
            j++;
        }
        MsgTeamPickPickPlayer(ids[j], 0);
    }
    _MsgTeamPick_iEventPlayer = ids[0];
    return n;
}

int MsgTeamPickAddEventPlayer(void)
{
    StoryTeamIdBlock_t ids;
    int index;
    int digt;
    int value8;
    int valueC;
    int ok = 0;

    index = fn_8022F384(fn_8022F4BC());
    digt = StoryTeamLoadOneToStats(index, 1, &ids);
    if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, ids.mUnknown0, 0)) {
        DbCursorSetInt(&_MsgTeamPick_PlayerCursor, 0x44494F50, ids.mUnknown0);
        ok = 1;
        DbCursorSetInt(&_MsgTeamPick_PlayerCursor, 0x44494754, digt);
        DbCursorSetInt(&_MsgTeamPick_PlayerCursor, 0x49544754, digt);
        value8 = DbCursorGetValue((DbCursor *)&_MsgTeamPick_PlayerCursor, 0x50585350);
        valueC = DbCursorGetInt(&_MsgTeamPick_PlayerCursor, 0x4F504250);
        _MsgTeamPick_pPool[0].mId = ids.mUnknown0;
        _MsgTeamPick_pPool[0].mUnknown8 = value8;
        _MsgTeamPick_pPool[0].mUnknownC = valueC;
        _MsgTeamPick_pPool[0].mUnknown10 = 0xFF;
        _MsgTeamPick_pPool[0].mSlot = -1;
        _MsgTeamPick_pPool[0].mTeam = 2;
        _MsgTeamPick_pPool[0].mUnknown15 = 0xFF;
        _MsgTeamPick_pState->mUnknown15 = 1;
        _MsgTeamPick_pState->mUnknown19 = 1;
        MsgTeamPickPickPlayer(ids.mUnknown0, 0);
        _MsgTeamPick_iEventPlayer = ids.mUnknown0;
    }
    return ok;
}

void MsgTeamPickBuildPool(void)
{
    float scale = 0.0f;
    int n = 0;
    int team = 0;
    int i;

    if (_MsgTeamPick_pTournamentRow) {
        MsgTeamPickBuildTournamentPool();
    } else {
        _MsgTeamPick_pPool = (TeamPickPlayer_t *)fn_801D2B7C(_MsgTeamPick_iPoolCount * sizeof(TeamPickPlayer_t), 0, 0);
        if (_MsgTeamPick_pEventRow) {
            n = MsgTeamPickAddEventPlayer();
        }
        if (_MsgTeamPick_abSources[2]) {
            MsgTeamPickCreateHoldingTeams();
            team = fn_800844B8("New Team", 6, 0);
            fn_800828FC();
            scale = fn_8005F754();
        }
        for (i = 0; i < 7; i++) {
            _MsgTeamPick_ascGroupQuota[i] = 2;
        }
        if (_MsgTeamPick_abSources[3]) {
            n = MsgTeamPickFillGroupQuotas(team);
        }
        if (_MsgTeamPick_iMode != 2 && n < _MsgTeamPick_iPoolCount) {
            n = MsgTeamPickFillRandomGroups(n, team, scale);
        }
        if (n < _MsgTeamPick_iPoolCount) {
            MsgTeamPickFillRemaining(n, team, scale);
        }
    }
    if (_MsgTeamPick_abSources[2]) {
        fn_800829D8();
    }
    FESndUpdate(1);
}

void MsgTeamPickCreateHoldingTeams(void)
{
    int i;

    fn_8022EF8C(0, 0x43544E52);
    for (i = 0; i < 7; i++) {
        _MsgTeamPick_aiHoldingTeam[i] = fn_8008454C(6, -1, 0);
    }
    _MsgTeamPick_iHoldingTeam = 0;
    fn_8022EFBC(0, 0x43544E52);
}

int MsgTeamPickCreatePlayer(TeamPickPlayer_t *pEntry, int pos, float scale, int team)
{
    int id;

    id = fn_80082AB0(pos, team, _MsgTeamPick_iLastCreatedId);
    _MsgTeamPick_iLastCreatedId = id;
    PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, id, 0);
    PlayerDbSetTeamIndex(&_MsgTeamPick_PlayerCursor, _MsgTeamPick_aiHoldingTeam[_MsgTeamPick_iHoldingTeam]);
    MsgTeamPickLowerRatings(id, scale);
    pEntry->mTeam = 2;
    pEntry->mUnknown15 = 0xFF;
    pEntry->mId = id;
    pEntry->mSlot = -1;
    pEntry->mUnknown8 = 0;
    if (++_MsgTeamPick_iHoldingTeam == 7) {
        _MsgTeamPick_iHoldingTeam = 0;
    }
    return 1;
}

void MsgTeamPickLowerRatings(int id, float scale)
{
    int i;

    if (_MsgTeamPick_pEventRow) {
        PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, id, 0);
        for (i = 0; i < 10; i++) {
            unsigned int value = PlayerDbGetRating(&_MsgTeamPick_PlayerCursor, _MsgTeamPick_aiRatingIndex[i]);

            value -= (int)((float)value * scale);
            value = value > 100 ? 100 : value;
            value = value < 5 ? 5 : value;
            PlayerDbSetRating(&_MsgTeamPick_PlayerCursor, _MsgTeamPick_aiRatingIndex[i], value);
        }
    }
}

int MsgTeamPickCompareNames(TeamPickPlayer_t *pA, TeamPickPlayer_t *pB)
{
    char first[16];
    char last[16];
    char nameA[32];
    char nameB[32];

    if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, pA->mId, 0)) {
        PlayerDbGetLastName(&_MsgTeamPick_PlayerCursor, last, 15);
        PlayerDbGetFirstName(&_MsgTeamPick_PlayerCursor, first, 12);
        fn_801C2D88(nameA, 27, "%s%s", last, first);
        if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, pB->mId, 0)) {
            PlayerDbGetLastName(&_MsgTeamPick_PlayerCursor, last, 15);
            PlayerDbGetFirstName(&_MsgTeamPick_PlayerCursor, first, 12);
            fn_801C2D88(nameB, 27, "%s%s", last, first);
            return strncmp(nameA, nameB, 27);
        }
    }
    return 0;
}

int MsgTeamPickCompareGroups(TeamPickPlayer_t *pA, TeamPickPlayer_t *pB)
{
    return (unsigned char)_MsgTeamPick_aiPositionGroup[pA->mUnknownC] - (unsigned char)_MsgTeamPick_aiPositionGroup[pB->mUnknownC];
}

void MsgTeamPickSortPool(void)
{
    unsigned short i;
    int last;
    int group;
    int j;
    int count;

    SortArray(1, _MsgTeamPick_pPool, _MsgTeamPick_iPoolCount, sizeof(TeamPickPlayer_t), MsgTeamPickCompareGroups, 0, 0, 1);
    for (i = 0; i < 7; i++) {
        _MsgTeamPick_ausGroupStart[i] = _MsgTeamPick_iPoolCount;
    }
    last = 0;
    _MsgTeamPick_ausGroupStart[0] = 0;
    for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
        group = MsgTeamPickGetPlayerGroup(i);
        if (group != last) {
            for (j = last + 1; j <= group; j++) {
                _MsgTeamPick_ausGroupStart[j] = i;
            }
            last = group;
        }
    }
    for (i = 0; i < 6; i++) {
        if (_MsgTeamPick_ausGroupStart[i + 1] < _MsgTeamPick_ausGroupStart[i]) {
            _MsgTeamPick_ausGroupStart[i + 1] = _MsgTeamPick_ausGroupStart[i];
        }
    }
    for (i = 0; i < 7; i++) {
        count = MsgTeamPickGetGroupCount(i);
        if (count) {
            SortArray(1, &_MsgTeamPick_pPool[_MsgTeamPick_ausGroupStart[i]], count, sizeof(TeamPickPlayer_t), MsgTeamPickCompareNames, 0, 0, 1);
        }
    }
}

void MsgTeamPickRegisterPortraits(void)
{
    void *pList;
    int i;

    pList = fn_8021EA44(1);
    for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
        if (_MsgTeamPick_pPool[i].mUnknown8 > 630) {
            fn_8021E2B4(pList, 10, _MsgTeamPick_pPool[i].mUnknown8);
        }
    }
    _MsgTeamPick_pState->mUnknown1B = 1;
}

void MsgTeamPickUnregisterPortraits(void)
{
    void *pList;
    int i;

    if (_MsgTeamPick_pState->mUnknown1B) {
        pList = fn_8021EA44(1);
        for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
            if (_MsgTeamPick_pPool[i].mUnknown8 > 630) {
                fn_8021E72C(pList, 10, _MsgTeamPick_pPool[i].mUnknown8);
            }
            if (i % 10 == 9) {
                FESndUpdate(1);
            }
        }
        _MsgTeamPick_pState->mUnknown1B = 0;
    }
}

void MsgTeamPickInitPool(void)
{
    _MsgTeamPick_iHoldingTeam = 0;
    MsgTeamPickBuildPool();
    MsgTeamPickSortPool();
    MsgTeamPickRegisterPortraits();
}

void MsgTeamPickFormatName(char *pDest, int unused, int abbreviate)
{
    char first[16];
    char last[16];

    PlayerDbGetFirstName(&_MsgTeamPick_PlayerCursor, first, 12);
    PlayerDbGetLastName(&_MsgTeamPick_PlayerCursor, last, 15);
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

int MsgTeamPickAllTeamsFull(void)
{
    unsigned char i;
    int result = 1;

    for (i = 0; i < _MsgTeamPick_pState->mCount; i++) {
        if (_MsgTeamPick_pState->mpCounts[i] < _MsgTeamPick_pState->mSize) {
            result = 0;
            break;
        }
    }
    return result;
}

void MsgTeamPickFillTeam(int group)
{
    int slot = _MsgTeamPick_pState->mUnknown0C[group];
    int i;

    for (i = 0; i < _MsgTeamPick_iPoolCount && slot <= 6; i++) {
        TeamPickPlayer_t *pEntry = &_MsgTeamPick_pPool[i];

        if (pEntry->mSlot < 0 || pEntry->mSlot == 1000) {
            pEntry->mSlot = slot;
            pEntry->mTeam = group;
            slot++;
        }
    }
}

void MsgTeamPickGetTeamIds(int group, int *pList)
{
    int n = 0;
    int i;

    for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
        if (_MsgTeamPick_pPool[i].mSlot >= 0 && _MsgTeamPick_pPool[i].mTeam == group) {
            pList[_MsgTeamPick_pPool[i].mSlot] = _MsgTeamPick_pPool[i].mId;
            n++;
        }
    }
    pList[n] = 0x7FFF;
}

int MsgTeamPickFindDepthEntry(int id, int side, int *pList)
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

void MsgTeamPickRemapDepthIds(int *pIds, int *pValues, int *pList)
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
            pList[MsgTeamPickFindDepthEntry(pIds[j], k, copy)] = pValues[j];
        }
    }
}

static inline void _MsgTeamPickResetState(int size)
{
    unsigned char i;

    for (i = 0; i < _MsgTeamPick_pState->mCount; i++) {
        fn_801C1F94(_MsgTeamPick_pState->mppLists[i], 0xFF, _MsgTeamPick_pState->mSize * 4);
    }
    fn_801C1F94(_MsgTeamPick_pState->mpCounts, 0, _MsgTeamPick_pState->mCount);
    fn_801C1F94(_MsgTeamPick_pState->mUnknown0C, 0, size);
    _MsgTeamPick_pState->mUnknown17 = 0;
    _MsgTeamPick_pState->mUnknown18 = 0;
}

void MsgTeamPickSaveTeam(int *pTeam, int *pIds, const char *pName)
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
        /* The same copy for the player's depth chart rows ('THCD'), switched off. */
        if (0) {
            fn_801F9980(0x54415453, &handle);
            fn_801FCE10(0, "use 'TATS' select into \x8c * from 'THCD' where ('DIGP' = \x82)\n", handle, oldIds[i]);
            fn_801FCE10(0, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIGP' = \x82 where ('DIGP' = \x82)\n", handle,
                        *pTeam, newIds[i], oldIds[i]);
            fn_801FCE10(0, "use 'TATS' insert into \x8c.'THCD' * select * from \x8c\n", 0x54415453, handle);
            fn_801F967C(0x54415453, handle);
        }
    }
    MsgTeamPickRemapDepthIds(oldIds, newIds, pIds);
}

void MsgTeamPickAllocState(unsigned char count, unsigned char size)
{
    unsigned char i;

    _MsgTeamPick_pState = (TeamPickState_t *)fn_801D2B7C(sizeof(TeamPickState_t), 0, 0);
    _MsgTeamPick_pState->mCount = count;
    _MsgTeamPick_pState->mSize = size;
    _MsgTeamPick_pState->mUnknown1B = 0;
    _MsgTeamPick_pState->mpUnknown08 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    _MsgTeamPick_pState->mppLists = (int **)fn_801D2B7C(count * 4, 0, 0);
    for (i = 0; i < count; i++) {
        _MsgTeamPick_pState->mppLists[i] = (int *)fn_801D2B7C(size * 4, 0, 0);
    }
    _MsgTeamPick_pState->mpCounts = (unsigned char *)fn_801D2B7C(count, 0, 0);
}

void MsgTeamPickFreeState(void)
{
    unsigned char i;

    fn_801D2BD0(_MsgTeamPick_pState->mpCounts);
    _MsgTeamPick_pState->mpCounts = 0;
    for (i = 0; i < _MsgTeamPick_pState->mCount; i++) {
        fn_801D2BD0(_MsgTeamPick_pState->mppLists[i]);
    }
    fn_801D2BD0(_MsgTeamPick_pState->mppLists);
    _MsgTeamPick_pState->mppLists = 0;
    fn_801D2BD0(_MsgTeamPick_pState->mpUnknown08);
    _MsgTeamPick_pState->mpUnknown08 = 0;
    fn_801D2BD0(_MsgTeamPick_pState);
    _MsgTeamPick_pState = 0;
}

void MsgTeamPickInitTwoTeams(unsigned char size)
{
    unsigned char team;
    unsigned char other;

    MsgTeamPickAllocState(2, size);
    team = GameInfoGet(2);
    other = team == 0;
    _MsgTeamPick_pState->mpUnknown08[0] = PortDbGetSidePort(other);
    _MsgTeamPick_pState->mpUnknown08[1] = PortDbGetSidePort(team);
    _MsgTeamPick_pState->mUnknown15 = 0;
    _MsgTeamPick_pState->mUnknown19 = other;
    _MsgTeamPickResetState(2);
}

void MsgTeamPickInitTournamentTeams(void)
{
    unsigned char i;

    MsgTeamPickAllocState(8, 7);
    _MsgTeamPick_pState->mUnknown15 = 0;
    _MsgTeamPick_pState->mUnknown19 = 0;
    {
        DbCursor cursor;
        int found;

        PortDbOpenSides(&cursor);
        found = DbCursorFirst(&cursor);
        for (i = 0; i < 8; i++) {
            unsigned char id;

            if (found) {
                id = PortDbGetPort(&cursor);
                found = DbCursorNext(&cursor);
            } else {
                id = 0xFF;
            }
            _MsgTeamPick_pState->mpUnknown08[i] = id;
        }
        PortDbCloseSides(&cursor);
    }
    _MsgTeamPickResetState(8);
}

void MsgTeamPickInitSixCaptains(void)
{
    unsigned char i;

    MsgTeamPickAllocState(6, 1);
    _MsgTeamPick_pState->mUnknown15 = 0;
    _MsgTeamPick_pState->mUnknown19 = 1;
    {
        DbCursor cursor;
        int found;

        PortDbOpenSides(&cursor);
        found = DbCursorFirst(&cursor);
        for (i = 0; i < 6; i++) {
            unsigned char id;

            if (found) {
                id = PortDbGetPort(&cursor);
                found = DbCursorNext(&cursor);
            } else {
                id = 0xFF;
            }
            _MsgTeamPick_pState->mpUnknown08[i] = id;
        }
        PortDbCloseSides(&cursor);
    }
    if (!GameModeTypeIsSpecial()) {
        for (i = 0; i < 6; i++) {
            unsigned char j = i + fn_802372EC(0, 6 - i);
            unsigned char id = _MsgTeamPick_pState->mpUnknown08[i];

            _MsgTeamPick_pState->mpUnknown08[i] = _MsgTeamPick_pState->mpUnknown08[j];
            _MsgTeamPick_pState->mpUnknown08[j] = id;
        }
    }
    _MsgTeamPickResetState(2);
}

void MsgTeamPickInitPairedCaptains(void)
{
    unsigned int count = fn_80178D70(0) * 2;
    unsigned char team = GameInfoGet(2);
    unsigned char other = team == 0;

    MsgTeamPickAllocState(count, 1);
    _MsgTeamPick_pState->mUnknown15 = 0;
    _MsgTeamPick_pState->mUnknown19 = other;
    _MsgTeamPick_pState->mpUnknown08[0] = PortDbGetSidePort(other);
    _MsgTeamPick_pState->mpUnknown08[1] = PortDbGetSidePort(team);
    if (count > 2) {
        _MsgTeamPick_pState->mpUnknown08[2] = _MsgTeamPick_pState->mpUnknown08[0];
        _MsgTeamPick_pState->mpUnknown08[3] = _MsgTeamPick_pState->mpUnknown08[1];
        {
            DbCursor cursor;
            int found;

            PortDbOpenSides(&cursor);
            for (found = DbCursorFirst(&cursor); found; found = DbCursorNext(&cursor)) {
                unsigned char id = PortDbGetPort(&cursor);

                if (PortDbGetSide(&cursor) == other && id != _MsgTeamPick_pState->mpUnknown08[0]) {
                    _MsgTeamPick_pState->mpUnknown08[2] = id;
                    break;
                }
            }
            for (found = DbCursorFirst(&cursor); found; found = DbCursorNext(&cursor)) {
                unsigned char id = PortDbGetPort(&cursor);

                if (PortDbGetSide(&cursor) == team && id != _MsgTeamPick_pState->mpUnknown08[1]) {
                    _MsgTeamPick_pState->mpUnknown08[3] = id;
                    break;
                }
            }
            PortDbCloseSides(&cursor);
        }
    }
    _MsgTeamPickResetState(2);
}

void MsgTeamPickInitSevenCaptains(void)
{
    unsigned char i;

    MsgTeamPickAllocState(7, 1);
    _MsgTeamPick_pState->mUnknown15 = 0;
    _MsgTeamPick_pState->mUnknown19 = 1;
    {
        DbCursor cursor;
        int found;

        PortDbOpenSides(&cursor);
        found = DbCursorFirst(&cursor);
        for (i = 0; i < 7; i++) {
            unsigned char id;

            if (found) {
                id = PortDbGetPort(&cursor);
                found = DbCursorNext(&cursor);
            } else {
                id = 0xFF;
            }
            _MsgTeamPick_pState->mpUnknown08[i] = id;
        }
        PortDbCloseSides(&cursor);
    }
    if (!GameModeTypeIsSpecial()) {
        for (i = 0; i < 4; i++) {
            unsigned char j = i + fn_802372EC(0, 4 - i);
            unsigned char id = _MsgTeamPick_pState->mpUnknown08[i];

            _MsgTeamPick_pState->mpUnknown08[i] = _MsgTeamPick_pState->mpUnknown08[j];
            _MsgTeamPick_pState->mpUnknown08[j] = id;
        }
    }
    _MsgTeamPickResetState(2);
}

void MsgTeamPickInitState(void)
{
    if (fn_801486A0() == 15) {
        if (_MsgTeamPick_pTournamentRow) {
            MsgTeamPickInitTournamentTeams();
        } else {
            MsgTeamPickInitTwoTeams(7);
        }
        return;
    }
    switch (fn_801486A0()) {
    case 0:
        MsgTeamPickInitSixCaptains();
        break;
    case 1:
        MsgTeamPickInitSevenCaptains();
        break;
    case 3:
        MsgTeamPickInitTwoTeams(fn_80148A58()->vfn_05(fn_80178308()));
        break;
    case 2:
        MsgTeamPickInitPairedCaptains();
        break;
    case 4:
        MsgTeamPickInitTwoTeams(fn_80148A58()->vfn_05(0));
        break;
    default:
        MsgTeamPickInitTwoTeams(7);
        break;
    }
}

void MsgTeamPickReleaseState(void)
{
    MsgTeamPickFreeState();
}

int MsgTeamPickInit(int *pController, int *pCount)
{
    _MsgTeamPick_bClosed = 0;
    _MsgTeamPick_iLastCreatedId = -1;
    _MsgTeamPick_pEventRow = fn_8005FC7C();
    _MsgTeamPick_pTournamentRow = fn_80061AD4();
    MsgTeamPickInitState();
    if (_MsgTeamPick_pState->mpUnknown08[_MsgTeamPick_pState->mUnknown15] != 0xFF) {
        *pController = GameTextGetPadPlayer(_MsgTeamPick_pState->mpUnknown08[_MsgTeamPick_pState->mUnknown15]);
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
        *pCount = _MsgTeamPick_pState->mCount / 2;
        break;
    default:
        *pCount = _MsgTeamPick_pState->mSize;
        break;
    }

    if (fn_801485D4()) {
        fn_80148AF8(fn_80148A58());
    }
    fn_8008044C(&_MsgTeamPick_PlayerCursor, 0, 0x54415453);
    fn_80083E40(&_MsgTeamPick_TeamCursor, 0, 0x54415453);

    if (MsgGameGetSetupState() == 1) {
        _MsgTeamPick_aiDepthValue[0] = MsgTeamPickRandomDepthValue();
        _MsgTeamPick_aiDepthValue[1] = MsgTeamPickRandomDepthValue();
        MsgTeamPickInitPool();
        MsgTeamPickBuildAutoDepth();
        if (_MsgTeamPick_pEventRow) {
            MsgTeamPickPickPlayer(MsgTeamPickAutoSelect(0, 0), 0);
            _MsgTeamPick_pState->mUnknown15 = 0;
            _MsgTeamPick_pState->mUnknown19 = GameInfoGet(2) ? 0 : 1;
        }
        if (_MsgTeamPick_pTournamentRow || _MsgTeamPick_pEventRow) {
            for (int i = 0; i < _MsgTeamPick_iPoolCount; i++) {
                if (_MsgTeamPick_pPool[i].mSlot >= 0) {
                    int excluded = 0xFF;
                    _MsgTeamPick_pPool[i].mUnknown10 =
                        AutoDepthGetBestSlot(_MsgTeamPick_pAutoDepth, &excluded, _MsgTeamPick_pPool[i].mId);
                }
            }
        }
    } else if (MsgGameGetSetupState() == 0) {
        for (int i = 0; i < _MsgTeamPick_pState->mCount; i++) {
            _MsgTeamPick_pState->mpCounts[i] = *pCount;
        }
        for (int i = 0; i < _MsgTeamPick_iPoolCount; i++) {
            TeamPickPlayer_t *pEntry = &_MsgTeamPick_pPool[i];
            if (pEntry->mSlot >= 0) {
                _MsgTeamPick_pState->mppLists[pEntry->mUnknown15][pEntry->mSlot] = pEntry->mId;
            }
        }
    }

    DepthChartLoad(MsgGameGetSetupState() == 1);
    return 0;
}

void MsgTeamPickShutdown(void)
{
    int digp[8][7];

    _MsgTeamPick_bClosed = 1;
    if (MsgGameGetSetupState() == 1) {
        unsigned int i;

        if (_MsgTeamPick_pTournamentRow) {
            for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
                if (_MsgTeamPick_pPool[i].mSlot >= 0) {
                    digp[_MsgTeamPick_pPool[i].mTeam][_MsgTeamPick_pPool[i].mSlot] = _MsgTeamPick_pPool[i].mId;
                }
            }
            fn_8022DC7C(0);
            fn_8022DCB0(0);
            fn_8022DCE4(0);
            fn_8022DD18(0);
            for (int team = 0; team < 8; team++) {
                fn_80061B90(_MsgTeamPick_aiTournamentTeam[team], digp[team]);
            }
        } else {
            DepthChartSide_t records[8];

            for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
                if (_MsgTeamPick_pPool[i].mSlot >= 0) {
                    digp[_MsgTeamPick_pPool[i].mTeam][_MsgTeamPick_pPool[i].mSlot] = _MsgTeamPick_pPool[i].mId;
                }
            }
            fn_8003DE74(0, digp[0]);
            fn_8003DE74(1, digp[1]);
            DepthChartGetSide(0, &records[0]);
            DepthChartGetSide(1, &records[1]);
            if (_MsgTeamPick_bSaveTeams) {
                MsgTeamPickSaveTeam(&_MsgTeamPick_aiSavedTeam[0], records[0].mUnknown, "Team Two");
                MsgTeamPickSaveTeam(&_MsgTeamPick_aiSavedTeam[1], records[1].mUnknown, "Team One");
                _MsgTeamPick_bSaveTeams = 0;
            }
            GameInfoSet(0, _MsgTeamPick_aiSavedTeam[0]);
            GameInfoSet(1, _MsgTeamPick_aiSavedTeam[1]);
            fn_8022A508(0, _MsgTeamPick_aiSavedTeam[0], _MsgTeamPick_aiSavedTeam[0], 6, -1);
            fn_8022A508(1, _MsgTeamPick_aiSavedTeam[1], _MsgTeamPick_aiSavedTeam[1], 6, -1);
            fn_8022DC7C(0);
            fn_8022DCB0(0);
            fn_8022DCE4(0);
            fn_8022DD18(0);
            for (unsigned char team = 0; team <= 1; team++) {
                for (unsigned char j = 0; j <= 6; j++) {
                    PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, records[team].mUnknown[j], 0);
                    fn_80081F50(&_MsgTeamPick_PlayerCursor, team, 1);
                }
            }
            if (_MsgTeamPick_pState->mSize == 1) {
                for (unsigned char k = 0; k < _MsgTeamPick_pState->mCount; k++) {
                    if (_MsgTeamPick_pState->mpUnknown08[k] != 0xFF) {
                        PortDbSetControlledPlayer(_MsgTeamPick_pState->mpUnknown08[k], *_MsgTeamPick_pState->mppLists[k]);
                    }
                }
            }
        }
        FELoopSetResume(1);
    } else if (MsgGameGetSetupState() == 0) {
        fn_8018C48C(0x54415453);
        fn_8018C48C(0x454D4147);
    }

    MsgTeamPickUnregisterPortraits();
    fn_8008056C(&_MsgTeamPick_PlayerCursor);
    fn_80083F68(&_MsgTeamPick_TeamCursor);
    DepthChartSave();
    if (MsgGameGetSetupState() == 0) {
        MsgTeamPickFreePool();
    }
    if (MsgGameGetSetupState() == 1) {
        if (_MsgTeamPick_pTournamentRow == 0 && _MsgTeamPick_pEventRow) {
            fn_8005FCF8(digp[0], digp[1]);
            fn_80015D28(_MsgTeamPick_pEventRow->mDive);
        }
    } else {
        GameTextSetSetupActive(0);
    }
    AutoDepthSetRateCallback(0);
    AutoDepthSetSelectCallback(0);
    MsgTeamPickReleaseState();
    _MsgTeamPick_pEventRow = 0;
}

void MsgTeamPickCyclePending(int group, int kind, int slot, int code, int a, int b)
{
    DepthChartCyclePending(group, kind, slot, code, a, b);
}

void MsgTeamPickRevertSide(int group)
{
    DepthChartRevertSide(group);
}

int MsgTeamPickGetTeamCode(int team)
{
    if (_MsgTeamPick_pTournamentRow == 0) {
        if (team == _MsgTeamPick_pState->mUnknown15) {
            if (_MsgTeamPick_pState->mUnknown19 != 1) {
                return -12;
            }
            return -11;
        }
        if (_MsgTeamPick_pState->mUnknown19 != 1) {
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

int MsgTeamPickFindListRow(int group, int row)
{
    int skipped = 0;
    int i = 0;
    int count = MsgTeamPickGetGroupCount(_MsgTeamPick_pState->mUnknown17);

    for (; i < count; i++) {
        int index = MsgTeamPickGroupToPoolIndex(group, i);
        if (index < _MsgTeamPick_iPoolCount) {
            if (_MsgTeamPick_pPool[index].mSlot >= 0) {
                skipped++;
            } else if (i - skipped == row) {
                break;
            }
        }
    }
    return i;
}

int MsgTeamPickCountUnplaced(int group, int count)
{
    int n = 0;

    for (int i = 0; i < count; i++) {
        int index = MsgTeamPickGroupToPoolIndex(group, i);
        if (index < _MsgTeamPick_iPoolCount && _MsgTeamPick_pPool[index].mSlot < 0) {
            n++;
        }
    }
    return n;
}

void MsgTeamPickGetPlayerInfo(int row, int *pId, int *pTeam, int *pValues, char *pHeight, int heightSize,
                 char *pWeight, int weightSize)
{
    int values[10];

    int line = MsgTeamPickFindListRow(_MsgTeamPick_pState->mUnknown17, row);
    int index = MsgTeamPickGroupToPoolIndex(_MsgTeamPick_pState->mUnknown17, line);
    *pId = _MsgTeamPick_pPool[index].mId;
    if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, *pId, 0)) {
        if (PlayerDbGetPrty(&_MsgTeamPick_PlayerCursor) == 2) {
            *pTeam = -19;
        } else {
            *pTeam = PlayerDbGetTeamId(&_MsgTeamPick_PlayerCursor);
        }
        PlayerGetGearRatings(&_MsgTeamPick_PlayerCursor, values);
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

        unsigned int height = PlayerDbGetHeight(&_MsgTeamPick_PlayerCursor);
        int weight = PlayerDbGetWeight(&_MsgTeamPick_PlayerCursor);
        fn_801C2D88(pHeight, heightSize, "%d ft %d in", height / 12, height % 12);
        fn_801C2D88(pWeight, weightSize, "%d lbs", weight);
    }
}

void MsgTeamPickStepGroup(int message, MenuArg_t text, int *pCount)
{
    Params_80005284 *pParams = text.pParams;

    switch (message) {
    case -1:
        break;
    case 1:
        if (_MsgTeamPick_pState->mUnknown17 < 6) {
            _MsgTeamPick_pState->mUnknown17++;
        } else {
            _MsgTeamPick_pState->mUnknown17 = 0;
        }
        _MsgTeamPick_pState->mUnknown18 = 0;
        break;
    case 3:
        if (_MsgTeamPick_pState->mUnknown17 != 0) {
            _MsgTeamPick_pState->mUnknown17--;
        } else {
            _MsgTeamPick_pState->mUnknown17 = 6;
        }
        _MsgTeamPick_pState->mUnknown18 = 0;
        break;
    }

    PositionAbbrevFormat(_MsgTeamPick_aaiGroupPositions[_MsgTeamPick_pState->mUnknown17][0], pParams->mpText);
    int count = MsgTeamPickGetGroupCount(_MsgTeamPick_pState->mUnknown17);
    *pCount = count;
    for (int i = _MsgTeamPick_ausGroupStart[_MsgTeamPick_pState->mUnknown17];
         i < _MsgTeamPick_ausGroupStart[_MsgTeamPick_pState->mUnknown17] + count; i++) {
        if (_MsgTeamPick_pPool[i].mSlot >= 0) {
            (*pCount)--;
        }
    }
}

void MsgTeamPickGetCaptain(int slot, int *pId, int *pController)
{
    if (fn_801486A0() == 0 || fn_801486A0() == 1) {
        if (slot < _MsgTeamPick_pState->mUnknown15) {
            *pId = *_MsgTeamPick_pState->mppLists[slot];
            if (_MsgTeamPick_pState->mpUnknown08[slot] == 0xFF) {
                *pController = -1;
            } else {
                *pController = GameTextGetPadPlayer(_MsgTeamPick_pState->mpUnknown08[slot]);
            }
            return;
        }
    } else if (fn_801486A0() == 2) {
        int team = _MsgTeamPick_pState->mUnknown19;
        if (slot < _MsgTeamPick_pState->mUnknown0C[team]) {
            unsigned int i;
            for (i = 0; i < _MsgTeamPick_iPoolCount; i++) {
                if (_MsgTeamPick_pPool[i].mTeam == team && _MsgTeamPick_pPool[i].mSlot == slot) {
                    *pId = _MsgTeamPick_pPool[i].mId;
                    break;
                }
            }
            for (unsigned char j = 0; j < _MsgTeamPick_pState->mCount; j++) {
                if (*_MsgTeamPick_pState->mppLists[j] == *pId) {
                    if (_MsgTeamPick_pState->mpUnknown08[j] == 0xFF) {
                        *pController = -1;
                    } else {
                        *pController = GameTextGetPadPlayer(_MsgTeamPick_pState->mpUnknown08[j]);
                    }
                    return;
                }
            }
            return;
        }
    } else {
        int team = _MsgTeamPick_pState->mUnknown15;
        if (slot < _MsgTeamPick_pState->mpCounts[team]) {
            *pId = _MsgTeamPick_pState->mppLists[team][slot];
            if (_MsgTeamPick_pState->mpUnknown08[team] == 0xFF) {
                *pController = -1;
            } else {
                *pController = GameTextGetPadPlayer(_MsgTeamPick_pState->mpUnknown08[team]);
            }
            return;
        }
    }
    *pId = -1;
    *pController = -1;
}

void MsgTeamPickGetRosterEntry(int slot, int *pId, MenuArg_t name, MenuArg_t position)
{
    unsigned char team = _MsgTeamPick_pState->mUnknown1A;
    Params_80005284 *pName = name.pParams;
    Params_80005284 *pPosition = position.pParams;

    if (fn_801486A0() == 2) {
        if (slot < _MsgTeamPick_pState->mUnknown0C[team]) {
            for (unsigned int i = 0; i < _MsgTeamPick_iPoolCount; i++) {
                if (_MsgTeamPick_pPool[i].mTeam == team && _MsgTeamPick_pPool[i].mSlot == slot) {
                    *pId = _MsgTeamPick_pPool[i].mId;
                    break;
                }
            }
        } else {
            *pId = -1;
        }
    } else {
        if (slot < _MsgTeamPick_pState->mpCounts[team]) {
            *pId = _MsgTeamPick_pState->mppLists[team][slot];
        } else {
            *pId = -1;
        }
    }

    if (*pId != -1 && PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, *pId, 0)) {
        PlayerDbGetLastName(&_MsgTeamPick_PlayerCursor, pName->mpText, pName->mLength);
        PositionAbbrevFormat(PlayerDbGetPbpo(&_MsgTeamPick_PlayerCursor), pPosition->mpText);
    }
}

void MsgTeamPickStepShownTeam(int dir, int *pResult, char *pText, int length)
{
    switch (dir) {
    case -1:
        if (fn_801486A0() == 2) {
            _MsgTeamPick_pState->mUnknown1A = _MsgTeamPick_pState->mUnknown19;
        } else {
            _MsgTeamPick_pState->mUnknown1A = _MsgTeamPick_pState->mUnknown15;
        }
        break;
    case 1:
        if (_MsgTeamPick_pState->mUnknown1A == _MsgTeamPick_pState->mCount - 1 ||
            (fn_801486A0() == 2 && _MsgTeamPick_pState->mUnknown1A == 1)) {
            _MsgTeamPick_pState->mUnknown1A = 0;
        } else {
            _MsgTeamPick_pState->mUnknown1A++;
        }
        break;
    case 3:
        if (_MsgTeamPick_pState->mUnknown1A == 0) {
            if (fn_801486A0() == 2) {
                _MsgTeamPick_pState->mUnknown1A = 1;
            } else {
                _MsgTeamPick_pState->mUnknown1A = _MsgTeamPick_pState->mCount - 1;
            }
        } else {
            _MsgTeamPick_pState->mUnknown1A--;
        }
        break;
    }

    int id = *pResult = MsgTeamPickGetTeamCode(_MsgTeamPick_pState->mUnknown1A);
    if (id < 0) {
        if (_MsgTeamPick_pTournamentRow) {
            int team = -19;
            switch (id) {
            case -11:
                team = _MsgTeamPick_aiTournamentTeam[0];
                break;
            case -12:
                team = _MsgTeamPick_aiTournamentTeam[1];
                break;
            case -13:
                team = _MsgTeamPick_aiTournamentTeam[2];
                break;
            case -14:
                team = _MsgTeamPick_aiTournamentTeam[3];
                break;
            case -15:
                team = _MsgTeamPick_aiTournamentTeam[4];
                break;
            case -16:
                team = _MsgTeamPick_aiTournamentTeam[5];
                break;
            case -17:
                team = _MsgTeamPick_aiTournamentTeam[6];
                break;
            case -18:
                team = _MsgTeamPick_aiTournamentTeam[7];
                break;
            case -19:
                break;
            }
            if (team != -19 && fn_80084034(&_MsgTeamPick_TeamCursor, team, 0)) {
                fn_80083F88(&_MsgTeamPick_TeamCursor, pText, length);
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
                strncpy(pText, pName, length);
            }
        }
    } else {
        if (fn_80084034(&_MsgTeamPick_TeamCursor, id, 0)) {
            fn_80083F88(&_MsgTeamPick_TeamCursor, pText, length);
        }
    }
}

void MsgTeamPickGetListName(int index, MenuArg_t text)
{
    Params_80005284 *pParams = text.pParams;
    int pick = MsgTeamPickFindListRow(_MsgTeamPick_pState->mUnknown17, index);
    int row = MsgTeamPickGroupToPoolIndex(_MsgTeamPick_pState->mUnknown17, pick);

    if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, _MsgTeamPick_pPool[row].mId, 0)) {
        MsgTeamPickFormatName(pParams->mpText, pParams->mLength, 1);
    }
}

int MsgTeamPickGetTurn(int *pController)
{
    unsigned char controller = _MsgTeamPick_pState->mpUnknown08[_MsgTeamPick_pState->mUnknown15];

    if (controller != 0xFF) {
        *pController = GameTextGetPadPlayer(controller);
    } else {
        *pController = -1;
    }
    return MsgTeamPickAllTeamsFull() == 0;
}

void MsgTeamPickGetSlotPlayer(int team, int slot, int *pId)
{
    *pId = -1;
    for (unsigned int i = 0; i < _MsgTeamPick_iPoolCount; i++) {
        if (_MsgTeamPick_pPool[i].mTeam == team && _MsgTeamPick_pPool[i].mSlot == slot) {
            *pId = _MsgTeamPick_pPool[i].mId;
            break;
        }
    }
}

void MsgTeamPickGetSideNames(int group, int kind, DepthChartText_t **pPairs)
{
    DepthChartGetSideNames(group, kind, pPairs);
}

void MsgTeamPickSwapPending(int group, int kind, int slot)
{
    DepthChartSwapPending(group, kind, slot);
}

void MsgTeamPickCommitSide(int group)
{
    DepthChartCommit(group);
}

void MsgTeamPickPickPlayer(int id, int *pSlot)
{
    TeamPickPlayer_t *pEntry = MsgTeamPickFindPlayer(id, 0);

    pEntry->mSlot = _MsgTeamPick_pState->mUnknown0C[_MsgTeamPick_pState->mUnknown19];
    pEntry->mTeam = _MsgTeamPick_pState->mUnknown19;
    pEntry->mUnknown15 = _MsgTeamPick_pState->mUnknown15;

    if (pSlot) {
        switch (fn_801486A0()) {
        case 0:
        case 1:
            *pSlot = _MsgTeamPick_pState->mUnknown0C[0] + _MsgTeamPick_pState->mUnknown0C[1];
            break;
        default:
            *pSlot = pEntry->mSlot;
            break;
        }
    }

    _MsgTeamPick_pState->mppLists[_MsgTeamPick_pState->mUnknown15][_MsgTeamPick_pState->mpCounts[_MsgTeamPick_pState->mUnknown15]] = id;
    _MsgTeamPick_pState->mpCounts[_MsgTeamPick_pState->mUnknown15]++;
    _MsgTeamPick_pState->mUnknown0C[_MsgTeamPick_pState->mUnknown19]++;

    if (MsgTeamPickAllTeamsFull()) {
        MsgTeamPickFinishTeam(0);
        MsgTeamPickFinishTeam(1);
        if (_MsgTeamPick_pEventRow) {
            int value = _MsgTeamPick_iEventPlayer;
            fn_80060330(1, &value, 1, &_MsgTeamPick_PlayerCursor);
        }
    } else {
        if (_MsgTeamPick_pState->mUnknown15 == _MsgTeamPick_pState->mCount - 1) {
            _MsgTeamPick_pState->mUnknown15 = 0;
        } else {
            _MsgTeamPick_pState->mUnknown15++;
        }

        if (_MsgTeamPick_pTournamentRow) {
            _MsgTeamPick_pState->mUnknown19++;
            if (_MsgTeamPick_pState->mCount <= _MsgTeamPick_pState->mUnknown19) {
                _MsgTeamPick_pState->mUnknown19 = 0;
            }
        } else if (_MsgTeamPick_pState->mCount > 1) {
            _MsgTeamPick_pState->mUnknown19 = !_MsgTeamPick_pState->mUnknown19;
        }
    }
}

int MsgTeamPickAutoSelect(int *pGroupDelta, int *pResult)
{
    int count = 0;
    int allowedCount = 0;
    int *pList = (int *)fn_801D2B7C((_MsgTeamPick_iPoolCount + 1) * 4, 0, 0);
    int allowed[16];
    int id;
    int category;
    int index;
    TeamPickPlayer_t *pEntry;

    for (index = 0; index < _MsgTeamPick_iPoolCount; index++) {
        pEntry = &_MsgTeamPick_pPool[index];
        if (pEntry->mSlot >= 0) {
            if (pEntry->mTeam == _MsgTeamPick_pState->mUnknown19) {
                allowed[allowedCount++] = pEntry->mUnknown10;
            }
        } else {
            pList[count++] = pEntry->mId;
        }
    }
    allowed[allowedCount] = 0xFF;
    pList[count] = 0x7FFF;

    AutoDepthSelect(_MsgTeamPick_pAutoDepth, pList, allowed, &id, &category);
    fn_801D2BD0(pList);

    unsigned char group = _MsgTeamPick_pState->mUnknown17;
    pEntry = MsgTeamPickFindPlayer(id, &index);
    unsigned char pickGroup = MsgTeamPickGetPlayerGroup(index);
    unsigned char b = MsgTeamPickPoolToGroupIndex(pickGroup, index);

    if (pGroupDelta) {
        if (group <= pickGroup) {
            *pGroupDelta = pickGroup - group;
        } else {
            *pGroupDelta = 7 - (group - pickGroup);
        }
    }
    if (pResult) {
        *pResult = MsgTeamPickCountUnplaced(pickGroup, b);
    }
    pEntry->mUnknown10 = category;
    return id;
}

void MsgTeamPickStepGroupTabs(int dir, int *pResult, MenuArg_t prevText, MenuArg_t groupText, MenuArg_t nextText)
{
    Params_80005284 *pPrev = prevText.pParams;
    Params_80005284 *pGroup = groupText.pParams;
    Params_80005284 *pNext = nextText.pParams;
    unsigned short prev;
    unsigned short next;

    switch (dir) {
    case 4:
        _MsgTeamPick_pState->mUnknown17 = 0;
        break;
    case 0:
        if (_MsgTeamPick_pState->mUnknown17 == 0) {
            _MsgTeamPick_pState->mUnknown17 = 6;
        } else {
            _MsgTeamPick_pState->mUnknown17--;
        }
        break;
    case 2:
        if (_MsgTeamPick_pState->mUnknown17 == 6) {
            _MsgTeamPick_pState->mUnknown17 = 0;
        } else {
            _MsgTeamPick_pState->mUnknown17++;
        }
        break;
    }

    if (_MsgTeamPick_pState->mUnknown17 == 0) {
        prev = 6;
        next = 1;
    } else if (_MsgTeamPick_pState->mUnknown17 == 6) {
        prev = 5;
        next = 0;
    } else {
        prev = _MsgTeamPick_pState->mUnknown17 - 1;
        next = _MsgTeamPick_pState->mUnknown17 + 1;
    }

    *pResult = MsgTeamPickGetGroupCount(_MsgTeamPick_pState->mUnknown17);
    PositionAbbrevFormat(_MsgTeamPick_aaiGroupPositions[prev][0], pPrev->mpText);
    PositionAbbrevFormat(_MsgTeamPick_aaiGroupPositions[_MsgTeamPick_pState->mUnknown17][0], pGroup->mpText);
    PositionAbbrevFormat(_MsgTeamPick_aaiGroupPositions[next][0], pNext->mpText);
}

void MsgTeamPickGetTeamSlot(int index, int team, int *pValid, int *pId, MenuArg_t name, MenuArg_t text)
{
    if (index < _MsgTeamPick_pState->mpCounts[team]) {
        *pValid = 1;
        for (unsigned short i = 0; i < _MsgTeamPick_iPoolCount; i++) {
            if (_MsgTeamPick_pPool[i].mTeam == team && _MsgTeamPick_pPool[i].mSlot == index) {
                PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, _MsgTeamPick_pPool[i].mId, 0);
                *pId = PlayerDbGetPortraitId(&_MsgTeamPick_PlayerCursor);
                PlayerDbGetLastName(&_MsgTeamPick_PlayerCursor, name.pParams->mpText, name.pParams->mLength);
                PositionAbbrevFormat(PlayerDbGetPbpo(&_MsgTeamPick_PlayerCursor), text.pParams->mpText);
                break;
            }
        }
    } else {
        *pValid = 0;
        *pId = -1;
        strnzcpy(name.pParams->mpText, "", name.pParams->mLength + 1);
        strnzcpy(text.pParams->mpText, "", text.pParams->mLength + 1);
    }
}

void MsgTeamPickGetTeamLogo(int id, int *pA, int *pB)
{
    *pA = -1;
    *pB = -1;
    if (_MsgTeamPick_pTournamentRow != 0 && (unsigned int)(id + 18) <= 7) {
        id = -11 - id;
        id = _MsgTeamPick_aiTournamentTeam[id];
    } else if (id == -11) {
        *pA = 0x85;
    } else if (id == -12) {
        *pA = 0x86;
    } else if (id == -19) {
        *pA = 0x84;
    }
    if (*pA == -1) {
        int found = fn_80084034(&_MsgTeamPick_TeamCursor, id, 0);
        if (fn_80084438(&_MsgTeamPick_TeamCursor) == 0) {
            unsigned char color[3];
            color[0] = fn_800841AC(&_MsgTeamPick_TeamCursor);
            color[1] = fn_800841D8(&_MsgTeamPick_TeamCursor);
            color[2] = fn_80084204(&_MsgTeamPick_TeamCursor);
            TeamLogoRequestTint(0, 4, fn_80084158(&_MsgTeamPick_TeamCursor), 0xAC, color);
            *pB = TeamLogoGetHandle(0);
        }
        if (found) {
            *pA = fn_80084158(&_MsgTeamPick_TeamCursor);
        } else {
            *pA = 0x84;
        }
    }
}

void MsgTeamPickGetOpponentName(int index, char *pDest, int size)
{
    *pDest = 0;
    if (GameModeTypeGet() != 7) {
        strncpy(pDest, "Opponent", size);
    } else if (index < _MsgTeamPick_pState->mCount && index > -1) {
        int id = *_MsgTeamPick_pState->mppLists[index];
        int result = 0;
        if (PlayerDbSeekId(&_MsgTeamPick_PlayerCursor, id, &result)) {
            PlayerDbGetShortName(&_MsgTeamPick_PlayerCursor, pDest, size);
        } else {
            strncpy(pDest, "Opponent", size);
        }
    }
}

void MsgTeamPickFreePool(void)
{
    if (_MsgTeamPick_pPool) {
        fn_801D2BD0(_MsgTeamPick_pPool);
        _MsgTeamPick_pPool = 0;
    }
    MsgTeamPickFreeAutoDepth();
}

void MsgTeamPickSetMode(int mode, int b)
{
    _MsgTeamPick_bModeSet = 1;
    _MsgTeamPick_iModeCleared = 0;
    _MsgTeamPick_iMode = mode;
    switch (mode) {
    case 0:
        _MsgTeamPick_iPoolCount = 40;
        break;
    case 2:
        _MsgTeamPick_iPoolCount = fn_80082414(0) * _MsgTeamPick_abSources[0] + fn_80082414(1) * _MsgTeamPick_abSources[1] +
                       fn_80082414(2) * _MsgTeamPick_abSources[2] + fn_80082414(3) * _MsgTeamPick_abSources[3];
        if (_MsgTeamPick_iPoolCount >= 14) {
            break;
        }
    case 1:
    default:
        _MsgTeamPick_iPoolCount = 14;
        break;
    }
}

void MsgTeamPickSetSources(int mask)
{
    _MsgTeamPick_abSources[0] = mask & 1;
    _MsgTeamPick_abSources[1] = (mask >> 1) & 1;
    _MsgTeamPick_abSources[2] = (mask >> 2) & 1;
    _MsgTeamPick_abSources[3] = (mask >> 3) & 1;
}

int MsgTeamPickHandleMessage(unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgTeamPickInit(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x80000002:
        MsgTeamPickShutdown();
        break;
    case 0x80000003:
        MsgTeamPickCyclePending(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, (int)pArgs[4].pParams->mpText,
                    pArgs[4].pParams->mLength);
        break;
    case 0x80000005:
        MsgTeamPickRevertSide(pArgs[0].i);
        break;
    case 0x80000006:
        MsgTeamPickGetPlayerInfo(pArgs[0].i, pArgs[1].pi, pArgs[2].pi, (int *)(pArgs[3].i + (*pArgs[3].pi + 1) * 4),
                    pArgs[4].pParams->mpText, pArgs[4].pParams->mLength, pArgs[5].pParams->mpText,
                    pArgs[5].pParams->mLength);
        break;
    case 0x80000011:
        MsgTeamPickStepGroup(pArgs[0].i, pArgs[1], pArgs[2].pi);
        break;
    case 0x80000012:
        *pResult = MsgTeamPickGetTeamCode(_MsgTeamPick_pState->mUnknown15);
        break;
    case 0x80000013:
        MsgTeamPickGetCaptain(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000018:
        MsgTeamPickGetListName(pArgs[0].i, pArgs[1]);
        break;
    case 0x80000014:
        MsgTeamPickStepShownTeam(pArgs[0].i, pArgs[1].pi, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        break;
    case 0x80000015:
        MsgTeamPickGetRosterEntry(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3]);
        break;
    case 0x80000016:
        *pResult = MsgTeamPickGetTurn(pArgs[0].pi);
        break;
    case 0x80000017:
        MsgTeamPickGetSlotPlayer(pArgs[0].i, pArgs[1].i, pArgs[2].pi);
        break;
    case 0x80000007:
        MsgTeamPickGetSideNames(pArgs[0].i, pArgs[1].i, (DepthChartText_t **)(pArgs[2].i + (*pArgs[2].pi + 1) * 4));
        break;
    case 0x80000008:
        MsgTeamPickSwapPending(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0x80000009:
        MsgTeamPickCommitSide(pArgs[0].i);
        break;
    case 0x8000000A:
        MsgTeamPickPickPlayer(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x8000000B:
        MsgTeamPickAutoSelect(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x8000000E:
        MsgTeamPickStepGroupTabs(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3], pArgs[4]);
        break;
    case 0x8000000F:
        MsgTeamPickGetTeamSlot(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pi, pArgs[4], pArgs[5]);
        break;
    case 0xA:
        if (*pArgs[0].pi != -1) {
            *pArgs[0].pi = GameTextGetPadPlayer(*pArgs[0].pi);
        }
        break;
    case 8:
        MsgTeamPickGetTeamLogo(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000019:
        MsgTeamPickGetOpponentName(_MsgTeamPick_pState->mUnknown19, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x147:
        *pResult = DepthChartScreenIsSideShown(pArgs[0].i);
        break;
    case 0x149:
        DepthChartScreenGetSideName(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        *pArgs[3].pi = fn_80178D70(pArgs[0].i ? fn_80178308() : fn_80178320());
        break;
    case 0x14A: {
        int *pList = (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4);
        DepthChartScreenGetSpot(pArgs[0].i, pArgs[4].i, pArgs[3].i, pList, pList + 1, pArgs[2].pParams->mpText,
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

void MsgTeamPickRequestTeamSave(void)
{
    _MsgTeamPick_bSaveTeams = 1;
}

}
