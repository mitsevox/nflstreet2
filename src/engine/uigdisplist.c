/* UI display lists: turns the offset of a stored menu display list into an
   address after its library item is loaded, turns it back before unloading,
   and draws the list through GX. */

#include <dolphin/gx/GXDispList.h>
#include "engine/uigdisplist.h"

void UIGDispListRelocate(UIGDispList_t *pList)
{
    pList->Offset += (Int32)pList;
}

void UIGDispListUnrelocate(UIGDispList_t *pList)
{
    pList->Offset -= (Int32)pList;
}

void UIGDispListCall(UIGDispList_t *pList)
{
    GXCallDisplayList((void *)pList->Offset, pList->Size);
}
