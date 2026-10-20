#include "game/Class_80148A58.h"
#include "game/fn_80177FE0.h"

struct Object_8015005C;

class Class_802A2918 : public Class_80148A58 {
public:
    Object_8015005C *mpUnknown1C;
};

extern "C" {
void fn_801528E0(Class_802A2918 *p, Point_8017886C *pOut)
{
    pOut->mX = 0.0f;
    pOut->mY = fn_80177FE0().mY + 20.0f + 10.0f;
}
}
