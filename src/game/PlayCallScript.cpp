/* Play-call script interpreter: installs the AI play-call script loaded with the playbook, runs
   its offense or defense stream for a game mode, and hands the commands it reaches (fill the
   situation, pick a play by kind or id, signal the end of the call) to the command callbacks. */

#include "game/PlayCallScript.h"

struct PlayCallScriptState_t {
    PlayCallScriptDesc_t mUnknown0;
    unsigned char **mUnknown16;
    unsigned char **mUnknown20;
};

static PlayCallScriptState_t _PlayCallScript_sState;

extern "C" {

int PlayCallScriptReadValue(unsigned char **pp, short *pRecord)
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

unsigned char *PlayCallScriptGetStream(unsigned char **pTable, int index)
{
    return pTable[index];
}

void PlayCallScriptRelocate(int *pTable, int count)
{
    for (int i = 0; i < count; ++i)
        pTable[i] = (int)pTable + pTable[i];
}

int PlayCallScriptIsEqual(int a, int b) { return a == b; }
int PlayCallScriptIsLess(int a, int b) { return a < b; }
int PlayCallScriptIsGreater(int a, int b) { return a > b; }
int PlayCallScriptIsLessEqual(int a, int b) { return a <= b; }
int PlayCallScriptIsGreaterEqual(int a, int b) { return a >= b; }
int PlayCallScriptIsNotEqual(int a, int b) { return a != b; }

}

static int (*const _PlayCallScript_apfnCompare[])(int, int) = {
    PlayCallScriptIsEqual, PlayCallScriptIsEqual, PlayCallScriptIsLess, PlayCallScriptIsGreater,
    PlayCallScriptIsLessEqual, PlayCallScriptIsGreaterEqual, PlayCallScriptIsNotEqual
};

extern "C" {

void PlayCallScriptExecute(unsigned char *p, short *pRecord, PlayCallScriptCallback_t callback)
{
    unsigned char *stack[10];
    int result = 0;
    unsigned char depth = 0;

    do {
        unsigned char *base;
        short offset;
        int i, a, b;
        unsigned char instruction = *p++;
        int count = instruction & 15;
        switch (instruction >> 4) {
        case 0: {
            if (depth == 0) {
                result = 3;
                break;
            }
            unsigned char *saved = stack[--depth];
            for (;;) {
                if (saved > p) {
                    p = saved - 1;
                    break;
                }
                if (depth == 0) {
                    result = 3;
                    goto next;
                }
                saved = stack[--depth];
            }
            break;
        }
        case 1: {
            base = p;
            offset = (short)(*p++ << 8);
            offset |= *p++;
            for (i = count; i > 0; --i) {
                a = PlayCallScriptReadValue(&p, pRecord);
                unsigned char comparison = *p++;
                b = PlayCallScriptReadValue(&p, pRecord);
                if (!_PlayCallScript_apfnCompare[comparison](a, b)) {
                    p = base + offset - 1;
                    break;
                }
            }
            break;
        }
        case 2: {
            base = p;
            a = PlayCallScriptReadValue(&p, pRecord);
            stack[depth] = base + (*p++ << 8);
            stack[depth] += *p++;
            ++depth;
            stack[depth] = base + (*p++ << 8);
            stack[depth] += *p++;
            for (i = 0; i < count; ++i) {
                base = p++;
                if ((*p & 0xC0) == 0x40 || (*p & 0xC0) == 0xC0) {
                    pRecord[17] = a;
                    if (callback(11, pRecord, *p))
                        b = a;
                    else
                        b = a + 1;
                    ++p;
                } else {
                    b = PlayCallScriptReadValue(&p, pRecord);
                }
                offset = (short)(*p++ << 8);
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
                PlayCallScriptReadValue(&p, pRecord);
            p += 2;
            break;
        case 7:
            pRecord[18] = *p++;
            pRecord[18] += *p++ << 8;
            break;
        }
next:
        ;
    } while (result == 0);
    pRecord[17] = result;
}

int PlayCallScriptHandleEndCode(short *pRecord, PlayCallScriptCallback_t callback)
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

int PlayCallScriptApplyOffenseResult(short *pRecord, PlayCallScriptCallback_t callback, int mode)
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
        result = PlayCallScriptHandleEndCode(pRecord, callback);
        break;
    }
    return result;
}

int PlayCallScriptApplyDefenseResult(short *pRecord, PlayCallScriptCallback_t callback, int mode)
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
        result = PlayCallScriptHandleEndCode(pRecord, callback);
        break;
    }
    return result;
}

void PlayCallScriptInit(PlayCallScriptDesc_t *pDesc)
{
    _PlayCallScript_sState.mUnknown0 = *pDesc;
    PlayCallScriptRelocate((int *)pDesc->mUnknown0, 10);
    _PlayCallScript_sState.mUnknown16 = (unsigned char **)pDesc->mUnknown0;
    _PlayCallScript_sState.mUnknown20 = (unsigned char **)(pDesc->mUnknown0 + 20);
}

int PlayCallScriptRunOffense(int mode)
{
    if (_PlayCallScript_sState.mUnknown0.mUnknown8)
        _PlayCallScript_sState.mUnknown0.mUnknown8(0, _PlayCallScript_sState.mUnknown0.mUnknown4, mode);
    unsigned char *p = PlayCallScriptGetStream(_PlayCallScript_sState.mUnknown16, mode);
    _PlayCallScript_sState.mUnknown0.mUnknown4[18] = -1;
    PlayCallScriptExecute(p, _PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknown8);
    PlayCallScriptApplyOffenseResult(_PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknown8, mode);
    return _PlayCallScript_sState.mUnknown0.mUnknown4[19];
}

int PlayCallScriptRunDefense(int mode)
{
    if (_PlayCallScript_sState.mUnknown0.mUnknownC)
        _PlayCallScript_sState.mUnknown0.mUnknownC(0, _PlayCallScript_sState.mUnknown0.mUnknown4, mode);
    unsigned char *p = PlayCallScriptGetStream(_PlayCallScript_sState.mUnknown20, mode);
    _PlayCallScript_sState.mUnknown0.mUnknown4[18] = -1;
    PlayCallScriptExecute(p, _PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknownC);
    PlayCallScriptApplyDefenseResult(_PlayCallScript_sState.mUnknown0.mUnknown4, _PlayCallScript_sState.mUnknown0.mUnknownC, mode);
    return _PlayCallScript_sState.mUnknown0.mUnknown4[19];
}

}
