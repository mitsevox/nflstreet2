#ifndef ENGINE_UIGDISPLIST_H
#define ENGINE_UIGDISPLIST_H

#include "types.h"

/* Display-list reference: the list address is kept relative to the
   reference itself while stored. */
typedef struct DisplayList_802260D0 {
    Uint32 Size;    /* 0x00 */
    Int32 Offset;   /* 0x04 */
} DisplayList_802260D0;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/uigdisplist.c */
void fn_802260B0(DisplayList_802260D0 *pList);
void fn_802260C0(DisplayList_802260D0 *pList);
void fn_802260D0(DisplayList_802260D0 *pList);

#ifdef __cplusplus
}
#endif

#endif
