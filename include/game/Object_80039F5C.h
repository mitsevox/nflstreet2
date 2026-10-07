#ifndef GAME_OBJECT_80039F5C_H
#define GAME_OBJECT_80039F5C_H

/* The player object returned by fn_80039F5C, with the blocks it contains or
   points to. */

struct Vector_80039F5C {
    float mX;
    float mY;
    float mZ;
};

/* Block at +4 of the player object; the entries of src/game/cu_80136B1C.cpp
   hold one at +0. */
struct Block_80170E64 {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    char mUnknown16[4];
    unsigned int mUnknown20;
    char mUnknown24[76];
    void *mpUnknown100;
    char mUnknown104[556];
    int mUnknown660;
};

/* Motion block at +424, passed to fn_800B26B0, fn_800B26D0, fn_800B26E0,
   fn_800B2A14 and fn_800B2D9C. Angles are 24-bit words. */
struct Object_800B26B0 {
    Vector_80039F5C mPos;
    char mUnknown12[12];
    int mFacing;
    float mUnknown28;
    int mUnknown32;
    float mUnknown36;
    char mUnknown40[12];
    float mUnknown52;
    char mUnknown56[4];
    float mUnknown60;
};

/* 16-byte record cleared by fn_8016D8B0; the player object holds two of them
   at +512 and +528. */
struct Object_8016D8B0 {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned short mUnknown12;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
};

/* The first word is tested both as a whole and byte by byte. */
union Flags_80170374 {
    unsigned int mAll;
    unsigned char mBytes[4];
};

/* 56-byte block at +560. */
struct Block_80170374 {
    Flags_80170374 mFlags;
    char mUnknown4[24];
    float mUnknown28;
    char mUnknown32[16];
    int mUnknown48;
    char mUnknown52[2];
    unsigned char mUnknown54;
    char mUnknown55[1];
};

/* Block at +1160. */
struct Block_801718E8 {
    char mUnknown0[52];
    unsigned char mUnknown52;
};

/* Four-byte record at +1240, reset by fn_800CE674 and fn_800CE684. */
struct Record_800CE674 {
    short mUnknown0;
    char mUnknown2;
    char mUnknown3;
};

/* Record that +784 points to. */
struct State_80039F5C {
    unsigned char mId;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3[1];
    unsigned char mUnknown4;
    char mUnknown5[1];
    unsigned char mUnknown6;
};

/* Object that +796 points to. */
struct Object_8016D9B8 {
    char mUnknown0[8];
    int mUnknown8;
};

struct Object_80039F5C {
    /* Read both as a word and byte by byte (+1 index, +2 team). */
    union {
        int mId;
        unsigned char mIdBytes[4];
    };
    Block_80170E64 *mpUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    unsigned int mFlags;
    int mUnknown16;
    char mUnknown20[316];
    int mUnknown336;
    char mUnknown340[20];
    unsigned char mUnknown360;
    char mUnknown361[31];
    unsigned char mUnknown392;
    char mUnknown393[9];
    unsigned char mUnknown402;
    char mUnknown403[21];
    Object_800B26B0 mMotion;
    char mUnknown488[24];
    Object_8016D8B0 mUnknown512;
    Object_8016D8B0 mUnknown528;
    unsigned char mUnknown544;
    unsigned char mUnknown545;
    char mUnknown546[2];
    int mUnknown548;
    char mUnknown552[8];
    Block_80170374 mUnknown560;
    char mUnknown616[152];
    float mUnknown768;
    char mUnknown772[4];
    unsigned char mUnknown776;
    char mUnknown777[7];
    State_80039F5C *mpState;
    char mUnknown788[4];
    void *mpUnknown792;
    Object_8016D9B8 *mpUnknown796;
    char mUnknown800[232];
    int mUnknown1032;
    int mUnknown1036;
    int mUnknown1040;
    int mUnknown1044;
    char mUnknown1048[16];
    short mUnknown1064;
    char mUnknown1066[60];
    unsigned char mUnknown1126;
    char mUnknown1127[7];
    unsigned short mUnknown1134;
    unsigned char mUnknown1136;
    unsigned char mUnknown1137;
    char mUnknown1138[22];
    Block_801718E8 mUnknown1160;
    unsigned char mUnknown1213;
    unsigned char mUnknown1214;
    char mUnknown1215[3];
    unsigned char mUnknown1218;
    unsigned char mUnknown1219;
    char mUnknown1220[20];
    Record_800CE674 mUnknown1240;
    char mUnknown1244[1656];
    float mUnknown2900;
    char mUnknown2904[4];
    unsigned short mUnknown2908;
    char mUnknown2910[4];
    unsigned char mUnknown2914;
    char mUnknown2915[1];
    unsigned char mUnknown2916;
    char mUnknown2917[83];
    short mRatings[10];
    char mUnknown3020[28];
    /* Message queue that mpState points to; passed to fn_800F03D8 and
       fn_800F053C. Only its head is declared. */
    State_80039F5C mUnknown3048;
};

extern "C" {
Object_80039F5C *fn_80039F5C(int team, unsigned short index);
Object_80039F5C *fn_8009BCE8(int *pRef);
void fn_8009BF5C(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, void *pA);
}

#endif
