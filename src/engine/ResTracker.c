extern int sprintf(char *s, const char *format, ...);
extern void *fn_801D2BB0(int heap, int size, int c, int d);
extern int fn_801F7ABC(void);

extern int lbl_803EBDB8;
extern char *lbl_803EBDBC;
extern char *lbl_803EBDC0;
extern int lbl_803EBDC4;
extern unsigned char lbl_803EBDC8;
extern int lbl_803EBDCC;
extern unsigned char lbl_803EBDD0;
extern unsigned char lbl_803EBDD1;

typedef struct ResTrackRes_801F23DC {
    int mUnk0;
    char *pName;
} ResTrackRes_801F23DC;

typedef struct ResTrackOpen_801F23DC {
    char *pName;
    char mMode;
} ResTrackOpen_801F23DC;

typedef struct ResTrackLoad_801F23DC {
    ResTrackRes_801F23DC *pRes;
    int mIndex;
    int mOffset;
    int mDiskSize;
    int mFullSize;
    unsigned char mAsync;
    char mMode;
} ResTrackLoad_801F23DC;

extern char lbl_802B1828[];
extern char lbl_802B1834[];
extern char lbl_802B183C[];
extern char lbl_802B1844[];
extern char lbl_802B184C[];
extern char lbl_802B1854[];
extern char lbl_802B1864[];
extern char lbl_802B1874[];
extern char lbl_802B1890[];
extern char lbl_802B18A0[];
extern char lbl_802B18A8[];
extern char lbl_802B18AC[];
extern char lbl_802B18BC[];
extern char lbl_802B18C4[];
extern char lbl_802B18CC[];
extern char lbl_802B18E0[];
extern char lbl_802B18E8[];
extern char lbl_802B18EC[];
extern char lbl_802B1904[];
extern char lbl_802B1914[];
extern char lbl_802B1930[];
extern char lbl_802B1944[];
extern char lbl_802B1954[];
extern char lbl_802B1994[];

int fn_801F2310(void)
{
    if (lbl_803EBDCC > 0) {
        return 1;
    }
    return 0;
}

void fn_801F2328(int heap)
{
    lbl_803EBDC4 = 0;
    lbl_803EBDBC = fn_801D2BB0(heap, lbl_803EBDB8, 0, 0);
    lbl_803EBDC0 = lbl_803EBDBC;
    lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B1828, lbl_802B1834, lbl_802B183C, lbl_802B1844, lbl_802B184C);
    lbl_803EBDCC = 0;
    lbl_803EBDD1 = 1;
}

void fn_801F23B8(int heap, int size)
{
    lbl_803EBDB8 = size;
    fn_801F2328(heap);
}

void fn_801F23DC(unsigned int type, void *pData)
{
    ResTrackLoad_801F23DC *pLoad;
    ResTrackRes_801F23DC *pRes;
    char *pMem;
    char *pName;
    int index;
    char mode;

    if (lbl_803EBDD0 == 1 && lbl_803EBDD1 == 1) {
        pMem = lbl_803EBDBC;
        if (pMem - lbl_803EBDC0 < lbl_803EBDB8 - 100) {
            if (lbl_803EBDC8 != 0) {
                switch (type) {
                case 0:
                    pName = ((ResTrackOpen_801F23DC *)pData)->pName;
                    index = -1;
                    break;
                case 2:
                    pRes = ((ResTrackLoad_801F23DC *)pData)->pRes;
                    index = ((ResTrackLoad_801F23DC *)pData)->mIndex;
                    pName = pRes->pName;
                    break;
                default:
                    pName = 0;
                    index = -1;
                    break;
                }
                if (pName != 0) {
                    lbl_803EBDBC += sprintf(pMem, lbl_802B1854, pName, index, lbl_803EBDC4, fn_801F7ABC());
                }
            } else {
                pLoad = pData;
                switch (type) {
                case 0:
                    if (fn_801F2310() == 0) {
                        mode = ((ResTrackOpen_801F23DC *)pData)->mMode;
                    } else {
                        mode = 'i';
                    }
                    lbl_803EBDBC += sprintf(pMem, lbl_802B1864, mode, fn_801F7ABC(), ((ResTrackOpen_801F23DC *)pData)->pName);
                    break;
                case 1:
                    pRes = pLoad->pRes;
                    lbl_803EBDBC += sprintf(pMem, lbl_802B1874, fn_801F7ABC(), pRes->pName, pLoad->mIndex, pLoad->mIndex);
                    break;
                case 2:
                    pRes = pLoad->pRes;
                    if (fn_801F2310() == 0) {
                        mode = pLoad->mMode;
                    } else {
                        mode = 'i';
                    }
                    lbl_803EBDBC += sprintf(pMem, lbl_802B1890, mode, fn_801F7ABC(), pRes->pName);
                    if (pLoad->mIndex == -1) {
                        lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B18A0);
                    } else {
                        lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B18A8, pLoad->mIndex);
                    }
                    lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B18AC, pLoad->mDiskSize, pLoad->mFullSize,
                                            pLoad->mAsync ? lbl_802B18BC : lbl_802B18C4, pLoad->mOffset);
                    break;
                case 3:
                    pRes = pLoad->pRes;
                    lbl_803EBDBC += sprintf(pMem, lbl_802B18CC, fn_801F7ABC(), pRes->pName);
                    if (pLoad->mIndex == -1) {
                        lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B18E0);
                    } else {
                        lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B18E8, pLoad->mIndex);
                    }
                    break;
                }
            }
            lbl_803EBDC4++;
        }
    }
}

void fn_801F2694(int enable)
{
    lbl_803EBDD0 = enable;
    if (enable == 1) {
        lbl_803EBDBC = lbl_803EBDC0;
        if (lbl_803EBDC8 != 0) {
            lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B18EC);
            lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B1904);
            lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B1914, lbl_802B1844, lbl_802B184C);
        } else {
            lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B1930);
            lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B1944);
            lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B1954);
        }
    }
}

void fn_801F2790(int tide)
{
    lbl_803EBDC8 = tide;
}

void fn_801F2798(char *pLabel)
{
    if (lbl_803EBDD0 == 1 && lbl_803EBDD1 == 1 &&
        lbl_803EBDBC - lbl_803EBDC0 < lbl_803EBDB8 - 100 && lbl_803EBDC8 == 0) {
        lbl_803EBDBC += sprintf(lbl_803EBDBC, lbl_802B1994, fn_801F7ABC(), pLabel);
    }
}

void fn_801F282C(void)
{
    lbl_803EBDCC++;
}

void fn_801F283C(void)
{
    lbl_803EBDCC--;
}
