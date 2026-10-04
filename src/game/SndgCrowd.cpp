#include "game/SndgCrowd.h"

void *operator new(unsigned int size, int unknown);

extern "C" {
extern char lbl_8030A60C[];
extern char lbl_802EC018[];

void *memset(void *pDest, int value, unsigned int size);
int fn_801EEB44(const char *pName, int unknown);
int fn_801EEFAC(int handle);
int fn_801F3E28(void);
int fn_800A350C(void);
int fn_800B65A0(int unknown);
int fn_8006DBF8(int handle, int unknown);
int fn_8006DC4C(int handle);
int fn_8006DC98(int handle, int unknown, int id, float value);
int fn_8006DD24(int id);
void fn_8006DD70(int id, unsigned char value);
int fn_8006DE00(int id, int unknown);
int fn_8006DE54(int id, int unknown);
}

static ModuleDependency sDependencies[] = { lbl_8030A60C, 0 };
static void *sLinks[] = { 0 };
static unsigned char sUnknownByte = 100;
static int sIds[2][16] = {
    { 0x0484B11F, 0x04275C81, 0x04B18E13, 0x041EDEAC, 0x049D2DD0, 0x047C218B, 0x04472AF5, 0x041E6CDB,
      0x041DB7F7, 0x046C4981, 0x041AEAFF, 0x0462E5B4, 0x04A6E7DF, 0x0424B9BC, 0x048D591F, 0x04221664 },
    { 0x0484B11F, 0x04275C81, 0x04B18E13, 0x041EDEAC, 0x0452C786, 0x046CB944, 0x0424B23A, 0x04D1CC7A,
      0x04E52F38, 0x045CD14E, 0x04D5A98D, 0x04ADE299, 0x04977F10, 0x04EB2A48, 0x0417C1D0, 0x04EDF3DC },
};
SndgCrowd gSndgCrowd;

ModuleDependency *SndgCrowd::GetDependencies() { return sDependencies; }
ModuleDependency *SndgCrowd::GetLinks() { return (ModuleDependency *)sLinks; }
const char *SndgCrowd::GetName() { return "SndgCrowd"; }

int SndgCrowd::Init()
{
    mpState.mp = new (0) SndgCrowdState;
    memset(mpState.mp, 0, sizeof(SndgCrowdState));
    mpState.mp->mUnknown0 = fn_801EEB44(lbl_802EC018, 44);
    if (fn_801F3E28()) {
        mpState.mp->mUnknown4 = fn_8006DBF8(mpState.mp->mUnknown0, 1);
        fn_8006DC98(mpState.mp->mUnknown0, 2, 0x14000001, 1.0f);
        fn_8006DD70(0x14000001, sUnknownByte);
        fn_8006DE54(0x14000001, 127);
    }
    return 1;
}

int SndgCrowd::Shutdown()
{
    if (fn_801F3E28()) {
        fn_8006DD24(0x14000001);
        fn_8006DC4C(mpState.mp->mUnknown4);
    }
    fn_801EEFAC(mpState.mp->mUnknown0);
    delete mpState.mp;
    mpState.mp = 0;
    return 1;
}

void fn_8006F344(unsigned char value)
{
    sUnknownByte = value;
    if (gSndgCrowd.fn_801CC96C() && fn_801F3E28()) {
        fn_8006DD70(0x14000001, sUnknownByte);
    }
}

int fn_8006F394(int index, int unknown)
{
    int result = 0;
    int flag;

    if (fn_800B65A0(unknown) == 0xFF) {
        flag = fn_800B65A0(unknown == 0) == 0xFF;
    } else {
        flag = 1;
    }
    if (fn_800A350C()) {
        result = fn_8006DE00(0x14000001, sIds[flag ? 0 : 1][index]);
    }
    return result;
}
