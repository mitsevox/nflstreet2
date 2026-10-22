extern unsigned char *lbl_803ECF1C;
extern unsigned int lbl_803ECF20;
extern int lbl_803ECF24;
extern int lbl_80399110[512];
extern int lbl_80399910[256];
extern int lbl_80399D10[256];
extern int lbl_8039A210[64];
extern int lbl_8039AB10[64];
extern const int lbl_802B0F50[64];

extern "C" int fn_801DB0B0(void);

void fn_801DB058(int count)
{
    lbl_803ECF20 <<= count;
    lbl_803ECF24 -= count;
    if (lbl_803ECF24 < 16) {
        lbl_803ECF20 |= ((lbl_803ECF1C[1] << 8) | lbl_803ECF1C[0]) << (16 - lbl_803ECF24);
        lbl_803ECF24 += 16;
        lbl_803ECF1C += 2;
    }
}

int fn_801DB0B0(void)
{
    int i;
    int code;
    int length;
    int index;
    int *p;

    lbl_8039AB10[0] = ((int)lbl_803ECF20 >> 24) * lbl_8039A210[0];
    fn_801DB058(8);
    p = &lbl_8039AB10[1];
    for (i = 0; i < 9; i++) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[4] = 0;
        p[5] = 0;
        p[6] = 0;
        p += 7;
    }
    i = 1;
    for (;;) {
        code = lbl_80399110[lbl_803ECF20 >> 23];
        length = code & 0xFF;
        if (length > 9) {
            if (!(code & 0x20)) {
                if (!(code & 0x10)) {
                    fn_801DB058(9);
                    code = lbl_80399910[lbl_803ECF20 >> 24];
                    length = code & 0xFF;
                } else {
                    fn_801DB058(6);
                    code = lbl_80399D10[lbl_803ECF20 >> 24];
                    length = code & 0xFF;
                }
            } else if (code & 0x10) {
                fn_801DB058(2);
                return i;
            } else {
                fn_801DB058(6);
                code = lbl_803ECF20;
                length = 16;
            }
        }
        fn_801DB058(length);
        i += (code >> 16) & 0x3F;
        lbl_8039AB10[lbl_802B0F50[i]] = (code >> 22) * lbl_8039A210[lbl_802B0F50[i]];
        i++;
    }
}
