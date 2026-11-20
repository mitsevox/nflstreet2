/* Memory compare and CRC-32: a memcmp wrapper and the table-driven CRC-32
   the game uses to checksum its state. */

#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
#include "engine/fn_80238680.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

extern unsigned int lbl_802FB464[256];
extern int fn_80238278(const void *p, int size, int seed);

int fn_80238258(const void *pA, const void *pB, unsigned int size)
{
    return memcmp(pA, pB, size);
}

int fn_80238278(const void *p, int size, int seed)
{
    const unsigned char *pBytes = p;
    unsigned int value = ~seed;
    while (size-- != 0) {
        value = lbl_802FB464[(value ^ *pBytes++) & 255] ^ (value >> 8);
    }
    return ~value;
}
