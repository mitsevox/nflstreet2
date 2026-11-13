#ifndef GAME_BIG_OBJ_H
#define GAME_BIG_OBJ_H

#include "game/Object_8003DEC4.h"
#include "game/BigObjInst.h"
#include "game/Ball.h"
#include "game/LevelSurface.h"

struct BigObjModelState_t {
    char mUnknown0[40];
    unsigned char mUnknown40;
};

struct BigObjFlags_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    char mUnknown4[16];
    short mUnknown20;
};

/* 548-byte object of pool type 28, one per placed object. */
struct BigObj_t {
    int mUnknown0;
    Vector_80039F5C mPos;
    char mUnknown16[4];
    int (*mUnknown20)(BigObj_t *pObject);
    Quat_801EB488 mRot;
    char mUnknown40[132];
    union {
        AnimPose_t mUnknown172;
        struct {
            char mUnknown172Head[8];
            /* Its start is passed to fn_801D0C58 as a position vector. */
            char mUnknown180[24];
            int mUnknown204;
            char mUnknown208[12];
            /* Three 16-bit angles, also stored as the pose's bone angles. */
            short *mpUnknown220;
            char mUnknown224[4];
        };
    };
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
    BigObjModelState_t *mUnknown300;
    AnimSkeleton_t **mUnknown304;
    int mUnknown308;
    union {
        char mUnknown312[16];
        struct { char mUnknown312Head[4]; int mWord316; char mUnknown320Tail[8]; };
    };
    int mUnknown328;
    LevelSurface_t *mUnknown332;
    float mUnknown336;
    float mUnknown340;
    char mName[128];
    BigObjInst *mUnknown472;
    BigObjFlags_t *mUnknown476;
    int mUnknown480;
    char mUnknown484[64];
};

extern "C" {
BigObj_t *BigObjGet(int index);
AnimSkeleton_t *BigObjGetSkeleton(int index);
AnimSkeleton_t *BigObjGetItemSkeleton(BigObj_t *pObject);
}

#endif
