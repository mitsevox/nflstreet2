#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"

struct Record_8011F4E0;

extern "C" {
int fn_80178308(void);
int fn_8011F1A4(void);
Record_8011F4E0 *fn_8011F4E0(void);
void *fn_8011F4EC(void);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_8009E9EC(Object_80039F5C *p, unsigned char index, Point_8017886C *pOut);
void fn_80117AA4(Object_80039F5C *p, Point_8017886C *pOut, float *pValue);
}

/* View of the block at player +336 used by fn_801180FC. */
struct Block_801180FC {
    char mUnknown0[8];
    int mUnknown8;
    float mUnknown12;
};

extern "C" void fn_801180FC(Object_80039F5C *p)
{
    Block_801180FC *pBlock;
    Point_8017886C origin;
    Point_8017886C spot;
    Point_8017886C target;

    fn_80178308();
    pBlock = (Block_801180FC *)&p->mUnknown336;
    origin = fn_80177FE0();
    fn_8011F4E0();
    fn_8009E9EC(p, p->mpState->mUnknown1 + 14, &spot);
    fn_8011F4EC();
    fn_80117AA4(p, &target, &pBlock->mUnknown12);
    fn_80227690(&target, &target, &p->mMotion.mPos);
    pBlock->mUnknown8 = fn_801CFE40(target.mY, target.mX);
    if ((p->mMotion.mUnknown28 != 0.0f && fn_802270A4(&target) < 0.5f)
        || (p->mMotion.mUnknown28 == 0.0f && fn_802270A4(&target) < 1.0f)) {
        pBlock->mUnknown12 = 0.0f;
        p->mUnknown512.mUnknown0 = 0.0f;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = 0xC00000;
        p->mUnknown512.mUnknown8 = 0xC00000;
    }
}


/* View of the block at player +336 used by fn_80118210. */
struct Block_80118210 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17[1];
    short mUnknown18;
    int mUnknown20;
    unsigned char mUnknown24;
    char mUnknown25[1];
    unsigned char mUnknown26;
};

extern "C" int fn_80118210(Object_80039F5C *p)
{
    Block_80118210 *pBlock = (Block_80118210 *)&p->mUnknown336;

    pBlock->mUnknown2 = 0;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown24 = 0;
    pBlock->mUnknown26 = 0;
    pBlock->mUnknown4 = 0xC00000;
    pBlock->mUnknown12 = 0.0f;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown20 = 0;
    if (fn_8011F1A4()) {
        int range;

        pBlock->mUnknown16 = 1;
        range = 255 - p->mRatings[8];
        if (range < 0) {
            range = 0;
        }
        pBlock->mUnknown18 = fn_802372EC(0, range / 6);
    } else {
        pBlock->mUnknown16 = 0;
        pBlock->mUnknown18 = 0;
    }
    return 0;
}

