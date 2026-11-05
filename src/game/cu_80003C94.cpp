#include "game/cu_80003C94.h"
#include "game/cu_801CF5BC.h"

static void *lbl_803EB8D8 = 0;

void fn_80003C94(void)
{
    lbl_803EB8D8 = MathNewRandomStream(0, MathGetRandomSeed());
}

int fn_80003CC4(void)
{
    int result = MathDelRandomStream(lbl_803EB8D8);
    lbl_803EB8D8 = 0;
    return result;
}
