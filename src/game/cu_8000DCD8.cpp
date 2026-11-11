#include <string.h>
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/FEPlyrLoad.h"
#include "game/fn_8021D7B8.h"
#include "game/cu_80181330.h"

/* lbl_8036AD78: fourteen words copied from the record filled by fn_800817CC. */
struct Record_8036AD78 {
    int mUnknown0[14];
};


/* Object returned by fn_8000EC44. */
struct Record_8036AD28 {
    Record_8036AD28();
    ~Record_8036AD28();
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    int mUnknown12;
    DbCursor mUnknown16;
};

inline Record_8036AD28 *fn_8000EC44()
{
    static Record_8036AD28 sRecord;
    return &sRecord;
}

inline Record_8036AD28::Record_8036AD28() {}
inline Record_8036AD28::~Record_8036AD28() {}

class Class_8000F540 : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, Entry_80182CC8 *pOut);
    virtual int GetEntryCount() { return 7; }
    virtual Entry_80182CC8 *GetEntries()
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

class Class_8000F500 : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int id);
    virtual void GetItemId(int index, int *pOut);
    virtual void GetItem(int id, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
    char mUnknown12[4];
    unsigned char mUnknown16;
};

class Class_8000F4B0 : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, Entry_80182CC8 *pOut);
    virtual int GetEntryCount() { return 7; }
    virtual Entry_80182CC8 *GetEntries()
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

class Class_8000F460 : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, Entry_80182CC8 *pOut);
    virtual int GetEntryCount() { return 7; }
    virtual Entry_80182CC8 *GetEntries()
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

class Class_8000F410 : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, Entry_80182CC8 *pOut);
    virtual int GetEntryCount() { return 2; }
    virtual Entry_80182CC8 *GetEntries()
    {
        static const Entry_80182CC8 sEntries[] = {
            { 0, 0, "Decals", 1 },
            { 1, 0, "Team Logos", 1 },
        };
        return (Entry_80182CC8 *)sEntries;
    }

    char mUnknown4[4];
};

class Class_8000F3C0 : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, Entry_80182CC8 *pOut);
    virtual int GetEntryCount() { return 3; }
    virtual Entry_80182CC8 *GetEntries()
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

class Class_8000F370 : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, Entry_80182CC8 *pOut);
    virtual int GetEntryCount() { return 2; }
    virtual Entry_80182CC8 *GetEntries()
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
extern void *gUISMainInfo;

int FEPlyrGetBackIndex(void);
int FEPlyrGetFrontIndex(void);
void FEPlyrRequestSwap(void);
void FEPlyrSetPose(int index, unsigned int value);
void FEPlyrSetPlayer(int index, int a, int b);
void FEPlyrSetPairSlot(int a, int b);
void PlayerLookSetLogo(int a, int b);
void PlayerLookSetGear(int index, int a, int b);
void PlayerLookSetFrontDecalKind(int a, int b);
void PlayerLookSetHair(int a, int b);
void PlayerLookSetPartVariant(int a, unsigned int b, int c);
void fn_8007BA48(DbCursor *pObject);
void fn_8007BB04(DbCursor *pObject);
int fn_8007BB4C(DbCursor *pObject, int a, int b);
int fn_8007BE54(DbCursor *pObject);
int fn_8007BE7C(DbCursor *pObject);
int fn_8007BECC(int a, const char *pName);
int fn_8007BF28(int index);
void HairListOpen(DbCursor *pObject);
void HairListClose(DbCursor *pObject);
int PlayerDbGetId(Object_8008044C *pObject);
int PlayerDbGetHairStyle(Object_8008044C *pObject);
int fn_800872E8(int a);
int fn_8008731C(int a, int id, int *pOut1, int *pOut2, char *pBuffer, int size);
int fn_8008736C(int a, int b);
void fn_80087600(int a, int b);
int fn_800876C0(void);
int fn_80087704(void);
int fn_80087BA0(int index);
unsigned int UserInfoGetPoints(int a);
void UserInfoSpendPoints(int a, int b);
Object_8008044C *fn_80182DC8(void);
void fn_80182DD4(const char *pText);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_801835C0(int a);
void fn_801835C8(void);
void fn_80183704(void);
int fn_8022F4BC(void);
}

static const int lbl_8000F590[] = {
    10, 0, 10, 8, 1, 11, 11, 2, 3, 4, 5, 6, 9, 10, 14, 14, 12, 13, 14, 14, 14, 14, 14,
};

static const Layout_802EA9E0 lbl_8000F5EC[] = {
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

void Class_8000F500::Enter(int a, int *pCount, int *pOut)
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

int Class_8000F500::Leave(int a, int b, void **pOut)
{
    int result = -1;

    fn_8000E834(&lbl_8036AD78);
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
    fn_800876C0();
    fn_8000EC44()->mUnknown0 = 0;
    fn_80183740(0);
    lbl_803EB948 = result;
    return result;
}

void Class_8000F500::GetItemId(int index, int *pOut)
{
    *pOut = index;
}

void Class_8000F500::GetItem(int id, Entry_80182CC8 *pOut)
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
        if (!fn_8008736C(mUnknown8, item) || UserInfoGetPoints(fn_8022F4BC()) < price) {
            pOut->mUnknown30 = 0;
        } else {
            pOut->mUnknown30 = 1;
        }
    }
}

void Class_8000F500::Highlight(int id)
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
        fn_8021D7B8(gUISMainInfo, 0x8000007E, 0, 0);
    }
}

void Class_8000F540::Enter(int a, int *pCount, int *pOut)
{
    MenuListScreen::Enter(a, pCount, pOut);
    fn_8000EC44()->mUnknown0 = 0;
    fn_80087704();
    if (a == 1) {
        int value;

        fn_8000EC44()->mUnknown8 = 0;
        fn_801835C8();
        HairListOpen(&fn_8000EC44()->mUnknown16);
        DbCursorFirst((DbCursor *)fn_80182DC8());
        value = PlayerDbGetId(fn_80182DC8());
        fn_8000EC44()->mUnknown12 = value;
        PlayerDbSeekId(fn_80182DC8(), value, 0);
        FEPlyrSetPlayer(FEPlyrGetBackIndex(), value, 1);
        FEPlyrSetPlayer(FEPlyrGetFrontIndex(), value, 1);
        FEPlyrLoadSetScaleRamp(0);
    }
    *pCount = 7;
    *pOut = lbl_803ECE34;
}

void Class_8000F540::GetItem(int id, Entry_80182CC8 *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F4B0::GetItem(int id, Entry_80182CC8 *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F410::GetItem(int id, Entry_80182CC8 *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F460::GetItem(int id, Entry_80182CC8 *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F3C0::GetItem(int id, Entry_80182CC8 *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

void Class_8000F370::GetItem(int id, Entry_80182CC8 *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    fn_8000E744("", "", "");
}

int Class_8000F540::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b) {
        fn_80183704();
        result = -1;
        HairListClose(&fn_8000EC44()->mUnknown16);
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

int Class_8000F4B0::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

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

int Class_8000F460::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

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
            FEPlyrSetPose(0, 8);
            FEPlyrSetPose(1, 8);
            break;
        case 5:
            pItems = fn_8000ED34();
            *pOut = pItems;
            result = 1;
            pItems->mUnknown8 = 11;
            fn_8000EC44()->mUnknown4 = 11;
            FEPlyrSetPose(0, 8);
            FEPlyrSetPose(1, 8);
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

int Class_8000F410::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

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

int Class_8000F3C0::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

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

int Class_8000F370::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

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
    Info_80307908 record;

    fn_800817CC(fn_80182DC8(), &record);
    pOut->mUnknown0[0] = record.mValues[0];
    pOut->mUnknown0[1] = record.mValues[1];
    pOut->mUnknown0[2] = record.mValues[2];
    pOut->mUnknown0[3] = record.mValues[3];
    pOut->mUnknown0[4] = record.mValues[4];
    pOut->mUnknown0[5] = record.mValues[5];
    pOut->mUnknown0[6] = record.mValues[6];
    pOut->mUnknown0[7] = record.mValues[7];
    pOut->mUnknown0[8] = record.mValues[8];
    pOut->mUnknown0[9] = record.mValues[9];
    pOut->mUnknown0[10] = record.mValues[10];
    pOut->mUnknown0[11] = record.mValues[11];
    pOut->mUnknown0[12] = record.mValues[12];
    pOut->mUnknown0[13] = record.mValues[13];
    lbl_803ECE30 = PlayerDbGetHairStyle(fn_80182DC8());
}

static void fn_8000E834(Record_8036AD78 *pRecord)
{
    DbCursor object;
    int i;

    for (i = 0; i <= 13; i++) {
        FEPlyrSetPairSlot(i, pRecord->mUnknown0[i]);
    }
    PlayerLookSetHair(0, lbl_803ECE30);
    PlayerLookSetHair(1, lbl_803ECE30);
    for (i = 0; i <= 2; i++) {
        PlayerLookSetPartVariant(0, i, 0);
        PlayerLookSetPartVariant(1, i, 0);
    }
    PlayerLookSetFrontDecalKind(0, 0);
    PlayerLookSetFrontDecalKind(1, 0);
}

static void fn_8000E8FC(int index, int value)
{
    fn_8000E834(&lbl_8036AD78);
    if (lbl_8000F590[index] != 14 || index == 22) {
        DbCursor object;
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
                FEPlyrSetPairSlot(6, a);
                FEPlyrSetPairSlot(7, a);
            }
        } else {
            switch (b) {
            case 12:
                FEPlyrSetPairSlot(12, 1);
                break;
            case 2:
                FEPlyrSetPairSlot(10, lbl_803EB94C);
                break;
            }
            FEPlyrSetPairSlot(c, a);
        }
    } else {
        switch (index) {
        case 14:
            value += 6;
            PlayerLookSetFrontDecalKind(0, value);
            PlayerLookSetFrontDecalKind(1, value);
            break;
        case 15:
            lbl_803EB948 = value + 45;
            PlayerLookSetLogo(0, value + 45);
            PlayerLookSetLogo(1, lbl_803EB948);
            PlayerLookSetFrontDecalKind(0, 5);
            PlayerLookSetFrontDecalKind(1, 5);
            break;
        case 18:
            PlayerLookSetHair(0, value);
            PlayerLookSetHair(1, value);
            break;
        case 19:
            PlayerLookSetGear(0, 10, 0);
            PlayerLookSetGear(1, 10, 0);
        case 20:
        case 21:
            PlayerLookSetPartVariant(0, fn_80087BA0(index), value);
            PlayerLookSetPartVariant(1, fn_80087BA0(index), value);
            break;
        }
    }
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
}

Class_8000F540 *fn_8000EB3C()
{
    return fn_8000EE2C();
}

unsigned int fn_8000EB5C()
{
    return UserInfoGetPoints(fn_8022F4BC());
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
    UserInfoSpendPoints(fn_8022F4BC(), price);
}

unsigned char fn_8000EC14()
{
    return fn_8000EC44()->mUnknown8;
}

int fn_8000EC38()
{
    return lbl_803EB948 | 0x40000;
}
