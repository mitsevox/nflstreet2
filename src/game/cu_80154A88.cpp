#include "game/Class_80148A58.h"
#include "game/Class_802A56E8.h"
#include "game/Object_80039F5C.h"

class Class_802A1930 : public Class_802A56E8 {
};

struct Score_801531C4;

struct Rules_801531C4 {
    char mUnknown0[44];
    Class_802A1930 mUnknown44;
    char mUnknown48[4];
    Score_801531C4 *mpUnknown52;
};

class Class_802A27F0 : public Class_80148A58 {
public:
    Rules_801531C4 *mpUnknown1C;
    char mUnknown20[4];
    unsigned char mUnknown24;
};

extern "C" {
int fn_801495E0(Class_80148A58 *p, int team, int index, Object_80039F5C *pPlayer, int kind);
int fn_801531C4(Class_802A1930 *p);
unsigned int fn_80153328(Class_802A1930 *p);
unsigned short fn_80153354(Class_802A1930 *p, int team);
unsigned short fn_80153394(Class_802A1930 *p, int team);
int fn_80178EE0(int team);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
Object_80039F5C *fn_80154FC0(Class_802A27F0 *p, int team, int index);

void fn_80154A88(Class_802A27F0 *p)
{
    fn_8009D8CC(5);
    fn_8009D964(5, 20);
}

int fn_80154AB8(Class_802A27F0 *p, int team, int index, Object_80039F5C *pPlayer, int kind)
{
    int other = !team;
    int result = 0;

    switch (kind) {
    case 1:
        if (p->vfn_27(team, index, 36) == 0 && p->vfn_27(team, index, 39) == 0) {
            result = fn_801495E0(p, team, index, pPlayer, kind);
        }
        break;
    case 9:
        result = fn_801495E0(p, team, index, pPlayer, kind);
        break;
    case 2:
        if (p->mUnknown24 > 1 && p->vfn_27(team, index, 35) == 0) {
            result = fn_801495E0(p, team, index, pPlayer, kind);
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
    case 11:
    case 13:
    case 14:
    case 15:
        result = fn_801495E0(p, team, index, pPlayer, kind);
        break;
    case 16: {
        int value = 0;
        if (fn_801531C4(&p->mpUnknown1C->mUnknown44) != team &&
            fn_80153328(&p->mpUnknown1C->mUnknown44) > 10) {
            Class_802A1930 *pRules = &p->mpUnknown1C->mUnknown44;
            unsigned char selected = fn_801531C4(pRules);
            value = fn_80153394(pRules, selected);
            value = value - fn_80153394(&p->mpUnknown1C->mUnknown44, team) == 1;
        }
        result = value;
        break;
    }
    case 34: {
        int value = 0;
        if (fn_801531C4(&p->mpUnknown1C->mUnknown44) == team &&
            fn_80153328(&p->mpUnknown1C->mUnknown44) > 10) {
            Class_802A1930 *pRules = &p->mpUnknown1C->mUnknown44;
            unsigned char selected = fn_801531C4(pRules);
            value = fn_80153394(pRules, selected);
            value = value - fn_80153394(&p->mpUnknown1C->mUnknown44, other) == 1;
        }
        result = value;
        break;
    }
    case 35: {
        int value = 0;
        if (p->vfn_27(team, index, 39) == 0) {
            value = fn_80153394(&p->mpUnknown1C->mUnknown44, team);
            value = value == fn_80153354(&p->mpUnknown1C->mUnknown44, team);
        }
        result = value;
        break;
    }
    case 36: {
        int value = 0;
        if (p->vfn_27(team, index, 39) == 0) {
            value = fn_80178EE0(other) == 0;
        }
        result = value;
        break;
    }
    case 37:
        if (p->mUnknown24 > 1) {
            int value = 0;
            Object_80039F5C *pOther = fn_80154FC0(p, team, index);
            if (p->vfn_30(1, team, index, pPlayer) > 2 && p->vfn_30(1, team, index, pOther) > 2 &&
                p->vfn_30(2, team, index, pPlayer) > 2 && p->vfn_30(2, team, index, pOther) > 2) {
                value = p->vfn_30(37, team, index, pPlayer) > 3;
            }
            result = value;
        }
        break;
    case 38:
        break;
    case 39: {
        int value = 0;
        if (p->vfn_26(team, index, pPlayer, 35) && p->vfn_26(team, index, pPlayer, 36)) {
            value = 1;
        }
        result = value;
        break;
    }
    }
    return result;
}
}
