#ifndef GAME_CAMERA_8013F738_H
#define GAME_CAMERA_8013F738_H

#include "game/RecordList_8002E7C0.h"

/* Leading block of a camera that a saved state restores. */
struct CameraHeader_8013F628 {
    unsigned char mUnknown00;
    unsigned char mType;
    char mPad02[2];
    float mUnknown04[3];
    char mPad10[4];
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    char mPad20[4];
    float mUnknown24;
};

struct Camera_8013F738 {
    CameraHeader_8013F628 mHeader;
    char mPad28[8];
    float mUnknown30;
    char mPad34[4];
    int mUnknown38;
    char mPad3C[0x28];
    float mUnknown64;
    float mUnknown68;
    float mUnknown6C;
    float mUnknown70;
    float mUnknown74;
    float mUnknown78;
    float mUnknown7C;
    float mUnknown80;
    int mUnknown84;
    int mUnknown88;
    int mUnknown8C;
    int mUnknown90;
    int mUnknown94;
    char mPad98[4];
    int mUnknown9C;
    int mUnknownA0;
    int mUnknownA4;
    int mUnknownA8;
    char mPadAC[4];
    int mUnknownB0;
    int mUnknownB4;
    char mPadB8[0xC];
    float mUnknownC4;
    float mUnknownC8;
    float mUnknownCC;
    int mUnknownD0;
    int mUnknownD4;
    int mUnknownD8;
    void (*mUnknownDC)(Camera_8013F738 *, int);
    float mUnknownE0;
    unsigned char mUnknownE4;
    unsigned char mUnknownE5;
    char mPadE6[2];
    float mUnknownE8;
    float mUnknownEC;
    float mUnknownF0;
    char mPadF4[4];
    char mPadF8[0x30];
    /* Script records of the replay camera (type 3). */
    RecordList_8002E7C0 mUnknown128;
    char mPad6B0[0x8AC];
    int mUnknownF5C;
};

#endif
