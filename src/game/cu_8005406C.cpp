#include "game/fn_801EF390.h"

struct Vector_8005406C {
    float mX;
    float mY;
    float mZ;
};

struct Object_8005406C {
    char mUnknown0[4];
    Vector_8005406C mScale;
};

extern "C" {
void *fn_800A336C(void);
int fn_800A3380(void);
void fn_80053C70(void);
Vector_8005406C *fn_800A3438(void);
void fn_80227264(Vector_8005406C *pOut, Vector_8005406C *pV, float scale);
void fn_80053BC8(Object_8005406C *pObject);
void fn_800543D4(void);
void fn_80054478(void);

extern float lbl_8028DEAC[];
Object_8005406C *lbl_803EA550 = 0;
extern Object_8005406C *lbl_803EA554;

void fn_8005406C(void)
{
    lbl_803EA550 = lbl_803EA554 = (Object_8005406C *)fn_801EF390(fn_800A336C(), fn_800A3380(), 1);
    fn_80053C70();
    fn_80227264(fn_800A3438(), &lbl_803EA554->mScale, lbl_8028DEAC[0]);
    fn_80053BC8(lbl_803EA554);
    fn_800543D4();
}

void fn_800540E0(void)
{
    fn_80054478();
    fn_801F010C(fn_800A336C(), fn_800A3380());
    lbl_803EA554 = 0;
    lbl_803EA550 = 0;
}
}
