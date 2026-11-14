/* Speech library utility (sputil.c): the table of external vectors that the game fills in. */

#include "engine/spchlib.h"

extern "C" {

SpchExtVecs_t gExtVecs = {0};

SpchExtVecs_t *SPCH_GetExtVecs(void)
{
    return &gExtVecs;
}
}
