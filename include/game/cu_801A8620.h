#ifndef GAME_CU_801A8620_H
#define GAME_CU_801A8620_H

#include "game/Object_80039F5C.h"

struct Texture_801A8D08;
struct Instance_801A8D9C;
struct Pose_801A8B84;
struct Env_801A8D9C;
struct Object_801A8620;

struct Element_801A8620 { unsigned char mUnknown0[0x28]; };

struct Child_801A9430 {
    unsigned char mUnknown0[0x30]; Vector_80039F5C mUnknown30;
    Vector_80039F5C mUnknown3C; unsigned char mUnknown48[8];
    Object_801A8620 *mpUnknown50; unsigned char mUnknown54[4];
    void *mpUnknown58; Child_801A9430 *mpUnknown5C; Vector_80039F5C mUnknown60;
    unsigned char mUnknown6C;
};

struct Object_801A8620 {
    unsigned char mUnknown0[4]; Vector_80039F5C mUnknown4;
    unsigned char mUnknown10[4]; int (*mUnknown14)(Object_801A8620 *, int); Vector_80039F5C mUnknown18;
    unsigned char mUnknown24[0x84]; void *mpUnknownA8; unsigned char mUnknownAC[8]; Vector_80039F5C mUnknownB4;
    unsigned char mUnknownC0[12]; int mUnknownCC;
    unsigned char mUnknownD0[12]; int mUnknownDC; unsigned char mUnknownE0[8];
    union { unsigned int mWord; unsigned char mBytes[4]; } mUnknownE8;
    unsigned char mUnknownEC[8]; int mUnknownF4; int mUnknownF8;
    unsigned char mUnknownFC; unsigned char mUnknownFD[3]; Texture_801A8D08 *mpUnknown100;
    Element_801A8620 mUnknown104; Instance_801A8D9C *mpUnknown12C;
    Env_801A8D9C *mpUnknown130; unsigned char mUnknown134[4]; unsigned char mUnknown138;
    unsigned char mUnknown139[3]; int mUnknown13C; unsigned char mUnknown140;
    unsigned char mUnknown141[11]; void *mpUnknown14C; unsigned char mUnknown150[8];
    char mUnknown158[128]; Pose_801A8B84 *mpUnknown1D8;
    unsigned char mUnknown1DC[4]; Child_801A9430 *mpUnknown1E0;
};

extern "C" void fn_801A8D08(Child_801A9430 *p, Object_801A8620 *owner);

#endif
