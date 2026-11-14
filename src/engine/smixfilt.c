/* Mixer filter insert (smixfilt.c): builds a filter node from a filter definition and adds it to a
   mixer voice's filter chain. */

#include "engine/sndlib.h"

void MIX_filteradd(int index, int slot, Desc_80276798 *desc)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node = (Node_80279D90 *)SNDMEMI_allocz(desc->m4);

    desc->mC(node, desc->m0, slot);
    node->m18 = desc->mA;
    node->m0 = desc->m10;
    node->m4 = desc->m14;
    node->m1A = 0;
    SFILTER_add(&record->m40, node);
}
