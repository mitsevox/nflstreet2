/* Controller remapping tables: each table maps game actions to combinations of pad buttons and analog
   axes, and RemapCheckEntry turns the current pad input into a float value for one action. */

#include "engine/SysSetLastErrorFunc.h"
#include "engine/fn_801F8014.h"
#include "engine/remap.h"
#include "game/fn_801D2B7C.h"

static unsigned char _Remap_ModuleActive = 0;

static Lock_801F8014 _Remap_CS;

/* The table geometry RemapInit was given and the table block it allocated. */
static unsigned int _Remap_NumTables;
static unsigned int _Remap_NumEntries;
static unsigned int _Remap_NumInputs;
static unsigned int _Remap_BytesPerTable;
static unsigned int _Remap_ArraySize;
static unsigned char *_pRemap_TableArray;
extern unsigned int Per_MaxAxis;
extern unsigned char Per_BtnMask[8];

void *memcpy();
int MemFill(void *p, unsigned int size, int value, int flags);

int RemapInit(unsigned int numTables, unsigned int numEntries, unsigned int numInputs)
{
    int err = 0;

    if (_Remap_ModuleActive == 0) {
        fn_801F7FA8(&_Remap_CS);
        fn_801F8014(&_Remap_CS);
        _Remap_NumTables = numTables;
        _Remap_NumEntries = numEntries;
        _Remap_NumInputs = numInputs;
        _pRemap_TableArray = 0;
        _Remap_BytesPerTable = numEntries * numInputs * 2;
        _Remap_ArraySize = _Remap_BytesPerTable * numTables;
        if (_Remap_ArraySize != 0) {
            _pRemap_TableArray = fn_801D2BB0(1, _Remap_ArraySize, 0, 0);
            if (_pRemap_TableArray == 0) {
                err = SysGetLastError();
            } else {
                MemFill(_pRemap_TableArray, _Remap_ArraySize, 0, 2);
                _Remap_ModuleActive = 1;
            }
        } else {
            _Remap_ModuleActive = 1;
        }
        fn_801F809C(&_Remap_CS);
    } else {
        err = 0x180001;
    }
    SysSetLastErrorFunc(err);
    return err;
}

int RemapShutdown(void)
{
    int err = 0;

    if (_Remap_ModuleActive != 0) {
        fn_801F8014(&_Remap_CS);
        if (_pRemap_TableArray != 0) {
            fn_801D2BD0(_pRemap_TableArray);
        }
        fn_801F809C(&_Remap_CS);
        fn_801F80D0(&_Remap_CS);
        _Remap_ModuleActive = 0;
    } else {
        err = 0x180002;
    }
    SysSetLastErrorFunc(err);
    return err;
}

int RemapSetupEntries(unsigned int table, unsigned int start, unsigned int count, void *pData)
{
    int err = 0;

    if (start + count <= _Remap_NumEntries && table < _Remap_NumTables && count != 0) {
        // FAKEMATCH: called through an unprototyped type, as a call with no prototype in scope compiles
        ((void *(*)())memcpy)((unsigned short *)(_pRemap_TableArray + table * _Remap_BytesPerTable) + start * _Remap_NumInputs, pData,
                    count * _Remap_NumInputs * sizeof(unsigned short));
    } else {
        err = 0x180003;
    }
    SysSetLastErrorFunc(err);
    return err;
}

int RemapCopyTable(unsigned int dst, unsigned int src)
{
    int err = 0x180003;

    if (src < _Remap_NumTables && dst < _Remap_NumTables) {
        RemapSetupEntries(dst, 0, _Remap_NumEntries, _pRemap_TableArray + src * _Remap_BytesPerTable);
        err = 0;
    }
    return err;
}

float RemapCheckEntry(unsigned int table, unsigned int entry, unsigned char *pInputs)
{
    int err = 0;
    float result = 0.0f;
    float value;
    unsigned short *pCode;
    unsigned int code;
    unsigned char index;
    unsigned int i;

    if (table < _Remap_NumTables && entry < _Remap_NumEntries) {
        pCode = (unsigned short *)(_pRemap_TableArray + table * _Remap_BytesPerTable) + entry * _Remap_NumInputs;
        for (i = 0; i < _Remap_NumInputs; i++) {
            code = pCode[i];
            if (code == 0) {
                break;
            }
            if (code & 0x2000) {
                value = ((float)(signed char)pInputs[code & 0xFF] + 128.0f) * (1.0f / 255.0f);
            } else if (code & 0x4000) {
                value = (float)(signed char)pInputs[code & 0xFF] * (1.0f / 127.0f);
            } else {
                index = code & 0xFF;
                if (Per_BtnMask[index & 7] & pInputs[Per_MaxAxis + (index >> 3)]) {
                    value = 1.0f;
                } else {
                    value = 0.0f;
                }
            }
            if (code & 0x100) {
                if (value != 0.0f) {
                    value = 0.0f;
                } else {
                    value = 1.0f;
                }
            }
            if (code & 0x200) {
                value = -value;
            }
            if (code & 0x400) {
                if (!(value >= 0.0f)) {
                    value = 0.0f;
                }
            }
            if (code & 0x800) {
                if (!(value <= 0.0f)) {
                    value = 0.0f;
                }
            }
            if ((code & 0x1000) && i != 0) {
                if (value == 0.0f) {
                    value = 1.0f;
                } else if (result == 0.0f) {
                    result = 1.0f;
                }
            }
            if (i == 0) {
                result = value;
            } else {
                result *= value;
            }
        }
    } else {
        err = 0x180003;
        result = 0.0f;
    }
    SysSetLastErrorFunc(err);
    return result;
}
