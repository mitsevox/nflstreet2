#ifndef GAME_POSE_80041930_H
#define GAME_POSE_80041930_H

/* Pose block copied, serialized and blended by src/game/cu_80041930.cpp:
   three shorts per bone in mUnknown48 and, for the main pose, one 64-byte
   matrix per bone in mUnknown52. */
struct Pose_80041930 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    short mUnknown6;
    float mUnknown8[3];
    float mUnknown20[3];
    int mUnknown32;
    int mUnknown36[3];
    short *mUnknown48;
    float (*mUnknown52)[4][4];
};

#endif
