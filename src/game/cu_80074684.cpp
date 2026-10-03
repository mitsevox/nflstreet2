extern "C" {
extern void (*lbl_803EBB10)(int, int, ...);

int fn_800737C8(int a, int b);
int fn_801AE5D4(int a, int b, int c);
}

static int lbl_803EA73C = -1;

extern "C" void fn_80074684(int a, int b)
{
    int value = fn_800737C8(a, b);

    lbl_803EA73C = value;
    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 1);
}

extern "C" void fn_800746E0(void)
{
    int value = lbl_803EA73C;

    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 4);
}

extern "C" void fn_80074734(void)
{
    int value = lbl_803EA73C;

    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 2);
}

extern "C" void fn_80074788(void)
{
    int value = lbl_803EA73C;

    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 8);
}
