#include "game/Class_80148A58.h"
#include "game/Class_80297BF8.h"
#include "game/fn_80178D18.h"

class Class_802A1BC8 : public Class_80297BF8 {
};

class Class_802A27F0 : public Class_80148A58 {
public:
    virtual void vfn_35(int a, int b);
};

extern "C" {
void fn_8017E094(int a);
void fn_8017DC08(void);
void fn_800A8738(int value);
void fn_80157514(void);

void fn_801537A0(Class_802A1BC8 *p)
{
    p->Class_80297BF8::vfn_03();
    fn_80148A58()->vfn_14();
    fn_8017E094(fn_80178D70(0) * 2);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(0, 0);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(1, 0);
    fn_8017DC08();
    fn_800A8738(1);
    fn_80157514();
}
}
