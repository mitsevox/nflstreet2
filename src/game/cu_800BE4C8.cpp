#include "game/Block_800BFAD0.h"
#include "game/fn_800B65A0.h"
#include "game/Object_80039F5C.h"
#include "game/cu_8002B8F8.h"

extern "C" {
int fn_801486A0(void);
int fn_800B6644(int index);
int fn_8002B59C(void);
int fn_8002B5A8(void);
void fn_8002B5A4(int value);
void fn_8015A0D0(int value);
void fn_8017D7C4(const char *pText);
int fn_800A7FD8(void);
int fn_800BF574(int a, unsigned int kind);
int fn_800A937C(void);
int fn_800BA6F8(void);
unsigned char fn_8002D060(Type_803EA368 *p);
void fn_800BA8CC(int value);
int fn_800BAAB8(void);
void fn_800BA804(int value);
void fn_800BDB14(int index, unsigned int msg, float value);
void fn_800BDFB4(int a, unsigned int msg, float value);
void fn_800C0488(int a, unsigned int kind, float value);
void fn_800BE3E8(int a, int kind, float value);
int fn_800BA71C(void);
void fn_800BD958(void);
void fn_800BE944(int index, int a, unsigned int msg, float value);
void fn_800BE8E4(int team);
int fn_80178308(void);
int fn_80178320(void);
int fn_801481B0(void);
void fn_80148108(int mode);
Object_80039F5C *fn_800B6544(int index);
void fn_800B6868(int a, int b, int c, int d);

extern float lbl_803EABAC[2];
}

extern "C" void fn_800BE4C8(int a, unsigned int msg, float value)
{
    int team;

    if (fn_801486A0() == 0) {
        return;
    }
    team = fn_800B6644(a);
    if (fn_8002B59C() && msg == 14 && value == 1.0f) {
        fn_8002B5A4(fn_8002B5A8() == 0);
        fn_8015A0D0(fn_8002B5A8() == 0);
        if (fn_8002B5A8()) {
            fn_8017D7C4("MarketCam-Pass Icons On");
        } else {
            fn_8017D7C4("MarketCam-Pass Icons Off");
        }
    }
    if (fn_800A7FD8()) {
        if (a != 255) {
            fn_800BF574(a, msg);
        }
        return;
    }
    if (fn_800A937C()) {
        return;
    }
    if (__builtin_fabsf(value) > 0.9999999f) {
        if (team != 255) {
            if (fn_800BA6F8()) {
                switch (msg) {
                case 94:
                    if (!fn_8002D060(lbl_803EA368)) {
                        fn_800BA8CC(1);
                    }
                    break;
                case 93:
                    if (!fn_8002D060(lbl_803EA368) && fn_800BAAB8()) {
                        fn_800BA804(1);
                    }
                    break;
                }
            }
            switch (lbl_803EABA8->mSlots[team].mUnknown0) {
            case 4:
                fn_800BE944(team, a, msg, value);
                break;
            case 0:
                fn_800BDB14(a, msg, value);
                break;
            case 1:
                fn_800BDFB4(a, msg, value);
                lbl_803EABAC[team] = 15.0f;
                break;
            case 3:
                fn_800C0488(a, msg, value);
                break;
            case 2:
                fn_800BE3E8(a, msg, value);
                break;
            }
        } else if (fn_800BA71C() == 1 && msg == 89) {
            fn_800BD958();
        }
    } else if (lbl_803EABA8->mSlots[team].mUnknown0 == 4) {
        fn_800BE944(team, a, msg, value);
    }
}

extern "C" void fn_800BE944(int index, int a, unsigned int msg, float value)
{
    if (fn_800B65A0(index) == a) {
        switch (msg) {
        case 134:
            break;
        case 132:
            fn_800BE8E4(index);
            lbl_803EABA8->mSlots[index].mUnknown10 = value;
            break;
        case 133:
            fn_800BE8E4(index);
            lbl_803EABA8->mSlots[index].mUnknown10 = value;
            lbl_803EABA8->mSlots[index].mUnknown14 = value == 1.0f && lbl_803EABA8->mSlots[index].mUnknown0 == 4;
            break;
        case 53:
            if (lbl_803EABA8->mSlots[index].mUnknown18 == 0 && lbl_803EABA8->mSlots[index].mUnknown19 == 0
                && index == fn_80178308()) {
                lbl_803EABA8->mSlots[index].mUnknownC = -value;
                lbl_803EABA8->mSlots[index].mUnknown15[2] = value != 0.0f;
            }
            break;
        case 54:
            if (lbl_803EABA8->mSlots[index].mUnknown15[2] == 0 && lbl_803EABA8->mSlots[index].mUnknown19 == 0
                && index == fn_80178308()) {
                lbl_803EABA8->mSlots[index].mUnknownC = value;
                lbl_803EABA8->mSlots[index].mUnknown18 = value != 0.0f;
            }
            break;
        case 16:
            if (lbl_803EABA8->mSlots[index].mUnknown15[2] == 0 && lbl_803EABA8->mSlots[index].mUnknown18 == 0
                && index == fn_80178308()) {
                lbl_803EABA8->mSlots[index].mUnknownC = value;
                lbl_803EABA8->mSlots[index].mUnknown19 = value != 0.0f;
            }
            break;
        default:
            if (lbl_803EABA8->mSlots[index].mUnknown0 == 4 && index == fn_80178320() && fn_801481B0() == 0) {
                fn_80148108(1);
            }
            break;
        }
    } else {
        Object_80039F5C *p;

        switch (msg) {
        case 6:
            if (value == 1.0f) {
                p = fn_800B6544(a);
                fn_800B6868((unsigned char)(p->mId >> 8), (unsigned char)(p->mId >> 16), p->mUnknown8, 0);
            }
            break;
        case 9:
            if (value == 1.0f) {
                p = fn_800B6544(a);
                fn_800B6868((unsigned char)(p->mId >> 8), (unsigned char)(p->mId >> 16), p->mUnknown8, 1);
            }
            break;
        }
    }
}
