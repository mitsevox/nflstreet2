#ifndef GAME_RECORD_800B15FC_H
#define GAME_RECORD_800B15FC_H

/* 0x1C-byte record of the list that r13-0x7788 holds: fn_800B15FC clears a new
   one, fn_800B1508 commits it and fn_800B1648 returns one by index. */
struct Record_800B15FC {
    /* Read both as a word and byte by byte. */
    union {
        int mUnknown0;
        unsigned char mUnknown0Bytes[4];
    };
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    unsigned int mUnknown18;
};

extern "C" {
void fn_800B1508(void);
unsigned short fn_800B15D4(void);
Record_800B15FC *fn_800B15FC(void);
Record_800B15FC *fn_800B1648(unsigned short index);
}

#endif
