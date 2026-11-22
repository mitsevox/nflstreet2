/* Reduces large single-precision angles for the game's trigonometric functions. */
/* kf_rem_pio2.c -- float version of k_rem_pio2.c
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
#include "engine/scalbnf.h"

typedef struct FloatAngleReductionTriple_t {
    FloatAngleReduction_t parts;
    float third;
} FloatAngleReductionTriple_t;

static const int _AngleReduction_aiInitialTerms[] = {4, 7, 9};

static const float _AngleReduction_afPiOverTwo[] = {
    1.5703125000e+00f, 4.5776367188e-04f, 2.5987625122e-05f,
    7.5437128544e-08f, 6.0026650317e-11f, 7.3896444519e-13f,
    5.3845816694e-15f, 5.6378512969e-18f, 8.3009228831e-20f,
    3.2756352257e-22f, 6.3331015649e-25f,
};

static const float _AngleReduction_fZero = 0.0f;
static const float _AngleReduction_fOne = 1.0f;
static const float _AngleReduction_fRadix = 256.0f;
static const float _AngleReduction_fInverseRadix = 0.00390625f;

/* Input chunks hold eight-bit digits of the normalized angle.
 * Precision 0 writes a float; precision 1 or 2 writes a reduction pair.
 */
extern "C" int __kernel_rem_pio2f(float *inputChunks, void *result, int chunkExponent,
                                 int chunkCount, int precision, const int *twoOverPi)
{
    int terms, inputLast, piIndex, piTerms, initialTerms, carry, multiple;
    int productDigits[20], i, j, k, coefficientLast, exponent, halfFlag;
    float fraction, sum, coefficients[20], remainder[20], products[20];

    initialTerms = _AngleReduction_aiInitialTerms[precision];
    piTerms = initialTerms;

    inputLast = chunkCount - 1;
    piIndex = (chunkExponent - 3) / 8;
    if (piIndex < 0) {
        piIndex = 0;
    }
    exponent = chunkExponent - 8 * (piIndex + 1);

    /* Align the reciprocal digits with the angle. */
    j = piIndex - inputLast;
    coefficientLast = inputLast + initialTerms;
    for (i = 0; i <= coefficientLast; i++, j++) {
        coefficients[i] = (j < 0) ? _AngleReduction_fZero : (float)twoOverPi[j];
    }

    for (i = 0; i <= initialTerms; i++) {
        for (j = 0, sum = 0.0f; j <= inputLast; j++) {
            sum += inputChunks[j] * coefficients[inputLast + i - j];
        }
        products[i] = sum;
    }

    terms = initialTerms;
recompute:
    /* Distill the convolution into base-256 digits, least significant first. */
    for (i = 0, j = terms, fraction = products[terms]; j > 0; i++, j--) {
        sum = (float)(int)(_AngleReduction_fInverseRadix * fraction);
        productDigits[i] = (int)(fraction - _AngleReduction_fRadix * sum);
        fraction = products[j - 1] + sum;
    }

    fraction = scalbnf(fraction, exponent);
    fraction -= 8.0f * floorf(fraction * 0.125f);
    multiple = (int)fraction;
    fraction -= (float)multiple;
    halfFlag = 0;
    if (exponent > 0) {
        i = productDigits[terms - 1] >> (8 - exponent);
        multiple += i;
        productDigits[terms - 1] -= i << (8 - exponent);
        halfFlag = productDigits[terms - 1] >> (7 - exponent);
    } else if (exponent == 0) {
        halfFlag = productDigits[terms - 1] >> 8;
    } else if (fraction >= 0.5f) {
        halfFlag = 2;
    }

    /* Select the nearest multiple and complement the fraction when it rounds up. */
    if (halfFlag > 0) {
        multiple += 1;
        carry = 0;
        for (i = 0; i < terms; i++) {
            j = productDigits[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    productDigits[i] = 0x100 - j;
                }
            } else {
                productDigits[i] = 0xff - j;
            }
        }
        if (exponent > 0) {
            switch (exponent) {
                case 1:
                    productDigits[terms - 1] &= 0x7f;
                    break;
                case 2:
                    productDigits[terms - 1] &= 0x3f;
                    break;
            }
        }
        if (halfFlag == 2) {
            fraction = _AngleReduction_fOne - fraction;
            if (carry != 0) {
                fraction -= scalbnf(_AngleReduction_fOne, exponent);
            }
        }
    }

    /* Pull more reciprocal digits when cancellation removes all available high terms. */
    if (fraction == _AngleReduction_fZero) {
        j = 0;
        for (i = terms - 1; i >= initialTerms; i--) {
            j |= productDigits[i];
        }
        if (j == 0) {
            for (k = 1; productDigits[initialTerms - k] == 0; k++) {
            }
            for (i = terms + 1; i <= terms + k; i++) {
                coefficients[inputLast + i] = (float)twoOverPi[piIndex + i];
                for (j = 0, sum = 0.0f; j <= inputLast; j++) {
                    sum += inputChunks[j] * coefficients[inputLast + i - j];
                }
                products[i] = sum;
            }
            terms += k;
            goto recompute;
        }
    }

    if (fraction == 0.0f) {
        terms -= 1;
        exponent -= 8;
        while (productDigits[terms] == 0) {
            terms--;
            exponent -= 8;
        }
    } else {
        fraction = scalbnf(fraction, -exponent);
        if (fraction >= _AngleReduction_fRadix) {
            sum = (float)(int)(_AngleReduction_fInverseRadix * fraction);
            productDigits[terms] = (int)(fraction - _AngleReduction_fRadix * sum);
            terms += 1;
            exponent += 8;
            productDigits[terms] = (int)sum;
        } else {
            productDigits[terms] = (int)fraction;
        }
    }

    /* Rescale the digits and reconstruct the signed remainder in radians. */
    sum = scalbnf(_AngleReduction_fOne, exponent);
    for (i = terms; i >= 0; i--) {
        products[i] = sum * (float)productDigits[i];
        sum *= _AngleReduction_fInverseRadix;
    }
    for (i = terms; i >= 0; i--) {
        for (sum = 0.0f, k = 0; k <= piTerms && k <= terms - i; k++) {
            sum += _AngleReduction_afPiOverTwo[k] * products[i + k];
        }
        remainder[terms - i] = sum;
    }

    switch (precision) {
        case 0: {
            float *output = (float *)result;
            sum = 0.0f;
            for (i = terms; i >= 0; i--) {
                sum += remainder[i];
            }
            output[0] = (halfFlag == 0) ? sum : -sum;
            break;
        }
        case 1:
        case 2: {
            FloatAngleReduction_t *output = (FloatAngleReduction_t *)result;
            sum = 0.0f;
            for (i = terms; i >= 0; i--) {
                sum += remainder[i];
            }
            output->head = sum;
            if (halfFlag != 0) {
                output->head = -sum;
            }
            sum = remainder[0] - sum;
            for (i = 1; i <= terms; i++) {
                sum += remainder[i];
            }
            output->tail = (halfFlag == 0) ? sum : -sum;
            break;
        }
        case 3: {
            FloatAngleReductionTriple_t *output = (FloatAngleReductionTriple_t *)result;
            for (i = terms; i > 0; i--) {
                sum = remainder[i - 1] + remainder[i];
                remainder[i] += remainder[i - 1] - sum;
                remainder[i - 1] = sum;
            }
            for (i = terms; i > 1; i--) {
                sum = remainder[i - 1] + remainder[i];
                remainder[i] += remainder[i - 1] - sum;
                remainder[i - 1] = sum;
            }
            for (sum = 0.0f, i = terms; i >= 2; i--) {
                sum += remainder[i];
            }
            if (halfFlag == 0) {
                output->parts.head = remainder[0];
                output->parts.tail = remainder[1];
                output->third = sum;
            } else {
                output->parts.head = -remainder[0];
                output->parts.tail = -remainder[1];
                output->third = -sum;
            }
            break;
        }
    }
    return multiple & 7;
}
