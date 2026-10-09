#ifndef GAME_OBJECT_8003DEC4_H
#define GAME_OBJECT_8003DEC4_H

#include "game/FMCAPPORT.h"
#include "game/Object_80146094.h"

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
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
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
    char mUnknown976[12];
    Item_800476DC *mUnknown988;
    /* Indexed as bytes from +992; the words at +1016 and +1020 are also
       accessed by name. */
    union {
        char mUnknown992[3192];
        struct {
            char mUnknown992Head[24];
            int mUnknown1016;
            int mUnknown1020;
        };
    };
    char mUnknown4184[772];
    int mUnknown4956;
    char mUnknown4960[8];
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
