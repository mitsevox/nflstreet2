/*
 * Shared helpers of the game's database modules. One random-number stream, created when the
 * game database starts and deleted when it stops, gives the random values the database code and
 * the game ask for within a range; and every database module allocates and frees its memory here,
 * either from the database heap that the system start-up sets or from the default heap.
 */
#include "engine/dbutil.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"

static void *_DbUtil_pRandomStream = 0;
static int _DbUtil_iHeap = 0;

void DbUtilRandomInit(void)
{
    _DbUtil_pRandomStream = MathNewRandomStream(0, MathGetRandomSeed());
}

void DbUtilRandomShutdown(void)
{
    MathDelRandomStream(_DbUtil_pRandomStream);
    _DbUtil_pRandomStream = 0;
}

int DbUtilRandomRange(unsigned int low, unsigned int high)
{
    if (low < high) {
        return low + MathGetRandomRange(_DbUtil_pRandomStream, high - low);
    }
    return low;
}

void DbUtilSetHeap(int heap)
{
    _DbUtil_iHeap = heap;
}

void *DbUtilAlloc(int size, int bUseHeap)
{
    void *p;

    if (bUseHeap != 0) {
        p = fn_801D2BB0(_DbUtil_iHeap, size, 0, 0);
    } else {
        p = fn_801D2B7C(size, 0, 0);
    }
    return p;
}

void DbUtilFree(void *p)
{
    fn_801D2BD0(p);
}
