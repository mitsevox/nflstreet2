/* Animation blend weights: each weight moves from its current value toward a target
   over time, held constant, faded linearly, cut to zero after a wait, or faded in,
   held and faded out. The module keeps a table of update functions and parameter
   sizes, one per weight type, that the animation channels step every frame. */

#include "engine/cu_801B9F00.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

typedef void (*AnimWgtFunc_t)(AnimWgt_t *p, float step);

static void _AnimWgtConstantFunction(AnimWgt_t *p, float step);
static void _AnimWgtLinearFunction(AnimWgt_t *p, float step);
static void _AnimWgtWaitToStopFunction(AnimWgt_t *p, float step);
static void _AnimWgtLinearInAndOutFunction(AnimWgt_t *p, float step);

static AnimWgtFunc_t *_AnimWgt_pFunctions = 0;
static unsigned char *_AnimWgt_TypeStructSize = 0;
static AnimWgtFunc_t _AnimWgt_pLibFunctions[4] = { _AnimWgtConstantFunction, _AnimWgtLinearFunction, _AnimWgtWaitToStopFunction, _AnimWgtLinearInAndOutFunction };
static unsigned char _AnimWgt_LibTypeStructSize[4] = { 0, sizeof(AnimWgtLinear_t), sizeof(AnimWgtWaitToStop_t), sizeof(AnimWgtLinearInAndOut_t) };
static int _AnimWgt_NumFunctions;

static void _AnimWgtConstantFunction(AnimWgt_t *p, float step)
{
}

static void _AnimWgtLinearFunction(AnimWgt_t *p, float step)
{
    AnimWgtLinear_t *pData = &p->mUnknownC.mType1;
    float value = p->mUnknown0;
    float target = p->mUnknown4;

    if (value != target) {
        p->mUnknown0 = (target - pData->mUnknown0) / (float)pData->mUnknown4 * step + value;
        if (pData->mUnknown0 < target) {
            if (p->mUnknown0 > target) {
                p->mUnknown0 = target;
            }
        } else if (p->mUnknown0 < target) {
            p->mUnknown0 = target;
        }
    }
}

static void _AnimWgtWaitToStopFunction(AnimWgt_t *p, float step)
{
    p->mUnknownC.mType2.mUnknown0 -= step;
    if (p->mUnknownC.mType2.mUnknown0 <= 0.0f) {
        p->mUnknown0 = 0.0f;
    }
}

static void _AnimWgtLinearInAndOutFunction(AnimWgt_t *p, float step)
{
    AnimWgtLinearInAndOut_t *pData = &p->mUnknownC.mType3;

    do {
        int advance = 0;
        float dt = step;

        step = 0.0f;
        switch (pData->mUnknown9) {
        case 0:
            advance = 1;
            pData->mUnknown4 -= dt;
            if (pData->mUnknown4 < 0.0f) {
                step = -pData->mUnknown4;
                pData->mUnknown9 = 1;
                dt -= step;
                pData->mUnknown4 = pData->mUnknownA;
            }
            break;
        case 1:
            pData->mUnknown4 -= dt;
            if (pData->mUnknown4 < 0.0f) {
                step = -pData->mUnknown4;
                pData->mUnknown9 = 2;
                dt -= step;
                pData->mUnknown4 = pData->mUnknown8;
            }
            break;
        case 2:
            advance = 1;
            break;
        }
        if (advance == 1) {
            float from;
            float to;
            float frames;

            if (pData->mUnknown9 != 2) {
                from = pData->mUnknown0;
                to = p->mUnknown4;
            } else {
                from = p->mUnknown4;
                to = pData->mUnknown0;
            }
            frames = (int)pData->mUnknown8;
            if (frames != 0.0f) {
                p->mUnknown0 = (to - from) / frames * dt + p->mUnknown0;
            }
            if (from < to) {
                if (p->mUnknown0 >= to) {
                    p->mUnknown0 = to;
                }
            } else if (p->mUnknown0 <= to) {
                p->mUnknown0 = to;
            }
        }
    } while (step > 0.0f);
}

void AnimWgtInit(int count)
{
    int i;

    _AnimWgt_pFunctions = fn_801D2B7C(count * 4, 0, 0);
    _AnimWgt_TypeStructSize = fn_801D2B7C(count, 0, 0);
    fn_801F7C88();
    _AnimWgt_NumFunctions = count;
    if (_AnimWgt_pFunctions != 0) {
        for (i = 0; i < 4; i++) {
            _AnimWgt_pFunctions[i] = _AnimWgt_pLibFunctions[i];
            _AnimWgt_TypeStructSize[i] = _AnimWgt_LibTypeStructSize[i];
        }
        for (; i < count; i++) {
            _AnimWgt_pFunctions[i] = 0;
            _AnimWgt_TypeStructSize[i] = 0;
        }
    }
}

int AnimWgtShutdown(void)
{
    if (_AnimWgt_pFunctions != 0) {
        fn_801D2BD0(_AnimWgt_pFunctions);
        fn_801D2BD0(_AnimWgt_TypeStructSize);
        _AnimWgt_pFunctions = 0;
        _AnimWgt_TypeStructSize = 0;
    }
    return 0;
}

void AnimWgtSet(AnimWgt_t *p, int type, float a, void *pSource, float b)
{
    if (a != -1.0f)
        p->mUnknown0 = a;
    if (b != -1.0f)
        p->mUnknown4 = b;
    p->mUnknown8 = type;
    if (pSource != 0 && _AnimWgt_TypeStructSize[type] != 0)
        memcpy(&p->mUnknownC, pSource, _AnimWgt_TypeStructSize[type]);
}

void AnimWgtClrTypeStruct(int type, void *pData)
{
    if (_AnimWgt_TypeStructSize[type] != 0)
        memset(pData, 0, _AnimWgt_TypeStructSize[type]);
}

void AnimWgtProcess(AnimWgt_t *p, float step)
{
    if (_AnimWgt_pFunctions != 0)
        _AnimWgt_pFunctions[p->mUnknown8](p, step);
}

void AnimWgtSetLinear(AnimWgt_t *p, unsigned int frames, float from, float to)
{
    AnimWgtLinear_t data;

    AnimWgtClrTypeStruct(1, &data);
    if (from == -1.0f)
        from = p->mUnknown0;
    data.mUnknown4 = frames;
    data.mUnknown0 = from;
    AnimWgtSet(p, 1, from, &data, to);
}

#if defined(DECOMP_COMPARE)
void AnimWgtSetLinearInAndOut(AnimWgt_t *p, unsigned char frames, unsigned char hold, float from, float to)
{
    AnimWgtLinearInAndOut_t data;

    AnimWgtClrTypeStruct(3, &data);
    if (from == -1.0f)
        from = p->mUnknown0;
    data.mUnknown0 = from;
    data.mUnknownA = hold;
    data.mUnknown9 = 0;
    data.mUnknown8 = frames;
    data.mUnknown4 = frames;
    AnimWgtSet(p, 3, from, &data, to);
}
#endif
