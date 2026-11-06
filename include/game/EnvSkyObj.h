#ifndef GAME_ENVSKYOBJ_H
#define GAME_ENVSKYOBJ_H

#include "game/Object_80039F5C.h"
#include "game/Object_80235588.h"

/* 0x1D0-byte item of the type-13 pool created by EnvSkyObjCreate. */
struct EnvSkyObj_t {
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
void EnvSkyInit(EnvSkyObj_t *pInstance);
void EnvSkyShutdown(EnvSkyObj_t *pInstance);
void EnvSkyDraw(EnvSkyObj_t *pInstance, int unused);
}

#endif
