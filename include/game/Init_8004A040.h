#ifndef GAME_INIT_8004A040_H
#define GAME_INIT_8004A040_H

#include "game/FMCAPPORT.h"
#include "game/cu_80047E28.h"

/* Creation argument of fn_8004A040. */
struct Init_8004A040 {
    int mUnknown00;
    int mUnknown04;
    char mUnknown08[8];
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
};

/* Full creation record built by fn_8003D378: the Init_8004A040 header,
   model ids, a name and the 53 FMCAPPORT values read by fn_801A3588. */
struct Creation_8003D378 {
    Init_8004A040 mInit;
    int mUnknown1C;
    Ids_8015F6E8 mUnknown20;
    int mUnknown28, mUnknown2C, mUnknown30, mUnknown34;
    char mUnknown38[31];
    unsigned char mUnknown57, mUnknown58, mUnknown59, mUnknown5A, mUnknown5B;
    FMCAPPORTValues mUnknown5C;
};

#endif
