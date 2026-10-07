#ifndef GAME_OBJECT_8003DEC4_H
#define GAME_OBJECT_8003DEC4_H

#include "game/FMCAPPORT.h"
#include "game/Object_80146094.h"

struct Item_800476DC;

/* Object returned by fn_8003DEC4 (0x19F0 bytes, the size fn_8004A140 passes
   to fn_801DCF0C). */
struct Object_8003DEC4 {
    char mUnknown0[4];
    char mUnknown4[16];
    int mUnknown20;
    float mUnknown24;
    char mUnknown28[4];
    int mUnknown32;
    int mUnknown36;
    char mUnknown40[12];
    float mUnknown52;
    float mUnknown56;
    float mUnknown60;
    char mUnknown64[12];
    int mUnknown76;
    char mUnknown80[12];
    Block_801470F0 *mUnknown92;
    float (*mUnknown96)[4][4];
    char mUnknown100[16];
    char mUnknown116[468];
    Half_801470F0 *mUnknown584;
    char mUnknown588[320];
    float mUnknown908[4][4];
    char mUnknown972[16];
    Item_800476DC *mUnknown988;
    char mUnknown992[3192];
    char mUnknown4184[772];
    int mUnknown4956;
    char mUnknown4960[8];
    unsigned char mUnknown4968;
    unsigned char mUnknown4969;
    unsigned char mUnknown4970;
    unsigned char mUnknown4971;
    unsigned char mUnknown4972;
    char mUnknown4973[3];
    FMCAPPORTValues mUnknown4976;
    Object_80146094 mUnknown5188;
};

extern "C" {
Object_8003DEC4 *fn_8003DEC4(int index);
/* Callback registered by fn_8004A140 through fn_801DD0C8; its second
   argument is not read. */
int fn_8004A1A8(Object_8003DEC4 *pObject, int unused);
}

#endif
