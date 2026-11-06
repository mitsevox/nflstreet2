/* Registers the collision types (players, the ball and others) with their per-frame update
   callbacks, and removes them again. */

#include "game/Collide.h"

struct CollTypeDef_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    CollideUpdateFunc mpUnknown4;
};

extern "C" {
void fn_8003A628(CollideObject_t *pRecord);
void BallUpdateCollRecord(CollideObject_t *pRecord);

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
        CollideRegisterType(_CollTypes_Defs[i].mUnknown0, _CollTypes_Defs[i].mUnknown1, _CollTypes_Defs[i].mpUnknown4);
    }
}

void CollTypesUnregister()
{
    unsigned char i;

    for (i = 0; i < 6; i++) {
        CollideUnregisterType(_CollTypes_Defs[i].mUnknown0);
    }
}
}
