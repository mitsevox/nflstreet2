#include "game/Class_80297BF8.h"

class Class_802A18C8 : public Class_80297BF8 {
};

extern "C" {
extern char *lbl_803EB2F8;
extern const char lbl_802A0B74[];

int fn_800C1E40(void);
void fn_800544A4(const char *pTitle, const char *pText, const char *pButtons);
int fn_80054568(void);

void fn_80155640(Class_802A18C8 *p, float dt)
{
    if (fn_80054568()) {
        p->Class_80297BF8::vfn_04(dt);
    }
}

void fn_801556CC(Class_802A18C8 *p)
{
}

void fn_8015568C(Class_802A18C8 *p)
{
    if (fn_800C1E40() == 0) {
        fn_800544A4("Quick Strike", lbl_803EB2F8, lbl_802A0B74);
    }
}
}
