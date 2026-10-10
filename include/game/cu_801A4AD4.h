#ifndef GAME_CU_801A4AD4_H
#define GAME_CU_801A4AD4_H

#include "game/FMCAPPORT.h"
#include "game/fn_8021216C.h"

struct Object_8003DEC4;

/* Entry of the table walked by fn_801A4C1C: a texture name looked up with
   fn_802345F8, a flag, and the descriptor passed to fn_8021216C. */
struct Entry_802F3488 {
    const char *mpName;
    unsigned char mUnknown4;
    Desc_802EE9E4 mUnknown8;
};

extern "C" {
void fn_801A4AD4(Object_8003DEC4 *pPlayer);
void *fn_801A4AE4(int player);
void fn_801A4B08(Desc_802347EC *pDesc);
void fn_801A4B28(void *pDest, void *pSrc, unsigned int size);
void fn_801A4C1C(Desc_802347EC *pDescs, Entry_802F3488 *pEntries);
}

#endif
