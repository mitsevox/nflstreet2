#ifndef GAME_ANIMPOSE_H
#define GAME_ANIMPOSE_H

/* Pose block copied, serialized and blended by src/game/PlyrPose.cpp:
   three shorts per bone in mUnknown48 and, for the main pose, one 64-byte
   matrix per bone in mUnknown52. */
struct AnimPose_t {
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
