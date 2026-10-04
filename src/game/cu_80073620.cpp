extern "C" {
extern void (*lbl_803EBB10)(int, int, ...);

void fn_800742A0(int index);
void fn_80074358(int index);
void fn_80075550(int *pResult, int value);
void fn_800755C4(int *pResult, int value);
int fn_801AE5D4(int a, int b, int c);
void fn_801AF2CC(int index);
}

static int lbl_803EA718 = 0;
static unsigned char lbl_803EA71C = 0;

extern "C" void fn_80073620(int a, int b, int c)
{
    int result1;
    int result2;

    lbl_803EA718 = b;
    if (a == 999) {
        lbl_803EA71C = 0;
    } else {
        lbl_803EA71C = 1;
    }
    if (lbl_803EA71C) {
        fn_80075550(&result1, b);
        fn_800755C4(&result2, c);
        if ((unsigned char)(b >> 8) == 0) {
            fn_80074358(1);
            lbl_803EBB10(fn_801AE5D4(1, 0, 0x201E), 3, a, result1, result2);
            fn_801AF2CC(1);
        } else {
            fn_80074358(0);
            lbl_803EBB10(fn_801AE5D4(2, 0, 0x401E), 3, a, result1, result2);
            fn_801AF2CC(0);
        }
    }
}

extern "C" void fn_8007371C(void)
{
    if (lbl_803EA71C) {
        if ((unsigned char)(lbl_803EA718 >> 8) == 0) {
            fn_800742A0(1);
        } else {
            fn_800742A0(0);
        }
    }
}

extern "C" void fn_80073764(void)
{
    if (lbl_803EA71C) {
        if ((unsigned char)(lbl_803EA718 >> 8) == 0) {
            fn_80074358(1);
        } else {
            fn_80074358(0);
        }
    }
    lbl_803EA718 = 0;
    lbl_803EA71C = 0;
}

extern "C" int fn_800737B8(void)
{
    return lbl_803EA718;
}

extern "C" unsigned char fn_800737C0(void)
{
    return lbl_803EA71C;
}

extern "C" int fn_800737C8(unsigned int a, int b)
{
    switch (a) {
    case 0:
        return b;
    case 1:
        return b + 7;
    case 2:
        return b + 16;
    case 3:
        return b + 24;
    case 4:
        return b + 30;
    }
    return 0;
}
