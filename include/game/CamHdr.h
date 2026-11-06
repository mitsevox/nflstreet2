#ifndef GAME_CAM_HDR_H
#define GAME_CAM_HDR_H

/* Leading block of a camera that a saved state restores. */
typedef struct CamHdr_t {
    unsigned char mUnknown00;
    unsigned char mType;
    char mPad02[2];
    float mUnknown04[3];
    char mPad10[4];
    int mUnknown14[3];
    float mUnknown20;
    float mUnknown24;
} CamHdr_t;

#endif
