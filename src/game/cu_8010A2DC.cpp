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
#include "game/Class_80297B90.h"

/* View of the block at player +336 that fn_8010A4E8 clears and seeds: two
   halfwords at +48 and +50 and the packed word at +52. */
struct Block_8010A4E8 {
    char mUnknown0[48];
    short mUnknown48;
    short mUnknown50;
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Count : 4;
    unsigned int mUnknown52Kind : 6;
    unsigned int mUnknown52Rest : 15;
};

extern "C" {
void fn_8003AB28(Object_80039F5C *p, Message_800F01CC *pMessage, int value);
unsigned char *fn_8003AB38(Object_80039F5C *p);
int fn_800A5DD0(Object_80039F5C *p);
int fn_800ABCC0(Class_80297B90 *p);
int fn_800AD9B4(void);
void fn_80109CA0(Object_80039F5C *p, int animation, unsigned char a, unsigned char b, unsigned char c);
int fn_8010BD58(Object_80039F5C *p);
void fn_8010BE54(Object_80039F5C *p);
int fn_801486A0(void);
float fn_80178A08(void);
float fn_80178A2C(void);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float e, void *pRecord);
void fn_802276B4(void *pOut, void *pA, void *pB);
}

extern "C" int fn_8010A2DC(Object_80039F5C *p, int a, short b) {
    int result = 0;
    int mode = fn_800AD9B4();

    

    if (fn_801486A0() != 0 && fn_801486A0() != 1 && (mode == 4 || (mode == 7 && (unsigned char)fn_800ABCC0(lbl_803EAA8C))) &&
        fn_801BE648(p->mpUnknown792) != 0xCB && p->mUnknown9[2] != 0) {
        if (*fn_8003AB38(p) != 62) {
            if (fn_8010BD58(p) != 0) {
                fn_8010BE54(p);
            } else {
                Message_800F01CC message;
                Vector_80039F5C toBall;

                fn_801C1F94(&message, 0, 4);
                message.mUnknown1[0] = a;
                message.mId = 62;
                fn_80137D58(fn_801374BC(), &toBall);
                fn_802276B4(&toBall, &toBall, &p->mMotion.mPos);
                if (b == -1) {
                    if (fabsf(p->mMotion.mPos.mY) < fn_80178A2C() - 3.0f &&
                        fabsf(p->mMotion.mPos.mX) < fn_80178A08() - 5.0f && !(p->mFlags & 0x400)) {
                        b = (short)fn_802270A4(&toBall);
                        b += fn_802372EC(0, 100);
                    } else {
                        b = 0;
                    }
                }
                fn_8003AB28(p, &message, b);
            }
            result = 1;
        } else {
            if (p->mFlags & 0x4000) {
                p->mUnknown3040 = 0;
            }
            if (fabsf(p->mMotion.mPos.mY) > fn_80178A2C() - 3.0f || fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 3.0f) {
                p->mUnknown3040 = 0;
            }
        }
    }
    return result;
}

extern "C" int fn_8010A4E8(Object_80039F5C *p) {
    Block_8010A4E8 *pBlock = (Block_8010A4E8 *)&p->mUnknown336;
    int mode = fn_800AD9B4();

    fn_801C1F94(pBlock, 0, 64);
    pBlock->mUnknown50 = -1;
    if (p->mpUnknown800 != (Record_800D81C8 *)(p->mUnknown1244 + 12)) {
        p->mpUnknown800 = (Record_800D81C8 *)(p->mUnknown1244 + 12);
    }
    if (fn_801486A0() == 0) {
        return 1;
    }
    if (mode == 4 || mode == 7 || mode == 8) {
        pBlock->mUnknown52State = p->mpState->mUnknown1;
        pBlock->mUnknown52Count = pBlock->mUnknown52State;
        pBlock->mUnknown52Kind = p->mpState->mUnknown3[0];
        pBlock->mUnknown52Mode = 0;
        pBlock->mUnknown52Rest = pBlock->mUnknown48 = 0;
        if (fn_801BE648(p->mpUnknown792) != 0x4A && fn_801BE648(p->mpUnknown792) != 0xCB && fn_800A5DD0(p) == 0) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0x4A, 1.0f, p);
        }
        p->mFlags &= ~0x10;
    } else {
        p->mUnknown1008Word = 30;
        fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
        return 1;
    }
    return 0;
}
