#ifndef GAME_BLOCK_800C9D6C_H
#define GAME_BLOCK_800C9D6C_H

/* One of the five 24-byte entries per team of Block_800C9D6C. */
struct Entry_800C9D6C {
    int mRef;
    unsigned int mUnknown4;
    int mUnknown8;
    unsigned int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned short mUnknown12;
    unsigned int mUnknown14;
};

/* Allocated through fn_80238174 under the id 'turb' (fn_800C9D6C). */
struct Block_800C9D6C {
    int mRefs[3];
    unsigned int mCounts[2];
    Entry_800C9D6C mEntries[2][5];
    unsigned char mUnknown104;
    unsigned char mUnknown105;
};


extern "C" Block_800C9D6C *fn_800CA8EC(void);

#endif
