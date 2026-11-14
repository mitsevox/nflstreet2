/* Animation pose decoding: turns one compressed frame of a blend entry into
   a pose (root position, root vector, root orientation and the per-bone
   samples), either as stored or mirrored left to right, and scales the
   root height above the standing height. */
#include "game/AnimFrameHeader.h"

#include <string.h>

extern "C" {
/* Root vector and orientation of a pose whose entry selects no frame vector. */
static float _AnimPoseDecode_afDefaultOffset[3] = { -0.111f, 0.0527f, -0.00534f };
static int _AnimPoseDecode_aiDefaultOrient[3] = { -188603, -472325, 7731779 };

void AnimReadVector(int *output, short *input, int index, AnimQuantContext *context);
}

extern "C" void AnimDecodePoseMirrored(AnimPose_t *pose, AnimBlendEntry *entry, float scale, int mode, AnimQuantContext *context, int unused)
{
    AnimFrameHeader frame;
    AnimFrameHeader *pFrame;
    int special = entry->mUnknown8 & 4;
    short *samples;
    if (context) {
        // FAKEMATCH: block-local alias of frame, only for the target register and frame layout
        AnimFrameHeader *pHeader = &frame;
        samples = pose->mUnknown48;
        short *encodedSamples = AnimReadFrameHeader(pHeader, entry->mpUnknown40);
        pFrame = pHeader;
        AnimUnpackFrameBits(samples, encodedSamples, context, 1);
    } else {
        samples = AnimReadFrameHeader(&frame, entry->mpUnknown40);
        pFrame = &frame;
    }
    unsigned int count = frame.count;
    if (count > 64)
        count = 64;
    if (special) {
        pose->mUnknown8[0] = pose->mUnknown8[2] = 0.0f;
        pose->mUnknown8[1] = pFrame->word6 * 0.000244140625f;
        if (pFrame->flags & 0x80) {
            int x = (unsigned short)pFrame->word4 | ((pFrame->flags & 3) << 16);
            int z = (unsigned short)pFrame->word8 | ((pFrame->flags & 0x18) << 13);
            if ((pFrame->flags & 4) && x)
                x |= 0xFFFC0000;
            if ((pFrame->flags & 0x20) && z)
                z |= 0xFFFC0000;
            entry->mUnknown24[0] = z * 0.000244140625f;
            entry->mUnknown24[1] = -(float)x * 0.000244140625f;
        } else {
            entry->mUnknown24[0] = pFrame->word8 * 0.000244140625f;
            entry->mUnknown24[1] = -(float)pFrame->word4 * 0.000244140625f;
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
    float height = pose->mUnknown8[1];
    if (scale != 1.0f && height > 1.1593530178070068f)
        height = (height - 1.1593530178070068f) * scale + 1.1593530178070068f;
    pose->mUnknown8[1] = height;
    if (!mode) {
        if (entry->mUnknown8 & 0x10)
            mode = 1;
        else if (entry->mUnknown8 & 0x20)
            mode = 2;
    }
    if (mode == 1) {
        pose->mUnknown20[0] = pFrame->vector10[0] * 0.0009765625f;
        pose->mUnknown20[1] = pFrame->vector10[1] * 0.0009765625f;
        pose->mUnknown20[2] = pFrame->vector10[2] * 0.0009765625f;
        AnimMirrorVector(pose->mUnknown36, samples, 19, context);
    } else if (mode == 2) {
        pose->mUnknown20[0] = pFrame->vectorA[0] * 0.0009765625f;
        pose->mUnknown20[1] = pFrame->vectorA[1] * 0.0009765625f;
        pose->mUnknown20[2] = pFrame->vectorA[2] * 0.0009765625f;
        AnimMirrorVector(pose->mUnknown36, samples, 25, context);
    } else {
        pose->mUnknown20[0] = _AnimPoseDecode_afDefaultOffset[0];
        pose->mUnknown20[1] = _AnimPoseDecode_afDefaultOffset[1];
        pose->mUnknown20[2] = _AnimPoseDecode_afDefaultOffset[2];
        pose->mUnknown36[0] = _AnimPoseDecode_aiDefaultOrient[0] << 8;
        pose->mUnknown36[1] = -_AnimPoseDecode_aiDefaultOrient[1] << 8;
        pose->mUnknown36[2] = -_AnimPoseDecode_aiDefaultOrient[2] << 8;
    }
    if (!context)
        AnimMirrorRotations(pose->mUnknown48, samples, count);
    pose->mUnknown8[0] = -pose->mUnknown8[0];
    pose->mUnknown20[0] = -pose->mUnknown20[0];
    AnimQuantTables *pair = &context->mUnknown4;
    entry->mUnknown12[0] = AnimDequantize(samples[0], 0, 0, context, pair) << 8;
    entry->mUnknown12[1] = -pFrame->word2 << 8;
    entry->mUnknown12[2] = -AnimDequantize(samples[2], 0, 2, context, pair) << 8;
}

extern "C" void AnimReadVector(int *output, short *input, int index, AnimQuantContext *context)
{
    if (context) {
        output[0] = AnimDequantize(input[index * 3], index, 0, context, &context->mUnknown4) << 8;
        output[1] = AnimDequantize(input[index * 3 + 1], index, 1, context, &context->mUnknown4) << 8;
        output[2] = AnimDequantize(input[index * 3 + 2], index, 2, context, &context->mUnknown4) << 8;
    } else {
        output[0] = input[index * 3] << 8;
        output[1] = input[index * 3 + 1] << 8;
        output[2] = input[index * 3 + 2] << 8;
    }
}

extern "C" void AnimDecodePose(AnimPose_t *pose, AnimBlendEntry *entry, float scale, int mode, AnimQuantContext *context, int unused)
{
    AnimFrameHeader frame;
    int special = entry->mUnknown8 & 4;
    short *samples;
    if (context) {
        short *encodedSamples = AnimReadFrameHeader(&frame, entry->mpUnknown40);
        AnimUnpackFrameBits(pose->mUnknown48, encodedSamples, context, 0);
        samples = pose->mUnknown48;
    } else {
        samples = AnimReadFrameHeader(&frame, entry->mpUnknown40);
    }
    unsigned int count = frame.count;
    // FAKEMATCH: alias of frame set after the count read, only for the target register layout
    AnimFrameHeader *pFrame = &frame;
    if (count > 64)
        count = 64;
    if (special) {
        pose->mUnknown8[0] = pose->mUnknown8[2] = 0.0f;
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
    float height = pose->mUnknown8[1];
    if (scale != 1.0f && height > 1.1593530178070068f)
        height = (height - 1.1593530178070068f) * scale + 1.1593530178070068f;
    pose->mUnknown8[1] = height;
    if (!mode) {
        if (entry->mUnknown8 & 0x10)
            mode = 1;
        else if (entry->mUnknown8 & 0x20)
            mode = 2;
    }
    if (mode == 1) {
        pose->mUnknown20[0] = pFrame->vectorA[0] * 0.0009765625f;
        pose->mUnknown20[1] = pFrame->vectorA[1] * 0.0009765625f;
        pose->mUnknown20[2] = pFrame->vectorA[2] * 0.0009765625f;
        AnimReadVector(pose->mUnknown36, samples, 25, context);
    } else if (mode == 2) {
        pose->mUnknown20[0] = pFrame->vector10[0] * 0.0009765625f;
        pose->mUnknown20[1] = pFrame->vector10[1] * 0.0009765625f;
        pose->mUnknown20[2] = pFrame->vector10[2] * 0.0009765625f;
        AnimReadVector(pose->mUnknown36, samples, 19, context);
    } else {
        pose->mUnknown20[0] = _AnimPoseDecode_afDefaultOffset[0];
        pose->mUnknown20[1] = _AnimPoseDecode_afDefaultOffset[1];
        pose->mUnknown20[2] = _AnimPoseDecode_afDefaultOffset[2];
        pose->mUnknown36[0] = _AnimPoseDecode_aiDefaultOrient[0] << 8;
        pose->mUnknown36[1] = _AnimPoseDecode_aiDefaultOrient[1] << 8;
        pose->mUnknown36[2] = _AnimPoseDecode_aiDefaultOrient[2] << 8;
    }
    if (!context)
        memcpy(pose->mUnknown48, samples, count * 6);
    AnimQuantTables *pair = &context->mUnknown4;
    entry->mUnknown12[0] = AnimDequantize(samples[0], 0, 0, context, pair) << 8;
    entry->mUnknown12[1] = pFrame->word2 << 8;
    entry->mUnknown12[2] = AnimDequantize(samples[2], 0, 2, context, pair) << 8;
}
