/* Starts up and shuts down in-game audio for the SndgIG module: sound banks, crowd, ambience, the
   game-event callback and the in-game speech (commentary) system, in a fixed order. */

#include "game/AudmonEvent.h"
#include "game/fn_8017F584.h"
#include "game/SndgCrowd.h"

struct SndgConfig_t;

extern "C" {
void SndgAmbInit(void);
void SndgAmbShutdown(void);
void SndgAmbPostCue(int type);
void SndgInit(SndgConfig_t *pInit);
void SndgShutdown(void);
void SndgChannelsCreateStreams(int withThird);
void SndgChannelsDestroyStreams(void);
void SndgApplyVolumeOptions(void);
void fn_8006F810(void);
void fn_8006F820(void);
void fn_800710C8(void);
void fn_80071594(void *pRecord);
void fn_80071600(void);
void fn_800716E4(void);
void fn_80071C34(int value);
void SpchIGInit(void);
void SpchIGShutdown(void);
int fn_800A350C(void);
void fn_800B1670(void (*pCallback)(void *));
int fn_800C8704(int *pA, int *pB);
void ResTrackLabel(const char *pText);

extern SndgConfig_t gSndgIGConfig;
}

static int _SndgIG_iReserved;

extern "C" void SndgIGLogStartupInfo(void)
{
    char s0[19];
    char s1[19];
    char s2[17];
    char s3[17];
    char s4[25];
    char s5[25];
    int a;
    int b;

    a = 0;
    b = 0;
    s0[sizeof(s0) - 1] = 0;
    s1[sizeof(s1) - 1] = 0;
    s2[sizeof(s2) - 1] = 0;
    s3[sizeof(s3) - 1] = 0;
    s4[sizeof(s4) - 1] = 0;
    s5[sizeof(s5) - 1] = 0;
    fn_800C8704(&a, &b);
}

extern "C" void SndgIGInitAudio(void)
{
    SndgInit(&gSndgIGConfig);
    _SndgIG_iReserved = 0;
    AudmonEventStartInGame();
    fn_800B1670(fn_80071594);
    SndgChannelsCreateStreams(fn_8017F584() == 11);
    SndgAmbInit();
    SndgAmbPostCue(0);
    if (fn_800A350C()) {
        SndgCrowdTriggerEvent(0, 0);
    }
    fn_8006F810();
    fn_80071600();
    fn_80071C34(0);
    SndgIGLogStartupInfo();
    SndgApplyVolumeOptions();
    fn_800710C8();
    ResTrackLabel("SpchIGInitStart");
    SpchIGInit();
    ResTrackLabel("SpchIGInitFinish");
}

extern "C" void SndgIGShutdownAudio(void)
{
    SpchIGShutdown();
    SndgAmbShutdown();
    fn_8006F820();
    fn_800716E4();
    SndgChannelsDestroyStreams();
    SndgShutdown();
}
