#ifndef GAME_STATE_80167094_H
#define GAME_STATE_80167094_H
#include <dolphin/gx/GXStruct.h>
struct Point_80167094 { float mX, mY; };
/* State passed from the play-data producers to the textured drawing callbacks. */
struct State_80167094 {
    unsigned char mUnknown0[0x940];
    int mUnknown940[12];
    Point_80167094 mUnknown970[11][12][4];
    int mUnknown19F0[11][12];
    unsigned char mUnknown1C00[0x210];
    int mUnknown1E10[11][12];
    GXColor mUnknown2020[11];
    GXColor mUnknown204C[11];
    unsigned char mUnknown2078[11];
    unsigned char mUnknown2083;
    float mUnknown2084[11][4];
    unsigned int mUnknown2134[11];
    int mUnknown2160;
    int mUnknown2164[5];
    float mUnknown2178[5][4];
    signed char mUnknown21C8[5];
    unsigned char mUnknown21CD[3];
};
#endif
