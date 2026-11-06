#ifndef GAME_PASSICONOBJ_H
#define GAME_PASSICONOBJ_H

#include "game/Object_80039F5C.h"

struct PassIconObj_t {
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
void PassIconObjRegister(void *pOwner);
void PassIconObjUnregister(void);
PassIconObj_t *PassIconObjNew(void *pOwner, unsigned char value, int a, int b);
void PassIconObjDelete(void *pOwner, PassIconObj_t *pItem);
void PassIconObjSetStyle(PassIconObj_t *pItem, unsigned char value);
}

#endif
