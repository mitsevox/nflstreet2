#ifndef GAME_LEVEL_80054130_H
#define GAME_LEVEL_80054130_H

/* 36-byte placement entry of the level data returned by fn_80054130. */
struct Entry_80054130 {
    float mUnknown0[6];
    unsigned short mUnknown24;
    int mUnknown28;
    int mUnknown32;
};

/* Three floats; fn_800541AC, fn_8005429C, fn_800542DC and fn_8005434C test
   mZ against 0.1 and copy mX and mY. */
struct Point_80054130 {
    float mX;
    float mY;
    float mZ;
};

/* 60-byte record of the list at +140 of the level data: a point followed by
   four points at +12. */
struct Record_80054130 {
    Point_80054130 mUnknown0;
    Point_80054130 mUnknown12[4];
};

/* 48-byte record of the list at +132 of the level data: four points. */
struct Corners_800542DC {
    Point_80054130 mPoint[4];
};

/* 36-byte entry of the list at +28 of the level data; fn_8005415C stores
   its second argument at +8 of each entry whose +32 equals its first. */
struct Entry_8005415C {
    char mUnknown0[8];
    int mUnknown8;
    char mUnknown12[20];
    int mUnknown32;
};

/* 28-byte entry of the list at +156 of the level data, returned by
   fn_8005438C. */
struct Entry_8005438C {
    char mUnknown0[28];
};

/* The level data whose address fn_80054130 returns. Only the accessed
   fields are declared. */
struct Level_80054130 {
    char mUnknown0[24];
    unsigned int mUnknown24;
    Entry_8005415C *mUnknown28;
    char mUnknown32[12];
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
    char mUnknown120[8];
    unsigned int mUnknown128;
    Corners_800542DC *mUnknown132;
    unsigned int mUnknown136;
    Record_80054130 *mUnknown140;
    char mUnknown144[8];
    unsigned int mUnknown152;
    Entry_8005438C *mUnknown156;
};

extern "C" {
Level_80054130 *fn_80054130(void);
void fn_800541AC(Record_80054130 *pRecord, void *pA, void *pB);
}

#endif
