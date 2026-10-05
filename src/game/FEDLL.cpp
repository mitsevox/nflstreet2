#include "game/Module.h"
#include "game/Record_802CC680.h"

extern "C" {
extern char lbl_800034A0[];

int fn_801D2130(Record_802CC680 *pObject);
int fn_80024B20(int team, int margin, int flag);
int fn_801D2570(int id);
void fn_80088E8C(char *pStart, char *pEnd);
void fn_80088EC8(char *pStart, char *pEnd);
}

static ModuleDependency sDependencies[] = { &gSys, 0 };
FEDLL gFEDLL;
static unsigned char sShutdown = 0;

ModuleDependency *FEDLL::GetDependencies() { return sDependencies; }
ModuleDependency *FEDLL::GetLinks() { return 0; }
const char *FEDLL::GetName() { return "FEDLL"; }

/* After a Shutdown: withdraws record 0x40 and restores the code range from ARAM. */
int FEDLL::Init()
{
    if (sShutdown) {
        fn_801D2570(0x40);
        fn_80088E8C(lbl_800034A0, (char *)fn_80024B20);
        sShutdown = 0;
    }
    return 1;
}

/* Copies the code range lbl_800034A0-fn_80024B20 to ARAM, then passes record
   0x40 to fn_801D2130. */
int FEDLL::Shutdown()
{
    Record_802CC680 *pObject = fn_80025E50(0x40);
    pObject->mUnknown10 = (char *)fn_80024B20 - lbl_800034A0;
    fn_80088EC8(lbl_800034A0, (char *)fn_80024B20);
    pObject->mUnknown10 = 0x209C0;
    fn_801D2130(pObject);
    sShutdown = 1;
    return 1;
}
