/* Loose resource files: builds the "looseres\<resource>\<index>" path of a resource entry stored
   as a separate file on disk, and checks whether it exists, gets its size and opens it. */

#include "engine/Resource.h"

extern int sprintf(char *buffer, const char *format, ...);
extern int FileOpenFileDevice(const char *pName, int device);
extern int FileClose(int handle);
extern int FileExistsFileDevice(const char *pName, int device);
extern int FileGetLength(int handle);

char _ResLooseFile_PathName[255];

static void _ResLooseFileGetName(ResFile_t *pFile, int index)
{
    static ResFile_t *_ResLooseFile_PrevRes = 0;
    static int _ResLooseFile_PrevIndex = -1;
    char name[5];
    char *p;

    if (pFile == _ResLooseFile_PrevRes && index == _ResLooseFile_PrevIndex) {
        return;
    }
    sprintf(name, "%4X", index);
    for (p = name; *p == ' '; p++) {
        *p = '0';
    }
    sprintf(_ResLooseFile_PathName, "%s%s\\%s", "looseres\\", pFile->pName, name);
    _ResLooseFile_PrevRes = pFile;
    _ResLooseFile_PrevIndex = index;
}

int ResLooseFileExists(ResFile_t *pFile, int index)
{
    _ResLooseFileGetName(pFile, index);
    return FileExistsFileDevice(_ResLooseFile_PathName, 0x2C) == 0;
}

int ResLooseFileGetSize(ResFile_t *pFile, unsigned int index, unsigned int *pSize)
{
    int result = 1;
    int handle;

    _ResLooseFileGetName(pFile, index);
    if (FileExistsFileDevice(_ResLooseFile_PathName, 0x2C) == 0) {
        handle = FileOpenFileDevice(_ResLooseFile_PathName, 0x2C);
        if (handle >= 0) {
            *pSize = FileGetLength(handle);
            FileClose(handle);
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
    if (FileExistsFileDevice(_ResLooseFile_PathName, 0x2C) == 0) {
        handle = FileOpenFileDevice(_ResLooseFile_PathName, 0x2C);
    } else {
        handle = -1;
    }
    return handle;
}
