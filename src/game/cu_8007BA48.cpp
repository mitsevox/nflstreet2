#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/Class_8018FD64Inline.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/Row_8007BC34.h"
#include "game/Key_8007A334.h"

extern "C" {
int fn_8022F384(int a);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
void fn_8007DDC8(Object_8007A334 *pCursor, int index);
void fn_8007DE20(Object_8007A334 *pCursor);
int fn_8007DEE0(Object_8007A334 *pCursor, int key);
int fn_8007DF4C(int key);
void fn_8007E274(int key);
void fn_8007E324(int key);
void fn_8018DF20(Object_8007A334 *pCursor, int index);
void fn_8018DF78(Object_8007A334 *pCursor);
char *fn_801C3084(const char *pString, int c);
}

extern "C" {
void fn_8008199C(Object_8008044C *pObject, Info_80307908 *pInfo);
}

static int sColumnTags[33] = {
    0x48545247, 0x54485447, 0x4C475447, 0x52545447, 0x50535447, 0x43425447, 0x424C5447,
    0x42455447, 0x41465447, 0x52575447, 0x44485447, 0x48545447, 0x4E4B5447, 0x53555447,
    0x534C5447, 0x48535447, 0x594B5047, 0x44494547, 0x4D4E5247, 0x54534247, 0x49545247,
    0x49545347, 0x49535247, 0x49434447, 0x46435347, 0x4C474C54, 0x42485247, 0x46485247,
    0x44425547, 0x53485247, 0x41485247, 0x54485247, 0x44544847
};

static int sShortColumnTags[10] = {
    0x4C474147, 0x504D4A47, 0x4B544247, 0x43544347, 0x44505347,
    0x4B435447, 0x53535047, 0x4B4C4247, 0x564F4347, 0x43544447
};

static int sIndexA[14] = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10, 11, 12 };
static int sIndexB[13] = { 0, 1, 2, 3, 4, 5, 14, 8, 9, 10, 11, 12, 13 };

static Key_8007A334 sKeys[2] = {
    { 0x52414547, 0x44494547, 0, 0 },
    { -1, -1, 3, 0 },
};

extern "C" {

void fn_8007BA48(Object_8007A334 *pCursor)
{
    fn_8007A334(pCursor, 0x52414547, 0x594B5047, 0, 0, 0x54415453);
}

void fn_8007BA88(Object_8007A334 *pCursor, int value)
{
    Object_80023BBC arg;

    arg.Set(6, 0x5241454749545247LL, 3, value);
    fn_8007A334(pCursor, 0x52414547, 0x594B5047, sKeys, &arg, 0x54415453);
}

void fn_8007BB04(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

int fn_8007BB24(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x594B5047);
}

int fn_8007BB4C(Object_8007A334 *pCursor, int key, int *pResult)
{
    return fn_8007A7F4(pCursor, 0x594B5047, key, 0, pResult);
}

int fn_8007BB84(Object_8007A334 *pCursor, int a, int b, int *pResult)
{
    ColumnValue_802D6424 list[3];

    list[0].Set(0x52414547, 0x44494547);
    list[0].mValue = b;
    list[1].Set(0x52414547, 0x49545247);
    list[1].mValue = a;
    list[2].Set(-1, -1);
    list[2].mValue = 0;
    return fn_8007A690(pCursor, list, 0, pResult);
}

int fn_8007BBFC(Object_8007A334 *pCursor, int key, int *pResult)
{
    return fn_8007A7F4(pCursor, 0x44494547, key, 0, pResult);
}

void fn_8007BC34(Object_8007A334 *pCursor, Row_8007BC34 *pOut)
{
    ColumnValue_802D6424 list[34];
    char *pSpace;
    int i;

    for (i = 0; i < 33; i++) {
        list[i].Set(0x52414547, sColumnTags[i]);
        list[i].mValue = 0;
    }
    list[33].Set(-1, -1);
    list[33].mValue = 0;
    list[18].mValue = (int)pOut->mUnknown10;
    list[19].mValue = (int)pOut->mName;
    pCursor->Read(list);

    pOut->mUnknown00 = list[16].mValue;
    pOut->mUnknown0C = list[17].mValue;
    pOut->mUnknown04 = list[20].mValue;
    pOut->mUnknown08 = list[21].mValue;
    pOut->mUnknown64 = list[22].mValue;
    pOut->mUnknown68 = list[23].mValue;
    pOut->mUnknown78 = list[25].mValue;
    pOut->mUnknown70 = list[26].mValue != 0;
    pOut->mUnknown71 = list[27].mValue != 0;
    pOut->mUnknown72 = list[28].mValue != 0;
    pOut->mUnknown73 = list[29].mValue != 0;
    pOut->mUnknown74 = list[30].mValue != 0;
    pOut->mUnknown75 = list[31].mValue != 0;
    pOut->mUnknown76 = list[32].mValue != 0;
    pOut->mUnknown6C = 0;

    pSpace = fn_801C3084(pOut->mName, ' ');
    if (pSpace) {
        *pSpace = 0;
    }
    for (i = 0; i < 16; i++) {
        pOut->mUnknown52[i] = list[i].mValue;
    }
}

unsigned int fn_8007BDF8(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x49535247);
}

void fn_8007BE20(Object_8007A334 *pCursor, char *pBuffer, int size)
{
    fn_8007AA3C(pCursor, 0x4D4E5247, (int)pBuffer, size);
}

int fn_8007BE54(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x44494547);
}

int fn_8007BE7C(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x49545247);
}

int fn_8007BEA4(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x49545347);
}

int fn_8007BECC(int a, int b)
{
    int value = 0;

    fn_801FCE10(0, "use 'TATS' select 'DIEG' into \x85 from 'RAEG' where 'ITRG' = \x85 and 'TSBG' = \x88\n",
                &value, a, b);
    return value;
}

int fn_8007BF14(int index)
{
    return sIndexA[index];
}

int fn_8007BF28(int index)
{
    return sIndexB[index];
}

int fn_8007C690(Object_8007A334 *pCursor, short *pOut);

int fn_8007BF3C(Object_8007A334 *pCursor)
{
    return fn_8007C690(pCursor, 0);
}

void fn_8007BF60(int id)
{
    int index = fn_8022F384(fn_8022F4BC());
    int handle = fn_8022F3D4(fn_8022F4BC());
    Class_8018FD64 cursor;

    cursor.fn_8018FDEC(0x4C504947, 0x49544947, 0, 0, handle);
    if (cursor.fn_8018FF54(0x49544947, id, 0, 0)) {
        int count = cursor.fn_8018FF78(0x4C504947);
        int next = count + 1;
        Key_8007A334 keys[2];
        Object_80023BBC both;
        Object_80023BBC first;
        Object_80023BBC second;
        int oldKeys[2];
        unsigned char fresh[2];
        int newKeys[2];
        int types[2];
        int oldIds[2];
        int newIds[2];
        int i;
        int j;

        cursor.fn_80190008(0x4C504947, next);
        keys[0].Set(0x50495247, 0x47504947, 0);
        keys[1].Set(-1, -1, 3);
        both.Set(11, &first, &second);
        first.Set(6, 0x5049524749544947LL, 2);
        first.mUnknown24.mInt = id;
        second.Set(6, 0x504952474C504947LL, 2);
        second.mUnknown24.mInt = count;
        {
            Class_8018FD64 rows;

            rows.fn_8018FDEC(0x50495247, 0x594B5047, keys, &both, 0x54415453);
            for (i = 0; i < 2; i++) {
                oldKeys[i] = rows.fn_8018FF78(0x594B5047);
                fresh[i] = !fn_8007DF4C(oldKeys[i]);
                if (fresh[i]) {
                    fn_8007E324(oldKeys[i]);
                }
                rows.fn_8018FEC4();
            }
        }
        second.Set(6, 0x504952474C504947LL, 2);
        second.mUnknown24.mInt = next;
        {
            Class_8018FD64 rows;

            rows.fn_8018FDEC(0x50495247, 0x594B5047, keys, &both, 0x54415453);
            for (i = 0; i < 2; i++) {
                newKeys[i] = rows.fn_8018FF78(0x594B5047);
                if (fresh[i]) {
                    fn_8007E274(newKeys[i]);
                }
                rows.fn_8018FEC4();
            }
        }
        for (i = 0; i < 2; i++) {
            Class_8018FD64 rows;

            rows.fn_8018FDEC(0x52414547, 0x594B5047, 0, 0, 0x54415453);
            rows.fn_8018FF54(0x594B5047, oldKeys[i], 0, 0);
            types[i] = rows.fn_8018FF78(0x49545247);
            oldIds[i] = rows.fn_8018FF78(0x44494547);
            rows.fn_8018FF54(0x594B5047, newKeys[i], 0, 0);
            newIds[i] = rows.fn_8018FF78(0x44494547);
        }
        {
            Object_8007A334 teams;
            Info_80307908 record;

            fn_8018DF20(&teams, index);
            if (fn_8007A444(&teams)) {
                do {
                    fn_800817CC((Object_8008044C *)&teams, &record);
                    for (i = 0; i < 14; i++) {
                        int type = fn_8007BF14(i);

                        for (j = 0; j < 2; j++) {
                            if (type == types[j] && record.mValues[i] == oldIds[j]) {
                                record.mValues[i] = newIds[j];
                            }
                        }
                    }
                    fn_8008199C((Object_8008044C *)&teams, &record);
                } while (fn_8007A510(&teams));
            }
            fn_8018DF78(&teams);
        }
    }
}

int fn_8007C46C(int key)
{
    int a;
    int b;
    int last;
    int max;
    int handle = fn_8022F3D4(fn_8022F4BC());

    fn_801FCE10(0, "use 'TATS' select 'ITIG' into \x82 and 'GPIG' into \x82 and 'LPIG' into \x82 from 'PIRG' where 'YKPG' = \x85\n",
                &a, &b, &last, key);
    fn_801FCE10(0, "use \x8c select 'LPIG' into \x82 from 'LPIG' where 'ITIG' = \x82\n", handle, &max, a);
    if (last != max) {
        int found;

        do {
            found = fn_801FCE10(0, "use 'TATS' select 'YKPG' into \x85 from 'PIRG' where 'ITIG' = \x82 and 'GPIG' = \x82 and 'LPIG' = \x82\n",
                                &key, a, b, max);
            max--;
        } while (found != 0 && max >= 0);
    }
    return key;
}

int fn_8007C538(int id)
{
    int result = 0;
    Object_80023BBC arg;
    Object_8007A334 keys;

    fn_8007DDC8(&keys, fn_8022F384(fn_8022F4BC()));
    arg.Set(6, 0x5049524749544947LL, 2, id);
    {
        Class_8018FD64 rows;
        int more;

        rows.fn_8018FDEC(0x50495247, 0x594B5047, 0, &arg, 0x54415453);
        for (more = rows.fn_8018FE7C(); more; more = rows.fn_8018FEC4()) {
            if (!fn_8007DEE0(&keys, rows.fn_8018FF9C(0x594B5047))) {
                result = 1;
                break;
            }
        }
        fn_8007DE20(&keys);
    }
    return result;
}

int fn_8007C67C(Row_8007BC34 *pRow)
{
    return pRow->mUnknown64 == 5;
}

int fn_8007C690(Object_8007A334 *pCursor, short *pOut)
{
    int result = 0;
    Object_80023BBC arg;
    int i;

    arg.Set(6, 0x50495247594B5047LL, 2, fn_8007BB24(pCursor));
    {
        Class_8018FD64 rows;

        rows.fn_8018FDEC(0x50495247, 0x594B5047, 0, &arg, 0x54415453);
        if (rows.fn_8018FE34() > 0 && rows.fn_8018FF78(0x49544947) > 0) {
            if (pOut) {
                for (i = 0; i < 10; i++) {
                    pOut[i] = rows.fn_8018FF78(sShortColumnTags[i]);
                }
            }
            result = 1;
        }
        if (pOut && !result) {
            memset(pOut, 0, 20);
        }
    }
    return result;
}
}
