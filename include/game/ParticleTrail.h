#ifndef GAME_PARTICLE_TRAIL_H
#define GAME_PARTICLE_TRAIL_H

#include "game/Vector_80039F5C.h"

/* Red, green, blue and alpha of a trail, copied whole from the colour tables. */
struct ParticleTrailColor_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
};

/* One of the four 0x8C-byte point histories at the start of
   ParticleTrailSet_t. Each update fills mSource[0]/mSource[1] through
   ParticleTrailGetJointPoint from the matrix indices mIndex[0]/mIndex[1] and stores one
   of them into the eight-entry ring mPoints at mHead. */
struct ParticleTrail_t {
    Vector_80039F5C mPoints[8];
    Vector_80039F5C mSource[2];
    int mHead;
    unsigned int mCount;
    int mToggle;
    int mIndex[2];
};

/* 0xB4-byte record copied whole from the object at +0x5C. */
struct ParticleTrailBodyPose_t {
    int mUnknown[45];
};

/* 0x36-byte record copied whole from the object at +0x248. */
struct ParticleTrailSubPose_t {
    short mUnknown[27];
};

/* Block at +0x1444 of Object_8003DEC4 (0x5AC bytes, to the end of the
   object). */
struct ParticleTrailSet_t {
    ParticleTrail_t mTrails[4];
    float mUnknown230;
    unsigned int mUnknown234;
    int mUnknown238;
    unsigned char mUnknown23C;
    ParticleTrailColor_t mUnknown240;
    ParticleTrailColor_t mUnknown250;
    float mUnknown260[2][4][4];
    ParticleTrailBodyPose_t mUnknown2E0[2];
    Vector_80039F5C mUnknown448[2];
    int mUnknown460[2];
    ParticleTrailSubPose_t mUnknown468[2];
    float mUnknown4D4[2][4][4];
    int mUnknown554;
    unsigned int mUnknown558;
    int mUnknown55C;
    unsigned char mUnknown560;
    float mUnknown564;
    unsigned char mUnknown568;
    float mUnknown56C;
    float mUnknown570;
    float mUnknown574;
    char mPad578[0x57C - 0x578];
    unsigned char mUnknown57C;
    float mUnknown580;
    float mUnknown584;
    float mUnknown588;
    char mPad58C[0x590 - 0x58C];
    float mUnknown590;
    float mUnknown594;
    float mUnknown598;
    char mPad59C[0x5A0 - 0x59C];
    unsigned int mUnknown5A0;
    int mUnknown5A4;
    unsigned int mUnknown5A8;
};

#endif
