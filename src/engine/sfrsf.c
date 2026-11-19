/* Sound filter (sfrsf.c): the resampling filter: its pitch setter, the processing callback that pulls
   input from the next node and converts it at the 16.16 pitch, and its init. */

#include "engine/sndsys.h"

extern "C" {

void rsflc(int count, float *src, float *dst, int *pos, void *phase, unsigned int stepHi,
           unsigned int stepLo);

void SFILTER_rsfsetpitch(Node_80279D90 *node, int value)
{
    ((SndRsfState_t *)node)->m1C = value;
}

int SFILTER_rsf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndRsfState_t *s = (SndRsfState_t *)node;
    float *in = a;
    float *out = b;
    float *hist;
    int n;
    int got = count;
    int i;
    int pos;
    unsigned int phase;

    if (s->m1C == 0x10000) {
        n = count;
        if (s->m28 == 0) {
            n = count + (4 - s->m2A);
        } else {
            for (i = 0; i < 4 - s->m2A; i++) {
                *out++ = s->m2C[i + s->m2A];
            }
        }
        if (s->mNode.m8 != 0) {
            got = s->mNode.m8->m0(s->mNode.m8, n, a, out, s->mNode.m1A);
        }
        if (got <= 0) {
            // FAKEMATCH: goto into the second path's flush block; the target has one copy of it
            goto flush;
        }
        if (s->m28 == 0) {
            s->m28 = 1;
            hist = out + (count - s->m2A);
        } else {
            hist = out + (count - 4);
        }
        s->m2C[0] = hist[0];
        s->m2C[1] = hist[1];
        s->m2C[2] = hist[2];
        s->m2C[3] = hist[3];
        return count;
    }

    n = (s->m1C * count + s->m20) >> 16;
    if (s->m28 == 0) {
        n = n + (4 - s->m2A);
        for (i = 0; i < s->m2A; i++) {
            *in++ = 0.0f;
        }
    } else {
        in[0] = s->m2C[0];
        in[1] = s->m2C[1];
        in[2] = s->m2C[2];
        in[3] = s->m2C[3];
        in += 4;
    }
    if (n > 0 && s->mNode.m8 != 0) {
        got = s->mNode.m8->m0(s->mNode.m8, n, b, in, s->mNode.m1A);
        if (got <= 0) {
        flush:
            if (s->m28 == 0) {
                s->m28 = 1;
            }
            s->m2C[0] = 0.0f;
            s->m2C[1] = 0.0f;
            s->m2C[2] = 0.0f;
            s->m2C[3] = 0.0f;
            return got;
        }
    }
    if (s->m28 != 0) {
        in -= 4 - s->m2A;
    } else {
        s->m28 = 1;
    }
    pos = 0;
    phase = s->m20 << 16;
    s->m24(count, in, b, &pos, &phase, (unsigned int)s->m1C >> 16, s->m1C << 16);
    s->m20 = (pos << 16) | (phase >> 16);
    hist = in + ((s->m20 >> 16) - s->m2A);
    s->m2C[0] = hist[0];
    s->m2C[1] = hist[1];
    s->m2C[2] = hist[2];
    s->m2C[3] = hist[3];
    s->m20 &= 0xFFFF;
    return count;
}

void SFILTER_rsfinit(Node_80279D90 *node, int a, int b)
{
    SndRsfState_t *s = (SndRsfState_t *)node;
    int i;

    s->mNode.m0 = SFILTER_rsf;
    s->mNode.m4 = 0;
    s->m20 = 0;
    s->m28 = 0;
    s->m2A = 0;
    if (b == 0) {
        s->m24 = rsflc;
    }
    for (i = 0; i < 4; i++) {
        s->m2C[i] = 0.0f;
    }
}

}
