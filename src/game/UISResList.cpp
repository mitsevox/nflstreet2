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
void TeamDbOpenQuery(DbCursor *pObject, int a);
void *UIGLibraryInit(UISResListDesc *pDesc);
void UIGLibrarySetDevice(void *pList, int index, const char *pName, int a, int b);
void UIGLibrarySet(void *pList, int index, const char *pName, int a, int b, int c);
int UIGLibraryPreloadItem(void *pList, int index, int value);
void UIGLibrarySetGlobal(int index, void *p);
void *UIGLibraryGetGlobal(int index);
}

extern char File_UisLibsStr[];
extern char File_UisComnStr[];
extern char lbl_802EBE98[];
extern char File_UisButtStr[];
extern char File_UisTmloStr[];
extern char File_UisClstStr[];
extern char File_UisCtrlStr[];
extern char File_UisFronStr[];
extern char File_UisFselStr[];
extern char File_UisPortStr[];
extern char File_UisIngmStr[];
extern char File_UisCrtmStr[];
extern char File_UisChalStr[];
extern char File_UisMoviStr[];
extern char File_UisMpicStr[];
extern char File_UisCmapStr[];
extern char File_UisPostStr[];
extern char gMainFEGroup[];

extern "C" {
void UISResListAddCommon(void)
{
    void *pList = UIGLibraryGetGlobal(1);

    UIGLibrarySetDevice(pList, 0, File_UisLibsStr, 1, 16);
    UIGLibrarySet(pList, 3, File_UisButtStr, 1, 0, 196);
    UIGLibrarySet(pList, 2, lbl_802EBE98, 1, 0, 200);
    UIGLibrarySet(pList, 5, File_UisClstStr, 1, 0, 65);
}

void UISResListAddFrontEnd(void)
{
    int flag = MainFEGroupIsFirstStart(gMainFEGroup);
    void *pList = UIGLibraryGetGlobal(1);

    if (flag == 0) {
        UIGLibrarySet(pList, 1, File_UisComnStr, 1, 0, 196);
        UIGLibrarySet(pList, 6, File_UisCtrlStr, 1, 0, 212);
        UIGLibrarySet(pList, 7, File_UisFronStr, 1, 0, 212);
        UIGLibrarySet(pList, 4, File_UisTmloStr, 1, 0, 84);
    } else {
        UIGLibrarySet(pList, 1, File_UisComnStr, 1, 0, 132);
        UIGLibrarySet(pList, 6, File_UisCtrlStr, 1, 0, 132);
        UIGLibrarySet(pList, 7, File_UisFronStr, 1, 0, 132);
        UIGLibrarySet(pList, 4, File_UisTmloStr, 1, 0, 4);
    }
    UIGLibrarySet(pList, 10, File_UisPortStr, 1, 0, 52);
    UIGLibrarySet(pList, 8, File_UisFselStr, 1, 0, 180);
    UIGLibrarySet(pList, 11, File_UisIngmStr, 1, 0, 132);
    UIGLibrarySet(pList, 12, File_UisCrtmStr, 1, 0, 52);
    UIGLibrarySet(pList, 14, File_UisChalStr, 1, 0, 180);
    UIGLibrarySet(pList, 16, File_UisMoviStr, 1, 0, 180);
    UIGLibrarySet(pList, 17, File_UisMpicStr, 1, 0, 180);
    UIGLibrarySet(pList, 19, File_UisCmapStr, 1, 0, 180);
    UIGLibrarySet(pList, 20, File_UisPostStr, 1, 0, 180);
}

void UISResListAddInGame(void)
{
    DbCursor cursor;
    int first = 0;
    int second = 0;
    void *pList = UIGLibraryGetGlobal(1);

    UIGLibrarySet(pList, 1, File_UisComnStr, 1, 0, 180);
    UIGLibrarySet(pList, 6, File_UisCtrlStr, 1, 0, 132);
    UIGLibrarySet(pList, 7, File_UisFronStr, 1, 0, 132);
    UIGLibrarySet(pList, 4, File_UisTmloStr, 1, 0, 20);
    UIGLibrarySet(pList, 10, File_UisPortStr, 1, 0, 52);
    UIGLibrarySet(pList, 8, File_UisFselStr, 1, 0, 132);
    UIGLibrarySet(pList, 11, File_UisIngmStr, 1, 0, 196);
    UIGLibrarySet(pList, 12, File_UisCrtmStr, 1, 0, 4);
    UIGLibrarySet(pList, 14, File_UisChalStr, 1, 0, 132);
    UIGLibrarySet(pList, 16, File_UisMoviStr, 1, 0, 132);
    UIGLibrarySet(pList, 17, File_UisMpicStr, 1, 0, 132);
    UIGLibrarySet(pList, 19, File_UisCmapStr, 1, 0, 132);
    UIGLibrarySet(pList, 20, File_UisPostStr, 1, 0, 132);
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
    TeamDbOpenQuery(&cursor, 0);
    if (TeamDbSeekId(&cursor, GameInfoGet(0), 0)) {
        first = DbCursorGetValue(&cursor, 0x4C474C54);
    }
    if (TeamDbSeekId(&cursor, GameInfoGet(1), 0)) {
        second = DbCursorGetValue(&cursor, 0x4C474C54);
    }
    TeamDbClose(&cursor);
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
