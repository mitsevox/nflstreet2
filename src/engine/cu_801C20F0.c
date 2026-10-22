/* The integer, float, scientific, hex and string field writers used by vsnprintf. */

#include "engine/cu_801C2EB4.h"


static char *fn_801C20F0(unsigned int value, char *pOut, char *pEnd, char pad, int width, int isSigned)
{
    char buf[16];
    int count = 0;
    int negative = 0;
    int i;

    if (isSigned) {
        negative = (int)value < 0;
        if (negative) {
            value = -value;
        }
    }
    do {
        buf[count++] = '0' + value - value / 10 * 10;
        value /= 10;
    } while (value);
    if (width) {
        for (i = width - negative - count; i > 0 && pOut < pEnd; i--) {
            *pOut++ = pad;
        }
    }
    if (negative) {
        buf[count++] = '-';
    }
    while (--count >= 0 && pOut < pEnd) {
        *pOut++ = buf[count];
    }
    return pOut;
}

static char *fn_801C21D0(float value, char *pOut, char *pEnd, int width, int precision)
{
    char buf[64];
    int count = 0;
    int negative;
    int pad;
    int digit;
    int i;
    float round;
    float fraction;
    float next;

    if (precision < 0) {
        precision = 6;
    }
    negative = value < 0.0f;
    if (negative) {
        value = -value;
    }
    round = 0.5f;
    for (i = precision; i > 0; i--) {
        round *= 0.1f;
    }
    value += round;
    fraction = value - (float)(int)value;
    do {
        next = value * 0.1f;
        buf[count++] = (int)(value - (float)((int)next * 10)) + '0';
        value = next;
    } while (value >= 1.0f);
    if (negative) {
        buf[count++] = '-';
    }
    if (width) {
        pad = (precision ? width - 1 : width) - (precision + count);
        for (; pad > 0 && pOut < pEnd; pad--) {
            *pOut++ = ' ';
        }
    }
    while (--count >= 0 && pOut < pEnd) {
        *pOut++ = buf[count];
    }
    if (precision && pOut < pEnd) {
        *pOut++ = '.';
        do {
            fraction *= 10.0f;
            digit = (int)fraction;
            *pOut++ = digit + '0';
            fraction -= (float)digit;
        } while (--precision && pOut < pEnd);
    }
    return pOut;
}

static char *fn_801C2428(float value, char *pOut, char *pEnd, int width, int precision, int caseOffset, int isExponent)
{
    int exponent = 0;
    int negative;
    int expNegative;
    int digit;
    int length;
    float mantissa;

    if (precision < 0) {
        precision = 6;
    }
    negative = value < 0.0f;
    mantissa = value;
    if (negative) {
        mantissa = -mantissa;
    }
    if (mantissa != 0.0f) {
        if (!(mantissa < 10.0f)) {
            do {
                mantissa *= 0.1f;
                exponent++;
            } while (mantissa >= 10.0f);
        }
        if (!(mantissa >= 1.0f)) {
            do {
                mantissa *= 10.0f;
                exponent--;
            } while (mantissa < 1.0f);
        }
    }
    if (!isExponent && exponent >= -4 && exponent < precision) {
        return fn_801C21D0(value, pOut, pEnd, width, precision);
    }
    expNegative = exponent < 0;
    if (expNegative) {
        exponent = -exponent;
    }
    if (precision) {
        length = 6 + negative + precision;
    } else {
        length = negative + 5;
    }
    width -= length;
    while (width > 0 && pOut < pEnd) {
        *pOut++ = ' ';
    }
    if (negative) {
        *pOut++ = '-';
    }
    digit = (int)mantissa;
    *pOut++ = digit + '0';
    if (precision && pOut < pEnd) {
        *pOut++ = '.';
        mantissa -= (float)digit;
        do {
            mantissa *= 10.0f;
            digit = (int)mantissa;
            *pOut++ = digit + '0';
            mantissa -= (float)digit;
        } while (--precision && pOut < pEnd);
    }
    if (pOut + 4 < pEnd) {
        *pOut++ = 'e' + caseOffset;
        *pOut++ = expNegative ? '-' : '+';
        *pOut++ = exponent / 10 + '0';
        *pOut++ = exponent % 10 + '0';
    } else if (pOut < pEnd) {
        *pOut++ = 'e' + caseOffset;
        if (pOut < pEnd) {
            *pOut++ = expNegative ? '-' : '+';
            if (pOut < pEnd) {
                *pOut++ = exponent / 10 + '0';
                if (pOut < pEnd) {
                    *pOut++ = exponent % 10 + '0';
                }
            }
        }
    }
    return pOut;
}

static char *fn_801C2728(unsigned int value, char *pOut, char *pEnd, int width, char pad, int caseOffset)
{
    char buf[16];
    int count = 0;
    char c;
    int i;

    do {
        c = (value & 0xF) | '0';
        if (c > '9') {
            c += 'a' - '9' - 1 + caseOffset;
        }
        buf[count++] = c;
        value >>= 4;
    } while (value);
    if (width) {
        for (i = width - count; i > 0 && pOut < pEnd; i--) {
            *pOut++ = pad;
        }
    }
    while (--count >= 0 && pOut < pEnd) {
        *pOut++ = buf[count];
    }
    return pOut;
}

static char *fn_801C27D0(const char *pString, char *pOut, char *pEnd, int width, int precision, int leftAlign)
{
    int count = 0;
    int length;

    width = width < 0 ? -width : width;
    length = fn_801C3180(pString);
    if (!leftAlign) {
        for (; count < width - length; count++) {
            *pOut++ = ' ';
        }
    }
    while (*pString) {
        *pOut++ = *pString++;
        count++;
        if (pOut == pEnd) {
            break;
        }
    }
    if (leftAlign == 1) {
        for (; count < width; count++) {
            *pOut++ = ' ';
        }
    }
    return pOut;
}
