#include "game/Module.h"

/* Copied whole by fn_801C93D0, which sizes two per-entry allocations by mCount;
   fn_801C92B8 copies a string from offset 0, 128, 512 or 640, chosen by its fourth argument. */
struct FileIOConfig {
    char mUnknown0[1024];
    int mUnknown1024;
    unsigned int mCount;
    unsigned char mUnknown1032;
};

/* fn_801C96E4 passes each mUnknown0[i], mUnknown32[i] pair to fn_801CA364. */
struct FileIOList {
    int mUnknown0[8];
    const char *mUnknown32[8];
    int mCount;
};

/* Argument of fn_801C9D40, which falls back to a default table when given null. */
struct FileIOListTable {
    FileIOList *mpLists[8];
    int mUnknown32;
};

extern "C" {

int fn_801C9D40(FileIOListTable *pTable);
int fn_801C9D6C(int unknown);
int fn_801C93D0(FileIOConfig *pConfig);
void fn_801CA8D4(const char *pTitle);
int fn_801C95C4(void);
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
    fn_801C9D40(&sListTable);
    fn_801C9D6C(0);
    fn_801C93D0(&sConfig);
    fn_801CA8D4(sTitle);
    return 1;
}

int FileIO::Shutdown()
{
    fn_801C95C4();
    return 1;
}
