/* Sound random numbers (srandom.c): a 192-bit add-with-carry generator seeded from a fixed table. */

#include "engine/sndbank.h"

unsigned int SNDIrandseedorig[6] = {
    0xF22D0E56, 0x883126E9, 0xC624DD2F, 0x0702C49C, 0x9E353F7D, 0x6FDF3B64,
};

unsigned int SNDIrandstate[6];

void SNDI_randomseed(unsigned int seed)
{
    int i;

    for (i = 0; i <= 5; i++) {
        SNDIrandstate[i] = SNDIrandseedorig[i] + seed;
    }
}

unsigned int iSNDrandom(void)
{
    unsigned int carry = 0;
    unsigned int sum = SNDIrandstate[5] + SNDIrandstate[4];

    if (sum < SNDIrandstate[5] || sum < SNDIrandstate[4]) {
        carry = 1;
    }
    SNDIrandstate[4] = sum;
    sum = sum + SNDIrandstate[3] + carry;
    carry = sum < SNDIrandstate[3];
    SNDIrandstate[3] = sum;
    sum = sum + SNDIrandstate[2] + carry;
    carry = sum < SNDIrandstate[2];
    SNDIrandstate[2] = sum;
    sum = sum + SNDIrandstate[1] + carry;
    carry = sum < SNDIrandstate[1];
    SNDIrandstate[1] = sum;
    sum = sum + SNDIrandstate[0] + carry;
    SNDIrandstate[0] = sum;
    if (++SNDIrandstate[5] == 0 && ++SNDIrandstate[4] == 0 && ++SNDIrandstate[3] == 0 && ++SNDIrandstate[2] == 0 &&
        ++SNDIrandstate[1] == 0) {
        sum = ++SNDIrandstate[0];
    }
    return sum;
}

