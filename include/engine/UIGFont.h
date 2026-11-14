#ifndef ENGINE_UIGFONT_H
#define ENGINE_UIGFONT_H

#include "types.h"
#include "engine/Font.h"
#include "engine/UIGLibraries.h"

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGFont.c */
void UIGFontCreateFontLibrary(UIGLibrary_t *pObject, Int16 a);
void UIGFontDestroyFontLibrary(UIGLibrary_t *pObject, Int16 a);
void UIGFontCreateFont(UIGLibrary_t *pObject, Int16 a, Int16 b, Int32 c);
void UIGFontDestroyFont(UIGLibrary_t *pObject, Int16 a, Int16 b);
Uint32 UIGFontGetStringWidth(UIGLibrary_t *pObject, Int32 a, Int32 b, const char *pText);
Font_801CCA64 *UIGFontGetFont(UIGLibrary_t *pObject, Int32 a, Int16 b, Int32 c);

#ifdef __cplusplus
}
#endif

#endif
