#ifndef GAME_INPUT_800B6D34_H
#define GAME_INPUT_800B6D34_H

#include "game/Object_80039F5C.h"

/* Filled by fn_800B6D34 for the player object it is given. Only the bytes
   its callers test are declared. */
struct Input_800B6D34 {
    char mUnknown0[93];
    unsigned char mUnknown93;
    char mUnknown94[1];
    unsigned char mUnknown95;
    unsigned char mUnknown96;
    unsigned char mUnknown97;
    unsigned char mUnknown98;
    char mUnknown99[5];
};

extern "C" void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);

#endif
