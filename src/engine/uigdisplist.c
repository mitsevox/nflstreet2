/* UI display lists: turns the offset of a stored menu display list into an
   address after its library item is loaded, turns it back before unloading,
   and draws the list through GX. */

#include <dolphin/gx/GXDispList.h>
#include "engine/uigdisplist.h"

void fn_802260B0(DisplayList_802260D0 *pList)
{
    pList->Offset += (Int32)pList;
}

void fn_802260C0(DisplayList_802260D0 *pList)
{
    pList->Offset -= (Int32)pList;
}

void fn_802260D0(DisplayList_802260D0 *pList)
{
    GXCallDisplayList((void *)pList->Offset, pList->Size);
}
