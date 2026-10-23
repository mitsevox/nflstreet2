#ifndef GAME_OBJECT_80039F5C_H
#define GAME_OBJECT_80039F5C_H

#include "game/Object_800D81C8.h"
#include "game/Message_800F01CC.h"
#include "game/Pose_80041930.h"

struct Area_80054138;

struct Block_800CC180 {
    unsigned short mUnknown0;
    char mUnknown2[6];
    float mUnknown8;
    float mUnknown12;
    int mUnknown16;
    char mUnknown20[4];
};

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

struct Object_80041904;

struct Rig_800C8860;

/* Block at +44 of Block_80170E64; fn_800C8860 turns the joints at +48. */
struct Model_800C8860 {
    char mUnknown0[48];
    Rig_800C8860 *mpRig;
    char mUnknown52[4];
};

/* Block at +4 of the player object; the entries of src/game/cu_80136B1C.cpp
   hold one at +0. */
struct Block_80170E64 {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    char mUnknown16[4];
    unsigned int mUnknown20;
    /* +24 is the scale fn_8009BD88 sets alongside player +768. */
    union {
        char mUnknown24[20];
        struct {
            float mScale;
            char mUnknown28[8];
            int mUnknown36;
            char mUnknown40[4];
        };
    };
    union {
        Pose_80041930 mUnknown44;
        Model_800C8860 mModel44;
    };
    void *mpUnknown100;
    char mUnknown104[4];
    Quat_801EB488 mUnknown108;
    Vector_80039F5C mUnknown124;
    Quat_801EB488 mUnknown136;
    unsigned char mUnknown152;
    char mUnknown153[507];
    Area_80054138 *mUnknown660;
    char mUnknown664[12];
    Object_80041904 *mpUnknown676;
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

/* The motion functions also reach the word 72 bytes into the block, past
   the end of Object_800B26B0 (the player object lays it out in mUnknown496). */
struct MotionTail_800B26B0 {
    Object_800B26B0 mMotion;
    float mUnknown64;
    float mUnknown68;
    float mUnknown72;
    int mUnknown76;
    float mUnknown80;
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

struct Snapshot_801718E8 {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknown12[20];
};

/* Block at +1160. */
struct Block_801718E8 {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    union {
        char mUnknown12[32];
        struct {
            int mUnknown12Word;
            float mUnknown16;
            float mUnknown20;
            float mUnknown24;
            short mUnknown28;
            unsigned char mUnknown30;
            char mUnknown31[1];
            float mUnknown32;
            float mUnknown36;
            int mUnknown40;
        };
        Snapshot_801718E8 mSnapshot12;
    };
    int mUnknown44;
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    char mUnknown55[1];
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

/* One entry of the player's message queue (ten 4-byte entries laid out like
   Message_800F01CC). mpState (+784) points to the first entry, which holds
   the current state; bytes are named by offset. */
struct State_80039F5C {
    unsigned char mId;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3[1];
};

/* Object that +3092 points to; its layout is declared where it is read. */
struct Object_800EA284;
/* Block at player +1072 (Block_8011E240 +40), passed to fn_8011DBC8. +52 is
   a halfword counter (fn_8011E884, fn_8011E88C, fn_8011DA40); +40, +44 and +48
   are reset to 1.0f by fn_8011DBC8. The byte at +54 is player +1126. */
struct Block_8011DBC8 {
    char mUnknown0[40];
    float mUnknown40;
    float mUnknown44;
    float mUnknown48;
    short mUnknown52;
    unsigned char mUnknown54;
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
    char mUnknown16[4];
    int mUnknown20;
    char mUnknown24[8];
    unsigned short mUnknown32;
    char mUnknown34[10];
    float mUnknown44;
    char mUnknown48[12];
    int mUnknown60;
    char mUnknown64[30];
    unsigned char mUnknown94;
    char mUnknown95[5];
    unsigned char mUnknown100;
    char mUnknown101[1];
    short mUnknown102;
    unsigned char mUnknown104;
    unsigned char mUnknown105;
    char mUnknown106[2];
};

/* Head/body turn at +300, eased towards mTarget by fn_800C8AF0 (24-bit
   angles); mRate indexes the easing tables. */
struct Turn_800C8AF0 {
    int mAngle[2];
    int mSpeed[2];
    int mTarget[2];
    int mRate[2];
    unsigned char mSettled;
};

/* Block at player +1140: the reference of the player being faced, the
   facing mode at +14, a flag at +16 and a value at +18. */
struct Target_800A3E84 {
    int mRef;
    char mUnknown4[10];
    short mMode;
    unsigned char mUnknown10;
    char mUnknown11[1];
    short mValue;
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
    /* Three 92-byte blocks at +16, +108 and +200 (filled from the +4
       object's pose by fn_8003AE24); each holds that pose's address at
       its +40. */
    int mUnknown16;
    char mUnknown20[36];
    Pose_80041930 *mpUnknown56;
    char mUnknown60[48];
    int mUnknown108;
    char mUnknown112[36];
    Pose_80041930 *mpUnknown148;
    char mUnknown152[48];
    int mUnknown200;
    char mUnknown204[36];
    Pose_80041930 *mpUnknown240;
    char mUnknown244[48];
    int mUnknown292;
    int mUnknown296;
    union {
        char mUnknown300[36];
        Turn_800C8AF0 mTurn;
    };
    union {
        struct {
            int mUnknown336;
            short mUnknown340;
            unsigned char mUnknown342;
            char mUnknown343[1];
            unsigned char mUnknown344;
            char mUnknown345[9];
            unsigned char mUnknown354;
            char mUnknown355[5];
        };
        Block_800CC180 mUnknown336Block;
        /* Per-state scratch: state 26 reads +344 as a word (fn_800C5BF0);
           state 58 keeps a player reference at +352 (fn_800C7D44). */
        struct {
            char mUnknown336Words[8];
            int mUnknown344Word;
            char mUnknown348[4];
            Object_80039F5C *mpUnknown352;
        };
    };
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
    char mUnknown636[4];
    float mUnknown640[4][4];
    float mUnknown704[4][4];
    float mUnknown768;
    float mUnknown772;
    unsigned char mUnknown776;
    unsigned char mUnknown777;
    union {
        short mUnknown778;
        unsigned short mUnknown778Unsigned;
    };
    Area_80054138 *mpUnknown780;
    State_80039F5C *mpState;
    char mUnknown788[4];
    void *mpUnknown792;
    Object_801BA03C *mpUnknown796;
    Record_800D81C8 *mpUnknown800;
    void *mpUnknown804;
    void *mpUnknown808;
    void *mpUnknown812;
    char mUnknown816[192];
    union {
        int mUnknown1008Word;
        struct {
            Key_80110630 mUnknown1008;
            unsigned char mUnknown1011;
        };
    };
    unsigned char mUnknown1012[4];
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
            char mUnknown1128[6];
            unsigned short mUnknown1134;
            unsigned char mUnknown1136;
            unsigned char mUnknown1137;
            unsigned char mUnknown1138;
            unsigned char mUnknown1139;
        };
        Block_8011E240 mBlock1032;
    };
    /* Block at +1140 whose first word is the player reference fn_8009BCE8
       resolves; fn_800A3E84 and fn_800A414C address it through a pointer. */
    union {
        struct {
            int mUnknown1140;
            int mUnknown1144;
            float mUnknown1148;
            short mUnknown1152;
            union {
                unsigned short mUnknown1154;
                short mUnknown1154Signed;
            };
            unsigned char mUnknown1156;
            char mUnknown1157[1];
            short mUnknown1158;
        };
        Target_800A3E84 mTarget;
    };
    Block_801718E8 mUnknown1160;
    char mUnknown1216[2];
    unsigned char mUnknown1218;
    unsigned char mUnknown1219;
    unsigned char mUnknown1220;
    unsigned char mUnknown1221;
    unsigned char mUnknown1222;
    char mUnknown1223[1];
    Object_80039F5C *mpUnknown1224;
    Block_800D0B90 mUnknown1228;
    Object_800CE674 mUnknown1240;
    char mUnknown1244[1656];
    float mUnknown2900;
    union {
        char mUnknown2904[4];
        float mUnknown2904Float;
    };
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
       fn_800F053C. */
    State_80039F5C mQueue[10];
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
