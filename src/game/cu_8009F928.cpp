#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Team_80167A8C.h"
#include "game/cu_80136B1C.h"
#include "game/Message_800F01CC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_8012CAB4(Object_80039F5C *p);
float fn_8012CD60(Object_80039F5C *p, float scale);
void fn_80227538(Point_80167910 *pOut, int angle, float length);
void fn_80227638(void *pOut, void *pA, void *pB);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801783AC(int bit);
int fn_80178320(void);
}

extern float lbl_803ED6CC;
extern float lbl_803ECB08;
extern float lbl_803EA9C4;
extern float lbl_803EA9C8;
extern float lbl_803EA9CC;

/* p's spot projected ahead along its heading: for state 20 by the move
   kind (predict set) or the fixed turn of the move kind, scaled by
   fn_8012CD60; otherwise by p's speed rating. distance scales the step. */
extern "C" void fn_8009F928(Object_80039F5C *p, Point_8017886C *pOut, unsigned int distance, int predict)
{
    if (p != 0) {
        if (pOut != 0) {
            int angle;
            float length;
            Point_80167910 step;

            pOut->mX = p->mMotion.mPos.mX;
            pOut->mY = p->mMotion.mPos.mY;
            if (p->mpState->mId == 20) {
                float scale;

                if (predict != 0) {
                    angle = fn_8012CAB4(p);
                    switch (p->mpState->mUnknown2) {
                    case 8:
                    case 9:
                        scale = 0.5f;
                        break;
                    case 5:
                    case 11:
                        scale = 0.25f;
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 6:
                    case 7:
                    case 10:
                    default:
                        scale = 1.0f;
                        break;
                    }
                } else {
                    distance = 30;
                    switch (p->mpState->mUnknown2) {
                    case 8:
                    case 9:
                        angle = 0xE00000;
                        scale = 1.0f;
                        if (p->mpState->mUnknown1 == 2) {
                            angle = 0xA00000;
                        }
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 7:
                    case 11:
                        angle = 0x400000;
                        scale = 1.0f;
                        break;
                    case 6:
                        angle = 0xC00000;
                        scale = 1.0f;
                        break;
                    default:
                        angle = p->mMotion.mUnknown32;
                        scale = 1.0f;
                        break;
                    }
                }
                length = fn_8012CD60(p, scale) * (float)distance;
            } else {
                float base = lbl_803ED6CC;

                angle = p->mMotion.mUnknown32;
                length = lbl_803ECB08 * ((1.0f - base) * (p->mRatings[4] / 255.0f) + base) * (float)distance;
            }
            fn_80227538(&step, angle, length);
            fn_80227638(pOut, pOut, &step);
        }
    } else if (pOut != 0) {
        pOut->mX = pOut->mY = 0.0f;
    }
}

/* Rolls whether p reacts to a loose ball (ball state 4 with play bit 24, 11
   or 12) within lbl_803EA9C4 of it: p's team rolls rating 8 against
   lbl_803EA9C8 and sends message 24, the other team rolls rating 3 against
   a distance-weighted chance and sends message 23 with the ball index.
   Returns whether a message was sent. The code matches, but the target
   pool holds this function's 1.0f before 255.0f and 2^31, which this
   source emits in the opposite order. */
extern "C" int fn_8009FB60(Object_80039F5C *p)
{
    int sent = 0;
    Object_80137ABC *pBall = fn_801374BC();

    if ((unsigned short)fn_8013BA58(pBall, 0) == 4 && (fn_801783AC(24) || fn_801783AC(11) || fn_801783AC(12))) {
        Vector_80039F5C spot;
        float distance;

        fn_80138064(pBall, &spot);
        distance = fn_8022781C(&spot, &p->mMotion.mPos);
        if (distance < lbl_803EA9C4) {
            Message_800F01CC message;

            if (p->mIdBytes[2] == fn_80178320()) {
                short rating = p->mRatings[8];

                if (fn_802372EC(0, (unsigned int)(lbl_803EA9C8 * 255.0f)) < rating) {
                    fn_801C1F94(&message, 0, sizeof(message));
                    sent = 1;
                    message.mId = 24;
                    message.mUnknown1[0] = 0;
                    fn_800F053C(0, p->mpState, &message, p);
                }
            } else {
                short rating = p->mRatings[3];
                float chance = ((1.0f - (lbl_803EA9C4 - distance) / lbl_803EA9C4) * lbl_803EA9CC + 1.0f) * 255.0f;

                if (fn_802372EC(0, (unsigned int)chance) < rating) {
                    fn_801C1F94(&message, 0, sizeof(message));
                    sent = 1;
                    message.mId = 23;
                    message.mUnknown1[0] = fn_801374E0(pBall);
                    fn_800F053C(0, p->mpState, &message, p);
                }
            }
        }
    }
    return sent;
}
