/* Speech sample banks: the bank table, finding a bank or sub-bank by id, the recent-play
   history of each bank and its cycle bits. */

#include "engine/spchlib.h"

extern "C" {

char *BANKHDR_GetValidParmMask(VoxBankHdr_t *p)
{
    return (char *)p + ((p->mUnknown5 * ((p->mUnknown4 & 127) + 2) + 15) & ~3);
}

char *BANKHDR_GetCycleBitsAddr(VoxBankHdr_t *p)
{
    char *result = BANKHDR_GetValidParmMask(p);
    return result + (p->mUnknown4 & 127) * 4;
}

char *BANKHDR_GetSampleRepeatAddr(VoxBankHdr_t *p)
{
    int size = 0;
    char *result = BANKHDR_GetCycleBitsAddr(p);
    if (p->mUnknown4 & 128) {
        size = (p->mUnknown5 + 7) / 8 + 1;
    }
    return result + size;
}

void iSPCH_InitBanks(void)
{
    gVoxBanks = 0;
    gNumBanks = 0;
    gBankCount = 0;
    gUniqueBankHandle = 0;
}

void iSPCH_DisposeBanks(void)
{
    gVoxBanks = 0;
    gNumBanks = 0;
    gBankCount = 0;
    gUniqueBankHandle = 0;
}

int SPCH_GetBankPtrMemSize(int count)
{
    return count * 8;
}

void SPCH_InitBankMem(int count, VoxBankSlot_t *slots)
{
    gNumBanks = count;
    gVoxBanks = slots;
    if (slots) {
        for (int i = 0; i < count; i++) {
            slots[i].mUnknown0 = 0;
            slots[i].mUnknown4 = 0;
        }
    }
}

int iSPCH_FindInsertPosition(VoxBankHdr_t *bank)
{
    int low = 0;
    int high = gBankCount - 1;
    if (gBankCount == 0) {
        return 0;
    }
    while (low <= high) {
        int mid = (low + high) / 2;
        if (bank->mUnknown0 == gVoxBanks[mid].mUnknown4->mUnknown0 && bank->mUnknown2 == gVoxBanks[mid].mUnknown4->mUnknown2) {
            // FAKEMATCH: goto past the loop; with return -1 here the slot-0 test does not reuse the hoisted id
            goto fail;
        }
        if (mid == 0) {
            if ((bank->mUnknown0 == gVoxBanks[0].mUnknown4->mUnknown0 && bank->mUnknown2 < gVoxBanks[0].mUnknown4->mUnknown2) || bank->mUnknown0 < gVoxBanks[0].mUnknown4->mUnknown0) {
                return (short)mid;
            }
        }
        if ((bank->mUnknown0 == gVoxBanks[mid].mUnknown4->mUnknown0 && bank->mUnknown2 < gVoxBanks[mid].mUnknown4->mUnknown2) || bank->mUnknown0 < gVoxBanks[mid].mUnknown4->mUnknown0) {
            if ((bank->mUnknown0 == gVoxBanks[mid - 1].mUnknown4->mUnknown0 && bank->mUnknown2 > gVoxBanks[mid - 1].mUnknown4->mUnknown2) || bank->mUnknown0 > gVoxBanks[mid - 1].mUnknown4->mUnknown0) {
                return (short)mid;
            }
        }
        if (bank->mUnknown0 > gVoxBanks[mid].mUnknown4->mUnknown0 || (bank->mUnknown0 == gVoxBanks[mid].mUnknown4->mUnknown0 && bank->mUnknown2 > gVoxBanks[mid].mUnknown4->mUnknown2)) {
            low = mid + 1;
            if (gVoxBanks[low].mUnknown4 == 0) {
                return (short)low;
            }
        } else {
            high = mid - 1;
        }
    }
fail:
    return -1;
}

int iSPCH_FindBank(unsigned int id, int *out)
{
    int low = 0;
    int high = gBankCount - 1;
    if (gVoxBanks && gBankCount) {
        while (low <= high) {
            int mid = (low + high) / 2;
            VoxBankHdr_t *p = gVoxBanks[mid].mUnknown4;
            if (id == p->mUnknown0) {
                *out = gVoxBanks[mid].mUnknown0;
                return (short)mid;
            }
            if (id > p->mUnknown0) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}

int iSPCH_FindSubBank(unsigned int id, unsigned int key, int *out)
{
    int low = 0;
    int high = gBankCount - 1;
    if (gVoxBanks && gBankCount) {
        while (low <= high) {
            int mid = (low + high) / 2;
            if (id == gVoxBanks[mid].mUnknown4->mUnknown0 && key == gVoxBanks[mid].mUnknown4->mUnknown2) {
                *out = gVoxBanks[mid].mUnknown0;
                return (short)mid;
            }
            if (id > gVoxBanks[mid].mUnknown4->mUnknown0 || (id == gVoxBanks[mid].mUnknown4->mUnknown0 && key > gVoxBanks[mid].mUnknown4->mUnknown2)) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}

int iSPCH_TestSubBankBounds(int i, unsigned int value)
{
    int result = 0;
    if (gVoxBanks && i >= 0) {
        int limit = gVoxBanks[i].mUnknown4->mUnknownA;
        if (limit != 65535) {
            result = value < (unsigned int)limit;
        }
    }
    return result;
}

int iSPCH_FindBankIndexFromHandle(int id)
{
    for (int i = 0; i < gBankCount; i++) {
        if (gVoxBanks[i].mUnknown0 == id) {
            return i;
        }
    }
    return -1;
}

void iSPCHBank_AddToQueue(VoxBankHdr_t *p, int value)
{
    if (p->mUnknown6) {
        unsigned char *history = (unsigned char *)BANKHDR_GetSampleRepeatAddr(p);
        unsigned char index = history[0];
        if (index < p->mUnknown6) {
            history[index + 1] = value;
        }
        index++;
        if (index >= p->mUnknown6) {
            index = 0;
        }
        history[0] = index;
    }
}

int iSPCHBank_GetSampleTimeInQueue(VoxBankHdr_t *p, int value)
{
    int count = p->mUnknown6;
    int result = 0;
    if (count > 0) {
        unsigned char *history = (unsigned char *)BANKHDR_GetSampleRepeatAddr(p);
        int index = *history++;
        for (int i = 0; i < count; i++) {
            if (--index < 0) {
                index = count - 1;
            }
            if (history[index] == value) {
                result = i + 1;
                // FAKEMATCH: goto past the loop; with break the loop keeps its jump-to-test form
                goto done;
            }
        }
    }
done:
    return result;
}

unsigned int iSPCH_GetStartSample(unsigned int a, int b, int c)
{
    int quotient = b / c;
    int remainder = b % c;
    unsigned int result;
    if (a > (unsigned int)remainder) {
        result = quotient * a + remainder;
    } else {
        result = quotient * a + a;
    }
    return result;
}

void iSPCH_SetCycleBits(VoxBankHdr_t *p)
{
    unsigned char *bits = (unsigned char *)BANKHDR_GetCycleBitsAddr(p);
    int count = bits[0];
    if (count > 0) {
        unsigned int time = (unsigned int)gGameNum % count;
        int size = p->mUnknown5;
        unsigned int start = iSPCH_GetStartSample(time, size, count);
        int length = iSPCH_GetStartSample(time + 1, size, count) - start;
        int index = start / 8 + 1;
        int bit = start & 7;
        for (int i = 0; i < length; i++) {
            bits[index] |= 1 << bit;
            if (++bit == 8) {
                bit = 0;
                index++;
            }
        }
    }
}

int SPCH_AddBank(VoxBankHdr_t *bank)
{
    int handle = -1;
    if (gVoxBanks) {
        int pos = iSPCH_FindInsertPosition(bank);
        if (pos < gNumBanks && pos >= 0) {
            if (bank->mUnknown4 & 128) {
                iSPCH_SetCycleBits(bank);
            }
            for (int i = gBankCount; i > pos; i--) {
                gVoxBanks[i] = gVoxBanks[i - 1];
            }
            handle = gUniqueBankHandle;
            gVoxBanks[pos].mUnknown4 = bank;
            gVoxBanks[pos].mUnknown0 = handle;
            gUniqueBankHandle++;
            gBankCount++;
        }
    }
    return handle;
}

}
