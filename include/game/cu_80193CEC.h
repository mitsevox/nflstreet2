#ifndef GAME_CU_80193CEC_H
#define GAME_CU_80193CEC_H

/* Record passed as the third argument of the fn_80193CEC callback; only
   the string at +0x20 is read. */
struct Comment_80193CEC {
    char mUnknown0[0x20];
    char mUnknown20[0x20];
};

extern "C" {
int fn_80193CEC(char *pOut, int unused, Comment_80193CEC *pComment);
void fn_80193D44(void);
void fn_80193D48(void *pData, int index, int *pOptional, int *pOut);
void fn_80193DC4(int *pFiles, int *pBlocks);
}

#endif
