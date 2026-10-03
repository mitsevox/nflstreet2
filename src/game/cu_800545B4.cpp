static unsigned char lbl_803EA560 = 0;
static unsigned char lbl_803EA561 = 1;

extern "C" void fn_800545B4(void) { lbl_803EA561 = 0; }

extern "C" void fn_800545C0(void)
{
    lbl_803EA560 = 0;
    fn_800545B4();
}

extern "C" void fn_800545E8(void) { lbl_803EA560 = 0; }

extern "C" unsigned char fn_800545F4(unsigned char value)
{
    unsigned char previous = lbl_803EA560;

    lbl_803EA560 = value;
    fn_800545B4();
    return previous;
}
