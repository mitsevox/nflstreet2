#include "game/cu_8003EC04.h"
#include "game/fn_80238174.h"

/* Eight-byte state allocated through fn_80238174 under the id 'scol'. */
struct State_803ECA0C {
    Set_8003EE6C *mpSet;
    int *mpValues;
};

extern "C" {
int fn_80143F40(void *p, int value);
int fn_80143F8C(void *p, int value);
int fn_80143FE0(void *p, void *q);
int fn_80144144(void *p, void *pBuffer);
int fn_8014421C(void *p, void *pBuffer);

static State_803ECA0C *lbl_803ECA0C;

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
