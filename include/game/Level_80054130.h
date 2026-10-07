#ifndef GAME_LEVEL_80054130_H
#define GAME_LEVEL_80054130_H

/* 36-byte placement entry of the level data returned by fn_80054130. */
struct Entry_80054130 {
    float mUnknown0[6];
    unsigned short mUnknown24;
    int mUnknown28;
    int mUnknown32;
};

/* 60-byte record of the list at +140 of the level data. */
struct Record_80054130 {
    char mUnknown0[60];
};

/* The level data whose address fn_80054130 returns. Only the accessed
   fields are declared. */
struct Level_80054130 {
    char mUnknown0[44];
    char *mUnknown44;
    char mUnknown48[12];
    char *mUnknown60;
    char mUnknown64[4];
    char *mUnknown68;
    char mUnknown72[16];
    unsigned int mUnknown88;
    Entry_80054130 *mUnknown92;
    char mUnknown96[8];
    unsigned int mUnknown104;
    Entry_80054130 *mUnknown108;
    unsigned int mUnknown112;
    Entry_80054130 *mUnknown116;
    char mUnknown120[16];
    unsigned int mUnknown136;
    Record_80054130 *mUnknown140;
};

extern "C" {
Level_80054130 *fn_80054130(void);
void fn_800541AC(Record_80054130 *pRecord, void *pA, void *pB);
}

#endif
