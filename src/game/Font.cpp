#include "game/Module.h"

extern "C" {
extern char lbl_802CC740[];
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
    FontInit(lbl_802CC740);
    FileInitErrorMessages(lbl_802EBE50, 3);
    return 1;
}

int Font::Shutdown()
{
    FontShutdown();
    return 1;
}
