#include "game/Class_802A56E8.h"

class Class_802A17A8 : public Class_802A56E8 {
public:
    unsigned char mUnknown4;
};

extern "C" {
int fn_80155384(Class_802A17A8 *p)
{
    return p->mUnknown4;
}

void fn_8015538C(Class_802A17A8 *p, int team)
{
    p->mUnknown4 = team;
}

int fn_80155394(Class_802A17A8 *p, int team)
{
    return 1;
}
}
