#ifndef GAME_MEMCARDCALLBACKS_H
#define GAME_MEMCARDCALLBACKS_H

/* Record passed as the third argument of the MemCardGetNameFromComment callback; only
   the string at +0x20 is read. */
struct MemCardComment {
    char mUnknown0[0x20];
    char mUnknown20[0x20];
};

extern "C" {
int MemCardGetNameFromComment(char *pOut, int unused, MemCardComment *pComment);
void MemCardNullCallback(void);
void MemCardGetIcon(void *pData, int index, unsigned char **pOptional, unsigned int *pOut);
void MemCardGetNewSaveSpace(int *pFiles, int *pBlocks);
}

#endif
