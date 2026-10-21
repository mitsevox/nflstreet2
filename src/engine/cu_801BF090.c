#include "engine/cu_801B9F00.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

typedef void (*Update_801BF2B0)(Block_801BF3C8 *p, float step);

extern Update_801BF2B0 *lbl_803EBB9C;
extern unsigned char *lbl_803EBBA0;
extern int lbl_803ED614;
extern Update_801BF2B0 lbl_802F484C[4];
extern unsigned char lbl_803EBBA4[4];

void fn_801BF090(Block_801BF3C8 *p, float step)
{
}

void fn_801BF094(Block_801BF3C8 *p, float step)
{
    Data1_801BF4A8 *pData = &p->mUnknownC.mType1;
    float value = p->mUnknown0;
    float target = p->mUnknown4;

    if (value != target) {
        p->mUnknown0 = (target - pData->mUnknown0) / (float)pData->mUnknown4 * step + value;
        if (!(pData->mUnknown0 >= target)) {
            if (!(p->mUnknown0 <= target)) {
                p->mUnknown0 = target;
            }
        } else if (!(p->mUnknown0 >= target)) {
            p->mUnknown0 = target;
        }
    }
}

void fn_801BF11C(Block_801BF3C8 *p, float step)
{
    p->mUnknownC.mType2.mUnknown0 -= step;
    if (!(p->mUnknownC.mType2.mUnknown0 > 0.0f)) {
        p->mUnknown0 = 0.0f;
    }
}

void fn_801BF140(Block_801BF3C8 *p, float step)
{
    Data3_801BF530 *pData = &p->mUnknownC.mType3;

    do {
        int advance = 0;
        float dt = step;

        step = 0.0f;
        switch (pData->mUnknown9) {
        case 0:
            advance = 1;
            pData->mUnknown4 -= dt;
            if (!(pData->mUnknown4 >= 0.0f)) {
                step = -pData->mUnknown4;
                pData->mUnknown9 = 1;
                dt -= step;
                pData->mUnknown4 = pData->mUnknownA;
            }
            break;
        case 1:
            pData->mUnknown4 -= dt;
            if (!(pData->mUnknown4 >= 0.0f)) {
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
            if (!(from >= to)) {
                if (!(p->mUnknown0 < to)) {
                    p->mUnknown0 = to;
                }
            } else if (!(p->mUnknown0 > to)) {
                p->mUnknown0 = to;
            }
        }
    } while (step > 0.0f);
}

void fn_801BF2B0(int count)
{
    int i;

    lbl_803EBB9C = fn_801D2B7C(count * 4, 0, 0);
    lbl_803EBBA0 = fn_801D2B7C(count, 0, 0);
    fn_801F7C88();
    lbl_803ED614 = count;
    if (lbl_803EBB9C != 0) {
        for (i = 0; i < 4; i++) {
            lbl_803EBB9C[i] = lbl_802F484C[i];
            lbl_803EBBA0[i] = lbl_803EBBA4[i];
        }
        for (; i < count; i++) {
            lbl_803EBB9C[i] = 0;
            lbl_803EBBA0[i] = 0;
        }
    }
}

int fn_801BF384(void)
{
    if (lbl_803EBB9C != 0) {
        fn_801D2BD0(lbl_803EBB9C);
        fn_801D2BD0(lbl_803EBBA0);
        lbl_803EBB9C = 0;
        lbl_803EBBA0 = 0;
    }
    return 0;
}

void fn_801BF3C8(Block_801BF3C8 *p, int type, float a, void *pSource, float b)
{
    if (a != -1.0f)
        p->mUnknown0 = a;
    if (b != -1.0f)
        p->mUnknown4 = b;
    p->mUnknown8 = type;
    if (pSource != 0 && lbl_803EBBA0[type] != 0)
        memcpy(&p->mUnknownC, pSource, lbl_803EBBA0[type]);
}

void fn_801BF434(int type, void *pData)
{
    if (lbl_803EBBA0[type] != 0)
        memset(pData, 0, lbl_803EBBA0[type]);
}

void fn_801BF46C(Block_801BF3C8 *p, float step)
{
    if (lbl_803EBB9C != 0)
        lbl_803EBB9C[p->mUnknown8](p, step);
}

void fn_801BF4A8(Block_801BF3C8 *p, unsigned int frames, float from, float to)
{
    Data1_801BF4A8 data;

    fn_801BF434(1, &data);
    if (from == -1.0f)
        from = p->mUnknown0;
    data.mUnknown4 = frames;
    data.mUnknown0 = from;
    fn_801BF3C8(p, 1, from, &data, to);
}

void fn_801BF530(Block_801BF3C8 *p, unsigned char frames, unsigned char hold, float from, float to)
{
    Data3_801BF530 data;

    fn_801BF434(3, &data);
    if (from == -1.0f)
        from = p->mUnknown0;
    data.mUnknown0 = from;
    data.mUnknown4 = frames;
    data.mUnknown9 = 0;
    data.mUnknown8 = frames;
    data.mUnknownA = hold;
    fn_801BF3C8(p, 3, from, &data, to);
}
