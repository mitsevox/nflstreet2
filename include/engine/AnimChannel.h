#ifndef ENGINE_ANIMCHANNEL_H
#define ENGINE_ANIMCHANNEL_H

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

typedef struct AnimWgtLinear_t {
    float mUnknown0;
    unsigned int mUnknown4;
} AnimWgtLinear_t;

typedef struct AnimWgtWaitToStop_t {
    float mUnknown0;
} AnimWgtWaitToStop_t;

typedef struct AnimWgtLinearInAndOut_t {
    float mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
    signed char mUnknown9;
    unsigned short mUnknownA;
} AnimWgtLinearInAndOut_t;

typedef union AnimWgtTypeData_t {
    AnimWgtLinear_t mType1;
    AnimWgtWaitToStop_t mType2;
    AnimWgtLinearInAndOut_t mType3;
} AnimWgtTypeData_t;

/* Weight fade: current and target value, update type and its parameters. */
typedef struct AnimWgt_t {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    AnimWgtTypeData_t mUnknownC;
} AnimWgt_t;

/* 124-byte animation channel. */
typedef struct AnimChannel_t {
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
    AnimWgt_t mUnknown30;
    float mUnknown48;
    AnimSeq_t mUnknown4C;
} AnimChannel_t;

#endif
