#ifndef GAME_PLAYALIGN_H
#define GAME_PLAYALIGN_H

#include "game/Object_80039F5C.h"
#include "game/fn_800670B4.h"

extern "C" {
void PlayAlignPlayer(Object_80039F5C *p, Entry_8006719C *pEntry, int side);
void PlayAlignTeam(Object_800670B4 *pObject, int team, const char **ppNames);

/* Null-terminated name list passed through to PlaySetGetEntry. */
extern const char *gPlayAlignNormSet[];
}

#endif
