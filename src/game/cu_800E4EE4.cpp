#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"

/* Play record bytes as fn_800E4EE4 reads and writes them. */
struct Record_800E4EE4 {
    unsigned char mUnknown0;
    char mUnknown1[3];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
};

/* Player block at +336 as fn_800E4EE4 tests it. */
struct State_800E4EE4 {
    char mUnknown0[32];
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    char mUnknown34[42];
    unsigned int mUnknown76;
};

extern "C" {
void fn_80227690(Point_8017886C *pOut, Point_8017886C *pA, Point_8017886C *pB);
float fn_801CFB94(int angle);
void fn_800E3C30(Object_80039F5C *p);
}

extern "C" int fn_800E4EE4(Object_80039F5C *p)
{
    State_800E4EE4 *pState = (State_800E4EE4 *)&p->mUnknown336;
    Record_800E4EE4 *pRecord =
        (Record_800E4EE4 *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);

    if ((pRecord->mUnknown0 & ~0x80) == 48 && fn_800AD9B4() == 3 && (pRecord->mUnknown4 & ~0x80) == 30) {
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&p->mMotion.mPos, (Point_8017886C *)&p->mUnknown403[1]);
        float yards = pRecord->mUnknown5 >> 3;
        yards += (pRecord->mUnknown5 & 7) * (1.0f / 7.0f);
        int angle = (pRecord->mUnknown6 << 17 & 0xFE0000) - 0xC00000;
        if (angle < 0) {
            angle = 0xC00000 - (pRecord->mUnknown6 << 17 & 0xFE0000);
        }
        float distance = yards * fn_801CFB94(angle);
        yards *= (distance + delta.mY) / distance;
        if (yards < 0.0f) {
            yards = 0.0f;
        }
        pRecord->mUnknown5 = (unsigned int)yards << 3;
        pRecord->mUnknown5 += (int)((yards - (unsigned int)yards) * 7.0f);
    }
    if ((pState->mUnknown76 & 0xFFFF0000) || pState->mUnknown33) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.0f;
    }
    if (pState->mUnknown32 == 0) {
        fn_800E3C30(p);
        return 1;
    }
    return 0;
}
