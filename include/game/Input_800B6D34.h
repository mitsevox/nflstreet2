#ifndef GAME_INPUT_800B6D34_H
#define GAME_INPUT_800B6D34_H

#include "game/Object_80039F5C.h"

/* Record that fn_800B6D34 fills for a player. Only the bytes its callers
   read are declared. */
struct Input_800B6D34 {
    char mUnknown0[12];
    float mUnknown12;
    float mUnknown16;
    char mUnknown20[72];
    unsigned char mUnknown92;
    unsigned char mUnknown93;
    unsigned char mUnknown94;
    unsigned char mUnknown95;
    unsigned char mUnknown96;
    unsigned char mUnknown97;
    unsigned char mUnknown98;
    char mUnknown99[5];
};

extern "C" {
void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);
}

#endif
