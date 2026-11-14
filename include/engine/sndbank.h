#ifndef ENGINE_SNDBANK_H
#define ENGINE_SNDBANK_H

/* Declarations shared by the sound-library files in 0x8026A664-0x8026D200: the bank files
   (sballoc.c to sbvalid.c), the play-option, client, server and utility files after them. */

#include "engine/sndlib.h"

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

/* The sample-format record of a patch (+0x2 its channel count). */
typedef struct SndSampleFormat_t {
    unsigned char m0;
    unsigned char m1;
    unsigned char m2;
} SndSampleFormat_t;

/* The sample-attribute record of a patch: per-channel buffers +0x18 and their sizes +0x30. */
typedef struct SndSampleAttr_t {
    unsigned char unk_0x0[0x18];
    void *m18[6];
    int m30[6];
} SndSampleAttr_t;

/* The play options record that SNDplaysetdef fills. */
typedef struct SndPlayOpts_t {
    unsigned char m0;
    unsigned char m1;
    unsigned char m2;
    unsigned char m3;
    unsigned char m4;
    unsigned char m5;
    unsigned char unk_0x6[2];
    unsigned short m8;
    unsigned short mA;
    unsigned short mC;
    unsigned short mE;
    unsigned short m10;
    unsigned char unk_0x12[2];
    short m14;
    unsigned short m16;
} SndPlayOpts_t;

extern "C" {

void *fn_801C2030(void *dst, const void *src, unsigned int n);

int fn_8026A288(int handle);
void fn_8026A40C(void *message, int value);
int fn_80270B10(BankVer_t *bank, void *patch, int bank_index, int patch_index, SndPlayOpts_t *opts);
void fn_80274924(int index);
void fn_80277EC4(int index);
int fn_80270E04(char **cursor, Struct_80270E04 *out);
void fn_80278598(int index);
void SNDstop(int handle);
int fn_8026C3F4(BankVer_t *bank, void *patch, SndSampleFormat_t *format, SndSampleAttr_t *attr, void *desc,
                unsigned char *out);

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
int fn_80278894(void);
void SNDMEMI_constrain(unsigned int *start, int *size);
void SNDMEMI_init(void *memory, int size);
void SNDMEMI_restore(void);

}

#endif
