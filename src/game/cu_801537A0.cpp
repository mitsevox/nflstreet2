#include "game/Class_80148A58.h"
#include "game/PreGamePhase.h"
#include "game/fn_80178D18.h"

class Class_802A1BC8 : public PreGamePhase {
};

class Class_802A27F0 : public Class_80148A58 {
public:
    virtual void vfn_35(int a, int b);
};

extern "C" {
void HudSetScoreTableRows(int a);
void HudPost3AOff(void);
void fn_800A8738(int value);
void TutorialReleasePause(void);

void fn_801537A0(Class_802A1BC8 *p)
{
    p->PreGamePhase::OnEnter();
    fn_80148A58()->vfn_14();
    HudSetScoreTableRows(fn_80178D70(0) * 2);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(0, 0);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(1, 0);
    HudPost3AOff();
    fn_800A8738(1);
    TutorialReleasePause();
}
}
