#include "game/Object_8003DEC4.h"
#include "game/fn_80233CBC.h"

extern "C" {
static int lbl_802E32B0[31][2] = {
    {2, 6},
    {1, 4},
    {1, 4},
    {1, 4},
    {1, 6},
    {13, 0},
    {4, 0},
    {9, 0},
    {9, 0},
    {10, 0},
    {7, 0},
    {7, 0},
    {12, 2},
    {12, 3},
    {4, 0},
    {6, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {52, 1},
    {52, 1},
    {3, 1},
    {1, 1},
    {1, 1},
    {1, 1},
    {1, 8},
    {1, 8},
    {1, 7},
    {1, 0},
    {1, 11},
    {1, 11},
};

int fn_801600FC(int index, int key);

void fn_8015FFC8(int index, int key, int value)
{
    Object_8003DEC4 *pObject = fn_8003DEC4(index);
    fn_80233CBC(pObject->mUnknown992 + lbl_802E32B0[key][1] * 240 + 192, key, value);
    switch (key) {
    case 6:
        fn_80233CBC(&pObject->mUnknown992[2592], 6, value);
        break;
    case 25:
    case 26:
        if (fn_801600FC(index, 27) != 255)
            fn_80233CBC(&pObject->mUnknown992[2112], key, value);
        else
            fn_80233CBC(&pObject->mUnknown992[2112], key, 255);
        break;
    case 27:
        fn_80233CBC(&pObject->mUnknown992[1872], key, value);
        break;
    case 28:
        fn_80233CBC(&pObject->mUnknown992[2352], 28, value);
        break;
    case 29:
    case 30:
        fn_80233CBC(&pObject->mUnknown992[2832], key, value);
        break;
    case 0:
        fn_80233CBC(&pObject->mUnknown992[1632], 0, value);
        break;
    case 5:
    default:
        break;
    }
}

int fn_801600FC(int index, int key)
{
    Object_8003DEC4 *pObject = fn_8003DEC4(index);
    return (unsigned char)(pObject->mUnknown992 + 200)[lbl_802E32B0[key][1] * 240 + key];
}
}
