/* Small markup reader: finds elements by dotted path in a loaded text file and reads their string, integer
   and float attributes for the game's data files. */
#include "engine/tmlib.h"

static unsigned char _Xml_aHexValue[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
    0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
extern float fn_80260428(float x, float y);

const unsigned char *_XmlDecodeEntity(const unsigned char *p, unsigned char *pOut)
{
    *pOut = '~';
    if (*p == '#') {
        int value;

        if (p[1] == 'x') {
            p += 2;
            value = 0;
            while (*p > '/') {
                value = (value << 4) | _Xml_aHexValue[*p];
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

const unsigned char *_XmlFindAttr(const unsigned char *p, const unsigned char *pName)
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

const unsigned char *_XmlSkipTag(const unsigned char *p)
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

const unsigned char *_XmlSkipElement(const unsigned char *p)
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

const unsigned char *XmlFindChild(const unsigned char *p, const unsigned char *pPath);
const unsigned char *XmlFindInElement(const unsigned char *p, const unsigned char *pPath);

const unsigned char *XmlFindPath(const unsigned char *p, const unsigned char *pPath)
{
    const unsigned char *pResult = 0;
    int i;

    if (p == 0 || *p == 0 || pPath == 0 || *pPath == 0) {
        return 0;
    }
    do {
        while (*p != '<' && *p != 0) {
            p++;
        }
        if (p[0] == '<' && p[1] == '?') {
            p = _XmlSkipTag(p);
            continue;
        }
        if (p[0] == '<' && p[1] == '!') {
            p = _XmlSkipTag(p);
            continue;
        }
        if (p[0] == '<' && p[1] == '/') {
            p = _XmlSkipTag(p);
            continue;
        }
        if (*p != 0) {
            p++;
        }
        for (i = 0; p[i] != 0 && pPath[i] != 0 && p[i] == pPath[i]; i++) {
        }
        if (p[i] == 0) {
            break;
        }
        if (p[i] <= ' ' || p[i] == '>' || p[i] == '/') {
            if (pPath[i] == 0) {
                pResult = p - 1;
                break;
            }
            if (pPath[i] == '.' && p[i] != '/') {
                while (*p != 0 && *p != '>') {
                    p++;
                }
                if (pPath[i + 1] == 0) {
                    pResult = 0;
                    if (*p != 0) {
                        pResult = p + 1;
                    }
                } else if (*p != 0) {
                    pResult = XmlFindInElement(p + 1, pPath + i + 1);
                }
                break;
            }
        }
        p = _XmlSkipTag(p - 1);
    } while (p != 0);
    return pResult;
}

const unsigned char *XmlFindChild(const unsigned char *p, const unsigned char *pPath)
{
    const unsigned char *pResult = 0;
    int i;

    if (p == 0 || *p == 0 || pPath == 0 || *pPath == 0) {
        return 0;
    }
    do {
        while (*p != '<' && *p != 0) {
            p++;
        }
        if (p[0] == '<' && p[1] == '?') {
            p = _XmlSkipElement(p);
            continue;
        }
        if (p[0] == '<' && p[1] == '!') {
            p = _XmlSkipElement(p);
            continue;
        }
        if (p[0] == '<' && p[1] == '/') {
            break;
        }
        if (*p != 0) {
            p++;
        }
        for (i = 0; p[i] != 0 && pPath[i] != 0 && p[i] == pPath[i]; i++) {
        }
        if (p[i] == 0) {
            break;
        }
        if (p[i] <= ' ' || p[i] == '>' || p[i] == '/') {
            if (pPath[i] == 0) {
                pResult = p - 1;
                break;
            }
            if (pPath[i] == '.' && p[i] != '/') {
                while (*p != 0 && *p != '>') {
                    p++;
                }
                if (pPath[i + 1] == 0) {
                    pResult = 0;
                    if (*p != 0) {
                        pResult = p + 1;
                    }
                } else if (*p != 0) {
                    pResult = XmlFindChild(p + 1, pPath + i + 1);
                }
                break;
            }
        }
        p = _XmlSkipElement(p - 1);
    } while (p != 0);
    return pResult;
}

const unsigned char *XmlFindInElement(const unsigned char *p, const unsigned char *pPath)
{
    const unsigned char *pResult = 0;
    const unsigned char *pEnd = 0;
    const unsigned char *q;
    int depth;
    int i;

    if (p == 0 || *p == 0 || pPath == 0 || *pPath == 0) {
        return 0;
    }
    do {
        while (*p != '<' && *p != 0) {
            p++;
        }
        if (p[0] == '<' && p[1] == '?') {
            p = _XmlSkipElement(p);
            continue;
        }
        if (p[0] == '<' && p[1] == '!') {
            p = _XmlSkipElement(p);
            continue;
        }
        if (p[0] == '<' && p[1] == '/') {
            break;
        }
        if (pEnd == 0) {
            depth = 0;
            for (q = p; *q != 0; q++) {
                if (*q == '<' && q[1] != '?' && q[1] != '!') {
                    if (q[1] != '/') {
                        depth++;
                    } else if (--depth == 0) {
                        pEnd = q;
                        break;
                    }
                }
            }
        } else if (p > pEnd) {
            break;
        }
        if (*p != 0) {
            p++;
        }
        for (i = 0; p[i] != 0 && pPath[i] != 0 && p[i] == pPath[i]; i++) {
        }
        if (p[i] == 0) {
            break;
        }
        if (p[i] <= ' ' || p[i] == '>' || p[i] == '/') {
            if (pPath[i] == 0) {
                pResult = p - 1;
                break;
            }
            if (pPath[i] == '.' && p[i] != '/') {
                while (*p != 0 && *p != '>') {
                    p++;
                }
                if (pPath[i + 1] == 0) {
                    pResult = 0;
                    if (*p != 0) {
                        pResult = p + 1;
                    }
                } else if (*p != 0) {
                    pResult = XmlFindChild(p + 1, pPath + i + 1);
                }
                break;
            }
        }
        p = _XmlSkipTag(p - 1);
    } while (p != 0);
    return pResult;
}

const unsigned char *XmlFindNext(const unsigned char *pElem)
{
    const unsigned char *p;

    while (*pElem != 0 && *pElem != '<') {
        pElem++;
    }
    p = pElem;
    while ((p = _XmlSkipElement(p)) != 0) {
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

int XmlGetAttrString(const unsigned char *p, const unsigned char *pName, unsigned char *pDst, int maxLen, const unsigned char *pDefault)
{
    int n;

    if (pDst == 0 || maxLen <= 0) {
        return -1;
    }
    p = _XmlFindAttr(p, pName);
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
                p = _XmlDecodeEntity(p + 1, pDst++);
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

int XmlGetAttrInt(const unsigned char *p, const unsigned char *pName, int def)
{
    int sign = 1;
    int value;

    p = _XmlFindAttr(p, pName);
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

float XmlGetAttrFloat(const unsigned char *p, const unsigned char *pName, float def)
{
    int sign = 1;
    float value;

    p = _XmlFindAttr(p, pName);
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

int XmlGetAttrFloats(const unsigned char *p, const unsigned char *pName, float *pOut, int count)
{
    int i;
    int sign;
    float value = 0.0f;

    p = _XmlFindAttr(p, pName);
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
