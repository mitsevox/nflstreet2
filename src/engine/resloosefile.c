/* Loose resource files: builds the "looseres\<resource>\<index>" path of a resource entry stored
   as a separate file on disk, and checks whether it exists, gets its size and opens it. */

#include "engine/Resource.h"

extern int sprintf(char *buffer, const char *format, ...);
extern int fn_801C96E4(const char *pName, int device);
extern int fn_801C97F0(int handle);
extern int fn_801C9910(const char *pName, int device);
extern int fn_801C9D18(int handle);

extern char lbl_802B19AC[];
extern char lbl_802B19B0[];
extern char lbl_802B19B8[];
extern char lbl_803E933C[];
extern ResFile_t *lbl_803EBDE8;
extern int lbl_803EBDEC;

static void _ResLooseFileGetName(ResFile_t *pFile, int index)
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

int ResLooseFileExists(ResFile_t *pFile, int index)
{
    _ResLooseFileGetName(pFile, index);
    return fn_801C9910(lbl_803E933C, 0x2C) == 0;
}

int ResLooseFileGetSize(ResFile_t *pFile, unsigned int index, unsigned int *pSize)
{
    int result = 1;
    int handle;

    _ResLooseFileGetName(pFile, index);
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

int ResLooseFileOpen(ResFile_t *pFile, int index)
{
    int handle;

    _ResLooseFileGetName(pFile, index);
    if (fn_801C9910(lbl_803E933C, 0x2C) == 0) {
        handle = fn_801C96E4(lbl_803E933C, 0x2C);
    } else {
        handle = -1;
    }
    return handle;
}
