/* Registers AEMS sound-module banks and initializes the sound module player's shared state. */

#include "engine/sndaems_state.h"

struct BankVer_t;

extern "C" {

typedef struct SndAemsModuleBank_t {
    unsigned char unk_0x0[0x14];
    int mAllocArgument;
    int mHeaderSize;
    unsigned char unk_0x1C[4];
    int mBankOffsetA;
    int mBankSizeA;
    int mBankOffsetB;
    int mBankSizeB;
    int mFixupHeaderOffset;
    unsigned char unk_0x34[8];
    int mHandle;
    int mBankA;
    int mBankB;
} SndAemsModuleBank_t;

int SNDAEMSI_createmodulebankhandle(void);
void SNDAEMSI_resolvemodulebank(SndAemsModuleBank_t *bank, void *modules, char *name, int arg);
int SNDbankadd(int *handle, BankVer_t *bank);
int SNDbankheadersize(int bank);
int SNDbankheadercopy(void *dst, int bank);
int SNDbankremove(int bank);
void SNDI_memcpy(void *dst, const void *src, int size);

int SNDAEMS_addmodulebank(SndAemsModuleBank_t *data, char *name, int arg,
                          void *(*alloc)(void *, int, int))
{
    SndAemsModuleBank_t *bank;
    SndAemsModuleBank_t *moved;
    int resultA = 0;
    int resultB = 0;
    int size;
    int sizeB;
    int result;

    bank = data;
    if (sndaems.mpBeforeAddBank != 0) {
        sndaems.mpBeforeAddBank();
    }
    data->mHandle = SNDAEMSI_createmodulebankhandle();
    if (data->mBankOffsetA != 0) {
        resultA = SNDbankadd(&data->mBankA, (BankVer_t *)((char *)data + data->mBankOffsetA));
        if (resultA < 0) {
            result = resultA;
            goto fail;
        }
    }
    if (data->mBankOffsetB != 0) {
        resultB = SNDbankadd(&data->mBankB, (BankVer_t *)((char *)data + data->mBankOffsetB));
        if (resultB < 0) {
            result = resultB;
            goto fail;
        }
    }
    result = data->mHeaderSize;
    if (resultA == 7) {
        result += SNDbankheadersize(data->mBankA);
    } else {
        result += data->mBankSizeA;
    }
    if (resultB == 7) {
        sizeB = SNDbankheadersize(data->mBankB);
    } else {
        sizeB = data->mBankSizeB;
    }
    size = result;
    result = (int)alloc(data, size + sizeB, data->mAllocArgument);
    if (result == 0) {
        result = -6;
        goto fail;
    }
    moved = (SndAemsModuleBank_t *)result;
    if (moved != data) {
        SNDI_memcpy(moved, data, data->mHeaderSize);
        bank = moved;
    }
    if (resultA != 0 && moved != data) {
        SNDbankheadercopy((char *)bank + bank->mHeaderSize, bank->mBankA);
    }
    if (resultB > 0 && (moved != data || resultA == 7)) {
        SNDbankheadercopy((char *)moved + size, bank->mBankB);
    }
    SNDAEMSI_resolvemodulebank(bank, (char *)data + bank->mFixupHeaderOffset, name, arg);
    return bank->mHandle;

fail:
    if (resultA > 0) {
        SNDbankremove(data->mBankA);
    }
    if (resultB > 0) {
        SNDbankremove(data->mBankB);
    }
    return result;
}

SndAemsState_t sndaems;
}
