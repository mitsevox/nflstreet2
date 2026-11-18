#ifndef GAME_REPLAYEVENT_H
#define GAME_REPLAYEVENT_H

#include "game/cu_8002B8F8.h"

/* Event list of the replay object (src/game/ReplayEvent.cpp). */
extern "C" {
unsigned int ReplayEventFind(Type_803EA368 *p, int id);
void ReplayEventAdd(Type_803EA368 *p, int id, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing);
int ReplayEventGetTime(Type_803EA368 *p, int id);
int ReplayEventGetPos(Type_803EA368 *p, int id, float *pOut);
Object_80039F5C *ReplayEventGetObject(Type_803EA368 *p, int id);
void ReplayEventClearAll(Type_803EA368 *p);
int ReplayEventExists(Type_803EA368 *p, int id);
int ReplayEventInWindow(Type_803EA368 *p, int id);
void ReplayEventAddPlayer(Object_80039F5C *p);
void ReplayEventAddForCode(Object_80039F5C *p, int code);
}

#endif
