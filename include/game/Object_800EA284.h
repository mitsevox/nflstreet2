#ifndef GAME_OBJECT_800EA284_H
#define GAME_OBJECT_800EA284_H

#include "game/Object_80039F5C.h"

/* Record addressed through word +32 of the player's +3092 object. */
struct Record_800EA284 {
    char mUnknown0[8];
    float mUnknown8;
    char mUnknown12[4];
    Vector_80039F5C mUnknown16;
    char mUnknown28[4];
    Vector_80039F5C mUnknown32;
};

struct Object_800EA284 {
    char mUnknown0[32];
    Record_800EA284 *mpUnknown32;
};

#endif
