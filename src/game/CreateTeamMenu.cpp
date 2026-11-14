/* Create-a-team menu: the first screen of team creation, where the player
   picks the team's logo, name, three team colours, logo colour and team
   type before going on to create its players. */

#include "game/DbCursor.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

extern "C" {
MenuScreen *CreatePlayerGetMenu(void);
void CreatePlayerSetPoints(int value);
int LogoIsNew(int a);
void LogoClearNew(int a);
void fn_80084180(DbCursor *pObject, int value);
int fn_800841AC(DbCursor *pObject);
int fn_800841D8(DbCursor *pObject);
int fn_80084204(DbCursor *pObject);
void fn_80084230(DbCursor *pObject, unsigned char value);
void fn_8008425C(DbCursor *pObject, unsigned char value);
void fn_80084288(DbCursor *pObject, unsigned char value);
void fn_800842B4(DbCursor *pObject, char *pText, int length);
void fn_80084470(DbCursor *pObject, int value);
DbCursor *fn_80182DBC(void);
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
void CreateTeamCopyStylePlayers(int a, int b, int c);
int CreateTeamGetStylePoints(int a);
}

class CreateTeamMenu : public MenuListScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual void Highlight(int id);
    virtual void GetItem(int index, MenuEntry_t *pEntry);
    virtual MenuItemEditor *GetEditor();
    virtual int GetEntryCount();
    virtual MenuEntry_t *GetEntries();

    char mUnknown4[4];
};

class CreateTeamOptionList : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual void Highlight(int index);
    virtual void GetItemId(int index, int *pId) { *pId = index; }
    virtual void GetItem(int index, MenuEntry_t *pEntry);

    char mUnknown4[4];
    int mUnknown8;
};

class CreateTeamEditor : public MenuItemEditor {
public:
    virtual void GetColor(int a, int *pResult);
    virtual void EndColor(int a, int b, int c);
    virtual void GetText(int a, int *pResult, MenuArg_t text);
    virtual void SetText(int a, MenuArg_t text);

    char mUnknown4[4];
};

static inline CreateTeamOptionList *_CreateTeamGetOptionList();
static inline CreateTeamEditor *_CreateTeamGetEditor();
static inline CreateTeamMenu *_CreateTeamGetMainMenu();

static int _CreateTeam_iTeamType = 0;
static unsigned char _CreateTeam_bNameFromLogo = 0;
static const char *_CreateTeam_aLogoColorNames[2] = {"Team", "Default"};

static MenuEntry_t _CreateTeam_aEntries[8] = {
    {0, 0, "Continue", 1, 0, 0, 0},
    {1, 0, "Logo", 1, 0x31, 0, 0},
    {2, 5, "Team Name", 1, 0x32, 0, 0},
    {3, 3, "Team Color 1", 1, 0x1E, 0, 0},
    {4, 3, "Team Color 2", 1, 0x21, 0, 0},
    {5, 3, "Team Color 3", 1, 0x33, 0, 0},
    {6, 0, "Logo Color", 1, 0x19, 0, 0},
    {7, 0, "Team Type", 1, 0, 0, 0},
};

static int _CreateTeam_aTeamTypeStyles[6] = {4, 0, 1, 2, 3, 5};

static const char *_CreateTeam_aTeamTypeNames[6] = {
    "Balanced", "Rush Offense", "Rush Defense", "Pass Offense", "Pass Defense", "Custom",
};

static DbCursor _CreateTeam_sLogoCursor;

static void _CreateTeamOpen();
static void _CreateTeamClose();

static void _CreateTeamNameFromLogo()
{
    char buffer[24];

    LogoListFind(&_CreateTeam_sLogoCursor, fn_80084158(fn_80182DBC()), 0);
    LogoListGetName(&_CreateTeam_sLogoCursor, buffer, 21);
    fn_800842B4(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
}

void CreateTeamMenu::Enter(int a, int *pCount, int *pValue)
{
    char buffer[24];

    if (a == 1) {
        _CreateTeamOpen();
    }
    MenuListScreen::Enter(a, pCount, pValue);
    fn_80083F88(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
    fn_80182DD4("");
    fn_80182E04("");
}

int CreateTeamMenu::Leave(int a, int b, void **ppResult)
{
    int result = MenuListScreen::Leave(a, b, ppResult);

    if (b != 0) {
        result = -1;
        _CreateTeamClose();
    } else {
        switch (a) {
        case 1:
        case 6:
        case 7:
            result = 1;
            _CreateTeamGetOptionList()->mUnknown8 = a;
            *ppResult = _CreateTeamGetOptionList();
            break;
        case 0:
            switch (fn_80183948()) {
            case 0:
                CreateTeamCopyStylePlayers(fn_80183354(), fn_80183360(), _CreateTeam_aTeamTypeStyles[_CreateTeam_iTeamType]);
                CreatePlayerSetPoints(CreateTeamGetStylePoints(_CreateTeam_aTeamTypeStyles[_CreateTeam_iTeamType]));
                break;
            case 3:
                fn_80183990();
                CreatePlayerSetPoints(250);
                break;
            }
            fn_801832A4();
            result = -3;
            *ppResult = CreatePlayerGetMenu();
            _CreateTeamClose();
            break;
        }
    }
    return result;
}

void CreateTeamMenu::Highlight(int id)
{
    fn_80182DD4(_CreateTeam_aEntries[id].mName);
}

void CreateTeamMenu::GetItem(int index, MenuEntry_t *pEntry)
{
    MenuListScreen::GetItem(index, pEntry);
    if (index == 1) {
        pEntry->mUnknown40 = 0;
        for (int found = DbCursorFirst(&_CreateTeam_sLogoCursor); found; found = DbCursorNext(&_CreateTeam_sLogoCursor)) {
            if (LogoIsNew(LogoListGetId(&_CreateTeam_sLogoCursor) - 45)) {
                pEntry->mUnknown40 = 1;
                break;
            }
        }
    }
}

MenuItemEditor *CreateTeamMenu::GetEditor()
{
    return _CreateTeamGetEditor();
}

int CreateTeamMenu::GetEntryCount()
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

MenuEntry_t *CreateTeamMenu::GetEntries()
{
    MenuEntry_t *pEntries;

    switch (fn_80183948()) {
    case 0:
    case 3:
        pEntries = &_CreateTeam_aEntries[0];
        break;
    default:
        pEntries = &_CreateTeam_aEntries[1];
        break;
    }
    return pEntries;
}

void CreateTeamOptionList::Enter(int a, int *pCount, int *pValue)
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
        LogoListFind(&_CreateTeam_sLogoCursor, fn_80084158(fn_80182DBC()), pValue);
        *pCount = DbCursorGetRowCount(&_CreateTeam_sLogoCursor);
        break;
    case 7:
        *pValue = _CreateTeam_iTeamType;
        *pCount = 6;
        break;
    }
}

int CreateTeamOptionList::Leave(int a, int b, void **ppResult)
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
            DbCursorSeek(&_CreateTeam_sLogoCursor, a);
            value = LogoListGetId(&_CreateTeam_sLogoCursor);
            LogoClearNew(value - 45);
            fn_80084180(fn_80182DBC(), value);
            if (_CreateTeam_bNameFromLogo) {
                _CreateTeamNameFromLogo();
            }
            break;
        case 7:
            _CreateTeam_iTeamType = a;
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

void CreateTeamOptionList::Highlight(int index)
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
        DbCursorSeek(&_CreateTeam_sLogoCursor, index);
        fn_80182E88(4, LogoListGetId(&_CreateTeam_sLogoCursor));
        break;
    case 7:
        break;
    }
}

void CreateTeamOptionList::GetItem(int index, MenuEntry_t *pEntry)
{
    char buffer[24];

    switch (mUnknown8) {
    case 6:
        fn_801C3284(pEntry->mName, _CreateTeam_aLogoColorNames[index], 22);
        break;
    case 1:
        DbCursorSeek(&_CreateTeam_sLogoCursor, index);
        pEntry->mUnknown40 = LogoIsNew(LogoListGetId(&_CreateTeam_sLogoCursor) - 45);
        LogoListGetName(&_CreateTeam_sLogoCursor, buffer, 21);
        fn_801C3284(pEntry->mName, buffer, 22);
        break;
    case 7:
        fn_801C3284(pEntry->mName, _CreateTeam_aTeamTypeNames[index], 22);
        break;
    }
}

void CreateTeamEditor::GetColor(int a, int *pResult)
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

void CreateTeamEditor::EndColor(int a, int b, int c)
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

void CreateTeamEditor::GetText(int a, int *pResult, MenuArg_t text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[24];

    if (a == 2) {
        fn_80083F88(fn_80182DBC(), buffer, 18);
        fn_801C3284(pParams->mpText, buffer, pParams->mLength + 1);
        *pResult = 3;
    }
}

void CreateTeamEditor::SetText(int a, MenuArg_t text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[24];

    if (a == 2) {
        fn_800842B4(fn_80182DBC(), pParams->mpText, pParams->mLength);
        fn_80083F88(fn_80182DBC(), buffer, 18);
        fn_80182E34(buffer);
        _CreateTeam_bNameFromLogo = 0;
    }
}

static void _CreateTeamOpen()
{
    LogoListOpen(&_CreateTeam_sLogoCursor);
    fn_801835C0(0x70);
    fn_8018324C();
    _CreateTeam_iTeamType = 0;
    _CreateTeam_bNameFromLogo = 0;
    if (fn_80183948() == 0 || fn_80183948() == 3) {
        _CreateTeamNameFromLogo();
        _CreateTeam_bNameFromLogo = 1;
    }
}

static void _CreateTeamClose()
{
    LogoListClose(&_CreateTeam_sLogoCursor);
}

extern "C" MenuScreen *CreateTeamGetMenu()
{
    return _CreateTeamGetMainMenu();
}

static inline CreateTeamOptionList *_CreateTeamGetOptionList()
{
    static CreateTeamOptionList sInstance;
    return &sInstance;
}

static inline CreateTeamEditor *_CreateTeamGetEditor()
{
    static CreateTeamEditor sInstance;
    return &sInstance;
}

static inline CreateTeamMenu *_CreateTeamGetMainMenu()
{
    static CreateTeamMenu sInstance;
    return &sInstance;
}
