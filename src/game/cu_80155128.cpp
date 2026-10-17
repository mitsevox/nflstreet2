#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/fn_800B65A0.h"

struct Rules_80155128 {
    char mUnknown0[8];
    Block_80170E64 *mpUnknown8[2][2];
    unsigned char mUnknown24[2][2];
};

class Class_802A27F0 : public Class_80148A58 {
public:
    Rules_80155128 *mpUnknown1C;
};

extern "C" {
unsigned char fn_8007AFDC(int team);

Rules_80155128 *fn_80155128(Class_80148A58 *p)
{
    return static_cast<Class_802A27F0 *>(p)->mpUnknown1C;
}

int fn_80155130(Class_80148A58 *p, int team, unsigned char index)
{
    int color = 255;

    if (fn_800B65A0(team) != 255) {
        if (fn_8007AFDC(team) == 2) {
            Object_80039F5C *pPlayer = fn_80039F5C(team, index);
            Rules_80155128 *pRules = static_cast<Class_802A27F0 *>(p)->mpUnknown1C;

            if (pRules->mpUnknown8[team][index] != pPlayer->mpUnknown4) {
                color = pRules->mUnknown24[team][index ^ 1];
            } else {
                color = pRules->mUnknown24[team][index];
            }
        } else {
            color = fn_800B65A0(team);
        }
    }
    return color;
}
}
