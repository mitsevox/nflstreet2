#include "game/cu_8008E978.h"

extern "C" {
Object_80039F5C *fn_8008FF28(Character_80093BCC *pCharacter, Actor_801C009C *pActor);
int fn_800E0188(Object_80039F5C *p, float *pA, float *pB);
}

extern "C" int fn_80091C84(int index, float *pOut)
{
    Character_80093BCC *pCharacter;
    int result = 0;

    pCharacter = fn_80093BCC(index);
    if (pCharacter != 0) {
        Object_80039F5C *p = fn_8008FF28(pCharacter, fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4));
        float start;
        float end;

        if (p->mIdBytes[3] == 1 && fn_800E0188(p, &start, &end) != 0) {
            if (pOut != 0) {
                *pOut = end - start;
            }
            if (end - start > 1.0f) {
                result = 1;
            }
        }
    }
    return result;
}
