#ifndef GAME_LEVEL_80054130_H
#define GAME_LEVEL_80054130_H

#include "game/Object_80039F5C.h"

/* 36-byte placement entry of the level data returned by fn_80054130. */
struct Entry_80054130 {
    float mUnknown0[6];
    unsigned short mUnknown24;
    int mUnknown28;
    int mUnknown32;
};

/* 60-byte record of the list at +140 of the level data: a point followed by
   four points at +12. */
struct Record_80054130 {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12[4];
};

/* Four points passed to fn_800542DC and fn_8005434C. fn_800542DC copies mX
   and mY of points whose mZ is below 0.1; fn_8005434C returns the last mZ
   at or above 0.1. fn_800541AC and fn_8005429C do the same over
   Record_80054130::mUnknown12. */
struct Points_800542DC {
    Vector_80039F5C mPoint[4];
};

/* 36-byte entry of the list at +28 of the level data; fn_8005415C stores
   its second argument at +8 of each entry whose +32 equals its first.
   fn_80053E78 reads its three corners as indices into the list at +20. */
struct Entry_8005415C {
    unsigned short mVertex[3];
    char mUnknown6[2];
    int mUnknown8;
    char mUnknown12[20];
    int mUnknown32;
};

/* 28-byte entry of the list at +156 of the level data, returned by
   fn_8005438C. */
struct Object_8005438C {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
    char mUnknown24[4];
};

/* 8-byte entry of the list at +20 of the level data: a point in the plane. */
struct Vertex_80053C70 {
    float mX;
    float mY;
};

/* 32-byte node of the tree at +160 of the level data. An inner node
   (mCount 0) splits on mX (mAxis 0) or mY at mSplit; a leaf lists mCount
   indices into the list at +28. */
struct Node_80053BCC {
    int mAxis;
    float mSplit;
    int mHasLeft;
    int mHasRight;
    Node_80053BCC *mpLeft;
    Node_80053BCC *mpRight;
    unsigned int mCount;
    int *mpIndices;
};

/* The level data whose address fn_80054130 returns: a 164-byte header of
   count and list pairs, followed by the lists and the tree in that order.
   fn_80053C70 sets each list pointer from the counts, laying the lists out
   consecutively after the header, then relocates the tree. */
struct Level_80054130 {
    char mUnknown0[16];
    unsigned int mUnknown16;
    Vertex_80053C70 *mUnknown20;
    unsigned int mUnknown24;
    Entry_8005415C *mUnknown28;
    unsigned int mUnknown32;
    char *mUnknown36;
    unsigned int mUnknown40;
    char *mUnknown44;
    unsigned int mUnknown48;
    char *mUnknown52;
    unsigned int mUnknown56;
    char *mUnknown60;
    unsigned int mUnknown64;
    char *mUnknown68;
    unsigned int mUnknown72;
    char *mUnknown76;
    unsigned int mUnknown80;
    char *mUnknown84;
    unsigned int mUnknown88;
    Entry_80054130 *mUnknown92;
    unsigned int mUnknown96;
    Entry_80054130 *mUnknown100;
    unsigned int mUnknown104;
    Entry_80054130 *mUnknown108;
    unsigned int mUnknown112;
    Entry_80054130 *mUnknown116;
    unsigned int mUnknown120;
    char *mUnknown124;
    unsigned int mUnknown128;
    char *mUnknown132;
    unsigned int mUnknown136;
    Record_80054130 *mUnknown140;
    unsigned int mUnknown144;
    int *mUnknown148;
    unsigned int mUnknown152;
    Object_8005438C *mUnknown156;
    Node_80053BCC *mUnknown160;
};

extern "C" {
Level_80054130 *fn_80054130(void);
void fn_800541AC(Record_80054130 *pRecord, void *pA, void *pB);
Object_8005438C *fn_8005438C(int id);
}

#endif
