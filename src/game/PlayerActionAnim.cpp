/* Player action animation: the option-pitch decision and the animation-phase handlers that pick and
   blend the player's animation-table entries while an action move plays. */
#include "game/PlayerAction.h"

static unsigned int lbl_803EAD1C = 0;

extern "C" int fn_800DAEE4(Object_80039F5C *p)
{
    int result;
    if (fn_8011F518()->mUnknown4 == 11) {
        result = 1;
        if (p->mUnknown776 == 1) {
            result = 2;
        }
    } else {
        int angle = MathAngleDiff(p->mMotion.mFacing, 0);
        result = 2;
        if (angle <= 0x3FFFFF) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800DAF5C(Table_80089904 *pTable, int key, void *pContext,
    Record_800D81C8 *pEntries, Object_80039F5C *p, int phase)
{
    if (phase != 0) {
        return 0;
    }
    Point_8017886C direction;
    direction.mX = (signed char)p->mUnknown1008.mUnknown1 * 0.1f;
    direction.mY = (signed char)p->mUnknown1008.mUnknown2 * 0.1f;
    int angle = (fn_801CFE40(direction.mY, direction.mX) - p->mMotion.mFacing) & 0xFFFFFF;
    int foot = PlayerLocoGetLowerAnkle(p);
    unsigned char side = (unsigned char)fn_800DAEE4(p);
    int index = PlayerLocoFindTableEntry(pTable, angle, foot, side);
    fn_801BA2A8(pContext, pEntries, pTable->mEntries[index].mUnknown0,
        pTable->mEntries[index].mUnknown2, key, p, 1.0f);
    return 0;
}

extern "C" void fn_800DB074(Object_80039F5C *p, Ball_t *pBall, Record_800DB074 *pRecord)
{
    Record_8011F518 *pRecord8011F518 = fn_8011F518();
    pRecord8011F518->mUnknown8 = pRecord->mUnknown16;
    Object_80039F5C *pOther = fn_8009BCE8(&pRecord->mUnknown12);
    if (pOther) {
        Point_8017886C delta;
        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        pRecord8011F518->mUnknown12 = fn_801CFE40(delta.mY, delta.mX);
    } else {
        pRecord8011F518->mUnknown12 = p->mMotion.mUnknown32;
    }
    fn_801061E8(p, pBall);
}

extern "C" void fn_800DB100(Object_80039F5C *p, Ball_t *pBall, Record_800DB074 *pRecord)
{
    Vector_80039F5C ball;
    Vector_80039F5C joint;

    BallGetPosition(pBall, &ball);
    fn_8009BF5C(p, 12, &joint, 0);
    if (ball.mZ < pRecord->mUnknown4 - 0.3f) {
        return;
    }
    if (ball.mZ <= joint.mZ - 0.15f) {
        return;
    }
    Record_8011F4F8 *pRequest = fn_8011F4F8(BallGetIndex(pBall));
    if (pRequest->mUnknownB != 1) {
        return;
    }
    pRequest->mUnknown8 = (pRequest->mUnknown8 - 5) / 3 + 5;
    pRequest->mUnknownC = pRecord->mUnknown16;
    Point_8017886C delta;
    delta.mX = 0.2f;
    delta.mY = pRecord->mUnknown8 - ball.mZ;
    delta.mY = delta.mY < 0.0f ? 0.0f : delta.mY;
    int angle = delta.Heading();
    pRequest->mUnknown10 = angle + fn_802372EC(0, 0xE38E3);
    if (pRequest->mUnknownC == 0.0f) {
        float value = pRequest->mUnknown10 * 2.3841858e-07f;
        pRequest->mUnknownC = value * 0.5f + 0.5f;
    }
    float scale = pRequest->mUnknownC * 0.5f;
    pRequest->mUnknown0 -= pRequest->mUnknown0 * scale;
    pRequest->mUnknown4 -= pRequest->mUnknown4 * scale;
    if (fn_80103CB0(p)) {
        Object_80039F5C *pOther = fn_8009BCE8(&pRecord->mUnknown12);
        if (pOther) {
            Record_800B15FC *pMessage = fn_800B15FC();
            fn_8009BD2C(pOther, &pMessage->mUnknown0);
            pMessage->mUnknownC = p->mMotion.mPos.mX;
            pMessage->mUnknown10 = p->mMotion.mPos.mY;
            pMessage->mUnknown14 = 34;
            fn_800B1508();
        }
    }
}

extern "C" void fn_800DB308(Object_80039F5C *p, float *pOut)
{
    float value = 12.0f;
    unsigned short kind = fn_801BE648(p->mpUnknown792);

    if (kind == 135 || kind == 191) {
        if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, kind)) {
            Record_800D81C8 *pRecords = p->mpUnknown800;
            unsigned short index = fn_801BA5A8(p->mpUnknown796, pRecords, kind, 0);
            value = AnimSeqGetKeyTime(pRecords[index].mUnknown4C.mpUnknown0, 0xC003);
            value -= AnimSeqGetTime(&pRecords[index].mUnknown4C);
            value = value < 0.0f ? 0.0f : (value > 12.0f ? 12.0f : value);
        }
    } else if (kind == 69 || kind == 178) {
        value = 0.0f;
    }
    if (pOut) {
        *pOut = value;
    }
}

extern "C" void fn_800DB40C(Record_800DB074 *pRecord, Object_80039F5C *p, Ball_t *pBall)
{
    fn_800DB308(p, &pRecord->mUnknown20);
    if (fn_80105FF8(p, pBall, pRecord->mUnknown20)) {
        pRecord->mUnknown1 = 1;
    }
    pRecord->mUnknown20 += (unsigned int)fn_8023790C();
}

extern "C" void fn_800DB498(Record_800DB074 *pRecord, Object_80039F5C *p, Ball_t *pBall)
{
    Vector_80039F5C pos;

    fn_800DB308(p, &pRecord->mUnknown20);
    pRecord->mUnknown0 = 1;
    BallGetPosition(pBall, &pos);
    pRecord->mUnknown8 = pRecord->mUnknown4 = pos.mZ;
    pRecord->mUnknown20 += (unsigned int)fn_8023790C();
}

extern "C" void fn_800DB520(Record_800DB074 *pRecord, Object_80039F5C *p, Object_80039F5C *pOther, float value)
{
    pRecord->mUnknown0 = 0;
    pRecord->mUnknown1 = 0;
    pRecord->mUnknown4 = 0.0f;
    pRecord->mUnknown8 = 0.0f;
    fn_8009BD2C(pOther, &pRecord->mUnknown12);
    pRecord->mUnknown16 = value / (gPlyrMoveFwdSpeed * 100621.12f);
    Ball_t *pBall = BallFindHeldBy(p);
    if (pBall) {
        int kind = fn_801BE648(p->mpUnknown792);
        if (kind == 69 || kind == 178) {
            if (fn_8011F4F8(BallGetIndex(pBall))->mUnknownB == 1) {
                fn_800DB498(pRecord, p, pBall);
            }
        } else if (kind == 135 || kind == 191) {
            fn_800DB40C(pRecord, p, pBall);
        }
    }
}

extern "C" void fn_800DB60C(Record_800DB074 *pRecord, Object_80039F5C *p)
{
    if (pRecord->mUnknown0 != 1 && pRecord->mUnknown1 != 1) {
        Ball_t *pBall = BallFindHeldBy(p);
        if (pBall && fn_80106580(p, (p->mFlags >> 14) & 1)) {
            fn_800DB40C(pRecord, p, pBall);
        }
    }
}

extern "C" void fn_800DB688(Record_800DB074 *pRecord, Object_80039F5C *p)
{
    int done = 0;

    if (pRecord->mUnknown0 == 1) {
        Ball_t *pBall = BallFindHeldBy(p);
        if (!pBall) {
            pRecord->mUnknown0 = 0;
        } else if (pRecord->mUnknown20 <= (unsigned int)fn_8023790C()) {
            if (p->mFlags & 0x1000) {
                fn_800DB100(p, pBall, pRecord);
                p->mFlags &= ~0x3000;
                pRecord->mUnknown0 = 0;
            }
        } else if (!fn_80106618(p)) {
            pRecord->mUnknown0 = 0;
        } else {
            Vector_80039F5C pos;
            BallGetPosition(pBall, &pos);
            if (pRecord->mUnknown8 < pos.mZ) {
                pRecord->mUnknown8 = pos.mZ;
            }
        }
        if (!done && pRecord->mUnknown0 == 0) {
            p->mUnknown778 = -1;
            fn_8011F4F8(BallGetIndex(BallGetCurrent()))->mUnknownB = 0;
        }
    }
}

extern "C" void fn_800DB7A4(Record_800DB074 *pRecord, Object_80039F5C *p)
{
    int done = 0;

    if (pRecord->mUnknown1 == 1) {
        int busy = fn_801787A0();
        if (!busy) {
            Ball_t *pBall = BallFindHeldBy(p);
            if (!pBall) {
                pRecord->mUnknown1 = 0;
            } else {
                if (pRecord->mUnknown20 <= (unsigned int)fn_8023790C()) {
                    done = 1;
                    fn_800DB074(p, pBall, pRecord);
                    p->mFlags &= ~0x3000;
                    pRecord->mUnknown1 = 0;
                } else if (!fn_80106618(p)) {
                    pRecord->mUnknown1 = 0;
                }
                if (fn_801BE648(p->mpUnknown792) == 234) {
                    pRecord->mUnknown1 = 0;
                }
                if (!done && pRecord->mUnknown1 == 0) {
                    p->mUnknown778 = -1;
                    fn_8009BD2C(0, &fn_8011F518()->mUnknown0);
                }
            }
        }
    }
}

extern "C" void fn_800DB8B4(Record_800DB60C *pRecord, Object_80039F5C *p)
{
    int allow = 1;
    int failed = 0;
    if (fn_800B65A0(p->mIdBytes[2]) != 255 || pRecord->mUnknown1 == 1) {
        return;
    }
    switch (p->mpState->mId) {
    case 10:
    case 16:
    case 58:
        break;
    default:
        return;
    }
    if (!(fn_8012506C(p, 3) <= 65.0f)) {
        allow = 0;
    }
    unsigned int roll = (unsigned int)fn_802372EC(0, 255);
    if (roll > (unsigned int)fn_800ACFA8(p)) {
        failed = 1;
    }
    if (failed && (unsigned int)fn_802372EC(0, 100) < (unsigned int)lbl_803EAD19) {
        allow = allow == 0;
    }
    Point_8017886C point;
    Object_80039F5C *pOther = fn_80105384(p, 0, &point);
    if (!pOther) {
        return;
    }
    int can = 0;
    if (allow && OptionRunCanPitchTo(p, &point, pOther)) {
        can = 1;
    }
    if (!can) {
        return;
    }
    int ready = 0;
    if (fn_801066D0(p, pOther, 9)) {
        ready = 1;
    }
    if (!ready) {
        return;
    }
    allow = fn_8012506C(pOther, 5) < lbl_803EAD14;
    if (!allow) {
        return;
    }
    if (fn_800ABDA4(fn_80178308()) == 0) {
        int count = fn_8011F59C(0);
        count += fn_8011F59C(1);
        if (count > 0) {
            allow = 0;
        }
    } else if (fn_800ABDA4(fn_80178308()) == 1) {
        int count = fn_8011F59C(0);
        count += fn_8011F59C(1);
        if (count > 1) {
            allow = 0;
        }
    }
    if (!allow) {
        return;
    }
    if (failed) {
        if ((unsigned int)fn_8011F59C(1) < (unsigned int)lbl_803EAD18) {
            fn_8011F5AC(1);
        } else {
            allow = 0;
        }
    } else {
        fn_8011F5AC(0);
    }
    if (allow) {
        fn_800DB60C(pRecord, p);
    }
}

extern "C" int fn_800DBAF0(Object_80039F5C *p)
{
    Record_800DB60C *pRecord = 0;
    switch (p->mpState->mId) {
    case 16:
        pRecord = (Record_800DB60C *)((char *)p + 368);
        break;
    case 10:
    case 58:
        pRecord = (Record_800DB60C *)((char *)p + 356);
        break;
    case 36:
        pRecord = (Record_800DB60C *)((char *)p + 336);
        break;
    }
    int result = 0;
    if (pRecord && pRecord->mUnknown1) {
        result = pRecord->mUnknown20 >= 0.0f;
    }
    return result;
}

extern "C" int fn_800DBB74(Object_80039F5C *p, unsigned char *pOut)
{
    int result;

    *pOut = 0;
    if (p->mUnknown8 == 255 || !(p->mFlags & 0x4000)) {
        int mode = fn_800AD9B4();
        result = 1;
        if (!fn_801783AC(0)) {
            unsigned char kind = p->mUnknown2914;
            if ((kind == 0 || kind == 20 || kind == 1 || kind == 3)
                && (fn_8011F1CC() || fn_8011F1F4())
                && mode == 3 && p->mpState->mId == 18 && p->mUnknown360 == 1) {
                *pOut = 1;
            }
        }
    } else {
        result = 0;
    }
    return result;
}

extern "C" void fn_800DBC4C(Object_80039F5C *p, int angle, float value)
{
    int dir = 0x755555;
    int result;
    int target;

    if (p->mUnknown2913 == 0) {
        dir = 0xAAAAA;
    }
    if (fn_801BE648(p->mpUnknown792) != 217 || value > 0.0f) {
        if (value <= 0.0f) {
            lbl_803EAD1C++;
            if (MathAngleDiff(p->mMotion.mFacing, dir) > 0x400000) {
                if (lbl_803EAD1C > 15) {
                    int base = 0x800000;
                    if (p->mUnknown2913 == 0) {
                        base = 0;
                    }
                    fn_8009BD60(p);
                    if (p->mUnknown2913 == 0) {
                        p->mUnknown1008.mUnknown0 = 1;
                    } else {
                        p->mUnknown1008.mUnknown0 = 2;
                    }
                    p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4 = base;
                    p->mUnknown512.mUnknown14 = 6;
                    p->mUnknown512.mUnknown0 = 1.0f;
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 217, 1.0f, p);
                    p->mUnknown512.mUnknown14 = 0;
                    p->mFlags &= ~4;
                } else {
                    if ((p->mFlags & 4) || fn_801BE648(p->mpUnknown792) != 222) {
                        p->mFlags &= ~4;
                        if (p->mUnknown2913 == 0) {
                            p->mUnknown1008.mUnknown0 = 1;
                        } else {
                            p->mUnknown1008.mUnknown0 = 2;
                        }
                        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 222, 1.0f, p);
                    }
                    p->mUnknown512.mUnknown14 = 0;
                }
                return;
            }
            angle = -0x400000;
        } else {
            lbl_803EAD1C = 0;
        }
        result = fn_800DC080(p);
        if (result == 1 && p->mUnknown512.mUnknown15 != 1) {
            if (MathAngleDiff(angle, -0x38E38E) <= 0x155554) {
                if (p->mUnknown2913 == 0) {
                    int facing = p->mMotion.mFacing & 0xFFFFFF;
                    if (facing >= 0x6E38E4 && facing <= 0xC38E38
                        && p->mMotion.mUnknown28 <= PlyrMoveGetRatedSpeed(p, 0.0f, 1.0f)) {
                        target = 0x6AAAAB;
                    } else {
                        target = (angle + 0x38E38E) & 0xFFFFFF;
                    }
                } else {
                    int facing = p->mMotion.mFacing & 0xFFFFFF;
                    if ((facing < 0x11C71C || facing > 0xBC71C7)
                        && p->mMotion.mUnknown28 <= PlyrMoveGetRatedSpeed(p, 0.0f, 1.0f)) {
                        target = 0x155555;
                    } else {
                        target = (angle - 0x38E38E) & 0xFFFFFF;
                    }
                }
                p->mUnknown512.mUnknown14 = 3;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown8 = target;
                p->mUnknown512.mUnknown0 = value;
            } else {
                p->mUnknown512.mUnknown14 = result;
                p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown0 = value;
                if (p->mUnknown512.mUnknown15 != 1) {
                    fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
                }
            }
        } else if (p->mMotion.mUnknown28 <= PlyrMoveGetRatedSpeed(p, 0.0f, 1.0f)) {
            angle = -0x400000;
            if (p->mUnknown2913 == 0) {
                int facing = p->mMotion.mFacing & 0xFFFFFF;
                if (facing >= 0x6E38E4 && facing <= 0xC38E38
                    && p->mMotion.mUnknown28 <= PlyrMoveGetRatedSpeed(p, 0.0f, 1.0f)) {
                    target = 0x6AAAAB;
                } else {
                    target = (angle + 0x38E38E) & 0xFFFFFF;
                }
            } else {
                int facing = p->mMotion.mFacing & 0xFFFFFF;
                if ((facing < 0x11C71C || facing > 0xBC71C7)
                    && p->mMotion.mUnknown28 <= PlyrMoveGetRatedSpeed(p, 0.0f, 1.0f)) {
                    target = 0x155555;
                } else {
                    target = (angle - 0x38E38E) & 0xFFFFFF;
                }
            }
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown8 = target;
            p->mUnknown512.mUnknown0 = value;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown0 = value;
            if (p->mUnknown512.mUnknown15 != 1) {
                fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
            }
        }
    } else if (p->mFlags & 4) {
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown8 = dir;
        p->mUnknown512.mUnknown0 = value;
    }
}

extern "C" int fn_800DC080(Object_80039F5C *p)
{
    int result = 0;
    unsigned char flag;

    if (p->mIdBytes[3] == 1) {
        int mode = fn_800AD9B4();
        PlayBookFormation_t *pTeam = PlayBookGetFormation(p->mIdBytes[2]);
        if (!fn_801783AC(0) && BallFindHeldBy(p)
            && (p == PlaySetGetKeyPlayer(pTeam)
                || ((p->mUnknown2914 == 1 || p->mUnknown2914 == 3) && fn_8011F2C4()
                    && (PassIconsAreShown() || !(p->mFlags & 0x400))))
            && (fn_8011F1CC() || fn_8011F1F4())
            && mode == 3 && p->mpState->mId != 1 && p->mUnknown512.mUnknown15 != 1) {
            if (!fn_800DBB74(p, &flag)) {
                if (!PassIconsWereShown()) {
                    result = 1;
                } else if (PassIconsAreShown() == 1) {
                    if (!(p->mFlags & 0x200000)) {
                        result = 1;
                    } else if (p->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.4f) {
                        p->mFlags &= ~0x200000;
                        result = 1;
                    }
                } else {
                    p->mFlags |= 0x200000;
                }
            } else {
                result = flag == 0;
            }
        } else if (fn_801486A0() == 1 && p->mpState->mId == 51) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800DC21C(Object_80039F5C *p)
{
    int result = 0;
    unsigned char flag;
    unsigned char shown;
    int mode = fn_800AD9B4();
    PlayBookFormation_t *pTeam = PlayBookGetFormation(p->mIdBytes[2]);

    if (!fn_801783AC(0) && BallFindHeldBy(p)
        && (p == PlaySetGetKeyPlayer(pTeam)
            || ((p->mUnknown2914 == 1 || p->mUnknown2914 == 3) && fn_8011F2C4()
                && (PassIconsAreShown() || !(p->mFlags & 0x400))))
        && fn_8011F1CC() && mode == 3 && p->mpState->mId != 1 && p->mpState->mId != 91) {
        if (!fn_800DBB74(p, &flag)) {
            if (!fn_800DC080(p)) {
                result = 1;
            }
        } else {
            result = flag;
        }
    }
    if (result && p && !PlayerMoveGetKind(p)) {
        fn_800CABF4(p, &shown, 0);
        if (shown) {
            TutorialSetMoveDone(21, 1);
        }
    }
    return result;
}

extern "C" int fn_800DC36C(List_800DC36C *pList, unsigned short key, void *pA,
                           Record_800D81C8 *pRecords, Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *pBlock = fn_801BE60C(p->mpUnknown792, key);
    int side;
    int i;

    switch (phase) {
    case 0:
        if (p->mUnknown2913 == 0) {
            side = 1;
            fn_800ADB90(p, 5, 8, 1);
        } else {
            side = 0;
            fn_800ADB90(p, 5, 8, 0);
        }
        for (i = 0; i < pList->mCount; i++) {
            Object_800DC36C *pObject = pList->mEntries[i].mpUnknown4;
            if (pObject->mUnknown36 == side
                && MathAngleDiff(pObject->mUnknown40, p->mUnknown512.mUnknown4) <= 0x400000) {
                break;
            }
        }
        fn_801BE760(p->mpUnknown792, key, 1);
        pBlock->mUnknown0Word = fn_801BA2A8(pA, pRecords, pList->mEntries[i].mUnknown0,
                                        pList->mEntries[i].mUnknown2, key, p, 1.0f);
        pBlock->mUnknown4Word = p->mMotion.mFacing;
        break;
    case 1:
        break;
    case 2:
        if (pBlock->mUnknown4Word != p->mMotion.mFacing) {
            p->mpUnknown800[pBlock->mUnknown0Word].mUnknownC =
                (p->mpUnknown800[pBlock->mUnknown0Word].mUnknownC
                 + (p->mMotion.mFacing - pBlock->mUnknown4Word)) & 0xFFFFFF;
            pBlock->mUnknown4Word = p->mMotion.mFacing;
        }
        AnimSeqSetSpeed(&pRecords[pBlock->mUnknown0Word].mUnknown4C, MathInverse(fn_800C495C(p, 1.0f)));
        if (fn_800A7EF4(p->mIdBytes[2]) == 2) {
            AnimSeqSetSpeed(&pRecords[pBlock->mUnknown0Word].mUnknown4C, MathInverse(2.0f));
        } else if (fn_800A7EF4(p->mIdBytes[2]) == 0) {
            AnimSeqSetSpeed(&pRecords[pBlock->mUnknown0Word].mUnknown4C, MathInverse(0.5f));
        }
        break;
    }
    return 0;
}

extern "C" void fn_800DC578(void)
{
    lbl_803EAD1C = 0;
}

extern "C" int fn_800DC584(Object_80039F5C *p, Record_800DC584 *pRecord)
{
    PlyrMoveCmd_t *pBlock = &p->mUnknown512;
    int delta = MathAngleDiff(pBlock->mUnknown4, pBlock->mUnknown8);
    int angle;
    int result;
    if (((pBlock->mUnknown4 - pBlock->mUnknown8) & 0xFFFFFF) > 0x800000) {
        angle = pBlock->mUnknown8 + (0x400000 - delta);
        result = 1;
    } else {
        angle = pBlock->mUnknown8 - (0x400000 - delta);
        result = 2;
    }
    pBlock->mUnknown8 &= 0xFFFFFF;
    p->mpUnknown800[pRecord->mUnknown0].mUnknownC = angle;
    return result;
}

extern "C" float fn_800DC61C(Object_801BBD5C *pObject, Object_80039F5C *p)
{
    float value = p->mMotion.mUnknown28;
    if (MathAngleDiff((p->mMotion.mUnknown32 - p->mMotion.mFacing) & 0xFFFFFF, pObject->mUnknown20) > 0x400000) {
        value = -value;
    }
    return value;
}

extern "C" int fn_800DC674(Object_801BBD5C *pObject, Object_80039F5C *p)
{
    return PlayerLocoFindSampleIndex(pObject, fn_800DC61C(pObject, p));
}

extern "C" float fn_800DC6A8(Object_801BBD5C *pObject, Object_80039F5C *p, int index, void *pA, int b)
{
    return PlayerLocoUpdateBlendWeights(index, pA, pObject, b, fn_800DC61C(pObject, p));
}

extern "C" int fn_800DC6F4(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DC6F4 *pRecord = (Record_800DC6F4 *)fn_801BE60C(p->mpUnknown792, key);
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        fn_8009BD60(p);
        pRecord->mUnknown8 = fn_800DC584(p, (Record_800DC584 *)pRecord);
        if (p->mIdBytes[3] != 1) {
            pRecord->mUnknown9 = 2;
            pRecord->mUnknown10 = 2;
        } else if (!p->mUnknown1052) {
            if (fn_800AD9B4() == 3) {
                pRecord->mUnknown10 = 4;
                pRecord->mUnknown9 = 2;
            } else {
                pRecord->mUnknown10 = 2;
                pRecord->mUnknown9 = !(p->mUnknown528.mUnknown0 <= 0.65f) ? 2 : 1;
            }
        } else {
            pRecord->mUnknown10 = 3;
            pRecord->mUnknown9 = 2;
        }
        p->mUnknown1008.mUnknown0 = pRecord->mUnknown8;
        p->mUnknown1008.mUnknown1 = pRecord->mUnknown9;
        p->mUnknown1008.mUnknown2 = pRecord->mUnknown10;
        int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
        unsigned char entry = fn_801BA2A8(pA, pEntries, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        pRecord->mUnknown0 = entry;
        pRecord->mUnknown4 = -1;
        AnimSeqSetSpeed(&pEntries[entry].mUnknown4C, MathInverse(p->mUnknown528.mUnknown0 + 0.2799999713897705f));
        break;
    }
    case 2: {
        int direction = fn_800DC584(p, (Record_800DC584 *)pRecord);
        if (direction != pRecord->mUnknown8) {
            if (pRecord->mUnknown4 != -1 && p->mpUnknown800[pRecord->mUnknown4].mUnknown8 == key) {
                fn_801BA384((AnimHeader_t *)pA, pEntries, pRecord->mUnknown4);
            }
            int next = fn_801BA2D0(pA, pEntries, &pEntries[pRecord->mUnknown0]);
            pRecord->mUnknown4 = pRecord->mUnknown0;
            AnimWgtSetLinear(&pEntries[pRecord->mUnknown0].mUnknown30, 12, -1.0f, 0.0f);
            pRecord->mUnknown0 = next;
            unsigned char value = pEntries[next].mUnknown4C.mUnknown1E;
            pRecord->mUnknown8 = direction;
            p->mUnknown1008.mUnknown0 = direction;
            p->mUnknown1008.mUnknown1 = pRecord->mUnknown9;
            p->mUnknown1008.mUnknown2 = pRecord->mUnknown10;
            int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
            fn_801BA418(pA, pEntries, pRecord->mUnknown0, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p);
            AnimWgtSet(&pEntries[pRecord->mUnknown0].mUnknown30, 0, 0.0f, 0, 0.0f);
            AnimWgtSetLinear(&pEntries[pRecord->mUnknown0].mUnknown30, 12, -1.0f, 1.0f);
            pEntries[pRecord->mUnknown0].mUnknown24.mUnknown4 = -pEntries[pRecord->mUnknown0].mUnknown24.mUnknown4;
            pEntries[pRecord->mUnknown0].mUnknown4C.mUnknown1E = value;
            float speed = p->mUnknown528.mUnknown0;
            speed -= speed * 0.2f;
            p->mUnknown528.mUnknown0 = speed;
            if (!(speed >= 0.01f)) {
                speed = 0.01f;
            }
            p->mUnknown528.mUnknown0 = speed;
        }
        int category = pRecord->mUnknown9;
        if (pRecord->mUnknown10 != 3) {
            category = !(p->mUnknown528.mUnknown0 <= 0.65f) ? 2 : 1;
        }
        if (category != pRecord->mUnknown9) {
            if (pRecord->mUnknown4 == -1 || !p->mpUnknown800[pRecord->mUnknown4].mUnknown1) {
                if (pRecord->mUnknown4 != -1 && p->mpUnknown800[pRecord->mUnknown4].mUnknown8 == key) {
                    fn_801BA384((AnimHeader_t *)pA, pEntries, pRecord->mUnknown4);
                }
                int next = fn_801BA2D0(pA, pEntries, &pEntries[pRecord->mUnknown0]);
                pRecord->mUnknown4 = pRecord->mUnknown0;
                AnimWgtSetLinear(&pEntries[pRecord->mUnknown0].mUnknown30, 16, -1.0f, 0.0f);
                pRecord->mUnknown9 = category;
                pRecord->mUnknown0 = next;
                p->mUnknown1008.mUnknown0 = pRecord->mUnknown8;
                p->mUnknown1008.mUnknown1 = pRecord->mUnknown9;
                p->mUnknown1008.mUnknown2 = pRecord->mUnknown10;
                int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
                fn_801BA418(pA, pEntries, pRecord->mUnknown0, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p);
                AnimWgtSet(&pEntries[pRecord->mUnknown0].mUnknown30, 0, 0.0f, 0, 0.0f);
                AnimWgtSetLinear(&pEntries[pRecord->mUnknown0].mUnknown30, 16, -1.0f, 1.0f);
            }
        }
        float rate = p->mUnknown528.mUnknown0;
        if (!(rate >= 0.01f)) {
            rate = 0.01f;
        }
        if (pRecord->mUnknown10 != 3) {
            if (pRecord->mUnknown9 == 1) {
                rate *= 1.5384615659713745f;
            } else if (!(rate >= 0.65f)) {
                rate = 0.65f;
            }
        }
        AnimSeqSetSpeed(&pEntries[pRecord->mUnknown0].mUnknown4C, MathInverse(rate));
        p->mpUnknown800[pRecord->mUnknown0].mUnknown2C = 1.5f;
        break;
    }
    }
    return 0;
}

extern "C" int fn_800DCC14(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DCC14 *pRecord = (Record_800DCC14 *)fn_801BE60C(p->mpUnknown792, key);
    Object_801BBD5C *pObject;
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        pObject = fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
        int index = fn_800DC674(pObject, p);
        pRecord->mUnknown4 = 1.0f;
        unsigned char *pEntry = (unsigned char *)&pTable->mEntries[index];
        PlayerLocoStartBlendPair((LocoBlendSet_t *)pObject, (Block_801BE60C *)pRecord, p, pEntry[1], (signed char)index, key, (FEPlyrModel_t *)pA, pEntries);
        pRecord->mUnknown12 = index;
        fn_800DC6A8(pObject, p, index, pRecord, (int)pEntries);
        pRecord->mUnknown16 = 0;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) != key) {
            break;
        }
        pObject = fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
        if (pRecord->mUnknown16 <= 0) {
            int index = fn_800DC674(pObject, p);
            if (index != pRecord->mUnknown12) {
                pRecord->mUnknown12 = index;
                pRecord->mUnknown16 = 8;
                unsigned char *pEntry = (unsigned char *)&pTable->mEntries[index];
                PlayerLocoSwitchBlendPair((LocoBlendSet_t *)pObject, (Block_801BE60C *)pRecord, p, pEntry[1], (signed char)index, key, pA, pEntries, 8);
            }
        }
        if (pRecord->mUnknown16 > 0) {
            --pRecord->mUnknown16;
            PlayerLocoSetFadeFraction((Block_801BE60C *)pRecord, 8.0f, pRecord->mUnknown16);
            PlayerLocoFadeOldPair((Block_801BE60C *)pRecord, pA, pEntries);
        } else {
            pRecord->mUnknown16 = 0;
            pRecord->mUnknown4 = 1.0f;
        }
        fn_800DC6A8(pObject, p, pRecord->mUnknown12, pRecord, (int)pEntries);
        break;
    }
    return 0;
}

extern "C" int fn_800DCE2C(Object_80039F5C *p, unsigned char *pInfo)
{
    Point_8017886C point = fn_80177FE0();
    int result = 0;
    unsigned int chance;
    switch (pInfo[3]) {
    case 1: chance = 100; break;
    case 2: chance = 70; break;
    case 3: chance = 50; break;
    case 4: chance = 25; break;
    case 5: chance = 5; break;
    default: chance = 0; break;
    }
    if ((unsigned int)fn_802372EC(0, 100) >= chance) {
        return result;
    }
    unsigned char role = p->mUnknown2914;
    int check = 0;
    if (fn_80177F70()) {
        switch (pInfo[0]) {
        case 1: result = 1; check = 1; break;
        case 12:
            if ((unsigned int)(role - 1) <= 1) {
                result = !(fabsf(point.mX - p->mMotion.mPos.mX) >= 6.0f) ? 2 : 1;
                check = 1;
            }
            if ((unsigned int)(role - 13) <= 2) {
                if (fn_80178308() == p->mIdBytes[2]) {
                    result = 0; check = 0;
                } else {
                    result = 2; check = 1;
                }
            }
            if (role == 16 || role == 18 || role == 17) {
                result = 2; check = 1;
            }
            break;
        case 7:
            if (p->mIdBytes[2] == fn_80178320()) { result = 2; check = 1; }
            break;
        case 4:
            if (role == 5 || role == 9 || role == 6 || role == 8 || role == 7 || role == 4 || role == 24) {
                result = !(fabsf(point.mX - p->mMotion.mPos.mX) >= 6.0f) ? 2 : 1;
                check = 1;
            }
            break;
        case 5:
            if (role == 3) {
                if (!(fabsf(point.mY - p->mMotion.mPos.mY) >= 3.0f)) { result = 2; check = 1; }
            } else if ((unsigned int)(role - 1) <= 1 || role == 4 || role == 25) {
                if (!(fabsf(point.mX - p->mMotion.mPos.mX) <= 6.0f)) { result = 2; check = 1; }
            }
            break;
        case 6:
            if (role == 7 || role == 24) { result = 3; check = 1; }
            break;
        }
    } else if (p->mIdBytes[2] == fn_80178308() && fn_801787A0()) {
        if (pInfo[0] == 8) {
            result = 3;
            switch (pInfo[2]) {
            case 2:
                if (!(p->mMotion.mPos.mX <= point.mX + 0.25f)) result = 0;
                break;
            case 3:
                if (!(p->mMotion.mPos.mX >= point.mX + 0.25f)) result = 0;
                break;
            case 4:
                if (p->mIdBytes[2] == 1) result = 0;
                break;
            case 7:
                result = 0;
                break;
            }
        }
    } else if (pInfo[0] == 2) {
        result = 3; check = 1;
    }
    if (check == 1) {
        fn_80178308();
        int valid = 1;
        switch (pInfo[2]) {
        case 2:
            if (role != 7 && role != 24 && !(p->mMotion.mPos.mX < point.mX + 0.25f) &&
                !(p->mMotion.mPos.mY < point.mY - 3.0f)) valid = 0;
            break;
        case 3:
            if (role == 7 || role == 24 || p->mMotion.mPos.mX < point.mX + 0.25f) {
                valid = 0;
            } else if (!(p->mMotion.mPos.mY >= point.mY - 3.0f)) {
                valid = 0;
            }
            break;
        case 7:
            valid = 0;
            if (!(p->mMotion.mPos.mY - point.mY >= 2.5f)) {
                valid = fabsf(p->mMotion.mPos.mX - point.mX) > 9.0f;
            }
            break;
        }
        if (!valid) result = 0;
    }
    return result;
}

extern "C" int fn_800DD2E8(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DD2E8 *pRecord = (Record_800DD2E8 *)fn_801BE60C(p->mpUnknown792, key);
    int found = 0;
    int chosen = -1;
    int score = 0;
    int update = 0;
    switch (mode) {
    case 0:
        pRecord->mUnknown0 = 5;
        fn_801BE760(p->mpUnknown792, key, 1);
        pRecord->mUnknown2 = 0xFFFF;
        update = 1;
    case 2:
        if (p->mFlags & 4) {
            if (fn_80177F70()) p->mFlags |= 0x40000;
            p->mFlags &= ~0x10;
            update = 1;
        }
        break;
    case 1:
        update = 1;
        break;
    }
    if (update == 1) {
        unsigned char category = 1;
        if (p->mUnknown16 != 2 && p->mUnknown108 != 2 && p->mUnknown200 != 2 && fn_801787A0() == 1) {
            --pRecord->mUnknown0;
            if (pRecord->mUnknown0 & 0x8000) {
                pRecord->mUnknown0 = 5;
                category = 0;
            }
        }
        while (!found) {
            int type = category ? 1 : 2;
            for (int i = 0; i < pTable->mCount; ++i) {
                unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
                if (pInfo[5] == type) {
                    int value = fn_800DCE2C(p, pInfo + 4);
                    if (value >= score && value > 0) {
                        if (score != value || (unsigned int)fn_802372EC(0, 100) <= 49) {
                            if (score != value) score = value;
                            chosen = i;
                        }
                    }
                }
            }
            if (chosen != -1) {
                found = 1;
            } else {
                ++category;
                if (category == 2) { chosen = 0; break; }
            }
        }
        int blend = pRecord->mUnknown6 ? 20 : 10;
        unsigned short old = pRecord->mUnknown2;
        if (old != 0xFFFF && pEntries[old].mUnknown1 == 2 && pEntries[old].mUnknown8 == key) {
            AnimWgtSetLinear(&pEntries[old].mUnknown30, blend, -1.0f, 0.0f);
        }
        unsigned char *pInfo = (unsigned char *)pTable->mEntries[chosen].mpInfo;
        pRecord->mUnknown6 = pInfo[5] == 2;
        pRecord->mUnknown4 = pInfo[4];
        p->mFlags &= ~4;
        pRecord->mUnknown2 = fn_801BA2A8(pA, pEntries, pTable->mEntries[chosen].mUnknown0, pTable->mEntries[chosen].mUnknown2, key, p, 1.0f);
        if (old != 0xFFFF) {
            AnimWgtSetLinear(&pEntries[pRecord->mUnknown2].mUnknown30, blend, 0.0f, 1.0f);
        }
    }
    return 0;
}

extern "C" int fn_800DD5E4(Object_80039F5C *p)
{
    int result = 0;
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (key >= 85 && key <= 86) {
        result = ((Record_800DD5E4 *)fn_801BE60C(p->mpUnknown792, key))->mUnknown6 == 1;
    }
    return result;
}

extern "C" int fn_800DD648(Object_80039F5C *p)
{
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (key >= 85 && key <= 86) {
        return ((Record_800DD648 *)fn_801BE60C(p->mpUnknown792, key))->mUnknown4;
    }
    return 0;
}

extern "C" int fn_800DD69C(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode)
{
    if (mode == 0) {
        fn_8009BD60(p);
        Point_8017886C point = fn_80177FE0();
        if (point.mY - p->mMotion.mPos.mY > 2.5f || fn_801486A0() == 3 || fn_801486A0() == 2) {
            p->mUnknown1008.mUnknown0 = 2;
        } else {
            p->mUnknown1008.mUnknown0 = 1;
        }
        int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
        fn_801BA2A8(pA, pB, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p, 1.0f);
    }
    return 0;
}

extern "C" int fn_800DD780(Object_80039F5C *p, int value, unsigned short key)
{
    int result = 1;
    if (InGameIsPlaying()) {
        unsigned char i;
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);
            if (pOther != p) {
                Record_800DD780 *pRecord = (Record_800DD780 *)fn_801BE60C(pOther->mpUnknown792, key);
                if (pRecord && pRecord->mUnknown16 == value && pRecord->mUnknown0 <= 59) {
                    result = 0;
                }
            }
        }
    }
    return result;
}

extern "C" int fn_800DD830(void *p) {
    return 1;
}

extern "C" int fn_800DD838(Object_80039F5C *p)
{
    int result = p->mUnknown1008Word;
    if (result == -1) {
        result = 2;
        switch (fn_800AD9B4()) {
        case 5:
            result = 30;
            if (p->mIdBytes[2] == fn_80178308() && p->mUnknown2914 == 0 && p->mIdBytes[1] == 0) {
                result = 94;
            } else {
                result |= 32;
            }
            if (BallFindHeldBy(p)) {
                result &= ~8;
            }
            break;
        case 1:
        case 10:
            result |= 12;
            break;
        case 2:
            result = 2;
            break;
        case 4:
        case 9:
            result |= 28;
            if (p->mUnknown2914 == 19 || p->mUnknown2914 == 20 || BallFindHeldBy(p)) {
                result &= ~8;
            }
            break;
        }
    }
    return result;
}

extern "C" void fn_800DD92C(Table_80089904 *pTable, unsigned short a, unsigned char value)
{
    unsigned char values[4];
    values[0] = value;
    values[1] = 255;
    values[2] = 255;
    values[3] = 255;
    fn_801BBC3C(a, pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF, pTable);
}

extern "C" void fn_800DD994(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, void *pA, void *pB,
                            Object_80039F5C *pOther, Record_800DDCE4 *pRecord, int mask)
{
    unsigned short weights[32];
    int total = 0;
    fn_800DD92C(pTable, p->mpUnknown796->mUnknown2, pRecord->mUnknown12);
    for (int i = 0; i < pTable->mCount; ++i) {
        unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
        int weight;
        switch (pInfo[4]) {
        case 1: weight = 100; break;
        case 2: weight = 50; break;
        case 3: weight = 20; break;
        case 4: weight = 10; break;
        case 5: weight = 5; break;
        default: weight = 0; break;
        }
        unsigned int shift = pInfo[5];
        unsigned int bit = (shift & 63) < 32 ? 1u << (shift & 31) : 0;
        if (!(mask & bit)) {
            weight = 0;
        } else if (shift == 5) {
            weight <<= 2;
        } else if (shift == 6) {
            weight <<= 3;
        }
        if (pInfo[6] != 1 && !fn_800DD830(p)) weight = 0;
        weights[i] = weight;
        total += weight;
    }
    unsigned short chosen = fn_802372EC(0, pTable->mCount);
    if (chosen >= pTable->mCount) chosen = pTable->mCount - 1;
    int i = 0;
    while (i < pTable->mCount) {
        if (fn_800DD780(p, (unsigned char)chosen, key)) {
            unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
            pRecord->mUnknown8 = pInfo[5];
            *((unsigned char *)pRecord + 16) = chosen;
            pRecord->mUnknown9 = pInfo[7] == 2;
            break;
        }
        chosen = chosen == pTable->mCount - 1 ? 0 : (unsigned short)(chosen + 1);
        ++i;
    }
    if (i == pTable->mCount) {
        chosen = fn_802372EC(0, i);
        if (chosen >= pTable->mCount) {
            unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
            chosen = pTable->mCount - 1;
            pRecord->mUnknown8 = pInfo[5];
            *((unsigned char *)pRecord + 16) = chosen;
            pRecord->mUnknown9 = pInfo[7] == 2;
        }
    }
    fn_802372EC(0, total);
    unsigned short old = pRecord->mUnknown14;
    Record_800D81C8 *pEntries = (Record_800D81C8 *)pB;
    if (old != 0xFFFF && !FELoopIsMainFEActive()) {
        AnimWgtSetLinear(&pEntries[old].mUnknown30, 10, -1.0f, 0.0f);
    }
    p->mFlags &= ~4;
    pRecord->mUnknown14 = fn_801BA2A8(pA, pB, pTable->mEntries[chosen].mUnknown0, pTable->mEntries[chosen].mUnknown2, key, pOther, 1.0f);
    if (FELoopIsMainFEActive()) {
        fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
    }
    unsigned char *pInfo = (unsigned char *)pTable->mEntries[chosen].mpInfo;
    pRecord->mUnknown10 = pInfo[6];
    if (old != 0xFFFF && !FELoopIsMainFEActive()) {
        AnimWgtSetLinear(&pEntries[(unsigned short)pRecord->mUnknown14].mUnknown30, 16, 0.0f, 1.0f);
    }
}

extern "C" void fn_800DDCE4(Object_80039F5C *p, Record_800DDCE4 *pRecord)
{
    if (p->mIdBytes[3] == 1) {
        if (pRecord->mUnknown9) {
            fn_8009D1F4(p);
        } else {
            fn_8009D1AC(p);
        }
    }
}

extern "C" int fn_800DDD24(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode)
{
    Record_800DDCE4 *pRecord = (Record_800DDCE4 *)fn_801BE60C(p->mpUnknown792, key);
    int mask;
    pRecord->mUnknown13 = 0;
    mask = pRecord->mUnknown4;
    switch (mode) {
    case 0:
        pRecord->mUnknown0 = 0;
        pRecord->mUnknown14 = -1;
        pRecord->mUnknown8 = 0;
        pRecord->mUnknown10 = 0;
        pRecord->mUnknown12 = 1;
        mask = pRecord->mUnknown4 = fn_800DD838(p);
        fn_801BE760(p->mpUnknown792, key, 1);
        pRecord->mUnknown13 = 1;
        break;
    case 1:
        break;
    case 2:
        pRecord->mUnknown0++;
        if (key == fn_801BE648(p->mpUnknown792) && (p->mFlags & 4)) {
            pRecord->mUnknown13 = 1;
        }
        fn_800DDCE4(p, pRecord);
        break;
    case 3:
        if (p->mIdBytes[3] == 1) {
            fn_8009D1AC(p);
        }
        break;
    }
    if (pRecord->mUnknown13) {
        fn_800DD994(pTable, p, key, pA, pB, p, pRecord, mask);
    }
    return 0;
}

extern "C" void fn_800DDE6C(Object_80039F5C *p)
{
    fn_8009BD60(p);
    if (p->mIdBytes[3] != 1 && BallFindHeldBy(p)) {
        p->mUnknown1008.mUnknown0 = 1;
    } else {
        p->mUnknown1008.mUnknown0 = 2;
    }
    if (p->mIdBytes[3] == 1) {
        if (p->mUnknown512.mUnknown14 == 7) {
            p->mUnknown1008.mUnknown1 = 3;
        } else {
            p->mUnknown1008.mUnknown1 = 2;
        }
    }
}

extern "C" int fn_800DDEE4(unsigned char *pA, unsigned char *pB)
{
    unsigned char i;
    int result = 1;
    for (i = 0; i < 2; i++) {
        if (pB[i] != 255 && pA[i] != pB[i]) {
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" unsigned short fn_800DDF34(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, int *pAngle, float *pTime, float *pRate)
{
    int facing = p->mMotion.mFacing & 0xFFFFFF;
    int desired = p->mUnknown512.mUnknown8 & 0xFFFFFF;
    *pAngle = 0;
    *pTime = 1.0f;
    *pRate = 1.0f;
    int difference = MathAngleDiff(facing, desired);
    int direction = ((desired - facing) & 0xFFFFFF) > 0x800000 ? -1 : 1;
    Info_800DDF34 *pChosen = 0;
    unsigned int chosen = 0;
    for (unsigned int i = 0; i < pTable->mCount; i++) {
        Info_800DDF34 *pInfo = (Info_800DDF34 *)pTable->mEntries[i].mpInfo;
        if (fn_800DDEE4(pInfo->mUnknown4, (unsigned char *)&p->mUnknown1008) &&
            difference >= pInfo->mUnknown16 && difference <= pInfo->mUnknown20 &&
            ((direction > 0 && pInfo->mUnknown12 > 0) || (direction < 0 && pInfo->mUnknown12 < 0))) {
            if (!pChosen || (unsigned int)fn_802372EC(0, 100) <= 49) {
                pChosen = pInfo;
                chosen = i;
            }
        }
    }
    if (pChosen && chosen < pTable->mCount) {
        if (key == 100 || p->mIdBytes[3] != 1) {
            *pRate = (float)(pChosen->mUnknown12 < 0 ? -pChosen->mUnknown12 : pChosen->mUnknown12) / (float)difference;
            if (!(*pRate >= 1.0f)) {
                *pRate = 1.0f;
            }
        }
        *pRate *= p->mUnknown512.mUnknown0;
        int magnitude = pChosen->mUnknown12 < 0 ? -pChosen->mUnknown12 : pChosen->mUnknown12;
        *pAngle = MathAngleDiff(magnitude, difference);
        if ((((facing + pChosen->mUnknown12) & 0xFFFFFF) - desired & 0xFFFFFF) <= 0x7FFFFF) {
            *pAngle = -*pAngle;
        }
        *pTime = pChosen->mUnknown24;
        *pTime /= *pRate;
    } else {
        chosen = 0;
    }
    return chosen;
}

extern "C" int fn_800DE19C(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DE19C *pRecord = (Record_800DE19C *)fn_801BE60C(p->mpUnknown792, key);
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        if (p->mIdBytes[3] != 1 || key == 100) {
            fn_800DDE6C(p);
        }
        int angle;
        float time, rate;
        int index = fn_800DDF34(pTable, p, key, &angle, &time, &rate);
        int entry = fn_801BA2A8(pA, pEntries, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        pRecord->mUnknown0 = entry;
        AnimSeqSetSpeed(&pEntries[entry].mUnknown4C, MathInverse(rate));
        pRecord->mUnknown4 = (int)((float)angle / time);
        p->mFlags &= ~4;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            p->mMotion.mFacing = (p->mMotion.mFacing + pRecord->mUnknown4) & 0xFFFFFF;
            Record_800D81C8 *pEntry = &p->mpUnknown800[pRecord->mUnknown0];
            pEntry->mUnknownC = (pEntry->mUnknownC + pRecord->mUnknown4) & 0xFFFFFF;
            if (p->mFlags & 4) {
                p->mMotion.mFacing &= 0xFFFFFF;
                pRecord->mUnknown4 = 0;
            }
        }
        break;
    }
    return 0;
}

extern "C" int fn_800DE364(unsigned int id)
{
    int result = 1;
    switch (id) {
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
    case 173:
        result = 0;
    }
    return result;
}

extern "C" void fn_800DE3B0(Block_800DE3B0 *pBlock, Object_80039F5C *p, Command_800DE3B0 *pCommand)
{
    int desired = fn_801CFE40(pCommand->mUnknown0.mUnknown4, pCommand->mUnknown0.mUnknown0) & 0xFFFFFF;
    State_800DE3B0 *pState = (State_800DE3B0 *)p->mUnknown1160.mUnknown12;
    int original = pState->mUnknown0 & 0xFFFFFF;
    Pair_802270A4 old = pState->mUnknown4;
    signed char frames = (int)(lbl_803EAD20 * pCommand->mUnknown18);
    if (frames < 1) {
        frames = 1;
    }
    pBlock->mUnknown3E = frames;
    pBlock->mUnknown38 = (original - desired) & 0xFFFFFF;
    if (pBlock->mUnknown38 > 0x800000) {
        pBlock->mUnknown38 -= 0x1000000;
    }
    pState->mUnknown1C = (p->mMotion.mFacing + pBlock->mUnknown38) & 0xFFFFFF;
    pState->mUnknown14.mUnknown0 = p->mMotion.mPos.mX;
    pState->mUnknown14.mUnknown4 = p->mMotion.mPos.mY;
    pBlock->mUnknown38 /= pBlock->mUnknown3E;
    pBlock->mUnknown3F = (int)(pCommand->mUnknown18 - (float)pBlock->mUnknown3E);
    pBlock->mUnknown4 = pCommand->mUnknownC;
    if (pState->mUnknown12 == 1) {
        fn_80227690(&pBlock->mUnknownC, &pBlock->mUnknown4, &p->mMotion);
        pBlock->mUnknown14 = desired;
    } else {
        fn_80227690(&pBlock->mUnknownC, &p->mMotion, &old);
        pBlock->mUnknown14 = original;
    }
}

extern "C" void fn_800DE51C(Object_80039F5C *p, Block_800DE3B0 *pBlock, int id)
{
    Table_80089904 *pTable = fn_801BE72C(p->mpUnknown796->mUnknown2, fn_801BE648(p->mpUnknown792));
    Entry_800DE51C *pChosen = 0, *pFallback = 0;
    int fallbackKey = 0;
    pBlock->mUnknown3F = pBlock->mUnknown3E = -1;
    for (unsigned int i = 0; i < pTable->mCount; i++) {
        int key = pTable->mEntries[i].mUnknown2 & 0x7FFF;
        Table_800DE51C *pRecords = (Table_800DE51C *)fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
        for (unsigned int j = 0; j < pRecords->mCount; j++) {
            Entry_800DE51C *pEntry = &pRecords->mEntries[j];
            if (!pEntry->mUnknown2) {
                pChosen = pEntry;
                if (pEntry->mUnknown0 == id) break;
            } else if (pEntry->mUnknown2 == 1 && pEntry->mUnknown0 == id) {
                fallbackKey = key;
                for (signed char k = 0; k < pRecords->mCount; k++) {
                    if (!pRecords->mEntries[k].mUnknown2) pFallback = &pRecords->mEntries[k];
                }
            }
        }
        if (pChosen->mUnknown0 == id) break;
        pChosen = 0;
    }
    if (pChosen && pChosen->mUnknown0 == id) {
        pBlock->mUnknown1C = 1;
        Object_80039F5C *pOther = 0;
        switch (p->mpState->mId) {
        case 16:
            if (((unsigned char *)&p->mUnknown1160)[56]) pBlock->mUnknown1F = ((unsigned char *)&p->mUnknown1160)[55];
            else if (p->mUnknown776 == 1) pBlock->mUnknown1F = 1;
            break;
        case 17:
            pOther = PlyrGet((unsigned char)(1-p->mIdBytes[2]), p->mpState->mUnknown3[0]);
            if (((unsigned char *)&p->mUnknown1160)[56]) pBlock->mUnknown1F = ((unsigned char *)&p->mUnknown1160)[55];
            else if (pOther->mUnknown776 == 1) pBlock->mUnknown1F = 1;
            break;
        case 32:
            if (p->mUnknown1036) pOther = PlyrGet((p->mUnknown1036 >> 8) & 255, p->mpState->mUnknown3[0]);
            else if (fn_801486A0() == 0 || fn_801486A0() == 1) pOther = PlyrGet(p->mIdBytes[2], p->mpState->mUnknown3[0]);
            else pOther = PlyrGet(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
            if (pOther->mUnknown1128[4] & 2) pBlock->mUnknown1F = 1;
            break;
        case 27: case 52: pOther = BallGetCurrentHolder(); break;
        default:
            if (p->mIdBytes[3] == 1) {
                int state = p->mUnknown1032;
                if (state == 4 || state == 5 || state == 2 || state == 8) {
                    pOther = fn_8009BCE8(&p->mUnknown1036);
                    if (pOther->mUnknown1128[4] & 2) pBlock->mUnknown1F = 1;
                } else if (state == 7) {
                    pOther = p;
                    if (pOther->mUnknown1128[4] & 2) pBlock->mUnknown1F = 1;
                }
            }
        }
        pBlock->mUnknownC.mUnknown0 = pBlock->mUnknownC.mUnknown4 = 0.0f;
        fn_800CEDA4(pChosen, &pBlock->mUnknown4, &pBlock->mUnknown14, pOther, pBlock->mUnknown1F);
        pBlock->mUnknown0 = 0.0f;
    } else {
        if (p->mpState->mId == 16) {
            if (((unsigned char *)&p->mUnknown1160)[56]) pBlock->mUnknown1F = ((unsigned char *)&p->mUnknown1160)[55];
            else if (p->mUnknown776 == 1) pBlock->mUnknown1F = 1;
        } else if (p->mpState->mId == 32 && (p->mUnknown1128[4] & 2)) pBlock->mUnknown1F = 1;
        Pair_802270A4 point;
        int angle;
        pBlock->mUnknown1C = 0;
        fn_800CEDA4(pFallback, &point, &angle, p, pBlock->mUnknown1F);
        fn_800DEAB0(p, pBlock, fallbackKey, &point, angle, pFallback);
    }
}

extern "C" void fn_800DE910(Object_80039F5C *p, Block_800DE3B0 *pBlock)
{
    Record_800D81C8 *pEntry = &p->mpUnknown800[pBlock->mUnknown1D];
    pBlock->mUnknown0 += 0.03333333507180214f;
    if (!(pBlock->mUnknown0 < 1.0f)) {
        pBlock->mUnknown1C = 0;
        pBlock->mUnknown0 = 1.0f;
        pEntry->mUnknownC = pBlock->mUnknown14;
    }
    Pair_802270A4 delta;
    fn_80227384(&delta, p->mUnknown552, -pEntry->mUnknownC);
    fn_80227638(&pBlock->mUnknownC, &delta, &pBlock->mUnknownC);
    fn_80227384(&delta, &pBlock->mUnknownC, pBlock->mUnknown14);
    fn_80227638(&delta, &delta, &pBlock->mUnknown4);
    p->mMotion.mPos.mX = (delta.mUnknown0 - p->mMotion.mPos.mX) * pBlock->mUnknown0 + p->mMotion.mPos.mX;
    p->mMotion.mPos.mY = (delta.mUnknown4 - p->mMotion.mPos.mY) * pBlock->mUnknown0 + p->mMotion.mPos.mY;
    int desired = (pBlock->mUnknown14 + pEntry->mUnknown1C) & 0xFFFFFF;
    int angle = (int)((float)MathAngleDiff(desired, p->mMotion.mFacing) * pBlock->mUnknown0);
    if (((p->mMotion.mFacing - desired) & 0xFFFFFF) <= 0x7FFFFF) {
        p->mMotion.mFacing = (p->mMotion.mFacing - angle) & 0xFFFFFF;
        pEntry->mUnknownC = (pEntry->mUnknownC - angle) & 0xFFFFFF;
    } else {
        p->mMotion.mFacing = (p->mMotion.mFacing + angle) & 0xFFFFFF;
        pEntry->mUnknownC = (pEntry->mUnknownC + angle) & 0xFFFFFF;
    }
}

extern "C" void fn_800DEAB0(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key, void *pData, int angle, Entry_800DE51C *pRecord)
{
    int active = fn_801BE648(p->mpUnknown792);
    unsigned char table[3048];
    union { Command_800CEE74 command; Command_800DE3B0 view; } command;
    switch (active) {
    case 181: case 186:
        fn_801BBC3C(1, key, (Table_80089904 *)table);
        fn_800CEE74(&command.command, p, fn_8009BCE8(&p->mUnknown336), pData, angle, (unsigned short)key, pBlock->mUnknown1F);
        fn_800CE804(&command.command, (Table_80089904 *)table, 0);
        fn_800DE3B0(pBlock, p, &command.view);
        break;
    case 195: case 196: case 197: case 210: case 224: case 228: case 229: case 230: case 235: case 237:
        fn_801BBC3C(1, key, (Table_80089904 *)table);
        fn_800CEE74(&command.command, p, 0, 0, 0, (unsigned short)key, pBlock->mUnknown1F);
        fn_800CE804(&command.command, (Table_80089904 *)table, pRecord->mUnknown0);
        fn_800DE3B0(pBlock, p, &command.view);
        break;
    }
}

extern "C" void fn_800DEC10(Object_80039F5C *p, Block_800DE3B0 *pBlock)
{
    State_800DE3B0 *pState = (State_800DE3B0 *)p->mUnknown1160.mUnknown12;
    Record_800D81C8 *pEntry = &p->mpUnknown800[pBlock->mUnknown1D];
    Object_80039F5C *pOther = 0;
    Record_800D81C8 *pOtherEntry = 0;
    Block_801BE60C *pOtherBlock = 0;
    int index = 0xFFFF;
    unsigned short key = (unsigned short)pBlock->mUnknown18;
    if (fn_801BE648(p->mpUnknown792) == 181 || fn_801BE648(p->mpUnknown792) == 186) {
        pOther = PlyrGet(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
        index = fn_801BA5A8(pOther->mpUnknown796, pOther->mpUnknown800, key, 0);
    }
    Pair_802270A4 point = pState->mUnknown4;
    if (index != 0xFFFF) {
        pOtherEntry = &pOther->mpUnknown800[index];
        pOtherBlock = fn_801BE60C(pOther->mpUnknown792, key);
    }
    Pair_802270A4 rotated, delta, offset;
    if (pBlock->mUnknown3E > 0) {
        --pBlock->mUnknown3E;
        if (pState->mUnknown12 == 1) {
            fn_80227384(&rotated, &pBlock->mUnknownC, pBlock->mUnknown38);
            fn_80227690(&delta, &rotated, &pBlock->mUnknownC);
            fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &delta);
            pBlock->mUnknownC = rotated;
            pBlock->mUnknown14 += pBlock->mUnknown38;
        } else {
            fn_80227690(&delta, &pBlock->mUnknown4, &point);
            fn_80227384(&rotated, &delta, pBlock->mUnknown38);
            fn_80227690(&delta, &rotated, &delta);
            fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &delta);
            fn_80227384(&rotated, &pBlock->mUnknownC, pBlock->mUnknown38);
            fn_80227690(&delta, &rotated, &pBlock->mUnknownC);
            pBlock->mUnknownC = rotated;
            fn_80227638(&p->mMotion, &p->mMotion, &delta);
            if (index != 0xFFFF) {
                fn_80227638(&pOther->mMotion, &pOther->mMotion, &delta);
                Point_8017886C adjustment = {delta.mUnknown0, delta.mUnknown4};
                fn_800DF134(pOther, adjustment, 0, pBlock->mUnknown18);
            }
        }
        p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown38) & 0xFFFFFF;
        p->mpUnknown800[pBlock->mUnknown1D].mUnknownC = (pEntry->mUnknownC + pBlock->mUnknown38) & 0xFFFFFF;
        if (index != 0xFFFF) {
            fn_80227690(&delta, &pOther->mMotion, &p->mMotion);
            fn_80227384(&rotated, &delta, pBlock->mUnknown38);
            fn_80227638(&pOther->mMotion, &rotated, &p->mMotion);
            pOther->mMotion.mFacing = (pOther->mMotion.mFacing + pBlock->mUnknown38) & 0xFFFFFF;
            pOtherEntry->mUnknownC = (pOtherEntry->mUnknownC + pBlock->mUnknown38) & 0xFFFFFF;
            fn_80227690(&delta, &pOtherBlock->mUnknown4, &p->mMotion);
            fn_80227384(&rotated, &delta, pBlock->mUnknown38);
            fn_80227690(&offset, &rotated, &delta);
            Point_8017886C adjustment = {offset.mUnknown0, offset.mUnknown4};
            fn_800DF134(pOther, adjustment, pBlock->mUnknown38, pBlock->mUnknown18);
        }
    } else if (pBlock->mUnknown3E == 0) {
        --pBlock->mUnknown3E;
        if (pState->mUnknown12 == 1) {
            fn_80227384(&rotated, (char *)pEntry + 36, pState->mUnknown1C);
            fn_80227690(&delta, &p->mMotion, &pState->mUnknown14);
            fn_80227690(&delta, &delta, &rotated);
            fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &delta);
            fn_80227690(&pBlock->mUnknownC, &point, &pBlock->mUnknown4);
        } else {
            fn_80227690(&pBlock->mUnknownC, &point, &pBlock->mUnknown4);
        }
        pBlock->mUnknownC.mUnknown0 /= (float)pBlock->mUnknown3F;
        pBlock->mUnknownC.mUnknown4 /= (float)pBlock->mUnknown3F;
    }
    if (pBlock->mUnknown3E < 0 && pBlock->mUnknown3F > 0) {
        --pBlock->mUnknown3F;
        fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &pBlock->mUnknownC);
        fn_80227638(&p->mMotion, &p->mMotion, &pBlock->mUnknownC);
        if (index != 0xFFFF) {
            fn_80227638(&pOther->mMotion, &pOther->mMotion, &pBlock->mUnknownC);
            Point_8017886C adjustment = {pBlock->mUnknownC.mUnknown0, pBlock->mUnknownC.mUnknown4};
            fn_800DF134(pOther, adjustment, 0, pBlock->mUnknown18);
        }
    }
    if (pBlock->mUnknown3F == 0) {
        --pBlock->mUnknown3F;
        Vector_80039F5C position = {pBlock->mUnknown4.mUnknown0, pBlock->mUnknown4.mUnknown4, pBlock->mUnknownC.mUnknown0};
        if (fn_801784C4()) {
            position.mX = -position.mX;
            position.mY = -position.mY;
        }
        float distance;
        void *pSurface = BigObjFindNearestOfType(&position, 7, &distance);
        if (pSurface && !(distance >= 1.6f)) HotspotFrameTouch(pSurface, p);
    }
}

extern "C" void fn_800DF134(Object_80039F5C *p, Point_8017886C offset, int angle, int key)
{
    if (key == fn_801BE648(p->mpUnknown792)) {
        Block_801BE60C *pRecord = fn_801BE60C(p->mpUnknown792, key);
        if (pRecord) {
            if (pRecord->mUnknown1C) {
                pRecord->mUnknown4 += offset.mX;
                pRecord->mUnknown14 = (pRecord->mUnknown14 + angle) & 0xFFFFFF;
                pRecord->mUnknown8 += offset.mY;
            }
            p->mpUnknown800[pRecord->mUnknown1D].mUnknownC =
                (p->mpUnknown800[pRecord->mUnknown1D].mUnknownC + angle) & 0xFFFFFF;
        }
    }
}

extern "C" int fn_800DF1F4(Table_80089904 *pTable, unsigned short key, void *pData, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Block_800DE3B0 *pBlock = (Block_800DE3B0 *)fn_801BE60C(p->mpUnknown792, key);
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        int first = p->mUnknown1008.mUnknown0 | (p->mUnknown1008.mUnknown1 << 8);
        int second = p->mUnknown1008.mUnknown2 | (p->mUnknown1011 << 8);
        pBlock->mUnknown1D = fn_801BA2A8(pData, pEntries, second, first, key, p, 1.0f);
        pBlock->mUnknown18 = key;
        if (fn_800DE364(key)) p->mFlags |= 512;
        bool excluded = (key >= 49 && key <= 55) || key == 59 || key == 60 || key == 106 || key == 107;
        if (key == 172 || key == 173) {
            for (unsigned short i = 0; i < pTable->mCount; i++) {
                if (pTable->mEntries[i].mUnknown0 == second) {
                    Table_800DE51C *pRecords = (Table_800DE51C *)fn_801BBD5C(pTable->mEntries[i].mUnknown2 & 0x7FFF, p->mpUnknown796->mUnknown2);
                    if (pRecords->mEntries[0].mUnknown0 == first || pRecords->mEntries[1].mUnknown0 == first) {
                        pBlock->mUnknown3C = ((unsigned char *)pTable->mEntries[i].mpInfo)[4];
                        break;
                    }
                }
            }
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown336);
            float rate = p->mpState->mId == 16 ? fn_80114EE4(p, pOther) : fn_80114EE4(pOther, p);
            AnimSeqSetSpeed(&pEntries[pBlock->mUnknown1D].mUnknown4C, MathInverse(rate));
        } else if (!excluded && p->mUnknown512.mUnknown14 == 5) {
            float rate = p->mUnknown512.mUnknown0 + 0.8f;
            if (!(rate <= 1.2f)) rate = 1.2f;
            AnimSeqSetSpeed(&pEntries[pBlock->mUnknown1D].mUnknown4C, MathInverse(rate));
        }
        fn_800DE51C(p, pBlock, first);
        if (pBlock->mUnknown1F) {
            Record_800D81C8 *pEntry = &pEntries[pBlock->mUnknown1D];
            fn_801BA6BC(pEntry, !fn_801BA6B0(pEntry));
            pBlock->mUnknown1F = fn_801BA6B0(&pEntries[pBlock->mUnknown1D]);
        }
        AnimMomentumInit(&pBlock->mUnknown20, p, pBlock->mUnknown1D);
        pBlock->mUnknown1E = fn_801784C4();
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            int orientation = fn_801784C4();
            if (orientation != pBlock->mUnknown1E) {
                pBlock->mUnknown1E = orientation;
                if (pBlock->mUnknown1C) {
                    pBlock->mUnknown4.mUnknown0 = -pBlock->mUnknown4.mUnknown0;
                    pBlock->mUnknown4.mUnknown4 = -pBlock->mUnknown4.mUnknown4;
                    pBlock->mUnknown14 = (pBlock->mUnknown14 + 0x800000) & 0xFFFFFF;
                } else if (key == 181 || key == 186) fn_800DF654(p, (Block_801BE60C *)pBlock);
            }
            if (key == 181 || key == 186) fn_800DEC10(p, pBlock);
            if (pBlock->mUnknown1C) fn_800DE910(p, pBlock);
            if (fn_801BE648(p->mpUnknown792) == 94 || fn_801BE648(p->mpUnknown792) == 95 || fn_801BE648(p->mpUnknown792) == 234) AnimMomentumUpdateLinked(&pBlock->mUnknown20, p);
            else AnimMomentumUpdate(&pBlock->mUnknown20, p);
        } else if (!fn_800DE364(fn_801BE648(p->mpUnknown792))) p->mFlags &= ~512;
        if ((key == 172 || key == 173) && (p->mFlags & 4)) fn_800C854C(p, key, pBlock->mUnknown3C);
        break;
    case 1: case 3:
        pBlock->mUnknown1C = 0;
        if (key == fn_801BE648(p->mpUnknown792) || !fn_800DE364(fn_801BE648(p->mpUnknown792))) p->mFlags &= ~512;
        break;
    }
    return 0;
}

extern "C" void fn_800DF654(Object_80039F5C *p, Block_801BE60C *pRecord)
{
    Block_800DF654 *pBlock = (Block_800DF654 *)p->mUnknown1160.mUnknown12;
    pRecord->mUnknown4 = -pRecord->mUnknown4;
    pRecord->mUnknown8 = -pRecord->mUnknown8;
    pRecord->mUnknownC = -pRecord->mUnknownC;
    pRecord->mUnknown10 = -pRecord->mUnknown10;
    pRecord->mUnknown14 = (pRecord->mUnknown14 + 0x800000) & 0xFFFFFF;
    pBlock->mUnknown0 = (pBlock->mUnknown0 + 0x800000) & 0xFFFFFF;
    pBlock->mUnknown4 = -pBlock->mUnknown4;
    pBlock->mUnknown8 = -pBlock->mUnknown8;
    pBlock->mUnknown20 = -pBlock->mUnknown20;
    pBlock->mUnknown24 = -pBlock->mUnknown24;
    pBlock->mUnknown28 = (pBlock->mUnknown28 + 0x800000) & 0xFFFFFF;
}
