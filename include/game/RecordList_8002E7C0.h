#ifndef GAME_RECORDLIST_8002E7C0_H
#define GAME_RECORDLIST_8002E7C0_H

#include "game/Object_80039F5C.h"

/* Timing block at Record_8002E7C0 +0x04: filled by fn_8002D338 and the
   replay script, applied by fn_8002E75C. */
struct Timer_8002E7C0 {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
};

/* One view of a record (+0x1C and +0x5C). */
struct View_8002E7C0 {
    float mUnknown00[3];
    float mUnknown0C[3];
    float mUnknown18;
    float mUnknown1C[3];
    float mUnknown28[3];
    int mUnknown34;
    Object_80039F5C *mUnknown38;
    int mUnknown3C;
};

/* One 0x9C-byte entry of RecordList_8002E7C0. */
struct Record_8002E7C0 {
    int mUnknown00;
    Timer_8002E7C0 mUnknown04;
    int mUnknown18;
    View_8002E7C0 mUnknown1C;
    View_8002E7C0 mUnknown5C;
};

/* The replay camera's script records (camera +0x128), 0x588 bytes. */
struct RecordList_8002E7C0 {
    Record_8002E7C0 mUnknown000[9];
    int mUnknown57C;
    int mUnknown580;
    int mUnknown584;
};

extern "C" {
Record_8002E7C0 *fn_8002E7C0(RecordList_8002E7C0 *pList);
int fn_8002E7D0(RecordList_8002E7C0 *pList);
}

#endif
