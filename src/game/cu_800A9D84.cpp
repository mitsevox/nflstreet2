#include "game/Object_8017886C.h"
#include "game/Block_8030F42C.h"
#include "game/fn_80177FE0.h"

extern "C" {
float fn_80178A2C(void);

extern Block_8030F42C lbl_8030F42C;
}

extern "C" void fn_800A9D84(Point_8017886C *pOut)
{
    int midRound = lbl_8030F42C.mUnknown0 >= 3 && lbl_8030F42C.mUnknown0 <= 5;
    int first = lbl_8030F42C.mUnknown4 == 0;
    Point_8017886C pos = fn_80177FE0();
    float y = pos.mY;
    float d;

    if (!midRound || first) {
        pOut->mY = y;
    }
    pOut->mX = pos.mX;
    if (first) {
        return;
    }
    d = fn_80178A2C() - y;
    switch (lbl_8030F42C.mUnknown0) {
    case 5:
        if (d > 6.0f) {
            if (lbl_8030F42C.mUnknown4 > 2) {
                pOut->mY += d - 6.0f;
            }
        } else if (d < 0.75f) {
            pOut->mY -= 0.75f - d;
        }
        break;
    case 4:
        if (d > 9.0f) {
            pOut->mY += d - 9.0f;
        } else if (d < 3.5f) {
            pOut->mY -= 3.5f - d;
        }
        break;
    case 3:
        if (d > 3.5f) {
            pOut->mY += d - 3.5f;
        }
        break;
    case 7:
        if (d < 10.33f) {
            if (lbl_8030F42C.mUnknown4 > 4) {
                pOut->mY -= 10.33f - d;
            } else if (lbl_8030F42C.mUnknown4 > 3) {
                pOut->mY -= (10.33f - d) * 0.5f;
            }
        }
        break;
    case 6:
        if (d < 1.0f) {
            pOut->mY -= 1.0f - d;
        }
        break;
    }
}
