#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

struct Layout_802F4598 {
    float mX;
    float mY;
    float mZ;
    float mScale;
    int mValue;
};

extern "C" {
int fn_8002B70C(void);
void fn_8002B714(int value);
void fn_80022398(void);
void fn_800223C0(void);
void fn_800223E4(int index, float x, float y, float z);
void fn_80022534(int index, float scale);
void fn_80022680(int index, int a, int b);
void fn_80022730(int index, int value);
int fn_8005FC7C(void);
void fn_80060278(void);
int fn_800602D8(void);
int fn_800602E0(void);
int fn_80078934();
int fn_800808F8(Object_8008044C *pObject);
int fn_80080920(Object_8008044C *pObject);
int fn_800809FC(Object_8008044C *pObject, int a, int *pResult);
void fn_80080B08(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80080BEC(Object_8008044C *pObject, char *pBuffer, int size);
int fn_80080D10(Object_8008044C *pObject);
int fn_80081188(Object_8008044C *pObject);
int fn_800812E0(Object_8008044C *pObject, int a);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
void fn_8015CCB4(int value);
void fn_8017F670(int a, char *pText);
void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor);
int fn_8018BDFC(int a, int b, int *pIds, int *pCount);
void fn_8018BF10(int a, int b);
void fn_8018C15C(int a, int b);
void fn_8018C1A8(int a, int b);
void fn_8018C48C(int tag);
int fn_8018D890(int a, int b);
void fn_8018D8EC(int a, int b);
void fn_8018DC18(int a, int b);
void fn_8018DD4C(int a, int b, int c);
int fn_8018E8F4(int a);
void fn_8018E920(int index, int value);
int fn_8018E94C(int a);
void fn_8018E978(int index, int value);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_8021E2B4(void *pObject, int a, int b);
int fn_8021E72C(void *pObject, int a, int b);
void *fn_8021EA44(int index);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022F384(int a);
int fn_8022F4BC(void);
}

static Layout_802F4598 lbl_802F4598 = { 550.0f, 330.0f, 7.0f, 1.0f, 14 };
static int lbl_802F45AC[20] = { 0x59414C50, 0x4F504250, 0, 0, 0x59414C50, 0x414E4C50, 0, 0,
                                0x59414C50, 0x414E4650, 0, 0, 0x59414C50, 0x44494750, 0, 0,
                                -1,         -1,         3, 0 };

static Object_8008044C lbl_8036B2B0;
static Object_8008044C lbl_8036B2DC;
static Object_8008044C lbl_8036B308;

static int lbl_803EBA60 = 0x7FFF;
static int lbl_803EBA64 = 0x7FFF;
static unsigned char lbl_803EBA68 = 0;
static int lbl_803EBA6C = 0;

static int lbl_803ECE64;
static int lbl_803ECE68;
static int lbl_803ECE6C;
static unsigned char lbl_803ECE70;
static Object_8008044C *lbl_803ECE74;
static int lbl_803ECE78;
static signed char lbl_803ECE7C;
static int lbl_803ECE80;
static int lbl_803ECE84;
static unsigned char lbl_803ECE88;
static unsigned char lbl_803ECE89;

extern "C" {
void fn_8001D314(int *pCount, int *pId, Arg_8018399C text)
{
    Object_8007A334 cursor;
    char name[18];

    *pCount = fn_8007A410((Object_8007A334 *)&lbl_8036B308);
    *pId = lbl_803ECE78;
    fn_80083E40(&cursor, 0, 0x54415453);
    fn_80084034(&cursor, lbl_803ECE78, 0);
    fn_80083F88(&cursor, name, 18);
    fn_80083F68(&cursor);
    fn_801C3284(text.pParams->mpText, name, text.pParams->mLength + 1);
}

void fn_8001D3D0(int index, int *pId, Arg_8018399C text, Arg_8018399C label)
{
    char name[27];

    if (fn_8007A600((Object_8007A334 *)&lbl_8036B308, index)) {
        *pId = fn_800808F8(&lbl_8036B308);
        fn_80080B08(&lbl_8036B308, name, 27);
        fn_801C3284(text.pParams->mpText, name, text.pParams->mLength + 1);
        fn_8017F670(fn_80080ECC(&lbl_8036B308), label.pParams->mpText);
    } else {
        *pId = -1;
    }
}

int fn_8001D464(void)
{
    int result = 0;

    if (lbl_803ECE88 != 0) {
        result = fn_8018E8F4(lbl_803ECE7C);
    }
    return result;
}

int fn_8001D49C(void)
{
    int result = 0;

    if (lbl_803ECE88 != 0) {
        result = fn_8018E94C(lbl_803ECE7C);
    }
    return result;
}

void fn_8001D4D4(void)
{
    void *pList = fn_8021EA44(1);

    if (fn_8007A444((Object_8007A334 *)&lbl_8036B2B0)) {
        do {
            fn_8021E2B4(pList, 10, fn_80080D10(&lbl_8036B2B0));
        } while (fn_8007A510((Object_8007A334 *)&lbl_8036B2B0));
    }
    fn_8007A444((Object_8007A334 *)&lbl_8036B2B0);
    if (lbl_803ECE89 == 0) {
        if (fn_8007A444((Object_8007A334 *)&lbl_8036B2DC)) {
            do {
                fn_8021E2B4(pList, 10, fn_80080D10(&lbl_8036B2DC));
            } while (fn_8007A510((Object_8007A334 *)&lbl_8036B2DC));
        }
        fn_8007A444((Object_8007A334 *)&lbl_8036B2DC);
    }
}

void fn_8001D5A8(int db)
{
    Object_8007A334 cursor;
    QueryResult result;
    Desc_8008044C desc;
    int ids[13] = { -1 };
    unsigned short count = 13;
    unsigned short teamCount = 1;
    int n;
    int handle;
    int i;
    int rows;
    int value;

    lbl_803ECE78 = fn_8018BDFC(db, 1, ids, &n);
    fn_801FCE10(&result, "use 'TATS' insert into 'MAET' * select * from \x8c\n", fn_800602E0());
    desc.mUnknown0 = 2;
    desc.mUnknown4 = 4;
    desc.mUnknown8 = lbl_803ECE78;
    desc.mUnknown12 = ids[0];
    fn_8008044C(&lbl_8036B2DC, &desc, 0x54415453);
    desc.mUnknown12 = 0;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = lbl_803ECE78;
    desc.mUnknown0 = 2;
    fn_8008044C(&lbl_8036B308, &desc, 0x54415453);
    fn_801FCE10(&result, "use 'TATS' select 'LGLT' into \x82 from 'MAET' where 'DIGT' = \x82\n", &lbl_803ECE84,
                lbl_803ECE78);
    rows = fn_8007A410((Object_8007A334 *)&lbl_8036B2DC);
    lbl_803ECE89 = rows == 0;
    lbl_803ECE70 = rows == 6;
    value = fn_800602D8();
    fn_8007A334(&cursor, value, 0x44494750, 0, 0, 0x54415453);
    n = fn_8007A410(&cursor);
    fn_80229AA4(0x54415453, 0x59414C50, ids, &count);
    n = count;
    fn_8022C628(0x54415453, 0x4D414554, &lbl_803ECE80, &teamCount);
    for (i = 0; i < n; i++) {
        if (fn_8007A600(&cursor, i)) {
            fn_8007ABA4(&cursor, 0x44494F50, ids[i]);
            fn_8007AA90(&cursor, 0x44494F50, -1);
            fn_8007ABA4(&cursor, 0x44494750, ids[i]);
            fn_8007ABA4(&cursor, 0x44494754, lbl_803ECE80);
        }
    }
    fn_801FCE10(&result, "use 'TATS' insert into 'YALP' * select * from \x8c\n", value);
    fn_8007A3C4(&cursor);
    desc.mUnknown12 = 0;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = lbl_803ECE80;
    desc.mUnknown0 = 2;
    fn_8008044C(&lbl_8036B2B0, &desc, 0x54415453);
    fn_801F9980(0x54415453, &handle);
    fn_801FCE10(&result, "use 'TATS' select into \x8c * from 'MAET' where 'DIGT' = \x82\n", handle, lbl_803ECE78);
    fn_801FCE10(&result, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIOT' = \x82 and 'LGLT' = \x82\n", handle,
                lbl_803ECE80, lbl_803ECE80, lbl_803ECE84);
    fn_801FCE10(&result, "use 'TATS' insert into 'MAET' * select * from \x8c\n", handle);
    fn_801F967C(0x54415453, handle);
    fn_8001D4D4();
}

void fn_8001D930(void)
{
    void *pList = fn_8021EA44(1);

    if (fn_8007A444((Object_8007A334 *)&lbl_8036B2B0)) {
        do {
            fn_8021E72C(pList, 10, fn_80080D10(&lbl_8036B2B0));
        } while (fn_8007A510((Object_8007A334 *)&lbl_8036B2B0));
    }
    if (lbl_803ECE89 == 0) {
        if (fn_8007A444((Object_8007A334 *)&lbl_8036B2DC)) {
            do {
                fn_8021E72C(pList, 10, fn_80080D10(&lbl_8036B2DC));
            } while (fn_8007A510((Object_8007A334 *)&lbl_8036B2DC));
        }
    }
}

void fn_8001D9EC(int direction)
{
    int step;

    switch (direction) {
    case 1:
    case 2:
        step = 1;
        break;
    case 0:
    case 3:
        step = -1;
        break;
    case -2:
    case -1:
    case 5:
        step = 0;
        break;
    default:
        step = 0;
        break;
    }
    lbl_803ECE68 += step;
    if (lbl_803ECE68 < 0) {
        lbl_803ECE68 = lbl_803ECE64 - 1;
    } else if (lbl_803ECE68 >= lbl_803ECE64) {
        lbl_803ECE68 = 0;
    }
    fn_8007A600((Object_8007A334 *)lbl_803ECE74, lbl_803ECE68);
    lbl_803ECE6C = fn_800808F8(lbl_803ECE74);
    fn_80022680(0, lbl_803ECE6C, 0);
}

void fn_8001DAB0(int *pId, int *pFlag, int *pPosition, int *pValues)
{
    pPosition[0] = lbl_803ECE68 + 1;
    pPosition[1] = lbl_803ECE64;
    *pId = lbl_803ECE6C;
    *pFlag = 0;
    if (lbl_803EBA6C == 0 && lbl_803ECE88 == 0 && fn_800809FC(&lbl_8036B2DC, *pId, 0)) {
        *pFlag = 1;
    }
    pValues[0] = fn_800812E0(lbl_803ECE74, 6);
    pValues[1] = fn_800812E0(lbl_803ECE74, 4);
    pValues[2] = fn_800812E0(lbl_803ECE74, 7);
    pValues[3] = fn_800812E0(lbl_803ECE74, 0);
    pValues[4] = fn_800812E0(lbl_803ECE74, 3);
    pValues[5] = fn_800812E0(lbl_803ECE74, 2);
    pValues[6] = fn_800812E0(lbl_803ECE74, 1);
    pValues[7] = fn_800812E0(lbl_803ECE74, 5);
    pValues[8] = fn_800812E0(lbl_803ECE74, 8);
    pValues[9] = fn_800812E0(lbl_803ECE74, 9);
}

void fn_8001DBDC(char *pBuffer, int size)
{
    fn_80080BEC(lbl_803ECE74, pBuffer, size);
}

void fn_8001DC0C(char *pText, int size)
{
    fn_8017F670(fn_80080ECC(lbl_803ECE74), pText);
}

void fn_8001DC44(char *pBuffer, int size)
{
    unsigned int height = fn_800811E0(lbl_803ECE74);

    fn_801C2D88(pBuffer, size, "%d ft %d in", height / 12, height % 12);
}

void fn_8001DCAC(char *pBuffer, int size)
{
    fn_801C2D88(pBuffer, size, "%d lbs", fn_80081188(lbl_803ECE74));
}

int fn_8001DCFC(void)
{
    int id;

    if (lbl_803EBA6C == 1) {
        id = lbl_803ECE78;
        lbl_803ECE74 = &lbl_8036B2DC;
    } else {
        if (lbl_803ECE88 != 0) {
            id = lbl_803ECE80;
        } else {
            id = fn_8002B70C();
        }
        lbl_803ECE74 = &lbl_8036B2B0;
    }
    lbl_803ECE64 = fn_8007A410((Object_8007A334 *)lbl_803ECE74);
    lbl_803ECE68 = 0;
    fn_8001D9EC(4);
    return id;
}

void fn_8001DD84(int value)
{
    lbl_803EBA60 = value;
}

void fn_8001DD8C(int value)
{
    lbl_803EBA64 = value;
    lbl_803EBA6C = 1;
}

unsigned char fn_8001DD9C(void)
{
    int found;

    lbl_803ECE70 = 0;
    lbl_803EBA60 = 0x7FFF;
    lbl_803EBA64 = 0x7FFF;
    lbl_803ECE7C = fn_8022F384(fn_8022F4BC());
    found = fn_8005FC7C();
    if (found) {
        lbl_803ECE88 = 1;
        fn_8001D5A8(lbl_803ECE7C);
    } else {
        Desc_8008044C desc;
        Object_80023BBC node;
        Object_80023BBC left;
        Object_80023BBC right;
        int count;
        int rows;
        int i;

        lbl_803ECE88 = 0;
        lbl_803ECE78 = fn_8018D890(lbl_803ECE7C, 0);
        desc.mUnknown8 = fn_8002B70C();
        desc.mUnknown4 = 1;
        desc.mUnknown0 = 2;
        fn_8008044C(&lbl_8036B2B0, &desc, 0x54415453);
        node.Set(11, &left, &right);
        left.Set(6, 0x59414C5044494754LL, 3, lbl_803ECE78);
        right.SetUnknown32(6, 0x59414C5044494F50LL, 3, 0x10006);
        right.mUnknown16.mValue.mInt = 32756;
        fn_8007A334((Object_8007A334 *)&lbl_8036B2DC, 0x59414C50, 0x44494750, lbl_802F45AC, &node, 0x54415453);
        desc.mUnknown12 = 0;
        desc.mUnknown4 = 1;
        desc.mUnknown8 = lbl_803ECE78;
        desc.mUnknown0 = 2;
        fn_8008044C(&lbl_8036B308, &desc, 0x54415453);
        count = fn_8007A410((Object_8007A334 *)&lbl_8036B2B0);
        lbl_803ECE89 = count == 0;
        rows = fn_8007A410((Object_8007A334 *)&lbl_8036B2DC);
        if (rows == 15) {
            lbl_803ECE70 = 1;
        } else if (rows <= 13) {
            lbl_803ECE70 = 0;
        } else {
            lbl_803ECE70 = 1;
            fn_8007A444((Object_8007A334 *)&lbl_8036B2DC);
            for (i = 0; i < count; i++) {
                if (fn_80080920(&lbl_8036B2DC) == 32756) {
                    lbl_803ECE70 = 0;
                    break;
                }
                fn_8007A510((Object_8007A334 *)&lbl_8036B2DC);
            }
            fn_8007A444((Object_8007A334 *)&lbl_8036B2DC);
        }
        fn_80078934();
        fn_8001D4D4();
    }
    fn_80022398();
    fn_800223E4(0, lbl_802F4598.mX, lbl_802F4598.mY, lbl_802F4598.mZ);
    fn_80022534(0, lbl_802F4598.mScale);
    fn_80022730(0, lbl_802F4598.mValue);
    lbl_803EBA68 = 1;
    lbl_803EBA6C = 0;
    Object_8007A334 cursor;
    fn_80083E40(&cursor, 0, 0x54415453);
    fn_80084034(&cursor, lbl_803ECE78, 0);
    if (fn_80084438(&cursor) == 0) {
        unsigned char color[3];

        color[0] = fn_800841AC(&cursor);
        color[1] = fn_800841D8(&cursor);
        color[2] = fn_80084204(&cursor);
        fn_80188CBC(0, 4, fn_80084158(&cursor), 172, color);
        fn_80188CBC(1, 4, fn_80084158(&cursor), 172, color);
    }
    fn_80083F68(&cursor);
    return lbl_803ECE70;
}

void fn_8001E100(void)
{
    if (lbl_803EBA60 != 0x7FFF) {
        if (lbl_803ECE88 != 0) {
            fn_8018C1A8(lbl_803EBA60, lbl_803ECE78);
            if (fn_8001D49C()) {
                fn_8018E978(lbl_803ECE7C, 0);
            }
        } else {
            fn_8018DC18(lbl_803ECE78, lbl_803EBA60);
        }
    }
}

void fn_8001E16C(void)
{
    if (lbl_803EBA64 != 0x7FFF) {
        int found = 0;

        if (lbl_803ECE88 == 0) {
            found = fn_800809FC(&lbl_8036B2DC, lbl_803EBA64, 0);
        }
        if (!found) {
            if (lbl_803ECE88 != 0) {
                fn_8018C15C(lbl_803ECE78, lbl_803EBA64);
                if (fn_8001D464()) {
                    fn_8018E920(lbl_803ECE7C, 0);
                }
            } else {
                fn_8018DD4C(lbl_803ECE78, lbl_803EBA64, 0);
            }
        }
    }
}

void fn_8001E204(void)
{
    fn_8001E100();
    fn_8001E16C();
    fn_8001D930();
    fn_800223C0();
    fn_8008056C(&lbl_8036B2B0);
    fn_8008056C(&lbl_8036B2DC);
    fn_8008056C(&lbl_8036B308);
    fn_8015CCB4(1);
    if (lbl_803ECE88 != 0) {
        fn_8018BF10(lbl_803ECE7C, lbl_803ECE78);
        fn_8018C48C(0x54415453);
        lbl_803ECE88 = 0;
        fn_80060278();
    } else {
        fn_8018D8EC(lbl_803ECE7C, lbl_803ECE78);
        fn_8018C48C(0x54415453);
    }
    fn_8002B714(1023);
    lbl_803EBA68 = 0;
}

int fn_8001E2C0(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        if (fn_8001DD9C()) {
            *pArgs[0].pi = 1;
        } else {
            *pArgs[0].pi = 0;
        }
        break;
    case 0x80000002:
        fn_8001E204();
        break;
    case 0x80000004: {
        int *pPosition = (int *)(pArgs[3].i + (*pArgs[3].pi + 1) * 4);
        int *pValues = (int *)(pArgs[6].i + (*pArgs[6].pi + 1) * 4);
        int direction = pArgs[0].i;
        int *pId = pArgs[1].pi;
        int *pFlag = pArgs[5].pi;

        fn_8001D9EC(direction);
        fn_8001DAB0(pId, pFlag, pPosition, pValues);
        fn_8001DBDC(pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        fn_8001DC0C(pArgs[4].pParams->mpText, pArgs[4].pParams->mLength);
        fn_8001DC44(pArgs[7].pParams->mpText, pArgs[7].pParams->mLength);
        fn_8001DCAC(pArgs[8].pParams->mpText, pArgs[8].pParams->mLength);
        break;
    }
    case 0x80000005: {
        int *pId = pArgs[0].pi;

        *pId = fn_8001DCFC();
        break;
    }
    case 0x80000006:
        fn_8001DD84(pArgs[0].i);
        break;
    case 0x80000007:
        fn_8001DD8C(pArgs[0].i);
        break;
    case 0x80000008:
        *pResult = 0;
        if (lbl_803ECE88 != 0 && fn_8001D464()) {
            *pResult = 1;
        }
        break;
    case 0x80000009:
        fn_8001D314(pArgs[0].pi, pArgs[1].pi, pArgs[2]);
        break;
    case 0x8000000A:
        fn_8001D3D0(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3]);
        break;
    default:
        return 0;
    }
    return 1;
}

unsigned char fn_8001E4F4(void)
{
    return lbl_803EBA68;
}
}
