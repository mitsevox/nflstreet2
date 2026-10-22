#include "game/Class_802A2B68.h"
#include "game/Object_80039F5C.h"

extern "C" {
Object_80039F5C *fn_8003AC84(int id);
Block_8014F104 *fn_8014F104(Class_80148A58 *p);
unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer);

int fn_8014FDD0(Class_802A2B68 *p, int kind, int team, int index,
               Object_80039F5C *pPlayer, int threshold, int mode)
{
    int original = p->vfn_30(kind, team, index, pPlayer);
    int result = 0;
    bool found = false;
    for (unsigned char t = 0; t <= 1; t++) {
        for (unsigned char i = 0; i < 6; i++) {
            Object_80039F5C *pCandidate = fn_80039F5C(t, i);
            if (pCandidate->mUnknown9[2] != 0) {
                if (!found) {
                    result = p->vfn_30(kind, t, i, pCandidate);
                    found = true;
                } else {
                    int value = p->vfn_30(kind, t, i, pCandidate);
                    if ((mode == 0 && value > result) || (mode == 1 && value < result)) {
                        result = value;
                    }
                }
            }
        }
    }
    if ((mode == 0 && result > threshold) || (mode == 1 && result < threshold)) {
        return original == result;
    }
    return 0;
}

int fn_8014FF34(Class_802A2B68 *p)
{
    int result = 0;
    for (unsigned int i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8 != 255) {
            result = fn_8014F474(p, fn_8003AC84(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0));
            break;
        }
    }
    return result;
}
}
