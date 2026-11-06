/* Profile list: fills the front end's list with the saved player profiles, most
   recently used first, and makes the chosen profile current. */

#include <string.h>
#include "game/TextRecord.h"
#include "game/fn_8022F478.h"

union ProfileListWord_t {
    int mUnknown0;
    TextRecord_t *mpRecord;
};

union ProfileListArgs_t {
    ProfileListWord_t *mpWords[3];
    signed char mUnknown0[4];
};

extern "C" {
int fn_80186DF0(signed char *pIndices, int length);
int fn_80186A10(int index, char *pText);
int fn_8022F358(int index);

void MsgProfileListFill(ProfileListWord_t *pRecords, ProfileListWord_t *pFlags, ProfileListWord_t *pIndices)
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
            TextRecord_t *pRecord = pRecords[count].mpRecord;
            strncpy(pRecord->mUnknown8, text, pRecord->mUnknown4);
            pFlags[count].mUnknown0 = 1;
            pIndices[count].mUnknown0 = indices[i];
            ++count;
        }
    }
}

int MsgProfileListHandleMessage(unsigned int id, ProfileListArgs_t *pArgs)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
    {
        ProfileListWord_t *pRecords = pArgs->mpWords[0];
        ProfileListWord_t *pFlags = pArgs->mpWords[1];
        ProfileListWord_t *pIndices = pArgs->mpWords[2];
        int recordsOffset = pRecords[0].mUnknown0 + 1;
        int flagsOffset = pFlags[0].mUnknown0 + 1;
        int indicesOffset = pIndices[0].mUnknown0 + 1;
        MsgProfileListFill(pRecords + recordsOffset, pFlags + flagsOffset, pIndices + indicesOffset);
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
