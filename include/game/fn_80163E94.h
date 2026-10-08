#ifndef GAME_FN_80163E94_H
#define GAME_FN_80163E94_H

#include "game/fn_800670B4.h"

/* Record fn_80163E94 returns. Only the byte its callers read is declared. */
struct Record_80163E94 {
    char mUnknown0[11];
    unsigned char mUnknownB;
};

extern "C" Record_80163E94 *fn_80163E94(Object_800670B4 *pObject, unsigned int index, void *pArg);

#endif
