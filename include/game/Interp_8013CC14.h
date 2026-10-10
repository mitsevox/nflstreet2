#ifndef GAME_INTERP_8013CC14_H
#define GAME_INTERP_8013CC14_H

/* A value easing from mStart to mTarget; mUpdate advances it. */
struct Interp_8013CC14 {
    float mStart;
    float mTarget;
    float mValue;
    float mTime;
    float mRate;
    void (*mUpdate)(Interp_8013CC14 *pInterp, int steps);
};

typedef void (*InterpFunc_8013CC14)(Interp_8013CC14 *pInterp, int steps);

#endif
