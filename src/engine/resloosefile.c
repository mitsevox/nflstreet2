typedef struct ResLooseFile_801F3308 {
    int mUnknown0;
    char *pName;
} ResLooseFile_801F3308;

extern int sprintf(char *buffer, const char *format, ...);
extern int fn_801C96E4(char *name, int mode);
extern int fn_801C97F0(int handle);
extern int fn_801C9910(char *name, int mode);
extern int fn_801C9D18(int handle);

extern char lbl_802B19AC[];
extern char lbl_802B19B0[];
extern char lbl_802B19B8[];
extern char lbl_803E933C[];
extern ResLooseFile_801F3308 *lbl_803EBDE8;
extern int lbl_803EBDEC;

static void fn_801F3308(ResLooseFile_801F3308 *pFile, int index)
{
    char name[5];
    char *p;

    if (pFile == lbl_803EBDE8 && index == lbl_803EBDEC) {
        return;
    }
    sprintf(name, lbl_802B19AC, index);
    for (p = name; *p == ' '; p++) {
        *p = '0';
    }
    sprintf(lbl_803E933C, lbl_802B19B0, lbl_802B19B8, pFile->pName, name);
    lbl_803EBDE8 = pFile;
    lbl_803EBDEC = index;
}

int fn_801F33B8(ResLooseFile_801F3308 *pFile, int index)
{
    fn_801F3308(pFile, index);
    return fn_801C9910(lbl_803E933C, 0x2C) == 0;
}

int fn_801F33F0(ResLooseFile_801F3308 *pFile, int index, int *pSize)
{
    int result = 1;
    int handle;

    fn_801F3308(pFile, index);
    if (fn_801C9910(lbl_803E933C, 0x2C) == 0) {
        handle = fn_801C96E4(lbl_803E933C, 0x2C);
        if (handle >= 0) {
            *pSize = fn_801C9D18(handle);
            fn_801C97F0(handle);
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    return result;
}

int fn_801F346C(ResLooseFile_801F3308 *pFile, int index)
{
    int handle;

    fn_801F3308(pFile, index);
    if (fn_801C9910(lbl_803E933C, 0x2C) == 0) {
        handle = fn_801C96E4(lbl_803E933C, 0x2C);
    } else {
        handle = -1;
    }
    return handle;
}
