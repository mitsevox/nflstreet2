#include "game/Class_80148A58.h"

struct Score_801531C4 {
    char mUnknown0[8];
    int mUnknown8;
    char mUnknown12[4];
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

class Class_802A27F0 : public Class_80148A58 {
public:
    char mUnknown1C[8];
    unsigned char mUnknown24;
    unsigned char mUnknown25;
};

extern "C" {
extern const float lbl_802A3000[][8];
extern int lbl_802DEB08[];

Rules_801531C4 *fn_80155128(Class_80148A58 *p);

unsigned char fn_80154520(Class_802A27F0 *p)
{
    return p->mUnknown24;
}

void fn_80154528(Class_802A27F0 *p, int kind, int value)
{
    switch (kind) {
    case 0:
        switch (value) {
        case 0:
            p->mUnknown0 = 8;
            p->mUnknown4 = 7;
            p->mUnknown24 = 2;
            break;
        case 1:
            p->mUnknown0 = 6;
            p->mUnknown4 = 5;
            p->mUnknown24 = 1;
            break;
        }
        break;
    case 1:
        p->mUnknown25 = value;
        break;
    }
}

const float *fn_80154588(Class_802A27F0 *p, int index)
{
    if (index == 1) {
        return lbl_802A3000[fn_80155128(fn_80148A58())->mpUnknown52->mUnknown8];
    }
    return 0;
}

void fn_801545D4(Class_802A27F0 *p, int value, int *pList, int *pIds)
{
    unsigned char i;

    for (i = 0; i < 7 && pList[i] != 32767; i++) {
        pIds[lbl_802DEB08[i]] = pIds[lbl_802DEB08[i + 7]] = pList[i];
    }
}
}
