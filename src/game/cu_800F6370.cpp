#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801C1F94.h"

/* Record at player +336 passed to fn_800F4E88, fn_800F4F08, fn_800F5208
   and fn_800F5CBC. Only the accessed members are declared. */
struct Record_800F4E88 {
    Point_8017886C mUnknown0;
    float mUnknown8;
    float mUnknown12;
    char mUnknown16[4];
    int mUnknown20;
    unsigned char mUnknown24;
};

extern "C" {
int fn_800F4E88(Object_80039F5C *p, Record_800F4E88 *pRecord);
void fn_800F4F08(Object_80039F5C *p, Record_800F4E88 *pRecord);
int fn_800F5208(Object_80039F5C *p, Record_800F4E88 *pRecord);
int fn_800F5CBC(Object_80039F5C *p, Record_800F4E88 *pRecord);
void fn_800F60BC(Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
void fn_8011E194(Object_80039F5C *p, unsigned char mask);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_8011F1CC(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_8011F2F8(void);
int fn_801783AC(int bit);
int fn_801CFFD0(int a, int b);
extern float lbl_803ECB08;
}

extern "C" int fn_800F6370(Object_80039F5C *p) {
    int result = 0;
    Record_800F4E88 *pRecord = (Record_800F4E88 *)&p->mUnknown336;
    Message_800F01CC message;
    int direction;

    if (p == fn_80137B40()) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
        fn_801C1F94(&message, 0, sizeof(message));
        message.mId = 1;
        fn_800F053C(0, p->mpState, &message, p);
        result = 1;
    } else {
        fn_8010A2DC(p, 0, -1);
        fn_800F60BC(p);
        if (!(p->mFlags & 0x4000)) {
            if (fn_800F5208(p, pRecord)) {
                fn_8011E3EC(p, 0);
                result = 1;
                fn_8011E240(p);
                p->mUnknown512.mUnknown15 = result;
                direction = fn_800F5CBC(p, pRecord);
                p->mUnknown512.mUnknown14 = result;
                p->mUnknown512.mUnknown4 = direction;
                p->mUnknown512.mUnknown8 = direction;
                p->mUnknown512.mUnknown0 = pRecord->mUnknown12;
                fn_801C1F94(&message, 0, sizeof(message));
                if (fn_801783AC(13) == 0 && fn_8013BA58(fn_801374BC(), 0) != 4
                    && fn_801783AC(0) == 0 && fn_8011F1CC() != 0) {
                    message.mId = 31;
                    if (fn_8011F2F8() != 0) {
                        message.mUnknown1[1] = result;
                        if (fn_801783AC(0) == 0) {
                            fn_8011E194(p, 1);
                        }
                        int found = fn_800F06F4(0, p->mpState, 19, 0xFFFF) == 0xFFFF ? 0 : 1;

                        if (found) {
                            message.mUnknown1[0] = 32;
                            fn_800F05E4(0, p->mpState, &message, p);
                        } else {
                            fn_800F053C(0, p->mpState, &message, p);
                        }
                    } else {
                        fn_800F053C(0, p->mpState, &message, p);
                    }
                } else {
                    message.mId = 33;
                    fn_800F053C(0, p->mpState, &message, p);
                }
                result = 1;
            } else {
                if (pRecord->mUnknown24 == 0) {
                    if (fn_800F4E88(p, pRecord)) {
                        pRecord->mUnknown24 = 1;
                        if (fn_801783AC(13) == 0
                            && (p->mpState->mUnknown3[1] == 47 || p->mpState->mUnknown3[1] == 72)) {
                            result = 1;
                        }
                    }
                } else {
                    fn_800F4F08(p, pRecord);
                }
                if (fn_801CFFD0(pRecord->mUnknown20, p->mMotion.mFacing) <= 0x155554) {
                    p->mUnknown512.mUnknown15 = 1;
                }
                direction = fn_800F5CBC(p, pRecord);
                if (p->mMotion.mUnknown28 > lbl_803ECB08 * 0.05f
                    && fn_801CFFD0(p->mMotion.mUnknown32, p->mMotion.mFacing) > 0x355555
                    && fn_801CFFD0(p->mMotion.mUnknown32, pRecord->mUnknown20) > 0x400000) {
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = pRecord->mUnknown20;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    p->mUnknown512.mUnknown4 = pRecord->mUnknown20;
                } else {
                    p->mUnknown512.mUnknown4 = direction;
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = direction;
                    p->mUnknown512.mUnknown0 = pRecord->mUnknown12;
                }
            }
        } else {
            fn_8011E3EC(p, 0);
            fn_8011E240(p);
            fn_801C1F94(&message, 0, sizeof(message));
            if (fn_801783AC(13) == 0 && fn_8013BA58(fn_801374BC(), 0) != 4
                && fn_801783AC(0) == 0 && fn_8011F1CC() != 0) {
                message.mId = 31;
                if (fn_8011F2F8() != 0) {
                    message.mUnknown1[1] = 1;
                    if (fn_801783AC(0) == 0) {
                        fn_8011E194(p, 1);
                    }
                    int found = fn_800F06F4(0, p->mpState, 19, 0xFFFF) == 0xFFFF ? 0 : 1;

                    if (found) {
                        message.mUnknown1[0] = 32;
                        fn_800F05E4(0, p->mpState, &message, p);
                    } else {
                        fn_800F053C(0, p->mpState, &message, p);
                    }
                } else {
                    fn_800F053C(0, p->mpState, &message, p);
                }
            } else {
                message.mId = 33;
                fn_800F053C(0, p->mpState, &message, p);
            }
            result = 1;
        }
    }
    return result;
}
