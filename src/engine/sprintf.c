/* The integer, float, scientific, hex and string field writers used by vsnprintf. */

#include <string.h>
#include <stdarg.h>


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
    length = strlen(pString);
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

int vsnprintf(char *pBuffer, int size, const char *pFormat, va_list args)
{
    char *pOut = pBuffer;
    char *pEnd = pBuffer + (size - 1);
    char c;
    int leftAlign;
    int width;
    int precision;
    int alt;
    int caseOffset;
    char pad;

    if (pBuffer == NULL || size == 0 || pFormat == NULL) {
        return -1;
    }
    c = *pFormat++;
    while (c != 0 && pOut < pEnd) {
        leftAlign = 0;
        if (c == '%') {
            c = *pFormat++;
            alt = 0;
            width = 0;
            precision = -1;
            pad = ' ';
            if (c == '-') {
                leftAlign = 1;
                c = *pFormat++;
            }
            if (c == '0') {
                pad = '0';
                c = *pFormat++;
            }
            while ((unsigned int)(c - '0') <= 9) {
                width = width * 10 + c - '0';
                c = *pFormat++;
            }
            if (c == '.') {
                c = *pFormat++;
            }
            if (c == 'l') {
                c = *pFormat++;
            }
            if ((unsigned char)(c - '0') <= 9) {
                precision = c - '0';
                c = *pFormat++;
                while ((unsigned int)(c - '0') <= 9) {
                    precision = precision * 10 + c - '0';
                    c = *pFormat++;
                }
            }
            switch (c) {
            case 'h':
            case 'L':
            case 'l':
                c = *pFormat++;
                break;
            }
            caseOffset = 0;
            if (c >= 'A' && c <= 'Z') {
                caseOffset = 'A' - 'a';
            }
            switch (c) {
            case 'c':
                *pOut++ = va_arg(args, int);
                break;
            case 's': {
                const char *pString = va_arg(args, const char *);
                if (pString != NULL) {
                    pOut = fn_801C27D0(pString, pOut, pEnd, width, precision, leftAlign);
                } else {
                    pOut = fn_801C27D0("(null)", pOut, pEnd, width, precision, leftAlign);
                }
                break;
            }
            case 'u':
                alt = 1;
            case 'd':
            case 'i':
                pOut = fn_801C20F0(va_arg(args, int), pOut, pEnd, pad, width, !alt);
                break;
            case 'f':
                pOut = fn_801C21D0(va_arg(args, double), pOut, pEnd, width, precision);
                break;
            case 'g':
            case 'G':
                alt = 1;
            case 'e':
            case 'E':
                pOut = fn_801C2428(va_arg(args, double), pOut, pEnd, width, precision, caseOffset, !alt);
                break;
            case 'x':
            case 'X':
            case 'p':
                pOut = fn_801C2728(va_arg(args, unsigned int), pOut, pEnd, width, pad, caseOffset);
                break;
            default:
                if (c != 0) {
                    *pOut++ = c;
                }
                break;
            }
        } else if (c != 0) {
            *pOut++ = c;
        }
        c = *pFormat++;
    }
    *pOut = 0;
    return pOut - pBuffer;
}

int snprintf(char *pBuffer, int size, const char *pFormat, ...)
{
    va_list args;

    va_start(args, pFormat);
    return vsnprintf(pBuffer, size, pFormat, args);
}

int sprintf(char *pBuffer, const char *pFormat, ...)
{
    va_list args;

    va_start(args, pFormat);
    return vsnprintf(pBuffer, 2048, pFormat, args);
}
