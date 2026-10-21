#include "game/fn_80147908.h"

extern "C" void fn_80147908(unsigned int a, unsigned int b, unsigned int *pColor,
                            float *pValue, float t, float x, float y)
{
    unsigned int ar = (a >> 16) & 255;
    unsigned int ag = (a >> 8) & 255;
    unsigned int ab = a & 255;
    unsigned int br = (b >> 16) & 255;
    unsigned int bg = (b >> 8) & 255;
    unsigned int bb = b & 255;

    *pValue = x * (1.0f - t) + y * t;
    unsigned int r = (unsigned int)(ar * (1.0f - t) + br * t);
    unsigned int g = (unsigned int)(ag * (1.0f - t) + bg * t);
    unsigned int blue = (unsigned int)(ab * (1.0f - t) + bb * t);
    *pColor = (r << 16) + (g << 8) + blue;
}
