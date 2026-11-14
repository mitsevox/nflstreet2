/* Playbook and play calling of the PlayBook and PlayTrack game modules. Opens the offense and
   defense playbook databases and keeps each team's current, previous, saved and audible play
   selections; fills the game situation for the AI play-call script, runs its byte-code streams and
   carries out the plays they pick; keeps a history of each team's recent plays and their results,
   and weights the AI's candidate plays by it; randomly mirrors a reloaded play; and builds play-art
   routes from route commands (unused in this build). */

#include <math.h>
#include <string.h>
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
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80178D18.h"
#include "game/fn_802372EC.h"
#include "game/PlaySet.h"
#include "game/PlayCandidate.h"
#include "game/Challenge.h"
#include "game/PlayTrack.h"
#include "game/Item_80097440.h"
#include "game/fn_80227638.h"

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
void PlayBookTurnPage(int team, int delta);
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

void PlayBookTurnPage(int team, int delta)
{
    PlayBookTeam_t *pTeam = &_PlayBook_pData->mUnknown4[(unsigned char)team];

    if (delta == 0) {
        int mode = fn_80177F70();

        if ((mode == 4 || mode == 6) && strcmp(pTeam->mUnknown20.mUnknown14.mUnknownCB0, "Special Teams") == 0) {
            Point_8017886C point = fn_80177FE0();

            if (mode == 6 || !(point.mY < fn_80178A2C() - 15.0f)) {
                pTeam->mUnknown20.mUnknownC = 2;
                return;
            }
        }
        pTeam->mUnknown20.mUnknownC = 0;
    } else {
        int page = pTeam->mUnknown20.mUnknownC + delta;
        int pages = (pTeam->mUnknown18 + 2) / 3;

        if (page >= pages) {
            page = 0;
        } else if (page < 0) {
            page = pages - 1;
        }
        pTeam->mUnknown20.mUnknownC = page;
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

extern "C" {
int fn_801486A0(void);
void PlayBookLoadCurrentPlay(int team);
void fn_800FBAA8(void);
void fn_8011F3A8(void);
void PlayRealignTeam(int team);
int fn_80178308(void);
int fn_80178320(void);
void fn_800B0DA4(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
void fn_800B49EC(short *ratings, void *p);
void fn_800B4798(short *ratings, int team, unsigned char index, void *p);
void fn_800A6F04(int team);
int fn_801788D8(int *p);
int fn_801787DC(int team);
int fn_80177F70(void);
float fn_80178A2C(void);
float fn_80178298(void);
int fn_800A8444(int team);
void PlayBookPickPlay(int team, int kind);
void PlayBookSelectPlayById(int team, int kind);
int PlayBookIsAiPlay(int team, int kind, int value);
void fn_800C02EC(void *p, int event);
void fn_800C02F8(void *p, int event);
void fn_800B4300(int value);
void fn_800B43AC(int value);
extern void *lbl_803EABA4;

int PlayCallGetPlaybookId(void)
{
    switch (fn_801486A0()) {
    case 4: return 1;
    case 3: return 4;
    case 2: return fn_80148A58()->vfn_05(0) == 1 ? 2 : 3;
    }
    return 0;
}

void PlayCallApplyPlay(int team, int value)
{
    if (value & 0x8000) {
        PlayBookLoadCurrentPlay(team);
        fn_800FBAA8();
        fn_8011F3A8();
        PlayRealignTeam(team);
        if (team == fn_80178308())
            fn_800B0DA4();
        for (int t = 0; t < 2; ++t) {
            PlayBookFormation_t *pBook = PlayBookGetFormation((unsigned char)t);
            int count = fn_80178D18((unsigned char)t);
            for (int i = 0; i < count; ++i) {
                Object_80039F5C *p = PlyrGet((unsigned char)t, i);
                unsigned char a, b;
                PlaySetGetEntryRoles(pBook, i, &a, &b);
                p->mUnknown2914 = a;
                fn_800B49EC(p->mRatings, p->mUnknown3020);
                fn_800B4798(p->mRatings, (unsigned char)t, i, &p->mUnknown2900);
            }
            fn_800A6F04((unsigned char)t);
        }
    }
}

void PlayCallFillOffenseExtra(short *p) {}
void PlayCallFillDefenseExtra(short *p) {}

void PlayCallFillSituation(short *p)
{
    Point_8017886C pos;
    pos = fn_80177FE0();
    int offense = fn_80178308();
    int defense = fn_80178320();
    p[15] = fn_800B65A0(offense);
    p[16] = fn_800B65A0(defense);
    int value;
    if (fn_801788D8(&value) == 0)
        p[0] = (unsigned short)value - fn_801787DC(offense);
    else
        p[0] = -1;
    p[1] = fn_80177F70();
    p[3] = (int)(fn_80178A2C() - pos.mY);
    p[4] = (int)(pos.mY + fn_80178A2C());
    p[7] = p[6] = 0;
    switch (fn_80177F70()) {
    case 0:
        p[1] = 0;
        p[6] = fn_8017886C()->mUnknown1D == -2 ? 2 : 1;
        p[7] = 0;
        break;
    case 3:
    case 4:
    case 5: break;
    case 6:
        p[1] = 4;
        p[6] = 0;
        p[7] = 1;
        break;
    }
    float line = fn_80178298();
    p[2] = (int)(line - fn_80177FE0().mY);
    p[5] = fn_802372EC(0, 100);
    p[8] = *(unsigned short *)((char *)PlayBookGetFormation(offense) + 26);
    p[9] = 0;
    p[13] = p[12] = 50;
    p[10] = *(unsigned short *)((char *)PlayBookGetPlay(offense) + 6);
    p[11] = *(unsigned short *)((char *)PlayBookGetPlay(defense) + 6);
    if (fn_800A8444(fn_80178320()))
        p[14] = 1;
    else
        p[14] = 0;
}

void PlayCallFillOffenseSituation(short *p, short mode)
{
    PlayCallFillSituation(p);
    p[9] = fn_80178308();
    if (mode == 4)
        PlayCallFillOffenseExtra(p);
}

void PlayCallFillDefenseSituation(short *p, short mode)
{
    PlayCallFillSituation(p);
    p[9] = fn_80178320();
    if (fn_80177F70() == 6)
        p[1] = 1;
    if (mode == 4)
        PlayCallFillDefenseExtra(p);
}

int PlayCallOffenseCommand(int id, short *p, int value)
{
    int result = 0;
    if (p[18] > 0)
        p[18] = -1;
    int team = fn_80178308();
    switch (id) {
    case 0: PlayCallFillOffenseSituation(p, value); break;
    case 1:
    case 10: break;
    case 8:
        PlayBookPickPlay(team, value & ~0x8000);
        PlayCallApplyPlay(team, value);
        break;
    case 9:
        PlayBookSelectPlayById(team, value & ~0x8000);
        PlayCallApplyPlay(team, value);
        break;
    case 4: fn_800C02EC(lbl_803EABA4, 39); break;
    case 6: p[19] = 255; break;
    case 7: p[19] = 254; break;
    case 11:
        if ((value & 0xC0) == 0xC0)
            team = (unsigned char)(team ^ 1);
        result = PlayBookIsAiPlay(team, value & ~0xC0, p[17]);
        break;
    case 2:
        fn_800B4300(0);
        if (fn_800B65A0(fn_80178308()) == 255)
            fn_800C02F8(lbl_803EABA4, 2);
        break;
    case 3:
        fn_800B4300(1);
        fn_800C02F8(lbl_803EABA4, 1);
        break;
    case 5:
        fn_800B43AC(1);
        if (fn_800B65A0(fn_80178308()) == 255)
            fn_800C02F8(lbl_803EABA4, 2);
        break;
    case 12:
        fn_800B43AC(2);
        if (fn_800B65A0(fn_80178308()) == 255)
            fn_800C02F8(lbl_803EABA4, 2);
        break;
    }
    return result;
}

int PlayCallDefenseCommand(int id, short *p, int value)
{
    int result = 0;
    int team = fn_80178320();
    switch (id) {
    case 0: PlayCallFillDefenseSituation(p, value); break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 10:
    case 12: break;
    case 8:
        PlayBookPickPlay(team, value & ~0x8000);
        PlayCallApplyPlay(team, value);
        break;
    case 9:
        PlayBookSelectPlayById(team, value & ~0x8000);
        PlayCallApplyPlay(team, value);
        break;
    case 11:
        if ((value & 0xC0) == 0x40)
            team = (unsigned char)(team ^ 1);
        result = PlayBookIsAiPlay(team, value & ~0xC0, p[17]);
        break;
    case 6: p[19] = 255; break;
    case 7: p[19] = 254; break;
    }
    return result;
}
}

struct PlayCallScriptState_t {
    PlayCallScriptDesc_t mUnknown0;
    unsigned char **mUnknown16;
    unsigned char **mUnknown20;
};

static PlayCallScriptState_t _PlayCallScript_sState;

extern "C" {

int PlayCallScriptReadValue(unsigned char **pp, short *pRecord)
{
    unsigned char first = *(*pp)++;
    if ((first & 0xC0) == 0x80)
        return pRecord[first & 0x7F];
    int value = *(*pp)++;
    value += first << 8;
    if (value & 0x2000)
        value |= 0xFFFFC000;
    return value;
}

unsigned char *PlayCallScriptGetStream(unsigned char **pTable, int index)
{
    return pTable[index];
}

void PlayCallScriptRelocate(int *pTable, int count)
{
    for (int i = 0; i < count; ++i)
        pTable[i] = (int)pTable + pTable[i];
}

int PlayCallScriptIsEqual(int a, int b) { return a == b; }
int PlayCallScriptIsLess(int a, int b) { return a < b; }
int PlayCallScriptIsGreater(int a, int b) { return a > b; }
int PlayCallScriptIsLessEqual(int a, int b) { return a <= b; }
int PlayCallScriptIsGreaterEqual(int a, int b) { return a >= b; }
int PlayCallScriptIsNotEqual(int a, int b) { return a != b; }

}

static int (*const _PlayCallScript_apfnCompare[])(int, int) = {
    PlayCallScriptIsEqual, PlayCallScriptIsEqual, PlayCallScriptIsLess, PlayCallScriptIsGreater,
    PlayCallScriptIsLessEqual, PlayCallScriptIsGreaterEqual, PlayCallScriptIsNotEqual
};

extern "C" {

void PlayCallScriptExecute(unsigned char *p, short *pRecord, PlayCallScriptCallback_t callback)
{
    unsigned char *stack[10];
    int result = 0;
    unsigned char depth = 0;

    do {
        unsigned char *base;
        short offset;
        int i, a, b;
        unsigned char instruction = *p++;
        int count = instruction & 15;
        switch (instruction >> 4) {
        case 0: {
            if (depth == 0) {
                result = 3;
                break;
            }
            unsigned char *saved = stack[--depth];
            for (;;) {
                if (saved > p) {
                    p = saved - 1;
                    break;
                }
                if (depth == 0) {
                    result = 3;
                    goto next;
                }
                saved = stack[--depth];
            }
            break;
        }
        case 1: {
            base = p;
            offset = (short)(*p++ << 8);
            offset |= *p++;
            for (i = count; i > 0; --i) {
                a = PlayCallScriptReadValue(&p, pRecord);
                unsigned char comparison = *p++;
                b = PlayCallScriptReadValue(&p, pRecord);
                if (!_PlayCallScript_apfnCompare[comparison](a, b)) {
                    p = base + offset - 1;
                    break;
                }
            }
            break;
        }
        case 2: {
            base = p;
            a = PlayCallScriptReadValue(&p, pRecord);
            stack[depth] = base + (*p++ << 8);
            stack[depth] += *p++;
            ++depth;
            stack[depth] = base + (*p++ << 8);
            stack[depth] += *p++;
            for (i = 0; i < count; ++i) {
                base = p++;
                if ((*p & 0xC0) == 0x40 || (*p & 0xC0) == 0xC0) {
                    pRecord[17] = a;
                    if (callback(11, pRecord, *p))
                        b = a;
                    else
                        b = a + 1;
                    ++p;
                } else {
                    b = PlayCallScriptReadValue(&p, pRecord);
                }
                offset = (short)(*p++ << 8);
                offset |= *p++;
                if (a == b)
                    break;
                p = base + offset;
            }
            if (i == count)
                p = stack[depth] - 1;
            break;
        }
        case 3:
            pRecord[19] = count;
            result = 4;
            break;
        case 4:
            pRecord[19] = *p;
            result = 1;
            break;
        case 5:
            pRecord[19] = *p++;
            pRecord[19] += *p << 8;
            result = 2;
            break;
        case 6:
            if ((*p & 0xC0) == 0x40 || (*p & 0xC0) == 0xC0)
                ++p;
            else
                PlayCallScriptReadValue(&p, pRecord);
            p += 2;
            break;
        case 7:
            pRecord[18] = *p++;
            pRecord[18] += *p++ << 8;
            break;
        }
next:
        ;
    } while (result == 0);
    pRecord[17] = result;
}

int PlayCallScriptHandleEndCode(short *pRecord, PlayCallScriptCallback_t callback)
{
    int result = -1;
    switch (pRecord[19]) {
    case 255:
        callback(6, pRecord, 0);
        result = 1;
        break;
    case 253:
        if (pRecord[15] == 255) {
            callback(6, pRecord, 0);
            result = 1;
        }
        break;
    case 252:
        if (pRecord[15] != 255)
            break;
    case 254:
        callback(7, pRecord, 0);
        result = 1;
        break;
    }
    return result;
}

int PlayCallScriptApplyOffenseResult(short *pRecord, PlayCallScriptCallback_t callback, int mode)
{
    int result = -1;
    switch (mode) {
    case 0:
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19]);
            result = 1;
            break;
        case 2:
            switch (pRecord[19]) {
            case 254:
                callback(5, pRecord, 254);
                break;
            case 255:
                callback(12, pRecord, 255);
                break;
            default:
                callback(9, pRecord, pRecord[19]);
                break;
            }
            result = 1;
            break;
        }
        break;
    case 1:
        callback(10, pRecord, pRecord[8]);
        result = 1;
        break;
    case 2:
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        case 2:
            callback(9, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        }
        pRecord[19] = result;
        break;
    case 3:
        if (pRecord[17] == 2) {
            switch (pRecord[19]) {
            case 255:
                callback(1, pRecord, 0);
                result = 1;
                break;
            case 254:
                callback(2, pRecord, 0);
                result = 1;
                break;
            case 253:
                callback(3, pRecord, 0);
                result = 1;
                break;
            case 252:
                callback(4, pRecord, 0);
                result = 1;
                break;
            }
        }
        break;
    case 4:
        result = PlayCallScriptHandleEndCode(pRecord, callback);
        break;
    }
    return result;
}

int PlayCallScriptApplyDefenseResult(short *pRecord, PlayCallScriptCallback_t callback, int mode)
{
    int result = 1;
    switch (mode) {
    case 0:
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19]);
            break;
        case 2:
            callback(9, pRecord, pRecord[19]);
            break;
        }
        break;
    case 2:
        result = 0;
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        case 2:
            callback(9, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        }
        break;
    case 3:
        if (pRecord[17] == 2)
            callback(1, pRecord, 0);
        break;
    case 4:
        result = PlayCallScriptHandleEndCode(pRecord, callback);
        break;
    }
    return result;
}

void PlayCallScriptInit(PlayCallScriptDesc_t *pDesc)
{
    _PlayCallScript_sState.mUnknown0 = *pDesc;
    PlayCallScriptRelocate((int *)pDesc->mUnknown0, 10);
    _PlayCallScript_sState.mUnknown16 = (unsigned char **)pDesc->mUnknown0;
    _PlayCallScript_sState.mUnknown20 = (unsigned char **)(pDesc->mUnknown0 + 20);
}

int PlayCallScriptRunOffense(int mode)
{
    if (_PlayCallScript_sState.mUnknown0.mUnknown8)
        _PlayCallScript_sState.mUnknown0.mUnknown8(0, _PlayCallScript_sState.mUnknown0.mUnknown4, mode);
    unsigned char *p = PlayCallScriptGetStream(_PlayCallScript_sState.mUnknown16, mode);
    _PlayCallScript_sState.mUnknown0.mUnknown4[18] = -1;
    PlayCallScriptExecute(p, _PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknown8);
    PlayCallScriptApplyOffenseResult(_PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknown8, mode);
    return _PlayCallScript_sState.mUnknown0.mUnknown4[19];
}

int PlayCallScriptRunDefense(int mode)
{
    if (_PlayCallScript_sState.mUnknown0.mUnknownC)
        _PlayCallScript_sState.mUnknown0.mUnknownC(0, _PlayCallScript_sState.mUnknown0.mUnknown4, mode);
    unsigned char *p = PlayCallScriptGetStream(_PlayCallScript_sState.mUnknown20, mode);
    _PlayCallScript_sState.mUnknown0.mUnknown4[18] = -1;
    PlayCallScriptExecute(p, _PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknownC);
    PlayCallScriptApplyDefenseResult(_PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknownC, mode);
    return _PlayCallScript_sState.mUnknown0.mUnknown4[19];
}

}

extern "C" {
int ChallengeIsActive(void);
int fn_800A82FC(int team);
int fn_800A8430(int team);
int fn_800C8744(int team);
int fn_801485D4(void);
int PlayBookGetDatabase(int team);
int fn_80177F70(void);
int fn_80178308(void);
float fn_80178A5C(void);
int GameTextGetAwayTeam(void);
int GameTextGetHomeTeam(void);
void *fn_8023816C(void);
}

static PlayTrack_t *_PlayTrack_pData = 0;

static float _PlayTrack_afPlayIdWeights[3] = {0.10625f, 0.01875f, 0.009375f};
static float _PlayTrack_afResult5Weights[3] = {0.10625f, 0.01875f, 0.009375f};
static float _PlayTrack_afResult6Weights[3] = {0.10625f, 0.01875f, 0.009375f};
static float _PlayTrack_afFlag10Weights[3] = {0.10625f, 0.01875f, 0.009375f};
static float _PlayTrack_afFlag11Weights[3] = {0.10625f, 0.01875f, 0.009375f};
static float _PlayTrack_afKind1Bit28Weights[3] = {0.08125f, 0.028125f, 0.0140625f};
static float _PlayTrack_afKind1Bit30Weights[3] = {0.08125f, 0.028125f, 0.0140625f};

extern "C" {
int PlayTrackGetKindGroup(int value);
void PlayTrackGetCallTendency(int team, unsigned char *pOut, unsigned int *pFlags);
float PlayTrackScoreTendencyMatch(int team, unsigned char kind, unsigned int flags, int group, unsigned int mask);
float PlayTrackRateResult5(int team);
float PlayTrackRateResult6(int team);
float PlayTrackRateFlag10(int team);
float PlayTrackRateFlag11(int team);
float PlayTrackScaleByMask(unsigned int a, unsigned int b, float value);
float PlayTrackScoreRepeatedPlay(int team, int a, int b);
float PlayTrackScoreFlagMatch(unsigned int mask, unsigned int flags, unsigned int other, float value);
void PlayTrackWeightOffense(int team, PlayCandidate_t *pList, unsigned int count);
void PlayTrackWeightDefense(int team, PlayCandidate_t *pList, unsigned int count);
void PlayTrackFilterByMode(int team, PlayCandidate_t *pList, unsigned int count);
void PlayTrackFilterByChallenge(int team, PlayCandidate_t *pList, unsigned int count, int mode);
unsigned int PlayTrackClassifyPlay(int kind, Point_8017886C from, Point_8017886C *pTo, int flag);
void PlayTrackGetRatingBias(int team, float *pA, float *pB);
void PlayTrackInit(void);
void PlayTrackShutdown(void);
void PlayTrackUpdateSummary(void);
void PlayTrackPushPlay(int team, int value);
void PlayTrackSetEntryWord4(int team, int value);
void PlayTrackSetEntryByteC(int team, signed char value);
void PlayTrackSetDirection(int team, Point_8017886C from, Point_8017886C to, int flag);
void PlayTrackSetGain(int team, float value);
void PlayTrackSetResult(int team, unsigned char value);
void PlayTrackSetKind(int team, unsigned char value);
void PlayTrackSetFlag10(int team, unsigned char value);
void PlayTrackSetFlag11(int team, unsigned char value);
void PlayTrackWeightCandidates(int team, PlayCandidate_t *pList, unsigned int count);
void PlayTrackGetGainTendency(int team, unsigned char *pOut, unsigned int *pFlags);
void PlayTrackGetPlayTendency(int team, PlayBookPlay_t *pRecord, unsigned char *pOut, unsigned int *pFlags);
float PlayTrackRatePlayId(int team, int value);
void PlayTrackRegister(void);
}

int PlayTrackGetKindGroup(int value)
{
    switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 0x26:
        return 2;
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x25:
        return 1;
    }
    return 0;
}

void PlayTrackGetCallTendency(int team, unsigned char *pOut, unsigned int *pFlags)
{
    *pOut = 0;
    *pFlags = 0;

    float kind2 = 0.0f;
    float other = 0.0f;
    float other4 = 0.0f;
    float other8 = 0.0f;
    float other2 = 0.0f;
    float kind2Flag100 = 0.0f;
    float kind2Flag200 = 0.0f;
    float kind2Flag80 = 0.0f;
    float kind2Flag40 = 0.0f;
    float kind2Flag20 = 0.0f;
    float kind2Flag10 = 0.0f;
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    float total = _PlayTrack_pData->mUnknown3DC[team];

    if (total <= 8.0f)
        return;

    for (unsigned char i = 0; i < total; i++) {
        unsigned int flags = pEntries[i].mUnknown8;
        if (pEntries[i].mUnknownF == 2) {
            kind2 += 1.0f;
            if (pEntries[i].mUnknownE != 4) {
                if (flags & 0x10)
                    kind2Flag10 += 1.0f;
                if (flags & 0x20)
                    kind2Flag20 += 1.0f;
                if (flags & 0x40)
                    kind2Flag40 += 1.0f;
                if (flags & 0x80)
                    kind2Flag80 += 1.0f;
                if (flags & 0x100)
                    kind2Flag100 += 1.0f;
                if (flags & 0x200)
                    kind2Flag200 += 1.0f;
            }
        } else {
            other += 1.0f;
            if (flags & 2)
                other2 += 1.0f;
            if (flags & 4)
                other4 += 1.0f;
            if (flags & 8)
                other8 += 1.0f;
        }
    }

    if (other / total > 0.65f)
        *pOut = 1;
    else if (kind2 / total > 0.65f)
        *pOut = 2;

    if (other != 0.0f) {
        if (other2 / other > 0.5f)
            *pFlags |= 2;
        else if (other8 / other > 0.5f)
            *pFlags |= 8;
        else if (other4 / other > 0.5f)
            *pFlags |= 4;
    }

    if (kind2 != 0.0f) {
        if (kind2Flag10 / kind2 > 0.5f)
            *pFlags |= 0x10;
        else if (kind2Flag20 / kind2 > 0.5f)
            *pFlags |= 0x20;
        else if (kind2Flag40 / kind2 > 0.5f)
            *pFlags |= 0x40;

        if (kind2Flag80 / kind2 > 0.5f)
            *pFlags |= 0x80;
        else if (kind2Flag200 / kind2 > 0.5f)
            *pFlags |= 0x200;
        else if (kind2Flag100 / kind2 > 0.5f)
            *pFlags |= 0x100;
    }
}

float PlayTrackScoreTendencyMatch(int team, unsigned char kind, unsigned int flags, int group, unsigned int mask)
{
    float value = 0.0f;

    if (kind != 0 && kind == group)
        value = 2.0f;

    unsigned int high = flags & 0x70;
    unsigned int low = flags & 0x38E;
    if (low && (low & mask))
        value += 1.5f;
    if (high && (high & mask))
        value += 1.5f;
    return value;
}

float PlayTrackRateResult5(int team)
{
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownE == 5 && pEntries[i].mUnknownD > 2.0f)
            value += _PlayTrack_afResult5Weights[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float PlayTrackRateResult6(int team)
{
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownE == 6 && pEntries[i].mUnknownD > 4.0f)
            value += _PlayTrack_afResult6Weights[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float PlayTrackRateFlag10(int team)
{
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknown10 != 0)
            value += _PlayTrack_afFlag10Weights[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float PlayTrackRateFlag11(int team)
{
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknown11 != 0)
            value += _PlayTrack_afFlag11Weights[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float PlayTrackScaleByMask(unsigned int a, unsigned int b, float value)
{
    float scale = (a & b) ? 0.75f : -0.75f;
    return scale * value + scale;
}

float PlayTrackScoreRepeatedPlay(int team, int a, int b)
{
    unsigned short matches = 0;
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    float result = 0.0f;
    float sum = result;
    unsigned short i;

    for (i = 0; i < count; i++) {
        if (b == pEntries[i].mUnknown0 && a == pEntries[i].mUnknown4) {
            matches++;
            switch (pEntries[i].mUnknownE) {
            case 1:
            case 3:
            case 4:
                sum -= 5.0f;
                break;
            default:
                sum += pEntries[i].mUnknownD;
                break;
            }
        }
    }

    if (matches != 0) {
        float limit;
        sum /= matches;
        if (pEntries[i].mUnknownF == 1)
            limit = 4.9f;
        else
            limit = 9.0f;
        if (sum < limit)
            result = 0.5f;
    }
    return result;
}

float PlayTrackScoreFlagMatch(unsigned int mask, unsigned int flags, unsigned int other, float value)
{
    unsigned int high = flags & 0x70;
    float result = 0.0f;

    flags &= 0x38E;
    if (flags & mask) {
        result = 0.35f;
        if (flags & other)
            result += 0.175f;
        result = result * value + result;
    }
    if (high & mask) {
        result += 0.75f;
        if (high & other)
            result += 0.375f;
        result = result * value + result;
    }
    return result;
}

void PlayTrackWeightOffense(int team, PlayCandidate_t *pList, unsigned int count)
{
    float group1Bias;
    float group2Bias;
    unsigned char kind;
    unsigned int flags;
    int preferred = 0;

    PlayTrackGetRatingBias(team, &group1Bias, &group2Bias);
    PlayTrackGetGainTendency(team, &kind, &flags);
    if (fn_801485D4())
        preferred = fn_80148A58()->vfn_08(1);

    for (unsigned short i = 0; i < count; i++) {
        float scale = 1.0f;
        int group = PlayTrackGetKindGroup(pList[i].mUnknown8);

        scale += PlayTrackScoreTendencyMatch(team, kind, flags, group, pList[i].mUnknown6);
        if (group == 2)
            scale += group2Bias;
        else if (group == 1)
            scale += group1Bias;
        if (scale < 0.0f)
            scale = 0.0f;

        if (fn_800A82FC(fn_80178308())) {
            if (fn_80177F70() != 6) {
                if (group == 2)
                    pList[i].mUnknown4 = 0;
                else if (group == 1)
                    pList[i].mUnknown4 = group;
            }
        } else if (preferred != 0) {
            if (group != preferred)
                pList[i].mUnknown4 = 0;
        } else {
            pList[i].mUnknown4 = (unsigned short)((float)pList[i].mUnknown4 * scale + 0.5f);
        }
    }
}

void PlayTrackWeightDefense(int team, PlayCandidate_t *pList, unsigned int count)
{
    int opponent = team ^ 1;
    PlayBookPlay_t *pRecord = PlayBookGetPlay(opponent);
    unsigned char kind;
    unsigned char trend;
    unsigned int mask;
    unsigned int flags;
    unsigned int rating;
    int id = pRecord->mUnknown4;

    PlayTrackGetPlayTendency(opponent, pRecord, &kind, &mask);
    PlayTrackGetCallTendency(opponent, &trend, &flags);
    float history = PlayTrackRatePlayId(opponent, id);
    float result5Rate = PlayTrackRateResult5(opponent);
    float result6Rate = PlayTrackRateResult6(opponent);

    int key = team == 0 ? GameTextGetHomeTeam() : GameTextGetAwayTeam();
    if (fn_801FCE10(0, "select 'ZBMT' into \x82 from 'MAET' where 'DIGT' = \x82\n", &rating, key) != 0)
        rating = 50;
    PlayBookGetDatabase(team);

    for (unsigned short i = 0; i < count; i++) {
        float weight = pList[i].mUnknown4;
        float scale = 1.0f;

        scale += PlayTrackScaleByMask(pList[i].mUnknown6, mask, history);
        scale += PlayTrackScoreRepeatedPlay(opponent, pList[i].mUnknown0, id);
        scale += PlayTrackScoreFlagMatch(pList[i].mUnknown6, flags, mask, history);
        if ((pList[i].mUnknown6 & 0x400) && kind == 2)
            scale += result5Rate;
        if ((pList[i].mUnknown6 & 0x800) && kind == 1)
            scale += result6Rate;

        float adjust = ((float)rating - 50.0f) * 0.02f;
        if (pList[i].mUnknown8 == 0x1F)
            scale += adjust * 0.5f;
        else
            scale -= adjust * 0.5f;
        if (scale < 0.0f)
            scale = 0.0f;

        pList[i].mUnknown4 = (unsigned short)(weight * scale);
    }
}

void PlayTrackFilterByMode(int team, PlayCandidate_t *pList, unsigned int count)
{
    int mode = fn_800A8430(team);

    if (mode == 0)
        return;
    for (unsigned short i = 0; i < count; i++) {
        int keep = 0;
        int group = PlayTrackGetKindGroup(pList[i].mUnknown8);
        if ((group == 2 && mode == 2) || (group == 1 && mode == 1) || group == 0)
            keep = 1;
        if (!keep)
            pList[i].mUnknown4 = keep;
    }
}

void PlayTrackFilterByChallenge(int team, PlayCandidate_t *pList, unsigned int count, int mode)
{
    if (mode == 3)
        return;
    for (unsigned short i = 0; i < count; i++) {
        int keep = 0;
        int group = PlayTrackGetKindGroup(pList[i].mUnknown8);
        if ((group == 2 && mode == 1) || (group == 1 && mode == 2))
            keep = 1;
        if (!keep)
            pList[i].mUnknown4 = keep;
    }
}

unsigned int PlayTrackClassifyPlay(int kind, Point_8017886C from, Point_8017886C *pTo, int flag)
{
    unsigned int result = 0;
    // FAKEMATCH: one local reused for both distances gives the target float registers
    float distance = fabsf(pTo->mX - from.mX);

    if (distance > 4.5f) {
        if (pTo->mX > from.mX) {
            if (kind == 2)
                result |= 0x200;
            else
                result |= 8;
        } else {
            if (kind == 2)
                result |= 0x80;
            else
                result |= 2;
        }
    } else {
        if (kind == 2)
            result |= 0x100;
        else
            result |= 4;
    }

    if (kind == 2) {
        distance = pTo->mY - from.mY;
        if (distance < 7.0f)
            result |= 0x10;
        else if (distance < 15.0f)
            result |= 0x20;
        else
            result |= 0x40;
        return result;
    }

    if (fabsf(from.mX) > fn_80178A5C() * 0.33333334f) {
        if ((pTo->mX > from.mX && from.mX < 0.0f) || (pTo->mX < from.mX && from.mX > 0.0f))
            result |= 0x10000000;
        else
            result |= 0x20000000;
    }
    if ((flag && pTo->mX > from.mX) || (!flag && pTo->mX < from.mX))
        result |= 0x40000000;
    return result;
}

void PlayTrackGetRatingBias(int team, float *pA, float *pB)
{
    unsigned int rating = 50;
    // FAKEMATCH: the local stops -ffast-math folding * 0.02f * 0.5f into one constant
    float value;

    int id = fn_800C8744(team);
    if (fn_801FCE10(0, "select 'PRMT' into \x82 from 'MAET' where 'DIGT' = \x82\n", &rating, id) != 0)
        rating = 50;

    *pA = 0.0f;
    *pB = 0.0f;
    if (rating > 50) {
        value = (float)(rating - 50) * 0.02f;
        *pB = value * 0.5f;
        *pA = -*pB;
    } else if (rating < 50) {
        value = (float)(50 - rating) * 0.02f;
        *pA = value * 0.5f;
        *pB = -*pA;
    }
}

void PlayTrackInit(void)
{
    // FAKEMATCH: never-set flag; keeps the PNIG/STPG query strings in .rodata (owner-accepted 2026-11-14)
    int resume = 0;
    void *pHandle = fn_80238174(0, (void **)&_PlayTrack_pData, sizeof(PlayTrack_t), 0, 0x7074726B);
    fn_801C1F94(fn_8023816C(), 0, sizeof(PlayTrack_t));
    if (resume) {
        int found;

        fn_801FCE10(0, "select 'PNIG' into \x82 from 'FNIG'\n", &found);
        resume = found;
    }
    if (resume) {
        fn_801FCE10(0, "select 'STPG' into \x89 from 'NIBG'\n", _PlayTrack_pData);
    }
    fn_802381E0(pHandle);
    PlayTrackRegister();
}

void PlayTrackShutdown(void)
{
}

void PlayTrackUpdateSummary(void)
{
    int team = fn_80178308();
    PlayBookPlay_t *pRecord = PlayBookGetPlay(team);

    _PlayTrack_pData->mUnknown0 = PlayTrackRatePlayId(team, pRecord->mUnknown4);
    _PlayTrack_pData->mUnknown4 = PlayTrackRateResult5(team);
    _PlayTrack_pData->mUnknown8 = PlayTrackRateResult6(team);
    _PlayTrack_pData->mUnknownC = PlayTrackRateFlag10(team);
    _PlayTrack_pData->mUnknown10 = PlayTrackRateFlag11(team);
    PlayTrackGetGainTendency(team, &_PlayTrack_pData->mUnknown18, &_PlayTrack_pData->mUnknown14);
}

void PlayTrackPushPlay(int team, int value)
{
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];

    for (unsigned char i = 23; i != 0; i--)
        pEntries[i] = pEntries[i - 1];
    fn_801C1F94(pEntries, 0, sizeof(PlayTrackEntry_t));
    pEntries[0].mUnknown0 = value;
    pEntries[0].mUnknownC = -1;

    int count = _PlayTrack_pData->mUnknown3DC[team] + 1;
    if (count > 24)
        count = 24;
    _PlayTrack_pData->mUnknown3DC[team] = count;
}

void PlayTrackSetEntryWord4(int team, int value)
{
    _PlayTrack_pData->mUnknown1C[team][0].mUnknown4 = value;
}

void PlayTrackSetEntryByteC(int team, signed char value)
{
    _PlayTrack_pData->mUnknown1C[team][0].mUnknownC = value;
}

void PlayTrackSetDirection(int team, Point_8017886C from, Point_8017886C to, int flag)
{
    PlayTrackEntry_t *pEntry = &_PlayTrack_pData->mUnknown1C[team][0];
    pEntry->mUnknown8 = PlayTrackClassifyPlay(pEntry->mUnknownF, from, &to, flag);
}

void PlayTrackSetGain(int team, float value)
{
    _PlayTrack_pData->mUnknown1C[team][0].mUnknownD = (int)value;
}

void PlayTrackSetResult(int team, unsigned char value)
{
    if (_PlayTrack_pData->mUnknown1C[team][0].mUnknownE == 0)
        _PlayTrack_pData->mUnknown1C[team][0].mUnknownE = value;
}

void PlayTrackSetKind(int team, unsigned char value)
{
    _PlayTrack_pData->mUnknown1C[team][0].mUnknownF = value;
}

void PlayTrackSetFlag10(int team, unsigned char value)
{
    _PlayTrack_pData->mUnknown1C[team][0].mUnknown10 = value;
}

void PlayTrackSetFlag11(int team, unsigned char value)
{
    _PlayTrack_pData->mUnknown1C[team][0].mUnknown11 = value;
}

void PlayTrackWeightCandidates(int team, PlayCandidate_t *pList, unsigned int count)
{
    if (team == fn_80178308())
        PlayTrackWeightOffense(team, pList, count);
    else
        PlayTrackWeightDefense(team, pList, count);

    if (fn_800A82FC(team) && fn_80177F70() != 6)
        PlayTrackFilterByMode(team, pList, count);

    if (ChallengeIsActive() && team == fn_80178308() && fn_800B65A0(team) == 0xFF) {
        int mode = ChalGetCurrent()->mUnknown1B4;
        if (mode != 0)
            PlayTrackFilterByChallenge(team, pList, count, mode);
    }
}

extern "C" {
int fn_8011F1CC(void);
int fn_8022DDB4(int tag, void *data);
unsigned char PlayTrackMatchesGainFlags(Point_8017886C *pTo);
float PlayTrackGetPlayIdRate(void);
float PlayTrackGetResult5Rate(void);
float GetTrackerFloat8(void);
float PlayTrackGetFlag10Rate(void);
float PlayTrackGetFlag11Rate(void);
void SumKind1WeightsBit28(int team, float *pBit29, float *pBit28);
void SumKind1WeightsBit30(int team, float *pSet, float *pClear);
void PlayTrackGetOffenseTendency(unsigned char *pOut);
void PlayTrackReset(void);
}

void PlayTrackGetGainTendency(int team, unsigned char *pOut, unsigned int *pFlags)
{
    float kind2Gain = 0.0f;
    float kind2 = 0.0f;
    float kind1Gain = 0.0f;
    float kind1 = 0.0f;
    float kind1Flag4 = 0.0f;
    float kind1Flag8 = 0.0f;
    float kind1Flag2 = 0.0f;
    float kind2Flag100 = 0.0f;
    float kind2Flag200 = 0.0f;
    float kind2Flag80 = 0.0f;
    float kind2Flag40 = 0.0f;
    float kind2Flag20 = 0.0f;
    float kind2Flag10 = 0.0f;
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];

    *pOut = 0;
    *pFlags = 0;
    if (count <= 8)
        return;

    for (unsigned char i = 0; i < count; i++) {
        unsigned int flags = pEntries[i].mUnknown8;
        float gain;

        switch (pEntries[i].mUnknownE) {
        case 1:
        case 3:
        case 4:
            gain = 0.0f;
            break;
        default:
            gain = pEntries[i].mUnknownD;
            break;
        }

        if (pEntries[i].mUnknownF == 1) {
            kind1 += 1.0f;
            if (gain > 4.9f) {
                kind1Gain += 1.0f;
                if (flags & 2)
                    kind1Flag2 += 1.0f;
                if (flags & 4)
                    kind1Flag4 += 1.0f;
                if (flags & 8)
                    kind1Flag8 += 1.0f;
            }
        } else {
            kind2 += 1.0f;
            if (gain > 9.0f) {
                kind2Gain += 1.0f;
                if (flags & 0x80)
                    kind2Flag80 += 1.0f;
                if (flags & 0x100)
                    kind2Flag100 += 1.0f;
                if (flags & 0x200)
                    kind2Flag200 += 1.0f;
                if (flags & 0x10)
                    kind2Flag10 += 1.0f;
                if (flags & 0x20)
                    kind2Flag20 += 1.0f;
                if (flags & 0x40)
                    kind2Flag40 += 1.0f;
            }
        }
    }

    if (kind1 <= 7.0f || kind2 <= 7.0f)
        return;

    float kind1Rate = kind1Gain / kind1;
    float kind2Rate = kind2Gain / kind2;
    if (fabsf(kind1Rate - kind2Rate) > 0.35f)
        *pOut = kind1Rate > kind2Rate ? 1 : 2;

    if (kind1Gain != 0.0f) {
        if (kind1Flag2 / kind1Gain > 0.4f)
            *pFlags |= 2;
        else if (kind1Flag8 / kind1Gain > 0.4f)
            *pFlags |= 8;
        else if (kind1Flag4 / kind1Gain > 0.4f)
            *pFlags |= 4;
    }

    if (kind2Gain != 0.0f) {
        if (kind2Flag10 / kind2Gain > 0.4f)
            *pFlags |= 0x10;
        else if (kind2Flag20 / kind2Gain > 0.4f)
            *pFlags |= 0x20;
        else if (kind2Flag40 / kind2Gain > 0.4f)
            *pFlags |= 0x40;

        if (kind2Flag80 / kind2Gain > 0.4f)
            *pFlags |= 0x80;
        else if (kind2Flag200 / kind2Gain > 0.4f)
            *pFlags |= 0x200;
        else if (kind2Flag100 / kind2Gain > 0.4f)
            *pFlags |= 0x100;
    }
}

unsigned char PlayTrackMatchesGainFlags(Point_8017886C *pTo)
{
    int kind = 1;

    if (fn_8011F1CC())
        kind = 2;
    return PlayTrackClassifyPlay(kind, fn_80177FE0(), pTo, 1) & _PlayTrack_pData->mUnknown14;
}

void PlayTrackGetPlayTendency(int team, PlayBookPlay_t *pRecord, unsigned char *pOut, unsigned int *pFlags)
{
    *pFlags = pRecord->mUnknown18 & 0x3FE;
    if (PlayBookGetFormation(team)->mUnknown8.mUnknownF != 0) {
        if (*pFlags & 8)
            *pFlags = (*pFlags & ~8) | 2;
        else if (*pFlags & 2)
            *pFlags = (*pFlags & ~2) | 8;
        if (*pFlags & 0x80)
            *pFlags = (*pFlags & ~0x80) | 0x200;
    }
    *pOut = PlayTrackGetKindGroup(pRecord->mUnknown17);
}

float PlayTrackRatePlayId(int team, int value)
{
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    float result = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (value == pEntries[i].mUnknown0)
            result += _PlayTrack_afPlayIdWeights[i / 8];
    }
    return result;
}

float PlayTrackGetPlayIdRate(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return _PlayTrack_pData->mUnknown0;
}

float PlayTrackGetResult5Rate(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return _PlayTrack_pData->mUnknown4;
}

float GetTrackerFloat8(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return _PlayTrack_pData->mUnknown8;
}

float PlayTrackGetFlag10Rate(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return _PlayTrack_pData->mUnknownC;
}

float PlayTrackGetFlag11Rate(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return _PlayTrack_pData->mUnknown10;
}

void SumKind1WeightsBit28(int team, float *pBit29, float *pBit28)
{
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    unsigned short kind1Count = 0;

    *pBit29 = 0.0f;
    *pBit28 = 0.0f;
    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownF == 1) {
            kind1Count++;
            if (pEntries[i].mUnknown8 & 0x10000000)
                *pBit28 += _PlayTrack_afKind1Bit28Weights[kind1Count / 8];
            else if (pEntries[i].mUnknown8 & 0x20000000)
                *pBit29 += _PlayTrack_afKind1Bit28Weights[kind1Count / 8];
        }
    }
}

void SumKind1WeightsBit30(int team, float *pSet, float *pClear)
{
    unsigned short count = _PlayTrack_pData->mUnknown3DC[team];
    PlayTrackEntry_t *pEntries = _PlayTrack_pData->mUnknown1C[team];
    unsigned short kind1Count = 0;

    *pSet = 0.0f;
    *pClear = 0.0f;
    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownF == 1) {
            kind1Count++;
            if (pEntries[i].mUnknown8 & 0x40000000)
                *pSet += _PlayTrack_afKind1Bit30Weights[kind1Count / 8];
            else
                *pClear += _PlayTrack_afKind1Bit30Weights[kind1Count / 8];
        }
    }
}

void PlayTrackGetOffenseTendency(unsigned char *pOut)
{
    unsigned int flags;

    if (fn_800BA6F8()) {
        *pOut = 0;
        flags = 0;
    } else {
        PlayTrackGetCallTendency(fn_80178308(), pOut, &flags);
    }
}

void PlayTrackReset(void)
{
    fn_801C1F94(_PlayTrack_pData, 0, sizeof(PlayTrack_t));
}

void PlayTrackRegister(void)
{
    fn_8022DDB4(0x53545047, _PlayTrack_pData);
}

extern "C" {
int PlayAutoFlip(int team)
{
    int flipped = 0;
    int chance = 50;
    PlayBookPlay_t *pRecord = PlayBookGetPlay(team);
    PlayBookFormation_t *pObject = PlayBookGetFormation(team);
    float x;
    unsigned char kind;
    unsigned int flags;

    if ((pObject->mUnknown8.mUnknown14 & 1) == 0 || (PlayBookGetPlay(team)->mUnknown18 & 1) == 0) {
        return 0;
    }

    x = fn_80177FE0().mX;
    PlayTrackGetGainTendency(team, &kind, &flags);
    switch (PlayTrackGetKindGroup(pRecord->mUnknown17)) {
    case 1:
        if (pRecord->mUnknown18 & 2) {
            if (x < 0.1f - fn_80178A5C()) {
                chance = 67;
            } else if (x > fn_80178A5C() - 0.1f) {
                chance = 33;
            }
            if (flags & 8) {
                chance += 15;
            }
            if (flags & 2) {
                chance -= 15;
            }
        }
        if (pRecord->mUnknown18 & 8) {
            if (x > fn_80178A5C() - 0.1f) {
                chance += 17;
            } else if (x < 0.1f - fn_80178A5C()) {
                chance -= 17;
            }
            if (flags & 2) {
                chance += 15;
            }
            if (flags & 8) {
                chance -= 15;
            }
        }
        break;
    case 2:
        if (pRecord->mUnknown18 & 0x80) {
            if (x < 0.1f - fn_80178A5C()) {
                chance = 67;
            } else if (x > fn_80178A5C() - 0.1f) {
                chance = 33;
            }
            if (flags & 0x200) {
                chance += 15;
            }
            if (flags & 0x80) {
                chance -= 15;
            }
        }
        if (pRecord->mUnknown18 & 0x200) {
            if (x > fn_80178A5C() - 0.1f) {
                chance += 17;
            } else if (x < 0.1f - fn_80178A5C()) {
                chance -= 17;
            }
            if (flags & 0x80) {
                chance += 15;
            }
            if (flags & 0x200) {
                chance -= 15;
            }
        }
        break;
    default:
        chance = 0;
        break;
    }

    if (fn_802372EC(0, 100) < chance) {
        flipped = 1;
        pObject->mUnknown8.mUnknownF ^= 1;
    }
    return flipped;
}
}

struct PlayRoutePoint_t {
    Point_8017886C mPos;
    char mUnknown8[8];
    int mType;
    char mUnknown14[0x10];
};

struct PlayRoute_t {
    int mCount;
    int mKind;
    PlayRoutePoint_t mPoints[12];
    Point_8017886C mCur;
};

struct PlayRouteCmd_t {
    unsigned char mOp;
    unsigned char mArgs[3];
};

static unsigned char _PlayRoute_bTurn = 10;

extern "C" {
extern unsigned char gGameTextPlayArtShift;
State_8011F4EC *fn_8011F4EC(void);
void fn_80227538(Point_8017886C *pOut, int angle, float magnitude);
int fn_801CFE40(float y, float x);

void PlayBookGetZoneCenter(int zone, Point_8017886C *pOut)
{
    Box_8009E674 *pBox = &fn_8011F4EC()->mUnknown18[zone];

    pOut->mX = (pBox->mUnknown8 + pBox->mUnknownC) * 0.5f - 0.5f;
    pOut->mY = (pBox->mUnknown0 + pBox->mUnknown4) * 0.5f;
}

void PlayBookRouteApplyTurn(int heading, Point_8017886C *pPos)
{
    Point_8017886C step;
    int turn;
    float scale;

    if (_PlayRoute_bTurn == 10) {
        return;
    }
    // FAKEMATCH: Xbox does not clear the step; the clear forms the 0.0f pool word
    step.mX = step.mY = 0.0f;
    switch (_PlayRoute_bTurn) {
    case 0:
    case 2:
        if (heading > 0x400000 && heading < 0xC00000) {
            turn = 0x800000;
            scale = 1.0f;
        } else {
            turn = 0;
            scale = 1.0f;
        }
        break;
    case 3:
        if (heading > 0x400000 && heading < 0xC00000) {
            turn = 0;
            scale = 1.0f;
        } else {
            turn = 0x800000;
            scale = 1.0f;
        }
        break;
    case 1:
    case 4:
        turn = 0xC00000;
        scale = 0.5f;
        break;
    default:
        goto done;
    }
    fn_80227538(&step, turn, scale);
    fn_80227638(pPos, pPos, &step);
done:
    _PlayRoute_bTurn = 10;
}

void PlayBookRouteAddStep(unsigned char *pArgs, PlayRoute_t *pRoute)
{
    Point_8017886C step;
    int heading = (pArgs[1] & 0x7F) << 17;
    unsigned char distance = pArgs[0];

    // FAKEMATCH: Xbox does not clear the step; the clear forms the 0.0f pool word
    step.mX = step.mY = 0.0f;
    PlayBookRouteApplyTurn(heading, &pRoute->mCur);
    fn_80227538(&step, heading, (float)(distance & 7) * (1.0f / 7.0f) + (float)(distance >> 3));
    fn_80227638(&pRoute->mCur, &pRoute->mCur, &step);
    pRoute->mKind = 2;
    pRoute->mPoints[pRoute->mCount].mType = 0;
    pRoute->mPoints[pRoute->mCount].mPos = pRoute->mCur;
    pRoute->mCount++;
}

void PlayBookRouteAddZoneStep(unsigned char *pArgs, PlayRoute_t *pRoute)
{
    PlayRouteCmd_t cmd;
    Box_8009E674 *pBox = &fn_8011F4EC()->mUnknown18[pArgs[0]];
    Point_8017886C center;

    *(int *)&cmd = 0;
    cmd.mArgs[0] = 0x50;
    center.mX = (pBox->mUnknown8 + pBox->mUnknownC) * 0.5f - 0.5f;
    center.mY = (pBox->mUnknown0 + pBox->mUnknown4) * 0.5f;
    cmd.mArgs[1] = fn_801CFE40(center.mY, center.mX) >> 17;
    PlayBookRouteAddStep(cmd.mArgs, pRoute);
}

void PlayBookRouteAddShift(PlayRoute_t *pRoute, float delta)
{
    pRoute->mCur.mY += delta;
    pRoute->mPoints[pRoute->mCount].mType = 0;
    pRoute->mPoints[pRoute->mCount].mPos = pRoute->mCur;
    pRoute->mCount++;
    pRoute->mKind = 1;
}

void PlayBookRouteToArt(PlayRoutePoint_t *pDst, PlayRoutePoint_t *pSrc, unsigned int count);

unsigned char PlayBookRouteCommand(unsigned char op, unsigned char *pArgs, PlayRoute_t *pRoute)
{
    unsigned char ok = 1;

    switch (op) {
    case 3:
    case 4:
    case 19:
    case 26:
    case 27:
    case 68:
        PlayBookRouteAddStep(pArgs, pRoute);
        break;
    case 30:
        PlayBookRouteAddStep(pArgs, pRoute);
        ok = 0;
        break;
    case 31:
        PlayBookRouteAddShift(pRoute, -2.0f);
        break;
    case 33:
        PlayBookRouteAddShift(pRoute, 2.0f);
        break;
    case 40:
    case 92:
        PlayBookRouteAddZoneStep(pArgs, pRoute);
        break;
    case 47:
    case 72:
        PlayBookRouteAddStep(pArgs, pRoute);
        pRoute->mKind = ok;
        break;
    case 52:
        _PlayRoute_bTurn = pArgs[0];
        break;
    case 85:
        ok = 0;
        break;
    }
    return ok;
}

void PlayBookBuildRoute(unsigned char *pScript, PlayRoute_t *pRoute, int toArt)
{
    unsigned char more;

    fn_801C1F94(pRoute, 0, sizeof(PlayRoute_t));
    pRoute->mCur.mY = pRoute->mCur.mX = 0.0f;
    do {
        PlayRouteCmd_t cmd = *(PlayRouteCmd_t *)pScript;

        more = (cmd.mOp & 0x80) != 0x80;
        cmd.mOp &= 0x7F;
        more &= PlayBookRouteCommand(cmd.mOp, cmd.mArgs, pRoute);
        pScript += 4;
    } while (more && *pScript != 0);
    if (toArt == 1) {
        PlayBookRouteToArt(pRoute->mPoints, pRoute->mPoints, pRoute->mCount);
    }
}

void PlayBookRouteToArt(PlayRoutePoint_t *pDst, PlayRoutePoint_t *pSrc, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        pDst[i].mType = pSrc[i].mType;
        if (pSrc[i].mType == 0) {
            pDst[i].mPos.mX = pSrc[i].mPos.mX * 1.875f;
            pDst[i].mPos.mY = pSrc[i].mPos.mY * (-100.0f / 41.0f);
        } else if (pSrc[i].mType == -1) {
            break;
        }
    }
}

void PlayBookPointToArt(Point_8017886C *pSrc, Point_8017886C *pDst)
{
    pDst->mX = pSrc->mX * 3.75f;
    pDst->mY = pSrc->mY * (-200.0f / 41.0f);
    pDst->mX += 60.0f;
    // FAKEMATCH: inverted test orders the pool as 50.0f then 90.0f; same result
    pDst->mY += !gGameTextPlayArtShift ? 50.0f : 90.0f;
    if (pDst->mY < 4.0f) {
        pDst->mY = 4.0f;
    } else if (pDst->mY > 96.0f) {
        pDst->mY = 96.0f;
    }
}
}
