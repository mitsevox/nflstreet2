/* Player pick-up screen: the player browses a pool of players, shown one at a time
   on the front-end player model with name, position, height, weight and ratings,
   picks one to add to the team and, when the team is full, one to release. The
   changes are written to the team when the screen closes. */

#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

struct PlayerPickupModelLayout_t {
    float mX;
    float mY;
    float mZ;
    float mScale;
    int mValue;
};

extern "C" {
int TeamFilterGet(void);
void TeamFilterSet(int value);
void FEPlyrShow(void);
void FEPlyrHide(void);
void FEPlyrSetPosition(int index, float x, float y, float z);
void FEPlyrSetScale(int index, float scale);
void FEPlyrSetPlayer(int index, int a, int b);
void FEPlyrSetPriority(int index, int value);
int fn_8005FC7C(void);
void fn_80060278(void);
int fn_800602D8(void);
int fn_800602E0(void);
int ChalGetTournamentWon();
int PlayerDbGetId(Object_8008044C *pObject);
int PlayerDbGetOriginalId(Object_8008044C *pObject);
int PlayerDbSeekOriginalId(Object_8008044C *pObject, int a, int *pResult);
void PlayerDbGetShortName(Object_8008044C *pObject, char *pBuffer, int size);
void PlayerDbGetFullName(Object_8008044C *pObject, char *pBuffer, int size);
int PlayerDbGetPortraitId(Object_8008044C *pObject);
int PlayerDbGetWeight(Object_8008044C *pObject);
int PlayerDbGetBoostedRating(Object_8008044C *pObject, int a);
int fn_800841AC(DbCursor *pObject);
int fn_800841D8(DbCursor *pObject);
int fn_80084204(DbCursor *pObject);
void FEPlyrLoadReset(int value);
void PositionAbbrevFormat(int a, char *pText);
void TeamLogoRequestTint(int index, int a, int b, int c, const unsigned char *pColor);
int StoryTeamLoadToStats(int a, int b, int *pIds, int *pCount);
void StoryTeamStoreFromStats(int a, int b);
void StoryPlayerMoveToTeam(int a, int b);
void StoryPlayerDelete(int a, int b);
void fn_8018C48C(int tag);
int fn_8018D890(int a, int b);
void fn_8018D8EC(int a, int b);
void fn_8018DC18(int a, int b);
void fn_8018DD4C(int a, int b, int c);
int StoryGetFlag100(int a);
void StorySetFlag100(int index, int value);
int StoryGetFlag200(int a);
void StorySetFlag200(int index, int value);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_8021E2B4(void *pObject, int a, int b);
int fn_8021E72C(void *pObject, int a, int b);
void *fn_8021EA44(int index);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022F384(int a);
int fn_8022F4BC(void);
}

static PlayerPickupModelLayout_t _MsgPlayerPickup_ModelLayout = { 550.0f, 330.0f, 7.0f, 1.0f, 14 };
static int _MsgPlayerPickup_aTeamSort[20] = { 0x59414C50, 0x4F504250, 0, 0, 0x59414C50, 0x414E4C50, 0, 0,
                                0x59414C50, 0x414E4650, 0, 0, 0x59414C50, 0x44494750, 0, 0,
                                -1,         -1,         3, 0 };

static Object_8008044C _MsgPlayerPickup_PoolCursor;
static Object_8008044C _MsgPlayerPickup_TeamCursor;
static Object_8008044C _MsgPlayerPickup_RosterCursor;

static int _MsgPlayerPickup_iDropPlayer = 0x7FFF;
static int _MsgPlayerPickup_iAddPlayer = 0x7FFF;
static unsigned char _MsgPlayerPickup_bOpen = 0;
static int _MsgPlayerPickup_bChoosingDrop = 0;

static int _MsgPlayerPickup_iListCount;
static int _MsgPlayerPickup_iListRow;
static int _MsgPlayerPickup_iShownPlayer;
static unsigned char _MsgPlayerPickup_bTeamFull;
static Object_8008044C *_MsgPlayerPickup_pList;
static int _MsgPlayerPickup_iTeam;
static signed char _MsgPlayerPickup_cProfile;
static int _MsgPlayerPickup_iCopyTeam;
static int _MsgPlayerPickup_iTeamLGLT;
static unsigned char _MsgPlayerPickup_bCopyMode;
static unsigned char _MsgPlayerPickup_bSkipTeam;

extern "C" {
void MsgPlayerPickupGetTeamInfo(int *pCount, int *pId, Arg_8018399C text)
{
    DbCursor cursor;
    char name[18];

    *pCount = DbCursorGetRowCount((DbCursor *)&_MsgPlayerPickup_RosterCursor);
    *pId = _MsgPlayerPickup_iTeam;
    fn_80083E40(&cursor, 0, 0x54415453);
    fn_80084034(&cursor, _MsgPlayerPickup_iTeam, 0);
    fn_80083F88(&cursor, name, 18);
    fn_80083F68(&cursor);
    fn_801C3284(text.pParams->mpText, name, text.pParams->mLength + 1);
}

void MsgPlayerPickupGetRosterRow(int index, int *pId, Arg_8018399C text, Arg_8018399C label)
{
    char name[27];

    if (DbCursorSeek((DbCursor *)&_MsgPlayerPickup_RosterCursor, index)) {
        *pId = PlayerDbGetId(&_MsgPlayerPickup_RosterCursor);
        PlayerDbGetShortName(&_MsgPlayerPickup_RosterCursor, name, 27);
        fn_801C3284(text.pParams->mpText, name, text.pParams->mLength + 1);
        PositionAbbrevFormat(PlayerDbGetPbpo(&_MsgPlayerPickup_RosterCursor), label.pParams->mpText);
    } else {
        *pId = -1;
    }
}

int MsgPlayerPickupGetAddFlag(void)
{
    int result = 0;

    if (_MsgPlayerPickup_bCopyMode != 0) {
        result = StoryGetFlag100(_MsgPlayerPickup_cProfile);
    }
    return result;
}

int MsgPlayerPickupGetDropFlag(void)
{
    int result = 0;

    if (_MsgPlayerPickup_bCopyMode != 0) {
        result = StoryGetFlag200(_MsgPlayerPickup_cProfile);
    }
    return result;
}

void MsgPlayerPickupRegisterPlayers(void)
{
    void *pList = fn_8021EA44(1);

    if (DbCursorFirst((DbCursor *)&_MsgPlayerPickup_PoolCursor)) {
        do {
            fn_8021E2B4(pList, 10, PlayerDbGetPortraitId(&_MsgPlayerPickup_PoolCursor));
        } while (DbCursorNext((DbCursor *)&_MsgPlayerPickup_PoolCursor));
    }
    DbCursorFirst((DbCursor *)&_MsgPlayerPickup_PoolCursor);
    if (_MsgPlayerPickup_bSkipTeam == 0) {
        if (DbCursorFirst((DbCursor *)&_MsgPlayerPickup_TeamCursor)) {
            do {
                fn_8021E2B4(pList, 10, PlayerDbGetPortraitId(&_MsgPlayerPickup_TeamCursor));
            } while (DbCursorNext((DbCursor *)&_MsgPlayerPickup_TeamCursor));
        }
        DbCursorFirst((DbCursor *)&_MsgPlayerPickup_TeamCursor);
    }
}

void MsgPlayerPickupCopyTeam(int db)
{
    DbCursor cursor;
    QueryResult result;
    Desc_8008044C desc;
    int ids[13] = { -1 };
    unsigned short count = 13;
    unsigned short teamCount = 1;
    int n;
    int handle;
    int i;
    int rows;
    int value;

    _MsgPlayerPickup_iTeam = StoryTeamLoadToStats(db, 1, ids, &n);
    fn_801FCE10(&result, "use 'TATS' insert into 'MAET' * select * from \x8c\n", fn_800602E0());
    desc.mUnknown0 = 2;
    desc.mUnknown4 = 4;
    desc.mUnknown8 = _MsgPlayerPickup_iTeam;
    desc.mUnknown12 = ids[0];
    fn_8008044C(&_MsgPlayerPickup_TeamCursor, &desc, 0x54415453);
    desc.mUnknown12 = 0;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = _MsgPlayerPickup_iTeam;
    desc.mUnknown0 = 2;
    fn_8008044C(&_MsgPlayerPickup_RosterCursor, &desc, 0x54415453);
    fn_801FCE10(&result, "use 'TATS' select 'LGLT' into \x82 from 'MAET' where 'DIGT' = \x82\n", &_MsgPlayerPickup_iTeamLGLT,
                _MsgPlayerPickup_iTeam);
    rows = DbCursorGetRowCount((DbCursor *)&_MsgPlayerPickup_TeamCursor);
    _MsgPlayerPickup_bSkipTeam = rows == 0;
    _MsgPlayerPickup_bTeamFull = rows == 6;
    value = fn_800602D8();
    DbCursorOpen(&cursor, value, 0x44494750, 0, 0, 0x54415453);
    n = DbCursorGetRowCount(&cursor);
    fn_80229AA4(0x54415453, 0x59414C50, ids, &count);
    n = count;
    fn_8022C628(0x54415453, 0x4D414554, &_MsgPlayerPickup_iCopyTeam, &teamCount);
    for (i = 0; i < n; i++) {
        if (DbCursorSeek(&cursor, i)) {
            fn_8007ABA4(&cursor, 0x44494F50, ids[i]);
            fn_8007AA90(&cursor, 0x44494F50, -1);
            fn_8007ABA4(&cursor, 0x44494750, ids[i]);
            fn_8007ABA4(&cursor, 0x44494754, _MsgPlayerPickup_iCopyTeam);
        }
    }
    fn_801FCE10(&result, "use 'TATS' insert into 'YALP' * select * from \x8c\n", value);
    DbCursorClose(&cursor);
    desc.mUnknown12 = 0;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = _MsgPlayerPickup_iCopyTeam;
    desc.mUnknown0 = 2;
    fn_8008044C(&_MsgPlayerPickup_PoolCursor, &desc, 0x54415453);
    fn_801F9980(0x54415453, &handle);
    fn_801FCE10(&result, "use 'TATS' select into \x8c * from 'MAET' where 'DIGT' = \x82\n", handle, _MsgPlayerPickup_iTeam);
    fn_801FCE10(&result, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIOT' = \x82 and 'LGLT' = \x82\n", handle,
                _MsgPlayerPickup_iCopyTeam, _MsgPlayerPickup_iCopyTeam, _MsgPlayerPickup_iTeamLGLT);
    fn_801FCE10(&result, "use 'TATS' insert into 'MAET' * select * from \x8c\n", handle);
    fn_801F967C(0x54415453, handle);
    MsgPlayerPickupRegisterPlayers();
}

void MsgPlayerPickupUnregisterPlayers(void)
{
    void *pList = fn_8021EA44(1);

    if (DbCursorFirst((DbCursor *)&_MsgPlayerPickup_PoolCursor)) {
        do {
            fn_8021E72C(pList, 10, PlayerDbGetPortraitId(&_MsgPlayerPickup_PoolCursor));
        } while (DbCursorNext((DbCursor *)&_MsgPlayerPickup_PoolCursor));
    }
    if (_MsgPlayerPickup_bSkipTeam == 0) {
        if (DbCursorFirst((DbCursor *)&_MsgPlayerPickup_TeamCursor)) {
            do {
                fn_8021E72C(pList, 10, PlayerDbGetPortraitId(&_MsgPlayerPickup_TeamCursor));
            } while (DbCursorNext((DbCursor *)&_MsgPlayerPickup_TeamCursor));
        }
    }
}

void MsgPlayerPickupStep(int direction)
{
    int step;

    switch (direction) {
    case 1:
    case 2:
        step = 1;
        break;
    case 0:
    case 3:
        step = -1;
        break;
    case -2:
    case -1:
    case 5:
        step = 0;
        break;
    default:
        step = 0;
        break;
    }
    _MsgPlayerPickup_iListRow += step;
    if (_MsgPlayerPickup_iListRow < 0) {
        _MsgPlayerPickup_iListRow = _MsgPlayerPickup_iListCount - 1;
    } else if (_MsgPlayerPickup_iListRow >= _MsgPlayerPickup_iListCount) {
        _MsgPlayerPickup_iListRow = 0;
    }
    DbCursorSeek((DbCursor *)_MsgPlayerPickup_pList, _MsgPlayerPickup_iListRow);
    _MsgPlayerPickup_iShownPlayer = PlayerDbGetId(_MsgPlayerPickup_pList);
    FEPlyrSetPlayer(0, _MsgPlayerPickup_iShownPlayer, 0);
}

void MsgPlayerPickupGetPlayerInfo(int *pId, int *pFlag, int *pPosition, int *pValues)
{
    pPosition[0] = _MsgPlayerPickup_iListRow + 1;
    pPosition[1] = _MsgPlayerPickup_iListCount;
    *pId = _MsgPlayerPickup_iShownPlayer;
    *pFlag = 0;
    if (_MsgPlayerPickup_bChoosingDrop == 0 && _MsgPlayerPickup_bCopyMode == 0 && PlayerDbSeekOriginalId(&_MsgPlayerPickup_TeamCursor, *pId, 0)) {
        *pFlag = 1;
    }
    pValues[0] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 6);
    pValues[1] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 4);
    pValues[2] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 7);
    pValues[3] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 0);
    pValues[4] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 3);
    pValues[5] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 2);
    pValues[6] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 1);
    pValues[7] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 5);
    pValues[8] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 8);
    pValues[9] = PlayerDbGetBoostedRating(_MsgPlayerPickup_pList, 9);
}

void MsgPlayerPickupGetPlayerName(char *pBuffer, int size)
{
    PlayerDbGetFullName(_MsgPlayerPickup_pList, pBuffer, size);
}

void MsgPlayerPickupGetPosition(char *pText, int size)
{
    PositionAbbrevFormat(PlayerDbGetPbpo(_MsgPlayerPickup_pList), pText);
}

void MsgPlayerPickupGetHeight(char *pBuffer, int size)
{
    unsigned int height = PlayerDbGetHeight(_MsgPlayerPickup_pList);

    fn_801C2D88(pBuffer, size, "%d ft %d in", height / 12, height % 12);
}

void MsgPlayerPickupGetWeight(char *pBuffer, int size)
{
    fn_801C2D88(pBuffer, size, "%d lbs", PlayerDbGetWeight(_MsgPlayerPickup_pList));
}

int MsgPlayerPickupSelectList(void)
{
    int id;

    if (_MsgPlayerPickup_bChoosingDrop == 1) {
        id = _MsgPlayerPickup_iTeam;
        _MsgPlayerPickup_pList = &_MsgPlayerPickup_TeamCursor;
    } else {
        if (_MsgPlayerPickup_bCopyMode != 0) {
            id = _MsgPlayerPickup_iCopyTeam;
        } else {
            id = TeamFilterGet();
        }
        _MsgPlayerPickup_pList = &_MsgPlayerPickup_PoolCursor;
    }
    _MsgPlayerPickup_iListCount = DbCursorGetRowCount((DbCursor *)_MsgPlayerPickup_pList);
    _MsgPlayerPickup_iListRow = 0;
    MsgPlayerPickupStep(4);
    return id;
}

void MsgPlayerPickupSetDropPlayer(int value)
{
    _MsgPlayerPickup_iDropPlayer = value;
}

void MsgPlayerPickupSetAddPlayer(int value)
{
    _MsgPlayerPickup_iAddPlayer = value;
    _MsgPlayerPickup_bChoosingDrop = 1;
}

unsigned char MsgPlayerPickupInit(void)
{
    int found;

    _MsgPlayerPickup_bTeamFull = 0;
    _MsgPlayerPickup_iDropPlayer = 0x7FFF;
    _MsgPlayerPickup_iAddPlayer = 0x7FFF;
    _MsgPlayerPickup_cProfile = fn_8022F384(fn_8022F4BC());
    found = fn_8005FC7C();
    if (found) {
        _MsgPlayerPickup_bCopyMode = 1;
        MsgPlayerPickupCopyTeam(_MsgPlayerPickup_cProfile);
    } else {
        Desc_8008044C desc;
        DbFilter node;
        DbFilter left;
        DbFilter right;
        int count;
        int rows;
        int i;

        _MsgPlayerPickup_bCopyMode = 0;
        _MsgPlayerPickup_iTeam = fn_8018D890(_MsgPlayerPickup_cProfile, 0);
        desc.mUnknown8 = TeamFilterGet();
        desc.mUnknown4 = 1;
        desc.mUnknown0 = 2;
        fn_8008044C(&_MsgPlayerPickup_PoolCursor, &desc, 0x54415453);
        node.Set(11, &left, &right);
        left.Set(6, 0x59414C5044494754LL, 3, _MsgPlayerPickup_iTeam);
        right.SetUnknown32(6, 0x59414C5044494F50LL, 3, 0x10006);
        right.mUnknown16.mValue.mInt = 32756;
        DbCursorOpen((DbCursor *)&_MsgPlayerPickup_TeamCursor, 0x59414C50, 0x44494750, _MsgPlayerPickup_aTeamSort, &node, 0x54415453);
        desc.mUnknown12 = 0;
        desc.mUnknown4 = 1;
        desc.mUnknown8 = _MsgPlayerPickup_iTeam;
        desc.mUnknown0 = 2;
        fn_8008044C(&_MsgPlayerPickup_RosterCursor, &desc, 0x54415453);
        count = DbCursorGetRowCount((DbCursor *)&_MsgPlayerPickup_PoolCursor);
        _MsgPlayerPickup_bSkipTeam = count == 0;
        rows = DbCursorGetRowCount((DbCursor *)&_MsgPlayerPickup_TeamCursor);
        if (rows == 15) {
            _MsgPlayerPickup_bTeamFull = 1;
        } else if (rows <= 13) {
            _MsgPlayerPickup_bTeamFull = 0;
        } else {
            _MsgPlayerPickup_bTeamFull = 1;
            DbCursorFirst((DbCursor *)&_MsgPlayerPickup_TeamCursor);
            for (i = 0; i < count; i++) {
                if (PlayerDbGetOriginalId(&_MsgPlayerPickup_TeamCursor) == 32756) {
                    _MsgPlayerPickup_bTeamFull = 0;
                    break;
                }
                DbCursorNext((DbCursor *)&_MsgPlayerPickup_TeamCursor);
            }
            DbCursorFirst((DbCursor *)&_MsgPlayerPickup_TeamCursor);
        }
        ChalGetTournamentWon();
        MsgPlayerPickupRegisterPlayers();
    }
    FEPlyrShow();
    FEPlyrSetPosition(0, _MsgPlayerPickup_ModelLayout.mX, _MsgPlayerPickup_ModelLayout.mY, _MsgPlayerPickup_ModelLayout.mZ);
    FEPlyrSetScale(0, _MsgPlayerPickup_ModelLayout.mScale);
    FEPlyrSetPriority(0, _MsgPlayerPickup_ModelLayout.mValue);
    _MsgPlayerPickup_bOpen = 1;
    _MsgPlayerPickup_bChoosingDrop = 0;
    DbCursor cursor;
    fn_80083E40(&cursor, 0, 0x54415453);
    fn_80084034(&cursor, _MsgPlayerPickup_iTeam, 0);
    if (fn_80084438(&cursor) == 0) {
        unsigned char color[3];

        color[0] = fn_800841AC(&cursor);
        color[1] = fn_800841D8(&cursor);
        color[2] = fn_80084204(&cursor);
        TeamLogoRequestTint(0, 4, fn_80084158(&cursor), 172, color);
        TeamLogoRequestTint(1, 4, fn_80084158(&cursor), 172, color);
    }
    fn_80083F68(&cursor);
    return _MsgPlayerPickup_bTeamFull;
}

void MsgPlayerPickupApplyDrop(void)
{
    if (_MsgPlayerPickup_iDropPlayer != 0x7FFF) {
        if (_MsgPlayerPickup_bCopyMode != 0) {
            StoryPlayerDelete(_MsgPlayerPickup_iDropPlayer, _MsgPlayerPickup_iTeam);
            if (MsgPlayerPickupGetDropFlag()) {
                StorySetFlag200(_MsgPlayerPickup_cProfile, 0);
            }
        } else {
            fn_8018DC18(_MsgPlayerPickup_iTeam, _MsgPlayerPickup_iDropPlayer);
        }
    }
}

void MsgPlayerPickupApplyAdd(void)
{
    if (_MsgPlayerPickup_iAddPlayer != 0x7FFF) {
        int found = 0;

        if (_MsgPlayerPickup_bCopyMode == 0) {
            found = PlayerDbSeekOriginalId(&_MsgPlayerPickup_TeamCursor, _MsgPlayerPickup_iAddPlayer, 0);
        }
        if (!found) {
            if (_MsgPlayerPickup_bCopyMode != 0) {
                StoryPlayerMoveToTeam(_MsgPlayerPickup_iTeam, _MsgPlayerPickup_iAddPlayer);
                if (MsgPlayerPickupGetAddFlag()) {
                    StorySetFlag100(_MsgPlayerPickup_cProfile, 0);
                }
            } else {
                fn_8018DD4C(_MsgPlayerPickup_iTeam, _MsgPlayerPickup_iAddPlayer, 0);
            }
        }
    }
}

void MsgPlayerPickupShutdown(void)
{
    MsgPlayerPickupApplyDrop();
    MsgPlayerPickupApplyAdd();
    MsgPlayerPickupUnregisterPlayers();
    FEPlyrHide();
    fn_8008056C(&_MsgPlayerPickup_PoolCursor);
    fn_8008056C(&_MsgPlayerPickup_TeamCursor);
    fn_8008056C(&_MsgPlayerPickup_RosterCursor);
    FEPlyrLoadReset(1);
    if (_MsgPlayerPickup_bCopyMode != 0) {
        StoryTeamStoreFromStats(_MsgPlayerPickup_cProfile, _MsgPlayerPickup_iTeam);
        fn_8018C48C(0x54415453);
        _MsgPlayerPickup_bCopyMode = 0;
        fn_80060278();
    } else {
        fn_8018D8EC(_MsgPlayerPickup_cProfile, _MsgPlayerPickup_iTeam);
        fn_8018C48C(0x54415453);
    }
    TeamFilterSet(1023);
    _MsgPlayerPickup_bOpen = 0;
}

int MsgPlayerPickupHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        if (MsgPlayerPickupInit()) {
            *pArgs[0].pi = 1;
        } else {
            *pArgs[0].pi = 0;
        }
        break;
    case 0x80000002:
        MsgPlayerPickupShutdown();
        break;
    case 0x80000004: {
        int *pPosition = (int *)(pArgs[3].i + (*pArgs[3].pi + 1) * 4);
        int *pValues = (int *)(pArgs[6].i + (*pArgs[6].pi + 1) * 4);
        int direction = pArgs[0].i;
        int *pId = pArgs[1].pi;
        int *pFlag = pArgs[5].pi;

        MsgPlayerPickupStep(direction);
        MsgPlayerPickupGetPlayerInfo(pId, pFlag, pPosition, pValues);
        MsgPlayerPickupGetPlayerName(pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        MsgPlayerPickupGetPosition(pArgs[4].pParams->mpText, pArgs[4].pParams->mLength);
        MsgPlayerPickupGetHeight(pArgs[7].pParams->mpText, pArgs[7].pParams->mLength);
        MsgPlayerPickupGetWeight(pArgs[8].pParams->mpText, pArgs[8].pParams->mLength);
        break;
    }
    case 0x80000005: {
        int *pId = pArgs[0].pi;

        *pId = MsgPlayerPickupSelectList();
        break;
    }
    case 0x80000006:
        MsgPlayerPickupSetDropPlayer(pArgs[0].i);
        break;
    case 0x80000007:
        MsgPlayerPickupSetAddPlayer(pArgs[0].i);
        break;
    case 0x80000008:
        *pResult = 0;
        if (_MsgPlayerPickup_bCopyMode != 0 && MsgPlayerPickupGetAddFlag()) {
            *pResult = 1;
        }
        break;
    case 0x80000009:
        MsgPlayerPickupGetTeamInfo(pArgs[0].pi, pArgs[1].pi, pArgs[2]);
        break;
    case 0x8000000A:
        MsgPlayerPickupGetRosterRow(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3]);
        break;
    default:
        return 0;
    }
    return 1;
}

unsigned char MsgPlayerPickupIsOpen(void)
{
    return _MsgPlayerPickup_bOpen;
}
}
