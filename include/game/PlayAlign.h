#ifndef GAME_PLAYALIGN_H
#define GAME_PLAYALIGN_H

#include "game/Object_80039F5C.h"
#include "game/PlayBookDb.h"

extern "C" {
void PlayAlignPlayer(Object_80039F5C *p, PlayBookPosition_t *pEntry, int side);
void PlayAlignTeam(PlayBookFormation_t *pObject, int team, const char **ppNames);

/* Null-terminated name list passed through to PlaySetGetEntry. */
extern const char *gPlayAlignNormSet[];
}

#endif
