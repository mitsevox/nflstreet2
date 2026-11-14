#ifndef GAME_PLYRSLOT_H
#define GAME_PLYRSLOT_H

#include "engine/AnimChannel.h"
#include "game/Object_80039F5C.h"

/* Player slot of the array that _PlyrMgr_pManager points to: the shared player
   object, then the main channel list and records with its 404-byte
   sequence state (player +808/+812/+804 point at them), then the two
   per-side lists, record pairs and states. Padded to the 5336-byte stride
   used by every walk of the array. */
struct PlyrSlot_t {
    Object_80039F5C mObject;
    AnimHeader_t mUnknown3096;
    AnimChannel_t mUnknown3108[4];
    char mUnknown3604[404];
    AnimHeader_t mUnknown4008[2];
    AnimChannel_t mUnknown4032[2][2];
    char mUnknown4528[2][404];
};

#endif
