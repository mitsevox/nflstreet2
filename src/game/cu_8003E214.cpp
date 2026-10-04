#include "game/fn_802372EC.h"
#include "game/cu_8003E214.h"
#include "game/Object_8008044C.h"
#include "game/fn_801D2B7C.h"

extern "C" {
unsigned int fn_8017F584(void);
int fn_801486A0(void);
unsigned int fn_80178DC8(void);
int fn_80027DF0(void);
void fn_80085020(Object_8007A334 *pObject);
void fn_80085060(Object_8007A334 *pObject);
int fn_80085080(Object_8007A334 *pObject, int value, int *pResult);
int fn_800850B8(Object_8007A334 *pObject, int category);
unsigned int fn_80081ECC(int category, int *pValues);
void fn_801F4B20(void);
}

static Record_8003E214 *lbl_803EA440 = 0;
static Update_8003E214 lbl_803EA444 = fn_8003E4E0;
static Select_8003E214 lbl_803EA448 = fn_8003E5E0;
static unsigned char lbl_803EA44C[7] = {0, 1, 2, 4, 3, 6, 5};
static unsigned char lbl_803EA454[7] = {0, 2, 3, 1, 5, 4, 6};
static unsigned char lbl_803EA45C[7] = {0, 1, 2, 3, 5, 4, 6};
static unsigned char lbl_803EA464[7] = {5, 0, 1, 4, 6, 2, 3};
static unsigned char lbl_803EA46C[7] = {4, 6, 2, 3, 5, 0, 1};
static unsigned char lbl_803EA474[7] = {4, 2, 6, 3, 5, 0, 1};
static int lbl_803EC780;

extern "C" {
int fn_8003E214(int *list, int value)
{
    int found = 0;
    int i = 0;
    while (list[i] != 255) {
        if (value == list[i]) {
            found = 1;
            break;
        }
        i++;
    }
    return found;
}

void fn_8003E24C(int category, int *id, unsigned int *value)
{
    int ids[4];
    unsigned int values[4];
    fn_8003E294(category, ids, values);
    *id = ids[0];
    *value = values[0];
}

void fn_8003E294(int category, int *ids, unsigned int *values)
{
    for (int i = 0; i < 4; i++) {
        values[i] = 0;
        ids[i] = 32767;
    }
    for (int i = 0; i < lbl_803EC780; i++) {
        if (!lbl_803EA440[i].excluded) {
            unsigned int value = lbl_803EA440[i].values[category];
            int id = lbl_803EA440[i].id;
            int ownCategory = lbl_803EA440[i].category;
            if (ids[0] == 32767 || value > values[0] ||
                (value == values[0] && category == ownCategory)) {
                for (unsigned int j = 3; j > 0; j--) {
                    values[j] = values[j - 1];
                    ids[j] = ids[j - 1];
                }
                values[0] = value;
                ids[0] = id;
            } else {
                for (unsigned int j = 3; j > 0; j--) {
                    if (ids[j] != 32767) {
                        if (value > values[j] || (value == values[j] && category == ownCategory)) {
                            if (j < 3) {
                                values[j + 1] = values[j];
                                ids[j + 1] = ids[j];
                            }
                            values[j] = value;
                            ids[j] = id;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void fn_8003E3FC(int id, unsigned char excluded)
{
    for (int i = 0; i < lbl_803EC780; i++) {
        if (lbl_803EA440[i].id == id) {
            lbl_803EA440[i].excluded = excluded;
            break;
        }
    }
}

void fn_8003E454(unsigned char excluded)
{
    for (int i = 0; i < lbl_803EC780; i++) lbl_803EA440[i].excluded = excluded;
}

void fn_8003E48C(int *list)
{
    fn_8003E454(1);
    while (*list != 32767) fn_8003E3FC(*list++, 0);
}

void fn_8003E4E0(Record_8003E214 *record, int *values, Object_8007A334 *query)
{
    for (int i = 0; i < 14; i++) {
        int adjustment = fn_800850B8(query, i);
        unsigned int value = fn_80081ECC(i, values) * (adjustment + 100) / 200;
        if (record->category == i) value = value * 1.1f;
        record->values[i] = value;
    }
}

void fn_8003E5E0(Record_8003E214 *unused, int count, int *excluded, int *id, int *category)
{
    unsigned int bestValues[4];
    unsigned int values[4];
    int bestIds[4];
    int ids[4];
    bestValues[0] = 0;
    for (int i = 0; i < 14; i++) {
        if (!fn_8003E214(excluded, i)) {
            fn_8003E294(i, ids, values);
            if (values[0] >= bestValues[0]) {
                for (int j = 0; j < 4; j++) {
                    bestValues[j] = values[j];
                    bestIds[j] = ids[j];
                }
                *id = bestIds[0];
                *category = i;
            }
        }
    }
    if (*category != 0 && fn_8017F584() == 2) {
        for (unsigned int i = 0; i < 3; i++) {
            if (bestIds[i + 1] == 32767) break;
            if (fn_802372EC(1, 4) == 0) *id = bestIds[i + 1];
            else break;
        }
    }
}

void fn_8003E710(int value, int *list, Record_8003E214 **pRecords)
{
    Object_8007A334 first;
    Object_8008044C second;
    int values[10];
    Record_8003E214 **records;
    if (!pRecords) {
        records = &lbl_803EA440;
    } else {
        records = pRecords;
    }
    fn_80085020(&first);
    fn_80085080(&first, value, 0);
    fn_8008044C(&second, 0, fn_80027DF0() ? 0x54415453 : 0x454D4147);
    int i = 0;
    while (list[i] != 32767) i++;
    lbl_803EC780 = i;
    *records = (Record_8003E214 *)fn_801D2B7C(i * sizeof(Record_8003E214), 0, 0);
    for (i = 0; i < lbl_803EC780; i++) {
        fn_800809C4(&second, list[i], 0);
        (*records)[i].id = list[i];
        (*records)[i].excluded = 0;
        (*records)[i].category = fn_80080ECC(&second);
        fn_80081788(&second, values);
        lbl_803EA444(&(*records)[i], values, &first);
        fn_801F4B20();
    }
    fn_8008056C(&second);
    fn_80085060(&first);
}

void fn_8003E8B8(Record_8003E214 **pRecords)
{
    Record_8003E214 **records;
    if (!pRecords) {
        records = &lbl_803EA440;
    } else {
        records = pRecords;
    }
    fn_801D2BD0(*records);
    *records = 0;
}

void fn_8003E8FC(int value, int *list, int *ids)
{
    unsigned int i;
    int id;
    unsigned int score;
    int category;
    fn_8003E710(value, list, 0);
    for (i = 0; i < fn_80178DC8(); i++) {
        switch (fn_801486A0()) {
        case 3: category = lbl_803EA454[i]; break;
        case 4: category = lbl_803EA45C[i]; break;
        default: category = lbl_803EA44C[i]; break;
        }
        fn_8003E24C(category, &id, &score);
        ids[category] = id;
        fn_8003E3FC(id, 1);
    }
    fn_8003E454(0);
    for (i = 0; i < fn_80178DC8(); i++) {
        switch (fn_801486A0()) {
        case 3: category = lbl_803EA46C[i]+7; break;
        case 4: category = lbl_803EA474[i]+7; break;
        default: category = lbl_803EA464[i]+7; break;
        }
        fn_8003E24C(category, &id, &score);
        ids[category] = id;
        fn_8003E3FC(id, 1);
    }
    fn_8003E8B8(0);
}

unsigned int fn_8003EA28(Record_8003E214 *records, int *excluded, int id)
{
    unsigned int result = 0;
    Record_8003E214 *saved = 0;
    if (records) {
        saved = lbl_803EA440;
        lbl_803EA440 = records;
    }
    int i;
    for (i = 0; i < lbl_803EC780; i++) if (id==lbl_803EA440[i].id) break;
    if (i < lbl_803EC780) {
        unsigned int best = 0, category = 0;
        for (unsigned int j = 0; j < 14; j++) {
            if (!fn_8003E214(excluded, j)) {
                if (lbl_803EA440[i].values[j] > best) {
                    best = lbl_803EA440[i].values[j];
                    category = j;
                }
            }
        }
        result = category;
    }
    if (records) lbl_803EA440 = saved;
    return result;
}

void fn_8003EB2C(Record_8003E214 *records, int *allowed, int *excluded, int *id, int *category)
{
    *category = 255;
    *id = 32767;
    Record_8003E214 *saved = 0;
    if (records) {
        saved = lbl_803EA440;
        lbl_803EA440 = records;
    }
    fn_8003E48C(allowed);
    lbl_803EA448(lbl_803EA440, lbl_803EC780, excluded, id, category);
    if (records) lbl_803EA440 = saved;
}

void fn_8003EBC4(Update_8003E214 callback)
{
    if (callback) lbl_803EA444 = callback;
    else lbl_803EA444 = fn_8003E4E0;
}

void fn_8003EBE4(Select_8003E214 callback)
{
    if (callback) lbl_803EA448 = callback;
    else lbl_803EA448 = fn_8003E5E0;
}
}
