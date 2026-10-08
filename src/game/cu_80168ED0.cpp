#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"
#include "game/fn_802372EC.h"

#include "game/Team_80167A8C.h"

extern "C" {
int fn_801486A0(void);
void fn_80167EA0(int team);
void fn_800FBAA8(void);
void fn_8011F3A8(void);
void fn_80164940(int team);
int fn_80178308(void);
int fn_80178320(void);
void fn_800B0DA4(void);
Object_800670B4 *fn_80168708(int team);
void fn_80164430(Object_800670B4 *p, unsigned char index, unsigned char *a, unsigned char *b);
void fn_800B49EC(short *ratings, void *p);
void fn_800B4798(short *ratings, int team, unsigned char index, void *p);
void fn_800A6F04(int team);
int fn_800B65A0(int team);
int fn_801788D8(int *p);
int fn_801787DC(int team);
int fn_80177F70(void);
Point_80167910 fn_80177FE0(void);
float fn_80178A2C(void);
float fn_80178298(void);
int fn_800A8444(int team);
void fn_80168B5C(int team, int kind);
void fn_80168B04(int team, int kind);
int fn_80168C10(int team, int kind, int value);
void fn_800C02EC(void *p, int event);
void fn_800C02F8(void *p, int event);
void fn_800B4300(int value);
void fn_800B43AC(int value);
extern void *lbl_803EABA4;

int fn_80168ED0(void)
{
    switch (fn_801486A0()) {
    case 4: return 1;
    case 3: return 4;
    case 2: return fn_80148A58()->vfn_05(0) == 1 ? 2 : 3;
    }
    return 0;
}

void fn_80168F58(int team, int value)
{
    if (value & 0x8000) {
        fn_80167EA0(team);
        fn_800FBAA8();
        fn_8011F3A8();
        fn_80164940(team);
        if (team == fn_80178308())
            fn_800B0DA4();
        for (int t = 0; t < 2; ++t) {
            unsigned char side = t;
            Object_800670B4 *pBook = fn_80168708(side);
            int count = fn_80178D18(side);
            for (int i = 0; i < count; ++i) {
                Object_80039F5C *p = fn_80039F5C(side, i);
                unsigned char a, b;
                fn_80164430(pBook, i, &a, &b);
                p->mUnknown2914 = a;
                fn_800B49EC(p->mRatings, p->mUnknown3020);
                fn_800B4798(p->mRatings, side, i, &p->mUnknown2900);
            }
            fn_800A6F04(side);
        }
    }
}

void fn_80169058(short *p) {}
void fn_8016905C(short *p) {}

void fn_80169060(short *p)
{
    Point_80167910 pos;
    pos = fn_80177FE0();
    int offense = fn_80178308();
    int defense = fn_80178320();
    p[15] = fn_800B65A0(offense);
    p[16] = fn_800B65A0(defense);
    int value;
    if (fn_801788D8(&value) == 0)
        p[0] = (unsigned short)value - fn_801787DC(offense);
    else
        p[0] = -1;
    p[1] = fn_80177F70();
    p[3] = (int)(fn_80178A2C() - pos.mY);
    p[4] = (int)(pos.mY + fn_80178A2C());
    p[7] = p[6] = 0;
    switch (fn_80177F70()) {
    case 0:
        p[1] = 0;
        p[6] = fn_8017886C()->mUnknown1D == -2 ? 2 : 1;
        p[7] = 0;
        break;
    case 3:
    case 4:
    case 5: break;
    case 6:
        p[1] = 4;
        p[6] = 0;
        p[7] = 1;
        break;
    }
    float line = fn_80178298();
    p[2] = (int)(line - fn_80177FE0().mY);
    p[5] = fn_802372EC(0, 100);
    p[8] = *(unsigned short *)((char *)fn_80168708(offense) + 26);
    p[9] = 0;
    p[13] = p[12] = 50;
    p[10] = *(unsigned short *)((char *)fn_8016871C(offense) + 6);
    p[11] = *(unsigned short *)((char *)fn_8016871C(defense) + 6);
    if (fn_800A8444(fn_80178320()))
        p[14] = 1;
    else
        p[14] = 0;
}

void fn_80169264(short *p, short mode)
{
    fn_80169060(p);
    p[9] = fn_80178308();
    if (mode == 4)
        fn_80169058(p);
}

void fn_801692AC(short *p, short mode)
{
    fn_80169060(p);
    p[9] = fn_80178320();
    if (fn_80177F70() == 6)
        p[1] = 1;
    if (mode == 4)
        fn_8016905C(p);
}

int fn_80169308(int id, short *p, int value)
{
    int result = 0;
    if (p[18] > 0)
        p[18] = -1;
    int team = fn_80178308();
    switch (id) {
    case 0: fn_80169264(p, value); break;
    case 1:
    case 10: break;
    case 8:
        fn_80168B5C(team, value & ~0x8000);
        fn_80168F58(team, value);
        break;
    case 9:
        fn_80168B04(team, value & ~0x8000);
        fn_80168F58(team, value);
        break;
    case 4: fn_800C02EC(lbl_803EABA4, 39); break;
    case 6: p[19] = 255; break;
    case 7: p[19] = 254; break;
    case 11:
        if ((value & 0xC0) == 0xC0)
            team = (unsigned char)(team ^ 1);
        result = fn_80168C10(team, value & ~0xC0, p[17]);
        break;
    case 2:
        fn_800B4300(0);
        if (fn_800B65A0(fn_80178308()) == 255)
            fn_800C02F8(lbl_803EABA4, 2);
        break;
    case 3:
        fn_800B4300(1);
        fn_800C02F8(lbl_803EABA4, 1);
        break;
    case 5:
        fn_800B43AC(1);
        if (fn_800B65A0(fn_80178308()) == 255)
            fn_800C02F8(lbl_803EABA4, 2);
        break;
    case 12:
        fn_800B43AC(2);
        if (fn_800B65A0(fn_80178308()) == 255)
            fn_800C02F8(lbl_803EABA4, 2);
        break;
    }
    return result;
}

int fn_801694C8(int id, short *p, int value)
{
    int result = 0;
    int team = fn_80178320();
    switch (id) {
    case 0: fn_801692AC(p, value); break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 10:
    case 12: break;
    case 8:
        fn_80168B5C(team, value & ~0x8000);
        fn_80168F58(team, value);
        break;
    case 9:
        fn_80168B04(team, value & ~0x8000);
        fn_80168F58(team, value);
        break;
    case 11:
        if ((value & 0xC0) == 0x40)
            team = (unsigned char)(team ^ 1);
        result = fn_80168C10(team, value & ~0xC0, p[17]);
        break;
    case 6: p[19] = 255; break;
    case 7: p[19] = 254; break;
    }
    return result;
}
}
