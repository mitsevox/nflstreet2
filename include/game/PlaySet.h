#ifndef GAME_PLAYSET_H
#define GAME_PLAYSET_H

#include "game/PlayBookDb.h"

struct Object_80039F5C;

extern "C" {
PlayBookPosition_t *PlaySetGetEntry(PlayBookFormation_t *pObject, unsigned int index, const char **ppNames);
int PlaySetGetNextOrder(PlayBookFormation_t *pObject, unsigned char index);
int PlaySetGetPrevOrder(PlayBookFormation_t *pObject, unsigned char index);
void PlaySetGetEntryRoles(PlayBookFormation_t *pObject, unsigned char index, unsigned char *pA, unsigned char *pB);
Object_80039F5C *PlaySetGetKeyPlayer(PlayBookFormation_t *pObject);
void PlaySetPointToRoleMate(Object_80039F5C *p);
}

#endif
