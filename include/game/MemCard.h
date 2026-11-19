#ifndef GAME_MEMCARD_H
#define GAME_MEMCARD_H

/* Card stream target record handed to the card stream open operation (src/game/CardStream.cpp). */
struct CardStreamTarget {
    unsigned int mChecksum;
    unsigned int mSize;
    unsigned int mPosition;
    unsigned char mFillToEnd;
};

extern "C" {
void MemCardAllocateIOBuffer(void);
void MemCardFreeIOBuffer(void);
void MemCardBeginSave(void);
void MemCardBeginLoad(void);
void MemCardFinishLoad(int a, int *b);
int MemCardUpdateSaveLoad(int a, int *b, int *c);
}

#endif
