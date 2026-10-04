#ifndef GAME_MESSAGE_800F01CC_H
#define GAME_MESSAGE_800F01CC_H

/* 4-byte message cleared by fn_801C1F94 and posted to a player's queue
   through fn_800F01CC, fn_800F03D8 or fn_800F053C. */
struct Message_800F01CC {
    unsigned char mId;
    unsigned char mUnknown1[3];
};

#endif
