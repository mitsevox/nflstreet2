#ifndef GAME_FN_800670B4_H
#define GAME_FN_800670B4_H

/* Filled by fn_800670B4, which clears all 0xCE4 bytes first. */
struct Object_800670B4 {
    int mUnknown0;
    char mUnknown4[0xCE0];
};

/* Filled by fn_80067338, which clears all 0x20C bytes first. */
struct Record_80067338 {
    char mUnknown0[0x1F0];
    char mUnknown1F0[0x1C];
};

extern "C" {
int fn_800670B4(int tag, int a, int b, Object_800670B4 *pObject);
unsigned short fn_800672BC(int tag, int handle);
int fn_80067338(int tag, int handle, int index, Record_80067338 *pRecord);
}

#endif
