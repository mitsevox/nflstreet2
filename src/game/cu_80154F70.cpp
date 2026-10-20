#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"

class Class_802A27F0 : public Class_80148A58 {
public:
    char mUnknown1C[8];
    unsigned char mUnknown24;
};

extern "C" {
extern int lbl_803ECA24[2];

int fn_8022B7A4(int handle, unsigned int tag, int *pValue);
int fn_801499A8(Class_80148A58 *p, int kind, int team, int index, Object_80039F5C *pPlayer);

int fn_80154F70(Class_802A27F0 *p, int kind, int team, int index, Object_80039F5C *pPlayer)
{
    int value;

    if (kind == 37) {
        fn_8022B7A4(lbl_803ECA24[team], 0x7A707374, &value);
    } else {
        value = fn_801499A8(p, kind, team, index, pPlayer);
    }
    return value;
}

Object_80039F5C *fn_80154FC0(Class_802A27F0 *p, int team, int index)
{
    Object_80039F5C *result = 0;

    if (p->mUnknown24 > 1) {
        result = fn_80039F5C(team, index == 0);
    }
    return result;
}
}
