#include "game/Object_80039F5C.h"

extern "C" int fn_8011F1A4(void);

/* View of the block at player +336 used by fn_80116B98. */
struct Block_80116B98 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17[1];
    short mUnknown18;
    unsigned char mUnknown20;
};

extern "C" int fn_80116B98(Object_80039F5C *p)
{
    Block_80116B98 *pBlock = (Block_80116B98 *)&p->mUnknown336;

    pBlock->mUnknown2 = 0;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown4 = 0xC00000;
    pBlock->mUnknown12 = 0.0f;
    if (fn_8011F1A4()) {
        pBlock->mUnknown16 = 1;
        pBlock->mUnknown18 = p->mRatings[5] <= 255 ? 255 - p->mRatings[5] : 0;
    } else {
        pBlock->mUnknown16 = 0;
        pBlock->mUnknown18 = 0;
    }
    return 0;
}

