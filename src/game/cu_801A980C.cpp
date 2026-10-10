#include "game/Frame_8019D3B8.h"
#include "game/Item_8019F044.h"
#include "game/Object_80040818.h"
#include "game/cu_801A8620.h"
#include "game/bitstream.h"
#include "game/fn_801D2B7C.h"
#include <string.h>

extern "C" {
void fn_801A679C(short *pOut, short *pA, short *pB, int weight, int count);
void fn_801A67DC(short *pOut, short *pA, short *pB, int weight, int count, short *pOffset, short *pScale);
void fn_801A6838(short *pOut, short *pA, int count, short *pOffset, short *pScale);
float fn_801BE5D0(void *p, int index);
void fn_801CF810(int *pOut, int *pA, int *pB, float t);
void fn_801CF8A8(int *pOut, int a, int b, float t);
void fn_80227930(float *pOut, float *pA, float *pB, float t);

void fn_801A980C(Child_801A9430 *p)
{
    Object_801A8620 *owner = p->mpUnknown50;
    if (owner->mUnknownE8.mWord & 0x10) {
        fn_801A8D08(p, owner);
    }
}

short *fn_801A983C(Frame_8019D3B8 *header, void *encoded)
{
    unsigned char *bytes = (unsigned char *)encoded;
    header->count = bytes[0] & 0x3F;
    header->flags = bytes[1];
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
    memset(header->vectorA, 0, 6);
    memset(header->vector10, 0, 6);
    return (short *)(bytes + ((char *)read - (char *)start));
}

void fn_801A991C(short *destination, short *source, Record_8019D8AC *context, int mirrored)
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

int fn_801A9C08(int value, int index, int component, void *pContext, Pair_8019D800 *pPair)
{
    if (pContext) {
        component += index * 3;
        value = (value * pPair->mUnknown4[component] >> 15) + pPair->mUnknown0[component];
    }
    return (short)value;
}

void fn_801A9C44(Pose_80041930 *pose, BlendEntry_8019EDDC *entry, Record_8019D8AC *context, int unused)
{
    Frame_8019D3B8 frame;
    int special = entry->mUnknown8 & 4;
    short *samples;
    if (context) {
        short *encodedSamples = fn_801A983C(&frame, entry->mpUnknown40);
        fn_801A991C(pose->mUnknown48, encodedSamples, context, 0);
        samples = pose->mUnknown48;
    } else {
        samples = fn_801A983C(&frame, entry->mpUnknown40);
    }
    unsigned int count = frame.count;
    Frame_8019D3B8 *pFrame = &frame;
    if (count > 64)
        count = 64;
    if (special) {
        pose->mUnknown8[0] = 0.0f;
        pose->mUnknown8[2] = 0.0f;
        pose->mUnknown8[1] = pFrame->word6 * 0.000244140625f;
        if (pFrame->flags & 0x80) {
            int x = (unsigned short)pFrame->word4 | ((pFrame->flags & 3) << 16);
            int z = (unsigned short)pFrame->word8 | ((pFrame->flags & 0x18) << 13);
            if ((pFrame->flags & 4) && x)
                x |= 0xFFFC0000;
            if ((pFrame->flags & 0x20) && z)
                z |= 0xFFFC0000;
            entry->mUnknown24[0] = z * 0.000244140625f;
            entry->mUnknown24[1] = x * 0.000244140625f;
        } else {
            entry->mUnknown24[0] = pFrame->word8 * 0.000244140625f;
            entry->mUnknown24[1] = pFrame->word4 * 0.000244140625f;
        }
    } else {
        if (pFrame->flags & 0x80) {
            int x = (unsigned short)pFrame->word4 | ((pFrame->flags & 3) << 16);
            int z = (unsigned short)pFrame->word8 | ((pFrame->flags & 0x18) << 13);
            if ((pFrame->flags & 4) && x)
                x |= 0xFFFC0000;
            if ((pFrame->flags & 0x20) && z)
                z |= 0xFFFC0000;
            pose->mUnknown8[0] = x * 0.000244140625f;
            pose->mUnknown8[2] = z * 0.000244140625f;
        } else {
            pose->mUnknown8[0] = pFrame->word4 * 0.000244140625f;
            pose->mUnknown8[2] = pFrame->word8 * 0.000244140625f;
        }
        pose->mUnknown8[1] = pFrame->word6 * 0.000244140625f;
        pose->mUnknown32 = pFrame->word2 << 8;
    }
    if (!context)
        memcpy(pose->mUnknown48, samples, count * 6);
    Pair_8019D800 *pair = &context->mUnknown4;
    entry->mUnknown12[0] = fn_801A9C08(samples[0], 0, 0, context, pair) << 8;
    entry->mUnknown12[1] = pFrame->word2 << 8;
    entry->mUnknown12[2] = fn_801A9C08(samples[2], 0, 2, context, pair) << 8;
}

void fn_801A9F98(Extra_8004149C *unused, Object_80040818 *pObject, int blend, int unused2)
{
    Blend_8019EDDC *pBlend = (Blend_8019EDDC *)blend;
    Pose_80041930 pose;
    short samples[64 * 3];
    Pose_80041930 *pPose = &pObject->mUnknown172;
    unsigned int entries = pBlend->mUnknown0;
    BlendEntry_8019EDDC *pEntry;
    Record_8019D8AC *pContext;
    Pair_8019D800 *pPair = 0;
    unsigned int values;
    float weight;
    unsigned int i;

    pose.mUnknown48 = samples;
    if (entries == 0) {
        return;
    }
    values = pPose->mUnknown4 * 3;
    pEntry = &pBlend->mUnknown4[0];
    pContext = pEntry->mpUnknown36;
    fn_801A9C44(pPose, pEntry, pContext, 0);
    if (pContext != 0) {
        pPair = &pContext->mUnknown4;
        fn_801A6838(pPose->mUnknown48, pPose->mUnknown48, values, pPair->mUnknown0, pPair->mUnknown4);
    }
    for (i = 1; i < entries; i++) {
        pEntry = &pBlend->mUnknown4[i];
        weight = pEntry->mUnknown4;
        pContext = pEntry->mpUnknown36;
        fn_801A9C44(&pose, pEntry, pContext, 0);
        if (pContext != 0) {
            pPair = &pContext->mUnknown4;
        }
        fn_80227930(pPose->mUnknown8, pose.mUnknown8, pPose->mUnknown8, weight);
        fn_801CF8A8(&pPose->mUnknown32, pose.mUnknown32, pPose->mUnknown32, weight);
        if (pContext != 0) {
            fn_801A67DC(pPose->mUnknown48, pose.mUnknown48, pPose->mUnknown48, (int)(weight * 4095.0f), values,
                        pPair->mUnknown0, pPair->mUnknown4);
        } else {
            fn_801A679C(pPose->mUnknown48, pose.mUnknown48, pPose->mUnknown48, (int)(weight * 4095.0f), values);
        }
    }
    pPose->mUnknown6 = -1;
}

void fn_801AA124(Object_80040818 *pObject, void *items, int count, void *p)
{
    Item_8019F044 *pItems = (Item_8019F044 *)items;
    int angles[3];
    float total = 0.0f;
    float weight;
    unsigned int i;

    angles[0] = angles[1] = angles[2] = 0;
    for (i = 0; i < (unsigned int)count; i++) {
        if (pItems[i].mUnknown1 != 0 && pItems[i].mUnknown48 == 0.0f) {
            weight = fn_801BE5D0(p, pItems[i].mUnknown8) * pItems[i].mUnknown30;
            total += weight;
            fn_801CF810(angles, pItems[i].mUnknown10, angles, weight / total);
        }
    }
    pObject->mUnknown172.mUnknown32 = angles[1];
    pObject->mUnknown172.mUnknown48[0] = angles[0] >> 8;
    pObject->mUnknown172.mUnknown48[1] = 0;
    pObject->mUnknown172.mUnknown48[2] = angles[2] >> 8;
}

short *fn_801AA220(int count)
{
    return (short *)fn_801D2B7C(64 * 3 * sizeof(short), 0, 0);
}

}
