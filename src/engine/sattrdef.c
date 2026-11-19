/* Sound attribute defaults (sattrdef.c): fills a patch's sample-attribute record with its default
   values before the patch decoder and the stream setup fill in what the patch gives. */

#include "engine/sndsys.h"
#include "engine/sndbank.h"

extern "C" {

int SND_attrsetdef(SndSampleAttr_t *p)
{
    int i;

    // FAKEMATCH: search-found store order (+0 after the first three bytes) for the scheduler's store order
    p->m2 = 0;
    p->m3 = 127;
    p->m4 = 64;
    p->m0 = 0;
    p->m5 = 0;
    p->m6 = 0;
    p->m7 = 2;
    p->m8 = 512;
    for (i = 0; i < 4; i++) {
        p->m48[i] = 0;
        p->m58[i] = 0;
    }
    for (i = 0; i < 6; i++) {
        p->mC[i] = 0;
        p->m18[i] = 0;
    }
    return 0;
}

}
