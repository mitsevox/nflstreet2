/* Sound filter (supmutpf.c): the unpack filter for MT-compressed samples, with its restore and
   init. */

#include "engine/sndsys.h"

extern "C" {

int fn_8027AEE4(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027B168 *decoder;
    Format_8027D284 format;
    int last;
    int total;
    int n;

    decoder = (Decoder_8027B168 *)node;
    total = 0;
    if (decoder->m28 != 0) {
        fn_8027952C(decoder->m24, decoder->m38, decoder->m28);
        decoder->m28 = 0;
    }
    while (count > 0) {
        n = fn_8027D05C(decoder->m34, &b, count);
        decoder->m2C += n;
        b += n;
        decoder->m28 += n;
        total += n;
        if (n < count) {
            count -= n;
            decoder->m1C = fn_802792F0(decoder->m24, decoder->m38, &decoder->m20, &last);
            if (decoder->m1C != 0) {
                decoder->m2C = 0;
                if (decoder->m30 <= 2) {
                    if (last == 0) {
                        format = fn_8027D284(decoder->m34);
                        format.m8 = 1;
                        fn_8027D2C4(decoder->m34, &format, 0);
                    } else {
                        format = fn_8027D284(decoder->m34);
                        format.m8 = 0;
                        fn_8027D2C4(decoder->m34, &format, 0);
                    }
                    fn_8027D2E0(decoder->m34, 0);
                } else {
                    if (last == 0) {
                        format = fn_8027D284(decoder->m34);
                        format.m4 = 0;
                        format.m8 = 1;
                    } else {
                        format = fn_8027D284(decoder->m34);
                        format.m8 = 0;
                    }
                    fn_8027D2C4(decoder->m34, &format, 0);
                    fn_8027D2E0(decoder->m34, 1);
                }
                fn_8027CFCC(decoder->m34, decoder->m1C + 1, decoder->m20 * 4, decoder->m20);
            } else {
                if (count > 0 && decoder->m28 != 0) {
                    memset(b, 0, count * 4);
                }
                decoder->m20 = 0;
                count = 0;
            }
        } else {
            count -= n;
        }
    }
    return total;
}

void fn_8027B13C(Node_80279D90 *node)
{
    Decoder_8027B168 *decoder;

    decoder = (Decoder_8027B168 *)node;
    if (decoder->m34 != 0) {
        fn_8027C04C(decoder->m34);
    }
}

void fn_8027B168(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B168 *decoder;

    decoder = (Decoder_8027B168 *)node;
    node->m0 = fn_8027AEE4;
    decoder->m24 = fn_802789E0(fn_80274304(params->m1C));
    decoder->m38 = fn_80274334(params->m1C);
    decoder->m1C = 0;
    decoder->m2C = 0;
    decoder->m30 = params->m24;
    decoder->m20 = params->mC;
    node->m4 = fn_8027B13C;
    decoder->m34 = fn_8027CF9C(fn_8027C020(3432));
    decoder->m28 = 0;
}

}
