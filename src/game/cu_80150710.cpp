#include "game/Class_80297BF8.h"

class Class_802A1DC8 : public Class_80297BF8 {
};

extern "C" {
extern char *lbl_803EB2E4;
extern const char lbl_802A0B74[];

int fn_800C1E40(void);
void fn_800544A4(const char *pTitle, const char *pText, const char *pButtons);
int fn_80054568(void);
void fn_800AD910(int a, float b);

void fn_80150710(Class_802A1DC8 *p, float value)
{
    if (fn_80054568()) {
        p->vfn_11(value);
    }
}

void fn_80150820(Class_802A1DC8 *p)
{
}

void fn_80150824(Class_802A1DC8 *p, float value)
{
    fn_800AD910(2, value);
}

void fn_801507E0(Class_802A1DC8 *p)
{
    if (fn_800C1E40() == 0) {
        fn_800544A4("Jump Ball Battle", lbl_803EB2E4, lbl_802A0B74);
    }
}
}
