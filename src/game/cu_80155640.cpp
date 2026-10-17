#include "game/Class_80297BF8.h"

class Class_802A18C8 : public Class_80297BF8 {
};

extern "C" {
int fn_80054568(void);

void fn_80155640(Class_802A18C8 *p, float dt)
{
    if (fn_80054568()) {
        p->Class_80297BF8::vfn_04(dt);
    }
}

void fn_801556CC(Class_802A18C8 *p)
{
}
}
