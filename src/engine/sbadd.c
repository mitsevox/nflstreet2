/* Partial source of the sound library's bank registration (sbadd.c). */

#include "engine/sndaems.h"

extern "C" {

typedef struct Object_8026A40C {
    unsigned char mUnknown0[23];
    signed char mUnknown17;
    unsigned char mUnknown18[28];
    int mUnknown34[4];
    int mUnknown44[4];
} Object_8026A40C;

typedef struct Message_8026A40C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    // FAKEMATCH: two unwritten words that give the target's 0x48-byte frame; whether the callbacks read them is not established
    int mUnknownC[2];
} Message_8026A40C;

void fn_8026A40C(Object_8026A40C *p, int value)
{
    Message_8026A40C message;
    int i;

    while (p->mUnknown17 > 0) {
        p->mUnknown17--;
        message.mUnknown0 = value;
        message.mUnknown4 = p->mUnknown34[p->mUnknown17];
        message.mUnknown8 = p->mUnknown44[p->mUnknown17];
        for (i = 0; i < lbl_803A6C24.mUnknown16E; i++)
            lbl_803A6C24.mUnknown1A4[i](&message);
    }
}
}
