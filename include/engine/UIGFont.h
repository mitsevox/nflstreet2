#ifndef ENGINE_UIGFONT_H
#define ENGINE_UIGFONT_H

#include "types.h"
#include "engine/Font.h"
#include "engine/UIGLibraries.h"

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGFont.c */
void fn_80225D90(Object_8021E688 *pObject, Int16 a);
void fn_80225E10(Object_8021E688 *pObject, Int16 a);
void fn_80225E64(Object_8021E688 *pObject, Int16 a, Int16 b, Int32 c);
void fn_80225F10(Object_8021E688 *pObject, Int16 a, Int16 b);
Uint32 fn_80225F88(Object_8021E688 *pObject, Int32 a, Int32 b, const char *pText);
Font_801CCA64 *fn_8022601C(Object_8021E688 *pObject, Int32 a, Int16 b, Int32 c);

#ifdef __cplusplus
}
#endif

#endif
