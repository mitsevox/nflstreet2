#include "game/Object_80039F5C.h"
#include "game/Level_80054130.h"
#include "game/fn_801C1F94.h"

extern "C" {
int fn_800C4E18(Object_80039F5C *p);
float fn_80237260(int stream);
int fn_800A84C0(int team);
float fn_800C4A70(Object_80039F5C *p, int index);
void fn_800E99A8(Object_80039F5C *p, int kind);
int fn_800E9B84(Object_80039F5C *p, int kind);

extern float lbl_802DA2F4[14];
extern float lbl_802DA364[14];
extern float lbl_802DA63C[14];
extern short lbl_803EABEA;
extern float lbl_803EABEC;
extern float lbl_803EABF0;
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


extern "C" int fn_800C4B6C(Object_80039F5C *p)
{
    int result = 0;
    short *pRating = &p->mRatings[0];
    float chance = fn_80237260(0) * (1.0f / 255.0f);
    float value = chance * p->mRatings[0];

    if (fn_800A84C0(p->mIdBytes[2]) != 0) {
        int kind;

        switch (p->mpState->mId) {
        case 34:
            kind = 3;
            break;
        case 35:
            kind = 4;
            break;
        default:
            kind = 5;
            break;
        }
        if (value < fn_800C4A70(p, 0)) {
            fn_800E9B84(p, kind);
            result = 1;
        } else if (value < fn_800C4A70(p, 1)) {
            fn_800E99A8(p, kind);
            result = 1;
        }
        if (result == 0 && (p->mpState->mId >= 34 && p->mpState->mId <= 36) && *pRating < lbl_803EABEA) {
            chance = fn_80237260(0);
            value = *pRating * -lbl_803EABEC / lbl_803EABEA + lbl_803EABEC;
            if (chance < value) {
                fn_800E9B84(p, kind);
                result = 1;
            } else {
                value = *pRating * -lbl_803EABF0 / lbl_803EABEA + lbl_803EABF0;
                if (chance < value) {
                    fn_800E99A8(p, kind);
                    result = 1;
                }
            }
        }
    }
    return result;
}
