#include "game/Class_80148A58.h"
#include "game/Class_802A56E8.h"
#include "game/Object_8017886C.h"
#include "game/fn_80178D18.h"

class Class_802A1930 : public Class_802A56E8 {
};

class Class_802A27F0 : public Class_80148A58 {
public:
    virtual void vfn_35(int a, int b);
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
Rules_801531C4 *fn_80155128(Class_80148A58 *p);
int fn_800948E4(Object_8017886C *p);
int fn_80178308(void);
int fn_80178320(void);
void fn_8017833C(int value);
int fn_80178348(void);
int fn_80178360(void);
void fn_80177E6C(int a, int b);
int fn_8008593C(int a, int b, int c, int d);
void fn_80178CD8(int a);

void fn_801534D4(Class_802A1930 *p)
{
    int a = 1;
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());
    Object_8017886C *o = fn_8017886C();
    if (fn_80178348() == fn_80178308()) {
        a = 0;
    }
    int kind = fn_800948E4(o);
    p->Class_802A56E8::vfn_10();
    if (pRules->mpUnknown52->mUnknown32 == 2) {
        pRules->mpUnknown52->mUnknown20[fn_80178348()]++;
        if (kind == 2) {
            if (a == 0) {
                pRules->mpUnknown52->mUnknown24[fn_80178348()]++;
            } else {
                pRules->mpUnknown52->mUnknown28[fn_80178360()]++;
                if (pRules->mpUnknown52->mUnknown24[fn_80178348()] != 0) {
                    pRules->mpUnknown52->mUnknown24[fn_80178348()]--;
                }
            }
        } else {
            pRules->mpUnknown52->mUnknown28[fn_80178360()]++;
        }
        Score_801531C4 *pScore = pRules->mpUnknown52;
        if (pScore->mUnknown20[0] >= pScore->mUnknown16 && pScore->mUnknown20[1] >= pScore->mUnknown16) {
            if (pScore->mUnknown24[0] > pScore->mUnknown24[1]) {
                pScore->mUnknown32 = 0;
            } else if (pScore->mUnknown24[1] > pScore->mUnknown24[0]) {
                pScore->mUnknown32 = 1;
            } else {
                pScore->mUnknown16++;
            }
        }
        if (a == 0 ? kind != 8 : kind == 8) {
            fn_8017833C(fn_80178320());
        } else if (kind != 8) {
            fn_80177E6C(0, 1);
        }

        int team = fn_80178308();
        if (fn_80178D70(team) == 2) {
            fn_8008593C(1, team, 0, 2);
        }
        fn_80178CD8(1);
    }
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(fn_80178348(), 0);
}
}
