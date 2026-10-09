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
    float mUnknown20;
    float mUnknown24;
};

struct Camera_8013F738 {
    CameraHeader_8013F628 mHeader;
    void *mUnknown28;
    float mUnknown2C;
    float mUnknown30;
    float mUnknown34;
    int mUnknown38;
    char mPad3C[0x20];
    float mUnknown5C;
    float mUnknown60;
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
    /* Base camera kind: 0 and 4 use the type-0 layout below, 1 the type-1
       layout. */
    unsigned int mUnknown98;
    int mUnknown9C;
    int mUnknownA0;
    int mUnknownA4;
    int mUnknownA8;
    int mUnknownAC;
    int mUnknownB0;
    int mUnknownB4;
    Vector_80039F5C mUnknownB8;
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
    float mUnknownF4;
    char mPadF8[0x30];
    /* Script records of the replay camera (type 3). */
    RecordList_8002E7C0 mUnknown128;
    char mPad6B0[0x8AC];
    int mUnknownF5C;
};

/* The leading 0x8C bytes as fn_8013C120 sets them up for kind 0 and 4
   (type descriptor 0x802F4890, 0x8C bytes). */
struct CameraType0_802F4890 {
    char mPad00[0x5C];
    float mUnknown5C[3];
    float mUnknown68[3];
    int mUnknown74[3];
    int mUnknown80[3];
};

/* The leading part as fn_8013C7C4 resets it for kind 1 (type descriptor
   0x802F4884, 0x94 bytes). */
struct CameraType1_802F4884 {
    char mPad00[0x4C];
    Vector_80039F5C mUnknown4C;
    float mUnknown58;
    int mUnknown5C;
    int mUnknown60;
};

/* Argument of fn_801C3610 when it creates a camera; fn_8013C340 clears it. */
struct Desc_8013C340 {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
};

#endif
