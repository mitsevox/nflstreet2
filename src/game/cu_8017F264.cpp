static unsigned char lbl_803EB4A0 = 0;
static unsigned char lbl_803EB4A1 = 0;
static unsigned char lbl_803EB4A2 = 0;
static unsigned char lbl_803EB4A3 = 0;
static unsigned char lbl_803EB4A4 = 0;
static unsigned char lbl_803EB4A5 = 0;
static float lbl_803EB4A8 = 0.0f;
static float lbl_803EB4AC = 0.0f;
static int lbl_803EB4B0 = 0;

extern "C" {
void fn_8017F2A4(void);

void fn_8017F264(void)
{
    fn_8017F2A4();
}

void fn_8017F284(void)
{
    fn_8017F2A4();
}

void fn_8017F2A4(void)
{
    lbl_803EB4A0 = 0;
    lbl_803EB4A1 = 0;
    lbl_803EB4A2 = 0;
    lbl_803EB4A3 = 0;
    lbl_803EB4A4 = 0;
    lbl_803EB4A5 = 0;
    lbl_803EB4B0 = 0;
    lbl_803EB4A8 = 0.0f;
    lbl_803EB4AC = 0.0f;
}

unsigned char fn_8017F2DC(unsigned char value)
{
    unsigned char old = lbl_803EB4A0;

    lbl_803EB4A0 = value;
    return old;
}

unsigned char fn_8017F2EC(unsigned char value)
{
    unsigned char old = lbl_803EB4A1;

    lbl_803EB4A1 = value;
    return old;
}

unsigned char fn_8017F2FC(unsigned char value)
{
    unsigned char old = lbl_803EB4A2;

    lbl_803EB4A2 = value;
    if (old == 1 && value == 0) {
        lbl_803EB4B0 = 30;
    }
    return old;
}

unsigned char fn_8017F324(unsigned char value)
{
    unsigned char old = lbl_803EB4A3;

    lbl_803EB4A3 = value;
    return old;
}

unsigned char fn_8017F334(unsigned char value)
{
    unsigned char old = lbl_803EB4A4;

    lbl_803EB4A4 = value;
    if (value == 1) {
        fn_8017F2EC(0);
        fn_8017F2FC(0);
        fn_8017F324(0);
    }
    return old;
}

unsigned char fn_8017F384(unsigned char value)
{
    unsigned char old = lbl_803EB4A5;

    lbl_803EB4A5 = value;
    return old;
}

unsigned char fn_8017F394(void)
{
    if (lbl_803EB4A2 == 0 && lbl_803EB4B0 != 0) {
        lbl_803EB4B0--;
        return 1;
    }
    return lbl_803EB4A2;
}
}
