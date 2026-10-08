#ifndef GAME_CONTROL_80132090_H
#define GAME_CONTROL_80132090_H

#include "game/Object_80039F5C.h"

struct Control_80132090 {
    int mUnknown0;
    float mValues[8];
    float mUnknown36;
    float mUnknown40;
    int mUnknown44;
    unsigned char mUnknown48;
    signed char mUnknown49;
    char mUnknown50[2];
    unsigned char mUnknown52;
    char mUnknown53[3];
    char mUnknown56[8];
    int mUnknown64;
    int mUnknown68;
    int mUnknown72;
    int mUnknown76;
    unsigned char mUnknown80;
    unsigned char mUnknown81;
    char mUnknown82[6];
};

extern "C" {
int fn_8012FA64(Object_80039F5C *p);
void fn_80130338(Object_80039F5C *p, Control_80132090 *pControl);
}

#endif
