#ifndef GAME_OBJECT_8003DEC4_H
#define GAME_OBJECT_8003DEC4_H

#include "game/FMCAPPORT.h"
#include "game/Object_80146094.h"
#include "game/Pair_8017055C.h"
#include "game/cu_801442FC.h"

struct Item_800476DC;

/* Bone table referenced at +100 of the player object: a bone count at +6
   and three base values per bone from +1040. */
struct Skeleton_80041930 {
    char mUnknown0[6];
    unsigned short mUnknown6;
    char mUnknown8[1032];
    unsigned short mUnknown1040[1][3];
};

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

/* Element of the two-entry array at +116, passed to fn_800ADDFC,
   fn_800ADD7C and fn_800ADEFC. */
struct Element_80041BF8 {
    unsigned char mUnknown0;
    char mUnknown1[3];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    char mUnknown7[1];
    short mUnknown8;
    char mUnknown10[2];
    Pose_80041930 mUnknown12;
    Skeleton_80041930 *mUnknown68;
};

/* Block at +280, passed to fn_800C2788. */
struct Block_800C2788 {
    char mUnknown0[1];
    unsigned char mUnknown1;
    char mUnknown2[254];
    Pose_80041930 mUnknown256;
    Skeleton_80041930 *mUnknown312;
};

/* Block at +596, passed to fn_800C2EC0. */
struct Block_800C2EC0 {
    char mUnknown0[1];
    unsigned char mUnknown1;
    char mUnknown2[158];
    Pose_80041930 mUnknown160;
    Skeleton_80041930 *mUnknown216;
};

/* Weight and two halfwords copied by fn_80042530 from each of the first two
   entries of its blend argument. */
struct Weight_80042530 {
    float mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
};

/* 0x34-byte record copied by fn_8020F2C4; the static at 0x80365D54 in
   src/game/cu_801A14D8.cpp has the same layout. */
struct Record_8020F2C4 {
    int mUnknown0;
    char mUnknown4[24];
    int mUnknown28;
    char mUnknown32[20];
};

/* One of the two 0x44-byte blocks at +0x400, selected by LOD. */
struct Block_8003DEC4 {
    char mUnknown0[16];
    Record_8020F2C4 mUnknown16;
};

struct Slot_801A3284;

/* Joint list of a model: four bytes per joint, the first a joint kind. */
struct Joints_801A209C {
    unsigned char (*mpUnknown0)[4];
    unsigned int mUnknown4;
};

struct Model_801A209C {
    char mUnknown0[12];
    Joints_801A209C *mpUnknown12;
};

/* Parameter block at +0x14 of each part, set through fn_80233CBC. */
struct Params_80233CBC {
    char mUnknown0[8];
    unsigned char mUnknown8[212];
};

/* One of the twelve 0xF0-byte model parts at +0x48C. */
struct Part_8003DEC4 {
    char mUnknown0[12];
    Model_801A209C *mpUnknown12;
    char mUnknown16[4];
    Params_80233CBC mUnknown20;
};

/* Matrix palette set up by fn_80233BB8: one 3x4 float matrix per joint. */
struct Joints_8003DEC4 {
    float (*mpUnknown0)[12];
    int mUnknown4;
    int mUnknown8;
};

/* 0x28-byte level-of-detail record at +0x1078, set up by fn_802341C4. */
struct Lod_802341C4 {
    unsigned int mUnknown0;
    char mUnknown4[8];
    float mUnknown12;
    float mUnknown16;
    unsigned int mUnknown20;
    int mUnknown24;
    void *mpUnknown28;
    float (*mpUnknown32)[4][4];
    int mUnknown36;
};

/* Clipped shadow polygon: up to seven points and texture coordinates. */
struct Clip_8003BFCC {
    float mPoints[7][3];
    Pair_8017055C mPairs[7];
    unsigned char mCount;
    unsigned char mUnknown141[3];
};

/* 0x2A4-byte shadow projection at +0x10A0: a colour, a quad, and up to
   mUnknown672 clipped polygons, drawn when mUnknown673 is set. */
struct Projection_8003BA10 {
    float mColor[4];
    float mPoints[4][3];
    Pair_8017055C mPairs[4];
    Clip_8003BFCC mRecords[4];
    unsigned char mUnknown672;
    unsigned char mUnknown673;
};

/* Object returned by fn_8003DEC4 (0x19F0 bytes, the size fn_8004A140 passes
   to fn_801DCF0C). */
struct Object_8003DEC4 {
    char mUnknown0[4];
    float mUnknown4[3];
    char mUnknown16[4];
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
    int mUnknown32;
    int mUnknown36;
    char mUnknown40[4];
    Pose_80041930 mUnknown44;
    Skeleton_80041930 *mUnknown100;
    Skeleton_80041930 *mUnknown104;
    Skeleton_80041930 *mUnknown108;
    float (*mUnknown112)[4][4];
    Element_80041BF8 mUnknown116[2];
    unsigned char mUnknown260;
    char mUnknown261[3];
    Weight_80042530 mUnknown264[2];
    Block_800C2788 mUnknown280;
    Block_800C2EC0 mUnknown596;
    int mUnknown816;
    float *mUnknown820;
    char mUnknown824[4];
    short mUnknown828;
    short mUnknown830;
    char mUnknown832[76];
    float mUnknown908[4][4];
    int mUnknown972;
    unsigned int mUnknown976;
    char mUnknown980[4];
    int mUnknown984;
    Item_800476DC *mUnknown988;
    union {
        char mBytes992[3192];
        struct {
        int mUnknown992;
        int mUnknown996;
        int mUnknown1000;
        int mUnknown1004;
        int mUnknown1008;
        int mUnknown1012;
        int mUnknown1016;
        int mUnknown1020;
        Block_8003DEC4 mUnknown1024[2];
        Slot_801A3284 *mUnknown1160;
        Part_8003DEC4 mUnknown1164[12];
        char mUnknown4044[16];
        Desc_802347EC *mUnknown4060;
        Joints_8003DEC4 mUnknown4064[6];
        Joints_8003DEC4 mUnknown4136[2];
        char mUnknown4160[24];
        };
    };
    char mUnknown4184[32];
    Lod_802341C4 mUnknown4216;
    Projection_8003BA10 mUnknown4256;
    char mUnknown4932[24];
    int mUnknown4956;
    Tracker_801442FC mUnknown4960;
    unsigned char mUnknown4968;
    unsigned char mUnknown4969;
    unsigned char mUnknown4970;
    unsigned char mUnknown4971;
    unsigned char mUnknown4972;
    char mUnknown4973[3];
    FMCAPPORTValues mUnknown4976;
    Object_80146094 mUnknown5188;
};

extern "C" {
Object_8003DEC4 *fn_8003DEC4(int index);
/* Callback registered by fn_8004A140 through fn_801DD0C8; its second
   argument is not read. */
int fn_8004A1A8(Object_8003DEC4 *pObject, int unused);
}

#endif
