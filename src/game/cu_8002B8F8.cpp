extern "C" {
void fn_8017F814(void);
}

static unsigned char lbl_803EA36C = 0;

extern "C" void fn_8002B8F8(void) {}

extern "C" void fn_8002B8FC(void)
{
    fn_8017F814();
    lbl_803EA36C = 0;
}

extern "C" unsigned char fn_8002B924(void) { return lbl_803EA36C; }

extern "C" void fn_8002B92C(void)
{
    if (fn_8002B924()) {
        fn_8002B8FC();
    } else {
        fn_8002B8F8();
    }
}
