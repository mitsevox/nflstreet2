/* TM renderer transforms: loads a model matrix into a GX matrix slot and selects that slot. */

#include <dolphin/gx/GXTransform.h>
#include "engine/tmlib.h"

void TMXform(u32 id, f32 (*pMtx)[4])
{
    f32 aMtx[4][4];

    if (pMtx == 0) {
        fn_801D0F80(aMtx);
        pMtx = aMtx;
    }
    GXLoadPosMtxImm(pMtx, id);
    GXLoadNrmMtxImm(pMtx, id);
}

void TMXformSelect(u32 id)
{
    GXSetCurrentMtx(id);
}
