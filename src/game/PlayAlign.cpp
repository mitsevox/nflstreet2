/* Lines a team up for the snap: sends every player to his spot and facing in the
   called play and staggers when they start moving. Also loads each play's player
   sets and route steps from the play database, issues the routes to the players,
   and builds the vertex strips of the route lines the play art draws. */

#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/ScrmPlayResult.h"
#include <string.h>
#include "game/ScrmGetTeamPlayerCount.h"
#include "game/Vec3Magnitude.h"
#include "game/Vec2Add.h"
#include "game/PlayBookDb.h"
#include "game/PlaySet.h"
#include "game/PlayAlign.h"
#include <math.h>
#include "game/PlayBookGetPlay.h"
#include "game/fn_800F06F4.h"
#include "game/State_803EB098.h"
#include "game/PlayArtState.h"
#include "game/PlayArtPlayer.h"
#include "game/DbQueryTable.h"
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

extern "C" {
void PlayAlignTeamBegin(PlayBookFormation_t *pObject, int team);
void PlayAlignResetSetNames(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
void ScrmPlayerSendLineUp(Object_80039F5C *p);
void PlyrAlignReset(Object_80039F5C *p);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800EFEF8(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FF6D8(Object_80039F5C *p);
void Vec2Sub(void *pOut, void *pA, void *pB);
void PlyrMgrClearTeamFlag(int team);
void PlyrClearPendingMsg(Object_80039F5C *p, int a);
Object_80039F5C *BallGetCurrentHolder(void);
int ScrmGetDown(void);
FieldPoint_t ScrmGetTeamSetupSpot(int team);
int ScrmGetDefenseTeam(void);
int MathAngleDiff(int a, int b);
float SyncRandGetFloat(int stream);

}

static PlayArtVertex_t _PlayAlign_aCurveWork[10];
static PlayArtVertex_t _PlayAlign_aCurveSamples[11];

static const char *_PlayAlign_apSetNames[4];

extern "C" const char *gPlayAlignNormSet[] = { "Norm", 0 };

extern "C" {
void PlayAlignPlayer(Object_80039F5C *p, PlayBookPosition_t *pEntry, int side)
{
    Message_800F01CC msg;
    FieldPoint_t delta;

    if (p->mpState->mId != '*') {
        p->mFlags &= ~0x40000;
        fn_800EFEF8(0, p->mpState, p);
        delta = ScrmGetTeamSetupSpot(p->mIdBytes[2]);
        Vec2Add(&delta, side == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10, &delta);
        Vec2Sub(&delta, &p->mMotion.mPos, &delta);
        if (Vec2Magnitude(&delta) > 0.5f) {
            memset(&msg, 0, 4);
            msg.mId = 7;
            fn_800F03D8(0, p->mpState, &msg, p);
            memset(&msg, 0, 4);
            msg.mId = 6;
            msg.mUnknown1[0] = (side == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20) >> 16;
            msg.mUnknown1[1] = 1;
            msg.mUnknown1[2] = 20;
            fn_800F03D8(0, p->mpState, &msg, p);
        } else if (MathAngleDiff(side == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20,
                       p->mMotion.mFacing) > 0xAAAAA) {
            memset(&msg, 0, 4);
            msg.mId = 6;
            msg.mUnknown1[0] = (side == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20) >> 16;
            msg.mUnknown1[1] = 1;
            msg.mUnknown1[2] = 20;
            fn_800F03D8(0, p->mpState, &msg, p);
        }
        PlaySetPointToRoleMate(p);
        memset(&msg, 0, 4);
        msg.mId = 9;
        msg.mUnknown1[0] = side == 1 ? pEntry->mUnknownA : pEntry->mUnknown9;
        msg.mUnknown1[1] = 0;
        msg.mUnknown1[2] = 146;
        fn_800F03D8(0, p->mpState, &msg, p);
        ScrmPlayerSendLineUp(p);
    } else {
        PlyrAlignReset(p);
    }
}

void PlayAlignTeamBegin(PlayBookFormation_t *pObject, int team)
{
}

void PlayAlignTeam(PlayBookFormation_t *pObject, int team, const char **ppNames)
{
    unsigned char i;
    unsigned int count;
    Message_800F01CC msg;

    if (team == ScrmGetDefenseTeam()) {
        PlayAlignResetSetNames();
    }
    PlayAlignTeamBegin(pObject, team);
    PlyrMgrClearTeamFlag(team);
    count = ScrmGetActivePlayerCount(team);
    for (i = 0; i < count; i++) {
        PlayBookPosition_t *pEntry = PlaySetGetEntry(pObject, i, ppNames);
        Object_80039F5C *p = PlyrGet(team, i);

        p->mFlags = (p->mFlags & ~0x4000) | 0x10;
        fn_800EFE60(0, p->mpState, p);
        PlyrClearPendingMsg(p, 0);
        if (p == BallGetCurrentHolder()) {
            memset(&msg, 0, 4);
            msg.mId = 49;
            fn_800F03D8(0, p->mpState, &msg, p);
        }
        memset(&msg, 0, 4);
        msg.mId = 7;
        fn_800F03D8(0, p->mpState, &msg, p);
        PlaySetPointToRoleMate(p);
        memset(&msg, 0, 4);
        msg.mId = 87;
        msg.mUnknown1[0] = pObject->mUnknown8.mUnknownF == 1 ? pEntry->mUnknownA : pEntry->mUnknown9;
        msg.mUnknown1[1] = (pObject->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20) >> 16;
        fn_800F03D8(0, p->mpState, &msg, p);
    }
}

void PlayRealignTeam(int team)
{
    unsigned char i;
    unsigned int count;
    int home = ScrmGetDefenseTeam();
    PlayBookFormation_t *pObject = PlayBookGetFormation(team);

    PlayAlignTeamBegin(pObject, team);
    count = ScrmGetActivePlayerCount(team);
    for (i = 0; i < count; i++) {
        int update = 1;
        PlayBookPosition_t *pEntry = PlaySetGetEntry(pObject, i, gPlayAlignNormSet);
        Object_80039F5C *p = PlyrGet(team, i);

        if (team != home) {
            if (ScrmGetDown() != 0) {
                if (p->mFlags & 0x40000) {
                    if (!(p->mFlags & 0x20000000)) {
                        update = 0;
                    }
                }
            }
        }
        if (update == 1) {
            p->mFlags &= ~0x40000;
            p->mFlags &= ~0x4000;
            p->mFlags |= 0x10;
            PlayAlignPlayer(p, pEntry, pObject->mUnknown8.mUnknownF);
        }
    }
}

void PlayAlignResetSetNames(void)
{
    _PlayAlign_apSetNames[0] = "Norm";
    _PlayAlign_apSetNames[1] = "Norm";
    _PlayAlign_apSetNames[2] = "Norm";
    _PlayAlign_apSetNames[3] = "Norm";
}

void PlayAlignPostStartDelays(int team)
{
    unsigned char i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);

        if (p->mQueue[0].mId != 0) {
            if (p->mQueue[0].mId == 7) {
                Message_800F01CC msg;
                float value;

                fn_800FF6D8(p);
                memset(&msg, 0, 4);
                msg.mId = 51;
                value = SyncRandGetFloat(0);
                if (ScrmGetDown() == 0) {
                    value *= 2.0f;
                } else {
                    value *= 0.4f;
                }
                msg.mUnknown1[0] = (int)(value * 32.0f);
                fn_800F00D4(0, p->mpState, &msg, p);
            }
        }
    }
}

const char *PlayAlignGetSetName(int index)
{
    return _PlayAlign_apSetNames[index];
}
}


extern "C" {
void Vec2Normalize(void *, void *);

extern int lbl_802E9964[];
extern PlayArtVertex_t lbl_802E98FC[];
extern unsigned char lbl_802E98E0[][4], lbl_802E98F0[][3];
extern unsigned char lbl_803EB3BB,lbl_803EB3BF,lbl_803EB3C3,lbl_803EB3C7,lbl_803EB3CB,lbl_803EB3CF;
extern unsigned char lbl_803EB3D3,lbl_803EB3D7,lbl_803EB3DB,lbl_803EB3DF,lbl_803EB3E3,lbl_803EB3E7;
extern unsigned char lbl_803EB3EB,lbl_803EB3EF,lbl_803EB3F3,lbl_803EB3F7,lbl_803EB3FB,lbl_803EB3FF,lbl_803EB403,lbl_803EB407,lbl_803EB40B;
int ScrmGetDown(void);
int PauseIsOpen(void);
void Vec2Add(void *, void *, void *);
float Vec2Distance(void *, void *);
int _TDbQrySelect(int, DbQueryTable *, DbFilter *, void *, int *, QueryResult *);
int fn_801C2E18(char *, const char *, ...);
int DbTextToTag(const char *);
int ScrmGetOffenseTeam(void);
unsigned int ScrmGetTeamPlayerCount(int);
int ScrmGetActivePlayerCount(int);
PlayBookFormation_t *PlayBookGetFormation(int);
Record_8011F4E0 *fn_8011F4E0(void);
Message_800F01CC *fn_800AEE20(Object_80039F5C *);
void fn_800AEF74(Object_80039F5C *, Message_800F01CC *);
void fn_800F0910(int, Message_800F01CC *);
int fn_800AD9B4(void);
int PlayAlignHasSlots(PlayBookPlay_t *);
void PlayAlignIssuePlayerRoute(PlayBookPlay_t *, Object_80039F5C *, int);

unsigned char PlayAlignGetKeyPlayer(void)
{
    Object_80039F5C *selected = PlaySetGetKeyPlayer(PlayBookGetFormation(ScrmGetOffenseTeam()));
    if (selected == PlyrGet(ScrmGetOffenseTeam(), 0)) {
        unsigned char i = 0;
        unsigned int n = ScrmGetTeamPlayerCount(ScrmGetOffenseTeam());
        if (i < n) do {
            Object_80039F5C *p = PlyrGet(ScrmGetOffenseTeam(), i);
            PlayBookPlay_t *record = PlayBookGetPlay(ScrmGetOffenseTeam());
            void *queue = PlayAlignGetRoute(record, ScrmGetOffenseTeam(), p->mIdBytes[1]);
            if (fn_800F06F4(0, queue, 18, 0xFFFF) != 0xFFFF) {selected = p; break;}
        } while (++i < n);
    }
    return selected->mIdBytes[1];
}

void PlayAlignIssueTeamRoutes(PlayBookFormation_t *object, PlayBookPlay_t *record, int team, int)
{
    int remap = object->mUnknown8.mUnknownF == 1 && (object->mUnknown8.mUnknown14 & 1) && (record->mUnknown18 & 1);
    int count = ScrmGetActivePlayerCount(team);
    for (int i = 0; i < count; ++i)
        PlayAlignIssuePlayerRoute(record, PlyrGet(team, (unsigned short)i), remap);
}

void PlayAlignIssuePlayerRoute(PlayBookPlay_t *record, Object_80039F5C *p, int remap)
{
    short count = 0;
    Record_8011F4E0 *info = fn_8011F4E0();
    int kind = p->mUnknown2914;
    if (info->mUnknown6 && (unsigned int)(kind - 17) <= 1) remap = !remap;
    unsigned char index;
    if (!remap) index = p->mIdBytes[1];
    else index = PlaySetGetEntry(PlayBookGetFormation(p->mIdBytes[2]), p->mIdBytes[1], 0)->mUnknownB;
    Message_800F01CC *queue = fn_800AEE20(p);
    if (!queue) {
        queue = (Message_800F01CC *)PlayAlignGetRoute(record, p->mIdBytes[2], index);
        int end;
        do {
            end = queue->mId >> 7;
            Message_800F01CC message = *queue;
            if (end) message.mId &= 0x7F;
            if (remap) fn_800F0910(0, &message);
            if (!message.mId) break;
            if (!count) fn_800F053C(0, p->mpState, &message, p);
            else fn_800F03D8(0, p->mpState, &message, p);
            ++count;
            ++queue;
        } while (!end);
    } else {
        fn_800AEF74(p, queue);
    }
}

int PlayAlignRouteHasCommand(PlayBookPlay_t *record, PlayBookFormation_t *object, Object_80039F5C *p, int kind)
{
    unsigned char index;
    if (object->mUnknown8.mUnknownF) index = PlaySetGetEntry(object, p->mIdBytes[1], 0)->mUnknownB;
    else index = p->mIdBytes[1];
    Message_800F01CC *queue = (Message_800F01CC *)PlayAlignGetRoute(record, p->mIdBytes[2], index);
    for (;;) {
        int end = queue->mId >> 7;
        int id = queue->mId;
        if (end) id &= 0x7F;
        if (id == kind) return 1;
        ++queue;
        if (end) return 0;
    }
}

void *PlayAlignGetRoute(void *record, int, unsigned short index)
{
    return (unsigned char *)record + 56 + index * 40;
}

unsigned char PlayAlignGetSlotPlayer(PlayBookFormation_t *object, PlayBookPlay_t *record, int slot, unsigned char *out, int remap)
{
    unsigned char index = 255;
    unsigned char (*slots)[4] = 0;
    int override = 0;
    if (PlayAlignHasSlots(record)) {
        int mode = fn_800AD9B4();
        slots = record->mUnknown1C;
        index = slots[slot][0];
        Object_80039F5C *p = PlyrGet(ScrmGetOffenseTeam(), index);
        if (mode == 2 && !p->mUnknown2914) {index = PlayAlignGetKeyPlayer(); override = 1;}
    }
    if (out) {
        if (slots && !override) {
            // FAKEMATCH: slot bytes addressed as base + (index << 2), not slots[index][n]
            if (!remap) *out = *((unsigned char *)slots + (slot << 2) + 1);
            else {
                unsigned char n = PlaySetGetEntry(object, index, 0)->mUnknownB;
                *out = 0;
                for (int i = 0; i <= 2; ++i) {
                    if (*((unsigned char *)slots + (i << 2)) == n) {*out = *((unsigned char *)slots + (i << 2) + 1); break;}
                }
            }
        } else *out = 0;
    }
    return index;
}

void PlayAlignSetSlotValue(PlayBookFormation_t *object, PlayBookPlay_t *record, int index, unsigned char value, int remap)
{
    unsigned char i;
    if (PlayAlignHasSlots(record)) {
        unsigned char (*slots)[4] = record->mUnknown1C;
        if (remap == 1) index = PlaySetGetEntry(object, index, 0)->mUnknownB;
        for (i = 0; i <= 2; ++i) {
            // FAKEMATCH: slot bytes addressed as base + (i << 2), not slots[i][n]
            if (index == *((unsigned char *)slots + (i << 2))) {
                *((unsigned char *)slots + (i << 2) + 1) = value;
                return;
            }
        }
    }
}

int PlayAlignIsPlayType2Or17(PlayBookPlay_t *record) {if (record->mUnknown14 == 2 || record->mUnknown14 == 17) return 1; return 0;}

int PlayAlignIsPlayType11To18(PlayBookPlay_t *record)
{
    switch ((unsigned int)record->mUnknown14) {
    case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
        return 1;
    }
    return 0;
}

int PlayAlignHasSlots(PlayBookPlay_t *record)
{
    switch ((unsigned int)record->mUnknown14) {
    case 1: case 2: case 3: case 4: case 5:
        return 1;
    }
    return 0;
}

int PlayAlignIsPlayType21(PlayBookPlay_t *record) {return record->mUnknown14 == 21;}

void PlayAlignSwapOuterSlots(PlayArtPlay_t *record, int force)
{
    int swap = 0;
    if (PlayAlignHasSlots((PlayBookPlay_t *)record)) {
        PlayBookFormation_t *object = PlayBookGetFormation(ScrmGetOffenseTeam());
        for (unsigned char i = 0; i <= 2; ++i) {
            // FAKEMATCH: slot byte addressed as record + (i << 2) + 0x1C, not record->mUnknown1C[i][0]
            unsigned char index = *((unsigned char *)record + (i << 2) + 0x1C);
            PlyrGet(ScrmGetOffenseTeam(), index);
            if (object->mUnknown8.mUnknown84[0][index].mUnknownB == index && (i == 0 || i == 2)) {swap = 1; break;}
        }
        if (swap || force) {
            unsigned char index = record->mUnknown1C[0][0];
            record->mUnknown1C[0][0] = record->mUnknown1C[2][0];
            record->mUnknown1C[2][0] = index;
            unsigned char value = record->mUnknown1C[0][1];
            record->mUnknown1C[0][1] = record->mUnknown1C[2][1];
            record->mUnknown1C[2][1] = value;
        }
    }
}

int PlayAlignLoadSetPlayers(void *handle, int, signed char, int id, PlayArtPlayer_t *records)
{
    DbFilter filter;
    DbQueryTable tables[2] = {{0x50544553}, {-1}};
    DbColumnValue columns[7] = {
        {0,0x50544553,0x6F736F70}, {0,0x50544553,0x69747261},
        {0,0x50544553,0x78747261}, {0,0x50544553,0x79747261},
        {0,0x50544553,0x736F5044}, {0,0x50544553,0x736F5045}, {0,-1,-1}
    };
    int cursor;
    int opened = 0;
    int status;

    tables[0].mFilter = &filter;
    filter.Set(6, 0x505445534C544553LL, 3, id);
    status = _TDbQrySelect((int)handle, tables, 0, 0, &cursor, 0);
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        opened = 1;
    }
    if (status == 0) {
        status = TDbQryRetrieve(cursor, 1, 0, columns);
        while (status == 0) {
            PlayArtPlayer_t *record = &records[columns[0].mValue];
            record->mUnknown8 = (float)columns[2].mValue;
            record->mUnknownC = (float)columns[3].mValue;
            record->mUnknown10 = columns[1].mValue;
            record->mUnknown14Word = columns[5].mValue;
            record->mUnknown18Word = columns[4].mValue;
            status = TDbQryRetrieve(cursor, 0, 1, columns);
        }
    }
    if (opened == 1) {
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = TDbQryDestroy(cursor);
        } else {
            TDbQryDestroy(cursor);
        }
    }
    return 1;
}

int PlayAlignLoadPlayRoutes(void *handle, int, int id, PlayArtPlayer_t *records)
{
    DbFilter play, route;
    DbQueryTable plays[2] = {{0x53594C50}, {-1}};
    DbQueryTable routes[2] = {{0x4C545241}, {-1}};
    DbColumnValue counts[2] = {{0,0x53594C50,0x746E6361}, {0,-1,-1}};
    DbColumnValue ids[3] = {{0,0x4C545241,0x4C545241}, {0,0x4C545241,0x6F736F70}, {0,-1,-1}};
    int cursor;
    int opened = 0;
    int status;

    routes[0].mFilter = &route;
    route.mUnknown32 = 0x10003;
    route.SetOperands(6, 0x4C5452414C545241LL, 3, id);
    plays[0].mFilter = &play;
    play.mUnknown32 = 0x10003;
    play.SetOperands(6, 0x53594C504C594C50LL, 3, id);
    status = _TDbQrySelect((int)handle, plays, 0, 0, &cursor, 0);
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        opened = 1;
    }
    if (status == 0) {
        status = TDbQryRetrieve(cursor, 1, 0, ids);
        while (status == 0) {
            route.mUnknown16.Set(3, ids[0].mValue);
            PlayArtPlayer_t *record = &records[ids[1].mValue];
            record->mUnknown0Word = ids[0].mValue;
            TDbQryGetSingleRow((int)handle, routes, 0, counts);
            record->mUnknown4Word = counts[0].mValue;
            status = TDbQryRetrieve(cursor, 0, 1, ids);
        }
    }
    if (opened == 1) {
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = TDbQryDestroy(cursor);
        } else {
            TDbQryDestroy(cursor);
        }
    }
    return 1;
}

int PlayAlignBuildSlotRects(PlayArtPlay_t *record, PlayArtState_t *state, PlayArtPlayer_t *)
{
    int result = 1;
    switch (record->mUnknown14) {
    case 1: case 2: case 3: case 4: case 5: case 38: {
        state->mUnknown2160 = 0;
        unsigned char *slot = record->mUnknown1C[0];
        for (int i = 0; i < 3; slot += 4, ++i) {
            unsigned char index = slot[0];
            int n = state->mUnknown2160;
            state->mUnknown2178[n][0] = state->mUnknown2084[index][0] - 4.0f;
            state->mUnknown2178[n][2] = state->mUnknown2084[index][2] + 4.0f;
            state->mUnknown2178[n][1] = state->mUnknown2084[index][1] - 4.0f;
            state->mUnknown2178[n][3] = state->mUnknown2084[index][3] + 4.0f;
            state->mUnknown2164[n] = i;
            ++state->mUnknown2160;
            if (slot[1]) {
                state->mUnknown2134[index] = 7;
                state->mUnknown21C8[n] = index & 0x7F;
            } else {
                state->mUnknown21C8[n] = index | 0x80;
            }
        }
        break;
    }
    default:
        state->mUnknown2160 = 0;
        result = 0;
        break;
    }
    return result;
}

int PlayAlignLoadRouteSteps(void *handle, PlayArtPlayer_t *records, int first, unsigned char count)
{
    for (unsigned int i = first; i < count; ++i) {
        PlayArtPlayer_t *record = &records[i];
        int steps = record->mUnknown4Word;
        memset(record->mUnknown1C, 0, 0x1B0);
        for (int j = 0; j < steps; ++j) {
            // FAKEMATCH: ax sized 5 (the formatted name and its NUL) so it is not a DImode array
            char ax[5], ay[8], au[8], av[8], at[8], sp[8], ct[8], lt[8], ls[8];
            fn_801C2E18(ax, "ax%02d", j+1);
            fn_801C2E18(ay, "ay%02d", j+1);
            fn_801C2E18(au, "au%02d", j+1);
            fn_801C2E18(av, "av%02d", j+1);
            fn_801C2E18(at, "at%02d", j+1);
            fn_801C2E18(sp, "sp%02d", j+1);
            fn_801C2E18(ct, "ct%02d", j+1);
            fn_801C2E18(lt, "lt%02d", j+1);
            fn_801C2E18(ls, "ls%02d", j+1);
            int x, y, u, v, type, speed, link, arrow, color;
            int axTag = DbTextToTag(ax), ayTag = DbTextToTag(ay), atTag = DbTextToTag(at);
            int auTag = DbTextToTag(au), avTag = DbTextToTag(av), ctTag = DbTextToTag(ct);
            int spTag = DbTextToTag(sp), ltTag = DbTextToTag(lt), lsTag = DbTextToTag(ls);
            int status = TDbCompilePerformOp(0, "use \x8c select \x8c into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c into \x85 and \x8c into \x85 and \x8c into \x85 and \x8c into \x85 from 'LTRA' where 'LTRA' = \x85\n",
                (int)handle, axTag,&x,ayTag,&y,atTag,&type,auTag,&u,avTag,&v,ctTag,&link,spTag,&speed,ltTag,&arrow,lsTag,&color,record->mUnknown0Word);
            if (!status) {
                record->mUnknown1C[j].mUnknown0 = (float)x;
                record->mUnknown1C[j].mUnknown4 = (float)y;
                record->mUnknown1C[j].mUnknown10 = type;
                record->mUnknown1C[j].mUnknown8 = (float)u;
                record->mUnknown1C[j].mUnknownC = (float)v;
                record->mUnknown1C[j].mUnknown14 = link;
                record->mUnknown1C[j].mUnknown18 = speed;
                record->mUnknown1C[j].mUnknown1C = arrow;
                record->mUnknown1C[j].mUnknown20 = color;
            }
        }
        record->mUnknown1C[steps].mUnknown10 = -1;
    }
    return 1;
}

void PlayAlignCurvePoint(PlayArtVertex_t *points, int count, float t, PlayArtVertex_t *out)
{
    int i, j;
    for (i = 0; i < count; ++i) _PlayAlign_aCurveWork[i] = *points++;
    for (j = 1; j < count; ++j)
        for (i = 0; i < count - j; ++i) {
            _PlayAlign_aCurveWork[i].mX = (1.0f - t) * _PlayAlign_aCurveWork[i].mX + t * _PlayAlign_aCurveWork[i+1].mX;
            _PlayAlign_aCurveWork[i].mY = (1.0f - t) * _PlayAlign_aCurveWork[i].mY + t * _PlayAlign_aCurveWork[i+1].mY;
        }
    *out = _PlayAlign_aCurveWork[0];
}

void PlayAlignSampleCurve(PlayArtVertex_t *points, int count, PlayArtVertex_t *out, int samples)
{
    int i;
    float t;
    float step = 1.0f / (float)(samples - 1);
    out[0] = points[0];
    for (i = 1, t = step; i < samples - 1; ++i, t += step)
        PlayAlignCurvePoint(points, count, t, out + i);
    out[samples-1] = points[count-1];
}

void PlayAlignStripEdge(PlayArtVertex_t *a, PlayArtVertex_t *b, PlayArtVertex_t *left, PlayArtVertex_t *right,
                int width, PlayArtVertex_t *prior, int average)
{
    PlayArtVertex_t normal;
    PlayArtVertex_t offset;
    float half;

    float dx = a->mX - b->mX;
    float dy = a->mY - b->mY;
    normal.mX = dy;
    normal.mY = dx;
    Vec2Normalize(&normal, &normal);
    half = (float)width * 0.25f;
    if (prior && average) {
        offset.mX = (normal.mX + prior->mX) * 0.5f;
        offset.mY = (normal.mY + prior->mY) * 0.5f;
        Vec2Normalize(&offset, &offset);
    } else {
        offset.mX = normal.mX;
        offset.mY = normal.mY;
    }
    offset.mX *= half;
    offset.mY *= half;
    left->mX = a->mX - offset.mX;
    left->mY = a->mY + offset.mY;
    right->mX = a->mX + offset.mX;
    right->mY = a->mY - offset.mY;
    if (prior) {
        prior->mX = normal.mX;
        prior->mY = normal.mY;
    }
}

void PlayAlignBuildCurveStrip(PlayArtVertex_t *control, PlayArtVertex_t *out, int samples, int width)
{
    PlayArtVertex_t prior;
    int i;
    int n = 2;

    PlayAlignSampleCurve(control, 3, _PlayAlign_aCurveSamples, samples);
    _PlayAlign_aCurveSamples[samples].mX = _PlayAlign_aCurveSamples[samples-2].mX;
    _PlayAlign_aCurveSamples[samples].mY = _PlayAlign_aCurveSamples[samples-2].mY;
    PlayAlignStripEdge(&_PlayAlign_aCurveSamples[0], &_PlayAlign_aCurveSamples[1], &out[0], &out[1], width, &prior, 0);
    for (i = 1; i < samples - 1; ++i, n += 2)
        PlayAlignStripEdge(&_PlayAlign_aCurveSamples[i], &_PlayAlign_aCurveSamples[i+1], &out[n], &out[n+1], width, &prior, 1);
    PlayAlignStripEdge(&_PlayAlign_aCurveSamples[samples-1], &_PlayAlign_aCurveSamples[samples], &out[n+1], &out[n], width, 0, 0);
}

void PlayAlignBuildSegmentStrip(PlayArtVertex_t *points, PlayArtVertex_t *out, int width)
{
    PlayAlignStripEdge(&points[0], &points[1], &out[0], &out[1], width, 0, 0);
    PlayAlignStripEdge(&points[1], &points[0], &out[2], &out[3], width, 0, 0);
}

}
