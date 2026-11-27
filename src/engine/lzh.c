/* LZH compression for the EA engine: an LZ coder whose output is Huffman
   coded block by block. It has an encoder (input, code buffer, tree
   building, bit writer, checksum) and two decoders, one reading through a
   stream callback and one reading from memory. */

#include <dolphin/os.h>
#include "engine/SysCriticalSection.h"
#include "game/fn_801D2B7C.h"
#include "engine/lzh.h"

typedef struct LZHStage_t
{
    int (*mpProcess)(void);
    int mCodeIndex;
} LZHStage_t;

typedef struct LZHHeapNode_t
{
    short mUnknown00;
    unsigned short mUnknown02;
} LZHHeapNode_t;

static unsigned char _LZH_ModuleIsActive = 0;

static SysCriticalSection_t _LZH_CS;
static SysCriticalSection_t _LZHMem_CS;
static SysCriticalSection_t _LZHHuff_CS;
static LZHDecodeEntry_t _LZH_LLCode_DecodeTable[570];
static LZHHuffCode_t _LZH_LLCode_HuffCode[285];
static LZHDecodeEntry_t _LZH_PCode_DecodeTable[60];
static LZHHuffCode_t _LZH_PCode_HuffCode[30];
static LZHDecodeEntry_t _LZHMem_LLCode_DecodeTable[570];
static LZHHuffCode_t _LZHMem_LLCode_HuffCode[285];
static LZHDecodeEntry_t _LZHMem_PCode_DecodeTable[60];
static LZHHuffCode_t _LZHMem_PCode_HuffCode[30];
static short _LZH_CodeLenCount[16];
static short _LZH_DecodeTree[285][2];
static unsigned char _LZH_LLCodeConvert[228];
static unsigned char _LZH_PCodeConvertLo[256];
static unsigned char _LZH_PCodeConvertHi[256];
static LZHHeapNode_t _LZH_Heap[286];
static unsigned char _LZH_ByteBuffer[256];

static unsigned char _LZH_IsCompleteOutBuffer;
static int _LZH_Usage;
static LZHStage_t _LZH_StageInfo;
static int _LZHMem_Usage;
static LZHStage_t _LZHMem_StageInfo;
static unsigned short _LZH_WindowBuffer;
static unsigned short _LZH_WindowEnd;
static unsigned char *_LZH_pWindow;
static short _LZH_WindowBufferSize;
static unsigned short *_LZH_pHashTable;
static unsigned short *_LZH_pHashValue;
static unsigned short *_LZH_pHashLink;
static unsigned char *_LZH_pLLCodeBuffer;
static unsigned short *_LZH_pPCodeBuffer;
static unsigned short _LZH_CodeBufferSize;
static unsigned int (*_LZHHuffReadBitsFunc)(short count);
static short *_LZH_pEncodeTree;
static short _LZH_NextFreeTable;
static LZHDecodeEntry_t *_LZH_pDecodeTable;
static short _LZH_HeapSize;
static LZHBlock_t *_LZH_pInBlock;
static LZHBlock_t *_LZH_pOutBlock;
static short _LZH_BitBufferSize;
static short _LZH_ByteBufferEnd;
static unsigned int _LZH_BitBuffer;
static short _LZH_ByteBufferNextEnd;
static short _LZH_ByteBufferBegin;
static int _LZH_InRemaining;
static unsigned char *_LZH_pInData;
static int _LZH_OutRemaining;
static unsigned char *_LZH_pOutData;
static unsigned int _LZH_Checksum;
static short _LZHMem_BitBufferSize;
static unsigned int _LZHMem_BitBuffer;
static int _LZHMem_InRemaining;
static unsigned char *_LZHMem_pInData;
static int _LZHMem_OutRemaining;
static unsigned char *_LZHMem_pOutData;
static unsigned int _LZHMem_Checksum;

static const LZHCodeSet_t _LZH_LLCode = { _LZH_LLCode_HuffCode, _LZH_LLCode_DecodeTable, 285 };
static const LZHCodeSet_t _LZH_PCode = { _LZH_PCode_HuffCode, _LZH_PCode_DecodeTable, 30 };
static const LZHCodeSet_t _LZHMem_LLCode = { _LZHMem_LLCode_HuffCode, _LZHMem_LLCode_DecodeTable, 285 };
static const LZHCodeSet_t _LZHMem_PCode = { _LZHMem_PCode_HuffCode, _LZHMem_PCode_DecodeTable, 30 };
static const unsigned char _LZH_LLCodeExtra[28] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 0,
};
static const short _LZH_LLCodeBase[29] = {
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
    35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 228,
};
static const unsigned char _LZH_PCodeExtra[30] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13,
};
static const unsigned short _LZH_PCodeBase[31] = {
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
    257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 32769,
};

void _LZHHuffWriteHuffData(const LZHCodeSet_t *p);
void _LZHHuffEncodeBuildTree(const LZHCodeSet_t *p);
void _LZHHuffEncodeGenCodeLen(const LZHCodeSet_t *p);
void _LZHHuffReadHuffData(const LZHCodeSet_t *p);
void _LZHHuffAssignCodes(const LZHCodeSet_t *p);
void _LZHHuffDecodeBuildTree(const LZHCodeSet_t *p);
void _LZHHuffDecodeBuildTable(const LZHCodeSet_t *p);
unsigned int _LZHReadBits(short count);
int _LZHDecodeInput(void);
int _LZHDecodeInputFull(void);
int _LZHEncodeCodeBuffer(void);
void _LZHEncodeCodeBufferStart(void);
void _LZHUpdateChecksum(unsigned int *sum, unsigned char *data, unsigned int length);
int _LZHEncodeNewBlock(void);
int _LZHEncodeNewBlockEOF(void);
int _LZHEncodeInput(void);
int _LZHDecodeNewBlock(void);
int _LZHMemDecodeNewBlock(void);
void _LZHHuffGenCodeConvertTables(void);
void _LZHWriteBits(short count, unsigned int value);
void _LZHFlushByteBuffer(void);
void _LZHFlushBitBuffer(void);
int _LZHMemDecStart(LZHBlock_t *a, LZHBlock_t *b);
void _LZHMemDecStop(LZHBlock_t *a, LZHBlock_t *b, int mode);
int _LZHMemProcess(LZHBlock_t *a, LZHBlock_t *b, int mode);

int _LZHInit(void)
{
    if (_LZH_ModuleIsActive == 0) {
        _LZH_ModuleIsActive = 1;
        _LZH_Usage = 0;
        _LZHMem_Usage = 0;
        SysInitCriticalSectionFunc(&_LZH_CS);
        SysInitCriticalSectionFunc(&_LZHMem_CS);
        SysInitCriticalSectionFunc(&_LZHHuff_CS);
        _LZH_pWindow = 0;
        return 0;
    }
    return 0x150001;
}

int _LZHShutdown(void)
{
    if (_LZH_ModuleIsActive != 0 && _LZH_Usage == 0 && _LZHMem_Usage == 0) {
        SysShutdownCriticalSectionFunc(&_LZH_CS);
        SysShutdownCriticalSectionFunc(&_LZHMem_CS);
        SysShutdownCriticalSectionFunc(&_LZHHuff_CS);
        _LZH_ModuleIsActive = 0;
        return 0;
    }
    return 0x150002;
}

int _LZHCoStart(void)
{
    unsigned short i;
    SysEnterCriticalSectionFunc(&_LZH_CS);
    _LZH_Usage = 1;
    _LZH_pWindow = fn_801D2BB0(1, 0x8000, 0, 0);
    _LZH_pHashTable = fn_801D2BB0(1, 0x7FFA, 0, 0);
    _LZH_pHashLink = fn_801D2BB0(1, 0x10000, 0, 0);
    _LZH_pHashValue = fn_801D2BB0(1, 0x10002, 0, 0);
    for (i = 0; i <= 0x3FFC; i++) {
        _LZH_pHashTable[i] = -32768;
    }
    _LZH_pHashValue[0x8000] = 0x3FFD;
    _LZH_pLLCodeBuffer = fn_801D2BB0(1, 0x4000, 0, 0);
    _LZH_pPCodeBuffer = fn_801D2BB0(1, 0x8000, 0, 0);
    _LZH_pEncodeTree = fn_801D2BB0(1, 0x474, 0, 0);
    _LZHHuffGenCodeConvertTables();
    _LZH_CodeBufferSize = 0;
    _LZH_ByteBufferEnd = 0;
    _LZH_Checksum = 1;
    _LZH_StageInfo.mpProcess = _LZHEncodeNewBlock;
    _LZH_WindowBuffer = 0;
    _LZH_WindowEnd = 0;
    _LZH_WindowBufferSize = 0;
    _LZH_BitBuffer = 0;
    _LZH_BitBufferSize = 0;
    _LZH_ByteBufferBegin = 0;
    return 0;
}

void _LZHCoStop(void)
{
    fn_801D2BD0(_LZH_pEncodeTree);
    fn_801D2BD0(_LZH_pPCodeBuffer);
    fn_801D2BD0(_LZH_pLLCodeBuffer);
    fn_801D2BD0(_LZH_pHashValue);
    fn_801D2BD0(_LZH_pHashLink);
    fn_801D2BD0(_LZH_pHashTable);
    fn_801D2BD0(_LZH_pWindow);
    _LZH_pWindow = 0;
    _LZH_Usage = 0;
    SysExitCriticalSectionFunc(&_LZH_CS);
}

int _LZHDecStart(LZHBlock_t *a, LZHBlock_t *b)
{
    if (a->mUnknown18 != 0 && b->mUnknown18 != 0) {
        return _LZHMemDecStart(a, b);
    }
    SysEnterCriticalSectionFunc(&_LZH_CS);
    _LZH_ByteBufferEnd = 0;
    _LZH_Usage = 2;
    _LZH_WindowBuffer = 0;
    _LZH_WindowEnd = 0;
    _LZH_WindowBufferSize = 0;
    _LZH_CodeBufferSize = 0;
    _LZH_BitBuffer = 0;
    _LZH_BitBufferSize = 0;
    _LZH_ByteBufferBegin = 0;
    if (b->mUnknown18 != 0) {
        _LZH_IsCompleteOutBuffer = 1;
    } else {
        _LZH_IsCompleteOutBuffer = 0;
        _LZH_pWindow = fn_801D2BB0(1, 0x8000, 0, 0);
    }
    _LZH_Checksum = 1;
    _LZH_StageInfo.mpProcess = _LZHDecodeNewBlock;
    return 0;
}

int _LZHMemDecStart(LZHBlock_t *a, LZHBlock_t *b)
{
    SysEnterCriticalSectionFunc(&_LZHMem_CS);
    _LZHMem_Usage = 2;
    _LZHMem_BitBufferSize = _LZHMem_BitBuffer = 0;
    _LZHMem_StageInfo.mpProcess = _LZHMemDecodeNewBlock;
    return 1;
}

void _LZHDecStop(LZHBlock_t *a, LZHBlock_t *b, int mode)
{
    if (mode == 1) {
        _LZHMemDecStop(a, b, 1);
    } else {
        if (_LZH_pWindow != 0) {
            fn_801D2BD0(_LZH_pWindow);
            _LZH_pWindow = 0;
        }
        _LZH_Usage = 0;
        SysExitCriticalSectionFunc(&_LZH_CS);
    }
}

void _LZHMemDecStop(LZHBlock_t *a, LZHBlock_t *b, int mode)
{
    _LZHMem_Usage = 0;
    SysExitCriticalSectionFunc(&_LZHMem_CS);
}

int _LZHProcess(LZHBlock_t *a, LZHBlock_t *b, int mode)
{
    static unsigned char bProcessing;

    if (mode == 1) {
        return _LZHMemProcess(a, b, 1);
    }
    bProcessing = 1;
    _LZH_pInBlock = a;
    _LZH_InRemaining = a->mUnknown04 - a->mUnknown08;
    _LZH_pInData = a->mUnknown00 + a->mUnknown08;
    _LZH_OutRemaining = b->mUnknown04 - b->mUnknown08;
    _LZH_pOutBlock = b;
    _LZH_pOutData = b->mUnknown00 + b->mUnknown08;
    if (_LZH_StageInfo.mpProcess != 0) {
        do {
            switch ((unsigned char)_LZH_StageInfo.mpProcess()) {
            case 0:
                break;
            case 1:
                bProcessing = 0;
                return 2;
            case 2:
                bProcessing = 0;
                return 3;
            }
        } while (_LZH_StageInfo.mpProcess != 0);
    }
    bProcessing = 0;
    return 1;
}

int _LZHMemProcess(LZHBlock_t *a, LZHBlock_t *b, int mode)
{
    static unsigned char bProcessing;

    bProcessing = 1;
    _LZHMem_InRemaining = a->mUnknown04 - a->mUnknown08;
    _LZHMem_pInData = a->mUnknown00 + a->mUnknown08;
    _LZHMem_OutRemaining = b->mUnknown04 - b->mUnknown08;
    _LZHMem_pOutData = b->mUnknown00 + b->mUnknown08;
    if (_LZHMem_StageInfo.mpProcess != 0) {
        do {
            _LZHMem_StageInfo.mpProcess();
        } while (_LZHMem_StageInfo.mpProcess != 0);
    }
    a->mUnknown08 = a->mUnknown04 - _LZHMem_InRemaining;
    b->mUnknown08 = b->mUnknown04 - _LZHMem_OutRemaining;
    bProcessing = 0;
    return 1;
}

int _LZHEncodeNewBlock(void)
{
    if (_LZH_InRemaining == 0 && _LZH_pInBlock->mUnknown18 != 0 && _LZH_WindowBufferSize == 0) {
        _LZHWriteBits(1, 1);
        _LZHWriteBits(32, _LZH_Checksum);
        _LZHFlushBitBuffer();
        _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
        _LZH_StageInfo.mpProcess = _LZHEncodeNewBlockEOF;
    } else {
        _LZHWriteBits(1, 0);
        _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
        _LZH_StageInfo.mpProcess = _LZHEncodeInput;
        _LZH_CodeBufferSize = 0;
    }
    return 0;
}

int _LZHEncodeNewBlockEOF(void)
{
    _LZHFlushByteBuffer();
    _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
    if (_LZH_ByteBufferBegin != _LZH_ByteBufferEnd) {
        return 2;
    }
    _LZH_pOutBlock->mUnknown18 = 1;
    _LZH_StageInfo.mpProcess = 0;
    return 0;
}

int _LZHEncodeInput(void)
{
    unsigned int best;
    unsigned short bestPos = 0;
    unsigned short pos;
    unsigned short head;
    unsigned short hash;
    unsigned short next;
    unsigned short search;
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char length;
    unsigned short scan;
    while (_LZH_CodeBufferSize <= 0x3FFF) {
        while (_LZH_WindowBufferSize <= 228) {
            if (_LZH_InRemaining == 0) {
                if (_LZH_pInBlock->mUnknown18 == 0) {
                    _LZHUpdateChecksum(&_LZH_Checksum, _LZH_pInBlock->mUnknown00, _LZH_pInBlock->mUnknown04);
                    _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04;
                    return 1;
                }
                break;
            }
            _LZH_pHashValue[_LZH_WindowEnd] = 16381;
            _LZH_InRemaining--;
            _LZH_pWindow[_LZH_WindowEnd++] = *_LZH_pInData++;
            _LZH_WindowBufferSize++;
            _LZH_WindowEnd &= 0x7FFF;
        }
        if (_LZH_WindowBufferSize == 0) {
            break;
        }
        pos = _LZH_WindowBuffer;
        a = _LZH_pWindow[pos];
        b = _LZH_pWindow[(pos + 1) & 0x7FFF];
        c = _LZH_pWindow[(pos + 2) & 0x7FFF];
        hash = ((a << 16) | (b << 8) | c) % 16381U;
        head = _LZH_pHashTable[hash];
        best = 0;
        search = 0;
        while (_LZH_pHashValue[head] == hash) {
            length = 0;
            scan = head;
            if (_LZH_pWindow[head] == _LZH_pWindow[pos & 0x7FFF] &&
                (pos & 0x7FFF) != _LZH_WindowEnd) {
                do {
                    length++;
                    scan = (scan + 1) & 0x7FFF;
                    next = (pos + length) & 0x7FFF;
                } while (_LZH_pWindow[scan] == _LZH_pWindow[next] && next != _LZH_WindowEnd);
            }
            if (length > best) {
                best = length;
                bestPos = head;
                if (best > 226) {
                    best = 227;
                    break;
                }
            }
            head = _LZH_pHashLink[head];
            search++;
            if (search > 15) {
                break;
            }
        }
        bestPos = (pos - bestPos) & 0x7FFF;
        if (best > 3 || (best == 3 && bestPos <= 4096)) {
            _LZH_pLLCodeBuffer[_LZH_CodeBufferSize] = best;
            _LZH_pPCodeBuffer[_LZH_CodeBufferSize++] = bestPos;
            next = pos;
            _LZH_WindowBuffer = (pos + best) & 0x7FFF;
            do {
                _LZH_pHashValue[next] = hash;
                _LZH_pHashLink[next] = _LZH_pHashTable[hash];
                _LZH_pHashTable[hash] = next;
                next = (next + 1) & 0x7FFF;
                if (next == _LZH_WindowBuffer) {
                    break;
                }
                a = b;
                b = c;
                c = _LZH_pWindow[(next + 2) & 0x7FFF];
                hash = ((a << 16) | (b << 8) | c) % 16381U;
            } while (1);
            _LZH_WindowBufferSize -= best;
        } else {
            _LZH_pHashValue[pos] = hash;
            _LZH_pHashLink[pos] = _LZH_pHashTable[hash];
            _LZH_pHashTable[hash] = pos;
            _LZH_WindowBuffer = pos + 1;
            _LZH_pLLCodeBuffer[_LZH_CodeBufferSize] = _LZH_pWindow[pos];
            _LZH_pPCodeBuffer[_LZH_CodeBufferSize++] = 0;
            _LZH_WindowBuffer &= 0x7FFF;
            _LZH_WindowBufferSize--;
        }
    }
    if (_LZH_InRemaining == 0 && _LZH_WindowBufferSize == 0 && _LZH_pInBlock->mUnknown18 != 0) {
        _LZHUpdateChecksum(&_LZH_Checksum, _LZH_pInBlock->mUnknown00, _LZH_pInBlock->mUnknown04);
    }
    _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04 - _LZH_InRemaining;
    _LZHEncodeCodeBufferStart();
    return 0;
}

void _LZHEncodeCodeBufferStart(void)
{
    LZHHuffCode_t *a = _LZH_LLCode.mpCodes;
    LZHHuffCode_t *b = _LZH_PCode.mpCodes;
    short i;
    unsigned short j;
    unsigned short n;
    unsigned short d;
    for (i = 0; i <= 284; i++) {
        a[i].mUnknown00 = 0;
    }
    a[256].mUnknown00 = 1;
    for (i = 0; i <= 29; i++) {
        b[i].mUnknown00 = 0;
    }
    for (j = 0; j < _LZH_CodeBufferSize; j++) {
        d = _LZH_pPCodeBuffer[j];
        n = _LZH_pLLCodeBuffer[j];
        if (d != 0) {
            a[_LZH_LLCodeConvert[n] + 257].mUnknown00++;
            d--;
            if (d <= 255) {
                d = _LZH_PCodeConvertLo[d];
            } else {
                d = _LZH_PCodeConvertHi[d >> 7];
            }
            b[d].mUnknown00++;
        } else {
            a[n].mUnknown00++;
        }
    }
    SysEnterCriticalSectionFunc(&_LZHHuff_CS);
    _LZHHuffEncodeBuildTree(&_LZH_LLCode);
    _LZHHuffEncodeGenCodeLen(&_LZH_LLCode);
    _LZHHuffAssignCodes(&_LZH_LLCode);
    _LZHHuffEncodeBuildTree(&_LZH_PCode);
    _LZHHuffEncodeGenCodeLen(&_LZH_PCode);
    _LZHHuffAssignCodes(&_LZH_PCode);
    SysExitCriticalSectionFunc(&_LZHHuff_CS);
    _LZHHuffWriteHuffData(&_LZH_LLCode);
    _LZHHuffWriteHuffData(&_LZH_PCode);
    _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
    _LZH_StageInfo.mpProcess = _LZHEncodeCodeBuffer;
    _LZH_StageInfo.mCodeIndex = 0;
}

static __inline void _LZHWriteCode(const LZHCodeSet_t *p, int sym)
{
    _LZHWriteBits(p->mpCodes[sym].mUnknown02, p->mpCodes[sym].mUnknown00);
}

int _LZHEncodeCodeBuffer(void)
{
    unsigned short d;
    unsigned char n;
    int code;
    _LZHFlushByteBuffer();
    while ((unsigned int)_LZH_StageInfo.mCodeIndex < _LZH_CodeBufferSize) {
        if (_LZH_OutRemaining == 0) {
            _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04;
            return 2;
        }
        n = _LZH_pLLCodeBuffer[_LZH_StageInfo.mCodeIndex];
        d = _LZH_pPCodeBuffer[_LZH_StageInfo.mCodeIndex++];
        if (d != 0) {
            code = _LZH_LLCodeConvert[n];
            _LZHWriteCode(&_LZH_LLCode, code + 257);
            if ((unsigned int)(code - 8) <= 18) {
                _LZHWriteBits(_LZH_LLCodeExtra[code], (short)(n - _LZH_LLCodeBase[code]));
            }
            if (d <= 256) {
                code = _LZH_PCodeConvertLo[d - 1];
            } else {
                code = _LZH_PCodeConvertHi[(d - 1) >> 7];
            }
            _LZHWriteCode(&_LZH_PCode, code);
            if (code > 3) {
                _LZHWriteBits(_LZH_PCodeExtra[code], (unsigned short)(d - _LZH_PCodeBase[code]));
            }
        } else {
            _LZHWriteCode(&_LZH_LLCode, n);
        }
    }
    _LZHWriteCode(&_LZH_LLCode, 256);
    _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
    _LZH_StageInfo.mpProcess = _LZHEncodeNewBlock;
    return 0;
}

/* Takes the next byte of the compressed input. */
static __inline unsigned char _LZHNextInByte(void)
{
    return *_LZH_pInData++;
}

int _LZHDecodeNewBlock(void)
{
    _LZH_ByteBufferNextEnd = (_LZH_ByteBufferEnd + 1) & 0xFF;
    while (_LZH_ByteBufferNextEnd != _LZH_ByteBufferBegin && _LZH_InRemaining != 0) {
        _LZH_ByteBuffer[_LZH_ByteBufferEnd] = _LZHNextInByte();
        _LZH_ByteBufferEnd = _LZH_ByteBufferNextEnd;
        _LZH_InRemaining--;
        _LZH_ByteBufferNextEnd = (_LZH_ByteBufferNextEnd + 1) & 0xFF;
    }
    if (_LZH_InRemaining == 0 && _LZH_pInBlock->mUnknown18 == 0) {
        _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04;
        return 1;
    }
    if ((unsigned char)_LZHReadBits(1) == 0) {
        SysEnterCriticalSectionFunc(&_LZHHuff_CS);
        _LZHHuffReadBitsFunc = _LZHReadBits;
        _LZHHuffReadHuffData(&_LZH_LLCode);
        _LZHHuffAssignCodes(&_LZH_LLCode);
        _LZHHuffDecodeBuildTree(&_LZH_LLCode);
        _LZHHuffDecodeBuildTable(&_LZH_LLCode);
        _LZHHuffReadHuffData(&_LZH_PCode);
        _LZHHuffAssignCodes(&_LZH_PCode);
        _LZHHuffDecodeBuildTree(&_LZH_PCode);
        _LZHHuffDecodeBuildTable(&_LZH_PCode);
        SysExitCriticalSectionFunc(&_LZHHuff_CS);
        _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04 - _LZH_InRemaining;
        if (_LZH_IsCompleteOutBuffer != 0) {
            _LZH_StageInfo.mpProcess = _LZHDecodeInputFull;
        } else {
            _LZH_StageInfo.mpProcess = _LZHDecodeInput;
        }
        return 0;
    }
    _LZHReadBits(32);
    _LZH_BitBufferSize = 0;
    _LZH_BitBuffer = 0;
    _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04 - _LZH_InRemaining;
    _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
    _LZH_pOutBlock->mUnknown18 = 1;
    _LZH_StageInfo.mpProcess = 0;
    return 0;
}

unsigned int _LZHReadBits(short n);
int _LZHMemDecodeInput(void);
unsigned int _LZHMemReadBits(short n);
void _LZHHuffReadHuffData(const LZHCodeSet_t *pDesc);
void _LZHHuffAssignCodes(const LZHCodeSet_t *pDesc);
void _LZHHuffDecodeBuildTree(const LZHCodeSet_t *pDesc);
void _LZHHuffDecodeBuildTable(const LZHCodeSet_t *pDesc);
void _LZHHuffDecodeBuildTableR(short node, LZHDecodeEntry_t *pLeaf);
void _LZHHeapPush(short symbol, unsigned short weight);
LZHHeapNode_t _LZHHeapPop();

int _LZHDecodeInput(void)
{
    LZHDecodeEntry_t *pTable;
    int index;
    short code;
    short symbol;
    short length;
    unsigned short distance;

    while (_LZH_WindowBuffer != _LZH_WindowEnd)
    {
        _LZH_OutRemaining--;
        *_LZH_pOutData++ = _LZH_pWindow[_LZH_WindowBuffer++];
        _LZH_WindowBuffer &= 0x7FFF;
    }
    for (;;)
    {
        _LZH_ByteBufferNextEnd = (_LZH_ByteBufferEnd + 1) & 0xFF;
        while (_LZH_ByteBufferNextEnd != _LZH_ByteBufferBegin && _LZH_InRemaining != 0)
        {
            _LZH_ByteBuffer[_LZH_ByteBufferEnd] = _LZHNextInByte();
            _LZH_ByteBufferEnd = _LZH_ByteBufferNextEnd++;
            _LZH_InRemaining--;
            _LZH_ByteBufferNextEnd &= 0xFF;
        }
        if (_LZH_InRemaining == 0 && _LZH_pInBlock->mUnknown18 == 0)
        {
            _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04;
            _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
            return 1;
        }
        pTable = _LZH_LLCode_DecodeTable;
        index = 0;
        do
        {
            index = pTable[index].mUnknown00 + _LZHReadBits(pTable[index].mUnknown02);
        } while (pTable[index].mUnknown02 != 0);
        code = pTable[index].mUnknown00;
        if (code <= 255)
        {
            _LZH_pWindow[_LZH_WindowEnd++] = code;
            _LZH_WindowEnd &= 0x7FFF;
        }
        else
        {
            if (code <= 256)
                break;
            code -= 257;
            if (code <= 7)
            {
                length = code + 3;
            }
            else if (_LZH_LLCodeExtra[code] != 0)
            {
                length = _LZH_LLCodeBase[code];
                length += _LZHReadBits(_LZH_LLCodeExtra[code]);
            }
            else
            {
                length = 227;
            }
            pTable = _LZH_PCode_DecodeTable;
            index = 0;
            do
            {
                index = pTable[index].mUnknown00 + _LZHReadBits(pTable[index].mUnknown02);
            } while (pTable[index].mUnknown02 != 0);
            symbol = pTable[index].mUnknown00;
            if (symbol <= 3)
            {
                distance = symbol + 1;
            }
            else
            {
                unsigned char bits = _LZH_PCodeExtra[symbol];
                distance = _LZH_PCodeBase[symbol];
                distance += _LZHReadBits(bits);
            }
            distance = (_LZH_WindowBuffer - (distance + 0x8000)) & 0x7FFF;
            do
            {
                _LZH_pWindow[_LZH_WindowEnd++] = _LZH_pWindow[distance++];
                distance &= 0x7FFF;
                _LZH_WindowEnd &= 0x7FFF;
            } while (--length > 0);
        }
        do
        {
            if (_LZH_OutRemaining == 0)
            {
                _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04 - _LZH_InRemaining;
                _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04;
                return 2;
            }
            _LZH_OutRemaining--;
            *_LZH_pOutData++ = _LZH_pWindow[_LZH_WindowBuffer++];
            _LZH_WindowBuffer &= 0x7FFF;
        } while (_LZH_WindowBuffer != _LZH_WindowEnd);
    }
    _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04 - _LZH_InRemaining;
    _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - _LZH_OutRemaining;
    _LZH_StageInfo.mpProcess = _LZHDecodeNewBlock;
    return 0;
}

#define RING_FILL()                                                \
    while (((wr + 1) & 0xFF) != rd && avail > 0)                   \
    {                                                              \
        avail--;                                                   \
        _LZH_ByteBuffer[wr++] = *pIn++;                               \
        wr &= 0xFF;                                                \
    }

#define RING_GETBITS(value, n)                                     \
    if ((n) < bitCount)                                            \
    {                                                              \
        value = bitBuf >> (bitCount - (n));                        \
        bitCount -= (n);                                           \
        bitBuf &= (1 << bitCount) - 1;                             \
    }                                                              \
    else                                                           \
    {                                                              \
        (n) -= bitCount;                                           \
        value = bitBuf;                                            \
        if (rd != wr)                                              \
        {                                                          \
            bitBuf = _LZH_ByteBuffer[rd++];                       \
            rd &= 0xFF;                                        \
            if (rd != wr)                                          \
            {                                                      \
                bitBuf = (bitBuf << 8) | _LZH_ByteBuffer[rd++];   \
                rd &= 0xFF;                                    \
                if (rd != wr)                                      \
                {                                                  \
                    bitBuf = (bitBuf << 8) | _LZH_ByteBuffer[rd++];\
                    rd &= 0xFF;                                \
                    if (rd != wr)                                  \
                    {                                              \
                        bitBuf = (bitBuf << 8) | _LZH_ByteBuffer[rd++];\
                        rd &= 0xFF;                            \
                        bitCount = 32;                             \
                    }                                              \
                    else                                           \
                        bitCount = 24;                             \
                }                                                  \
                else                                               \
                    bitCount = 16;                                 \
            }                                                      \
            else                                                   \
                bitCount = 8;                                      \
        }                                                          \
        else                                                       \
            bitCount = 0;                                          \
        RING_FILL();                                               \
        if ((n) > 0)                                               \
        {                                                          \
            value = (value << (n)) | (bitBuf >> (bitCount - (n))); \
            bitCount -= (n);                                       \
            bitBuf &= (1 << bitCount) - 1;                         \
        }                                                          \
    }

int _LZHDecodeInputFull(void)
{
    short wr = _LZH_ByteBufferEnd;
    short rd = _LZH_ByteBufferBegin;
    unsigned char flag = _LZH_pInBlock->mUnknown18;
    short bitCount = _LZH_BitBufferSize;
    unsigned int bitBuf = _LZH_BitBuffer;
    int avail = _LZH_InRemaining;
    unsigned char *pIn = _LZH_pInData;
    int remaining = _LZH_OutRemaining;
    unsigned char *pOut = _LZH_pOutData;
    short n;
    short bits;
    short code;
    short length;
    unsigned short distance;
    unsigned char *pSrc;
    unsigned char *pEnd;

    RING_FILL();
    for (;;)
    {
        if (avail == 0 && flag == 0)
        {
            _LZH_ByteBufferEnd = wr;
            _LZH_ByteBufferBegin = rd;
            _LZH_BitBufferSize = bitCount;
            _LZH_BitBuffer = bitBuf;
            _LZH_InRemaining = avail;
            _LZH_pInData = pIn;
            _LZH_pOutData = pOut;
            _LZH_OutRemaining = remaining;
            _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04;
            _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - remaining;
            return 1;
        }
        length = 0;
        do
        {
            n = _LZH_LLCode_DecodeTable[length].mUnknown02;
            RING_GETBITS(bits, n);
            length = _LZH_LLCode_DecodeTable[length].mUnknown00 + bits;
        } while (_LZH_LLCode_DecodeTable[length].mUnknown02 != 0);
        code = _LZH_LLCode_DecodeTable[length].mUnknown00;
        if (code <= 255)
        {
            *pOut++ = code;
            remaining--;
            continue;
        }
        if (code <= 256)
            break;
        code -= 257;
        if (code <= 7)
        {
            length = code + 3;
        }
        else
        {
            n = _LZH_LLCodeExtra[code];
            if (n > 0)
            {
                RING_GETBITS(length, n);
                length += _LZH_LLCodeBase[code];
            }
            else
            {
                length = 227;
            }
        }
        distance = 0;
        do
        {
            n = _LZH_PCode_DecodeTable[distance].mUnknown02;
            RING_GETBITS(bits, n);
            distance = _LZH_PCode_DecodeTable[distance].mUnknown00 + bits;
        } while (_LZH_PCode_DecodeTable[distance].mUnknown02 != 0);
        code = _LZH_PCode_DecodeTable[distance].mUnknown00;
        if (code <= 3)
        {
            distance = code + 1;
        }
        else
        {
            n = _LZH_PCodeExtra[code];
            RING_GETBITS(distance, n);
            distance += _LZH_PCodeBase[code];
        }
        remaining -= length;
        pSrc = pOut - distance;
        pEnd = pSrc + length;
        do
        {
            *pOut++ = *pSrc++;
        } while (pSrc < pEnd);
    }
    _LZH_ByteBufferEnd = wr;
    _LZH_ByteBufferBegin = rd;
    _LZH_BitBufferSize = bitCount;
    _LZH_BitBuffer = bitBuf;
    _LZH_pInData = pIn;
    _LZH_pOutData = pOut;
    _LZH_InRemaining = avail;
    _LZH_OutRemaining = remaining;
    _LZH_pInBlock->mUnknown08 = _LZH_pInBlock->mUnknown04 - avail;
    _LZH_pOutBlock->mUnknown08 = _LZH_pOutBlock->mUnknown04 - remaining;
    _LZH_StageInfo.mpProcess = _LZHDecodeNewBlock;
    return 0;
}

unsigned int _LZHReadBits(short n)
{
    unsigned int result;

    if (n < _LZH_BitBufferSize)
    {
        result = _LZH_BitBuffer >> (_LZH_BitBufferSize - n);
        _LZH_BitBufferSize -= n;
        _LZH_BitBuffer &= (1 << _LZH_BitBufferSize) - 1;
    }
    else
    {
        n -= _LZH_BitBufferSize;
        result = _LZH_BitBuffer;
        if (_LZH_ByteBufferBegin != _LZH_ByteBufferEnd)
        {
            _LZH_BitBuffer = _LZH_ByteBuffer[_LZH_ByteBufferBegin++];
            _LZH_ByteBufferBegin &= 0xFF;
            if (_LZH_ByteBufferBegin != _LZH_ByteBufferEnd)
            {
                _LZH_BitBuffer = (_LZH_BitBuffer << 8) | _LZH_ByteBuffer[_LZH_ByteBufferBegin++];
                _LZH_ByteBufferBegin &= 0xFF;
                if (_LZH_ByteBufferBegin != _LZH_ByteBufferEnd)
                {
                    _LZH_BitBuffer = (_LZH_BitBuffer << 8) | _LZH_ByteBuffer[_LZH_ByteBufferBegin++];
                    _LZH_ByteBufferBegin &= 0xFF;
                    if (_LZH_ByteBufferBegin != _LZH_ByteBufferEnd)
                    {
                        _LZH_BitBuffer = (_LZH_BitBuffer << 8) | _LZH_ByteBuffer[_LZH_ByteBufferBegin++];
                        _LZH_ByteBufferBegin &= 0xFF;
                        _LZH_BitBufferSize = 32;
                    }
                    else
                        _LZH_BitBufferSize = 24;
                }
                else
                    _LZH_BitBufferSize = 16;
            }
            else
                _LZH_BitBufferSize = 8;
        }
        else
            _LZH_BitBufferSize = 0;
        _LZH_ByteBufferNextEnd = (_LZH_ByteBufferEnd + 1) & 0xFF;
        while (_LZH_ByteBufferNextEnd != _LZH_ByteBufferBegin && _LZH_InRemaining != 0)
        {
            _LZH_ByteBuffer[_LZH_ByteBufferEnd] = _LZHNextInByte();
            _LZH_ByteBufferEnd = _LZH_ByteBufferNextEnd++;
            _LZH_InRemaining--;
            _LZH_ByteBufferNextEnd &= 0xFF;
        }
        if (n > 0)
        {
            result = (result << n) | (_LZH_BitBuffer >> (_LZH_BitBufferSize - n));
            _LZH_BitBufferSize -= n;
            _LZH_BitBuffer &= (1 << _LZH_BitBufferSize) - 1;
        }
    }
    return result;
}

int _LZHMemDecodeNewBlock(void)
{
    if (!(unsigned char)_LZHMemReadBits(1))
    {
        SysEnterCriticalSectionFunc(&_LZHHuff_CS);
        _LZHHuffReadBitsFunc = _LZHMemReadBits;
        _LZHHuffReadHuffData(&_LZHMem_LLCode);
        _LZHHuffAssignCodes(&_LZHMem_LLCode);
        _LZHHuffDecodeBuildTree(&_LZHMem_LLCode);
        _LZHHuffDecodeBuildTable(&_LZHMem_LLCode);
        _LZHHuffReadHuffData(&_LZHMem_PCode);
        _LZHHuffAssignCodes(&_LZHMem_PCode);
        _LZHHuffDecodeBuildTree(&_LZHMem_PCode);
        _LZHHuffDecodeBuildTable(&_LZHMem_PCode);
        SysExitCriticalSectionFunc(&_LZHHuff_CS);
        _LZHMem_StageInfo.mpProcess = _LZHMemDecodeInput;
        return 0;
    }
    _LZHMem_Checksum = _LZHMemReadBits(32);
    _LZHMem_BitBufferSize = 0;
    _LZHMem_BitBuffer = 0;
    _LZHMem_StageInfo.mpProcess = 0;
    return 0;
}

#define GETBITS(value, width)                                        \
    {                                                              \
        short count = (width);                                      \
    if (count < bitCount)                                            \
    {                                                              \
        value = bitBuf >> (bitCount - count);                        \
        bitCount -= count;                                           \
        bitBuf &= (1 << bitCount) - 1;                             \
    }                                                              \
    else                                                           \
    {                                                              \
        count -= bitCount;                                           \
        value = bitBuf;                                            \
        if (avail > 3)                                             \
        {                                                          \
            avail -= 4;                                            \
            bitCount = 32;                                         \
            bitBuf = *pIn++;                                       \
            bitBuf = (bitBuf << 8) | *pIn++;                       \
            bitBuf = (bitBuf << 8) | *pIn++;                       \
            bitBuf = (bitBuf << 8) | *pIn++;                       \
        }                                                          \
        else if (avail > 2)                                        \
        {                                                          \
            avail -= 3;                                            \
            bitCount = 24;                                         \
            bitBuf = *pIn++;                                       \
            bitBuf = (bitBuf << 8) | *pIn++;                       \
            bitBuf = (bitBuf << 8) | *pIn++;                       \
        }                                                          \
        else if (avail > 1)                                        \
        {                                                          \
            avail -= 2;                                            \
            bitCount = 16;                                         \
            bitBuf = *pIn++;                                       \
            bitBuf = (bitBuf << 8) | *pIn++;                       \
        }                                                          \
        else if (avail > 0)                                        \
        {                                                          \
            avail -= 1;                                            \
            bitCount = 8;                                          \
            bitBuf = *pIn++;                                       \
        }                                                          \
        else                                                       \
        {                                                          \
            bitCount = 0;                                          \
            bitBuf = 0;                                            \
        }                                                          \
        if (count > 0)                                               \
        {                                                          \
            value = (value << count) | (bitBuf >> (bitCount - count)); \
            bitCount -= count;                                       \
            bitBuf &= (1 << bitCount) - 1;                         \
        }                                                          \
    } \
    }

int _LZHMemDecodeInput(void)
{
    short bitCount = _LZHMem_BitBufferSize;
    unsigned int bitBuf = _LZHMem_BitBuffer;
    int avail = _LZHMem_InRemaining;
    unsigned char *pIn = _LZHMem_pInData;
    int remaining = _LZHMem_OutRemaining;
    unsigned char *pOut = _LZHMem_pOutData;

    for (;;)
    {
        short index = 0;
        short code;
        short bits;
        short length;
        unsigned short ubits;
        unsigned short distance;
        unsigned char *pSrc;
        unsigned char *pEnd;

        do
        {
            GETBITS(bits, _LZHMem_LLCode_DecodeTable[index].mUnknown02);
            index = _LZHMem_LLCode_DecodeTable[index].mUnknown00 + bits;
        } while (_LZHMem_LLCode_DecodeTable[index].mUnknown02 != 0);
        code = _LZHMem_LLCode_DecodeTable[index].mUnknown00;
        if (code <= 255)
        {
            *pOut++ = code;
            remaining--;
            continue;
        }
        if (code <= 256)
            break;
        code -= 257;
        if (code <= 7)
        {
            length = code + 3;
        }
        else
        {
            index = _LZH_LLCodeExtra[code];
            if (index > 0)
            {
                GETBITS(length, index);
                length += _LZH_LLCodeBase[code];
            }
            else
            {
                length = 227;
            }
        }
        index = 0;
        do
        {
            GETBITS(ubits, _LZHMem_PCode_DecodeTable[index].mUnknown02);
            index = _LZHMem_PCode_DecodeTable[index].mUnknown00 + ubits;
        } while (_LZHMem_PCode_DecodeTable[index].mUnknown02 != 0);
        code = _LZHMem_PCode_DecodeTable[index].mUnknown00;
        if (code <= 3)
        {
            distance = code + 1;
        }
        else
        {
            index = _LZH_PCodeExtra[code];
            GETBITS(distance, index);
            distance += _LZH_PCodeBase[code];
        }
        remaining -= length;
        pSrc = pOut - distance;
        pEnd = pSrc + length;
        do
        {
            *pOut++ = *pSrc++;
        } while (pSrc < pEnd);
    }
    _LZHMem_BitBufferSize = bitCount;
    _LZHMem_BitBuffer = bitBuf;
    _LZHMem_InRemaining = avail;
    _LZHMem_pInData = pIn;
    _LZHMem_OutRemaining = remaining;
    _LZHMem_pOutData = pOut;
    _LZHMem_StageInfo.mpProcess = _LZHMemDecodeNewBlock;
    return 0;
}

unsigned int _LZHMemReadBits(short n)
{
    unsigned int result;

    if (n < _LZHMem_BitBufferSize)
    {
        result = _LZHMem_BitBuffer >> (_LZHMem_BitBufferSize - n);
        _LZHMem_BitBufferSize -= n;
        _LZHMem_BitBuffer &= (1 << _LZHMem_BitBufferSize) - 1;
    }
    else
    {
        n -= _LZHMem_BitBufferSize;
        result = _LZHMem_BitBuffer;
        if (_LZHMem_InRemaining > 3)
        {
            _LZHMem_BitBufferSize = 32;
            _LZHMem_InRemaining -= 4;
            _LZHMem_BitBuffer = *_LZHMem_pInData++;
            _LZHMem_BitBuffer = (_LZHMem_BitBuffer << 8) | *_LZHMem_pInData++;
            _LZHMem_BitBuffer = (_LZHMem_BitBuffer << 8) | *_LZHMem_pInData++;
            _LZHMem_BitBuffer = (_LZHMem_BitBuffer << 8) | *_LZHMem_pInData++;
        }
        else if (_LZHMem_InRemaining > 2)
        {
            _LZHMem_BitBufferSize = 24;
            _LZHMem_InRemaining -= 3;
            _LZHMem_BitBuffer = *_LZHMem_pInData++;
            _LZHMem_BitBuffer = (_LZHMem_BitBuffer << 8) | *_LZHMem_pInData++;
            _LZHMem_BitBuffer = (_LZHMem_BitBuffer << 8) | *_LZHMem_pInData++;
        }
        else if (_LZHMem_InRemaining > 1)
        {
            _LZHMem_BitBufferSize = 16;
            _LZHMem_InRemaining -= 2;
            _LZHMem_BitBuffer = *_LZHMem_pInData++;
            _LZHMem_BitBuffer = (_LZHMem_BitBuffer << 8) | *_LZHMem_pInData++;
        }
        else if (_LZHMem_InRemaining > 0)
        {
            _LZHMem_BitBufferSize = 8;
            _LZHMem_InRemaining -= 1;
            _LZHMem_BitBuffer = *_LZHMem_pInData++;
        }
        else
        {
            _LZHMem_BitBufferSize = 0;
            _LZHMem_BitBuffer = 0;
        }
        if (n > 0)
        {
            result = (result << n) | (_LZHMem_BitBuffer >> (_LZHMem_BitBufferSize - n));
            _LZHMem_BitBufferSize -= n;
            _LZHMem_BitBuffer &= (1 << _LZHMem_BitBufferSize) - 1;
        }
    }
    return result;
}

void _LZHHuffWriteHuffData(const LZHCodeSet_t *p)
{
    LZHHuffCode_t *pElems = p->mpCodes;
    short count = p->mCount;
    short i;

    for (i = 0; i < count; i++)
        _LZHWriteBits(4, pElems[i].mUnknown02);
}

void _LZHHuffEncodeBuildTree(const LZHCodeSet_t *p)
{
    LZHHuffCode_t *pElems = p->mpCodes;
    short count = p->mCount;
    unsigned short used;
    short i;
    short next;
    unsigned short weight;
    LZHHeapNode_t node;

    _LZH_Heap[0].mUnknown02 = 0;
    _LZH_Heap[0].mUnknown00 = 0;
    _LZH_HeapSize = 0;
    used = 0;
    for (i = 0; i < count; i++)
    {
        if (pElems[i].mUnknown00 != 0)
        {
            used++;
            _LZHHeapPush(i + count, pElems[i].mUnknown00);
        }
    }
    while (used <= 1)
    {
        for (i = 0; pElems[i].mUnknown00 != 0; i++)
            ;
        pElems[i].mUnknown00 = 1;
        used++;
        _LZHHeapPush(i + count, 1);
    }
    next = count - 1;
    while (_LZH_HeapSize > 1)
    {
        node = _LZHHeapPop();
        _LZH_pEncodeTree[node.mUnknown00] = next;
        weight = node.mUnknown02;
        node = _LZHHeapPop();
        _LZH_pEncodeTree[node.mUnknown00] = next;
        weight += node.mUnknown02;
        _LZHHeapPush(next, weight);
        next--;
    }
    node = _LZHHeapPop();
    _LZH_pEncodeTree[node.mUnknown00] = 0;
}

void _LZHHuffEncodeGenCodeLen(const LZHCodeSet_t *p)
{
    short count = p->mCount;
    LZHHuffCode_t *pElems = p->mpCodes;
    short i;
    short j;
    short length;
    short overflow;
    LZHHeapNode_t node;

    for (i = 0; i <= 15; i++)
        _LZH_CodeLenCount[i] = 0;
    overflow = 0;
    for (i = 0; i < count; i++)
    {
        if (pElems[i].mUnknown00 != 0)
        {
            length = 0;
            for (j = _LZH_pEncodeTree[i + count]; j > 0; j = _LZH_pEncodeTree[j])
                length++;
            if (length > 15)
            {
                length = 15;
                overflow++;
            }
            pElems[i].mUnknown02 = length;
            _LZH_CodeLenCount[length]++;
        }
        else
        {
            pElems[i].mUnknown02 = 0;
        }
    }
    if (overflow > 0)
    {
        length = 14;
        do
        {
            while (_LZH_CodeLenCount[length] == 0)
                length--;
            _LZH_CodeLenCount[length]--;
            _LZH_CodeLenCount[length + 1] += 2;
            _LZH_CodeLenCount[15]--;
            overflow -= 2;
        } while (overflow > 0);
        _LZH_Heap[0].mUnknown02 = 0;
        _LZH_Heap[0].mUnknown00 = 0;
        _LZH_HeapSize = 0;
        for (i = 0; i < count; i++)
        {
            if (pElems[i].mUnknown00 != 0)
                _LZHHeapPush(i, pElems[i].mUnknown00);
        }
        for (length = 15; length > 0; length--)
        {
            for (count = _LZH_CodeLenCount[length]; count > 0; count--)
            {
                node = _LZHHeapPop();
                pElems[node.mUnknown00].mUnknown02 = length;
            }
        }
    }
}

void _LZHHuffReadHuffData(const LZHCodeSet_t *pDesc)
{
    LZHHuffCode_t *pCodes = pDesc->mpCodes;
    short count = pDesc->mCount;
    short i;
    short length;

    for (length = 1; length <= 15; length++)
        _LZH_CodeLenCount[length] = 0;
    for (i = 0; i < count; i++)
    {
        length = _LZHHuffReadBitsFunc(4);

        pCodes[i].mUnknown02 = length;
        _LZH_CodeLenCount[length]++;
    }
    _LZH_CodeLenCount[0] = 0;
}

void _LZHHuffAssignCodes(const LZHCodeSet_t *pDesc)
{
    unsigned short next[16];
    LZHHuffCode_t *pCodes = pDesc->mpCodes;
    short count = pDesc->mCount;
    unsigned short n = 0;
    short bits;

    for (bits = 1; bits <= 15; bits++)
    {
        n = (n + _LZH_CodeLenCount[bits - 1]) << 1;
        next[bits] = n;
    }
    for (n = 0; n < count; n++)
    {
        short length = pCodes[n].mUnknown02;

        if (length > 0)
            pCodes[n].mUnknown00 = next[length]++;
    }
}

void _LZHHuffDecodeBuildTree(const LZHCodeSet_t *pDesc)
{
    LZHHuffCode_t *pCodes = pDesc->mpCodes;
    short count = pDesc->mCount;
    short i;
    short next = 1;

    _LZH_DecodeTree[0][0] = count;
    _LZH_DecodeTree[0][1] = count;
    for (i = 0; i < count; i++)
    {
        short length = pCodes[i].mUnknown02;

        if (length > 0)
        {
            unsigned short code = pCodes[i].mUnknown00;
            short node = 0;
            int bit;

            length--;
            bit = (code >> length) & 1;
            while (length != 0)
            {
                short child = _LZH_DecodeTree[node][bit];

                if (child != count)
                {
                    node = child;
                }
                else
                {
                    child = next++;
                    _LZH_DecodeTree[child][1] = count;
                    _LZH_DecodeTree[child][0] = count;
                    _LZH_DecodeTree[node][bit] = child;
                    node = child;
                }
                length--;
                bit = (code >> length) & 1;
            }
            _LZH_DecodeTree[node][bit] = -i;
        }
    }
}

void _LZHHuffDecodeBuildTable(const LZHCodeSet_t *pDesc)
{
    _LZH_HeapSize = 0;
    _LZH_NextFreeTable = 1;
    _LZH_pDecodeTable = pDesc->mpLeaves;
    _LZHHuffDecodeBuildTableR(0, pDesc->mpLeaves);
}

void _LZHHuffDecodeBuildTableR(short node, LZHDecodeEntry_t *pLeaf)
{
    short depth;
    short value;
    short size;
    short count;
    short index;
    short top;

    _LZH_HeapSize++;
    _LZH_Heap[_LZH_HeapSize].mUnknown00 = node;
    _LZH_Heap[_LZH_HeapSize].mUnknown02 = 0;
    value = _LZH_DecodeTree[node][0];
    depth = 1;
    while (value > 0)
    {
        _LZH_HeapSize++;
        _LZH_Heap[_LZH_HeapSize].mUnknown00 = value;
        _LZH_Heap[_LZH_HeapSize].mUnknown02 = 0;
        value = _LZH_DecodeTree[value][0];
        depth++;
    }
    pLeaf->mUnknown02 = depth;
    size = 1 << depth;
    pLeaf->mUnknown00 = _LZH_NextFreeTable;
    index = _LZH_NextFreeTable;
    _LZH_NextFreeTable += size;
    _LZH_pDecodeTable[index].mUnknown02 = 0;
    _LZH_pDecodeTable[index].mUnknown00 = -value;
    depth = 0;
    index++;
    for (count = size - 1; count > 0; count--)
    {
        do
        {
            top = _LZH_HeapSize--;
            depth++;
        } while (++_LZH_Heap[top].mUnknown02 > 1);
        depth--;
        _LZH_HeapSize = top;
        value = _LZH_DecodeTree[_LZH_Heap[top].mUnknown00][1];
        while (depth > 0)
        {
            _LZH_HeapSize++;
            _LZH_Heap[_LZH_HeapSize].mUnknown00 = value;
            _LZH_Heap[_LZH_HeapSize].mUnknown02 = 0;
            value = _LZH_DecodeTree[value][0];
            depth--;
        }
        if (value <= 0)
        {
            _LZH_pDecodeTable[index].mUnknown02 = 0;
            _LZH_pDecodeTable[index].mUnknown00 = -value;
        }
        else
        {
            _LZHHuffDecodeBuildTableR(value, &_LZH_pDecodeTable[index]);
        }
        index++;
    }
    _LZH_HeapSize -= pLeaf->mUnknown02;
}

void _LZHHuffGenCodeConvertTables(void)
{
    unsigned short length = 1;
    unsigned char code;

    for (code = 0; length <= 256; code++)
    {
        for (; length < _LZH_PCodeBase[code + 1]; length++)
            _LZH_PCodeConvertLo[length - 1] = code;
    }
    for (; code <= 29; code++)
    {
        for (; length < _LZH_PCodeBase[code + 1]; length++)
            _LZH_PCodeConvertHi[(length - 1) >> 7] = code;
    }
    length = 0;
    for (code = 0; code <= 27; code++)
    {
        while (length < _LZH_LLCodeBase[code + 1])
            _LZH_LLCodeConvert[length++] = code;
    }
}

void _LZHUpdateChecksum(unsigned int *pSum, unsigned char *pData, unsigned int length)
{
    unsigned int s1 = *pSum & 0xFFFF;
    unsigned int s2 = *pSum >> 16;
    unsigned short n;

    while (length != 0)
    {
        if (length > 5552) n = 5552; else n = length;
        length -= n;
        do
        {
            s1 += *pData++;
            s2 += s1;
        } while (--n != 0);
        s1 %= 65521;
        s2 %= 65521;
    }
    *pSum = (s2 << 16) | s1;
}

void _LZHWriteBits(short count, unsigned int value)
{
    unsigned char shift;

    do
    {
        if (count + _LZH_BitBufferSize <= 7)
        {
            _LZH_BitBufferSize += count;
            _LZH_BitBuffer = (unsigned char)((_LZH_BitBuffer << count) | value);
            break;
        }
        shift = 8 - _LZH_BitBufferSize;
        _LZH_BitBuffer = (unsigned char)((_LZH_BitBuffer << shift) | (value >> (count - shift)));
        count -= shift;
        _LZH_ByteBuffer[_LZH_ByteBufferEnd++] = (unsigned char)_LZH_BitBuffer;
        _LZH_ByteBufferEnd &= 0xFF;
        _LZH_BitBufferSize = 0;
    } while (count > 0);
    _LZHFlushByteBuffer();
}

void _LZHFlushByteBuffer(void)
{
    while (_LZH_ByteBufferBegin != _LZH_ByteBufferEnd && _LZH_OutRemaining != 0)
    {
        _LZH_OutRemaining--;
        *_LZH_pOutData++ = _LZH_ByteBuffer[_LZH_ByteBufferBegin++];
        _LZH_ByteBufferBegin &= 0xFF;
    }
}

void _LZHFlushBitBuffer(void)
{
    if (_LZH_BitBufferSize <= 7)
    {
        if (_LZH_BitBufferSize > 0)
        {
            _LZH_BitBuffer <<= 8 - _LZH_BitBufferSize;
            _LZH_BitBufferSize = 8;
        }
    }
    if (_LZH_BitBufferSize == 8)
    {
        _LZH_ByteBuffer[_LZH_ByteBufferEnd++] = (unsigned char)_LZH_BitBuffer;
        _LZH_ByteBufferEnd &= 0xFF;
        _LZH_BitBufferSize = 0;
        _LZHFlushByteBuffer();
    }
}

void _LZHHeapPush(short symbol, unsigned short weight)
{
    short i = ++_LZH_HeapSize;

    while (_LZH_Heap[i / 2].mUnknown02 > weight)
    {
        _LZH_Heap[i] = _LZH_Heap[i / 2];
        i /= 2;
    }
    _LZH_Heap[i].mUnknown00 = symbol;
    _LZH_Heap[i].mUnknown02 = weight;
}

LZHHeapNode_t _LZHHeapPop(void)
{
    LZHHeapNode_t top = _LZH_Heap[1];
    unsigned short weight = _LZH_Heap[_LZH_HeapSize].mUnknown02;
    short count = --_LZH_HeapSize;
    short i = 1;
    short child;

    while (i <= count / 2)
    {
        child = i << 1;
        if (child < count && _LZH_Heap[child].mUnknown02 > _LZH_Heap[child + 1].mUnknown02)
            child++;
        if (_LZH_Heap[child].mUnknown02 >= weight)
            break;
        _LZH_Heap[i] = _LZH_Heap[child];
        i = child;
    }
    _LZH_Heap[i] = _LZH_Heap[_LZH_HeapSize + 1];
    return top;
}
