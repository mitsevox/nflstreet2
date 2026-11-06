/* Keeps replay frames in auxiliary RAM: stores each recorded frame there and copies frames back
   into a ring of four main-RAM buffers for playback. */
#include "game/fn_801D2B7C.h"

extern "C" {
void fn_801C1D98(void *pDst, char *pSrc, int size);
void fn_801C1E78(char *pDst, void *pSrc, int size);
void *fn_801D2BB0(int a, int size, int c, int d);
}

static unsigned int _ReplayAuxRam_iScratchSlot = 0;
static char *_ReplayAuxRam_pScratch;
static char *_ReplayAuxRam_pFrames;

extern "C" void ReplayAuxRamStoreFrame(char *pSrc, int index, int size)
{
    fn_801C1D98(_ReplayAuxRam_pFrames + index * size, pSrc, size);
}

extern "C" char *ReplayAuxRamGetScratch(int a, int size)
{
    unsigned int slot = _ReplayAuxRam_iScratchSlot;

    if (++_ReplayAuxRam_iScratchSlot > 3) {
        _ReplayAuxRam_iScratchSlot = 0;
    }
    return _ReplayAuxRam_pScratch + slot * size;
}

extern "C" char *ReplayAuxRamLoadFrame(int index, int size)
{
    unsigned int slot = _ReplayAuxRam_iScratchSlot;
    char *pDst;

    if (++_ReplayAuxRam_iScratchSlot > 3) {
        _ReplayAuxRam_iScratchSlot = 0;
    }
    pDst = _ReplayAuxRam_pScratch + slot * size;
    fn_801C1E78(pDst, _ReplayAuxRam_pFrames + index * size, size);
    return pDst;
}

extern "C" void ReplayAuxRamInit(int count, int size)
{
    _ReplayAuxRam_pScratch = (char *)fn_801D2B7C(size * 4, 0, 0);
    _ReplayAuxRam_pFrames = (char *)fn_801D2BB0(16, count * size, 0, 0);
}

extern "C" void ReplayAuxRamShutdown(void)
{
    fn_801D2BD0(_ReplayAuxRam_pScratch);
    _ReplayAuxRam_pScratch = 0;
    fn_801D2BD0(_ReplayAuxRam_pFrames);
    _ReplayAuxRam_pFrames = 0;
}
