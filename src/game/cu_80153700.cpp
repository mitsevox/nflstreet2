#include "game/Class_80148A58.h"
#include "game/Class_802A56E8.h"
#include "game/fn_801C1F94.h"

class Class_802A1930 : public Class_802A56E8 {
};

struct Score_801531C4 {
    char mUnknown0[12];
    unsigned int mUnknown12;
    unsigned int mUnknown16;
    unsigned short mUnknown20[2];
    unsigned short mUnknown24[2];
    unsigned short mUnknown28[2];
    unsigned char mUnknown32;
};

struct Rules_801531C4 {
    char mUnknown0[52];
    Score_801531C4 *mpUnknown52;
};

extern "C" {
Rules_801531C4 *fn_80155128(Class_80148A58 *p);
void fn_800D7520(int a);

void fn_80153700(Class_802A1930 *p, int team)
{
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());

    p->Class_802A56E8::vfn_11(team);
    fn_801C1F94(pRules->mpUnknown52->mUnknown20, 0, sizeof(pRules->mpUnknown52->mUnknown20));
    fn_801C1F94(pRules->mpUnknown52->mUnknown24, 0, sizeof(pRules->mpUnknown52->mUnknown24));
    fn_801C1F94(pRules->mpUnknown52->mUnknown28, 0, sizeof(pRules->mpUnknown52->mUnknown28));
    pRules->mpUnknown52->mUnknown32 = 2;
    pRules->mpUnknown52->mUnknown16 = pRules->mpUnknown52->mUnknown12;
    fn_800D7520(0);
}
}
