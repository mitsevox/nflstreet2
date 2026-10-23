#include "game/Block_800B21D0.h"
#include "game/Step_800C4460.h"
#include "game/Object_80039F5C.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern "C" {
int fn_8017F494(void);
unsigned char fn_8017F48C(void);
void fn_8017F444(void);
void fn_800B2630(void);
int fn_801784E8(void);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8017C3E4(unsigned short team, short yards, int handle);

extern Block_800B21D0 *lbl_803EAB20;
}

extern "C" int fn_800B1AAC(void *p)
{
    Pair_800A14A8 *pPair = (Pair_800A14A8 *)p;
    int result = 1;

    if (fn_8017F494() != -1) {
        if (fn_8017F48C() != 0) {
            fn_8017F444();
        }
        if (fn_8017F494() == 0) {
            lbl_803EAB20->mUnknown4.mUnknown5C |= 2;
        } else {
            lbl_803EAB20->mUnknown4.mUnknown48 = 0.0f;
            fn_800B2630();
        }
        if (lbl_803EAB20->mUnknown4.mUnknown5C & 2) {
            unsigned char team = lbl_803EAB20->mUnknown4.mUnknown0[0].mUnknown4Bytes[2];
            float line = pPair->mpSecond->mUnknown08.mY;
            int handle;

            if ((pPair->mpSecond->mUnknown18 & 0x10) && fn_801784E8() != 0) {
                line = -line;
            }
            float yards = ABS(line - pPair->mpSecond->mUnknown10) + 0.5f;
            fn_8009BD2C(0, &handle);
            fn_8017C3E4(team, (short)yards, handle);
        } else {
            lbl_803EAB20->mUnknown4.mUnknown48 = 0.0f;
        }
        result = 0;
        lbl_803EAB20->mUnknown4.mUnknown5A = 0;
        lbl_803EAB20->mUnknown4.mUnknown5B = 0;
    }
    return result;
}
