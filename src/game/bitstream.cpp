#include "game/bitstream.h"

void OpenBitStream(BitStream_t *pStream, void *pBuffer, BitStreamMode_t mode)
{
    pStream->mpBuffer = (unsigned long long *)pBuffer;
    pStream->mWord = 0;
    pStream->mBit = 63;
    pStream->mMode = mode;
}

/* Returns the number of bytes used, counting a partly filled word. */
int CloseBitStream(BitStream_t *pStream)
{
    int size = pStream->mWord * 8;

    if (pStream->mBit != 63) {
        size += 8;
    }
    pStream->mMode = kBitStreamClosed;
    return size;
}

long long ReadBitStream(BitStream_t *pStream, unsigned int bits)
{
    int word = pStream->mWord;
    int bit = pStream->mBit;
    unsigned long long *pWord = &pStream->mpBuffer[word];
    unsigned long long value = *pWord;
    unsigned long long result;
    unsigned int count = bit + 1;

    if (count < bits) {
        bits -= count;
        result = value & ((((unsigned long long)((count >> 6) ^ 1)) << count) - 1);
        result <<= bits;
        result |= pWord[1] >> (64 - bits);
        pStream->mBit = 63 - bits;
        pStream->mWord = word + 1;
    } else {
        result = value >> (bit - (bits - 1));
        result &= (1ULL << bits) - 1;
        pStream->mBit = bit - bits;
    }
    if (pStream->mBit < 0) {
        pStream->mBit += 64;
        pStream->mWord++;
    }
    return result;
}

void fn_80191068(BitStream_t *pStream, unsigned long long value, unsigned int bits)
{
    unsigned long long current;
    int word;
    unsigned long long *pBuffer;
    unsigned int count;

    if (pStream->mBit != 63) {
        current = pStream->mpBuffer[pStream->mWord];
        word = pStream->mWord;
        pBuffer = pStream->mpBuffer;
    } else {
        current = 0;
        word = pStream->mWord;
        pBuffer = pStream->mpBuffer;
    }
    value &= (((unsigned long long)((bits >> 6) ^ 1)) << bits) - 1;
    count = pStream->mBit + 1;
    if (count < bits) {
        unsigned long long low;

        bits -= count;
        low = value << (64 - bits);
        value >>= bits;
        current |= value;
        pBuffer[word] = current;
        pStream->mpBuffer[pStream->mWord + 1] = low;
        pStream->mBit = 63 - bits;
        pStream->mWord++;
    } else {
        unsigned int shift = bits - 1;

        current |= value << (pStream->mBit - shift);
        pBuffer[word] = current;
        pStream->mBit -= bits;
    }
    if (pStream->mBit < 0) {
        pStream->mBit += 64;
        pStream->mWord++;
    }
}
