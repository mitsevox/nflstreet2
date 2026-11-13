/* The system modules registered at start-up: resources, camera, context, curves, the
   database and game database, debug print, events, loading, maths, memory card,
   peripherals, remapping, sorting, preloading, tasks, video memory and front-end music. */

#include "engine/vram.h"
#include "engine/dbtats.h"
#include "engine/dbteams.h"
#include "engine/cu_80229270.h"
#include "game/GameOptions.h"
#include "game/DbgFont.h"
#include "game/ResOpenDevice.h"
#include "game/SysModules.h"
#include "game/SndgPathfinder.h"
#include "game/MemPoolDesc.h"
#include "game/PadInput.h"
#include "game/cu_8015D3EC.h"
#include "engine/periph.h"
#include "engine/remap.h"

/* Argument of fn_801F8A0C and fn_801F8A54. */
struct DbInitDesc_t {
    int mUnknown0;
    int mUnknown4[9];
};

extern "C" {
extern char lbl_802DBD7C[];
extern char lbl_802EBE24[];
extern char lbl_802EBE34[];
extern char lbl_802EBE40[];
extern Driver_801E11E8 lbl_802F94D0;

void MemCardFilesInit(void);
void MemCardFilesShutdown(void);
void MemCardFilesResetSlot(int a, int b, int c);
void MemCardFilesRenameSlot(int a, int b, char *pText);
void MemCardFilesMakeName(int a, char *pText, int b);
void PlaDynClutOpen(void);
void PlaDynClutUnload(void);
void SndgMusicInit(void);
void SndgMusicShutdown(void);
void PortraitSystemInit(void);
void PortraitSystemShutdown(void);
void fn_8008FAA8(void);
void fn_8015E548(void);
void fn_8015E65C(void);
void fn_8015E684(void);
void fn_8015E714(void);
void PlaTexCacheOpenArchive(int a);
void DbgPrintEnable(void);
void DbgPrintDisable(void);
void DbgScreenClear(void);
void LoadingInit(void);
void ResStreamInit(int a);
void ResStreamShutdown(void);
int CamInit(int a, int b, void *p, int c);
int CamShutdown(void);
int CurveInit(void);
int CurveShutdown(void);
int ConInit(int a, int b);
int ConShutdown(void);
int ConSetChannelInfo(int a, int b, int c);
int MathInit(void);
int MathShutdown(void);
int SortInit(void);
int SortShutdown(void);
void fn_801F8A0C(DbInitDesc_t *pDesc);
int fn_801F8A54(DbInitDesc_t *pDesc);
void fn_801F8C64(void);
int fn_801F9430(int a, int *pTable4, int *pTable8);
int fn_801F9574(void);
int fn_801FC9D4(int a, int b, int c, int d, int e);
void fn_801FCD04(void);
int TaskInit(int a);
int TaskShutdown(void);
void TDbExtInit(MemPoolDesc_t *pRecord);
void TDbExtShutdown(void);
int fn_80229470(void);
void fn_80229494(void);
void fn_8022C930(int a);
int fn_8022EA80(int a, const char *pName, int b);
void fn_8022EAD8(void);
int fn_8022EBF0(int a, const char *pName, int b);
void fn_8022EC48(void);
int fn_8022EF14(const char *pName);
void fn_8022EF60(void);
int fn_8022F028(int a, const char *pName, int b);
void fn_8022F094(void);
int fn_8022F4C4(void);
int fn_8022F744(void);
}

static ModuleDependency sAResDependencies[] = { &gRes, 0 };
ARes gARes;

ModuleDependency *ARes::GetDependencies() { return sAResDependencies; }
ModuleDependency *ARes::GetLinks() { return 0; }
const char *ARes::GetName() { return "ARes"; }

int ARes::Init()
{
    ResStreamInit(1);
    return 1;
}

int ARes::Shutdown()
{
    ResStreamShutdown();
    return 1;
}

static ModuleDependency sCamDependencies[] = { &gObj, &gMat, &gMath, &gVec, 0 };
Cam gCam;

ModuleDependency *Cam::GetDependencies() { return sCamDependencies; }
ModuleDependency *Cam::GetLinks() { return 0; }
const char *Cam::GetName() { return "Cam"; }

int Cam::Init()
{
    CamInit(12, 5, lbl_802DBD7C, 2);
    return 1;
}

int Cam::Shutdown()
{
    CamShutdown();
    return 1;
}

extern "C" {
static void _ContextResetPorts()
{
    unsigned int count = 4;
    unsigned int i;

    for (i = 0; i < count; i++) {
        ConSetChannelInfo(i, 0, i);
        PadInputSetupRemap(i, 0);
        ConSetChannelInfo(i, 4, 1);
    }
}
}

static ModuleDependency sContextDependencies[] = { &gEvent, &gRemap, 0 };
Context gContext;

ModuleDependency *Context::GetDependencies() { return sContextDependencies; }
ModuleDependency *Context::GetLinks() { return 0; }
const char *Context::GetName() { return "Context"; }

int Context::Init()
{
    ConInit(10, PadInputGetValueCount());
    PadInputSetDefaultHandler();
    ConSetChannelInfo(-1, 2, (int)PadInputRead);
    _ContextResetPorts();
    return 1;
}

int Context::Shutdown()
{
    ConShutdown();
    return 1;
}

static void *sCurveDependencies[] = { 0 };
Curve gCurve;

ModuleDependency *Curve::GetDependencies() { return (ModuleDependency *)sCurveDependencies; }
ModuleDependency *Curve::GetLinks() { return 0; }
const char *Curve::GetName() { return "Curve"; }

int Curve::Init()
{
    CurveInit();
    return 1;
}

int Curve::Shutdown()
{
    CurveShutdown();
    return 1;
}

static ModuleDependency sDbDependencies[] = { &gSys, 0 };
Db gDb;

ModuleDependency *Db::GetDependencies() { return sDbDependencies; }
ModuleDependency *Db::GetLinks() { return 0; }
const char *Db::GetName() { return "Db"; }

int Db::Init()
{
    MemPoolDesc_t *record = MemPoolGetDesc(2);
    DbInitDesc_t desc;

    fn_8022C930(32);
    TDbExtInit(record);
    fn_801F8A0C(&desc);
    desc.mUnknown0 = record->mUnknown10;
    fn_801F8A54(&desc);
    fn_801FC9D4(5, 1270, 400, 30, 150);
    return 1;
}

int Db::Shutdown()
{
    fn_801FCD04();
    fn_801F8C64();
    TDbExtShutdown();
    return 1;
}

static int _DbGame_aSaveTags[] = { 0x45564153, 0x45564153, -1 };
static int _DbGame_aOptionTables[] = { 0x54504F53, 0x54504F47, -1 };
static ModuleDependency sDbGameDependencies[] = { &gSys, &gRes, &gDb, 0 };
DbGame gDbGame;

ModuleDependency *DbGame::GetDependencies() { return sDbGameDependencies; }
ModuleDependency *DbGame::GetLinks() { return 0; }
const char *DbGame::GetName() { return "DbGame"; }

int DbGame::Init()
{
    void *data;

    fn_80229470();
    data = ResOpenDevice(lbl_802EBE24, 44);
    fn_8022EA80(0x3000, lbl_802EBE24, 4);
    fn_8022EB10();
    DbTatsInit(0x96000, lbl_802EBE24, 2);
    DbTatsLoad();
    fn_8022EBF0(0x96000, lbl_802EBE24, 2);
    fn_8022EF14(lbl_802EBE34);
    fn_8022F028(0x3000, lbl_802EBE24, 5);
    fn_8022F4C4();
    DbTeamsInit(lbl_802EBE40);
    fn_801F9430(0x54415453, _DbGame_aOptionTables, _DbGame_aSaveTags);
    GameOptionsInit(1);
    ResClose(data);
    return 1;
}

int DbGame::Shutdown()
{
    GameOptionsShutdown();
    fn_801F9574();
    DbTeamsShutdown();
    fn_8022F744();
    fn_8022F094();
    fn_8022EF60();
    fn_8022EC48();
    DbTatsUnload();
    DbTatsShutdown();
    fn_8022EBC8();
    fn_8022EAD8();
    fn_80229494();
    return 1;
}

static void *sDbgPrintDependencies[] = { 0 };
DbgPrint gDbgPrint;

ModuleDependency *DbgPrint::GetDependencies() { return (ModuleDependency *)sDbgPrintDependencies; }
ModuleDependency *DbgPrint::GetLinks() { return 0; }
const char *DbgPrint::GetName() { return "DbgPrint"; }

int DbgPrint::Init()
{
    DbgFontInit();
    DbgPrintEnable();
    DbgScreenClear();
    return 1;
}

int DbgPrint::Shutdown()
{
    DbgFontShutdown();
    DbgPrintDisable();
    return 1;
}

static ModuleDependency sEventDependencies[] = { &gPeriph, 0 };
Event gEvent;

ModuleDependency *Event::GetDependencies() { return sEventDependencies; }
ModuleDependency *Event::GetLinks() { return 0; }
const char *Event::GetName() { return "Event"; }

int Event::Init()
{
    PadInputInit();
    return 1;
}

int Event::Shutdown()
{
    PadInputShutdown();
    return 1;
}

static ModuleDependency sLoadingDependencies[] = { &gVRAM, &gTex, 0 };
Loading gLoading;

ModuleDependency *Loading::GetDependencies() { return sLoadingDependencies; }
ModuleDependency *Loading::GetLinks() { return 0; }
const char *Loading::GetName() { return "Loading"; }

int Loading::Init()
{
    LoadingInit();
    return 1;
}

int Loading::Shutdown()
{
    return 1;
}

static void *sMathDependencies[] = { 0 };
Math gMath;

ModuleDependency *Math::GetDependencies() { return (ModuleDependency *)sMathDependencies; }
ModuleDependency *Math::GetLinks() { return 0; }
const char *Math::GetName() { return "Math"; }

int Math::Init()
{
    MathInit();
    return 1;
}

int Math::Shutdown()
{
    MathShutdown();
    return 1;
}

static ModuleDependency sMemCardDependencies[] = { &gPeriph, &gContext, &gRemap, 0 };
MemCard gMemCard;

ModuleDependency *MemCard::GetDependencies() { return sMemCardDependencies; }
ModuleDependency *MemCard::GetLinks() { return 0; }
const char *MemCard::GetName() { return "MemCard"; }

int MemCard::Init()
{
    char text[32];

    MemCardFilesInit();
    MemCardFilesResetSlot(1, 0, 1);
    MemCardFilesMakeName(1, text, 0);
    MemCardFilesRenameSlot(1, 0, text);
    return 1;
}

int MemCard::Shutdown()
{
    MemCardFilesShutdown();
    return 1;
}

/* Null-terminated list read by fn_801E11E8 through Desc_801E1478::mppDrivers. */
static Driver_801E11E8 *sPeriphEntries[] = { &lbl_802F94D0, 0 };
static int sPeriphCounter = 0;

extern "C" {
static int _PeriphNextId()
{
    return sPeriphCounter++;
}
}

static int sPeriphState[2];
static Desc_801E1478 sPeriphDesc = { 4, 16, 16, _PeriphNextId, sPeriphEntries, sPeriphState };
static ModuleDependency sPeriphDependencies[] = { &gSys, 0 };
Periph gPeriph;

ModuleDependency *Periph::GetDependencies() { return sPeriphDependencies; }
ModuleDependency *Periph::GetLinks() { return 0; }
const char *Periph::GetName() { return "Periph"; }

int Periph::Init()
{
    sPeriphState[0] = 0;
    sPeriphState[1] = 0;
    fn_801E1478(&sPeriphDesc);
    return 1;
}

int Periph::Shutdown()
{
    fn_801E153C();
    return 1;
}

static ModuleDependency sRemapDependencies[] = { &gEvent, 0 };
Remap gRemap;

ModuleDependency *Remap::GetDependencies() { return sRemapDependencies; }
ModuleDependency *Remap::GetLinks() { return 0; }
const char *Remap::GetName() { return "Remap"; }

int Remap::Init()
{
    RemapInit(10, PadInputGetValueCount(), 3);
    return 1;
}

int Remap::Shutdown()
{
    RemapShutdown();
    return 1;
}

static ModuleDependency sSortDependencies[] = { &gSys, 0 };
Sort gSort;

ModuleDependency *Sort::GetDependencies() { return sSortDependencies; }
ModuleDependency *Sort::GetLinks() { return 0; }
const char *Sort::GetName() { return "Sort"; }

int Sort::Init()
{
    SortInit();
    return 1;
}

int Sort::Shutdown()
{
    SortShutdown();
    return 1;
}

static ModuleDependency sSysPreLoadDependencies[] = { &gRes, 0 };
SysPreLoad gSysPreLoad;

ModuleDependency *SysPreLoad::GetDependencies() { return sSysPreLoadDependencies; }
ModuleDependency *SysPreLoad::GetLinks() { return 0; }
const char *SysPreLoad::GetName() { return "SysPreLoad"; }

int SysPreLoad::Init()
{
    fn_8008FAA8();
    return 1;
}

int SysPreLoad::Shutdown()
{
    PlaDynClutUnload();
    PortraitSystemShutdown();
    fn_8015E714();
    fn_8015E65C();
    return 1;
}

void SysPreLoad::LoadSystems()
{
    PlaDynClutOpen();
    fn_8015E548();
    fn_8015E620(14, 1);
    fn_8015E684();
    PortraitSystemInit();
    PlaTexCacheOpenArchive(4);
}

static ModuleDependency sTaskDependencies[] = { &gSys, 0 };
Task gTask;

ModuleDependency *Task::GetDependencies() { return sTaskDependencies; }
ModuleDependency *Task::GetLinks() { return 0; }
const char *Task::GetName() { return "Task"; }

int Task::Init()
{
    TaskInit(10);
    return 1;
}

int Task::Shutdown()
{
    TaskShutdown();
    return 1;
}

static void *sVRAMDependencies[] = { 0 };
static VramInitBlock_t sVRAMDesc = { 1000 };
VRAM gVRAM;

ModuleDependency *VRAM::GetDependencies() { return (ModuleDependency *)sVRAMDependencies; }
ModuleDependency *VRAM::GetLinks() { return 0; }
const char *VRAM::GetName() { return "VRAM"; }

int VRAM::Init()
{
    VramInit(&sVRAMDesc);
    return 1;
}

int VRAM::Shutdown()
{
    VramShutdown();
    return 1;
}

static ModuleDependency sFMSndgMusicDependencies[] = { &gSndgPathfinder, &gDbGame, 0 };
static void *sFMSndgMusicLinks[] = { 0 };
FMSndgMusic gFMSndgMusic;

ModuleDependency *FMSndgMusic::GetDependencies() { return sFMSndgMusicDependencies; }
ModuleDependency *FMSndgMusic::GetLinks() { return (ModuleDependency *)sFMSndgMusicLinks; }
const char *FMSndgMusic::GetName() { return "FMSndgMusic"; }

int FMSndgMusic::Init()
{
    SndgMusicInit();
    return 1;
}

int FMSndgMusic::Shutdown()
{
    SndgMusicShutdown();
    return 1;
}
