#ifndef GAME_CONTROL_80132090_H
#define GAME_CONTROL_80132090_H

#include "game/Object_80039F5C.h"

/* Eight bytes at +56 of Control_80132090, passed to fn_8012F5A0 as one
   block. */
struct Block_8012F5A0 {
    short mUnknown0;
    unsigned char mUnknown2;
    char mUnknown3[1];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    char mUnknown7[1];
};

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
    Block_8012F5A0 mUnknown56;
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
void fn_8012DDCC(Object_80039F5C *p, Control_80132090 *pControl, int a);
void fn_8012F5A0(Object_80039F5C *p, Control_80132090 *pControl, Block_8012F5A0 *pBlock);
void fn_8012F89C(Object_80039F5C *p, Control_80132090 *pControl, int a);
void fn_80130338(Object_80039F5C *p, Control_80132090 *pControl);
}

#endif
