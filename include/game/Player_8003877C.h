#ifndef GAME_PLAYER_8003877C_H
#define GAME_PLAYER_8003877C_H

#include "engine/Record_800D81C8.h"
#include "game/Object_80039F5C.h"

/* Player slot of the array that lbl_803EA3F8 points to: the shared player
   object, then the main channel list and records with its 404-byte
   sequence state (player +808/+812/+804 point at them), then the two
   per-side lists, record pairs and states. Padded to the 5336-byte stride
   used by every walk of the array. */
struct Player_8003877C {
    Object_80039F5C mObject;
    Object_801BA03C mUnknown3096;
    Record_800D81C8 mUnknown3108[4];
    char mUnknown3604[404];
    Object_801BA03C mUnknown4008[2];
    Record_800D81C8 mUnknown4032[2][2];
    char mUnknown4528[2][404];
};

#endif
