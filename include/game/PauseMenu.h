#ifndef GAME_PAUSEMENU_H
#define GAME_PAUSEMENU_H

typedef int (*PauseRequestFn_t)(unsigned short *pA, unsigned short *pB, int *pC);

extern "C" {
void PauseEnterAudio(void);
void PauseExitAudio(void);
void PauseResetState(void);
int PauseIsActive(void);
void PauseInstallRequests(void);
void PauseCameraStart(void);
int PauseCameraUpdate(void);
int PauseCameraRestore(void);
void PauseCloseHook(void);
void PauseCloseRequestHook(void);
void PausePollRequests(void);
void PauseSetRequestCallback(int index, PauseRequestFn_t pCallback);
void PauseClearRequestCallback(int index);
void PauseInit(void);
void PauseShutdown(void);
void PauseOpenScreen(unsigned short a, unsigned short b, int c);
void PauseOpenScreenArgs(unsigned short a, unsigned short b, int c, unsigned int count, int *pArgs, int keep);
void PauseUpdate(void);
void PauseRequestClose(void);
void PauseClose(void);
void PauseBlock(void);
void PauseUnblock(void);
void PauseClearBlocks(void);
int PauseIsUnblocked(void);
int PauseIsOpen(void);
int PauseGetSavedMode(void);
void PauseNullHook(void);
void PauseClearSavedFlags(void);
int PauseGetValue(void);
unsigned char PauseIsAudioPaused(void);
void PauseSetQuitFlag(unsigned char value);
unsigned char PauseGetQuitFlag(void);
void PauseSetSavedRumble(unsigned char value);
void PauseSetAltAction(unsigned char value);
void PauseSetPollDelay(int value);
}

#endif
