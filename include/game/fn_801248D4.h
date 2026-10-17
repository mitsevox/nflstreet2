#ifndef GAME_FN_801248D4_H
#define GAME_FN_801248D4_H
#include "game/Object_80039F5C.h"

struct Filter_801248D4 {
    unsigned char mCount;
    unsigned char mValues[1];
};

extern "C" int fn_801248D4(Object_80039F5C *p, Vector_80039F5C *pPos, Vector_80039F5C *pTarget, Object_80039F5C **pOut, float margin, float width, Filter_801248D4 *pFilter, Object_80039F5C *pExclude);
#endif
