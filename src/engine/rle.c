#include <string.h>
#include "engine/GCmp.h"

extern void *fn_801D310C(void *allocation, int size, int c, int d);

void *fn_802802A0(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int fn_802802A8(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char *pIn = pSrc->mpData;
    unsigned int size = pSrc->mSize;
    unsigned int pos = pSrc->mPos;
    unsigned char *pOut = pDst->mpData;
    unsigned int outPos = pDst->mPos;
    unsigned int capacity = pDst->mSize;
    unsigned char value;
    unsigned char run;
    unsigned char marker = '!';
    int escape;
    unsigned int length;

    while (pos < size) {
        value = pIn[pos];
        run = 1;
        pos++;
        while (pos < size && run < 255 && pIn[pos] == value) {
            run++;
            pos++;
        }
        if (run > 3 || value == marker) {
            escape = 1;
            length = 3;
        } else {
            escape = 0;
            length = run;
        }
        while (outPos + length > capacity) {
            pOut = fn_801D310C(pOut, capacity * 2, 0, 0);
            capacity *= 2;
        }
        if (escape) {
            pOut[outPos++] = marker;
            pOut[outPos++] = value;
            pOut[outPos++] = run;
        } else {
            memset(&pOut[outPos], value, run);
            outPos += run;
        }
    }
    pSrc->mPos = pos;
    pDst->mPos = outPos;
    pDst->mSize = capacity;
    pDst->mpData = pOut;
    return 1;
}

void fn_802803F8(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}

void *fn_802803FC(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

int fn_80280404(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    unsigned char *pIn = pSrc->mpData;
    unsigned int size = pSrc->mSize;
    unsigned int pos = pSrc->mPos;
    unsigned char *pOut = pDst->mpData;
    unsigned int outPos = pDst->mPos;
    unsigned int capacity = pDst->mSize;
    unsigned char value;
    unsigned char run;

    while (pos < size) {
        value = pIn[pos];
        run = 1;
        pos++;
        if (value == '!') {
            value = pIn[pos];
            pos++;
            run = pIn[pos];
            pos++;
        }
        while (outPos + run > capacity) {
            pOut = fn_801D310C(pOut, capacity * 2, 0, 0);
            capacity *= 2;
        }
        if (run == 1) {
            pOut[outPos++] = value;
        } else {
            memset(&pOut[outPos], value, run);
            outPos += run;
        }
    }
    pSrc->mPos = pos;
    pDst->mPos = outPos;
    pDst->mSize = capacity;
    pDst->mpData = pOut;
    return 1;
}

void fn_80280500(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}
