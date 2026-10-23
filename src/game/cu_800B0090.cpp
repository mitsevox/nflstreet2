#include "game/Object_80039F5C.h"
#include "game/Block_800B0CFC.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"

extern "C" {
int fn_80178308(void);
Object_800670B4 *fn_80168708(int team);
int fn_801641E0(Object_800670B4 *pObject, int index, const char **ppNames);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_800B0004(void);
void fn_80227690(void *pOut, void *pA, void *pB);

extern const char *lbl_802D8754[2][5];
}

extern "C" void fn_800B0090(void)
{
    int team = fn_80178308();
    Object_800670B4 *pObject = fn_80168708(team);
    int count = fn_80178D18(team);
    const char *names[2];
    unsigned int group;

    names[1] = 0;
    fn_801C1F94(lbl_803EAB14, 0, sizeof(lbl_803EAB14->mEntries));
    for (group = 0; group <= 1; group++) {
        unsigned int slot;

        for (slot = 0; slot <= 4; slot++) {
            Entry_800B0CFC *pEntry = &lbl_803EAB14->mEntries[group][slot];
            short i;

            for (i = 0; i < count; i++) {
                int row;

                names[0] = lbl_802D8754[group][slot];
                row = fn_801641E0(pObject, (unsigned char)i, names);
                if (row != -1 && pEntry->mUnknown46 <= 4) {
                    Object_80039F5C *pPlayer = fn_80039F5C(team, i);
                    Zone_800AFE8C *pZone;
                    unsigned int n;

                    pEntry->mUnknown3C[pEntry->mUnknown46] = row;
                    pZone = (Zone_800AFE8C *)&pObject->mUnknown8.mUnknown84[row][i];
                    pEntry->mpUnknown0[pEntry->mUnknown46] = pZone;
                    fn_8009BD2C(pPlayer, &pEntry->mUnknown28[pEntry->mUnknown46]);
                    names[0] = "Norm";
                    row = fn_801641E0(pObject, (unsigned char)i, names);
                    pEntry->mUnknown41[pEntry->mUnknown46] = row;
                    pEntry->mpUnknown14[pEntry->mUnknown46] = (Zone_800AFE8C *)&pObject->mUnknown8.mUnknown84[row][i];
                    if (pEntry->mpUnknown0[0] != 0 && (pZone->mUnknownE & 1) && (n = pEntry->mUnknown46) != 0) {
                        Zone_800AFE8C *pSwap;
                        int ref;

                        pSwap = pEntry->mpUnknown0[0];
                        pEntry->mpUnknown0[0] = pEntry->mpUnknown0[n];
                        pEntry->mpUnknown0[n] = pSwap;
                        ref = pEntry->mUnknown28[0];
                        pEntry->mUnknown28[0] = pEntry->mUnknown28[pEntry->mUnknown46];
                        pEntry->mUnknown28[pEntry->mUnknown46] = ref;
                        pSwap = pEntry->mpUnknown14[0];
                        pEntry->mpUnknown14[0] = pEntry->mpUnknown14[pEntry->mUnknown46];
                        pEntry->mpUnknown14[pEntry->mUnknown46] = pSwap;
                        row = pEntry->mUnknown3C[0];
                        pEntry->mUnknown3C[0] = pEntry->mUnknown3C[pEntry->mUnknown46];
                        pEntry->mUnknown3C[pEntry->mUnknown46] = row;
                        row = pEntry->mUnknown41[0];
                        pEntry->mUnknown41[0] = pEntry->mUnknown41[pEntry->mUnknown46];
                        pEntry->mUnknown41[pEntry->mUnknown46] = row;
                    }
                    pEntry->mUnknown46++;
                }
            }
        }
    }
    fn_800B0004();
}

extern "C" int fn_800B0558(Object_80039F5C *p, Point_80167910 *pPoint)
{
    Point_8017886C spot;
    Point_8017886C target;

    spot = fn_80177FE0();
    target.mX = spot.mX + pPoint->mX;
    target.mY = spot.mY + pPoint->mY;
    fn_80227690(&target, &p->mMotion.mPos, &target);
    return fn_802270A4(&target) < 0.5f;
}
