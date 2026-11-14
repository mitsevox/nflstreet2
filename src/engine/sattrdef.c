/* Sound attribute defaults (sattrdef.c): fills a play-attribute record with its default values. */

#include "engine/sndsys.h"

extern "C" {

/* Record set up by 0x80277CF0 (callers 0x8026C4DC and 0x8027838C); partial layout. */
typedef struct Channel_80277CF0 {
    unsigned short m0;
    unsigned char m2;
    unsigned char m3;
    unsigned char m4;
    unsigned char m5;
    unsigned char m6;
    unsigned char m7;
    unsigned short m8;
    unsigned char mUnknownA[2];
    short mC[6];
    int m18[6];
    unsigned char mUnknown30[0x18];
    int m48[4];
    int m58[4];
} Channel_80277CF0;

int SND_attrsetdef(Channel_80277CF0 *p)
{
    int i;

    p->m2 = 0;
    p->m3 = 127;
    p->m4 = 64;
    p->m6 = 0;
    p->m7 = 2;
    p->m8 = 512;
    p->m0 = 0;
    p->m5 = 0;
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
