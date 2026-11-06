#ifndef GAME_BALL_SWEEP_H
#define GAME_BALL_SWEEP_H

#include "game/Object_80039F5C.h"

/* Two points 16 bytes apart with a float after the first; BallSegmentsTouch
   passes both points of two of these to fn_80088FFC, and BallSweepToPart copies
   one as a 32-byte block from +16 of a CollideShape_t and adds the floats at
   +12 of two of them. These 32 bytes are the region +16..+48 that
   include/game/Collide.h declares as separate floats. */
struct BallSegment_t {
    Vector_80039F5C mUnknown0;
    float mUnknownC;
    Vector_80039F5C mUnknown10;
    char mUnknown1C[4];
};

extern "C" {
int BallSegmentsTouch(BallSegment_t *pA, BallSegment_t *pB, float limit);
int BallSweepLinear(Vector_80039F5C *pOut, BallSegment_t *pA, BallSegment_t *pB, Vector_80039F5C *pStep, float limit);
int BallSweepBisect(Vector_80039F5C *pPos, BallSegment_t *pA, BallSegment_t *pB, Vector_80039F5C *pStep, float limit);
}

#endif
