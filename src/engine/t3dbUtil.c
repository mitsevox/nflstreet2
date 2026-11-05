/* T3DB helper that packs a list of table/column literals into the 64-bit column references the
   query code works with. */

#include "engine/t3db.h"

void TDbUtilFillTableColRefsForTableColLits(TDbLitRef_t *pLits, unsigned long long *pOut)
{
    unsigned char i = 0;

    do {
        pOut[i] = ((unsigned long long)pLits[i].mTableId << 32) | (unsigned int)pLits[i].mId;
    } while (pLits[i++].mId != -1);
}
