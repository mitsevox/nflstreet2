/* Pass-through codec for the compression library: copies data unchanged. */

#include "engine/GCmp.h"

void *_NONECoStart(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int _NONECoProcess(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char value;

    if (GCmpRead(pSrc, &value, 1) == 0) {
        return 1;
    }
    GCmpWrite(pDst, &value, 1);
    return 0;
}

void _NONECoStop(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}

void *_NONEDecStart(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int _NONEDecProcess(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char value;

    if (GCmpRead(pSrc, &value, 1) == 0) {
        return 1;
    }
    GCmpWrite(pDst, &value, 1);
    return 0;
}

void _NONEDecStop(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}
