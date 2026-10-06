#ifndef GAME_CU_800478DC_H
#define GAME_CU_800478DC_H

#include "game/Record_803078E8.h"
#include "game/Row_8007BC34.h"

/* Defined in src/game/cu_800478DC.cpp. */
extern "C" {
void fn_800478DC(unsigned char *pColors);
void fn_8004795C(unsigned char *pColors, unsigned char flag);
void fn_800479B0(Row_8007BC34 *pRow, Record_803078E8 *pRecord, int *pIds, int *pPalettes, int slot);
int fn_80047C84(Row_8007BC34 *pRow);
void fn_80047CA4(int *pIds, Record_803078E8 *pRecord);
}

#endif
