/* Stat generator module support: creates the clock-seeded random-number
   stream the StatGen module uses while it runs and deletes it when the
   module shuts down. */
#include "game/StatGen.h"
#include "game/cu_801CF5BC.h"

static void *_StatGen_pRandomStream = 0;

void StatGenCreateRandomStream(void)
{
    _StatGen_pRandomStream = fn_801CF5BC(0, fn_801CF7AC());
}

int StatGenDestroyRandomStream(void)
{
    int result = fn_801CF67C(_StatGen_pRandomStream);
    _StatGen_pRandomStream = 0;
    return result;
}
