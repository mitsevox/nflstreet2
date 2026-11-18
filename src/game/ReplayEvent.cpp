/* Replay events: the replay object (lbl_803EA368) keeps a list of 60 game
   events (an event id, the elapsed count when it happened, a position, a
   facing value and the player involved). Game code records events here as
   plays happen, and the replay code in src/game/cu_8002B8F8.cpp asks whether
   an event happened inside the recorded window and where. */
#include "game/ReplayEvent.h"

/* One row of _ReplayEvent_aCodeEvents: ReplayEventAddForCode maps mCode to the event id mEvent. */
struct ReplayEventCode_t {
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

/* The address of event slot i's position, &p->mEvents[i].mPos. */
// FAKEMATCH: integer address arithmetic (slot offset + object + field offset) instead of
// &p->mEvents[i].mPos, so the slot sum is formed before the field offset as in the target
#define EVENT_POS(p, i) \
    ((Vector_80039F5C *)((i) * sizeof(ReplayEvent_t) + (unsigned int)(p) + \
                         (unsigned int)&((Type_803EA368 *)0)->mEvents[0].mPos))

static ReplayEventCode_t _ReplayEvent_aCodeEvents[] = {
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
unsigned int ReplayEventFind(Type_803EA368 *p, int id)
{
    unsigned int i;

    for (i = 0; i < 60; i++) {
        if (p->mEvents[i].mId == id) {
            break;
        }
    }
    return i;
}

void ReplayEventAdd(Type_803EA368 *p, int id, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing)
{
    Vector_80039F5C zero = { 0 };
    unsigned int i;

    if (p->mUnknownD90 == 4) {
        return;
    }
    if (ReplayEventExists(p, id)) {
        return;
    }
    i = ReplayEventFind(p, -1);
    if (i < 60) {
        if (pPos) {
            Vector_80039F5C *pDst = EVENT_POS(p, i);

            pDst->mX = pPos->mX;
            pDst->mY = pPos->mY;
            pDst->mZ = pPos->mZ;
        } else {
            Vector_80039F5C *pDst = EVENT_POS(p, i);

            pDst->mX = zero.mX;
            pDst->mY = zero.mY;
            pDst->mZ = zero.mZ;
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

int ReplayEventGetTime(Type_803EA368 *p, int id)
{
    int value = 0;
    unsigned int i = ReplayEventFind(p, id);

    if (i < 60) {
        value = p->mEvents[i].mUnknown04;
    }
    return value;
}

int ReplayEventGetPos(Type_803EA368 *p, int id, float *pOut)
{
    unsigned int i = ReplayEventFind(p, id);

    if (i < 60) {
        Vector_80039F5C *pPos = EVENT_POS(p, i);

        pOut[0] = pPos->mX;
        pOut[1] = pPos->mY;
        pOut[2] = pPos->mZ;
        return 0;
    }
    return -1;
}

Object_80039F5C *ReplayEventGetObject(Type_803EA368 *p, int id)
{
    unsigned int i = ReplayEventFind(p, id);

    if (i < 60) {
        return p->mEvents[i].mpObject;
    }
    return 0;
}

void ReplayEventClearAll(Type_803EA368 *p)
{
    unsigned int i;

    for (i = 0; i < 60; i++) {
        p->mEvents[i].mId = -1;
    }
}

int ReplayEventExists(Type_803EA368 *p, int id)
{
    return ReplayEventFind(p, id) < 60;
}

int ReplayEventInWindow(Type_803EA368 *p, int id)
{
    int result = 0;
    int i;

    if (id == 0) {
        result = 1;
    } else {
        i = ReplayEventFind(p, id);
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

void ReplayEventAddPlayer(Object_80039F5C *p)
{
    if (fn_8011F1A4() || !p->mUnknown2914) {
        ReplayEventAdd(lbl_803EA368, 0x13, p, &p->mMotion.mPos, 0);
    }
}

void ReplayEventAddForCode(Object_80039F5C *p, int code)
{
    int event = 0xFFFF;
    int i = 0;

    while (_ReplayEvent_aCodeEvents[i].mCode != 0xFFFF) {
        if (_ReplayEvent_aCodeEvents[i].mCode == (unsigned short)code) {
            event = _ReplayEvent_aCodeEvents[i].mEvent;
            break;
        }
        i++;
    }
    if (event != 0xFFFF) {
        ReplayEventAdd(lbl_803EA368, event, p, &p->mMotion.mPos, &p->mMotion.mFacing);
    }
}
}
