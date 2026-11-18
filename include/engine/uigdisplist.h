#ifndef ENGINE_UIGDISPLIST_H
#define ENGINE_UIGDISPLIST_H

#include "types.h"

/* Display-list reference: the list address is kept relative to the
   reference itself while stored. */
typedef struct UIGDispList_t {
    Uint32 Size;    /* 0x00 */
    Int32 Offset;   /* 0x04 */
} UIGDispList_t;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/uigdisplist.c */
void UIGDispListRelocate(UIGDispList_t *pList);
void UIGDispListUnrelocate(UIGDispList_t *pList);
void UIGDispListCall(UIGDispList_t *pList);

#ifdef __cplusplus
}
#endif

#endif
