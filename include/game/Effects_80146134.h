#ifndef GAME_EFFECTS_80146134_H
#define GAME_EFFECTS_80146134_H

struct Vector_80146134 { float x, y, z; };

struct Subrecord_80146134 { int mUnknown0; float mUnknown4, mUnknown8, mUnknownC, mUnknown10, mUnknown14; };

struct Slot_80146A6C { Subrecord_80146134 *mUnknown0; float mUnknown4; };

struct Entry_80146C4C {
    Subrecord_80146134 *mUnknown0;
    int mUnknown4, mUnknown8, mUnknownC;
    unsigned char mUnknown10, mUnknown11;
    char mUnknown12[2];
    float mUnknown14;
    Vector_80146134 mUnknown18, mUnknown24;
    float mUnknown30;
    unsigned char mUnknown34, mUnknown35, mUnknown36;
    char mUnknown37;
    float mUnknown38;
    char mUnknown3C[136]; /* Indexed as 8-byte slots; original capacity unknown. */
};

struct Resource_80146E64 {
    void *mUnknown0;
    int mUnknown4, mUnknown8;
    unsigned char mUnknownC;
    char mUnknownD[3];
    unsigned char mUnknown10[44];
    unsigned char mUnknown3C[40];
    unsigned char mUnknown64;
    char mUnknown65[3];
};

extern "C" int fn_80146BA8(Vector_80146134 *);

#endif
