#include "engine/cu_801D86B4.h"

/* VP6 chunk identifiers: 'MVhd' (header), 'MV0F' and 'MV0K' (frames). */

int fn_801DC9C8(int id)
{
    return id == 0x4D566864;
}

int fn_801DC9E0(int id)
{
    if (id == 0x4D563046 || id == 0x4D56304B) {
        return 1;
    }
    return 0;
}
