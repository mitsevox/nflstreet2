#include <string.h>

#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>
#include "UIStudio/UIStudio.h"
#include "engine/Resource.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

/* UI graphics render state shared by the node renderers: the texture palette
   swap for image nodes, the active and last renderer words, the stack of
   colour states (multiply and add colours pushed by transform nodes), and the
   transform node that pushes and pops the matrix and colour state around its
   children. */

/* Transform record read by fn_80221198; +0x30 is not accessed and the size is not established. */
typedef struct Transform_80221198 {
    Float32 mPosition[3];   /* 0x00 */
    Float32 mPivot[3];      /* 0x0C */
    Float32 mRotation[3];   /* 0x18 */
    Float32 mScale[3];      /* 0x24 */
    Uint8 unk_30[4];        /* 0x30 */
    Float32 mMultiply[4];   /* 0x34 */
    Float32 mScaleColor[4]; /* 0x44 */
} Transform_80221198;

static UIGMaterialColorState_t lbl_8039F878[8];
static unsigned short *lbl_803EBF48 = NULL;
static Int32 lbl_803EBF4C = 0;
static UIGMaterialColorState_t *lbl_803EBF50 = lbl_8039F878;
static Int32 lbl_803EBF54 = 0;
static Int32 lbl_803EBF58 = 0;
static Uint8 lbl_803EBF5C = 0;
static Int32 lbl_803ED00C;

Int32 fn_80220BFC(Int32 a, Int32 b);
void fn_80220D3C(void);
void fn_80221198(void *p);
void fn_80221294(void *p);

Int32 fn_80220BFC(Int32 a, Int32 b)
{
    UIGLibrary_t *pObject;

    pObject = UIGLibraryGetGlobal(1);
    if (pObject == NULL) {
        return 0;
    }
    return UIGLibraryLoadItem(pObject, a, b);
}

void fn_80220C4C(Int32 a, Int32 b, Int32 c)
{
    Int32 p;

    lbl_803EBF48 = UIGTexNodeGetPalette((struct UIGTexNode_t *)c);
    p = fn_80220BFC(a, b);
    if (p != 0) {
        UIGTexNodeSetPalette((struct UIGTexNode_t *)c, (unsigned short *)p);
    }
}

void fn_80220CA4(Int32 a, Int32 b, Int32 c)
{
    if (lbl_803EBF48 != NULL) {
        UIGTexNodeSetPalette((struct UIGTexNode_t *)c, lbl_803EBF48);
    }
    lbl_803EBF48 = NULL;
}

void fn_80220CDC(Int32 a)
{
    lbl_803EBF54 = a;
}

Int32 fn_80220CE4(void)
{
    if (lbl_803EBF5C == 0) {
        return 0;
    }
    return lbl_803EBF54;
}

void fn_80220CFC(Int32 a)
{
    lbl_803EBF58 = a;
}

void fn_80220D04(void)
{
    fn_80220D3C();
    fn_80220CDC(0);
    fn_80220CFC(0);
}

void *fn_80220D34(void)
{
    return lbl_803EBF50;
}

void fn_80220D3C(void)
{
    lbl_803ED00C = 0;
    lbl_8039F878[0].unk_00[0] = 1.0f;
    lbl_8039F878[0].unk_00[1] = 1.0f;
    lbl_8039F878[0].unk_00[2] = 1.0f;
    lbl_8039F878[0].unk_00[3] = 1.0f;
    lbl_8039F878[0].unk_00[4] = 0.0f;
    lbl_8039F878[0].unk_00[5] = 0.0f;
    lbl_8039F878[0].unk_00[6] = 0.0f;
    lbl_8039F878[0].unk_00[7] = 0.0f;
    lbl_803EBF50 = lbl_8039F878;
    fn_80220CFC(0);
}

static inline unsigned char fn_80220DA4_ToByte(Float32 v)
{
    Float32 f;

    if (!(v < 0.0f)) {
        f = v;
        if (!(f <= 255.0f)) {
            f = 255.0f;
        }
        return (int)f;
    }
    return 0;
}

void fn_80220DA4(Float32 *pMul, Float32 *pScale)
{
    UIGMaterialColorState_t *pCur;
    UIGMaterialColorState_t *pNext;

    pCur = &lbl_8039F878[lbl_803ED00C];
    pNext = pCur + 1;
    pNext->unk_00[0] = pCur->unk_00[0] * pMul[0];
    pNext->unk_00[1] = pCur->unk_00[1] * pMul[1];
    pNext->unk_00[2] = pCur->unk_00[2] * pMul[2];
    pNext->unk_00[3] = pCur->unk_00[3] * pMul[3];
    pNext->unk_00[4] = pCur->unk_00[4] * pScale[0];
    pNext->unk_00[5] = pCur->unk_00[5] * pScale[1];
    pNext->unk_00[6] = pCur->unk_00[6] * pScale[2];
    pNext->unk_00[7] = pCur->unk_00[7] * pScale[3];
    if (!(pNext->unk_00[3] < 1.0f)) {
        pNext->unk_00[3] = 1.0f;
    }
    if (!(pNext->unk_00[3] > 0.0f)) {
        pNext->unk_00[3] = 0.0f;
    }
    pNext->mMaterialColor.r = fn_80220DA4_ToByte(pNext->unk_00[0] * 255.0f);
    pNext->mMaterialColor.g = fn_80220DA4_ToByte(pNext->unk_00[1] * 255.0f);
    pNext->mMaterialColor.b = fn_80220DA4_ToByte(pNext->unk_00[2] * 255.0f);
    pNext->mMaterialColor.a = fn_80220DA4_ToByte(pNext->unk_00[3] * 255.0f);
    pNext->mLightColor.r = fn_80220DA4_ToByte(pNext->unk_00[4] * 255.0f);
    pNext->mLightColor.g = fn_80220DA4_ToByte(pNext->unk_00[5] * 255.0f);
    pNext->mLightColor.b = fn_80220DA4_ToByte(pNext->unk_00[6] * 255.0f);
    pNext->mLightColor.a = fn_80220DA4_ToByte(pNext->unk_00[7] * 255.0f);
    lbl_803ED00C++;
    lbl_803EBF50++;
    fn_80220CFC(0);
}

void fn_80221118(void)
{
    lbl_803ED00C--;
    lbl_803EBF50--;
    fn_80220CFC(0);
}

long long fn_80221154(Float32 *pV)
{
    long long result = 0;

    if (pV[0] != 0.0f || pV[1] != 0.0f || pV[2] != 0.0f) {
        result = 1;
    }
    return result;
}

void fn_80221198(void *p)
{
    Transform_80221198 *pXf = p;
    float aNeg[3];

    MatSetStack(VptGetMatrixStack());
    MatPush();
    MatTranslate(pXf->mPosition);
    MatTranslate(pXf->mPivot);
    if (fn_80221154(pXf->mRotation) != 0) {
        MatRotX((int)(pXf->mRotation[0] * 46603.38f));
        MatRotY((int)(pXf->mRotation[1] * 46603.38f));
        MatRotZ((int)(pXf->mRotation[2] * 46603.38f));
    }
    MatScaleCol(pXf->mScale[0], pXf->mScale[1], pXf->mScale[2]);
    aNeg[0] = -pXf->mPivot[0];
    aNeg[1] = -pXf->mPivot[1];
    aNeg[2] = -pXf->mPivot[2];
    MatTranslate(aNeg);
    fn_80220DA4(pXf->mMultiply, pXf->mScaleColor);
    fn_80220CFC(0);
}

void fn_80221294(void *p)
{
    MatSetStack(VptGetMatrixStack());
    MatPop();
    fn_80221118();
    fn_80220CFC(0);
}

void fn_802212C8(Uint32 Type, void *p)
{
    switch (Type) {
    case 0:
        break;
    case 1:
        fn_80221198(p);
        break;
    case 2:
        fn_80221294(p);
        break;
    }
}
