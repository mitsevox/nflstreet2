/* Rate-limited player turning: two movement mode handlers that swing the player's facing toward
   the requested heading by at most a rating-based turn rate and ease the move speed toward the
   request, and the check that caps speed and turn rate in certain player states. */
#include "engine/animchan.h"
#include "game/Object_80039F5C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801BE60C.h"
#include "game/Ball.h"

extern "C" {
void fn_800B26D0(Object_800B26B0 *pMotion, int a, int b, float c);
int MathAngleDiff(int a, int b);
int BallStateGet(Ball_t *p, int *pArg);

/* Turn limit per call for a speed scale: from the first rating for players of kind 1, a fixed
   rate for the others. */
static inline int _PlyrMoveTurnScaledLimit(Object_80039F5C *p, float scale)
{
    int limit;

    if (p->mIdBytes[3] == 1) {
        float base = p->mRatings[0] * 0.0015686274273321033f + 0.6f;
        float rate = scale * 512637.0f;
        limit = (int)(base * rate);
    } else {
        limit = (int)(scale * 461373.3125f);
    }
    return limit;
}

void PlyrMoveTurnLimited(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    PlyrMoveCmd_t *pControl = &p->mUnknown528;
    int requested = pControl->mUnknown8;
    int limit;

    if (pMotion->mUnknown36 != 0.0f && pMotion->mUnknown28 <= pMotion->mUnknown36) {
        // FAKEMATCH: repeated test; its else arms are unreachable, but the target emits them
        if (pMotion->mUnknown36 != 0.0f) {
            limit = _PlyrMoveTurnScaledLimit(p, 1.0f - pMotion->mUnknown28 / pMotion->mUnknown36 * 0.5f);
        } else if (p->mIdBytes[3] == 1) {
            limit = (int)((p->mRatings[0] * 0.0015686274273321033f + 0.6f) * 512637.0f);
        } else {
            limit = 0x70A3D;
        }
    } else if (p->mIdBytes[3] == 1) {
        limit = (int)((p->mRatings[0] * 0.0015686274273321033f + 0.6f) * 512637.0f);
    } else {
        limit = 0x70A3D;
    }
    if (fn_801BE648(p->mpUnknown792) == 84) {
        limit = 0xAAAAA;
    }
    int difference = MathAngleDiff(requested, pMotion->mFacing);
    if (difference != 0 && difference > limit) {
        if (((requested - pMotion->mFacing) & 0xFFFFFF) > 0x800000) {
            limit = -limit;
        }
        pControl->mUnknown8 = pMotion->mFacing = (pMotion->mFacing + limit) & 0xFFFFFF;
    } else {
        pControl->mUnknown8 = pMotion->mFacing = requested;
    }
    if (p->mUnknown545 == 0) {
        difference = MathAngleDiff(pControl->mUnknown8, requested);
        if (difference > 0x200000 && pMotion->mUnknown28 > pMotion->mUnknown36 * 0.5f) {
            pMotion->mUnknown52 -= (pMotion->mUnknown52 + pMotion->mUnknown52)
                                  * difference * 0.00000011920928955078125f;
        }
        fn_800B26D0(pMotion, pControl->mUnknown4, pControl->mUnknown8, pMotion->mUnknown52);
    }
    float step;
    if (p->mIdBytes[3] == 1) {
        step = (p->mRatings[4] * 0.0015686274273321033f + 0.6f) * 0.005f;
    } else {
        step = 0.004500000271946192f;
    }
    if (pControl->mUnknown0 < p->mUnknown512.mUnknown0) {
        pControl->mUnknown0 += step;
        pControl->mUnknown0 = pControl->mUnknown0 > p->mUnknown512.mUnknown0
                                  ? p->mUnknown512.mUnknown0 : pControl->mUnknown0;
    } else {
        pControl->mUnknown0 -= step;
        // FAKEMATCH: same field as pControl->mUnknown0, spelled through p to force the reload
        pControl->mUnknown0 = p->mUnknown528.mUnknown0 < p->mUnknown512.mUnknown0
                                  ? p->mUnknown512.mUnknown0 : p->mUnknown528.mUnknown0;
    }
}

void PlyrMoveTurnWithAnim(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    PlyrMoveCmd_t *pControl = &p->mUnknown528;
    int limit;

    if (pMotion->mUnknown28 != 0.0f && pMotion->mUnknown28 < pMotion->mUnknown36) {
        limit = _PlyrMoveTurnScaledLimit(p, 1.0f - pMotion->mUnknown28 / pMotion->mUnknown36 * 0.5f);
    } else if (p->mIdBytes[3] == 1) {
        limit = (int)((p->mRatings[0] * 0.0015686274273321033f + 0.6f) * 512637.0f);
    } else {
        limit = 0x70A3D;
    }
    int difference = MathAngleDiff(p->mUnknown512.mUnknown8, pMotion->mFacing);
    if (difference != 0 && difference > limit) {
        if (((p->mUnknown512.mUnknown8 - pMotion->mFacing) & 0xFFFFFF) > 0x800000) {
            limit = -limit;
        }
        pMotion->mFacing = (pMotion->mFacing + limit) & 0xFFFFFF;
        if (p->mUnknown545 != 0) {
            AnimHeader_t *pHeader = p->mpUnknown796;
            AnimChannel_t *pEntries = p->mpUnknown800;
            int index = AnimChanGetStateChannelByIndex(pHeader, pEntries, fn_801BE648(p->mpUnknown792), 0);
            if (index != 0xFFFF) {
                p->mpUnknown800[index].mUnknownC = (p->mpUnknown800[index].mUnknownC + limit) & 0xFFFFFF;
            }
        }
        pControl->mUnknown8 = pMotion->mFacing;
    } else {
        pMotion->mFacing = p->mUnknown512.mUnknown8;
        pControl->mUnknown8 = p->mUnknown512.mUnknown8;
    }
    if (p->mUnknown545 == 0) {
        difference = MathAngleDiff(pControl->mUnknown8, p->mUnknown512.mUnknown8);
        if (difference > 0x200000 && pMotion->mUnknown28 > pMotion->mUnknown36 * 0.5f) {
            pMotion->mUnknown52 -= (pMotion->mUnknown52 + pMotion->mUnknown52)
                                  * difference * 0.00000011920928955078125f;
        }
        fn_800B26D0(pMotion, pControl->mUnknown4, pControl->mUnknown8, pMotion->mUnknown52);
    }
    float step;
    if (p->mIdBytes[3] == 1) {
        step = (p->mRatings[4] * 0.0015686274273321033f + 0.6f) * 0.005f;
    } else {
        step = 0.004500000271946192f;
    }
    if (pControl->mUnknown0 < p->mUnknown512.mUnknown0) {
        pControl->mUnknown0 += step;
        pControl->mUnknown0 = pControl->mUnknown0 > p->mUnknown512.mUnknown0
                                  ? p->mUnknown512.mUnknown0 : pControl->mUnknown0;
    } else {
        pControl->mUnknown0 -= step;
        // FAKEMATCH: same field as pControl->mUnknown0, spelled through p to force the reload
        pControl->mUnknown0 = p->mUnknown528.mUnknown0 < p->mUnknown512.mUnknown0
                                  ? p->mUnknown512.mUnknown0 : p->mUnknown528.mUnknown0;
    }
}

int PlyrMoveInCappedState(Object_80039F5C *p)
{
    int first = fn_800F06F4(0, p->mpState, 26, 0xFFFF);
    int result = 0;
    int second = fn_800F06F4(0, p->mpState, 27, 0xFFFF);
    int third = fn_800F06F4(0, p->mpState, 25, 0xFFFF);
    int fourth = fn_800F06F4(0, p->mpState, 68, 0xFFFF);

    if (first == 0xFFFF) {
        if (second == 0xFFFF) {
            if (third == 0xFFFF) {
                if (fourth != 0xFFFF) {
                    if (p->mpState->mId != 68 || BallStateGet(BallGetCurrent(), 0) != 3) {
                        result = 1;
                    }
                }
            } else {
                result = 1;
                if (p->mpState->mId == 25 && (unsigned char)p->mUnknown336Block.mUnknown2[2] == 11) {
                    result = 0;
                }
            }
        } else {
            result = 1;
        }
    } else {
        result = 1;
    }
    return result;
}
}
