#include "game/fn_80177FE0.h"

extern "C" {
float fn_800A32B4(void);
float fn_802373C8(int selector, float first, float last);

void fn_8014FFC4(Point_8017886C *p)
{
    float width = fn_800A32B4();
    float originY = fn_80177FE0().mY;
    if (!(width <= 6.0f)) {
        width = 6.0f;
    }
    p->mY = fn_802373C8(0, originY + 20.0f, originY + 40.0f);
    p->mX = fn_802373C8(0, -width, width);
}
}
