/* The Street Feats screen: builds the list of feats for the user and hands the screen each feat's
   name, text and value. */
#include "game/cu_800314E0.h"
#include <stdio.h>
#include "game/cu_8017F90C.h"

struct FeatsScreenText_t {
    int mUnknown0;
    int mUnknown4;
    char *mString;
};

struct FeatsScreenArgs_t {
    int mMode;
    FeatsScreenText_t *mName;
    FeatsScreenText_t *mText;
    int *mValue;
};

extern "C" {
static int _FeatsScreen_iCursor;

int FeatsScreenGetNextFeat(int mode, char *pName, char *pText, int *pValue)
{
    Entry_80306620 entry;

    switch (mode) {
    case 0:
    case 1:
    case 2: {
        int count = fn_8003203C();
        if (_FeatsScreen_iCursor >= count) {
            break;
        }
        fn_80032044(_FeatsScreen_iCursor, &entry);
        if (mode == 1 && _FeatsScreen_iCursor == 0) {
            sprintf(pName, "Create a User ID to get your Street Feats rolling.  Completing varying tasks will earn you Credits to spend in the Store.  Find the full list of Feats under Stats and Rewards.");
        } else {
            sprintf(pName, entry.mName);
        }
        sprintf(pText, entry.mText);
        *pValue = entry.mUnknown164;
        _FeatsScreen_iCursor++;
        return 1;
    }
    case 3:
        if (fn_80032110(&entry) == 1) {
            sprintf(pName, entry.mName);
            sprintf(pText, entry.mText);
            *pValue = entry.mUnknown164;
            return 1;
        }
        break;
    }
    return 0;
}

int FeatsScreenHandleMessage(unsigned int id, FeatsScreenArgs_t *pArgs, int a, int *pResult)
{
    switch (id) {
    case 387:
        _FeatsScreen_iCursor = 0;
        switch (pArgs->mMode) {
        case 2:
            fn_80031C28();
            break;
        case 1:
            fn_80031DC8();
            break;
        case 0:
            fn_80031EFC();
            break;
        }
        break;
    case 388:
        *pResult = FeatsScreenGetNextFeat(pArgs->mMode, pArgs->mName->mString, pArgs->mText->mString, pArgs->mValue);
        break;
    case 389:
        fn_800320B0();
        break;
    default:
        return 0;
    }
    return 1;
}
}
