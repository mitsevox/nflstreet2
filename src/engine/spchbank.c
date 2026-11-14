/* Speech sample banks: the bank table, finding a bank or sub-bank by id, the recent-play
   history of each bank and its cycle bits. */

#include "engine/spchlib.h"

extern "C" {

char *fn_801B23A0(RowBank_801AFE90 *p)
{
    return (char *)p + ((p->mUnknown5 * ((p->mUnknown4 & 127) + 2) + 15) & ~3);
}

char *fn_801B23C4(RowBank_801AFE90 *p)
{
    char *result = fn_801B23A0(p);
    return result + (p->mUnknown4 & 127) * 4;
}

char *fn_801B23FC(RowBank_801AFE90 *p)
{
    int size = 0;
    char *result = fn_801B23C4(p);
    if (p->mUnknown4 & 128) {
        size = (p->mUnknown5 + 7) / 8 + 1;
    }
    return result + size;
}

void fn_801B2450(void)
{
    lbl_803EBB00 = 0;
    lbl_803EBB08 = 0;
    lbl_803EBB0C = 0;
    lbl_803EBB04 = 0;
}

void fn_801B2468(void)
{
    lbl_803EBB00 = 0;
    lbl_803EBB08 = 0;
    lbl_803EBB0C = 0;
    lbl_803EBB04 = 0;
}

int fn_801B2480(int count)
{
    return count * 8;
}

void fn_801B2488(int count, Slot_801B2450 *slots)
{
    lbl_803EBB08 = count;
    lbl_803EBB00 = slots;
    if (slots) {
        for (int i = 0; i < count; i++) {
            slots[i].mUnknown0 = 0;
            slots[i].mUnknown4 = 0;
        }
    }
}

int fn_801B2648(unsigned int id, int *out)
{
    int low = 0;
    int high = lbl_803EBB0C - 1;
    if (lbl_803EBB00 && lbl_803EBB0C) {
        while (low <= high) {
            int mid = (low + high) / 2;
            RowBank_801AFE90 *p = lbl_803EBB00[mid].mUnknown4;
            if (id == p->mUnknown0) {
                *out = lbl_803EBB00[mid].mUnknown0;
                return (short)mid;
            }
            if (id > p->mUnknown0) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}

int fn_801B26D8(unsigned int id, unsigned int key, int *out)
{
    int low = 0;
    int high = lbl_803EBB0C - 1;
    if (lbl_803EBB00 && lbl_803EBB0C) {
        while (low <= high) {
            int mid = (low + high) / 2;
            RowBank_801AFE90 *p = lbl_803EBB00[mid].mUnknown4;
            if (id == p->mUnknown0 && key == p->mUnknown2) {
                *out = lbl_803EBB00[mid].mUnknown0;
                return (short)mid;
            }
            if (id > p->mUnknown0 || (id == p->mUnknown0 && key > p->mUnknown2)) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}

int fn_801B2798(int i, unsigned int value)
{
    int result = 0;
    if (lbl_803EBB00 && i >= 0) {
        int limit = lbl_803EBB00[i].mUnknown4->mUnknownA;
        if (limit != 65535) {
            result = value < (unsigned int)limit;
        }
    }
    return result;
}

int fn_801B27E4(int id)
{
    for (int i = 0; i < lbl_803EBB0C; i++) {
        if (lbl_803EBB00[i].mUnknown0 == id) {
            return i;
        }
    }
    return -1;
}

void fn_801B2828(RowBank_801AFE90 *p, int value)
{
    if (p->mUnknown6) {
        unsigned char *history = (unsigned char *)fn_801B23FC(p);
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

int fn_801B2898(RowBank_801AFE90 *p, int value)
{
    int count = p->mUnknown6;
    int result = 0;
    if (count > 0) {
        unsigned char *history = (unsigned char *)fn_801B23FC(p);
        int index = *history++;
        for (int i = 0; i < count; i++) {
            if (--index < 0) {
                index = count - 1;
            }
            if (history[index] == value) {
                result = i + 1;
                break;
            }
        }
    }
    return result;
}

unsigned int fn_801B2918(unsigned int a, int b, int c)
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

void fn_801B2944(RowBank_801AFE90 *p)
{
    unsigned char *bits = (unsigned char *)fn_801B23C4(p);
    int count = bits[0];
    if (count > 0) {
        unsigned int time = (unsigned int)gGameNum % count;
        int size = p->mUnknown5;
        unsigned int start = fn_801B2918(time, size, count);
        int length = fn_801B2918(time + 1, size, count) - start;
        int index = start / 8 + 1;
        int bit = start & 7;
        for (int i = 0; i < length; i++) {
            bits[index] |= 1 << bit;
            if (bit == 7) {
                bit = 0;
                index++;
            } else {
                bit++;
            }
        }
    }
}

}
