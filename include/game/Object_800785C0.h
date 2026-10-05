#ifndef GAME_OBJECT_800785C0_H
#define GAME_OBJECT_800785C0_H

/* Eight-byte entry of the two-entry list at +500 of Object_800785C0:
   fn_80079864 compares mId, and fn_80079538 passes mUnknown4 on to
   fn_8007947C. */
struct Entry_80079864 {
    int mId;
    unsigned short mUnknown4;
    char mUnknown6[2];
};

/* 40-byte block at +524 of Object_800785C0; fn_8007984C tests mUnknown0. */
struct Info_8007984C {
    int mUnknown0;
    char mUnknown4[12];
    char *mUnknown10[3];
    int mUnknown1C;
    unsigned short mUnknown20[3];
    char mUnknown26[2];
};

/* Record that fn_800780F8 clears and fills; fn_800785C0 returns the one at
   0x8030AE64. Only the accessed fields are declared. */
struct Object_800785C0 {
    unsigned char mUnknown0;
    char mUnknown1[202];
    char mUnknownCB[203];
    unsigned short mUnknown196;
    unsigned char mUnknown198;
    char mUnknown199[15];
    int mUnknown1A8;
    int mUnknown1AC;
    int mUnknown1B0;
    int mUnknown1B4;
    char mUnknown1B8[4];
    int mUnknown1BC;
    char mUnknown1C0[1];
    unsigned char mUnknown1C1;
    char mUnknown1C2[0x1F4 - 0x1C2];
    Entry_80079864 mUnknown1F4[2];
    char mUnknown204[4];
    int mUnknown208;
    Info_8007984C mUnknown20C;
};

extern "C" {
Object_800785C0 *fn_800785C0(void);
}

#endif
