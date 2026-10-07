#ifndef GAME_BITSTREAM_H
#define GAME_BITSTREAM_H

enum BitStreamMode_t {
    kBitStreamClosed = -1,
    kBitStreamRead = 0,
    kBitStreamWrite = 1
};

/* Bit stream over a buffer of 64-bit words, filled from the most significant
   bit of each word down. */
struct BitStream_t {
    unsigned long long *mpBuffer;
    BitStreamMode_t mMode;
    int mWord;
    int mBit;
};

void OpenBitStream(BitStream_t *pStream, void *pBuffer, BitStreamMode_t mode);
int CloseBitStream(BitStream_t *pStream);
unsigned long long ReadBitStream(BitStream_t *pStream, unsigned int bits);

extern "C" void fn_80191068(BitStream_t *pStream, unsigned long long value, unsigned int bits);

#endif
