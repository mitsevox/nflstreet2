#ifndef GAME_RECORD_800DB60C_H
#define GAME_RECORD_800DB60C_H

#include "game/Object_80039F5C.h"

/* Record passed as the first argument of PlayerActionAnimPitchTryStart and PlayerActionAnimArmPitch.
   The accessed prefix is declared; the original full size is not established. */
struct Record_800DB60C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    char mUnknown2[2];
    float mUnknown4;
    float mUnknown8;
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
};

extern "C" {
void PlayerActionAnimPitchTryStart(Record_800DB60C *pRecord, Object_80039F5C *p);
}

#endif
