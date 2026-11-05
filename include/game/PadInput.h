#ifndef GAME_PADINPUT_H
#define GAME_PADINPUT_H

/* 34 floats (0x88 bytes), copied and cleared as a whole. */
struct InputValues {
    float mValue[34];
};

extern "C" {
float PadInputGetCallbackAxis(int slot);
float PadInputSnapAxis(float x);
void PadInputCopyValues(InputValues *pDst, InputValues *pSrc);
int PadInputIsDeviceReady(int handle);
int PadInputInit(void);
void PadInputShutdown(void);
void PadInputRead(int slot, InputValues *pPrevious, InputValues *pCurrent);
void PadInputSetupRemap(int slot, int index);
void PadInputSetDefaultHandler(void);
void PadInputSaveHandlers(void **pHandlers);
void PadInputRestoreHandlers(void **pHandlers);
void PadInputSetAxisCallback(int (*pCallback)());
float PadInputAxisFromFixed(int value);
int PadInputAxisToFixed(float x);
void PadInputResetSlot(int slot);
char *PadInputGetDeviceData(void);
int PadInputGetValueCount(void);
}

#endif
