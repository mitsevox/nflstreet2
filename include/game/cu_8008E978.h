#ifndef GAME_CU_8008E978_H
#define GAME_CU_8008E978_H

#include "game/Object_80039F5C.h"
#include "game/Params_80092E54.h"

struct Object_80137ABC;

/* Views of the records returned by fn_80093BAC, fn_80093BCC and
   fn_80096DA8. Their original identities and the contents of the opaque
   spans remain unknown. */
struct Frame_80141210 { unsigned char mUnknown0[0x14]; int mUnknown14; float mUnknown18, mUnknown1C, mUnknown20, mUnknown24; unsigned char mUnknown28[2]; unsigned short mUnknown2A; unsigned char mUnknown2C[4]; float mUnknown30, mUnknown34, mUnknown38, mUnknown3C; };
struct Frame_800DF7CC;

/* One of the mUnknown6 48-byte entries at +32 of an Actor_801C009C;
   fn_80091644 looks for the id 'JMA'. */
struct Entry_80091644 {
    int mId;
    unsigned char mUnknown4[44];
};

struct Actor_801C009C {
    union {
        struct { unsigned short mUnknown0, mUnknown2; };
        int mUnknown0Word;
    };
    union {
        struct { unsigned short mUnknown4, mUnknown6; };
        int mUnknown4Word;
    };
    unsigned int mUnknown8;
    unsigned char mUnknownC[12];
    Frame_80141210 *mUnknown18;
    Frame_800DF7CC *mpUnknown1C;
    Entry_80091644 *mpUnknown20;
};

/* One of the four 912-byte records at +128 of the block fn_800925F0
   allocates. */
struct Character_80093BCC : Params_80092E54 {
    unsigned char mUnknownEC[0x2A0];
    int mUnknown38C;
};

struct Table_800680A8;

/* Data whose word +4 fn_80094374 returns and whose words from +8
   fn_80093BAC indexes; the bound of that array is not established. */
struct Table_80093BAC {
    unsigned char mUnknown0[4];
    int mUnknown4;
    Actor_801C009C *mpUnknown8[1];
};

/* One of the six 20-byte entries at +4 of Block_800925F0. */
struct Entry_80094238 {
    Table_80093BAC *mpUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
};

/* The 3664 bytes at +128 of Block_800925F0 that fn_800920EC copies and
   fn_80092168 compares. */
struct Block_800920EC {
    Character_80093BCC mCharacters[4];
    short mUnknownE40[7];
    unsigned char mUnknownE4E;
    unsigned char mUnknownE4F[1];
};

/* Allocated through fn_80238174 under the id 'anms' (fn_800925F0). */
struct Block_800925F0 {
    Table_800680A8 *mpUnknown0;
    Entry_80094238 mEntries[6];
    void *mpUnknown7C;
    Block_800920EC mUnknown80;
};

extern Block_800925F0 *lbl_803EC924;

/* 16-byte records of the two-entry table cleared by fn_8009418C. */
struct Slot_8009418C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
};

extern Slot_8009418C lbl_8030C164[2];

/* One of the two 48-byte records at +16 of the block fn_80096954
   allocates. */
struct Playback_80096DA8 {
    int mUnknown0,mUnknown4; union { int mWord; unsigned short mParts[2]; } mUnknown8; unsigned int mUnknownC;
    int mUnknown10; union { int mWord; unsigned short mParts[2]; } mUnknown14,mUnknown18,mUnknown1C;
    float mUnknown20,mUnknown24;
    unsigned short mUnknown28, mUnknown2A; unsigned int mUnknown2C;
};

/* One of the ten 40-byte entries of the block fn_80094E80 allocates under
   the id 'anmm'. */
struct Entry_80094BC4 {
    void *mpUnknown0;
    void *mpUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    Vector_80039F5C mUnknown14;
    void (*mpCallback20)(void *p);
    int mUnknown24;
};

/* 24-byte items of the array at lbl_803EC97C. */
struct Item_800AF82C {
    unsigned char mUnknown0[24];
};

/* 64-byte entries; fn_800AF804 clears three of them. */
struct Pose_80041930;

struct Entry_800AF82C {
    union {
        int mUnknown0;
        Pose_80041930 *mpUnknown0;
    };
    Item_800AF82C *mpUnknown4;
    void *mpUnknown8;
    float mUnknownC;
    float mUnknown10;
    union {
        int mUnknown14;
        Vector_80039F5C *mpUnknown14;
    };
    Vector_80039F5C mUnknown18;
    Vector_80039F5C mUnknown24;
    int mUnknown30[3];
    unsigned char mUnknown3C;
    unsigned char mUnknown3D;
    unsigned char mUnknown3E[2];
};

/* 8-byte records from +12 of Table_800AA80C. */
struct Entry_800AA80C {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5[3];
};

typedef void (*Callback_800AAE20)(Entry_800AA80C *pEntries, int index);

/* The .data table whose address fn_800AA80C stores at +0 of
   Block_800AACD4: three callbacks, then the records. */
struct Table_800AA80C {
    Callback_800AAE20 mpCallback0;
    Callback_800AAE20 mpCallback4;
    Callback_800AAE20 mpCallback8;
    Entry_800AA80C mEntries[15];
    float mUnknown84;
};

/* 24-byte block allocated under the id 'gend' at 0x800AACFC. */
struct Block_800AACD4 {
    Table_800AA80C *mpUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    signed char mUnknown16;
    unsigned char mUnknown17;
};

extern "C" {
Actor_801C009C *fn_80093BAC(int,int);
Character_80093BCC *fn_80093BCC(unsigned int);
Playback_80096DA8 *fn_80096DA8(unsigned int);
Actor_801C009C *fn_80096DCC(unsigned int,int);
}

/* Partial view of the object whose word +40 fn_800C6640 decodes as a
   player reference. The size is unknown. */
struct Object_800C6640 {
    unsigned char mUnknown0;
    unsigned char mUnknown1[31];
    float mUnknown32;
    unsigned char mUnknown36[4];
    int mUnknown40;
    unsigned char mUnknown44[9];
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
};

/* 8.24 fixed-point multiply used by the head/body turn easing. */
static inline int FixedMul(int a, int b)
{
    return (int)(((long long)a * b) >> 24);
}

#endif
