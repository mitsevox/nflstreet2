#ifndef ENGINE_UIGFMV_H
#define ENGINE_UIGFMV_H

#include "types.h"
#include "engine/UIGLibraries.h"

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGFmv.c */
void UIGFmvInit(UIGLibrary_t *pObject, Int32 a);
void UIGFmvShutdown(UIGLibrary_t *pObject, Int32 a);
void UIGFmvProcess(UIGLibrary_t *pObject, Int32 a, Int32 b);
void UIGFmvAddInstance(UIGLibrary_t *pObject, Int32 a, Int32 b);
void UIGFmvSwapInstance(UIGLibrary_t *pObject, Int32 a, Int32 b, Int32 c, Int32 d);
void UIGFmvDeleteInstance(UIGLibrary_t *pObject, Int32 a, Int32 b);
void UIGFmvUpdate(UIGLibrary_t *pObject, Int32 a, Int32 b);
Uint8 UIGFmvHaveAlphaMap(void);
Int32 UIGFmvHaveSound(void);
Int32 UIGFmvGetHeap(void);
void UIGFmvStart(UIGLibrary_t *pObject, Int32 a, Int32 b);
void UIGFmvStop(UIGLibrary_t *pObject, Int32 a, Int32 b);

#ifdef __cplusplus
}
#endif

#endif
