#ifndef GAME_OBJECT_8015C244_H
#define GAME_OBJECT_8015C244_H

#include "game/Object_80039F5C.h"

/* 0xD4-byte instance (the size fn_8015BED4 registers with fn_8015A2B4 and
   fn_8015A354). +20 is the record set up through fn_8003F66C-fn_8003F6E8,
   which receives the ten points at +88. */
struct Object_8015C244 {
    char mUnknown0[20];
    char mUnknown20[28];
    float mUnknown48;
    char mUnknown52[16];
    float mUnknown68;
    float mUnknown72;
    char mUnknown76[4];
    unsigned char mUnknown80;
    unsigned char mUnknown81;
    char mUnknown82[2];
    unsigned int mUnknown84;
    float mUnknown88[10][3];
    Object_80039F5C *mpUnknown208;
};

#endif
