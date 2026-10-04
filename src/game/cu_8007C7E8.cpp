#include "game/Object_8007A334.h"

/* Values copied out of one fetched row by fn_8007C84C. */
struct Record_8007C84C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
    short mUnknown36;
    short mUnknown38;
    short mUnknown40;
    short mUnknown42;
    short mUnknown44;
    short mUnknown46;
    short mUnknown48;
    short mUnknown50;
    short mUnknown52;
    short mUnknown54;
    short mUnknown56;
    short mUnknown58;
    short mUnknown60;
    short mUnknown62;
    short mUnknown64;
    short mUnknown66;
    short mUnknown68;
    short mUnknown70;
    short mUnknown72;
    short mUnknown74;
    int mUnknown76;
    unsigned char mUnknown80;
};

static int sColumnTags[31] = {
    0x44494247, 0x50544247, 0x52494247, 0x52444247, 0x4C564247, 0x4C504247,
    0x54504247, 0x4E444247, 0x31304D47, 0x31324D47, 0x33304D47, 0x34304D47,
    0x35304D47, 0x36304D47, 0x37304D47, 0x38304D47, 0x39304D47, 0x30314D47,
    0x31314D47, 0x32324D47, 0x33314D47, 0x34314D47, 0x35314D47, 0x36314D47,
    0x37314D47, 0x38314D47, 0x39314D47, 0x30324D47, 0x52474247, 0x4E504247,
    0x504F4247
};

extern "C" {

int fn_8007C7E8(Object_8007A334 *pCursor, int key, int *pResult)
{
    ColumnValue_802D6424 list[2];

    list[0].Set(0x4B524247, 0x44494247);
    list[0].mValue = key;
    list[1].Set(-1, -1);
    list[1].mValue = 0;
    return fn_8007A690(pCursor, list, 0, pResult);
}

void fn_8007C84C(Object_8007A334 *pCursor, Record_8007C84C *pOut)
{
    ColumnValue_802D6424 list[32];
    int i;

    for (i = 0; i < 31; i++) {
        list[i].Set(0x4B524247, sColumnTags[i]);
        list[i].mValue = 0;
    }
    list[31].Set(-1, -1);
    list[31].mValue = 0;
    pCursor->Read(list);

    pOut->mUnknown0 = list[0].mValue;
    pOut->mUnknown4 = list[30].mValue;
    pOut->mUnknown8 = list[1].mValue;
    pOut->mUnknown12 = list[2].mValue;
    pOut->mUnknown20 = list[4].mValue;
    pOut->mUnknown16 = list[3].mValue;
    pOut->mUnknown24 = list[5].mValue;
    pOut->mUnknown28 = list[6].mValue;
    pOut->mUnknown32 = list[7].mValue;
    pOut->mUnknown36 = list[8].mValue;
    pOut->mUnknown38 = list[9].mValue;
    pOut->mUnknown40 = list[10].mValue;
    pOut->mUnknown42 = list[11].mValue;
    pOut->mUnknown44 = list[12].mValue;
    pOut->mUnknown46 = list[13].mValue;
    pOut->mUnknown48 = list[14].mValue;
    pOut->mUnknown50 = list[15].mValue;
    pOut->mUnknown52 = list[16].mValue;
    pOut->mUnknown54 = list[17].mValue;
    pOut->mUnknown56 = list[18].mValue;
    pOut->mUnknown58 = list[19].mValue;
    pOut->mUnknown60 = list[20].mValue;
    pOut->mUnknown62 = list[21].mValue;
    pOut->mUnknown64 = list[22].mValue;
    pOut->mUnknown66 = list[23].mValue;
    pOut->mUnknown68 = list[24].mValue;
    pOut->mUnknown70 = list[25].mValue;
    pOut->mUnknown72 = list[26].mValue;
    pOut->mUnknown74 = list[27].mValue;
    pOut->mUnknown76 = list[28].mValue;
    pOut->mUnknown80 = list[29].mValue;
}
}
