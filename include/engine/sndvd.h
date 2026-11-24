#ifndef ENGINE_SNDVD_H
#define ENGINE_SNDVD_H

#include <dolphin/os.h>

#ifdef __cplusplus
extern "C" {
#endif
void SNDVDEmuInit(int id);
void SNDVDEmuInitDSIHandler(void);
u32 SNDVDEmuControl(int request);
#ifdef __cplusplus
}
#endif

#endif
