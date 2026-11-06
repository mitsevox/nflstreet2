/* A 128-character text buffer ("The Users String") that the menus can set and
   read back. */

#include <string.h>

static char _UserString_szText[128] = "The Users String";
static int _UserString_iLength = 128;

extern "C" int UserStringGet(char *pDest, int count)
{
    strncpy(pDest, _UserString_szText, count);
    pDest[count] = 0;
    return _UserString_iLength;
}

extern "C" void UserStringSet(const char *pSource, int count)
{
    _UserString_iLength = count;
    strncpy(_UserString_szText, pSource, count);
    _UserString_szText[_UserString_iLength] = 0;
}
