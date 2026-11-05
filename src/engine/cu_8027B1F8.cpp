/* Sound decoders, continued (neutral file name): more decoder constructors and callbacks, then the
   start of the MT block decoder. */

#include "engine/sndsys.h"

extern "C" {

void fn_8027B328(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B328 *decoder;

    decoder = (Decoder_8027B328 *)node;
    node->m0 = fn_8027B1F8;
    decoder->m28 = fn_802789E0(fn_80274304(params->m1C));
    decoder->m31 = fn_80274334(params->m1C);
    decoder->m20 = -1;
    decoder->m1C = 0;
    decoder->m24 = 0;
    decoder->m30 = params->m18;
    decoder->m2C = 0;
}

int fn_8027B39C(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027B464 *decoder;
    int n;

    decoder = (Decoder_8027B464 *)node;
    if (decoder->m28 >= decoder->m24) {
        return -1;
    }
    n = fn_8027BE24(decoder->m1C, &b, count);
    decoder->m28 += n;
    b += n;
    if (n < count) {
        count -= n;
        memset(b, 0, count * 4);
        n += count;
    }
    return n;
}

int fn_8027B430(Node_80279D90 *node)
{
    return ((Decoder_8027B464 *)node)->m28;
}

void fn_8027B438(Node_80279D90 *node)
{
    Decoder_8027B464 *decoder;

    decoder = (Decoder_8027B464 *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void fn_8027B464(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B464 *decoder;

    decoder = (Decoder_8027B464 *)node;
    node->m0 = fn_8027B39C;
    node->m4 = fn_8027B438;
    decoder->m20 = (char *)params->m0;
    decoder->m24 = params->mC;
    decoder->m28 = 0;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
    params->m28 = fn_8027B430;
    fn_8027BDE8(decoder->m1C, decoder->m20, decoder->m24 * 4, decoder->m24);
}

int fn_8027B77C(Node_80279D90 *node)
{
    return ((Decoder_8027B7B0 *)node)->m20;
}

void fn_8027B784(Node_80279D90 *node)
{
    Decoder_8027B7B0 *decoder;

    decoder = (Decoder_8027B7B0 *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void fn_8027B7B0(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B7B0 *decoder;

    decoder = (Decoder_8027B7B0 *)node;
    node->m0 = fn_8027B4F4;
    node->m4 = fn_8027B784;
    decoder->m20 = 0;
    decoder->m2C = params->m4;
    decoder->m30 = params->m24;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
    params->m28 = fn_8027B77C;
    if (decoder->m30 <= 2) {
        decoder->m34 = params->m0;
        decoder->m40 = 0;
        decoder->m38 = params->mC;
        decoder->m3C = 0;
        decoder->m44 = params->m10;
        decoder->m48 = params->m14;
    } else {
        fn_8027BDE8(decoder->m1C, (char *)params->m0, decoder->m24 * 4, decoder->m24);
    }
}

void fn_8027BA40(Node_80279D90 *node)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void fn_8027BA6C(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    node->m0 = fn_8027B888;
    node->m4 = fn_8027BA40;
    decoder->m30 = fn_802789E0(fn_80274304(params->m1C));
    decoder->m38 = fn_80274334(params->m1C);
    decoder->m2C = params->m24;
    decoder->m20 = 0;
    decoder->m24 = params->mC;
    decoder->m28 = 0;
    decoder->m34 = 0;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
}

void *fn_8027BD68(int size)
{
    return lbl_803B53E4(size);
}

void fn_8027BD94(void *p)
{
    lbl_803B53E8(p);
}

int fn_8027BDE8(Struct_8027BE24 *p, char *data, int size, int count)
{
    if (data == 0) {
        return -1;
    }
    if (p->m8 != 0) {
        return -1;
    }
    p->m8 = count;
    p->mC = size;
    p->m94.mC = data;
    return 0;
}

Pair_8027BFDC fn_8027BFDC(Struct_8027BE24 *p)
{
    Pair_8027BFDC pair;

    pair.m0 = p->m94.m4;
    pair.m4 = p->m94.m8;
    return pair;
}

void fn_8027C00C(Struct_8027BE24 *p, Pair_8027BFDC *pair)
{
    p->m94.m4 = pair->m0;
    p->m94.m8 = pair->m4;
}

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

}
