/* Front-end sound: starts, services every frame and stops the audio of the menus. */

struct SndgConfig_t;

extern "C" {
extern SndgConfig_t gSndgFEConfig;

void SndgInit(SndgConfig_t *pInit);
void SndgShutdown(void);
void SndgChannelsInitFE(void);
void SndgChannelsShutdownFE(void);
void SndgApplyVolumeOptions(void);
void SndgMusicUpdate(void);
void SpchIGInitFrontEnd(void);
void fn_801F4B20(void);

void FESndInit(void)
{
    SndgInit(&gSndgFEConfig);
    SndgChannelsInitFE();
    SpchIGInitFrontEnd();
    SndgApplyVolumeOptions();
}

void FESndUpdate(int a)
{
    SndgMusicUpdate();
    fn_801F4B20();
}

void FESndShutdown(void)
{
    SndgChannelsShutdownFE();
    SndgShutdown();
}

}
