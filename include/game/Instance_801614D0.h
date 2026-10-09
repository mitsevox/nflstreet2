#ifndef GAME_INSTANCE_801614D0_H
#define GAME_INSTANCE_801614D0_H

#include "game/Object_80039F5C.h"
#include "game/Object_80235588.h"

/* 0x1D0-byte item of the type-13 pool created by fn_801615EC. */
struct Instance_801614D0 {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    char mUnknown10[4];
    int mUnknown14;
    char mUnknown18[0x30];
    Object_80235588 mUnknown48;
    Object_80235588 mUnknown108;
    int mUnknown1C8;
    unsigned char mUnknown1CC;
};

extern "C" {
void fn_801A5478(Instance_801614D0 *pInstance);
void fn_801A553C(Instance_801614D0 *pInstance);
void fn_801A5568(Instance_801614D0 *pInstance, int unused);
}

#endif
