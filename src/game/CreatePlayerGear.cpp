/* Gear menus of create-a-player: the player picks a body area (head, arms,
   torso, legs), then a gear category, then an item, decal or decal team.
   Each choice is previewed on the player model and stored in the player's
   gear record; unique items are taken from the teammate who wore them. */

#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/Row_8007BC34.h"
#include "game/FEPlyrLoad.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

/* One selectable gear row of the current category, built by _GearBuildItemList. */
struct GearItem_t {
    int mUnknown0;
    int mId;
    int mOwner;
    unsigned char mUnknown12;
};

extern "C" {
void FEPlyrSetPose(int index, unsigned int value);
void FEPlyrSetPlayer(int index, int a, int b);
void FEPlyrRequestSwap(void);
int FEPlyrGetBackIndex(void);
int FEPlyrGetFrontIndex(void);
void FEPlyrSetPairSlot(int a, int b);
int DecalCountUnlocked(int index);
int DecalCountNew(int index);
void DecalGetName(int a, char *pBuffer, int size);
unsigned char DecalIsNew(int index, int a);
void DecalClearNew(int index, int a);
int DecalFindIndex(int index, int a);
int DecalGetIdAt(int index, int a);
int PlayerLookMapHatKind(unsigned int type);
int PlayerLookItemKeepsLogo(int type);
void PlayerLookSetHeadDecalColors(int index, int value);
void PlayerLookSetDecalColors(int index, int value);
void PlayerLookSetHatStyle(int index, unsigned char value);
void PlayerLookSetHeadDecalKind(int index, unsigned char value);
void PlayerLookSetFrontDecalKind(int index, int value);
void PlayerLookSetBackDecalKind(int index, unsigned char value);
void PlayerLookSetSwitchFlagsA(int index, unsigned char value);
void PlayerLookSetSwitchFlagsB(int index, unsigned char value);
int DbCursorGetRow(DbCursor *pObject);
void fn_8007BA88(DbCursor *pCursor, int value);
void fn_8007BB04(DbCursor *pCursor);
int fn_8007BB24(DbCursor *pCursor);
int fn_8007BBFC(DbCursor *pCursor, int key, int *pResult);
void fn_8007BE20(DbCursor *pCursor, char *pBuffer, int size);
int fn_8007BE54(DbCursor *pCursor);
int fn_8007BE7C(DbCursor *pCursor);
int fn_8007BEA4(DbCursor *pCursor);
int fn_8007BF14(int index);
int fn_8007BF28(int index);
int fn_8007BF3C(DbCursor *pCursor);
int fn_8007C690(DbCursor *pCursor, short *pOut);
void GearLockOpen(DbCursor *pObject, int a);
void GearLockClose(DbCursor *pObject);
void GearLockGetFlags(DbCursor *pObject, int key, unsigned char *pA, unsigned char *pB);
void GearLockClearNew(DbCursor *pObject, int id);
int GearHasNew(int type, int a, int b);
int PlayerDbGetId(Object_8008044C *pObject);
int PlayerDbGetPortraitId(Object_8008044C *pObject);
void fn_8008199C(Object_8008044C *pObject, PlayerGear_t *pInfo);
DbCursor *fn_80182DBC(void);
Object_8008044C *fn_80182DC8(void);
void fn_80182DD4(const char *pText);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_80182ED0(void);
void fn_80182F24(PlayerGear_t *pInfo);
void fn_80182FD4(int a, unsigned char value);
void fn_8018300C(void);
void fn_80183130(int a);
void fn_801831A4(void);
void fn_801831E8(unsigned char a);
void fn_801832B0(char *pText, int size);
int fn_80183354(void);
void fn_801835C8(void);
void fn_80183704(void);
int fn_80183948(void);
int fn_80183950(void);
int fn_80183968(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C302C(const char *s1, const char *s2, int n);
int fn_8022F384(int a);
int fn_8022F4BC(void);
}

extern const MenuEntry_t _Gear_aAreaEntries[];
extern const MenuEntry_t _Gear_aHeadEntries[];
extern const MenuEntry_t _Gear_aJewelryEntries[];
extern const MenuEntry_t _Gear_aTorsoEntries[];
extern const MenuEntry_t _Gear_aShirtEntries[];
extern const MenuEntry_t _Gear_aArmsEntries[];
extern const MenuEntry_t _Gear_aLegsEntries[];
extern const int _Gear_aHeadCategories[];
extern const int _Gear_aTorsoCategories[];
extern const int _Gear_aShirtCategories[];
extern const int _Gear_aArmsCategories[];
extern const int _Gear_aLegsCategories[];

/* Entries of the body-area menu and its submenus. */
const MenuEntry_t _Gear_aAreaEntries[] = {
    { 0, 0, "Head", 1 },
    { 1, 0, "Arms", 1 },
    { 2, 0, "Torso", 1 },
    { 3, 0, "Legs", 1 },
};

const MenuEntry_t _Gear_aHeadEntries[] = {
    { 0, 0, "Headwear", 1, 20 },
    { 1, 0, "Headwear Style", 1, 21 },
    { 2, 0, "Headwear Decal", 1, 19 },
    { 3, 0, "Glasses", 1, 15 },
};

const MenuEntry_t _Gear_aJewelryEntries[] = {
    { 0, 0, "Chain", 1 },
    { 1, 0, "Medallion", 1 },
};

const MenuEntry_t _Gear_aTorsoEntries[] = {
    { 0, 0, "Shirt", 1, 34 },
    { 1, 0, "Front Decal", 1, 13 },
    { 2, 0, "Back Decal", 1, 3 },
    { 3, 0, "Shoulder Pads", 1, 36 },
    { 4, 0, "Jewelry", 1 },
};

const MenuEntry_t _Gear_aShirtEntries[] = {
    { 0, 0, "Long Sleeve", 1, 34 },
    { 1, 0, "Short Sleeve", 1, 34 },
    { 2, 0, "Jersey", 1, 34 },
    { 3, 0, "NFL Jersey", 1, 34 },
    { 4, 0, "Throwback Jersey", 1, 34 },
};

const MenuEntry_t _Gear_aArmsEntries[] = {
    { 0, 0, "Upper Arm", 1, 53 },
    { 1, 0, "Elbow", 1, 10 },
    { 2, 0, "Wrist", 1, 55 },
    { 3, 0, "Hands", 1, 18 },
};

const MenuEntry_t _Gear_aLegsEntries[] = {
    { 0, 0, "Pants", 1, 26 },
    { 1, 0, "Socks", 1, 43 },
    { 2, 0, "Shoes", 1, 35 },
};

/* Gear category of each menu entry; 14 marks an entry without one. */
const int _Gear_aHeadCategories[] = { 0, 14, 14, 1 };
const int _Gear_aTorsoCategories[] = { 14, 14, 14, 2, 14 };
const int _Gear_aShirtCategories[] = { 10, 10, 10, 10, 10 };
const int _Gear_aArmsCategories[] = { 3, 4, 5, 6 };
const int _Gear_aLegsCategories[] = { 11, 8, 9 };
static const int _Gear_aJewelryCategories[] = { 12, 13 };

static const char *_Gear_aSideNames[] = { "L", "R", "B" };
static const char *_Gear_aHatStyleNames[] = {
    "Front", "Back", "Side", "Upside Down Front", "Upside Down Back", "Upside Down Side",
};
static const char *_Gear_aDecalOptionNames[] = {
    "None", "Number", "Team Name", "Team Logo & Name", "Team Logo & Name", "Team Logo",
};
static int _Gear_aDecalOptions[] = { 0, 1, 5 };
static int _Gear_aDecalOptionsMode5[] = { 0, 1, 5, 2, 3 };
static int _Gear_aHatStylesKind1[] = { 0, 1, 2 };
static int _Gear_aHatStylesKind7[] = { 0, 2, 3, 5, 1 };

static const Layout_802EA9E0 _Gear_aAreaLayouts[] = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 1 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, -15.0f, 0.0f, 335.0f, 0.25f, 15, 0 },
};

static const unsigned short _Gear_aCategoryPoses[] = { 2, 2, 14, 11, 11, 12, 8, 12, 15, 15, 2, 9, 2, 2 };

static inline bool AnyDecalFlagged()
{
    return DecalCountNew(fn_80183354()) != 0;
}

class GearPlayerList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut);
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
};

class GearAreaMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int id);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 4; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_Gear_aAreaEntries; }

    char mUnknown4[4];
};

class GearHeadMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 4; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_Gear_aHeadEntries; }
    int HasNewItems();

    char mUnknown4[4];
};

class GearJewelryMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 2; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_Gear_aJewelryEntries; }
    int HasNewItems();

    char mUnknown4[4];
};

class GearTorsoMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 5; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_Gear_aTorsoEntries; }
    int HasNewItems();

    char mUnknown4[4];
};

class GearShirtMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 5; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_Gear_aShirtEntries; }
    int HasNewItems();

    char mUnknown4[4];
};

class GearArmsMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 4; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_Gear_aArmsEntries; }
    int HasNewItems();

    char mUnknown4[4];
};

class GearLegsMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **pOut);
    virtual void GetItem(int id, MenuEntry_t *pOut);
    virtual int GetEntryCount() { return 3; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_Gear_aLegsEntries; }
    int HasNewItems();

    char mUnknown4[4];
};

class GearItemList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
    int mUnknown12;
};

class GearDecalTeamList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
    int mUnknown12;
};

class GearHeadwearOptionList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class GearShirtDecalList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

static inline GearHeadMenu *_GearGetHeadMenu();
static inline GearTorsoMenu *_GearGetTorsoMenu();
static inline GearArmsMenu *_GearGetArmsMenu();
static inline GearLegsMenu *_GearGetLegsMenu();
static inline GearAreaMenu *_GearGetAreaMenu();
static inline GearItemList *_GearGetItemList();
static inline GearHeadwearOptionList *_GearGetHeadwearOptionList();
static inline GearShirtMenu *_GearGetShirtMenu();
static inline GearShirtDecalList *_GearGetShirtDecalList();
static inline GearJewelryMenu *_GearGetJewelryMenu();
static inline GearDecalTeamList *_GearGetDecalTeamList();

static DbCursor _Gear_sItemCursor;
static DbCursor _Gear_sLockCursor;
static DbCursor _Gear_sTeamCursor;
static PlayerGear_t _Gear_sPlayerGear;
static GearItem_t _Gear_aItems[166];
static unsigned char _Gear_bFromCreatePlayer = 0;
static int _Gear_iCategory;
static int _Gear_iItemSet;
static int _Gear_iItemCount;
static int _Gear_iPlayerId;

static void _GearTakeFromOwner(int id, int index)
{
    if (_Gear_iCategory != 14) {
        int type = fn_8007BF14(_Gear_iCategory);
        int row = DbCursorGetRow((DbCursor *)fn_80182DC8());
        PlayerGear_t info;

        PlayerDbSeekId(fn_80182DC8(), id, 0);
        fn_800817CC(fn_80182DC8(), &info);
        fn_8007BBFC(&_Gear_sItemCursor, 0, 0);
        if (fn_8007BF28(type) != 14) {
            info.mValues[fn_8007BF28(type)] = 0;
        } else if (type == 6) {
            info.mValues[7] = 0;
            info.mValues[6] = 0;
        }
        fn_8008199C(fn_80182DC8(), &info);
        DbCursorSeek((DbCursor *)fn_80182DC8(), row);
    }
}

static int _GearFindOwner(int type, int value)
{
    int result = -1;

    if (_Gear_iCategory != 14) {
        int row = DbCursorGetRow((DbCursor *)fn_80182DC8());
        PlayerGear_t info;
        int found;

        for (found = DbCursorFirst((DbCursor *)fn_80182DC8()); found && result == -1; found = DbCursorNext((DbCursor *)fn_80182DC8())) {
            int id;

            fn_800817CC(fn_80182DC8(), &info);
            id = PlayerDbGetId(fn_80182DC8());
            if (fn_8007BF28(type) != 14) {
                if (info.mValues[fn_8007BF28(type)] == value) {
                    result = id;
                }
            } else if (type == 6) {
                if (info.mValues[7] == value || info.mValues[6] == value) {
                    result = id;
                }
            }
        }
        DbCursorSeek((DbCursor *)fn_80182DC8(), row);
    }
    return result;
}

static void _GearShowOwner()
{
    int type = fn_8007BE7C(&_Gear_sItemCursor);
    int id = fn_8007BE54(&_Gear_sItemCursor);
    int unique = fn_8007BF3C(&_Gear_sItemCursor);
    int current = PlayerDbGetId(fn_80182DC8());
    int owner = _GearFindOwner(type, id);

    if (unique && owner != -1 && owner != current) {
        fn_80183130(owner);
    } else {
        fn_801831A4();
    }
}

static void _GearMarkAffectedRatings()
{
    short flags[10];

    fn_8018300C();
    if (fn_8007C690(&_Gear_sItemCursor, flags)) {
        int i;

        for (i = 0; i <= 9; i++) {
            if (flags[i]) {
                fn_80182FD4(i, 1);
            }
        }
    }
}

static int _GearBuildItemList()
{
    int type = fn_8007BF14(_Gear_iCategory);
    int showUnique = 1;
    int count;
    int i;

    if (fn_80183950() || fn_80183948() == 5) {
        showUnique = 0;
    }
    fn_8007BA88(&_Gear_sItemCursor, type);
    count = DbCursorGetRowCount(&_Gear_sItemCursor);
    _Gear_iItemCount = 0;
    DbCursorFirst(&_Gear_sItemCursor);
    for (i = 0; i < count; i++) {
        int id = fn_8007BE54(&_Gear_sItemCursor);
        int set = fn_8007BEA4(&_Gear_sItemCursor);

        if (id == 0 || _Gear_iItemSet == set) {
            int key = fn_8007BB24(&_Gear_sItemCursor);
            int unique = fn_8007BF3C(&_Gear_sItemCursor);
            unsigned char locked;
            unsigned char flag;

            GearLockGetFlags(&_Gear_sLockCursor, key, &locked, &flag);
            if (!locked && (showUnique || !unique)) {
                _Gear_aItems[_Gear_iItemCount].mUnknown12 = flag;
                if (unique) {
                    _Gear_aItems[_Gear_iItemCount].mOwner = _GearFindOwner(type, id);
                } else {
                    _Gear_aItems[_Gear_iItemCount].mOwner = -1;
                }
                _Gear_aItems[_Gear_iItemCount].mUnknown0 = key;
                _Gear_aItems[_Gear_iItemCount].mId = id;
                _Gear_iItemCount++;
            }
        }
        DbCursorNext(&_Gear_sItemCursor);
    }
    return _Gear_iItemCount;
}

static void _GearCloseItemList()
{
    fn_8007BB04(&_Gear_sItemCursor);
}

static int _GearFindItemIndex(int id)
{
    int i;

    for (i = 0; i < _Gear_iItemCount; i++) {
        if (_Gear_aItems[i].mId == id) {
            break;
        }
    }
    if (i >= _Gear_iItemCount) {
        i = 0;
    }
    return i;
}

static int _GearCategoryHasNew(int index, int a)
{
    int result = 0;

    if (index != 14) {
        int type = fn_8007BF14(index);

        result = GearHasNew(type, a, fn_80183968());
    }
    return result;
}

static int _GearCategoryAnyNew(int index)
{
    return _GearCategoryHasNew(index, -1);
}

static int _GearTypeHasSides(int type)
{
    switch (type) {
    case 3:
    case 5:
    case 6:
        return 1;
    }
    return 0;
}

static int _GearGetSide(int type)
{
    int result = 0;

    switch (type) {
    case 3:
        result = _Gear_sPlayerGear.mUnknown00 - 1;
        break;
    case 5:
        result = _Gear_sPlayerGear.mUnknown01 - 1;
        break;
    case 6:
        if (_Gear_sPlayerGear.mValues[6] && _Gear_sPlayerGear.mValues[7] &&
            _Gear_sPlayerGear.mValues[6] == _Gear_sPlayerGear.mValues[7]) {
            result = 2;
        } else {
            result = _Gear_sPlayerGear.mValues[6] == 0;
        }
        break;
    }
    return result;
}

static void _GearSetSide(int type, int value, int item)
{
    switch (type) {
    case 3:
        _Gear_sPlayerGear.mUnknown00 = value + 1;
        break;
    case 5:
        _Gear_sPlayerGear.mUnknown01 = value + 1;
        break;
    case 6:
        if (item == 0) {
            _Gear_sPlayerGear.mValues[6] = 0;
            _Gear_sPlayerGear.mValues[7] = 0;
        } else {
            switch (value) {
            case 0:
                _Gear_sPlayerGear.mValues[6] = item;
                _Gear_sPlayerGear.mValues[7] = 0;
                break;
            case 1:
                _Gear_sPlayerGear.mValues[6] = 0;
                _Gear_sPlayerGear.mValues[7] = item;
                break;
            case 2:
                _Gear_sPlayerGear.mValues[6] = item;
                _Gear_sPlayerGear.mValues[7] = item;
                break;
            default:
                _Gear_sPlayerGear.mValues[6] = 0;
                _Gear_sPlayerGear.mValues[7] = 0;
                break;
            }
        }
        break;
    }
}

static unsigned int _GearFindTableIndex(int value, int *pTable, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (pTable[i] == value) {
            break;
        }
    }
    if (i >= count) {
        i = 0;
    }
    return i;
}

static int _GearGetHatKind(unsigned char *pFlag, unsigned char *pSkullcap)
{
    Row_8007BC34 row;
    DbCursor cursor;
    int type;

    fn_8007BA88(&cursor, 0);
    fn_8007BBFC(&cursor, _Gear_sPlayerGear.mValues[0], 0);
    fn_8007BC34(&cursor, &row);
    type = PlayerLookMapHatKind(row.mUnknown64);
    fn_8007BB04(&cursor);
    if (pFlag) {
        *pFlag = row.mUnknown76;
    }
    if (pSkullcap) {
        if (fn_801C302C(row.mName, "SKULLCAP_BLACK_L", 16) == 0 || fn_801C302C(row.mName, "SKULLCAP_WHITE_L", 16) == 0) {
            *pSkullcap = 1;
        } else {
            *pSkullcap = 0;
        }
    }
    return type;
}

static int _GearShirtAllowsFrontDecal()
{
    DbCursor cursor;
    Row_8007BC34 row;

    fn_8007BA88(&cursor, 9);
    fn_8007BBFC(&cursor, _Gear_sPlayerGear.mValues[10], 0);
    fn_8007BC34(&cursor, &row);
    fn_8007BB04(&cursor);
    return row.mUnknown71 && !row.mUnknown76;
}

static int _GearShirtAllowsBackDecal()
{
    DbCursor cursor;
    Row_8007BC34 row;

    fn_8007BA88(&cursor, 9);
    fn_8007BBFC(&cursor, _Gear_sPlayerGear.mValues[10], 0);
    fn_8007BC34(&cursor, &row);
    fn_8007BB04(&cursor);
    return row.mUnknown70 && !row.mUnknown76;
}

static int _GearShirtAllowsShoulderPads()
{
    DbCursor cursor;
    Row_8007BC34 row;

    fn_8007BA88(&cursor, 9);
    fn_8007BBFC(&cursor, _Gear_sPlayerGear.mValues[10], 0);
    fn_8007BC34(&cursor, &row);
    fn_8007BB04(&cursor);
    return PlayerLookItemKeepsLogo(row.mUnknown64);
}

static int _GearHatAllowsDecal()
{
    unsigned char flag = 0;
    unsigned char skullcap = 0;
    int allowed;

    switch (_GearGetHatKind(&flag, &skullcap)) {
    case 1:
    case 4:
    case 5:
    case 7:
    case 12:
    case 13:
    case 14:
        allowed = 1;
        break;
    default:
        allowed = 0;
        break;
    }
    return allowed && !flag && !skullcap;
}

static int _GearHatStyleCount()
{
    int count = 0;

    switch (_GearGetHatKind(0, 0)) {
    case 1:
        count = 3;
        break;
    case 7:
        count = 5;
        break;
    }
    return count;
}

static int _GearHatStyleAt(int index)
{
    int value = 0;

    switch (_GearGetHatKind(0, 0)) {
    case 1:
        value = _Gear_aHatStylesKind1[index];
        break;
    case 7:
        value = _Gear_aHatStylesKind7[index];
        break;
    }
    return value;
}

static int _GearValidateHatStyle(int value)
{
    int result = 0;
    unsigned int i;

    switch (_GearGetHatKind(0, 0)) {
    case 1:
        for (i = 0; i < 3; i++) {
            if (_Gear_aHatStylesKind1[i] == value) {
                break;
            }
        }
        if (i < 3) {
            result = value;
        }
        break;
    case 7:
        for (i = 0; i < 5; i++) {
            if (_Gear_aHatStylesKind7[i] == value) {
                break;
            }
        }
        if (i < 5) {
            result = value;
        }
        break;
    }
    return result;
}

static unsigned int _GearFindHatStyle(int value)
{
    unsigned int i = 0;

    switch (_GearGetHatKind(0, 0)) {
    case 1:
        for (i = 0; i < 3; i++) {
            if (_Gear_aHatStylesKind1[i] == value) {
                break;
            }
        }
        break;
    case 7:
        for (i = 0; i < 5; i++) {
            if (_Gear_aHatStylesKind7[i] == value) {
                break;
            }
        }
        break;
    }
    return i;
}

void GearAreaMenu::Enter(int a, int *pCount, int *pOut)
{
    MenuListScreen::Enter(a, pCount, pOut);
    fn_80183740(0);
    if (!_Gear_bFromCreatePlayer) {
        FEPlyrSetPlayer(FEPlyrGetBackIndex(), _Gear_iPlayerId, 1);
        FEPlyrLoadSetScaleRamp(0);
    }
}

int GearAreaMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        switch (a) {
        case 0:
            result = 1;
            fn_80183740(&_Gear_aAreaLayouts[1]);
            *pOut = _GearGetHeadMenu();
            break;
        case 2:
            result = 1;
            fn_80183740(&_Gear_aAreaLayouts[2]);
            *pOut = _GearGetTorsoMenu();
            break;
        case 1:
            result = 1;
            fn_80183740(&_Gear_aAreaLayouts[3]);
            *pOut = _GearGetArmsMenu();
            break;
        case 3:
            result = 1;
            fn_80183740(&_Gear_aAreaLayouts[4]);
            *pOut = _GearGetLegsMenu();
            break;
        }
    }
    if (!_Gear_bFromCreatePlayer) {
        FEPlyrLoadSetScaleRamp(1);
    }
    return result;
}

void GearAreaMenu::Highlight(int id)
{
    fn_80182DD4("Gear");
}

void GearAreaMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    switch (id) {
    case 0:
        pOut->mUnknown40 = _GearGetHeadMenu()->HasNewItems();
        break;
    case 2:
        pOut->mUnknown40 = _GearGetTorsoMenu()->HasNewItems();
        break;
    case 1:
        pOut->mUnknown40 = _GearGetArmsMenu()->HasNewItems();
        break;
    case 3:
        pOut->mUnknown40 = _GearGetLegsMenu()->HasNewItems();
        break;
    }
}

void GearPlayerList::Enter(int a, int *pCount, int *pOut)
{
    char buffer[18];

    fn_80083F88(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
    fn_80182DD4("");
    fn_80182E04("");
    *pCount = DbCursorGetRowCount((DbCursor *)fn_80182DC8()) + 1;
    DbCursorFirst((DbCursor *)fn_80182DC8());
    _Gear_iPlayerId = PlayerDbGetId(fn_80182DC8());
    FEPlyrSetPlayer(FEPlyrGetFrontIndex(), _Gear_iPlayerId, 1);
}

int GearPlayerList::Leave(int a, int b, void **pOut)
{
    char buffer[27];

    *pOut = _GearGetAreaMenu();
    PlayerDbSeekId(fn_80182DC8(), a, 0);
    fn_801832B0(buffer, 27);
    fn_80182E34(buffer);
    fn_800817CC(fn_80182DC8(), &_Gear_sPlayerGear);
    return 1;
}

void GearPlayerList::Highlight(int index)
{
    if (index != 0x7FFF) {
        char buffer[27];

        PlayerDbSeekId(fn_80182DC8(), index, 0);
        _Gear_iPlayerId = index;
        FEPlyrSetPlayer(FEPlyrGetFrontIndex(), index, 0);
        fn_801832B0(buffer, 27);
        fn_80182DD4(buffer);
        fn_80182ED0();
    } else {
        fn_80182DD4("Save And Exit");
    }
}

void GearPlayerList::GetItemId(int index, int *pOut)
{
    if (index >= DbCursorGetRowCount((DbCursor *)fn_80182DC8())) {
        *pOut = 0x7FFF;
    } else {
        DbCursorSeek((DbCursor *)fn_80182DC8(), index);
        *pOut = PlayerDbGetId(fn_80182DC8());
    }
}

void GearPlayerList::GetItem(int index, MenuEntry_t *pOut)
{
    char buffer[27] = { 0 };

    pOut->mUnknown40 = 0;
    if (index != 0x7FFF) {
        int value;

        PlayerDbSeekId(fn_80182DC8(), index, 0);
        value = PlayerDbGetPortraitId(fn_80182DC8());
        pOut->mUnknown36 = DbCursorGetRow((DbCursor *)fn_80182DC8());
        pOut->mId = index;
        pOut->mUnknown30 = 1;
        pOut->mUnknown4 = 0;
        pOut->mUnknown32 = value | 0xA0000;
        fn_801832B0(buffer, 27);
        fn_801C3284(pOut->mName, buffer, 22);
    } else {
        pOut->mUnknown36 = DbCursorGetRowCount((DbCursor *)fn_80182DC8());
        pOut->mId = index;
        pOut->mUnknown30 = 1;
        pOut->mUnknown4 = 4;
        pOut->mUnknown32 = 0xC0034;
        fn_801C3284(pOut->mName, "Undo Changes", 22);
    }
}

int GearHeadMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        int type = _Gear_aHeadCategories[a];

        if (type != 14) {
            GearItemList *pItems = _GearGetItemList();

            result = 1;
            pItems->mUnknown8 = type;
            pItems->mUnknown12 = 0;
            *pOut = _GearGetItemList();
        } else {
            switch (a) {
            case 1:
            case 2:
                _GearGetHeadwearOptionList()->mUnknown8 = a;
                result = 1;
                *pOut = _GearGetHeadwearOptionList();
                break;
            }
        }
    }
    return result;
}

void GearHeadMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    if (id == 2) {
        pOut->mUnknown40 = AnyDecalFlagged();
    } else {
        pOut->mUnknown40 = _GearCategoryAnyNew(_Gear_aHeadCategories[id]);
    }
    switch (id) {
    case 1:
        pOut->mUnknown30 = _GearHatStyleCount() != 0;
        break;
    case 2:
        pOut->mUnknown30 = _GearHatAllowsDecal();
        break;
    default:
        pOut->mUnknown30 = _Gear_aHeadEntries[id].mUnknown30;
        break;
    }
}

int GearHeadMenu::HasNewItems()
{
    int result = 0;
    int i;

    for (i = 0; i <= 3; i++) {
        if (_GearCategoryAnyNew(_Gear_aHeadCategories[i])) {
            result = 1;
            break;
        }
    }
    if (!result) {
        result = AnyDecalFlagged();
    }
    return result;
}

int GearJewelryMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        int value = _Gear_aJewelryCategories[a];
        GearItemList *pItems = _GearGetItemList();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = b;
        *pOut = _GearGetItemList();
    }
    return result;
}

void GearJewelryMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = _GearCategoryAnyNew(_Gear_aJewelryCategories[id]);
    if (_Gear_aJewelryEntries[id].mId == 1) {
        pOut->mUnknown30 = _Gear_sPlayerGear.mValues[12] != 0;
    }
}

int GearJewelryMenu::HasNewItems()
{
    int result = 0;
    int i;

    for (i = 0; i < 2; i++) {
        if (_GearCategoryAnyNew(_Gear_aJewelryCategories[i])) {
            result = 1;
            break;
        }
    }
    return result;
}

int GearTorsoMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        int value = _Gear_aTorsoCategories[a];

        if (value != 14) {
            GearItemList *pItems = _GearGetItemList();

            result = 1;
            pItems->mUnknown8 = value;
            pItems->mUnknown12 = b;
            *pOut = _GearGetItemList();
        } else {
            switch (a) {
            case 0:
                *pOut = _GearGetShirtMenu();
                result = 1;
                break;
            case 1:
            case 2:
                _GearGetShirtDecalList()->mUnknown8 = a;
                result = 1;
                *pOut = _GearGetShirtDecalList();
                break;
            case 4:
                *pOut = _GearGetJewelryMenu();
                result = 1;
                break;
            }
        }
    }
    return result;
}

void GearTorsoMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    switch (id) {
    case 0:
        pOut->mUnknown40 = _GearGetShirtMenu()->HasNewItems();
        break;
    case 4:
        pOut->mUnknown40 = _GearGetJewelryMenu()->HasNewItems();
        break;
    case 1:
    case 2:
        pOut->mUnknown40 = AnyDecalFlagged();
        break;
    default:
        pOut->mUnknown40 = _GearCategoryAnyNew(_Gear_aTorsoCategories[id]);
        break;
    }
    switch (id) {
    case 2:
        pOut->mUnknown30 = _GearShirtAllowsBackDecal();
        break;
    case 1:
        pOut->mUnknown30 = _GearShirtAllowsFrontDecal();
        break;
    case 3:
        pOut->mUnknown30 = _GearShirtAllowsShoulderPads();
        break;
    default:
        pOut->mUnknown30 = _Gear_aTorsoEntries[id].mUnknown30;
        break;
    }
}

int GearTorsoMenu::HasNewItems()
{
    int result = 0;
    int i;

    for (i = 0; i < 5; i++) {
        if (_GearCategoryAnyNew(_Gear_aTorsoCategories[i])) {
            result = 1;
            break;
        }
    }
    if (!result) {
        result = _GearGetShirtMenu()->HasNewItems();
        if (!result) {
            result = _GearGetJewelryMenu()->HasNewItems();
            if (!result) {
                result = AnyDecalFlagged();
            }
        }
    }
    return result;
}

int GearShirtMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        int value = _Gear_aShirtCategories[a];
        GearItemList *pItems = _GearGetItemList();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = a;
        *pOut = _GearGetItemList();
    }
    return result;
}

void GearShirtMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = _GearCategoryHasNew(_Gear_aShirtCategories[id], id);
}

int GearShirtMenu::HasNewItems()
{
    int result = 0;

    if (_GearCategoryAnyNew(10)) {
        result = 1;
    }
    return result;
}

int GearArmsMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        int value = _Gear_aArmsCategories[a];
        GearItemList *pItems = _GearGetItemList();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = b;
        *pOut = _GearGetItemList();
    }
    return result;
}

void GearArmsMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = _GearCategoryAnyNew(_Gear_aArmsCategories[id]);
}

int GearArmsMenu::HasNewItems()
{
    int result = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (_GearCategoryAnyNew(_Gear_aArmsCategories[i])) {
            result = 1;
            break;
        }
    }
    return result;
}

int GearLegsMenu::Leave(int a, int b, void **pOut)
{
    int result = MenuListScreen::Leave(a, b, pOut);

    if (b == 0) {
        int value = _Gear_aLegsCategories[a];
        GearItemList *pItems = _GearGetItemList();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = b;
        *pOut = _GearGetItemList();
    }
    return result;
}

void GearLegsMenu::GetItem(int id, MenuEntry_t *pOut)
{
    MenuListScreen::GetItem(id, pOut);
    pOut->mUnknown40 = _GearCategoryAnyNew(_Gear_aLegsCategories[id]);
}

int GearLegsMenu::HasNewItems()
{
    int result = 0;
    int i;

    for (i = 0; i < 3; i++) {
        if (_GearCategoryAnyNew(_Gear_aLegsCategories[i])) {
            result = 1;
            break;
        }
    }
    return result;
}

void GearItemList::Enter(int a, int *pCount, int *pOut)
{
    int type;
    int id;

    _Gear_iCategory = mUnknown8;
    _Gear_iItemSet = mUnknown12;
    type = fn_8007BF14(_Gear_iCategory);
    *pCount = _GearBuildItemList();
    if (type == 6) {
        id = _Gear_sPlayerGear.mValues[6];
        if (id == 0) {
            id = _Gear_sPlayerGear.mValues[7];
        }
    } else {
        int index = _Gear_iCategory;

        id = _Gear_sPlayerGear.mValues[index];
    }
    *pOut = _GearFindItemIndex(id);
    if (_GearTypeHasSides(type)) {
        *pCount = (*pCount - 1) * 3 + 1;
        if (*pOut != 0) {
            *pOut = (*pOut - 1) * 3 + 1;
            *pOut += _GearGetSide(type);
        }
    }
}

int GearItemList::Leave(int a, int b, void **pOut)
{
    int result = -1;

    if (b == 0) {
        Row_8007BC34 row;
        int index = a;
        int type = fn_8007BF14(_Gear_iCategory);

        if (_GearTypeHasSides(type) && index != 0) {
            index = (index - 1) / 3 + 1;
        }
        DbCursorSeek(&_Gear_sItemCursor, _Gear_aItems[index].mId);
        fn_8007BC34(&_Gear_sItemCursor, &row);
        if (row.mUnknown76) {
            _GearGetDecalTeamList()->mUnknown8 = type;
            result = 1;
            _GearGetDecalTeamList()->mUnknown12 = _Gear_aItems[index].mUnknown0;
            *pOut = _GearGetDecalTeamList();
        } else {
            if (_Gear_aItems[index].mUnknown12) {
                GearLockClearNew(&_Gear_sLockCursor, _Gear_aItems[index].mUnknown0);
            }
            if (_Gear_aItems[index].mOwner != -1 && _Gear_aItems[index].mOwner != _Gear_iPlayerId) {
                _GearTakeFromOwner(_Gear_aItems[index].mOwner, index);
            }
            if (_Gear_iCategory == 0) {
                _Gear_sPlayerGear.mUnknown02 = _GearValidateHatStyle(_Gear_sPlayerGear.mUnknown02);
            }
            fn_8008199C(fn_80182DC8(), &_Gear_sPlayerGear);
        }
    } else {
        fn_800817CC(fn_80182DC8(), &_Gear_sPlayerGear);
        if (fn_8007BF14(_Gear_iCategory) == 6) {
            FEPlyrSetPairSlot(6, _Gear_sPlayerGear.mValues[6]);
            FEPlyrSetPairSlot(7, _Gear_sPlayerGear.mValues[7]);
        } else {
            FEPlyrSetPairSlot(_Gear_iCategory, _Gear_sPlayerGear.mValues[_Gear_iCategory]);
        }
        if (_Gear_iCategory == 0) {
            PlayerLookSetHatStyle(0, _Gear_sPlayerGear.mUnknown02);
            PlayerLookSetHatStyle(1, _Gear_sPlayerGear.mUnknown02);
        }
        PlayerLookSetSwitchFlagsA(0, _Gear_sPlayerGear.mUnknown00);
        PlayerLookSetSwitchFlagsA(1, _Gear_sPlayerGear.mUnknown00);
        PlayerLookSetSwitchFlagsB(0, _Gear_sPlayerGear.mUnknown01);
        PlayerLookSetSwitchFlagsB(1, _Gear_sPlayerGear.mUnknown01);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    }
    fn_801831A4();
    fn_8018300C();
    fn_801831E8(0);
    fn_80182ED0();
    _GearCloseItemList();
    FEPlyrSetPose(0, 2);
    FEPlyrSetPose(1, 2);
    return result;
}

void GearItemList::Highlight(int index)
{
    int side = -1;
    int item;
    int type;

    FEPlyrSetPose(0, _Gear_aCategoryPoses[_Gear_iCategory]);
    FEPlyrSetPose(1, _Gear_aCategoryPoses[_Gear_iCategory]);
    item = index;
    type = fn_8007BF14(_Gear_iCategory);
    if (_GearTypeHasSides(type) && item != 0) {
        side = (item - 1) % 3;
        item = (item - 1) / 3 + 1;
    }
    DbCursorSeek(&_Gear_sItemCursor, _Gear_aItems[item].mId);
    _Gear_sPlayerGear.mValues[_Gear_iCategory] = _Gear_aItems[item].mId;
    _GearShowOwner();
    _GearMarkAffectedRatings();
    if (_GearTypeHasSides(type)) {
        _GearSetSide(type, side, _Gear_aItems[item].mId);
    }
    if (type == 6) {
        FEPlyrSetPairSlot(6, _Gear_sPlayerGear.mValues[6]);
        FEPlyrSetPairSlot(7, _Gear_sPlayerGear.mValues[7]);
    } else {
        FEPlyrSetPairSlot(_Gear_iCategory, _Gear_sPlayerGear.mValues[_Gear_iCategory]);
    }
    if (_Gear_iCategory == 0) {
        unsigned char value = _GearValidateHatStyle(_Gear_sPlayerGear.mUnknown02);

        PlayerLookSetHatStyle(0, value);
        PlayerLookSetHatStyle(1, value);
    }
    fn_80182F24(&_Gear_sPlayerGear);
    PlayerLookSetSwitchFlagsA(0, _Gear_sPlayerGear.mUnknown00);
    PlayerLookSetSwitchFlagsA(1, _Gear_sPlayerGear.mUnknown00);
    PlayerLookSetSwitchFlagsB(0, _Gear_sPlayerGear.mUnknown01);
    PlayerLookSetSwitchFlagsB(1, _Gear_sPlayerGear.mUnknown01);
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
}

void GearItemList::GetItem(int index, MenuEntry_t *pOut)
{
    int item = index;
    int side = -1;
    char name[32];

    if (_GearTypeHasSides(fn_8007BF14(_Gear_iCategory)) && item != 0) {
        side = (item - 1) % 3;
        item = (item - 1) / 3 + 1;
    }
    DbCursorSeek(&_Gear_sItemCursor, _Gear_aItems[item].mId);
    pOut->mUnknown40 = _Gear_aItems[item].mUnknown12;
    fn_8007BE20(&_Gear_sItemCursor, name, 32);
    if (side != -1) {
        fn_801C2D88(pOut->mName, 22, "%s-%s", _Gear_aSideNames[side], name);
    } else {
        fn_801C3284(pOut->mName, name, 22);
    }
}

void GearDecalTeamList::Enter(int a, int *pCount, int *pOut)
{
    TeamQuery query;
    int selected;

    query.mUnknown4 = 3;
    query.mUnknown0 = 1;
    selected = 0;
    fn_80083E40(&_Gear_sTeamCursor, &query, 0x54415453);
    *pCount = DbCursorGetRowCount(&_Gear_sTeamCursor);
    switch (mUnknown8) {
    case 0:
        selected = _Gear_sPlayerGear.mUnknown0D;
        break;
    case 9:
        selected = _Gear_sPlayerGear.mUnknown0C;
        break;
    }
    *pOut = 0;
    for (int more = DbCursorFirst(&_Gear_sTeamCursor); more; more = DbCursorNext(&_Gear_sTeamCursor)) {
        if (fn_80084158(&_Gear_sTeamCursor) - 1 == selected) {
            *pOut = DbCursorGetRow(&_Gear_sTeamCursor);
            break;
        }
    }
}

int GearDecalTeamList::Leave(int a, int b, void **pOut)
{
    int result;
    int value;

    DbCursorSeek(&_Gear_sTeamCursor, a);
    result = -1;
    value = fn_80084158(&_Gear_sTeamCursor) - 1;
    if (b == 0) {
        switch (mUnknown8) {
        case 0:
            _Gear_sPlayerGear.mUnknown0D = value;
            break;
        case 9:
            _Gear_sPlayerGear.mUnknown0C = value;
            break;
        }
        result = -2;
        GearLockClearNew(&_Gear_sLockCursor, mUnknown12);
        fn_8008199C(fn_80182DC8(), &_Gear_sPlayerGear);
    } else {
        fn_800817CC(fn_80182DC8(), &_Gear_sPlayerGear);
        switch (mUnknown8) {
        case 0:
            PlayerLookSetHeadDecalColors(0, _Gear_sPlayerGear.mUnknown0D);
            PlayerLookSetHeadDecalColors(1, _Gear_sPlayerGear.mUnknown0D);
            break;
        case 9:
            PlayerLookSetDecalColors(0, _Gear_sPlayerGear.mUnknown0C);
            PlayerLookSetDecalColors(1, _Gear_sPlayerGear.mUnknown0C);
            break;
        }
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    }
    fn_80083F68(&_Gear_sTeamCursor);
    return result;
}

void GearDecalTeamList::Highlight(int index)
{
    int value;

    DbCursorSeek(&_Gear_sTeamCursor, index);
    value = fn_80084158(&_Gear_sTeamCursor) - 1;
    switch (mUnknown8) {
    case 0:
        PlayerLookSetHeadDecalColors(0, value);
        PlayerLookSetHeadDecalColors(1, value);
        break;
    case 9:
        PlayerLookSetDecalColors(0, value);
        PlayerLookSetDecalColors(1, value);
        break;
    }
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
}

void GearDecalTeamList::GetItem(int index, MenuEntry_t *pOut)
{
    char name[18];

    DbCursorSeek(&_Gear_sTeamCursor, index);
    fn_80083F88(&_Gear_sTeamCursor, name, 18);
    fn_801C3284(pOut->mName, name, 22);
}

static int _GearDecalOptionCount()
{
    return fn_80183948() != 5 ? 3 : 5;
}

static int _GearDecalOptionAt(int index)
{
    if (fn_80183948() == 5) {
        return _Gear_aDecalOptionsMode5[index];
    }
    return _Gear_aDecalOptions[index];
}

static int *_GearDecalOptionTable()
{
    if (fn_80183948() == 5) {
        return _Gear_aDecalOptionsMode5;
    }
    return _Gear_aDecalOptions;
}

void GearHeadwearOptionList::Enter(int a, int *pCount, int *pOut)
{
    *pCount = 0;
    *pOut = 0;
    switch (mUnknown8) {
    case 1:
        *pOut = _GearFindHatStyle(_Gear_sPlayerGear.mUnknown02);
        *pCount = _GearHatStyleCount();
        break;
    case 2: {
        unsigned char value = _Gear_sPlayerGear.mUnknown0B;

        if (value <= 5) {
            *pOut = _GearFindTableIndex(value, _GearDecalOptionTable(), _GearDecalOptionCount());
        } else {
            *pOut = DecalFindIndex(fn_80183354(), _Gear_sPlayerGear.mUnknown0B - 6) + _GearDecalOptionCount();
        }
        *pCount = _GearDecalOptionCount() + DecalCountUnlocked(fn_80183354());
        break;
    }
    }
}

int GearHeadwearOptionList::Leave(int a, int b, void **pOut)
{
    if (b == 0) {
        fn_8008199C(fn_80182DC8(), &_Gear_sPlayerGear);
        if (mUnknown8 == 2 && _Gear_sPlayerGear.mUnknown0B > 5) {
            DecalClearNew(fn_80183354(), _Gear_sPlayerGear.mUnknown0B - 6);
        }
    } else {
        fn_800817CC(fn_80182DC8(), &_Gear_sPlayerGear);
        switch (mUnknown8) {
        case 1:
            PlayerLookSetHatStyle(0, _Gear_sPlayerGear.mUnknown02);
            PlayerLookSetHatStyle(1, _Gear_sPlayerGear.mUnknown02);
            break;
        case 2:
            PlayerLookSetHeadDecalKind(0, _Gear_sPlayerGear.mUnknown0B);
            PlayerLookSetHeadDecalKind(1, _Gear_sPlayerGear.mUnknown0B);
            break;
        }
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    }
    return -1;
}

void GearHeadwearOptionList::Highlight(int index)
{
    switch (mUnknown8) {
    case 1:
        if (_GearHatStyleCount()) {
            _Gear_sPlayerGear.mUnknown02 = _GearHatStyleAt(index);
            PlayerLookSetHatStyle(0, _Gear_sPlayerGear.mUnknown02);
            PlayerLookSetHatStyle(1, _Gear_sPlayerGear.mUnknown02);
            FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
            FEPlyrRequestSwap();
        }
        break;
    case 2:
        if (index < _GearDecalOptionCount()) {
            _Gear_sPlayerGear.mUnknown0B = _GearDecalOptionAt(index);
        } else {
            _Gear_sPlayerGear.mUnknown0B = DecalGetIdAt(fn_80183354(), index - _GearDecalOptionCount()) + 6;
        }
        PlayerLookSetHeadDecalKind(0, _Gear_sPlayerGear.mUnknown0B);
        PlayerLookSetHeadDecalKind(1, _Gear_sPlayerGear.mUnknown0B);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    }
}

void GearHeadwearOptionList::GetItem(int index, MenuEntry_t *pOut)
{
    switch (mUnknown8) {
    case 1:
        if (_GearHatStyleCount()) {
            fn_801C3284(pOut->mName, _Gear_aHatStyleNames[_GearHatStyleAt(index)], 22);
        }
        break;
    case 2:
        if (index < _GearDecalOptionCount()) {
            fn_801C3284(pOut->mName, _Gear_aDecalOptionNames[_GearDecalOptionAt(index)], 22);
        } else {
            int id = DecalGetIdAt(fn_80183354(), index - _GearDecalOptionCount());

            pOut->mUnknown40 = DecalIsNew(fn_80183354(), id);
            DecalGetName(id, pOut->mName, 22);
        }
        break;
    }
}

void GearShirtDecalList::Enter(int a, int *pCount, int *pOut)
{
    *pCount = 0;
    *pOut = 0;
    switch (mUnknown8) {
    case 1: {
        unsigned char value = _Gear_sPlayerGear.mUnknown09;

        if (value <= 5) {
            *pOut = _GearFindTableIndex(value, _GearDecalOptionTable(), _GearDecalOptionCount());
        } else {
            *pOut = DecalFindIndex(fn_80183354(), _Gear_sPlayerGear.mUnknown09 - 6) + _GearDecalOptionCount();
        }
        *pCount = _GearDecalOptionCount() + DecalCountUnlocked(fn_80183354());
        break;
    }
    case 2: {
        unsigned char value = _Gear_sPlayerGear.mUnknown0A;

        if (value <= 5) {
            *pOut = _GearFindTableIndex(value, _GearDecalOptionTable(), _GearDecalOptionCount());
        } else {
            *pOut = DecalFindIndex(fn_80183354(), _Gear_sPlayerGear.mUnknown0A - 6) + _GearDecalOptionCount();
        }
        *pCount = _GearDecalOptionCount() + DecalCountUnlocked(fn_80183354());
        break;
    }
    }
}

int GearShirtDecalList::Leave(int a, int b, void **pOut)
{
    if (b == 0) {
        fn_8008199C(fn_80182DC8(), &_Gear_sPlayerGear);
        switch (mUnknown8) {
        case 1:
            if (_Gear_sPlayerGear.mUnknown09 > 5) {
                DecalClearNew(fn_80183354(), _Gear_sPlayerGear.mUnknown09 - 6);
            }
            break;
        case 2:
            if (_Gear_sPlayerGear.mUnknown0A > 5) {
                DecalClearNew(fn_80183354(), _Gear_sPlayerGear.mUnknown0A - 6);
            }
            break;
        }
    } else {
        fn_800817CC(fn_80182DC8(), &_Gear_sPlayerGear);
        switch (mUnknown8) {
        case 1:
            PlayerLookSetFrontDecalKind(0, _Gear_sPlayerGear.mUnknown09);
            PlayerLookSetFrontDecalKind(1, _Gear_sPlayerGear.mUnknown09);
            break;
        case 2:
            PlayerLookSetBackDecalKind(0, _Gear_sPlayerGear.mUnknown0A);
            PlayerLookSetBackDecalKind(1, _Gear_sPlayerGear.mUnknown0A);
            break;
        }
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    }
    return -1;
}

void GearShirtDecalList::Highlight(int index)
{
    switch (mUnknown8) {
    case 1:
        if (index < _GearDecalOptionCount()) {
            _Gear_sPlayerGear.mUnknown09 = _GearDecalOptionAt(index);
        } else {
            _Gear_sPlayerGear.mUnknown09 = DecalGetIdAt(fn_80183354(), index - _GearDecalOptionCount()) + 6;
        }
        PlayerLookSetFrontDecalKind(0, _Gear_sPlayerGear.mUnknown09);
        PlayerLookSetFrontDecalKind(1, _Gear_sPlayerGear.mUnknown09);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    case 2:
        if (index < _GearDecalOptionCount()) {
            _Gear_sPlayerGear.mUnknown0A = _GearDecalOptionAt(index);
        } else {
            _Gear_sPlayerGear.mUnknown0A = DecalGetIdAt(fn_80183354(), index - _GearDecalOptionCount()) + 6;
        }
        PlayerLookSetBackDecalKind(0, _Gear_sPlayerGear.mUnknown0A);
        PlayerLookSetBackDecalKind(1, _Gear_sPlayerGear.mUnknown0A);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    }
}

void GearShirtDecalList::GetItem(int index, MenuEntry_t *pOut)
{
    switch (mUnknown8) {
    case 1:
        if (index < _GearDecalOptionCount()) {
            fn_801C3284(pOut->mName, _Gear_aDecalOptionNames[_GearDecalOptionAt(index)], 22);
        } else {
            int id = DecalGetIdAt(fn_80183354(), index - _GearDecalOptionCount());

            pOut->mUnknown40 = DecalIsNew(fn_80183354(), id);
            DecalGetName(id, pOut->mName, 22);
        }
        break;
    case 2:
        if (index < _GearDecalOptionCount()) {
            fn_801C3284(pOut->mName, _Gear_aDecalOptionNames[_GearDecalOptionAt(index)], 22);
        } else {
            int id = DecalGetIdAt(fn_80183354(), index - _GearDecalOptionCount());

            pOut->mUnknown40 = DecalIsNew(fn_80183354(), id);
            DecalGetName(id, pOut->mName, 22);
        }
        break;
    }
}

void GearMenuOpen(int a)
{
    GearLockOpen(&_Gear_sLockCursor, fn_8022F384(fn_8022F4BC()));
    _Gear_bFromCreatePlayer = a;
    if (a == 0) {
        fn_801835C8();
    } else {
        _Gear_iPlayerId = PlayerDbGetId(fn_80182DC8());
        fn_800817CC(fn_80182DC8(), &_Gear_sPlayerGear);
    }
}

void GearMenuClose()
{
    if (_Gear_bFromCreatePlayer == 0) {
        fn_80183704();
    }
    GearLockClose(&_Gear_sLockCursor);
}

GearAreaMenu *GearMenuGetRoot()
{
    return _GearGetAreaMenu();
}

static inline GearHeadMenu *_GearGetHeadMenu()
{
    static GearHeadMenu sInstance;
    return &sInstance;
}

static inline GearTorsoMenu *_GearGetTorsoMenu()
{
    static GearTorsoMenu sInstance;
    return &sInstance;
}

static inline GearArmsMenu *_GearGetArmsMenu()
{
    static GearArmsMenu sInstance;
    return &sInstance;
}

static inline GearLegsMenu *_GearGetLegsMenu()
{
    static GearLegsMenu sInstance;
    return &sInstance;
}

static inline GearAreaMenu *_GearGetAreaMenu()
{
    static GearAreaMenu sInstance;
    return &sInstance;
}

static inline GearItemList *_GearGetItemList()
{
    static GearItemList sInstance;
    return &sInstance;
}

static inline GearHeadwearOptionList *_GearGetHeadwearOptionList()
{
    static GearHeadwearOptionList sInstance;
    return &sInstance;
}

static inline GearShirtMenu *_GearGetShirtMenu()
{
    static GearShirtMenu sInstance;
    return &sInstance;
}

static inline GearShirtDecalList *_GearGetShirtDecalList()
{
    static GearShirtDecalList sInstance;
    return &sInstance;
}

static inline GearJewelryMenu *_GearGetJewelryMenu()
{
    static GearJewelryMenu sInstance;
    return &sInstance;
}

static inline GearDecalTeamList *_GearGetDecalTeamList()
{
    static GearDecalTeamList sInstance;
    return &sInstance;
}

static inline GearPlayerList *_GearGetPlayerList()
{
    static GearPlayerList sInstance;
    return &sInstance;
}
