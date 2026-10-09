#ifndef GAME_OBJECT_80040818_H
#define GAME_OBJECT_80040818_H

#include "game/cu_80041210.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80054138.h"

struct Anim_8004AA34 {
    int mUnknown0;
    unsigned short mUnknown4;
};

struct Track_800410E0 {
    char mUnknown0[6];
    unsigned short mUnknown6;
};

struct Model_8004E0CC {
    char mUnknown0[40];
    unsigned char mUnknown40;
};

struct Flags_800411C8 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
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
    char mUnknown180[52];
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
