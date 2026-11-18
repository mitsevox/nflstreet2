/* MT block decoder (mtdecf.cpp): decodes MT compressed sample blocks into a 432-sample float buffer
   for the MT unpack filters: allocation, the bit reader, block parsing, sample delivery and the
   decoder's state save/restore. */

#include "engine/sndsys.h"

extern "C" {

void fn_8027CA34(Codec_8027CF9C *unused, unsigned char *data, Codec_8027CF9C *p, int flag);
void fn_8027CBA4(Codec_8027CF9C *p);

void *fn_8027C020(int size)
{
    return lbl_803B53E4(size);
}

void fn_8027C04C(void *p)
{
    lbl_803B53E8(p);
}

unsigned int fn_8027C078(Bits_8027C078 *bits, int count)
{
    unsigned int value;

    value = bits->m4 & lbl_80301428[count];
    bits->m4 >>= count;
    bits->m8 -= count;
    if (bits->m8 <= 7) {
        bits->m4 |= *bits->m0++ << bits->m8;
        bits->m8 += 8;
    }
    return value;
}

void fn_8027C0D8(Bits_8027C078 *bits, int count)
{
    bits->m4 >>= count;
    bits->m8 -= count;
    if (bits->m8 <= 7) {
        bits->m4 |= *bits->m0++ << bits->m8;
        bits->m8 += 8;
    }
}

Codec_8027CF9C *fn_8027CF9C(void *memory)
{
    Codec_8027CF9C *p = (Codec_8027CF9C *)memory;

    p->mD44 = 0;
    p->mD54 = 0;
    p->mD58 = 0;
    p->mD50 = 0;
    p->mD52 = 0;
    p->mD5C = 0;
    p->mD60 = 0;
    p->mD64 = 1;
    return p;
}

int fn_8027CFCC(Codec_8027CF9C *p, unsigned char *data, int size, int count)
{
    if (data == 0 || p->mD54 != 0) {
        return -1;
    }
    p->mD54 = count;
    p->mD58 = size;
    p->mD44 = 0;
    p->mD48 = data;
    if (p->mD64 == 1) {
        if (*data == 0xEE) {
            p->mD60 = 1;
        } else {
            p->mD60 = 0;
        }
        fn_8027CA34(p, data + 1, p, p->mD5C);
    } else {
        fn_8027CA34(p, data, p, p->mD5C);
    }
    return 0;
}

int CodecReadSamples(Codec_8027CF9C *p, float **dst, int count)
{
    int total;
    int left;
    int n;
    unsigned char *src;
    float *out;
    short i;
    short value;
    unsigned char *d;
    unsigned char *e;
    unsigned char *f;

    n = p->mD44;
    if (p->mD54 == 0) {
        return 0;
    }
    p->mD4C = *dst;
    total = p->mD54;
    if (total > count) {
        total = count;
    }
    left = total;
    while (left > 0) {
        if (left < n) {
            n = left;
        }
        lbl_80301000(p->mD4C, &p->m684[432 - p->mD44], n * 4);
        left -= n;
        p->mD4C += n;
        p->mD44 -= n;
        if (left <= 0) {
            break;
        }
        fn_8027CBA4(p);
        p->mD44 = 432;
        n = 432;
        if (p->mD64 == 1) {
            p->mD48 = p->m0 - 1;
            src = p->mD48;
            if (p->mD60 != 0) {
                d = (unsigned char *)&p->mD52;
                d[0] = src[0];
                d[1] = src[1];
                src += 2;
                e = (unsigned char *)&p->mD50;
                e[0] = src[0];
                e[1] = src[1];
                src += 2;
                p->mD48 = p->mD48 + p->mD50 * 2 + 4;
                p->m0 = p->mD48 + 1;
                out = &p->m684[p->mD52];
                for (i = 0; i < p->mD50; i++) {
                    f = (unsigned char *)&value;
                    f[0] = src[0];
                    f[1] = src[1];
                    src += 2;
                    *out++ = value;
                }
                p->mD60 = 0;
            }
            if (*p->mD48 == 0xEE) {
                p->mD60 = 1;
            }
            p->m8 = 8;
            p->m4 = *p->m0;
            p->m0++;
        }
    }
    p->mD54 -= total;
    return total;
}

Format_8027D284 fn_8027D284(Codec_8027CF9C *p)
{
    Format_8027D284 format;

    format.m0 = p->m4;
    format.m8 = p->mD5C;
    format.m4 = p->mD44;
    return format;
}

void fn_8027D2C4(Codec_8027CF9C *p, Format_8027D284 *format, int flags)
{
    p->m4 = format->m0;
    p->mD5C = format->m8;
    p->mD44 = format->m4;
}

void fn_8027D2E0(Codec_8027CF9C *p, int mode)
{
    p->mD64 = mode;
}

}
