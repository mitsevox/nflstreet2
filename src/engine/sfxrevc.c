/* Mixer effect globals (sfxrevc.c): creates and frees the per-channel wet (effect send) buffers and
   the effect node lists of the software mixer, and returns one channel's wet buffer. */

#include "engine/sndlib.h"

static int fxGlobalsCreated = 0;

float *MIX_getwetbuffer(int index)
{
    return lbl_803B4E24[index];
}

void MIX_createFxglobals(void)
{
    int size = lbl_8030002C * sizeof(float *) + lbl_8030002C * sizeof(int) + lbl_8030002C * sizeof(float);
    float **buffer = (float **)SNDMEMI_allocz(size);

    lbl_803B4E24 = buffer;
    lbl_803B4E34.m14 = (int *)(buffer + lbl_8030002C);
    lbl_803B4E34.m100 = (float *)(lbl_803B4E34.m14 + lbl_8030002C);
    memset(buffer, 0, size);
    lbl_803B4E20 = (Node_803B4E20 **)SNDMEMI_allocz(lbl_8030002C * 4);
    memset(lbl_803B4E20, 0, lbl_8030002C * 4);
    fxGlobalsCreated = 1;
}

void MIX_destroyFxglobals(void)
{
    int i;

    if (fxGlobalsCreated != 0) {
        SNDMEMI_free(lbl_803B4E24);
        for (i = 0; i < lbl_8030002C; i++) {
            if (lbl_803B4E20[i] != 0) {
                Node_803B4E20 *node = lbl_803B4E20[i];

                do {
                    Node_803B4E20 *next = node->m0;

                    SNDMEMI_free(node);
                    node = next;
                } while (node != 0);
            }
        }
        SNDMEMI_free(lbl_803B4E20);
        fxGlobalsCreated = 0;
    }
}
