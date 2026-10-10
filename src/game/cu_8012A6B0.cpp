#include "game/Control_80132090.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800D81C8.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Table_80089904.h"
#include "game/cu_80067C10.h"
#include "game/cu_8003108C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8007F828.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80227638.h"
#include "game/fn_802372EC.h"

/* Player block at +336 as used by fn_8012C548, fn_8012C7E0, fn_8012CAA4,
   fn_8012CAAC and fn_8012CD4C. Only the accessed fields are declared; the
   size is unknown. */
struct State_8012C7E0 {
    Point_8017886C mUnknown0;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    char mUnknown24[20];
    int mUnknown44;
};

extern "C" {
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800A5A8C(int a, void *pA, void *pB);
int fn_800A8444(int team);
int fn_800A8740(void);
int fn_800ABDA4(int team);
short fn_800ACC80(Object_80039F5C *p, short value);
int fn_800B76E8(Object_80039F5C *p);
void fn_800B8344(Object_80039F5C *p);
void fn_800D058C(Object_80039F5C *p);
void fn_800D0660(Object_80039F5C *p, unsigned char *pOut);
int fn_800D0694(Object_80039F5C *p);
int fn_800D5A6C(int a, int b, int c);
int fn_8009AD30(Object_80039F5C *p, int value);
void fn_800D6CC0(Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FD68C(Message_800F01CC *, void *, void *);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
void fn_8011168C(Object_80039F5C *p);
int fn_80110824(Object_80039F5C *p, int a, int b, int c);
int fn_8011E9B4(Object_80039F5C *p);
void fn_8012311C(Object_80039F5C *p, Plan_80121264 *pPlan, int angle);
Entry_801230B8 *fn_80123174(Plan_80121264 *pPlan);
void fn_8012430C(float *pOut, int kind, Object_80039F5C *p);
int fn_801243E0(float *pValues, int a);
void fn_8012B2E0(Object_80039F5C *p, Point_8017886C *pOut);
void fn_8012C3A4(Object_80039F5C *p);
void fn_8012CB98(int a, int b, int angle, Point_8017886C *pOut);
void fn_8012CEF4(Object_80039F5C *p, Control_80132090 *pControl);
void fn_8012CFA0(Object_80039F5C *p);
void fn_8012D258(Object_80039F5C *p);
void fn_8012D4FC(Object_80039F5C *p, int mode);
void fn_8012D8A8(Object_80039F5C *p, Control_80132090 *pControl, int *pMode, Entry_801230B8 *pEntry);
int fn_8012FC08(Object_80039F5C *p, Control_80132090 *pControl);
int fn_8012FDDC(Object_80039F5C *p, Control_80132090 *pControl);
void fn_8013FA8C(int a);
void fn_80148154(void);
int fn_801481B0(void);
void fn_801483C8(void);
int fn_801486A0(void);
int fn_80178320(void);
int fn_801BA568(Object_8016D9B8 *p, Record_800D81C8 *pRecords, int key);
int fn_801BA5A8(Object_8016D9B8 *p, Record_800D81C8 *pRecords, int key, int index);
float fn_801BD660(void *p, int key);
float fn_801BD690(Block_801BD6D4 *p, int key);
int fn_801BE648(void *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227890(void *pA, void *pB);
float fn_8022710C(void *pV);

extern Table_80089904 lbl_8031AABC;
}

extern "C" void fn_8012B268(Object_80039F5C *p)
{
    Message_800F01CC message;
    Point_8017886C point;

    fn_8012B2E0(p, &point);
    fn_801C1F94(&message, 0, 4);
    message.mId = 19;
    fn_800FD68C(&message, &p->mMotion, &point);
    message.mUnknown1[2] = 255;
    fn_800F00D4(0, p->mpState, &message, p);
}

extern "C" Info_80089904 *fn_8012C4B4(int a, int b)
{
    unsigned int i;

    fn_801BBC3C(1, 153, &lbl_8031AABC);
    for (i = 0; i < lbl_8031AABC.mCount; i++) {
        Info_80089904 *pInfo = lbl_8031AABC.mEntries[i].mpInfo;

        if (pInfo->mType == a && pInfo->mValue == b) {
            return pInfo;
        }
    }
    return lbl_8031AABC.mEntries[0].mpInfo;
}

extern "C" void fn_8012C548(Object_80039F5C *p)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;
    Info_80089904 *pInfo = fn_8012C4B4(p->mpState->mUnknown2, p->mpState->mUnknown1);

    state->mUnknown8 = p->mMotion.mFacing & 0xFFFFFF;
    state->mUnknown12 = state->mUnknown8 + pInfo->mUnknown12 & 0xFFFFFF;
    state->mUnknown16 = 0;
}

extern "C" void fn_8012C5A8(Object_80039F5C *p, int value)
{
    Message_800F01CC message;
    int team;

    fn_80067E3C(38, &p->mMotion.mPos, p->mId, 0, 0, 0);
    fn_800D6CC0(p);
    fn_801C1F94(&message, 0, 4);
    message.mId = 20;
    team = p->mpState->mUnknown2;
    if (team == 4) {
        team = 1;
    }
    message.mUnknown1[1] = team;
    message.mUnknown1[0] = p->mpState->mUnknown1;
    message.mUnknown1[2] = value;
    fn_800F00D4(0, p->mpState, &message, p);
}

extern "C" int fn_8012C7E0(Object_80039F5C *p)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;

    state->mUnknown20 = 0;
    fn_8012C548(p);
    fn_8012C3A4(p);
    fn_8012CB98(p->mpState->mUnknown2, p->mpState->mUnknown1, state->mUnknown8 + state->mUnknown16,
                &state->mUnknown0);
    fn_80227638(&state->mUnknown0, &state->mUnknown0, &p->mMotion.mPos);
    if (fn_801BE648(p->mpUnknown792) == 153) {
        fn_800A5A8C(10, p, p);
    }
    return 0;
}

extern "C" int fn_8012CA78()
{
    return 1;
}

extern "C" void fn_8012CA80(unsigned char *p)
{
    if (p[1] == 1) {
        p[1] = 2;
    } else {
        p[1] = 1;
    }
}

extern "C" int fn_8012CAA4(Object_80039F5C *p)
{
    return ((State_8012C7E0 *)&p->mUnknown336)->mUnknown12;
}

extern "C" int fn_8012CAAC(Object_80039F5C *p)
{
    return ((State_8012C7E0 *)&p->mUnknown336)->mUnknown8;
}

extern "C" int fn_8012CCA0(Object_80039F5C *p);

extern "C" int fn_8012CAB4(Object_80039F5C *p)
{
    int angle = 0;
    int other = 0;
    State_80039F5C *pState = p->mpState;

    switch (pState->mUnknown2) {
    case 8:
    case 9: {
        int count = fn_8012CCA0(p);

        if (pState->mUnknown2 == 8 ? count <= 55 : count <= 51) {
            angle = fn_8012CAA4(p) + 0x800000 & 0xFFFFFF;
        } else {
            other = 1;
        }
        break;
    }
    default:
        other = 1;
        break;
    }
    if (other) {
        angle = fn_8012CAA4(p);
    }
    return angle;
}

extern "C" int fn_8012CB50(Message_800F01CC *pMessage)
{
    int angle = 0;
    Info_80089904 *pInfo = fn_8012C4B4(pMessage->mUnknown1[1], pMessage->mUnknown1[0]);

    if (pInfo) {
        angle = pInfo->mUnknown12 & 0xFFFFFF;
    }
    return angle;
}

extern "C" int fn_8012CC04(int a)
{
    int result = 0;
    Info_80089904 *pInfo = fn_8012C4B4(a, 1);

    if (pInfo) {
        result = (int)pInfo->mUnknown24;
    }
    return result;
}

extern "C" int fn_8012CC50(Object_80039F5C *p)
{
    int result = 0;
    int count = fn_8012CCA0(p);
    int limit = fn_8012CC04(p->mpState->mUnknown2);

    if (limit > count) {
        result = limit - count;
    }
    return result;
}

extern "C" int fn_8012CCA0(Object_80039F5C *p)
{
    int result = 0;

    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 153)) {
        int index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 153, 0);
        float start = fn_801BD690(&p->mpUnknown800[index].mUnknown4C, 0xC004);

        result = (int)(fn_801BD660(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0xC004) - start);
    }
    return result;
}

extern "C" void fn_8012CD4C(Object_80039F5C *p, Point_8017886C *pOut)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;

    pOut->mX = state->mUnknown0.mX;
    pOut->mY = state->mUnknown0.mY;
}

extern "C" int fn_8012CE60(Object_80039F5C *p)
{
    int result = fn_800ABDA4(p->mIdBytes[2]) == 0;
    unsigned char i;
    unsigned int count;

    if (fn_800A8740()) {
        result = 1;
    }
    count = fn_80178D18(fn_80178320());
    for (i = 0; i < count; i++) {
        if (fn_80039F5C(fn_80178320(), i)->mMotion.mPos.mY > p->mMotion.mPos.mY) {
            result = 1;
            break;
        }
    }
    return result;
}

extern "C" int fn_8012D1E4(Object_80039F5C *p)
{
    int result = 1;

    if (fn_800A8444(p->mIdBytes[2])) {
        result = fn_8007F828(14) == 1;
    }
    switch (fn_801486A0()) {
    case 0:
    case 2:
    case 3:
        result = 0;
        break;
    }
    return result;
}

extern "C" int fn_8012E590(Object_80039F5C *p, Object_80039F5C *pOther)
{
    State_8012C7E0 *state = (State_8012C7E0 *)&p->mUnknown336;
    int result = 0;

    if (fn_8011E9B4(pOther)) {
        result = 1;
    } else {
        Object_80039F5C *pRef = fn_8009BCE8(&pOther->mUnknown1036);

        if (pRef) {
            Point_8017886C delta;

            fn_80227690(&delta, &pRef->mMotion.mPos, &p->mMotion.mPos);
            if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), state->mUnknown44) <= 0x355554
                && fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing) <= 0x355554) {
                float distance = fn_8022710C(&delta);

                if (distance < fn_80227890(&p->mMotion.mPos, &pOther->mMotion.mPos)) {
                    result = 1;
                }
            }
        }
    }
    return result;
}

extern "C" int fn_8012EA14(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    if (fn_8011E9B4(pOther) && fn_802372EC(0, 100) < (unsigned int)(p->mRatings[0] >> 3 & 0x7FFFFFFF)) {
        Point_8017886C delta;
        int direction;

        fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
        direction = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801CFFD0(pMotion->mFacing, direction) <= 0x11C71B) {
            int side = 1;

            if ((direction - pMotion->mFacing & 0xFFFFFF) <= 0x7FFFFF) {
                side = 2;
            }
            if (fn_80110824(p, 2, side, 0)) {
                return 1;
            }
        }
    }
    return 0;
}

extern "C" int fn_8012F2E0(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b, int c, float d)
{
    return 0;
}

extern "C" int fn_8012F524(Object_80039F5C *p)
{
    unsigned int value = p->mUnknown2914;

    if (value == 1 || value == 2) {
        return 1;
    }
    switch (value) {
    case 3:
    case 16:
    case 17:
    case 18:
    case 21:
    case 22:
        return 2;
    case 0:
    case 13:
    case 14:
    case 15:
    case 25:
        return 1;
    }
    return 0;
}

extern "C" int fn_8012FEAC(Object_80039F5C *p)
{
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;

    fn_80130338(p, pControl);
    fn_80031404(p);
    if (fn_800AD9B4() == 3) {
        pControl->mUnknown0 = fn_8012FA64(p);
        if (fn_80137B40() == p) {
            if (fn_801481B0()) {
                fn_8013FA8C(1);
            }
            fn_80148154();
            fn_801483C8();
        }
        return 0;
    }
    return 1;
}

extern "C" int fn_8012FF30(Object_80039F5C *p)
{
    fn_800A3B58(p, 2, 0);
    return 1;
}

extern "C" int fn_8012FF5C(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;
    Plan_80121264 plan;
    Message_800F01CC message;
    int mode = 0;

    fn_800B8344(p);
    if (p == fn_80137B40()) {
        fn_8012CEF4(p, pControl);
        fn_800D5A6C(0, 0, 0);
        fn_800A3B58(p, 2, 0);
    } else {
        fn_801C1F94(&message, 0, 4);
        if (fn_801486A0() == 0) {
            message.mId = 57;
            message.mUnknown1[0] = fn_801374D4();
        } else {
            message.mId = 33;
        }
        fn_800F053C(0, p->mpState, &message, p);
        return 0;
    }
    if (fn_8010A2DC(p, 0, -1)) {
        p->mUnknown512.mUnknown15 = pControl->mUnknown52;
        return 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if (--pControl->mUnknown49 <= 0) {
            float *pValues = pControl->mValues;
            Entry_801230B8 *pEntry;

            pControl->mUnknown49 = (255 - ((p->mRatings[0] >> 1) + (p->mRatings[2] >> 1))) >> 4;
            pControl->mUnknown40 = 1.0f;
            pControl->mUnknown52 = 1;
            fn_8012430C(pValues, 1, p);
            fn_8012CFA0(p);
            pControl->mUnknown48 = fn_801243E0(pValues, pMotion->mFacing);
            pControl->mUnknown44 = pControl->mUnknown48 << 21;
            fn_8012D4FC(p, mode);
            fn_8012311C(p, &plan, pControl->mUnknown44);
            pEntry = fn_80123174(&plan);
            if (pEntry) {
                int angle = pEntry->mUnknown16;

                pControl->mUnknown44 = angle;
                pControl->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
            }
            fn_8012D8A8(p, pControl, &mode, pEntry);
            fn_8012DDCC(p, pControl, mode);
            fn_8012D258(p);
            pControl->mUnknown0 = fn_8012FA64(p);
            fn_8012F89C(p, pControl, mode);
            if (pControl->mUnknown56.mUnknown6) {
                fn_800D0694(p);
            }
        }
        fn_800D058C(p);
        fn_800D0660(p, &pControl->mUnknown52);
        p->mUnknown512.mUnknown15 = pControl->mUnknown52;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pControl->mUnknown44;
        p->mUnknown512.mUnknown4 = pControl->mUnknown44;
        p->mUnknown512.mUnknown0 = pControl->mUnknown40;
        if (p->mFlags & 0x400000) {
            p->mUnknown512.mUnknown14 = 10;
            p->mUnknown512.mUnknown8 = pMotion->mFacing;
            p->mUnknown512.mUnknown4 = pMotion->mFacing;
            p->mUnknown512.mUnknown0 = 0.5f;
        }
        fn_8012F5A0(p, pControl, &pControl->mUnknown56);
    } else {
        if (fn_800D0694(p)) {
            fn_800D058C(p);
            fn_800D0660(p, &pControl->mUnknown52);
            p->mUnknown512.mUnknown15 = pControl->mUnknown52;
        }
        if (p->mFlags & 0x400000) {
            p->mUnknown512.mUnknown14 = 10;
            p->mUnknown512.mUnknown8 = pMotion->mFacing;
            p->mUnknown512.mUnknown4 = pMotion->mFacing;
            p->mUnknown512.mUnknown0 = 0.5f;
        }
    }
    if (p->mpState->mId == 1) {
        fn_8012FDDC(p, pControl);
        fn_8012FC08(p, pControl);
        fn_8011168C(p);
    }
    return 0;
}

extern "C" int fn_8013028C(Object_80039F5C *p)
{
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;

    pControl->mUnknown44 = 0x400000;
    pControl->mUnknown52 = 0;
    pControl->mUnknown49 = 0;
    pControl->mUnknown56.mUnknown0 = (signed char)(16 - (p->mRatings[2] + p->mRatings[0]) / 32);
    pControl->mUnknown56.mUnknown0 = fn_800ACC80(p, pControl->mUnknown56.mUnknown0);
    pControl->mUnknown56.mUnknown0 = fn_8009AD30(p, pControl->mUnknown56.mUnknown0);
    return 0;
}

extern "C" int fn_80130318(Object_80039F5C *p)
{
    return fn_800B76E8(p);
}

extern "C" void fn_80130338(Object_80039F5C *p, Control_80132090 *pControl)
{
    pControl->mUnknown36 = fn_80177FE0().mY;
    pControl->mUnknown44 = 0;
    pControl->mUnknown49 = 0;
    pControl->mUnknown56.mUnknown0 = (signed char)(16 - (p->mRatings[2] + p->mRatings[0]) / 32);
    pControl->mUnknown56.mUnknown0 = fn_800ACC80(p, pControl->mUnknown56.mUnknown0);
    pControl->mUnknown56.mUnknown0 = fn_8009AD30(p, pControl->mUnknown56.mUnknown0);
    pControl->mUnknown52 = 1;
    pControl->mUnknown40 = 1.0f;
    pControl->mUnknown0 = 0;
    pControl->mUnknown56.mUnknown4 = 0;
    pControl->mUnknown56.mUnknown5 = 0;
    if (fn_801486A0() == 0) {
        if (!(p->mFlags & 0x400)) {
            unsigned char roll = fn_802372EC(0, 100);

            if ((fn_800ABDA4(1) == 0 && roll > 80) || (fn_800ABDA4(1) == 1 && roll > 40)
                || (fn_800ABDA4(1) == 2 && roll != 0)) {
                pControl->mUnknown56.mUnknown6 = 1;
            } else {
                pControl->mUnknown56.mUnknown6 = 0;
            }
        } else {
            pControl->mUnknown56.mUnknown6 = 1;
        }
    } else {
        pControl->mUnknown56.mUnknown6 = 1;
    }
    if (fn_800AD9B4() == 3) {
        pControl->mUnknown0 = fn_8012FA64(p);
    }
    pControl->mUnknown56.mUnknown2 = 0;
}
