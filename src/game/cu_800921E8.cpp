#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/Camera_8013F738.h"
#include "game/fn_80178D18.h"

extern "C" {
Object_80039F5C *fn_800963EC(Character_80093BCC *pCharacter);
int fn_801C01B8(void);
Camera_8013F738 *fn_8013FA04(int index);
float fn_800921B0(Object_80039F5C *p, Camera_8013F738 *pCamera);
int fn_80027DF0(void);
}

/* Updates bit 0 of every player's +4 block flags. With active set, players
   other than state 50 whose camera distance is at most character index's
   distance + 0.5 get it cleared; otherwise players with +11 set get it set.
   The fn_80137B40 player's fn_801374BC entry gets the same change in its
   word at +0x14, written through the Block_80170E64 view (whose +0x14 is
   that flags word). */
extern "C" void fn_800921E8(int index, int active)
{
    Camera_8013F738 *pCamera = 0;
    float distance = 0.0f;
    int side;

    if (active != 0) {
        Character_80093BCC *pCharacter = &lbl_803EC924->mUnknown80.mCharacters[index];
        Object_80039F5C *pTarget = fn_800963EC(pCharacter);

        fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
        if (fn_801C01B8() == 0) {
            pCamera = fn_8013FA04(2);
        }
        distance = fn_800921B0(pTarget, pCamera);
    }
    if (fn_80027DF0() == 0) {
        for (side = 0; side <= 1; side++) {
            unsigned int count = fn_80178D18((unsigned char)side);
            unsigned int i;

            for (i = 0; i < count; i++) {
                Object_80039F5C *p = fn_80039F5C((unsigned char)side, i);

                if (active != 0 && p->mpState->mId != 50) {
                    if (fn_800921B0(p, pCamera) <= distance + 0.5f) {
                        p->mpUnknown4->mUnknown20 &= ~1;
                        if (p == fn_80137B40()) {
                            ((Block_80170E64 *)fn_801374BC())->mUnknown20 &= ~1;
                        }
                    }
                } else {
                    if (p->mUnknown9[2] != 0) {
                        p->mpUnknown4->mUnknown20 |= 1;
                    }
                    if (p == fn_80137B40()) {
                        ((Block_80170E64 *)fn_801374BC())->mUnknown20 |= 1;
                    }
                }
            }
        }
    }
}
