#ifndef GAME_AUTODEPTH_H
#define GAME_AUTODEPTH_H

#include "game/DbCursor.h"

struct AutoDepthPlayer_t {
    int id;
    unsigned int values[14];
    unsigned char excluded;
    unsigned char mUnknown61[3];
    int category;
};

typedef void (*AutoDepthRateFunc)(AutoDepthPlayer_t *, int *, DbCursor *);
typedef void (*AutoDepthSelectFunc)(AutoDepthPlayer_t *, int, int *, int *, int *);

extern "C" {
int AutoDepthListHas(int *list, int value);
void AutoDepthGetBest(int category, int *id, unsigned int *value);
void AutoDepthRankSlot(int category, int *ids, unsigned int *values);
void AutoDepthSetExcluded(int id, unsigned char excluded);
void AutoDepthSetAllExcluded(unsigned char excluded);
void AutoDepthAllowOnly(int *list);
void AutoDepthRatePlayer(AutoDepthPlayer_t *record, int *values, DbCursor *query);
void AutoDepthPickBest(AutoDepthPlayer_t *records, int count, int *excluded, int *id, int *category);
void AutoDepthBuild(int value, int *list, AutoDepthPlayer_t **pRecords);
void AutoDepthFree(AutoDepthPlayer_t **pRecords);
void AutoDepthFillChart(int value, int *list, int *ids);
unsigned int AutoDepthGetBestSlot(AutoDepthPlayer_t *records, int *excluded, int id);
void AutoDepthSelect(AutoDepthPlayer_t *records, int *allowed, int *excluded, int *id, int *category);
void AutoDepthSetRateCallback(AutoDepthRateFunc callback);
void AutoDepthSetSelectCallback(AutoDepthSelectFunc callback);
}

#endif
