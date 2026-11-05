#ifndef GAME_LIGHT_TRACKER_H
#define GAME_LIGHT_TRACKER_H

struct LightTracker_t {
    int mId;
    unsigned char mCount;
};

struct LightSource_t {
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
void LightTrackerReset(LightTracker_t *pTracker);
int LightTrackerUpdate(LightTracker_t *pTracker, LightSource_t *pSource, float *pDirection, float *pScaled);
void LightTrackerSnap(LightTracker_t *pTracker, LightSource_t *pSource);
#ifdef __cplusplus
}
#endif

#endif
