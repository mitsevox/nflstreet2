/* UI resource lists: the uis_*.dat packages loaded for the front end and
   for in-game screens, with the team logos. */
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/DbCursor.h"
#include "game/GameInfo.h"

struct UISResListDesc {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
int MainFEGroupIsFirstStart(void *p);
int DbCursorGetValue(DbCursor *pObject, int key);
void fn_80083E1C(DbCursor *pObject, int a);
void *UIGLibraryInit(UISResListDesc *pDesc);
void UIGLibrarySetDevice(void *pList, int index, const char *pName, int a, int b);
void UIGLibrarySet(void *pList, int index, const char *pName, int a, int b, int c);
int UIGLibraryPreloadItem(void *pList, int index, int value);
void UIGLibrarySetGlobal(int index, void *p);
void *UIGLibraryGetGlobal(int index);
}

extern char lbl_802EBE68[];
extern char lbl_802EBE88[];
extern char lbl_802EBE98[];
extern char lbl_802EBEA8[];
extern char lbl_802EBEB8[];
extern char lbl_802EBEC8[];
extern char lbl_802EBED8[];
extern char lbl_802EBEE8[];
extern char lbl_802EBEF8[];
extern char lbl_802EBF08[];
extern char lbl_802EBF18[];
extern char lbl_802EBF28[];
extern char lbl_802EBF38[];
extern char lbl_802EBF48[];
extern char lbl_802EBF58[];
extern char lbl_802EBF68[];
extern char lbl_802EBF78[];
extern char gMainFEGroup[];

extern "C" {
void UISResListAddCommon(void)
{
    void *pList = UIGLibraryGetGlobal(1);

    UIGLibrarySetDevice(pList, 0, lbl_802EBE68, 1, 16);
    UIGLibrarySet(pList, 3, lbl_802EBEA8, 1, 0, 196);
    UIGLibrarySet(pList, 2, lbl_802EBE98, 1, 0, 200);
    UIGLibrarySet(pList, 5, lbl_802EBEC8, 1, 0, 65);
}

void UISResListAddFrontEnd(void)
{
    int flag = MainFEGroupIsFirstStart(gMainFEGroup);
    void *pList = UIGLibraryGetGlobal(1);

    if (flag == 0) {
        UIGLibrarySet(pList, 1, lbl_802EBE88, 1, 0, 196);
        UIGLibrarySet(pList, 6, lbl_802EBED8, 1, 0, 212);
        UIGLibrarySet(pList, 7, lbl_802EBEE8, 1, 0, 212);
        UIGLibrarySet(pList, 4, lbl_802EBEB8, 1, 0, 84);
    } else {
        UIGLibrarySet(pList, 1, lbl_802EBE88, 1, 0, 132);
        UIGLibrarySet(pList, 6, lbl_802EBED8, 1, 0, 132);
        UIGLibrarySet(pList, 7, lbl_802EBEE8, 1, 0, 132);
        UIGLibrarySet(pList, 4, lbl_802EBEB8, 1, 0, 4);
    }
    UIGLibrarySet(pList, 10, lbl_802EBF08, 1, 0, 52);
    UIGLibrarySet(pList, 8, lbl_802EBEF8, 1, 0, 180);
    UIGLibrarySet(pList, 11, lbl_802EBF18, 1, 0, 132);
    UIGLibrarySet(pList, 12, lbl_802EBF28, 1, 0, 52);
    UIGLibrarySet(pList, 14, lbl_802EBF38, 1, 0, 180);
    UIGLibrarySet(pList, 16, lbl_802EBF48, 1, 0, 180);
    UIGLibrarySet(pList, 17, lbl_802EBF58, 1, 0, 180);
    UIGLibrarySet(pList, 19, lbl_802EBF68, 1, 0, 180);
    UIGLibrarySet(pList, 20, lbl_802EBF78, 1, 0, 180);
}

void UISResListAddInGame(void)
{
    DbCursor cursor;
    int first = 0;
    int second = 0;
    void *pList = UIGLibraryGetGlobal(1);

    UIGLibrarySet(pList, 1, lbl_802EBE88, 1, 0, 180);
    UIGLibrarySet(pList, 6, lbl_802EBED8, 1, 0, 132);
    UIGLibrarySet(pList, 7, lbl_802EBEE8, 1, 0, 132);
    UIGLibrarySet(pList, 4, lbl_802EBEB8, 1, 0, 20);
    UIGLibrarySet(pList, 10, lbl_802EBF08, 1, 0, 52);
    UIGLibrarySet(pList, 8, lbl_802EBEF8, 1, 0, 132);
    UIGLibrarySet(pList, 11, lbl_802EBF18, 1, 0, 196);
    UIGLibrarySet(pList, 12, lbl_802EBF28, 1, 0, 4);
    UIGLibrarySet(pList, 14, lbl_802EBF38, 1, 0, 132);
    UIGLibrarySet(pList, 16, lbl_802EBF48, 1, 0, 132);
    UIGLibrarySet(pList, 17, lbl_802EBF58, 1, 0, 132);
    UIGLibrarySet(pList, 19, lbl_802EBF68, 1, 0, 132);
    UIGLibrarySet(pList, 20, lbl_802EBF78, 1, 0, 132);
    UIGLibraryPreloadItem(pList, 1, 0);
    UIGLibraryPreloadItem(pList, 1, 1);
    UIGLibraryPreloadItem(pList, 1, 2);
    UIGLibraryPreloadItem(pList, 1, 10);
    UIGLibraryPreloadItem(pList, 1, 11);
    UIGLibraryPreloadItem(pList, 1, 12);
    UIGLibraryPreloadItem(pList, 1, 13);
    UIGLibraryPreloadItem(pList, 1, 14);
    UIGLibraryPreloadItem(pList, 1, 15);
    UIGLibraryPreloadItem(pList, 7, 4);
    fn_80083E1C(&cursor, 0);
    if (fn_80084034(&cursor, GameInfoGet(0), 0)) {
        first = DbCursorGetValue(&cursor, 0x4C474C54);
    }
    if (fn_80084034(&cursor, GameInfoGet(1), 0)) {
        second = DbCursorGetValue(&cursor, 0x4C474C54);
    }
    fn_80083F68(&cursor);
    UIGLibraryPreloadItem(pList, 4, first);
    if (second != first) {
        UIGLibraryPreloadItem(pList, 4, second);
    }
    UIGLibraryPreloadItem(pList, 4, 0);
}

void UISResListSetup(void)
{
    UISResListDesc desc;

    desc.mUnknown0 = 21;
    desc.mUnknown4 = 21;
    desc.mUnknown8 = 1;
    UIGLibrarySetGlobal(1, UIGLibraryInit(&desc));
    UISResListAddCommon();
    if (FELoopIsMainFEActive()) {
        UISResListAddFrontEnd();
    } else if (InGameIsPlaying()) {
        UISResListAddInGame();
    }
}
}
