#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801C1F94.h"

/* Player block at +336 as used by fn_800E8420 and fn_800E8554. */
struct State_800E8420 {
    float mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    short mUnknown6;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    char mUnknown12[4];
    unsigned char mUnknown16;
    unsigned char mUnknown17;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
};

extern "C" {
int fn_800D0B90(Object_80039F5C *p);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
int fn_800E73D4(Object_80039F5C *p);
int fn_800E745C(Object_80039F5C *p);
void fn_800E7588(Object_80039F5C *p, State_800E8420 *pState);
void fn_800E7B90(Object_80039F5C *p, State_800E8420 *pState);
void fn_800E7E78(Object_80039F5C *p, State_800E8420 *pState);
unsigned char fn_800E8898(Object_80039F5C *p, void *pArg);
void fn_80178718(Object_80039F5C *p);
void fn_801718E8(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
}

extern "C" int fn_800E8420(Object_80039F5C *p)
{
    State_800E8420 *pState = (State_800E8420 *)&p->mUnknown336;
    int mode = fn_800D0B90(p);
    Input_800B6D34 input;

    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    pState->mUnknown11 = fn_800E745C(p);
    pState->mUnknown5 = p->mpState->mUnknown1;
    pState->mUnknown8 = p->mpState->mUnknown2;
    pState->mUnknown9 = 1;
    pState->mUnknown10 = 0;
    pState->mUnknown17 = 0;
    pState->mUnknown19 = 0;
    pState->mUnknown0 = 0.0f;
    pState->mUnknown6 = 0;
    if (pState->mUnknown5 == 0 || pState->mUnknown5 == 3) {
        pState->mUnknown18 = 0;
    } else {
        pState->mUnknown18 = 1;
    }
    fn_800B6D34(p, &input);
    fn_800E7E78(p, pState);
    pState->mUnknown4 = 0;
    if (mode == 4) {
        fn_800E7B90(p, pState);
    } else {
        fn_800E7588(p, pState);
    }
    p->mUnknown9[0] = 1;
    p->mUnknown512.mUnknown14 = 0;
    fn_800A3B58(p, 7, 0);
    if (p->mFlags & 0x4000) {
        pState->mUnknown16 = 1;
    } else {
        pState->mUnknown16 = 0;
    }
    return 0;
}

extern "C" int fn_800E8554(Object_80039F5C *p)
{
    State_800E8420 *pState = (State_800E8420 *)&p->mUnknown336;

    if (pState->mUnknown4 == 0) {
        if (pState->mUnknown18 == 0) {
            pState->mUnknown18 = fn_800E73D4(p);
        }
        if (pState->mUnknown10 && !(p->mFlags & 0x800) && p == fn_80137B40() && p->mUnknown560.mFlags.mBytes[0]) {
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
            if (pOther) {
                if (!(p->mFlags & 0x10000)) {
                    fn_80178718(pOther);
                    p->mFlags |= 0x10000;
                    p->mFlags &= ~0x80000;
                }
                switch (p->mUnknown560.mUnknown54) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 9:
                case 10:
                    fn_801718E8(p, pOther);
                    pState->mUnknown10 = 0;
                    break;
                }
            }
        }
        if (pState->mUnknown17 == 0) {
            pState->mUnknown17 = fn_800E8898(p, pState->mUnknown12);
        }
        if (p->mUnknown9[0] != 1 && (p->mFlags & 0x800)) {
            Message_800F01CC message;
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
            return 1;
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 0.4f;
            return 1;
        }
    }
    return 0;
}
