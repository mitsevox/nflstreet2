#ifndef GAME_FRAME_800DF7CC_H
#define GAME_FRAME_800DF7CC_H

struct Actor_801C009C;

/* 48-byte frame record returned by fn_801C029C: index 0 gives the record
   Actor +0x18 points to, index n the (n-1)th record of the array Actor +0x1C
   points to. */
struct Frame_800DF7CC {
    unsigned int mUnknown0;
    char mUnknown4[10]; unsigned short mUnknown14;
    char mUnknown16[3]; unsigned char mUnknown19;
    unsigned int mUnknown20; char mUnknown24[18]; unsigned short mUnknown42;
    unsigned char mUnknown44[4];
};

/* The callers extend the index to 16 bits (clrlwi r4,r29,16 at 0x800AA3AC). */
extern "C" Frame_800DF7CC *fn_801C029C(Actor_801C009C *pActor, unsigned short index);

#endif
