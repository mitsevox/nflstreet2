#include "game/Frame_8019D3B8.h"

extern "C" {
void fn_801C1FBC(void *destination, void *source, unsigned int size);
extern float lbl_802F26FC[];
extern int lbl_802F2708[];

void fn_8019DF38(int *output, short *input, int index, Record_8019D8AC *context);
}

extern "C" void fn_8019D994(Pose_80041930 *pose, BlendEntry_8019EDDC *entry, int mode, float scale, Record_8019D8AC *context, int unused)
{
    Frame_8019D3B8 frame;
    int special = entry->mUnknown8 & 4;
    short *samples;
    if (context) {
        samples = pose->mUnknown48;
        short *encodedSamples = fn_8019D3B8(&frame, entry->mpUnknown40);
        fn_8019D514(samples, encodedSamples, context, 1);
    } else {
        samples = fn_8019D3B8(&frame, entry->mpUnknown40);
    }
    unsigned int count = frame.count;
    if (count > 64)
        count = 64;
    if (special) {
        pose->mUnknown8[0] = 0.0f;
        pose->mUnknown8[2] = 0.0f;
        pose->mUnknown8[1] = frame.word6 * 0.000244140625f;
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            entry->mUnknown24[0] = z * 0.000244140625f;
            entry->mUnknown24[1] = -(float)x * 0.000244140625f;
        } else {
            entry->mUnknown24[0] = frame.word8 * 0.000244140625f;
            entry->mUnknown24[1] = -(float)frame.word4 * 0.000244140625f;
        }
    } else {
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            pose->mUnknown8[0] = x * 0.000244140625f;
            pose->mUnknown8[2] = z * 0.000244140625f;
        } else {
            pose->mUnknown8[0] = frame.word4 * 0.000244140625f;
            pose->mUnknown8[2] = frame.word8 * 0.000244140625f;
        }
        pose->mUnknown8[1] = frame.word6 * 0.000244140625f;
        pose->mUnknown32 = frame.word2 << 8;
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
        pose->mUnknown20[0] = frame.vector10[0] * 0.0009765625f;
        pose->mUnknown20[1] = frame.vector10[1] * 0.0009765625f;
        pose->mUnknown20[2] = frame.vector10[2] * 0.0009765625f;
        fn_8019D8AC(pose->mUnknown36, samples, 19, context);
    } else if (mode == 2) {
        pose->mUnknown20[0] = frame.vectorA[0] * 0.0009765625f;
        pose->mUnknown20[1] = frame.vectorA[1] * 0.0009765625f;
        pose->mUnknown20[2] = frame.vectorA[2] * 0.0009765625f;
        fn_8019D8AC(pose->mUnknown36, samples, 25, context);
    } else {
        pose->mUnknown20[0] = lbl_802F26FC[0];
        pose->mUnknown20[1] = lbl_802F26FC[1];
        pose->mUnknown20[2] = lbl_802F26FC[2];
        pose->mUnknown36[0] = lbl_802F2708[0] << 8;
        pose->mUnknown36[1] = -lbl_802F2708[1] << 8;
        pose->mUnknown36[2] = -lbl_802F2708[2] << 8;
    }
    if (!context)
        fn_8019D83C(pose->mUnknown48, samples, count);
    pose->mUnknown8[0] = -pose->mUnknown8[0];
    pose->mUnknown20[0] = -pose->mUnknown20[0];
    Pair_8019D800 *pair = &context->mUnknown4;
    entry->mUnknown12[0] = fn_8019D800(samples[0], 0, 0, context, pair) << 8;
    entry->mUnknown12[1] = -frame.word2 << 8;
    entry->mUnknown12[2] = -fn_8019D800(samples[2], 0, 2, context, pair) << 8;
}

extern "C" void fn_8019DF38(int *output, short *input, int index, Record_8019D8AC *context)
{
    if (context) {
        output[0] = fn_8019D800(input[index * 3], index, 0, context, &context->mUnknown4) << 8;
        output[1] = fn_8019D800(input[index * 3 + 1], index, 1, context, &context->mUnknown4) << 8;
        output[2] = fn_8019D800(input[index * 3 + 2], index, 2, context, &context->mUnknown4) << 8;
    } else {
        output[0] = input[index * 3] << 8;
        output[1] = input[index * 3 + 1] << 8;
        output[2] = input[index * 3 + 2] << 8;
    }
}

extern "C" void fn_8019E00C(Pose_80041930 *pose, BlendEntry_8019EDDC *entry, int mode, float scale, Record_8019D8AC *context, int unused)
{
    Frame_8019D3B8 frame;
    int special = entry->mUnknown8 & 4;
    short *samples;
    if (context) {
        samples = pose->mUnknown48;
        short *encodedSamples = fn_8019D3B8(&frame, entry->mpUnknown40);
        fn_8019D514(samples, encodedSamples, context, 0);
        samples = pose->mUnknown48;
    } else {
        samples = fn_8019D3B8(&frame, entry->mpUnknown40);
    }
    unsigned int count = frame.count;
    if (count > 64)
        count = 64;
    if (special) {
        pose->mUnknown8[0] = 0.0f;
        pose->mUnknown8[2] = 0.0f;
        pose->mUnknown8[1] = frame.word6 * 0.000244140625f;
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            entry->mUnknown24[0] = z * 0.000244140625f;
            entry->mUnknown24[1] = x * 0.000244140625f;
        } else {
            entry->mUnknown24[0] = frame.word8 * 0.000244140625f;
            entry->mUnknown24[1] = frame.word4 * 0.000244140625f;
        }
    } else {
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            pose->mUnknown8[0] = x * 0.000244140625f;
            pose->mUnknown8[2] = z * 0.000244140625f;
        } else {
            pose->mUnknown8[0] = frame.word4 * 0.000244140625f;
            pose->mUnknown8[2] = frame.word8 * 0.000244140625f;
        }
        pose->mUnknown8[1] = frame.word6 * 0.000244140625f;
        pose->mUnknown32 = frame.word2 << 8;
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
        pose->mUnknown20[0] = frame.vectorA[0] * 0.0009765625f;
        pose->mUnknown20[1] = frame.vectorA[1] * 0.0009765625f;
        pose->mUnknown20[2] = frame.vectorA[2] * 0.0009765625f;
        fn_8019DF38(pose->mUnknown36, samples, 25, context);
    } else if (mode == 2) {
        pose->mUnknown20[0] = frame.vector10[0] * 0.0009765625f;
        pose->mUnknown20[1] = frame.vector10[1] * 0.0009765625f;
        pose->mUnknown20[2] = frame.vector10[2] * 0.0009765625f;
        fn_8019DF38(pose->mUnknown36, samples, 19, context);
    } else {
        pose->mUnknown20[0] = lbl_802F26FC[0];
        pose->mUnknown20[1] = lbl_802F26FC[1];
        pose->mUnknown20[2] = lbl_802F26FC[2];
        pose->mUnknown36[0] = lbl_802F2708[0] << 8;
        pose->mUnknown36[1] = lbl_802F2708[1] << 8;
        pose->mUnknown36[2] = lbl_802F2708[2] << 8;
    }
    if (!context)
        fn_801C1FBC(pose->mUnknown48, samples, count * 6);
    Pair_8019D800 *pair = &context->mUnknown4;
    entry->mUnknown12[0] = fn_8019D800(samples[0], 0, 0, context, pair) << 8;
    entry->mUnknown12[1] = frame.word2 << 8;
    entry->mUnknown12[2] = fn_8019D800(samples[2], 0, 2, context, pair) << 8;
}
