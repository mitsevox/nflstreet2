#ifndef GAME_BLOCK_80307980_H
#define GAME_BLOCK_80307980_H

struct FMCAPPORTValues;
struct Object_8008044C;

/* 40-byte block filled by fn_80082138 and read by fn_80046898. */
struct Block_80307980 {
    int mUnknown0[10];
};

extern "C" {
void fn_80046804(Block_80307980 *pBlock, FMCAPPORTValues *pValues);
int fn_80046898(Block_80307980 *pBlock);
void fn_80049F10(int index, Block_80307980 *pBlock);
void fn_80049FC8(int index, Block_80307980 *pBlock);
void fn_80082138(Object_8008044C *pObject, Block_80307980 *pBlock);
void fn_80082334(Object_8008044C *pObject, Block_80307980 *pBlock);
}

#endif
