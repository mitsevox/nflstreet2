extern "C" {
extern void (*lbl_803EBB10)(int, int, ...);

void fn_80075550(int *pResult, int value);
int fn_80178320(void);
int fn_801AE5D4(int a, int b, int c);
}

static int lbl_803EA754 = 0;

extern "C" void fn_80075100(void)
{
    int result;

    fn_80075550(&result, lbl_803EA754);
    if (fn_80178320() == 0) {
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2022), 1, result);
    } else {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4022), 1, result);
    }
}

extern "C" void fn_80075188(int value) { lbl_803EA754 = value; }
extern "C" int fn_80075190(void) { return lbl_803EA754; }
