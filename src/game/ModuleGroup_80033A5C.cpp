#include "game/fn_801EEB44.h"
#include "game/fn_801FCE10.h"
#include "game/GameState.h"
#include "game/ModuleGroup_80033A5C.h"

extern "C" {
extern char lbl_80306B34[];
extern char lbl_802EBDBC[];
extern char lbl_802EBDF8[];
extern char lbl_802EBFC0[];
extern char lbl_803EB6F0[];
extern char lbl_803EB6F8[];

int fn_80027DF0(void);
int fn_8002894C(void);
int fn_80033124(void *pObject);
void fn_80067C10(void);
void fn_80067C44(void);
void fn_800A1A58(void);
void fn_800A1A80(void);
int fn_800A3444(void);
void fn_801779D8(void);
void fn_80177B54(void);
void fn_801787FC(int which, short value);
void fn_8017885C(void);
void fn_80189F68(void);
void fn_8018A40C(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_801CF7AC(void);
void fn_801F2798(const char *pText);
int fn_801F2C54(const char *pName, int unknown);
int fn_801F2CD4(const char *pName);
void fn_802371B0(int unknown, int seed);
void fn_8023725C(void);
}

static ModuleDependency sAnimDataDependencies[] = { &gRes, 0 };
AnimData gAnimData;

ModuleDependency *AnimData::GetDependencies() { return sAnimDataDependencies; }
ModuleDependency *AnimData::GetLinks() { return 0; }
const char *AnimData::GetName() { return "AnimData"; }

int AnimData::Init()
{
    mData.mp = fn_801EEB44(lbl_802EBDBC, 44);
    fn_8002894C();
    return 1;
}

int AnimData::Shutdown()
{
    fn_801EEFAC(mData.mp);
    mData.mp = 0;
    return 1;
}

void *AnimData::fn_80033AF8() { return mData.mp; }

static ModuleDependency sAudmonDependencies[] = { &gGameState, 0 };
Audmon gAudmon;

ModuleDependency *Audmon::GetDependencies() { return sAudmonDependencies; }
ModuleDependency *Audmon::GetLinks() { return 0; }
const char *Audmon::GetName() { return "Audmon"; }

int Audmon::Init()
{
    fn_80067C10();
    return 1;
}

int Audmon::Shutdown()
{
    fn_80067C44();
    return 1;
}

static ModuleDependency sGRandDependencies[] = { &gGameState, 0 };
GRand gGRand;

ModuleDependency *GRand::GetDependencies() { return sGRandDependencies; }
ModuleDependency *GRand::GetLinks() { return 0; }
const char *GRand::GetName() { return "GRand"; }

int GRand::Init()
{
    fn_802371B0(2, fn_801CF7AC());
    return 1;
}

int GRand::Shutdown()
{
    fn_8023725C();
    return 1;
}

static ModuleDependency sIGMiscDependencies[] = { &gSys, &gRes, 0 };
IGMisc gIGMisc;

ModuleDependency *IGMisc::GetDependencies() { return sIGMiscDependencies; }
ModuleDependency *IGMisc::GetLinks() { return 0; }
const char *IGMisc::GetName() { return "IGMisc"; }

int IGMisc::Init()
{
    mData.mp = fn_801EEB44(lbl_802EBDF8, 44);
    return 1;
}

int IGMisc::Shutdown()
{
    fn_801EEFAC(mData.mp);
    mData.mp = 0;
    return 1;
}

static ModuleDependency sMemAuditDependencies[] = { &gSys, 0 };
MemAudit gMemAudit;
static const char *sLoopName = 0;

ModuleDependency *MemAudit::GetDependencies() { return sMemAuditDependencies; }
ModuleDependency *MemAudit::GetLinks() { return 0; }
const char *MemAudit::GetName() { return "MemAudit"; }

int MemAudit::Init()
{
    if (fn_8002894C()) {
        sLoopName = "GameLoop";
    } else if (fn_80027DF0()) {
        sLoopName = "FELoop";
    } else {
        sLoopName = "unknown";
    }
    return 1;
}

int MemAudit::Shutdown()
{
    sLoopName = 0;
    return 1;
}

static ModuleDependency sQklDependencies[] = { &gRes, 0 };
Qkl gQkl;

ModuleDependency *Qkl::GetDependencies() { return sQklDependencies; }
ModuleDependency *Qkl::GetLinks() { return 0; }
const char *Qkl::GetName() { return "Qkl"; }

int Qkl::Init()
{
    char text[24];

    if (fn_80033124(lbl_80306B34)) {
        fn_801F2798("FELoopEnterStart");
    } else {
        fn_801C2E18(text, "GameLoopEnterStart%d", fn_800A3444());
        fn_801F2798(text);
    }

    if (fn_80033124(lbl_80306B34)) {
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

    if (fn_80033124(lbl_80306B34)) {
        fn_801F2798("FELoopEnterFinish");
    } else {
        fn_801C2E18(text, "GameLoopEnterFinish%d", fn_800A3444());
        fn_801F2798(text);
    }
    return 1;
}

static ModuleDependency sScrmRuleDependencies[] = { &gGameState, 0 };
ScrmRule gScrmRule;

ModuleDependency *ScrmRule::GetDependencies() { return sScrmRuleDependencies; }
ModuleDependency *ScrmRule::GetLinks() { return 0; }
const char *ScrmRule::GetName() { return "ScrmRule"; }

int ScrmRule::Init()
{
    fn_800A1A58();
    fn_801779D8();
    if (!fn_80027DF0()) {
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

static ModuleDependency sStaDataDependencies[] = { &gRes, 0 };
StaData gStaData;

ModuleDependency *StaData::GetDependencies() { return sStaDataDependencies; }
ModuleDependency *StaData::GetLinks() { return 0; }
const char *StaData::GetName() { return "StaData"; }

int StaData::Init()
{
    mData.mp = fn_801EEB44(lbl_802EBFC0, 44);
    return 1;
}

int StaData::Shutdown()
{
    fn_801EEFAC(mData.mp);
    mData.mp = 0;
    return 1;
}

void *StaData::fn_80033FD4() { return mData.mp; }

static ModuleDependency sUISDependencies[] = { &gGRender, 0 };
UIS gUIS;

ModuleDependency *UIS::GetDependencies() { return sUISDependencies; }
ModuleDependency *UIS::GetLinks() { return 0; }
const char *UIS::GetName() { return "UIS"; }

int UIS::Init()
{
    fn_80189F68();
    return 1;
}

int UIS::Shutdown()
{
    fn_8018A40C();
    return 1;
}
