/* Stadium crowd sound module: starts and stops the crowd track, sets the crowd
   volume and fires crowd reaction cues for game events. */

#include "game/ResOpenDevice.h"
#include "game/SndgCrowd.h"
#include "game/SndgPathfinder.h"
#include "game/fn_800B65A0.h"

void *operator new(unsigned int size, int unknown);

extern "C" {
extern char lbl_802EC018[];

void *memset(void *pDest, int value, unsigned int size);
int SndEnabled(void);
int fn_800A350C(void);
}

static ModuleDependency sDependencies[] = { &gSndgPathfinder, 0 };
static void *sLinks[] = { 0 };
static unsigned char _SndgCrowd_uVolume = 100;
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
    mpState.mp->mpUnknown0 = ResOpenDevice(lbl_802EC018, 44);
    if (SndEnabled()) {
        mpState.mp->mUnknown4 = SndgPathLoadMap(mpState.mp->mpUnknown0, 1);
        SndgPathCreateTrack(mpState.mp->mpUnknown0, 2, 0x14000001, 1.0f);
        SndgPathSetTrackVolume(0x14000001, _SndgCrowd_uVolume);
        SndgPathControl(0x14000001, 127);
    }
    return 1;
}

int SndgCrowd::Shutdown()
{
    if (SndEnabled()) {
        SndgPathDestroyTrack(0x14000001);
        SndgPathUnloadMap(mpState.mp->mUnknown4);
    }
    ResClose(mpState.mp->mpUnknown0);
    delete mpState.mp;
    mpState.mp = 0;
    return 1;
}

void SndgCrowdSetVolume(unsigned char value)
{
    _SndgCrowd_uVolume = value;
    if (gSndgCrowd.IsStarted() && SndEnabled()) {
        SndgPathSetTrackVolume(0x14000001, _SndgCrowd_uVolume);
    }
}

int SndgCrowdTriggerEvent(int index, int unknown)
{
    int result = 0;
    int flag;

    if (fn_800B65A0(unknown) == 0xFF) {
        flag = fn_800B65A0(unknown == 0) == 0xFF;
    } else {
        flag = 1;
    }
    if (fn_800A350C()) {
        result = SndgPathPostEvent(0x14000001, sIds[flag ? 0 : 1][index]);
    }
    return result;
}
