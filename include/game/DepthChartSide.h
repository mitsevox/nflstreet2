#ifndef GAME_DEPTHCHARTSIDE_H
#define GAME_DEPTHCHARTSIDE_H

/* Record copied out by DepthChartGetSide. */
struct DepthChartSide_t {
    int mUnknown[14];
};

extern "C" void DepthChartGetSide(int a, DepthChartSide_t *pRecord);

#endif
