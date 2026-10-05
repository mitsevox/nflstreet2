#ifndef GAME_OBJECT_800785C0_H
#define GAME_OBJECT_800785C0_H

/* Block that fn_800785C0 returns; only the accessed fields are declared. */
struct Object_800785C0 {
    char mUnknown0[0x1A8];
    int mUnknown1A8;
    int mUnknown1AC;
    int mUnknown1B0;
    int mUnknown1B4;
    char mUnknown1B8[0x1C1 - 0x1B8];
    unsigned char mUnknown1C1;
};

extern "C" {
Object_800785C0 *fn_800785C0(void);
}

#endif
