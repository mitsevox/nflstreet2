extern "C" {
extern void (*lbl_803EBB10)(int, int, ...);

int fn_800745BC(int side);
void fn_80075550(int *pResult, int value);
int fn_80178308(void);
int fn_80178320(void);
int fn_801AE5D4(int a, int b, int c);
}

extern "C" void fn_800747DC(int value)
{
    int result;

    fn_80075550(&result, value);
    if (fn_80178308() == 0) {
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2023), 1, result);
    } else {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4023), 1, result);
    }
}

extern "C" void fn_80074864(int value)
{
    int result;

    fn_80075550(&result, value);
    if (fn_80178320() == 0) {
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2024), 1, result);
    } else {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4024), 1, result);
    }
}

extern "C" void fn_800748EC(int value)
{
    int result;

    fn_80075550(&result, value);
    if (fn_80178308() == 0) {
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2025), 1, result);
    } else {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4025), 1, result);
    }
}

extern "C" void fn_80074974(int value)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, value);
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2026), 1, result);
    } else {
        fn_80075550(&result, value);
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4026), 1, result);
    }
}

extern "C" void fn_80074A14(int value)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, value);
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2027), 1, result);
    } else {
        fn_80075550(&result, value);
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4027), 1, result);
    }
}

extern "C" void fn_80074AB4(int value)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, value);
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2028), 1, result);
    } else {
        fn_80075550(&result, value);
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4028), 1, result);
    }
}

extern "C" void fn_80074B54(int)
{
    int result;

    if (fn_80178320() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2029), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4029), 1, result);
    }
}

extern "C" void fn_80074C08(int)
{
    int result;

    if (fn_80178320() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x202A), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402A), 1, result);
    }
}

extern "C" void fn_80074CBC(void)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x201B), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x401B), 1, result);
    }
}
