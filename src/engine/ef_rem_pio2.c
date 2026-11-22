/* Reduce single-precision angles for the sine, cosine and tangent wrappers. */
/* ef_rem_pio2.c -- float version of e_rem_pio2.c
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include <math.h>
#include "engine/float_angle_reduction.h"

typedef union FloatAngleBits_t {
    float value;
    int word;
} FloatAngleBits_t;

#define GET_FLOAT_WORD(out, x) do { \
    FloatAngleBits_t bits; \
    bits.value = (x); \
    (out) = bits.word; \
} while (0)

#define SET_FLOAT_WORD(out, x) do { \
    FloatAngleBits_t bits; \
    bits.word = (x); \
    (out) = bits.value; \
} while (0)

static const int _AngleReduce_aiTwoOverPi[198] = {
    0xa2, 0xf9, 0x83, 0x6e, 0x4e, 0x44, 0x15, 0x29,
    0xfc, 0x27, 0x57, 0xd1, 0xf5, 0x34, 0xdd, 0xc0,
    0xdb, 0x62, 0x95, 0x99, 0x3c, 0x43, 0x90, 0x41,
    0xfe, 0x51, 0x63, 0xab, 0xde, 0xbb, 0xc5, 0x61,
    0xb7, 0x24, 0x6e, 0x3a, 0x42, 0x4d, 0xd2, 0xe0,
    0x06, 0x49, 0x2e, 0xea, 0x09, 0xd1, 0x92, 0x1c,
    0xfe, 0x1d, 0xeb, 0x1c, 0xb1, 0x29, 0xa7, 0x3e,
    0xe8, 0x82, 0x35, 0xf5, 0x2e, 0xbb, 0x44, 0x84,
    0xe9, 0x9c, 0x70, 0x26, 0xb4, 0x5f, 0x7e, 0x41,
    0x39, 0x91, 0xd6, 0x39, 0x83, 0x53, 0x39, 0xf4,
    0x9c, 0x84, 0x5f, 0x8b, 0xbd, 0xf9, 0x28, 0x3b,
    0x1f, 0xf8, 0x97, 0xff, 0xde, 0x05, 0x98, 0x0f,
    0xef, 0x2f, 0x11, 0x8b, 0x5a, 0x0a, 0x6d, 0x1f,
    0x6d, 0x36, 0x7e, 0xcf, 0x27, 0xcb, 0x09, 0xb7,
    0x4f, 0x46, 0x3f, 0x66, 0x9e, 0x5f, 0xea, 0x2d,
    0x75, 0x27, 0xba, 0xc7, 0xeb, 0xe5, 0xf1, 0x7b,
    0x3d, 0x07, 0x39, 0xf7, 0x8a, 0x52, 0x92, 0xea,
    0x6b, 0xfb, 0x5f, 0xb1, 0x1f, 0x8d, 0x5d, 0x08,
    0x56, 0x03, 0x30, 0x46, 0xfc, 0x7b, 0x6b, 0xab,
    0xf0, 0xcf, 0xbc, 0x20, 0x9a, 0xf4, 0x36, 0x1d,
    0xa9, 0xe3, 0x91, 0x61, 0x5e, 0xe6, 0x1b, 0x08,
    0x65, 0x99, 0x85, 0x5f, 0x14, 0xa0, 0x68, 0x40,
    0x8d, 0xff, 0xd8, 0x80, 0x4d, 0x73, 0x27, 0x31,
    0x06, 0x06, 0x15, 0x56, 0xca, 0x73, 0xa8, 0xc9,
    0x60, 0xe2, 0x7b, 0xc0, 0x8c, 0x6b,
};

static const int _AngleReduce_aiMultipleWords[32] = {
    0x3fc90f00, 0x40490f00, 0x4096cb00, 0x40c90f00, 0x40fb5300, 0x4116cb00, 0x412fed00, 0x41490f00,
    0x41623100, 0x417b5300, 0x418a3a00, 0x4196cb00, 0x41a35c00, 0x41afed00, 0x41bc7e00, 0x41c90f00,
    0x41d5a000, 0x41e23100, 0x41eec200, 0x41fb5300, 0x4203f200, 0x420a3a00, 0x42108300, 0x4216cb00,
    0x421d1400, 0x42235c00, 0x4229a500, 0x422fed00, 0x42363600, 0x423c7e00, 0x4242c700, 0x42490f00,
};

static const float _AngleReduce_fZero = 0.0f;
static const float _AngleReduce_fHalf = 0.5f;
static const float _AngleReduce_fChunkBase = 256.0f;
static const float _AngleReduce_fTwoOverPi = 0.6366198062896729f;
static const float _AngleReduce_fPiOverTwoHigh = 1.5707855224609375f;
static const float _AngleReduce_fPiOverTwoTail = 1.0804334124259185e-05f;
static const float _AngleReduce_fPiOverTwoMid = 1.0804273188114166e-05f;
static const float _AngleReduce_fPiOverTwoMidTail = 6.07709993438732e-11f;
static const float _AngleReduce_fPiOverTwoLow = 6.077094383272197e-11f;
static const float _AngleReduce_fPiOverTwoLowTail = 6.123234262925839e-17f;

int __ieee754_rem_pio2f(float x, FloatAngleReduction_t *reduced)
{
    float high, correction, previous, multiple, part;
    float firstHead, secondHead, unsignedHead;
    float chunks[3];
    int signWord, magnitudeWord, multipleCount, exponent, remainderWord;
    int exponentLoss, index, chunkCount;

    GET_FLOAT_WORD(signWord, x);
    magnitudeWord = signWord & 0x7fffffff;
    if (magnitudeWord <= 0x3f490fd8) {
        reduced->head = x;
        reduced->tail = _AngleReduce_fZero;
        return 0;
    }

    /* Use an extra split close to pi/2, where subtraction loses leading bits. */
    if (magnitudeWord <= 0x4016cbe3) {
        if (signWord > 0) {
            part = x - _AngleReduce_fPiOverTwoHigh;
            if ((magnitudeWord & 0xfffffff0) != 0x3fc90fd0) {
                float head = part - _AngleReduce_fPiOverTwoTail;
                reduced->head = head;
                reduced->tail = (part - head) - _AngleReduce_fPiOverTwoTail;
            } else {
                float head;
                part -= _AngleReduce_fPiOverTwoMid;
                head = part - _AngleReduce_fPiOverTwoMidTail;
                reduced->head = head;
                reduced->tail = (part - head) - _AngleReduce_fPiOverTwoMidTail;
            }
            return 1;
        }
        part = x + _AngleReduce_fPiOverTwoHigh;
        if ((magnitudeWord & 0xfffffff0) != 0x3fc90fd0) {
            float head = part + _AngleReduce_fPiOverTwoTail;
            reduced->head = head;
            reduced->tail = (part - head) + _AngleReduce_fPiOverTwoTail;
        } else {
            float head;
            part += _AngleReduce_fPiOverTwoMid;
            head = part + _AngleReduce_fPiOverTwoMidTail;
            reduced->head = head;
            reduced->tail = (part - head) + _AngleReduce_fPiOverTwoMidTail;
        }
        return -1;
    }

    /* Refine the subtraction only when the first remainder loses precision. */
    if (magnitudeWord <= 0x43490f80) {
        previous = fabsf(x);
        multipleCount = (int)(previous * _AngleReduce_fTwoOverPi + _AngleReduce_fHalf);
        multiple = (float)multipleCount;
        high = previous - multiple * _AngleReduce_fPiOverTwoHigh;
        correction = multiple * _AngleReduce_fPiOverTwoTail;
        if (multipleCount < 32 &&
            (magnitudeWord & 0xffffff00) != _AngleReduce_aiMultipleWords[multipleCount - 1]) {
            reduced->head = high - correction;
        } else {
            int inputExponent = magnitudeWord >> 23;
            firstHead = high - correction;
            reduced->head = firstHead;
            GET_FLOAT_WORD(remainderWord, firstHead);
            exponentLoss = inputExponent - ((remainderWord >> 23) & 0xff);
            if (exponentLoss > 8) {
                previous = high;
                correction = multiple * _AngleReduce_fPiOverTwoMid;
                high = previous - correction;
                correction = multiple * _AngleReduce_fPiOverTwoMidTail - ((previous - high) - correction);
                secondHead = high - correction;
                reduced->head = secondHead;
                GET_FLOAT_WORD(remainderWord, secondHead);
                exponentLoss = inputExponent - ((remainderWord >> 23) & 0xff);
                if (exponentLoss > 25) {
                    previous = high;
                    correction = multiple * _AngleReduce_fPiOverTwoLow;
                    high = previous - correction;
                    correction = multiple * _AngleReduce_fPiOverTwoLowTail - ((previous - high) - correction);
                    reduced->head = high - correction;
                }
            }
        }
        unsignedHead = reduced->head;
        reduced->tail = (high - unsignedHead) - correction;
        if (signWord < 0) {
            reduced->head = -unsignedHead;
            reduced->tail = -reduced->tail;
            return -multipleCount;
        }
        return multipleCount;
    }

    if (magnitudeWord >= 0x7f800000) {
        reduced->head = reduced->tail = x - x;
        return 0;
    }

    /* Express the magnitude as base-256 digits before calling the large reducer. */
    exponent = (magnitudeWord >> 23) - 134;
    SET_FLOAT_WORD(part, magnitudeWord - (exponent << 23));
    for (index = 0; index < 2; index++) {
        chunks[index] = (float)(int)part;
        part = (part - chunks[index]) * _AngleReduce_fChunkBase;
    }
    chunks[2] = part;
    chunkCount = 3;
    while (chunks[chunkCount - 1] == _AngleReduce_fZero) {
        chunkCount--;
    }
    multipleCount = __kernel_rem_pio2f(chunks, reduced, exponent, chunkCount, 2, _AngleReduce_aiTwoOverPi);
    if (signWord < 0) {
        reduced->head = -reduced->head;
        reduced->tail = -reduced->tail;
        return -multipleCount;
    }
    return multipleCount;
}
