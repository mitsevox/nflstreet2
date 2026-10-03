extern "C" {
void fn_80190280(int a);
int fn_801908A0(int index);
}

static unsigned char lbl_80309E34[55];

extern "C" void fn_80054CA8(int a)
{
    unsigned int i = 0;

    fn_80190280(a);
    while (i < 55) {
        lbl_80309E34[i] |= fn_801908A0(i);
        i++;
    }
}

extern "C" void fn_80054CFC(void)
{
    unsigned int i;

    for (i = 0; i < 55; i++) {
        lbl_80309E34[i] = 0;
    }
}

extern "C" unsigned char fn_80054D24(int index) { return lbl_80309E34[index]; }
