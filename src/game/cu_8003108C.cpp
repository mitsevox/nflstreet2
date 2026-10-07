/* Event list of the replay object (lbl_803EA368): 60 slots at +0xDFC that
   record an event id with the fn_8023790C value, a position, a facing
   value and a player. The replay code in src/game/cu_8002B8F8.cpp adds and
   queries events through these functions. Neutral file name; the whole file is a
   draft compiled only for comparison. */
#include "game/cu_8003108C.h"

/* One row of lbl_802CCA34: fn_8003145C maps mCode to the event id mEvent. */
struct Row_802CCA34 {
    unsigned short mCode;
    int mEvent;
    int mUnknown8;
};

extern "C" {
int fn_8002D0AC(Type_803EA368 *p);
int fn_8002D0D0(Type_803EA368 *p);
int fn_8002D158(Type_803EA368 *p);
int fn_8011F1A4(void);
int fn_8023790C(void);
}

static Row_802CCA34 lbl_802CCA34[] = {
    { 0x02, 0x37, 0 },
    { 0x03, 0x37, 0 },
    { 0x04, 0x37, 0 },
    { 0x05, 0x37, 0 },
    { 0x06, 0x37, 0 },
    { 0x07, 0x37, 0 },
    { 0x08, 0x37, 0 },
    { 0x09, 0x37, 0 },
    { 0x0A, 0x37, 0 },
    { 0x12, 0x36, 0 },
    { 0x13, 0x36, 0 },
    { 0x14, 0x36, 0 },
    { 0x15, 0x36, 0 },
    { 0x16, 0x36, 0 },
    { 0x17, 0x36, 0 },
    { 0x18, 0x36, 0 },
    { 0x22, 0x3A, 0 },
    { 0x23, 0x3A, 0 },
    { 0xFFFF, 0xFFFF, 0 },
};

extern "C" {
unsigned int fn_8003108C(Type_803EA368 *p, int id)
{
    unsigned int i;

    for (i = 0; i < 60; i++) {
        if (p->mEvents[i].mId == id) {
            break;
        }
    }
    return i;
}

void fn_800310C0(Type_803EA368 *p, int id, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing)
{
    Vector_80039F5C zero = { 0 };
    unsigned int i;

    if (p->mUnknownD90 == 4) {
        return;
    }
    if (fn_800312FC(p, id)) {
        return;
    }
    i = fn_8003108C(p, -1);
    if (i < 60) {
        if (pPos) {
            p->mEvents[i].mPos.mX = pPos->mX;
            p->mEvents[i].mPos.mY = pPos->mY;
            p->mEvents[i].mPos.mZ = pPos->mZ;
        } else {
            p->mEvents[i].mPos.mX = zero.mX;
            p->mEvents[i].mPos.mY = zero.mY;
            p->mEvents[i].mPos.mZ = zero.mZ;
        }
        if (pFacing) {
            p->mEvents[i].mFacing = *pFacing;
        } else {
            p->mEvents[i].mFacing = 0;
        }
        p->mEvents[i].mId = id;
        p->mEvents[i].mpObject = pObject;
        p->mEvents[i].mUnknown04 = fn_8023790C();
        if (id == 0x34) {
            p->mEvents[i].mUnknown04 -= 6;
        }
    }
}

int fn_800311E4(Type_803EA368 *p, int id)
{
    int value = 0;
    unsigned int i = fn_8003108C(p, id);

    if (i < 60) {
        value = p->mEvents[i].mUnknown04;
    }
    return value;
}

int fn_8003122C(Type_803EA368 *p, int id, float *pOut)
{
    unsigned int i = fn_8003108C(p, id);

    if (i < 60) {
        Vector_80039F5C *pPos = &p->mEvents[i].mPos;

        pOut[0] = pPos->mX;
        pOut[1] = pPos->mY;
        pOut[2] = pPos->mZ;
        return 0;
    }
    return -1;
}

Object_80039F5C *fn_80031294(Type_803EA368 *p, int id)
{
    unsigned int i = fn_8003108C(p, id);

    if (i < 60) {
        return p->mEvents[i].mpObject;
    }
    return 0;
}

void fn_800312DC(Type_803EA368 *p)
{
    unsigned int i;

    for (i = 0; i < 60; i++) {
        p->mEvents[i].mId = -1;
    }
}

int fn_800312FC(Type_803EA368 *p, int id)
{
    return fn_8003108C(p, id) < 60;
}

int fn_80031328(Type_803EA368 *p, int id)
{
    int result = 0;
    int i;

    if (id == 0) {
        result = 1;
    } else {
        i = fn_8003108C(p, id);
        if (i < 60) {
            if (fn_8002D0AC(p)) {
                result = fn_8002D158(p) <= p->mEvents[i].mUnknown04;
            } else {
                int inside = 0;

                if (fn_8002D158(p) <= p->mEvents[i].mUnknown04) {
                    inside = fn_8002D158(p) + fn_8002D0D0(p) >= p->mEvents[i].mUnknown04;
                }
                result = inside;
            }
        }
    }
    return result;
}

void fn_80031404(Object_80039F5C *p)
{
    if (fn_8011F1A4() || !p->mUnknown2914) {
        fn_800310C0(lbl_803EA368, 0x13, p, &p->mMotion.mPos, 0);
    }
}

void fn_8003145C(Object_80039F5C *p, int code)
{
    int event = 0xFFFF;
    int i = 0;

    while (lbl_802CCA34[i].mCode != 0xFFFF) {
        if (lbl_802CCA34[i].mCode == (unsigned short)code) {
            event = lbl_802CCA34[i].mEvent;
            break;
        }
        i++;
    }
    if (event != 0xFFFF) {
        fn_800310C0(lbl_803EA368, event, p, &p->mMotion.mPos, &p->mMotion.mFacing);
    }
}
}
