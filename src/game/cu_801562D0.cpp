#include "game/Class_802A56E8.h"

class Class_802A1E38 : public Class_802A56E8 {
};

struct Settings_8031BDD4 {
    char mUnknown0[32];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
extern Settings_8031BDD4 lbl_8031BDD4;

int fn_801562D0(Class_802A1E38 *p)
{
    return 0x7FFFFFFF;
}

int fn_801562DC(Class_802A1E38 *p, int team)
{
    return 0;
}

int fn_801562E4(Class_802A1E38 *p, int team)
{
    return 0;
}

int fn_801562EC(Class_802A1E38 *p)
{
    if (lbl_8031BDD4.mUnknown36 != 0) {
        return 1;
    }
    return 0;
}

int fn_80156308(Class_802A1E38 *p)
{
    return lbl_8031BDD4.mUnknown36;
}

int fn_80156314(Class_802A1E38 *p)
{
    return 0;
}
}
