#include "game/Frame_8019D3B8.h"
#include "game/fn_801BE60C.h"
#include "game/Player_8003877C.h"

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
    t = (1.0f - fn_801CFB94((int)(t * 8388608.0f))) * 0.5f;

    pBlend->mUnknown0 = 2;
    pBlend->mUnknown4[0].mUnknown4 = 1.0f;
    pBlend->mUnknown4[0].mUnknown8 = index == 0;
    pBlend->mUnknown4[0].mpUnknown40 = lbl_8030F958[(signed char)p->mUnknown5];
    pBlend->mUnknown4[1].mUnknown4 = 1.0f - t;
    pBlend->mUnknown4[1].mUnknown8 = index == 0;
    pBlend->mUnknown4[1].mpUnknown40 = lbl_8030F958[(signed char)p->mUnknown4];
    return pBlend;
}

extern "C" void fn_800AE018(Player_8003877C *p, int side, unsigned short key)
{
    if (p->mObject.mIdBytes[3] == 1) {
        p->mObject.mUnknown1008.mUnknown0 = key;
        p->mObject.mUnknown1008.mUnknown1 = key >> 8;
        p->mObject.mUnknown1008.mUnknown2 = side;
        if (side == 1) {
            fn_801BE068(p->mUnknown4528[1], &p->mUnknown4008[1], p->mUnknown4032[1], 2, p, 1.0f);
        } else {
            fn_801BE068(p->mUnknown4528[side], &p->mUnknown4008[side], p->mUnknown4032[side], 3, p, 1.0f);
        }
    }
}
