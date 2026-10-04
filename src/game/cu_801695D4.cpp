#include "game/Desc_80169DF8.h"

struct State_80169DF8 {
    Desc_80169DF8 mUnknown0;
    unsigned char **mUnknown16;
    unsigned char **mUnknown20;
};

static State_80169DF8 lbl_8036167C;

extern "C" {

int fn_801695D4(unsigned char **pp, short *pRecord)
{
    unsigned char first = *(*pp)++;
    if ((first & 0xC0) == 0x80)
        return pRecord[first & 0x7F];
    int value = *(*pp)++;
    value += first << 8;
    if (value & 0x2000)
        value |= 0xFFFFC000;
    return value;
}

unsigned char *fn_80169628(unsigned char **pTable, int index)
{
    return pTable[index];
}

void fn_80169634(int *pTable, int count)
{
    for (int i = 0; i < count; ++i)
        pTable[i] = (int)pTable + pTable[i];
}

int fn_8016965C(int a, int b) { return a == b; }
int fn_8016966C(int a, int b) { return a < b; }
int fn_8016967C(int a, int b) { return a > b; }
int fn_8016968C(int a, int b) { return a <= b; }
int fn_801696A0(int a, int b) { return a >= b; }
int fn_801696B4(int a, int b) { return a != b; }

}

static int (*const lbl_802A4BF8[])(int, int) = {
    fn_8016965C, fn_8016965C, fn_8016966C, fn_8016967C,
    fn_8016968C, fn_801696A0, fn_801696B4
};

extern "C" {

void fn_801696C8(unsigned char *p, short *pRecord, Callback_80169DF8 callback)
{
    unsigned char *stack[10];
    int result = 0;
    unsigned char depth = 0;

    do {
        unsigned char instruction = *p++;
        int count = instruction & 15;
        switch (instruction >> 4) {
        case 0: {
            if (depth == 0) {
                result = 3;
                break;
            }
            unsigned char *saved = stack[--depth];
            while (saved <= p) {
                if (depth == 0) {
                    result = 3;
                    break;
                }
                saved = stack[--depth];
            }
            if (result != 0)
                break;
            p = saved - 1;
            break;
        }
        case 1: {
            unsigned char *base = p;
            int offset = (short)(*p++ << 8);
            offset |= *p++;
            for (int i = count; i > 0; --i) {
                int a = fn_801695D4(&p, pRecord);
                unsigned char comparison = *p++;
                int b = fn_801695D4(&p, pRecord);
                if (!lbl_802A4BF8[comparison](a, b)) {
                    p = base + offset - 1;
                    break;
                }
            }
            break;
        }
        case 2: {
            unsigned char *base = p;
            int a = fn_801695D4(&p, pRecord);
            stack[depth] = base + (*p++ << 8);
            stack[depth] += *p++;
            ++depth;
            stack[depth] = base + (*p++ << 8);
            stack[depth] += *p++;
            int i;
            for (i = 0; i < count; ++i) {
                base = p++;
                int b;
                if ((*p & 0xC0) == 0x40 || (*p & 0xC0) == 0xC0) {
                    pRecord[17] = a;
                    if (callback(11, pRecord, *p))
                        b = a;
                    else
                        b = a + 1;
                    ++p;
                } else {
                    b = fn_801695D4(&p, pRecord);
                }
                int offset = (short)(*p++ << 8);
                offset |= *p++;
                if (a == b)
                    break;
                p = base + offset;
            }
            if (i == count)
                p = stack[depth] - 1;
            break;
        }
        case 3:
            pRecord[19] = count;
            result = 4;
            break;
        case 4:
            pRecord[19] = *p;
            result = 1;
            break;
        case 5:
            pRecord[19] = *p++;
            pRecord[19] += *p << 8;
            result = 2;
            break;
        case 6:
            if ((*p & 0xC0) == 0x40 || (*p & 0xC0) == 0xC0)
                ++p;
            else
                fn_801695D4(&p, pRecord);
            p += 2;
            break;
        case 7:
            pRecord[18] = *p++;
            pRecord[18] += *p++ << 8;
            break;
        }
    } while (result == 0);
    pRecord[17] = result;
}

int fn_80169A7C(short *pRecord, Callback_80169DF8 callback)
{
    int result = -1;
    switch (pRecord[19]) {
    case 255:
        callback(6, pRecord, 0);
        result = 1;
        break;
    case 253:
        if (pRecord[15] == 255) {
            callback(6, pRecord, 0);
            result = 1;
        }
        break;
    case 252:
        if (pRecord[15] != 255)
            break;
    case 254:
        callback(7, pRecord, 0);
        result = 1;
        break;
    }
    return result;
}

int fn_80169B20(short *pRecord, Callback_80169DF8 callback, int mode)
{
    int result = -1;
    switch (mode) {
    case 0:
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19]);
            result = 1;
            break;
        case 2:
            switch (pRecord[19]) {
            case 254:
                callback(5, pRecord, 254);
                break;
            case 255:
                callback(12, pRecord, 255);
                break;
            default:
                callback(9, pRecord, pRecord[19]);
                break;
            }
            result = 1;
            break;
        }
        break;
    case 1:
        callback(10, pRecord, pRecord[8]);
        result = 1;
        break;
    case 2:
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        case 2:
            callback(9, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        }
        pRecord[19] = result;
        break;
    case 3:
        if (pRecord[17] == 2) {
            switch (pRecord[19]) {
            case 255:
                callback(1, pRecord, 0);
                result = 1;
                break;
            case 254:
                callback(2, pRecord, 0);
                result = 1;
                break;
            case 253:
                callback(3, pRecord, 0);
                result = 1;
                break;
            case 252:
                callback(4, pRecord, 0);
                result = 1;
                break;
            }
        }
        break;
    case 4:
        result = fn_80169A7C(pRecord, callback);
        break;
    }
    return result;
}

int fn_80169CE0(short *pRecord, Callback_80169DF8 callback, int mode)
{
    int result = 1;
    switch (mode) {
    case 0:
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19]);
            break;
        case 2:
            callback(9, pRecord, pRecord[19]);
            break;
        }
        break;
    case 2:
        result = 0;
        switch (pRecord[17]) {
        case 1:
            callback(8, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        case 2:
            callback(9, pRecord, pRecord[19] | 0x8000);
            result = 1;
            break;
        }
        break;
    case 3:
        if (pRecord[17] == 2)
            callback(1, pRecord, 0);
        break;
    case 4:
        result = fn_80169A7C(pRecord, callback);
        break;
    }
    return result;
}

void fn_80169DF8(Desc_80169DF8 *pDesc)
{
    lbl_8036167C.mUnknown0 = *pDesc;
    fn_80169634((int *)pDesc->mUnknown0, 10);
    lbl_8036167C.mUnknown16 = (unsigned char **)pDesc->mUnknown0;
    lbl_8036167C.mUnknown20 = (unsigned char **)(pDesc->mUnknown0 + 20);
}

int fn_80169E68(int mode)
{
    if (lbl_8036167C.mUnknown0.mUnknown8)
        lbl_8036167C.mUnknown0.mUnknown8(0, lbl_8036167C.mUnknown0.mUnknown4, mode);
    unsigned char *p = fn_80169628(lbl_8036167C.mUnknown16, mode);
    lbl_8036167C.mUnknown0.mUnknown4[18] = -1;
    fn_801696C8(p, lbl_8036167C.mUnknown0.mUnknown4, lbl_8036167C.mUnknown0.mUnknown8);
    fn_80169B20(lbl_8036167C.mUnknown0.mUnknown4, lbl_8036167C.mUnknown0.mUnknown8, mode);
    return lbl_8036167C.mUnknown0.mUnknown4[19];
}

int fn_80169EF4(int mode)
{
    if (lbl_8036167C.mUnknown0.mUnknownC)
        lbl_8036167C.mUnknown0.mUnknownC(0, lbl_8036167C.mUnknown0.mUnknown4, mode);
    unsigned char *p = fn_80169628(lbl_8036167C.mUnknown20, mode);
    lbl_8036167C.mUnknown0.mUnknown4[18] = -1;
    fn_801696C8(p, lbl_8036167C.mUnknown0.mUnknown4, lbl_8036167C.mUnknown0.mUnknownC);
    fn_80169CE0(lbl_8036167C.mUnknown0.mUnknown4, lbl_8036167C.mUnknown0.mUnknownC, mode);
    return lbl_8036167C.mUnknown0.mUnknown4[19];
}

}
