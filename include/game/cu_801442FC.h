#ifndef GAME_CU_801442FC_H
#define GAME_CU_801442FC_H

struct Tracker_801442FC {
    int mId;
    unsigned char mCount;
};

struct Object_80144310 {
    char mUnknown0[0xC];
    float mUnknownC;
    float mUnknown10;
    float mUnknown14;
    char mUnknown18[4];
    int mUnknown1C;
};

#ifdef __cplusplus
extern "C" {
#endif
void fn_801442FC(Tracker_801442FC *pTracker);
int fn_80144310(Tracker_801442FC *pTracker, Object_80144310 *pSource, float *pDirection, float *pScaled);
void fn_801444A0(Tracker_801442FC *pTracker, Object_80144310 *pSource);
#ifdef __cplusplus
}
#endif

#endif
