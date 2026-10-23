#include "game/Object_80039F5C.h"
#include "game/cu_8008E978.h"

extern "C" float fn_8016B9B0(void);

extern "C" void fn_800A481C(Object_80039F5C *p, Object_80039F5C *pOther, int index,
                            Params_800A4E8C *pParams)
{
    pParams->mUnknown4 += pParams->mUnknown4 / 2;
    pParams->mUnknown0 += pParams->mUnknown0 / 2;
    if (p->mUnknown2914 == 16)
        pParams->mUnknown8 = 255;
    switch (pParams->mUnknown10) {
    case 0:
        break;
    case 1:
        pParams->mUnknown8 += pParams->mUnknown8 / 6;
        break;
    case 2:
        pParams->mUnknown8 = 255;
        break;
    }
    pParams->mUnknown8 = (unsigned int)((float)pParams->mUnknown8 * (1.0f - fn_8016B9B0()));
}
