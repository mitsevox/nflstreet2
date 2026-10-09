#include "game/Record_8019D8AC.h"

struct Frame_8019D3B8 {
    unsigned char count;
    unsigned char flags;
    short word2;
    short word4;
    short word6;
    short word8;
    short vectorA[3];
    short vector10[3];
};

struct State_8019D994 {
    unsigned char unknown0[8];
    float vector8[3];
    float vector14[3];
    int word20;
    int vector24[3];
    short *samples;
};

struct Input_8019D994 {
    unsigned char unknown0[8];
    unsigned char flags;
    unsigned char unknown9[3];
    int vectorC[3];
    float planar18[2];
    unsigned char unknown20[8];
    void *encoded;
};

extern "C" {
short *fn_8019D3B8(Frame_8019D3B8 *header, void *encoded);
void fn_8019D514(short *destination, short *source, Record_8019D8AC *context, int mirrored);
void fn_801C1FBC(void *destination, void *source, unsigned int size);
extern float lbl_802F26FC[];
extern int lbl_802F2708[];

void fn_8019DF38(int *output, short *input, int index, Record_8019D8AC *context);
}

extern "C" void fn_8019D994(State_8019D994 *state, Input_8019D994 *input, int mode, Record_8019D8AC *context, float scale, int unused)
{
    Frame_8019D3B8 frame;
    int special = input->flags & 4;
    short *samples;
    if (context) {
        samples = state->samples;
        short *encodedSamples = fn_8019D3B8(&frame, input->encoded);
        fn_8019D514(samples, encodedSamples, context, 1);
    } else {
        samples = fn_8019D3B8(&frame, input->encoded);
    }
    unsigned int count = frame.count;
    if (count > 64)
        count = 64;
    if (special) {
        state->vector8[0] = 0.0f;
        state->vector8[2] = 0.0f;
        state->vector8[1] = frame.word6 * 0.000244140625f;
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            input->planar18[0] = z * 0.000244140625f;
            input->planar18[1] = -(float)x * 0.000244140625f;
        } else {
            input->planar18[0] = frame.word8 * 0.000244140625f;
            input->planar18[1] = -(float)frame.word4 * 0.000244140625f;
        }
    } else {
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            state->vector8[0] = x * 0.000244140625f;
            state->vector8[2] = z * 0.000244140625f;
        } else {
            state->vector8[0] = frame.word4 * 0.000244140625f;
            state->vector8[2] = frame.word8 * 0.000244140625f;
        }
        state->vector8[1] = frame.word6 * 0.000244140625f;
        state->word20 = frame.word2 << 8;
    }
    float height = state->vector8[1];
    if (scale != 1.0f && height > 1.1593530178070068f)
        height = (height - 1.1593530178070068f) * scale + 1.1593530178070068f;
    state->vector8[1] = height;
    if (!mode) {
        if (input->flags & 0x10)
            mode = 1;
        else if (input->flags & 0x20)
            mode = 2;
    }
    if (mode == 1) {
        state->vector14[0] = frame.vector10[0] * 0.0009765625f;
        state->vector14[1] = frame.vector10[1] * 0.0009765625f;
        state->vector14[2] = frame.vector10[2] * 0.0009765625f;
        fn_8019D8AC(state->vector24, samples, 19, context);
    } else if (mode == 2) {
        state->vector14[0] = frame.vectorA[0] * 0.0009765625f;
        state->vector14[1] = frame.vectorA[1] * 0.0009765625f;
        state->vector14[2] = frame.vectorA[2] * 0.0009765625f;
        fn_8019D8AC(state->vector24, samples, 25, context);
    } else {
        state->vector14[0] = lbl_802F26FC[0];
        state->vector14[1] = lbl_802F26FC[1];
        state->vector14[2] = lbl_802F26FC[2];
        state->vector24[0] = lbl_802F2708[0] << 8;
        state->vector24[1] = -lbl_802F2708[1] << 8;
        state->vector24[2] = -lbl_802F2708[2] << 8;
    }
    if (!context)
        fn_8019D83C(state->samples, samples, count);
    state->vector8[0] = -state->vector8[0];
    state->vector14[0] = -state->vector14[0];
    Pair_8019D800 *pair = &context->mUnknown4;
    input->vectorC[0] = fn_8019D800(samples[0], 0, 0, context, pair) << 8;
    input->vectorC[1] = -frame.word2 << 8;
    input->vectorC[2] = -fn_8019D800(samples[2], 0, 2, context, pair) << 8;
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

extern "C" void fn_8019E00C(State_8019D994 *state, Input_8019D994 *input, int mode, Record_8019D8AC *context, float scale, int unused)
{
    Frame_8019D3B8 frame;
    int special = input->flags & 4;
    short *samples;
    if (context) {
        samples = state->samples;
        short *encodedSamples = fn_8019D3B8(&frame, input->encoded);
        fn_8019D514(samples, encodedSamples, context, 0);
        samples = state->samples;
    } else {
        samples = fn_8019D3B8(&frame, input->encoded);
    }
    unsigned int count = frame.count;
    if (count > 64)
        count = 64;
    if (special) {
        state->vector8[0] = 0.0f;
        state->vector8[2] = 0.0f;
        state->vector8[1] = frame.word6 * 0.000244140625f;
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            input->planar18[0] = z * 0.000244140625f;
            input->planar18[1] = x * 0.000244140625f;
        } else {
            input->planar18[0] = frame.word8 * 0.000244140625f;
            input->planar18[1] = frame.word4 * 0.000244140625f;
        }
    } else {
        if (frame.flags & 0x80) {
            int x = (unsigned short)frame.word4 | ((frame.flags & 3) << 16);
            int z = (unsigned short)frame.word8 | ((frame.flags & 0x18) << 13);
            if ((frame.flags & 4) && x)
                x |= 0xFFFC0000;
            if ((frame.flags & 0x20) && z)
                z |= 0xFFFC0000;
            state->vector8[0] = x * 0.000244140625f;
            state->vector8[2] = z * 0.000244140625f;
        } else {
            state->vector8[0] = frame.word4 * 0.000244140625f;
            state->vector8[2] = frame.word8 * 0.000244140625f;
        }
        state->vector8[1] = frame.word6 * 0.000244140625f;
        state->word20 = frame.word2 << 8;
    }
    float height = state->vector8[1];
    if (scale != 1.0f && height > 1.1593530178070068f)
        height = (height - 1.1593530178070068f) * scale + 1.1593530178070068f;
    state->vector8[1] = height;
    if (!mode) {
        if (input->flags & 0x10)
            mode = 1;
        else if (input->flags & 0x20)
            mode = 2;
    }
    if (mode == 1) {
        state->vector14[0] = frame.vectorA[0] * 0.0009765625f;
        state->vector14[1] = frame.vectorA[1] * 0.0009765625f;
        state->vector14[2] = frame.vectorA[2] * 0.0009765625f;
        fn_8019DF38(state->vector24, samples, 25, context);
    } else if (mode == 2) {
        state->vector14[0] = frame.vector10[0] * 0.0009765625f;
        state->vector14[1] = frame.vector10[1] * 0.0009765625f;
        state->vector14[2] = frame.vector10[2] * 0.0009765625f;
        fn_8019DF38(state->vector24, samples, 19, context);
    } else {
        state->vector14[0] = lbl_802F26FC[0];
        state->vector14[1] = lbl_802F26FC[1];
        state->vector14[2] = lbl_802F26FC[2];
        state->vector24[0] = lbl_802F2708[0] << 8;
        state->vector24[1] = lbl_802F2708[1] << 8;
        state->vector24[2] = lbl_802F2708[2] << 8;
    }
    if (!context)
        fn_801C1FBC(state->samples, samples, count * 6);
    Pair_8019D800 *pair = &context->mUnknown4;
    input->vectorC[0] = fn_8019D800(samples[0], 0, 0, context, pair) << 8;
    input->vectorC[1] = frame.word2 << 8;
    input->vectorC[2] = fn_8019D800(samples[2], 0, 2, context, pair) << 8;
}
