#include "engine/t3db.h"

char *fn_80201C70(TDbLexer_801FCE10 *pLexer, char *p)
{
    unsigned int used = pLexer->mBufUsed;
    char c;

    do {
        c = *++p;
        pLexer->mBuffer[used++] = c;
        if (c == '\\') {
            pLexer->mBuffer[used++] = *++p;
            c = *++p;
            pLexer->mBuffer[used++] = c;
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
    pLexer->mTokens[pLexer->mCount].mValue = &pLexer->mBuffer[pLexer->mBufUsed];
    pLexer->mTokens[pLexer->mCount++].mSrc = p + (-used - pLexer->mBufUsed);
    pLexer->mBufUsed = used;
    return p + 1;
}
