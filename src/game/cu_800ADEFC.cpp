#include "game/Frame_8019D3B8.h"

extern "C" {
float fn_801CFB94(int angle);

extern Blend_8019EDDC lbl_8030F534;
extern void *lbl_8030F958[11];
}

/* Blend between an element's current and next pose, eased over its
   duration. */
extern "C" Blend_8019EDDC *fn_800ADEFC(Element_80041BF8 *pElements, unsigned int index)
{
    Blend_8019EDDC *pBlend = &lbl_8030F534;
    Element_80041BF8 *p = &pElements[index];
    unsigned int length = p->mUnknown6 * 16;
    float t = (float)p->mUnknown8 / (float)length;
    float s = fn_801CFB94((int)(t * 8388608.0f));

    pBlend->mUnknown0 = 2;
    pBlend->mUnknown4[0].mUnknown4 = 1.0f;
    pBlend->mUnknown4[0].mUnknown8 = index == 0;
    pBlend->mUnknown4[1].mUnknown8 = index == 0;
    pBlend->mUnknown4[1].mUnknown4 = 1.0f - (1.0f - s) * 0.5f;
    pBlend->mUnknown4[0].mpUnknown40 = lbl_8030F958[(signed char)p->mUnknown5];
    pBlend->mUnknown4[1].mpUnknown40 = lbl_8030F958[(signed char)p->mUnknown4];
    return pBlend;
}
