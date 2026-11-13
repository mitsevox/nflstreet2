/* MAD video decoder inner loop: reads bits from the compressed frame and decodes one 8x8
   block of picture coefficients. */

#include "engine/maddec.h"

extern unsigned char *maddataptr;
extern unsigned int madshiftreg;
extern int madbitcount;
extern int madvlctbl1[512];
extern int madvlctbl2[256];
extern int madvlctbl3[256];
extern int madquant[64];
extern int idctinput[64];
extern const int lbl_802B0F50[64];

void discardbits(int count)
{
    madshiftreg <<= count;
    madbitcount -= count;
    if (madbitcount < 16) {
        madshiftreg |= ((maddataptr[1] << 8) | maddataptr[0]) << (16 - madbitcount);
        madbitcount += 16;
        maddataptr += 2;
    }
}

int madvlcdecode(void)
{
    int i;
    int code;
    int length;
    int index;
    int *p;

    idctinput[0] = ((int)madshiftreg >> 24) * madquant[0];
    discardbits(8);
    p = &idctinput[1];
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
        code = madvlctbl1[madshiftreg >> 23];
        length = code & 0xFF;
        if (length > 9) {
            if (!(code & 0x20)) {
                if (!(code & 0x10)) {
                    discardbits(9);
                    code = madvlctbl2[madshiftreg >> 24];
                    length = code & 0xFF;
                } else {
                    discardbits(6);
                    code = madvlctbl3[madshiftreg >> 24];
                    length = code & 0xFF;
                }
            } else if (code & 0x10) {
                discardbits(2);
                return i;
            } else {
                discardbits(6);
                code = madshiftreg;
                length = 16;
            }
        }
        discardbits(length);
        i += (code >> 16) & 0x3F;
        idctinput[lbl_802B0F50[i]] = (code >> 22) * madquant[lbl_802B0F50[i]];
        i++;
    }
}
