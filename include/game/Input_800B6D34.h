#ifndef GAME_INPUT_800B6D34_H
#define GAME_INPUT_800B6D34_H

#include "game/Object_80039F5C.h"

/* 104-byte record that fn_800B6D34 fills for a player by copying the block
   fn_800F177C returns; fn_800F0FD0 builds those blocks. Only accessed members
   are named. */
struct Input_800B6D34 {
    unsigned int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    float mUnknown24[12];
    float mUnknown72[5];
    unsigned char mUnknown92[9];
    char mUnknown101[3];
};

extern "C" {
void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);
}

#endif
