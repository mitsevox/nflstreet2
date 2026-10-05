#include "game/cu_80003C94.h"
#include "game/cu_801CF5BC.h"

static void *lbl_803EB8D8 = 0;

void *fn_80003C94(void)
{
    return lbl_803EB8D8 = fn_801CF5BC(0, fn_801CF7AC());
}

int fn_80003CC4(void)
{
    int result = fn_801CF67C(lbl_803EB8D8);
    lbl_803EB8D8 = 0;
    return result;
}
