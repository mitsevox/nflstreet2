#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"

/* Comparison source of fn_8010CEB8 (0x8010CEB8-0x8010CFD4) of the
   provisional cu_800EFC68 grouping. It posts message 0x44 to the player's
   state: byte 1 is 0xA0, byte 2 the top bits of the facing and byte 3 the
   player's +528 value scaled to 0..255. */

extern "C" {
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800D5A28(void);
extern float lbl_803EAF48;
extern float lbl_803EAF4C;
}

extern "C" void fn_8010CEB8(Object_80039F5C *p, int kind) {
    Message_800F01CC message;
    float value = p->mUnknown528.mUnknown0;
    float level;

    if (p->mIdBytes[3] == 1) {
        float scaled = value * (0.8f / 153.0f);

        value = scaled * p->mRatings[4];
    }
    level = value < lbl_803EAF48 ? lbl_803EAF48 : (value > lbl_803EAF4C ? lbl_803EAF4C : value);
    level *= 255.0f;
    message.mId = 0x44;
    message.mUnknown1[0] = 0xA0;
    message.mUnknown1[1] = p->mMotion.mFacing >> 17;
    message.mUnknown1[2] = level < 0.0f ? 0 : (int)(level > 255.0f ? 255.0f : level);
    fn_800F00D4(0, p->mpState, &message, p);
    if (kind == 11) {
        fn_800D5A28();
    }
}
