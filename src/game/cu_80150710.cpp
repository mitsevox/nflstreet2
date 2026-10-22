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
