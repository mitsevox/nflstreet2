#ifndef GAME_CU_8008E978_H
#define GAME_CU_8008E978_H

#include "game/Object_80039F5C.h"

struct Object_80137ABC;

/* Views of the records returned by fn_80093BAC, fn_80093BCC and
   fn_80096DA8. Their original identities and the contents of the opaque
   spans remain unknown. */
struct Frame_80141210 { unsigned char mUnknown0[0x14]; int mUnknown14; unsigned char mUnknown18[0x18]; float mUnknown30, mUnknown34; unsigned char mUnknown38[4]; float mUnknown3C; };
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
};
struct Selection_80141210 { unsigned char mUnknown0; unsigned char mUnknown1[3]; union { int mWord; unsigned short mParts[2]; } mUnknown4,mUnknown8; };

/* One of the four 912-byte records at +128 of the block fn_800925F0
   allocates. */
struct Character_80093BCC {
    int mUnknown0,mUnknown4;
    unsigned char mUnknown8[12];
    Object_80039F5C *mUnknown14[24];
    Object_80137ABC *mUnknown74[24];
    unsigned char mUnknownD4[4];
    union { int mWord; unsigned short mParts[2]; } mUnknownD8;
    unsigned char mUnknownDC[4];
    Selection_80141210 mUnknownE0;
    unsigned char mUnknownEC[0x2A0];
    int mUnknown38C;
};

/* One of the two 48-byte records at +16 of the block fn_80096954
   allocates. */
struct Playback_80096DA8 {
    int mUnknown0,mUnknown4,mUnknown8; unsigned int mUnknownC;
    int mUnknown10; union { int mWord; unsigned short mParts[2]; } mUnknown14,mUnknown18,mUnknown1C;
    float mUnknown20,mUnknown24;
    unsigned char mUnknown28[4]; unsigned int mUnknown2C;
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
struct Entry_800AF82C {
    int mUnknown0;
    Item_800AF82C *mpUnknown4;
    void *mpUnknown8;
    float mUnknownC;
    float mUnknown10;
    int mUnknown14;
    unsigned char mUnknown18[24];
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

#endif
