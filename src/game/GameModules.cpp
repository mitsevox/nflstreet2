/* Nine small modules the front-end and in-game groups list: AnimData and
   StaData (each opens a data archive), Audmon, GRand (seeds the game
   random numbers), IGMisc (in-game data archive), MemAudit (records
   which loop is running), Qkl (opens the loop's .qkl file), ScrmRule and
   UIS. Each gives its dependencies and name and has Init and Shutdown. */
#include "game/FELoop.h"
#include "engine/rand.h"
#include "game/InGame.h"
#include "game/ResOpenDevice.h"
#include "game/fn_801FCE10.h"
#include "game/AudmonEvent.h"
#include "game/GameState.h"
#include "game/GameModules.h"
#include "game/MainFEGroup.h"

extern "C" {
extern char lbl_802EBDBC[];
extern char lbl_802EBDF8[];
extern char lbl_802EBFC0[];
extern char lbl_803EB6F0[];
extern char lbl_803EB6F8[];

void fn_800A1A58(void);
void fn_800A1A80(void);
int fn_800A3444(void);
void fn_801779D8(void);
void fn_80177B54(void);
void fn_801787FC(int which, short value);
void fn_8017885C(void);
void UISGameInit(void);
void UISGameShutdown(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
void ResTrackLabel(const char *pText);
int fn_801F2C54(const char *pName, int unknown);
int fn_801F2CD4(const char *pName);
void fn_802371B0(int unknown, int seed);
void fn_8023725C(void);
}

static ModuleDependency _GameModules_aAnimDataDependencies[] = { &gRes, 0 };
AnimData gAnimData;

ModuleDependency *AnimData::GetDependencies() { return _GameModules_aAnimDataDependencies; }
ModuleDependency *AnimData::GetLinks() { return 0; }
const char *AnimData::GetName() { return "AnimData"; }

int AnimData::Init()
{
    mData.mp = ResOpenDevice(lbl_802EBDBC, 44);
    InGameIsPlaying();
    return 1;
}

int AnimData::Shutdown()
{
    ResClose(mData.mp);
    mData.mp = 0;
    return 1;
}

void *AnimData::GetArchive() { return mData.mp; }

static ModuleDependency _GameModules_aAudmonDependencies[] = { &gGameState, 0 };
Audmon gAudmon;

ModuleDependency *Audmon::GetDependencies() { return _GameModules_aAudmonDependencies; }
ModuleDependency *Audmon::GetLinks() { return 0; }
const char *Audmon::GetName() { return "Audmon"; }

int Audmon::Init()
{
    AudmonEventInit();
    return 1;
}

int Audmon::Shutdown()
{
    AudmonEventShutdown();
    return 1;
}

static ModuleDependency _GameModules_aGRandDependencies[] = { &gGameState, 0 };
GRand gGRand;

ModuleDependency *GRand::GetDependencies() { return _GameModules_aGRandDependencies; }
ModuleDependency *GRand::GetLinks() { return 0; }
const char *GRand::GetName() { return "GRand"; }

int GRand::Init()
{
    fn_802371B0(2, MathGetRandomSeed());
    return 1;
}

int GRand::Shutdown()
{
    fn_8023725C();
    return 1;
}

static ModuleDependency _GameModules_aIGMiscDependencies[] = { &gSys, &gRes, 0 };
IGMisc gIGMisc;

ModuleDependency *IGMisc::GetDependencies() { return _GameModules_aIGMiscDependencies; }
ModuleDependency *IGMisc::GetLinks() { return 0; }
const char *IGMisc::GetName() { return "IGMisc"; }

int IGMisc::Init()
{
    mData.mp = ResOpenDevice(lbl_802EBDF8, 44);
    return 1;
}

int IGMisc::Shutdown()
{
    ResClose(mData.mp);
    mData.mp = 0;
    return 1;
}

static ModuleDependency _GameModules_aMemAuditDependencies[] = { &gSys, 0 };
MemAudit gMemAudit;
static const char *_GameModules_pszMemAuditLoopName = 0;

ModuleDependency *MemAudit::GetDependencies() { return _GameModules_aMemAuditDependencies; }
ModuleDependency *MemAudit::GetLinks() { return 0; }
const char *MemAudit::GetName() { return "MemAudit"; }

int MemAudit::Init()
{
    if (InGameIsPlaying()) {
        _GameModules_pszMemAuditLoopName = "GameLoop";
    } else if (FELoopIsMainFEActive()) {
        _GameModules_pszMemAuditLoopName = "FELoop";
    } else {
        _GameModules_pszMemAuditLoopName = "unknown";
    }
    return 1;
}

int MemAudit::Shutdown()
{
    _GameModules_pszMemAuditLoopName = 0;
    return 1;
}

static ModuleDependency _GameModules_aQklDependencies[] = { &gRes, 0 };
Qkl gQkl;

ModuleDependency *Qkl::GetDependencies() { return _GameModules_aQklDependencies; }
ModuleDependency *Qkl::GetLinks() { return 0; }
const char *Qkl::GetName() { return "Qkl"; }

int Qkl::Init()
{
    char text[24];

    if (MainFEGroupIsStarted(&gMainFEGroup)) {
        ResTrackLabel("FELoopEnterStart");
    } else {
        fn_801C2E18(text, "GameLoopEnterStart%d", fn_800A3444());
        ResTrackLabel(text);
    }

    if (MainFEGroupIsStarted(&gMainFEGroup)) {
        fn_801C2EF0(mFileName.mText, lbl_803EB6F0, sizeof(mFileName.mText));
    } else {
        fn_801C2D88(mFileName.mText, sizeof(mFileName.mText), "%s%d.qkl", lbl_803EB6F8, fn_800A3444());
    }
    fn_801F2C54(mFileName.mText, 44);
    return 1;
}

int Qkl::Shutdown()
{
    char text[24];

    fn_801F2CD4(mFileName.mText);
    mFileName.mText[0] = 0;

    if (MainFEGroupIsStarted(&gMainFEGroup)) {
        ResTrackLabel("FELoopEnterFinish");
    } else {
        fn_801C2E18(text, "GameLoopEnterFinish%d", fn_800A3444());
        ResTrackLabel(text);
    }
    return 1;
}

static ModuleDependency _GameModules_aScrmRuleDependencies[] = { &gGameState, 0 };
ScrmRule gScrmRule;

ModuleDependency *ScrmRule::GetDependencies() { return _GameModules_aScrmRuleDependencies; }
ModuleDependency *ScrmRule::GetLinks() { return 0; }
const char *ScrmRule::GetName() { return "ScrmRule"; }

int ScrmRule::Init()
{
    fn_800A1A58();
    fn_801779D8();
    if (!FELoopIsMainFEActive()) {
        int csag;
        int cshg;

        fn_801FCE10(0, "select 'CSAG' into \x85 and 'CSHG' into \x85 from 'FNIG'\n", &csag, &cshg);
        fn_801787FC(1, csag);
        fn_801787FC(0, cshg);
        fn_8017885C();
    }
    return 1;
}

int ScrmRule::Shutdown()
{
    fn_80177B54();
    fn_800A1A80();
    return 1;
}

static ModuleDependency _GameModules_aStaDataDependencies[] = { &gRes, 0 };
StaData gStaData;

ModuleDependency *StaData::GetDependencies() { return _GameModules_aStaDataDependencies; }
ModuleDependency *StaData::GetLinks() { return 0; }
const char *StaData::GetName() { return "StaData"; }

int StaData::Init()
{
    mData.mp = ResOpenDevice(lbl_802EBFC0, 44);
    return 1;
}

int StaData::Shutdown()
{
    ResClose(mData.mp);
    mData.mp = 0;
    return 1;
}

void *StaData::GetArchive() { return mData.mp; }

static ModuleDependency _GameModules_aUISDependencies[] = { &gGRender, 0 };
UIS gUIS;

ModuleDependency *UIS::GetDependencies() { return _GameModules_aUISDependencies; }
ModuleDependency *UIS::GetLinks() { return 0; }
const char *UIS::GetName() { return "UIS"; }

int UIS::Init()
{
    UISGameInit();
    return 1;
}

int UIS::Shutdown()
{
    UISGameShutdown();
    return 1;
}
