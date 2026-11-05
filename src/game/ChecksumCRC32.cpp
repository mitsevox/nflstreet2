/* CRC-32 checksum: builds the lookup table, folds data into the running value and returns
   the final checksum. */

#include "game/fn_801D2B7C.h"
extern "C" {
}

struct ChecksumCRC32State {
    unsigned int *mpTable;
    unsigned int mValue;
};

static ChecksumCRC32State _ChecksumCRC32_State;

extern "C" {
static unsigned int _ChecksumCRC32_Calculate(unsigned int value)
{
    unsigned char bit = 8;

    do {
        if (value & 1) {
            value = (value >> 1) ^ 0xEDB88320;
        } else {
            value >>= 1;
        }
    } while (--bit != 0);
    return value;
}

static void _ChecksumCRC32_CreateLookupTable(unsigned int *pTable)
{
    unsigned int i;

    for (i = 0; i < 256; i++) {
        pTable[i] = _ChecksumCRC32_Calculate(i);
    }
}

void ChecksumCRC32Begin(void)
{
    _ChecksumCRC32_State.mpTable = (unsigned int *)fn_801D2B7C(1024, 0, 0);
    _ChecksumCRC32_CreateLookupTable(_ChecksumCRC32_State.mpTable);
    _ChecksumCRC32_State.mValue = 0xFFFFFFFF;
}

void ChecksumCRC32Update(void *pData, unsigned int size)
{
    unsigned int crc = _ChecksumCRC32_State.mValue;
    unsigned int i;

    for (i = 0; i < size; i++) {
        crc = (crc >> 8) ^ _ChecksumCRC32_State.mpTable[(crc & 0xFF) ^ ((unsigned char *)pData)[i]];
    }
    _ChecksumCRC32_State.mValue = crc;
}

void ChecksumCRC32End(unsigned int *pResult)
{
    fn_801D2BD0(_ChecksumCRC32_State.mpTable);
    _ChecksumCRC32_State.mpTable = 0;
    if (pResult != 0) {
        *pResult = ~_ChecksumCRC32_State.mValue;
    }
}
}
