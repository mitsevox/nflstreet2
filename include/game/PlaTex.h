#ifndef GAME_PLATEX_H
#define GAME_PLATEX_H

#include "game/PlayerLookRecord.h"
#include "game/GearDb.h"

/* Defined in src/game/PlaTex.cpp. */
extern "C" {
void PlaTexRemapColors(unsigned char *pColors);
void PlaTexApplyAwayColors(unsigned char *pColors, unsigned char flag);
void PlaTexBuildPartIds(GearRow_t *pRow, PlayerLook_t *pRecord, int *pIds, int *pPalettes, int slot);
int PlaTexIsNumberItem(GearRow_t *pRow);
void PlaTexBuildDefaultIds(int *pIds, PlayerLook_t *pRecord);
}

#endif
