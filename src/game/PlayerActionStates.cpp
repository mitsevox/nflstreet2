/* Player action states: the handlers of player states in the player state-handler table (attached
   model animation, ball release and pickup, a fixed-animation state) and the alignment and
   pursuit helpers that they and the play code call. */
#include "game/PlayerAction.h"

extern "C" int fn_800DF6EC(Object_80039F5C *p)
{
    int result = 0;
    if (p->mFlags & 0x1000) {
        p->mFlags &= ~0x1000;
        result = 1;
    }
    return result;
}

extern "C" void fn_800DF710(Object_80039F5C *p, int joint, Vector_80039F5C *pPos, QuatEulerAngles_t *pAngles)
{
    float rot[4];
    fn_8009BFD0(p, pPos, rot);
    QuatToEuler(pAngles, rot);
}

extern "C" void fn_800DF750(Ball_t *pBall, Vector_80039F5C *pPos, int *pAngles)
{
    Vector_80039F5C old;
    Vector_80039F5C delta;
    BallGetPosition(pBall, &old);
    fn_802276B4(&delta, pPos, &old);
    BallSetPrevPosition(pBall, &old);
    BallSetPosition(pBall, pPos);
    BallSetRotation(pBall, pAngles);
    BallSetVelocity(pBall, &delta);
}

extern "C" void fn_800DF7CC(Object_80039F5C *p, Character_80093BCC *pCharacter, Attachment_800DF7CC *pAttachments, Frame_800DF7CC *pFrame, int index, unsigned int frame)
{
    float time = (float)frame / AnimSequencerGetTicksPerSecond(p);
    Character_800DF7CC *pView = (Character_800DF7CC *)pCharacter;
    fn_80093BAC(pView->mUnknown0, pView->mUnknown4);
    Vector_80039F5C position;
    QuatEulerAngles_t angles;
    if (pFrame->mUnknown20 && pFrame->mUnknown20 != 0x4E4F4E45) {
        if (AnimSeqncrGetKeyValue(pFrame, time) && !fn_800DF6EC(p)) {
            int joint = !pFrame->mUnknown19 || (pView->mFlags & 8) ? 25 : 19;
            fn_800DF710(p, joint, &position, &angles);
            pAttachments[index].mPos = position;
            pAttachments[index].mAngles = angles;
            pAttachments[index].mFrame = frame;
        } else {
            *(int *)(p->mpUnknown4->mUnknown24 + 8) = 0;
            if (pAttachments[index].mFrame != -1) {
                pAttachments[index].mFrame = -1;
                if (pFrame->mUnknown20 == 0x42414C4C) {
                    if (BallsExist()) {
                        Ball_t *pBall = pView->mpBall[index];
                        if (pBall) BallRelease(pBall, 3, 0);
                    } else {
                        pView->mpUnknown20->mUnknown12 &= ~0x40000;
                    }
                }
            }
        }
        if (pFrame->mUnknown20 == 0x42414C4C && BallsExist()) {
            Ball_t *pBall = pView->mpBall[index];
            if (BallStateGet(pBall, 0) == 8) fn_800DF750(pBall, &position, (int *)&angles);
        }
    }
}

extern "C" void fn_800DF9FC(Object_80039F5C *p, void *pRecord, unsigned int value) {
}

extern "C" int fn_800DFA00(Object_80039F5C *p, float *pValue)
{
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    Character_80093BCC *pCharacter = fn_80093BCC(pBlock->mUnknown8);
    if (!pCharacter) return 1;
    Character_800DF7CC *pView = (Character_800DF7CC *)pCharacter;
    Frame_800DF7CC *pFrame = AnimSeqncrGetPlayerPtr(fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4), pBlock->mUnknown9);
    p->mpUnknown4->mUnknown20 |= 0x1000;
    unsigned int handle = fn_801BBE5C(pFrame->mUnknown42 | 0x4000, pFrame->mUnknown14);
    void *pData = fn_801BC084(handle);
    if (!pData) return 1;
    float value;
    pBlock->mUnknown13 = AnimSeqHasOpcode(&value, AnimFileGetAnimation(pData, 0), 0x8003) || AnimSeqHasOpcode(&value, AnimFileGetAnimation(pData, 0), 0x8001);
    *pValue = AnimSeqGetLife(AnimFileGetAnimation(pData, 0));
    fn_8009BD60(p);
    p->mUnknown1008.mUnknown0 = ((unsigned char *)pCharacter)[3];
    p->mUnknown1008.mUnknown1 = ((unsigned char *)pCharacter)[7];
    p->mUnknown1008.mUnknown2 = pBlock->mUnknown9;
    p->mUnknown1011 = pBlock->mUnknown10;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 10, 1.0f, p);
    if ((pView->mFlags & 32) || p->mIdBytes[3] == 3) fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
    if (pView->mFlags & 8) {
        unsigned char count = fn_801BA568(p->mpUnknown796, p->mpUnknown800, 10);
        for (unsigned char i = 0; i < count; i++) {
            Record_800D81C8 *pEntry = &p->mpUnknown800[fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 10, i)];
            fn_801BA6BC(pEntry, !fn_801BA6B0(pEntry));
        }
        fn_800D7A0C(p, p->mUnknown776 == 2 ? 1 : 2);
    }
    if ((pView->mFlags & 16) && fn_801BA568(p->mpUnknown796, p->mpUnknown800, 10)) {
        p->mpUnknown800[fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 10, 0)].mUnknown2C = 1.0f / p->mUnknown768;
    }
    if (handle != 0xFFFFFF) {
        unsigned int other = fn_801BBEC0(handle, 1024);
        if (other != 0xFFFFFF) {
            fn_8009BD60(p);
            unsigned int key = fn_801BBCC8(0, other);
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

extern "C" void fn_800DFCEC(Object_80039F5C *p)
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
    fn_800DFA00(p, &pBlock->mUnknown4);
}

extern "C" int fn_800DFD90(Object_80039F5C *p)
{
    Character_80093BCC *pCharacter = fn_80093BCC(p->mUnknown344);
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    fn_8003E174(1);
    p->mpUnknown4->mUnknown20 &= ~0x80;
    if (!FELoopIsMainFEActive() && fn_800AD9B4() == 7) {
        return 0;
    }
    if (!(pActor->mUnknown8 & 0x40)) {
        if (p->mIdBytes[3] == 3) {
            fn_8009BD60(p);
            p->mUnknown1008.mUnknown0 = 1;
            p->mUnknown1008Word = 6;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 82, 1.0f, p);
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
        } else if (p->mIdBytes[3] == 1) {
            int mode = fn_800AD9B4();
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            if (mode == 4) {
                fn_8010A2DC(p, 0, -1);
            }
        }
    }
    return 1;
}

extern "C" int fn_800DFED0(Object_80039F5C *p)
{
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    Character_80093BCC *pCharacter = fn_80093BCC(pBlock->mUnknown8);
    Attachment_800DF7CC *pAttachments = fn_80093C08(pBlock->mUnknown8);
    if (!pCharacter || !pAttachments) {
        fn_800ADBC0(p, 1, 8, 0);
        fn_800ADBC0(p, 1, 8, 1);
        return 1;
    }
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    Frame_800DF7CC *pFrame = AnimSeqncrGetPlayerPtr(pActor, pBlock->mUnknown9);
    fn_800DF9FC(p, pCharacter, (unsigned int)pBlock->mUnknown0);
    fn_800DF7CC(p, pCharacter, pAttachments, pFrame, pBlock->mUnknown9, (unsigned int)pBlock->mUnknown0);
    if (fn_800943B0(pBlock->mUnknown8)) return 0;
    pBlock->mUnknown0 += gFrameTimeScale;
    if (!(pBlock->mUnknown0 <= pBlock->mUnknown4) && !pBlock->mUnknown13) {
        fn_8009134C(pBlock->mUnknown8);
        p->mpUnknown4->mUnknown20 &= ~0x1000;
        p->mpUnknown4->mUnknown20 &= ~0x80;
        if (!(pActor->mUnknown8 & 64)) {
            if (p->mIdBytes[3] == 3) {
                fn_8009BD60(p);
                p->mUnknown1008.mUnknown0 = 1;
                p->mUnknown1008Word = 6;
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 82, 1.0f, p);
                fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            } else if (p->mIdBytes[3] == 1) {
                int mode = fn_800AD9B4();
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
                fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
                if (mode == 4) fn_8016DBE4(p);
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
                p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            }
        }
        fn_800ADBC0(p, 1, 8, 0);
        fn_800ADBC0(p, 1, 8, 1);
        return 1;
    }
    return 0;
}

extern "C" int fn_800E0188(Object_80039F5C *p, float *pA, float *pB)
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

extern "C" void fn_800E01D8(Object_80039F5C *p, Block_800E0230 *pBlock, int a)
{
    if (p == BallGetCurrentHolder() && fn_801BE648(p->mpUnknown792) == 74 && fn_801486A0()) {
        PossReleaseBall(p);
    }
}

extern "C" void fn_800E0230(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (fn_802372EC(0, 100) <= 64) {
        pBlock->mUnknown9 = 0;
        if (p->mUnknown776 == 2) {
            fn_800E01D8(p, pBlock, 6);
        } else {
            fn_800E01D8(p, pBlock, 3);
        }
    } else {
        pBlock->mUnknown9 = 1;
        if (p->mUnknown776 == 2) {
            fn_800E01D8(p, pBlock, 6);
        } else {
            fn_800E01D8(p, pBlock, 3);
        }
    }
}

extern "C" float fn_800E02D0(Object_80039F5C *p)
{
    float value;
    if (fn_80124C28(p, &value, 0x355555, 5.0f, 0.5f, p->mMotion.mFacing)) {
        return (1.0f - value * 0.2f) * 0.5f + 0.5f;
    }
    return 0.5f;
}

extern "C" void fn_800E034C(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.2f || (unsigned char)fn_800B9A90(lbl_803EAB84) != 1) {
        pBlock->mUnknown8 = 0;
        pBlock->mUnknown0 = fn_800E02D0(p);
        pBlock->mUnknown4 = p->mMotion.mFacing;
        float y = fabsf(p->mMotion.mPos.mY);
        if (!(y <= fn_80178A2C())) {
            pBlock->mUnknown4 = MathAngleDiff(p->mMotion.mFacing, 0) > 0x400000 ? 0x800000 : 0;
        }
        p->mUnknown512.mUnknown14 = 10;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown0;
    } else {
        fn_800E0230(p, pBlock);
    }
}

extern "C" void fn_800E0438(Object_80039F5C *p, Block_800E0230 *pBlock)
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
            fn_8013AD04(pBall, &velocity, 3, 0.0f, 1.0f);
            break;
        }
        }
    }
}

extern "C" void fn_800E04C8(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (!(p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed > 0.2f) && (unsigned char)fn_800B9A90(lbl_803EAB84) == 1) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = 0.2f;
        fn_800E0230(p, pBlock);
    } else {
        p->mUnknown512.mUnknown14 = 10;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown0;
    }
}

extern "C" int fn_800E0574(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (BallFindHeldBy(p) == 0) {
        return 1;
    }
    fn_800E034C(p, pBlock);
    return 0;
}

extern "C" int fn_800E05C0(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (BallFindHeldBy(p) == 0) {
        return 1;
    }
    unsigned char state = pBlock->mUnknown8;
    switch (state) {
    case 0:
        fn_800E04C8(p, pBlock);
        break;
    case 1:
        if (p->mFlags & 0x1000) {
            p->mFlags &= ~0x1000;
            fn_800E0438(p, pBlock);
        }
        if (p->mFlags & 4) {
            fn_800E0438(p, pBlock);
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

extern "C" int fn_800E068C(Object_80039F5C *p) {
    return 0;
}

extern "C" void fn_800E0694(Object_80039F5C *p, int handle, int index)
{
    if (p->mRatings[0] < lbl_803EAD34) {
        unsigned int threshold = p->mRatings[0] * lbl_803EAD2C;
        if ((unsigned int)fn_802372EC(0, lbl_803EAD28) > threshold) {
            p->mUnknown1008.mUnknown0 = fn_8009A63C(handle)->mUnknown4;
            p->mUnknown1008.mUnknown1 = !(fn_80237260(0) >= lbl_803EAD30) ? 1 : 2;
            p->mUnknown1008.mUnknown2 = handle < 0 ? 2 : 1;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 226, 1.0f, p);
            return;
        }
    }
    fn_80099F04(p, handle, index);
    p->mUnknown1160.mUnknown53 = 1;
    fn_800A2190(1);
    AudmonEventPostId(49, &p->mMotion.mPos, p->mId, 0, 0, 0);
    AudmonEventPostId(54, &p->mMotion.mPos, p->mId, 0, 0, 0);
}

extern "C" void fn_800E0818(int a, Vector_80039F5C *pOut, unsigned char *pIndex)
{
    BallGetPosition(BallGet(*pIndex), pOut);
}

extern "C" int fn_800E0850(Object_80039F5C *p)
{
    Block_800E0850 *pBlock = (Block_800E0850 *)&p->mUnknown336;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown2 = 0;
    unsigned char index;
    int handle;
    fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &index, &handle);
    float time = fn_8009A270(handle);
    if (fn_801BE648(p->mpUnknown792) == 224) {
        unsigned char entry = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 224, 0);
        time += AnimSeqGetLife(p->mpUnknown800[entry].mUnknown4C.mpUnknown0);
    }
    Ball_t *pBall = BallGet(index);
    BallGetPosition(pBall, &pBlock->mUnknown4);
    Vector_80039F5C velocity;
    BallGetVelocity(pBall, &velocity);
    float drop = time * 0.002981481608003378f;
    drop = time * drop;
    drop *= 0.5f;
    float z = velocity.mZ * time - drop;
    pBlock->mUnknown4.mX = velocity.mX * time + pBlock->mUnknown4.mX;
    pBlock->mUnknown4.mZ += z;
    pBlock->mUnknown4.mY = velocity.mY * time + pBlock->mUnknown4.mY;
    pBlock->mUnknown16 = (unsigned int)time;
    pBlock->mUnknown24 = (int)(time * 0.8f);
    pBlock->mUnknown20 = (int)(p->mpState->mUnknown3[0] << 16);
    if (pBlock->mUnknown20 > 0x800000) pBlock->mUnknown20 -= 0x1000000;
    if (pBlock->mUnknown24) pBlock->mUnknown20 /= pBlock->mUnknown24;
    if (fn_8009A578(handle) == 5) {
        Vector_80039F5C pos = p->mMotion.mPos;
        pos.mZ = (float)p->mMotion.mUnknown32;
    }
    pBlock->mUnknown28 = (p->mFlags & 0x4000) != 0;
    fn_800A3B58(p, 4, 0);
    if (fn_801BE648(p->mpUnknown792) == 227) {
        p->mUnknown1160.mUnknown54 = 1;
        PlayerMoveBegin(p, 1, 28);
    }
    if (fn_801BE648(p->mpUnknown792) == 224 || fn_801BE648(p->mpUnknown792) == 225) {
        p->mFlags |= 8;
    }
    return 0;
}

extern "C" int fn_800E0AD8(Object_80039F5C *p)
{
    Block_800E0850 *pBlock = (Block_800E0850 *)&p->mUnknown336;
    ++pBlock->mUnknown0;
    fn_800B8344(p);
    if (!fn_8009A68C(p)) return 1;
    unsigned char index;
    int handle;
    fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &index, &handle);
    if (p->mFlags & 0x4000) {
        Input_800B6D34 input;
        fn_800B6D34(p, &input);
        pBlock->mUnknown29 = (input.mUnknown96 & 0x11) != 0;
    }
    float time = fn_8009A270(handle);
    if (--pBlock->mUnknown24 >= 0) {
        p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown20) & 0xFFFFFF;
        p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
        unsigned short entry = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, fn_801BE648(p->mpUnknown792), 0);
        if (entry != 0xFFFF) {
            p->mpUnknown800[entry].mUnknownC = (p->mpUnknown800[entry].mUnknownC + pBlock->mUnknown20) & 0xFFFFFF;
        }
    }
    if (!pBlock->mUnknown2) {
        if (!(p->mFlags & 4) && !((float)pBlock->mUnknown0 <= time - 90.0f) &&
            !((float)pBlock->mUnknown0 >= time) && p->mUnknown16 != 0 && p->mUnknown16 != 4) {
            *fn_8009CC2C(p, fn_800E0818, 15, 2) = index;
        }
        pBlock->mUnknown2 = 1;
    } else if ((p->mFlags & 4) || !((float)pBlock->mUnknown0 <= time)) {
        fn_8009CE88(p, &p->mUnknown16, 8);
    }
    if (!((float)pBlock->mUnknown0 <= time - 30.0f)) PlyrPoseDelayBlink(p->mpUnknown4);
    Ball_t *pBall = BallGet(index);
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (BallGetHolder(pBall) && BallGetHolder(pBall) != p && !fn_8009A68C(p) && key != 70) return 1;
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        if (fn_800C4B6C(p)) return 1;
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        if (p->mUnknown9[0] != 8 && p->mUnknown9[0] != 1) {
            Message_800F01CC message;
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F00D4(0, p->mpState, &message, p);
            fn_8009A260(p);
            return 1;
        }
        if (fn_801BE648(p->mpUnknown792) == 224) {
            fn_800E0694(p, handle, index);
        } else if (fn_801BE648(p->mpUnknown792) == 226) {
            return 1;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            fn_8009A260(p);
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_800E0E8C(Object_80039F5C *p)
{
    Block_800E0E8C *pBlock = (Block_800E0E8C *)&p->mUnknown336;
    if (pBlock->mUnknown2 == 1) {
        fn_8009CE88(p, &p->mUnknown16, 8);
        pBlock->mUnknown2 = 0;
    }
    fn_8009A260(p);
    p->mFlags &= ~8;
    return 1;
}

extern "C" int fn_800E0EF0(Object_80039F5C *p)
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

extern "C" int fn_800E0F40(Object_80039F5C *p) {
    return 0;
}

extern "C" int fn_800E0F48(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC)
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

extern "C" int fn_800E1044(Object_80039F5C *p, Vector_80039F5C *pTarget)
{
    int result = 0;
    if (fn_8009B9A8(0) && fn_80094488() > 1) {
        Vector_80039F5C end;
        Vector_80039F5C start;
        unsigned short i;
        fn_80227690(&end, pTarget, &p->mMotion.mPos);
        fn_802271A4(&end, &end);
        fn_80227248(&end, &end, p->mMotion.mUnknown28 * fn_8009BB54(0));
        fn_80227638(&end, &end, &p->mMotion.mPos);
        end.mZ = 0.0f;
        start = p->mMotion.mPos;
        start.mZ = 0.0f;
        for (i = 0; i < fn_80094488() - 1; i++) {
            if (fn_800E0F48(&p->mMotion.mPos, &end, fn_80094490(i), fn_80094490(i + 1)) ||
                fn_80227B04(&start, &end, fn_80094490(i)) < 4.0f ||
                fn_80227B04(&start, &end, fn_80094490(i + 1)) < 4.0f) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

extern "C" int fn_800E11C0(Object_80039F5C *p)
{
    int result = 0;
    Block_800E11C0 *pBlock = p->mpUnknown3092->mpUnknown32;
    float distance = fn_8022781C(&pBlock->mUnknown32, &pBlock->mUnknown16);
    if (distance > 0.0f) {
        result = fn_801CFE08(fabsf(pBlock->mUnknown32.mZ - pBlock->mUnknown16.mZ) / distance) <= 0x155555;
    }
    return result;
}

extern "C" int fn_800E1248(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    if (p && pOther) {
        result = fn_80120794(&p->mMotion, &pOther->mMotion, &pOther->mMotion.mUnknown40, 0.2f,
                             pOther->mMotion.mUnknown28, pOther->mMotion.mUnknown32,
                             fn_8022781C(&pOther->mMotion, &p->mMotion));
    }
    return result;
}

extern "C" int fn_800E12D4(Object_80039F5C *p)
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

extern "C" int fn_800E1350(Object_80039F5C *p)
{
    int result = 0;
    if (p && fn_800E12D4(p)) {
        Message_800F01CC message;
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 94;
        fn_800F00D4(0, p->mpState, &message, p);
        fn_800AE7F0(13, p->mIdBytes[2], p);
        fn_800A8954(11, p->mIdBytes[2], p);
    }
    return result;
}

extern "C" int fn_800E13E4(Object_80039F5C *p)
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

extern "C" int fn_800E1438(Object_80039F5C *p)
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
        pBlock->mUnknown8 = fn_800E11C0(p);
    }
    if (pBlock->mUnknown6 == 0) {
        pBlock->mUnknown6 = fn_800E8898(p, &pBlock->mUnknown12);
    }
    if (p->mUnknown9[0] != 1 && (p->mFlags & 0x800)) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 11;
        message.mUnknown1[0] = p->mUnknown9[0];
        fn_800F05E4(0, p->mpState, &message, p);
        pBlock1160->mUnknown52 = 0;
        result = 1;
    }
    return result;
}

extern "C" int fn_800E1544(Object_80039F5C *p)
{
    return ((Block_800E13E4 *)&p->mUnknown336)->mUnknown8 == 0;
}

extern "C" int fn_800E1554(Object_80039F5C *p)
{
    int result = 0;
    if (p && p->mpState->mId == 94) {
        result = ((Block_800E13E4 *)&p->mUnknown336)->mUnknown5 == 0;
    }
    return result;
}

extern "C" int fn_800E1584(Object_80039F5C *p)
{
    float chance = 0.1f;
    float angle = 10.0f;
    int result = 0;
    Object_80039F5C *pOther = BallGetCurrentHolder();
    if (pOther && MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) <= 0x38E38E && p && !(p->mFlags & 0x4000)) {
        int special = 0;
        fn_800ACDE4(p, &chance, &angle);
        if (fn_80178308() == fn_80178348() && !(p->mMotion.mPos.mY >= fn_80177FE0().mY) &&
            (pOther->mpState->mId == 1 || pOther->mpState->mId == 18)) {
            special = 1;
        }
        if (special) {
            if (!(fn_8022781C(&p->mMotion, &pOther->mMotion) >= 3.0f) &&
                MathAngleDiff(fn_800E1248(p, pOther), p->mMotion.mUnknown32) < (int)(angle * 46603.37890625f) &&
                !(fn_80237260(0) >= chance) && fn_800E1350(p)) {
                result = 1;
            }
        } else {
            if (!(p->mMotion.mPos.mY >= pOther->mMotion.mPos.mY) &&
                !(fn_8022781C(&p->mMotion, &pOther->mMotion) >= 3.0f) &&
                MathAngleDiff(fn_800E1248(p, pOther), p->mMotion.mUnknown32) < (int)(angle * 46603.37890625f) &&
                !(fn_80237260(0) >= 0.1f) && fn_800E1350(p)) {
                result = 1;
            }
        }
    }
    return result;
}

extern "C" int fn_800E1778(Object_80039F5C *p)
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
        pRecord = (Record_800E1778 *)fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
    } else {
        unsigned char index = PlaySetGetEntry(pObject, p->mIdBytes[1], 0)->mUnknownB;
        pRecord = (Record_800E1778 *)fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]), p->mIdBytes[2], index);
    }
    if ((pRecord->mUnknown0 & ~0x80) == 85) {
        chance = 0;
    }
    if (chance != 0 && fn_802372EC(0, 100) < chance) {
        pBlock->mUnknown24 = 1;
        pBlock->mUnknown30 = 0;
    }
    return 0;
}

extern "C" int fn_800E1870(Object_80039F5C *p)
{
    int result = 0;
    int inArea = 0;
    if (!(p->mMotion.mPos.mY >= fn_80177FFC(p->mIdBytes[2]).mY + 2.0f) &&
        !(p->mMotion.mPos.mY <= fn_80177FFC(p->mIdBytes[2]).mY + 1.0f) &&
        !(fabsf(p->mMotion.mPos.mX) >= 8.0f)) {
        inArea = (unsigned int)(p->mUnknown2914 - 4) <= 8;
    }
    if (inArea) {
        result = 1;
    }
    if (fn_801BE648(p->mpUnknown792) == 86) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800E1954(Object_80039F5C *p)
{
    Point_8017886C marked = {0.0f, 0.0f};
    Record_8011F4E0 *pTactics = fn_8011F4E0();
    Point_8017886C goal = fn_80177FFC(p->mIdBytes[2]);
    Object_80039F5C *pLeft = 0, *pRight = 0, *pSpecial = 0, *pMarked = 0;
    unsigned int count = fn_80178D18(fn_80178320());
    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(fn_80178320(), i);
        Block_800E1954 *pOtherBlock = (Block_800E1954 *)&pOther->mUnknown336;
        if (pOther->mUnknown2914 >= 17 && pOther->mUnknown2914 <= 18) {
            if (!(pOther->mMotion.mPos.mX <= goal.mX)) pRight = pOther;
            else pLeft = pOther;
        }
        if (fn_8009F778(pOther) && fn_8009F6B4() == 1) pSpecial = pOther;
        if (fn_8009F778(pOther) && fn_8009F6B4() == 1 && !pOtherBlock->mpUnknown36) PlayAlignGetSetName(2);
    }
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    PlayBookFormation_t *pTeam = PlayBookGetFormation(fn_80178320());
    PlayBookPosition_t *pEntry = PlaySetGetEntry(pTeam, p->mIdBytes[1], 0);
    Point_8017886C own = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown18 : pEntry->mUnknown10;
    fn_80227638(&own, &own, &goal);
    if (!fn_8009F780() || fn_801BE648(p->mpUnknown792) == 86) {
        if (pBlock->mUnknown49 && !pBlock->mUnknown0) {
            pBlock->mUnknown49 = 0;
            pBlock->mUnknown1 = 1;
        }
        return;
    }
    pBlock->mUnknown49 = 0;
    if (pTactics->mUnknown4) {
        unsigned char slot = pTactics->mUnknown32[p->mIdBytes[1]];
        if (slot <= 3) pMarked = PlyrGet(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
    }
    if (pMarked) {
        {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(fn_80178308());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
        }
    }
    switch (p->mUnknown2914) {
    case 17: case 18:
        if (pMarked) {
            if (!(own.mX <= goal.mX)) {
                if (!(marked.mX <= own.mX + 4.0f)) {
                    pBlock->mUnknown40.mX = marked.mX - 3.0f;
                    float y = own.mY - 4.5f;
                    if (!(y >= goal.mY + 3.5f)) y = goal.mY + 3.5f;
                    pBlock->mUnknown40.mY = y;
                } else {
                    pBlock->mUnknown40.mX = own.mX;
                    float y = own.mY - 3.0f;
                    if (!(y >= goal.mY + 6.0f)) y = goal.mY + 6.0f;
                    pBlock->mUnknown40.mY = y;
                }
            } else {
                if (!(marked.mX >= own.mX - 4.0f)) {
                    pBlock->mUnknown40.mX = marked.mX + 3.0f;
                    float y = own.mY - 4.5f;
                    if (!(y >= goal.mY + 3.5f)) y = goal.mY + 3.5f;
                    pBlock->mUnknown40.mY = y;
                } else {
                    pBlock->mUnknown40.mX = own.mX;
                    float y = own.mY - 3.0f;
                    if (!(y >= goal.mY + 6.0f)) y = goal.mY + 6.0f;
                    pBlock->mUnknown40.mY = y;
                }
            }
            pBlock->mUnknown49 = 1;
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
                        if (y > fn_80178A44() - 5.0f) y = fn_80178A44() - 5.0f;
                        pBlock->mUnknown40.mY = y;
                    }
                } else if (!(marked.mX <= own.mX + 2.0f)) {
                    pBlock->mUnknown40.mX = own.mX + 3.5f;
                    pBlock->mUnknown49 = 1;
                    pBlock->mUnknown40.mY = own.mY;
                    float y = own.mY + 2.5f;
                    if (y > fn_80178A44() - 5.0f) y = fn_80178A44() - 5.0f;
                    pBlock->mUnknown40.mY = y;
                }
            } else {
                int slot = !(own.mX <= goal.mX) ? 1 : 5;
                pMarked = PlyrGet(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
                {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(fn_80178308());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
        }
                if ((slot == 1 && marked.mX < goal.mX + 6.0f) || (slot == 5 && !(marked.mX <= goal.mX - 6.0f))) {
                    pBlock->mUnknown40.mX = slot == 1 ? own.mX - 3.5f : own.mX + 3.5f;
                    float y = own.mY + 2.5f;
                    if (y > fn_80178A44() - 5.0f) y = fn_80178A44() - 5.0f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            }
        } else if (fn_8009F778(p) && pTactics->mUnknown16[p->mIdBytes[1]] == 255) {
            if (pMarked) {
                if (!(own.mX <= goal.mX)) {
                    if (!(own.mX <= marked.mX + 3.0f)) pBlock->mUnknown40.mX = own.mX - 2.5f;
                } else if (!(own.mX >= marked.mX - 3.0f)) pBlock->mUnknown40.mX = own.mX + 2.5f;
                pBlock->mUnknown40.mY = own.mY;
            } else {
                int slot = !(own.mX <= goal.mX) ? 2 : 4;
                pMarked = PlyrGet(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
                {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(fn_80178308());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
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
                    pBlock->mUnknown40.mX = marked.mX - 1.5f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            } else if (!(marked.mX >= own.mX - 3.0f) && (!pSpecial || specialRight)) {
                pBlock->mUnknown40.mX = marked.mX + 1.5f;
                float y = own.mY;
                if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                pBlock->mUnknown40.mY = y;
                pBlock->mUnknown49 = 1;
            }
        } else {
            int slot = !(own.mX <= goal.mX) ? 2 : 4;
            pMarked = PlyrGet(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
            {
            PlayBookFormation_t *pMarkedTeam = PlayBookGetFormation(fn_80178308());
            PlayBookPosition_t *pMarkedEntry = PlaySetGetEntry(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
        }
            if (!(own.mX <= goal.mX) && !(marked.mX <= own.mX + 3.0f)) {
                if (pRight && !pRight->mUnknown361[24] && (!pSpecial || !specialRight)) {
                    pBlock->mUnknown40.mX = marked.mX - 1.5f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            } else if (!(own.mX >= goal.mX) && !(marked.mX >= own.mX - 3.0f)) {
                if (pLeft && !pLeft->mUnknown361[24] && (!pSpecial || specialRight)) {
                    pBlock->mUnknown40.mX = marked.mX + 1.5f;
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
        Point_8017886C delta;
        if (pBlock->mUnknown49) fn_80227690(&delta, &pBlock->mUnknown40, &p->mMotion);
        else fn_80227690(&delta, &own, &p->mMotion);
        if (!(fn_802270A4(&delta) <= 1.5f) && !pBlock->mUnknown24) pBlock->mUnknown1 = 1;
    }
}

extern "C" void fn_800E2550(Object_80039F5C *p, Point_8017886C *pOut, int *pAngle)
{
    Point_8017886C point = fn_80177FFC(p->mIdBytes[2]);
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    PlayBookFormation_t *pTeam = PlayBookGetFormation(fn_80178320());
    PlayBookPosition_t *pEntry = PlaySetGetEntry(pTeam, p->mIdBytes[1], 0);
    *pOut = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown18 : pEntry->mUnknown10;
    fn_80227638(pOut, pOut, &point);
    if (!(pOut->mX >= 1.0f - fn_80178A08())) {
        pOut->mX = 1.0f - fn_80178A08();
    } else if (pOut->mX > fn_80178A08() - 1.0f) {
        pOut->mX = fn_80178A08() - 1.0f;
    }
    if (!(pOut->mY >= 1.0f - fn_80178A44())) {
        pOut->mY = 1.0f - fn_80178A44();
    } else if (pOut->mY > fn_80178A44() - 1.0f) {
        pOut->mY = fn_80178A44() - 1.0f;
    }
    if (pBlock->mpUnknown36) {
        fn_8011F4E0();
        Object_80039F5C *pOther = pBlock->mpUnknown36;
        if (pOther) {
            Point_8017886C delta;
            fn_80227690(&delta, &p->mMotion, &pOther->mMotion);
            fn_801CFE40(delta.mY, delta.mX);
            if (p->mUnknown2914 >= 17 && p->mUnknown2914 <= 18) {
                pBlock->mUnknown78 = pTeam->mUnknown8.mUnknown4 == 11;
            } else {
                pBlock->mUnknown78 = !fn_8009FE24(p);
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
    } else if (pBlock->mUnknown49 && fn_8009F780() && fn_8016EADC()) {
        *pOut = pBlock->mUnknown40;
    } else {
        fn_800E3DCC(p, pOut);
    }
    *pAngle = pEntry->mUnknown20;
}

extern "C" int fn_800E283C(Object_80039F5C *p, int count, float *pValues, float *pOut, float direction, float target)
{
    int result = 0;
    if (direction == -1.0f) {
        int i = 0;
        if (i < count && !(pValues[i] > p->mMotion.mPos.mX)) {
            do { ++i; } while (i < count && pValues[i] <= p->mMotion.mPos.mX);
        }
        if (i == count) return result;
        if (!i) {
            *pOut = pValues[0] - 0.7f;
            return 1;
        }
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
        int i = count - 1;
        if (i < 0) return result;
        if (!(pValues[i] < p->mMotion.mPos.mX)) {
            do { --i; } while (i >= 0 && pValues[i] >= p->mMotion.mPos.mX);
        }
        if (i < 0) return result;
        if (i == count - 1) {
            *pOut = pValues[i] + 0.7f;
            return 1;
        }
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
    }
    return result;
}

extern "C" void fn_800E2ABC(Object_80039F5C *p)
{
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    Point_8017886C point = fn_80177FFC(p->mIdBytes[2]);
    float random = fn_80237260(0);
    Point_8017886C target;
    target.mY = point.mY + 1.4f + random;
    if (!(target.mY <= p->mMotion.mPos.mY)) {
        target.mY = fn_80177FFC(p->mIdBytes[2]).mY + 1.0f;
        if (!(target.mY <= p->mMotion.mPos.mY)) target.mY = p->mMotion.mPos.mY;
    }
    Record_800E2ABC *pRecord = (Record_800E2ABC *)fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]), p->mIdBytes[1], p->mIdBytes[2]);
    if ((pRecord->mUnknown4 & ~0x80) == 30) {
        Point_8017886C velocity;
        float value = (float)(pRecord->mUnknown5 >> 3) + (float)(pRecord->mUnknown5 & 7) * 0.1428571492433548f;
        fn_80227538(&velocity, pRecord->mUnknown6 << 17, value);
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
    fn_800E586C(p, &target);
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown4 = target;
    if (!PlayerPathIsLaneClear(p, &pBlock->mUnknown4)) {
        float values[7];
        int count = 0;
        int players = fn_80178D18(p->mIdBytes[2]);
        for (int i = 0; i < players; ++i) {
            Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);
            if (pOther != p && !(pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY)) {
                values[count++] = pOther->mMotion.mPos.mX;
            }
        }
        if (count) {
            int changed;
            do {
                changed = 0;
                for (int i = 0; i < count - 1; ++i) {
                    if (!(values[i + 1] >= values[i])) {
                        float temp = values[i + 1];
                        values[i + 1] = values[i];
                        values[i] = temp;
                        changed = 1;
                    }
                }
            } while (changed == 1);
            Point_8017886C goal = fn_80177FFC(p->mIdBytes[2]);
            float direction = !(pBlock->mUnknown4.mX <= goal.mX) ? -1.0f : 1.0f;
            int next = 0;
            float value;
            pBlock->mUnknown22 = 0;
            pBlock->mUnknown23 = 0;
            pBlock->mUnknown12.mY = pBlock->mUnknown4.mY;
            if (fn_800E283C(p, count, values, &value, direction, target.mX) == 1) {
                next = 1;
                pBlock->mUnknown4.mX = value;
                pBlock->mUnknown22 = 1;
            }
            if (fn_800E283C(p, count, values, &value, -direction, target.mX) == 1) {
                (&pBlock->mUnknown4)[next].mX = value;
                (&pBlock->mUnknown22)[next] = 1;
            }
        } else {
            pBlock->mUnknown22 = 1;
        }
    } else {
        pBlock->mUnknown22 = 1;
    }
    if (!pBlock->mUnknown22) {
        pBlock->mUnknown24 = 0;
    } else if (pBlock->mUnknown22 == 1 && pBlock->mUnknown23 == 1) {
        int angle = pRecord->mUnknown6 << 17;
        if (PlayBookGetTeam(fn_80178320())->mUnknown48) angle = (0x800000 - angle) & 0xFFFFFF;
        if (angle <= 0xBFFFFF) {
            pBlock->mUnknown20 = pBlock->mUnknown4.mX >= pBlock->mUnknown12.mX;
        } else {
            pBlock->mUnknown20 = pBlock->mUnknown4.mX < pBlock->mUnknown12.mX;
        }
    }
}

extern "C" int fn_800E2F20(Object_80039F5C *p, Point_8017886C *pPoint)
{
    int result = 0;
    if (fn_801BE648(p->mpUnknown792) == 86) {
        Point_8017886C delta = *pPoint;
        if (!(fabsf(delta.mY - p->mMotion.mPos.mY) >= 1.0f)) {
            delta.mY = p->mMotion.mPos.mY;
            fn_80227690(&delta, &delta, &p->mMotion.mPos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            result = (unsigned int)(MathAngleDiff(p->mMotion.mFacing, angle) - 0x271C72) <= 0x31C71B;
        }
    }
    return result;
}
