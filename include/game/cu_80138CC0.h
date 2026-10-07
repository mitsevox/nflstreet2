#ifndef GAME_CU_80138CC0_H
#define GAME_CU_80138CC0_H

#include "game/Object_80039F5C.h"

/* Two points 16 bytes apart with a float after the first; fn_80138CC0
   passes both points of two of these to fn_80088FFC, and fn_80138F64 copies
   one as a 32-byte block from +16 of a Sub_8003EC54 and adds the floats at
   +12 of two of them. These 32 bytes are the region +16..+48 that
   include/game/cu_8003EC04.h declares as separate floats. */
struct Segment_80138CC0 {
    Vector_80039F5C mUnknown0;
    float mUnknownC;
    Vector_80039F5C mUnknown10;
    char mUnknown1C[4];
};

extern "C" {
int fn_80138CC0(Segment_80138CC0 *pA, Segment_80138CC0 *pB, float limit);
int fn_80138D08(Vector_80039F5C *pOut, Segment_80138CC0 *pA, Segment_80138CC0 *pB, Vector_80039F5C *pStep, float limit);
int fn_80138E20(Vector_80039F5C *pPos, Segment_80138CC0 *pA, Segment_80138CC0 *pB, Vector_80039F5C *pStep, float limit);
}

#endif
