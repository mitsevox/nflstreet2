/* Speech library utility (sputil.c): the table of external vectors that the game fills in. */

#include "engine/spchlib.h"

extern "C" {

extern SpchExtVecs_t gExtVecs;

SpchExtVecs_t *SPCH_GetExtVecs(void)
{
    return &gExtVecs;
}
}
