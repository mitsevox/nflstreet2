/* Sound decoders (neutral file name): sample conversion callbacks, the ordered node list and the
   decoder constructors for each sample format. */

#include "engine/sndsys.h"

extern "C" {

int fn_80279BC0(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    int i;
    int value;
    int clamped;

    for (i = 0; i < count; i++) {
        value = (int)a[i];
        if (value < -32767) {
            clamped = -32767;
        } else if (value > 32767) {
            clamped = 32767;
        } else {
            clamped = value;
        }
        ((int *)b)[i] = clamped;
    }
    return count;
}

void fn_80279C20(Node_80279D90 *node)
{
    node->m0 = fn_80279BC0;
    node->m4 = 0;
}

int fn_80279C38(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    int n;

    if (node->m8 != 0) {
        n = node->m8->m0(node->m8, count, b, a, node->m1A);
        if (n <= 0) {
            return n;
        }
    } else {
        n = count;
    }
    fn_8027A248(&((Struct_80279C38 *)node)->m1C, n, a, b);
    return n;
}

int fn_80279CB8(Node_80279D90 *node)
{
    node->m8 = 0;
    node->mC = 0;
    node->m10 = 0;
    node->m14 = 0;
    node->m1B = 0;
    node->m4 = 0;
    node->m0 = fn_80279C38;
    fn_8027A21C(&((Struct_80279C38 *)node)->m1C);
    return 0;
}

void fn_80279D90(Node_80279D90 **list, Node_80279D90 *node)
{
    Node_80279D90 *prev;
    Node_80279D90 *cur;

    prev = 0;
    cur = *list;
    while (cur != 0 && cur->m18 < node->m18) {
        prev = cur;
        cur = cur->m8;
    }
    node->m8 = cur;
    if (cur != 0) {
        cur->m10 = node;
    }
    if (prev == 0) {
        *list = node;
    } else {
        prev->m8 = node;
        node->m10 = prev;
    }
}

void fn_80279DF8(Node_80279D90 **list, Node_80279D90 *node)
{
    Node_80279D90 *prev = *list;
    Node_80279D90 *cur;
    if (node == prev) {
        *list = prev->m8;
        return;
    }
    cur = prev->m8;
    while (cur != 0 && cur != node) {
        prev = cur;
        cur = prev->m8;
    }
    if (cur != 0 && cur == node) {
        node = node->m8;
        if (node != 0) {
            node->m10 = prev;
        }
        prev->m8 = prev->m8->m8;
    }
}

void fn_8027A21C(State_8027A248 *state)
{
    state->m0[0] = 0.0f;
    state->m0[1] = 0.0f;
    state->m0[2] = 0.0f;
    state->m0[3] = 0.0f;
    state->m0[4] = 0.0f;
    state->m0[5] = 0.0f;
    state->m0[6] = 0.0f;
    state->m0[7] = 0.0f;
}

void fn_8027A248(State_8027A248 *state, int count, float *in, float *out)
{
    int i;
    for (i = 0; i < count; i++) {
        out[i] = state->m20 * (in[i] + state->m0[7]) +
                 state->m24 * (state->m0[0] + state->m0[6]) +
                 state->m28 * (state->m0[1] + state->m0[5]) +
                 state->m2C * (state->m0[2] + state->m0[4]) +
                 state->m30 * state->m0[3];
        state->m0[7] = state->m0[6];
        state->m0[6] = state->m0[5];
        state->m0[5] = state->m0[4];
        state->m0[4] = state->m0[3];
        state->m0[3] = state->m0[2];
        state->m0[2] = state->m0[1];
        state->m0[1] = state->m0[0];
        state->m0[0] = in[i];
    }
}

void fn_8027A4C0(Node_80279D90 *node, int value)
{
    ((Struct_8027A4C0 *)node)->m1C = value;
}

void fn_8027A9FC(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027AB00(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027AC08(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027AE04(Node_80279D90 *node, Params_80275F80 *params);

void fn_8027A7FC(void)
{
    lbl_803B4E34.m18[0][0] = fn_8027A9FC;
    lbl_803B4E34.m60[0][0] = 44;
    lbl_803B4E34.m18[0][1] = fn_8027AB00;
    lbl_803B4E34.m60[0][1] = 48;
    lbl_803B4E34.m18[0][2] = fn_8027B328;
    lbl_803B4E34.m60[0][2] = 52;
}

void fn_8027A844(void)
{
    lbl_803B4E34.m18[2][0] = fn_8027AC08;
    lbl_803B4E34.m60[2][0] = 44;
    lbl_803B4E34.m18[2][2] = SFILTER_unpackmtpfinit;
    lbl_803B4E34.m60[2][2] = 60;
    lbl_803B4E34.m18[2][1] = fn_8027AE04;
    lbl_803B4E34.m60[2][1] = 48;
    lbl_803B4E34.m18[3][0] = fn_8027AC08;
    lbl_803B4E34.m60[3][0] = 44;
    lbl_803B4E34.m18[3][2] = SFILTER_unpackmtpfinit;
    lbl_803B4E34.m60[3][2] = 60;
    lbl_803B4E34.m18[3][1] = fn_8027AE04;
    lbl_803B4E34.m60[3][1] = 48;
}

void fn_8027A8A4(void)
{
    lbl_803B4E34.m18[1][0] = fn_8027B464;
    lbl_803B4E34.m60[1][0] = 44;
    lbl_803B4E34.m60[1][1] = 84;
    lbl_803B4E34.m18[1][1] = fn_8027B7B0;
    lbl_803B4E34.m18[1][2] = fn_8027BA6C;
    lbl_803B4E34.m60[1][2] = 60;
}

void fn_8027A8EC(int count, float *src, float *dst, float gain)
{
    int i;

    for (i = 0; i < count; i++) {
        dst[i] = src[i] * gain + dst[i];
    }
}

int fn_8027A91C(Node_80279D90 *node)
{
    return ((Decoder_8027A9FC *)node)->m20;
}

int fn_8027A924(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027A9FC *decoder;
    unsigned int pos;
    int n;

    decoder = (Decoder_8027A9FC *)node;
    pos = decoder->m20;
    if (pos >= decoder->m24) {
        return -1;
    }
    decoder->m20 = pos + count;
    if (decoder->m20 < decoder->m24) {
        if (decoder->m28 != 0) {
            lbl_803B4E34.m1E4(count, (short *)(decoder->m1C + (pos << 1)), b);
        }
    } else {
        n = decoder->m24 - pos;
        if (decoder->m28 != 0) {
            lbl_803B4E34.m1E4(n, (short *)(decoder->m1C + (pos << 1)), b);
        }
        memset(b + n, 0, (count - n) * 4);
    }
    return 1;
}

void fn_8027A9FC(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027A9FC *decoder;

    decoder = (Decoder_8027A9FC *)node;
    node->m0 = fn_8027A924;
    decoder->m1C = params->m0;
    decoder->m20 = 0;
    decoder->m24 = params->mC;
    decoder->m28 = params->m18;
    params->m28 = fn_8027A91C;
    node->m4 = 0;
}

int fn_8027AA3C(Node_80279D90 *node)
{
    return ((Decoder_8027AB00 *)node)->m20;
}

int fn_8027AA44(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027AB00 *decoder;
    int n;

    decoder = (Decoder_8027AB00 *)node;
    while (count > 0) {
        n = decoder->m28 - decoder->m20 + 1;
        if (count < n) {
            n = count;
        }
        if (decoder->m2C != 0) {
            lbl_803B4E34.m1E4(n, (short *)(decoder->m1C + (decoder->m20 << 1)), b);
        }
        b += n;
        decoder->m20 += n;
        count -= n;
        if (decoder->m20 > decoder->m28) {
            decoder->m20 = decoder->m24;
        }
    }
    return 1;
}

void fn_8027AB00(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027AB00 *decoder;

    decoder = (Decoder_8027AB00 *)node;
    node->m0 = fn_8027AA44;
    decoder->m1C = params->m0;
    decoder->m20 = 0;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m2C = params->m18;
    params->m28 = fn_8027AA3C;
}

int fn_8027AB44(Node_80279D90 *node)
{
    return ((Decoder_8027AC08 *)node)->m20;
}

int fn_8027AB4C(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027AC08 *decoder;
    int n;

    decoder = (Decoder_8027AC08 *)node;
    if (decoder->m20 >= decoder->m1C) {
        return -1;
    }
    n = fn_8027D05C(decoder->m28, &b, count);
    decoder->m20 += n;
    b += n;
    if (n < count) {
        count -= n;
        memset(b, 0, count * 4);
    }
    return 1;
}

void fn_8027ABDC(Node_80279D90 *node)
{
    Decoder_8027AC08 *decoder;

    decoder = (Decoder_8027AC08 *)node;
    if (decoder->m28 != 0) {
        fn_8027C04C(decoder->m28);
    }
}

void fn_8027AC08(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027AC08 *decoder;
    Format_8027D284 format;

    decoder = (Decoder_8027AC08 *)node;
    node->m0 = fn_8027AB4C;
    decoder->m1C = params->mC;
    decoder->m20 = 0;
    decoder->m24 = params->m24;
    params->m28 = fn_8027AB44;
    node->m4 = fn_8027ABDC;
    decoder->m28 = fn_8027CF9C(fn_8027C020(3432));
    format = fn_8027D284(decoder->m28);
    format.m8 = 1;
    fn_8027D2C4(decoder->m28, &format, 0);
    if (decoder->m24 <= 2) {
        fn_8027D2E0(decoder->m28, 0);
    } else {
        fn_8027D2E0(decoder->m28, 1);
    }
    fn_8027CFCC(decoder->m28, (unsigned char *)params->m0, decoder->m1C * 4, decoder->m1C);
}

int fn_8027AD08(Node_80279D90 *node)
{
    return ((Decoder_8027AE04 *)node)->m20;
}

int fn_8027AD10(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027AE04 *decoder;
    Format_8027D284 format;
    int n;

    decoder = (Decoder_8027AE04 *)node;
    while (count > 0) {
        n = fn_8027D05C(decoder->m1C, &b, count);
        b += n;
        decoder->m20 += n;
        count -= n;
        if (n < count) {
            decoder->m20 = decoder->m24;
            format.m4 = 0;
            format.m0 = 0;
            format.m8 = 1;
            fn_8027D2C4(decoder->m1C, &format, 0);
            fn_8027CFCC(decoder->m1C, decoder->m2C, (decoder->m28 - decoder->m24 + 1) * 4,
                        decoder->m28 - decoder->m24 + 1);
        }
    }
    return 1;
}

void fn_8027ADD8(Node_80279D90 *node)
{
    Decoder_8027AE04 *decoder;

    decoder = (Decoder_8027AE04 *)node;
    if (decoder->m1C != 0) {
        fn_8027C04C(decoder->m1C);
    }
}

void fn_8027AE04(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027AE04 *decoder;
    Format_8027D284 format;

    decoder = (Decoder_8027AE04 *)node;
    node->m0 = fn_8027AD10;
    node->m4 = fn_8027ADD8;
    decoder->m2C = (unsigned char *)params->m4;
    decoder->m20 = 0;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m1C = fn_8027CF9C(fn_8027C020(3432));
    format = fn_8027D284(decoder->m1C);
    format.m8 = 1;
    fn_8027D2C4(decoder->m1C, &format, 0);
    fn_8027CFCC(decoder->m1C, (unsigned char *)params->m0, decoder->m24 * 4, decoder->m24);
    params->m28 = fn_8027AD08;
}

}
