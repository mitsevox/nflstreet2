#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8009D990.h"
#include "game/fn_8021D7B8.h"
#include "game/cu_80064864.h"
#include "game/fn_800B65A0.h"
#include "game/fn_802372EC.h"
#include <string.h>

struct Team_80168EBC {
    char mUnknown0[0x40];
    int mUnknown40;
};

extern "C" {
extern unsigned char lbl_803EB2B4;
extern unsigned char lbl_803EB2B5;
extern char *lbl_803EB2B0;
extern void *lbl_803EB688;
extern void *lbl_803EABA4;
extern const int lbl_802DE3D0[];

int fn_801787DC(int team);
void fn_801787FC(int team, short value);
void fn_800C87CC(int team, int value);
void fn_80177768(void *p, int team);
void fn_801735D8(unsigned int mask);
void fn_801735B4(unsigned int mask);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
void fn_8009D888(int index, int value);
void fn_8009D944(int index);
float fn_80178A2C(void);
void fn_80178A20(float value);
void fn_80178E88(float v);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
void fn_80178370(void);
int fn_801783AC(int bit);
int fn_80178AE0(void);
void fn_80178CD8(int a);
void fn_801790D0(int team, float a, float b);
void fn_8017833C(int team);
void fn_8017E430(void);
void fn_80157514(void);
int fn_80054568(void);
int fn_800C1E40(void);
void fn_800544A4(const char *pTitle, const char *pText, const char *pButtons);
void fn_8021956C(void *p, int a, int b, int c);
void fn_801486A8(void);
void fn_801487C0(int team, unsigned char begin);
void fn_80139274(void);
void fn_80168640(int team, int kind);
int fn_80169E68(int mode);
void fn_80167EA0(int team);
void fn_80168744(int team, unsigned int a, unsigned int b, unsigned int c);
Team_80168EBC *fn_80168EBC(int team);
int fn_80085A34(int formation, int team);
void fn_800B3EFC(int team);
void fn_800AD910(int a, float b);
void fn_8013FB44(void);
void fn_8016DDDC(int team);
Object_80039F5C *fn_8003A130(Vector_80039F5C *pPos, float *pOut, int team);
int fn_8011F1CC(void);
void fn_8017D7C4(const char *pText);
void fn_8003A450(void);
int fn_8005BFD4(void);
void fn_8005BF18(void);
void fn_80173B8C(void);
void fn_800C02EC(void *p, short value);

void fn_800BC5DC(void *p);
void fn_800BCB18(void *p, float dt);
void fn_800AAD58(void *p, float dt);
void fn_800B3718(void *p, float dt);
void fn_800B3C68(void *p, float dt);
void fn_800B4020(void *p, float dt);
void fn_800BFB88(void *p, float dt);
void fn_800BFFD4(void *p, float dt);
void fn_800A042C(void *p, float dt);
void fn_800A050C(void *p, float dt);
int fn_800B8E18(void *p, char *pText);
void fn_800B9830(void *p, float dt);

int fn_8014AB64(void)
{
    int result = 2;
    int first = fn_801787DC(0);
    int second = fn_801787DC(1);
    if (lbl_803EB2B4 && fn_8009D990(1) == 0) {
        if (first > second) {
            result = 0;
        } else if (first < second) {
            result = 1;
        }
    } else {
        result = 2;
    }
    return result;
}

void fn_8014ABE4(void *p, int team)
{
    fn_80177768(p, team);
    lbl_803EB2B4 = 0;
}

void fn_8014AC0C(void *p, int team)
{
    lbl_803EB2B4 = 1;
    unsigned short points;
    if (team == 0) {
        points = fn_801787DC(1);
    } else {
        points = fn_801787DC(0);
    }
    int score = points + 1;
    fn_801787FC(team, score);
    fn_800C87CC(team, score);
    fn_801735D8(2048);
    fn_8009D8CC(1);
    fn_8009D964(1, 0);
}

void fn_8014AC88(void *p)
{
    fn_800BC5DC(p);
    fn_80178E88(fn_80178A2C() * 2.0f - 20.0f);
    fn_801790D0(fn_80178308(), 0.0f, 0.0f);
    fn_801790D0(fn_80178320(), 5.0f, 3.0f);
    fn_80178A20(fn_80178A2C() * 2.0f);
    fn_801735B4(2048);
    lbl_803EB2B4 = 0;
    fn_8017833C(1);
    lbl_803EB2B5 = 0;
    fn_8017E430();
    fn_80157514();
}

void fn_8014AD24(void *p, float dt)
{
    if (fn_80054568()) {
        fn_800BCB18(p, dt);
    }
}

void fn_8014AD70(void)
{
    if (fn_800C1E40() == 0) {
        fn_800544A4("2 Minute Challenge", lbl_803EB2B0, "|^Done");
    }
}

void fn_8014ADB0(void *p, float dt)
{
    fn_801735D8(2048);
    fn_8009D8CC(1);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_17(lbl_802DE3D0);
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 0, 0);
    fn_800AAD58(p, dt);
}

void fn_8014AE58(void)
{
    fn_80064EFC(3, 17, -1);
}

void fn_8014AE84(void)
{
    fn_8021956C(lbl_803EB688, 3, 17, 1);
}

void fn_8014AEB4(void *p, float dt)
{
    fn_801487C0(fn_80178308(), 3);
    fn_801487C0(fn_80178320(), 2);
    if (fn_800B65A0(fn_80178308()) != 255) {
        fn_800B3718(p, dt);
    } else {
        fn_80139274();
    }
}

void fn_8014AF24(void *p, float dt)
{
    if (fn_800B65A0(fn_80178308()) != 255) {
        fn_800B3C68(p, dt);
    } else {
        int team = fn_80178308();
        int other = team == 0;
        fn_80168640(team, 1);
        fn_80168640(other, 11);
        fn_80169E68(0);
        fn_80167EA0(team);
        fn_80168744(other, 0, 0, 0);
        fn_80167EA0(other);
        fn_80085A34(fn_80168EBC(0)->mUnknown40, 0);
        fn_80085A34(fn_80168EBC(1)->mUnknown40, 1);
        fn_800B3EFC(team);
        fn_800B3EFC(other);
        fn_800AD910(2, dt);
    }
    fn_80148A58()->vfn_15();
}

void fn_8014B028(void *p, float dt)
{
    if (fn_800B65A0(fn_80178308()) != 255) {
        fn_800B4020(p, dt);
    } else {
        fn_8009D888(0, 10);
        fn_8013FB44();
        fn_8016DDDC(fn_80178308());
        fn_8016DDDC(fn_80178320());
        fn_8009D944(1);
        fn_8009D944(0);
        short value = 9 - fn_802372EC(0, 5);
        fn_800C02EC(lbl_803EABA4, value);
    }
}

int fn_8014B0C8(void)
{
    return 10;
}

void fn_8014B0D0(void *p, float dt)
{
    fn_801486A8();
    fn_800BFB88(p, dt);
    fn_801487C0(fn_80178308(), 3);
    fn_801487C0(fn_80178320(), 2);
    short value = 9 - fn_802372EC(0, 5);
    fn_800C02EC(lbl_803EABA4, value);
    Object_80137ABC *pBall = fn_801374BC();
    Vector_80039F5C pos;
    fn_80137D58(pBall, &pos);
    fn_80137A04(pBall, fn_8003A130(&pos, 0, fn_80178308()));
}

void fn_8014B178(void *p, float dt)
{
    fn_800BFFD4(p, dt);
    fn_80148A58()->vfn_15();
    if (fn_8009D990(1) == 0) {
        fn_80178370();
    }
}

void fn_8014B1C8(void *p, float dt)
{
    fn_801735B4(2048);
    fn_800A042C(p, dt);
}

void fn_8014B210(void *p, float dt)
{
    fn_800A050C(p, dt);
    fn_80148A58()->vfn_15();
    if (fn_8011F1CC() && fn_801783AC(0) && !fn_801783AC(13) && !fn_801783AC(1) &&
        !fn_801783AC(20)) {
        fn_80178370();
        fn_8017D7C4("Passer Cannot Run!");
    } else if (fn_80178308() != fn_80178348()) {
        fn_80178370();
    }
}

int fn_8014B2CC(void *p, char *pText)
{
    if (fn_8009D990(1) != 0 || lbl_803EB2B4 != 0) {
        return fn_800B8E18(p, pText);
    }
    strcpy(pText, "Switch Sides!");
    return 1;
}

void fn_8014B350(void *p, float dt)
{
    fn_800B9830(p, dt);
    fn_80148A58()->vfn_15();
}

void fn_8014B38C(void *p, float dt)
{
    fn_8003A450();
    if (fn_8005BFD4() != 4) {
        fn_8005BF18();
    }
    if (fn_8009D990(1)) {
        fn_800AD910(5, dt);
    } else {
        int pending = 0;
        fn_801735D8(2048);
        fn_8009D8CC(1);
        fn_801735D8(16);
        if (fn_80178AE0() == 2) {
            if (lbl_803EB2B4) {
                lbl_803EB2B5 = 1;
            }
            if (lbl_803EB2B5) {
                fn_8009D964(1, 30);
            } else {
                fn_8009D964(1, 120);
            }
            fn_8017833C(fn_80178360());
            fn_80178CD8(1);
            lbl_803EB2B4 = !lbl_803EB2B4;
            fn_800AD910(5, 0.0f);
        } else {
            pending = 1;
        }
        if (pending) {
            fn_80173B8C();
        }
    }
}
}
