static int lbl_803EA350 = 0x3FF;

extern "C" int fn_8002B70C(void)
{
    return lbl_803EA350;
}

extern "C" void fn_8002B714(int value)
{
    lbl_803EA350 = value;
}
