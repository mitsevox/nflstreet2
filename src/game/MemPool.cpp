/* The table of named memory pools (MAIN, DB, STATE, SOUND and others) and the lookup of a pool by its id. */

#include "game/MemPoolDesc.h"

static MemPoolDesc _MemPool_aDesc[8] = {
    { "MAIN", 1, 0, 0, 0x200A00 },
    { "DB", 2, 0, 0x104000, 0x80A00 },
    { "DEBUG", 8, 0, 0, 0x200A00 },
    { "STATE", 4, 0, 0x44000, 0x200A00 },
    { "MISC", 0x20, 0, 0x7000, 0x200A00 },
    { "AUXRAM", 0x10, 0, 0xAFC000, 0x200A00 },
    { "SOUND", 0x100, 0, 0x3800, 0x100A00 },
    { "UNLOAD", 0x40, 0, 0, 0x200A00 },
};

extern "C" {

MemPoolDesc *MemPoolGetDesc(unsigned int id)
{
    MemPoolDesc *pRecord = 0;

    switch (id) {
    case 1:
        pRecord = &_MemPool_aDesc[0];
        break;
    case 2:
        pRecord = &_MemPool_aDesc[1];
        break;
    case 8:
        pRecord = &_MemPool_aDesc[2];
        break;
    case 4:
        pRecord = &_MemPool_aDesc[3];
        break;
    case 0x20:
        pRecord = &_MemPool_aDesc[4];
        break;
    case 0x10:
        pRecord = &_MemPool_aDesc[5];
        break;
    case 0x100:
        pRecord = &_MemPool_aDesc[6];
        break;
    case 0x40:
        pRecord = &_MemPool_aDesc[7];
        break;
    }
    return pRecord;
}

void MemPoolRelease(int a)
{
}

}
