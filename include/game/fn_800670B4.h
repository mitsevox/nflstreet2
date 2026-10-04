#ifndef GAME_FN_800670B4_H
#define GAME_FN_800670B4_H

/* One of the seven 40-byte entries at Object_8006719C +0x84. */
struct Entry_8006719C {
    char mUnknown0[0xB];
    unsigned char mUnknownB;
    char mUnknownC[0x1C];
};

/* Filled by fn_8006719C and fn_8006723C, which clear all 0xCA8 bytes first. */
struct Object_8006719C {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[7];
    unsigned char mUnknownF;
    char mUnknown10[4];
    unsigned int mUnknown14;
    char mUnknown18[0x6C];
    Entry_8006719C mUnknown84[7];
    char mUnknown19C[0xB0C];
};

/* Filled by fn_800670B4, which clears all 0xCE4 bytes first. */
struct Object_800670B4 {
    int mUnknown0;
    int mUnknown4;
    Object_8006719C mUnknown8;
    char mUnknownCB0[0x34];
};

/* Filled by fn_80067338, which clears all 0x20C bytes first. */
struct Record_80067338 {
    char mUnknown0[0x18];
    unsigned int mUnknown18;
    char mUnknown1C[0x1D4];
    char mUnknown1F0[0x1C];
};

extern "C" {
unsigned short fn_80067038(int tag, int kind);
int fn_800670B4(int tag, int a, int b, Object_800670B4 *pObject);
unsigned short fn_80067120(int tag, int handle);
void fn_8006719C(int tag, int handle, int index, void *pOwner, Object_8006719C *pObject);
void fn_8006723C(int tag, int handle, void *pOwner, Object_8006719C *pObject);
unsigned short fn_800672BC(int tag, int handle);
int fn_80067338(int tag, int handle, int index, Record_80067338 *pRecord);
}

#endif
