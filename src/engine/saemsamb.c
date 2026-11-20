/* Partial source of the sound library's module bank registration (saemsamb.c). */


extern "C" {
typedef struct Object_803A6BCC {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8[32];
    int mUnknown28;
    int mUnknown2C;
    void (*mpLockCallback)(void);
} Object_803A6BCC;

extern Object_803A6BCC lbl_803A6BCC;

typedef struct SndAemsModuleBank_t {
    unsigned char unk_0x0[0x14];
    int mAllocParam;
    int mHeaderSize;
    unsigned char unk_0x1C[4];
    int mBankOffsetA;
    int mBankSizeA;
    int mBankOffsetB;
    int mBankSizeB;
    int mModuleOffset;
    unsigned char unk_0x34[8];
    int mHandle;
    int mBankA;
    int mBankB;
} SndAemsModuleBank_t;

int fn_80269484(void);
void fn_802694AC(SndAemsModuleBank_t *bank, void *modules, char *name, int arg);
int fn_8026A4D4(int *pHandle, void *pData);
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
    if (lbl_803A6BCC.mpLockCallback != 0) {
        lbl_803A6BCC.mpLockCallback();
    }
    data->mHandle = fn_80269484();
    if (data->mBankOffsetA != 0) {
        resultA = fn_8026A4D4(&data->mBankA, (char *)data + data->mBankOffsetA);
        if (resultA < 0) {
            result = resultA;
            goto fail;
        }
    }
    if (data->mBankOffsetB != 0) {
        resultB = fn_8026A4D4(&data->mBankB, (char *)data + data->mBankOffsetB);
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
    result = (int)alloc(data, size + sizeB, data->mAllocParam);
    if (result == 0) {
        result = -6;
        goto fail;
    }
    moved = (SndAemsModuleBank_t *)result;
    if (moved != data) {
        bank = moved;
        SNDI_memcpy(moved, data, data->mHeaderSize);
        if (resultA != 0) {
            SNDbankheadercopy((char *)bank + bank->mHeaderSize, bank->mBankA);
        }
    }
    if (resultB > 0 && (moved != data || resultA == 7)) {
        SNDbankheadercopy((char *)moved + size, bank->mBankB);
    }
    fn_802694AC(bank, (char *)data + bank->mModuleOffset, name, arg);
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

void fn_80269990(int a, int b)
{
    if (b == 0xFFFF && a != 0) {
        lbl_803A6BCC.mUnknown0 = 0;
        lbl_803A6BCC.mUnknown4 = 0;
        lbl_803A6BCC.mUnknown28 = 0;
        lbl_803A6BCC.mUnknown2C = 0;
    }
}

void fn_802699C8(void)
{
    fn_80269990(1, 0xFFFF);
}
}
