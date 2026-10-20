#include "game/Object_80039F5C.h"

extern "C" {
float fn_80237260(int stream);
int fn_800A84C0(int team);
float fn_800C4A70(Object_80039F5C *p, int index);
}

extern "C" int fn_800C4D54(Object_80039F5C *p)
{
    int result = 0;
    float chance = fn_80237260(0) * (1.0f / 255.0f);
    float value = chance * p->mRatings[0];

    if (fn_800A84C0(p->mIdBytes[2]) != 0) {
        if (value < fn_800C4A70(p, 0)) {
            result = 1;
        } else if (value < fn_800C4A70(p, 1)) {
            result = 2;
        }
    }
    return result;
}

