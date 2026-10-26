#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

extern "C" {
Message_800F01CC *fn_800AEE20(Object_80039F5C *p);
Point_8017886C fn_80177FFC(int team);
float fn_80178A08(void);
float fn_80178A44(void);
}

extern "C" void fn_800E3DCC(Object_80039F5C *p, Point_8017886C *pOut)
{
    Point_8017886C target;
    Point_8017886C goal;
    Message_800F01CC *pMessage;

    target.mX = target.mY = 0.0f;
    pMessage = fn_800AEE20(p);
    if (pMessage) {
        if (pMessage->mId == 40) {
            goal = fn_80177FFC(p->mIdBytes[2]);
            switch (pMessage->mUnknown1[0]) {
            case 1:
                target.mX = goal.mX - 5.0f;
                target.mY = goal.mY + 8.0f;
                break;
            case 2:
                target.mX = goal.mX + 5.0f;
                target.mY = goal.mY + 8.0f;
                break;
            case 3:
                target.mX = goal.mX - 7.0f;
                target.mY = goal.mY + 8.0f;
                break;
            case 0:
            case 4:
                target.mX = goal.mX;
                target.mY = goal.mY + 8.0f;
                break;
            case 5:
                target.mX = goal.mX + 7.0f;
                target.mY = goal.mY + 8.0f;
                break;
            }
            target.mX = CLAMP(target.mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
            target.mY = CLAMP(target.mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
            *pOut = target;
        } else if (pMessage->mId == 92) {
            goal = fn_80177FFC(p->mIdBytes[2]);
            switch (pMessage->mUnknown1[0]) {
            case 0:
                target.mX = goal.mX;
                target.mY = goal.mY + 3.0f;
                break;
            case 1:
                target.mX = goal.mX - 6.0f;
                target.mY = goal.mY + 3.0f;
                break;
            case 2:
                target.mX = goal.mX + 6.0f;
                target.mY = goal.mY + 3.0f;
                break;
            }
            target.mX = CLAMP(target.mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
            target.mY = CLAMP(target.mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
            *pOut = target;
        }
    }
}
