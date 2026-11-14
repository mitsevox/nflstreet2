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

static Uint8 lbl_803EBF78 = 0;
static Uint8 lbl_803EBF79 = 1;
static Uint8 lbl_803EBF7A = 0;
static Int32 lbl_803EBF7C = 1;

void fn_802260F8(Object_8021E688 *pObject, Int32 a)
{
    void *p = ResOpenDevice((const char *)fn_8021E970(pObject, a), 44);

    fn_8021E244(pObject, a, ResGetNumResources(p));
    fn_8021E998(pObject, a, p);
    fn_802267D0();
}

void fn_8022615C(Object_8021E688 *pObject, Int32 a)
{
    void *p = fn_8021E984(pObject, a);

    if (p != NULL) {
        ResClose(p);
        fn_802267D4();
    }
}

void fn_8022618C(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && lbl_803EBF78) {
        fn_80226498(pObject, pMovie);
    }
}

void fn_802261D4(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie == NULL) {
        pMovie = fn_802268D4(pObject, a, b);
        fn_8021E6A8(pObject, a, b, (Int32)pMovie);
        lbl_803EBF78 = 0;
    }
}

void fn_8022623C(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c, Int32 d)
{
    Object_802268D4 *pMovie;

    if (c == -1) {
        pMovie = NULL;
    } else {
        pMovie = (Object_802268D4 *)fn_8021E688(pObject, c, d);
    }
    if (pMovie != NULL) {
        fn_80226F34(pObject, a, b, pMovie);
    } else {
        fn_802261D4(pObject, a, b);
    }
    lbl_803EBF78 = 0;
}

void fn_802262C4(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL) {
        fn_802269C8(pObject, pMovie);
        fn_8021E6A8(pObject, a, b, 0);
    }
}

void fn_80226320(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && lbl_803EBF78) {
        fn_8021EF04(a, b);
        fn_8022666C(pObject, pMovie);
        fn_8021EF34();
    }
}

Uint8 fn_80226384(void)
{
    return lbl_803EBF79;
}

Int32 fn_8022638C(void)
{
    Int32 Result = 0;

    if (lbl_803EBF7A && SndEnabled()) {
        Result = 1;
    }
    return Result;
}

Int32 fn_802263D4(void)
{
    return lbl_803EBF7C;
}

void fn_802263DC(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && !lbl_803EBF78) {
        fn_8021EF04(a, b);
        fn_80226A68(pObject, pMovie);
        fn_8021EF34();
        lbl_803EBF78 = 1;
    }
}

void fn_80226448(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && lbl_803EBF78) {
        fn_80226C40(pObject, pMovie);
        lbl_803EBF78 = 0;
    }
}
