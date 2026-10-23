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

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

/* View of the block at player +336 driven by fn_8010A640: the packed word at
   +52 holds the mode (top 3 bits), the state, a queued state, a kind and a
   signed 15-bit timer. */
struct Block_8010A640 {
    short mUnknown0;
    char mUnknown2[6];
    Point_8017886C mUnknown8;
    char mUnknown16[8];
    float mUnknown24;
    char mUnknown28[20];
    short mUnknown48;
    unsigned short mUnknown50;
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Count : 4;
    unsigned int mUnknown52Kind : 6;
    int mUnknown52Timer : 15;
    Point_8017886C mUnknown56;
};

extern "C" {
int fn_800A5C04(Object_80039F5C *p, int a, int b);
int fn_800AD9B4(void);
int fn_800CB708(Object_80039F5C *p, int *pIndex, Point_8017886C target, int angle, int beyond);
void fn_800CBB00(Object_80039F5C *p, int index, Point_8017886C target, int angle, int beyond);
void fn_800CC388(Object_80039F5C *p);
int fn_800E1044(Object_80039F5C *p, Vector_80039F5C *pTarget);
int fn_800FF094(Object_80039F5C *p);
void fn_800FF598(Block_8010A640 *pBlock, Object_80039F5C *p, Point_8017886C *pPoint, int angle, float value);
void fn_8009D1AC(Object_80039F5C *p);
int fn_8009D1F4(Object_80039F5C *p);
void fn_801096D4(Object_80039F5C *p);
void fn_80109CA0(Object_80039F5C *p, int animation, unsigned char a, unsigned char b, unsigned char c);
int fn_80109D70(Object_80039F5C *p, Point_8017886C *pOut);
int fn_80109E48(Object_80039F5C *p, int kind, int *pOut);
int fn_80109F34(Object_80039F5C *p);
int fn_8010A07C(Object_80039F5C *p);
int fn_8010A0A0(Object_80039F5C *p, int index);
int fn_8016DAA4(Object_80039F5C *p);
void fn_8016DBE4(Object_80039F5C *p);
void fn_80171DB0(Object_80039F5C *p);
int fn_80177F70(void);
float fn_80178A08(void);
float fn_80178A44(void);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
extern int lbl_803EAF04;
extern float lbl_803EAF0C;
extern unsigned int lbl_803EAF14;
extern float lbl_803EAF18;
extern float lbl_803ECB08;
}

extern "C" int fn_8010A640(Object_80039F5C *p) {
    Block_8010A640 *pBlock = (Block_8010A640 *)&p->mUnknown336;
    int done = 0;

    if (fn_800A5C04(p, p->mMotion.mFacing, p->mMotion.mFacing) == 0) {
        int mode = fn_800AD9B4();

        pBlock->mUnknown52Timer--;
        if (mode == 4 || mode == 7) {
            switch (pBlock->mUnknown52Mode) {
            case 0:
                break;
            case 1:
                if (pBlock->mUnknown48 != -9999 && --pBlock->mUnknown48 <= 0 && (p->mFlags & 4)) {
                    pBlock->mUnknown52State = 0;
                    pBlock->mUnknown52Mode = 0;
                }
                break;
            case 3: {
                float limit = pBlock->mUnknown52State == 2 ? 0.0f : 0.14f;

                if (limit == 0.0f && p->mMotion.mUnknown28 < 0.04) {
                    p->mMotion.mUnknown28 = 0.0f;
                }
                if (p->mMotion.mUnknown28 > limit) {
                    if (fn_8016DAA4(p)) {
                        p->mUnknown512.mUnknown14 = 10;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = 0.08f;
                    } else {
                        p->mUnknown512.mUnknown14 = 1;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = 0.0f;
                    }
                } else {
                    pBlock->mUnknown52Mode = 0;
                    pBlock->mUnknown52State = 0;
                }
                break;
            }
            case 2: {
                int index;

                pBlock->mUnknown48--;
                fn_8009D1F4(p);
                if (fn_8022781C(&p->mMotion.mPos, &pBlock->mUnknown56) < 6.0f && p->mMotion.mUnknown28 > 0.006f &&
                    fn_800CB708(p, &index, pBlock->mUnknown56, p->mMotion.mFacing, 1)) {
                    pBlock->mUnknown52Mode = 5;
                    fn_800CBB00(p, index, pBlock->mUnknown56, p->mMotion.mFacing, 1);
                } else if (pBlock->mUnknown48 <= 0 || fn_800FF094(p) == 1) {
                    if (pBlock->mUnknown48 <= 0) {
                        if (pBlock->mUnknown48 + 1 > 0 &&
                            fn_800CB708(p, &index, pBlock->mUnknown56, p->mMotion.mFacing, 2)) {
                            fn_800CBB00(p, index, pBlock->mUnknown56, p->mMotion.mFacing, 2);
                            pBlock->mUnknown52Mode = 5;
                        }
                    }
                    if (pBlock->mUnknown52Mode != 5) {
                        pBlock->mUnknown52Mode = 0;
                        pBlock->mUnknown52State = 0;
                        p->mUnknown512.mUnknown14 = 1;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = 0.0f;
                        fn_8009D1AC(p);
                        switch (fn_802372EC(0, 5)) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            pBlock->mUnknown52Count = 5;
                            break;
                        case 4:
                            pBlock->mUnknown52Count = 4;
                            break;
                        default:
                            pBlock->mUnknown52Count = 6;
                            break;
                        }
                        pBlock->mUnknown52Count = 5;
                    }
                }
                break;
            }
            case 6:
                if (p->mFlags & 4) {
                    p->mUnknown512.mUnknown14 = 3;
                    p->mFlags &= ~4;
                    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = lbl_803EAF18;
                    pBlock->mUnknown24 = lbl_803EAF18;
                    pBlock->mUnknown52Mode = 2;
                    pBlock->mUnknown0 = 0;
                }
                break;
            case 5:
                if (p->mFlags & 4) {
                    p->mFlags &= ~4;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    p->mUnknown512.mUnknown14 = 3;
                    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    pBlock->mUnknown52Mode = 2;
                    pBlock->mUnknown0 = 0;
                    pBlock->mUnknown8.mX = p->mMotion.mPos.mX;
                    pBlock->mUnknown8.mY = p->mMotion.mPos.mY;
                }
                break;
            case 4:
                fn_8009D1F4(p);
                if (fn_8010A0A0(p, pBlock->mUnknown50)) {
                    pBlock->mUnknown52Mode = 0;
                    fn_8009D1AC(p);
                    pBlock->mUnknown52Timer = lbl_803EAF04;
                    if (pBlock->mUnknown52State == 1) {
                        float length;

                        p->mUnknown512.mUnknown14 = 3;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
                        length = fn_802372EC(0, lbl_803EAF14) + 2.0f;
                        fn_80227538(&pBlock->mUnknown56, p->mMotion.mFacing, length);
                        fn_80227638(&pBlock->mUnknown56, &pBlock->mUnknown56, &p->mMotion.mPos);
                        fn_800FF598(pBlock, p, &pBlock->mUnknown56, p->mMotion.mFacing & 0xFFFFFF, 0.0f);
                        pBlock->mUnknown24 = p->mMotion.mUnknown28 / lbl_803ECB08;
                        pBlock->mUnknown52Mode = 2;
                        if (length > 4.0f && fn_802372EC(0, 3) == 0) {
                            pBlock->mUnknown52Mode = 3;
                        }
                        pBlock->mUnknown48 = 10000;
                    }
                    pBlock->mUnknown52State = 0;
                }
                break;
            default:
                pBlock->mUnknown52Mode = 0;
                break;
            }
            if (pBlock->mUnknown48 != -9999) {
                fn_801096D4(p);
                if (pBlock->mUnknown48 != -9999 && fn_800E1044(p, (Vector_80039F5C *)&pBlock->mUnknown56)) {
                    p->mUnknown1008Word = 30;
                    fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
                    if (fn_80137B40() == p) {
                        fn_80171DB0(p);
                    }
                    pBlock->mUnknown52Mode = 1;
                    pBlock->mUnknown48 = -9999;
                    pBlock->mUnknown52State = 6;
                    done = 1;
                }
            }
            if (pBlock->mUnknown52Mode == 0 && done == 0) {
                if (pBlock->mUnknown52Count != 0) {
                    pBlock->mUnknown52State = pBlock->mUnknown52Count;
                } else {
                    pBlock->mUnknown52State = fn_80109D70(p, &pBlock->mUnknown56);
                }
                if (pBlock->mUnknown52State == 10) {
                    fn_800CC388(p);
                } else if (pBlock->mUnknown52State == 5) {
                    fn_80177F70();
                    fn_8016DBE4(p);
                } else {
                    int result;

                    if (fn_80109E48(p, pBlock->mUnknown52State, &result)) {
                        if (result == 1) {
                            pBlock->mUnknown52Mode = 4;
                        }
                    } else if (fn_80109F34(p)) {
                        pBlock->mUnknown48 = fn_802372EC(0, 120) + 10000;
                    } else if (fn_8010A07C(p)) {
                        pBlock->mUnknown52Mode = 3;
                    } else {
                        pBlock->mUnknown48 = fn_802372EC(0, 120) + 30;
                        p->mUnknown1008Word = 30;
                        fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
                        pBlock->mUnknown52Mode = 1;
                    }
                }
            }
        } else {
            p->mUnknown1008Word = 30;
            fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
            return 1;
        }
        pBlock->mUnknown56.mX =
            CLAMP(pBlock->mUnknown56.mX, lbl_803EAF0C - fn_80178A08(), fn_80178A08() - lbl_803EAF0C);
        pBlock->mUnknown56.mY =
            CLAMP(pBlock->mUnknown56.mY, lbl_803EAF0C - fn_80178A44(), fn_80178A44() - lbl_803EAF0C);
    }
    return 0;
}
