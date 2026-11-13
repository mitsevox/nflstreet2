/* Playbook state of the PlayBook game module: opens the offense and defense playbook
   databases, keeps each team's current, previous, saved and audible play selections
   (formation, set and play with their records and formation spots), and answers the rest of
   the game's questions about the chosen play. */

#include "game/ResLoad.h"
#include "game/PlayCallScript.h"
#include "game/Class_80148A58.h"
#include "game/PlayBookGetPlay.h"
#include "game/DbCursor.h"
#include "game/PlayBookDb.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/fn_800B65A0.h"
#include "game/fn_80177FE0.h"

#include "game/PlayBookTeam.h"

/* Allocated through fn_80238174 under the id 'plbk' (PlayBookAlloc). */
struct PlayBook_t {
    unsigned int mUnknown0;
    PlayBookTeam_t mUnknown4[2];
    char mUnknownD2EC[0x28];
    unsigned char mUnknownD314[43][4];
};



extern "C" {
int PlayBookDbOpen(unsigned int id, int a, int b, int c, int d, int e);
void PlayBookDbClose(unsigned int id, int a);
void PlayBookDbGetPlayPath(int tag, int a, int *pResult);
void PlayBookDbSetAudiblePlay(int tag, int a, int b);
void PlayBookDbPickAIPlayPath(int team, int tag, int kind, int *pResult);
int PlayBookDbHasAIPlay(int tag, int a, int b);
void AudibleDbOpen(DbCursor *pCursor);
void AudibleDbClose(DbCursor *pCursor);
int AudibleDbSeekFormation(DbCursor *pCursor, int key);
unsigned char AudibleDbGetPlayIndex(DbCursor *pCursor, int column);
unsigned char PlaybookSideGetLoaded(int index);
void fn_800B508C(unsigned char index);
int fn_800BA6F8(void);
QueryCursor fn_800C0750(int index, unsigned short *pValues);
void fn_800C07C4(QueryCursor cursor);
void fn_800C07F0(QueryCursor cursor, int index, unsigned short *pValues);
int fn_80164ED8(PlayBookFormation_t *pObject, PlayBookPlay_t *pRecord, int index, unsigned char *pOut, unsigned char flag);
int fn_80165000(PlayBookFormation_t *pObject, PlayBookPlay_t *pRecord, int index, unsigned char *pOut, unsigned char flag);
void PlayArtSetFlip(signed char team, int a, int b);
void PlayBookOffsetSpots(Vec2_t *pPoints, int count);
int PlayAutoFlip(int team);
int fn_801485D4(void);
int fn_801486A0(void);
int fn_80177F70(void);
int fn_80178308(void);
float fn_80178A2C(void);
int fn_80178E10(void);
void fn_80179144(int a);
void fn_8017916C(void);
int MemFill(void *pDest, int size, int value, int width);
void fn_801F9FA4(int tag, int index, int column);
int fn_801FA038(int tag, int index, int column);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
}

static PlayBook_t *_PlayBook_pData;

extern "C" {
void PlayBookPostInit(void);
int PlayBookCompareData(void *p, void *q);
void PlayBookSetupTeam(int team, int kind);
void PlayBookReadFormation(int tag, int team, unsigned char kind, unsigned int index, PlayBookFormation_t *pObject);
void PlayBookReadSet(int tag, int handle, unsigned int index, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject);
void PlayBookSelectFormation(int team, unsigned int a, unsigned int b, int c);
void PlayBookLoadFormation(int team);
void PlayBookLoadSet(int team, int flag);
void PlayBookReloadSet(int team);
void PlayBookClearAudibles(int team, int a, int flag);
void PlayBookOpenDatabases(int a, int b, int c, int d, int e, int f);
void PlayBookLoadCurrentPlay(int team);
void PlayBookLoadAudibles(int team);
void PlayBookAlloc(void);
void PlayBookClear(void);
void PlayBookLoadAudibleTable(void);
void PlayBookOpenAndRegister(int a, int b, int c, int d, int e, int f, int g, int h);
void PlayBookReopen(int a, int b, int c, int d, int e, int f, int g);
void PlayBookCloseDatabases(int a);
void PlayBookSetFormationType(int team, int kind);
PlayBookFormation_t *PlayBookGetFormation(int team);
PlayBookPlay_t *PlayBookGetSavedPlay(int team);
void PlayBookSetIndices(unsigned char team, unsigned char a, unsigned char b, unsigned char c);
void PlayBookPickPage(int team, int a, int b, int c);
unsigned int PlayBookGetSetIndex(int team);
unsigned int PlayBookGetFormationIndex(int team);
unsigned int PlayBookGetPlayIndex(int team);
unsigned int PlayBookGetLoadFlags(void);
void PlayBookSetLoadFlags(unsigned int flags);
void PlayBookClearLoadFlags(unsigned int flags);
void PlayBookSelectAudible(int team, unsigned int index);
PlayBookPlay_t *PlayBookGetAudiblePlay(int team, int index);
void PlayBookSaveSelection(int team);
void PlayBookRestoreSelection(int team);
void GetPlayerPosition(unsigned char team, int index, float *pX, float *pY);
void PlayBookSetSelection(int team, int kind, unsigned int a, unsigned int b, unsigned int c);
void PlayBookSelectPlayById(int team, int a);
void PlayBookPickPlay(int team, int kind);
int PlayBookIsAiPlay(int team, int a, int b);
void PlayBookSetupTeams(void);
void PlayBookSetAudible(int which, int team, int a, int b, int c);
void PlayBookToggleFlip(int team);
unsigned int PlayBookLoadPlayById(int team, int a, int b);
int PlayBookGetReceiver(int team, int index, unsigned char *pOut);
int PlayBookSetReceiverOption(int team, int index, unsigned char *pOut);
int PlayBookGetDatabase(int team);
PlayBookTeam_t *PlayBookGetTeam(int team);
}

void PlayBookOffsetSpots(Vec2_t *pPoints, int count)
{
    while (count--) {
        pPoints[count].mX = (int)pPoints[count].mX - 100;
        pPoints[count].mY = (int)pPoints[count].mY - 150;
    }
}

void PlayBookPostInit(void)
{
}

int PlayBookCompareData(void *p, void *q)
{
    if (q == 0) {
        return 0;
    }
    return fn_80238258(p, q, sizeof(PlayBook_t));
}

void PlayBookSetupTeam(int team, int kind)
{
    unsigned char index = team;

    PlayBookSetFormationType(index, kind);
    PlayBookLoadAudibles(index);
    PlayBookSelectAudible(index, 0);
    PlayBookLoadCurrentPlay(index);
}

void PlayBookReadFormation(int tag, int team, unsigned char kind, unsigned int index, PlayBookFormation_t *pObject)
{
    PlayBookDbLoadFormation(tag, kind, index, pObject);
}

void PlayBookReadSet(int tag, int handle, unsigned int index, PlayBookTeam_t *pTeam, PlayBookSet_t *pObject)
{
    PlayBookDbLoadSetByOrder(tag, handle, index, pTeam, pObject);
}

void PlayBookSelectFormation(int team, unsigned int a, unsigned int b, int c)
{
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[team];

    pTeam->mUnknown20.mUnknown0 = a;
    pTeam->mUnknown20.mUnknown4 = b;
    PlayBookLoadFormation(team);
    PlayBookReloadSet(team);
}

void PlayBookLoadFormation(int team)
{
    int tag = _PlayBook_pData->mUnknown4[team].mUnknown8;
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[team];
    unsigned int index = pTeam->mUnknown20.mUnknown0;
    PlayBookFormation_t *pObject = &pTeam->mUnknown20.mUnknown14;
    unsigned int flags = PlayBookGetLoadFlags();

    PlayBookSetLoadFlags(3);
    PlayBookReadFormation(tag, team, _PlayBook_pData->mUnknown4[team].mUnknownC, index, pObject);
    pTeam->mUnknown14 = PlayBookDbCountSets(tag, pTeam->mUnknown20.mUnknown14.mUnknown0);
    PlayBookClearLoadFlags(3);
    PlayBookSetLoadFlags(flags);
}

void PlayBookLoadSet(int team, int flag)
{
    int tag = _PlayBook_pData->mUnknown4[team].mUnknown8;
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[team];
    PlayBookSet_t *pObject = &pTeam->mUnknown20.mUnknown14.mUnknown8;
    unsigned int index = pTeam->mUnknown20.mUnknown4;
    unsigned int flags = PlayBookGetLoadFlags();

    PlayBookSetLoadFlags(7);
    if (flag) {
        PlayBookSetLoadFlags(8);
    }
    PlayBookReadSet(tag, pTeam->mUnknown20.mUnknown14.mUnknown0, index, pTeam, pObject);
    PlayBookClearLoadFlags(15);
    PlayBookSetLoadFlags(flags);
    PlayBookOffsetSpots(pTeam->mUnknown693C, 7);
    pTeam->mUnknown18 = PlayBookDbCountPlays(tag, pTeam->mUnknown20.mUnknown14.mUnknown8.mUnknown0);
}

void PlayBookReloadSet(int team)
{
    int tag = _PlayBook_pData->mUnknown4[team].mUnknown8;
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[team];

    PlayBookReadSet(tag, pTeam->mUnknown20.mUnknown14.mUnknown0, pTeam->mUnknown20.mUnknown4, pTeam,
                &pTeam->mUnknown20.mUnknown14.mUnknown8);
    PlayBookOffsetSpots(pTeam->mUnknown693C, 7);
    pTeam->mUnknown18 = PlayBookDbCountPlays(tag, pTeam->mUnknown20.mUnknown14.mUnknown8.mUnknown0);
}

void PlayBookClearAudibles(int team, int a, int flag)
{
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (flag) {
            PlayBookSetAudible(1, team, i, 0xFFFF, 0);
        } else {
            PlayBookSetAudible(0, team, i, 0xFFFF, 0);
        }
    }
}

void PlayBookOpenDatabases(int a, int b, int c, int d, int e, int f)
{
    if (a != 0x3FF) {
        int first;
        int second;

        _PlayBook_pData->mUnknown4[0].mUnknown0 = 0x31544250;
        _PlayBook_pData->mUnknown4[0].mUnknown4 = 0x31444250;
        first = 2;
        second = 1;
        if (fn_801485D4()) {
            first = fn_80148A58()->mUnknown0;
            second = fn_80148A58()->mUnknown4;
        }
        PlayBookDbOpen(0x31544250, first, 4, 0, 0, 1);
        PlayBookDbOpen(0x31444250, second, 4, 0, 0, 1);
    } else {
        _PlayBook_pData->mUnknown4[0].mUnknown4 = _PlayBook_pData->mUnknown4[0].mUnknown0 = -1;
    }
    if (b != 0x3FF) {
        _PlayBook_pData->mUnknown4[1].mUnknown0 = 0x31544250;
        _PlayBook_pData->mUnknown4[1].mUnknown4 = 0x31444250;
    } else {
        _PlayBook_pData->mUnknown4[1].mUnknown4 = _PlayBook_pData->mUnknown4[1].mUnknown0 = -1;
    }
    fn_801FCE10(0, "use \x8c create \x8b index on 'LASP' order by 'LASP' asc\n", 0x31544250, 0x4C415350);
    fn_801FCE10(0, "use \x8c create \x8b index on 'SYLP' order by 'LYLP' asc and 'osop' asc\n", 0x31544250, 0x4C594C50);
    fn_801FCE10(0, "use \x8c create \x8b index on 'LASP' order by 'LASP' asc\n", 0x31444250, 0x4C415350);
    fn_801FCE10(0, "use \x8c create \x8b index on 'SYLP' order by 'LYLP' asc and 'osop' asc\n", 0x31444250, 0x4C594C50);
}

void PlayBookLoadCurrentPlay(int team)
{
    unsigned int flags = PlayBookGetLoadFlags();
    int tag;
    PlayBookTeam_t *pTeam;
    PlayBookSel_t *pState;
    PlayBookFormation_t *pObject;
    PlayBookSet_t *pEntry;
    PlayBookPlay_t *pRecord;

    PlayBookSetLoadFlags(3);
    tag = _PlayBook_pData->mUnknown4[team].mUnknown8;
    pTeam = &_PlayBook_pData->mUnknown4[team];
    pState = &pTeam->mUnknown20;
    pObject = &pState->mUnknown14;
    PlayBookReadFormation(tag, team, _PlayBook_pData->mUnknown4[team].mUnknownC, pState->mUnknown0, pObject);
    pEntry = &pObject->mUnknown8;
    pRecord = &pState->mUnknownCF8;
    PlayBookClearLoadFlags(3);
    PlayBookReadSet(tag, pObject->mUnknown0, pState->mUnknown4, &_PlayBook_pData->mUnknown4[team], pEntry);
    PlayBookSetLoadFlags(3);
    PlayBookDbLoadSet(tag, PlayBookDbLoadPlay(tag, pEntry->mUnknown0, pState->mUnknown8, pRecord), pTeam, pEntry);
    if ((pObject->mUnknown8.mUnknown14 & 1) && (pRecord->mUnknown18 & 1)) {
        pEntry->mUnknownF = pState->mUnknown10;
    } else {
        pEntry->mUnknownF = 0;
    }
    PlayBookClearLoadFlags(3);
    PlayBookSetLoadFlags(flags);
    if (fn_80178308() == team && fn_800B65A0(team) == 0xFF && !fn_800BA6F8() &&
        (!fn_801485D4() || fn_801486A0() != 2)) {
        PlayAutoFlip(team);
    }
}

void PlayBookLoadAudibles(int team)
{
    unsigned int flags = PlayBookGetLoadFlags();
    int count = _PlayBook_pData->mUnknown4[team].mUnknown20.mUnknown14.mUnknown8.mUnknown4;
    int tag;
    int kind;
    unsigned char swap;
    unsigned int i;

    if (fn_80178308() == team) {
        tag = 0x31544250;
        kind = 1;
    } else {
        tag = 0x31444250;
        kind = 11;
    }
    swap = PlayBookGetFormation(team)->mUnknown8.mUnknownF;
    for (i = 0; i <= 3; i++) {
        PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown2D2C[i];
        unsigned char value;
        PlayBookTeam_t *pOwner;

        if (swap) {
            if (i == 3) {
                value = _PlayBook_pData->mUnknownD314[count - 1][2];
            } else if (i == 2) {
                value = _PlayBook_pData->mUnknownD314[count - 1][3];
            } else {
                value = _PlayBook_pData->mUnknownD314[count - 1][i];
            }
        } else {
            value = _PlayBook_pData->mUnknownD314[count - 1][i];
        }
        PlayBookSetLoadFlags(3);
        pState->mUnknown10 = 0;
        pState->mUnknown8 = value;
        pState->mUnknown0 = 0;
        pState->mUnknown4 = 0;
        pState->mUnknownC = value / 3;
        PlayBookDbLoadFormation(tag, kind, 0, &pState->mUnknown14);
        PlayBookClearLoadFlags(3);
        pOwner = PlayBookGetTeam(0);
        PlayBookDbLoadSetByOrder(tag, pState->mUnknown14.mUnknown0, pState->mUnknown4, pOwner, &pState->mUnknown14.mUnknown8);
        PlayBookSetLoadFlags(3);
        PlayBookDbLoadSet(tag, PlayBookDbLoadPlay(tag, pState->mUnknown14.mUnknown8.mUnknown0, pState->mUnknown8, &pState->mUnknownCF8),
                    pOwner, &pState->mUnknown14.mUnknown8);
        pState->mUnknown14.mUnknown8.mUnknownF = swap;
        PlayBookClearLoadFlags(3);
        PlayBookSetLoadFlags(flags);
    }
    _PlayBook_pData->mUnknown4[team].mUnknown1C = 4;
}

void PlayBookAlloc(void)
{
    void *pHandle = fn_80238174(0, (void **)&_PlayBook_pData, sizeof(PlayBook_t), 0, 0x706C626B);

    fn_80238234(pHandle, 0, 0, 0, PlayBookCompareData);
    fn_802381E0(pHandle);
}

void PlayBookClear(void)
{
    if (_PlayBook_pData) {
        MemFill(_PlayBook_pData, sizeof(PlayBook_t), 0, 4);
        _PlayBook_pData->mUnknown4[1].mUnknown4 = _PlayBook_pData->mUnknown4[1].mUnknown0 =
            _PlayBook_pData->mUnknown4[0].mUnknown4 = _PlayBook_pData->mUnknown4[0].mUnknown0 = -1;
    }
}

void PlayBookLoadAudibleTable(void)
{
    if (fn_80178E10()) {
        DbCursor cursor;
        unsigned int key;

        AudibleDbOpen(&cursor);
        for (key = 1; key <= 43; key++) {
            if (AudibleDbSeekFormation(&cursor, key)) {
                unsigned int i;

                for (i = 0; i <= 3; i++) {
                    _PlayBook_pData->mUnknownD314[key - 1][i] = AudibleDbGetPlayIndex(&cursor, i);
                }
            }
        }
        AudibleDbClose(&cursor);
    }
}

void PlayBookOpenAndRegister(int a, int b, int c, int d, int e, int f, int g, int h)
{
    PlayBookCloseDatabases(h);
    PlayBookOpenDatabases(b, c, d, e, f, g);
    PlayBookClearAudibles(0, d, 1);
    PlayBookClearAudibles(1, e, 1);
    PlayBookClearAudibles(0, f, 0);
    PlayBookClearAudibles(1, g, 0);
    if (h) {
        PlayCallScriptDesc_t desc;

        desc.mUnknown0 = ResLoad((void *)a, 4, 1);
        desc.mUnknown4 = (short *)_PlayBook_pData->mUnknownD2EC;
        desc.mUnknown8 = PlayCallOffenseCommand;
        desc.mUnknownC = PlayCallDefenseCommand;
        PlayCallScriptInit(&desc);
    }
}

void PlayBookReopen(int a, int b, int c, int d, int e, int f, int g)
{
    PlayBookCloseDatabases(g);
    PlayBookOpenDatabases(a, b, c, d, e, f);
    PlayBookClearAudibles(0, c, 1);
    PlayBookClearAudibles(1, d, 1);
    PlayBookClearAudibles(0, e, 0);
    PlayBookClearAudibles(1, f, 0);
}

void PlayBookCloseDatabases(int a)
{
    if (!fn_801FA038(0x31544250, 0x4C415350, 0x4C415350)) {
        fn_801F9FA4(0x31544250, 0x4C415350, 0x4C415350);
    }
    if (!fn_801FA038(0x31544250, 0x53594C50, 0x4C594C50)) {
        fn_801F9FA4(0x31544250, 0x53594C50, 0x4C594C50);
    }
    if (!fn_801FA038(0x31444250, 0x4C415350, 0x4C415350)) {
        fn_801F9FA4(0x31444250, 0x4C415350, 0x4C415350);
    }
    if (!fn_801FA038(0x31444250, 0x53594C50, 0x4C594C50)) {
        fn_801F9FA4(0x31444250, 0x53594C50, 0x4C594C50);
    }
    if (_PlayBook_pData->mUnknown4[0].mUnknown4 != -1) {
        PlayBookDbClose(0x31444250, PlaybookSideGetLoaded(1));
        _PlayBook_pData->mUnknown4[0].mUnknown4 = -1;
    }
    if (_PlayBook_pData->mUnknown4[0].mUnknown0 != -1) {
        PlayBookDbClose(0x31544250, PlaybookSideGetLoaded(0));
        _PlayBook_pData->mUnknown4[0].mUnknown0 = -1;
    }
}

void PlayBookSetFormationType(int team, int kind)
{
    int tag;

    switch (kind) {
    case 1:
        _PlayBook_pData->mUnknown4[team].mUnknown8 = _PlayBook_pData->mUnknown4[team].mUnknown0;
        break;
    case 11:
        _PlayBook_pData->mUnknown4[team].mUnknown8 = _PlayBook_pData->mUnknown4[team].mUnknown4;
        break;
    }
    tag = _PlayBook_pData->mUnknown4[team].mUnknown8;
    _PlayBook_pData->mUnknown4[team].mUnknownC = kind;
    _PlayBook_pData->mUnknown4[team].mUnknown20.mUnknown10 = 0;
    _PlayBook_pData->mUnknown4[team].mUnknown10 = PlayBookDbCountFormations(tag, kind);
    PlayArtSetFlip(team, 0, -1);
    PlayBookSelectFormation(team, 0, 0, 1);
}

PlayBookFormation_t *PlayBookGetFormation(int team)
{
    return &_PlayBook_pData->mUnknown4[team].mUnknown20.mUnknown14;
}

PlayBookPlay_t *PlayBookGetPlay(int team)
{
    return &_PlayBook_pData->mUnknown4[team].mUnknown20.mUnknownCF8;
}

PlayBookPlay_t *PlayBookGetSavedPlay(int team)
{
    return &_PlayBook_pData->mUnknown4[team].mUnknown1E28.mUnknownCF8;
}

void PlayBookSetIndices(unsigned char team, unsigned char a, unsigned char b, unsigned char c)
{
    PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;

    if (a < _PlayBook_pData->mUnknown4[team].mUnknown10) {
        pState->mUnknown0 = a;
    } else {
        pState->mUnknown0 = _PlayBook_pData->mUnknown4[team].mUnknown10 - 1;
    }
    if (b < _PlayBook_pData->mUnknown4[team].mUnknown14) {
        pState->mUnknown4 = b;
    } else {
        pState->mUnknown4 = _PlayBook_pData->mUnknown4[team].mUnknown14 - 1;
    }
    if (c < _PlayBook_pData->mUnknown4[team].mUnknown18) {
        pState->mUnknown8 = c;
    } else {
        pState->mUnknown8 = _PlayBook_pData->mUnknown4[team].mUnknown18 - 1;
    }
    pState->mUnknownC = pState->mUnknown8 / 3;
}

void PlayBookPickPage(int team, int a, int b, int c)
{
    if (a == -1 && b == -1) {
        int mode = fn_80177F70();

        if (mode == 4 || mode == 6) {
            PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;
            Point_8017886C point;

            point = fn_80177FE0();

            if (mode == 6 || !(point.mY < fn_80178A2C() - 15.0f)) {
                pState->mUnknownC = 2;
            } else {
                pState->mUnknownC = 0;
            }
        }
    }
}

unsigned int PlayBookGetSetIndex(int team)
{
    PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;

    return pState->mUnknown4;
}

unsigned int PlayBookGetFormationIndex(int team)
{
    PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;

    return pState->mUnknown0;
}

unsigned int PlayBookGetPlayIndex(int team)
{
    PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;

    return pState->mUnknown8;
}

unsigned int PlayBookGetLoadFlags(void)
{
    return _PlayBook_pData->mUnknown0;
}

void PlayBookSetLoadFlags(unsigned int flags)
{
    _PlayBook_pData->mUnknown0 |= flags;
}

void PlayBookClearLoadFlags(unsigned int flags)
{
    _PlayBook_pData->mUnknown0 &= ~flags;
}

void PlayBookSelectAudible(int team, unsigned int index)
{
    PlayBookTeam_t *pTeam;
    PlayBookSel_t *pState;

    if (index >= _PlayBook_pData->mUnknown4[team].mUnknown1C) {
        index = 0;
    }
    pTeam = &_PlayBook_pData->mUnknown4[team];
    pState = &pTeam->mUnknown2D2C[index];
    pTeam->mUnknown20 = *pState;
}

PlayBookPlay_t *PlayBookGetAudiblePlay(int team, int index)
{
    return &_PlayBook_pData->mUnknown4[team].mUnknown2D2C[index].mUnknownCF8;
}

void PlayBookSaveSelection(int team)
{
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[team];

    pTeam->mUnknown1E28 = pTeam->mUnknown20;
}

void PlayBookRestoreSelection(int team)
{
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[team];

    pTeam->mUnknown20 = pTeam->mUnknown1E28;
}

void GetPlayerPosition(unsigned char team, int index, float *pX, float *pY)
{
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[team];

    if (pTeam->mUnknown20.mUnknown10 == 1) {
        index = pTeam->mUnknown20.mUnknown14.mUnknown8.mUnknown84[0][index].mUnknownB;
    }
    if (pX) {
        *pX = pTeam->mUnknown693C[index].mX;
        if (pTeam->mUnknown20.mUnknown10 == 1) {
            *pX *= -1.0f;
        }
    }
    if (pY) {
        *pY = pTeam->mUnknown693C[index].mY + 9.0f;
    }
}

void PlayBookSetSelection(int team, int kind, unsigned int a, unsigned int b, unsigned int c)
{
    PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;

    _PlayBook_pData->mUnknown4[team].mUnknownF24 = _PlayBook_pData->mUnknown4[team].mUnknown20;
    _PlayBook_pData->mUnknown4[team].mUnknownC = kind;
    pState->mUnknown0 = a;
    pState->mUnknown4 = b;
    pState->mUnknown8 = c;
}

void PlayBookSelectPlayById(int team, int a)
{
    int result[4];

    PlayBookDbGetPlayPath(_PlayBook_pData->mUnknown4[team].mUnknown8, a, result);
    PlayBookSetSelection(team, result[3], result[0], result[1], result[2]);
}

void PlayBookPickPlay(int team, int kind)
{
    int tag = _PlayBook_pData->mUnknown4[team].mUnknown8;
    int result[4];

    if (fn_800B65A0(team) == 0xFF) {
        if (kind == 14) {
            fn_80179144(2);
            fn_8017916C();
        } else if (kind == 17) {
            fn_80179144(1);
            fn_8017916C();
        }
    }
    PlayBookDbPickAIPlayPath(team, tag, kind, result);
    _PlayBook_pData->mUnknown4[team].mUnknownC = result[3];
    PlayBookSetSelection(team, result[3], result[0], result[1], result[2]);
}

int PlayBookIsAiPlay(int team, int a, int b)
{
    return PlayBookDbHasAIPlay(_PlayBook_pData->mUnknown4[team].mUnknown8, a, b);
}

void PlayBookSetupTeams(void)
{
    int team;

    for (team = 0; team <= 1; team++) {
        unsigned short values[7];
        QueryCursor cursor;

        PlayBookSetupTeam(team, 1);
        cursor = fn_800C0750((unsigned char)team, values);
        fn_800C07F0(cursor, (unsigned char)team, values);
        fn_800C07C4(cursor);
        fn_800B508C(team);
    }
}

void PlayBookSetAudible(int which, int team, int a, int b, int c)
{
    int tag;

    if (team == 0) {
        tag = which ? 0x31544250 : 0x31444250;
    } else {
        tag = which ? 0x32544250 : 0x32444250;
    }
    PlayBookDbSetAudiblePlay(tag, a, b);
}

void PlayBookToggleFlip(int team)
{
    PlayBookSel_t *pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;

    pState->mUnknown10 = !pState->mUnknown10;
}

unsigned int PlayBookLoadPlayById(int team, int a, int b)
{
    PlayBookSel_t *pState;

    PlayBookSelectPlayById(team, a);
    PlayBookLoadFormation(team);
    PlayBookLoadSet(team, 1);
    pState = &_PlayBook_pData->mUnknown4[team].mUnknown20;
    pState->mUnknownC = pState->mUnknown8 / 3;
    return pState->mUnknown8;
}

int PlayBookGetReceiver(int team, int index, unsigned char *pOut)
{
    PlayBookPlay_t *pRecord = PlayBookGetPlay(team);
    PlayBookFormation_t *pObject = PlayBookGetFormation(team);

    return fn_80164ED8(pObject, pRecord, index, pOut, pObject->mUnknown8.mUnknownF);
}

int PlayBookSetReceiverOption(int team, int index, unsigned char *pOut)
{
    PlayBookPlay_t *pRecord = PlayBookGetPlay(team);
    PlayBookFormation_t *pObject = PlayBookGetFormation(team);

    return fn_80165000(pObject, pRecord, index, pOut, pObject->mUnknown8.mUnknownF);
}

int PlayBookGetDatabase(int team)
{
    return _PlayBook_pData->mUnknown4[team].mUnknown8;
}

PlayBookTeam_t *PlayBookGetTeam(int team)
{
    return &_PlayBook_pData->mUnknown4[team];
}
