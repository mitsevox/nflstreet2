#include "game/fn_80177FE0.h"
#include "game/fn_800670B4.h"

extern "C" {
int fn_80177F70(void);
float fn_80178298(void);
Object_800670B4 *fn_80168708(int team);
int fn_8022D23C(void);
int fn_8022D25C(int value);
int fn_8022D2F4(unsigned short handle, unsigned short a, unsigned char b, unsigned char *pPairs, int c);
int fn_8022D3AC(void);
short fn_8022D3D4(unsigned char index);
int fn_8022D418(int a, int b, int mode);
int fn_8022D540(void);
int fn_8022E558(void);
int fn_8022E560(void);

void fn_8017CC34(int team, Object_800670B4 *pTeam);

int fn_8017CB40(void)
{
    float y = fn_80178298();
    Point_8017886C point;
    signed char distance;

    point = fn_80177FE0();
    distance = (signed char)(y - point.mY + 0.001f);
    if (fn_80177F70() == 3 && distance > 3) {
        return 1;
    }
    return 0;
}

void fn_8017CBD0(void)
{
}

void fn_8017CBD4(void)
{
    fn_8022D23C();
    fn_8022D25C(0);
}

void fn_8017CBFC(int team)
{
    fn_8017CC34(team, fn_80168708(team));
}

void fn_8017CC34(int team, Object_800670B4 *pTeam)
{
    unsigned char pairs[7][2];
    int flag;
    unsigned char i;
    int handle;

    flag = 0;
    if (fn_8017CB40()) {
        flag = 1;
    }
    for (i = 0; i <= 6; i++) {
        unsigned short value = pTeam->mUnknown8.mUnknown84[i].mUnknown0;
        if (flag && value == 1) {
            pairs[i][0] = 25;
        } else {
            pairs[i][0] = value;
        }
        pairs[i][1] = pTeam->mUnknown8.mUnknown84[i].mUnknown3 - 1;
    }
    if (team == 0) {
        handle = fn_8022E558();
    } else {
        handle = fn_8022E560();
    }
    fn_8022D418(handle, 0x3FF, 1);
    fn_8022D2F4(handle, pTeam->mUnknown8.mUnknown4, pTeam->mUnknown4, &pairs[0][0], 1);
}

void fn_8017CD20(void)
{
    fn_8022D540();
    fn_8022D3AC();
}

short fn_8017CD44(unsigned char index)
{
    return fn_8022D3D4(index);
}
}
