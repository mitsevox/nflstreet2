#ifndef GAME_PLAYBOOKTEAM_H
#define GAME_PLAYBOOKTEAM_H

#include "game/fn_800670B4.h"

struct Vec2_t {
    float mX;
    float mY;
};

/* One 0xF04-byte state block; PlayBookSelectAudible, PlayBookSaveSelection, PlayBookRestoreSelection and
   PlayBookSetSelection copy it whole. */
struct PlayBookSel_t {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned int mUnknownC;
    unsigned char mUnknown10;
    Object_800670B4 mUnknown14;
    Record_80067338 mUnknownCF8;
};

/* One of the two 0x6974-byte entries indexed by the team argument. */
struct PlayBookTeam_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
    unsigned int mUnknown14;
    unsigned int mUnknown18;
    unsigned int mUnknown1C;
    PlayBookSel_t mUnknown20;
    PlayBookSel_t mUnknownF24;
    PlayBookSel_t mUnknown1E28;
    PlayBookSel_t mUnknown2D2C[4];
    Vec2_t mUnknown693C[7];
};

#endif
