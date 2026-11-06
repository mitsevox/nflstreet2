#ifndef GAME_DEPTHCHART_H
#define GAME_DEPTHCHART_H

/* src/game/DepthChart.cpp; DepthChartGetSide is declared in game/DepthChartSide.h. */

/* Passed by pointer; only the words at +4 and +8 are read. */
struct DepthChartText_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
void DepthChartSetSpotSlot(int kind, int index, int value);
int DepthChartCanSwapSpots(int a, int kind, int index0, int index1, int unused);
int DepthChartCommit(int group);
int DepthChartCancel(int group);
void DepthChartAutoFill(int group, int *list, int value);
void DepthChartLoad(int reset);
void DepthChartSave(void);
void DepthChartGetSpotStatNames(int a, int kind, int index, int d, DepthChartText_t *p0, DepthChartText_t *p1, DepthChartText_t *p2);
void DepthChartGetSpotPlayer(int a, int kind, int index, int key, int e, DepthChartText_t *pPair, int *pValues, int *pResult);
}

#endif
