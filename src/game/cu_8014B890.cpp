#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/cu_8003E214.h"

struct States_802A2DB8 {
    char mUnknown0[0x20];
    int mUnknown20[2][3];
};

class Class_802A2DB8 : public Class_80148A58 {
public:
    States_802A2DB8 *mpUnknown1C;
};

struct Stats_8005C844 {
    Object_80039F5C *mpPlayers[3];
    int mValues[4];
};

extern "C" {
int fn_80178308(void);
int fn_801787DC(int team);
int fn_800C8744(int team);
Object_80039F5C *fn_8003AC84(int id);
int fn_8022B7A4(int handle, unsigned int tag, int *pValue);
int fn_80149F40(Class_80148A58 *p, int team, int kind);
int fn_8014A1B8(Class_80148A58 *p, int kind, int team);
void fn_8014A6A0(const int *pValues, int *pOrder, unsigned int count);
void fn_8014A8D8(const int *pValues, int *pOrder, unsigned int count);

int fn_8014B890(void)
{
    return 2;
}

int fn_8014B898(Class_80148A58 *p, int team)
{
    if (team == fn_80178308()) {
        return 3;
    }
    return 2;
}

void fn_8014B8D4(Class_80148A58 *p, int value, int *pList, int *pIds)
{
    fn_8003E8FC(value, pList, pIds);
    fn_8014A6A0(pList, pIds, 3);
    fn_8014A8D8(pList, pIds, 3);
}

void fn_8014B930(Class_80148A58 *p, int value, int *pList, int *pIds, int count, int slot)
{
    fn_8003E8FC(value, pList, pIds);
    int first = pList[0];
    switch (slot) {
    case 0:
    case 2:
    case 3:
        break;
    default:
        slot = 3;
        break;
    }
    for (unsigned char i = 0; i < 7; i++) {
        if (pIds[i] == first) {
            pIds[i] = pIds[slot];
            pIds[slot] = first;
            break;
        }
    }
    fn_8014A6A0(pList, pIds, count);
    int values[3];
    values[0] = pIds[0];
    values[1] = pIds[2];
    values[2] = pIds[3];
    fn_8014A8D8(values, pIds, 3);
}

void fn_8014BA20(Class_802A2DB8 *p, int team, Stats_8005C844 *pStats)
{
    int value = 0;
    int handle = fn_800C8744(team);
    for (unsigned char i = 0; i < 3; i++) {
        pStats->mpPlayers[i] = fn_8003AC84(p->mpUnknown1C->mUnknown20[team][i]);
    }
    pStats->mValues[0] = fn_801787DC((unsigned char)team);
    fn_8022B7A4(handle, 0x74727374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x74507374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x64647374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x69447374, &value);
    pStats->mValues[3] = value;
    fn_8022B7A4(handle, 0x72667374, &value);
    pStats->mValues[2] = value;
}

int fn_8014BB4C(Class_80148A58 *p, int team, int kind)
{
    int result = 0;
    switch (kind) {
    case 16:
        if (fn_801787DC(team) >= fn_801787DC((team + 1) & 1) - 3 && p->vfn_34(2, team, 100, 1)) {
            result = 1;
        }
        break;
    case 20:
        if (fn_801787DC(team) > 99) {
            result = 1;
        }
        break;
    case 21:
        if (fn_801787DC(team) < 0) {
            result = 1;
        }
        break;
    default:
        result = fn_80149F40(p, team, kind);
        break;
    }
    return result;
}

int fn_8014BC40(Class_80148A58 *p, int kind, int team)
{
    switch (kind) {
    case 16:
    case 20:
    case 21:
        return fn_801787DC(team);
    default:
        return fn_8014A1B8(p, kind, team);
    }
}

int fn_8014BC88(void)
{
    return 0;
}

int fn_8014BC90(void)
{
    return 0;
}
}
