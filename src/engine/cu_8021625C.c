#include "engine/tmlib.h"

extern unsigned char lbl_802F9E98[];
extern float fn_80260428(float x, float y);

const unsigned char *fn_8021625C(const unsigned char *p, unsigned char *pOut)
{
    *pOut = '~';
    if (*p == '#') {
        int value;

        if (p[1] == 'x') {
            p += 2;
            value = 0;
            while (*p > '/') {
                value = (value << 4) | lbl_802F9E98[*p];
                p++;
            }
        } else {
            p++;
            value = 0;
            while ((unsigned char)(*p - '0') <= 9) {
                value = value * 10 + (*p & 0xF);
                p++;
            }
        }
        *pOut = value;
    } else if (p[0] == 'a' && p[1] == 'm' && p[2] == 'p') {
        *pOut = '&';
        p += 3;
    } else if (p[0] == 'a' && p[1] == 'p' && p[2] == 'o' && p[3] == 's') {
        *pOut = '\'';
        p += 4;
    } else if (p[0] == 'q' && p[1] == 'u' && p[2] == 'o' && p[3] == 't') {
        *pOut = '"';
        p += 4;
    } else if (p[0] == 'l' && p[1] == 't') {
        *pOut = '<';
        p += 2;
    } else if (p[0] == 'g' && p[1] == 't') {
        *pOut = '>';
        p += 2;
    }
    if (*p == ';') {
        p++;
    }
    return p;
}

const unsigned char *fn_802163F0(const unsigned char *p, const unsigned char *pName)
{
    const unsigned char *pValue = 0;

    if (p != 0 && *p == '<') {
        do {
            p++;
        } while (*p > ' ');
        for (;;) {
            unsigned char c;
            int i;

            while (*p != 0 && *p <= ' ') {
                p++;
            }
            i = 0;
            while (p[i] != 0 && p[i] == pName[i]) {
                i++;
            }
            if (pName[i] == 0) {
                p += i;
                while (*p != 0 && *p <= ' ') {
                    p++;
                }
                if (*p == '=') {
                    pValue = p + 1;
                    while (*pValue != 0 && *pValue <= ' ') {
                        pValue++;
                    }
                    break;
                }
            }
            while (*p != 0 && *p != '>' && *p != '=') {
                p++;
            }
            if (*p != '=') {
                break;
            }
            p++;
            while (*p != 0 && *p <= ' ') {
                p++;
            }
            c = *p;
            if (c == '"' || c == '\'') {
                p++;
                while (*p != 0 && *p != c) {
                    p++;
                }
                if (*p == c) {
                    p++;
                }
            } else {
                while (*p != 0 && *p <= ' ') {
                    p++;
                }
            }
        }
    }
    return pValue;
}

const unsigned char *fn_8021658C(const unsigned char *p)
{
    if (p == 0 || *p != '<') {
        return 0;
    }
    if (p[1] == '?') {
        for (p += 2; *p != 0 && *p != '?' && p[1] != '>'; p++) {
        }
        if (*p != 0) {
            p += 2;
        }
    } else if (p[1] == '!') {
        int depth = 1;

        for (p++; *p != 0 && depth > 0; p++) {
            if (*p == '>') {
                depth--;
            }
            if (*p == '<') {
                depth++;
            }
        }
    } else {
        p++;
        while (*p != 0) {
            if (*p == '<') {
                if (p[1] != '/') {
                    break;
                }
                for (p++; *p != 0 && *p != '>'; p++) {
                }
                if (*p == '>') {
                    p++;
                }
            } else if (*p == '/' && p[1] == '>') {
                p += 2;
            } else {
                p++;
            }
        }
    }
    while (*p != 0 && *p <= ' ') {
        p++;
    }
    if (*p == 0) {
        p = 0;
    }
    return p;
}

const unsigned char *fn_802166F0(const unsigned char *p)
{
    if (p == 0 || *p != '<') {
        return 0;
    }
    if (p[1] == '?') {
        for (p += 2; *p != 0 && *p != '?' && p[1] != '>'; p++) {
        }
        if (*p != 0) {
            p += 2;
        }
    } else if (p[1] == '!') {
        int depth = 1;

        for (p++; *p != 0 && depth > 0; p++) {
            if (*p == '>') {
                depth--;
            }
            if (*p == '<') {
                depth++;
            }
        }
    } else {
        int depth = 1;

        for (p++; depth > 0 && *p != 0;) {
            if (*p == '<') {
                if (p[1] != '/') {
                    depth++;
                } else {
                    depth--;
                }
                do {
                    p++;
                } while (*p != 0 && *p != '>' && *p != '/');
                if (*p != '>') {
                    continue;
                }
            } else if (*p == '/' && p[1] == '>') {
                depth--;
            }
            p++;
        }
    }
    while (*p != 0 && *p <= ' ') {
        p++;
    }
    if (*p == 0) {
        p = 0;
    }
    return p;
}

const unsigned char *fn_80216E34(const unsigned char *pElem)
{
    const unsigned char *p;

    while (*pElem != 0 && *pElem != '<') {
        pElem++;
    }
    p = pElem;
    while ((p = fn_802166F0(p)) != 0) {
        int i;

        while (*p != 0 && *p != '<') {
            p++;
        }
        if (*p == 0 || (*p == '<' && p[1] == '/')) {
            p = 0;
            break;
        }
        for (i = 0; p[i] > ' ' && p[i] != '>' && pElem[i] > ' ' && pElem[i] != '>' && p[i] == pElem[i]; i++) {
        }
        if ((p[i] <= ' ' || p[i] == '>') && (pElem[i] <= ' ' || pElem[i] == '>')) {
            return p;
        }
    }
    return p;
}

int fn_80216F3C(const unsigned char *p, const unsigned char *pName, unsigned char *pDst, int maxLen, const unsigned char *pDefault)
{
    int n;

    if (pDst == 0 || maxLen <= 0) {
        return -1;
    }
    p = fn_802163F0(p, pName);
    if (p != 0) {
        unsigned char quote;

        while (*p != 0 && *p <= ' ') {
            p++;
        }
        if (*p == '"' || *p == '\'') {
            quote = *p;
            p++;
        } else {
            quote = 0;
        }
        for (n = 1; n < maxLen && *p != quote && *p != 0 && *p != '>'; n++) {
            if (*p == '&') {
                p = fn_8021625C(p + 1, pDst++);
            } else {
                *pDst++ = *p++;
            }
        }
        *pDst = 0;
    } else if (pDefault != 0) {
        for (n = 1; n < maxLen && *pDefault != 0; n++) {
            *pDst++ = *pDefault++;
        }
        *pDst = 0;
    } else {
        n = 0;
    }
    return n - 1;
}

int fn_80217070(const unsigned char *p, const unsigned char *pName, int def)
{
    int sign = 1;
    int value;

    p = fn_802163F0(p, pName);
    if (p == 0) {
        return def;
    }
    while (*p != 0 && *p <= ' ') {
        p++;
    }
    if (*p == '"' || *p == '\'') {
        p++;
    }
    if (*p == '+') {
        sign = 1;
        p++;
    }
    if (*p == '-') {
        sign = -1;
        p++;
    }
    value = 0;
    while (*p >= '0' && *p <= '9') {
        value = value * 10 + (*p & 0xF);
        p++;
    }
    if ((p[0] | 0x20) == 't' && (p[1] | 0x20) == 'r' && (p[2] | 0x20) == 'u' && (p[3] | 0x20) == 'e') {
        sign = 1;
        value = 1;
    }
    if ((p[0] | 0x20) == 'f' && (p[1] | 0x20) == 'a' && (p[2] | 0x20) == 'l' && (p[3] | 0x20) == 's' && (p[4] | 0x20) == 'e') {
        sign = 1;
        value = 0;
    }
    return sign * value;
}

float fn_802171DC(const unsigned char *p, const unsigned char *pName, float def)
{
    int sign = 1;
    float value;

    p = fn_802163F0(p, pName);
    if (p == 0) {
        return def;
    }
    while (*p != 0 && *p <= ' ') {
        p++;
    }
    if (*p == '"' || *p == '\'') {
        p++;
    }
    if (*p == '+') {
        sign = 1;
        p++;
    }
    if (*p == '-') {
        sign = -1;
        p++;
    }
    value = 0.0f;
    while (*p >= '0' && *p <= '9') {
        value = value * 10.0f + (*p & 0xF);
        p++;
    }
    if (*p == '.') {
        int n = 1;

        p++;
        while (*p >= '0' && *p <= '9') {
            value += (*p++ & 0xF) / fn_80260428(10.0f, n++);
        }
    }
    if ((p[0] | 0x20) == 't' && (p[1] | 0x20) == 'r' && (p[2] | 0x20) == 'u' && (p[3] | 0x20) == 'e') {
        sign = 1;
        value = 1.0f;
    }
    if ((p[0] | 0x20) == 'f' && (p[1] | 0x20) == 'a' && (p[2] | 0x20) == 'l' && (p[3] | 0x20) == 's' && (p[4] | 0x20) == 'e') {
        sign = 1;
        value = 0.0f;
    }
    return sign * value;
}

int fn_8021743C(const unsigned char *p, const unsigned char *pName, float *pOut, int count)
{
    int i;
    int sign;
    float value = 0.0f;

    p = fn_802163F0(p, pName);
    if (p == 0) {
        return 0;
    }
    while (*p != 0 && *p <= ' ') {
        p++;
    }
    if (*p == '"' || *p == '\'') {
        p++;
    }
    for (i = 0; i < count; i++) {
        sign = 1;
        while (*p != 0 && *p <= ' ') {
            p++;
        }
        if (*p == '"' || *p == '\'') {
            return 0;
        }
        if (*p == '+') {
            sign = 1;
            p++;
        }
        if (*p == '-') {
            sign = -1;
            p++;
        }
        value = 0.0f;
        while (*p >= '0' && *p <= '9') {
            value = value * 10.0f + (*p & 0xF);
            p++;
        }
        if (*p == '.') {
            int n = 1;

            p++;
            while (*p >= '0' && *p <= '9') {
                value += (*p++ & 0xF) / fn_80260428(10.0f, n++);
            }
        }
        if ((p[0] | 0x20) == 't' && (p[1] | 0x20) == 'r' && (p[2] | 0x20) == 'u' && (p[3] | 0x20) == 'e') {
            sign = 1;
            value = 1.0f;
        }
        if ((p[0] | 0x20) == 'f' && (p[1] | 0x20) == 'a' && (p[2] | 0x20) == 'l' && (p[3] | 0x20) == 's' && (p[4] | 0x20) == 'e') {
            sign = 1;
            value = 0.0f;
        }
        pOut[i] = sign * value;
    }
    return 1;
}
