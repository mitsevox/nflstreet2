#ifndef GAME_RECORD_8011F4F8_H
#define GAME_RECORD_8011F4F8_H

/* 32-byte record whose address fn_8011F4F8 returns for an index. Only the
   accessed fields are declared; the size of the whole array is not
   established. */
struct Record_8011F4F8 {
    float mUnknown0;
    float mUnknown4;
    short mUnknown8;
    char mUnknownA[1];
    unsigned char mUnknownB;
    float mUnknownC;
    int mUnknown10;
    char mUnknown14[12];
};

extern "C" Record_8011F4F8 *fn_8011F4F8(int index);

#endif
