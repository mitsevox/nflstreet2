#include "game/Class_80148A58.h"
#include "game/PreSnapPhase.h"
#include "game/GameOptions.h"

class LivePlayPhase;
class Class_80297B50;
class Class_80297B90;
class PreGamePhase;
class PostPlayPhase;
class ScrmRuleSet;

struct States_802A2DB8 {
    char mUnknown0[8];
    PreSnapPhase mUnknown8;
    char mUnknownC[16];
    int mUnknown1C;
    int mUnknown20[2][3];
    unsigned char mUnknown38;
};

class Class_802A2DB8 : public Class_80148A58 {
public:
    States_802A2DB8 *mpUnknown1C;
};

extern "C" {
void fn_800BC51C(PreGamePhase *pObject);
void fn_800B3644(Class_80297B50 *pObject);
void fn_800BFAB4(PreSnapPhase *pObject);
void fn_800A039C(LivePlayPhase *pObject);
void fn_800B9598(PostPlayPhase *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(ScrmRuleSet *pObject);

void fn_8014B7D4(Class_802A2DB8 *p)
{
    if (p->mpUnknown1C->mUnknown38 != 0) {
        GameOptionsSet(19, 1);
    }
    fn_800BC51C(0);
    fn_800B3644(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    if (p->mpUnknown1C->mUnknown1C != 0) {
        GameOptionsSet(14, p->mpUnknown1C->mUnknown1C);
    }
    fn_80178F20(0);
    delete p->mpUnknown1C;
    p->mpUnknown1C = 0;
}
}
