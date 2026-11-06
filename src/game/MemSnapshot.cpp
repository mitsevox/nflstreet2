/* Copies a block of memory aside and later copies it back; the front-end DLL module uses
   it to keep a code range while that memory is reused. */

#include "game/fn_801D2B7C.h"
extern "C" {
void fn_801C1D98(void *pDst, char *pSrc, int size);
void fn_801C1E78(char *pDst, void *pSrc, int size);
void *fn_801D2BB0(int a, int size, int c, int d);
}

static void *_MemSnapshot_pBuffer = 0;
static int _MemSnapshot_iSize;
static char *_MemSnapshot_pStart;

extern "C" void MemSnapshotRestore(char *pStart, char *pEnd)
{
    fn_801C1E78(_MemSnapshot_pStart, _MemSnapshot_pBuffer, _MemSnapshot_iSize);
    fn_801D2BD0(_MemSnapshot_pBuffer);
    _MemSnapshot_pBuffer = 0;
}

extern "C" void MemSnapshotSave(char *pStart, char *pEnd)
{
    int size = (pEnd - pStart + 31) & ~31;

    _MemSnapshot_pBuffer = fn_801D2BB0(16, size, 0, 0);
    fn_801C1D98(_MemSnapshot_pBuffer, pStart, size);
    _MemSnapshot_iSize = size;
    _MemSnapshot_pStart = pStart;
}
