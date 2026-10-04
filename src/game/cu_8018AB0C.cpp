#include "game/fn_8018AB0C.h"

extern "C" {
int fn_80163C30(void *p, int value);
void fn_80163CD0(void);

unsigned char lbl_803EB6B0 = 0;

int fn_8018AB0C(void)
{
    int result = fn_80163C30(0, 40);
    lbl_803EB6B0 = 1;
    return result;
}

void fn_8018AB3C(void)
{
    fn_80163CD0();
    lbl_803EB6B0 = 0;
}
}
