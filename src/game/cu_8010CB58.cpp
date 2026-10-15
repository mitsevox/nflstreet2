#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801BE60C.h"
#include "game/Record_800DB60C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801BA2A8.h"
#include "game/Table_80089904.h"
#include "game/fn_8022781C.h"
#include "game/fn_80227638.h"

/* View of the block at player +336 as fn_801113DC accesses it. Only the
   accessed fields are declared. */
struct State_801113DC {
    int mUnknown0;
    float mUnknown4;
    char mUnknown8[4];
    unsigned char mUnknown12;
    char mUnknown13[3];
    Object_80039F5C *mpUnknown16;
    Record_800DB60C mUnknown20;
};

struct State_8010CAE8 {
    char mUnknown0[12];
    float mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    char mUnknown21[3];
    int mUnknown24;
    char mUnknown28[16];
    float mUnknown44;
    float mUnknown48;
};

/* View of the block at player +336 with the record at +32, as fn_8010D090
   reads it from the ball carrier. Only the accessed fields are declared. */
struct State_8010D090 {
    char mUnknown0[32];
    Record_800DB60C mUnknown32;
};

struct State_8010D80C {
    Vector_80039F5C mUnknown0;
    char mUnknown12[4];
    float mUnknown16;
    int mUnknown20;
    unsigned short mUnknown24;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

extern "C" {
int fn_8010C8F8(Object_80039F5C *p);
void fn_8010C98C(Object_80039F5C *p);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801783AC(int bit);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_8009BD60(Object_80039F5C *p);
int fn_801BA5A8(void *pA, void *pB, int id, int index);
int fn_801BA6B0(Entry_800EAC9C *pEntry);
void fn_801BA6BC(Entry_800EAC9C *pEntry, int flag);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800B8344(Object_80039F5C *p);
int fn_800FD580(Object_80039F5C *p);
void fn_800D5A28(void);
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
int fn_801486A0(void);
Object_80039F5C *fn_8010DA38(Object_80039F5C *p, Object_80039F5C *pExclude);
unsigned char *fn_8003AB38(Object_80039F5C *p);
int fn_80099734(Object_80039F5C *p, Object_80137ABC *pBall, int a, int mode, void *pBlock, int b, int c, int d, int e,
                float range);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
int fn_8010CE90(Object_80039F5C *p, Object_80137ABC *pBall);
void fn_8010CFD4(Object_80039F5C *p);
void fn_80227384(void *pOut, void *pIn, int angle);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
extern Table_80089904 lbl_80319ED8;
extern float lbl_803EAF48;
extern float lbl_803EAF4C;
extern float lbl_803EAF54;
extern float lbl_803ECB08;
}

extern "C" int fn_8010CB58(Object_80039F5C *p) {
    int result = 0;
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;
    int anim;

    fn_800B8344(p);
    anim = fn_801BE648(p->mpUnknown792);
    switch (pState->mUnknown20) {
    case 0:
        if (anim == 30 || anim == 31 || anim == 202 || anim == 200) {
            p->mUnknown512.mUnknown14 = 0;
            pState->mUnknown20 = 1;
        } else {
            Object_80039F5C *pCarrier;

            result = fn_800FD580(p);
            pCarrier = fn_80137B40();
            if (pCarrier != 0 && pCarrier->mpState->mId == 18 && (p->mFlags & 0x4000)) {
                result = 1;
            }
            if (fn_8010C8F8(p)) {
                fn_8010C98C(p);
                pState->mUnknown20 = 1;
            }
        }
        break;
    case 1:
        if (fn_80137B40() == p && anim == 74) {
            pState->mUnknown20 = 2;
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            pState->mUnknown24 = 20;
            pState->mUnknown20 = 2;
        } else if (!(anim == 30 || anim == 31 || anim == 202 || anim == 200)) {
            if (anim == 78) {
                p->mUnknown512.mUnknown14 = 0;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pState->mUnknown16;
                p->mUnknown512.mUnknown4 = pState->mUnknown16;
                p->mUnknown512.mUnknown0 = pState->mUnknown12;
            }
        }
        break;
    case 2: {
        int pass = fn_800F06F4(0, p->mpState, 18, 0xFFFF) != 0xFFFF;
        int dive = fn_800F06F4(0, p->mpState, 26, 0xFFFF) != 0xFFFF;
        int pitch = fn_800F06F4(0, p->mpState, 25, 0xFFFF) != 0xFFFF;

        if (p == fn_80137B40() && !pass && !dive && !pitch) {
            Message_800F01CC message;

            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = 0.72f;
        } else if (pass) {
            p->mUnknown512.mUnknown14 = 1;
            result = 1;
            p->mUnknown512.mUnknown8 = pState->mUnknown16;
            p->mUnknown512.mUnknown4 = pState->mUnknown16;
            p->mUnknown512.mUnknown0 = pState->mUnknown12;
        } else if (--pState->mUnknown24 < 0) {
            result = 1;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = pState->mUnknown16;
            p->mUnknown512.mUnknown4 = pState->mUnknown16;
            p->mUnknown512.mUnknown0 = pState->mUnknown12;
        }
        break;
    }
    }
    return result;
}

extern "C" void fn_8010CEB8(Object_80039F5C *p, int kind) {
    Message_800F01CC message;
    float speed = p->mUnknown528.mUnknown0;
    float value;

    if (p->mIdBytes[3] == 1) {
        float scale = speed * 0.0052287583f;

        speed = scale * p->mRatings[4];
    }
    value = speed < lbl_803EAF48 ? lbl_803EAF48 : (speed > lbl_803EAF4C ? lbl_803EAF4C : speed);
    value *= 255.0f;
    message.mId = 68;
    message.mUnknown1[0] = 160;
    message.mUnknown1[1] = p->mMotion.mFacing >> 17;
    if (value >= 0.0f) {
        message.mUnknown1[2] = (int)(value > 255.0f ? 255.0f : value);
    } else {
        message.mUnknown1[2] = 0;
    }
    fn_800F00D4(0, p->mpState, &message, p);
    if (kind == 11) {
        fn_800D5A28();
    }
}

extern "C" int fn_8010D090(Object_80039F5C *p) {
    int result = 0;
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;
    Object_80039F5C *pCarrier;
    Message_800F01CC message;
    Message_800F01CC request;

    fn_800B8344(p);
    pCarrier = fn_80137B40();
    fn_8010A2DC(p, 0, 0);
    if (*fn_8003AB38(p) == 57) {
        p->mUnknown3040 = 0;
    }
    if (pCarrier == p) {
        int index = fn_800F06F4(0, p->mpState, 26, 0xFFFF);

        if (index == 0xFFFF && fn_800F06F4(0, p->mpState, 18, 0xFFFF) == index) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
        } else {
            result = 1;
        }
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        p->mUnknown512.mUnknown15 = 0;
    } else {
        Object_80137ABC *pBall = fn_801374BC();

        if (fn_8013BA58(pBall, 0) == 3) {
            int handle = fn_80099734(p, pBall, 0, 1, &pState->mUnknown24, 1, 0, 0, result, 120.0f);

            if (handle != 0x1FFFFFFF && fn_80099F04(p, handle, fn_801374E0(pBall)) == 1) {
                return 0;
            }
            result = fn_8010CE90(p, pBall);
        } else {
            Record_800DB60C *pRecord = 0;

            if (pCarrier != 0) {
                switch (pCarrier->mpState->mId) {
                case 10:
                case 58:
                    pRecord = &((State_801113DC *)&pCarrier->mUnknown336)->mUnknown20;
                    break;
                case 16:
                    pRecord = &((State_8010D090 *)&pCarrier->mUnknown336)->mUnknown32;
                    break;
                }
                if (pRecord != 0 && pRecord->mUnknown1 == 0) {
                    switch (p->mpState[1].mId) {
                    case 0:
                    case 18:
                    case 26:
                        fn_801C1F94(&request, 0, 4);
                        request.mId = 90;
                        request.mUnknown1[0] = 0;
                        request.mUnknown1[1] = 224;
                        fn_800F053C(0, p->mpState, &request, p);
                        break;
                    }
                    result = 1;
                }
            }
            if (fn_8022781C(&pState->mUnknown44, &p->mMotion) > (unsigned int)p->mpState->mUnknown1 * 0.125f) {
                result = 1;
            }
        }
        if (result != 1) {
            fn_800FD580(p);
            fn_8010CFD4(p);
        }
    }
    return result;
}

extern "C" void fn_8010D434(Object_80039F5C *p, State_8010D80C *pState) {
    p->mFlags &= ~4;
    if (p->mUnknown1008.mUnknown0 == 2) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 176, p, 1.0f);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 37, p, 1.0f);
    }
    if (pState->mUnknown27) {
        Record_800D81C8 *pRecords = p->mpUnknown800;
        Record_800D81C8 *pRecord;

        pRecord = pRecords + fn_801BA5A8(p->mpUnknown796, pRecords, 37, 0);
        fn_801BA6BC(pRecord, fn_801BA6B0(pRecord) == 0);
    }
    pState->mUnknown26 = 1;
}

extern "C" void fn_8010D508(Object_80039F5C *p) {
    int near = 0;
    State_80039F5C *pQueue = p->mpState;
    State_8010D80C *pState = (State_8010D80C *)&p->mUnknown336;
    Info_80089904 *pInfo;
    Vector_80039F5C offset;
    Vector_80039F5C target;
    int index;

    pState->mUnknown27 = near;
    fn_8009BD60(p);
    if (fn_8022781C(&p->mMotion, &fn_80137AD0(fn_801374BC())->mMotion) < 2.5f) {
        fn_801BBC3C(1, 37, &lbl_80319ED8);
        near = 1;
        p->mUnknown1008.mUnknown0 = 1;
    } else {
        fn_801BBC3C(1, 176, &lbl_80319ED8);
        p->mUnknown1008.mUnknown0 = 2;
    }
    p->mUnknown1008.mUnknown1 = pQueue->mUnknown1;
    index = fn_8009C4B0(&lbl_80319ED8, &p->mUnknown1008);
    pState->mUnknown24 = lbl_80319ED8.mEntries[index].mUnknown0;
    pState->mUnknown20 = lbl_80319ED8.mEntries[index].mUnknown2;
    pInfo = lbl_80319ED8.mEntries[index].mpInfo;
    pState->mUnknown16 = pInfo->mUnknown32;
    offset.mX = pInfo->mUnknown8Float;
    offset.mY = pInfo->mUnknown12Float;
    offset.mZ = pInfo->mUnknown16Float;
    target.mX = pInfo->mUnknown20Float;
    target.mY = pInfo->mUnknown24;
    target.mZ = pInfo->mUnknown28;
    pState->mUnknown0 = offset;
    fn_80227690(pState, pState, &target);
    fn_80227264(&pState->mUnknown0, &pState->mUnknown0, p->mUnknown768);
    fn_80227638(pState, pState, &target);
    fn_80227384(pState, pState, p->mMotion.mFacing);
    fn_8022765C(pState, pState, &p->mMotion);
    if (near) {
        fn_8010D434(p, pState);
    } else {
        pState->mUnknown26 = near;
    }
}

extern "C" int fn_8010D834(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pRecords,
                           Object_80039F5C *p, int mode) {
    if (mode == 0) {
        if (p->mpState->mId == 56) {
            State_8010D80C *pState = (State_8010D80C *)&p->mUnknown336;

            fn_801BA2A8(pA, pRecords, pState->mUnknown24, pState->mUnknown20, key, p, 1.0f);
        } else {
            int index = fn_8009C4B0(pTable, &p->mUnknown1008);

            if (index >= 0) {
                fn_801BA2A8(pA, pRecords, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key,
                            p, 1.0f);
            }
        }
    }
    return 0;
}

extern "C" int fn_8010D8F4(Object_80039F5C *p) {
    int result = 0;
    Object_80039F5C *pCarrier;

    if ((fn_801486A0() != 2 || fn_801783AC(20)) && (pCarrier = fn_80137B40()) != 0 &&
        pCarrier->mpState->mId == 1 && pCarrier->mMotion.mPos.mY > p->mMotion.mPos.mY &&
        fn_8022781C(&pCarrier->mMotion, &p->mMotion) < 7.0f) {
        Object_80039F5C *pOther = fn_8010DA38(pCarrier, p);

        if (pOther == 0) {
            result = 1;
        } else if (p->mRatings[4] > pOther->mRatings[4] * lbl_803EAF54) {
            Message_800F01CC message;

            result = 1;
            fn_801C1F94(&message, 0, 4);
            message.mId = 33;
            fn_800F053C(0, pOther->mpState, &message, pOther);
        }
    }
    return result;
}
