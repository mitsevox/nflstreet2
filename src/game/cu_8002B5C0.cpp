static int lbl_803EC610;

extern "C" void fn_8002B5C0(int value)
{
    lbl_803EC610 = value;
}

extern "C" int fn_8002B5C8(void)
{
    return lbl_803EC610;
}
