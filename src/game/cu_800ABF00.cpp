#include "game/Object_80039F5C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_801BE60C.h"

extern "C" {
unsigned int fn_800ABDA4(int team);
int fn_80178308(void);
}

/* Block whose four floats at +0x18 fn_800ABF00 scales by the skill level. */
struct Block_800ABF00 {
    unsigned char mUnknown0[0x18];
    float mUnknown18;
    float mUnknown1C;
    float mUnknown20;
    float mUnknown24;
};

extern float lbl_803EAAA8;
extern float lbl_803EAAAC;
extern float lbl_803EAAB0;
extern float lbl_803EAAB4;

extern "C" void fn_800ABF00(int team, Block_800ABF00 *p)
{
    float d0;
    float d1;
    float d2;
    float d3;

    switch (fn_800ABDA4(team)) {
    case 0:
        d0 = p->mUnknown18 * lbl_803EAAA8;
        d1 = p->mUnknown1C * lbl_803EAAAC;
        d2 = p->mUnknown20 * lbl_803EAAB0;
        d3 = p->mUnknown24 * lbl_803EAAB4;
        break;
    case 1:
        d0 = p->mUnknown18 * 0.05f;
        d1 = p->mUnknown1C * 0.05f;
        d2 = p->mUnknown20 * 0.05f;
        d3 = p->mUnknown24 * 0.05f;
        break;
    case 2:
        d0 = p->mUnknown18 * 0.15f;
        d1 = p->mUnknown1C * 0.15f;
        d2 = p->mUnknown20 * 0.15f;
        d3 = p->mUnknown24 * 0.15f;
        break;
    default:
        d0 = 0.0f;
        d1 = 0.0f;
        d2 = 0.0f;
        d3 = 0.0f;
        break;
    }
    p->mUnknown18 += d0;
    p->mUnknown1C += d1;
    p->mUnknown20 += d2;
    p->mUnknown24 += d3;
}

extern "C" float fn_800AC004(int team, float value)
{
    switch (fn_800ABDA4(team)) {
    case 0:
        value *= 0.35f;
        break;
    case 1:
        value *= 1.15f;
        break;
    case 2:
        value *= 1.25f;
        break;
    }
    return value;
}

extern "C" unsigned int fn_800AC074(int team, unsigned int value)
{
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        flag = 1;
        team = team == 0;
    }
    switch (fn_800ABDA4(team)) {
    case 0:
        if (flag != 0) {
            value = (unsigned int)(value * 2.0f);
        } else {
            value = (unsigned int)(value * 0.8f);
        }
        break;
    case 1:
        value = (unsigned int)(value * 1.2f);
        break;
    case 2:
        value = (unsigned int)(value * 1.0f);
        break;
    }
    return value;
}

extern "C" float fn_800AC44C(Object_80039F5C *p, float value)
{
    int team = p->mIdBytes[2];

    if (value > 0.0f) {
        switch (fn_800ABDA4(team)) {
        case 0:
            if (fn_800B65A0(team) == 255) {
                value *= 0.15f;
            }
            break;
        case 1:
            break;
        case 2:
            if (fn_800B65A0(team) == 255) {
                if (fn_801BE648(p->mpUnknown792) == 225) {
                    value *= 1.15f;
                } else {
                    value *= 1.15f;
                }
            }
            break;
        }
    }
    return value;
}

extern "C" float fn_800AC504(int team, float value)
{
    if (value > 0.0f) {
        switch (fn_800ABDA4(team ^ 1)) {
        case 0:
        case 1:
            value *= 0.5f;
            break;
        case 2:
            fn_800B65A0(team);
            break;
        }
    }
    return value;
}

extern "C" int fn_800AC584(int team, int value)
{
    if (value > 0) {
        if (fn_800B65A0(team) == 255) {
            switch (fn_800ABDA4(team)) {
            case 0:
                value = (int)(value * 0.85f);
                break;
            case 1:
                break;
            case 2:
                value = (int)(value * 1.15f);
                break;
            }
        } else {
            team = (team + 1) & 1;
            if (fn_800B65A0(team) == 255) {
                switch (fn_800ABDA4(team)) {
                case 0:
                    value = (int)(value * 1.15f);
                    break;
                case 1:
                    break;
                case 2:
                    value = (int)(value * 0.85f);
                    break;
                }
            }
        }
    }
    return value;
}

extern "C" float fn_800AC6BC(int team, float value)
{
    if (fn_800B65A0(team) != 255 && fn_800ABDA4(team ^ 1) == 0) {
        value += 0.15f;
    }
    if (value > 1.0f) {
        value = 1.0f;
    }
    return value;
}

extern "C" float fn_800AC734(Object_80039F5C *p, float value)
{
    if (p->mUnknown8 != 255) {
        if (fn_800ABDA4(fn_80178308()) == 0) {
            value += 0.15f;
        }
    } else {
        switch (fn_800ABDA4(fn_80178308())) {
        case 0:
            value += -0.6f;
            break;
        case 1:
            value += -0.3f;
            break;
        case 2:
            break;
        }
    }
    if (value < 0.0f) {
        return 0.0f;
    }
    return value > 1.0f ? 1.0f : value;
}

extern "C" float fn_800AC7E0(int team, float value)
{
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        team ^= 1;
        flag = 1;
    }
    switch (fn_800ABDA4(team)) {
    case 0:
        if (flag != 0) {
            value *= 0.75f;
        }
        break;
    case 1:
        break;
    case 2:
        if (flag == 0) {
            value *= 0.83f;
        }
        break;
    }
    return value;
}

extern "C" int fn_800AC87C(Object_80039F5C *p, int value)
{
    int team = p->mIdBytes[2];
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        team ^= 1;
        flag = 1;
    }
    switch (fn_800ABDA4(team)) {
    case 0:
        if (flag == 0) {
            value = (int)(value * 2.0f);
        } else {
            value = (int)(value * 0.75f);
        }
        break;
    case 1:
        break;
    case 2:
        if (flag == 0) {
            value = (int)(value * 0.75f);
        }
        break;
    }
    return value;
}

extern "C" int fn_800AC980(Object_80039F5C *p, int value)
{
    int team = p->mIdBytes[2];
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        team ^= 1;
        flag = 1;
    }
    switch (fn_800ABDA4(team)) {
    case 0:
        break;
    case 1:
        if (flag == 0) {
            value = (int)(value * 0.75f);
        }
        break;
    case 2:
        if (flag == 0) {
            value = (int)(value * 0.5f);
        }
        break;
    }
    return value;
}
