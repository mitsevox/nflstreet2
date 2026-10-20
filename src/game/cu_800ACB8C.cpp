#include "game/Object_80039F5C.h"
#include "game/Block_800AD634.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80064864.h"
#include "game/fn_800B65A0.h"

extern "C" {
unsigned int fn_800ABDA4(int team);
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);
extern Block_800AD634 *lbl_803EAAD4;
}

extern float lbl_803EAABC;

extern "C" float fn_800ACB8C(int team)
{
    float result;

    switch (fn_800ABDA4(team)) {
    case 0:
        result = lbl_803EAABC * 0.5f;
        break;
    case 1:
        result = 0.25f;
        break;
    case 2:
        result = 0.12f;
        break;
    default:
        result = 1.0f;
        break;
    }
    return result;
}

extern float lbl_803EAAC8;

extern "C" short fn_800ACC80(Object_80039F5C *p, short value)
{
    short result;

    if (fn_800ABDA4(p->mIdBytes[2]) == 0) {
        result = (short)(value * lbl_803EAAC8);
    } else {
        result = value;
    }
    return result;
}

extern unsigned short lbl_803EAACC[3];

extern "C" int fn_800ACD04(Object_80039F5C *p)
{
    int team = p->mIdBytes[2];
    int flag = 0;
    int degrees;

    if (fn_800B65A0(team) != 255) {
        team ^= 1;
        flag = 1;
    }
    switch (fn_800ABDA4(team)) {
    case 0:
        if (flag != 0) {
            degrees = lbl_803EAACC[0];
        } else {
            degrees = lbl_803EAACC[2];
        }
        break;
    case 2:
        if (flag != 0) {
            degrees = lbl_803EAACC[2];
        } else {
            degrees = lbl_803EAACC[0];
        }
        break;
    case 1:
    default:
        degrees = lbl_803EAACC[1];
        break;
    }
    return (int)(degrees * 46603.378f);
}

extern "C" void fn_800ACDE4(Object_80039F5C *p, float *pA, float *pB)
{
    int team = p->mIdBytes[2];
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        team ^= 1;
        flag = 1;
    }
    if (flag == 0) {
        switch (fn_800ABDA4(team)) {
        case 0:
            *pA *= 0.5f;
            *pB *= 2.0f;
            break;
        case 1:
            break;
        case 2:
            *pB *= 0.5f;
            break;
        }
    }
}

extern "C" void fn_800ACE90(Object_80039F5C *p, int *pValue)
{
    int team = p->mIdBytes[2];
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        flag = 1;
    }
    if (flag == 0) {
        switch (fn_800ABDA4(team)) {
        case 0:
        case 1:
            break;
        case 2:
            *pValue = (int)(*pValue * 0.5f);
            break;
        }
    }
}

extern "C" short fn_800ACFFC(int team, short value)
{
    if (value > 0) {
        switch (fn_800ABDA4(team)) {
        case 0:
            if (fn_800B65A0(team) == 255) {
                value = (short)(value * 0.5f);
            }
            break;
        case 1:
            break;
        case 2:
            if (fn_800B65A0(team) == 255) {
                value = (short)(value * 1.15f);
            }
            break;
        }
    }
    return value;
}

extern "C" float fn_80237260(int stream);

extern "C" float fn_800AD168(int team, float value)
{
    switch (fn_800ABDA4(team)) {
    case 0:
        value -= fn_80237260(0) * 3.0f;
        break;
    case 1:
        value -= fn_80237260(0) * 2.0f;
        break;
    case 2:
        value -= fn_80237260(0) * 0.0f;
        break;
    }
    if (value < 0.0f) {
        value = 0.0f;
    }
    return value;
}

extern "C" float fn_800AD204(int team, int value)
{
    float result = value;
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        flag = 1;
        team = team == 0;
    }
    switch (fn_800ABDA4(team)) {
    case 0:
        if (flag != 0) {
            result += 168.3f;
        } else {
            result += 63.75f;
        }
        break;
    case 1:
    case 2:
    default:
        result += 63.75f;
        break;
    }
    if (result > 255.0f) {
        result = 255.0f;
    }
    return result * (1.0f / 255.0f);
}

extern "C" void fn_800AD31C(float dt)
{
    Block_800AD634 *p = lbl_803EAAD4;

    if (p != 0) {
        if (p->mUnknownC <= 0.0f) {
            fn_8002C9A8(lbl_803EA368, 5, 0);
            p->mUnknown8 = 0;
            fn_800655D0();
        } else {
            p->mUnknownC -= dt;
        }
        p->mUnknownC = p->mUnknownC < 0.0f ? 0.0f : p->mUnknownC;
    }
}
