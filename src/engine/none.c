/* Pass-through codec for the compression library: copies data unchanged. */

#include "engine/GCmp.h"

void *_NONECoStart(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    return 0;
}

int _NONECoProcess(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    unsigned char value;

    if (GCmpRead(pSrc, &value, 1) == 0) {
        return 1;
    }
    GCmpWrite(pDst, &value, 1);
    return 0;
}

void _NONECoStop(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState)
{
}

void *_NONEDecStart(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    return 0;
}

int _NONEDecProcess(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    unsigned char value;

    if (GCmpRead(pSrc, &value, 1) == 0) {
        return 1;
    }
    GCmpWrite(pDst, &value, 1);
    return 0;
}

void _NONEDecStop(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState)
{
}
