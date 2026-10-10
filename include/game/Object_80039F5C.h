#ifndef GAME_OBJECT_80039F5C_H
#define GAME_OBJECT_80039F5C_H

#include "game/Object_800D81C8.h"

/* The player object returned by fn_80039F5C, with the blocks it contains or
   points to. */

struct Vector_80039F5C {
    float mX;
    float mY;
    float mZ;
};

/* Rotation built by fn_801EBEF8 from three angles and reset by fn_801EB488. */
struct Quat_801EB488 {
    float mX;
    float mY;
    float mZ;
    float mW;
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
    char mUnknown104[4];
    Quat_801EB488 mUnknown108;
    Vector_80039F5C mUnknown124;
    Quat_801EB488 mUnknown136;
    unsigned char mUnknown152;
    char mUnknown153[507];
    int mUnknown660;
};

/* Motion block at +424, passed to fn_800B26B0, fn_800B26D0, fn_800B26E0,
   fn_800B2A14 and fn_800B2D9C. Angles are 24-bit words. */
struct Object_800B26B0 {
    Vector_80039F5C mPos;
    Vector_80039F5C mUnknown12;
    int mFacing;
    float mUnknown28;
    int mUnknown32;
    float mUnknown36;
    float mUnknown40;
    float mUnknown44;
    float mUnknown48;
    float mUnknown52;
    int mUnknown56;
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

/* 56-byte block at +560 (0x800AEB5C clears 0x38 bytes); fn_80143D3C resets
   it and fn_80143464 accumulates into it. */
struct Block_80170374 {
    Flags_80170374 mFlags;
    Vector_80039F5C mUnknown4;
    Vector_80039F5C mUnknown16;
    float mUnknown28;
    float mUnknown32;
    float mUnknown36;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
};

/* The 68 bytes at +560 as fn_80143668 addresses them: the block followed by
   the contact point it copies to +56. */
struct Contact_80143668 {
    Block_80170374 mBlock;
    Vector_80039F5C mUnknown56;
};

/* Block at +1160. */
struct Block_801718E8 {
    char mUnknown0[12];
    char mUnknown12[40];
    unsigned char mUnknown52;
};

/* Three bytes at +1008, compared field by field by fn_80110630. */
struct Key_80110630 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

/* Block at +1240, reset by fn_800CE674 and fn_800CE684. Only the accessed
   prefix is declared; the size is unknown. */
struct Object_800CE674 {
    short mUnknown0;
    char mUnknown2;
    char mUnknown3;
};

/* 124-byte entry of the array that +800 points to. */
typedef Record_800D81C8 Entry_800EAC9C;

/* 12-byte block at +1228; fn_800D0B90 returns its first word. */
struct Block_800D0B90 {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    char mUnknown6[2];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
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

/* Record that +780 points to. Only the word +8 is accessed. */
struct Record_800C4E18 {
    char mUnknown0[8];
    int mUnknown8;
};

/* Object that +796 points to. */
struct Object_8016D9B8 {
    char mUnknown0[2];
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    char mUnknown6[2];
    int mUnknown8;
};

/* Object that +3092 points to; its layout is declared where it is read. */
struct Object_800EA284;
/* Block at player +1072 (Block_8011E240 +40), passed to fn_8011DBC8. +52 is
   a halfword counter (fn_8011E884, fn_8011E88C, fn_8011DA40). Declared up to
   +54; the byte there is player +1126. */
struct Block_8011DBC8 {
    char mUnknown0[52];
    short mUnknown52;
};

/* View of the 108 bytes at player +1032 as one block: fn_8011DF90 clears
   them with one 108-byte fn_801C1F94 call, and fn_8011E194, fn_8011E1A8,
   fn_8011E1BC, fn_8011E240, fn_8011E33C and fn_8011E3A4 address them
   through a register holding player +1032. The per-field view is the
   mUnknown1032-mUnknown1139 members; this view declares the bytes the
   block-relative code accesses and leaves the others opaque. +102 is the
   signed view of player +1134 (lha at 0x8011DB2C, extsh at 0x8011DB54). */
struct Block_8011E240 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    char mUnknown16[78];
    unsigned char mUnknown94;
    char mUnknown95[5];
    unsigned char mUnknown100;
    char mUnknown101[1];
    short mUnknown102;
    unsigned char mUnknown104;
    unsigned char mUnknown105;
    char mUnknown106[2];
};

struct Object_80039F5C {
    /* Read both as a word and byte by byte (+1 index, +2 team). */
    union {
        int mId;
        unsigned char mIdBytes[4];
    };
    Block_80170E64 *mpUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9[3];
    unsigned int mFlags;
    int mUnknown16;
    char mUnknown20[88];
    int mUnknown108;
    char mUnknown112[88];
    int mUnknown200;
    char mUnknown204[132];
    int mUnknown336;
    short mUnknown340;
    unsigned char mUnknown342;
    char mUnknown343[1];
    unsigned char mUnknown344;
    char mUnknown345[9];
    unsigned char mUnknown354;
    char mUnknown355[5];
    unsigned char mUnknown360;
    char mUnknown361[27];
    unsigned int mUnknown388;
    unsigned char mUnknown392;
    char mUnknown393[9];
    unsigned char mUnknown402;
    char mUnknown403[21];
    Object_800B26B0 mMotion;
    float mUnknown488;
    float mUnknown492;
    char mUnknown496[12];
    float mUnknown508;
    Object_8016D8B0 mUnknown512;
    Object_8016D8B0 mUnknown528;
    unsigned char mUnknown544;
    unsigned char mUnknown545;
    char mUnknown546[2];
    int mUnknown548;
    char mUnknown552[8];
    /* The 68 bytes at +560, as the 56-byte block and as the block with the
       contact point that follows it. */
    union {
        Block_80170374 mUnknown560;
        Contact_80143668 mContact560;
    };
    int mUnknown628[2];
    char mUnknown636[132];
    float mUnknown768;
    float mUnknown772;
    unsigned char mUnknown776;
    unsigned char mUnknown777;
    union {
        short mUnknown778;
        unsigned short mUnknown778Unsigned;
    };
    Record_800C4E18 *mpUnknown780;
    State_80039F5C *mpState;
    char mUnknown788[4];
    void *mpUnknown792;
    Object_8016D9B8 *mpUnknown796;
    Record_800D81C8 *mpUnknown800;
    char mUnknown804[204];
    union {
        int mUnknown1008Word;
        struct {
            Key_80110630 mUnknown1008;
            unsigned char mUnknown1011;
        };
    };
    char mUnknown1012[4];
    float mUnknown1016[2];
    float mUnknown1024[2];
    /* The 108 bytes at +1032, read field by field and as Block_8011E240. */
    union {
        struct {
            int mUnknown1032;
            int mUnknown1036;
            int mUnknown1040;
            int mUnknown1044;
            int mUnknown1048;
            int mUnknown1052;
            char mUnknown1056[8];
            short mUnknown1064;
            char mUnknown1066[6];
            Block_8011DBC8 mUnknown1072;
            unsigned char mUnknown1126;
            char mUnknown1127[7];
            unsigned short mUnknown1134;
            unsigned char mUnknown1136;
            unsigned char mUnknown1137;
            unsigned char mUnknown1138;
            unsigned char mUnknown1139;
        };
        Block_8011E240 mBlock1032;
    };
    char mUnknown1140[16];
    unsigned char mUnknown1156;
    char mUnknown1157[3];
    Block_801718E8 mUnknown1160;
    unsigned char mUnknown1213;
    unsigned char mUnknown1214;
    char mUnknown1215[3];
    unsigned char mUnknown1218;
    unsigned char mUnknown1219;
    unsigned char mUnknown1220;
    unsigned char mUnknown1221;
    unsigned char mUnknown1222;
    char mUnknown1223[1];
    int mUnknown1224;
    Block_800D0B90 mUnknown1228;
    Object_800CE674 mUnknown1240;
    char mUnknown1244[1656];
    float mUnknown2900;
    char mUnknown2904[4];
    unsigned short mUnknown2908;
    char mUnknown2910[2];
    unsigned char mUnknown2912;
    unsigned char mUnknown2913;
    unsigned char mUnknown2914;
    char mUnknown2915[1];
    unsigned char mUnknown2916;
    char mUnknown2917[3];
    unsigned char mUnknown2920;
    unsigned char mUnknown2921;
    char mUnknown2922[1];
    unsigned char mUnknown2923[4];
    char mUnknown2927[73];
    short mRatings[10];
    char mUnknown3020[20];
    int mUnknown3040;
    char mUnknown3044[4];
    /* Message queue that mpState points to; passed to fn_800F03D8 and
       fn_800F053C. Only its head is declared. */
    State_80039F5C mUnknown3048;
    char mUnknown3055[33];
    unsigned char mUnknown3088;
    char mUnknown3089[1];
    unsigned short mUnknown3090;
    Object_800EA284 *mpUnknown3092;
};

extern "C" {
Object_80039F5C *fn_80039F5C(int team, unsigned short index);
Object_80039F5C *fn_8009BCE8(int *pRef);
void fn_8009BF5C(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, void *pA);
}

#endif
