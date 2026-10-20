#ifndef GAME_RECORD_8011F4F8_H
#define GAME_RECORD_8011F4F8_H

/* 32-byte record whose address fn_8011F4F8 returns for an index. Only the
   accessed fields are declared; the size of the whole array is not
   established. */
struct Record_8011F4F8 {
    float mUnknown0;
    float mUnknown4;
    short mUnknown8;
    /* Read as a plain char array and as an unsigned byte. */
    union {
        char mUnknownA[1];
        unsigned char mUnknownAByte;
    };
    unsigned char mUnknownB;
    float mUnknownC;
    int mUnknown10;
    float mUnknown14;
    float mUnknown18;
    char mUnknown1C[1];
    unsigned char mUnknown1D;
    char mUnknown1E[2];
};

extern "C" Record_8011F4F8 *fn_8011F4F8(int index);

#endif
