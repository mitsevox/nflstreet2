#include "game/Object_8007A334.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

extern "C" {
void *fn_800088C8(void);
void fn_8000890C(int value);
int fn_8007E5EC(int a);
void fn_8007E69C(int a);
void fn_80084180(Object_8007A334 *pObject, int value);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
void fn_80084230(Object_8007A334 *pObject, unsigned char value);
void fn_8008425C(Object_8007A334 *pObject, unsigned char value);
void fn_80084288(Object_8007A334 *pObject, unsigned char value);
void fn_800842B4(Object_8007A334 *pObject, char *pText, int length);
void fn_80084470(Object_8007A334 *pObject, int value);
Object_8007A334 *fn_80182DBC(void);
void fn_80182DD4(const char *pText);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_80182E88(int a, int b);
void fn_80182E9C(int a);
void fn_801831F8(int a);
void fn_8018324C(void);
void fn_8018326C(int index);
void fn_801832A4(void);
int fn_80183354(void);
int fn_80183360(void);
void fn_801835C0(int a);
int fn_80183948(void);
void fn_80183990(void);
void fn_8018D358(int a, int b, int c);
int fn_8018D70C(int a);
}

class Class_80005618 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual void vfn_03(int id);
    virtual void vfn_05(int index, Entry_80182CC8 *pEntry);
    virtual Class_802A6BB0 *vfn_06();
    virtual int vfn_07();
    virtual Entry_80182CC8 *vfn_08();

    char mUnknown4[4];
};

class Class_800055D8 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pId) { *pId = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pEntry);

    char mUnknown4[4];
    int mUnknown8;
};

class Class_80005578 : public Class_802A6BB0 {
public:
    virtual void vfn_01(int a, int *pResult);
    virtual void vfn_02(int a, int b, int c);
    virtual void vfn_09(int a, int *pResult, Arg_8018399C text);
    virtual void vfn_10(int a, Arg_8018399C text);

    char mUnknown4[4];
};

static inline Class_800055D8 *fn_80005438();
static inline Class_80005578 *fn_80005468();
static inline Class_80005618 *fn_80005490();

static int lbl_803EB900 = 0;
static unsigned char lbl_803EB904 = 0;
static const char *lbl_803EB908[2] = {"Team", "Default"};

static Entry_80182CC8 lbl_802F3E7C[8] = {
    {0, 0, "Continue", 1, 0, 0, 0},
    {1, 0, "Logo", 1, 0x31, 0, 0},
    {2, 5, "Team Name", 1, 0x32, 0, 0},
    {3, 3, "Team Color 1", 1, 0x1E, 0, 0},
    {4, 3, "Team Color 2", 1, 0x21, 0, 0},
    {5, 3, "Team Color 3", 1, 0x33, 0, 0},
    {6, 0, "Logo Color", 1, 0x19, 0, 0},
    {7, 0, "Team Type", 1, 0, 0, 0},
};

static int lbl_802F3FDC[6] = {4, 0, 1, 2, 3, 5};

static const char *lbl_802F3FF4[6] = {
    "Balanced", "Rush Offense", "Rush Defense", "Pass Offense", "Pass Defense", "Custom",
};

static Object_8007A334 lbl_80369D70;

static void fn_80005344();
static void fn_800053A8();

static void fn_80004AF0()
{
    char buffer[24];

    fn_8007F0F4(&lbl_80369D70, fn_80084158(fn_80182DBC()), 0);
    fn_8007F094(&lbl_80369D70, buffer, 21);
    fn_800842B4(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
}

void Class_80005618::vfn_01(int a, int *pCount, int *pValue)
{
    char buffer[24];

    if (a == 1) {
        fn_80005344();
    }
    Class_802A6B60::vfn_01(a, pCount, pValue);
    fn_80083F88(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
    fn_80182DD4("");
    fn_80182E04("");
}

int Class_80005618::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b != 0) {
        result = -1;
        fn_800053A8();
    } else {
        switch (a) {
        case 1:
        case 6:
        case 7:
            result = 1;
            fn_80005438()->mUnknown8 = a;
            *ppResult = fn_80005438();
            break;
        case 0:
            switch (fn_80183948()) {
            case 0:
                fn_8018D358(fn_80183354(), fn_80183360(), lbl_802F3FDC[lbl_803EB900]);
                fn_8000890C(fn_8018D70C(lbl_802F3FDC[lbl_803EB900]));
                break;
            case 3:
                fn_80183990();
                fn_8000890C(250);
                break;
            }
            fn_801832A4();
            result = -3;
            *ppResult = fn_800088C8();
            fn_800053A8();
            break;
        }
    }
    return result;
}

void Class_80005618::vfn_03(int id)
{
    fn_80182DD4(lbl_802F3E7C[id].mName);
}

void Class_80005618::vfn_05(int index, Entry_80182CC8 *pEntry)
{
    Class_802A6B60::vfn_05(index, pEntry);
    if (index == 1) {
        pEntry->mUnknown40 = 0;
        for (int found = fn_8007A444(&lbl_80369D70); found; found = fn_8007A510(&lbl_80369D70)) {
            if (fn_8007E5EC(fn_8007F0C8(&lbl_80369D70) - 45)) {
                pEntry->mUnknown40 = 1;
                break;
            }
        }
    }
}

Class_802A6BB0 *Class_80005618::vfn_06()
{
    return fn_80005468();
}

int Class_80005618::vfn_07()
{
    switch (fn_80183948()) {
    case 3:
        return 7;
    case 0:
        return 8;
    default:
        return 6;
    }
}

Entry_80182CC8 *Class_80005618::vfn_08()
{
    Entry_80182CC8 *pEntries;

    switch (fn_80183948()) {
    case 0:
    case 3:
        pEntries = &lbl_802F3E7C[0];
        break;
    default:
        pEntries = &lbl_802F3E7C[1];
        break;
    }
    return pEntries;
}

void Class_800055D8::vfn_01(int a, int *pCount, int *pValue)
{
    switch (mUnknown8) {
    case 6:
        if (fn_80084438(fn_80182DBC())) {
            *pValue = 1;
        } else {
            *pValue = 0;
        }
        *pCount = 2;
        break;
    case 1:
        if (fn_80084438(fn_80182DBC())) {
            fn_801831F8(-1);
        } else {
            fn_801831F8(0);
        }
        fn_8007F0F4(&lbl_80369D70, fn_80084158(fn_80182DBC()), pValue);
        *pCount = fn_8007A410(&lbl_80369D70);
        break;
    case 7:
        *pValue = lbl_803EB900;
        *pCount = 6;
        break;
    }
}

int Class_800055D8::vfn_02(int a, int b, void **ppResult)
{
    int value;

    if (b == 0) {
        switch (mUnknown8) {
        case 6:
            if (a == 0) {
                fn_80084470(fn_80182DBC(), 0);
            } else {
                fn_80084470(fn_80182DBC(), 1);
            }
            break;
        case 1:
            fn_8007A600(&lbl_80369D70, a);
            value = fn_8007F0C8(&lbl_80369D70);
            fn_8007E69C(value - 45);
            fn_80084180(fn_80182DBC(), value);
            if (lbl_803EB904) {
                fn_80004AF0();
            }
            break;
        case 7:
            lbl_803EB900 = a;
            break;
        }
    }
    value = fn_80084158(fn_80182DBC());
    fn_80182E88(4, value);
    if (fn_80084438(fn_80182DBC())) {
        fn_80182E9C(-1);
    } else {
        fn_80182E9C(0);
    }
    return -1;
}

void Class_800055D8::vfn_03(int index)
{
    switch (mUnknown8) {
    case 6:
        if (index == 0) {
            fn_80182E9C(0);
        } else {
            fn_80182E9C(-1);
        }
        break;
    case 1:
        fn_8007A600(&lbl_80369D70, index);
        fn_80182E88(4, fn_8007F0C8(&lbl_80369D70));
        break;
    case 7:
        break;
    }
}

void Class_800055D8::vfn_05(int index, Entry_80182CC8 *pEntry)
{
    char buffer[24];

    switch (mUnknown8) {
    case 6:
        fn_801C3284(pEntry->mName, lbl_803EB908[index], 22);
        break;
    case 1:
        fn_8007A600(&lbl_80369D70, index);
        pEntry->mUnknown40 = fn_8007E5EC(fn_8007F0C8(&lbl_80369D70) - 45);
        fn_8007F094(&lbl_80369D70, buffer, 21);
        fn_801C3284(pEntry->mName, buffer, 22);
        break;
    case 7:
        fn_801C3284(pEntry->mName, lbl_802F3FF4[index], 22);
        break;
    }
}

void Class_80005578::vfn_01(int a, int *pResult)
{
    switch (a) {
    case 3:
        *pResult = fn_800841AC(fn_80182DBC());
        fn_8018326C(0);
        break;
    case 4:
        *pResult = fn_800841D8(fn_80182DBC());
        fn_8018326C(1);
        break;
    case 5:
        *pResult = fn_80084204(fn_80182DBC());
        fn_8018326C(2);
        break;
    }
}

void Class_80005578::vfn_02(int a, int b, int c)
{
    fn_8018324C();
    if (b == 0) {
        switch (a) {
        case 3:
            fn_80084230(fn_80182DBC(), c);
            break;
        case 4:
            fn_8008425C(fn_80182DBC(), c);
            break;
        case 5:
            fn_80084288(fn_80182DBC(), c);
            break;
        }
    }
}

void Class_80005578::vfn_09(int a, int *pResult, Arg_8018399C text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[24];

    if (a == 2) {
        fn_80083F88(fn_80182DBC(), buffer, 18);
        fn_801C3284(pParams->mpText, buffer, pParams->mLength + 1);
        *pResult = 3;
    }
}

void Class_80005578::vfn_10(int a, Arg_8018399C text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[24];

    if (a == 2) {
        fn_800842B4(fn_80182DBC(), pParams->mpText, pParams->mLength);
        fn_80083F88(fn_80182DBC(), buffer, 18);
        fn_80182E34(buffer);
        lbl_803EB904 = 0;
    }
}

static void fn_80005344()
{
    fn_8007EEFC(&lbl_80369D70);
    fn_801835C0(0x70);
    fn_8018324C();
    lbl_803EB900 = 0;
    lbl_803EB904 = 0;
    if (fn_80183948() == 0 || fn_80183948() == 3) {
        fn_80004AF0();
        lbl_803EB904 = 1;
    }
}

static void fn_800053A8()
{
    fn_8007F064(&lbl_80369D70);
}

extern "C" Class_80005618 *fn_800053D0()
{
    return fn_80005490();
}

static inline Class_800055D8 *fn_80005438()
{
    static Class_800055D8 sInstance;
    return &sInstance;
}

static inline Class_80005578 *fn_80005468()
{
    static Class_80005578 sInstance;
    return &sInstance;
}

static inline Class_80005618 *fn_80005490()
{
    static Class_80005618 sInstance;
    return &sInstance;
}
