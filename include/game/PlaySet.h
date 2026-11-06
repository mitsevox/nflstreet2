#ifndef GAME_PLAYSET_H
#define GAME_PLAYSET_H

#include "game/fn_800670B4.h"

struct Object_80039F5C;

extern "C" {
Entry_8006719C *PlaySetGetEntry(Object_800670B4 *pObject, unsigned int index, const char **ppNames);
int PlaySetGetNextOrder(Object_800670B4 *pObject, unsigned char index);
int PlaySetGetPrevOrder(Object_800670B4 *pObject, unsigned char index);
void PlaySetGetEntryRoles(Object_800670B4 *pObject, unsigned char index, unsigned char *pA, unsigned char *pB);
Object_80039F5C *PlaySetGetKeyPlayer(Object_800670B4 *pObject);
void PlaySetNotifyRoleMates(Object_80039F5C *p);
}

#endif
