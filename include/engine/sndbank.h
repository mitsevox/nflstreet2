#ifndef ENGINE_SNDBANK_H
#define ENGINE_SNDBANK_H

/* Declarations shared by the sound-library files in 0x8026A664-0x8026D200: the bank files
   (sballoc.c to sbvalid.c), the play-option, client, server and utility files after them. */

#include "engine/sndlib.h"
#include "engine/sndsample.h"

typedef Struct_80270E04 SNDIPATCHHEADER;

/* A loaded sound bank's header: patch count and the self-relative offsets of its patches. */
typedef struct BankVer_t {
    unsigned char unk_0x0[6];
    unsigned short m6;
    int m8;
    int mC;
    int m10;
    int m14[1];
} BankVer_t;

/* One entry of the bank table lbl_803A6C24.m1D0. */
typedef struct SndBankSlot_t {
    BankVer_t *m0;
    int m4;
    unsigned char m8;
    unsigned char unk_0x9[3];
} SndBankSlot_t;

/* One envelope stage of a voice record (Record_803A6DF0 +0x70): its length in ticks and target level. */
typedef struct SndEnvStage_t {
    int m0;
    int m4;
} SndEnvStage_t;

extern "C" {

void *memmove(void *dst, const void *src, unsigned int n);

int SNDVOICEI_get(int handle);
void SNDBANKI_userdatacallback(SNDIPATCHHEADER *patch, int event);
int SNDbankadd(int *handle, BankVer_t *bank);
int SNDBANKI_playpatch(BankVer_t *bank, void *patch, int bank_index, int patch_index, SndPlayOpts_t *opts);
void SndHalSetDry(int index);
void iSNDcalcpitch(int index);
int fn_80270E04(char **cursor, Struct_80270E04 *out);
void fn_80278598(int index);
int SNDstop(int handle);
void SNDI_patchtohdr(BankVer_t *bank, unsigned char *patch, SndSampleFormat_t *format, SndSampleAttr_t *attr,
                     SndSampleDesc_t *desc, unsigned char *isStream);

int SNDBANKI_alloc(void);
void *SNDBANKI_getppatch(BankVer_t *bank, int patch);
void SNDBANKI_asyncloadmemresolve(void);
void SNDBANKI_asyncloadmem100hz(void);
int SNDBANK_asyncloadmem(int *handle, BankVer_t *bank);
int SNDBANK_asyncloadmemdone(void);
int SNDbankheadercopy(void *dst, int bank);
int SNDbankheadersize(int bank);
int SNDBANK_patchinfo(int bank, int patch, SndSampleFormat_t *format, SndSampleAttr_t *attr, void *desc);
int SNDBANK_play(int bank, int patch, SndPlayOpts_t *opts);
int SNDbankremove(int bank);
int SNDBANKI_valid(int bank);
void SNDI_checkplayopts(SndPlayOpts_t *opts);
void SNDSYS_add100hzclient(void (*client)(void));
void SNDSYS_remove100hzclient(void (*client)(void));
int SNDCTRL_drylevel(int handle, int level);
int SNDmemlimits(unsigned int start, unsigned int end);
int iSNDpatchkey(int handle, int *cursor);
int SNDpitchmult(int handle, int pitch);
int SNDplaysetdef(SndPlayOpts_t *opts);
int SNDPROFILE_outputlatency(void);
void SNDI_randomseed(unsigned int seed);
unsigned int iSNDrandom(void);
int SNDrelease(int handle);
int SNDBANKI_asyncresolvepatch(int mask, void *patch, int base, int *count);
int fn_801B9410(void *handle, void *params);
void SNDSYSI_variabletimerservice(void);
void SNDSYSI_100hzserver(void);
int iSNDsin(int angle);
int SNDMEM_gethighwater(void);
void SNDMEMI_constrain(unsigned int *start, int *size);
void SNDMEMI_init(void *memory, int size);
int SNDMEMI_restore(void);

}

#endif
