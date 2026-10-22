#ifndef GAME_CAMERAHEADER_8013F628_H
#define GAME_CAMERAHEADER_8013F628_H

/* Leading block of a camera that a saved state restores. */
typedef struct CameraHeader_8013F628 {
    unsigned char mUnknown00;
    unsigned char mType;
    char mPad02[2];
    float mUnknown04[3];
    char mPad10[4];
    int mUnknown14[3];
    float mUnknown20;
    float mUnknown24;
} CameraHeader_8013F628;

#endif
