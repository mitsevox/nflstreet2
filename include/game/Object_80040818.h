#ifndef GAME_OBJECT_80040818_H
#define GAME_OBJECT_80040818_H

#include "game/Object_80039F5C.h"

struct Area_80054138;
struct Flags_800411C8;
struct Model_8004E0CC;
struct Object_80041904;
struct Track_800410E0;

struct Anim_8004AA34 {
    int mUnknown0;
    unsigned short mUnknown4;
};

/* 548-byte object of pool type 28, one per placed object. */
struct Object_80040818 {
    int mUnknown0;
    Vector_80039F5C mPos;
    char mUnknown16[4];
    int (*mUnknown20)(Object_80040818 *pObject);
    Quat_801EB488 mRot;
    char mUnknown40[132];
    Anim_8004AA34 mUnknown172;
    /* Its start is passed to fn_801D0C58 as a position vector. */
    char mUnknown180[24];
    int mUnknown204;
    char mUnknown208[12];
    /* Three 16-bit angles. */
    short *mpUnknown220;
    char mUnknown224[8];
    unsigned int mUnknown232_0 : 27;
    unsigned int mUnknown232_27 : 1;
    unsigned int mUnknown232_28 : 1;
    unsigned int mUnknown232_29 : 1;
    unsigned int mUnknown232_30 : 1;
    unsigned char mUnknown232_31 : 1;
    char mUnknown236[64];
    Model_8004E0CC *mUnknown300;
    Track_800410E0 **mUnknown304;
    int mUnknown308;
    char mUnknown312[16];
    int mUnknown328;
    Area_80054138 *mUnknown332;
    float mUnknown336;
    float mUnknown340;
    char mName[128];
    Object_80041904 *mUnknown472;
    Flags_800411C8 *mUnknown476;
    int mUnknown480;
    char mUnknown484[64];
};

#endif
