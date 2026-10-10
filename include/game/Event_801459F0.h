#ifndef GAME_EVENT_801459F0_H
#define GAME_EVENT_801459F0_H

#include "game/cu_801444D8.h"

struct Object_80039F5C;

/* One 0x60-byte entry of the pool at lbl_803EB24C. */
struct Event_801459F0 {
    int mType;
    unsigned char mUnknown04;
    float (*mUnknown08)[4][4];
    Object_80039F5C *mUnknown0C;
    void *mUnknown10;
    int mUnknown14;
    Object_80144CE0 *mUnknown18;
    int mUnknown1C;
    float mUnknown20[4][4];
};

extern "C" {
void fn_80145314(Event_801459F0 *pEvent);
void fn_801454DC(Event_801459F0 *pEvent);
void fn_801455F8(Event_801459F0 *pEvent);
void fn_80145798(Event_801459F0 *pEvent);
void fn_801458C8(Event_801459F0 *pEvent);
}

#endif
