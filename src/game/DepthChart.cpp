/* The team depth chart: which player fills each of the 14 roster slots of both teams, loaded from
   and saved to the roster tables, and the edits the depth-chart screen makes (cycling, swapping,
   committing and cancelling). */
#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Object_8008044C.h"
#include "game/DepthChart.h"
#include "game/AutoDepth.h"
#include "game/DepthChartSide.h"
#include "game/fn_801C1F94.h"

extern "C" {
int PlayerDbGetId(Object_8008044C *pObject);
int PlayerDbSeekOriginalId(Object_8008044C *pObject, int a, int *pResult);
int PlayerDbGetPortraitId(Object_8008044C *pObject);
int PlayerDbGetBoostedRating(Object_8008044C *pObject, int a);
int FormationGetByIndex(int a, int b);
int *FormationLineupFetchUser(int a, int b);
int fn_8008593C(int a, int b, int c, int d);
int fn_80085BE4(int a);
int fn_80085C3C(int a);
int fn_80085C94(int a, int *values);
int fn_80085D54(void);
int fn_800B4A18(int a, int b, int c);
int fn_801485D4(void);
int fn_80187C6C(void);
int fn_80187C8C(void);
int fn_8022D874(int tag, int a, int b, int c);
}

static Object_8008044C _DepthChart_sPlayerCursor;
static int _DepthChart_aWorking[2][14];
static int _DepthChart_aCommitted[2][14];
static int _DepthChart_aSpotSlot[2][7];

static int _DepthChart_aSpotToSlot[2][7] = {
    {11, 8, 10, 7, 13, 9, 12},
    {2, 4, 5, 6, 3, 0, 1},
};
static int _DepthChart_aSlotRatings[14][3] = {
    {6, 2, 0}, {2, 4, 0}, {3, 4, 1}, {3, 4, 1}, {7, 0, 4}, {7, 0, 4}, {7, 0, 4},
    {9, 5, 4}, {9, 5, 4}, {5, 8, 4}, {5, 8, 4}, {8, 5, 4}, {8, 5, 4}, {8, 5, 4},
};

/* Pending slot for each row of _DepthChart_aWorking; 7 means none. */
static int _DepthChart_aPending[2] = {7, 7};
static unsigned char _DepthChart_bNeedsLoad = 1;
static unsigned char _DepthChart_bOpen = 0;

extern "C" {
void DepthChartGetPlayerName(int a, int b, int c)
{
    PlayerDbGetLastName(&_DepthChart_sPlayerCursor, (char *)a, b);
}

void DepthChartSetSpotSlot(int kind, int index, int value)
{
    _DepthChart_aSpotSlot[kind][index] = value;
}

void DepthChartGetSpotStatNames(int a, int kind, int index, int d, DepthChartText_t *p0, DepthChartText_t *p1, DepthChartText_t *p2)
{
    fn_800B4A18(_DepthChart_aSlotRatings[_DepthChart_aSpotSlot[kind][index]][0], p0->mUnknown8, p0->mUnknown4);
    fn_800B4A18(_DepthChart_aSlotRatings[_DepthChart_aSpotSlot[kind][index]][1], p1->mUnknown8, p1->mUnknown4);
    fn_800B4A18(_DepthChart_aSlotRatings[_DepthChart_aSpotSlot[kind][index]][2], p2->mUnknown8, p2->mUnknown4);
}

void DepthChartGetSpotPlayer(int a, int kind, int index, int key, int e, DepthChartText_t *pPair, int *pValues, int *pResult)
{
    int handle;
    int *list;
    unsigned char i;

    if (kind == 1) {
        handle = FormationGetByIndex(e, 1);
    } else {
        handle = FormationGetByIndex(e, 0);
    }
    list = FormationLineupFetchUser(handle, a);
    if (list != 0) {
        if (PlayerDbSeekId(&_DepthChart_sPlayerCursor, list[_DepthChart_aSpotSlot[kind][key]], 0) != 0) {
            DepthChartGetPlayerName(pPair->mUnknown8, pPair->mUnknown4, 1);
            for (i = 0; i <= 2; i++) {
                pValues[i] = PlayerDbGetBoostedRating(&_DepthChart_sPlayerCursor, _DepthChart_aSlotRatings[_DepthChart_aSpotSlot[kind][index]][i]);
            }
            *pResult = PlayerDbGetPortraitId(&_DepthChart_sPlayerCursor);
        }
    }
}

int DepthChartCanSwapSpots(int a, int kind, int index0, int index1, int unused)
{
    return fn_8008593C(kind == 1, a, _DepthChart_aSpotSlot[kind][index0], _DepthChart_aSpotSlot[kind][index1]);
}

void DepthChartCyclePending(int group, int kind, int slot, int code, int a, int b)
{
    int step;
    int row;

    step = code == 1 ? 1 : (code == 3 ? -1 : 0);
    slot--;
    row = kind == 1;
    if (_DepthChart_aPending[group] == 7) {
        _DepthChart_aPending[group] = slot;
    }
    _DepthChart_aPending[group] = (_DepthChart_aPending[group] + step + 7) % 7;
    PlayerDbSeekId(&_DepthChart_sPlayerCursor, _DepthChart_aWorking[group][_DepthChart_aSpotToSlot[row][_DepthChart_aPending[group]]], 0);
    DepthChartGetPlayerName(a, b, 1);
}

void DepthChartRevertSide(int group)
{
    int i;

    for (i = 0; i < 14; i++) {
        _DepthChart_aWorking[group][i] = _DepthChart_aCommitted[group][i];
    }
    _DepthChart_aPending[group] = 7;
}

void DepthChartGetSideNames(int group, int kind, DepthChartText_t **pPairs)
{
    int row = kind == 1;
    int i;

    for (i = 0; i < 7; i++) {
        PlayerDbSeekId(&_DepthChart_sPlayerCursor, _DepthChart_aWorking[group][_DepthChart_aSpotToSlot[row][i]], 0);
        DepthChartGetPlayerName(pPairs[i]->mUnknown8, pPairs[i]->mUnknown4, 1);
    }
}

void DepthChartSwapPending(int group, int kind, int slot)
{
    int current;
    int row;
    int from;
    int to;
    int temp;

    slot--;
    if (slot < 0 || slot > 6) {
        return;
    }
    current = _DepthChart_aPending[group];
    if (current == 7) {
        return;
    }
    row = kind == 1;
    if (slot != current) {
        from = _DepthChart_aSpotToSlot[row][slot];
        to = _DepthChart_aSpotToSlot[row][current];
        temp = _DepthChart_aWorking[group][from];
        _DepthChart_aWorking[group][from] = _DepthChart_aWorking[group][to];
        _DepthChart_aWorking[group][to] = temp;
    }
    _DepthChart_aPending[group] = 7;
}

int DepthChartCommit(int group)
{
    int i;

    for (i = 0; i < 14; i++) {
        _DepthChart_aCommitted[group][i] = _DepthChart_aWorking[group][i];
    }
    return fn_80085BE4(group);
}

int DepthChartCancel(int group)
{
    int i;

    for (i = 0; i < 14; i++) {
        _DepthChart_aWorking[group][i] = _DepthChart_aCommitted[group][i];
    }
    return fn_80085C3C(group);
}

void DepthChartAutoFill(int group, int *list, int value)
{
    if (fn_801485D4()) {
        fn_80148A58()->vfn_10(value, list, _DepthChart_aCommitted[group]);
    } else {
        AutoDepthFillChart(value, list, _DepthChart_aCommitted[group]);
    }
    fn_80085C94(group, _DepthChart_aCommitted[group]);
    fn_80085BE4(group);
}

int DepthChartAutoFillEx(int group, int *list, int value, int a, int b)
{
    if (fn_801485D4()) {
        fn_80148A58()->vfn_11(value, list, _DepthChart_aCommitted[group], a, b);
    } else {
        AutoDepthFillChart(value, list, _DepthChart_aCommitted[group]);
    }
    fn_80085C94(group, _DepthChart_aCommitted[group]);
    return fn_80085BE4(group);
}

unsigned char DepthChartGetEntry(int group, int index, int *pValue)
{
    unsigned char loaded = _DepthChart_bNeedsLoad;

    *pValue = _DepthChart_aCommitted[group][index];
    return loaded;
}

void DepthChartSetEntryPair(int group, int value, int index0, int index1)
{
    _DepthChart_aCommitted[group][index0] = value;
    _DepthChart_aCommitted[group][index1] = value;
}

int DepthChartFindPlayer(int group, int value, int *pFirst, int *pSecond)
{
    int found;
    unsigned char i;

    *pSecond = 0xFF;
    *pFirst = 0xFF;
    found = 0;
    for (i = 0; i < 7; i++) {
        if (_DepthChart_aCommitted[group][i] == value) {
            *pFirst = i;
            break;
        }
    }
    for (i = 7; i < 14; i++) {
        if (_DepthChart_aCommitted[group][i] == value) {
            *pSecond = i;
            break;
        }
    }
    if (*pFirst != 0xFF && *pSecond != 0xFF) {
        found = 1;
    }
    return found;
}

void DepthChartSetSide(int group, int *values)
{
    int i;

    for (i = 0; i < 14; i++) {
        _DepthChart_aCommitted[group][i] = values[i];
    }
}

void DepthChartGetSide(int group, DepthChartSide_t *pRecord)
{
    int i;

    for (i = 0; i < 14; i++) {
        pRecord->mUnknown[i] = _DepthChart_aCommitted[group][i];
    }
}

void DepthChartLoad(int reset)
{
    _DepthChart_bOpen = 1;
    if (FELoopIsMainFEActive()) {
        Desc_8008044C desc;
        int *p;

        desc.mUnknown0 = 1;
        fn_8008044C(&_DepthChart_sPlayerCursor, &desc, 0x54415453);
        _DepthChart_bNeedsLoad = 1;
        if (reset) {
            fn_80085D54();
            p = _DepthChart_aPending;
            do {
                *p = 7;
                p++;
            } while (p <= &_DepthChart_aPending[1]);
            fn_801C1F94(_DepthChart_aWorking, 0, sizeof(_DepthChart_aWorking));
            fn_801C1F94(_DepthChart_aCommitted, 0, sizeof(_DepthChart_aCommitted));
        }
    } else {
        fn_8008040C(&_DepthChart_sPlayerCursor, 0);
        if (_DepthChart_bNeedsLoad) {
            Object_8008044C cursor;
            Desc_8008044C desc;
            int ids[2];
            unsigned char group;
            int i;

            ids[0] = fn_80187C8C();
            ids[1] = fn_80187C6C();
            for (group = 0; group <= 1; group++) {
                desc.mUnknown0 = 1;
                desc.mUnknown4 = 1;
                desc.mUnknown8 = ids[group];
                fn_8008040C(&cursor, &desc);
                for (i = 0; i < 14; i++) {
                    PlayerDbSeekOriginalId(&cursor, _DepthChart_aCommitted[group][i], 0);
                    _DepthChart_aWorking[group][i] = _DepthChart_aCommitted[group][i] = PlayerDbGetId(&cursor);
                }
                fn_8008056C(&cursor);
            }
        }
        _DepthChart_bNeedsLoad = 0;
        fn_80085BE4(0);
        fn_80085BE4(1);
    }
}

void DepthChartSave(void)
{
    _DepthChart_bOpen = 0;
    fn_8008056C(&_DepthChart_sPlayerCursor);
    if (!FELoopIsMainFEActive()) {
        int ids[2];
        unsigned char group;
        int i;

        ids[0] = fn_80187C8C();
        ids[1] = fn_80187C6C();
        for (group = 0; group <= 1; group++) {
            for (i = 0; i <= 13; i++) {
                fn_8022D874(0x54484344, ids[group], _DepthChart_aCommitted[group][i], i);
            }
        }
    }
}
}
