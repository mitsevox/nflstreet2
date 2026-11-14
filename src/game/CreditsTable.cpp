/* Credits: reads the credits lines and their line types from the game database, one
   line at a time, for the credits screen. */

#include "game/fn_801FCE10.h"
extern "C" {
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
char *strncpy(char *pDest, const char *pSource, int count);
}

static QueryCursor _Credits_Cursor;
static char _Credits_szLine[72];
static int _Credits_iLineType;

extern "C" {
int CreditsFetchLine(void)
{
    return fn_801FCE10(0, "fetch from \x8a 'ilRC' into \x88 and 'ytRC' into \x82\n", &_Credits_Cursor, _Credits_szLine,
                       &_Credits_iLineType) == 0;
}

void CreditsOpen(void)
{
    _Credits_szLine[0] = 0;
    _Credits_iLineType = 0;
    if (fn_8022EF8C(0, 0x4C524443) == 0) {
        _Credits_Cursor.mUnknown0 = 0;
        _Credits_Cursor.mUnknown4 = 0;
        _Credits_Cursor.mUnknown8 = -1;
        _Credits_Cursor.mUnknown12 = 0;
        fn_801FCE10(0, "declare \x8a cursor for select * from 'LRDC'\n", &_Credits_Cursor);
    }
}

void CreditsClose(void)
{
    if (_Credits_Cursor.mUnknown0 != 0) {
        fn_801FCFA0(&_Credits_Cursor);
    }
    fn_8022EFBC(0, 0x4C524443);
    _Credits_szLine[0] = 0;
    _Credits_iLineType = 0;
}

void CreditsCountLines(int *pCount)
{
    int count = 0;

    fn_801FCE10(0, "select count(*) into \x85 from 'LRDC'\n", &count);
    *pCount = count;
}

void CreditsGetLine(char *pDest, int count)
{
    strncpy(pDest, _Credits_szLine, count);
}

void CreditsGetLineType(int *pValue)
{
    *pValue = _Credits_iLineType;
}
}
