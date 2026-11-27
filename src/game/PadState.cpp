/* Pad state: during a game the pad handler passes every controller input
   here, and the latest value of each button or stick input is kept in a
   per-slot record that gameplay reads back when it builds a player's
   controls. */

#include "game/PadInput.h"

/* One slot's record of the pad state table (the array described as
   Pool_800B8544 in cu_8008E978.cpp). */
struct PadState_t {
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

/* The record array and its count. */
struct PadStateTable_t {
    PadState_t *mpRecords;
    unsigned char mCount;
};

extern PadStateTable_t lbl_803EC930;

extern "C" void PadStateSetValue(unsigned int index, unsigned int id, float value)
{
    if (index >= lbl_803EC930.mCount) return;
    PadState_t *pRecord = &lbl_803EC930.mpRecords[index];
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
        pRecord->mUnknown30 = PadInputAxisToFixed(value);
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

/* Four controller configurations of 68 mask words each (two header words, 36 button masks,
   then the single-bit masks 1 << 0 .. 1 << 29), and six small values that go with each. The
   assignment code (Assign.cpp) gives a player's entry one configuration and its values through
   the two pointer tables below. */
static unsigned int _PadState_Config0[68] = {
    0x100, 0xFFFFFFFF, 0x800, 0x400000, 0x1000, 0x2000, 0x800000, 0x1000000,
    0x400, 0x200000, 0x800, 0x100000, 0x400, 0x800200, 0x200, 0x40000,
    0x40000, 0x2000800, 0xFFFFFFFF, 0x800, 0x100, 0x200, 0x400, 0x80000,
    0x100000, 0x200000, 0x2000, 0x1000000, 0x200, 0x200000, 0x800, 0x1000,
    0x800000, 0x200, 0x100, 0x200, 0x800000, 0x800000, 0x1, 0x2,
    0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200,
    0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000,
    0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 0x1000000, 0x2000000,
    0x4000000, 0x8000000, 0x10000000, 0x20000000,
};

static unsigned int _PadState_Config1[68] = {
    0x100, 0xFFFFFFFF, 0x800, 0x400000, 0x1000, 0x2000, 0x800000, 0x1000000,
    0x400, 0x200000, 0x800, 0x100000, 0x400, 0x800200, 0x200, 0x800,
    0x800, 0x20000800, 0xFFFFFFFF, 0xFFFFFFFF, 0x100, 0x200, 0x400, 0x80000,
    0x100000, 0x200000, 0x2000, 0x1000000, 0x800, 0x200000, 0x200, 0x1000,
    0x800000, 0x400, 0x100, 0x200, 0x800000, 0x800000, 0x1, 0x2,
    0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200,
    0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000,
    0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 0x1000000, 0x2000000,
    0x4000000, 0x8000000, 0x10000000, 0x20000000,
};

static unsigned int _PadState_Config2[68] = {
    0x100, 0xFFFFFFFF, 0x800, 0x400000, 0x1000, 0x2000, 0x800000, 0x1000000,
    0x400, 0x200000, 0x800, 0x100000, 0x400, 0x800200, 0x200, 0x800,
    0x800, 0x20000800, 0xFFFFFFFF, 0xFFFFFFFF, 0x100, 0x200, 0x400, 0x80000,
    0x100000, 0x200000, 0x2000, 0x1000000, 0x800, 0x200000, 0x200, 0x1000,
    0x800000, 0x400, 0x100, 0x200, 0x800000, 0x800000, 0x1, 0x2,
    0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200,
    0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000,
    0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 0x1000000, 0x2000000,
    0x4000000, 0x8000000, 0x10000000, 0x20000000,
};

static unsigned int _PadState_Config3[68] = {
    0x100, 0xFFFFFFFF, 0x800, 0x400000, 0x1000, 0x2000, 0x800000, 0x1000000,
    0x400, 0x200000, 0x800, 0x100000, 0x200, 0x800200, 0x200, 0x800,
    0x800, 0x20000800, 0xFFFFFFFF, 0xFFFFFFFF, 0x100, 0x200, 0x400, 0x80000,
    0x100000, 0x200000, 0x2000, 0x1000000, 0x800, 0x200000, 0x200, 0x1000,
    0x800000, 0x400, 0x100, 0x200, 0x800000, 0x800000, 0x1, 0x2,
    0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200,
    0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000,
    0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 0x1000000, 0x2000000,
    0x4000000, 0x8000000, 0x10000000, 0x20000000,
};

static int _PadState_Params0[6] = { 5, 9, 8, 6, 7, 7 };
static int _PadState_Params1[6] = { 5, 9, 8, 6, 5, 7 };
static int _PadState_Params2[6] = { 5, 9, 8, 6, 7, 7 };
static int _PadState_Params3[6] = { 6, 9, 8, 6, 5, 7 };

unsigned int *gPadStateConfigs[4] = {
    _PadState_Config0, _PadState_Config1, _PadState_Config2, _PadState_Config3,
};

int *gPadStateConfigParams[4] = {
    _PadState_Params0, _PadState_Params1, _PadState_Params2, _PadState_Params3,
};
