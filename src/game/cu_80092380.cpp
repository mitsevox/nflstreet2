#include "game/cu_8008E978.h"
#include "game/fn_80178D18.h"

extern "C" void fn_8009BD88(Object_80039F5C *p, float scale);

extern unsigned char lbl_803EA8D5;
/* Saved player scales, seven per team. */
extern float lbl_8030C12C[14];

/* With enable set (and not already applied), saves every player's scale and
   rescales them by 1.03 over the scale of character's first object, then
   sets that character's objects to 1.03. With enable clear (and applied),
   restores the saved scales. */
extern "C" void fn_80092380(Character_80093BCC *pCharacter, int enable)
{
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    unsigned int side;
    unsigned int i;

    if (enable != 0) {
        if (pActor != 0 && lbl_803EA8D5 == 0) {
            float ratio = 1.03f / pCharacter->mUnknown14[0]->mUnknown768;

            for (side = 0; side <= 1; side++) {
                unsigned int count = fn_80178D18((unsigned char)side);

                for (i = 0; i < count; i++) {
                    Object_80039F5C *p = fn_80039F5C((unsigned char)side, i);

                    float scale = p->mUnknown768;

                    lbl_8030C12C[side * 7 + i] = scale;
                    fn_8009BD88(p, scale * ratio);
                }
            }
            for (i = 0; i < pActor->mUnknown4; i++) {
                fn_8009BD88(pCharacter->mUnknown14[i], 1.03f);
            }
            lbl_803EA8D5 = 1;
        }
    } else if (pActor != 0 && lbl_803EA8D5 != 0) {
        for (side = 0; side <= 1; side++) {
            unsigned int count = fn_80178D18((unsigned char)side);

            for (i = 0; i < count; i++) {
                fn_8009BD88(fn_80039F5C((unsigned char)side, i), lbl_8030C12C[side * 7 + i]);
            }
        }
        lbl_803EA8D5 = 0;
    }
}
