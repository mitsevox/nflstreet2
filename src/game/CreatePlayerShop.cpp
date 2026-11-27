/* Shops of create-a-player: the player picks a shop (Reebok Store,
   Barbershop, Department Store, Jewelry Store, Screen Printing, Sporting
   Goods, Tattoo Parlor), then a category, then an item priced in points.
   The highlighted item is previewed on the two player models over the
   player's saved look, and buying it spends the user's points. */

#include <string.h>
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/FEPlyrLoad.h"
#include "game/UISProcessHint.h"
#include "game/EditMenu.h"

struct ShopSavedLook_t {
    int mGear[14];
};


struct ShopState {
    ShopState();
    ~ShopState();
    int mPrice;
    int mCategory;
    unsigned char mBought;
    int mPlayerId;
    DbCursor mHairCursor;
};

inline ShopState *ShopGetState()
{
    static ShopState sRecord;
    return &sRecord;
}

inline ShopState::ShopState() {}
inline ShopState::~ShopState() {}

class ShopStoreMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 7; }
    virtual MenuEntry_t *GetEntries()
    {
        static const MenuEntry_t sEntries[] = {
            { 0, 0, "Reebok Store", 1 },
            { 1, 0, "Barbershop", 1 },
            { 2, 0, "Department Store", 1 },
            { 3, 0, "Jewelry Store", 1 },
            { 4, 0, "Screen Printing", 1 },
            { 5, 0, "Sporting Goods", 1 },
            { 6, 0, "Tattoo Parlor", 1 },
        };
        return (MenuEntry_t *)sEntries;
    }

    char mUnknown4[4];
};

class ShopItemList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int id);
    virtual void GetItemId(int index, int *pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mCategory;
    char mUnknown12[4];
    unsigned char mOutOfStock;
};

class ShopDepartmentMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 7; }
    virtual MenuEntry_t *GetEntries()
    {
        static const MenuEntry_t sEntries[] = {
            { 0, 0, "Headwear", 1 },
            { 1, 0, "Glasses", 1 },
            { 2, 0, "Short Sleeve Shirts", 1 },
            { 3, 0, "Long Sleeve Shirts", 1 },
            { 4, 0, "Pants", 1 },
            { 5, 0, "Shorts", 1 },
            { 6, 0, "Socks", 1 },
        };
        return (MenuEntry_t *)sEntries;
    }

    char mUnknown4[4];
};

class ShopSportingGoodsMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 7; }
    virtual MenuEntry_t *GetEntries()
    {
        static const MenuEntry_t sEntries[] = {
            { 0, 0, "Throwback Jerseys", 1 },
            { 1, 0, "Shoulder Pads", 1 },
            { 2, 0, "Arm Bands", 1 },
            { 3, 0, "Elbow Pads", 1 },
            { 4, 0, "Wrist", 1 },
            { 5, 0, "Gloves", 1 },
            { 6, 0, "Shoes", 1 },
        };
        return (MenuEntry_t *)sEntries;
    }

    char mUnknown4[4];
};

class ShopScreenPrintingMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 2; }
    virtual MenuEntry_t *GetEntries()
    {
        static const MenuEntry_t sEntries[] = {
            { 0, 0, "Decals", 1 },
            { 1, 0, "Team Logos", 1 },
        };
        return (MenuEntry_t *)sEntries;
    }

    char mUnknown4[4];
};

class ShopTattooMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 3; }
    virtual MenuEntry_t *GetEntries()
    {
        static const MenuEntry_t sEntries[] = {
            { 0, 0, "Back Tattoos", 1 },
            { 1, 0, "Left Arm Tattoos", 1 },
            { 2, 0, "Right Arm Tattoos", 1 },
        };
        return (MenuEntry_t *)sEntries;
    }

    char mUnknown4[4];
};

class ShopJewelryMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 2; }
    virtual MenuEntry_t *GetEntries()
    {
        static const MenuEntry_t sEntries[] = {
            { 0, 0, "Necklaces", 1 },
            { 1, 0, "Medallions", 1 },
        };
        return (MenuEntry_t *)sEntries;
    }

    char mUnknown4[4];
};

inline ShopItemList *ShopGetItemList()
{
    static ShopItemList sInstance;
    return &sInstance;
}

inline ShopDepartmentMenu *ShopGetDepartmentMenu()
{
    static ShopDepartmentMenu sInstance;
    return &sInstance;
}

inline ShopScreenPrintingMenu *ShopGetScreenPrintingMenu()
{
    static ShopScreenPrintingMenu sInstance;
    return &sInstance;
}

inline ShopSportingGoodsMenu *ShopGetSportingGoodsMenu()
{
    static ShopSportingGoodsMenu sInstance;
    return &sInstance;
}

inline ShopTattooMenu *ShopGetTattooMenu()
{
    static ShopTattooMenu sInstance;
    return &sInstance;
}

inline ShopJewelryMenu *ShopGetJewelryMenu()
{
    static ShopJewelryMenu sInstance;
    return &sInstance;
}

inline ShopStoreMenu *ShopGetStoreMenu()
{
    static ShopStoreMenu sInstance;
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
void GearDbOpen(DbCursor *pObject);
void GearDbClose(DbCursor *pObject);
int GearDbSeekKey(DbCursor *pObject, int a, int b);
int GearDbGetId(DbCursor *pObject);
int GearDbGetType(DbCursor *pObject);
int GearDbFindIdByGbst(int a, const char *pName);
int GearDbGetTypeSlot(int index);
void HairListOpen(DbCursor *pObject);
void HairListClose(DbCursor *pObject);
int PlayerDbGetId(Object_8008044C *pObject);
int PlayerDbGetHairStyle(Object_8008044C *pObject);
int StoreGetItemCount(int a);
int StoreGetItemByRow(int a, int id, int *pOut1, int *pOut2, char *pBuffer, int size);
int StoreIsItemLocked(int a, int b);
void StoreUnlockItem(int a, int b);
int StoreClose(void);
int StoreOpen(void);
int StoreGetTattooLocation(int index);
unsigned int UserInfoGetPoints(int a);
void UserInfoSpendPoints(int a, int b);
Object_8008044C *EditMenuGetPlayerCursor(void);
void EditMenuSetHeading(const char *pText);
void EditMenuSetItemName(const char *pText);
void EditMenuSetName(char *pText);
void EditMenuSetView(int a);
void EditMenuShowPlayers(void);
void EditMenuHidePlayers(void);
int DbUserGetCurrent(void);
}

static const int _Shop_aCategorySlots[] = {
    10, 0, 10, 8, 1, 11, 11, 2, 3, 4, 5, 6, 9, 10, 14, 14, 12, 13, 14, 14, 14, 14, 14,
};

static const PlayerLayout_t _Shop_aCategoryLayouts[] = {
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

static int _Shop_iPreviewLogo = -1;
static int _Shop_iMannequinPads = 0;
static int _Shop_iSavedHairStyle;
static int _Shop_iLastStore;
static ShopSavedLook_t _Shop_sSavedLook;

static void _ShopResetView();
static void _ShopSetTexts(char *a, const char *b, const char *c);
static void _ShopSaveLook(ShopSavedLook_t *pOut);
static void _ShopRestoreLook(ShopSavedLook_t *pRecord);
static void _ShopPreviewItem(int index, int value);

void ShopItemList::Enter(int a, int *pCount, int *pOut)
{
    ShopGetState()->mPrice = -1;
    StoreOpen();
    _ShopResetView();
    _ShopSaveLook(&_Shop_sSavedLook);
    _Shop_iMannequinPads = GearDbFindIdByGbst(9, "MANNEQUINSHIRTPADS");
    *pCount = StoreGetItemCount(mCategory);
    if (*pCount == 0) {
        mOutOfStock = 1;
        *pCount = 1;
    } else {
        mOutOfStock = 0;
    }
    *pOut = 0;
    _Shop_iPreviewLogo = -1;
    EditMenuMovePlayers(&_Shop_aCategoryLayouts[mCategory]);
}

int ShopItemList::Leave(int a, int b, void **pOut)
{
    int result = -1;

    _ShopRestoreLook(&_Shop_sSavedLook);
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
    StoreClose();
    ShopGetState()->mPrice = 0;
    EditMenuMovePlayers(0);
    _Shop_iPreviewLogo = result;
    return result;
}

void ShopItemList::GetItemId(int index, int *pOut)
{
    *pOut = index;
}

void ShopItemList::GetItem(int id, MenuEntry_t *pOut)
{
    pOut->mUnknown36 = id;
    pOut->mUnknown4 = 6;
    pOut->mId = id;
    if (mOutOfStock) {
        pOut->mUnknown30 = 0;
        pOut->mUnknown40 = 0;
        strncpy(pOut->mName, "Out of Stock", 22);
    } else {
        int item;
        int price;

        pOut->mUnknown40 = 0;
        StoreGetItemByRow(mCategory, id, &item, &price, pOut->mName, 22);
        if (!StoreIsItemLocked(mCategory, item) || UserInfoGetPoints(DbUserGetCurrent()) < price) {
            pOut->mUnknown30 = 0;
        } else {
            pOut->mUnknown30 = 1;
        }
    }
}

void ShopItemList::Highlight(int id)
{
    if (mOutOfStock) {
        ShopGetState()->mPrice = -1;
    } else {
        int item;
        int price;

        StoreGetItemByRow(mCategory, id, &item, &price, 0, 0);
        _ShopPreviewItem(mCategory, item);
        if (StoreIsItemLocked(mCategory, item)) {
            if (price == 0) {
                ShopGetState()->mPrice = -2;
            } else {
                ShopGetState()->mPrice = price;
            }
        } else {
            ShopGetState()->mPrice = -1;
        }
        UISProcessHint(gUISMainInfo, 0x8000007E, 0, 0);
    }
}

void ShopStoreMenu::Enter(int a, int *pCount, int *pOut)
{
    MenuListScreen::Enter(a, pCount, pOut);
    ShopGetState()->mPrice = 0;
    StoreOpen();
    if (a == 1) {
        int value;

        ShopGetState()->mBought = 0;
        EditMenuShowPlayers();
        HairListOpen(&ShopGetState()->mHairCursor);
        DbCursorFirst((DbCursor *)EditMenuGetPlayerCursor());
        value = PlayerDbGetId(EditMenuGetPlayerCursor());
        ShopGetState()->mPlayerId = value;
        PlayerDbSeekId(EditMenuGetPlayerCursor(), value, 0);
        FEPlyrSetPlayer(FEPlyrGetBackIndex(), value, 1);
        FEPlyrSetPlayer(FEPlyrGetFrontIndex(), value, 1);
        FEPlyrLoadSetScaleRamp(0);
    }
    *pCount = 7;
    *pOut = _Shop_iLastStore;
}

void ShopStoreMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    _ShopSetTexts("", "", "");
}

void ShopDepartmentMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    _ShopSetTexts("", "", "");
}

void ShopScreenPrintingMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    _ShopSetTexts("", "", "");
}

void ShopSportingGoodsMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    _ShopSetTexts("", "", "");
}

void ShopTattooMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    _ShopSetTexts("", "", "");
}

void ShopJewelryMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = 0;
    pOut->mUnknown30 = 1;
    _ShopSetTexts("", "", "");
}

int ShopStoreMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b) {
        EditMenuHidePlayers();
        result = -1;
        HairListClose(&ShopGetState()->mHairCursor);
        ShopGetState()->mPlayerId = result;
        ShopGetState()->mPrice = 0;
    } else {
        ShopItemList *pItems;

        switch (a) {
        case 0:
            _Shop_iLastStore = a;
            pItems = ShopGetItemList();
            result = 1;
            *pOut = pItems;
            pItems->mCategory = 22;
            ShopGetState()->mCategory = 22;
            break;
        case 1:
            _Shop_iLastStore = a;
            pItems = ShopGetItemList();
            result = 1;
            *pOut = pItems;
            pItems->mCategory = 18;
            ShopGetState()->mCategory = 18;
            break;
        case 2:
            _Shop_iLastStore = 2;
            result = 1;
            *pOut = ShopGetDepartmentMenu();
            break;
        case 4:
            _Shop_iLastStore = 4;
            result = 1;
            *pOut = ShopGetScreenPrintingMenu();
            break;
        case 5:
            _Shop_iLastStore = a;
            result = 1;
            *pOut = ShopGetSportingGoodsMenu();
            break;
        case 6:
            _Shop_iLastStore = a;
            result = 1;
            *pOut = ShopGetTattooMenu();
            break;
        case 3:
            _Shop_iLastStore = a;
            result = 1;
            *pOut = ShopGetJewelryMenu();
            break;
        }
    }
    return result;
}

int ShopDepartmentMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        ShopItemList *pItems;

        switch (a) {
        case 0:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 1;
            ShopGetState()->mCategory = 1;
            return 1;
        case 1:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 4;
            ShopGetState()->mCategory = 4;
            return 1;
        case 2:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 0;
            ShopGetState()->mCategory = 0;
            return 1;
        case 3:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 2;
            ShopGetState()->mCategory = 2;
            return 1;
        case 4:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 5;
            ShopGetState()->mCategory = 5;
            return 1;
        case 5:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 6;
            ShopGetState()->mCategory = 6;
            return 1;
        case 6:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 3;
            ShopGetState()->mCategory = 3;
            return 1;
        }
    }
    return result;
}

int ShopSportingGoodsMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        ShopItemList *pItems;

        switch (a) {
        case 0:
            pItems = ShopGetItemList();
            *pOut = pItems;
            result = 1;
            pItems->mCategory = 13;
            ShopGetState()->mCategory = 13;
            break;
        case 1:
            pItems = ShopGetItemList();
            *pOut = pItems;
            result = 1;
            pItems->mCategory = 7;
            ShopGetState()->mCategory = 7;
            break;
        case 2:
            pItems = ShopGetItemList();
            *pOut = pItems;
            result = 1;
            pItems->mCategory = 8;
            ShopGetState()->mCategory = 8;
            break;
        case 3:
            pItems = ShopGetItemList();
            *pOut = pItems;
            result = 1;
            pItems->mCategory = 9;
            ShopGetState()->mCategory = 9;
            break;
        case 4:
            pItems = ShopGetItemList();
            *pOut = pItems;
            result = 1;
            pItems->mCategory = 10;
            ShopGetState()->mCategory = 10;
            FEPlyrSetPose(0, 8);
            FEPlyrSetPose(1, 8);
            break;
        case 5:
            pItems = ShopGetItemList();
            *pOut = pItems;
            result = 1;
            pItems->mCategory = 11;
            ShopGetState()->mCategory = 11;
            FEPlyrSetPose(0, 8);
            FEPlyrSetPose(1, 8);
            break;
        case 6:
            pItems = ShopGetItemList();
            *pOut = pItems;
            result = 1;
            pItems->mCategory = 12;
            ShopGetState()->mCategory = 12;
            break;
        }
    }
    return result;
}

int ShopScreenPrintingMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        ShopItemList *pItems;

        switch (a) {
        case 0:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 14;
            ShopGetState()->mCategory = 14;
            return 1;
        case 1:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 15;
            ShopGetState()->mCategory = 15;
            return 1;
        }
    }
    return result;
}

int ShopTattooMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        ShopItemList *pItems;

        switch (a) {
        case 0:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 19;
            ShopGetState()->mCategory = 19;
            return 1;
        case 2:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 20;
            ShopGetState()->mCategory = 20;
            return 1;
        case 1:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 21;
            ShopGetState()->mCategory = 21;
            return 1;
        }
    }
    return result;
}

int ShopJewelryMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        ShopItemList *pItems;

        switch (a) {
        case 0:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 16;
            ShopGetState()->mCategory = 16;
            return 1;
        case 1:
            pItems = ShopGetItemList();
            *pOut = pItems;
            pItems->mCategory = 17;
            ShopGetState()->mCategory = 17;
            return 1;
        }
    }
    return result;
}

static void _ShopResetView()
{
    EditMenuSetView(900);
    _ShopSetTexts("", "", "");
}

static void _ShopSetTexts(char *a, const char *b, const char *c)
{
    EditMenuSetName(a);
    EditMenuSetHeading(b);
    EditMenuSetItemName(c);
}

static void _ShopSaveLook(ShopSavedLook_t *pOut)
{
    PlayerGear_t record;

    PlayerDbReadGear(EditMenuGetPlayerCursor(), &record);
    pOut->mGear[0] = record.mValues[0];
    pOut->mGear[1] = record.mValues[1];
    pOut->mGear[2] = record.mValues[2];
    pOut->mGear[3] = record.mValues[3];
    pOut->mGear[4] = record.mValues[4];
    pOut->mGear[5] = record.mValues[5];
    pOut->mGear[6] = record.mValues[6];
    pOut->mGear[7] = record.mValues[7];
    pOut->mGear[8] = record.mValues[8];
    pOut->mGear[9] = record.mValues[9];
    pOut->mGear[10] = record.mValues[10];
    pOut->mGear[11] = record.mValues[11];
    pOut->mGear[12] = record.mValues[12];
    pOut->mGear[13] = record.mValues[13];
    _Shop_iSavedHairStyle = PlayerDbGetHairStyle(EditMenuGetPlayerCursor());
}

static void _ShopRestoreLook(ShopSavedLook_t *pRecord)
{
    DbCursor object;
    int i;

    for (i = 0; i <= 13; i++) {
        FEPlyrSetPairSlot(i, pRecord->mGear[i]);
    }
    PlayerLookSetHair(0, _Shop_iSavedHairStyle);
    PlayerLookSetHair(1, _Shop_iSavedHairStyle);
    for (i = 0; i <= 2; i++) {
        PlayerLookSetPartVariant(0, i, 0);
        PlayerLookSetPartVariant(1, i, 0);
    }
    PlayerLookSetFrontDecalKind(0, 0);
    PlayerLookSetFrontDecalKind(1, 0);
}

static void _ShopPreviewItem(int index, int value)
{
    _ShopRestoreLook(&_Shop_sSavedLook);
    if (_Shop_aCategorySlots[index] != 14 || index == 22) {
        DbCursor object;
        int a = 0;
        int b = 0;
        int c = 0;

        GearDbOpen(&object);
        if (GearDbSeekKey(&object, value, 0)) {
            a = GearDbGetId(&object);
            b = GearDbGetType(&object);
            c = GearDbGetTypeSlot(b);
        }
        GearDbClose(&object);
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
                FEPlyrSetPairSlot(10, _Shop_iMannequinPads);
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
            _Shop_iPreviewLogo = value + 45;
            PlayerLookSetLogo(0, value + 45);
            PlayerLookSetLogo(1, _Shop_iPreviewLogo);
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
            PlayerLookSetPartVariant(0, StoreGetTattooLocation(index), value);
            PlayerLookSetPartVariant(1, StoreGetTattooLocation(index), value);
            break;
        }
    }
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
}

extern "C" ShopStoreMenu *ShopGetMenu()
{
    return ShopGetStoreMenu();
}

extern "C" unsigned int ShopGetPoints()
{
    return UserInfoGetPoints(DbUserGetCurrent());
}

extern "C" int ShopGetPrice()
{
    return ShopGetState()->mPrice;
}

extern "C" void ShopBuyItem(int id)
{
    int item;
    int price;
    char buffer[8];

    StoreGetItemByRow(ShopGetState()->mCategory, id, &item, &price, buffer, 8);
    ShopGetState()->mBought = 1;
    StoreUnlockItem(ShopGetState()->mCategory, item);
    UserInfoSpendPoints(DbUserGetCurrent(), price);
}

extern "C" unsigned char ShopIsBought()
{
    return ShopGetState()->mBought;
}

extern "C" int ShopGetPreviewLogo()
{
    return _Shop_iPreviewLogo | 0x40000;
}
