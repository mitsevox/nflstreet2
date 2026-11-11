/* Create-a-player menu: the list of the team's players and, for the chosen
   player, the Attributes, Info, Appearance and Gear menus. Ratings, height
   and weight are bought with development points on sliders; info, hair,
   face and skin choices are previewed on the player model as they are
   highlighted. */

#include "game/FaceFeatures.h"
#include "game/AppearanceNameTable.h"
#include "game/FchrCursor.h"
#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/PlayerLook.h"
#include "game/FEPlyrLoad.h"
#include "game/cu_80181330.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

/* Range of one face feature: its values start at mOffset in the
   _CreatePlayer_sFace slot mSlot, and the menu shows mCount of them. */
struct FaceFeatureRange_t {
    int mOffset;
    int mCount;
    int mSlot;
};

/* Per-row record of the table at 0x80369E64: a key (mKey, -1 when the
   slot is free) and twelve values indexed by attribute (-1 when unset). */
struct CreatePlayerOriginal_t {
    int mKey;
    int mValues[12];
};

void *operator new(unsigned int size, int unknown);

extern "C" {
void FEPlyrSetPose(int index, unsigned int value);
void FEPlyrSetPlayer(int index, int a, int b);
void FEPlyrSetHeight(int index, unsigned int value);
void FEPlyrRequestSwap(void);
int FEPlyrGetBackIndex(void);
int FEPlyrGetFrontIndex(void);
void FEPlyrPlayPairAnim(void);
void FaceTableOpen();
void FaceTableClose();
void PoseTableOpen(DbCursor *pObject);
void PoseTableClose(DbCursor *pObject);
void PoseTableSeek(DbCursor *pCursor, int value, int *pResult);
void PoseTableGetName(DbCursor *pCursor, char *pBuffer, int size);
int PoseTableGetNumber(DbCursor *pCursor);
void TattooTableOpen(DbCursor *pCursor, int type);
void TattooTableClose(DbCursor *pCursor);
void TattooTableGetName(DbCursor *pCursor, char *pBuffer, int size);
int TattooTableGetId(DbCursor *pCursor);
void PlayerLookSetName(int index, const char *pName);
void DbColPalGetPaletteName(int index, char *pBuffer, int size);
int DbCursorGetRow(DbCursor *pObject);
void HairListOpen(DbCursor *pObject);
void HairListClose(DbCursor *pObject);
void HairListGetName(DbCursor *pObject, char *pBuffer, int size);
int HairListGetId(DbCursor *pObject);
int PlayerDbGetId(Object_8008044C *pObject);
int PlayerDbGetOriginalId(Object_8008044C *pObject);
void PlayerDbGetFirstName(Object_8008044C *pObject, char *pBuffer, int size);
void PlayerDbGetNickname(Object_8008044C *pObject, char *pBuffer, int size);
int PlayerDbHasPlil(Object_8008044C *pObject);
int PlayerDbGetPortraitId(Object_8008044C *pObject);
int PlayerDbGetPlex(Object_8008044C *pObject);
int PlayerDbGetPlht(Object_8008044C *pObject);
int PlayerDbGetHairStyle(Object_8008044C *pObject);
void PlayerDbSetPbpo(Object_8008044C *pObject, int value);
int PlayerDbGetPpsn(void *pObject);
int PlayerDbGetSgt(void *pObject, int index);
void PlayerDbSetPpsn(void *pObject, int value);
void PlayerDbSetSgt(void *pObject, int index, int value);
void PlayerDbSetHairStyle(Object_8008044C *pObject, int value);
void PlayerDbSetPybt(Object_8008044C *pObject, int value);
void PlayerDbSetSkinTone(Object_8008044C *pObject, int value);
void PlayerDbSetPlex(Object_8008044C *pObject, int value);
void PlayerDbSetHairColor(Object_8008044C *pObject, int value);
int PlayerDbGetHairColor(Object_8008044C *pObject);
void PlayerDbSetFacialHairColor(Object_8008044C *pObject, int value);
int PlayerDbGetFacialHairColor(Object_8008044C *pObject);
void PlayerDbSetWeight(Object_8008044C *pObject, int value);
int PlayerDbGetWeight(Object_8008044C *pObject);
void PlayerDbSetHeight(Object_8008044C *pObject, int value);
int PlayerDbGetPhan(Object_8008044C *pObject);
void PlayerDbSetPhan(Object_8008044C *pObject, int value);
int PlayerDbGetPjen(Object_8008044C *pObject);
void PlayerDbSetPjen(Object_8008044C *pObject, int value);
int PlayerDbGetRating(Object_8008044C *pObject, int index);
void PlayerDbSetRating(Object_8008044C *pObject, int index, int value);
void fn_8008199C(Object_8008044C *pObject, PlayerGear_t *pInfo);
int fn_80081E3C(Object_8008044C *pObject);
void fn_80081E64(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80081E98(Object_8008044C *pObject, char *pBuffer, int size);
int fn_80082280(Object_8008044C *pObject);
void fn_800822A8(Object_8008044C *pObject, int value);
int fn_800822D4(Object_8008044C *pObject);
void fn_80082308(Object_8008044C *pObject, int value);
int fn_80087938(int table, DbCursor *pObject, int index, int *pResult);
int fn_800879E8(int table, DbCursor *pObject);
void fn_80087A30(int table, DbCursor *pObject);
int fn_80087A78(int table, DbCursor *pObject, int value, int *pIndex);
int fn_80087B00(int table, DbCursor *pObject);
int fn_80087B5C(int type);
void FEPlyrLoadInvalidate(int index);
void fn_8015F638(int a, int b, int c, int *pResult);
int PlaTexCacheGetCapFaceId(int a);
void PlaTexCacheGetHairTexture(int a, int *pId, int *pPalette);
void FEMiscSetHelpText(const char *pText);
DbCursor *fn_80182DBC(void);
Object_8008044C *fn_80182DC8(void);
void fn_80182DD4(const char *pText);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_80182E64(int a);
void fn_80182E70(int a);
void fn_80182E7C(int a);
void fn_80182ED0(void);
void fn_80182EFC(void);
void fn_80182F60(int index, int delta);
void fn_80182FD4(int a, unsigned char value);
void fn_8018300C(void);
void fn_801831F0(unsigned char a);
int fn_80183220(void);
int fn_80183228(void);
int fn_80183230(void);
int fn_80183238(int index);
void fn_801832B0(char *pText, int size);
void fn_801835C0(int a);
void fn_801835C8(void);
void fn_80183704(void);
int fn_80183948(void);
int fn_80183950(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);

int CreatePlayerGetPoints(void);
}

class GearAreaMenu;

void GearMenuOpen(int a);
void GearMenuClose();
GearAreaMenu *GearMenuGetRoot();

extern const MenuEntry_t _CreatePlayer_aMenuEntries[];
extern const MenuEntry_t _CreatePlayer_aInfoEntries[];
extern const MenuEntry_t _CreatePlayer_aAppearanceEntries[];
extern const MenuEntry_t _CreatePlayer_aHairEntries[];
extern const MenuEntry_t _CreatePlayer_aFaceEntries[];
extern const FaceFeatureRange_t _CreatePlayer_aFaceRanges[];
extern const MenuEntry_t _CreatePlayer_aSkinEntries[];
extern const int _CreatePlayer_aSkinParts[];
extern const MenuEntry_t _CreatePlayer_aAttributeEntries[];
extern const MenuEntry_t _CreatePlayer_aSignatureEntries[];

static unsigned short _CreatePlayer_aDefaultSkillCosts[21] = {
    0, 5, 5, 5, 10, 10, 15, 20, 25, 30, 35, 45, 60, 75, 100, 175, 300, 450, 650, 900, 1000,
};
static unsigned short _CreatePlayer_aHeightCosts[6] = { 15, 20, 25, 75, 150, 250 };
static unsigned short _CreatePlayer_aWeightCosts[11] = { 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5 };

/* Top level of the create-a-player menu. */
const MenuEntry_t _CreatePlayer_aMenuEntries[] = {
    { 0, 0, "Attributes", 1, 2 },
    { 1, 0, "Info", 1 },
    { 2, 0, "Appearance", 1 },
    { 3, 0, "Gear", 1, 14 },
};

const MenuEntry_t _CreatePlayer_aInfoEntries[] = {
    { 0, 5, "First Name", 1, 12 },
    { 1, 5, "Last Name", 1, 24 },
    { 2, 0, "Position", 1, 29 },
    { 3, 0, "Jersey Number", 1, 23 },
    { 4, 0, "Handedness", 1 },
    { 5, 0, "Celebration", 1, 28 },
    { 6, 0, "Signature Style", 1, 37 },
};

const MenuEntry_t _CreatePlayer_aAppearanceEntries[] = {
    { 0, 0, "Hair", 1 },
    { 1, 0, "Face", 1 },
    { 2, 0, "Skin", 1 },
};

const MenuEntry_t _CreatePlayer_aHairEntries[] = {
    { 0, 0, "Hair Style", 1 },
    { 1, 0, "Hair Color", 1 },
    { 2, 0, "Facial Hair Style", 1 },
    { 3, 0, "Facial Hair Color", 1 },
    { 4, 0, "Eyebrows", 1 },
};

const MenuEntry_t _CreatePlayer_aFaceEntries[] = {
    { 0, 0, "Head Shape", 1 },
    { 1, 0, "Brow", 1 },
    { 2, 0, "Eyes", 1 },
    { 3, 0, "Ears", 1 },
    { 4, 0, "Nose", 1 },
    { 5, 0, "Lips", 1 },
    { 6, 0, "Mouth", 1 },
    { 7, 0, "Jaw & Chin", 1 },
    { 8, 0, "Expression", 1 },
};

const FaceFeatureRange_t _CreatePlayer_aFaceRanges[] = {
    { 0, 7, 3 },
    { 0, 8, 1 },
    { 48, 24, 7 },
    { 8, 6, 2 },
    { 72, 33, 8 },
    { 30, 4, 5 },
    { 21, 9, 4 },
    { 34, 14, 6 },
    { -1, -1, -1 },
};

const MenuEntry_t _CreatePlayer_aSkinEntries[] = {
    { 0, 0, "Skin Tone", 1 },
    { 1, 0, "Back Tattoo", 1 },
    { 2, 0, "Left Arm Tattoo", 1 },
    { 3, 0, "Right Arm Tattoo", 1 },
};

/* Part of each CreatePlayerSkinOptionList entry: 3 selects the skin tone; 0-2 are the
   TattooTableOpen tattoo types (right arm, left arm, back). */
const int _CreatePlayer_aSkinParts[] = { 3, 2, 1, 0 };

const MenuEntry_t _CreatePlayer_aAttributeEntries[] = {
    { 0, 2, "Passing", 1, 27 },
    { 1, 2, "Speed", 1, 44 },
    { 2, 2, "Blocking", 1, 4 },
    { 3, 2, "O-Moves", 1, 1 },
    { 4, 2, "Catching", 1, 7 },
    { 5, 2, "Run Power", 1, 32 },
    { 6, 2, "Jumping", 1, 6 },
    { 7, 2, "Tackling", 1, 45 },
    { 8, 2, "Coverage", 1, 8 },
    { 9, 2, "D-Moves", 1, 9 },
    { 10, 2, "Height", 1, 22 },
    { 11, 2, "Weight", 1, 54 },
};

/* Help line of each attribute. */
static const char *_CreatePlayer_aAttributeHelp[] = {
    "Increases throwing power and accuracy.",
    "Makes player faster.",
    "Increases ability to block effectively.",
    "Improves ability to juke, spin and use the walls.",
    "Helps player catch the ball.",
    "Improves ability to break tackles.",
    "Improves ability to make jumping catches.",
    "Makes tackling more effective.",
    "Improves ability to cover receivers.",
    "Increases ability to shed blocks effectively.",
    "Makes player taller.",
    "Makes player heavier.",
};

const MenuEntry_t _CreatePlayer_aSignatureEntries[] = {
    { 0, 0, "Style+Up", 1, 41 },
    { 1, 0, "Style+Right", 1, 40 },
    { 2, 0, "Style+Down", 1, 38 },
    { 3, 0, "Style+Left", 1, 39 },
};

static const char *_CreatePlayer_aCelebrationNames[] = { "Athlete", "Rap", "Rock" };
static int _CreatePlayer_aCelebrationStyles[] = { 2, 1, 3 };
static const char *_CreatePlayer_aHeadShapeNames[] = {
    "Lid", "Big Fathead", "Fathead", "Pill", "Big Pinhead", "Pinhead", "Meatball",
};
static const char *_CreatePlayer_aExpressionNames[] = { "Crazed", "Determined", "Growl", "Pensive", "Smirk" };
static unsigned short _CreatePlayer_aCelebrationPoses[] = { 1, 10, 13 };
static const char *_CreatePlayer_aHandNames[] = { "Right", "Left" };
static const char *_CreatePlayer_aPositionNames[] = { "QB", "RB", "WR", "OL", "DL", "LB", "DB" };
static int _CreatePlayer_aPositionCodes[7] = { 0, 1, 2, 4, 7, 9, 11 };

/* Value stored to _CreatePlayer_iSkillGroup for each result of PlayerDbGetPbpo. */
static int _CreatePlayer_aSkillGroups[] = { 0, 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6 };

/* Enabled byte of each top-level entry: _CreatePlayer_aStoryEnabled while fn_80183950 is
   nonzero and the player id is nonzero, _CreatePlayer_aExistingEnabled while it is zero and a
   player is selected. */
static const unsigned char _CreatePlayer_aExistingEnabled[] = { 0, 0, 0, 1 };
static const unsigned char _CreatePlayer_aStoryEnabled[] = { 0, 0, 0, 1 };

static const Layout_802EA9E0 _CreatePlayer_aAppearanceLayouts[] = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 1 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
};

static const Layout_802EA9E0 _CreatePlayer_aSkinLayouts[] = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 1 },
    { 0.0f, 300.0f, 0.0f, 180.0f, 1.1f, 15, 0 },
    { 0.0f, 205.0f, 0.0f, 300.0f, 0.8f, 15, 0 },
    { 0.0f, 205.0f, 0.0f, 60.0f, 0.8f, 15, 0 },
};

/* Presets applied by CreatePlayerApplyPreset: one value for each of the twelve
   attributes. */
static const short _CreatePlayer_aPresets[7][12] = {
    { 50, 25, 1, 25, 1, 15, 15, 10, 5, 1, 65, 160 },
    { 10, 35, 1, 35, 25, 25, 5, 10, 1, 1, 65, 160 },
    { 1, 50, 1, 25, 35, 1, 25, 10, 1, 1, 65, 160 },
    { 1, 15, 50, 1, 1, 25, 1, 15, 1, 10, 65, 220 },
    { 1, 15, 10, 1, 1, 25, 1, 15, 1, 50, 65, 220 },
    { 1, 25, 1, 10, 10, 15, 10, 50, 10, 15, 65, 160 },
    { 1, 35, 1, 15, 15, 1, 15, 15, 50, 1, 65, 160 },
};

static int _CreatePlayer_iPoints = 0;
static int _CreatePlayer_iPendingCost = 0;
static int _CreatePlayer_iPlayerId = 0x7FFF;
static unsigned char _CreatePlayer_bGearOpen = 0;
static unsigned char _CreatePlayer_bSliderOpen = 0;
static int _CreatePlayer_iNextCost = 0;
static unsigned char _CreatePlayer_bSkillTable = 0;
static int _CreatePlayer_iSkillGroup = 15;

/* Player list. */
class CreatePlayerList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pId);
    virtual void GetItem(int index, MenuEntry_t *pEntry);

    char mUnknown4[4];
};

/* Top-level menu of the selected player. */
class CreatePlayerMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual void Highlight(int id);
    virtual void GetItem(int index, MenuEntry_t *pEntry);
    virtual int GetEntryCount() { return 4; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aMenuEntries; }

    char mUnknown4[4];
};

class CreatePlayerInfoMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **ppResult);
    virtual MenuItemEditor *GetEditor();
    virtual int GetEntryCount() { return 7; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aInfoEntries; }

    char mUnknown4[4];
};

class CreatePlayerAppearanceMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual void Highlight(int id);
    virtual int GetEntryCount() { return 3; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aAppearanceEntries; }

    char mUnknown4[4];
};

class CreatePlayerHairMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **ppResult);
    virtual int GetEntryCount() { return 5; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aHairEntries; }

    char mUnknown4[4];
};

class CreatePlayerFaceMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **ppResult);
    virtual int GetEntryCount() { return 9; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aFaceEntries; }

    const FaceFeatureRange_t *GetRange(int feature) { return &_CreatePlayer_aFaceRanges[feature]; }

    char mUnknown4[4];
};

class CreatePlayerSkinMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual int GetEntryCount() { return 4; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aSkinEntries; }

    char mUnknown4[4];
};

class CreatePlayerAttributeMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual void Highlight(int id);
    virtual MenuItemEditor *GetEditor();
    virtual int GetEntryCount() { return 12; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aAttributeEntries; }

    char mUnknown4[4];
};

class CreatePlayerSignatureMenu : public MenuListScreen {
public:
    virtual int Leave(int a, int b, void **ppResult);
    virtual int GetEntryCount() { return 4; }
    virtual MenuEntry_t *GetEntries() { return (MenuEntry_t *)_CreatePlayer_aSignatureEntries; }

    char mUnknown4[4];
};

class CreatePlayerHairOptionList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class CreatePlayerFaceOptionList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
    AppearanceNameTable *mUnknown12;
};

class CreatePlayerSkinOptionList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class CreatePlayerInfoOptionList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class CreatePlayerNameEditor : public MenuItemEditor {
public:
    virtual void GetText(int a, int *pResult, MenuArg_t text);
    virtual void SetText(int a, MenuArg_t text);

    char mUnknown4[4];
};

class CreatePlayerAttributeSlider : public MenuItemEditor {
public:
    virtual void BeginSlider(int a, int b, int c, int *pD, int *pE, MenuArg_t textF, MenuArg_t textG,
                             MenuArg_t textH);
    virtual int MoveSlider(int a, int b, MenuArg_t text);
    virtual void EndSlider(int a, int b, int c);

    char mUnknown4[4];
};

class CreatePlayerSignatureList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pOut);
    virtual int Leave(int a, int b, void **pOut);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pOut) { *pOut = index; }
    virtual void GetItem(int index, MenuEntry_t *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

static inline CreatePlayerAttributeSlider *_CreatePlayerGetSlider();
static inline CreatePlayerSignatureList *_CreatePlayerGetSignatureList();
static inline CreatePlayerMenu *_CreatePlayerGetPlayerMenu();
static inline CreatePlayerInfoMenu *_CreatePlayerGetInfoMenu();
static inline CreatePlayerAppearanceMenu *_CreatePlayerGetAppearanceMenu();
static inline CreatePlayerAttributeMenu *_CreatePlayerGetAttributeMenu();
static inline CreatePlayerSignatureMenu *_CreatePlayerGetSignatureMenu();
static inline CreatePlayerInfoOptionList *_CreatePlayerGetInfoOptionList();
static inline CreatePlayerNameEditor *_CreatePlayerGetNameEditor();
static inline CreatePlayerHairOptionList *_CreatePlayerGetHairOptionList();
static inline CreatePlayerFaceOptionList *_CreatePlayerGetFaceOptionList();
static inline CreatePlayerSkinOptionList *_CreatePlayerGetSkinOptionList();
static inline CreatePlayerHairMenu *_CreatePlayerGetHairMenu();
static inline CreatePlayerFaceMenu *_CreatePlayerGetFaceMenu();
static inline CreatePlayerSkinMenu *_CreatePlayerGetSkinMenu();
static inline CreatePlayerList *_CreatePlayerGetPlayerList();

static void _CreatePlayerSaveOriginal(int key, int index, int value);
static void _CreatePlayerOpen();
static void _CreatePlayerClose();
static void _CreatePlayerSpendPoints(int value);
static int _CreatePlayerGetOriginal(int key, int index);

static DbCursor _CreatePlayer_sHairCursor;
static DbCursor _CreatePlayer_sPoseCursor;
static FchrCursor _CreatePlayer_sFaceCursor;
static CreatePlayerOriginal_t _CreatePlayer_aOriginals[15];
static FaceFeatures_t _CreatePlayer_sFace;
static unsigned short _CreatePlayer_aSkillCosts[21];
static int _CreatePlayer_iBodyType;

static int _CreatePlayerHasContinue()
{
    int mode = fn_80183948();

    return mode == 0 || mode == 3;
}

static void _CreatePlayerLoadSkillCosts(int position, int skill)
{
    int i;
    int loaded = 0;

    if (_CreatePlayer_bSkillTable) {
        loaded = fn_801FCE10(0,
                       "select '10VL' into \x84 and '20VL' into \x84 and '30VL' into \x84 and '40VL' into \x84 and "
                       "'50VL' into \x84 and '60VL' into \x84 and '70VL' into \x84 and '80VL' into \x84 and "
                       "'90VL' into \x84 and '01VL' into \x84 and '11VL' into \x84 and '21VL' into \x84 and "
                       "'31VL' into \x84 and '41VL' into \x84 and '51VL' into \x84 and '61VL' into \x84 and "
                       "'71VL' into \x84 and '81VL' into \x84 and '91VL' into \x84 and '02VL' into \x84 "
                       "from 'CLKS' where 'SOPB' = \x85 and 'DIKS' = \x85\n",
                       &_CreatePlayer_aSkillCosts[1], &_CreatePlayer_aSkillCosts[2], &_CreatePlayer_aSkillCosts[3], &_CreatePlayer_aSkillCosts[4],
                       &_CreatePlayer_aSkillCosts[5], &_CreatePlayer_aSkillCosts[6], &_CreatePlayer_aSkillCosts[7], &_CreatePlayer_aSkillCosts[8],
                       &_CreatePlayer_aSkillCosts[9], &_CreatePlayer_aSkillCosts[10], &_CreatePlayer_aSkillCosts[11], &_CreatePlayer_aSkillCosts[12],
                       &_CreatePlayer_aSkillCosts[13], &_CreatePlayer_aSkillCosts[14], &_CreatePlayer_aSkillCosts[15], &_CreatePlayer_aSkillCosts[16],
                       &_CreatePlayer_aSkillCosts[17], &_CreatePlayer_aSkillCosts[18], &_CreatePlayer_aSkillCosts[19], &_CreatePlayer_aSkillCosts[20],
                       position, skill) == 0;
    }
    if (!loaded) {
        for (i = 0; i < 21; i++) {
            _CreatePlayer_aSkillCosts[i] = _CreatePlayer_aDefaultSkillCosts[i];
        }
    }
}

static int _CreatePlayerPositionIndex(int value)
{
    int i;

    switch (value) {
    case 3:
        value = 2;
        break;
    case 5:
    case 6:
        value = 4;
        break;
    case 8:
        value = 7;
        break;
    case 10:
        value = 9;
        break;
    case 12:
    case 13:
        value = 11;
        break;
    }
    for (i = 0; i < 7; i++) {
        if (_CreatePlayer_aPositionCodes[i] == value) {
            break;
        }
    }
    return i;
}

static int _CreatePlayerPositionAt(int index)
{
    return _CreatePlayer_aPositionCodes[index];
}

static unsigned short _CreatePlayerSkillCostAt(int index)
{
    return _CreatePlayer_aSkillCosts[index];
}

static int _CreatePlayerRatingCost(int from, int to)
{
    int total = 0;
    int i = from / 5;
    int end = to / 5;

    while (i < end) {
        total += _CreatePlayerSkillCostAt(i + 1);
        i++;
    }
    return total;
}

static int _CreatePlayerHeightCost(int from, int to)
{
    int sign = 1;
    int total = 0;
    int i;

    if (from > to) {
        sign = from;
        from = to;
        to = sign;
        sign = -1;
    }
    for (i = from; i < to; i++) {
        int index = (i - 65) * 6 / 19;
        total += _CreatePlayer_aHeightCosts[index];
    }
    return total * sign;
}

static int _CreatePlayerWeightCost(int from, int to)
{
    int sign = 1;
    int total = 0;
    int i;

    if (from > to) {
        sign = from;
        from = to;
        to = sign;
        sign = -1;
    }
    for (i = from; i < to; i++) {
        int index = (i - 160) / 20;
        total += _CreatePlayer_aWeightCosts[index];
    }
    return total * sign;
}

static unsigned int _CreatePlayerFindValue(int value, int *pTable, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (pTable[i] == value) {
            break;
        }
    }
    return i;
}

static void _CreatePlayerQueuePortrait(int id)
{
    Object_8008044C object;
    FaceFeatures_t block;
    FMCAPPORTValues values;
    FMCAPPORTText text60;
    FMCAPPORTText text20;
    int ids[2];
    int unknown52;
    int unknown56;
    int entryId;
    int value6E;
    int value6C;
    int value72;
    int value73;
    int value74;
    int value76;
    int unknown8;
    int unknown12;
    unsigned int color18;
    unsigned int color19;

    fn_8008044C(&object, 0, 0x54415453);
    PlayerDbSeekId(&object, id, 0);
    entryId = PlayerDbGetPortraitId(&object);
    value6E = PlayerDbGetHairStyle(&object);
    value6C = PlayerDbGetPlht(&object);
    value72 = fn_80081E3C(&object);
    value73 = fn_80082280(&object);
    value74 = fn_800822D4(&object);
    value76 = PlayerDbGetPlex(&object);
    color18 = PlayerDbGetHairColor(&object);
    color19 = PlayerDbGetFacialHairColor(&object);
    fn_80082138(&object, &block);
    FaceMorphBuildWeights(&block, &values);
    fn_8015F638(value6E, value6C, 0, ids);
    PlaTexCacheGetHairTexture(value6E, &unknown52, &unknown56);
    unknown8 = PlaTexCacheGetCapFaceId(value72 + 1);
    unknown12 = value73 * 3 + value74 + 0x33BA;
    fn_801C1F94(&text60, 0, sizeof(text60));
    fn_801C1F94(&text20, 0, sizeof(text20));
    text60.mChars[18] = color18 + 0x80;
    text20.mChars[19] = color19 + 0x80;
    gFMCAPPORT.SetEntry(entryId, 0xFFFF, unknown8, unknown12, 0xA7, &text20, ids[0], unknown52, unknown56, &text60,
                        &values, value76);
    fn_8008056C(&object);
}

static void _CreatePlayerSetFaceFeature(int index, int value)
{
    int flag;

    _CreatePlayer_sFace.mUnknown0[index] = value;
    if (index == 3) {
        PlayerLookSetHeadType(0, _CreatePlayer_sFace.mUnknown0[index]);
        PlayerLookSetHeadType(1, _CreatePlayer_sFace.mUnknown0[index]);
    }
    FaceMorphBuildWeights(&_CreatePlayer_sFace, &fn_8003DEC4(0)->mUnknown4976);
    FaceMorphBuildWeights(&_CreatePlayer_sFace, &fn_8003DEC4(1)->mUnknown4976);
    PlayerLookSetFeatures(0, &_CreatePlayer_sFace);
    PlayerLookSetFeatures(1, &_CreatePlayer_sFace);
    flag = FaceMorphIsAllowed(&_CreatePlayer_sFace);
    PlayerLookSetFaceFlag(0, flag);
    PlayerLookSetFaceFlag(1, flag);
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
}

static void _CreatePlayerSetFace(int value)
{
    int flag;

    PlayerLookSetFace(0, value);
    PlayerLookSetFace(1, value);
    _CreatePlayer_sFaceCursor.FindFchrRow(value, 0);
    _CreatePlayer_sFace.mUnknown0[0] = _CreatePlayer_sFaceCursor.GetFchrFhstCode();
    FaceMorphBuildWeights(&_CreatePlayer_sFace, &fn_8003DEC4(0)->mUnknown4976);
    FaceMorphBuildWeights(&_CreatePlayer_sFace, &fn_8003DEC4(1)->mUnknown4976);
    PlayerLookSetFeatures(0, &_CreatePlayer_sFace);
    PlayerLookSetFeatures(1, &_CreatePlayer_sFace);
    flag = FaceMorphIsAllowed(&_CreatePlayer_sFace);
    PlayerLookSetFaceFlag(0, flag);
    PlayerLookSetFaceFlag(1, flag);
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
}

static int _CreatePlayerUpdateBodyType(unsigned int value)
{
    int mode = 2;

    if (value > 294) {
        mode = 0;
    } else if (value > 229) {
        mode = 1;
    } else if (value > 199) {
        mode = 3;
    }
    if (_CreatePlayer_iBodyType != mode) {
        _CreatePlayer_iBodyType = mode;
        _CreatePlayer_sFace.mUnknown0[9] = mode;
        PlayerLookSetBodyType(1, mode);
        PlayerLookSetBodyType(0, mode);
        FaceMorphBuildWeights(&_CreatePlayer_sFace, &fn_8003DEC4(0)->mUnknown4976);
        FaceMorphBuildWeights(&_CreatePlayer_sFace, &fn_8003DEC4(1)->mUnknown4976);
        PlayerLookSetFeatures(0, &_CreatePlayer_sFace);
        PlayerLookSetFeatures(1, &_CreatePlayer_sFace);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    }
    return mode;
}

static void _CreatePlayerSetHair(int value)
{
    PlayerLookSetHair(0, value);
    PlayerLookSetHair(1, value);
    FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
    FEPlyrRequestSwap();
}

static unsigned char _CreatePlayerGetTattoo(PlayerGear_t *pInfo, int part)
{
    switch (part) {
    case 1:
        return pInfo->mUnknown05;
    case 0:
        return pInfo->mUnknown04;
    case 2:
        return pInfo->mUnknown08;
    }
    return pInfo->mUnknown05;
}

static void _CreatePlayerSetTattoo(PlayerGear_t *pInfo, int part, unsigned char value)
{
    switch (part) {
    case 1:
        pInfo->mUnknown05 = value;
        break;
    case 0:
        pInfo->mUnknown04 = value;
        break;
    case 2:
        pInfo->mUnknown08 = value;
        break;
    }
}

void CreatePlayerAttributeMenu::Enter(int a, int *pCount, int *pValue)
{
    MenuListScreen::Enter(a, pCount, pValue);
    fn_801831F0(1);
}

int CreatePlayerAttributeMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    fn_801831F0(0);
    FEMiscSetHelpText("");
    return result;
}

void CreatePlayerAttributeMenu::Highlight(int id)
{
    MenuListScreen::Highlight(id);
    FEMiscSetHelpText(_CreatePlayer_aAttributeHelp[id]);
    if (id >= 0 && id <= 9) {
        _CreatePlayerLoadSkillCosts(_CreatePlayer_iSkillGroup, id);
    }
}

MenuItemEditor *CreatePlayerAttributeMenu::GetEditor()
{
    return _CreatePlayerGetSlider();
}

int CreatePlayerSignatureMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
            _CreatePlayerGetSignatureList()->mUnknown8 = a;
            result = 1;
            *ppResult = _CreatePlayerGetSignatureList();
            break;
        }
    }
    return result;
}

void CreatePlayerList::Enter(int a, int *pCount, int *pValue)
{
    char buffer[18];
    int index;

    if (a == 1) {
        _CreatePlayerOpen();
    }
    fn_80083F88(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
    fn_80182DD4("");
    fn_80182E04("");
    *pCount = DbCursorGetRowCount((DbCursor *)fn_80182DC8());
    if (_CreatePlayerHasContinue()) {
        (*pCount)++;
    }
    index = *pValue;
    if (_CreatePlayerHasContinue()) {
        index--;
    }
    if (index >= 0) {
        DbCursorSeek((DbCursor *)fn_80182DC8(), index);
        int id = PlayerDbGetId(fn_80182DC8());

        if (_CreatePlayer_iPlayerId != id || a == 1) {
            if (_CreatePlayer_iPlayerId != 0x7FFF) {
                PlayerDbSeekId(fn_80182DC8(), _CreatePlayer_iPlayerId, pValue);
            } else {
                _CreatePlayer_iPlayerId = id;
            }
            FEPlyrSetPlayer(FEPlyrGetFrontIndex(), _CreatePlayer_iPlayerId, 1);
        }
    } else {
        _CreatePlayer_iPlayerId = 0x7FFF;
    }
}

int CreatePlayerList::Leave(int a, int b, void **ppResult)
{
    int result = 1;

    if (b != 0) {
        result = -1;
        _CreatePlayerClose();
    } else {
        char buffer[27];

        *ppResult = _CreatePlayerGetPlayerMenu();
        PlayerDbSeekId(fn_80182DC8(), a, 0);
        fn_801832B0(buffer, 27);
        fn_80182E34(buffer);
    }
    return result;
}

void CreatePlayerList::Highlight(int index)
{
    if (index != 0x7FFF) {
        char buffer[27];
        int position;

        PlayerDbSeekId(fn_80182DC8(), index, 0);
        FEPlyrSetPlayer(FEPlyrGetFrontIndex(), index, 0);
        _CreatePlayer_iPlayerId = index;
        position = PlayerDbGetPbpo(fn_80182DC8());
        _CreatePlayer_iSkillGroup = _CreatePlayer_aSkillGroups[position];
        fn_80182E64(position);
        fn_80182E70(PlayerDbGetHeight(fn_80182DC8()));
        fn_80182E7C(PlayerDbGetWeight(fn_80182DC8()));
        fn_801832B0(buffer, 27);
        fn_80182DD4(buffer);
        fn_80182ED0();
        fn_80082138(fn_80182DC8(), &_CreatePlayer_sFace);
    } else {
        _CreatePlayer_iPlayerId = index;
        if (_CreatePlayerHasContinue()) {
            fn_80182DD4("Continue");
        }
        fn_80182EFC();
        fn_80182E64(0xFF);
        fn_80182E70(-1);
        fn_80182E7C(-1);
        FEPlyrLoadInvalidate(FEPlyrGetFrontIndex());
    }
    fn_80183740(0);
}

void CreatePlayerList::GetItemId(int index, int *pId)
{
    if (_CreatePlayerHasContinue()) {
        index--;
    }
    if (index >= 0) {
        DbCursorSeek((DbCursor *)fn_80182DC8(), index);
        *pId = PlayerDbGetId(fn_80182DC8());
    } else {
        *pId = 0x7FFF;
    }
}

void CreatePlayerList::GetItem(int index, MenuEntry_t *pEntry)
{
    char buffer[27] = { 0 };

    pEntry->mUnknown40 = 0;
    if (index != 0x7FFF) {
        int value;

        PlayerDbSeekId(fn_80182DC8(), index, 0);
        if (fn_80183950() && index == 0) {
            pEntry->mUnknown41 = 1;
        }
        value = PlayerDbGetPortraitId(fn_80182DC8());
        pEntry->mUnknown36 = DbCursorGetRow((DbCursor *)fn_80182DC8());
        if (_CreatePlayerHasContinue()) {
            pEntry->mUnknown36++;
        }
        pEntry->mId = index;
        pEntry->mUnknown30 = PlayerDbHasPlil(fn_80182DC8()) == 0;
        pEntry->mUnknown4 = 0;
        pEntry->mUnknown32 = value | 0xA0000;
        fn_801832B0(buffer, 27);
        fn_801C3284(pEntry->mName, buffer, 22);
    } else {
        pEntry->mId = index;
        pEntry->mUnknown36 = 0;
        pEntry->mUnknown30 = 1;
        pEntry->mUnknown32 = 0xC0000;
        if (_CreatePlayerHasContinue()) {
            pEntry->mUnknown4 = 8;
            fn_801C3284(pEntry->mName, "Continue", 22);
        }
    }
    FEPlyrPlayPairAnim();
}

void CreatePlayerMenu::Enter(int a, int *pCount, int *pValue)
{
    MenuListScreen::Enter(a, pCount, pValue);
    if (PlayerDbGetOriginalId(fn_80182DC8()) != 0x7FFF) {
        *pValue = 3;
    }
    FEPlyrSetPlayer(FEPlyrGetBackIndex(), _CreatePlayer_iPlayerId, 1);
    FEPlyrLoadSetScaleRamp(0);
    if (_CreatePlayer_bGearOpen) {
        GearMenuClose();
        _CreatePlayer_bGearOpen = 0;
    }
}

int CreatePlayerMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 1:
            *ppResult = _CreatePlayerGetInfoMenu();
            result = 1;
            break;
        case 2:
            *ppResult = _CreatePlayerGetAppearanceMenu();
            result = 1;
            break;
        case 0:
            *ppResult = _CreatePlayerGetAttributeMenu();
            result = 1;
            break;
        case 3:
            GearMenuOpen(1);
            _CreatePlayer_bGearOpen = 1;
            result = 1;
            *ppResult = GearMenuGetRoot();
            break;
        }
    } else {
        FEPlyrLoadSetScaleRamp(1);
    }
    return result;
}

void CreatePlayerMenu::Highlight(int id)
{
    fn_80182DD4(_CreatePlayer_aMenuEntries[id].mName);
}

void CreatePlayerMenu::GetItem(int index, MenuEntry_t *pEntry)
{
    MenuListScreen::GetItem(index, pEntry);
    if (fn_80183950()) {
        if (PlayerDbGetId(fn_80182DC8()) != 0) {
            pEntry->mUnknown30 = _CreatePlayer_aStoryEnabled[index];
            return;
        }
    } else if (PlayerDbGetOriginalId(fn_80182DC8()) != 0x7FFF) {
        pEntry->mUnknown30 = _CreatePlayer_aExistingEnabled[index];
        return;
    }
    pEntry->mUnknown30 = _CreatePlayer_aMenuEntries[index].mUnknown30;
}

int CreatePlayerInfoMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 6:
            *ppResult = _CreatePlayerGetSignatureMenu();
            result = 1;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            _CreatePlayerGetInfoOptionList()->mUnknown8 = a;
            result = 1;
            *ppResult = _CreatePlayerGetInfoOptionList();
            break;
        }
    }
    return result;
}

MenuItemEditor *CreatePlayerInfoMenu::GetEditor()
{
    return _CreatePlayerGetNameEditor();
}

int CreatePlayerHairMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            _CreatePlayerGetHairOptionList()->mUnknown8 = a;
            result = 1;
            *ppResult = _CreatePlayerGetHairOptionList();
            break;
        }
    }
    return result;
}

int CreatePlayerFaceMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            _CreatePlayerGetFaceOptionList()->mUnknown8 = a;
            result = 1;
            *ppResult = _CreatePlayerGetFaceOptionList();
            break;
        }
    }
    return result;
}

void CreatePlayerSkinMenu::Enter(int a, int *pCount, int *pValue)
{
    MenuListScreen::Enter(a, pCount, pValue);
    fn_80183740(0);
}

int CreatePlayerSkinMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
            _CreatePlayerGetSkinOptionList()->mUnknown8 = a;
            result = 1;
            *ppResult = _CreatePlayerGetSkinOptionList();
            break;
        }
        switch (a) {
        case 0:
            fn_80183740(&_CreatePlayer_aSkinLayouts[0]);
            break;
        case 1:
            fn_80183740(&_CreatePlayer_aSkinLayouts[1]);
            break;
        case 2:
            fn_80183740(&_CreatePlayer_aSkinLayouts[2]);
            break;
        case 3:
            fn_80183740(&_CreatePlayer_aSkinLayouts[3]);
            break;
        }
    }
    return result;
}

void CreatePlayerAppearanceMenu::Enter(int a, int *pCount, int *pValue)
{
    MenuListScreen::Enter(a, pCount, pValue);
    fn_80183740(0);
}

int CreatePlayerAppearanceMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
            result = 1;
            fn_80183740(&_CreatePlayer_aAppearanceLayouts[1]);
            *ppResult = _CreatePlayerGetHairMenu();
            break;
        case 1:
            result = 1;
            fn_80183740(&_CreatePlayer_aAppearanceLayouts[2]);
            *ppResult = _CreatePlayerGetFaceMenu();
            break;
        case 2:
            *ppResult = _CreatePlayerGetSkinMenu();
            result = 1;
            break;
        }
    } else {
        _CreatePlayerQueuePortrait(_CreatePlayer_iPlayerId);
    }
    return result;
}

void CreatePlayerAppearanceMenu::Highlight(int id)
{
    MenuListScreen::Highlight(id);
}

void CreatePlayerInfoOptionList::Enter(int a, int *pCount, int *pOut)
{
    switch (mUnknown8) {
    case 2:
        *pOut = _CreatePlayerPositionIndex(PlayerDbGetPbpo(fn_80182DC8()));
        *pCount = 7;
        break;
    case 5:
        *pOut = _CreatePlayerFindValue(PlayerDbGetPpsn(fn_80182DC8()), _CreatePlayer_aCelebrationStyles, 3);
        *pCount = 3;
        break;
    case 3:
        *pOut = PlayerDbGetPjen(fn_80182DC8());
        *pCount = 100;
        break;
    case 4:
        *pOut = PlayerDbGetPhan(fn_80182DC8());
        *pCount = 2;
        break;
    }
}

int CreatePlayerInfoOptionList::Leave(int a, int b, void **pOut)
{
    fn_80183740(0);
    if (b == 0) {
        switch (mUnknown8) {
        case 2:
            PlayerDbSetPbpo(fn_80182DC8(), _CreatePlayerPositionAt(a));
            fn_80182E64(_CreatePlayerPositionAt(a));
            break;
        case 3:
            PlayerDbSetPjen(fn_80182DC8(), a);
            break;
        case 5:
            PlayerDbSetPpsn(fn_80182DC8(), _CreatePlayer_aCelebrationStyles[a]);
            break;
        case 4:
            PlayerDbSetPhan(fn_80182DC8(), a);
            break;
        }
    } else if (mUnknown8 == 3) {
        PlayerLookSetNumber(0, PlayerDbGetPjen(fn_80182DC8()));
        PlayerLookSetNumber(1, PlayerDbGetPjen(fn_80182DC8()));
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    }
    return -1;
}

void CreatePlayerInfoOptionList::Highlight(int index)
{
    switch (mUnknown8) {
    case 2:
        break;
    case 3:
        PlayerLookSetNumber(0, index);
        PlayerLookSetNumber(1, index);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    case 4:
        break;
    case 5:
        FEPlyrSetPose(0, _CreatePlayer_aCelebrationPoses[index]);
        FEPlyrSetPose(1, _CreatePlayer_aCelebrationPoses[index]);
        break;
    }
}

void CreatePlayerInfoOptionList::GetItem(int index, MenuEntry_t *pOut)
{
    switch (mUnknown8) {
    case 2:
        fn_801C3284(pOut->mName, _CreatePlayer_aPositionNames[index], 22);
        break;
    case 3:
        fn_801C2D88(pOut->mName, 22, "%02d", index);
        break;
    case 5:
        fn_801C3284(pOut->mName, _CreatePlayer_aCelebrationNames[index], 22);
        break;
    case 4:
        fn_801C3284(pOut->mName, _CreatePlayer_aHandNames[index], 22);
        break;
    }
}

void CreatePlayerNameEditor::GetText(int a, int *pResult, MenuArg_t text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[16];
    char buffer2[16];

    switch (a) {
    case 0:
        *pResult = 1;
        PlayerDbGetFirstName(fn_80182DC8(), buffer, 12);
        fn_801C3284(pParams->mpText, buffer, pParams->mLength + 1);
        break;
    case 1:
        *pResult = 2;
        PlayerDbGetLastName(fn_80182DC8(), buffer2, 15);
        fn_801C3284(pParams->mpText, buffer2, pParams->mLength + 1);
        break;
    }
}

void CreatePlayerNameEditor::SetText(int a, MenuArg_t text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[16];
    char label[27];
    char label2[27];
    char name[32];

    switch (a) {
    case 0:
        fn_801C3284(buffer, pParams->mpText, 12);
        fn_80081E64(fn_80182DC8(), buffer, 12);
        fn_801832B0(label, 27);
        fn_80182E34(label);
        PlayerDbSeekId(fn_80182DC8(), _CreatePlayer_iPlayerId, 0);
        break;
    case 1:
        fn_801C3284(buffer, pParams->mpText, 15);
        fn_80081E98(fn_80182DC8(), buffer, 15);
        fn_801832B0(label2, 27);
        fn_80182E34(label2);
        PlayerDbSeekId(fn_80182DC8(), _CreatePlayer_iPlayerId, 0);
        PlayerDbGetNickname(fn_80182DC8(), name, 31);
        PlayerLookSetName(0, name);
        PlayerLookSetName(1, name);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    }
    FEPlyrSetPose(0, 24);
    FEPlyrSetPose(1, 24);
}

void CreatePlayerHairOptionList::Enter(int a, int *pCount, int *pOut)
{
    _CreatePlayer_sFaceCursor.OpenFchrTable();
    switch (mUnknown8) {
    case 0:
        fn_80087A78(0x12, &_CreatePlayer_sHairCursor, PlayerDbGetHairStyle(fn_80182DC8()), pOut);
        *pCount = fn_80087B00(0x12, &_CreatePlayer_sHairCursor);
        break;
    case 1:
        *pOut = PlayerDbGetHairColor(fn_80182DC8());
        *pCount = 12;
        break;
    case 2:
        _CreatePlayer_sFaceCursor.FindFchrRow(fn_80082280(fn_80182DC8()), pOut);
        *pCount = _CreatePlayer_sFaceCursor.GetRowCount();
        break;
    case 3:
        *pOut = PlayerDbGetFacialHairColor(fn_80182DC8());
        *pCount = 12;
        break;
    case 4:
        *pOut = fn_800822D4(fn_80182DC8());
        *pCount = 3;
        break;
    }
}

int CreatePlayerHairOptionList::Leave(int a, int b, void **pOut)
{
    if (b == 0) {
        switch (mUnknown8) {
        case 0:
            fn_80087938(0x12, &_CreatePlayer_sHairCursor, a, 0);
            fn_80087A30(0x12, &_CreatePlayer_sHairCursor);
            PlayerDbSetHairStyle(fn_80182DC8(), HairListGetId(&_CreatePlayer_sHairCursor));
            break;
        case 1:
            PlayerDbSetHairColor(fn_80182DC8(), a);
            break;
        case 2:
            _CreatePlayer_sFaceCursor.MoveToRow(a);
            fn_800822A8(fn_80182DC8(), _CreatePlayer_sFaceCursor.GetFchrPffh());
            FEPlyrSetPose(0, 26);
            FEPlyrSetPose(1, 26);
            break;
        case 3:
            PlayerDbSetFacialHairColor(fn_80182DC8(), a);
            FEPlyrSetPose(0, 26);
            FEPlyrSetPose(1, 26);
            break;
        case 4:
            fn_80082308(fn_80182DC8(), a);
            break;
        }
    } else {
        switch (mUnknown8) {
        case 0:
            _CreatePlayerSetHair(PlayerDbGetHairStyle(fn_80182DC8()));
            break;
        case 1:
            PlayerLookSetHairColor(0, PlayerDbGetHairColor(fn_80182DC8()));
            PlayerLookSetHairColor(1, PlayerDbGetHairColor(fn_80182DC8()));
            FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
            FEPlyrRequestSwap();
            break;
        case 2:
            _CreatePlayerSetFace(fn_80082280(fn_80182DC8()));
            break;
        case 3:
            PlayerLookSetFacialHairColor(0, PlayerDbGetFacialHairColor(fn_80182DC8()));
            PlayerLookSetFacialHairColor(1, PlayerDbGetFacialHairColor(fn_80182DC8()));
            FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
            FEPlyrRequestSwap();
            break;
        case 4:
            PlayerLookSetBrow(0, fn_800822D4(fn_80182DC8()));
            PlayerLookSetBrow(1, fn_800822D4(fn_80182DC8()));
            FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
            FEPlyrRequestSwap();
            break;
        }
    }
    _CreatePlayer_sFaceCursor.CloseTable();
    return -1;
}

void CreatePlayerHairOptionList::Highlight(int index)
{
    switch (mUnknown8) {
    case 0:
        fn_80087938(0x12, &_CreatePlayer_sHairCursor, index, 0);
        _CreatePlayerSetHair(HairListGetId(&_CreatePlayer_sHairCursor));
        break;
    case 1:
        PlayerLookSetHairColor(0, index);
        PlayerLookSetHairColor(1, index);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    case 2:
        _CreatePlayer_sFaceCursor.MoveToRow(index);
        _CreatePlayerSetFace(_CreatePlayer_sFaceCursor.GetFchrPffh());
        break;
    case 3:
        PlayerLookSetFacialHairColor(0, index);
        PlayerLookSetFacialHairColor(1, index);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    case 4:
        PlayerLookSetBrow(0, index);
        PlayerLookSetBrow(1, index);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
        break;
    }
}

void CreatePlayerHairOptionList::GetItem(int index, MenuEntry_t *pOut)
{
    char name[32];

    switch (mUnknown8) {
    case 0:
        fn_80087938(0x12, &_CreatePlayer_sHairCursor, index, 0);
        pOut->mUnknown40 = fn_800879E8(0x12, &_CreatePlayer_sHairCursor);
        HairListGetName(&_CreatePlayer_sHairCursor, name, 26);
        fn_801C3284(pOut->mName, name, 22);
        break;
    case 1:
    case 3:
        DbColPalGetPaletteName(index, name, 21);
        fn_801C3284(pOut->mName, name, 22);
        break;
    case 2:
        _CreatePlayer_sFaceCursor.MoveToRow(index);
        _CreatePlayer_sFaceCursor.GetFchrFhdcText(name, 21);
        fn_801C3284(pOut->mName, name, 22);
        break;
    case 4:
        fn_801C2D88(pOut->mName, 22, "EyeBrow %d", index + 1);
        break;
    }
}

void CreatePlayerFaceOptionList::Enter(int a, int *pCount, int *pOut)
{
    mUnknown12 = new (0) AppearanceNameTable;
    if (mUnknown8 == 8) {
        *pOut = PlayerDbGetPlex(fn_80182DC8());
        *pCount = 5;
    } else {
        const FaceFeatureRange_t *pRange = _CreatePlayerGetFaceMenu()->GetRange(mUnknown8);

        *pOut = _CreatePlayer_sFace.mUnknown0[pRange->mSlot] - pRange->mOffset;
        *pCount = pRange->mCount;
    }
}

int CreatePlayerFaceOptionList::Leave(int a, int b, void **pOut)
{
    if (b == 0) {
        if (mUnknown8 == 8) {
            PlayerDbSetPlex(fn_80182DC8(), a);
        } else {
            const FaceFeatureRange_t *pRange = _CreatePlayerGetFaceMenu()->GetRange(mUnknown8);

            _CreatePlayer_sFace.mUnknown0[pRange->mSlot] = a + pRange->mOffset;
            fn_80082334(fn_80182DC8(), &_CreatePlayer_sFace);
            PlayerLookSetFeatures(0, &_CreatePlayer_sFace);
            PlayerLookSetFeatures(1, &_CreatePlayer_sFace);
        }
    } else {
        if (mUnknown8 == 8) {
            PlayerLookSetPlex(0, PlayerDbGetPlex(fn_80182DC8()));
            PlayerLookSetPlex(1, PlayerDbGetPlex(fn_80182DC8()));
            FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
            FEPlyrRequestSwap();
        } else {
            fn_80082138(fn_80182DC8(), &_CreatePlayer_sFace);
            PlayerLookSetFeatures(0, &_CreatePlayer_sFace);
            PlayerLookSetFeatures(1, &_CreatePlayer_sFace);
            int slot = _CreatePlayerGetFaceMenu()->GetRange(mUnknown8)->mSlot;

            _CreatePlayerSetFaceFeature(slot, _CreatePlayer_sFace.mUnknown0[slot]);
        }
    }
    delete mUnknown12;
    return -1;
}

void CreatePlayerFaceOptionList::Highlight(int index)
{
    if (mUnknown8 == 8) {
        PlayerLookSetPlex(0, index);
        PlayerLookSetPlex(1, index);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    } else {
        const FaceFeatureRange_t *pRange = _CreatePlayerGetFaceMenu()->GetRange(mUnknown8);

        _CreatePlayerSetFaceFeature(pRange->mSlot, index + pRange->mOffset);
    }
}

void CreatePlayerFaceOptionList::GetItem(int index, MenuEntry_t *pOut)
{
    char name[32];

    if (mUnknown8 == 8) {
        fn_801C3284(pOut->mName, _CreatePlayer_aExpressionNames[index], 22);
    } else {
        const FaceFeatureRange_t *pRange = _CreatePlayerGetFaceMenu()->GetRange(mUnknown8);

        if (mUnknown8 == 0) {
            fn_801C3284(pOut->mName, _CreatePlayer_aHeadShapeNames[index + pRange->mOffset], 22);
        } else {
            mUnknown12->GetItemName(index + pRange->mOffset, (int)name, 31);
            fn_801C3284(pOut->mName, name, 22);
        }
    }
}

void CreatePlayerSkinOptionList::Enter(int a, int *pCount, int *pOut)
{
    int type = _CreatePlayer_aSkinParts[mUnknown8];

    if (type == 3) {
        *pCount = 12;
        *pOut = fn_80081E3C(fn_80182DC8());
    } else {
        DbCursor cursor;
        PlayerGear_t info;
        int key;

        fn_800817CC(fn_80182DC8(), &info);
        TattooTableOpen(&cursor, type);
        key = fn_80087B5C(type);
        fn_80087A78(key, &cursor, _CreatePlayerGetTattoo(&info, type), pOut);
        *pCount = fn_80087B00(fn_80087B5C(type), &cursor);
        TattooTableClose(&cursor);
    }
}

int CreatePlayerSkinOptionList::Leave(int a, int b, void **pOut)
{
    PlayerGear_t info;

    fn_800817CC(fn_80182DC8(), &info);
    int type = _CreatePlayer_aSkinParts[mUnknown8];

    if (b == 0) {
        if (type == 3) {
            PlayerDbSetSkinTone(fn_80182DC8(), a);
        } else {
            DbCursor cursor;

            TattooTableOpen(&cursor, type);
            fn_80087938(fn_80087B5C(type), &cursor, a, 0);
            fn_80087A30(fn_80087B5C(type), &cursor);
            _CreatePlayerSetTattoo(&info, type, TattooTableGetId(&cursor));
            TattooTableClose(&cursor);
            fn_8008199C(fn_80182DC8(), &info);
        }
    } else {
        if (type == 3) {
            PlayerLookSetSkin(0, fn_80081E3C(fn_80182DC8()) + 1);
            PlayerLookSetSkin(1, fn_80081E3C(fn_80182DC8()) + 1);
            FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
            FEPlyrRequestSwap();
        } else {
            PlayerLookSetPartVariant(0, type, _CreatePlayerGetTattoo(&info, type));
            PlayerLookSetPartVariant(1, type, _CreatePlayerGetTattoo(&info, type));
            FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
            FEPlyrRequestSwap();
        }
    }
    return -1;
}

void CreatePlayerSkinOptionList::Highlight(int index)
{
    int type = _CreatePlayer_aSkinParts[mUnknown8];

    if (type == 3) {
        PlayerLookSetSkin(0, index + 1);
        PlayerLookSetSkin(1, index + 1);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    } else {
        DbCursor cursor;
        int value;

        TattooTableOpen(&cursor, type);
        fn_80087938(fn_80087B5C(type), &cursor, index, 0);
        value = TattooTableGetId(&cursor);
        TattooTableClose(&cursor);
        PlayerLookSetPartVariant(0, type, value);
        PlayerLookSetPartVariant(1, type, value);
        FEPlyrLoadRequestReload(FEPlyrGetBackIndex(), 15);
        FEPlyrRequestSwap();
    }
}

void CreatePlayerSkinOptionList::GetItem(int index, MenuEntry_t *pOut)
{
    int type = _CreatePlayer_aSkinParts[mUnknown8];

    if (type == 3) {
        fn_801C2D88(pOut->mName, 22, "Skin Tone %d", index + 1);
    } else {
        DbCursor cursor;

        TattooTableOpen(&cursor, type);
        fn_80087938(fn_80087B5C(type), &cursor, index, 0);
        pOut->mUnknown40 = fn_800879E8(fn_80087B5C(type), &cursor);
        TattooTableGetName(&cursor, pOut->mName, 22);
        TattooTableGetId(&cursor);
        TattooTableClose(&cursor);
    }
}

void CreatePlayerSignatureList::Enter(int a, int *pCount, int *pOut)
{
    PoseTableSeek(&_CreatePlayer_sPoseCursor, PlayerDbGetSgt(fn_80182DC8(), mUnknown8), pOut);
    *pCount = DbCursorGetRowCount(&_CreatePlayer_sPoseCursor);
}

int CreatePlayerSignatureList::Leave(int a, int b, void **pOut)
{
    fn_80183740(0);
    if (b == 0) {
        DbCursorSeek(&_CreatePlayer_sPoseCursor, a);
        PlayerDbSetSgt(fn_80182DC8(), mUnknown8, PoseTableGetNumber(&_CreatePlayer_sPoseCursor));
    }
    return -1;
}

void CreatePlayerSignatureList::Highlight(int index)
{
    DbCursorSeek(&_CreatePlayer_sPoseCursor, index);
    FEPlyrSetPose(0, (unsigned short)(PoseTableGetNumber(&_CreatePlayer_sPoseCursor) + 31));
    FEPlyrSetPose(1, (unsigned short)(PoseTableGetNumber(&_CreatePlayer_sPoseCursor) + 31));
}

void CreatePlayerSignatureList::GetItem(int index, MenuEntry_t *pOut)
{
    DbCursorSeek(&_CreatePlayer_sPoseCursor, index);
    PoseTableGetName(&_CreatePlayer_sPoseCursor, pOut->mName, 22);
}

void CreatePlayerAttributeSlider::BeginSlider(int a, int b, int c, int *pD, int *pE, MenuArg_t textF, MenuArg_t textG,
                                 MenuArg_t textH)
{
    Params_80005284 *pLeft = textF.pParams;
    Params_80005284 *pRight = textG.pParams;
    Params_80005284 *pValue = textH.pParams;
    int *pMin = (int *)b;
    int *pMax = (int *)c;

    _CreatePlayer_iPendingCost = 0;
    fn_801C2D88(pValue->mpText, pValue->mLength, "");
    fn_80183740(0);
    _CreatePlayer_bSliderOpen = 1;
    switch (a) {
    case 10:
        *pMin = 65;
        *pMax = 84;
        *pE = PlayerDbGetHeight(fn_80182DC8());
        _CreatePlayerSaveOriginal(PlayerDbGetId(fn_80182DC8()), 10, *pE);
        *pD = _CreatePlayerGetOriginal(PlayerDbGetId(fn_80182DC8()), 10);
        fn_801C2D88(pLeft->mpText, pLeft->mLength, "Shorter");
        fn_801C2D88(pRight->mpText, pRight->mLength, "Taller");
        fn_801C2D88(pValue->mpText, pValue->mLength, "%d ft %d in", *pE / 12, *pE % 12);
        if (*pE < 84) {
            _CreatePlayer_iNextCost = _CreatePlayerHeightCost(*pE, *pE + 1);
        } else {
            _CreatePlayer_iNextCost = 0;
        }
        break;
    case 11:
        *pMin = 160;
        *pMax = 380;
        *pE = PlayerDbGetWeight(fn_80182DC8());
        _CreatePlayerSaveOriginal(PlayerDbGetId(fn_80182DC8()), 11, *pE);
        *pD = _CreatePlayerGetOriginal(PlayerDbGetId(fn_80182DC8()), 11);
        _CreatePlayer_iBodyType = PlayerDbGetPybt(fn_80182DC8());
        fn_801C2D88(pLeft->mpText, pLeft->mLength, "Lighter");
        fn_801C2D88(pRight->mpText, pRight->mLength, "Heavier");
        fn_801C2D88(pValue->mpText, pValue->mLength, "%d lbs", *pE);
        if (*pE < 380) {
            _CreatePlayer_iNextCost = _CreatePlayerWeightCost(*pE, *pE + 1);
        } else {
            _CreatePlayer_iNextCost = 0;
        }
        break;
    default: {
        int level;

        *pMin = 0;
        *pMax = 20;
        level = PlayerDbGetRating(fn_80182DC8(), fn_80183238(a));
        *pE = level / 5;
        if (level < 100) {
            if (level == 1) {
                _CreatePlayer_iNextCost = _CreatePlayerRatingCost(1, 5);
            } else {
                _CreatePlayer_iNextCost = _CreatePlayerRatingCost(level, level + 5);
            }
        } else {
            _CreatePlayer_iNextCost = 0;
        }
        _CreatePlayerSaveOriginal(PlayerDbGetId(fn_80182DC8()), a, *pE);
        *pD = _CreatePlayerGetOriginal(PlayerDbGetId(fn_80182DC8()), a);
        fn_801C2D88(pLeft->mpText, pLeft->mLength, "Worse");
        fn_801C2D88(pRight->mpText, pRight->mLength, "Better");
        fn_801C2D88(pValue->mpText, pValue->mLength, "Level %d", *pE);
        fn_80182FD4(fn_80183238(a), 1);
        break;
    }
    }
}

int CreatePlayerAttributeSlider::MoveSlider(int a, int b, MenuArg_t text)
{
    Params_80005284 *pParams = text.pParams;
    int result = 0;
    int cost;

    fn_801C2D88(pParams->mpText, pParams->mLength, "");
    switch (a) {
    case 10:
        if (b >= 65 && b <= 84 && b >= fn_80183230()) {
            cost = _CreatePlayerHeightCost(fn_80183228(), b);

            if (cost <= CreatePlayerGetPoints()) {
                if (b > fn_80183220()) {
                    FEPlyrSetPose(0, 6);
                    FEPlyrSetPose(1, 6);
                } else if (b < fn_80183220()) {
                    FEPlyrSetPose(0, 5);
                    FEPlyrSetPose(1, 5);
                }
                FEPlyrSetHeight(0, b);
                result = 1;
                FEPlyrSetHeight(1, b);
                _CreatePlayer_iPendingCost = cost;
                if (b < 84) {
                    _CreatePlayer_iNextCost = _CreatePlayerHeightCost(b, b + 1);
                } else {
                    _CreatePlayer_iNextCost = 0;
                }
            }
        }
        if (!result) {
            b = fn_80183220();
        }
        fn_801C2D88(pParams->mpText, pParams->mLength, "%d ft %d in", b / 12, b % 12);
        fn_80182E70(b);
        break;
    case 11:
        if (b >= 160 && b <= 380 && b >= fn_80183230()) {
            cost = _CreatePlayerWeightCost(fn_80183228(), b);

            if (cost <= CreatePlayerGetPoints()) {
                FEPlyrSetPose(0, 3);
                result = 1;
                FEPlyrSetPose(1, 3);
                _CreatePlayerUpdateBodyType(b);
                _CreatePlayer_iPendingCost = cost;
                if (b < 380) {
                    _CreatePlayer_iNextCost = _CreatePlayerWeightCost(b, b + 1);
                } else {
                    _CreatePlayer_iNextCost = 0;
                }
            }
        }
        if (!result) {
            b = fn_80183220();
        }
        fn_801C2D88(pParams->mpText, pParams->mLength, "%d lbs", b);
        fn_80182E7C(b);
        break;
    default: {
        int level = b * 5;
        int previous;

        if (level == 0) {
            level = 1;
        }
        previous = fn_80183228() * 5;
        if (previous == 0) {
            previous = 1;
        }
        if (level >= 1 && level <= 100 && b >= fn_80183230()) {
            if (b > fn_80183228()) {
                cost = _CreatePlayerRatingCost(previous, level);
            } else {
                cost = -_CreatePlayerRatingCost(level, previous);
            }
            if (cost <= CreatePlayerGetPoints()) {
                result = 1;
                fn_80182F60(fn_80183238(a), level);
                _CreatePlayer_iPendingCost = cost;
                if (level < 100) {
                    if (level == 1) {
                        _CreatePlayer_iNextCost = _CreatePlayerRatingCost(1, 5);
                    } else {
                        _CreatePlayer_iNextCost = _CreatePlayerRatingCost(level, level + 5);
                    }
                } else {
                    _CreatePlayer_iNextCost = 0;
                }
            }
        }
        if (!result) {
            b = fn_80183220();
        }
        fn_801C2D88(pParams->mpText, pParams->mLength, "Level %d", b);
        break;
    }
    }
    return result;
}

void CreatePlayerAttributeSlider::EndSlider(int a, int b, int c)
{
    int played = 0;

    _CreatePlayer_bSliderOpen = 0;
    if (b == 0) {
        switch (a) {
        case 10:
            CreatePlayerGetPoints();
            _CreatePlayerSpendPoints(_CreatePlayer_iPendingCost);
            FEPlyrSetHeight(0, c);
            FEPlyrSetHeight(1, c);
            PlayerDbSetHeight(fn_80182DC8(), c);
            if (c == 84) {
                FEPlyrSetPose(0, 22);
                played = 1;
                FEPlyrSetPose(1, 22);
            } else if (c >= 79 && c <= 83) {
                FEPlyrSetPose(0, 23);
                played = 1;
                FEPlyrSetPose(1, 23);
            }
            break;
        case 11: {
            int build;

            CreatePlayerGetPoints();
            _CreatePlayerSpendPoints(_CreatePlayer_iPendingCost);
            build = _CreatePlayerUpdateBodyType(c);
            PlayerDbSetPybt(fn_80182DC8(), build);
            PlayerDbSetWeight(fn_80182DC8(), c);
            if (c > 379) {
                FEPlyrSetPose(0, 21);
                played = 1;
                FEPlyrSetPose(1, 21);
            } else if (c > 294) {
                FEPlyrSetPose(0, 28);
                played = 1;
                FEPlyrSetPose(1, 28);
            } else if (c > 229) {
                FEPlyrSetPose(0, 27);
                played = 1;
                FEPlyrSetPose(1, 27);
            }
            break;
        }
        default: {
            float fraction = c * 0.05f;
            unsigned int value = PlayerDbGetRating(fn_80182DC8(), fn_80183238(a));
            int level;

            if (fraction > value * 0.01f) {
                if (fraction >= 0.5 && fraction < 0.75) {
                    FEPlyrSetPose(0, 17);
                    played = 1;
                    FEPlyrSetPose(1, 17);
                } else if (fraction >= 0.75 && fraction <= 0.99) {
                    FEPlyrSetPose(0, 18);
                    played = 1;
                    FEPlyrSetPose(1, 18);
                } else if (fraction == 1.0) {
                    FEPlyrSetPose(0, 19);
                    played = 1;
                    FEPlyrSetPose(1, 19);
                }
            }
            CreatePlayerGetPoints();
            _CreatePlayerSpendPoints(_CreatePlayer_iPendingCost);
            level = c * 5;
            if (level == 0) {
                level = 1;
            }
            PlayerDbSetRating(fn_80182DC8(), fn_80183238(a), level);
            break;
        }
        }
    } else {
        switch (a) {
        case 10:
            FEPlyrSetHeight(0, PlayerDbGetHeight(fn_80182DC8()));
            FEPlyrSetHeight(1, PlayerDbGetHeight(fn_80182DC8()));
            break;
        case 11:
            _CreatePlayerUpdateBodyType(PlayerDbGetWeight(fn_80182DC8()));
            break;
        default: {
            int index = fn_80183238(a);

            fn_80182F60(index, PlayerDbGetRating(fn_80182DC8(), index));
            break;
        }
        }
        FEPlyrSetPose(0, 20);
        played = 1;
        FEPlyrSetPose(1, 20);
    }
    fn_80182E70(PlayerDbGetHeight(fn_80182DC8()));
    fn_80182E7C(PlayerDbGetWeight(fn_80182DC8()));
    fn_8018300C();
    _CreatePlayer_iPendingCost = 0;
    if (!played) {
        fn_80183740(0);
    }
}

static void _CreatePlayerSaveOriginal(int key, int index, int value)
{
    signed char i;

    for (i = 0; i <= 14; i++) {
        if (_CreatePlayer_aOriginals[i].mKey != -1) {
            if (_CreatePlayer_aOriginals[i].mKey == key) {
                if (_CreatePlayer_aOriginals[i].mValues[index] == -1) {
                    _CreatePlayer_aOriginals[i].mValues[index] = value;
                }
                return;
            }
        } else {
            _CreatePlayer_aOriginals[i].mKey = key;
            _CreatePlayer_aOriginals[i].mValues[index] = value;
            return;
        }
    }
}

static void _CreatePlayerOpen()
{
    fn_801835C0(0x71);
    _CreatePlayer_iPlayerId = 0x7FFF;
    fn_801835C8();
    FaceTableOpen();
    HairListOpen(&_CreatePlayer_sHairCursor);
    PoseTableOpen(&_CreatePlayer_sPoseCursor);
    DbCursorFirst((DbCursor *)fn_80182DC8());
    if (fn_80183950()) {
        if (fn_80183948() != 3) {
            _CreatePlayer_iPlayerId = 0;
        }
        if (fn_8022EF8C(0, 0x434C4B53) == 0) {
            _CreatePlayer_bSkillTable = 1;
            _CreatePlayer_aSkillCosts[0] = 0;
            _CreatePlayer_iSkillGroup = 15;
        }
    }
}

static void _CreatePlayerClose()
{
    fn_80183704();
    FaceTableClose();
    HairListClose(&_CreatePlayer_sHairCursor);
    PoseTableClose(&_CreatePlayer_sPoseCursor);
    if (_CreatePlayer_bSkillTable) {
        fn_8022EFBC(0, 0x434C4B53);
        _CreatePlayer_bSkillTable = 0;
    }
    _CreatePlayer_iPlayerId = 0x7FFF;
}

extern "C" MenuScreen *CreatePlayerGetMenu(void)
{
    return _CreatePlayerGetPlayerList();
}

static void _CreatePlayerSpendPoints(int value)
{
    if (_CreatePlayer_iPoints >= value) {
        _CreatePlayer_iPoints -= value;
    } else {
        _CreatePlayer_iPoints = 0;
    }
}

extern "C" void CreatePlayerSetPoints(int value)
{
    _CreatePlayer_iPoints = value;
}

extern "C" int CreatePlayerGetPoints(void)
{
    return _CreatePlayer_iPoints;
}

extern "C" int CreatePlayerGetPendingCost(void)
{
    return _CreatePlayer_iPendingCost;
}

extern "C" void CreatePlayerResetOriginals(void)
{
    unsigned char i;
    unsigned char j;

    for (i = 0; i <= 14; i++) {
        _CreatePlayer_aOriginals[i].mKey = -1;
        for (j = 0; j <= 11; j++) {
            _CreatePlayer_aOriginals[i].mValues[j] = -1;
        }
    }
}

static int _CreatePlayerGetOriginal(int key, int index)
{
    signed char i;

    for (i = 0; i <= 14; i++) {
        if (_CreatePlayer_aOriginals[i].mKey == key) {
            return _CreatePlayer_aOriginals[i].mValues[index];
        }
    }
    return -1;
}

extern "C" int CreatePlayerGetNextCost(void)
{
    if (!_CreatePlayer_bSliderOpen) {
        return 0;
    }
    return _CreatePlayer_iNextCost;
}

extern "C" int CreatePlayerGetPlayerId(void)
{
    return _CreatePlayer_iPlayerId;
}

extern "C" void CreatePlayerApplyPreset(int a)
{
    int i;
    int value = _CreatePlayerPositionAt(a);

    PlayerDbSetPbpo(fn_80182DC8(), value);
    for (i = 0; i <= 11; i++) {
        switch (i) {
        case 10:
            PlayerDbSetHeight(fn_80182DC8(), _CreatePlayer_aPresets[a][i]);
            break;
        case 11:
            PlayerDbSetWeight(fn_80182DC8(), _CreatePlayer_aPresets[a][i]);
            break;
        default:
            PlayerDbSetRating(fn_80182DC8(), fn_80183238(i), _CreatePlayer_aPresets[a][i]);
            break;
        }
    }
}

static inline CreatePlayerAttributeSlider *_CreatePlayerGetSlider()
{
    static CreatePlayerAttributeSlider sInstance;
    return &sInstance;
}

static inline CreatePlayerSignatureList *_CreatePlayerGetSignatureList()
{
    static CreatePlayerSignatureList sInstance;
    return &sInstance;
}

static inline CreatePlayerMenu *_CreatePlayerGetPlayerMenu()
{
    static CreatePlayerMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerInfoMenu *_CreatePlayerGetInfoMenu()
{
    static CreatePlayerInfoMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerAppearanceMenu *_CreatePlayerGetAppearanceMenu()
{
    static CreatePlayerAppearanceMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerAttributeMenu *_CreatePlayerGetAttributeMenu()
{
    static CreatePlayerAttributeMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerSignatureMenu *_CreatePlayerGetSignatureMenu()
{
    static CreatePlayerSignatureMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerInfoOptionList *_CreatePlayerGetInfoOptionList()
{
    static CreatePlayerInfoOptionList sInstance;
    return &sInstance;
}

static inline CreatePlayerNameEditor *_CreatePlayerGetNameEditor()
{
    static CreatePlayerNameEditor sInstance;
    return &sInstance;
}

static inline CreatePlayerHairOptionList *_CreatePlayerGetHairOptionList()
{
    static CreatePlayerHairOptionList sInstance;
    return &sInstance;
}

static inline CreatePlayerFaceOptionList *_CreatePlayerGetFaceOptionList()
{
    static CreatePlayerFaceOptionList sInstance;
    return &sInstance;
}

static inline CreatePlayerSkinOptionList *_CreatePlayerGetSkinOptionList()
{
    static CreatePlayerSkinOptionList sInstance;
    return &sInstance;
}

static inline CreatePlayerHairMenu *_CreatePlayerGetHairMenu()
{
    static CreatePlayerHairMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerFaceMenu *_CreatePlayerGetFaceMenu()
{
    static CreatePlayerFaceMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerSkinMenu *_CreatePlayerGetSkinMenu()
{
    static CreatePlayerSkinMenu sInstance;
    return &sInstance;
}

static inline CreatePlayerList *_CreatePlayerGetPlayerList()
{
    static CreatePlayerList sInstance;
    return &sInstance;
}
