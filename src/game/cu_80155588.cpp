#include "game/Class_80148A58.h"
#include "game/Class_802A56E8.h"

class Class_802A17A8 : public Class_802A56E8 {
public:
    unsigned char mUnknown4;
};

extern "C" {
void fn_80155D7C(Class_80148A58 *p);

void fn_80155588(Class_802A17A8 *p, int team)
{
    p->Class_802A56E8::vfn_11(team);
    p->mUnknown4 = 2;
    fn_80155D7C(fn_80148A58());
}
}
