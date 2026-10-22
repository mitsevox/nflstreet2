#include "game/Object_80039F5C.h"
#include "game/Class_80297BF8.h"

class Class_802A1DC8 : public Class_80297BF8 {
};

extern "C" {
int fn_80054568(void);
void fn_800AD910(int a, float b);

void fn_80150710(Class_802A1DC8 *p, float value)
{
    if (fn_80054568()) {
        p->vfn_11(value);
    }
}

void fn_80150820(Class_802A1DC8 *p)
{
}

void fn_80150824(Class_802A1DC8 *p, float value)
{
    fn_800AD910(2, value);
}
}

extern "C" {
void fn_800BCC30(Class_80297BF8 *p);
void fn_80149040(Object_80039F5C *p);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pPlayer);

void fn_8015076C(Class_802A1DC8 *p)
{
    fn_800BCC30(p);
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned short i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = fn_80039F5C(team, i);
            fn_80149040(pPlayer);
            fn_800EFE60(0, pPlayer->mpState, pPlayer);
        }
    }
}

}
