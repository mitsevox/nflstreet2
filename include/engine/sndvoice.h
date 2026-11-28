#ifndef ENGINE_SNDVOICE_H
#define ENGINE_SNDVOICE_H

#ifdef __cplusplus
extern "C" {
#endif

int SNDVOICEI_get(int handle);
int iSNDpatchkey(int handle, int *index);
void iSNDcalcvol(int index);
int SNDfxlevel(int handle, int bus, int level);
int SNDPLATFORM_getcurframe(int index);
int SNDCTRL_getprogvol(int handle);

#ifdef __cplusplus
}
#endif

#endif
