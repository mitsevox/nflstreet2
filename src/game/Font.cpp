#include "game/Module.h"

struct FontParams_t {
    int mMaxFonts;
    int mUnk4;
    int mHeap;
    unsigned short mUnkC;
    unsigned short mUnkE;
};

static FontParams_t _Font_Params = {11, 1, 1, 640, 480};

extern "C" {
extern char lbl_802EBE50[];

int FontInit(void *);
void FileInitErrorMessages(const char *, int);
int FontShutdown(void);
}

static ModuleDependency sDependencies[] = { &gSys, &gRes, 0 };
Font gFont;

ModuleDependency *Font::GetDependencies() { return sDependencies; }
ModuleDependency *Font::GetLinks() { return 0; }
const char *Font::GetName() { return "Font"; }

int Font::Init()
{
    FontInit(&_Font_Params);
    FileInitErrorMessages(lbl_802EBE50, 3);
    return 1;
}

int Font::Shutdown()
{
    FontShutdown();
    return 1;
}
