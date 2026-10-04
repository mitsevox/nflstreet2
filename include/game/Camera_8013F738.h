#ifndef GAME_CAMERA_8013F738_H
#define GAME_CAMERA_8013F738_H

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
    char mPad28[0x6C];
    int mUnknown94;
    char mPad98[0x10];
    int mUnknownA8;
    char mPadAC[4];
    int mUnknownB0;
    int mUnknownB4;
};

#endif
