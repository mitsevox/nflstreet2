#ifndef GAME_OBJECT_80040818_H
#define GAME_OBJECT_80040818_H

#include "game/Object_8003DEC4.h"
#include "game/cu_80041210.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80054138.h"

struct Model_8004E0CC {
    char mUnknown0[40];
    unsigned char mUnknown40;
};

struct Flags_800411C8 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    char mUnknown4[16];
    short mUnknown20;
};

/* 548-byte object of pool type 28, one per placed object. */
struct Object_80040818 {
    int mUnknown0;
    Vector_80039F5C mPos;
    char mUnknown16[4];
    int (*mUnknown20)(Object_80040818 *pObject);
    Quat_801EB488 mRot;
    char mUnknown40[132];
    Pose_80041930 mUnknown172;
    void *mUnknown228;
    unsigned int mUnknown232_0 : 27;
    unsigned int mUnknown232_27 : 1;
    unsigned int mUnknown232_28 : 1;
    unsigned int mUnknown232_29 : 1;
    unsigned int mUnknown232_30 : 1;
    unsigned char mUnknown232_31 : 1;
    char mUnknown236[12];
    unsigned int mUnknown248;
    char mUnknown252[48];
    Model_8004E0CC *mUnknown300;
    Skeleton_80041930 **mUnknown304;
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

extern "C" {
Object_80040818 *fn_80040F18(int index);
Skeleton_80041930 *fn_800410B8(int index);
Skeleton_80041930 *fn_800410E0(Object_80040818 *pObject);
}

#endif
