#include <string.h>
#include "game/Record_80021154.h"
#include "game/fn_8022F478.h"

union Word_80020DC0 {
    int mUnknown0;
    Record_80021154 *mpRecord;
};

union Args_80020DC0 {
    Word_80020DC0 *mpWords[3];
    signed char mUnknown0[4];
};

extern "C" {
int fn_80186DF0(signed char *pIndices, int length);
int fn_80186A10(int index, char *pText);
int fn_8022F358(int index);

void fn_80020CF8(Word_80020DC0 *pRecords, Word_80020DC0 *pFlags, Word_80020DC0 *pIndices)
{
    char text[64];
    signed char indices[4];
    fn_80186DF0(indices, 4);
    signed char count = 0;
    signed char i;
    for (i = 0; i < 4; ++i) {
        pFlags[i].mUnknown0 = 0;
    }
    for (i = 0; i < 4; ++i) {
        if (indices[i] != -1) {
            fn_80186A10(indices[i], text);
            Record_80021154 *pRecord = pRecords[count].mpRecord;
            strncpy(pRecord->mUnknown8, text, pRecord->mUnknown4);
            pFlags[count].mUnknown0 = 1;
            pIndices[count].mUnknown0 = indices[i];
            ++count;
        }
    }
}

int fn_80020DC0(unsigned int id, Args_80020DC0 *pArgs)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
    {
        Word_80020DC0 *pRecords = pArgs->mpWords[0];
        Word_80020DC0 *pFlags = pArgs->mpWords[1];
        Word_80020DC0 *pIndices = pArgs->mpWords[2];
        int recordsOffset = pRecords[0].mUnknown0 + 1;
        int flagsOffset = pFlags[0].mUnknown0 + 1;
        int indicesOffset = pIndices[0].mUnknown0 + 1;
        fn_80020CF8(pRecords + recordsOffset, pFlags + flagsOffset, pIndices + indicesOffset);
        break;
    }
    case 0x80000003:
        fn_8022F478(fn_8022F358(pArgs->mUnknown0[3]));
        break;
    default:
        return 0;
    }
    return 1;
}
}
