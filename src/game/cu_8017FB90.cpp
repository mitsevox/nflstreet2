#include "game/cu_8017F90C.h"
#include "game/InGame.h"
#include "game/cu_80064864.h"

extern "C" {
unsigned char fn_8018631C(void);
}

extern "C" int lbl_803EB52C;

// Message handler offered to fn_8017F90C: returns nonzero for the ids it handles.
extern "C" int fn_8017FB90(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0xC3:
        fn_800282DC();
        fn_800652A8();
        break;
    case 0xBF:
    case 0xE2:
        *pResult = 1;
        break;
    case 0x199:
        *pResult = fn_8018631C();
        break;
    case 0x00:
        *pResult = 0;
        break;
    case 0xE3:
    case 0xEA:
        *pResult = 0;
        break;
    case 0x8D:
    case 0xB3:
    case 0xE4:
    case 0xE9:
    case 0x130:
    case 0x13B:
    case 0x13F:
    case 0x145:
    case 0x18E:
    case 0x1A0:
        *pResult = 0;
        break;
    case 0x141:
        *pResult = lbl_803EB52C > 2;
        break;
    case 0x41:
    case 0x85:
    case 0x86:
    case 0xB5:
    case 0xB6:
    case 0xBE:
    case 0xC0:
    case 0xC1:
    case 0xC2:
    case 0xC5:
    case 0xD8:
    case 0xD9:
    case 0xE1:
    case 0xE5:
    case 0xE6:
    case 0xE7:
    case 0xE8:
    case 0xEB:
    case 0xEC:
    case 0xEE:
    case 0xEF:
    case 0xF3:
    case 0xF4:
    case 0x119:
    case 0x120:
    case 0x121:
    case 0x131:
    case 0x135:
    case 0x13D:
    case 0x140:
    case 0x142:
        break;
    default:
        return 0;
    }
    return 1;
}
