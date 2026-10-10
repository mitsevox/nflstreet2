#include "game/PaletteColor.h"
#include "game/cu_8017F90C.h"

struct Block_8017FAE8 {
    int mUnknown0;
    int mUnknown4;
    int *mpUnknown8;
    int *mpUnknownC;
    int *mpUnknown10;
};

static int lbl_803EB518 = -1;
static int lbl_803EB51C = -1;
static int lbl_803EB520 = -1;

extern "C" {
int fn_8017FB54(int a, int b);

void fn_8017FA78(int a, int b)
{
    lbl_803EB518 = a;
    lbl_803EB51C = b;
}

void fn_8017FA84(int a, int b, int *pOut0, int *pOut1, int *pOut2)
{
    PaletteColor color;
    int value = fn_8017FB54(a, b);

    lbl_803EB520 = value;
    fn_8007A068(value, &color);
    *pOut0 = color.r;
    *pOut2 = color.b;
    *pOut1 = color.g;
}

int fn_8017FAE8(int id, Block_8017FAE8 *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 17:
        fn_8017FA78(pBlock->mUnknown0, pBlock->mUnknown4);
        break;
    case 18:
        fn_8017FA84(pBlock->mUnknown0, pBlock->mUnknown4, pBlock->mpUnknown8, pBlock->mpUnknownC, pBlock->mpUnknown10);
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_8017FB54(int a, int b)
{
    return a * lbl_803EB51C + b;
}

void fn_8017FB64(int value, int *pQuotient, int *pRemainder)
{
    *pQuotient = value / lbl_803EB51C;
    *pRemainder = value % lbl_803EB51C;
}

int fn_8017FB88(void)
{
    return lbl_803EB520;
}
}
