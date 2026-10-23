#ifndef GAME_PLAYER_800ADA1C_H
#define GAME_PLAYER_800ADA1C_H

#include "engine/Record_800D81C8.h"
#include "game/Object_80039F5C.h"

/* Player slot: the shared player object followed by the two per-side
   sequence states, channel pairs and the 404-byte state blocks that
   fn_801BE068 and fn_801BE60C take. Only the accessed tail is declared. */
struct Player_800ADA1C {
    Object_80039F5C mObject;
    char mUnknown3096[912];
    Object_801BA03C mUnknown4008[2];
    Record_800D81C8 mUnknown4032[2][2];
    char mUnknown4528[2][404];
};

#endif
