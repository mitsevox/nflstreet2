#include "game/Class_80148A58.h"
#include "game/Class_802A56E8.h"
#include "game/Class_80297BF8.h"

class Class_802A17A8 : public Class_802A56E8 {
public:
    unsigned char mUnknown4;
};

extern "C" {
void fn_80155D7C(Class_80148A58 *p);
extern unsigned char lbl_803EB2FC;
extern unsigned char lbl_803EB2FD;
float fn_80178A2C(void);
void fn_80178A20(float value);
void fn_80178E88(float value);
void fn_80157514(void);

void fn_80155588(Class_802A17A8 *p, int team)
{
    p->Class_802A56E8::vfn_11(team);
    p->mUnknown4 = 2;
    fn_80155D7C(fn_80148A58());
}

void fn_801555C4(Class_80297BF8 *p, float value)
{
    fn_80178E88(fn_80178A2C() * 2.0f - 18.0f);
    p->Class_80297BF8::vfn_03();
    fn_80178A20(fn_80178A2C() * 2.0f);
    fn_80155D7C(fn_80148A58());
    lbl_803EB2FC = 0;
    lbl_803EB2FD = 0;
    fn_80157514();
}
}
