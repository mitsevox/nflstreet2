/* Chooses a player's movement animation (stand, run, turn, reverse) from the current and
   wanted heading and speed; one function per movement state. */

#include "game/Object_80039F5C.h"
#include "game/Ball.h"
#include "game/fn_801BE60C.h"

extern "C" {
int fn_800C4B6C(Object_80039F5C *p);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
int PlayerActionAnimIsPassReady(Object_80039F5C *p);
int fn_80178320(void);
int MathAngleDiff(int a, int b);
}

#define MAX(a, b) ((a) >= (b) ? (a) : (b))

extern float gPlyrMoveSideSpeed;
extern float gPlyrMoveBackSpeed;

/* The PlayerMoveAnimUpdate* functions are the movement-state handlers: the player's
   movement state picks one each update. PlayerMoveAnimUpdateMove chooses its animation
   with PlayerMoveAnimSelectByHeading or PlayerMoveAnimSelectTurn and checks for a
   reversal with PlayerMoveAnimCheckReverse. The keys are animation ids, the ones the
   animation player reports and starts. */

extern "C" int PlayerMoveAnimWantsReverse(Object_80039F5C *p, int key)
{
    PlyrMoveCmd_t *pNext = &p->mUnknown528;
    Object_800B26B0 *pMotion = &p->mMotion;
    int result = 0;

    if (key == 74 && pNext->mUnknown0 != 0.0f
        && MathAngleDiff(pMotion->mFacing, pNext->mUnknown8) > 0x5FFFFF) {
        int diff = MathAngleDiff(pMotion->mUnknown32, pNext->mUnknown4);
        unsigned char team = p->mIdBytes[2];

        if (diff > 0x755555 && team == fn_80178320() && pMotion->mUnknown28 >= 0.05f
            && fn_800C4B6C(p)) {
            result = 1;
        }
        if (diff <= 0xAAAA9 && team == fn_80178320() && fn_800C4B6C(p)) {
            result = 1;
        }
    }
    return result;
}

extern "C" int PlayerMoveAnimCheckReverse(Object_80039F5C *p, unsigned short key)
{
    int result = 0;

    if (p->mIdBytes[3] == 1 && p->mpState->mId != 61) {
        result = PlayerMoveAnimWantsReverse(p, key);
    }
    return result;
}

extern "C" int PlayerMoveAnimSelectByHeading(Object_80039F5C *p, int diff, unsigned short *pKey)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;
    int result = 0;

    if (diff <= 0x1C71C6 || pCur->mUnknown0 == 0.0f) {
        *pKey = 74;
        pNext->mUnknown14 = 1;
        pNext->mUnknown4 = pCur->mUnknown4;
        pNext->mUnknown8 = pCur->mUnknown4;
        pNext->mUnknown0 = pCur->mUnknown0;
    } else {
        if (diff <= 0x56C16B && pCur->mUnknown4 > 0x800000) {
            *pKey = 84;
            if (fn_801BE648(p->mpUnknown792) == 84 && fn_801BE7C8(p->mpUnknown792, 84) != 0.0f) {
                pCur->mUnknown8 = p->mMotion.mFacing;
                pCur->mUnknown0 = 0.0f;
            }
            if (MathAngleDiff(pCur->mUnknown4, pNext->mUnknown4) > 0x400000) {
                result = 1;
            }
            pNext->mUnknown14 = pCur->mUnknown14;
            pNext->mUnknown4 = pCur->mUnknown4;
            pNext->mUnknown8 = pCur->mUnknown8;
            pNext->mUnknown0 = pCur->mUnknown0;
        } else {
            *pKey = 74;
            pNext->mUnknown14 = pCur->mUnknown14;
            pNext->mUnknown4 = pCur->mUnknown4;
            pNext->mUnknown8 = pCur->mUnknown8;
            pNext->mUnknown0 = pCur->mUnknown0;
        }
    }
    return result;
}

extern "C" int PlayerMoveAnimSelectTurn(Object_80039F5C *p, int flag)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;
    int handled = 0;
    int key = 74;
    int diff;

    pCur->mUnknown8 &= 0xFFFFFF;
    pCur->mUnknown4 &= 0xFFFFFF;
    if (flag) {
        pCur->mUnknown8 = 0xC00000;
    }
    diff = MathAngleDiff(pCur->mUnknown4, pCur->mUnknown8);

    if (BallGetCurrentHolder() != p && diff > 0x2E38E2 && pCur->mUnknown0 > 0.0f) {
        if (diff <= 0x56C16B) {
            if (flag || p->mUnknown492 <= gPlyrMoveSideSpeed) {
                if (p->mIdBytes[2] == fn_80178320() || flag) {
                    key = 160;
                    pNext->mUnknown0 = MAX(pCur->mUnknown0, gPlyrMoveSideSpeed * 0.18f / gPlyrMoveSideSpeed);
                } else {
                    key = 73;
                    pNext->mUnknown0 = MAX(pCur->mUnknown0, gPlyrMoveSideSpeed * 0.4f / gPlyrMoveSideSpeed);
                }
                handled = 1;
                pNext->mUnknown14 = pCur->mUnknown14;
                pNext->mUnknown8 = pCur->mUnknown8;
                pNext->mUnknown4 = pCur->mUnknown4;
            }
        } else if (diff <= 0x71C71B && p->mIdBytes[2] == fn_80178320()) {
            if (flag || p->mUnknown492 <= gPlyrMoveBackSpeed) {
                int offset;
                fn_800C89F0(p, pCur->mUnknown8, 2, 0, 1.0f);
                key = 159;
                offset = diff - 0x400000;
                if (((pCur->mUnknown8 - pCur->mUnknown4) & 0xFFFFFF) <= 0x800000) {
                    key = 157;
                    offset = -offset;
                }
                pNext->mUnknown0 = MAX(pCur->mUnknown0, gPlyrMoveSideSpeed * 0.18f / gPlyrMoveSideSpeed);
                handled = 1;
                pNext->mUnknown14 = pCur->mUnknown14;
                pNext->mUnknown8 = (pCur->mUnknown8 + offset) & 0xFFFFFF;
                pNext->mUnknown4 = pCur->mUnknown4;
            }
        } else if (flag || p->mUnknown492 <= gPlyrMoveBackSpeed) {
            key = 74;
            handled = 1;
            pNext->mUnknown0 = pCur->mUnknown0;
            pNext->mUnknown14 = pCur->mUnknown14;
            pNext->mUnknown8 = pCur->mUnknown8;
            pNext->mUnknown4 = pCur->mUnknown4;
        }
    }

    if (!handled) {
        if (pCur->mUnknown8 != pCur->mUnknown4) {
            fn_800C89F0(p, pCur->mUnknown8, 2, 0, 1.0f);
        }
        key = 74;
        pNext->mUnknown14 = 1;
        pNext->mUnknown4 = pCur->mUnknown4;
        pNext->mUnknown8 = pCur->mUnknown4;
        pNext->mUnknown0 = pCur->mUnknown0;
    }
    return key;
}

extern "C" void PlayerMoveAnimUpdateStand(Object_80039F5C *p)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;
    unsigned short key;

    pNext->mUnknown0 = pCur->mUnknown0;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    pNext->mUnknown14 = pCur->mUnknown14;

    key = fn_801BE648(p->mpUnknown792);
    switch (key) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 73:
    case 84:
    case 100:
    case 106:
    case 107:
    case 160:
        key = 74;
        break;
    }
    if (fn_801BE648(p->mpUnknown792) != key) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, 1.0f, p);
    }
}

extern "C" void PlayerMoveAnimUpdateHold(Object_80039F5C *p)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;

    pNext->mUnknown14 = pCur->mUnknown14;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown4;
    pNext->mUnknown0 = pCur->mUnknown0;

    fn_801BE648(p->mpUnknown792);
    if (fn_801BE648(p->mpUnknown792) != 74) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
    }
}

extern "C" void PlayerMoveAnimUpdateSpecial(Object_80039F5C *p);

extern "C" void PlayerMoveAnimUpdateMove(Object_80039F5C *p)
{
    int changed = 0;
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;
    unsigned short key = fn_801BE648(p->mpUnknown792);
    int diff = MathAngleDiff(pCur->mUnknown4, pCur->mUnknown8);

    if (p->mIdBytes[3] == 2) {
        pNext->mUnknown14 = 1;
        key = 74;
        pNext->mUnknown4 = pCur->mUnknown4;
        pNext->mUnknown8 = pCur->mUnknown4;
        pNext->mUnknown0 = pCur->mUnknown0;
    } else if (PlayerActionAnimIsPassReady(p)) {
        changed = PlayerMoveAnimSelectByHeading(p, diff, &key);
    } else {
        int flag = pCur->mUnknown15 == 4 || pCur->mUnknown15 == 5;
        if (flag && pCur->mUnknown0 == 0.0f) {
            PlayerMoveAnimUpdateSpecial(p);
            return;
        }
        key = PlayerMoveAnimSelectTurn(p, flag);
    }

    if (PlayerMoveAnimCheckReverse(p, key) == 0) {
        if (fn_801BE648(p->mpUnknown792) != key || changed) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, 1.0f, p);
        }
    }
}

extern "C" void PlayerMoveAnimUpdateKeep(Object_80039F5C *p)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;

    pNext->mUnknown14 = pCur->mUnknown14;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown0 = pCur->mUnknown0;
}

extern "C" void PlayerMoveAnimUpdateLimited(Object_80039F5C *p)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;
    unsigned short key = fn_801BE648(p->mpUnknown792);

    switch (key) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 106:
    case 107:
        if (p->mUnknown1032 != 4) {
            key = 74;
        }
        break;
    case 25:
    case 56:
    case 61:
    case 79:
        if (p->mUnknown1032 != 5) {
            key = 74;
        }
        break;
    case 62:
    case 63:
    case 66:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 125:
    case 130:
    case 131:
    case 146:
    case 147:
    case 148:
    case 149:
    case 150:
    case 151:
    case 161:
    case 241:
        key = 74;
        break;
    default:
        key = 74;
        break;
    }

    pNext->mUnknown0 = pCur->mUnknown0;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    pNext->mUnknown14 = pCur->mUnknown14;
    if (fn_801BE648(p->mpUnknown792) != key) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, 1.0f, p);
    }
}

extern "C" void PlayerMoveAnimUpdateDefault(Object_80039F5C *p)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;

    pNext->mUnknown14 = pCur->mUnknown14;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    pNext->mUnknown0 = pCur->mUnknown0;

    if (fn_801BE648(p->mpUnknown792) != 74) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
    }
}

extern "C" void PlayerMoveAnimUpdateSpecial(Object_80039F5C *p)
{
    PlyrMoveCmd_t *pCur = &p->mUnknown512;
    PlyrMoveCmd_t *pNext = &p->mUnknown528;

    pNext->mUnknown0 = pCur->mUnknown0;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    pNext->mUnknown14 = pCur->mUnknown14;

    switch (p->mIdBytes[3]) {
    case 1:
    case 2:
        if (fn_801BE648(p->mpUnknown792) != 100) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 100, 1.0f, p);
        }
        break;
    default:
        PlayerMoveAnimUpdateStand(p);
        break;
    }
}
