extern "C" {
void fn_8018AFD0(int value);
unsigned char fn_8018AFD8(unsigned char value);
unsigned char fn_8018AFE8(void);
}

static unsigned char lbl_803EB6B8 = 0;
static int lbl_803EB6BC = 0;

extern "C" void fn_8018AFD0(int value)
{
    lbl_803EB6BC = value;
}

extern "C" unsigned char fn_8018AFD8(unsigned char value)
{
    unsigned char previous = lbl_803EB6B8;

    lbl_803EB6B8 = value;
    return previous;
}

extern "C" unsigned char fn_8018AFE8(void)
{
    return lbl_803EB6B8;
}
