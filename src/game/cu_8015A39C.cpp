struct Object_8015C244 {
    char mUnknown0[48];
    float mUnknown48;
};

extern "C" {
extern unsigned char lbl_803ECA68;

void fn_8015C244(Object_8015C244 *p)
{
    p->mUnknown48 = 0.6f;
}

void fn_8015C254(int value)
{
    lbl_803ECA68 = value;
}
}
