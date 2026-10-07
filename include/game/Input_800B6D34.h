#ifndef GAME_INPUT_800B6D34_H
#define GAME_INPUT_800B6D34_H

#include "game/Object_80039F5C.h"

/* 104-byte record that fn_800B6D34 fills for a player. */
struct Input_800B6D34 {
    char mUnknown0[12];
    float mUnknown12;
    float mUnknown16;
    char mUnknown20[73];
    unsigned char mUnknown93;
    char mUnknown94[1];
    unsigned char mUnknown95;
    unsigned char mUnknown96;
    char mUnknown97[7];
};

extern "C" void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);

#endif
