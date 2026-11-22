/* Registers sample banks, downloads their samples to ARAM and dispatches patch user data. */

#include "engine/sndbank.h"

extern "C" {

typedef struct SndBankUserDataMessage_t {
    int mEvent;
    unsigned char *mPayload;
    unsigned int mPayloadSize;
    // FAKEMATCH: two unwritten words that give the target's 0x48-byte frame; whether the callbacks read them is not established
    int unk_0xC[2];
} SndBankUserDataMessage_t;

/* Dispatch a message for each user-data payload in the parsed patch. */
void SNDBANKI_userdatacallback(SNDIPATCHHEADER *patch, int event)
{
    SndBankUserDataMessage_t message;
    int i;

    while (patch->mUserDataCount > 0) {
        patch->mUserDataCount--;
        message.mEvent = event;
        message.mPayload = patch->mUserDataPayloads[patch->mUserDataCount];
        message.mPayloadSize = patch->mUserDataSizes[patch->mUserDataCount];
        for (i = 0; i < lbl_803A6C24.mBankUserDataCallbackCount; i++) {
            lbl_803A6C24.mBankUserDataCallbacks[i](&message);
        }
    }
}

/* Register the bank, copy its samples to ARAM and resolve its patches. */
int SNDbankadd(int *handle, BankVer_t *bank)
{
    lbl_803A6C24.m1C0 = SNDbankremove;
    int index = SNDBANKI_alloc();
    *handle = index;
    SndBankSlot_t &slot = lbl_803A6C24.m1D0[index];
    slot.m0 = bank;
    slot.m8 = 1;
    slot.m4 = 0;

    if (bank->mC != 0) {
        slot.m4 = (int)SNDPLATFORM_memalloc(512, bank->mC + 48);
        if (slot.m4 == 0) {
            slot.m0 = 0;
            slot.m8 = 0;
            return -6;
        }

        for (int offset = 0; offset < bank->mC; offset += 4096) {
            int size = bank->mC - offset;
            if (size > 4096) {
                size = 4096;
            }
            int key = SNDPLATFORM_download(512, (unsigned int)((char *)bank + bank->m8 + bank->m10 + offset),
                                           slot.m4 + offset, size);
            while (SNDPLATFORM_downloadcomplete(key) == 0) {
            }
        }
        int count = 0;
        for (int patch = 0; patch < bank->m6; patch++) {
            int offset = bank->m14[patch];
            if (offset != 0) {
                SNDBANKI_asyncresolvepatch(512, (char *)&bank->m14[patch] + offset, slot.m4, &count);
            }
        }
    }
    slot.m8 = 0;
    return bank->mC != 0 || bank->m10 != 0 ? 7 : 8;
}

}
