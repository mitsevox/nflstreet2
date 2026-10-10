#include "game/cu_800314E0.h"
#include <stdio.h>
#include "game/cu_8017F90C.h"

struct Value_8005542C {
    int mUnknown0;
    int mUnknown4;
    char *mString;
};

struct Args_8005542C {
    int mMode;
    Value_8005542C *mName;
    Value_8005542C *mText;
    int *mValue;
};

extern "C" {
static int lbl_803EC7E8;

int fn_80055318(int mode, char *pName, char *pText, int *pValue)
{
    Entry_80306620 entry;

    switch (mode) {
    case 0:
    case 1:
    case 2: {
        int count = fn_8003203C();
        if (lbl_803EC7E8 >= count) {
            break;
        }
        fn_80032044(lbl_803EC7E8, &entry);
        if (mode == 1 && lbl_803EC7E8 == 0) {
            sprintf(pName, "Create a User ID to get your Street Feats rolling.  Completing varying tasks will earn you Credits to spend in the Store.  Find the full list of Feats under Stats and Rewards.");
        } else {
            sprintf(pName, entry.mName);
        }
        sprintf(pText, entry.mText);
        *pValue = entry.mUnknown164;
        lbl_803EC7E8++;
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

int fn_8005542C(unsigned int id, Args_8005542C *pArgs, int a, int *pResult)
{
    switch (id) {
    case 387:
        lbl_803EC7E8 = 0;
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
        *pResult = fn_80055318(pArgs->mMode, pArgs->mName->mString, pArgs->mText->mString, pArgs->mValue);
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
