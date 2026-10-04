#include <string.h>
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/fn_8021D7B8.h"
#include "game/cu_80181330.h"

/* Element of lbl_8000F5EC, passed to fn_80183740. */
struct Record_8000F5EC {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    unsigned char mUnknown24;
};

/* lbl_8036AD78: fourteen words copied from the record filled by fn_800817CC. */
struct Record_8036AD78 {
    int mUnknown0[14];
};

/* Record filled by fn_800817CC. */
struct Record_800817CC {
    char mUnknown0[16];
    Record_8036AD78 mUnknown16;
};

/* Object returned by fn_8000EC44. */
struct Record_8036AD28 {
    Record_8036AD28();
    ~Record_8036AD28();
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    int mUnknown12;
    Object_8007A334 mUnknown16;
};

inline Record_8036AD28 *fn_8000EC44()
{
    static Record_8036AD28 sRecord;
    return &sRecord;
}

inline Record_8036AD28::Record_8036AD28() {}
inline Record_8036AD28::~Record_8036AD28() {}

class Class_8000F540 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 7; }
    virtual Entry_80182CC8 *vfn_08()
    {
        static const Entry_80182CC8 sEntries[] = {
            { 0, 0, "Reebok Store", 1 },
            { 1, 0, "Barbershop", 1 },
            { 2, 0, "Department Store", 1 },
            { 3, 0, "Jewelry Store", 1 },
            { 4, 0, "Screen Printing", 1 },
            { 5, 0, "Sporting Goods", 1 },
            { 6, 0, "Tattoo Parlor", 1 },
        };
        return (Entry_80182CC8 *)sEntries;
    }

    char mUnknown4[4];
};

class Class_8000F500 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int id);
    virtual void vfn_04(int index, int *pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
    char mUnknown12[4];
    unsigned char mUnknown16;
};

class Class_8000F4B0 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 7; }
    virtual Entry_80182CC8 *vfn_08()
    {
        static const Entry_80182CC8 sEntries[] = {
            { 0, 0, "Headwear", 1 },
            { 1, 0, "Glasses", 1 },
            { 2, 0, "Short Sleeve Shirts", 1 },
            { 3, 0, "Long Sleeve Shirts", 1 },
            { 4, 0, "Pants", 1 },
            { 5, 0, "Shorts", 1 },
            { 6, 0, "Socks", 1 },
        };
        return (Entry_80182CC8 *)sEntries;
    }

    char mUnknown4[4];
};

class Class_8000F460 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 7; }
    virtual Entry_80182CC8 *vfn_08()
    {
        static const Entry_80182CC8 sEntries[] = {
            { 0, 0, "Throwback Jerseys", 1 },
            { 1, 0, "Shoulder Pads", 1 },
            { 2, 0, "Arm Bands", 1 },
            { 3, 0, "Elbow Pads", 1 },
            { 4, 0, "Wrist", 1 },
            { 5, 0, "Gloves", 1 },
            { 6, 0, "Shoes", 1 },
        };
        return (Entry_80182CC8 *)sEntries;
    }

    char mUnknown4[4];
};

class Class_8000F410 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 2; }
    virtual Entry_80182CC8 *vfn_08()
    {
        static const Entry_80182CC8 sEntries[] = {
            { 0, 0, "Decals", 1 },
            { 1, 0, "Team Logos", 1 },
        };
        return (Entry_80182CC8 *)sEntries;
    }

    char mUnknown4[4];
};

class Class_8000F3C0 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 3; }
    virtual Entry_80182CC8 *vfn_08()
    {
        static const Entry_80182CC8 sEntries[] = {
            { 0, 0, "Back Tattoos", 1 },
            { 1, 0, "Left Arm Tattoos", 1 },
            { 2, 0, "Right Arm Tattoos", 1 },
        };
        return (Entry_80182CC8 *)sEntries;
    }

    char mUnknown4[4];
};

class Class_8000F370 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 2; }
    virtual Entry_80182CC8 *vfn_08()
    {
        static const Entry_80182CC8 sEntries[] = {
            { 0, 0, "Necklaces", 1 },
            { 1, 0, "Medallions", 1 },
        };
        return (Entry_80182CC8 *)sEntries;
    }

    char mUnknown4[4];
};

inline Class_8000F500 *fn_8000ED34()
{
    static Class_8000F500 sInstance;
    return &sInstance;
}

inline Class_8000F4B0 *fn_8000ED64()
{
    static Class_8000F4B0 sInstance;
    return &sInstance;
}

inline Class_8000F410 *fn_8000ED8C()
{
    static Class_8000F410 sInstance;
    return &sInstance;
}

inline Class_8000F460 *fn_8000EDB4()
{
    static Class_8000F460 sInstance;
    return &sInstance;
}

inline Class_8000F3C0 *fn_8000EDDC()
{
    static Class_8000F3C0 sInstance;
    return &sInstance;
}

inline Class_8000F370 *fn_8000EE04()
{
    static Class_8000F370 sInstance;
    return &sInstance;
}

inline Class_8000F540 *fn_8000EE2C()
{
    static Class_8000F540 sInstance;
    return &sInstance;
}

extern "C" {
extern void *lbl_803EB688;

int fn_80022D78(void);
int fn_80022D80(void);
void fn_80022D6C(void);
void fn_800225F4(int index, unsigned int value);
void fn_80022680(int index, int a, int b);
void fn_80022E40(int a, int b);
void fn_80048FD0(int a, int b);
void fn_800490A0(int index, int a, int b);
void fn_80049B00(int a, int b);
void fn_80049B90(int a, int b);
void fn_80049D6C(int a, unsigned int b, int c);
void fn_8007BA48(Object_8007A334 *pObject);
void fn_8007BB04(Object_8007A334 *pObject);
int fn_8007BB4C(Object_8007A334 *pObject, int a, int b);
int fn_8007BE54(Object_8007A334 *pObject);
int fn_8007BE7C(Object_8007A334 *pObject);
int fn_8007BECC(int a, const char *pName);
int fn_8007BF28(int index);
void fn_8007CC50(Object_8007A334 *pObject);
void fn_8007CCC4(Object_8007A334 *pObject);
int fn_800808F8(Object_8008044C *pObject);
int fn_80080E98(Object_8008044C *pObject);
void fn_800817CC(Object_8008044C *pObject, Record_800817CC *pOut);
int fn_800872E8(int a);
void fn_8008731C(int a, int id, int *pOut1, int *pOut2, char *pBuffer, int size);
int fn_8008736C(int a, int b);
void fn_80087600(int a, int b);
void fn_800876C0(void);
void fn_80087704(void);
int fn_80087BA0(int index);
unsigned int fn_800886BC(int a);
void fn_800888D0(int a, int b);
void fn_8015D180(int a, int b);
void fn_8015D38C(int a);
Object_8007A334 *fn_80182DC8(void);
void fn_80182DD4(const char *pText);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_801835C0(int a);
void fn_801835C8(void);
void fn_80183704(void);
void fn_80183740(const Record_8000F5EC *pRecord);
int fn_8022F4BC(void);
}

static const int lbl_8000F590[] = {
    10, 0, 10, 8, 1, 11, 11, 2, 3, 4, 5, 6, 9, 10, 14, 14, 12, 13, 14, 14, 14, 14, 14,
};

static const Record_8000F5EC lbl_8000F5EC[] = {
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, -15.0f, 0.0f, 335.0f, 0.25f, 15, 0 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
    { 0.0f, -15.0f, 0.0f, 335.0f, 0.25f, 15, 0 },
    { 0.0f, -15.0f, 0.0f, 335.0f, 0.25f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, -15.0f, 0.0f, 335.0f, 0.25f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
    { 0.0f, 300.0f, 0.0f, 180.0f, 1.1f, 15, 0 },
    { 0.0f, 205.0f, 0.0f, 60.0f, 0.8f, 15, 0 },
    { 0.0f, 205.0f, 0.0f, 300.0f, 0.8f, 15, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 1 },
};

static int lbl_803EB948 = -1;
static int lbl_803EB94C = 0;
static int lbl_803ECE30;
static int lbl_803ECE34;
static Record_8036AD78 lbl_8036AD78;

static void fn_8000E70C();
static void fn_8000E744(char *a, const char *b, const char *c);
static void fn_8000E784(Record_8036AD78 *pOut);
static void fn_8000E834(Record_8036AD78 *pRecord);
static void fn_8000E8FC(int index, int value);

void Class_8000F500::vfn_01(int a, int *pCount, int *pOut)
{
    fn_8000EC44()->mUnknown0 = -1;
    fn_80087704();
    fn_8000E70C();
    fn_8000E784(&lbl_8036AD78);
    lbl_803EB94C = fn_8007BECC(9, "MANNEQUINSHIRTPADS");
    *pCount = fn_800872E8(mUnknown8);
    if (*pCount == 0) {
        mUnknown16 = 1;
        *pCount = 1;
    } else {
        mUnknown16 = 0;
    }
    *pOut = 0;
    lbl_803EB948 = -1;
    fn_80183740(&lbl_8000F5EC[mUnknown8]);
}

int Class_8000F500::vfn_02(int a, int b, void **pOut)
{
    int result = -1;

    fn_8000E834(&lbl_8036AD78);
    fn_8015D180(fn_80022D78(), 15);
    fn_80022D6C();
    fn_800876C0();
    fn_8000EC44()->mUnknown0 = 0;
    fn_80183740(0);
    lbl_803EB948 = result;
    return result;
}

void Class_8000F500::vfn_04(int index, int *pOut)
{
    *pOut = index;
}

void Class_8000F500::vfn_05(int id, Entry_80182CC8 *pOut)
{
    pOut->mUnknown36 = id;
    pOut->mUnknown4 = 6;
    pOut->mId = id;
    if (mUnknown16) {
        pOut->mUnknown30 = 0;
        pOut->mUnknown40 = 0;
        strncpy(pOut->mName, "Out of Stock", 22);
    } else {
        int item;
        int price;

        pOut->mUnknown40 = 0;
        fn_8008731C(mUnknown8, id, &item, &price, pOut->mName, 22);
        if (!fn_8008736C(mUnknown8, item) || fn_800886BC(fn_8022F4BC()) < price) {
            pOut->mUnknown30 = 0;
        } else {
            pOut->mUnknown30 = 1;
        }
    }
}

void Class_8000F500::vfn_03(int id)
{
    if (mUnknown16) {
        fn_8000EC44()->mUnknown0 = -1;
    } else {
        int item;
        int price;

        fn_8008731C(mUnknown8, id, &item, &price, 0, 0);
        fn_8000E8FC(mUnknown8, item);
        if (fn_8008736C(mUnknown8, item)) {
            if (price == 0) {
                fn_8000EC44()->mUnknown0 = -2;
            } else {
                fn_8000EC44()->mUnknown0 = price;
            }
        } else {
            fn_8000EC44()->mUnknown0 = -1;
        }
        fn_8021D7B8(lbl_803EB688, 0x8000007E, 0, 0);
    }
}

void Class_8000F540::vfn_01(int a, int *pCount, int *pOut)
{
    Class_802A6B60::vfn_01(a, pCount, pOut);
    fn_8000EC44()->mUnknown0 = 0;
    fn_80087704();
    if (a == 1) {
        int value;

        fn_8000EC44()->mUnknown8 = 0;
        fn_801835C8();
        fn_8007CC50(&fn_8000EC44()->mUnknown16);
        fn_8007A444(fn_80182DC8());
        value = fn_800808F8((Object_8008044C *)fn_80182DC8());
        fn_8000EC44()->mUnknown12 = value;
        fn_800809C4((Object_8008044C *)fn_80182DC8(), value, 0);
        fn_80022680(fn_80022D78(), value, 1);
        fn_80022680(fn_80022D80(), value, 1);
        fn_8015D38C(0);
    }
    *pCount = 7;
    *pOut = lbl_803ECE34;
}

void Class_8000F540::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F4B0::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F410::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F460::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F3C0::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F370::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

int Class_8000F540::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b) {
        fn_80183704();
        result = -1;
        fn_8007CCC4(&fn_8000EC44()->mUnknown16);
        fn_8000EC44()->mUnknown12 = result;
        fn_8000EC44()->mUnknown0 = 0;
    } else {
        Class_8000F500 *pItems;

        switch (a) {
        case 0:
            lbl_803ECE34 = a;
            pItems = fn_8000ED34();
            result = 1;
            *pOut = pItems;
            pItems->mUnknown8 = 22;
            fn_8000EC44()->mUnknown4 = 22;
            break;
        case 1:
            lbl_803ECE34 = a;
            pItems = fn_8000ED34();
            result = 1;
            *pOut = pItems;
            pItems->mUnknown8 = 18;
            fn_8000EC44()->mUnknown4 = 18;
            break;
        case 2:
            lbl_803ECE34 = 2;
            result = 1;
            *pOut = fn_8000ED64();
            break;
        case 4:
            lbl_803ECE34 = 4;
            result = 1;
            *pOut = fn_8000ED8C();
            break;
        case 5:
            lbl_803ECE34 = a;
            result = 1;
            *pOut = fn_8000EDB4();
            break;
        case 6:
            lbl_803ECE34 = a;
            result = 1;
            *pOut = fn_8000EDDC();
            break;
        case 3:
            lbl_803ECE34 = a;
            result = 1;
            *pOut = fn_8000EE04();
            break;
        }
    }
    return result;
}

int Class_8000F4B0::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        Class_8000F500 *pItems;

        switch (a) {
        case 0:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 1;
            fn_8000EC44()->mUnknown4 = 1;
            return 1;
        case 1:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 4;
            fn_8000EC44()->mUnknown4 = 4;
            return 1;
        case 2:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 0;
            fn_8000EC44()->mUnknown4 = 0;
            return 1;
        case 3:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 2;
            fn_8000EC44()->mUnknown4 = 2;
            return 1;
        case 4:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 5;
            fn_8000EC44()->mUnknown4 = 5;
            return 1;
        case 5:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 6;
            fn_8000EC44()->mUnknown4 = 6;
            return 1;
        case 6:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 3;
            fn_8000EC44()->mUnknown4 = 3;
            return 1;
        }
    }
    return result;
}

int Class_8000F460::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        Class_8000F500 *pItems;

        switch (a) {
        case 0:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 13;
            fn_8000EC44()->mUnknown4 = 13;
            break;
        case 1:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 7;
            fn_8000EC44()->mUnknown4 = 7;
            break;
        case 2:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 8;
            fn_8000EC44()->mUnknown4 = 8;
            break;
        case 3:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 9;
            fn_8000EC44()->mUnknown4 = 9;
            break;
        case 4:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 10;
            fn_8000EC44()->mUnknown4 = 10;
            fn_800225F4(0, 8);
            fn_800225F4(1, 8);
            break;
        case 5:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 11;
            fn_8000EC44()->mUnknown4 = 11;
            fn_800225F4(0, 8);
            fn_800225F4(1, 8);
            break;
        case 6:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 12;
            fn_8000EC44()->mUnknown4 = 12;
            break;
        }
    }
    return result;
}

int Class_8000F410::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        Class_8000F500 *pItems;

        switch (a) {
        case 0:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 14;
            fn_8000EC44()->mUnknown4 = 14;
            return 1;
        case 1:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 15;
            fn_8000EC44()->mUnknown4 = 15;
            return 1;
        }
    }
    return result;
}

int Class_8000F3C0::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        Class_8000F500 *pItems;

        switch (a) {
        case 0:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 19;
            fn_8000EC44()->mUnknown4 = 19;
            return 1;
        case 2:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 20;
            fn_8000EC44()->mUnknown4 = 20;
            return 1;
        case 1:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 21;
            fn_8000EC44()->mUnknown4 = 21;
            return 1;
        }
    }
    return result;
}

int Class_8000F370::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        Class_8000F500 *pItems;

        switch (a) {
        case 0:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 16;
            fn_8000EC44()->mUnknown4 = 16;
            return 1;
        case 1:
            pItems = fn_8000ED34();
            *pOut = pItems;
            pItems->mUnknown8 = 17;
            fn_8000EC44()->mUnknown4 = 17;
            return 1;
        }
    }
    return result;
}

static void fn_8000E70C()
{
    fn_801835C0(900);
    fn_8000E744("", "", "");
}

static void fn_8000E744(char *a, const char *b, const char *c)
{
    fn_80182E34(a);
    fn_80182DD4(b);
    fn_80182E04(c);
}

static void fn_8000E784(Record_8036AD78 *pOut)
{
    Record_800817CC record;

    fn_800817CC((Object_8008044C *)fn_80182DC8(), &record);
    pOut->mUnknown0[0] = record.mUnknown16.mUnknown0[0];
    pOut->mUnknown0[1] = record.mUnknown16.mUnknown0[1];
    pOut->mUnknown0[2] = record.mUnknown16.mUnknown0[2];
    pOut->mUnknown0[3] = record.mUnknown16.mUnknown0[3];
    pOut->mUnknown0[4] = record.mUnknown16.mUnknown0[4];
    pOut->mUnknown0[5] = record.mUnknown16.mUnknown0[5];
    pOut->mUnknown0[6] = record.mUnknown16.mUnknown0[6];
    pOut->mUnknown0[7] = record.mUnknown16.mUnknown0[7];
    pOut->mUnknown0[8] = record.mUnknown16.mUnknown0[8];
    pOut->mUnknown0[9] = record.mUnknown16.mUnknown0[9];
    pOut->mUnknown0[10] = record.mUnknown16.mUnknown0[10];
    pOut->mUnknown0[11] = record.mUnknown16.mUnknown0[11];
    pOut->mUnknown0[12] = record.mUnknown16.mUnknown0[12];
    pOut->mUnknown0[13] = record.mUnknown16.mUnknown0[13];
    lbl_803ECE30 = fn_80080E98((Object_8008044C *)fn_80182DC8());
}

static void fn_8000E834(Record_8036AD78 *pRecord)
{
    Object_8007A334 object;
    int i;

    for (i = 0; i <= 13; i++) {
        fn_80022E40(i, pRecord->mUnknown0[i]);
    }
    fn_80049B90(0, lbl_803ECE30);
    fn_80049B90(1, lbl_803ECE30);
    for (i = 0; i <= 2; i++) {
        fn_80049D6C(0, i, 0);
        fn_80049D6C(1, i, 0);
    }
    fn_80049B00(0, 0);
    fn_80049B00(1, 0);
}

static void fn_8000E8FC(int index, int value)
{
    fn_8000E834(&lbl_8036AD78);
    if (lbl_8000F590[index] != 14 || index == 22) {
        Object_8007A334 object;
        int a = 0;
        int b = 0;
        int c = 0;

        fn_8007BA48(&object);
        if (fn_8007BB4C(&object, value, 0)) {
            a = fn_8007BE54(&object);
            b = fn_8007BE7C(&object);
            c = fn_8007BF28(b);
        }
        fn_8007BB04(&object);
        if (c == 14) {
            if (b == 6) {
                fn_80022E40(6, a);
                fn_80022E40(7, a);
            }
        } else {
            switch (b) {
            case 12:
                fn_80022E40(12, 1);
                break;
            case 2:
                fn_80022E40(10, lbl_803EB94C);
                break;
            }
            fn_80022E40(c, a);
        }
    } else {
        switch (index) {
        case 14:
            value += 6;
            fn_80049B00(0, value);
            fn_80049B00(1, value);
            break;
        case 15:
            lbl_803EB948 = value + 45;
            fn_80048FD0(0, value + 45);
            fn_80048FD0(1, lbl_803EB948);
            fn_80049B00(0, 5);
            fn_80049B00(1, 5);
            break;
        case 18:
            fn_80049B90(0, value);
            fn_80049B90(1, value);
            break;
        case 19:
            fn_800490A0(0, 10, 0);
            fn_800490A0(1, 10, 0);
        case 20:
        case 21:
            fn_80049D6C(0, fn_80087BA0(index), value);
            fn_80049D6C(1, fn_80087BA0(index), value);
            break;
        }
    }
    fn_8015D180(fn_80022D78(), 15);
    fn_80022D6C();
}

Class_8000F540 *fn_8000EB3C()
{
    return fn_8000EE2C();
}

unsigned int fn_8000EB5C()
{
    return fn_800886BC(fn_8022F4BC());
}

int fn_8000EB80()
{
    return fn_8000EC44()->mUnknown0;
}

void fn_8000EBA4(int id)
{
    int item;
    int price;
    char buffer[8];

    fn_8008731C(fn_8000EC44()->mUnknown4, id, &item, &price, buffer, 8);
    fn_8000EC44()->mUnknown8 = 1;
    fn_80087600(fn_8000EC44()->mUnknown4, item);
    fn_800888D0(fn_8022F4BC(), price);
}

unsigned char fn_8000EC14()
{
    return fn_8000EC44()->mUnknown8;
}

int fn_8000EC38()
{
    return lbl_803EB948 | 0x40000;
}
