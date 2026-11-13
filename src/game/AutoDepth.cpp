/* Automatic depth-chart builder: scores every player of a team for each roster slot from his
   ratings and fills the offensive and defensive slots with the best remaining players. */
#include "game/FELoop.h"
#include "game/GameModeType.h"
#include "game/fn_802372EC.h"
#include "game/AutoDepth.h"
#include "game/Object_8008044C.h"
#include "game/fn_801D2B7C.h"

extern "C" {
int fn_801486A0(void);
unsigned int fn_80178DC8(void);
void fn_80085020(DbCursor *pObject);
void fn_80085060(DbCursor *pObject);
int fn_80085080(DbCursor *pObject, int value, int *pResult);
int fn_800850B8(DbCursor *pObject, int category);
unsigned int fn_80081ECC(int category, int *pValues);
void fn_801F4B20(void);
}

static AutoDepthPlayer_t *_AutoDepth_pRecords = 0;
static AutoDepthRateFunc _AutoDepth_pRateFunc = AutoDepthRatePlayer;
static AutoDepthSelectFunc _AutoDepth_pSelectFunc = AutoDepthPickBest;
static unsigned char _AutoDepth_aOffenseOrder[7] = {0, 1, 2, 4, 3, 6, 5};
static unsigned char _AutoDepth_aOffenseOrder3[7] = {0, 2, 3, 1, 5, 4, 6};
static unsigned char _AutoDepth_aOffenseOrder4[7] = {0, 1, 2, 3, 5, 4, 6};
static unsigned char _AutoDepth_aDefenseOrder[7] = {5, 0, 1, 4, 6, 2, 3};
static unsigned char _AutoDepth_aDefenseOrder3[7] = {4, 6, 2, 3, 5, 0, 1};
static unsigned char _AutoDepth_aDefenseOrder4[7] = {4, 2, 6, 3, 5, 0, 1};
static int _AutoDepth_iCount;

extern "C" {
int AutoDepthListHas(int *list, int value)
{
    int found = 0;
    int i = 0;
    while (list[i] != 255) {
        if (value == list[i]) {
            found = 1;
            break;
        }
        i++;
    }
    return found;
}

void AutoDepthGetBest(int category, int *id, unsigned int *value)
{
    int ids[4];
    unsigned int values[4];
    AutoDepthRankSlot(category, ids, values);
    *id = ids[0];
    *value = values[0];
}

void AutoDepthRankSlot(int category, int *ids, unsigned int *values)
{
    for (int i = 0; i < 4; i++) {
        values[i] = 0;
        ids[i] = 32767;
    }
    for (int i = 0; i < _AutoDepth_iCount; i++) {
        if (!_AutoDepth_pRecords[i].excluded) {
            unsigned int value = _AutoDepth_pRecords[i].values[category];
            int id = _AutoDepth_pRecords[i].id;
            int ownCategory = _AutoDepth_pRecords[i].category;
            if (ids[0] == 32767 || value > values[0] ||
                (value == values[0] && category == ownCategory)) {
                for (unsigned int j = 3; j > 0; j--) {
                    values[j] = values[j - 1];
                    ids[j] = ids[j - 1];
                }
                values[0] = value;
                ids[0] = id;
            } else {
                for (unsigned int j = 3; j > 0; j--) {
                    if (ids[j] != 32767) {
                        if (value > values[j] || (value == values[j] && category == ownCategory)) {
                            if (j < 3) {
                                values[j + 1] = values[j];
                                ids[j + 1] = ids[j];
                            }
                            values[j] = value;
                            ids[j] = id;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void AutoDepthSetExcluded(int id, unsigned char excluded)
{
    for (int i = 0; i < _AutoDepth_iCount; i++) {
        if (_AutoDepth_pRecords[i].id == id) {
            _AutoDepth_pRecords[i].excluded = excluded;
            break;
        }
    }
}

void AutoDepthSetAllExcluded(unsigned char excluded)
{
    for (int i = 0; i < _AutoDepth_iCount; i++) _AutoDepth_pRecords[i].excluded = excluded;
}

void AutoDepthAllowOnly(int *list)
{
    AutoDepthSetAllExcluded(1);
    while (*list != 32767) AutoDepthSetExcluded(*list++, 0);
}

void AutoDepthRatePlayer(AutoDepthPlayer_t *record, int *values, DbCursor *query)
{
    for (int i = 0; i < 14; i++) {
        int adjustment = fn_800850B8(query, i);
        unsigned int value = fn_80081ECC(i, values) * (adjustment + 100) / 200;
        if (record->category == i) value = value * 1.1f;
        record->values[i] = value;
    }
}

void AutoDepthPickBest(AutoDepthPlayer_t *unused, int count, int *excluded, int *id, int *category)
{
    unsigned int bestValues[4];
    unsigned int values[4];
    int bestIds[4];
    int ids[4];
    bestValues[0] = 0;
    for (int i = 0; i < 14; i++) {
        if (!AutoDepthListHas(excluded, i)) {
            AutoDepthRankSlot(i, ids, values);
            if (values[0] >= bestValues[0]) {
                for (int j = 0; j < 4; j++) {
                    bestValues[j] = values[j];
                    bestIds[j] = ids[j];
                }
                *id = bestIds[0];
                *category = i;
            }
        }
    }
    if (*category != 0 && GameModeTypeGet() == 2) {
        for (unsigned int i = 0; i < 3; i++) {
            if (bestIds[i + 1] == 32767) break;
            if (fn_802372EC(1, 4) == 0) *id = bestIds[i + 1];
            else break;
        }
    }
}

void AutoDepthBuild(int value, int *list, AutoDepthPlayer_t **pRecords)
{
    DbCursor first;
    Object_8008044C second;
    int values[10];
    AutoDepthPlayer_t **records;
    if (!pRecords) {
        records = &_AutoDepth_pRecords;
    } else {
        records = pRecords;
    }
    fn_80085020(&first);
    fn_80085080(&first, value, 0);
    fn_8008044C(&second, 0, FELoopIsMainFEActive() ? 0x54415453 : 0x454D4147);
    int i = 0;
    while (list[i] != 32767) i++;
    _AutoDepth_iCount = i;
    *records = (AutoDepthPlayer_t *)fn_801D2B7C(i * sizeof(AutoDepthPlayer_t), 0, 0);
    for (i = 0; i < _AutoDepth_iCount; i++) {
        PlayerDbSeekId(&second, list[i], 0);
        (*records)[i].id = list[i];
        (*records)[i].excluded = 0;
        (*records)[i].category = PlayerDbGetPbpo(&second);
        PlayerGetGearRatings(&second, values);
        _AutoDepth_pRateFunc(&(*records)[i], values, &first);
        fn_801F4B20();
    }
    fn_8008056C(&second);
    fn_80085060(&first);
}

void AutoDepthFree(AutoDepthPlayer_t **pRecords)
{
    AutoDepthPlayer_t **records;
    if (!pRecords) {
        records = &_AutoDepth_pRecords;
    } else {
        records = pRecords;
    }
    fn_801D2BD0(*records);
    *records = 0;
}

void AutoDepthFillChart(int value, int *list, int *ids)
{
    unsigned int i;
    int id;
    unsigned int score;
    int category;
    AutoDepthBuild(value, list, 0);
    for (i = 0; i < fn_80178DC8(); i++) {
        switch (fn_801486A0()) {
        case 3: category = _AutoDepth_aOffenseOrder3[i]; break;
        case 4: category = _AutoDepth_aOffenseOrder4[i]; break;
        default: category = _AutoDepth_aOffenseOrder[i]; break;
        }
        AutoDepthGetBest(category, &id, &score);
        ids[category] = id;
        AutoDepthSetExcluded(id, 1);
    }
    AutoDepthSetAllExcluded(0);
    for (i = 0; i < fn_80178DC8(); i++) {
        switch (fn_801486A0()) {
        case 3: category = _AutoDepth_aDefenseOrder3[i]+7; break;
        case 4: category = _AutoDepth_aDefenseOrder4[i]+7; break;
        default: category = _AutoDepth_aDefenseOrder[i]+7; break;
        }
        AutoDepthGetBest(category, &id, &score);
        ids[category] = id;
        AutoDepthSetExcluded(id, 1);
    }
    AutoDepthFree(0);
}

unsigned int AutoDepthGetBestSlot(AutoDepthPlayer_t *records, int *excluded, int id)
{
    unsigned int result = 0;
    AutoDepthPlayer_t *saved = 0;
    if (records) {
        saved = _AutoDepth_pRecords;
        _AutoDepth_pRecords = records;
    }
    int i;
    for (i = 0; i < _AutoDepth_iCount; i++) if (id==_AutoDepth_pRecords[i].id) break;
    if (i < _AutoDepth_iCount) {
        unsigned int best = 0, category = 0;
        for (unsigned int j = 0; j < 14; j++) {
            if (!AutoDepthListHas(excluded, j)) {
                if (_AutoDepth_pRecords[i].values[j] > best) {
                    best = _AutoDepth_pRecords[i].values[j];
                    category = j;
                }
            }
        }
        result = category;
    }
    if (records) _AutoDepth_pRecords = saved;
    return result;
}

void AutoDepthSelect(AutoDepthPlayer_t *records, int *allowed, int *excluded, int *id, int *category)
{
    *category = 255;
    *id = 32767;
    AutoDepthPlayer_t *saved = 0;
    if (records) {
        saved = _AutoDepth_pRecords;
        _AutoDepth_pRecords = records;
    }
    AutoDepthAllowOnly(allowed);
    _AutoDepth_pSelectFunc(_AutoDepth_pRecords, _AutoDepth_iCount, excluded, id, category);
    if (records) _AutoDepth_pRecords = saved;
}

void AutoDepthSetRateCallback(AutoDepthRateFunc callback)
{
    if (callback) _AutoDepth_pRateFunc = callback;
    else _AutoDepth_pRateFunc = AutoDepthRatePlayer;
}

void AutoDepthSetSelectCallback(AutoDepthSelectFunc callback)
{
    if (callback) _AutoDepth_pSelectFunc = callback;
    else _AutoDepth_pSelectFunc = AutoDepthPickBest;
}
}
