#ifndef GAME_CAM_INTERP_H
#define GAME_CAM_INTERP_H

/* A value easing from mStart to mTarget; mUpdate advances it. */
struct CamInterp_t {
    float mStart;
    float mTarget;
    float mValue;
    float mTime;
    float mRate;
    void (*mUpdate)(CamInterp_t *pInterp, int steps);
};

typedef void (*CamInterpFunc_t)(CamInterp_t *pInterp, int steps);

#endif
