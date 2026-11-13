/* Statcoll: the collision-set block of the Statcoll game module. On start it
   allocates a small state holding a collision set and a value array and
   registers the callbacks that clear, free, compare, save and size that
   state with the game-state block manager. The ball code and the per-frame
   collision update test other sets against the set it returns. */
#include <string.h>

#include "game/Collide.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"

/* Eight-byte state allocated through the block manager under the id 'scol'. */
struct StatcollState_t {
    CollideSet_t *mpSet;
    int *mpValues;
};

extern "C" {
int MemFill(void *pDest, int size, int value, int width);
int fn_80238278(const void *p, int size, int seed);

int StatcollBlockInit(void *p, int value);

static int _Statcoll_iUnused = 0;
static StatcollState_t *_Statcoll_pState;

#if defined(DECOMP_COMPARE)
int StatcollBlockInit(void *p, int value)
{
    StatcollState_t *pState = (StatcollState_t *)p;

    MemFill(pState, sizeof(StatcollState_t), 0, 4);
    _Statcoll_iUnused = 0;
    pState->mpSet = 0;
    pState->mpValues = 0;
    return 0;
}
#endif

int StatcollBlockShutdown(void *p, int value)
{
    StatcollState_t *pState = (StatcollState_t *)p;

    if (pState->mpValues != 0) {
        CollideSetDestroy(pState->mpSet);
        fn_801D2BD0(pState->mpValues);
    }
    pState->mpValues = 0;
    _Statcoll_iUnused = 0;
    return 0;
}

int StatcollBlockCompare(void *p, void *q)
{
    StatcollState_t *pState = (StatcollState_t *)p;
    StatcollState_t *pOther = (StatcollState_t *)q;
    CollideSet_t *pSet = pState->mpSet;
    int result;

    if (pOther != 0) {
        CollideSet_t *pOtherSet = pOther->mpSet;

        result = memcmp(pState, pOther, sizeof(StatcollState_t));
        if (pState->mpValues != 0) {
            result |= memcmp(pSet, pOtherSet, sizeof(CollideSet_t));
            result |= memcmp(pSet->mpUnknown0, pOtherSet->mpUnknown0, pSet->mUnknown4 * sizeof(CollideObject_t));
            result |= memcmp(pSet->mpUnknown14[0], pOtherSet->mpUnknown14[0], pSet->mUnknownC * sizeof(CollideShape_t));
            result |= memcmp(pSet->mpUnknown14[1], pOtherSet->mpUnknown14[1], pSet->mUnknownC * sizeof(CollideShape_t));
            result |= memcmp(pState->mpValues, pOther->mpValues, pSet->mUnknown4 * 4);
        }
    } else {
        result = fn_80238278(pState, sizeof(StatcollState_t), 0);
        if (pState->mpValues != 0) {
            result = fn_80238278(pSet, sizeof(CollideSet_t), result);
            result = fn_80238278(pSet->mpUnknown0, pSet->mUnknown4 * sizeof(CollideObject_t), result);
            result = fn_80238278(pSet->mpUnknown14[0], pSet->mUnknownC * sizeof(CollideShape_t), result);
            result = fn_80238278(pSet->mpUnknown14[1], pSet->mUnknownC * sizeof(CollideShape_t), result);
            result = fn_80238278(pState->mpValues, pSet->mUnknown4 * 4, result);
        }
    }
    return result;
}

int StatcollBlockSave(void *p, void *pBuffer)
{
    StatcollState_t *pState = (StatcollState_t *)p;
    CollideSet_t *pSet = pState->mpSet;

    memcpy(pBuffer, p, sizeof(StatcollState_t));
    pBuffer = (char *)pBuffer + sizeof(StatcollState_t);
    if (pState->mpValues != 0) {
        memcpy(pBuffer, pSet, sizeof(CollideSet_t));
        pBuffer = (char *)pBuffer + sizeof(CollideSet_t);
        memcpy(pBuffer, pSet->mpUnknown0, pSet->mUnknown4 * sizeof(CollideObject_t));
        pBuffer = (char *)pBuffer + pSet->mUnknown4 * sizeof(CollideObject_t);
        for (short i = 0; i < 2; i++) {
            memcpy(pBuffer, pSet->mpUnknown14[i], pSet->mUnknownC * sizeof(CollideShape_t));
            pBuffer = (char *)pBuffer + pSet->mUnknownC * sizeof(CollideShape_t);
        }
        memcpy(pBuffer, pState->mpValues, pSet->mUnknown4 * 4);
    }
    return 1;
}

int StatcollBlockRestore(void *p, void *pBuffer)
{
    return 1;
}

/* Size of the saved image: the state, then the record pool, its records, both sub-record arrays and the values. */
int StatcollBlockGetSaveSize(void *p)
{
    if (_Statcoll_pState->mpValues != 0) {
        CollideSet_t *pSet = _Statcoll_pState->mpSet;

        return sizeof(StatcollState_t) + sizeof(CollideSet_t) + pSet->mUnknown4 * sizeof(CollideObject_t) +
               pSet->mUnknownC * sizeof(CollideShape_t) * 2 + pSet->mUnknown4 * 4;
    }
    return sizeof(StatcollState_t);
}

void StatcollStart(void)
{
    void *pHandle = fn_80238174(0, (void **)&_Statcoll_pState, sizeof(StatcollState_t), 0, 0x73636F6C);

    fn_80238234(pHandle, StatcollBlockInit, StatcollBlockShutdown, 0, StatcollBlockCompare);
    fn_80238248(pHandle, StatcollBlockSave, StatcollBlockGetSaveSize, StatcollBlockRestore);
    fn_802381E0(pHandle);
}

CollideSet_t *StatcollGetSet(void)
{
    return _Statcoll_pState->mpSet;
}
}
