#include "game/Module.h"

static void *sDependencies[] = { 0 };
Debug gDebug;

ModuleDependency *Debug::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Debug::GetLinks() { return 0; }
const char *Debug::GetName() { return "Debug"; }

int Debug::Init()
{
    return 1;
}

int Debug::Shutdown()
{
    return 1;
}
