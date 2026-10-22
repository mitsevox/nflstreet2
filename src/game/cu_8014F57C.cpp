#include "game/Class_802A2B68.h"
#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"


extern "C" {
unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer);
int fn_801499A8(Class_80148A58 *p, int kind, int team, int index, Object_80039F5C *pPlayer);
int fn_801495E0(Class_80148A58 *p, int team, int index, Object_80039F5C *pPlayer, int kind);
int fn_8007DBB4(int a);

int fn_8014F57C(Class_802A2B68 *p, int team, int index, Object_80039F5C *pPlayer, int kind)
{
    int result = 0;
    unsigned int i = fn_8014F474(p, pPlayer);
    Record_8014F104 *pRecord = &p->mpUnknown1C->mpUnknown34[i];
    switch (kind) {
    case 26:
        if (p->vfn_31(26, team, index, pPlayer, 1, 0)) {
            unsigned int j;
            result = 1;
            for (j = 0; j <= 5; j++) {
                if (i != j && pRecord->mUnknown4 < p->mpUnknown1C->mpUnknown34[j].mUnknown4 * 2) {
                    result = 0;
                    break;
                }
            }
            if (pRecord->mUnknown8 != 255) {
                result = 0;
            }
        }
        break;
    case 19:
        if (p->vfn_31(26, team, index, pPlayer, 1, 0)) {
            unsigned int j;
            result = 1;
            for (j = 0; j <= 5; j++) {
                if (i != j && pRecord->mUnknown4 < p->mpUnknown1C->mpUnknown34[j].mUnknown4 * 2) {
                    result = 0;
                    break;
                }
            }
        }
        break;
    case 16: {
        unsigned int max = 0;
        unsigned int j;
        for (j = 0; j < 4; j++) {
            if (p->mpUnknown1C->mpUnknown34[j].mUnknown4 >= max) {
                max = p->mpUnknown1C->mpUnknown34[j].mUnknown4;
            }
        }
        if (pRecord->mUnknown4 >= max - 2 && pRecord->mUnknown4 < max) {
            result = 1;
        }
        break;
    }
    case 17:
        {
            int ok = p->vfn_31(17, team, index, pPlayer, 1, 0) && pRecord->mUnknown4 >= fn_8007DBB4(22);
            result = ok;
        }
        break;
    case 18:
        result = p->vfn_31(18, team, index, pPlayer, 1, 0);
        break;
    case 22:
        result = p->vfn_31(22, team, index, pPlayer, 1, 0);
        break;
    case 23:
        result = p->vfn_31(23, team, index, pPlayer, 1, 0);
        break;
    case 24:
        result = p->vfn_31(24, team, index, pPlayer, 100, 1);
        break;
    case 25:
        result = p->vfn_31(25, team, index, pPlayer, 1, 0);
        break;
    case 1:
        result = p->vfn_31(1, team, index, pPlayer, 1, 0);
        break;
    case 3:
        result = p->vfn_31(3, team, index, pPlayer, 1, 0);
        break;
    case 4:
        result = p->vfn_31(4, team, index, pPlayer, 3, 0);
        break;
    case 5:
        result = p->vfn_31(5, team, index, pPlayer, 3, 0);
        break;
    case 6:
        result = p->vfn_31(6, team, index, pPlayer, 1, 0);
        break;
    case 7:
        result = p->vfn_31(7, team, index, pPlayer, 3, 0);
        break;
    case 8:
        {
            int ok = p->vfn_31(6, team, index, pPlayer, 100, 1) && p->vfn_31(1, team, index, pPlayer, 100, 1);
            result = ok;
        }
        break;
    case 9:
        {
            int ok = p->vfn_31(9, team, index, pPlayer, 100, 1) && !p->vfn_28(8);
            result = ok;
        }
        break;
    case 10:
    default:
        result = fn_801495E0(p, team, index, pPlayer, kind);
        break;
    }
    return result;
}

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
