#include "game/Record_802CC680.h"

static Record_802CC680 lbl_802CC680[8] = {
    { "MAIN", 1, 0, 0, 0x200A00 },
    { "DB", 2, 0, 0x104000, 0x80A00 },
    { "DEBUG", 8, 0, 0, 0x200A00 },
    { "STATE", 4, 0, 0x44000, 0x200A00 },
    { "MISC", 0x20, 0, 0x7000, 0x200A00 },
    { "AUXRAM", 0x10, 0, 0xAFC000, 0x200A00 },
    { "SOUND", 0x100, 0, 0x3800, 0x100A00 },
    { "UNLOAD", 0x40, 0, 0, 0x200A00 },
};

extern "C" {

Record_802CC680 *fn_80025E50(unsigned int id)
{
    Record_802CC680 *pRecord = 0;

    switch (id) {
    case 1:
        pRecord = &lbl_802CC680[0];
        break;
    case 2:
        pRecord = &lbl_802CC680[1];
        break;
    case 8:
        pRecord = &lbl_802CC680[2];
        break;
    case 4:
        pRecord = &lbl_802CC680[3];
        break;
    case 0x20:
        pRecord = &lbl_802CC680[4];
        break;
    case 0x10:
        pRecord = &lbl_802CC680[5];
        break;
    case 0x100:
        pRecord = &lbl_802CC680[6];
        break;
    case 0x40:
        pRecord = &lbl_802CC680[7];
        break;
    }
    return pRecord;
}

void fn_80025F20(void)
{
}

}
