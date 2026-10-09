#include "game/Frame_8019D3B8.h"
#include "game/bitstream.h"
#include <string.h>

/* Encoded frame blocks start with a count byte whose top two bits flag the
   optional vectors, then a flags byte and four header words. */
struct Block_8019D3B8 {
    unsigned int mWords[7];
};

extern "C" {

void fn_8019D2EC(Pose_80041930 *pose, BlendEntry_8019EDDC *entry, int mirrored)
{
    unsigned char *encoded = (unsigned char *)entry->mpUnknown40;
    unsigned int count = encoded[0];
    short *source = (short *)(encoded + 2);
    if (!mirrored) {
        for (unsigned int i = 0; i < count; i++) {
            pose->mUnknown48[i * 3] = source[i * 3];
            pose->mUnknown48[i * 3 + 1] = source[i * 3 + 1];
            pose->mUnknown48[i * 3 + 2] = source[i * 3 + 2];
        }
    } else {
        for (unsigned int i = 0; i < count; i++) {
            pose->mUnknown48[i * 3] = source[i * 3];
            pose->mUnknown48[i * 3 + 1] = -source[i * 3 + 1];
            pose->mUnknown48[i * 3 + 2] = -source[i * 3 + 2];
        }
    }
}

short *fn_8019D3B8(Frame_8019D3B8 *header, void *encoded)
{
    unsigned char *bytes = (unsigned char *)encoded;
    unsigned int first = bytes[0];
    unsigned int optional = first >> 6;
    header->flags = bytes[1];
    header->count = first & 0x3F;
    Block_8019D3B8 aligned;
    short *read;
    if ((unsigned int)encoded & 1) {
        aligned = *(Block_8019D3B8 *)encoded;
        read = (short *)&aligned;
    } else {
        read = (short *)encoded;
    }
    short *start = read;
    header->word2 = read[1];
    header->word4 = read[2];
    header->word6 = read[3];
    header->word8 = read[4];
    read += 5;
    if (optional & 1) {
        header->vectorA[0] = read[0];
        header->vectorA[1] = read[1];
        header->vectorA[2] = read[2];
        read += 3;
    } else {
        memset(header->vectorA, 0, 6);
    }
    if (optional & 2) {
        header->vector10[0] = read[0];
        header->vector10[1] = read[1];
        header->vector10[2] = read[2];
        read += 3;
    } else {
        memset(header->vector10, 0, 6);
    }
    return (short *)(bytes + ((char *)read - (char *)start));
}

int fn_8019D4EC(unsigned char *encoded)
{
    unsigned int optional = encoded[0] >> 6;
    int size = 10;
    if (optional & 1)
        size = 16;
    if (optional & 2)
        size += 6;
    return size;
}

void fn_8019D514(short *destination, short *source, Record_8019D8AC *context, int mirrored)
{
    BitStream_t stream;
    OpenBitStream(&stream, source, kBitStreamRead);
    unsigned char *channels = context->mpUnknown14;
    int i = 0;
    for (; i < context->mUnknown0 - 5; i += 5) {
        unsigned char *channel = &channels[i * 2];
        unsigned int bits0 = channel[1];
        unsigned int bits1 = channel[3];
        unsigned int bits2 = channel[5];
        unsigned int bits3 = channel[7];
        unsigned int bits4 = channel[9];
        unsigned long long value = ReadBitStream(&stream, bits0 + bits1 + bits2 + bits3 + bits4);
        if (mirrored) {
            destination[channel[8]] = value << (16 - bits4);
            value >>= bits4;
            destination[channel[6]] = value << (16 - bits3);
            value >>= bits3;
            destination[channel[4]] = value << (16 - bits2);
            value >>= bits2;
            destination[channel[2]] = value << (16 - bits1);
            value >>= bits1;
            destination[channel[0]] = value << (16 - bits0);
        } else {
            destination[i + 4] = value << (16 - bits4);
            value >>= bits4;
            destination[i + 3] = value << (16 - bits3);
            value >>= bits3;
            destination[i + 2] = value << (16 - bits2);
            value >>= bits2;
            destination[i + 1] = value << (16 - bits1);
            value >>= bits1;
            destination[i] = value << (16 - bits0);
        }
    }
    for (; i < context->mUnknown0; i++) {
        unsigned int bits = channels[i * 2 + 1];
        if (mirrored)
            destination[channels[i * 2]] = ReadBitStream(&stream, bits) << (16 - bits);
        else
            destination[i] = ReadBitStream(&stream, bits) << (16 - bits);
    }
    CloseBitStream(&stream);
}

int fn_8019D800(int value, int index, int component, void *pContext, Pair_8019D800 *pPair)
{
    if (pContext) {
        component += index * 3;
        value = (value * pPair->mUnknown4[component] >> 15) + pPair->mUnknown0[component];
    }
    return (short)value;
}

}
