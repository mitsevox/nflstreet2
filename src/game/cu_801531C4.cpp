#include "game/Class_80148A58.h"
#include "game/Class_802A56E8.h"
#include "game/Object_80039F5C.h"

class Class_802A1930 : public Class_802A56E8 {
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

unsigned char fn_801531C4(Class_802A1930 *p)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown32;
}

int fn_801532E0(Class_802A1930 *p)
{
    return 2;
}

unsigned short fn_801532E8(Class_802A1930 *p, int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown24[team];
}

unsigned int fn_80153328(Class_802A1930 *p)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown16;
}

unsigned short fn_80153354(Class_802A1930 *p, int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown20[team];
}

unsigned short fn_80153394(Class_802A1930 *p, int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown24[team];
}

unsigned short fn_801533D4(Class_802A1930 *p, int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown28[team];
}

int fn_80153414(Class_802A1930 *p)
{
    unsigned int count0 = 0;
    unsigned int count1 = 0;
    int mode = fn_80148A58()->vfn_05(0);
    int i;

    for (i = 0; i <= 6; i++) {
        if (fn_80039F5C(0, i)->mUnknown8 != 255) {
            count0++;
        } else if (fn_80039F5C(1, i)->mUnknown8 != 255) {
            count1++;
        }
    }
    if (mode == 2 && count0 <= 1 && count1 <= 1) {
        return 1;
    }
    return 0;
}
}
