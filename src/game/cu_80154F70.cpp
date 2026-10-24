#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"

class Class_802A27F0 : public Class_80148A58 {
public:
    char mUnknown1C[8];
    unsigned char mUnknown24;
};

extern "C" {
extern int lbl_803ECA24[2];
extern const char lbl_802A0DDC[];
int fn_801C2D88(char *pText, int capacity, const char *pFormat, ...);

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

void fn_80155004(Class_802A27F0 *p, int team, int index, int kind,
                 char *pFirst, int firstLength, char *pSecond, int secondLength)
{
    Object_80039F5C *pPlayer = fn_80039F5C(team, index);
    switch (kind) {
    case 0:
        fn_801C2D88(pFirst, firstLength, "TDs");
        fn_801C2D88(pSecond, secondLength, lbl_802A0DDC,
                    p->vfn_30(2, team, index, pPlayer));
        break;
    case 1:
        fn_801C2D88(pFirst, firstLength, "Tackles");
        fn_801C2D88(pSecond, secondLength, lbl_802A0DDC,
                    p->vfn_30(1, team, index, pPlayer));
        break;
    }
}
}
