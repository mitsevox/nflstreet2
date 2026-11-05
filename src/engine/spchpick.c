/* Speech picking (spchpick.c): chooses which sentence and which recorded samples to play for an
   event, by its parameters, weights and what was played recently. */

#include "engine/spchlib.h"

extern "C" {

char *fn_801AF75C(RowBank_801AFE90 *p)
{
    return (char *)p + ((p->mUnknown5 * ((p->mUnknown4 & 127) + 2) + 15) & ~3);
}

char *fn_801AF780(RowBank_801AFE90 *p)
{
    char *result = fn_801AF75C(p);
    return result + (p->mUnknown4 & 127) * 4;
}

char *fn_801AF7B8(RowBank_801AFE90 *p)
{
    int size = 0;
    char *result = fn_801AF780(p);
    if (p->mUnknown4 & 128) {
        size = (p->mUnknown5 + 7) / 8 + 1;
    }
    return result + size;
}

char *fn_801AF80C(RowBank_801AFE90 *p)
{
    char *result = fn_801AF7B8(p);
    int size = p->mUnknown6;
    if (size) {
        result += size + 1;
    }
    return result;
}

Entry_801AF84C *fn_801AF84C(Record_801AF75C *p, int i)
{
    return p->mEntries + i;
}

int fn_801AF85C(unsigned char *p)
{
    return p[2] >> 2;
}

int fn_801AF868(unsigned char *p)
{
    return p[2] & 3;
}

char *fn_801AF874(unsigned char *p)
{
    return (char *)p + (((fn_801AF85C(p) + 3) & ~3) + 8);
}

char *fn_801AF8B0(unsigned char *p)
{
    int size = p[4] * 4;
    return fn_801AF874(p) + size;
}

int fn_801AF8E4(Item_801AE3F4 *p)
{
    return p->mUnknown7;
}

int fn_801AF8EC(Item_801AE3F4 *p)
{
    return p->mUnknown8 & 15;
}

int fn_801AF8F8(Item_801AE3F4 *p)
{
    return p->mUnknown8 >> 4;
}

int fn_801AF904(Item_801AE3F4 *p)
{
    return p->mUnknownA & 1;
}

int fn_801AF910(Item_801AE3F4 *p)
{
    return (p->mUnknownA >> 3) & 1;
}

int fn_801AF91C(Item_801AE3F4 *p)
{
    return (p->mUnknownA >> 5) & 1;
}

char *fn_801AF928(char *p, unsigned char *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801AF938(char *p, unsigned short *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801AF94C(Item_801AE3F4 *p)
{
    return (char *)p + (((p->mUnknown6 * 2 + 3) & ~3) + 12);
}

char *fn_801AF968(Item_801AE3F4 *p)
{
    char *result = fn_801AF94C(p);
    return result + ((fn_801AF8E4(p) * 3 + 3) & ~3);
}

char *fn_801AF9B4(Item_801AE3F4 *p)
{
    char *result = fn_801AF968(p);
    return result + ((((fn_801AF8E4(p) + 7) / 8) * p->mUnknown6 * 2 + 3) & ~3);
}

int fn_801AFA14(Item_801AE3F4 *p, int i)
{
    char *result = fn_801AF9B4(p);
    result += (fn_801AF8F8(p) * 3 + 3) & ~3;
    return ((unsigned short *)(result + 4))[i];
}

int fn_801AFA70(Item_801AE3F4 *p)
{
    char *result = fn_801AF9B4(p);
    return *(int *)(result + ((fn_801AF8F8(p) * 3 + 3) & ~3));
}

void fn_801AFABC(Object_80266AF8 *p, int *a, int *b)
{
    *a = p->mUnknown8;
    *b = p->mUnknown9;
}

void fn_801AFAD0(unsigned char *p, Record_801AF75C *record, unsigned char *values)
{
    int *words = (int *)fn_801AF8B0(p);
    int count = record->mUnknown4;
    for (int i = 0; i < count; i++) {
        if (fn_801AF84C(record, i)->mUnknown4 == 254) {
            int flags = fn_801AF84C(record, i)->mUnknown6;
            if (flags & 128) {
                words[flags & 127] |= 1 << values[i];
            }
        }
    }
}

int fn_801AFB70(Record_801AF75C *record)
{
    int found = 0;
    int count = record->mUnknown4;
    for (int i = 0; i < count; i++) {
        if (fn_801AF84C(record, i)->mUnknown4 == 254) {
            found = 1;
            break;
        }
    }
    return found;
}

int fn_801AFBD8(unsigned char *p, Record_801AF75C *record, EventWord_801AFBD8 *event, unsigned char *values)
{
    int count = record->mUnknown4;
    int result = 1;
    for (int i = 0; i < count; i++) {
        int value = values[i];
        result = 0;
        if ((unsigned int)value > 31) break;
        unsigned int mask = 1U << value;
        int id = fn_801AF84C(record, i)->mUnknown4;
        if (fn_801AF84C(record, i)->mUnknown0 & mask) {
            if (id == 0 || id == 254) {
                result = 1;
            } else if (id == 255) {
                int flags = fn_801AF84C(record, i)->mUnknown6;
                if (flags & 128) {
                    int *words = (int *)fn_801AF8B0(p);
                    if (words[flags & 127] & mask) result = 1;
                } else {
                    Key_801AE658 key = event[0].mKey;
                    char *text;
                    if (fn_801AE7B4(&key, &text) && (unsigned char)text[flags] == value) result = 1;
                }
            } else {
                if (event[id].mWord & mask) result = 1;
            }
        }
        if (!result) break;
    }
    return result;
}

int fn_801AFD04(Key_801AE658 *key, EventWord_801AFBD8 *event, Result_801AFD04 *out)
{
    int mode = key->mUnknown3;
    int index = key->mUnknown2;
    int id = key->mId;
    int value = -1;
    out->mUnknown4 = -1;
    out->mUnknown6 = -1;
    out->mUnknown0 = -1;
    switch (mode) {
    case 0:
        out->mUnknown4 = fn_801B2648(id, &value);
        out->mUnknown0 = (short)value;
        break;
    case 1:
        out->mUnknown4 = fn_801B26D8(id, event[index].mHalfwords[1], &value);
        out->mUnknown0 = value;
        break;
    case 2:
        {
            int slot = fn_801B2648(id, &value);
            if (fn_801B2798(slot, event[index].mWord)) out->mUnknown6 = event[index].mHalfwords[1];
            else value = -1;
            out->mUnknown4 = slot;
            out->mUnknown0 = value;
        }
        break;
    }
    return out->mUnknown0 >= 0;
}

void fn_801AFDFC(RowBank_801AFE90 *p, int i)
{
    int index = i / 8 + 1;
    unsigned char mask = ~(1 << (i % 8));
    unsigned char *bits = (unsigned char *)fn_801AF780(p);
    bits[index] &= mask;
}

int fn_801AFE58(unsigned char *bits, int i)
{
    unsigned char mask = 1 << (i % 8);
    return bits[i / 8] & mask;
}

int fn_801AFE90(Result_801AFD04 *result, RowBank_801AFE90 *p, int i)
{
    int index = result->mUnknown6;
    int found = 0;
    if (p->mUnknownA > index) {
        i += p->mUnknown5 * index;
        found = fn_801AFE58((unsigned char *)fn_801AF80C(p), i);
    }
    return found;
}

int fn_801AFEE8(Result_801AFD04 *result, RowBank_801AFE90 *p, int i)
{
    int found = 1;
    if (i > p->mUnknown5) {
        found = 0;
    } else {
        if (result->mUnknown6 != -1) {
            found = fn_801AFE90(result, p, i);
        }
        if (found && (p->mUnknown4 & 128)) {
            found = fn_801AFE58((unsigned char *)fn_801AF780(p) + 1, i);
        }
    }
    return found;
}

int fn_801AFF74(Buffer_801AFF74 *p, int value)
{
    int result = 0;
    if (p->mCount < 200) {
        result = 1;
        p->mValues[p->mCount] = value;
        p->mCount++;
    }
    return result;
}

int fn_801AFFA4(Record_801AF75C *a, RowBank_801AFE90 *b, int *values)
{
    int *words = (int *)fn_801AF75C(b);
    int count = b->mUnknown4 & 127;
    int result = 1;
    for (int i = 0; i < count; i++) {
        int id = fn_801AF84C(a, i)->mUnknown4;
        if (id != 0 && id != 255 && id != 254) {
            if (!(words[i] & values[id])) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

int fn_801B01E8(int value)
{
    int result = 0;
    if (lbl_803ECEA4) {
        result = value * 100 / lbl_803ECEA4;
    }
    return result;
}

int fn_801B0208(unsigned char *p, Work_801B10AC *work)
{
    int total = 0;
    int count = fn_801AF85C(p);
    for (int i = 0; i < count; i++) {
        int index = work->mEntries[i].mUnknown4;
        RowBank_801AFE90 *record = lbl_803EBB00[index].mUnknown4;
        int a, b;
        if (fn_801B22E0(record, work->mValues[work->mEntries[i].mUnknownA], &a, &b)) {
            total += b;
        }
    }
    return fn_801B01E8(total);
}

int fn_801B029C(unsigned int value)
{
    return (value & 31) * lbl_802F475C[(value >> 5) & 7];
}

int fn_801B02B8(unsigned char *p)
{
    return fn_801B029C(*p);
}

int fn_801B040C(Item_801AE3F4 *p, int channel)
{
    int result = 1;
    if (p->mId == lbl_8037E234[channel].mKey.mId) {
        int limit = fn_801AF8EC(p);
        if (limit > 0) result = lbl_8037E234[channel].mUnknown4 < limit;
    }
    return result;
}

int fn_801B0474(unsigned char *p, int mode)
{
    int result = 0;
    int value = fn_801AF868(p);
    if ((value == 1 && mode == 2) || (value == 2 && mode != 2) || value == 0) {
        result = 1;
    }
    return result;
}

void fn_801B04D4(unsigned char *p)
{
    int *words = (int *)fn_801AF8B0(p);
    for (int i = 0; i < p[3]; i++) {
        words[i] = 0;
    }
}

int fn_801B052C(unsigned char *p, Record_801AF75C *record)
{
    int count = record->mUnknown4;
    int result = 1;
    for (int i = 0; i < count; i++) {
        if (fn_801AF84C(record, i)->mUnknown4 == 255) {
            int flags = fn_801AF84C(record, i)->mUnknown6;
            if (flags != 255 && (flags & 128)) {
                flags &= 127;
                int *words = (int *)fn_801AF8B0(p);
                if (words && !words[flags]) {
                    result = 0;
                    break;
                }
            }
        }
    }
    return result;
}

void fn_801B08DC(unsigned char *p, Work_801B10AC *work)
{
    int count = fn_801AF85C(p);
    for (int i = 0; i < count; i++) {
        int n = work->mEntries[i].mUnknown9;
        unsigned char *values = work->mValues + work->mEntries[i].mUnknown8;
        while (n > 1) {
            int j = fn_801B1C1C(n, -1);
            unsigned char value = values[j];
            values[j] = values[n - 1];
            values[n - 1] = value;
            n--;
        }
    }
}

int fn_801B0974(unsigned char *p, Work_801B10AC *work)
{
    int result = 0;
    int index = fn_801AF85C(p) - 1;
    int done = 0;
    WorkEntry_801B0B18 *entry = &work->mEntries[index];
    int end = entry->mUnknown8 + entry->mUnknown9;
    do {
        entry->mUnknownA++;
        if (entry->mUnknownA < end) {
            done = 1;
        } else {
            entry->mUnknownA = entry->mUnknown8;
            if (--index < 0) {
                done = 1;
                result = 1;
            }
            entry = &work->mEntries[index];
            end = entry->mUnknown8 + entry->mUnknown9;
        }
    } while (!done);
    return result;
}

int fn_801B0A18(unsigned char *p, Work_801B10AC *work, int limit)
{
    int count = fn_801AF85C(p);
    int found = 0;
    int done = 0;
    for (int i = 0; i < count; i++) work->mEntries[i].mUnknownA = work->mEntries[i].mUnknown8;
    while (!done && !found) {
        found = 1;
        if (limit) found = fn_801B0208(p, work) <= limit;
        if (found) {
            if (p[3] && !fn_801B05E4(work, p)) found = 0;
        }
        if (!found) done = fn_801B0974(p, work);
    }
    return found;
}

int fn_801B0B18(WorkEntry_801B0B18 *p)
{
    int value = fn_801B1C1C(p->mUnknown9, p->mUnknown4);
    p->mUnknownA = p->mUnknown8 + value;
    return 1;
}

void fn_801B0B5C(Key_801AE658 *key, Work_801B10AC *work, unsigned char *p)
{
    char *text;
    if (fn_801AE7B4(key, &text)) {
        int count = fn_801AF85C(p);
        for (int i = 0; i < count; i++) {
            Record_801AF75C *record = (Record_801AF75C *)fn_801AF928((char *)p, p + 8, i);
            for (int j = 0; j < record->mUnknown4; j++) {
                if (fn_801AF84C(record, j)->mUnknown4 == 254) {
                    if (!(fn_801AF84C(record, j)->mUnknown6 & 128)) {
                        int slot = work->mEntries[i].mUnknown4;
                        RowBank_801AFE90 *bank = lbl_803EBB00[slot].mUnknown4;
                        char *values = fn_801B22B0(bank, work->mValues[work->mEntries[i].mUnknownA]);
                        if (values) {
                            int index = fn_801AF84C(record, j)->mUnknown6;
                            text[index] = values[j];
                        }
                    }
                }
            }
        }
    }
}

int fn_801B0C7C(Key_801AE658 *key, Work_801B10AC *work, unsigned char *p, int a, int limit)
{
    int result;
    if (limit > 0 || p[3]) {
        fn_801B08DC(p, work);
        result = fn_801B0A18(p, work, limit);
    } else {
        int count = fn_801AF85C(p);
        result = 1;
        for (int i = 0; i < count; i++) {
            WorkEntry_801B0B18 *entry = &work->mEntries[i];
            if (!entry->mUnknown9) return 0;
            fn_801AF928((char *)p, p + 8, i);
            if (!fn_801B0B18(entry)) return 0;
        }
    }
    fn_801B0B5C(key, work, p);
    return result;
}

void fn_801B10AC(Work_801B10AC *p)
{
    p->mUnknown90 = 0;
    p->mCount = 0;
    for (int i = 0; i <= 11; i++) p->mEntries[i].mUnknownB = 0;
}

void fn_801B10D8(int channel)
{
    Channel_801B118C *p = &lbl_8037E294[channel];
    if (p->mUnknownC) {
        fn_801AF500(p->mUnknownC);
        p->mUnknownC = 0;
    }
    p->mUnknown0 = 0;
    p->mUnknown4 = 0;
    p->mUnknownB = 0;
    p->mUnknown8 = 0;
    p->mUnknown9 = 0;
    p->mUnknownA = 0;
    p->mUnknownC = 0;
    for (int i = 0; i <= 11; i++) {
        p->mEntries[i].mUnknown0 = -1;
        p->mEntries[i].mUnknown8 = 0;
        p->mEntries[i].mUnknown4 = -1;
        p->mEntries[i].mUnknown6 = -1;
    }
}

void fn_801B118C(void)
{
    for (int channel = 0; channel <= 7; channel++) {
        Channel_801B118C *p = &lbl_8037E294[channel];
        p->mUnknown0 = 0;
        p->mUnknown4 = 0;
        p->mUnknownB = 0;
        p->mUnknown8 = 0;
        p->mUnknown9 = 0;
        p->mUnknownA = 0;
        p->mUnknownC = 0;
        for (int i = 0; i <= 11; i++) {
            p->mEntries[i].mUnknown0 = -1;
            p->mEntries[i].mUnknown8 = 0;
            p->mEntries[i].mUnknown4 = -1;
            p->mEntries[i].mUnknown6 = -1;
        }
    }
}

int fn_801B1368(unsigned int channel)
{
    return lbl_8037E294[channel].mUnknown9;
}

int fn_801B1474(unsigned int bits, int value, int index)
{
    int result = 0;
    switch ((bits >> (index * 2)) & 3) {
    case 1:
        if (value != 0) result = 1;
        break;
    case 2:
        if (value != -1) result = 1;
        break;
    }
    return result;
}

int fn_801B14B4(Item_801AE3F4 *p, int *values)
{
    unsigned int bits = fn_801AFA70(p);
    int result = 0;
    unsigned short mask = 1;
    for (int i = 0; i <= 15; i++) {
        if (fn_801B1474(bits, values[i + 1], i)) {
            result |= mask;
        }
        mask <<= 1;
    }
    return result;
}

int fn_801B15E4(unsigned char *p)
{
    return fn_801B1C1C(100, -1) < p[1];
}

void fn_801B192C(int value)
{
    lbl_803ECEA8 = value;
}

unsigned int fn_801B1934(void)
{
    unsigned int old = lbl_802F477C[4];
    unsigned int sum = old + lbl_802F477C[5];
    unsigned int carry = sum < old || sum < lbl_802F477C[5];
    lbl_802F477C[4] = sum;
    old = lbl_802F477C[3];
    sum += old + carry;
    lbl_802F477C[3] = sum;
    carry = sum < old;
    old = lbl_802F477C[2];
    sum += old + carry;
    lbl_802F477C[2] = sum;
    carry = sum < old;
    old = lbl_802F477C[1];
    sum += old + carry;
    lbl_802F477C[1] = sum;
    carry = sum < old;
    sum += lbl_802F477C[0] + carry;
    lbl_802F477C[0] = sum;
    for (int i = 5; i >= 0; i--) {
        if (++lbl_802F477C[i]) break;
    }
    return lbl_802F477C[0];
}

}
