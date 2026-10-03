#include "game/Module.h"

static void (*sCallback)(void *) = 0;

void Module::fn_80025F24() {}

void Module::fn_80025F28(void *pArg)
{
    if (sCallback) {
        sCallback(pArg);
    }
}

void Module::fn_80025F5C() {}
void Module::fn_80025F60() {}
