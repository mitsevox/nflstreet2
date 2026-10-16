#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"

struct Record_8014F104 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    unsigned int mUnknown12[9];
    unsigned int mUnknown48;
    char mUnknown52[4];
};

struct Block_8014F104 {
    char mUnknown0[0x34];
    Record_8014F104 *mpUnknown34;
};

class Class_802A2B68 : public Class_80148A58 {
public:
    Block_8014F104 *mpUnknown1C;
};

extern "C" {
unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer);
int fn_801499A8(Class_80148A58 *p, int kind, int team, int index, Object_80039F5C *pPlayer);

int fn_8014FBB4(Class_802A2B68 *p, int kind, int team, int index, Object_80039F5C *pPlayer)
{
    int result = 0;
    unsigned int i = fn_8014F474(p, pPlayer);
    switch (kind) {
    case 16:
    case 17:
    case 18:
    case 19:
    case 26:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown4;
        break;
    case 22:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[1] - p->mpUnknown1C->mpUnknown34[i].mUnknown12[0];
        break;
    case 23:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown48;
        break;
    case 24:
        if (p->mpUnknown1C->mpUnknown34[i].mUnknown12[7] != 0) {
            result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[8] / p->mpUnknown1C->mpUnknown34[i].mUnknown12[7];
        } else {
            result = 10000;
        }
        break;
    case 25:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[8];
        break;
    case 1:
    case 9:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[0];
        break;
    case 3:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[2] + p->mpUnknown1C->mpUnknown34[i].mUnknown12[3] * 10;
        break;
    case 4:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[4];
        break;
    case 5:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[5];
        break;
    case 6:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[7];
        break;
    case 7:
        result = p->mpUnknown1C->mpUnknown34[i].mUnknown12[6];
        break;
    case 8:
        break;
    case 10:
    default:
        result = fn_801499A8(p, kind, team, index, pPlayer);
        break;
    }
    return result;
}

int fn_8014FF2C(Class_802A2B68 *p)
{
    return 0;
}
}
