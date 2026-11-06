/* Swappable model parts: for each slot and state, the list of geometry nodes to draw, with
   relocation after loading and lookups. */

#include "engine/tmlib.h"

void TMSwapRelocateChunk(TMSwapDef_t *pSwap, void *pOldBase, void *pNewBase)
{
    unsigned short i;
    unsigned short j;

    pSwap->mpSlots = TMModelResRelocatePtr(pSwap->mpSlots, pOldBase, pNewBase);
    pSwap->mpStates = TMModelResRelocatePtr(pSwap->mpStates, pOldBase, pNewBase);
    pSwap->mpNodeIndices = TMModelResRelocatePtr(pSwap->mpNodeIndices, pOldBase, pNewBase);
    for (i = 0; i < pSwap->mNumSlots; i++) {
        TMSwapSlot_t *pSlot = TMSwapGetNode(pSwap, i);

        for (j = 0; j < pSlot->mNumStates; j++) {
            TMSwapState_t *pState = TMSwapGetState(pSwap, i, j);

            pState->mNumActive = pState->mNumNodes;
        }
    }
}

TMSwapSlot_t *TMSwapGetNode(TMSwapDef_t *pSwap, int slot)
{
    if (slot < (int)pSwap->mNumSlots) {
        return &pSwap->mpSlots[slot];
    }
    return 0;
}

TMSwapState_t *TMSwapGetState(TMSwapDef_t *pSwap, int slot, int state)
{
    if (slot < (int)pSwap->mNumSlots) {
        TMSwapSlot_t *pSlot = &pSwap->mpSlots[slot];

        if (state < pSlot->mNumStates) {
            return &(pSwap->mpStates + pSlot->mFirstState)[state];
        }
    }
    return 0;
}

int TMSwapGetGeomRefs(TMSwapDef_t *pSwap, unsigned short *pNodes, int slot, int state)
{
    TMSwapState_t *pState;
    unsigned int numNodes = 0;
    unsigned int i;

    pState = TMSwapGetState(pSwap, slot, state);
    if (pState != 0) {
        numNodes = pState->mNumNodes;
        for (i = 0; i < numNodes; i++) {
            pNodes[i] = pSwap->mpNodeIndices[pState->mFirstNode + i];
        }
    }
    return numNodes;
}

