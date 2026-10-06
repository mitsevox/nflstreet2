#include "game/Block_80307980.h"

/* Ints that must not appear among the ten block words, ended by 0xFFFF; the list holds only
   the terminator, so the result is always 1. */
static const int lbl_803ED6A0[] = { 0xFFFF };

int fn_80046898(Block_80307980 *pBlock) {
    int result = 1;
    int i;
    int j;
    int *pWords = pBlock->mUnknown0;

    for (i = 0; lbl_803ED6A0[i] != 0xFFFF; i++) {
        for (j = 0; j < 10; j++) {
            if (lbl_803ED6A0[i] == pWords[j]) {
                result = 0;
                break;
            }
        }
    }
    return result;
}
