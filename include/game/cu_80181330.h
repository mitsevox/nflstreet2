#ifndef GAME_CU_80181330_H
#define GAME_CU_80181330_H

/* Layout returned by fn_80183734; fn_80183740 adds an optional
   offset record of the same layout to it. */
struct Layout_802EA9E0 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    unsigned char mUnknown24;
};

extern "C" void fn_80183740(const Layout_802EA9E0 *pOffset);

/* 44-byte list entry. */
struct MenuEntry_t {
    int mId;
    int mUnknown4;
    char mName[22];
    unsigned char mUnknown30;
    int mUnknown32;
    int mUnknown36;
    unsigned char mUnknown40;
    unsigned char mUnknown41;
};

/* Text argument record reached through MenuArg_t::pParams. */
struct Params_80005284 {
    int mUnknown0;
    int mLength;
    char *mpText;
};

/* One argument or result slot of the message handler fn_8018399C. Text
   arguments are passed on to the MenuItemEditor entries by value. */
union MenuArg_t {
    int i;
    float f;
    int *pi;
    float *pf;
    Params_80005284 *pParams;
};

/* The value controls of the current menu item: a colour pick, a left/right
   choice, a slider and a text field. Each control is opened, read and then
   ended with b 0 to keep the new value or 1 to cancel. The defaults do
   nothing. */
class MenuItemEditor {
public:
    virtual void GetColor(int a, int *pResult);
    virtual void EndColor(int a, int b, int c);
    virtual void GetCycle(int a, int *pB, int *pC);
    virtual void EndCycle(int a, int b, int c);
    virtual void GetCycleText(int a, int b, MenuArg_t text);
    virtual void BeginSlider(int a, int b, int c, int *pD, int *pE, MenuArg_t textF,
                             MenuArg_t textG, MenuArg_t textH);
    virtual int MoveSlider(int a, int b, MenuArg_t text);
    virtual void EndSlider(int a, int b, int c);
    virtual void GetText(int a, int *pResult, MenuArg_t text);
    virtual void SetText(int a, MenuArg_t text);
};

/* One screen of a menu. The menu keeps a stack of screens; the top one is
   entered, gives its items and the item editor, previews the highlighted
   item and, when left, says whether to go back, open another screen or
   start over from one. */
class MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue) = 0;
    virtual int Leave(int a, int b, void **ppResult) = 0;
    virtual void Highlight(int index) = 0;
    virtual void GetItemId(int index, int *pId) = 0;
    virtual void GetItem(int index, MenuEntry_t *pEntry) = 0;
    virtual MenuItemEditor *GetEditor();
};

/* A menu screen whose items are a constant table of MenuEntry_t records
   that the derived screen supplies. */
class MenuListScreen : public MenuScreen {
public:
    virtual void Enter(int a, int *pCount, int *pValue);
    virtual int Leave(int a, int b, void **ppResult);
    virtual void Highlight(int id);
    virtual void GetItemId(int index, int *pId);
    virtual void GetItem(int index, MenuEntry_t *pEntry);
    virtual int GetEntryCount() = 0;
    virtual MenuEntry_t *GetEntries() = 0;
};

#endif
