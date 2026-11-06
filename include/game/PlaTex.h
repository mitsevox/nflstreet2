#ifndef GAME_PLATEX_H
#define GAME_PLATEX_H

#include "game/PlayerLookRecord.h"
#include "game/Row_8007BC34.h"

/* Defined in src/game/PlaTex.cpp. */
extern "C" {
void PlaTexRemapColors(unsigned char *pColors);
void PlaTexApplyAwayColors(unsigned char *pColors, unsigned char flag);
void PlaTexBuildPartIds(Row_8007BC34 *pRow, PlayerLook_t *pRecord, int *pIds, int *pPalettes, int slot);
int PlaTexIsNumberItem(Row_8007BC34 *pRow);
void PlaTexBuildDefaultIds(int *pIds, PlayerLook_t *pRecord);
}

#endif
