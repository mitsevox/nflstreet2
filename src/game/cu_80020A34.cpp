#include "game/Block_80063910.h"
#include "game/fn_80063A0C.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include "game/fn_80072AA8.h"

extern "C" {
void fn_80020A34(void)
{
    fn_80072AA8();
    fn_80072F90();
}

void fn_80020A58(unsigned int index, int value)
{
    int id = fn_80063A0C(index);

    if (id != 24) {
        fn_8007F6F8(id, value);
    }
}

int fn_80020A94(unsigned int index)
{
    int result = 0;
    int id = fn_80063A0C(index);

    if (id != 24) {
        result = fn_8007F828(id);
    }
    return result;
}

void fn_80020AD4(void) {}
void fn_80020AD8(void) {}

int fn_80020ADC(unsigned int id, Block_80063910 *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80020AD8();
        break;
    case 0x80000002:
        fn_80020AD4();
        break;
    case 0x80000003:
        *pResult = fn_80020A94(pBlock->mUnknown0);
        break;
    case 0x80000005:
        fn_80020A58(pBlock->mUnknown0, pBlock->mUnknown4);
        break;
    case 0x80000004:
        fn_80020A34();
        break;
    default:
        return 0;
    }
    return 1;
}
}
