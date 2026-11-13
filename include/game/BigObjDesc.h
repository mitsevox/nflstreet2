#ifndef GAME_BIG_OBJ_DESC_H
#define GAME_BIG_OBJ_DESC_H

#include "game/BigObjInst.h"

/* Placement record that BigObjCreate turns into an object. */
struct BigObjDesc_t {
    int mUnknown0;
    char mName[128];
    BigObjPlacement_t mUnknown132;
    void *mUnknown160;
    void *mUnknown164;
    int mUnknown168;
    int mUnknown172;
    int mUnknown176;
    unsigned short mUnknown180;
};

#endif
