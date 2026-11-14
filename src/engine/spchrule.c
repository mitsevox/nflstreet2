/* Speech sentence rules: offsets into the event and sentence records, which parameters a
   sentence uses, its rule settings and the per-sample parameter data. */

#include "engine/spchlib.h"

extern "C" {


Entry_801AF84C *fn_801B1CFC(Record_801AF75C *p, int i)
{
    // FAKEMATCH: the base-pointer local keeps the target's add order (base + 8 first)
    Entry_801AF84C *entries = p->mEntries;
    return entries + i;
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
    return (b & value) == a;
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

}
