#ifndef GAME_LEVELDATA_H
#define GAME_LEVELDATA_H

#include "game/Object_80039F5C.h"

/* 36-byte placement entry of the level data returned by LevelGetData. */
struct LevelPlacement_t {
    float mUnknown0[6];
    union {
        unsigned short mUnknown24;
        unsigned char mUnknown24Bytes[2];
    };
    int mUnknown28;
    int mUnknown32;
};

/* 60-byte record of the list at +140 of the level data: a point followed by
   four points at +12. */
struct LevelWall_t {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12[4];
};

/* Four points passed to LevelGetQuadBase and LevelGetQuadHeight. LevelGetQuadBase copies mX
   and mY of points whose mZ is below 0.1; LevelGetQuadHeight returns the last mZ
   at or above 0.1. LevelGetWallBase and LevelGetWallHeight do the same over
   LevelWall_t::mUnknown12. */
struct LevelQuad_t {
    Vector_80039F5C mPoint[4];
};

/* 36-byte entry of the list at +28 of the level data; LevelSetSurface stores
   its second argument at +8 of each entry whose +32 equals its first.
   LevelMeshInArea reads its three corners as indices into the list at +20. */
struct LevelArea_t {
    unsigned short mVertex[3];
    char mUnknown6[2];
    int mUnknown8;
    char mUnknown12[20];
    int mUnknown32;
};

/* 28-byte entry of the list at +156 of the level data, returned by
   LevelGetMarker. */
struct LevelMarker_t {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
    char mUnknown24[4];
};

/* 8-byte entry of the list at +20 of the level data: a point in the plane. */
struct LevelVertex_t {
    float mX;
    float mY;
};

/* 32-byte node of the tree at +160 of the level data. An inner node
   (mCount 0) splits on mX (mAxis 0) or mY at mSplit; a leaf lists mCount
   indices into the list at +28. */
struct LevelAreaNode_t {
    int mAxis;
    float mSplit;
    int mHasLeft;
    int mHasRight;
    LevelAreaNode_t *mpLeft;
    LevelAreaNode_t *mpRight;
    unsigned int mCount;
    int *mpIndices;
};

/* The level data whose address LevelGetData returns: a 164-byte header of
   count and list pairs, followed by the lists and the tree in that order.
   LevelMeshRelocate sets each list pointer from the counts, laying the lists out
   consecutively after the header, then relocates the tree. */
struct LevelData_t {
    char mUnknown0[16];
    unsigned int mUnknown16;
    LevelVertex_t *mUnknown20;
    unsigned int mUnknown24;
    LevelArea_t *mUnknown28;
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
    LevelPlacement_t *mUnknown92;
    unsigned int mUnknown96;
    LevelPlacement_t *mUnknown100;
    unsigned int mUnknown104;
    LevelPlacement_t *mUnknown108;
    unsigned int mUnknown112;
    LevelPlacement_t *mUnknown116;
    unsigned int mUnknown120;
    char *mUnknown124;
    unsigned int mUnknown128;
    char *mUnknown132;
    unsigned int mUnknown136;
    LevelWall_t *mUnknown140;
    unsigned int mUnknown144;
    int *mUnknown148;
    unsigned int mUnknown152;
    LevelMarker_t *mUnknown156;
    LevelAreaNode_t *mUnknown160;
};

extern "C" {
LevelData_t *LevelGetData(void);
void LevelGetWallBase(LevelWall_t *pRecord, void *pA, void *pB);
LevelMarker_t *LevelGetMarker(int id);
}

#endif
