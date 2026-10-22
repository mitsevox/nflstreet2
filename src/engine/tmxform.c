#include <dolphin/gx/GXTransform.h>
#include "engine/tmlib.h"

extern void fn_801D0F80(f32 mtx[3][4]);

void fn_8020FA38(u32 id, f32 (*pMtx)[4])
{
    f32 aMtx[4][4];

    if (pMtx == 0) {
        fn_801D0F80(aMtx);
        pMtx = aMtx;
    }
    GXLoadPosMtxImm(pMtx, id);
    GXLoadNrmMtxImm(pMtx, id);
}

void fn_8020FA8C(u32 id)
{
    GXSetCurrentMtx(id);
}
