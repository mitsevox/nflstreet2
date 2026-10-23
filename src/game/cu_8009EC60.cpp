#include "game/Item_80097440.h"
#include "game/Object_8017886C.h"

extern "C" {
State_8011F4EC *fn_8011F4EC(void);
int fn_80178308(void);
void fn_8009F928(Object_80039F5C *p, Point_8017886C *pOut, unsigned int distance, int predict);
}

/* Returns the index-th player of the play state's roster list after sorting
   it by depth (mode 1), and that player's spot through pOut. */
extern "C" Object_80039F5C *fn_8009EC60(unsigned int index, Point_8017886C *pOut)
{
    State_8011F4EC *pState;
    Object_80039F5C *p;

    if (pOut != 0) {
        pOut->mX = pOut->mY = 0.0f;
    }
    pState = fn_8011F4EC();
    if (index < pState->mUnknown1A3) {
        int team = fn_80178308();

        if (pState->mUnknown1A4 != 1) {
            int swapped;

            pState->mUnknown1A4 = 1;
            do {
                unsigned char i;

                swapped = 0;
                for (i = 0; i < pState->mUnknown1A3 - 1; i++) {
                    Object_80039F5C *pB;
                    Point_8017886C a;
                    Point_8017886C b;

                    p = fn_80039F5C(team, pState->mUnknown1A5[i]);
                    pB = fn_80039F5C(team, pState->mUnknown1A5[i + 1]);
                    fn_8009F928(p, &a, 5, 1);
                    fn_8009F928(pB, &b, 5, 1);
                    if (a.mY < b.mY) {
                        unsigned char temp = pState->mUnknown1A5[i];

                        pState->mUnknown1A5[i] = pState->mUnknown1A5[i + 1];
                        pState->mUnknown1A5[i + 1] = temp;
                        swapped = 1;
                    }
                }
            } while (swapped == 1);
        }
        p = fn_80039F5C(team, pState->mUnknown1A5[index]);
        if (pOut != 0) {
            fn_8009F928(p, pOut, 5, 1);
        }
    } else {
        p = 0;
    }
    return p;
}
