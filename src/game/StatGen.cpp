/* Stat generator module support: creates the clock-seeded random-number
   stream the StatGen module uses while it runs and deletes it when the
   module shuts down, and holds the record of the game the stat generator
   simulates (the game keeps none of its simulation functions). */
#include "game/StatGen.h"
#include "engine/rand.h"

static void *_StatGen_pRandomStream = 0;

typedef struct StatGenGame_t {
    unsigned char unk_0x0[0x27D4];
} StatGenGame_t;

static StatGenGame_t _StatGen_sGame;

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
