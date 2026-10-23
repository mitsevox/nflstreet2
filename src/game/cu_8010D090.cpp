#include "engine/cu_801B9F00.h"
#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"
#include "game/Block_801BE60C.h"

/* View of the block at player +336 used by fn_8010D090: an output slot at
   +24 and a position at +44. */
struct Block_8010D090 {
    char mUnknown0[24];
    char mUnknown24[20];
    Vector_80039F5C mUnknown44;
};

/* View of the ball carrier's block at player +336: fn_8010D090 checks byte
   1 of the record at +20 or +32, chosen by the carrier's state. */
struct Carrier_8010D090 {
    char mUnknown0[20];
    unsigned char mUnknown20[12];
    unsigned char mUnknown32[4];
};

extern "C" {
void fn_800B8344(Object_80039F5C *p);
int fn_800FD580(Object_80039F5C *p);
int fn_80099734(Object_80039F5C *p, Object_80137ABC *pBall, int a, int mode, void *pBlock, int b, int c, int d, int e,
                float range);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_8010CE90(Object_80039F5C *p, Object_80137ABC *pBall);
void fn_8010CFD4(Object_80039F5C *p);
unsigned char *fn_8003AB38(Object_80039F5C *p);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
extern float lbl_803ECB08;
}

extern "C" int fn_8010D090(Object_80039F5C *p) {
    Block_8010D090 *pBlock = (Block_8010D090 *)&p->mUnknown336;
    int result = 0;
    Object_80039F5C *pCarrier;
    Message_800F01CC message;
    Message_800F01CC message2;

    fn_800B8344(p);
    pCarrier = fn_80137B40();
    fn_8010A2DC(p, 0, 0);
    if (*fn_8003AB38(p) == 0x39) {
        p->mUnknown3040 = 0;
    }
    if (pCarrier == p) {
        int id = fn_800F06F4(0, p->mpState, 0x1A, 0xFFFF);

        if (id == 0xFFFF && fn_800F06F4(0, p->mpState, 0x12, 0xFFFF) == id) {

            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
        } else {
            result = 1;
        }
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        p->mUnknown512.mUnknown15 = 0;
    } else {
        Object_80137ABC *pBall = fn_801374BC();

        if (fn_8013BA58(pBall, 0) == 3) {
            int angle = fn_80099734(p, pBall, 0, 1, pBlock->mUnknown24, 1, 0, 0, 0, 120.0f);

            if (angle != 0x1FFFFFFF && fn_80099F04(p, angle, fn_801374E0(pBall)) == 1) {
                return 0;
            }
            result = fn_8010CE90(p, pBall);
        } else {
            unsigned char *pRecord = 0;

            if (pCarrier != 0) {
                switch (pCarrier->mpState->mId) {
                case 10:
                case 0x3A:
                    pRecord = ((Carrier_8010D090 *)&pCarrier->mUnknown336)->mUnknown20;
                    break;
                case 16:
                    pRecord = ((Carrier_8010D090 *)&pCarrier->mUnknown336)->mUnknown32;
                    break;
                }
                if (pRecord != 0 && pRecord[1] == 0) {
                    switch (p->mpState[1].mId) {
                    case 0:
                    case 0x12:
                    case 0x1A:
                        fn_801C1F94(&message2, 0, 4);
                        message2.mId = 0x5A;
                        message2.mUnknown1[0] = 0;
                        message2.mUnknown1[1] = 0xE0;
                        fn_800F053C(0, p->mpState, &message2, p);
                        break;
                    }
                    result = 1;
                }
            }
            if (fn_8022781C(&pBlock->mUnknown44, &p->mMotion.mPos) > (float)p->mpState->mUnknown1 * 0.125f) {
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
