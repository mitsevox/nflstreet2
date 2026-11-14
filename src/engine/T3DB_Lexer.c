/* Tokenizes the database query language into a two-token lookahead buffer. */
#include "engine/t3db.h"

#define TDB_LEX_TOKEN(TYPE, ADVANCE, LENGTH)         \
    pLexer->mTokens[pLexer->mCount].mType = (TYPE); \
    p += (ADVANCE);                                 \
    pLexer->mTokens[pLexer->mCount++].mSrc = p - (LENGTH)

extern char *T3DB_Lexer_Number(TDbLexer_t *pLexer, char *p);
extern char *T3DB_Lexer_Identifier(TDbLexer_t *pLexer, char *p);

/* Fills the two-token lookahead window from the current query cursor. */
void T3DB_Lexer_GetTokens(TDbLexer_t *pLexer, unsigned int start)
{
    char *p = pLexer->mSrc;

    pLexer->mTokens[1].mType = 0x49;
    pLexer->mTokens[1].mSrc = p;
    pLexer->mCount = start;
    while (p != 0 && pLexer->mCount <= 1) {
        if (*p == ' ') {
            p++;
        } else if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || *p == '_') {
            p = T3DB_Lexer_Identifier(pLexer, p);
        } else if (*p < 0) {
            TDB_LEX_TOKEN((unsigned char)*p - 0x80, 1, 1);
        } else if ((unsigned char)(*p - '0') <= 9 || (*p == '-' && (unsigned char)(p[1] - '0') <= 9)) {
            p = T3DB_Lexer_Number(pLexer, p);
        } else if (*p == '\'') {
            /* four-character constant between quotes */
            pLexer->mTokens[pLexer->mCount].mType = 0x33;
            pLexer->mTokens[pLexer->mCount].mValue.u = 4;
            p += 5;
            pLexer->mTokens[pLexer->mCount++].mSrc = p - 4;
            p++;
        } else if (*p == '%') {
            TDB_LEX_TOKEN(0x43, 1, 1);
        } else if (*p == '\0') {
            break;
        } else if (*p == '[') {
            p = T3DB_Lexer_StringLiteral(pLexer, p);
        } else if (*p == '\n') {
            p++;
        } else if (*p == '\t') {
            p++;
        } else if (*p == '\r') {
            p++;
        } else if (*p == '\f') {
            p++;
        } else if (*p == '>') {
            if (*++p == '=') {
                TDB_LEX_TOKEN(0x35, 1, 2);
            } else {
                TDB_LEX_TOKEN(0x3B, 0, 1);
            }
        } else if (*p == '<') {
            if (*++p == '=') {
                TDB_LEX_TOKEN(0x34, 1, 2);
            } else {
                TDB_LEX_TOKEN(0x3A, 0, 1);
            }
        } else if (*p == '*') {
            TDB_LEX_TOKEN(0x41, 1, 1);
        } else if (*p == '&') {
            if (*++p == '&') {
                TDB_LEX_TOKEN(0x38, 1, 2);
            } else {
                TDB_LEX_TOKEN(0x46, 0, 1);
            }
        } else if (*p == '^') {
            TDB_LEX_TOKEN(0x45, 1, 1);
        } else if (*p == '|') {
            if (*++p == '|') {
                TDB_LEX_TOKEN(0x39, 1, 2);
            } else {
                TDB_LEX_TOKEN(0x47, 0, 1);
            }
        } else if (*p == '=') {
            if (*++p == '=') {
                TDB_LEX_TOKEN(0x36, 1, 2);
            } else {
                TDB_LEX_TOKEN(0x36, 0, 1);
            }
        } else if (*p == '!') {
            if (*++p == '=') {
                TDB_LEX_TOKEN(0x37, 1, 2);
            } else {
                TDB_LEX_TOKEN(0x3F, 0, 1);
            }
        } else if (*p == '(') {
            TDB_LEX_TOKEN(0x3C, 1, 1);
        } else if (*p == ')') {
            TDB_LEX_TOKEN(0x3D, 1, 1);
        } else if (*p == '.') {
            TDB_LEX_TOKEN(0x3E, 1, 1);
        } else if (*p == '+') {
            TDB_LEX_TOKEN(0x44, 1, 1);
        } else if (*p == '-') {
            TDB_LEX_TOKEN(0x40, 1, 1);
        } else if (*p == '~') {
            TDB_LEX_TOKEN(0x48, 1, 1);
        } else {
            TDB_LEX_TOKEN(-1, 1, 1);
        }
    }
    if (pLexer->mCount == 0) {
        TDB_LEX_TOKEN(0x49, 0, 0);
    }
    pLexer->mSrc = p;
}

#if defined(DECOMP_COMPARE)

/* Scans an integer or fractional literal and stores its numeric payload. */
char *T3DB_Lexer_Number(TDbLexer_t *pLexer, char *p)
{
    int negative = 0;
    int value = 0;
    int multiplier;
    char c;

    if (*p == '0' && (p[1] == 'X' || p[1] == 'x')) {
        p++;
        multiplier = 1;
        c = *++p;
        while ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') ||
               (c >= 'a' && c <= 'f')) {
            value *= multiplier;
            multiplier = 16;
            if (c >= '0' && c <= '9') {
                value += c - '0';
            } else if (c >= 'A' && c <= 'F') {
                value += c - 'A' + 10;
            } else if (c >= 'a' && c <= 'f') {
                value += c - 'a' + 10;
            }
            c = *++p;
        }
    } else {
        value = 0;
        multiplier = 1;
        if (*p == '-') {
            negative = 1;
            p++;
        }
        c = *p;
        while (c >= '0' && c <= '9') {
            value *= multiplier;
            multiplier = 10;
            value += c - '0';
            c = *++p;
        }
        if (*p == '.') {
            double real = value;

            c = *++p;
            multiplier = 10;
            while ((unsigned char)(c - '0') <= 9) {
                real += (double)(c - '0') / multiplier;
                multiplier *= 10;
                c = *++p;
            }
            if (c == 'f') {
                p++;
            }
            if (negative) {
                real = -real;
            }
            pLexer->mTokens[pLexer->mCount].mType = 0x31;
            pLexer->mTokens[pLexer->mCount].mValue.f = real;
            pLexer->mTokens[pLexer->mCount++].mSrc = p;
            goto done;
        }
        if (negative) {
            value = -value;
        }
    }
    pLexer->mTokens[pLexer->mCount].mType = 0x30;
    pLexer->mTokens[pLexer->mCount].mValue.i = value;
    pLexer->mTokens[pLexer->mCount++].mSrc = p;
done:
    return p;
}

/* Recognizes lowercase query keywords and records other identifier lengths. */
char *T3DB_Lexer_Identifier(TDbLexer_t *pLexer, char *p)
{
    char word[48];
    int length = 0;
    char c = *p;

    do {
        word[length++] = c;
        c = *++p;
    } while ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') ||
             (*p >= '0' && *p <= '9') || *p == '_');

    switch (length) {
    case 2:
        if (word[0] == 'o') {
            if (word[1] == 'r') {
                TDB_LEX_TOKEN(0x39, 0, 2);
                goto done;
            } else if (word[1] == 'n') {
                TDB_LEX_TOKEN(0x1D, 0, 2);
                goto done;
            }
        }
        if (word[0] == 'b' && word[1] == 'y') {
            TDB_LEX_TOKEN(0x21, 0, 2);
            goto done;
        }
        break;
    case 3:
        if (word[0] == 'a' && word[1] == 's' && word[2] == 'c') {
            TDB_LEX_TOKEN(0x22, 0, 3);
            goto done;
        } else if (word[0] == 's' && word[1] == 'e' && word[2] == 't') {
            TDB_LEX_TOKEN(0x1E, 0, 3);
            goto done;
        } else if (word[0] == 'a' && word[1] == 'n' && word[2] == 'd') {
            TDB_LEX_TOKEN(0x38, 0, 3);
            goto done;
        } else if (word[0] == 'u' && word[1] == 's' && word[2] == 'e') {
            TDB_LEX_TOKEN(0x1F, 0, 3);
            goto done;
        } else if (word[0] == 'f' && word[1] == 'o' && word[2] == 'r') {
            TDB_LEX_TOKEN(0x29, 0, 3);
            goto done;
        } else if (word[0] == 'm' && word[1] == 'i' && word[2] == 'n') {
            TDB_LEX_TOKEN(0x2C, 0, 3);
            goto done;
        } else if (word[0] == 'm' && word[1] == 'a' && word[2] == 'x') {
            TDB_LEX_TOKEN(0x2D, 0, 3);
            goto done;
        } else if (word[0] == 's' && word[1] == 'u' && word[2] == 'm') {
            TDB_LEX_TOKEN(0x2E, 0, 3);
            goto done;
        }
        break;
    case 4:
        if (word[0] == 'f' && word[1] == 'r' && word[2] == 'o' && word[3] == 'm') {
            TDB_LEX_TOKEN(0x16, 0, 4);
            goto done;
        } else if (word[0] == 'i' && word[1] == 'n' && word[2] == 't' && word[3] == 'o') {
            TDB_LEX_TOKEN(0x17, 0, 4);
            goto done;
        } else if (word[0] == 'd' && word[1] == 'e' && word[2] == 's' && word[3] == 'c') {
            TDB_LEX_TOKEN(0x23, 0, 4);
            goto done;
        } else if (word[0] == 'j' && word[1] == 'o' && word[2] == 'i' && word[3] == 'n') {
            TDB_LEX_TOKEN(0x19, 0, 4);
            goto done;
        } else if (word[0] == 'l' && word[1] == 'e' && word[2] == 'f' && word[3] == 't') {
            TDB_LEX_TOKEN(0x1A, 0, 4);
            goto done;
        }
        break;
    case 5:
        if (word[0] == 'w' && word[1] == 'h' && word[2] == 'e' && word[3] == 'r' && word[4] == 'e') {
            TDB_LEX_TOKEN(0x14, 0, 5);
            goto done;
        } else if (word[0] == 'f' && word[1] == 'e' && word[2] == 't' && word[3] == 'c' && word[4] == 'h') {
            TDB_LEX_TOKEN(0x13, 0, 5);
            goto done;
        } else if (word[0] == 'o' && word[1] == 'r' && word[2] == 'd' && word[3] == 'e' && word[4] == 'r') {
            TDB_LEX_TOKEN(0x20, 0, 5);
            goto done;
        } else if (word[0] == 'i' && word[1] == 'n' && word[2] == 'd' && word[3] == 'e' && word[4] == 'x') {
            TDB_LEX_TOKEN(0x26, 0, 5);
            goto done;
        } else if (word[0] == 'i' && word[1] == 'n' && word[2] == 'n' && word[3] == 'e' && word[4] == 'r') {
            TDB_LEX_TOKEN(0x18, 0, 5);
            goto done;
        } else if (word[0] == 'c' && word[1] == 'o' && word[2] == 'u' && word[3] == 'n' && word[4] == 't') {
            TDB_LEX_TOKEN(0x2B, 0, 5);
            goto done;
        } else if (word[0] == 'o' && word[1] == 'u' && word[2] == 't' && word[3] == 'e' && word[4] == 'r') {
            TDB_LEX_TOKEN(0x1B, 0, 5);
            goto done;
        }
        break;
    case 6:
        if (word[0] == 's' && word[1] == 'e' && word[2] == 'l' && word[3] == 'e' && word[4] == 'c' && word[5] == 't') {
            TDB_LEX_TOKEN(0x11, 0, 6);
            goto done;
        } else if (word[0] == 'i' && word[1] == 'n' && word[2] == 's' && word[3] == 'e' && word[4] == 'r' && word[5] == 't') {
            TDB_LEX_TOKEN(0x12, 0, 6);
            goto done;
        } else if (word[0] == 'u' && word[1] == 'p' && word[2] == 'd' && word[3] == 'a' && word[4] == 't' && word[5] == 'e') {
            TDB_LEX_TOKEN(0x1C, 0, 6);
            goto done;
        } else if (word[0] == 'd' && word[1] == 'e' && word[2] == 'l' && word[3] == 'e' && word[4] == 't' && word[5] == 'e') {
            TDB_LEX_TOKEN(0x15, 0, 6);
            goto done;
        } else if (word[0] == 'c' && word[1] == 'u' && word[2] == 'r' && word[3] == 's' && word[4] == 'o' && word[5] == 'r') {
            TDB_LEX_TOKEN(0x27, 0, 6);
            goto done;
        } else if (word[0] == 'c' && word[1] == 'r' && word[2] == 'e' && word[3] == 'a' && word[4] == 't' && word[5] == 'e') {
            TDB_LEX_TOKEN(0x25, 0, 6);
            goto done;
        } else if (word[0] == 'u' && word[1] == 'n' && word[2] == 'i' && word[3] == 'q' && word[4] == 'u' && word[5] == 'e') {
            TDB_LEX_TOKEN(0x2A, 0, 6);
            goto done;
        }
        break;
    case 7:
        if (word[0] == 'd' && word[1] == 'e' && word[2] == 'c' && word[3] == 'l' && word[4] == 'a' && word[5] == 'r' && word[6] == 'e') {
            TDB_LEX_TOKEN(0x24, 0, 7);
            goto done;
        }
        break;
    case 10:
        if (word[0] == 'f' && word[1] == 'a' && word[2] == 's' && word[3] == 't' && word[4] == 'c' && word[5] == 'u' && word[6] == 'r' && word[7] == 's' && word[8] == 'o' && word[9] == 'r') {
            TDB_LEX_TOKEN(0x28, 0, 10);
            goto done;
        }
        break;
    }
    pLexer->mTokens[pLexer->mCount].mType = 0x2F;
    pLexer->mTokens[pLexer->mCount].mValue.u = length;
    pLexer->mTokens[pLexer->mCount++].mSrc = p - length;
done:
    return p;
}

/* Copies bracketed literal text into the lexer buffer. */
char *T3DB_Lexer_StringLiteral(TDbLexer_t *pLexer, char *p)
{
    unsigned int used = pLexer->mBufUsed;
    char c;

    do {
        pLexer->mBuffer[used++] = c = *++p;
        if (c == '\\') {
            c = *++p;
            pLexer->mBuffer[used++] = c;
            pLexer->mBuffer[used++] = c = *++p;
        }
    } while (c != ']' && c != '\0');
    used--;
    pLexer->mBuffer[used++] = '\0';
    if (c == '\0') {
        pLexer->mTokens[pLexer->mCount].mType = -1;
        pLexer->mTokens[pLexer->mCount++].mSrc = p;
        return p;
    }
    while (used & 3) {
        pLexer->mBuffer[used++] = '\0';
    }
    pLexer->mTokens[pLexer->mCount].mType = 0x32;
    pLexer->mTokens[pLexer->mCount].mValue.s = &pLexer->mBuffer[pLexer->mBufUsed];
    pLexer->mTokens[pLexer->mCount++].mSrc = p + (-used - pLexer->mBufUsed);
    pLexer->mBufUsed = used;
    return p + 1;
}

#endif
