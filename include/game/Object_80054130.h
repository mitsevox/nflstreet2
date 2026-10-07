#ifndef GAME_OBJECT_80054130_H
#define GAME_OBJECT_80054130_H

/* 60-byte record of the list fn_80054130's object points to. */
struct Record_80054130 {
    char mUnknown00[0x3C];
};

/* The object whose address fn_80054130 returns. Only the accessed fields
   are declared. */
struct Object_80054130 {
    char mUnknown00[0x88];
    unsigned int mUnknown88;
    Record_80054130 *mUnknown8C;
};

extern "C" {
Object_80054130 *fn_80054130(void);
void fn_800541AC(Record_80054130 *pRecord, void *pA, void *pB);
}

#endif
