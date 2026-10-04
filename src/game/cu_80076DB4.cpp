extern "C" {
extern void (*lbl_803EBB10)(int, int, ...);

void fn_800742A0(int index);
void fn_80074358(int index);
void fn_80075550(int *pResult, int value);
void fn_800755C4(int *pResult, int value);
int fn_801AE5D4(int a, int b, int c);
}

static int lbl_803EA780 = 0;
static int lbl_803EA784 = 0;

extern "C" void fn_80076DB4(int a, int b, int c, int index)
{
    int result1;
    int result2;

    switch (index) {
    case 0:
        lbl_803EA780 = b;
        fn_80074358(0);
        fn_80075550(&result1, b);
        fn_800755C4(&result2, c);
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x401E), 3, a, result1, result2);
        break;
    case 1:
        lbl_803EA784 = b;
        fn_80074358(1);
        fn_80075550(&result1, b);
        fn_800755C4(&result2, c);
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x201E), 3, a, result1, result2);
        break;
    }
}

extern "C" void fn_80076EA4(int index)
{
    switch (index) {
    case 0:
        fn_800742A0(0);
        break;
    case 1:
        fn_800742A0(1);
        break;
    }
}

extern "C" void fn_80076EE8(int index)
{
    switch (index) {
    case 0:
        fn_80074358(0);
        lbl_803EA780 = 0;
        break;
    case 1:
        fn_80074358(1);
        lbl_803EA784 = 0;
        break;
    }
}

extern "C" int fn_80076F40(int index)
{
    int value = 0;

    switch (index) {
    case 0:
        value = lbl_803EA780;
        break;
    case 1:
        value = lbl_803EA784;
        break;
    }
    return value;
}
