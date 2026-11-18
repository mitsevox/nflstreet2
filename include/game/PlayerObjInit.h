#ifndef GAME_PLAYEROBJINIT_H
#define GAME_PLAYEROBJINIT_H

#include "game/FMCAPPORT.h"
#include "game/PlayerLook.h"

/* Creation argument of PlayerObjCreate. */
struct PlayerObjInit_t {
    short mUnknown00;
    short mUnknown02;
    int mUnknown04;
    char mUnknown08[8];
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
};

/* Full creation record built by fn_8003D378: the PlayerObjInit_t header,
   model ids, a name and the 53 FMCAPPORT values read by fn_801A3588. */
struct Creation_8003D378 {
    PlayerObjInit_t mInit;
    int mUnknown1C;
    PlayerHeadIds_t mUnknown20;
    int mUnknown28, mUnknown2C, mUnknown30, mUnknown34;
    char mUnknown38[31];
    unsigned char mUnknown57, mUnknown58, mUnknown59, mUnknown5A, mUnknown5B;
    FMCAPPORTValues mUnknown5C;
};

#endif
