#ifndef GAME_INPUT_800B6D34_H
#define GAME_INPUT_800B6D34_H

#include "game/Object_80039F5C.h"

/* 104-byte record that fn_800B6D34 fills for a player through fn_800F177C,
   which copies one of the blocks fn_800F0FD0 builds into it. Only accessed
   members are named. */
struct Input_800B6D34 {
    unsigned int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    float mUnknown24[12];
    float mUnknown72[5];
    union {
        unsigned char mBytes92[9];
        struct {
            unsigned char mUnknown92;
            unsigned char mUnknown93;
            unsigned char mUnknown94;
            unsigned char mUnknown95;
            unsigned char mUnknown96;
            unsigned char mUnknown97;
            unsigned char mUnknown98;
            char mUnknown99[2];
        };
    };
    char mUnknown101[3];
};

extern "C" {
void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);
}

#endif
