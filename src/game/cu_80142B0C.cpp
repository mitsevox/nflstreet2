struct Entry_802DCF9C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    void (*mpUnknown4)();
};

extern "C" {
void fn_8003A628();
void fn_801380DC();
void fn_8003EDD8(unsigned char a, unsigned char b, void (*pCallback)());
void fn_8003EE00(unsigned char a);

static Entry_802DCF9C lbl_802DCF9C[6] = {
    { 0, 11, fn_8003A628 },
    { 1, 1, fn_801380DC },
    { 2, 4, 0 },
    { 3, 1, 0 },
    { 4, 0, 0 },
    { 5, 1, 0 },
};

void fn_80142B0C()
{
    unsigned char i;

    for (i = 0; i < 6; i++) {
        fn_8003EDD8(lbl_802DCF9C[i].mUnknown0, lbl_802DCF9C[i].mUnknown1, lbl_802DCF9C[i].mpUnknown4);
    }
}

void fn_80142B68()
{
    unsigned char i;

    for (i = 0; i < 6; i++) {
        fn_8003EE00(lbl_802DCF9C[i].mUnknown0);
    }
}
}
