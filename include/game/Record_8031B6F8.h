#ifndef GAME_RECORD_8031B6F8_H
#define GAME_RECORD_8031B6F8_H

#include "game/cu_801444D8.h"

/* One 0x24-byte record of the six-entry table written to the replay stream. */
struct Record_8031B6F8 {
    int mId;
    float mPos[3];
    float mRot[4];
    Source_80144CE0 *mpSource;
};

extern "C" void fn_8014516C(Record_8031B6F8 record);

#endif
