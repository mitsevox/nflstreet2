#include "game/fn_8017F584.h"
extern "C" {
void fn_80073EE4(void);
void fn_80074190(void);
void fn_800744C0(unsigned char value);
int fn_801486A0(void);
unsigned int fn_801568F0(void);
}

static int lbl_803EA710 = 0;

extern "C" void fn_8007355C(void)
{
    int state;

    fn_800744C0(1);
    if (fn_8017F584() == 11 && fn_801568F0() <= 4) {
        fn_80073EE4();
        state = 1;
    } else {
        if (fn_801486A0() == 0 || fn_801486A0() == 1 || fn_801486A0() == 2) {
            fn_80073EE4();
            fn_800744C0(0);
        } else {
            fn_80073EE4();
        }
        state = 2;
    }
    lbl_803EA710 = state;
}

extern "C" void fn_800735E4(void)
{
    switch (lbl_803EA710) {
    case 1:
    case 2:
        fn_80074190();
        break;
    }
    lbl_803EA710 = 0;
}
