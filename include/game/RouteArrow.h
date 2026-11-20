#ifndef GAME_ROUTEARROW_H
#define GAME_ROUTEARROW_H

#include "game/Object_80039F5C.h"

struct RouteArrow_t {
    char mUnknown0[20];
    char mArrow[28];
    float mHighlight;
    char mUnknown52[12];
    unsigned char mbMotion;
    char mUnknown65[3];
    float mStartX;
    float mStartY;
    unsigned char *mpCommands;
    unsigned char mbShown;
    unsigned char mbFlip;
    char mUnknown82[2];
    unsigned int mPendingTurn;
    float mPoints[10][3];
    Object_80039F5C *mpPlayer;
};

#endif
