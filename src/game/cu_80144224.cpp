#include "game/fn_80238174.h"

/* 0x1C-byte header saved and restored by the 'scol' stream callbacks. */
struct Header_803ECA0C {
    void *mpEntries;
    int mEntryCount;
    int mUnknown8;
    int mPairCount;
    int mUnknown10;
    void *mpPairs[2];
};

/* Eight-byte state allocated through fn_80238174 under the id 'scol'. */
struct State_803ECA0C {
    Header_803ECA0C *mpHeader;
    int *mpValues;
};

extern "C" {
int fn_80143F40(void *p, int value);
int fn_80143F8C(void *p, int value);
int fn_80143FE0(void *p, void *q);
int fn_80144144(void *p, void *pBuffer);
int fn_8014421C(void *p, void *pBuffer);

static State_803ECA0C *lbl_803ECA0C;

/* Size of the saved image: the state, then the header, entries, both pair arrays and the values. */
int fn_80144224(void *p)
{
    if (lbl_803ECA0C->mpValues != 0) {
        Header_803ECA0C *pHeader = lbl_803ECA0C->mpHeader;

        return sizeof(State_803ECA0C) + sizeof(Header_803ECA0C) + pHeader->mEntryCount * 0x30 + pHeader->mPairCount * 0x30 * 2 + pHeader->mEntryCount * 4;
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

Header_803ECA0C *fn_801442F0(void)
{
    return lbl_803ECA0C->mpHeader;
}
}
