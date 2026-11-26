#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"

/* UI graphics render state shared by the node renderers: the active and last
   renderer words, the stack of colour states (multiply and add colours pushed
   by transform nodes), and the transform node that pushes and pops the matrix
   and colour state around its children. */

/* Transform record read by UIGRenderPushTransform; +0x30 is not accessed and the size is not established. */
typedef struct UIGTransform_t {
    Float32 mPosition[3];   /* 0x00 */
    Float32 mPivot[3];      /* 0x0C */
    Float32 mRotation[3];   /* 0x18 */
    Float32 mScale[3];      /* 0x24 */
    Uint8 unk_30[4];        /* 0x30 */
    Float32 mMultiply[4];   /* 0x34 */
    Float32 mScaleColor[4]; /* 0x44 */
} UIGTransform_t;

static UIGMaterialColorState_t _UIGRender_aColorStates[8];
static UIGMaterialColorState_t *_UIGRender_pColorState = _UIGRender_aColorStates;
static Int32 _UIGRender_iActive = 0;
static Int32 _UIGRender_iLast = 0;
static Uint8 _UIGRender_bActiveValid = 0;
static Int32 _UIGRender_iColorState;

void UIGRenderResetColorState(void);
void UIGRenderPushTransform(void *p);
void UIGRenderPopTransform(void *p);

void UIGRenderSetActive(Int32 a)
{
    _UIGRender_iActive = a;
}

Int32 UIGRenderGetActive(void)
{
    if (_UIGRender_bActiveValid == 0) {
        return 0;
    }
    return _UIGRender_iActive;
}

void UIGRenderSetLast(Int32 a)
{
    _UIGRender_iLast = a;
}

void UIGRenderReset(void)
{
    UIGRenderResetColorState();
    UIGRenderSetActive(0);
    UIGRenderSetLast(0);
}

void *UIGRenderGetColorState(void)
{
    return _UIGRender_pColorState;
}

void UIGRenderResetColorState(void)
{
    _UIGRender_iColorState = 0;
    _UIGRender_aColorStates[0].unk_00[0] = 1.0f;
    _UIGRender_aColorStates[0].unk_00[1] = 1.0f;
    _UIGRender_aColorStates[0].unk_00[2] = 1.0f;
    _UIGRender_aColorStates[0].unk_00[3] = 1.0f;
    _UIGRender_aColorStates[0].unk_00[4] = 0.0f;
    _UIGRender_aColorStates[0].unk_00[5] = 0.0f;
    _UIGRender_aColorStates[0].unk_00[6] = 0.0f;
    _UIGRender_aColorStates[0].unk_00[7] = 0.0f;
    _UIGRender_pColorState = _UIGRender_aColorStates;
    UIGRenderSetLast(0);
}

static inline unsigned char _UIGRenderColorToByte(Float32 v)
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

void UIGRenderPushColorState(Float32 *pMul, Float32 *pScale)
{
    UIGMaterialColorState_t *pCur;
    UIGMaterialColorState_t *pNext;

    pCur = &_UIGRender_aColorStates[_UIGRender_iColorState];
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
    pNext->mMaterialColor.r = _UIGRenderColorToByte(pNext->unk_00[0] * 255.0f);
    pNext->mMaterialColor.g = _UIGRenderColorToByte(pNext->unk_00[1] * 255.0f);
    pNext->mMaterialColor.b = _UIGRenderColorToByte(pNext->unk_00[2] * 255.0f);
    pNext->mMaterialColor.a = _UIGRenderColorToByte(pNext->unk_00[3] * 255.0f);
    pNext->mLightColor.r = _UIGRenderColorToByte(pNext->unk_00[4] * 255.0f);
    pNext->mLightColor.g = _UIGRenderColorToByte(pNext->unk_00[5] * 255.0f);
    pNext->mLightColor.b = _UIGRenderColorToByte(pNext->unk_00[6] * 255.0f);
    pNext->mLightColor.a = _UIGRenderColorToByte(pNext->unk_00[7] * 255.0f);
    _UIGRender_iColorState++;
    _UIGRender_pColorState++;
    UIGRenderSetLast(0);
}

void UIGRenderPopColorState(void)
{
    _UIGRender_iColorState--;
    _UIGRender_pColorState--;
    UIGRenderSetLast(0);
}

long long UIGRenderIsRotated(Float32 *pV)
{
    long long result = 0;

    if (pV[0] != 0.0f || pV[1] != 0.0f || pV[2] != 0.0f) {
        result = 1;
    }
    return result;
}

void UIGRenderPushTransform(void *p)
{
    UIGTransform_t *pXf = p;
    float aNeg[3];

    MatSetStack(VptGetMatrixStack());
    MatPush();
    MatTranslate(pXf->mPosition);
    MatTranslate(pXf->mPivot);
    if (UIGRenderIsRotated(pXf->mRotation) != 0) {
        MatRotX((int)(pXf->mRotation[0] * 46603.38f));
        MatRotY((int)(pXf->mRotation[1] * 46603.38f));
        MatRotZ((int)(pXf->mRotation[2] * 46603.38f));
    }
    MatScaleCol(pXf->mScale[0], pXf->mScale[1], pXf->mScale[2]);
    aNeg[0] = -pXf->mPivot[0];
    aNeg[1] = -pXf->mPivot[1];
    aNeg[2] = -pXf->mPivot[2];
    MatTranslate(aNeg);
    UIGRenderPushColorState(pXf->mMultiply, pXf->mScaleColor);
    UIGRenderSetLast(0);
}

void UIGRenderPopTransform(void *p)
{
    MatSetStack(VptGetMatrixStack());
    MatPop();
    UIGRenderPopColorState();
    UIGRenderSetLast(0);
}

void UIGRenderTransformNodeAction(Uint32 Type, void *p)
{
    switch (Type) {
    case 0:
        break;
    case 1:
        UIGRenderPushTransform(p);
        break;
    case 2:
        UIGRenderPopTransform(p);
        break;
    }
}
