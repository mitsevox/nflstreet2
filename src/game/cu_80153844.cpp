#include "game/Class_80148A58.h"
#include "game/Class_80297BF8.h"
#include "game/Class_802A56E8.h"
#include "game/cu_8013BB18.h"

class Class_802A1930 : public Class_802A56E8 {
};

class Class_802A1BC8 : public Class_80297BF8 {
};

struct Score_801531C4 {
    char mUnknown0[16];
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
extern char *lbl_803EB2F0;
extern const char lbl_802A0B74[];

int fn_800C1E40(void);
void fn_800544A4(const char *pTitle, const char *pText, const char *pButtons);
Rules_801531C4 *fn_80155128(Class_80148A58 *p);
int fn_80054568(void);
void fn_8013FA8C(int a);
void fn_8013F97C(int a);
Camera_8013F738 *fn_8013FA04(int index);
void fn_80141164(float value);

void fn_80153844(Class_802A1930 *p, int team)
{
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());
    int other = !team;

    pRules->mpUnknown52->mUnknown24[team] = pRules->mpUnknown52->mUnknown20[team] = pRules->mpUnknown52->mUnknown20[other] = pRules->mpUnknown52->mUnknown16;
    if (pRules->mpUnknown52->mUnknown24[other] >= pRules->mpUnknown52->mUnknown24[team]) {
        pRules->mpUnknown52->mUnknown24[other] = pRules->mpUnknown52->mUnknown24[team] - 1;
    }
    pRules->mpUnknown52->mUnknown32 = team;
}

void fn_801538C8(Class_802A1BC8 *p)
{
    p->Class_80297BF8::vfn_05();
    fn_8013FA8C(1);
    fn_8013F97C(0);
    fn_8013C6F0(fn_8013FA04(5));
    fn_80141164(2.5f);
}

void fn_80153910(Class_802A1BC8 *p, float dt)
{
    if (fn_80054568()) {
        p->Class_80297BF8::vfn_04(dt);
    }
}

void fn_8015399C(Class_802A1BC8 *p)
{
}

void fn_8015395C(Class_802A1BC8 *p)
{
    if (fn_800C1E40() == 0) {
        fn_800544A4("Open Field Showdown", lbl_803EB2F0, lbl_802A0B74);
    }
}
}
