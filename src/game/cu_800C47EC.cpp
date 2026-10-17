#include "game/Object_80039F5C.h"
#include "game/Level_80054130.h"
#include "game/fn_801C1F94.h"

extern "C" {
int fn_800C4E18(Object_80039F5C *p);

extern float lbl_802DA2F4[14];
extern float lbl_802DA364[14];
extern float lbl_802DA63C[14];
}

extern "C" void fn_800C47EC(Level_80054130 *pLevel)
{
    unsigned int counts[14];
    unsigned int i;
    int kind;

    fn_801C1F94(counts, 0, sizeof(counts));
    for (i = 0; i < pLevel->mUnknown24; i++) {
        counts[pLevel->mUnknown28[i].mUnknown8]++;
    }
    for (kind = 0; kind < 14; kind++) {
        lbl_802DA63C[kind] = (float)counts[kind] / (float)pLevel->mUnknown24;
    }
}

extern "C" float fn_800C49EC(float value)
{
    float sum = 0.0f;
    int i;

    for (i = 0; i < 14; i++) {
        sum += lbl_802DA63C[i] * lbl_802DA2F4[i];
    }
    return sum * value;
}

extern "C" float fn_800C4A2C(Object_80039F5C *p)
{
    float result = 0.0f;

    if (p->mpUnknown780 != 0) {
        int kind = fn_800C4E18(p);

        result = lbl_802DA364[kind];
    }
    return result;
}

