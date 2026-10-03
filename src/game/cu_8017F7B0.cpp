struct Args_8017F868 {
    char mUnknown0[4];
    int mUnknown4;
    int mUnknown8;
};

struct Block_8017F868 {
    int mUnknown0;
    Args_8017F868 *mpArgs;
    int mUnknown8;
};

extern "C" {
extern void *lbl_803EB688;

void fn_8021956C(void *p, int a, int b, int c);
}

static void (*lbl_803EB500)(int, int, int) = 0;
static void (*lbl_803EB504)(int, int, int, int) = 0;
static unsigned char lbl_803EB508 = 0;

extern "C" void fn_8017F7B0(int a, int b, int c)
{
    if (lbl_803EB500 != 0) {
        lbl_803EB500(a, b, c);
    }
}

extern "C" void fn_8017F7E0(int a, int b, int c, int d)
{
    if (lbl_803EB504 != 0) {
        lbl_803EB504(a, b, c, d);
    }
}

extern "C" void fn_8017F810(void) {}

extern "C" unsigned char fn_8017F860(void);

extern "C" void fn_8017F814(void)
{
    if (fn_8017F860()) {
        fn_8021956C(lbl_803EB688, 2, 3, 1);
        lbl_803EB500 = 0;
        lbl_803EB504 = 0;
        lbl_803EB508 = 0;
    }
}

extern "C" unsigned char fn_8017F860(void) { return lbl_803EB508; }

extern "C" int fn_8017F868(unsigned int id, Block_8017F868 *pBlock)
{
    switch (id) {
    case 0x80000001:
        fn_8017F810();
        break;
    case 0x80000002:
        fn_8017F7B0(pBlock->mUnknown0, pBlock->mpArgs->mUnknown8, pBlock->mpArgs->mUnknown4);
        break;
    case 0x80000003:
        fn_8017F7E0(pBlock->mUnknown0, pBlock->mpArgs->mUnknown8, pBlock->mpArgs->mUnknown4, pBlock->mUnknown8);
        break;
    default:
        return 0;
    }
    return 1;
}
