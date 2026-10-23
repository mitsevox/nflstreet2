#include "game/Block_800B21D0.h"
#include "game/Object_8017886C.h"
#include "game/Input_80174868.h"
#include "game/fn_80177FE0.h"

extern "C" {
int fn_80177F70(void);
float fn_80178298(void);
Point_8017886C fn_8017808C(void);
int fn_801784E8(void);
int fn_80178308(void);
int fn_80176378(int value);
float fn_80176328(float value);

extern Block_800B21D0 *lbl_803EAB20;
}

extern "C" int fn_800B1C28(State_800B19E8 *pState, unsigned int count, Object_8017886C *pPlay)
{
    int result = 0;
    unsigned char i = 0;

    lbl_803EAB20->mUnknown4.mUnknown5C &= ~6;
    lbl_803EAB20->mUnknown4.mUnknown48 = 0.0f;
    pPlay->mUnknown18 = 0;
    signed char previous = pPlay->mUnknown1D;
    pPlay->mUnknown1D = 0;

    for (; i < count; i++) {
        Input_80174868 in;
        Output_80174868 out;

        in.mUnknown22 = pState->mUnknown0[0].mUnknown20;
        in.mUnknown23 = pState->mUnknown0[0].mUnknown21;
        in.mUnknown8 = pState->mUnknown0[0].mUnknown10;
        in.mUnknown1C = pState->mUnknown0[0].mUnknown14;
        in.mUnknown10 = pState->mUnknown0[0].mUnknown18;
        in.mUnknown18 = pState->mUnknown0[0].mUnknown1C;
        in.mUnknown14 = fn_80177F70();
        in.mUnknown20 = pState->mUnknown0[0].mUnknown4Bytes[2];
        in.mUnknown21 = pState->mUnknown0[0].mUnknown22;
        in.mUnknown24 = previous;
        in.mUnknownC = fn_80178298();
        in.mUnknown0 = fn_80177FE0().mY;
        in.mUnknown4 = fn_8017808C().mY;
        if (fn_801784E8() != 0) {
            in.mUnknownC = -in.mUnknownC;
            in.mUnknown0 = -in.mUnknown0;
        }
        out.mUnknownC = 0.0f;
        fn_801764A0(pState->mUnknown0[0].mUnknown0, &in, &out);
        lbl_803EAB20->mUnknown4.mUnknown48 = out.mUnknownC;
        pPlay->mUnknown10 = out.mUnknown8;
        pPlay->mUnknown08.mX = fn_8017808C().mX;
        pPlay->mUnknown08.mY = out.mUnknown0;
        out.mUnknown4 = in.mUnknownC;
        int team = fn_80178308();
        if (out.mUnknown15 != team) {
            pPlay->mUnknown18 |= 0x10;
            if (fn_801784E8() != 0) {
                pPlay->mUnknown08.mX = -pPlay->mUnknown08.mX;
                pPlay->mUnknown08.mY = -pPlay->mUnknown08.mY;
            }
        }
        if (in.mUnknown18 > 0) {
            pPlay->mUnknown18 |= 0x20;
        }
        switch (out.mUnknown10) {
        case 3:
            pPlay->mUnknown04 = 0;
            pPlay->mUnknown08.mX = 0.0f;
            if (in.mUnknown14 != 0) {
                pPlay->mUnknown18 |= 0x80;
            }
            break;
        case 0:
            pPlay->mUnknown04 = fn_80176378(in.mUnknown14);
            if (pPlay->mUnknown04 == 5 || pPlay->mUnknown04 == 7) {
                pPlay->mUnknown04 = 1;
                result = 1;
                pPlay->mUnknown18 |= 4;
            }
            if (pPlay->mUnknown04 == 1) {
                out.mUnknown4 = fn_80176328(out.mUnknown0);
                pPlay->mUnknown18 |= 0x40;
            }
            break;
        case 1:
            if (out.mUnknown0 < in.mUnknownC) {
                pPlay->mUnknown04 = in.mUnknown14;
                pPlay->mUnknown08.mX = fn_80177FE0().mX;
                break;
            }
            /* fall through */
        case 2:
            out.mUnknown4 = fn_80176328(out.mUnknown0);
            pPlay->mUnknown18 |= 0x40;
            pPlay->mUnknown04 = 1;
            break;
        }
        pPlay->mUnknown1D = out.mUnknown14;
        switch (out.mUnknown14) {
        case 6:
        case 9:
            pPlay->mUnknown04 = 6;
            pPlay->mUnknown18 &= ~0x40;
            break;
        case 3:
            pPlay->mUnknown04 = 0;
            pPlay->mUnknown18 |= 0x80;
            break;
        case -2:
            pPlay->mUnknown18 |= 0x80;
            break;
        }
    }
    return result;
}
