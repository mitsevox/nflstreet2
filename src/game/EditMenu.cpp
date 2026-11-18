/* The edit menu behind the create-team, create-player, gear and story-team
   screens. It keeps the stack of menu screens and the item editor of the
   current one, answers the UI messages of these screens (opening, choosing,
   highlighting and the colour, choice, slider and text controls), holds the
   team being edited for the session (backing it up, restoring or saving it)
   and shows the two front-end player models. */
#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/PaletteColor.h"
#include "game/EditMenu.h"
#include <string.h>
#include "game/fn_8021D7B8.h"
#include "game/UISGameMsg.h"

/* One entry of the screen stack _EditMenu_aScreenStack. */
struct EditMenuStackEntry_t {
    int mUnknown0;
    MenuScreen *mpScreen;
};

/* Texts and values shown by the current screen. */
struct EditMenuState_t {
    char mName0[21];
    char mName1[21];
    char mName2[21];
    int mUnknown64;
    int mUnknown68;
    int mUnknown72;
    int mUnknown76;
    int mUnknown80;
    int mUnknown84;
    int mUnknown88;
    unsigned char mUnknown92;
    int mUnknown96;
    int mValues[10];
    int mUnknown140;
};

extern "C" {
extern void *gUISMainInfo;

MenuScreen *CreateTeamGetMenu(void);
MenuScreen *CreatePlayerGetMenu(void);
void CreatePlayerSetPoints(int value);
int CreatePlayerGetPoints(void);
int CreatePlayerGetPendingCost(void);
void CreatePlayerResetOriginals(void);
int CreatePlayerGetNextCost(void);
int CreatePlayerGetPlayerId(void);
void CreatePlayerApplyPreset(int a);
MenuScreen *fn_8000EB3C(void);
int fn_8000EB5C(void);
int fn_8000EB80(void);
void fn_8000EBA4(int a);
int fn_8000EC14(void);
int fn_8000EC38(void);
void FEPlyrShow(void);
void FEPlyrHide(void);
void FEPlyrSetPosition(int index, float x, float y, float z);
void FEPlyrSetAngle(int index, float angle);
void FEPlyrSetScale(int index, float scale);
void FEPlyrPlayAnim(int index, int a, int b);
void FEPlyrSetPose(int index, unsigned int value);
void FEPlyrSetPriority(int index, int a);
void FEPlyrMoveTo(int index, float x, float y, float z, float angle, float scale, int flag);
int FEPlyrUpdateMoves(void);
float FEPlyrSpin(float a);
void FEPlyrResetPose(int a);
unsigned char FEPlyrSetPairMode(unsigned char enable, int a, int b);
void MemCardFilesStoreChecksum(int a, int b);
void fn_8005F29C(void);
void ChalCloseCursors(void);
int ChalGetDevPoints(void);
void ChalSetDevPoints(int a);
int DbCursorGetRow(DbCursor *pObject);
int fn_800841AC(DbCursor *pObject);
int fn_800841D8(DbCursor *pObject);
int fn_80084204(DbCursor *pObject);
void fn_8007BA48(DbCursor *pObject);
void fn_8007BB04(DbCursor *pObject);
int fn_8007BB84(DbCursor *pCursor, int a, int b, int *pResult);
void fn_8007BE20(DbCursor *pCursor, char *pBuffer, int size);
int fn_8007BF14(int a);
int fn_8007C690(DbCursor *pCursor, short *pOut);
void PlayerDbGetShortName(Object_8008044C *pObject, char *pBuffer, int size);
void PlayerDbGetFullName(Object_8008044C *pObject, char *pBuffer, int size);
void PlayerAddGearRatings(Object_8008044C *pObject, PlayerGear_t *pInfo, int *pValues);
void PlayerGetGearBonuses(Object_8008044C *pObject, short *pValues);
void fn_80082534(int a, int b);
void fn_80082558(int a, int b);
int fn_8008775C(void);
void fn_80087880(int a);
void PositionAbbrevFormat(int a, char *pText);
int ColorPickCellToIndex(int a, int b);
void ColorPickIndexToCell(int value, int *pQuotient, int *pRemainder);
int ColorPickGetSelected(void);
int MsgGameGetSetupState(void);
int fn_80186B38(int a);
void TeamLogoRequestTint(int index, int a, int b, int c, const unsigned char *pColor);
int TeamLogoGetHandle(int a);
int StoryTeamExists(int a);
int StoryTeamLoadToStats(int a, int b, int c, int *pD);
void StoryTeamStoreFromStats(int a, int b);
void StoryTeamClear(void);
void StoryTeamBackup(int *pA, int *pB, int c);
void StoryTeamFreeBackup(int a, int b);
void StoryTeamRestore(int a, int b);
void fn_8018C48C(int tag);
int CreateTeamInsertNew(int a);
int CreateTeamExists(int a);
int CreateTeamLoadToStats(int a, int b);
void CreateTeamStoreFromStats(int a, int b);
void CreateTeamClear(void);
void CreateTeamBackup(int *pA, int *pB, int c);
void CreateTeamFreeBackup(int a, int b);
void CreateTeamRestore(int a, int b);
int StoryGetDevPoints(int a);
void StorySetDevPoints(int a, int b);
int StoryStartNew(void);
void StorySetNew(int index, int value);
void StorySetIndexedFlag(int a, int b, int c);
void fn_8018EF6C(int a);
int GauntletGetCurrentTeam(int a);
void GauntletReset(int a);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
void *UIGLibraryGetGlobal(int index);
unsigned int UIGFontGetStringWidth(void *a, int b, int c, const char *pText);
int fn_8022F384(int a);
int fn_8022F4BC(void);
}

static int _EditMenu_iMode = 6;
static unsigned char _EditMenu_bActive = 0;
static int _EditMenu_iStackTop = 0;
static int _EditMenu_iHighlight = 0;
static int _EditMenu_iItemCount = 0;
static signed char _EditMenu_cTeamSlot = 0;
static int _EditMenu_iCycleIndex = 0;
static int _EditMenu_iCycleStart = 0;
static int _EditMenu_iCycleCount = 0;
static int _EditMenu_iView = -1;
static int _EditMenu_iSliderValue = 0;
static int _EditMenu_iSliderStart = 0;
static int _EditMenu_iSliderMin = 0;
static unsigned char _EditMenu_bPresetPending = 0;
static int _EditMenu_iShownLogo = -1;
static int _EditMenu_iShownLogoHandle = -1;
static unsigned char _EditMenu_bChanged = 0;
static unsigned char _EditMenu_bHasOwner = 0;
static unsigned char _EditMenu_bAttributeMode = 0;
static unsigned char _EditMenu_bOwnerFlag = 0;
static unsigned char _EditMenu_bPending = 0;
static unsigned char _EditMenu_bSaving = 0;

static MenuEntry_t _EditMenu_aTopEntries[2] = {
    {0, 0, "Edit Team", 1, 0, 0, 0},
    {1, 0, "Edit Player", 1, 0, 0, 0},
};
static PlayerLayout_t _EditMenu_PlayerLayout = {525.0f, 415.0f, 8.2f, 353.0f, 1.0f, 15, 1};
static int _EditMenu_aRatingSlots[10] = {6, 4, 7, 0, 3, 2, 1, 5, 8, 9};
static char _EditMenu_szOwnerText[28] = "";

extern DbCursor gEditMenuTeamCursor;
extern Object_8008044C gEditMenuPlayerCursor;
static EditMenuState_t _EditMenu_State;
static EditMenuStackEntry_t _EditMenu_aScreenStack[8];
static char _EditMenu_szOwnerName[28];
static unsigned char _EditMenu_aRatingFlags[10];

extern MenuItemEditor gEditMenuDefaultEditor;
static MenuItemEditor *_EditMenu_pEditor;
static int _EditMenu_iTeam;
static unsigned char _EditMenu_aTeamColors[3];
static unsigned char _EditMenu_aColorPick[3];
static int _EditMenu_iTeamTableCopy;
static int _EditMenu_iPlayerTableCopy;
static int _EditMenu_iSavedPoints;

/* Functions of this file referenced before their definitions. */
extern "C" {
void EditMenuReloadTeam(void);
void EditMenuGetColorIndices(unsigned char *pOut);
DbCursor *EditMenuGetTeamCursor(void);
Object_8008044C *EditMenuGetPlayerCursor(void);
void EditMenuSetItemName(const char *pText);
void EditMenuSetName(char *pText);
void EditMenuSetPosition(int a);
void EditMenuSetHeight(int a);
void EditMenuSetWeight(int a);
void EditMenuSetLogo(int a, int b);
void EditMenuSetLogoHandle(int a);
void EditMenuSetLogoFlag(unsigned char a);
void EditMenuClearRatingFlags(void);
void EditMenuClearOwner(void);
void EditMenuSetOwnerFlag(unsigned char a);
void EditMenuSetItemLogo(int a);
void EditMenuBegin(int mode, int value);
void EditMenuEnd(void);
int EditMenuIsOpen(void);
void EditMenuSetView(int a);
PlayerLayout_t *EditMenuGetPlayerLayout(void);
int EditMenuGetMode(void);
int EditMenuIsStoryTeam(void);
int EditMenuIsCreateTeam(void);
int EditMenuIsPlayerCopy(void);
}

inline MenuItemEditor *MenuScreen::GetEditor()
{
    return 0;
}

/* The top screen of the edit menu: "Edit Team" or "Edit Player". */
class EditTopMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual int GetEntryCount() { return 2; }
    virtual MenuEntry_t *GetEntries() { return _EditMenu_aTopEntries; }

    char mUnknown4[4];
};

static inline EditTopMenu *_EditMenuGetTopMenu();

extern "C" {

void EditMenuBackupTeam(void)
{
    switch (_EditMenu_iMode) {
    case 4:
        _EditMenu_iSavedPoints = StoryGetDevPoints(_EditMenu_cTeamSlot);
        StoryTeamBackup(&_EditMenu_iTeamTableCopy, &_EditMenu_iPlayerTableCopy, fn_8022F4BC());
        break;
    case 3:
        _EditMenu_iSavedPoints = StoryGetDevPoints(_EditMenu_cTeamSlot);
        break;
    case 5:
        _EditMenu_iSavedPoints = 0;
        break;
    case 0:
    case 2:
        _EditMenu_iSavedPoints = ChalGetDevPoints();
        break;
    default:
        _EditMenu_iSavedPoints = ChalGetDevPoints();
        CreateTeamBackup(&_EditMenu_iTeamTableCopy, &_EditMenu_iPlayerTableCopy, fn_8022F4BC());
        break;
    }
}

void EditMenuFreeBackup(void)
{
    switch (_EditMenu_iMode) {
    case 4:
        StoryTeamFreeBackup(_EditMenu_iTeamTableCopy, _EditMenu_iPlayerTableCopy);
        break;
    case 0:
    case 2:
    case 3:
    case 5:
        break;
    default:
        CreateTeamFreeBackup(_EditMenu_iTeamTableCopy, _EditMenu_iPlayerTableCopy);
        break;
    }
}

void EditMenuRestoreTeam(void)
{
    if (EditMenuIsPlayerCopy()) {
        fn_80082558(_EditMenu_iTeam, _EditMenu_cTeamSlot);
        return;
    }
    if (EditMenuIsStoryTeam()) {
        StoryTeamRestore(_EditMenu_iTeamTableCopy, _EditMenu_iPlayerTableCopy);
    } else {
        CreateTeamRestore(_EditMenu_iTeamTableCopy, _EditMenu_iPlayerTableCopy);
    }
    EditMenuReloadTeam();
    CreatePlayerSetPoints(_EditMenu_iSavedPoints);
    if (!EditMenuIsStoryTeam()) {
        ChalSetDevPoints(_EditMenu_iSavedPoints);
    }
    CreatePlayerResetOriginals();
}

void EditMenuPushScreen(MenuScreen *pScreen)
{
    _EditMenu_iStackTop++;
    _EditMenu_aScreenStack[_EditMenu_iStackTop].mpScreen = pScreen;
    _EditMenu_aScreenStack[_EditMenu_iStackTop].mUnknown0 = 0;
}

void EditMenuResetScreens(MenuScreen *pScreen)
{
    _EditMenu_iStackTop = 0;
    _EditMenu_aScreenStack[_EditMenu_iStackTop].mUnknown0 = 0;
    _EditMenu_aScreenStack[_EditMenu_iStackTop].mpScreen = pScreen;
}

void EditMenuPopScreen(void)
{
    _EditMenu_aScreenStack[_EditMenu_iStackTop].mpScreen = 0;
    _EditMenu_iStackTop--;
}

MenuScreen *EditMenuGetScreen(void)
{
    return _EditMenu_aScreenStack[_EditMenu_iStackTop].mpScreen;
}

int EditMenuGetSelection(void)
{
    return _EditMenu_aScreenStack[_EditMenu_iStackTop].mUnknown0;
}

void EditMenuSetSelection(int value)
{
    _EditMenu_aScreenStack[_EditMenu_iStackTop].mUnknown0 = value;
}

int EditMenuGetRatingSlot(int value)
{
    int i;

    for (i = 0; i < 10; i++) {
        if (_EditMenu_aRatingSlots[i] == value) {
            break;
        }
    }
    return i;
}

void EditMenuEnterScreen(int a, int *pCount, int *pValue)
{
    EditMenuGetScreen()->Enter(a, pCount, pValue);
    _EditMenu_iItemCount = *pCount;
    EditMenuSetSelection(*pValue);
    _EditMenu_pEditor = EditMenuGetScreen()->GetEditor();
    if (_EditMenu_pEditor == 0) {
        _EditMenu_pEditor = &gEditMenuDefaultEditor;
    }
}

void EditMenuOpen(int a, int *pCount, int *pValue)
{
    char buffer[24];

    _EditMenu_iStackTop = -1;
    switch (a) {
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x78:
        switch (_EditMenu_iMode) {
        case 0:
        case 3:
            EditMenuPushScreen(CreateTeamGetMenu());
            break;
        case 5:
            EditMenuPushScreen(CreatePlayerGetMenu());
            break;
        default:
            EditMenuPushScreen(_EditMenuGetTopMenu());
            break;
        }
        break;
    case 0x384:
        EditMenuPushScreen(fn_8000EB3C());
        break;
    }
    *pValue = 0;
    EditMenuEnterScreen(1, pCount, pValue);
    EditMenuSetLogo(4, fn_80084158(EditMenuGetTeamCursor()));
    if (fn_80084438(EditMenuGetTeamCursor())) {
        EditMenuSetLogoHandle(-1);
    } else {
        EditMenuSetLogoHandle(0);
    }
    EditMenuSetLogoFlag(0);
    _EditMenu_State.mUnknown96 = -1;
    _EditMenu_aTeamColors[0] = fn_800841AC(EditMenuGetTeamCursor());
    _EditMenu_aTeamColors[1] = fn_800841D8(EditMenuGetTeamCursor());
    _EditMenu_aTeamColors[2] = fn_80084204(EditMenuGetTeamCursor());
    TeamLogoRequestTint(0, 4, fn_80084158(EditMenuGetTeamCursor()), 172, _EditMenu_aTeamColors);
    _EditMenu_iShownLogo = fn_80084158(EditMenuGetTeamCursor());
    _EditMenu_iShownLogoHandle = 0;
    fn_80083F88(EditMenuGetTeamCursor(), buffer, 18);
    EditMenuSetName(buffer);
    if (!EditMenuIsPlayerCopy()) {
        if (EditMenuIsStoryTeam()) {
            CreatePlayerSetPoints(StoryGetDevPoints(_EditMenu_cTeamSlot));
        } else {
            CreatePlayerSetPoints(ChalGetDevPoints());
        }
    }
}

void EditMenuStart(int a)
{
    if (_EditMenu_bPending) {
        EditMenuBegin(_EditMenu_iMode, _EditMenu_iTeam);
        _EditMenu_bPending = 1;
    }
    if (!EditMenuIsOpen()) {
        switch (a) {
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x78:
        case 0x195:
            EditMenuBegin(1, 0x3FF);
            _EditMenu_bPending = 1;
            break;
        case 0x384:
            EditMenuBegin(2, 0x3FF);
            _EditMenu_bPending = 1;
            break;
        }
    }
    switch (a) {
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x78:
    case 0x195:
        if (EditMenuIsPlayerCopy()) {
            EditMenuSetView(0x71);
        } else {
            EditMenuSetView(0x70);
        }
        break;
    case 0x384:
        EditMenuSetView(0x384);
        _EditMenu_bPending = 1;
        break;
    }
    EditMenuBackupTeam();
    FEPlyrResetPose(0);
    EditMenuClearOwner();
    EditMenuClearRatingFlags();
    EditMenuSetPosition(0xFF);
    EditMenuSetHeight(-1);
    EditMenuSetWeight(-1);
    EditMenuSetOwnerFlag(0);
}

void EditMenuReloadTeam(void)
{
    Desc_8008044C desc;
    int status;

    fn_8008056C(&gEditMenuPlayerCursor);
    if (EditMenuIsStoryTeam()) {
        fn_8018C48C(0x54415453);
        if (StoryTeamExists(_EditMenu_cTeamSlot)) {
            _EditMenu_iTeam = StoryTeamLoadToStats(_EditMenu_cTeamSlot, 0, 0, &status);
        }
    } else if (EditMenuIsPlayerCopy()) {
        fn_80082558(_EditMenu_iTeam, _EditMenu_cTeamSlot);
    } else {
        fn_8018C48C(0x54415453);
        if (CreateTeamExists(_EditMenu_cTeamSlot)) {
            _EditMenu_iTeam = CreateTeamLoadToStats(_EditMenu_cTeamSlot, 0);
        }
    }
    fn_80084034(&gEditMenuTeamCursor, _EditMenu_iTeam, 0);
    desc.mUnknown8 = _EditMenu_iTeam;
    desc.mUnknown4 = 1;
    desc.mUnknown0 = 1;
    fn_8008044C(&gEditMenuPlayerCursor, &desc, 0x54415453);
}

void EditMenuWaitForSave(void)
{
    int busy = gFMCAPPORT.IsBusy();

    if (!busy) {
        FELoopSetFrameCallback(0);
        EditMenuEnd();
        _EditMenu_bPending = busy;
        _EditMenu_bSaving = busy;
    }
}

void EditMenuClose(unsigned char a)
{
    void *pResult = 0;
    int done = 0;

    EditMenuGetScreen()->Leave(_EditMenu_iHighlight, 1, &pResult);
    _EditMenu_aScreenStack[_EditMenu_iStackTop].mpScreen = 0;
    _EditMenu_bChanged = done;
    if (!a) {
        switch (_EditMenu_iMode) {
        case 0:
        case 3:
            if (!MsgGameGetSetupState()) {
                done = 1;
            }
            break;
        case 2:
            break;
        case 5:
            fn_80082558(_EditMenu_iTeam, _EditMenu_cTeamSlot);
            break;
        default:
            EditMenuReloadTeam();
            break;
        }
        gFMCAPPORT.ClearEntries();
    }
    EditMenuFreeBackup();
    EditMenuSetView(-1);
    if (EditMenuIsStoryTeam() || _EditMenu_bPending) {
        FELoopSetFrameCallback(EditMenuWaitForSave);
        _EditMenu_bSaving = 1;
    }
    if (done) {
        MemCardFilesStoreChecksum(2, fn_8022F384(fn_8022F4BC()));
    }
}

void EditMenuChoose(int a, int *pCount, int *pValue)
{
    int result;
    void *pResult = 0;
    int back = a == 0;

    result = EditMenuGetScreen()->Leave(_EditMenu_iHighlight, back, &pResult);
    if (result == -1) {
        if (!back) {
            _EditMenu_bChanged = 1;
        }
        EditMenuPopScreen();
    } else if (result == 1) {
        EditMenuPushScreen((MenuScreen *)pResult);
    } else if (result == -2) {
        if (!back) {
            _EditMenu_bChanged = 1;
        }
        EditMenuPopScreen();
        EditMenuPopScreen();
    } else {
        EditMenuResetScreens((MenuScreen *)pResult);
        result = 1;
    }
    *pValue = EditMenuGetSelection();
    EditMenuSetItemLogo(-1);
    EditMenuEnterScreen(result, pCount, pValue);
}

void EditMenuGetItemId(int a, int *pId)
{
    EditMenuGetScreen()->GetItemId(a, pId);
}

void EditMenuInitEntry(MenuEntry_t *pEntry, int id)
{
    pEntry->mId = id;
    pEntry->mUnknown36 = id;
    pEntry->mUnknown4 = 0;
    pEntry->mUnknown40 = 0;
    pEntry->mUnknown30 = 1;
    pEntry->mUnknown32 = 0xC0000;
    pEntry->mUnknown41 = 0;
    strnzcpy(pEntry->mName, "NO TEXT!", 22);
}

void EditMenuHighlight(int a, int *pResult, MenuArg_t text0, MenuArg_t text1, MenuArg_t text2)
{
    MenuText_t *p0 = text0.pParams;
    MenuText_t *p1 = text1.pParams;
    MenuText_t *p2 = text2.pParams;
    MenuEntry_t entry;

    _EditMenu_iHighlight = a;
    EditMenuInitEntry(&entry, a);
    EditMenuGetScreen()->Highlight(a);
    EditMenuGetScreen()->GetItem(a, &entry);
    if (entry.mUnknown36 < 0 || entry.mUnknown36 >= _EditMenu_iItemCount) {
        entry.mUnknown36 = 0;
    }
    EditMenuSetSelection(entry.mUnknown36);
    strnzcpy(p0->mpText, _EditMenu_State.mName0, p0->mLength + 1);
    strnzcpy(p1->mpText, _EditMenu_State.mName1, p1->mLength + 1);
    strnzcpy(p2->mpText, _EditMenu_State.mName2, p2->mLength + 1);
    *pResult = _EditMenu_iStackTop;
}

}


extern "C" {

void EditMenuGetLogo(int a, int *pA, int *pB, int *pC)
{
    EditMenuState_t *pState = &_EditMenu_State;
    unsigned char colors[3];

    *pA = (pState->mUnknown80 << 16) | pState->mUnknown84;
    *pB = pState->mUnknown88;
    *pC = pState->mUnknown92;
    EditMenuGetColorIndices(colors);
    _EditMenu_aTeamColors[0] = fn_800841AC(EditMenuGetTeamCursor());
    _EditMenu_aTeamColors[1] = fn_800841D8(EditMenuGetTeamCursor());
    _EditMenu_aTeamColors[2] = fn_80084204(EditMenuGetTeamCursor());
    EditMenuGetColorIndices(colors);
    TeamLogoRequestTint(0, pState->mUnknown80, pState->mUnknown84, 172, colors);
    _EditMenu_iShownLogo = *pA;
    _EditMenu_iShownLogoHandle = *pB;
}

void EditMenuGetPlayerInfo(int a, int *pValues, int *pResult, MenuArg_t text0, MenuArg_t text1,
                 MenuArg_t text2)
{
    MenuText_t *p0 = text0.pParams;
    MenuText_t *p1 = text1.pParams;
    MenuText_t *p2 = text2.pParams;
    int i;

    if (_EditMenu_iHighlight == a) {
        for (i = 0; i < 10; i++) {
            pValues[EditMenuGetRatingSlot(i)] = _EditMenu_State.mValues[i];
        }
        if ((unsigned int)_EditMenu_State.mUnknown64 < 14) {
            PositionAbbrevFormat(_EditMenu_State.mUnknown64, p0->mpText);
            fn_801C2D88(p1->mpText, p1->mLength + 1, "%d ft %d in", _EditMenu_State.mUnknown68 / 12,
                        _EditMenu_State.mUnknown68 % 12);
            fn_801C2D88(p2->mpText, p2->mLength + 1, "%d lbs", _EditMenu_State.mUnknown72);
        } else {
            strnzcpy(p0->mpText, "", p0->mLength + 1);
            strnzcpy(p1->mpText, "", p1->mLength + 1);
            strnzcpy(p2->mpText, "", p2->mLength + 1);
        }
        *pResult = 1;
    }
}

void EditMenuGetItem(int a, int *p1, int *p2, int *p3, MenuArg_t text, int *p5, int *p6, int *p7,
                 int *p8)
{
    MenuText_t *p4 = text.pParams;
    MenuEntry_t entry;

    EditMenuInitEntry(&entry, a);
    EditMenuGetScreen()->GetItem(a, &entry);
    *p1 = entry.mUnknown30;
    *p2 = entry.mUnknown4;
    *p7 = entry.mUnknown40;
    *p8 = entry.mUnknown41;
    if (_EditMenu_iStackTop == 0) {
        *p3 = 1;
    } else {
        *p3 = 0;
    }
    *p5 = 0;
    *p6 = 0;
    strnzcpy(p4->mpText, entry.mName, p4->mLength + 1);
}

void EditMenuGetColor(int a, int *pB, int *pC)
{
    int value = 0;

    _EditMenu_pEditor->GetColor(a, &value);
    ColorPickIndexToCell(value, pB, pC);
}

void EditMenuEndColor(int a, int b, int c)
{
    int value = ColorPickCellToIndex(b, c);

    _EditMenu_pEditor->EndColor(a, 0, value);
    _EditMenu_bChanged = 1;
}

void EditMenuCancelColor(int a)
{
    _EditMenu_pEditor->EndColor(a, 1, -1);
}

void EditMenuEndCycle(int a)
{
    _EditMenu_pEditor->EndCycle(a, 0, _EditMenu_iCycleIndex);
    if (_EditMenu_iCycleStart != _EditMenu_iCycleIndex) {
        _EditMenu_bChanged = 1;
    }
}

void EditMenuCancelCycle(int a)
{
    _EditMenu_pEditor->EndCycle(a, 1, -1);
}

void EditMenuCycle(int a, int b, MenuArg_t text)
{
    switch (b) {
    case 3:
        if (--_EditMenu_iCycleIndex < 0) {
            _EditMenu_iCycleIndex = _EditMenu_iCycleCount - 1;
        }
        break;
    case 1:
        if (++_EditMenu_iCycleIndex >= _EditMenu_iCycleCount) {
            _EditMenu_iCycleIndex = 0;
        }
        break;
    case -1:
        _EditMenu_iCycleIndex = 0;
        _EditMenu_iCycleCount = 0;
        _EditMenu_pEditor->GetCycle(a, &_EditMenu_iCycleIndex, &_EditMenu_iCycleCount);
        _EditMenu_iCycleStart = _EditMenu_iCycleIndex;
        break;
    }
    _EditMenu_pEditor->GetCycleText(a, _EditMenu_iCycleIndex, text);
}

void EditMenuBeginSlider(int a, int b, int c, int *pOut, MenuArg_t text0, MenuArg_t text1,
                 MenuArg_t text2)
{
    int x;
    int y;

    _EditMenu_pEditor->BeginSlider(a, b, c, &x, &y, text0, text1, text2);
    *pOut = y;
    _EditMenu_iSliderStart = y;
    _EditMenu_iSliderValue = y;
    _EditMenu_iSliderMin = x;
}

int EditMenuMoveSlider(int a, int b, MenuArg_t text)
{
    int result = _EditMenu_pEditor->MoveSlider(a, b, text);

    if (result) {
        _EditMenu_iSliderValue = b;
    }
    return result;
}

void EditMenuEndSlider(int a)
{
    _EditMenu_pEditor->EndSlider(a, 0, _EditMenu_iSliderValue);
    if (_EditMenu_iSliderStart != _EditMenu_iSliderValue) {
        _EditMenu_bChanged = 1;
    }
}

void EditMenuCancelSlider(int a)
{
    _EditMenu_pEditor->EndSlider(a, 1, -1);
}

void EditMenuGetText(int a, int *pResult, MenuArg_t text)
{
    _EditMenu_pEditor->GetText(a, pResult, text);
}

void EditMenuSetText(int a, MenuArg_t text)
{
    _EditMenu_pEditor->SetText(a, text);
    _EditMenu_bChanged = 1;
}

void EditMenuGetTeamColors(int a, int *pOut)
{
    unsigned char indices[3];
    PaletteColor color;

    EditMenuGetColorIndices(indices);
    DbColPalGetPrimaryColor(indices[0], &color);
    *pOut++ = color.r;
    *pOut++ = color.g;
    *pOut++ = color.b;
    DbColPalGetPrimaryColor(indices[1], &color);
    *pOut++ = color.r;
    *pOut++ = color.g;
    *pOut++ = color.b;
    DbColPalGetPrimaryColor(indices[2], &color);
    *pOut++ = color.r;
    *pOut++ = color.g;
    *pOut = color.b;
}

void EditMenuGetColorIndices(unsigned char *pOut)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (_EditMenu_aColorPick[i]) {
            pOut[i] = ColorPickGetSelected();
        } else {
            pOut[i] = _EditMenu_aTeamColors[i];
        }
    }
}

void EditMenuGetGearNames(int *pCount, MenuArg_t *pList)
{
    int i;

    *pCount = 0;
    for (i = 0; i < 10; i++) {
        strnzcpy(pList[i].pParams->mpText, "", pList[i].pParams->mLength);
    }
    if (CreatePlayerGetPlayerId() != 0x7FFF) {
        PlayerGear_t info;
        DbCursor query;
        char buffer[32];
        int type;
        int seen;

        fn_8007BA48(&query);
        seen = 0;
        PlayerDbSeekId(EditMenuGetPlayerCursor(), CreatePlayerGetPlayerId(), 0);
        fn_800817CC(EditMenuGetPlayerCursor(), &info);
        for (i = 0; i < 14; i++) {
            type = fn_8007BF14(i);
            fn_8007BB84(&query, type, info.mValues[i], 0);
            if (fn_8007C690(&query, 0)) {
                if ((type != 6 || !seen) && *pCount < 10) {
                    fn_8007BE20(&query, buffer, 32);
                    strnzcpy(pList[*pCount].pParams->mpText, buffer, pList[*pCount].pParams->mLength);
                    (*pCount)++;
                }
                if (type == 6) {
                    seen = 1;
                }
            }
        }
        fn_8007BB04(&query);
    }
}

void EditMenuGetOwner(int a, int *pFlag, MenuArg_t text, int *pOut)
{
    MenuText_t *pParams = text.pParams;

    *pFlag = _EditMenu_bHasOwner;
    if (_EditMenu_bHasOwner) {
        strnzcpy(pParams->mpText, _EditMenu_szOwnerName, pParams->mLength);
    } else {
        strnzcpy(pParams->mpText, "", pParams->mLength);
    }
    *pOut = _EditMenu_bOwnerFlag;
}

unsigned char EditMenuGetRatingFlag(int index)
{
    return _EditMenu_aRatingFlags[index];
}

void EditMenuSaveTeam(void)
{
    if (EditMenuIsStoryTeam()) {
        if (EditMenuGetMode() == 3) {
            fn_8018EF6C(_EditMenu_iTeam);
            StorySetNew(_EditMenu_cTeamSlot, 0);
        }
        StorySetDevPoints(_EditMenu_cTeamSlot, CreatePlayerGetPoints());
        StoryTeamStoreFromStats(_EditMenu_cTeamSlot, _EditMenu_iTeam);
    } else if (EditMenuIsPlayerCopy()) {
        fn_80082534(_EditMenu_iTeam, _EditMenu_cTeamSlot);
    } else if (EditMenuGetMode() != 2) {
        CreateTeamStoreFromStats(_EditMenu_cTeamSlot, _EditMenu_iTeam);
        if (ChalGetDevPoints() != CreatePlayerGetPoints()) {
            ChalSetDevPoints(CreatePlayerGetPoints());
        }
    }
    if (EditMenuIsStoryTeam() || EditMenuIsCreateTeam()) {
        gFMCAPPORT.Start();
    }
}

void EditMenuCancel(void)
{
    EditMenuRestoreTeam();
}

}

void MenuItemEditor::GetColor(int a, int *pResult)
{
}

void MenuItemEditor::EndColor(int a, int b, int c)
{
}

void MenuItemEditor::GetCycle(int a, int *pB, int *pC)
{
}

void MenuItemEditor::EndCycle(int a, int b, int c)
{
}

void MenuItemEditor::GetCycleText(int a, int b, MenuArg_t text)
{
}

void MenuItemEditor::BeginSlider(int a, int b, int c, int *pD, int *pE, MenuArg_t textF, MenuArg_t textG,
                                 MenuArg_t textH)
{
}

int MenuItemEditor::MoveSlider(int a, int b, MenuArg_t text)
{
    return 0;
}

void MenuItemEditor::EndSlider(int a, int b, int c)
{
}

void MenuItemEditor::GetText(int a, int *pResult, MenuArg_t text)
{
}

void MenuItemEditor::SetText(int a, MenuArg_t text)
{
}

void EditTopMenu::Enter(int a, int *pCount, int *pValue)
{
    MenuListScreen::Enter(a, pCount, pValue);
    EditMenuSetView(0x70);
}

int EditTopMenu::Leave(int a, int b, void **ppResult)
{
    int result;

    MenuListScreen::Leave(a, b, ppResult);
    result = -1;
    if (b == 0) {
        result = 1;
        switch (a) {
        case 0:
            *ppResult = CreateTeamGetMenu();
            break;
        case 1:
            *ppResult = CreatePlayerGetMenu();
            break;
        }
    }
    return result;
}

void MenuListScreen::Enter(int a, int *pCount, int *pValue)
{
    *pCount = GetEntryCount();
}

int MenuListScreen::Leave(int a, int b, void **ppResult)
{
    EditMenuSetItemName("");
    *ppResult = 0;
    return -1;
}

void MenuListScreen::Highlight(int id)
{
    MenuEntry_t *pEntries = GetEntries();
    int count = GetEntryCount();
    int i;

    for (i = 0; i < count; i++) {
        if (pEntries[i].mId == id) {
            break;
        }
    }
    if (i >= count) {
        i = 0;
    }
    EditMenuSetItemName(pEntries[i].mName);
}

void MenuListScreen::GetItemId(int index, int *pId)
{
    *pId = GetEntries()[index].mId;
}

void MenuListScreen::GetItem(int id, MenuEntry_t *pEntry)
{
    MenuEntry_t *pEntries = GetEntries();
    int count = GetEntryCount();
    int i;

    for (i = 0; i < count; i++) {
        if (pEntries[i].mId == id) {
            break;
        }
    }
    if (i >= count) {
        i = 0;
    }
    pEntry->mUnknown30 = pEntries[i].mUnknown30;
    pEntry->mUnknown4 = pEntries[i].mUnknown4;
    pEntry->mUnknown32 = pEntries[i].mUnknown32 | 0xC0000;
    pEntry->mId = pEntries[i].mId;
    pEntry->mUnknown36 = i;
    pEntry->mUnknown40 = 0;
    strnzcpy(pEntry->mName, pEntries[i].mName, 22);
}

extern "C" {

DbCursor *EditMenuGetTeamCursor(void)
{
    return &gEditMenuTeamCursor;
}

Object_8008044C *EditMenuGetPlayerCursor(void)
{
    return &gEditMenuPlayerCursor;
}

void EditMenuSetHeading(const char *pText)
{
    strnzcpy(_EditMenu_State.mName0, pText, 21);
}

void EditMenuSetItemName(const char *pText)
{
    strnzcpy(_EditMenu_State.mName1, pText, 21);
}

void EditMenuSetName(char *pText)
{
    strnzcpy(_EditMenu_State.mName2, pText, 21);
}

void EditMenuSetPosition(int a)
{
    _EditMenu_State.mUnknown64 = a;
}

void EditMenuSetHeight(int a)
{
    _EditMenu_State.mUnknown68 = a;
}

void EditMenuSetWeight(int a)
{
    _EditMenu_State.mUnknown72 = a;
}

void EditMenuSetLogo(int a, int b)
{
    _EditMenu_State.mUnknown80 = a;
    _EditMenu_State.mUnknown84 = b;
}

void EditMenuSetLogoHandle(int a)
{
    _EditMenu_State.mUnknown88 = TeamLogoGetHandle(a);
}

void EditMenuSetLogoFlag(unsigned char a)
{
    _EditMenu_State.mUnknown92 = a;
}

void EditMenuLoadRatings(void)
{
    PlayerGetGearRatings(EditMenuGetPlayerCursor(), _EditMenu_State.mValues);
}

void EditMenuClearRatings(void)
{
    int i;

    for (i = 9; i >= 0; i--) {
        _EditMenu_State.mValues[i] = 0;
    }
}

void EditMenuAddGearRatings(PlayerGear_t *pInfo)
{
    PlayerAddGearRatings(EditMenuGetPlayerCursor(), pInfo, _EditMenu_State.mValues);
}

void EditMenuSetRating(int index, int delta)
{
    short values[10];
    int value;

    PlayerGetGearBonuses(EditMenuGetPlayerCursor(), values);
    value = values[index] + delta;
    _EditMenu_State.mValues[index] = value > 0 ? (value > 99 ? 99 : value) : 1;
}

void EditMenuSetRatingFlag(int a, unsigned char value)
{
    _EditMenu_aRatingFlags[EditMenuGetRatingSlot(a)] = value;
}

void EditMenuClearRatingFlags(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        _EditMenu_aRatingFlags[i] = 0;
    }
}

void EditMenuSendOwnerText(const char *pText)
{
    static MenuText_t sText;

    if (pText) {
        if (strncmp(pText, _EditMenu_szOwnerText, 28)) {
            MenuArg_t args[2];

            strncpy(_EditMenu_szOwnerText, pText, 28);
            args[0].i = 1;
            sText.mUnknown0 = 0;
            sText.mLength = 27;
            sText.mpText = _EditMenu_szOwnerText;
            args[1].pParams = &sText;
            fn_8021D7B8(gUISMainInfo, 0x80000088, 2, args);
        }
    } else {
        MenuArg_t args[2];

        strncpy(_EditMenu_szOwnerText, "", 28);
        args[0].i = 0;
        sText.mUnknown0 = 0;
        sText.mLength = 27;
        sText.mpText = _EditMenu_szOwnerText;
        args[1].pParams = &sText;
        fn_8021D7B8(gUISMainInfo, 0x80000088, 2, args);
    }
}

void EditMenuSetOwner(int a)
{
    int row;

    _EditMenu_bHasOwner = 1;
    row = DbCursorGetRow((DbCursor *)EditMenuGetPlayerCursor());
    PlayerDbSeekId(EditMenuGetPlayerCursor(), a, 0);
    PlayerDbGetShortName(EditMenuGetPlayerCursor(), _EditMenu_szOwnerName, 28);
    DbCursorSeek((DbCursor *)EditMenuGetPlayerCursor(), row);
    EditMenuSendOwnerText(_EditMenu_szOwnerName);
}

void EditMenuClearOwner(void)
{
    _EditMenu_bHasOwner = 0;
    strnzcpy(_EditMenu_szOwnerName, "", 28);
    EditMenuSendOwnerText(0);
}

void EditMenuSetOwnerFlag(unsigned char a)
{
    _EditMenu_bOwnerFlag = a;
}

void EditMenuSetAttributeMode(unsigned char a)
{
    _EditMenu_bAttributeMode = a;
}

void EditMenuSetItemLogo(int a)
{
    _EditMenu_State.mUnknown96 = TeamLogoGetHandle(a);
}

int EditMenuGetSliderValue(void)
{
    return _EditMenu_iSliderValue;
}

int EditMenuGetSliderStart(void)
{
    return _EditMenu_iSliderStart;
}

int EditMenuGetSliderMin(void)
{
    return _EditMenu_iSliderMin;
}

int EditMenuGetSlotRating(int index)
{
    return _EditMenu_aRatingSlots[index];
}

void EditMenuClearColorPick(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        _EditMenu_aColorPick[i] = 0;
    }
}

void EditMenuSetColorPick(int index)
{
    EditMenuClearColorPick();
    _EditMenu_aColorPick[index] = 1;
}

void EditMenuSetChanged(void)
{
    _EditMenu_bChanged = 1;
}

void EditMenuGetPlayerName(char *pText, int size)
{
    void *pFont = UIGLibraryGetGlobal(1);
    unsigned int limit;
    unsigned int width;

    PlayerDbGetFullName(EditMenuGetPlayerCursor(), pText, size);
    limit = UIGFontGetStringWidth(pFont, 2, 3, "WWWWWWWWWW");
    width = UIGFontGetStringWidth(pFont, 2, 3, pText);
    if (strlen(pText) > 20 || width > limit) {
        PlayerDbGetShortName(EditMenuGetPlayerCursor(), pText, size);
    }
}

int EditMenuGetTeamSlot(void)
{
    return _EditMenu_cTeamSlot;
}

int EditMenuGetTeam(void)
{
    return _EditMenu_iTeam;
}

void EditMenuBegin(int mode, int value)
{
    Desc_8008044C desc;
    int status;

    _EditMenu_iMode = mode;
    _EditMenu_cTeamSlot = fn_8022F384(fn_8022F4BC());
    _EditMenu_bActive = 1;
    _EditMenu_bPending = 0;
    _EditMenu_bChanged = 0;
    switch (_EditMenu_iMode) {
    case 4:
        _EditMenu_iTeam = StoryTeamLoadToStats(_EditMenu_cTeamSlot, 0, 0, &status);
        break;
    case 3:
        _EditMenu_iTeam = StoryStartNew();
        EditMenuSetChanged();
        break;
    case 5:
        fn_80082558(value, _EditMenu_cTeamSlot);
        _EditMenu_iTeam = value;
        break;
    case 0:
        _EditMenu_iTeam = CreateTeamInsertNew(_EditMenu_cTeamSlot);
        EditMenuSetChanged();
        break;
    case 2:
        _EditMenu_iTeam = fn_8008775C();
        break;
    default:
        if (CreateTeamExists(_EditMenu_cTeamSlot)) {
            _EditMenu_iTeam = CreateTeamLoadToStats(_EditMenu_cTeamSlot, 0);
        }
        break;
    }
    fn_80083E40(&gEditMenuTeamCursor, 0, 0x54415453);
    fn_80084034(&gEditMenuTeamCursor, _EditMenu_iTeam, 0);
    desc.mUnknown8 = _EditMenu_iTeam;
    desc.mUnknown4 = 1;
    desc.mUnknown0 = 1;
    fn_8008044C(&gEditMenuPlayerCursor, &desc, 0x54415453);
    UIGLibraryGetGlobal(1);
    CreatePlayerResetOriginals();
}

void EditMenuEnd(void)
{
    if (_EditMenu_bActive) {
        fn_80083F68(&gEditMenuTeamCursor);
        fn_8008056C(&gEditMenuPlayerCursor);
        if (EditMenuIsStoryTeam()) {
            fn_8018C48C(0x54415453);
            if (MsgGameGetSetupState() == 1 && EditMenuGetMode() == 3) {
                fn_8005F29C();
            }
        } else if (!EditMenuIsPlayerCopy()) {
            if (_EditMenu_iMode == 2) {
                fn_80087880(_EditMenu_iTeam);
            } else {
                fn_8018C48C(0x54415453);
            }
        }
        ChalCloseCursors();
        _EditMenu_iMode = 6;
        _EditMenu_bActive = 0;
    }
    _EditMenu_bSaving = 0;
}

int EditMenuIsOpen(void)
{
    int result = 0;

    if (_EditMenu_bActive) {
        result = _EditMenu_bSaving == 0;
    }
    return result;
}

void EditMenuSetView(int a)
{
    _EditMenu_iView = a;
}

void EditMenuShowPlayers(void)
{
    FEPlyrShow();
    FEPlyrSetPairMode(1, 0, 1);
    FEPlyrResetPose(0);
    FEPlyrResetPose(1);
    FEPlyrPlayAnim(0, 0xD6, 0);
    FEPlyrPlayAnim(1, 0xD6, 0);
    FEPlyrSetPose(0, 2);
    FEPlyrSetPose(1, 2);
    FEPlyrSetPosition(0, EditMenuGetPlayerLayout()->mUnknown0, EditMenuGetPlayerLayout()->mUnknown4, EditMenuGetPlayerLayout()->mUnknown8);
    FEPlyrSetPosition(1, EditMenuGetPlayerLayout()->mUnknown0, EditMenuGetPlayerLayout()->mUnknown4, EditMenuGetPlayerLayout()->mUnknown8);
    FEPlyrSetScale(0, EditMenuGetPlayerLayout()->mUnknown16);
    FEPlyrSetScale(1, EditMenuGetPlayerLayout()->mUnknown16);
    FEPlyrSetPriority(0, EditMenuGetPlayerLayout()->mUnknown20);
    FEPlyrSetPriority(1, EditMenuGetPlayerLayout()->mUnknown20);
    FEPlyrSetAngle(0, 0.0f);
    FEPlyrSetAngle(1, 0.0f);
}

void EditMenuHidePlayers(void)
{
    FEPlyrSetPairMode(0, 0, 1);
    FEPlyrHide();
}

PlayerLayout_t *EditMenuGetPlayerLayout(void)
{
    return &_EditMenu_PlayerLayout;
}

void EditMenuMovePlayers(const PlayerLayout_t *pOffset)
{
    if (!pOffset) {
        FEPlyrMoveTo(0, EditMenuGetPlayerLayout()->mUnknown0, EditMenuGetPlayerLayout()->mUnknown4, EditMenuGetPlayerLayout()->mUnknown8,
                    EditMenuGetPlayerLayout()->mUnknown12, EditMenuGetPlayerLayout()->mUnknown16, EditMenuGetPlayerLayout()->mUnknown24);
        FEPlyrMoveTo(1, EditMenuGetPlayerLayout()->mUnknown0, EditMenuGetPlayerLayout()->mUnknown4, EditMenuGetPlayerLayout()->mUnknown8,
                    EditMenuGetPlayerLayout()->mUnknown12, EditMenuGetPlayerLayout()->mUnknown16, EditMenuGetPlayerLayout()->mUnknown24);
        FEPlyrSetPose(0, 2);
        FEPlyrSetPose(1, 2);
    } else {
        FEPlyrMoveTo(0, EditMenuGetPlayerLayout()->mUnknown0 + pOffset->mUnknown0,
                    EditMenuGetPlayerLayout()->mUnknown4 + pOffset->mUnknown4,
                    EditMenuGetPlayerLayout()->mUnknown8 + pOffset->mUnknown8,
                    EditMenuGetPlayerLayout()->mUnknown12 + pOffset->mUnknown12,
                    EditMenuGetPlayerLayout()->mUnknown16 + pOffset->mUnknown16, pOffset->mUnknown24);
        FEPlyrMoveTo(1, EditMenuGetPlayerLayout()->mUnknown0 + pOffset->mUnknown0,
                    EditMenuGetPlayerLayout()->mUnknown4 + pOffset->mUnknown4,
                    EditMenuGetPlayerLayout()->mUnknown8 + pOffset->mUnknown8,
                    EditMenuGetPlayerLayout()->mUnknown12 + pOffset->mUnknown12,
                    EditMenuGetPlayerLayout()->mUnknown16 + pOffset->mUnknown16, pOffset->mUnknown24);
    }
}

void EditMenuRequest(int mode, int value)
{
    _EditMenu_iMode = mode;
    _EditMenu_iTeam = value;
    _EditMenu_bPending = 1;
}

void EditMenuCancelRequest(void)
{
    _EditMenu_bPending = 0;
    _EditMenu_iMode = 6;
}

int EditMenuGetMode(void)
{
    return _EditMenu_iMode;
}

int EditMenuIsStoryTeam(void)
{
    return _EditMenu_iMode == 3 || _EditMenu_iMode == 4;
}

int EditMenuIsCreateTeam(void)
{
    return _EditMenu_iMode == 0 || _EditMenu_iMode == 1;
}

int EditMenuIsPlayerCopy(void)
{
    return _EditMenu_iMode == 5;
}

void EditMenuSetPresetPending(void)
{
    _EditMenu_bPresetPending = 1;
}

}

extern "C" {

int EditMenuHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, MenuArg_t *pResult)
{
    switch (id) {
    case 0x1E:
        EditMenuOpen(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0xC6:
        EditMenuStart(pArgs[0].i);
        break;
    case 0xC7:
        EditMenuClose(pArgs[0].i);
        break;
    case 0x20:
        EditMenuChoose(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x1F:
        EditMenuGetItemId(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x16:
        EditMenuHighlight(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3], pArgs[4]);
        break;
    case 0x94:
        EditMenuGetLogo(pArgs[0].i, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x95:
        EditMenuGetPlayerInfo(pArgs[0].i, (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4), pArgs[2].pi, pArgs[3], pArgs[4],
                    pArgs[5]);
        break;
    case 0x15:
        EditMenuGetItem(pArgs[0].i, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi, pArgs[4], pArgs[5].pi, pArgs[6].pi,
                    pArgs[7].pi, pArgs[8].pi);
        break;
    case 0x138:
        fn_8000EBA4(pArgs[0].i);
        break;
    case 0x17:
        EditMenuGetColor(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x18:
        EditMenuEndColor(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0xCA:
        EditMenuCancelColor(pArgs[0].i);
        break;
    case 0x19:
        EditMenuCycle(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x1A:
        EditMenuEndCycle(pArgs[0].i);
        break;
    case 0xC8:
        EditMenuCancelCycle(pArgs[0].i);
        break;
    case 0x1C:
        EditMenuBeginSlider(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].pi, pArgs[4], pArgs[5], pArgs[6]);
        break;
    case 0x1D:
        pResult->i = EditMenuMoveSlider(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x1B:
        EditMenuEndSlider(pArgs[0].i);
        break;
    case 0xC9:
        EditMenuCancelSlider(pArgs[0].i);
        break;
    case 0x9D:
        EditMenuGetText(pArgs[0].i, pArgs[1].pi, pArgs[2]);
        break;
    case 0x9E:
        EditMenuSetText(pArgs[0].i, pArgs[1]);
        break;
    case 0xCC:
        pResult->i = FEPlyrUpdateMoves();
        break;
    case 0x128:
        if (_EditMenu_iView == 0x384 || _EditMenu_iView == 0x71) {
            pResult->f = FEPlyrSpin(pArgs[0].f);
        }
        break;
    case 0x10A:
        switch (_EditMenu_iMode) {
        case 2:
            pResult->i = fn_8000EB5C();
            *pArgs[0].pi = fn_8000EB80();
            break;
        case 5:
            pResult->i = -1;
            *pArgs[0].pi = 0;
            break;
        default:
            pResult->i = CreatePlayerGetPoints() - CreatePlayerGetPendingCost();
            *pArgs[0].pi = CreatePlayerGetNextCost();
            break;
        }
        break;
    case 0x115: {
        int index = pArgs[1].pi[0] + 1;

        EditMenuGetTeamColors(pArgs[0].i, &pArgs[1].pi[index]);
        break;
    }
    case 0x117: {
        int index = pArgs[1].pi[0] + 1;

        EditMenuGetGearNames(pArgs[0].pi, (MenuArg_t *)&pArgs[1].pi[index]);
        break;
    }
    case 0x116:
        EditMenuGetOwner(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3].pi);
        break;
    case 0x118:
        pResult->i = EditMenuGetRatingFlag(pArgs[0].i);
        break;
    case 0x11A:
        EditMenuSaveTeam();
        break;
    case 0x124:
        pResult->i = 0;
        if (_EditMenu_bActive) {
            if (_EditMenu_iView == 0x384) {
                pResult->i = fn_8000EC14();
            } else {
                pResult->i = _EditMenu_bChanged;
            }
        }
        break;
    case 0x18F:
        pResult->i = 0;
        if (_EditMenu_iMode == 0 || _EditMenu_iMode == 3) {
            strnzcpy(pArgs[0].pParams->mpText, "Exit and lose changes?", pArgs[0].pParams->mLength);
        } else {
            strnzcpy(pArgs[0].pParams->mpText, "", pArgs[0].pParams->mLength);
            pResult->i = 1;
        }
        break;
    case 0x126:
        if (pArgs[0].i == 7) {
            pResult->i = StoryTeamExists(fn_8022F384(fn_8022F4BC()));
        } else if (pArgs[0].i == 6) {
            pResult->i = CreateTeamExists(fn_8022F384(fn_8022F4BC()));
        } else if (pArgs[0].i == 8) {
            pResult->i = GauntletGetCurrentTeam(fn_8022F384(fn_8022F4BC())) != 0x3FF;
        }
        break;
    case 0x125:
        if (pArgs[0].i == 7) {
            StoryTeamClear();
        } else if (pArgs[0].i == 6) {
            int team;

            CreateTeamClear();
            team = fn_80186B38(fn_8022F4BC());
            if (StoryTeamExists(team)) {
                StorySetIndexedFlag(team, 1, 0);
            }
        } else if (pArgs[0].i == 8) {
            GauntletReset(fn_8022F384(fn_8022F4BC()));
        }
        break;
    case 0xF0:
        pResult->i = _EditMenu_bAttributeMode;
        break;
    case 0xF1:
        EditMenuCancel();
        break;
    case 0x12F:
        FEPlyrSetScale(0, 0.0f);
        FEPlyrSetScale(1, 0.0f);
        break;
    case 0x92:
        pResult->i = _EditMenu_iView;
        break;
    case 0x197:
        MemCardFilesStoreChecksum(2, fn_8022F384(fn_8022F4BC()));
        break;
    case 0x19A:
        pResult->i = _EditMenu_bPresetPending;
        break;
    case 0x19B:
        CreatePlayerApplyPreset(pArgs[0].i);
        _EditMenu_bPresetPending = 0;
        break;
    case 0x19E:
        *pArgs[0].pi = -1;
        *pArgs[1].pi = -1;
        if (_EditMenu_iMode == 2) {
            *pArgs[0].pi = fn_8000EC38();
        }
        break;
    case 0x19F:
        pResult->i = EditMenuIsStoryTeam();
        break;
    case 0x127:
        break;
    default:
        return 0;
    }
    return 1;
}

}

DbCursor gEditMenuTeamCursor;
Object_8008044C gEditMenuPlayerCursor;
MenuItemEditor gEditMenuDefaultEditor;

static inline EditTopMenu *_EditMenuGetTopMenu()
{
    static EditTopMenu sInstance;
    return &sInstance;
}
