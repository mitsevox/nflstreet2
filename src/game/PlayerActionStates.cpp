/* Player action states: the handlers of player states in the player state-handler table (attached
   model animation, ball release and pickup, a fixed-animation state) and the alignment and
   pursuit helpers that they and the play code call. */
#include "game/PlayerAction.h"

extern "C" int PlayerActionTakeFlag1000(Object_80039F5C *p)
{
    int result = 0;
    if (p->mFlags & 0x1000) {
        p->mFlags &= ~0x1000;
        result = 1;
    }
    return result;
}

extern "C" void PlayerActionGetJointPose(Object_80039F5C *p, int joint, Vector_80039F5C *pPos, QuatEulerAngles_t *pAngles)
{
    float rot[4];
    PlyrGetBallHoldTransform(p, pPos, rot);
    QuatToEuler(pAngles, rot);
}

extern "C" void PlayerActionMoveBall(Ball_t *pBall, Vector_80039F5C *pPos, int *pAngles)
{
    Vector_80039F5C old;
    Vector_80039F5C delta;
    BallGetPosition(pBall, &old);
    Vec3Sub(&delta, pPos, &old);
    BallSetPrevPosition(pBall, &old);
    BallSetPosition(pBall, pPos);
    BallSetRotation(pBall, pAngles);
    BallSetVelocity(pBall, &delta);
}

extern "C" void PlayerActionCharAnimUpdateAttachments(Object_80039F5C *p, Character_80093BCC *pCharacter, Attachment_800DF7CC *pAttachments, Frame_800DF7CC *pFrame, int index, unsigned int frame)
{
    float time = (float)frame / AnimSequencerGetTicksPerSecond(p);
    Character_800DF7CC *pView = (Character_800DF7CC *)pCharacter;
    AnmsGetScript(pView->mUnknown0, pView->mUnknown4);
    Vector_80039F5C position;
    QuatEulerAngles_t angles;
    Ball_t *pBall;
    if (pFrame->mUnknown20 && pFrame->mUnknown20 != 0x4E4F4E45) {
        Block_80170E64 *pInfo = p->mpUnknown4;
        if (AnimSeqncrGetKeyValue(pFrame, time) && !PlayerActionTakeFlag1000(p)) {
            int joint = !pFrame->mUnknown19 || (pView->mFlags & 8) ? 25 : 19;
            PlayerActionGetJointPose(p, joint, &position, &angles);
            pAttachments[index].mPos.mX = position.mX;
            pAttachments[index].mPos.mY = position.mY;
            pAttachments[index].mPos.mZ = position.mZ;
            pAttachments[index].mAngles = angles;
            pAttachments[index].mFrame = frame;
        } else {
            *(int *)(pInfo->mUnknown24 + 8) = 0;
            if (pAttachments[index].mFrame != -1) {
                pAttachments[index].mFrame = -1;
                switch ((unsigned int)pFrame->mUnknown20) {
                // FAKEMATCH: the empty 'NONE' label leaves no compare in the target (it tests only 'COIN' and
                // 'BALL'); it does nothing, like the missing default, and only shapes the compare tree
                case 0x4E4F4E45:
                case 0x434F494E:
                    break;
                case 0x42414C4C:
                    if (BallsExist()) {
                        pBall = pView->mpBall[index];
                        if (pBall) BallRelease(pBall, 3, 0);
                    } else {
                        pView->mpUnknown20->mUnknown12 &= ~0x40000;
                    }
                    break;
                }
            }
        }
        switch ((unsigned int)pFrame->mUnknown20) {
        // FAKEMATCH: the empty 'NONE' label leaves no compare in the target (it tests only 'COIN' and 'BALL');
        // it does nothing, like the missing default, and only shapes the compare tree
        case 0x4E4F4E45:
        case 0x434F494E:
            break;
        case 0x42414C4C:
            if (BallsExist()) {
                pBall = pView->mpBall[index];
                if (BallStateGet(pBall, 0) == 8) PlayerActionMoveBall(pBall, &position, (int *)&angles);
            }
            break;
        }
    }
}

extern "C" void PlayerActionCharAnimNotify(Object_80039F5C *p, void *pRecord, unsigned int value) {
}

extern "C" int PlayerActionCharAnimLoad(Object_80039F5C *p, float *pValue)
{
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    Character_80093BCC *pCharacter = fn_80093BCC(pBlock->mUnknown8);
    if (pCharacter) {
        Character_800DF7CC *pView = (Character_800DF7CC *)pCharacter;
        Frame_800DF7CC *pFrame = AnimSeqncrGetPlayerPtr(AnmsGetScript(pCharacter->mUnknown0, pCharacter->mUnknown4), pBlock->mUnknown9);
        p->mpUnknown4->mUnknown20 |= 0x1000;
        unsigned int handle = AnimFileGetSlotFromFileNum(pFrame->mUnknown42 | 0x4000, pFrame->mUnknown14);
        void *pData = AnimFileGetPtrFromSlot(handle);
        if (pData) {
            AnimSeq_t seq;
            if (AnimSeqHasOpcode(&seq, AnimFileGetAnimation(pData, 0), 0x8003) || AnimSeqHasOpcode(&seq, AnimFileGetAnimation(pData, 0), 0x8001)) {
                pBlock->mUnknown13 = 1;
            } else {
                pBlock->mUnknown13 = 0;
            }
            *pValue = AnimSeqGetLife(AnimFileGetAnimation(pData, 0));
            fn_8009BD60(p);
            p->mUnknown1008.mUnknown0 = ((unsigned char *)pCharacter)[3];
            p->mUnknown1008.mUnknown1 = ((unsigned char *)pCharacter)[7];
            p->mUnknown1008.mUnknown2 = pBlock->mUnknown9;
            p->mUnknown1011 = pBlock->mUnknown10;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 10, 1.0f, p);
            if ((pView->mFlags & 32) || p->mIdBytes[3] == 3) fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            if (pView->mFlags & 8) {
                unsigned char count = AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 10);
                for (unsigned char i = 0; i < count; i++) {
                    AnimChannel_t *pEntry = &p->mpUnknown800[AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 10, i)];
                    AnimChanSetMirrored(pEntry, !AnimChanIsMirrored(pEntry));
                }
                fn_800D7A0C(p, p->mUnknown776 == 2 ? 1 : 2);
            }
            if ((pView->mFlags & 16) && AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 10)) {
                p->mpUnknown800[AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 10, 0)].mUnknown2C = 1.0f / p->mUnknown768;
            }
            if (handle != 0xFFFFFF) {
                unsigned int other = AnimFileGetSiblingSlot(handle, 1024);
                if (other != 0xFFFFFF) {
                    fn_8009BD60(p);
                    unsigned int key = AnimFileGetStateQueryIndex(0, other);
                    p->mUnknown1012[1] = key >> 8;
                    p->mUnknown1012[0] = key;
                    fn_801BE068(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, 0, 1.0f, p);
                }
            }
            p->mpUnknown4->mUnknown20 |= 16;
            p->mFlags &= ~4;
            p->mFlags &= ~0x1000;
            return 0;
        }
    }
    return 1;
}

extern "C" void PlayerActionCharAnimEnter(Object_80039F5C *p)
{
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    pBlock->mUnknown8 = p->mpState->mUnknown1;
    pBlock->mUnknown9 = p->mpState->mUnknown2;
    pBlock->mUnknown10 = 0;
    pBlock->mUnknown12 = 0;
    pBlock->mUnknown0 = 0.0f;
    pBlock->mUnknown4 = 0.0f;
    pBlock->mUnknown11 = 0;
    p->mpUnknown4->mUnknown20 |= 0x80;
    if (p->mIdBytes[3] == 1 || p->mIdBytes[3] == 3) {
        PlyrClearPendingMsg(p, 0);
        p->mUnknown512.mUnknown14 = 0;
    }
    PlayerActionCharAnimLoad(p, &pBlock->mUnknown4);
}

extern "C" int PlayerActionCharAnimExit(Object_80039F5C *p)
{
    Character_80093BCC *pCharacter = fn_80093BCC(p->mUnknown344);
    Actor_801C009C *pActor = AnmsGetScript(pCharacter->mUnknown0, pCharacter->mUnknown4);
    PlyrObjsSetDrawFlag(1);
    p->mpUnknown4->mUnknown20 &= ~0x80;
    if (!FELoopIsMainFEActive() && fn_800AD9B4() == 7) {
        return 0;
    }
    if (!(pActor->mUnknown8 & 0x40)) {
        switch (p->mIdBytes[3]) {
        case 3:
            fn_8009BD60(p);
            p->mUnknown1008.mUnknown0 = 1;
            p->mUnknown1008Word = 6;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 82, 1.0f, p);
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            break;
        case 1: {
            int mode = fn_800AD9B4();
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            if (mode == 4) {
                PlyrTryQueueMsg62(p, 0, -1);
            }
            break;
        }
        }
    }
    return 1;
}

extern "C" int PlayerActionCharAnimUpdate(Object_80039F5C *p)
{
    int result = 0;
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    Character_80093BCC *pCharacter = fn_80093BCC(pBlock->mUnknown8);
    Attachment_800DF7CC *pAttachments = AnmsGetSceneAttachments(pBlock->mUnknown8);
    if (!pCharacter || !pAttachments) {
        PlyrHandSetPoseByKey(p, 1, 8, 0);
        PlyrHandSetPoseByKey(p, 1, 8, 1);
        return 1;
    }
    Actor_801C009C *pActor = AnmsGetScript(pCharacter->mUnknown0, pCharacter->mUnknown4);
    Frame_800DF7CC *pFrame = AnimSeqncrGetPlayerPtr(pActor, pBlock->mUnknown9);
    PlayerActionCharAnimNotify(p, pCharacter, (unsigned int)pBlock->mUnknown0);
    PlayerActionCharAnimUpdateAttachments(p, pCharacter, pAttachments, pFrame, pBlock->mUnknown9, (unsigned int)pBlock->mUnknown0);
    if (!AnmsIsScenePaused(pBlock->mUnknown8)) {
    float scale = gFrameTimeScale;
    pBlock->mUnknown0 += scale;
    if (!(pBlock->mUnknown0 <= pBlock->mUnknown4) && !pBlock->mUnknown13) {
        AnmsStopCamShot(pBlock->mUnknown8);
        p->mpUnknown4->mUnknown20 &= ~0x1000;
        p->mpUnknown4->mUnknown20 &= ~0x80;
        if (!(pActor->mUnknown8 & 64)) {
            switch (p->mIdBytes[3]) {
            case 3:
                fn_8009BD60(p);
                p->mUnknown1008.mUnknown0 = 1;
                p->mUnknown1008Word = 6;
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 82, 1.0f, p);
                fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
                break;
            case 1: {
                int mode = fn_800AD9B4();
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
                fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
                if (mode == 4) ScrmPlayerToHuddle(p);
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
                p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
                break;
            }
            }
        }
        PlyrHandSetPoseByKey(p, 1, 8, 0);
        PlyrHandSetPoseByKey(p, 1, 8, 1);
        result = 1;
    }
    }
    return result;
}

extern "C" int PlayerActionCharAnimGetTime(Object_80039F5C *p, float *pA, float *pB)
{
    if (p->mIdBytes[3] == 1 && p->mpState->mId == 50) {
        Block_800E0188 *pBlock = (Block_800E0188 *)&p->mUnknown336;
        if (pA) {
            *pA = pBlock->mUnknown0;
        }
        if (pB) {
            *pB = pBlock->mUnknown4;
        }
        return 1;
    }
    return 0;
}

extern "C" void PlayerActionDropBallRelease(Object_80039F5C *p, Block_800E0230 *pBlock, int a)
{
    if (p == BallGetCurrentHolder() && fn_801BE648(p->mpUnknown792) == 74 && fn_801486A0()) {
        PossReleaseBall(p);
    }
}

extern "C" void PlayerActionDropBallPickVariant(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (SyncRandGetRange(0, 100) <= 64) {
        pBlock->mUnknown9 = 0;
        if (p->mUnknown776 == 2) {
            PlayerActionDropBallRelease(p, pBlock, 6);
        } else {
            PlayerActionDropBallRelease(p, pBlock, 3);
        }
    } else {
        pBlock->mUnknown9 = 1;
        if (p->mUnknown776 == 2) {
            PlayerActionDropBallRelease(p, pBlock, 6);
        } else {
            PlayerActionDropBallRelease(p, pBlock, 3);
        }
    }
}

extern "C" float PlayerActionDropBallGetSpeed(Object_80039F5C *p)
{
    float value;
    if (!fn_80124C28(p, &value, 0x355555, 5.0f, 0.5f, p->mMotion.mFacing)) {
        return 0.5f;
    }
    float result = 1.0f - value * 0.2f;
    return result * 0.5f + 0.5f;
}

extern "C" void PlayerActionDropBallStart(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.2f || (unsigned char)fn_800B9A90(lbl_803EAB84) != 1) {
        pBlock->mUnknown8 = 0;
        pBlock->mUnknown0 = PlayerActionDropBallGetSpeed(p);
        pBlock->mUnknown4 = p->mMotion.mFacing;
        float y = fabsf(p->mMotion.mPos.mY);
        if (!(y <= ScrmGetGoalLineY())) {
            if (MathAngleDiff(p->mMotion.mFacing, 0) > 0x400000) {
                pBlock->mUnknown4 = 0x800000;
            } else {
                pBlock->mUnknown4 = 0;
            }
        }
        p->mUnknown512.mUnknown14 = 10;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown0;
    } else {
        PlayerActionDropBallPickVariant(p, pBlock);
    }
}

extern "C" void PlayerActionDropBallLetGo(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    Ball_t *pBall = BallFindHeldBy(p);
    if (pBall) {
        switch (pBlock->mUnknown9) {
        case 0:
        case 1: {
            Vector_80039F5C velocity;
            BallSetTarget(pBall, 0);
            BallGetVelocity(pBall, &velocity);
            BallReleaseStill(pBall, 3, 0);
            BallLaunchWithVelocity(pBall, &velocity, 3, 0.0f, 1.0f);
            break;
        }
        }
    }
}

extern "C" void PlayerActionDropBallWait(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (!(p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed > 0.2f) && (unsigned char)fn_800B9A90(lbl_803EAB84) == 1) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = 0.2f;
        PlayerActionDropBallPickVariant(p, pBlock);
    } else {
        p->mUnknown512.mUnknown14 = 10;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown0;
    }
}

extern "C" int PlayerActionDropBallEnter(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (BallFindHeldBy(p) == 0) {
        return 1;
    }
    PlayerActionDropBallStart(p, pBlock);
    return 0;
}

extern "C" int PlayerActionDropBallUpdate(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (BallFindHeldBy(p) == 0) {
        return 1;
    }
    unsigned char state = pBlock->mUnknown8;
    switch (state) {
    case 0:
        PlayerActionDropBallWait(p, pBlock);
        break;
    case 1:
        if (p->mFlags & 0x1000) {
            p->mFlags &= ~0x1000;
            PlayerActionDropBallLetGo(p, pBlock);
        }
        if (p->mFlags & 4) {
            PlayerActionDropBallLetGo(p, pBlock);
            p->mUnknown512.mUnknown14 = state;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            return 1;
        }
        break;
    }
    return 0;
}

extern "C" int PlayerActionDropBallExit(Object_80039F5C *p) {
    return 0;
}

static inline void _PlayerActionFallBack(Object_80039F5C *p, int handle, int index)
{
    fn_80099F04(p, handle, index);
    p->mUnknown1160.mUnknown53 = 1;
    fn_800A2190(1);
    AudmonEventPostId(49, &p->mMotion.mPos, p->mId, 0, 0, 0);
    AudmonEventPostId(54, &p->mMotion.mPos, p->mId, 0, 0, 0);
}

extern "C" void PlayerActionCatchResolve(Object_80039F5C *p, int handle, int index)
{
    if (p->mRatings[0] < lbl_803EAD34) {
        unsigned int threshold = p->mRatings[0] * lbl_803EAD2C;
        if ((unsigned int)SyncRandGetRange(0, lbl_803EAD28) > threshold) {
            p->mUnknown1008.mUnknown0 = CatchAnimGetRecord(handle)->mUnknown4;
            if (!(SyncRandGetFloat(0) >= lbl_803EAD30)) p->mUnknown1008.mUnknown1 = 1; else p->mUnknown1008.mUnknown1 = 2;
            p->mUnknown1008.mUnknown2 = handle < 0 ? 2 : 1;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 226, 1.0f, p);
        } else {
            _PlayerActionFallBack(p, handle, index);
        }
    } else {
        _PlayerActionFallBack(p, handle, index);
    }
}

extern "C" void PlayerActionCatchGetBallPos(int a, Vector_80039F5C *pOut, unsigned char *pIndex)
{
    BallGetPosition(BallGet(*pIndex), pOut);
}

extern "C" int PlayerActionCatchEnter(Object_80039F5C *p)
{
    Block_800E0850 *pBlock = (Block_800E0850 *)&p->mUnknown336;
    Block_801718E8 *pMove = &p->mUnknown1160;
    Vector_80039F5C velocity;
    Vector_80039F5C pos;
    unsigned char index;
    int handle;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown2 = 0;
    CatchAnimUnpackHandle(p->mpState->mUnknown1, p->mpState->mUnknown2, &index, &handle);
    float time = CatchAnimGetTime(handle);
    if (fn_801BE648(p->mpUnknown792) == 224) {
        unsigned char entry = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 224, 0);
        time += AnimSeqGetLife(p->mpUnknown800[entry].mUnknown4C.mpUnknown0);
    }
    Ball_t *pBall = BallGet(index);
    BallGetPosition(pBall, &pBlock->mUnknown4);
    BallGetVelocity(pBall, &velocity);
    float drop = time * 0.002981481608003378f * time * 0.5f;
    pBlock->mUnknown4.mX = velocity.mX * time + pBlock->mUnknown4.mX;
    pBlock->mUnknown4.mY = velocity.mY * time + pBlock->mUnknown4.mY;
    pBlock->mUnknown4.mZ += velocity.mZ * time - drop;
    pBlock->mUnknown16 = (unsigned int)time;
    pBlock->mUnknown24 = (int)(time * 0.8f);
    pBlock->mUnknown20 = (int)(p->mpState->mUnknown3[0] << 16);
    if (pBlock->mUnknown20 > 0x800000) pBlock->mUnknown20 -= 0x1000000;
    if (pBlock->mUnknown24) pBlock->mUnknown20 /= pBlock->mUnknown24;
    if (CatchAnimGetType(handle) == 5) {
        pos = p->mMotion.mPos;
        pos.mZ = (float)p->mMotion.mUnknown32;
    }
    if (p->mFlags & 0x4000) {
        pBlock->mUnknown28 = 1;
    } else {
        pBlock->mUnknown28 = 0;
    }
    fn_800A3B58(p, 4, 0);
    if (fn_801BE648(p->mpUnknown792) == 227) {
        pMove->mUnknown54 = 1;
        PlayerMoveBegin(p, 1, 28);
    }
    if (fn_801BE648(p->mpUnknown792) == 224 || fn_801BE648(p->mpUnknown792) == 225) {
        p->mFlags |= 8;
    }
    return 0;
}

extern "C" int PlayerActionCatchUpdate(Object_80039F5C *p)
{
    Block_800E0850 *pBlock = (Block_800E0850 *)&p->mUnknown336;
    ++pBlock->mUnknown0;
    fn_800B8344(p);
    if (!CatchIsInCatchAnim(p)) return 1;
    Input_800B6D34 input;
    unsigned char index;
    int handle;
    CatchAnimUnpackHandle(p->mpState->mUnknown1, p->mpState->mUnknown2, &index, &handle);
    if (p->mFlags & 0x4000) {
        fn_800B6D34(p, &input);
        if ((input.mUnknown96 & 1) || (input.mUnknown96 & 0x10))
            pBlock->mUnknown29 = 1;
        else
            pBlock->mUnknown29 = 0;
    }
    float time = CatchAnimGetTime(handle);
    if (--pBlock->mUnknown24 >= 0) {
        p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown20) & 0xFFFFFF;
        p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
        unsigned short entry = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, fn_801BE648(p->mpUnknown792), 0);
        if (entry != 0xFFFF) {
            p->mpUnknown800[entry].mUnknownC = (p->mpUnknown800[entry].mUnknownC + pBlock->mUnknown20) & 0xFFFFFF;
        }
    }
    if (!pBlock->mUnknown2) {
        if (!(p->mFlags & 4) && !(pBlock->mUnknown0 <= time - 90.0f) &&
            !(pBlock->mUnknown0 >= time) && p->mUnknown16 != 0 && p->mUnknown16 != 4) {
            *PlyrTrackStartHead(p, PlayerActionCatchGetBallPos, 15, 2) = index;
        }
        pBlock->mUnknown2 = 1;
    } else if ((p->mFlags & 4) || !(pBlock->mUnknown0 <= time)) {
        fn_8009CE88(p, &p->mUnknown16, 8);
    }
    if (!(pBlock->mUnknown0 <= time - 30.0f)) PlyrPoseDelayBlink(p->mpUnknown4);
    Ball_t *pBall = BallGet(index);
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (BallGetHolder(pBall) && p != BallGetHolder(pBall) && !CatchIsInCatchAnim(p) && key != 70) return 1;
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        if (fn_800C4B6C(p)) return 1;
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        if (p->mUnknown9[0] != 8 && p->mUnknown9[0] != 1) {
            Message_800F01CC message;
            memset(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F00D4(0, p->mpState, &message, p);
            CatchResetHeightBoost(p);
            return 1;
        }
        if (fn_801BE648(p->mpUnknown792) == 224) {
            PlayerActionCatchResolve(p, handle, index);
        } else if (fn_801BE648(p->mpUnknown792) == 226) {
            return 1;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            CatchResetHeightBoost(p);
            return 1;
        }
    }
    return 0;
}

extern "C" int PlayerActionCatchExit(Object_80039F5C *p)
{
    Block_800E0E8C *pBlock = (Block_800E0E8C *)&p->mUnknown336;
    if (pBlock->mUnknown2 == 1) {
        fn_8009CE88(p, &p->mUnknown16, 8);
        pBlock->mUnknown2 = 0;
    }
    CatchResetHeightBoost(p);
    p->mFlags &= ~8;
    return 1;
}

extern "C" int PlayerActionIsUserCatch(Object_80039F5C *p)
{
    int result = 0;
    unsigned char id = p->mpState->mId;
    if (id == 28) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown28;
    } else if (id == 5) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown0;
    } else if (id == 12) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown16;
    } else if (id == 94) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown7;
    }
    return result;
}

extern "C" int PlayerActionIsCatchBlocked(Object_80039F5C *p) {
    return 0;
}

extern "C" int PlayerActionSegmentsCross(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC)
{
    float d0 = p->mX * (pC->mY - pB->mY) + pC->mX * (pB->mY - p->mY) + pB->mX * (p->mY - pC->mY);
    float d1 = pB->mX * (p->mY - pA->mY) + p->mX * (pA->mY - pB->mY) + pA->mX * (pB->mY - p->mY);
    float d2 = pA->mX * (pB->mY - pC->mY) + pB->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - pB->mY);
    float d3 = pC->mX * (pA->mY - p->mY) + pA->mX * (p->mY - pC->mY) + p->mX * (pC->mY - pA->mY);
    if ((d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f && d3 >= 0.0f) ||
        (d0 <= 0.0f && d1 <= 0.0f && d2 <= 0.0f && d3 <= 0.0f)) {
        return 1;
    }
    return 0;
}

extern "C" int PlayerActionRunCrossesLine(Object_80039F5C *p, Vector_80039F5C *pTarget)
{
    int result = 0;
    if (CelebrationBlockIsActive(0) && AnmsGetOutlineCount() > 1) {
        Vector_80039F5C end;
        Vector_80039F5C start;
        unsigned short i;
        Vec2Sub(&end, pTarget, &p->mMotion.mPos);
        Vec2Normalize(&end, &end);
        Vec2Scale(&end, &end, p->mMotion.mUnknown28 * CelebrationBlockGetTimeLeft(0));
        Vec2Add(&end, &end, &p->mMotion.mPos);
        end.mZ = 0.0f;
        start = p->mMotion.mPos;
        start.mZ = 0.0f;
        for (i = 0; i < AnmsGetOutlineCount() - 1; i++) {
            if (PlayerActionSegmentsCross(&p->mMotion.mPos, &end, AnmsGetOutlinePoint(i), AnmsGetOutlinePoint(i + 1)) ||
                Vec3DistanceSqrToSegment(&start, &end, AnmsGetOutlinePoint(i)) < 4.0f ||
                Vec3DistanceSqrToSegment(&start, &end, AnmsGetOutlinePoint(i + 1)) < 4.0f) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

extern "C" int PlayerActionIsShallowPath(Object_80039F5C *p)
{
    int result = 0;
    Block_800E11C0 *pBlock = p->mpUnknown3092->mpUnknown32;
    float distance = Vec2Distance(&pBlock->mUnknown32, &pBlock->mUnknown16);
    if (distance > 0.0f) {
        result = MathArcTan(fabsf(pBlock->mUnknown32.mZ - pBlock->mUnknown16.mZ) / distance) <= 0x155555;
    }
    return result;
}

extern "C" int PlayerActionGetInterceptHeading(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    if (p && pOther) {
        result = fn_80120794(&p->mMotion, &pOther->mMotion, &pOther->mMotion.mUnknown40, 0.2f,
                             pOther->mMotion.mUnknown28, pOther->mMotion.mUnknown32,
                             Vec2Distance(&pOther->mMotion, &p->mMotion));
    }
    return result;
}

extern "C" int PlayerActionCanDive(Object_80039F5C *p)
{
    int result = 1;
    switch (p->mpState->mId) {
    case 16:
    case 17:
    case 28:
        result = 0;
        break;
    default:
        if (p->mUnknown1032 == 4 || p->mUnknown1032 == 6 || p->mUnknown1032 == 5) {
            result = 0;
        }
        break;
    }
    if (fn_8011E188() <= 30) {
        result = 0;
    }
    return result;
}

extern "C" int PlayerActionTryDive(Object_80039F5C *p)
{
    int result = 0;
    if (p && PlayerActionCanDive(p)) {
        Message_800F01CC message;
        result = 1;
        memset(&message, 0, 4);
        message.mId = 94;
        fn_800F00D4(0, p->mpState, &message, p);
        fn_800AE7F0(13, p->mIdBytes[2], p);
        fn_800A8954(11, p->mIdBytes[2], p);
    }
    return result;
}

extern "C" int PlayerActionDiveEnter(Object_80039F5C *p)
{
    Block_800E13E4 *pBlock = (Block_800E13E4 *)&p->mUnknown336;
    pBlock->mUnknown4 = 30;
    pBlock->mUnknown5 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown6 = 0;
    p->mUnknown1160.mUnknown52 = 1;
    pBlock->mUnknown0 = p->mUnknown512.mUnknown8;
    pBlock->mUnknown12 = 0;
    if (p->mFlags & 0x4000) {
        pBlock->mUnknown7 = 1;
    } else {
        pBlock->mUnknown7 = 0;
    }
    return 0;
}

extern "C" int PlayerActionDiveUpdate(Object_80039F5C *p)
{
    int result = 0;
    Block_801718E8 *pBlock1160 = &p->mUnknown1160;
    Block_800E1438 *pBlock = (Block_800E1438 *)&p->mUnknown336;
    if (fn_801BE648(p->mpUnknown792) != 70) {
        p->mUnknown1008.mUnknown0 = 2;
        p->mUnknown1008.mUnknown1 = 2;
        p->mUnknown1008.mUnknown2 = 10;
        p->mUnknown1011 = 1;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 70, 1.0f, p);
    }
    if (pBlock->mUnknown8 == 0) {
        pBlock->mUnknown8 = PlayerActionIsShallowPath(p);
    }
    if (pBlock->mUnknown6 == 0) {
        pBlock->mUnknown6 = PlyrTackleContest(p, &pBlock->mUnknown12);
    }
    if (p->mUnknown9[0] != 1 && (p->mFlags & 0x800)) {
        Message_800F01CC message;
        memset(&message, 0, 4);
        message.mId = 11;
        message.mUnknown1[0] = p->mUnknown9[0];
        fn_800F05E4(0, p->mpState, &message, p);
        pBlock1160->mUnknown52 = 0;
        result = 1;
    }
    return result;
}

extern "C" int PlayerActionDiveExit(Object_80039F5C *p)
{
    return ((Block_800E13E4 *)&p->mUnknown336)->mUnknown8 == 0;
}

extern "C" int PlayerActionDiveIsActive(Object_80039F5C *p)
{
    int result = 0;
    if (p && p->mpState->mId == 94) {
        result = ((Block_800E13E4 *)&p->mUnknown336)->mUnknown5 == 0;
    }
    return result;
}

extern "C" int PlayerActionAiConsiderDive(Object_80039F5C *p)
{
    float chance = 0.1f;
    float angle = 10.0f;
    int result = 0;
    Object_80039F5C *pOther = BallGetCurrentHolder();
    if (pOther && MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) <= 0x38E38E && p && !(p->mFlags & 0x4000)) {
        GameSkillAdjustDiveChance(p, &chance, &angle);
        int special = ScrmGetOffenseTeam() == ScrmGetSnapOffense() && !(p->mMotion.mPos.mY >= ScrmGetBallSpot().mY) &&
            (pOther->mpState->mId == 1 || pOther->mpState->mId == 18);
        if (special) {
            if (!(Vec2Distance(&p->mMotion, &pOther->mMotion) >= 3.0f) &&
                MathAngleDiff(PlayerActionGetInterceptHeading(p, pOther), p->mMotion.mUnknown32) < (int)(angle * 46603.37890625f) &&
                !(SyncRandGetFloat(0) >= chance) && PlayerActionTryDive(p)) {
                result = 1;
            }
        } else {
            if (!(p->mMotion.mPos.mY >= pOther->mMotion.mPos.mY) &&
                !(Vec2Distance(&p->mMotion, &pOther->mMotion) >= 3.0f) &&
                MathAngleDiff(PlayerActionGetInterceptHeading(p, pOther), p->mMotion.mUnknown32) < (int)(angle * 46603.37890625f) &&
                !(SyncRandGetFloat(0) >= 0.1f) && PlayerActionTryDive(p)) {
                result = 1;
            }
        }
    }
    return result;
}

extern "C" int PlayerActionRollAlignChange(Object_80039F5C *p)
{
    Block_800E1778 *pBlock = (Block_800E1778 *)&p->mUnknown336;
    unsigned int chance = 0;
    Record_800E1778 *pRecord;
    switch (p->mUnknown2914) {
    case 13:
    case 15:
        chance = 15;
        break;
    case 14:
        chance = 10;
        break;
    }
    PlayBookFormation_t *pObject = PlayBookGetFormation(p->mIdBytes[2]);
    if (pObject->mUnknown8.mUnknownF == 0) {
        pRecord = (Record_800E1778 *)PlayAlignGetRoute(PlayBookGetPlay(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
    } else {
        unsigned char index = PlaySetGetEntry(pObject, p->mIdBytes[1], 0)->mUnknownB;
        pRecord = (Record_800E1778 *)PlayAlignGetRoute(PlayBookGetPlay(p->mIdBytes[2]), p->mIdBytes[2], index);
    }
    if ((pRecord->mUnknown0 & ~0x80) == 85) {
        chance = 0;
    }
    if (chance != 0 && SyncRandGetRange(0, 100) < chance) {
        pBlock->mUnknown24 = 1;
        pBlock->mUnknown30 = 0;
    }
    return 0;
}

extern "C" int PlayerActionIsNearLine(Object_80039F5C *p)
{
    int result = 0;
    int inArea = !(p->mMotion.mPos.mY >= ScrmGetTeamSetupSpot(p->mIdBytes[2]).mY + 2.0f) &&
        !(p->mMotion.mPos.mY <= ScrmGetTeamSetupSpot(p->mIdBytes[2]).mY + 1.0f) &&
        !(fabsf(p->mMotion.mPos.mX) >= 8.0f) && (unsigned int)(p->mUnknown2914 - 4) <= 8;
    if (inArea) {
        result = 1;
    }
    if (fn_801BE648(p->mpUnknown792) == 86) {
        result = 1;
    }
    return result;
}

// FAKEMATCH: stand-in for stripped debug code that named the two linebacker slots; the empty inline
// compiles to nothing but keeps the "LB_L"/"LB_R" literals at 0x8029DA9C/0x8029DAA4 in the pool.
static inline void _PlayerActionDebugSlot(Object_80039F5C *, const char *)
{
}

extern "C" void PlayerActionAlignDefender(Object_80039F5C *p)
{
    FieldPoint_t marked;
    marked.mY = 0.0f;
    marked.mX = 0.0f;
    Record_8011F4E0 *pTactics = fn_8011F4E0();
    FieldPoint_t goal;
    goal = ScrmGetTeamSetupSpot(p->mIdBytes[2]);
    Object_80039F5C *pLeft = 0, *pRight = 0, *pSpecial = 0, *pMarked = 0;
    unsigned int count = ScrmGetTeamPlayerCount(ScrmGetDefenseTeam());
    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(ScrmGetDefenseTeam(), i);
        Block_800E1954 *pOtherBlock = (Block_800E1954 *)&pOther->mUnknown336;
        if (pOther->mUnknown2914 >= 17 && pOther->mUnknown2914 <= 18) {
            if (!(pOther->mMotion.mPos.mX <= goal.mX)) pRight = pOther;
            else pLeft = pOther;
            _PlayerActionDebugSlot(pOther, pOther == pLeft ? "LB_L" : "LB_R");
        }
        if (fn_8009F778(pOther) && fn_8009F6B4() == 1) pSpecial = pOther;
        if (fn_8009F778(pOther) && fn_8009F6B4() == 1 && !pOtherBlock->mpUnknown36) PlayAlignGetSetName(2);
    }
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    PlayBookFormation_t *pTeam = PlayBookGetFormation(ScrmGetDefenseTeam());
    PlayBookPosition_t *pEntry = PlaySetGetEntry(pTeam, p->mIdBytes[1], 0);
    FieldPoint_t own;
    own.mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
    own.mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
    Vec2Add(&own, &own, &goal);
    if (DefCoverIsAlignHeld() && fn_801BE648(p->mpUnknown792) != 86) {
    pBlock->mUnknown49 = 0;
    if (pTactics->mUnknown4) {
        unsigned char slot = pTactics->mUnknown32[p->mIdBytes[1]];
        if (slot <= 3) pMarked = PlyrGet(ScrmGetOffenseTeam(), ((unsigned char *)pTactics)[7 + slot]);
    }
    if (pMarked) {
        {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(ScrmGetOffenseTeam());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked.mX = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mX;
            marked.mY = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mY;
            Vec2Add(&marked, &marked, &goal);
        }
    }
    switch (p->mUnknown2914) {
    case 17: case 18:
        if (pMarked) {
            if (!(own.mX <= goal.mX)) {
                if (!(marked.mX <= own.mX + 4.0f)) {
                    pBlock->mUnknown40.mX = marked.mX - 3.0f;
                    float floor = goal.mY + 3.5f;
                    float y = own.mY - 4.5f;
                    if (!(y >= floor)) y = floor;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                } else {
                    pBlock->mUnknown40.mX = own.mX;
                    float floor = goal.mY + 6.0f;
                    float y = own.mY - 3.0f;
                    if (!(y >= floor)) y = floor;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            } else {
                if (!(marked.mX >= own.mX - 4.0f)) {
                    pBlock->mUnknown40.mX = marked.mX + 3.0f;
                    float floor = goal.mY + 3.5f;
                    float y = own.mY - 4.5f;
                    if (!(y >= floor)) y = floor;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                } else {
                    pBlock->mUnknown40.mX = own.mX;
                    float floor = goal.mY + 6.0f;
                    float y = own.mY - 3.0f;
                    if (!(y >= floor)) y = floor;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            }
        }
        break;
    case 16:
        if (!fn_8009F778(p) && pTactics->mUnknown16[p->mIdBytes[1]] == 255) {
            if (pMarked) {
                if (!(own.mX <= goal.mX)) {
                    if (!(marked.mX >= own.mX - 2.0f)) {
                        pBlock->mUnknown40.mX = own.mX - 3.5f;
                        pBlock->mUnknown49 = 1;
                        pBlock->mUnknown40.mY = own.mY;
                        float y = own.mY + 2.5f;
                        if (y > ScrmGetEndLineY() - 5.0f) y = ScrmGetEndLineY() - 5.0f;
                        pBlock->mUnknown40.mY = y;
                    }
                } else if (!(marked.mX <= own.mX + 2.0f)) {
                    pBlock->mUnknown40.mX = own.mX + 3.5f;
                    pBlock->mUnknown49 = 1;
                    pBlock->mUnknown40.mY = own.mY;
                    float y = own.mY + 2.5f;
                    if (y > ScrmGetEndLineY() - 5.0f) y = ScrmGetEndLineY() - 5.0f;
                    pBlock->mUnknown40.mY = y;
                }
            } else {
                int slot = !(own.mX <= goal.mX) ? 1 : 5;
                pMarked = PlyrGet(ScrmGetOffenseTeam(), ((unsigned char *)pTactics)[7 + slot]);
                {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(ScrmGetOffenseTeam());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked.mX = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mX;
            marked.mY = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mY;
            Vec2Add(&marked, &marked, &goal);
        }
                if ((slot == 1 && marked.mX < goal.mX + 6.0f) || (slot == 5 && !(marked.mX <= goal.mX - 6.0f))) {
                    pBlock->mUnknown40.mX = slot == 1 ? own.mX - 3.5f : own.mX + 3.5f;
                    float y = own.mY + 2.5f;
                    if (y > ScrmGetEndLineY() - 5.0f) y = ScrmGetEndLineY() - 5.0f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            }
        } else if (fn_8009F778(p) && pTactics->mUnknown16[p->mIdBytes[1]] == 255) {
            if (pMarked) {
                if (!(own.mX <= goal.mX)) {
                    if (!(own.mX <= marked.mX + 3.0f)) pBlock->mUnknown40.mX = own.mX - 1.5f;
                } else if (!(own.mX >= marked.mX - 3.0f)) pBlock->mUnknown40.mX = own.mX + 1.5f;
                pBlock->mUnknown40.mY = own.mY;
            } else {
                int slot = !(own.mX <= goal.mX) ? 2 : 4;
                pMarked = PlyrGet(ScrmGetOffenseTeam(), ((unsigned char *)pTactics)[7 + slot]);
                {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(ScrmGetOffenseTeam());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked.mX = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mX;
            marked.mY = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mY;
            Vec2Add(&marked, &marked, &goal);
        }
                if ((slot == 2 && marked.mX < goal.mX + 6.0f) || (slot == 4 && !(marked.mX <= goal.mX - 6.0f))) {
                    pBlock->mUnknown40.mX = slot == 2 ? own.mX - 2.0f : own.mX + 2.0f;
                    pBlock->mUnknown49 = 1;
                    pBlock->mUnknown40.mY = own.mY;
                }
            }
        }
        break;
    case 13: case 15: {
        bool specialRight = pSpecial && pSpecial->mMotion.mPos.mX > p->mMotion.mPos.mX;
        if (pMarked) {
            if (!(p->mMotion.mPos.mX <= goal.mX) && (!pSpecial || !specialRight)) {
                if (!(marked.mX <= own.mX + 3.0f)) {
                    pBlock->mUnknown40.mX = marked.mX - 1.0f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            } else if (!(marked.mX >= own.mX - 3.0f) && (!pSpecial || specialRight)) {
                pBlock->mUnknown40.mX = marked.mX + 1.0f;
                float y = own.mY;
                if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                pBlock->mUnknown40.mY = y;
                pBlock->mUnknown49 = 1;
            }
        } else {
            int slot = !(own.mX <= goal.mX) ? 2 : 4;
            pMarked = PlyrGet(ScrmGetOffenseTeam(), ((unsigned char *)pTactics)[7 + slot]);
            {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(ScrmGetOffenseTeam());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked.mX = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mX;
            marked.mY = (pMarkedTeam->mUnknown8.mUnknownF == 1 ? &pMarkedEntry->mUnknown18 : &pMarkedEntry->mUnknown10)->mY;
            Vec2Add(&marked, &marked, &goal);
        }
            if (!(own.mX <= goal.mX) && !(marked.mX <= own.mX + 3.0f)) {
                if (pRight && !pRight->mUnknown361[24] && (!pSpecial || !specialRight)) {
                    pBlock->mUnknown40.mX = marked.mX - 1.0f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            } else if (!(own.mX >= goal.mX) && !(marked.mX >= own.mX - 3.0f)) {
                if (pLeft && !pLeft->mUnknown361[24] && (!pSpecial || specialRight)) {
                    pBlock->mUnknown40.mX = marked.mX + 1.0f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            }
        }
        break;
    }
    default: pBlock->mUnknown49 = 0;
    }
    if (!pBlock->mUnknown0) {
        FieldPoint_t delta;
        if (pBlock->mUnknown49) Vec2Sub(&delta, &pBlock->mUnknown40, &p->mMotion);
        else Vec2Sub(&delta, &own, &p->mMotion);
        if (!(Vec2Magnitude(&delta) <= 1.0f) && !pBlock->mUnknown24) pBlock->mUnknown1 = 1;
    }
    } else if (pBlock->mUnknown49 && !pBlock->mUnknown0) {
        pBlock->mUnknown49 = 0;
        pBlock->mUnknown1 = 1;
    }
}

extern "C" void PlayerActionGetAlignSpot(Object_80039F5C *p, FieldPoint_t *pOut, int *pAngle)
{
    FieldPoint_t point;
    point = ScrmGetTeamSetupSpot(p->mIdBytes[2]);
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    PlayBookFormation_t *pTeam = PlayBookGetFormation(ScrmGetDefenseTeam());
    PlayBookPosition_t *pEntry = PlaySetGetEntry(pTeam, p->mIdBytes[1], 0);
    pOut->mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
    pOut->mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
    Vec2Add(pOut, pOut, &point);
    pOut->mX = !(pOut->mX >= 1.0f - ScrmGetSidelineX()) ? 1.0f - ScrmGetSidelineX()
        : (pOut->mX > ScrmGetSidelineX() - 1.0f ? ScrmGetSidelineX() - 1.0f : pOut->mX);
    pOut->mY = !(pOut->mY >= 1.0f - ScrmGetEndLineY()) ? 1.0f - ScrmGetEndLineY()
        : (pOut->mY > ScrmGetEndLineY() - 1.0f ? ScrmGetEndLineY() - 1.0f : pOut->mY);
    if (pBlock->mpUnknown36) {
        fn_8011F4E0();
        Object_80039F5C *pOther = pBlock->mpUnknown36;
        if (pOther) {
            FieldPoint_t delta;
            Vec2Sub(&delta, &p->mMotion, &pOther->mMotion);
            MathArcTan2(delta.mY, delta.mX);
            switch (p->mUnknown2914) {
            case 17:
            case 18:
                if (pTeam->mUnknown8.mUnknown4 == 11) {
                    pBlock->mUnknown78 = 1;
                } else {
                    pBlock->mUnknown78 = 0;
                }
                break;
            default:
                if (fn_8009FE24(p)) {
                    pBlock->mUnknown78 = 0;
                } else {
                    pBlock->mUnknown78 = 1;
                }
                break;
            }
            int ref = fn_800B0F98();
            if (fn_800B146C() && fn_8009BCE8(&ref) == pBlock->mpUnknown36) pBlock->mUnknown78 = 1;
            if (pBlock->mUnknown78) {
                pOut->mX = pOther->mMotion.mUnknown40 * 10.0f + pOther->mMotion.mPos.mX;
                if (!(pOut->mX <= p->mMotion.mPos.mX)) {
                    if (!(pOut->mX >= 4.0f)) pOut->mY += 1.5f;
                } else {
                    if (!(pOut->mX <= -4.0f)) pOut->mY += 1.5f;
                }
            } else {
                fn_800FE03C(p, pOut);
            }
        }
    } else if (pBlock->mUnknown49 && DefCoverIsAlignHeld() && ScrmOffenseAnyPlaced()) {
        pOut->mX = pBlock->mUnknown40.mX;
        pOut->mY = pBlock->mUnknown40.mY;
    } else {
        PlyrAlignGetCallTarget(p, pOut);
    }
    *pAngle = pEntry->mUnknown20;
}

extern "C" int PlayerActionFindGap(Object_80039F5C *p, int count, float *pValues, float *pOut, float direction, float target)
{
    int result = 0;
    if (direction == -1.0f) {
        int i = 0;
        if (i < count && !(pValues[i] > p->mMotion.mPos.mX)) {
            do { ++i; } while (i < count && pValues[i] <= p->mMotion.mPos.mX);
        }
        if (i != count) {
        if (i) {
            while (!result && i > 0) {
                --i;
                float left = pValues[i];
                float right = pValues[i + 1];
                if (!((left + right) * 0.5f >= target)) {
                    float upper = right - 0.7f;
                    if (!(upper <= target)) upper = target;
                    if (!(upper <= p->mMotion.mPos.mX + 1.2f)) upper = p->mMotion.mPos.mX + 1.2f;
                    float lower = left + 0.7f;
                    if (!(lower >= p->mMotion.mPos.mX - 1.2f)) lower = p->mMotion.mPos.mX - 1.2f;
                    if (!(upper <= lower)) {
                        result = 1;
                        *pOut = (upper + lower) * 0.5f;
                    }
                }
            }
        } else {
            *pOut = pValues[0] - 0.7f;
            return 1;
        }
        }
    } else {
        int i = count - 1;
        if (i >= 0) {
        if (!(pValues[i] < p->mMotion.mPos.mX)) {
            do { --i; } while (i >= 0 && pValues[i] >= p->mMotion.mPos.mX);
        }
        if (i >= 0) {
        if (i != count - 1) {
        while (!result && i < count - 1) {
            ++i;
            float right = pValues[i];
            float left = pValues[i - 1];
            if (!((right + left) * 0.5f <= target)) {
                float upper = right - 0.7f;
                if (!(upper <= p->mMotion.mPos.mX + 1.2f)) upper = p->mMotion.mPos.mX + 1.2f;
                float lower = left + 0.7f;
                if (!(lower >= p->mMotion.mPos.mX - 1.2f)) lower = p->mMotion.mPos.mX - 1.2f;
                if (!(lower >= target)) lower = target;
                if (!(upper <= lower)) {
                    result = 1;
                    *pOut = (upper + lower) * 0.5f;
                }
            }
        }
        } else {
            *pOut = pValues[i] + 0.7f;
            return 1;
        }
        }
        }
    }
    return result;
}

extern "C" void PlayerActionPickLaneTarget(Object_80039F5C *p)
{
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    FieldPoint_t point;
    point = ScrmGetTeamSetupSpot(p->mIdBytes[2]);
    float random = SyncRandGetFloat(0);
    FieldPoint_t target;
    target.mY = point.mY + 1.4f + random;
    if (!(target.mY <= p->mMotion.mPos.mY)) {
        target.mY = ScrmGetTeamSetupSpot(p->mIdBytes[2]).mY + 1.0f;
        if (!(target.mY <= p->mMotion.mPos.mY)) target.mY = p->mMotion.mPos.mY;
    }
    Record_800E2ABC *pRecord = (Record_800E2ABC *)PlayAlignGetRoute(PlayBookGetPlay(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
    if ((pRecord->mUnknown4 & ~0x80) == 30) {
        FieldPoint_t velocity;
        float value = (float)(pRecord->mUnknown5 >> 3) + (float)(pRecord->mUnknown5 & 7) * 0.1428571492433548f;
        Vec2FromAngle(&velocity, (pRecord->mUnknown6 & 0x7F) << 17, value);
        target.mX = (target.mY - p->mMotion.mPos.mY) * velocity.mX;
        target.mX /= velocity.mY;
        target.mX = (point.mX - p->mMotion.mPos.mX) * 0.0833333358168602f + target.mX;
    } else {
        float x = (point.mX - p->mMotion.mPos.mX) * 0.75f;
        float y = point.mY - 6.0f;
        y -= p->mMotion.mPos.mY;
        target.mX = (target.mY - p->mMotion.mPos.mY) * x / y;
    }
    target.mX += p->mMotion.mPos.mX;
    PlyrAlignAvoidTeammates(p, &target);
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown4.mX = target.mX;
    pBlock->mUnknown4.mY = target.mY;
    if (!PlayerPathIsLaneClear(p, &pBlock->mUnknown4)) {
        float values[7];
        int count = 0;
        int players = ScrmGetTeamPlayerCount(p->mIdBytes[2]);
        int i;
        for (i = 0; i < players; ++i) {
            Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);
            if (pOther != p && !(pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY)) {
                values[count++] = pOther->mMotion.mPos.mX;
            }
        }
        if (count) {
            float value;
            int changed;
            do {
                changed = 0;
                for (i = 0; i < count - 1; ++i) {
                    if (!(values[i + 1] >= values[i])) {
                        value = values[i + 1];
                        values[i + 1] = values[i];
                        values[i] = value;
                        changed = 1;
                    }
                }
            } while (changed == 1);
            FieldPoint_t *pGoal = &pBlock->mUnknown4;
            FieldPoint_t goal = ScrmGetTeamSetupSpot(p->mIdBytes[2]);
            float direction = !(pBlock->mUnknown4.mX <= goal.mX) ? -1.0f : 1.0f;
            int next = 0;
            pBlock->mGoalFound[0] = 0;
            pBlock->mGoalFound[1] = 0;
            pBlock->mUnknown12.mY = pBlock->mUnknown4.mY;
            if (PlayerActionFindGap(p, count, values, &value, direction, target.mX) == 1) {
                pGoal->mX = value;
                pBlock->mGoalFound[0] = 1;
                next = 1;
            }
            if (PlayerActionFindGap(p, count, values, &value, -direction, target.mX) == 1) {
                pGoal[next].mX = value;
                pBlock->mGoalFound[next] = 1;
            }
        } else {
            pBlock->mGoalFound[0] = 1;
        }
    } else {
        pBlock->mGoalFound[0] = 1;
    }
    if (!pBlock->mGoalFound[0]) {
        pBlock->mUnknown24 = 0;
    } else if (pBlock->mGoalFound[0] == 1 && pBlock->mGoalFound[1] == 1) {
        int angle = (pRecord->mUnknown6 & 0x7F) << 17;
        if (PlayBookGetTeam(ScrmGetDefenseTeam())->mUnknown48) angle = (0x800000 - angle) & 0xFFFFFF;
        if (angle <= 0xBFFFFF) {
            pBlock->mUnknown20 = pBlock->mUnknown4.mX >= pBlock->mUnknown12.mX;
        } else {
            pBlock->mUnknown20 = pBlock->mUnknown4.mX < pBlock->mUnknown12.mX;
        }
    }
}

extern "C" int PlayerActionIsFacingPoint(Object_80039F5C *p, FieldPoint_t *pPoint)
{
    int result = 0;
    if (fn_801BE648(p->mpUnknown792) == 86) {
        FieldPoint_t delta;
        delta.mX = pPoint->mX;
        delta.mY = pPoint->mY;
        if (!(fabsf(delta.mY - p->mMotion.mPos.mY) >= 1.0f)) {
            delta.mY = p->mMotion.mPos.mY;
            Vec2Sub(&delta, &delta, &p->mMotion.mPos);
            unsigned int diff = MathAngleDiff(p->mMotion.mFacing, delta.Heading()) - 0x271C72;
            result = diff <= 0x31C71B;
        }
    }
    return result;
}
