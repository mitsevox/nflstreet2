#include "game/Class_801CC350.h"
#include "game/Class_801CBC50.h"
#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/GameState.h"
#include "game/ModuleGroup_80033A5C.h"

class MainFEGroup : public Class_801CC350 {
public:
    virtual void vfn_02();
    virtual int vfn_03(int a, int b);
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
    virtual const char *GetName();
};

extern "C" {
void fn_800245DC(void);
void fn_80024628(void);
void fn_80072C90(unsigned int delay, int wait);
void fn_80072D98(unsigned int delay);
void fn_80187C5C(unsigned char a);
int fn_801CBFA0(Class_801CBC50 *pTable);
int fn_801CC4F4(Class_801CC350 *pGroup);
int fn_801CC4FC(Class_801CC350 *pGroup);
}

void fn_80026BA4();

static Record_802CCBAC lbl_802CCBF4[] = {
    { 9, "FE Loading" },
    { 7, "FE FirstStart" },
    { 8, "FE FirstStartComplete" },
    { 10, "FE MainMenu" },
    { 11, "FE Online" },
    { 12, "FE ExitToInGame" },
    { 14, "FE ExitProgram" },
    { -1, 0 },
};

static Record_803EA3A8 lbl_802CCC34[] = {
    { 7, 8 },
    { 8, 9 },
    { 9, 10 },
    { 9, 11 },
    { 10, 12 },
    { 10, 14 },
    { 10, 11 },
    { 11, 9 },
    { 11, 12 },
    { -1, -1 },
};

extern LoadingFE gLoadingFE;
extern FEDLL gFEDLL;
extern UIListener gUIListener;
extern DbColPal gDbColPal;
extern FMMainFEInit gFMMainFEInit;
extern Timg gTimg;
extern FESnd gFESnd;
extern StatGen gStatGen;
extern FEPlyr gFEPlyr;

MainFEGroup lbl_80306B34;

static ModuleDependency lbl_80306B58[] = {
    &gQkl,
    &gGRender,
    &gFEDLL,
    &gUIListener,
    &gGameState,
    &gTimg,
    &gGRand,
    &gGameStateActivate,
    &gFESnd,
    &gUIS,
    0,
};

static ModuleDependency lbl_80306B84[] = {
    &gQkl,
    &gGRender,
    &gFEDLL,
    &gUIListener,
    0,
};

static ModuleDependency lbl_80306B98[] = {
    &gGRender,
    &gLoadingFE,
    &gFEDLL,
    &gQkl,
    &gUIListener,
    &gDbColPal,
    &gFMMainFEInit,
    &gMemAudit,
    &gGameState,
    &gTimg,
    &gGRand,
    &gScrmRule,
    &gFEPlyBk,
    &gAnmsCelebration,
    &gAudmon,
    &gGameStateActivate,
    &gFESnd,
    &gStatGen,
    &gFEPlyr,
    &gRumble,
    &gUIS,
    &gFMCAPPORT,
    0,
};

static ModuleDependency lbl_80306BF4[] = {
    &gGRender,
    &gFEDLL,
    &gFELoop,
    &gUIListener,
    &gDbColPal,
    &gFMMainFEInit,
    &gMemAudit,
    &gGameState,
    &gTimg,
    &gGRand,
    &gScrmRule,
    &gFEPlyBk,
    &gAnmsCelebration,
    &gAudmon,
    &gGameStateActivate,
    &gFESnd,
    &gStatGen,
    &gFEPlyr,
    &gRumble,
    &gUIS,
    &gFMCAPPORT,
    0,
};

static ModuleDependency lbl_80306C4C[] = {
    &gMemAudit,
    &gFEDLL,
    0,
};

static ModuleDependency lbl_80306C58[] = {
    &gFEDLL,
    &gMemAudit,
    0,
};

const char *MainFEGroup::GetName() { return "MainFE Group"; }
Record_802CCBAC *MainFEGroup::vfn_04() { return lbl_802CCBF4; }
Record_803EA3A8 *MainFEGroup::vfn_05() { return lbl_802CCC34; }

ModuleDependency *MainFEGroup::vfn_06(int id)
{
    switch (id) {
    case 7:
        return lbl_80306B58;
    case 8:
        return lbl_80306B84;
    case 9:
        return lbl_80306B98;
    case 10:
        return lbl_80306BF4;
    case 12:
    case 14:
        return lbl_80306C58;
    case 11:
        return lbl_80306C4C;
    default:
        return 0;
    }
}

void MainFEGroup::vfn_02()
{
    Class_803067B0 *p = &lbl_803067B0;

    if (p->fn_801CBE9C(3) == 0) {
        switch (p->fn_801CBEC8(2)) {
        case 7:
            gFELoop.fn_800279AC();
            p->fn_801CBEF4(2, 8);
            break;
        case 8:
            fn_80187C5C(1);
            p->fn_801CBEF4(2, 9);
            break;
        case 9:
            fn_800245DC();
            p->fn_801CBEF4(2, 10);
            break;
        case 10:
            if (!gFELoop.fn_80027C58()) {
                fn_80024628();
                if (!fn_801CBFA0(p)) {
                    p->fn_801CBEF4(2, 14);
                }
            }
            break;
        case 12:
            p->fn_801CBE24(2);
            p->fn_801CBD80(1, -1);
            break;
        case 14:
            fn_80026BA4();
            break;
        }
    }
}

int MainFEGroup::vfn_03(int a, int b)
{
    switch (b) {
    case 12:
        fn_80072C90(250, 1);
        break;
    case 10:
        fn_80072D98(250);
        break;
    }
    return 1;
}

extern "C" int fn_80033124(Class_801CC350 *pGroup) { return fn_801CC4F4(pGroup); }

extern "C" int fn_80033144(Class_801CC350 *pGroup)
{
    int result = 0;
    int stage = fn_801CC4FC(pGroup);

    if (fn_80033124(pGroup) && (stage == 7 || stage == 8)) {
        result = 1;
    }
    return result;
}
