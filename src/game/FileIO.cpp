#include "game/Module.h"

/* Copied whole by FileInit, which sizes two per-entry allocations by mCount;
   FileCreateAbsoluteFileName copies a string from offset 0, 128, 512 or 640, chosen by its fourth argument. */
struct FileIOConfig {
    char mUnknown0[1024];
    int mUnknown1024;
    unsigned int mCount;
    unsigned char mUnknown1032;
};

/* FileOpenFileDevice passes each mUnknown0[i], mUnknown32[i] pair to FileOpenhDevice. */
struct FileIOList {
    int mUnknown0[8];
    const char *mUnknown32[8];
    int mCount;
};

/* Argument of FileSetDeviceList, which falls back to a default table when given null. */
struct FileIOListTable {
    FileIOList *mpLists[8];
    int mUnknown32;
};

extern "C" {

int FileSetDeviceList(FileIOListTable *pTable);
int FileSetDefaultDevice(int unknown);
int FileInit(FileIOConfig *pConfig);
void FileAsyncSetErrorGameName(const char *pTitle);
int FileShutdown(void);
}

static FileIOConfig sConfig = { "", 80, 42, 1 };
static FileIOList sList = { { 1 }, { "/" }, 1 };
static FileIOListTable sListTable = { { &sList }, 1 };

static ModuleDependency sDependencies[] = { &gMat, &gVpt, 0 };
FileIO gFileIO;

ModuleDependency *FileIO::GetDependencies() { return sDependencies; }
ModuleDependency *FileIO::GetLinks() { return 0; }
const char *FileIO::GetName() { return "FileIO"; }

static const char *sTitle = "NFL STREET 2";

int FileIO::Init()
{
    FileSetDeviceList(&sListTable);
    FileSetDefaultDevice(0);
    FileInit(&sConfig);
    FileAsyncSetErrorGameName(sTitle);
    return 1;
}

int FileIO::Shutdown()
{
    FileShutdown();
    return 1;
}
