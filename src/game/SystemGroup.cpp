#include "game/Class_801CC350.h"

extern "C" {
extern char lbl_803653B4[];
extern char lbl_8030A60C[];
extern char lbl_8030C060[];
extern char lbl_8030BEF8[];
extern char lbl_8030BF1C[];
extern char lbl_8030BF38[];
extern char lbl_8030BF48[];
extern char lbl_8030BF58[];
extern char lbl_8030BF78[];
extern char lbl_8030BF88[];
extern char lbl_8030BF98[];
extern char lbl_8030BFB4[];
extern char lbl_8030BFC4[];
extern char lbl_8030BFE4[];
extern char lbl_8030BFF4[];
extern char lbl_8030C004[];
extern char lbl_8030C014[];
extern char lbl_8030C044[];
extern char lbl_8030C034[];
extern char lbl_8030C024[];
}

static Record_802CCBAC sStages[] = { { 0, "System Stage" }, { -1, 0 } };
static Record_803EA3A8 sRecords[] = { { -1, -1 } };
SystemGroup gSystemGroup;
static ModuleDependency sModules[] = {
    &gSys,
    &gFileIO,
    &gRes,
    &gFont,
    &gGLIB,
    lbl_803653B4,
    &gSnd,
    lbl_8030A60C,
    lbl_8030C060,
    lbl_8030BEF8,
    lbl_8030BF1C,
    lbl_8030BF38,
    lbl_8030BF48,
    &gMat,
    lbl_8030BF58,
    lbl_8030BF78,
    lbl_8030BF88,
    lbl_8030BF98,
    lbl_8030BFB4,
    lbl_8030BFC4,
    lbl_8030BFE4,
    &gObj,
    lbl_8030BFF4,
    lbl_8030C004,
    lbl_8030C014,
    &gTex,
    &gVec,
    &gVpt,
    lbl_8030C044,
    lbl_8030C034,
    lbl_8030C024,
    0
};

const char *SystemGroup::GetName() { return "System Group"; }
Record_802CCBAC *SystemGroup::fn_800324BC() { return sStages; }
Record_803EA3A8 *SystemGroup::fn_800324C8() { return sRecords; }

ModuleDependency *SystemGroup::fn_800324D0(int id)
{
    if (id == 0) {
        return sModules;
    }
    return 0;
}

void SystemGroup::fn_800324E4() {}
int SystemGroup::fn_800324E8() { return 1; }
