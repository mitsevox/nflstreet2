#ifndef GAME_CU_80164568_H
#define GAME_CU_80164568_H

#include "game/Object_80039F5C.h"
#include "game/fn_800670B4.h"

extern "C" {
void fn_80164568(Object_80039F5C *p, Entry_8006719C *pEntry, int side);
void fn_801647A4(Object_800670B4 *pObject, int team, const char **ppNames);

/* Null-terminated name list passed through to fn_80163E94. */
extern const char *lbl_803EB3B0[];
}

#endif
