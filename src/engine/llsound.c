typedef struct SndBank_801F5034 {
    char mUnknown0[12];
    void *pData;
    int mUnknown10;
    void *pBank;
} SndBank_801F5034;

typedef struct SndBankEntry_801F50C8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} SndBankEntry_801F50C8;

extern void *fn_801D2BB0(int heap, int size, int ident, int flags);
extern int fn_801D2BD0(void *p);
extern void *fn_801D310C(void *pAddr, int size, int ident, int flags);
extern void fn_8026A980(void *pDest, void *pBank);
extern int fn_8026A9F4(void *pBank);
extern void fn_8026B4D8(int a, int b);

extern int lbl_803EBE18;

void fn_801F5034(SndBank_801F5034 *pBank, int move)
{
    void *pData;

    if (move) {
        pData = fn_801D2BB0(lbl_803EBE18, fn_8026A9F4(pBank->pBank), 0, 0);
        fn_8026A980(pData, pBank->pBank);
        fn_801D2BD0(pBank->pData);
    } else {
        pData = fn_801D310C(pBank->pData, fn_8026A9F4(pBank->pBank), 0, 0);
        pBank->pData = pData;
    }
    pBank->pData = pData;
}

void fn_801F50C8(SndBankEntry_801F50C8 *pEntries, int index)
{
    fn_8026B4D8(pEntries[index].mUnknown4, pEntries[index].mUnknown8);
}

void fn_801F50F8(int heap)
{
    lbl_803EBE18 = heap;
}
