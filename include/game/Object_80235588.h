#ifndef GAME_OBJECT_80235588_H
#define GAME_OBJECT_80235588_H

/* Record at +0x8 of the +0x64 block; only its +0x10 flag word is accessed here. */
typedef struct Record_80235630 {
    char mUnknown0[16];
    unsigned int mUnknown16;
} Record_80235630;

/* 0xC0-byte block set up by 0x80235588 and passed to 0x802355E4; partial layout. */
typedef struct Object_80235588 {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8[4][4];
    float mUnknown72;
    char mUnknown76[8];
    void *mpUnknown84;
    void *mpUnknown88;
    char mUnknown92[8];
    struct {
        char mUnknown0[8];
        Record_80235630 *mpUnknown8;
        char mUnknown12[40];
    } mUnknown100;
    char mUnknown152[32];
    int mUnknown184;
    float mUnknown188;
} Object_80235588;

#endif
