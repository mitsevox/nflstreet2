#include "game/Record_803EB25C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8007A334.h"
#include "game/PaletteColor.h"

/* Three bytes read by fn_800840A4. */
struct Rgb_800840A4 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

/* Argument of fn_801476C8. */
struct Args_801476C8 {
    char mUnknown0[2];
    unsigned char mUnknown2;
    Object_8003DEC4 *mUnknown4;
};

extern "C" {
int fn_8003DEB4(void);
void fn_80083E1C(Object_8007A334 *pObject, int a);
void fn_800840A4(Object_8007A334 *pObject, void *pBuffer);
int fn_800A7EF4(unsigned char a);
int fn_800C8744(int team);
int fn_80188030(int a);
void fn_801D0424(void *p, float (*m)[4]);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(float (*m)[4]);
void fn_801D06D4(void *p);
void fn_801D0FB8(Point_80146FDC *pOut);

extern Record_803EB25C *lbl_803EB25C;
extern unsigned int lbl_803EB260;
}

static Color_802DD68C lbl_802DD68C[10] = {
    { 1.0f, 0.0f, 0.0f, 0.25f },
    { 0.0f, 0.0f, 1.0f, 0.25f },
    { 0.0f, 1.0f, 0.0f, 0.25f },
    { 1.0f, 0.8f, 0.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 0.25f, 0.25f, 1.0f, 0.45f },
};

static unsigned char lbl_803EB27C = 1;
static float lbl_803EB280 = 0.45f;

/* Maps step t of n onto the range lo..hi. */
static inline float Interpolate(float t, float lo, float hi, float n)
{
    return t * (hi - lo) / n + lo;
}

extern "C" {

float fn_80146F40(unsigned int index)
{
    if (lbl_803EB25C != 0 && index < lbl_803EB260) {
        return lbl_803EB25C[index].mUnknown20;
    }
    return 0.0f;
}

void fn_80146F74(Object_8003DEC4 *pObject, int index, Point_80146FDC *pOut)
{
    fn_801D04C4();
    fn_801D06D4(pObject->mUnknown908);
    fn_801D0664(pObject->mUnknown44.mUnknown52[index]);
    fn_801D0FB8(pOut);
    fn_801D0544();
}

void fn_80146FCC(void)
{
    lbl_803EB27C = 1;
}

void fn_80146FD8(void)
{
}

void fn_80146FDC(Object_80146094 *pObject)
{
    unsigned int i;

    pObject->mUnknown230 = 1.0f;
    pObject->mUnknown234 = 0;
    pObject->mUnknown238 = -1;
    pObject->mUnknown240 = lbl_802DD68C[8];
    pObject->mUnknown23C = 0;
    pObject->mUnknown554 = 1;
    pObject->mUnknown558 = 0;
    pObject->mUnknown560 = 0;
    for (i = 0; i < 4; i++) {
        Trail_80146FDC *pTrail = &pObject->mTrails[i];

        pTrail->mCount = 0;
        pTrail->mHead = 7;
        pTrail->mToggle = 0;
        switch (i) {
        case 0:
            pTrail->mIndex[0] = 18;
            pTrail->mIndex[1] = 16;
            break;
        case 1:
            pTrail->mIndex[0] = 3;
            pTrail->mIndex[1] = 2;
            break;
        case 2:
            pTrail->mIndex[0] = 24;
            pTrail->mIndex[1] = 22;
            break;
        case 3:
            pTrail->mIndex[0] = 7;
            pTrail->mIndex[1] = 6;
            break;
        }
    }
}

void fn_801470F0(Object_8003DEC4 *pObject)
{
    Object_80146094 *pData = &pObject->mUnknown5188;
    unsigned int i;

    if (--pData->mUnknown55C < 0) {
        pData->mUnknown55C = 3;
        if (--pData->mUnknown554 < 0) {
            pData->mUnknown554 = 1;
        }
        fn_801D0424(pData->mUnknown260[pData->mUnknown554], pObject->mUnknown908);
        pData->mUnknown2E0[pData->mUnknown554] = *(Block_801470F0 *)pObject->mUnknown44.mUnknown48;
        pData->mUnknown448[pData->mUnknown554].x = pObject->mUnknown44.mUnknown8[0];
        pData->mUnknown448[pData->mUnknown554].y = pObject->mUnknown44.mUnknown8[1];
        pData->mUnknown448[pData->mUnknown554].z = pObject->mUnknown44.mUnknown8[2];
        pData->mUnknown460[pData->mUnknown554] = pObject->mUnknown44.mUnknown32;
        pData->mUnknown468[pData->mUnknown554] = *(Half_801470F0 *)pObject->mUnknown280.mUnknown256.mUnknown48;
        fn_801D0424(pData->mUnknown4D4[pData->mUnknown554], pObject->mUnknown44.mUnknown52[13]);
        if (pData->mUnknown560 == 0) {
            if (pData->mUnknown558 != 0) {
                pData->mUnknown558--;
            } else {
                pObject->mUnknown20 &= ~0x20000;
            }
        } else if (pData->mUnknown558 <= 1) {
            pData->mUnknown558++;
        }
    }

    if (fn_800A7EF4(pObject->mUnknown4968) == 0) {
        pData->mUnknown240 = lbl_802DD68C[9];
    } else if (pData->mUnknown238 == -1) {
        pData->mUnknown240 = lbl_802DD68C[8];
    } else {
        pData->mUnknown240 = lbl_802DD68C[pData->mUnknown238];
    }

    if (pObject->mUnknown20 & 0x10000) {
        float count = pData->mUnknown234 + 1;

        if (count > 35.0f) {
            count = 35.0f;
        }
        pData->mUnknown234 = (unsigned int)count;
        pData->mUnknown230 = Interpolate(pData->mUnknown234, 0.05f, 1.0f, 35.0f);
    } else if (pData->mUnknown234 != 0) {
        pObject->mUnknown20 |= 0x10000;
        pData->mUnknown234--;
        pData->mUnknown230 = Interpolate(pData->mUnknown234, 0.05f, 1.0f, 35.0f);
    } else {
        pData->mUnknown234 = 0;
        pData->mUnknown230 = 0.0f;
    }

    for (i = 0; i < 4; i++) {
        Trail_80146FDC *pTrail = &pData->mTrails[i];

        if (pTrail->mCount < 8) {
            pTrail->mCount++;
        }
        fn_80146F74(pObject, pTrail->mIndex[0], &pTrail->mSource[0]);
        fn_80146F74(pObject, pTrail->mIndex[1], &pTrail->mSource[1]);
        if (--pTrail->mHead < 0) {
            pTrail->mHead = 7;
        }
        pTrail->mToggle = pTrail->mToggle == 1 ? 0 : 1;
        pTrail->mPoints[pTrail->mHead] = pTrail->mSource[pTrail->mToggle];
    }
}

void fn_80147598(Object_8003DEC4 *pObject, int bit, unsigned int slot, unsigned char flag)
{
    Object_80146094 *pData = &pObject->mUnknown5188;
    int index;

    pObject->mUnknown20 |= 1 << bit;
    index = -1;
    if (slot <= 8) {
        index = fn_80188030(slot);
    }
    pData->mUnknown238 = index;
    pData->mUnknown23C = flag;
}

void fn_801475F4(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        Object_8003DEC4 *pObject = fn_8003DEC4(i);
        Object_80146094 *pData = &pObject->mUnknown5188;
        Trail_80146FDC *pTrail;
        int j;

        pData->mUnknown230 = 1.0f;
        pData->mUnknown234 = 0;
        pData->mUnknown238 = -1;
        pData->mUnknown240 = lbl_802DD68C[8];
        pData->mUnknown554 = 1;
        pData->mUnknown558 = 0;
        pData->mUnknown560 = 0;
        pTrail = pData->mTrails;
        for (j = 0; j < 4; j++) {
            pTrail->mCount = 0;
            pTrail->mHead = 7;
            pTrail->mToggle = 0;
            pTrail++;
        }
    }
}

void fn_801476C8(Args_801476C8 *pArgs)
{
    Object_8007A334 cursor;
    Rgb_800840A4 rgb;
    PaletteColor color;
    Object_8003DEC4 *pObject = pArgs->mUnknown4;
    int id = fn_800C8744(pArgs->mUnknown2);

    fn_80083E1C(&cursor, 0);
    fn_80084034(&cursor, id, 0);
    fn_800840A4(&cursor, &rgb);
    fn_80083F68(&cursor);
    fn_8007A068(rgb.mUnknown0, &color);
    pObject->mUnknown5188.mUnknown250.mUnknown0 = color.r / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknown4 = color.g / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknown8 = color.b / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknownC = lbl_803EB280;
}

void fn_801477F0(Object_8003DEC4 *pObject)
{
    if (pObject->mUnknown5188.mUnknown560 == 0) {
        pObject->mUnknown20 |= 0x20000;
        pObject->mUnknown5188.mUnknown560 = 1;
        pObject->mUnknown5188.mUnknown558 = 1;
        pObject->mUnknown5188.mUnknown55C = 3;
        pObject->mUnknown5188.mUnknown564 = 0.0f;
    } else {
        pObject->mUnknown5188.mUnknown564 = 0.0f;
    }
}

void fn_80147840(Object_8003DEC4 *pObject)
{
    pObject->mUnknown5188.mUnknown560 = 0;
    pObject->mUnknown5188.mUnknown558 = 0;
    pObject->mUnknown20 &= ~0x20000;
}

void fn_80147860(Object_8003DEC4 *pObject, float step)
{
    if (pObject->mUnknown5188.mUnknown560 == 1) {
        pObject->mUnknown5188.mUnknown564 += step;
        if (pObject->mUnknown5188.mUnknown564 >= 30.0f) {
            fn_80147840(pObject);
        }
    }
}

void fn_801478A8(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        fn_801470F0(fn_8003DEC4(i));
    }
}

unsigned char fn_801478F0(unsigned char a)
{
    unsigned char previous = lbl_803EB27C;

    lbl_803EB27C = a;
    return previous;
}

unsigned char fn_80147900(void)
{
    return lbl_803EB27C;
}

}
