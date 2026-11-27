#ifndef GAME_PLYROVERLAYANIM_H
#define GAME_PLYROVERLAYANIM_H

#include "game/Table_80089904.h"
#include "game/Object_80039F5C.h"
#include "engine/AnimChannel.h"

/* Motion-phase callbacks of the lbl_8030EFB4 table. */
typedef int (*Callback_800A3530)(Table_80089904 *pTable, unsigned short key, void *pRecord,
                                 AnimChannel_t *pEntries, Object_80039F5C *p, unsigned int phase);

extern "C" {
int PlyrOverlayAnimTableCallback(Table_80089904 *pTable, unsigned short key, void *pRecord, AnimChannel_t *pEntries,
                Object_80039F5C *p, unsigned int phase);
int PlyrOverlayAnimPoseCallback(Table_80089904 *pTable, unsigned short key, void *pRecord, AnimChannel_t *pEntries,
                Object_80039F5C *p, unsigned int phase);
int PlyrOverlayAnimIndexCallback(Table_80089904 *pTable, unsigned short key, void *pRecord, AnimChannel_t *pEntries,
                Object_80039F5C *p, unsigned int phase);
int PlyrOverlayAnimCountActive(Object_80039F5C *p);
}

#endif
