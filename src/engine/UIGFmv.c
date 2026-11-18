/* UI graphics movies: the front end's full-motion-video library type. Opens
   the movie packages, creates, swaps and deletes the playing movie of a menu
   slot, starts, stops and updates it each frame, and keeps the play, alpha
   map and sound switches and the heap the player allocates from. */

#include "engine/Resource.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGFmv.h"
#include "engine/LLUIGFmv.h"
#include "game/ResOpenDevice.h"

int ResGetNumResources(ResFile_t *pRes);
unsigned char SndEnabled(void);

static Uint8 UIGFMV_bPlay = 0;
static Uint8 UIGFMV_AlphaMap = 1;
static Uint8 UIGFMV_Sound = 0;
static Int32 _UIGFMV_HeapId = 1;

void UIGFmvInit(UIGLibrary_t *pObject, Int32 a)
{
    void *p = ResOpenDevice((const char *)UIGLibraryGetFilename(pObject, a), 44);

    UIGLibrarySelfManagedInit(pObject, a, ResGetNumResources(p));
    UIGLibrarySetResFile(pObject, a, p);
    LLUIGFmvInit();
}

void UIGFmvShutdown(UIGLibrary_t *pObject, Int32 a)
{
    void *p = UIGLibraryGetResFile(pObject, a);

    if (p != NULL) {
        ResClose(p);
        LLUIGFmvShutdown();
    }
}

void UIGFmvProcess(UIGLibrary_t *pObject, Int32 a, Int32 b)
{
    LLUIGFmvMovie_t *pMovie = (LLUIGFmvMovie_t *)UIGLibraryGetItemData(pObject, a, b);

    if (pMovie != NULL && UIGFMV_bPlay) {
        LLUIGFmvProcess(pObject, pMovie);
    }
}

void UIGFmvAddInstance(UIGLibrary_t *pObject, Int32 a, Int32 b)
{
    LLUIGFmvMovie_t *pMovie = (LLUIGFmvMovie_t *)UIGLibraryGetItemData(pObject, a, b);

    if (pMovie == NULL) {
        pMovie = LLUIGFmvAddInstance(pObject, a, b);
        UIGLibrarySetItemData(pObject, a, b, (Int32)pMovie);
        UIGFMV_bPlay = 0;
    }
}

void UIGFmvSwapInstance(UIGLibrary_t *pObject, Int32 a, Int32 b, Int32 c, Int32 d)
{
    LLUIGFmvMovie_t *pMovie;

    if (c == -1) {
        pMovie = NULL;
    } else {
        pMovie = (LLUIGFmvMovie_t *)UIGLibraryGetItemData(pObject, c, d);
    }
    if (pMovie != NULL) {
        LLUIGFmvSwapInstance(pObject, a, b, pMovie);
    } else {
        UIGFmvAddInstance(pObject, a, b);
    }
    UIGFMV_bPlay = 0;
}

void UIGFmvDeleteInstance(UIGLibrary_t *pObject, Int32 a, Int32 b)
{
    LLUIGFmvMovie_t *pMovie = (LLUIGFmvMovie_t *)UIGLibraryGetItemData(pObject, a, b);

    if (pMovie != NULL) {
        LLUIGFmvDeleteInstance(pObject, pMovie);
        UIGLibrarySetItemData(pObject, a, b, 0);
    }
}

void UIGFmvUpdate(UIGLibrary_t *pObject, Int32 a, Int32 b)
{
    LLUIGFmvMovie_t *pMovie = (LLUIGFmvMovie_t *)UIGLibraryGetItemData(pObject, a, b);

    if (pMovie != NULL && UIGFMV_bPlay) {
        UIGLibrarySetMemInfo(a, b);
        LLUIGFmvUpdate(pObject, pMovie);
        UIGLibraryClearMemInfo();
    }
}

Uint8 UIGFmvHaveAlphaMap(void)
{
    return UIGFMV_AlphaMap;
}

Int32 UIGFmvHaveSound(void)
{
    Int32 Result = 0;

    if (UIGFMV_Sound && SndEnabled()) {
        Result = 1;
    }
    return Result;
}

Int32 UIGFmvGetHeap(void)
{
    return _UIGFMV_HeapId;
}

void UIGFmvStart(UIGLibrary_t *pObject, Int32 a, Int32 b)
{
    LLUIGFmvMovie_t *pMovie = (LLUIGFmvMovie_t *)UIGLibraryGetItemData(pObject, a, b);

    if (pMovie != NULL && !UIGFMV_bPlay) {
        UIGLibrarySetMemInfo(a, b);
        LLUIGFmvStartInstance(pObject, pMovie);
        UIGLibraryClearMemInfo();
        UIGFMV_bPlay = 1;
    }
}

void UIGFmvStop(UIGLibrary_t *pObject, Int32 a, Int32 b)
{
    LLUIGFmvMovie_t *pMovie = (LLUIGFmvMovie_t *)UIGLibraryGetItemData(pObject, a, b);

    if (pMovie != NULL && UIGFMV_bPlay) {
        LLUIGFmvStopInstance(pObject, pMovie);
        UIGFMV_bPlay = 0;
    }
}
