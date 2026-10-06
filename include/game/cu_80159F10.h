#ifndef GAME_CU_80159F10_H
#define GAME_CU_80159F10_H

#include "game/Object_80039F5C.h"

struct Instance_80159F10 {
    char mPad00[4];
    Vector_80039F5C mUnknown04;
    char mPad10[4];
    int mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C;
    signed char mUnknown1D;
    char mPad1E[2];
    float mUnknown20;
};

extern "C" {
void fn_8015A110(void *pOwner);
void fn_8015A17C(void);
Instance_80159F10 *fn_8015A1A8(void *pOwner, unsigned char value, int a, int b);
void fn_8015A204(void *pOwner, Instance_80159F10 *pItem);
void fn_8015A240(Instance_80159F10 *pItem, unsigned char value);
}

#endif
