#include "game/cu_80026BB0.h"

/* 196-byte record of the array described as Pool_800B8544 in
   cu_8008E978.cpp. */
struct Record_8019A9A0 {
    float mUnknown00;
    float mUnknown04;
    float mUnknown08;
    float mUnknown0C;
    float mUnknown10;
    float mUnknown14;
    float mUnknown18;
    float mUnknown1C;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown2C;
    int mUnknown30;
    float mUnknown34;
    float mUnknown38;
    float mUnknown3C;
    float mUnknown40;
    float mUnknown44;
    float mUnknown48;
    float mUnknown4C;
    float mUnknown50;
    unsigned char mUnknown54[8];
    float mUnknown5C;
    float mUnknown60;
    float mUnknown64;
    float mUnknown68;
    float mUnknown6C;
    float mUnknown70;
    float mUnknown74;
    float mUnknown78;
    float mUnknown7C;
    unsigned char mUnknown80[8];
    float mUnknown88;
    unsigned char mUnknown8C[24];
    float mUnknownA4;
    float mUnknownA8;
    float mUnknownAC;
    float mUnknownB0;
    float mUnknownB4;
    float mUnknownB8;
    unsigned int mUnknownBC;
    unsigned char mActive;
    unsigned char mUnknownC1[3];
};

struct Pool_8019A9A0 {
    Record_8019A9A0 *mpRecords;
    unsigned char mCount;
};

extern Pool_8019A9A0 lbl_803EC930;

extern "C" void fn_8019A9A0(unsigned int index, unsigned int id, float value)
{
    if (index >= lbl_803EC930.mCount) return;
    Record_8019A9A0 *pRecord = &lbl_803EC930.mpRecords[index];
    if (pRecord->mActive != 1) return;
    switch (id) {
    case 0x33:
        pRecord->mUnknown00 = value;
        break;
    case 0x34:
        pRecord->mUnknown04 = value;
        break;
    case 0x35:
        pRecord->mUnknown08 = value;
        break;
    case 0x36:
        pRecord->mUnknown0C = value;
        break;
    case 0x2:
        pRecord->mUnknown10 = value;
        break;
    case 0x3:
        pRecord->mUnknown14 = value;
        break;
    case 0x4:
        pRecord->mUnknown18 = value;
        break;
    case 0x5:
        pRecord->mUnknown1C = value;
        break;
    case 0x10:
        pRecord->mUnknown20 = value;
        break;
    case 0x11:
        pRecord->mUnknown24 = value;
        break;
    case 0x12:
        pRecord->mUnknown28 = value;
        break;
    case 0x13:
        pRecord->mUnknown2C = value;
        break;
    case 0x8f:
        pRecord->mUnknown30 = fn_800272EC(value);
        break;
    case 0xa:
        pRecord->mUnknown44 = value;
        break;
    case 0xb:
        pRecord->mUnknown48 = value;
        break;
    case 0xc:
        pRecord->mUnknown4C = value;
        break;
    case 0xd:
        pRecord->mUnknown50 = value;
        break;
    case 0x15:
        pRecord->mUnknown5C = value;
        break;
    case 0x7:
    case 0x23:
        pRecord->mUnknown38 = value;
        break;
    case 0x8:
    case 0x24:
        pRecord->mUnknown34 = value;
        break;
    case 0x9:
    case 0x25:
        pRecord->mUnknown3C = value;
        break;
    case 0x6:
    case 0x26:
        pRecord->mUnknown40 = value;
        break;
    case 0x3b:
        pRecord->mUnknown70 = value;
        break;
    case 0x3c:
        pRecord->mUnknown74 = value;
        break;
    case 0x3d:
        pRecord->mUnknown78 = value;
        break;
    case 0x3e:
        pRecord->mUnknown7C = value;
        break;
    case 0x41:
        pRecord->mUnknown88 = value;
        break;
    case 0x38:
    case 0x42:
        pRecord->mUnknown64 = value;
        break;
    case 0x39:
    case 0x43:
        pRecord->mUnknown60 = value;
        break;
    case 0x3a:
    case 0x44:
        pRecord->mUnknown68 = value;
        break;
    case 0x37:
    case 0x45:
        pRecord->mUnknown6C = value;
        break;
    case 0x2d:
        pRecord->mUnknownA4 = value;
        break;
    case 0x2e:
        pRecord->mUnknownA8 = value;
        break;
    case 0x2f:
        pRecord->mUnknownAC = value;
        break;
    case 0x30:
        pRecord->mUnknownB0 = value;
        break;
    case 0x31:
        pRecord->mUnknownB4 = value;
        break;
    case 0x32:
        pRecord->mUnknownB8 = value;
        break;
    }
}
