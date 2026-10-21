#ifndef GAME_OBJECT_8016B04C_H
#define GAME_OBJECT_8016B04C_H

/* One 20-byte history entry; fn_8016B144 shifts the list down and
   starts a new entry at index 0. */
struct Entry_8016B144 {
    int mUnknown0;
    int mUnknown4;
    unsigned int mUnknown8;
    signed char mUnknownC;
    signed char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
};

/* Allocated through fn_80238174 under the id 'ptrk' (fn_8016B04C). */
struct Object_8016B04C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned int mUnknown14;
    unsigned char mUnknown18;
    Entry_8016B144 mUnknown1C[2][24];
    unsigned short mUnknown3DC[2];
};

#endif
