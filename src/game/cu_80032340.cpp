#include "game/Class_801CBC50.h"
#include "game/Class_801CC350.h"
#include "game/Class_800325E8.h"

extern "C" {
extern char lbl_80306B34[];
}

Class_803067B0 lbl_803067B0;

int Class_803067B0::fn_80032340() { return 4; }

void *Class_803067B0::fn_80032348(int index)
{
    switch (index) {
    case 0:
        return &gSystemGroup;
    case 1:
        return &lbl_803068B4;
    case 2:
        return lbl_80306B34;
    case 3:
        return &gDebugGroup;
    }
    return 0;
}

void Class_803067B0::fn_800323AC() {}
