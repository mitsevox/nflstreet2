#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"

extern "C" {
void fn_800814BC(Info_80307908 *pInfo, short *pValues);

static int lbl_802D6928[10] = {
    0x49474150, 0x4D554A50, 0x4B544250, 0x48544350, 0x44505350,
    0x4B415450, 0x53535050, 0x4B4C4250, 0x564F4350, 0x54464450,
};

int fn_800812B0(Object_8008044C *pObject, int index)
{
    return fn_8007A98C(pObject, lbl_802D6928[index]);
}

int fn_800812E0(Object_8008044C *pObject, int index)
{
    unsigned int value = fn_800812B0(pObject, index);
    short values[10];
    Info_80307908 info;

    fn_800817CC(pObject, &info);
    fn_800814BC(&info, values);
    value += values[index];
    return value == 0 ? 1 : (value > 99 ? 99 : value);
}

void fn_8008135C(Object_8008044C *pObject, int index, int value)
{
    fn_8007ABA4(pObject, lbl_802D6928[index], value);
}

void fn_8008138C(Object_8008044C *pObject, int *pValues)
{
    ColumnValue_802D6424 columns[11];
    ColumnValue_802D6424 *pColumns = columns;
    int i;

    for (i = 0; i < 10; i++) {
        pColumns[i].Set(pObject->mUnknown8, lbl_802D6928[i], 0);
    }
    columns[10].SetEnd();
    fn_801FA228(pObject->mUnknown0, 0, 0, pColumns);
    for (i = 0; i < 10; i++) {
        pValues[i] = pColumns[i].mValue;
    }
}

}
