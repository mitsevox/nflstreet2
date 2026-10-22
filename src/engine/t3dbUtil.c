#include "engine/t3db.h"

void fn_8020CCBC(TDbLitRef_80205754 *pLits, unsigned long long *pOut)
{
    unsigned char i = 0;

    do {
        pOut[i] = ((unsigned long long)pLits[i].mTableId << 32) | (unsigned int)pLits[i].mId;
    } while (pLits[i++].mId != -1);
}
