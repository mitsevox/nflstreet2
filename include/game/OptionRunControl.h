#ifndef GAME_OPTION_RUN_CONTROL_H
#define GAME_OPTION_RUN_CONTROL_H

#include "game/Object_80039F5C.h"
#include "game/Directions_8012430C.h"

/* Eight bytes at +56 of OptionRunControl_t, passed to CarrierRunTryMoves as one
   block. */
struct OptionRunMove_t {
    short mUnknown0;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    char mUnknown7[1];
};

struct OptionRunControl_t {
    int mUnknown0;
    Directions_8012430C mValues;
    float mUnknown36;
    float mUnknown40;
    int mUnknown44;
    unsigned char mUnknown48;
    signed char mUnknown49;
    unsigned char mUnknown50;
    char mUnknown51[1];
    unsigned char mUnknown52;
    char mUnknown53[1];
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    OptionRunMove_t mUnknown56;
    int mUnknown64;
    int mUnknown68;
    int mUnknown72;
    int mUnknown76;
    unsigned char mUnknown80;
    unsigned char mUnknown81;
    char mUnknown82[6];
};

extern "C" {
int CarrierRunFindLeadBlocker(Object_80039F5C *p);
void CarrierRunKeepInBounds(Object_80039F5C *p, OptionRunControl_t *pControl, int a);
void CarrierRunTryMoves(Object_80039F5C *p, OptionRunControl_t *pControl, OptionRunMove_t *pBlock);
void CarrierRunSetSpeed(Object_80039F5C *p, OptionRunControl_t *pControl, int a);
void CarrierRunResetControl(Object_80039F5C *p, OptionRunControl_t *pControl);
}

#endif
