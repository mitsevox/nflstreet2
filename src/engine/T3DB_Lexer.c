#include "engine/t3db.h"

#define TDB_LEX_TOKEN(TYPE, ADVANCE, LENGTH)         \
    pLexer->mTokens[pLexer->mCount].mType = (TYPE); \
    p += (ADVANCE);                                 \
    pLexer->mTokens[pLexer->mCount++].mSrc = p - (LENGTH)

extern char *fn_80200DD4(TDbLexer_801FCE10 *pLexer, char *p);
extern char *fn_80201030(TDbLexer_801FCE10 *pLexer, char *p);

void fn_802009B0(TDbLexer_801FCE10 *pLexer, unsigned int start)
{
    char *p = pLexer->mSrc;

    pLexer->mTokens[1].mType = 0x49;
    pLexer->mTokens[1].mSrc = p;
    pLexer->mCount = start;
    while (p != 0 && pLexer->mCount <= 1) {
        if (*p == ' ') {
            p++;
        } else if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || *p == '_') {
            p = fn_80201030(pLexer, p);
        } else if (*p < 0) {
            TDB_LEX_TOKEN((unsigned char)*p - 0x80, 1, 1);
        } else if ((unsigned char)(*p - '0') <= 9 || (*p == '-' && (unsigned char)(p[1] - '0') <= 9)) {
            p = fn_80200DD4(pLexer, p);
        } else if (*p == '\'') {
            /* four-character constant between quotes */
            pLexer->mTokens[pLexer->mCount].mType = 0x33;
            pLexer->mTokens[pLexer->mCount].mValue = (void *)4;
            p += 5;
            pLexer->mTokens[pLexer->mCount++].mSrc = p - 4;
            p++;
        } else if (*p == '%') {
            TDB_LEX_TOKEN(0x43, 1, 1);
        } else if (*p == '\0') {
            break;
        } else if (*p == '[') {
            p = fn_80201C70(pLexer, p);
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
