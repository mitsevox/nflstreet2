#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"

extern "C" {
extern float lbl_803EAF48;
extern float lbl_803EAF4C;
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void StyleTrackerFinishRun(void);
}

/* Posts message 68 to the player's queue with the facing and a 0-255
   effort level taken from the move speed (scaled by rating 4 for a player
   whose id byte 3 is 1); kind 11 also finishes the running-style run. */
extern "C" void fn_8010CEB8(Object_80039F5C *p, int kind)
{
    Message_800F01CC message;
    float speed = p->mUnknown528.mUnknown0;
    float level;

    if (p->mIdBytes[3] == 1) {
        speed = speed * 0.0052287583f * p->mRatings[4];
    }
    level = speed < lbl_803EAF48 ? lbl_803EAF48 : (speed > lbl_803EAF4C ? lbl_803EAF4C : speed);
    level *= 255.0f;
    message.mId = 68;
    message.mUnknown1[0] = 160;
    message.mUnknown1[1] = p->mMotion.mFacing >> 17;
    message.mUnknown1[2] = level < 0.0f ? 0 : (unsigned char)(level > 255.0f ? 255.0f : level);
    fn_800F00D4(0, p->mpState, &message, p);
    if (kind == 11) {
        StyleTrackerFinishRun();
    }
}
