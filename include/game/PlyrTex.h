#ifndef GAME_PLYRTEX_H
#define GAME_PLYRTEX_H

#include "game/FMCAPPORT.h"
#include "engine/tmtexlib.h"

struct Object_8003DEC4;

/* Entry of the table walked by PlyrTexApplyFilters: a texture name looked up with
   fn_802345F8, a flag, and the descriptor passed to TMTexLibSetFilterParm. */
struct PlyrTexPartFilter {
    const char *mpName;
    unsigned char mUnknown4;
    TMTexFilterDesc_t mUnknown8;
};

extern "C" {
void PlyrTexRequestNameplate(Object_8003DEC4 *pPlayer);
void *PlyrTexGetLib(int player);
void PlyrTexFreeDesc(Desc_802347EC *pDesc);
void PlyrTexCopy(void *pDest, void *pSrc, unsigned int size);
void PlyrTexApplyFilters(Desc_802347EC *pDescs, PlyrTexPartFilter *pEntries);
}

#endif
