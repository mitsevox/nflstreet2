#include "game/Class_80148A58.h"
#include "game/Class_80297B90.h"
#include "game/fn_8021D7B8.h"

class Class_802A1860 : public Class_80297B90 {
};

extern "C" {
extern void *lbl_803EB688;
void fn_800AAD58(void *p, float dt);
void fn_80064EFC(int a, int b, int c);
void fn_8021956C(void *p, int a, int b, int c);
int fn_80178348(void);
void fn_80155A7C(Class_80148A58 *p, unsigned char team, int kind, int value);
void fn_80155BF4(Class_80148A58 *p, unsigned char team, int kind, int value, int flag);

void fn_801556D0(unsigned int kind, int value, int flag)
{
    int team = fn_80178348();

    if (kind <= 1 || kind == 6 || kind == 7 || kind == 5 || kind == 8) {
        fn_80155A7C(fn_80148A58(), team, kind, value);
    } else if (kind >= 2 && kind <= 4) {
        fn_80155BF4(fn_80148A58(), team, kind, value, flag);
    }
}

void fn_8015576C(Class_802A1860 *p, float dt)
{
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 0, 0);
    fn_80148A58()->vfn_12();
    fn_800AAD58(p, dt);
}

void fn_801557E0(Class_802A1860 *p)
{
    fn_80064EFC(3, 25, -1);
}

void fn_8015580C(Class_802A1860 *p)
{
    fn_8021956C(lbl_803EB688, 3, 25, 1);
}
}
