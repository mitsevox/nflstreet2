/* Registers the collision types (players, the ball and others) with their per-frame update
   callbacks, and removes them again. */

#include "game/cu_8003EC04.h"

struct CollTypeDef_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    Callback_802DCF9C mpUnknown4;
};

extern "C" {
void fn_8003A628(Record_8003EC04 *pRecord);
void BallUpdateCollRecord(Record_8003EC04 *pRecord);

static CollTypeDef_t _CollTypes_Defs[6] = {
    { 0, 11, fn_8003A628 },
    { 1, 1, BallUpdateCollRecord },
    { 2, 4, 0 },
    { 3, 1, 0 },
    { 4, 0, 0 },
    { 5, 1, 0 },
};

void CollTypesRegister()
{
    unsigned char i;

    for (i = 0; i < 6; i++) {
        fn_8003EDD8(_CollTypes_Defs[i].mUnknown0, _CollTypes_Defs[i].mUnknown1, _CollTypes_Defs[i].mpUnknown4);
    }
}

void CollTypesUnregister()
{
    unsigned char i;

    for (i = 0; i < 6; i++) {
        fn_8003EE00(_CollTypes_Defs[i].mUnknown0);
    }
}
}
