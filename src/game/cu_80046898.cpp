#include "game/Block_80307980.h"

/* Face part ids the check rejects, ended by 0xFFFF; the list holds only the terminator. */
static const int lbl_803ED6A0[] = { 0xFFFF };

int fn_80046898(Block_80307980 *pBlock) {
    int allowed = 1;
    int i;
    int j;
    int *pIds = pBlock->mUnknown0;

    for (i = 0; lbl_803ED6A0[i] != 0xFFFF; i++) {
        for (j = 0; j < 10; j++) {
            if (lbl_803ED6A0[i] == pIds[j]) {
                allowed = 0;
                break;
            }
        }
    }
    return allowed;
}
