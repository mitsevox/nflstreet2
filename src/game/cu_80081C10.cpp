#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"

extern "C" {
int fn_800808F8(Object_8008044C *pObject);
}

static int lbl_803EA7D0[2] = { 0x31414850, 0x43484650 };

extern "C" void fn_80081C10(Object_8008044C *pObject, unsigned char *p)
{
    ColumnValue_802D6424 columns[3];
    int i;

    fn_800808F8(pObject);
    for (i = 0; i < 2; ++i) {
        columns[i].Set(0x59414C50, lbl_803EA7D0[i], 0);
    }
    columns[2].SetEnd();
    pObject->Read(columns);
    for (i = 0; i < 2; ++i) {
        p[i] = columns[i].mValue;
    }
    p[0] += 0x80;
    p[1] += 0x80;
}
