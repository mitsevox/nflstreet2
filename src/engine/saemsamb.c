/* Partial source of the sound library's module bank registration (saemsamb.c). */


extern "C" {
typedef struct Object_803A6BCC {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8[32];
    int mUnknown28;
    int mUnknown2C;
} Object_803A6BCC;

extern Object_803A6BCC lbl_803A6BCC;

void fn_80269990(int a, int b)
{
    if (b == 0xFFFF && a != 0) {
        lbl_803A6BCC.mUnknown0 = 0;
        lbl_803A6BCC.mUnknown4 = 0;
        lbl_803A6BCC.mUnknown28 = 0;
        lbl_803A6BCC.mUnknown2C = 0;
    }
}

void fn_802699C8(void)
{
    fn_80269990(1, 0xFFFF);
}
}
