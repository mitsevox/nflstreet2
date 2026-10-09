#ifndef GAME_LEVEL_80054130_H
#define GAME_LEVEL_80054130_H

#include "game/Object_80039F5C.h"

/* 36-byte placement entry of the level data returned by fn_80054130. */
struct Entry_80054130 {
    float mUnknown0[6];
    unsigned short mUnknown24;
    int mUnknown28;
    int mUnknown32;
};

/* 60-byte record of the list at +140 of the level data: a point followed by
   four points at +12. */
struct Record_80054130 {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12[4];
};

/* Four points passed to fn_800542DC and fn_8005434C. fn_800542DC copies mX
   and mY of points whose mZ is below 0.1; fn_8005434C returns the last mZ
   at or above 0.1. fn_800541AC and fn_8005429C do the same over
   Record_80054130::mUnknown12. */
struct Points_800542DC {
    Vector_80039F5C mPoint[4];
};

/* 36-byte entry of the list at +28 of the level data; fn_8005415C stores
   its second argument at +8 of each entry whose +32 equals its first. */
struct Entry_8005415C {
    char mUnknown0[8];
    int mUnknown8;
    char mUnknown12[20];
    int mUnknown32;
};

/* 28-byte entry of the list at +156 of the level data, returned by
   fn_8005438C. */
struct Object_8005438C {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
    int mUnknown24;
};

/* The level data whose address fn_80054130 returns. Only the accessed
   fields are declared. */
struct Level_80054130 {
    char mUnknown0[24];
    unsigned int mUnknown24;
    Entry_8005415C *mUnknown28;
    char mUnknown32[12];
    char *mUnknown44;
    char mUnknown48[12];
    char *mUnknown60;
    char mUnknown64[4];
    char *mUnknown68;
    char mUnknown72[16];
    unsigned int mUnknown88;
    Entry_80054130 *mUnknown92;
    char mUnknown96[8];
    unsigned int mUnknown104;
    Entry_80054130 *mUnknown108;
    unsigned int mUnknown112;
    Entry_80054130 *mUnknown116;
    char mUnknown120[16];
    unsigned int mUnknown136;
    Record_80054130 *mUnknown140;
    char mUnknown144[8];
    unsigned int mUnknown152;
    Object_8005438C *mUnknown156;
};

extern "C" {
Level_80054130 *fn_80054130(void);
void fn_800541AC(Record_80054130 *pRecord, void *pA, void *pB);
Object_8005438C *fn_8005438C(int id);
}

#endif
