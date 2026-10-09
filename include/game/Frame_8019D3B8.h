#ifndef GAME_FRAME_8019D3B8_H
#define GAME_FRAME_8019D3B8_H

#include "game/Record_8019D8AC.h"

/* Frame header decoded by fn_8019D3B8 from an encoded sample block. */
struct Frame_8019D3B8 {
    unsigned char count;
    unsigned char flags;
    short word2;
    short word4;
    short word6;
    short word8;
    short vectorA[3];
    short vector10[3];
};

struct State_8019D994 {
    unsigned char unknown0[8];
    float vector8[3];
    float vector14[3];
    int word20;
    int vector24[3];
    short *samples;
};

struct Input_8019D994 {
    unsigned char unknown0[8];
    unsigned char flags;
    unsigned char unknown9[3];
    int vectorC[3];
    float planar18[2];
    unsigned char unknown20[8];
    void *encoded;
};

extern "C" {
void fn_8019D2EC(State_8019D994 *state, Input_8019D994 *input, int mirrored);
short *fn_8019D3B8(Frame_8019D3B8 *header, void *encoded);
int fn_8019D4EC(unsigned char *encoded);
void fn_8019D514(short *destination, short *source, Record_8019D8AC *context, int mirrored);
}

#endif
