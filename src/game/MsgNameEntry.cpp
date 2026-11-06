/* Name entry: keeps the name the player typed on the front end so that other
   screens can read it back. */

#include <string.h>

#include "game/TextRecord.h"
#include "game/fn_801C3284.h"

static char _MsgNameEntry_szName[20];

extern "C" void MsgNameEntrySetName(const char *pText)
{
    strcpy(_MsgNameEntry_szName, pText);
}

extern "C" void MsgNameEntryGetName(char *pDest, int length)
{
    fn_801C3284(pDest, _MsgNameEntry_szName, length + 1);
}

extern "C" int MsgNameEntryHandleMessage(int id, TextRecord_t **ppRecord, int c, int *pResult)
{
    switch (id) {
    case 0x80000002:
        MsgNameEntrySetName((*ppRecord)->mUnknown8);
        break;
    case 0x80000001:
        *pResult = 1;
        break;
    default:
        return 0;
    }
    return 1;
}
