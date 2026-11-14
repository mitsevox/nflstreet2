/* Speech rules and sample banks (neutral file name): sentence rule settings, then loading and
   finding the banks that hold the recorded samples. */

#include "engine/spchlib.h"

extern "C" {

Entry_801AF84C *fn_801B1CFC(Record_801AF75C *p, int i)
{
    return p->mEntries + i;
}

int fn_801B1D0C(unsigned char *p)
{
    return p[2] >> 2;
}

int fn_801B1D18(Item_801AE3F4 *p)
{
    return p->mUnknown7;
}

char *fn_801B1D20(char *p, unsigned char *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801B1D30(char *p, unsigned short *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801B1D44(Item_801AE3F4 *p)
{
    return (char *)p + (((p->mUnknown6 * 2 + 3) & ~3) + 12);
}

char *fn_801B1D60(Item_801AE3F4 *p)
{
    char *result = fn_801B1D44(p);
    return result + ((fn_801B1D18(p) * 3 + 3) & ~3);
}

int fn_801B1DAC(unsigned char *p, int value)
{
    int result = 0;
    int count = fn_801B1D0C(p);
    for (int i = 0; i < count; i++) {
        Record_801AF75C *record = (Record_801AF75C *)fn_801B1D20((char *)p, p + 8, i);
        if (record->mUnknown2 == value) {
            result = 1;
            break;
        }
        int n = record->mUnknown4;
        for (int j = 0; j < n; j++) {
            if (fn_801B1CFC(record, j)->mUnknown4 == value) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

unsigned char *fn_801B2190(Item_801AE3F4 *item, int index, unsigned int *a, unsigned int *b)
{
    *a = 0;
    *b = 0;
    int size = (fn_801B1D18(item) + 7) / 8;
    int offset = size * item->mUnknown6;
    unsigned char *p = (unsigned char *)fn_801B1D60(item) + index * size;
    unsigned char *q = p + offset;
    if (size <= 4) {
        for (int i = 0; i < size; i++) {
            *a += p[i] << ((3 - i) * 8);
            *b += q[i] << ((3 - i) * 8);
        }
    }
    return p;
}

int fn_801B2250(Item_801AE3F4 *item, int index, unsigned int value, unsigned int excluded)
{
    unsigned int a, b;
    fn_801B2190(item, index, &a, &b);
    b &= ~excluded;
    a &= b;
    value &= b;
    return value == a;
}

char *fn_801B22B0(RowBank_801AFE90 *p, int i)
{
    char *result = 0;
    if (i < p->mUnknown5) {
        result = (char *)p->mRows + i * ((p->mUnknown4 & 127) + 2) + 2;
    }
    return result;
}

int fn_801B22E0(RowBank_801AFE90 *p, int i, int *a, int *b)
{
    int result = 0;
    int count = p->mUnknown5;
    if (i < count) {
        int stride = (p->mUnknown4 & 127) + 2;
        unsigned char *record = p->mRows + i * stride;
        int scale = (p->mUnknown7 + 1) << 8;
        int start = ((record[0] << 8) + record[1]) * scale;
        unsigned char *next = record + stride;
        int end;
        if (i + 1 >= count) end = p->mUnknown8;
        else end = (next[0] << 8) + next[1];
        *a = start;
        *b = end * scale - start;
        result = 1;
    }
    return result;
}

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
    if (a > (unsigned int)remainder) {
        return quotient * a + remainder;
    }
    return quotient * a + a;
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
