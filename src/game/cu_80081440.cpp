#include "game/fn_801C1F94.h"

#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/Table_8007E020.h"

extern "C" {
int fn_8007BF14(int index);
int fn_801FA290(int handle, Table_8007E020 *pTables, Object_80023BBC *pFilter,
                ColumnValue_802D6424 *pColumns);
void fn_8008138C(Object_8008044C *pObject, int *pValues);
void fn_800814BC(Info_80307908 *pInfo, short *pValues);

#if defined(DECOMP_COMPARE)
static ColumnValue_802D6424 lbl_802D6A28[11] = {
    { 0, 0x50495247, 0x4C474147, 0 },
    { 0, 0x50495247, 0x504D4A47, 0 },
    { 0, 0x50495247, 0x4B544247, 0 },
    { 0, 0x50495247, 0x43544347, 0 },
    { 0, 0x50495247, 0x44505347, 0 },
    { 0, 0x50495247, 0x4B435447, 0 },
    { 0, 0x50495247, 0x53535047, 0 },
    { 0, 0x50495247, 0x4B4C4247, 0 },
    { 0, 0x50495247, 0x564F4347, 0 },
    { 0, 0x50495247, 0x43544447, 0 },
    { 0, -1, -1, 0 },
};

void fn_80081440(Object_8008044C *pObject, short *pValues)
{
    Info_80307908 info;
    int i;

    fn_800817CC(pObject, &info);
    fn_800814BC(&info, pValues);
    for (i = 0; i < 10; i++) {
        pValues[i] = pValues[i] * 255 / 99;
    }
}

void fn_800814BC(Info_80307908 *pInfo, short *pValues)
{
    Table_8007E020 tables[3];
    Object_80023BBC filter;
    Object_80023BBC left;
    Object_80023BBC right;
    Object_80023BBC join;
    int i;
    int j;

    fn_801C1F94(pValues, 0, 10 * sizeof(short));
    tables[0].Set(0x52414547, 0, &filter);
    tables[1].Set(0x50495247, 0, &join);
    tables[2].Set(-1);
    join.Set(6, ((unsigned long long)0x50495247 << 32) | 0x594B5047, 6);
    join.mUnknown24.mLong = ((unsigned long long)0x52414547 << 32) | 0x594B5047;
    filter.Set(11, &left, &right);
    for (i = 0; i < 14; i++) {
        if (i != 7) {
            int result = fn_8007BF14(i);

            if (i == 6 && pInfo->mValues[6] == 0) {
                i = 7;
            }
            left.Set(6, ((unsigned long long)0x52414547 << 32) | 0x44494547, 3, pInfo->mValues[i]);
            right.Set(6, ((unsigned long long)0x52414547 << 32) | 0x49545247, 2, result);
            if (fn_801FA290(0x54415453, tables, 0, lbl_802D6A28) != 0x17) {
                for (j = 0; j < 10; j++) {
                    pValues[j] += lbl_802D6A28[j].mValue;
                }
            }
        }
    }
}

#endif

void fn_800816C4(Object_8008044C *pObject, Info_80307908 *pInfo, int *pValues)
{
    short sums[10];
    int i;

    fn_8008138C(pObject, pValues);
    fn_800814BC(pInfo, sums);
    for (i = 0; i < 10; i++) {
        pValues[i] = sums[i] + pValues[i];
        pValues[i] = pValues[i] <= 0 ? 1 : (pValues[i] > 99 ? 99 : pValues[i]);
    }
}

void fn_8008174C(Object_8008044C *pObject, short *pValues)
{
    Info_80307908 info;

    fn_800817CC(pObject, &info);
    fn_800814BC(&info, pValues);
}

void fn_80081788(Object_8008044C *pObject, int *pValues)
{
    Info_80307908 info;

    fn_800817CC(pObject, &info);
    fn_800816C4(pObject, &info, pValues);
}

}
