#include <string.h>

#include "game/fn_800670B4.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F3D4(int a);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int fn_801C302C(const char *s1, const char *s2, int n);
int fn_80088224(int id);
void fn_80088294(int id);
}

/* lbl_803EA810 and lbl_803EA811: open flags of the 'LPUT' and 'FNIT' tables.
   lbl_803EA812: set by fn_80088294 when fn_800881B8 succeeds after the
   'RUUT' update, read and cleared by fn_80088628. lbl_803EA814: database index set by fn_80088638 (-1 when
   unset). */
static unsigned char lbl_803EA810 = 0;
static unsigned char lbl_803EA811 = 0;
static unsigned char lbl_803EA812 = 0;
static int lbl_803EA814 = -1;

extern "C" {

unsigned char fn_80087F10(void)
{
    unsigned char result = 1;

    if (!lbl_803EA810) {
        if (fn_8022EF8C(0, 0x4C505554)) {
            lbl_803EA810 = 0;
            result = 0;
        } else {
            lbl_803EA810 = 1;
        }
    }
    return result;
}

unsigned char fn_80087F70(void)
{
    unsigned char result = 1;

    if (!lbl_803EA811) {
        if (fn_8022EF8C(0, 0x464E4954)) {
            lbl_803EA811 = 0;
            result = 0;
        } else {
            lbl_803EA811 = 1;
        }
    }
    return result;
}

unsigned char fn_80087FD0(void)
{
    unsigned char result = 1;

    if (lbl_803EA811) {
        result = fn_8022EFBC(0, 0x464E4954) == 0;
        lbl_803EA811 = 0;
    }
    return result;
}

unsigned char fn_8008801C(void)
{
    unsigned char result = 1;

    if (lbl_803EA810) {
        result = fn_8022EFBC(0, 0x4C505554) == 0;
        lbl_803EA810 = 0;
    }
    return result;
}

int fn_80088068(int id)
{
    int value = 0;

    if (lbl_803EA814 != -1) {
        fn_801FCE10(0, "use \x8c select 'GCUT' into \x82 from 'RUUT' where 'NCUT' = \x82\n",
                    fn_8022F3D4(lbl_803EA814), &value, id);
    }
    return value;
}

void fn_800880D0(unsigned int id, unsigned int count)
{
    unsigned int limit = 0;
    int update = 1;
    unsigned char set = fn_80088224(id);
    unsigned int value = count;

    switch (id) {
    case 0:
        limit = 7;
        break;
    case 2:
        limit = 8;
        break;
    case 3:
        limit = 6;
        break;
    case 1:
    case 4:
        limit = 9;
        break;
    }

    if (set) {
        update = 0;
    } else if (count >= limit) {
        value = 0;
        fn_80088294(id);
    }

    if (update) {
        fn_801FCE10(0, "use \x8c update 'RUUT' set 'GCUT' = \x82 where 'NCUT' = \x82\n",
                    fn_8022F3D4(lbl_803EA814), value, id);
    }
}

int fn_800881B8(void)
{
    int count = fn_80088224(0);

    count += fn_80088224(1);
    count += fn_80088224(2);
    count += fn_80088224(3);
    count += fn_80088224(4);
    return count == 5;
}

int fn_80088224(int id)
{
    int value = 0;

    if (lbl_803EA814 != -1) {
        int db = fn_8022F3D4(lbl_803EA814);
        if (db != -1) {
            fn_801FCE10(0, "use \x8c select 'MCUT' into \x82 from 'RUUT' where 'NCUT' = \x82\n", db, &value, id);
        }
    }
    return value;
}

void fn_80088294(int id)
{
    int db = fn_8022F3D4(lbl_803EA814);

    if (db != -1) {
        int value = 0;
        fn_801FCE10(0, "use \x8c select 'MCUT' into \x85 from 'RUUT' where 'NCUT' = \x85\n", db, &value, id);
        if (value == 0) {
            fn_801FCE10(0, "use \x8c update 'RUUT' set 'MCUT' = \x82 where 'NCUT' = \x82\n", db, 1, id);
            if (fn_800881B8()) {
                lbl_803EA812 = 1;
            }
        }
    }
}

void fn_80088338(int id, char *pDest, int count)
{
    char buffer[80];

    fn_801FCE10(0, "select 'CSDT' into \x88 from 'FNIT' where 'DIDT' = \x82\n", buffer, id);
    strncpy(pDest, buffer, count);
}

unsigned int fn_80088390(int a, int b, int flag)
{
    Object_800670B4 table;
    char key[3];
    Record_80067338 record;
    int id;
    int handle;
    int tag;
    int kind;
    unsigned int count;
    unsigned int i;

    fn_801FCE10(0, "select 'CUUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &id, a, b);
    if (flag) {
        tag = 0x31544250;
        kind = 1;
    } else {
        tag = 0x31444250;
        kind = 11;
    }
    fn_800670B4(tag, kind, 0, &table);
    fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n", tag,
                &handle, 1, table.mUnknown0);
    count = fn_800672BC(tag, handle);
    fn_801C2E18(key, "%02d", id);
    for (i = 0; i < count; i++) {
        fn_80067338(tag, handle, i, &record);
        if (fn_801C302C(record.mUnknown1F0, key, 2) == 0) {
            break;
        }
    }
    return i;
}

unsigned int fn_8008849C(int a, int b, int flag)
{
    Object_800670B4 table;
    char key[3];
    Record_80067338 record;
    int id;
    int handle;
    int tag;
    int kind;
    unsigned int count;
    unsigned int i;

    fn_801FCE10(0, "select 'PUUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &id, a, b);
    if (flag) {
        tag = 0x31444250;
        kind = 11;
    } else {
        tag = 0x31544250;
        kind = 1;
    }
    fn_800670B4(tag, kind, 0, &table);
    fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n", tag,
                &handle, 1, table.mUnknown0);
    count = fn_800672BC(tag, handle);
    fn_801C2E18(key, "%02d", id);
    for (i = 0; i < count; i++) {
        fn_80067338(tag, handle, i, &record);
        if (fn_801C302C(record.mUnknown1F0, key, 2) == 0) {
            break;
        }
    }
    return i;
}

int fn_800885A8(int a, int b)
{
    int value;

    fn_801FCE10(0, "select 'OPUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &value, a, b);
    return value;
}

float fn_800885E8(int a, int b)
{
    float value;

    fn_801FCE10(0, "select 'PSUT' into \x82 from 'LPUT' where 'DIUT' = \x82 and 'IGUT' = \x82\n", &value, a, b);
    return value;
}

unsigned char fn_80088628(void)
{
    unsigned char result = lbl_803EA812;

    lbl_803EA812 = 0;
    return result;
}

void fn_80088638(int db)
{
    lbl_803EA814 = db;
}

int fn_80088640(void)
{
    return lbl_803EA814;
}
}
