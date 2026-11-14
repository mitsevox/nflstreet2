/* Speech library event database resolution (spchrslv.c): registers loaded event databases in the
   eight-slot table, binds their Csis parameters and resets their global match parameters. */

#include "engine/spchlib.h"

extern "C" {

unsigned char *iSPCH_GetGlobalMatchParmAddr(Bank_801AE444 *bank)
{
    return (unsigned char *)bank + (((bank->mUnknown10 + bank->mUnknown10 + 3) & ~3) + 24);
}

void SPCH_ClearMatchParmSettings(int key)
{
    int i;
    int j;
    unsigned char *bytes;

    for (i = 0; i < 8; i++) {
        if (gEventDats[i].mBank != 0 && gEventDats[i].mValue == key) {
            bytes = iSPCH_GetGlobalMatchParmAddr(gEventDats[i].mBank);
            for (j = 0; j < gEventDats[i].mBank->mUnknown12[0]; j++)
                bytes[j] = 0xFF;
        }
    }
}
}

int iSPCH_BindData(char *data, unsigned int key)
{
    Object_80266AF8 *p = (Object_80266AF8 *)data;
    int a;
    int b;
    int result = 0;
    int i;

    if ((p->mUnknown0 & 0xFFFF0000) == 0x03100000) {
        fn_801AFABC(p, &a, &b);
        for (i = 0; i < 8; i++) {
            Bank_801AE444 *bank = gEventDats[i].mBank;
            // FAKEMATCH: goto to the shared return instead of return result, so the found case branches to the final mr r3,r29 as in the target
            if (bank != 0 && bank->mUnknown9 == b && bank->mUnknown8 == a)
                goto done;
        }
        for (i = 0; i < 8; i++) {
            if (gEventDats[i].mBank == 0) {
                gEventDats[i].mBank = (Bank_801AE444 *)data;
                result = 1;
                gEventDats[i].mValue = key;
                break;
            }
        }
        SPCH_ClearMatchParmSettings(key);
    }
done:
    return result;
}

extern "C" {

int SPCH_AddEventDB(char *data, unsigned int key)
{
    int result = 0;

    if (key <= 7) {
        result = iSPCH_BindData(data, key);
        iSPCH_InitCsis((Bank_801AE444 *)data);
    }
    return result;
}
}
