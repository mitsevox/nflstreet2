#include "engine/tmlib.h"

void fn_802160A0(Swap_802160A0 *pSwap, void *pOldBase, void *pNewBase)
{
    unsigned short i;
    unsigned short j;

    pSwap->mpSlots = fn_8020EB94(pSwap->mpSlots, pOldBase, pNewBase);
    pSwap->mpStates = fn_8020EB94(pSwap->mpStates, pOldBase, pNewBase);
    pSwap->mpNodeIndices = fn_8020EB94(pSwap->mpNodeIndices, pOldBase, pNewBase);
    for (i = 0; i < pSwap->mNumSlots; i++) {
        SwapSlot_802160A0 *pSlot = fn_8021616C(pSwap, i);

        for (j = 0; j < pSlot->mNumStates; j++) {
            SwapState_802160A0 *pState = fn_80216190(pSwap, i, j);

            pState->mNumActive = pState->mNumNodes;
        }
    }
}

SwapSlot_802160A0 *fn_8021616C(Swap_802160A0 *pSwap, int slot)
{
    if (slot < (int)pSwap->mNumSlots) {
        return &pSwap->mpSlots[slot];
    }
    return 0;
}

SwapState_802160A0 *fn_80216190(Swap_802160A0 *pSwap, int slot, int state)
{
    if (slot < (int)pSwap->mNumSlots) {
        SwapSlot_802160A0 *pSlot = &pSwap->mpSlots[slot];

        if (state < pSlot->mNumStates) {
            return &(pSwap->mpStates + pSlot->mFirstState)[state];
        }
    }
    return 0;
}

int fn_802161D8(Swap_802160A0 *pSwap, unsigned short *pNodes, int slot, int state)
{
    SwapState_802160A0 *pState;
    unsigned int numNodes = 0;
    unsigned int i;

    pState = fn_80216190(pSwap, slot, state);
    if (pState != 0) {
        numNodes = pState->mNumNodes;
        for (i = 0; i < numNodes; i++) {
            pNodes[i] = pSwap->mpNodeIndices[pState->mFirstNode + i];
        }
    }
    return numNodes;
}

