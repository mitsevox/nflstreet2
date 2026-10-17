#ifndef GAME_ITEM_80097440_H
#define GAME_ITEM_80097440_H

#include "game/Object_80039F5C.h"
#include "game/Block_801BE60C.h"
#include "game/cu_8008E978.h"

/* 60-byte records that fn_80097440 copies into the buffer at +3048 of
   Record_80097518. */
struct Item_80097440 {
    unsigned char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6[2];
    Vector_80039F5C mUnknown8;
    Vector_80039F5C mUnknown14;
    float mUnknown20;
    unsigned short mUnknown24;
    unsigned char mUnknown26[2];
    int mUnknown28;
    unsigned char mUnknown2C[12];
    int mUnknown38;
};

/* 8-byte entries from +8 of Record_80097518. */
struct Slot_80097440 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Item_80097440 *mpUnknown4;
};

/* 3080-byte records of the .bss array at 0x8030C2B8. */
struct Record_80097518 {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned char mUnknown6[2];
    Slot_80097440 mUnknown8[380];
    Item_80097440 *mpUnknownBE8;
    unsigned short mUnknownBEC[7];
    unsigned short mUnknownBFA[7];
};

/* Block at player +336 passed to fn_80099734, fn_800997F4 and fn_8009817C.
   Only the accessed fields are declared. */
struct Block_800997F4 {
    char mUnknown0[8];
    int mUnknown8;
    int mUnknown12;
};

/* 60-byte payload fn_801BE60C returns for the state fn_8009A344 runs; phase
   0 initialises it from the template at +4 of Block_80099630. */
struct Block_8009A344 {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    int mUnknown14;
    float mUnknown18;
    float mUnknown1C;
    int mUnknown20;
    State_800D8140 mUnknown24;
};

/* The 64-byte block fn_80099630 allocates under the id 'ctch'. */
struct Block_80099630 {
    int mUnknown0;
    Block_8009A344 mUnknown4;
};

/* 12-byte block allocated by fn_8009AB34 under the id 'ctup'. */
struct Block_8009AB34 {
    float mUnknown0[2];
    unsigned char mUnknown8;
};

/* 16-byte callback records copied into Block_8009B5E8 by fn_8009B87C. */
struct Entry_8009B87C {
    int (*mpCallback0)(int value, int *pData);
    int (*mpCallback4)(int *pData);
    void (*mpCallback8)(int *pData);
    float (*mpCallbackC)(int *pData);
};

/* The 300 bytes at +4 of Block_8009B720 that fn_8009B698 copies and
   fn_8009B5E8 checks. */
struct Block_8009B5E8 {
    int mUnknown0;
    Entry_8009B87C mEntries[2];
    unsigned int mUnknown24;
    int mUnknown28[63];
    unsigned char mUnknown124[3];
    unsigned char mUnknown127;
    int mUnknown128;
};

/* 304-byte blocks allocated by fn_8009B720 under the id 'celb'. */
struct Block_8009B720 {
    void *mpUnknown0;
    Block_8009B5E8 mUnknown4;
};

/* 24-byte entries at +44 of Block_8009C6F4. */
struct Entry_8009C684 {
    void (*mpCallback0)(Object_80039F5C *p, Vector_80039F5C *pVec, void *pData);
    Vector_80039F5C mUnknown4;
    unsigned char mUnknown10[8];
};

/* Record passed to fn_8009C6F4, fn_8009C814 and fn_8009C88C. Only the
   accessed fields are declared; the size is unknown. */
struct Block_8009C6F4 {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned int mUnknown8;
    short mUnknownC;
    short mUnknownE;
    Vector_80039F5C mUnknown10;
    int mUnknown1C[3];
    Pose_80041930 *mpPose;
    Entry_8009C684 mEntries[2];
};

struct Entry_8009D964 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
};

/* Allocated through fn_80238174 under the id 'clck' (fn_8009D474). */
struct Block_8009D474 {
    int mUnknown0;
    Entry_8009D964 mEntries[6];
    int mUnknown94;
    int mUnknown98;
};

/* One of the 24 four-float boxes fn_8009E674 lays out at +0x18 of
   State_8011F4EC. */
struct Box_8009E674 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
};

typedef Box_8009E674 Entry_8011F4EC;

/* Object whose address fn_8011F4EC returns. Only the accessed bytes are
   declared; the size is not established. */
struct State_8011F4EC {
    int mUnknown0;
    int mUnknown4[2];
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned char mUnknown16[2];
    Box_8009E674 mUnknown18[24];
    unsigned char mUnknown198;
    unsigned char mUnknown199[3];
    unsigned char mUnknown19C[3];
    unsigned char mUnknown19F[3];
    unsigned char mUnknown1A2;
    unsigned char mUnknown1A3;
    unsigned char mUnknown1A4;
    unsigned char mUnknown1A5[3];
    unsigned char mUnknown1A8;
    unsigned char mUnknown1A9;
    unsigned char mUnknown1AA[2];
    float mUnknown1AC[3];
    unsigned char mUnknown1B8[3];
    unsigned char mUnknown1BB[3];
    unsigned char mUnknown1BE[3];
    unsigned char mUnknown1C1[3];
    unsigned char mUnknown1C4;
    unsigned char mUnknown1C5;
};

#endif
