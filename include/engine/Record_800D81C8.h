#ifndef ENGINE_RECORD_800D81C8_H
#define ENGINE_RECORD_800D81C8_H

/* Animation channel types shared by the engine animation library and the game. */

typedef struct Pair_802270A4 {
    float mUnknown0;
    float mUnknown4;
} Pair_802270A4;

typedef struct Triple_801BCA74 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} Triple_801BCA74;

/* Channel list header: +0 selects the initial channel state, +2 the object
   type, +4 the channel count; +8 is the shared angle base. */
typedef struct AnimHeader_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned char mUnknown6[2];
    int mUnknown8;
} AnimHeader_t;

/* Sequence script: rate byte (sixteenths), flag byte +2, then opcode halfwords. */
typedef struct AnimScript_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    unsigned short mUnknown4[1];
} AnimScript_t;

typedef struct AnimSeqLoop_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    float mUnknown4;
} AnimSeqLoop_t;

/* Sequence playback state (channel +0x4C). */
typedef struct AnimSeq_t {
    AnimScript_t *mpUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    float mUnknown14;
    unsigned short mUnknown18;
    unsigned short mUnknown1A;
    unsigned short mUnknown1C;
    unsigned char mUnknown1E;
    unsigned char mUnknown1F;
    AnimSeqLoop_t mUnknown20[2];
} AnimSeq_t;

typedef struct Data1_801BF4A8 {
    float mUnknown0;
    unsigned int mUnknown4;
} Data1_801BF4A8;

typedef struct Data2_801BF11C {
    float mUnknown0;
} Data2_801BF11C;

typedef struct Data3_801BF530 {
    float mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
    signed char mUnknown9;
    unsigned short mUnknownA;
} Data3_801BF530;

typedef union Data_801BF3C8 {
    Data1_801BF4A8 mType1;
    Data2_801BF11C mType2;
    Data3_801BF530 mType3;
} Data_801BF3C8;

/* Weight fade: current and target value, update type and its parameters. */
typedef struct Block_801BF3C8 {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    Data_801BF3C8 mUnknownC;
} Block_801BF3C8;

/* 124-byte animation channel. */
typedef struct Record_800D81C8 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    short mUnknown2;
    unsigned short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    int mUnknownC;
    Triple_801BCA74 mUnknown10;
    int mUnknown1C;
    int mUnknown20;
    Pair_802270A4 mUnknown24;
    float mUnknown2C;
    Block_801BF3C8 mUnknown30;
    float mUnknown48;
    AnimSeq_t mUnknown4C;
} Record_800D81C8;

#endif
