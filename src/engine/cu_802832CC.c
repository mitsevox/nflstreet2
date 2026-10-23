/* Partial source for the range 0x802832CC-0x80285A90 (neutral file name). */

#include <dolphin/os.h>
#include <dolphin/gba.h>
#include <engine/fn_801F8014.h>

extern int fn_801C96E4(const char *pName, int device);
extern int fn_801C97F0(int handle);
extern int fn_801C9844(int handle, int offset, unsigned int whence);
extern int fn_801C9960(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int fn_801CA648(int handle, int pos, void *pBuffer, int size);
void *fn_801C1F94();

typedef struct Code_802C2860
{
    unsigned short mUnknown00;
    short mUnknown02;
} Code_802C2860;

typedef struct Leaf_802C2860
{
    short mUnknown00;
    unsigned char mUnknown02;
} Leaf_802C2860;

typedef struct Desc_802C2860
{
    Code_802C2860 *mpCodes;
    Leaf_802C2860 *mpLeaves;
    short mCount;
} Desc_802C2860;

typedef struct Node_803B795C
{
    short mUnknown00;
    unsigned short mUnknown02;
} Node_803B795C;

typedef struct Struct_803ED474
{
    char mUnknown00[4];
    int mUnknown04;
    int mUnknown08;
    char mUnknown0C[12];
    unsigned char mUnknown18;
} Struct_803ED474;

typedef struct Struct_803E990C
{
    OSTick mUnknown00;
    char mUnknown04[4];
    int mUnknown08;
    char mUnknown0C[0x260 - 0xC];
} Struct_803E990C;

typedef struct File_80285808
{
    int mHandle;
    int mPosition;
    const void *mUnknown08;
} File_80285808;

typedef struct Struct_80285A24
{
    char mUnknown00[4];
    unsigned int mUnknown04;
    void *mUnknown08;
    char mUnknown0C[4];
    void *(*mUnknown10)(void *);
    char *mUnknown14;
} Struct_80285A24;

extern Desc_802C2860 lbl_802C2860;
extern Desc_802C2860 lbl_802C286C;
extern unsigned char lbl_802C2878[];
extern short lbl_802C2894[];
extern unsigned char lbl_802C28D0[];
extern unsigned short lbl_802C28EE[];
extern Lock_801F8014 lbl_803B543C;
extern Leaf_802C2860 lbl_803B545C[];
extern Leaf_802C2860 lbl_803B61B8[];
extern Leaf_802C2860 lbl_803B6320[];
extern Leaf_802C2860 lbl_803B707C[];
extern short lbl_803B71E4[];
extern short lbl_803B7204[][2];
extern unsigned char lbl_803B7678[];
extern unsigned char lbl_803B775C[];
extern unsigned char lbl_803B785C[];
extern Node_803B795C lbl_803B795C[];
extern unsigned char lbl_803B7DD4[];
extern OSThread lbl_803BA580;
extern Struct_803E990C lbl_803E990C[];
extern int lbl_803EC590;
extern int (*lbl_803ED428)(void);
extern int (*lbl_803ED434)(void);
extern unsigned short lbl_803ED43C;
extern unsigned short lbl_803ED43E;
extern unsigned char *lbl_803ED440;
extern unsigned int (*lbl_803ED460)(short n);
extern short *lbl_803ED464;
extern short lbl_803ED468;
extern Leaf_802C2860 *lbl_803ED46C;
extern short lbl_803ED470;
extern Struct_803ED474 *lbl_803ED474;
extern Struct_803ED474 *lbl_803ED478;
extern short lbl_803ED47C;
extern short lbl_803ED47E;
extern unsigned int lbl_803ED480;
extern short lbl_803ED484;
extern short lbl_803ED486;
extern int lbl_803ED488;
extern unsigned char *lbl_803ED48C;
extern int lbl_803ED490;
extern unsigned char *lbl_803ED494;
extern short lbl_803ED49C;
extern unsigned int lbl_803ED4A0;
extern int lbl_803ED4A4;
extern unsigned char *lbl_803ED4A8;
extern int lbl_803ED4AC;
extern unsigned char *lbl_803ED4B0;
extern unsigned int lbl_803ED4B4;
extern OSCond lbl_803ED4BC;

int fn_802830F0(void);
unsigned int fn_80283E48(short n);
int fn_80284030(void);
int fn_8028410C(void);
unsigned int fn_80284700(short n);
void fn_80284D1C(Desc_802C2860 *pDesc);
void fn_80284DD0(Desc_802C2860 *pDesc);
void fn_80284E70(Desc_802C2860 *pDesc);
void fn_80284F78(Desc_802C2860 *pDesc);
void fn_80284FB8(short node, Leaf_802C2860 *pLeaf);
void fn_80285394(short count, unsigned int value);
void fn_80285458(void);
void fn_8028555C(short symbol, unsigned short weight);
Node_803B795C fn_802855EC();

int fn_802832CC(void)
{
    Leaf_802C2860 *pTable;
    int index;
    short code;
    short symbol;
    short length;
    unsigned short distance;

    while (lbl_803ED43C != lbl_803ED43E)
    {
        lbl_803ED490--;
        *lbl_803ED494++ = lbl_803ED440[lbl_803ED43C++];
        lbl_803ED43C &= 0x7FFF;
    }
    for (;;)
    {
        lbl_803ED484 = (lbl_803ED47E + 1) & 0xFF;
        while (lbl_803ED484 != lbl_803ED486 && lbl_803ED488 != 0)
        {
            lbl_803B7DD4[lbl_803ED47E] = *lbl_803ED48C;
            lbl_803ED48C++;
            lbl_803ED47E = lbl_803ED484++;
            lbl_803ED488--;
            lbl_803ED484 &= 0xFF;
        }
        if (lbl_803ED488 == 0 && lbl_803ED474->mUnknown18 == 0)
        {
            lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04;
            lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
            return 1;
        }
        pTable = lbl_803B545C;
        index = 0;
        do
        {
            index = pTable[index].mUnknown00 + fn_80283E48(pTable[index].mUnknown02);
        } while (pTable[index].mUnknown02 != 0);
        code = pTable[index].mUnknown00;
        if (code <= 255)
        {
            lbl_803ED440[lbl_803ED43E++] = code;
            lbl_803ED43E &= 0x7FFF;
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
            else if (lbl_802C2878[code] != 0)
            {
                length = lbl_802C2894[code];
                length += fn_80283E48(lbl_802C2878[code]);
            }
            else
            {
                length = 227;
            }
            pTable = lbl_803B61B8;
            index = 0;
            do
            {
                index = pTable[index].mUnknown00 + fn_80283E48(pTable[index].mUnknown02);
            } while (pTable[index].mUnknown02 != 0);
            symbol = pTable[index].mUnknown00;
            if (symbol <= 3)
            {
                distance = symbol + 1;
            }
            else
            {
                distance = lbl_802C28EE[symbol];
                distance += fn_80283E48(lbl_802C28D0[symbol]);
            }
            distance = (lbl_803ED43C - (distance + 0x8000)) & 0x7FFF;
            do
            {
                lbl_803ED440[lbl_803ED43E++] = lbl_803ED440[distance++];
                distance &= 0x7FFF;
                lbl_803ED43E &= 0x7FFF;
            } while (--length > 0);
        }
        do
        {
            if (lbl_803ED490 == 0)
            {
                lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04 - lbl_803ED488;
                lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04;
                return 2;
            }
            lbl_803ED490--;
            *lbl_803ED494++ = lbl_803ED440[lbl_803ED43C++];
            lbl_803ED43C &= 0x7FFF;
        } while (lbl_803ED43C != lbl_803ED43E);
    }
    lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04 - lbl_803ED488;
    lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
    lbl_803ED428 = fn_802830F0;
    return 0;
}

#define RING_FILL()                                                \
    while (((wr + 1) & 0xFF) != rd && avail > 0)                   \
    {                                                              \
        avail--;                                                   \
        lbl_803B7DD4[wr++] = *pIn++;                               \
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
            bitBuf = lbl_803B7DD4[rd++];                       \
            rd &= 0xFF;                                        \
            if (rd != wr)                                          \
            {                                                      \
                bitBuf = (bitBuf << 8) | lbl_803B7DD4[rd++];   \
                rd &= 0xFF;                                    \
                if (rd != wr)                                      \
                {                                                  \
                    bitBuf = (bitBuf << 8) | lbl_803B7DD4[rd++];\
                    rd &= 0xFF;                                \
                    if (rd != wr)                                  \
                    {                                              \
                        bitBuf = (bitBuf << 8) | lbl_803B7DD4[rd++];\
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

int fn_80283660(void)
{
    short wr = lbl_803ED47E;
    short rd = lbl_803ED486;
    unsigned char flag = lbl_803ED474->mUnknown18;
    short bitCount = lbl_803ED47C;
    unsigned int bitBuf = lbl_803ED480;
    int avail = lbl_803ED488;
    unsigned char *pIn = lbl_803ED48C;
    int remaining = lbl_803ED490;
    unsigned char *pOut = lbl_803ED494;
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
            lbl_803ED47E = wr;
            lbl_803ED486 = rd;
            lbl_803ED47C = bitCount;
            lbl_803ED480 = bitBuf;
            lbl_803ED488 = avail;
            lbl_803ED48C = pIn;
            lbl_803ED494 = pOut;
            lbl_803ED490 = remaining;
            lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04;
            lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - remaining;
            return 1;
        }
        length = 0;
        do
        {
            n = lbl_803B545C[length].mUnknown02;
            RING_GETBITS(bits, n);
            length = lbl_803B545C[length].mUnknown00 + bits;
        } while (lbl_803B545C[length].mUnknown02 != 0);
        code = lbl_803B545C[length].mUnknown00;
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
            n = lbl_802C2878[code];
            if (n > 0)
            {
                RING_GETBITS(length, n);
                length += lbl_802C2894[code];
            }
            else
            {
                length = 227;
            }
        }
        distance = 0;
        do
        {
            n = lbl_803B61B8[distance].mUnknown02;
            RING_GETBITS(bits, n);
            distance = lbl_803B61B8[distance].mUnknown00 + bits;
        } while (lbl_803B61B8[distance].mUnknown02 != 0);
        code = lbl_803B61B8[distance].mUnknown00;
        if (code <= 3)
        {
            distance = code + 1;
        }
        else
        {
            n = lbl_802C28D0[code];
            RING_GETBITS(distance, n);
            distance += lbl_802C28EE[code];
        }
        remaining -= length;
        pSrc = pOut - distance;
        pEnd = pSrc + length;
        do
        {
            *pOut++ = *pSrc++;
        } while (pSrc < pEnd);
    }
    lbl_803ED47E = wr;
    lbl_803ED486 = rd;
    lbl_803ED47C = bitCount;
    lbl_803ED480 = bitBuf;
    lbl_803ED48C = pIn;
    lbl_803ED494 = pOut;
    lbl_803ED488 = avail;
    lbl_803ED490 = remaining;
    lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04 - avail;
    lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - remaining;
    lbl_803ED428 = fn_802830F0;
    return 0;
}

unsigned int fn_80283E48(short n)
{
    unsigned int result;

    if (n < lbl_803ED47C)
    {
        result = lbl_803ED480 >> (lbl_803ED47C - n);
        lbl_803ED47C -= n;
        lbl_803ED480 &= (1 << lbl_803ED47C) - 1;
    }
    else
    {
        n -= lbl_803ED47C;
        result = lbl_803ED480;
        if (lbl_803ED486 != lbl_803ED47E)
        {
            lbl_803ED480 = lbl_803B7DD4[lbl_803ED486++];
            lbl_803ED486 &= 0xFF;
            if (lbl_803ED486 != lbl_803ED47E)
            {
                lbl_803ED480 = (lbl_803ED480 << 8) | lbl_803B7DD4[lbl_803ED486++];
                lbl_803ED486 &= 0xFF;
                if (lbl_803ED486 != lbl_803ED47E)
                {
                    lbl_803ED480 = (lbl_803ED480 << 8) | lbl_803B7DD4[lbl_803ED486++];
                    lbl_803ED486 &= 0xFF;
                    if (lbl_803ED486 != lbl_803ED47E)
                    {
                        lbl_803ED480 = (lbl_803ED480 << 8) | lbl_803B7DD4[lbl_803ED486++];
                        lbl_803ED486 &= 0xFF;
                        lbl_803ED47C = 32;
                    }
                    else
                        lbl_803ED47C = 24;
                }
                else
                    lbl_803ED47C = 16;
            }
            else
                lbl_803ED47C = 8;
        }
        else
            lbl_803ED47C = 0;
        lbl_803ED484 = (lbl_803ED47E + 1) & 0xFF;
        while (lbl_803ED484 != lbl_803ED486 && lbl_803ED488 != 0)
        {
            lbl_803B7DD4[lbl_803ED47E] = *lbl_803ED48C;
            lbl_803ED48C++;
            lbl_803ED47E = lbl_803ED484++;
            lbl_803ED488--;
            lbl_803ED484 &= 0xFF;
        }
        if (n > 0)
        {
            result = (result << n) | (lbl_803ED480 >> (lbl_803ED47C - n));
            lbl_803ED47C -= n;
            lbl_803ED480 &= (1 << lbl_803ED47C) - 1;
        }
    }
    return result;
}

int fn_80284030(void)
{
    if (!(unsigned char)fn_80284700(1))
    {
        fn_801F8014(&lbl_803B543C);
        lbl_803ED460 = fn_80284700;
        fn_80284D1C(&lbl_802C2860);
        fn_80284DD0(&lbl_802C2860);
        fn_80284E70(&lbl_802C2860);
        fn_80284F78(&lbl_802C2860);
        fn_80284D1C(&lbl_802C286C);
        fn_80284DD0(&lbl_802C286C);
        fn_80284E70(&lbl_802C286C);
        fn_80284F78(&lbl_802C286C);
        fn_801F809C(&lbl_803B543C);
        lbl_803ED434 = fn_8028410C;
        return 0;
    }
    lbl_803ED4B4 = fn_80284700(32);
    lbl_803ED434 = 0;
    lbl_803ED49C = 0;
    lbl_803ED4A0 = 0;
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

int fn_8028410C(void)
{
    short bitCount = lbl_803ED49C;
    unsigned int bitBuf = lbl_803ED4A0;
    int avail = lbl_803ED4A4;
    unsigned char *pIn = lbl_803ED4A8;
    int remaining = lbl_803ED4AC;
    unsigned char *pOut = lbl_803ED4B0;

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
            GETBITS(bits, lbl_803B6320[index].mUnknown02);
            index = lbl_803B6320[index].mUnknown00 + bits;
        } while (lbl_803B6320[index].mUnknown02 != 0);
        code = lbl_803B6320[index].mUnknown00;
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
            index = lbl_802C2878[code];
            if (index > 0)
            {
                GETBITS(length, index);
                length += lbl_802C2894[code];
            }
            else
            {
                length = 227;
            }
        }
        index = 0;
        do
        {
            GETBITS(ubits, lbl_803B707C[index].mUnknown02);
            index = lbl_803B707C[index].mUnknown00 + ubits;
        } while (lbl_803B707C[index].mUnknown02 != 0);
        code = lbl_803B707C[index].mUnknown00;
        if (code <= 3)
        {
            distance = code + 1;
        }
        else
        {
            index = lbl_802C28D0[code];
            GETBITS(distance, index);
            distance += lbl_802C28EE[code];
        }
        remaining -= length;
        pSrc = pOut - distance;
        pEnd = pSrc + length;
        do
        {
            *pOut++ = *pSrc++;
        } while (pSrc < pEnd);
    }
    lbl_803ED49C = bitCount;
    lbl_803ED4A0 = bitBuf;
    lbl_803ED4A4 = avail;
    lbl_803ED4A8 = pIn;
    lbl_803ED4AC = remaining;
    lbl_803ED4B0 = pOut;
    lbl_803ED434 = fn_80284030;
    return 0;
}

unsigned int fn_80284700(short n)
{
    unsigned int result;

    if (n < lbl_803ED49C)
    {
        result = lbl_803ED4A0 >> (lbl_803ED49C - n);
        lbl_803ED49C -= n;
        lbl_803ED4A0 &= (1 << lbl_803ED49C) - 1;
    }
    else
    {
        n -= lbl_803ED49C;
        result = lbl_803ED4A0;
        if (lbl_803ED4A4 > 3)
        {
            lbl_803ED49C = 32;
            lbl_803ED4A4 -= 4;
            lbl_803ED4A0 = *lbl_803ED4A8++;
            lbl_803ED4A0 = (lbl_803ED4A0 << 8) | *lbl_803ED4A8++;
            lbl_803ED4A0 = (lbl_803ED4A0 << 8) | *lbl_803ED4A8++;
            lbl_803ED4A0 = (lbl_803ED4A0 << 8) | *lbl_803ED4A8++;
        }
        else if (lbl_803ED4A4 > 2)
        {
            lbl_803ED49C = 24;
            lbl_803ED4A4 -= 3;
            lbl_803ED4A0 = *lbl_803ED4A8++;
            lbl_803ED4A0 = (lbl_803ED4A0 << 8) | *lbl_803ED4A8++;
            lbl_803ED4A0 = (lbl_803ED4A0 << 8) | *lbl_803ED4A8++;
        }
        else if (lbl_803ED4A4 > 1)
        {
            lbl_803ED49C = 16;
            lbl_803ED4A4 -= 2;
            lbl_803ED4A0 = *lbl_803ED4A8++;
            lbl_803ED4A0 = (lbl_803ED4A0 << 8) | *lbl_803ED4A8++;
        }
        else if (lbl_803ED4A4 > 0)
        {
            lbl_803ED49C = 8;
            lbl_803ED4A4 -= 1;
            lbl_803ED4A0 = *lbl_803ED4A8++;
        }
        else
        {
            lbl_803ED49C = 0;
            lbl_803ED4A0 = 0;
        }
        if (n > 0)
        {
            result = (result << n) | (lbl_803ED4A0 >> (lbl_803ED49C - n));
            lbl_803ED49C -= n;
            lbl_803ED4A0 &= (1 << lbl_803ED49C) - 1;
        }
    }
    return result;
}

void fn_8028490C(Desc_802C2860 *p)
{
    Code_802C2860 *pElems = p->mpCodes;
    short count = p->mCount;
    short i;

    for (i = 0; i < count; i++)
        fn_80285394(4, pElems[i].mUnknown02);
}

void fn_80284968(Desc_802C2860 *p)
{
    Code_802C2860 *pElems = p->mpCodes;
    short count = p->mCount;
    unsigned short used;
    short i;
    short next;
    unsigned short weight;
    Node_803B795C node;

    lbl_803B795C[0].mUnknown02 = 0;
    lbl_803B795C[0].mUnknown00 = 0;
    lbl_803ED470 = 0;
    used = 0;
    for (i = 0; i < count; i++)
    {
        if (pElems[i].mUnknown00 != 0)
        {
            used++;
            fn_8028555C(i + count, pElems[i].mUnknown00);
        }
    }
    while (used <= 1)
    {
        for (i = 0; pElems[i].mUnknown00 != 0; i++)
            ;
        pElems[i].mUnknown00 = 1;
        used++;
        fn_8028555C(i + count, 1);
    }
    next = count - 1;
    while (lbl_803ED470 > 1)
    {
        node = fn_802855EC();
        lbl_803ED464[node.mUnknown00] = next;
        weight = node.mUnknown02;
        node = fn_802855EC();
        lbl_803ED464[node.mUnknown00] = next;
        weight += node.mUnknown02;
        fn_8028555C(next, weight);
        next--;
    }
    node = fn_802855EC();
    lbl_803ED464[node.mUnknown00] = 0;
}

void fn_80284AEC(Desc_802C2860 *p)
{
    short count = p->mCount;
    Code_802C2860 *pElems = p->mpCodes;
    short i;
    short j;
    short length;
    short overflow;
    Node_803B795C node;

    for (i = 0; i <= 15; i++)
        lbl_803B71E4[i] = 0;
    overflow = 0;
    for (i = 0; i < count; i++)
    {
        if (pElems[i].mUnknown00 != 0)
        {
            length = 0;
            for (j = lbl_803ED464[i + count]; j > 0; j = lbl_803ED464[j])
                length++;
            if (length > 15)
            {
                length = 15;
                overflow++;
            }
            pElems[i].mUnknown02 = length;
            lbl_803B71E4[length]++;
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
            while (lbl_803B71E4[length] == 0)
                length--;
            lbl_803B71E4[length]--;
            lbl_803B71E4[length + 1] += 2;
            lbl_803B71E4[15]--;
            overflow -= 2;
        } while (overflow > 0);
        lbl_803B795C[0].mUnknown02 = 0;
        lbl_803B795C[0].mUnknown00 = 0;
        lbl_803ED470 = 0;
        for (i = 0; i < count; i++)
        {
            if (pElems[i].mUnknown00 != 0)
                fn_8028555C(i, pElems[i].mUnknown00);
        }
        for (length = 15; length > 0; length--)
        {
            for (count = lbl_803B71E4[length]; count > 0; count--)
            {
                node = fn_802855EC();
                pElems[node.mUnknown00].mUnknown02 = length;
            }
        }
    }
}

void fn_80284D1C(Desc_802C2860 *pDesc)
{
    Code_802C2860 *pCodes = pDesc->mpCodes;
    short count = pDesc->mCount;
    short i;
    short length;

    for (length = 1; length <= 15; length++)
        lbl_803B71E4[length] = 0;
    for (i = 0; i < count; i++)
    {
        length = lbl_803ED460(4);

        pCodes[i].mUnknown02 = length;
        lbl_803B71E4[length]++;
    }
    lbl_803B71E4[0] = 0;
}

void fn_80284DD0(Desc_802C2860 *pDesc)
{
    unsigned short next[16];
    Code_802C2860 *pCodes = pDesc->mpCodes;
    short count = pDesc->mCount;
    unsigned short n = 0;
    short bits;

    for (bits = 1; bits <= 15; bits++)
    {
        n = (n + lbl_803B71E4[bits - 1]) << 1;
        next[bits] = n;
    }
    for (n = 0; n < count; n++)
    {
        short length = pCodes[n].mUnknown02;

        if (length > 0)
            pCodes[n].mUnknown00 = next[length]++;
    }
}

void fn_80284E70(Desc_802C2860 *pDesc)
{
    Code_802C2860 *pCodes = pDesc->mpCodes;
    short count = pDesc->mCount;
    short i;
    short next = 1;

    lbl_803B7204[0][0] = count;
    lbl_803B7204[0][1] = count;
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
                short child = lbl_803B7204[node][bit];

                if (child != count)
                {
                    node = child;
                }
                else
                {
                    child = next++;
                    lbl_803B7204[child][1] = count;
                    lbl_803B7204[child][0] = count;
                    lbl_803B7204[node][bit] = child;
                    node = child;
                }
                length--;
                bit = (code >> length) & 1;
            }
            lbl_803B7204[node][bit] = -i;
        }
    }
}

void fn_80284F78(Desc_802C2860 *pDesc)
{
    lbl_803ED470 = 0;
    lbl_803ED468 = 1;
    lbl_803ED46C = pDesc->mpLeaves;
    fn_80284FB8(0, pDesc->mpLeaves);
}

void fn_80284FB8(short node, Leaf_802C2860 *pLeaf)
{
    short depth;
    short value;
    short size;
    short count;
    short index;
    short top;

    lbl_803ED470++;
    lbl_803B795C[lbl_803ED470].mUnknown00 = node;
    lbl_803B795C[lbl_803ED470].mUnknown02 = 0;
    value = lbl_803B7204[node][0];
    depth = 1;
    while (value > 0)
    {
        lbl_803ED470++;
        lbl_803B795C[lbl_803ED470].mUnknown00 = value;
        lbl_803B795C[lbl_803ED470].mUnknown02 = 0;
        value = lbl_803B7204[value][0];
        depth++;
    }
    pLeaf->mUnknown02 = depth;
    size = 1 << depth;
    pLeaf->mUnknown00 = lbl_803ED468;
    index = lbl_803ED468;
    lbl_803ED468 += size;
    lbl_803ED46C[index].mUnknown02 = 0;
    lbl_803ED46C[index].mUnknown00 = -value;
    depth = 0;
    index++;
    for (count = size - 1; count > 0; count--)
    {
        do
        {
            top = lbl_803ED470--;
            depth++;
        } while (++lbl_803B795C[top].mUnknown02 > 1);
        depth--;
        lbl_803ED470 = top;
        value = lbl_803B7204[lbl_803B795C[top].mUnknown00][1];
        while (depth > 0)
        {
            lbl_803ED470++;
            lbl_803B795C[lbl_803ED470].mUnknown00 = value;
            lbl_803B795C[lbl_803ED470].mUnknown02 = 0;
            value = lbl_803B7204[value][0];
            depth--;
        }
        if (value <= 0)
        {
            lbl_803ED46C[index].mUnknown02 = 0;
            lbl_803ED46C[index].mUnknown00 = -value;
        }
        else
        {
            fn_80284FB8(value, &lbl_803ED46C[index]);
        }
        index++;
    }
    lbl_803ED470 -= pLeaf->mUnknown02;
}

void fn_802851E8(void)
{
    unsigned short length = 1;
    unsigned char code;

    for (code = 0; length <= 256; code++)
    {
        for (; length < lbl_802C28EE[code + 1]; length++)
            lbl_803B775C[length - 1] = code;
    }
    for (; code <= 29; code++)
    {
        for (; length < lbl_802C28EE[code + 1]; length++)
            lbl_803B785C[(length - 1) >> 7] = code;
    }
    length = 0;
    for (code = 0; code <= 27; code++)
    {
        while (length < lbl_802C2894[code + 1])
            lbl_803B7678[length++] = code;
    }
}

void fn_80285304(unsigned int *pSum, unsigned char *pData, unsigned int length)
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

void fn_80285394(short count, unsigned int value)
{
    unsigned char shift;

    do
    {
        if (count + lbl_803ED47C <= 7)
        {
            lbl_803ED47C += count;
            lbl_803ED480 = (unsigned char)((lbl_803ED480 << count) | value);
            break;
        }
        shift = 8 - lbl_803ED47C;
        lbl_803ED480 = (unsigned char)((lbl_803ED480 << shift) | (value >> (count - shift)));
        count -= shift;
        lbl_803B7DD4[lbl_803ED47E++] = (unsigned char)lbl_803ED480;
        lbl_803ED47E &= 0xFF;
        lbl_803ED47C = 0;
    } while (count > 0);
    fn_80285458();
}

void fn_80285458(void)
{
    while (lbl_803ED486 != lbl_803ED47E && lbl_803ED490 != 0)
    {
        lbl_803ED490--;
        *lbl_803ED494++ = lbl_803B7DD4[lbl_803ED486++];
        lbl_803ED486 &= 0xFF;
    }
}

void fn_802854D8(void)
{
    if (lbl_803ED47C <= 7)
    {
        if (lbl_803ED47C > 0)
        {
            lbl_803ED480 <<= 8 - lbl_803ED47C;
            lbl_803ED47C = 8;
        }
    }
    if (lbl_803ED47C == 8)
    {
        lbl_803B7DD4[lbl_803ED47E++] = (unsigned char)lbl_803ED480;
        lbl_803ED47E &= 0xFF;
        lbl_803ED47C = 0;
        fn_80285458();
    }
}

void fn_8028555C(short symbol, unsigned short weight)
{
    short i = ++lbl_803ED470;

    while (lbl_803B795C[i / 2].mUnknown02 > weight)
    {
        lbl_803B795C[i] = lbl_803B795C[i / 2];
        i /= 2;
    }
    lbl_803B795C[i].mUnknown00 = symbol;
    lbl_803B795C[i].mUnknown02 = weight;
}

Node_803B795C fn_802855EC(void)
{
    Node_803B795C top = lbl_803B795C[1];
    unsigned short weight = lbl_803B795C[lbl_803ED470].mUnknown02;
    short count = --lbl_803ED470;
    short i = 1;
    short child;

    while (i <= count / 2)
    {
        child = i << 1;
        if (child < count && lbl_803B795C[child].mUnknown02 > lbl_803B795C[child + 1].mUnknown02)
            child++;
        if (lbl_803B795C[child].mUnknown02 >= weight)
            break;
        lbl_803B795C[i] = lbl_803B795C[child];
        i = child;
    }
    lbl_803B795C[i] = lbl_803B795C[lbl_803ED470 + 1];
    return top;
}

void fn_802856D8(void)
{
    int i;

    GBAInit();
    for (i = 0; i < 4; i++)
        fn_801C1F94(&lbl_803E990C[i], 0, sizeof(Struct_803E990C));
}

int fn_8028572C(int channel)
{
    OSTick tick;
    u8 status;

    if (lbl_803E990C[channel].mUnknown08 < 2 || lbl_803E990C[channel].mUnknown08 > 4)
    {
        tick = OSGetTick();
        if (GBAGetStatus(channel, &status) == 0)
        {
            lbl_803E990C[channel].mUnknown00 = tick;
            lbl_803E990C[channel].mUnknown08 = 1;
        }
        else if (OSTicksToSeconds(tick - lbl_803E990C[channel].mUnknown00) != 0)
        {
            lbl_803E990C[channel].mUnknown08 = 0;
        }
    }
    return lbl_803E990C[channel].mUnknown08;
}

void fn_802857D8(void)
{
    if (lbl_803EC590 != 0)
        OSSignalCond(&lbl_803ED4BC);
}

int fn_80285808(File_80285808 *pFile, const void *pValue, const char *pName, int write)
{
    int handle;

    if (write)
        handle = fn_801C96E4(pName, 44);
    else
        handle = fn_801C96E4(pName, 36);
    if (handle < 0)
        return 36;
    pFile->mHandle = handle;
    pFile->mPosition = 0;
    pFile->mUnknown08 = pValue;
    return 0;
}

int fn_80285878(File_80285808 *pFile)
{
    if (pFile->mHandle < 0)
        return 3;
    if (fn_801C97F0(pFile->mHandle) != 0)
        return 36;
    return 0;
}

int fn_802858BC(File_80285808 *pFile, void *pBuffer, int size, int *pCount)
{
    int count;

    if (pFile->mHandle < 0)
        return 3;
    count = fn_801CA648(pFile->mHandle, pFile->mPosition, pBuffer, size);
    if (count < 0)
    {
        *pCount = 0;
        return 36;
    }
    *pCount = count;
    pFile->mPosition += count;
    return 0;
}

int fn_80285940(File_80285808 *pFile, void *pBuffer, int size, int *pCount)
{
    int count;

    if (pFile->mHandle < 0)
        return 3;
    count = fn_801C9960(pFile->mHandle, pBuffer, size, 0);
    if (count < 0)
    {
        *pCount = 0;
        return 36;
    }
    *pCount = count;
    pFile->mPosition += count;
    return 0;
}

int fn_802859B4(File_80285808 *pFile, int offset)
{
    if (pFile->mHandle < 0)
        return 3;
    if (fn_801C9844(pFile->mHandle, offset, 1) != 0)
        return 36;
    pFile->mPosition += offset;
    return 0;
}

int fn_80285A1C(void)
{
    return 0;
}

void fn_80285A24(Struct_80285A24 *p)
{
    if ((unsigned char)OSCreateThread(&lbl_803BA580, p->mUnknown10, p->mUnknown08, p->mUnknown14 + p->mUnknown04, p->mUnknown04, 22, 1))
        OSResumeThread(&lbl_803BA580);
}

void fn_80285A8C(void)
{
}
