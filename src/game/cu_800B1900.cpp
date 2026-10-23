#include "game/Block_800B21D0.h"
#include "game/fn_801FCE10.h"

extern "C" void fn_800B1900(Block_800B21D0 *p)
{
    int codes[11] = {
        'SFPO', 'OHPO', 'MFPO', 'POPO', 'PDPO', 'IPPO',
        'FPPO', 'LCPO', 'GIPO', 'PRPO', 'KRPO',
    };
    int value;

    for (unsigned char i = 0; i <= 10; i++) {
        fn_801FCE10(0, "select \x8c into \x82 from 'TPOG'\n", codes[i], &value);
        p->mUnknown4.mUnknown4E[i] = value;
    }
}
