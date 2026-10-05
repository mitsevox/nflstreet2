#include <string.h>

#include "game/cu_8003EC04.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"

/* Eight-byte state allocated through fn_80238174 under the id 'scol'. */
struct State_803ECA0C {
    Set_8003EE6C *mpSet;
    int *mpValues;
};

extern "C" {
int fn_801D34D0(void *pDest, int size, int value, int width);
int fn_80238278(const void *p, int size, int seed);

int fn_80143F40(void *p, int value);

static int lbl_803EB220 = 0;
static State_803ECA0C *lbl_803ECA0C;

#if defined(DECOMP_COMPARE)
int fn_80143F40(void *p, int value)
{
    State_803ECA0C *pState = (State_803ECA0C *)p;

    fn_801D34D0(pState, sizeof(State_803ECA0C), 0, 4);
    lbl_803EB220 = 0;
    pState->mpSet = 0;
    pState->mpValues = 0;
    return 0;
}
#endif

int fn_80143F8C(void *p, int value)
{
    State_803ECA0C *pState = (State_803ECA0C *)p;

    if (pState->mpValues != 0) {
        fn_8003EF5C(pState->mpSet);
        fn_801D2BD0(pState->mpValues);
    }
    pState->mpValues = 0;
    lbl_803EB220 = 0;
    return 0;
}

int fn_80143FE0(void *p, void *q)
{
    State_803ECA0C *pState = (State_803ECA0C *)p;
    State_803ECA0C *pOther = (State_803ECA0C *)q;
    Set_8003EE6C *pSet = pState->mpSet;
    int result;

    if (pOther != 0) {
        Set_8003EE6C *pOtherSet = pOther->mpSet;

        result = memcmp(pState, pOther, sizeof(State_803ECA0C));
        if (pState->mpValues != 0) {
            result |= memcmp(pSet, pOtherSet, sizeof(Set_8003EE6C));
            result |= memcmp(pSet->mpUnknown0, pOtherSet->mpUnknown0, pSet->mUnknown4 * sizeof(Record_8003EC04));
            result |= memcmp(pSet->mpUnknown14[0], pOtherSet->mpUnknown14[0], pSet->mUnknownC * sizeof(Sub_8003EC54));
            result |= memcmp(pSet->mpUnknown14[1], pOtherSet->mpUnknown14[1], pSet->mUnknownC * sizeof(Sub_8003EC54));
            result |= memcmp(pState->mpValues, pOther->mpValues, pSet->mUnknown4 * 4);
        }
    } else {
        result = fn_80238278(pState, sizeof(State_803ECA0C), 0);
        if (pState->mpValues != 0) {
            result = fn_80238278(pSet, sizeof(Set_8003EE6C), result);
            result = fn_80238278(pSet->mpUnknown0, pSet->mUnknown4 * sizeof(Record_8003EC04), result);
            result = fn_80238278(pSet->mpUnknown14[0], pSet->mUnknownC * sizeof(Sub_8003EC54), result);
            result = fn_80238278(pSet->mpUnknown14[1], pSet->mUnknownC * sizeof(Sub_8003EC54), result);
            result = fn_80238278(pState->mpValues, pSet->mUnknown4 * 4, result);
        }
    }
    return result;
}

int fn_80144144(void *p, void *pBuffer)
{
    State_803ECA0C *pState = (State_803ECA0C *)p;
    Set_8003EE6C *pSet = pState->mpSet;

    memcpy(pBuffer, p, sizeof(State_803ECA0C));
    pBuffer = (char *)pBuffer + sizeof(State_803ECA0C);
    if (pState->mpValues != 0) {
        memcpy(pBuffer, pSet, sizeof(Set_8003EE6C));
        pBuffer = (char *)pBuffer + sizeof(Set_8003EE6C);
        memcpy(pBuffer, pSet->mpUnknown0, pSet->mUnknown4 * sizeof(Record_8003EC04));
        pBuffer = (char *)pBuffer + pSet->mUnknown4 * sizeof(Record_8003EC04);
        for (short i = 0; i < 2; i++) {
            memcpy(pBuffer, pSet->mpUnknown14[i], pSet->mUnknownC * sizeof(Sub_8003EC54));
            pBuffer = (char *)pBuffer + pSet->mUnknownC * sizeof(Sub_8003EC54);
        }
        memcpy(pBuffer, pState->mpValues, pSet->mUnknown4 * 4);
    }
    return 1;
}

int fn_8014421C(void *p, void *pBuffer)
{
    return 1;
}

/* Size of the saved image: the state, then the record pool, its records, both sub-record arrays and the values. */
int fn_80144224(void *p)
{
    if (lbl_803ECA0C->mpValues != 0) {
        Set_8003EE6C *pSet = lbl_803ECA0C->mpSet;

        return sizeof(State_803ECA0C) + sizeof(Set_8003EE6C) + pSet->mUnknown4 * sizeof(Record_8003EC04) +
               pSet->mUnknownC * sizeof(Sub_8003EC54) * 2 + pSet->mUnknown4 * 4;
    }
    return sizeof(State_803ECA0C);
}

void fn_80144264(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803ECA0C, sizeof(State_803ECA0C), 0, 0x73636F6C);

    fn_80238234(pHandle, fn_80143F40, fn_80143F8C, 0, fn_80143FE0);
    fn_80238248(pHandle, fn_80144144, fn_80144224, fn_8014421C);
    fn_802381E0(pHandle);
}

Set_8003EE6C *fn_801442F0(void)
{
    return lbl_803ECA0C->mpSet;
}
}
