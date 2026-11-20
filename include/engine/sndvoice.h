#ifndef ENGINE_SNDVOICE_H
#define ENGINE_SNDVOICE_H

#ifdef __cplusplus
extern "C" {
#endif

int SNDVOICEI_get(int handle);
int iSNDpatchkey(int handle, int *index);
int fn_8026E160(int key, int value, void *data, int arg, int mode);
int fn_80274EAC(int index);

#ifdef __cplusplus
}
#endif

#endif
