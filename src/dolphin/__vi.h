#ifndef DOLPHIN_VI_INTERNAL_H
#define DOLPHIN_VI_INTERNAL_H

#include <dolphin/vi.h>

typedef struct VITimingInfo
{
    u8 equ;
    u16 acv;
    u16 prbOdd;
    u16 prbEven;
    u16 psbOdd;
    u16 psbEven;
    u8 bs1;
    u8 bs2;
    u8 bs3;
    u8 bs4;
    u16 be1;
    u16 be2;
    u16 be3;
    u16 be4;
    u16 numHalfLines;
    u16 hlw;
    u8 hsy;
    u8 hcs;
    u8 hce;
    u8 hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITimingInfo;
typedef struct VIPositionInfo
{
    u16 dispPosX;
    u16 dispPosY;
    u16 dispSizeX;
    u16 dispSizeY;
    u16 adjDispPosX;
    u16 adjDispPosY;
    u16 adjDispSizeY;
    u16 adjPanPosY;
    u16 adjPanSizeY;
    u16 fbSizeX;
    u16 fbSizeY;
    u16 panPosX;
    u16 panPosY;
    u16 panSizeX;
    u16 panSizeY;
    VIXFBMode xfbMode;
    u32 nonInter;
    u32 tv;
    u8 wordPerLine;
    u8 std;
    u8 wpl;
    u32 bufAddr;
    u32 tfbb;
    u32 bfbb;
    u8 xof;
    BOOL isBlack;
    BOOL is3D;
    u32 rbufAddr;
    u32 rtfbb;
    u32 rbfbb;
    VITimingInfo* timing;
} VIPositionInfo;

void __VIInit(VITVMode mode);
void __VIDisplayPositionToXY(u32 hcount, u32 vcount, s16* x, s16* y);
void __VIGetCurrentPosition(s16* x, s16* y);

#endif
