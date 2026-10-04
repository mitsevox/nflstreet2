#include "game/cu_8007F12C.h"
#include "game/fn_801EEB44.h"
#include "game/ModuleGroup_8008CC74.h"
#include "game/Record_802CC680.h"
#include "game/cu_80026BB0.h"

/* Argument of fn_801F8A0C and fn_801F8A54. */
struct Desc_801F8A0C {
    int mUnknown0;
    int mUnknown4[9];
};

/* Argument of fn_801E1478. */
struct Desc_801E1478 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int (*mpUnknown12)();
    void **mpUnknown16;
    int *mpUnknown20;
};

/* Argument of fn_80228E44. */
struct Desc_80228E44 {
    unsigned short mUnknown0;
    unsigned char mUnknown2[2];
};

extern "C" {
extern char lbl_802DBD7C[];
extern char lbl_802EBE24[];
extern char lbl_802EBE34[];
extern char lbl_802EBE40[];
extern char lbl_802F94D0[];
extern char lbl_8030A60C[];

void fn_800296B0(void);
void fn_800297D0(void);
void fn_80029C2C(int a, int b, int c);
void fn_8002A1D4(int a, int b, char *pText);
void fn_8002A5F0(int a, char *pText, int b);
void fn_800460DC(void);
void fn_800461E0(void);
void fn_8007272C(void);
void fn_80072890(void);
void fn_8008A88C(void);
void fn_8008A8D0(void);
void fn_8008FAA8(void);
void fn_8015E548(void);
void fn_8015E620(int a, int b);
void fn_8015E65C(void);
void fn_8015E684(void);
void fn_8015E714(void);
void fn_801607F0(int a);
void fn_80191200(void);
void fn_80191224(void);
void fn_801912A4(void);
void fn_80191414(void);
void fn_80191418(void);
void fn_80194794(void);
void fn_801C1710(int a);
void fn_801C17BC(void);
int fn_801C34F8(int a, int b, void *p, int c);
int fn_801C35B8(void);
int fn_801C4F64(void);
int fn_801C4FB8(void);
int fn_801C5E24(int a, int b);
int fn_801C5F9C(void);
int fn_801C6280(int a, int b, int c);
int fn_801CEF48(void);
int fn_801CEFA0(void);
int fn_801E1478(Desc_801E1478 *pDesc);
int fn_801E153C(void);
int fn_801EC1B4(int a, int b, int c);
int fn_801EC298(void);
int fn_801F512C(void);
int fn_801F518C(void);
void fn_801F8A0C(Desc_801F8A0C *pDesc);
int fn_801F8A54(Desc_801F8A0C *pDesc);
void fn_801F8C64(void);
int fn_801F9430(int a, int *pTable4, int *pTable8);
int fn_801F9574(void);
int fn_801FC9D4(int a, int b, int c, int d, int e);
void fn_801FCD04(void);
int fn_8020CFB0(int a);
int fn_8020D048(void);
void fn_8020D0CC(Record_802CC680 *pRecord);
void fn_8020D158(void);
int fn_80228E44(Desc_80228E44 *pDesc);
int fn_80228F0C(void);
int fn_80228F78(int a, const char *pName, int b);
void fn_80228FD8(void);
void fn_80229010(void);
void fn_8022905C(void);
int fn_80229094(const char *pName);
void fn_802290E0(void);
int fn_80229470(void);
void fn_80229494(void);
void fn_8022C930(int a);
int fn_8022EA80(int a, const char *pName, int b);
void fn_8022EAD8(void);
void fn_8022EB10(void);
void fn_8022EBC8(void);
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
    fn_801C1710(1);
    return 1;
}

int ARes::Shutdown()
{
    fn_801C17BC();
    return 1;
}

static ModuleDependency sCamDependencies[] = { &gObj, &gMat, &gMath, &gVec, 0 };
Cam gCam;

ModuleDependency *Cam::GetDependencies() { return sCamDependencies; }
ModuleDependency *Cam::GetLinks() { return 0; }
const char *Cam::GetName() { return "Cam"; }

int Cam::Init()
{
    fn_801C34F8(12, 5, lbl_802DBD7C, 2);
    return 1;
}

int Cam::Shutdown()
{
    fn_801C35B8();
    return 1;
}

extern "C" {
static void fn_8008CD58()
{
    unsigned int count = 4;
    unsigned int i;

    for (i = 0; i < count; i++) {
        fn_801C6280(i, 0, i);
        fn_80027114(i, 0);
        fn_801C6280(i, 4, 1);
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
    fn_801C5E24(10, fn_800273A4());
    fn_800271A4();
    fn_801C6280(-1, 2, (int)fn_80026DD4);
    fn_8008CD58();
    return 1;
}

int Context::Shutdown()
{
    fn_801C5F9C();
    return 1;
}

static void *sCurveDependencies[] = { 0 };
Curve gCurve;

ModuleDependency *Curve::GetDependencies() { return (ModuleDependency *)sCurveDependencies; }
ModuleDependency *Curve::GetLinks() { return 0; }
const char *Curve::GetName() { return "Curve"; }

int Curve::Init()
{
    fn_801C4F64();
    return 1;
}

int Curve::Shutdown()
{
    fn_801C4FB8();
    return 1;
}

static ModuleDependency sDbDependencies[] = { &gSys, 0 };
Db gDb;

ModuleDependency *Db::GetDependencies() { return sDbDependencies; }
ModuleDependency *Db::GetLinks() { return 0; }
const char *Db::GetName() { return "Db"; }

int Db::Init()
{
    Record_802CC680 *record = fn_80025E50(2);
    Desc_801F8A0C desc;

    fn_8022C930(32);
    fn_8020D0CC(record);
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
    fn_8020D158();
    return 1;
}

static int sDbGameTable_802D7064[] = { 0x45564153, 0x45564153, -1 };
static int sDbGameTable_802D7070[] = { 0x54504F53, 0x54504F47, -1 };
static ModuleDependency sDbGameDependencies[] = { &gSys, &gRes, &gDb, 0 };
DbGame gDbGame;

ModuleDependency *DbGame::GetDependencies() { return sDbGameDependencies; }
ModuleDependency *DbGame::GetLinks() { return 0; }
const char *DbGame::GetName() { return "DbGame"; }

int DbGame::Init()
{
    void *data;

    fn_80229470();
    data = fn_801EEB44(lbl_802EBE24, 44);
    fn_8022EA80(0x3000, lbl_802EBE24, 4);
    fn_8022EB10();
    fn_80228F78(0x96000, lbl_802EBE24, 2);
    fn_80229010();
    fn_8022EBF0(0x96000, lbl_802EBE24, 2);
    fn_8022EF14(lbl_802EBE34);
    fn_8022F028(0x3000, lbl_802EBE24, 5);
    fn_8022F4C4();
    fn_80229094(lbl_802EBE40);
    fn_801F9430(0x54415453, sDbGameTable_802D7070, sDbGameTable_802D7064);
    fn_8007F328(1);
    fn_801EEFAC(data);
    return 1;
}

int DbGame::Shutdown()
{
    fn_8007F374();
    fn_801F9574();
    fn_802290E0();
    fn_8022F744();
    fn_8022F094();
    fn_8022EF60();
    fn_8022EC48();
    fn_8022905C();
    fn_80228FD8();
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
    fn_80191414();
    fn_80191200();
    fn_801912A4();
    return 1;
}

int DbgPrint::Shutdown()
{
    fn_80191418();
    fn_80191224();
    return 1;
}

static ModuleDependency sEventDependencies[] = { &gPeriph, 0 };
Event gEvent;

ModuleDependency *Event::GetDependencies() { return sEventDependencies; }
ModuleDependency *Event::GetLinks() { return 0; }
const char *Event::GetName() { return "Event"; }

int Event::Init()
{
    fn_80026D50();
    return 1;
}

int Event::Shutdown()
{
    fn_80026DA8();
    return 1;
}

static ModuleDependency sLoadingDependencies[] = { &gVRAM, &gTex, 0 };
Loading gLoading;

ModuleDependency *Loading::GetDependencies() { return sLoadingDependencies; }
ModuleDependency *Loading::GetLinks() { return 0; }
const char *Loading::GetName() { return "Loading"; }

int Loading::Init()
{
    fn_80194794();
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
    fn_801CEF48();
    return 1;
}

int Math::Shutdown()
{
    fn_801CEFA0();
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

    fn_800296B0();
    fn_80029C2C(1, 0, 1);
    fn_8002A5F0(1, text, 0);
    fn_8002A1D4(1, 0, text);
    return 1;
}

int MemCard::Shutdown()
{
    fn_800297D0();
    return 1;
}

/* Null-terminated list read by fn_801E11E8 through Desc_801E1478::mpUnknown16. */
static void *sPeriphEntries[] = { lbl_802F94D0, 0 };
static int sPeriphCounter = 0;

extern "C" {
static int fn_8008D2CC()
{
    return sPeriphCounter++;
}
}

static int sPeriphUnknown[2];
static Desc_801E1478 sPeriphDesc = { 4, 16, 16, fn_8008D2CC, sPeriphEntries, sPeriphUnknown };
static ModuleDependency sPeriphDependencies[] = { &gSys, 0 };
Periph gPeriph;

ModuleDependency *Periph::GetDependencies() { return sPeriphDependencies; }
ModuleDependency *Periph::GetLinks() { return 0; }
const char *Periph::GetName() { return "Periph"; }

int Periph::Init()
{
    sPeriphUnknown[0] = 0;
    sPeriphUnknown[1] = 0;
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
    fn_801EC1B4(10, fn_800273A4(), 3);
    return 1;
}

int Remap::Shutdown()
{
    fn_801EC298();
    return 1;
}

static ModuleDependency sSortDependencies[] = { &gSys, 0 };
Sort gSort;

ModuleDependency *Sort::GetDependencies() { return sSortDependencies; }
ModuleDependency *Sort::GetLinks() { return 0; }
const char *Sort::GetName() { return "Sort"; }

int Sort::Init()
{
    fn_801F512C();
    return 1;
}

int Sort::Shutdown()
{
    fn_801F518C();
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
    fn_800461E0();
    fn_8008A8D0();
    fn_8015E714();
    fn_8015E65C();
    return 1;
}

void SysPreLoad::fn_8008D4A8()
{
    fn_800460DC();
    fn_8015E548();
    fn_8015E620(14, 1);
    fn_8015E684();
    fn_8008A88C();
    fn_801607F0(4);
}

static ModuleDependency sTaskDependencies[] = { &gSys, 0 };
Task gTask;

ModuleDependency *Task::GetDependencies() { return sTaskDependencies; }
ModuleDependency *Task::GetLinks() { return 0; }
const char *Task::GetName() { return "Task"; }

int Task::Init()
{
    fn_8020CFB0(10);
    return 1;
}

int Task::Shutdown()
{
    fn_8020D048();
    return 1;
}

static void *sVRAMDependencies[] = { 0 };
static Desc_80228E44 sVRAMDesc = { 1000 };
VRAM gVRAM;

ModuleDependency *VRAM::GetDependencies() { return (ModuleDependency *)sVRAMDependencies; }
ModuleDependency *VRAM::GetLinks() { return 0; }
const char *VRAM::GetName() { return "VRAM"; }

int VRAM::Init()
{
    fn_80228E44(&sVRAMDesc);
    return 1;
}

int VRAM::Shutdown()
{
    fn_80228F0C();
    return 1;
}

static ModuleDependency sFMSndgMusicDependencies[] = { lbl_8030A60C, &gDbGame, 0 };
static void *sFMSndgMusicLinks[] = { 0 };
FMSndgMusic gFMSndgMusic;

ModuleDependency *FMSndgMusic::GetDependencies() { return sFMSndgMusicDependencies; }
ModuleDependency *FMSndgMusic::GetLinks() { return (ModuleDependency *)sFMSndgMusicLinks; }
const char *FMSndgMusic::GetName() { return "FMSndgMusic"; }

int FMSndgMusic::Init()
{
    fn_8007272C();
    return 1;
}

int FMSndgMusic::Shutdown()
{
    fn_80072890();
    return 1;
}
