#include "game/Class_80148A58.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297C60.h"
#include "game/cu_80064864.h"
#include "game/fn_8021D7B8.h"

class Class_802A1A58 : public Class_80297C60 {
};

class Class_802A19F0 : public Class_80297B90 {
};

extern "C" {
extern void *lbl_803EB688;
extern const int lbl_802DEB78[];

int fn_800A2178(void);
void fn_800D42D4(void);
char *fn_801C2EB4(char *pDest, const char *pSource);
void fn_801735D8(unsigned int mask);
void fn_8009D8CC(int index);
void fn_800AAD58(void *p, float dt);
void fn_8021956C(void *p, int a, int b, int c);

int fn_80154050(Class_802A1A58 *p, char *pText)
{
    char touchdown[10] = "Touchdown";
    char defensive[13] = "Defensive TD";
    int result = 0;
    int kind = fn_800A2178();

    if (kind == 0) {
        fn_800D42D4();
        result = 1;
        fn_801C2EB4(pText, touchdown);
    } else if (kind == 14) {
        fn_800D42D4();
        result = 1;
        fn_801C2EB4(pText, defensive);
    }
    return result;
}

void fn_80154110(Class_802A19F0 *p, float dt)
{
    fn_801735D8(2048);
    fn_8009D8CC(1);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_16(lbl_802DEB78);
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 0, 0);
    fn_800AAD58(p, dt);
}

void fn_801541B8(Class_802A19F0 *p)
{
    fn_80064EFC(3, 20, -1);
}

void fn_801541E4(Class_802A19F0 *p)
{
    fn_8021956C(lbl_803EB688, 3, 20, 1);
}
}
