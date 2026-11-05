/* The Module base class: the default hooks that run before and after every game module starts and stops. */

#include "game/Module.h"

static void (*sCallback)(void *) = 0;

void Module::GSPreModuleStart(void *pArg) {}

void Module::GSPostModuleStart(void *pArg)
{
    if (sCallback) {
        sCallback(pArg);
    }
}

void Module::GSPreModuleStop(void *pArg) {}
void Module::GSPostModuleStop(void *pArg) {}
