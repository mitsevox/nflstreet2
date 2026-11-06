/* Stat generator module support: creates the clock-seeded random-number
   stream the StatGen module uses while it runs and deletes it when the
   module shuts down. */
#include "game/StatGen.h"
#include "engine/rand.h"

static void *_StatGen_pRandomStream = 0;

void StatGenCreateRandomStream(void)
{
    _StatGen_pRandomStream = MathNewRandomStream(0, MathGetRandomSeed());
}

int StatGenDestroyRandomStream(void)
{
    int result = MathDelRandomStream(_StatGen_pRandomStream);
    _StatGen_pRandomStream = 0;
    return result;
}
