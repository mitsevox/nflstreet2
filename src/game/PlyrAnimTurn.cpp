/* Player animation helpers: the "Animations" replay channel that records each
   player's anim state and anim, the hand a player carries the ball in for the
   current anim state, and the turning anim state that steps a player's facing
   toward the commanded direction or the ball carrier over the anim's frames. */
#include "game/State_800D7A4C.h"
#include "game/Block_801BE60C.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/Object_801BC084.h"
#include "game/Ball.h"
#include "game/bitstream.h"
#include "game/fn_801BE60C.h"
#include "game/AnimChanStartAnim.h"
#include "game/Table_80089904.h"
#include "engine/animchan.h"


extern "C" {
void ReplayRegisterChannel(void (*pWrite)(BitStream_t *),
                 void (*pRead)(BitStream_t *, BitStream_t *, BitStream_t *, BitStream_t *, float),
                 unsigned int size, const char *pName);
void PlyrAnimReplayWrite(BitStream_t *pStream);
void PlyrAnimReplayRead(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                 BitStream_t *pStream3, float t);
int MathAngleDiff(int a, int b);
float AnimSeqGetOpcodeTime(void *p, int key);
void OSReport(const char *pMsg, ...);
unsigned char PlyrBallHandFromAnim(Object_80039F5C *p, unsigned short id);
void PlyrAnimTurnComputeStep(Object_80039F5C *p, Block_801BE60C *pBlock);
void PlyrTackleAimAtCarrier(Object_80039F5C *p, State_800D7A4C *pState);
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
int fn_800CA5CC(Object_80039F5C *p, int kind, int apply);
float PlayerGetActionScale(int kind, Object_80039F5C *p);
void AnimMomentumInit(AnimMomentum_t *p, AnimMomentumActor_t *pOther, int entry);
void AnimMomentumUpdate(AnimMomentum_t *p, AnimMomentumActor_t *pOther);
void fn_800AE7F0(int index, int team, Object_80039F5C *p);
int ScrmGetDefenseTeam(void);

extern unsigned short lbl_803192BC[2][7];
extern unsigned short lbl_803192D8[2][7];
extern signed char lbl_802DA87C[];
extern float lbl_803EAD00;
extern float lbl_803EAD04;
extern float lbl_803EAD08;
extern float lbl_803EAD0C;
extern float lbl_803EAD10;
}

// FAKEMATCH: invented unused static; its body exists only for its int-to-float double and 1.0f in .rodata
extern "C" {
static float _StrippedFramesToTime(int frames)
{
    return (float)frames + 1.0f;
}
}

// FAKEMATCH: invented unused static; its body exists only for its two blank-name strings in .rodata
extern "C" {
static void _StrippedPrintBlankName(int wide)
{
    if (!wide) {
        OSReport("???                 ");
    } else {
        OSReport("???                           ");
    }
}
}

extern "C" void PlyrAnimReplayWrite(BitStream_t *pStream)
{
    unsigned short anim = 0;

    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned char i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = PlyrGet(team, i);
            unsigned int id = fn_801BE648(pPlayer->mpUnknown792);
            for (unsigned char k = 0; k < pPlayer->mpUnknown796->mUnknown4; k++) {
                if (pPlayer->mpUnknown800[k].mUnknown8 == id) {
                    Object_801BC084 *pInfo = AnimFileGetPtrFromSlot(pPlayer->mpUnknown800[k].mUnknown6);
                    anim = pPlayer->mpUnknown800[k].mUnknown2 + pInfo->mUnknown3 * 1000;
                    break;
                }
            }
            fn_80191068(pStream, id, 16);
            fn_80191068(pStream, anim, 16);
        }
    }
}

extern "C" void PlyrAnimReplayRead(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                            BitStream_t *pStream3, float t)
{
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned char i = 0; i <= 6; i++) {
            unsigned short id = ReadBitStream(pStream1, 16);
            unsigned short anim = ReadBitStream(pStream1, 16);
            lbl_803192BC[team][i] = id;
            lbl_803192D8[team][i] = anim;
            if (pStream2) {
                ReadBitStream(pStream2, 32);
            }
            if (pStream3) {
                ReadBitStream(pStream3, 32);
            }
            if (pStream0) {
                ReadBitStream(pStream0, 32);
            }
        }
    }
}

extern "C" void PlyrAnimReplayRegister(void)
{
    ReplayRegisterChannel(PlyrAnimReplayWrite, PlyrAnimReplayRead, 448, "Animations");
}

// FAKEMATCH: invented unused static around the two target strings; its body exists only for them in .rodata
extern "C" {
static void _StrippedCheckDownOpcodes(int anim, int hasPosition, int hasDown, int hasUp)
{
    if (hasPosition && !hasDown && !hasUp) {
        OSReport("Anim %d has a POSITION opcode with no PLAYERDOWN or PLAYERUP opcode.", anim);
    }
    if (hasDown && !hasUp && !hasPosition) {
        OSReport("Anim %d has a PLAYERDOWN opcode with no PLAYERUP or POSITION opcode.", anim);
    }
}
}

extern "C" void PlyrBallHandUpdate(Object_80039F5C *p)
{
    Ball_t *pBall = BallFindHeldBy(p);
    unsigned short id = fn_801BE648(p->mpUnknown792);

    if (pBall) {
        if (p->mUnknown776) {
            if (id != p->mUnknown778Unsigned) {
                unsigned char value = PlyrBallHandFromAnim(p, id);
                p->mUnknown777 = value;
                p->mUnknown776 = value;
            }
        } else {
            unsigned char value = PlyrBallHandFromAnim(p, id);
            p->mUnknown776 = value;
            p->mUnknown777 = value;
        }
    } else {
        p->mUnknown776 = 0;
        p->mUnknown777 = 0;
    }
    p->mUnknown778Unsigned = id;
}

extern "C" unsigned char PlyrBallHandFromAnim(Object_80039F5C *p, unsigned short id)
{
    float best = -1.0f;
    int search = 1;
    unsigned char result = 0;
    unsigned int count = AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, id);

    switch (id) {
    case 30:
    case 31:
    case 74:
    case 77:
    case 164:
    case 181:
    case 186:
    case 247:
        if (p->mUnknown776) {
            search = 0;
        }
        break;
    }
    if (!search) {
        result = p->mUnknown776;
    } else {
        for (unsigned short i = 0; i < count; i++) {
            int index = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, id, i);
            if (p->mpUnknown800[index].mUnknown30.mUnknown0 > best) {
                best = p->mpUnknown800[index].mUnknown30.mUnknown0;
                if (p->mpUnknown800[index].mUnknown7 & 0x10) {
                    result = 1;
                } else if (p->mpUnknown800[index].mUnknown7 & 0x20) {
                    result = 2;
                } else if (p->mpUnknown800[index].mUnknown7 & 1) {
                    result = 1;
                } else {
                    result = 2;
                }
            }
        }
    }
    return result;
}

// FAKEMATCH: invented unused static; its body exists only for its eight-float table in .rodata
extern "C" {
static float _StrippedGetHoldWeight(int index)
{
    static const float weights[8] = {0.14f, 0.4f, 0.4f, 0.14f, 1.0f, 0.0f, 1.6f, 1.0f};
    return weights[index];
}
}

extern "C" void fn_800D7A0C(Object_80039F5C *p, int value)
{
    p->mUnknown776 = value;
    p->mUnknown777 = value;
}

extern "C" void fn_800D7A18(Object_80039F5C *p)
{
    p->mUnknown778Unsigned = fn_801BE648(p->mpUnknown792);
}

extern "C" void PlyrAnimTurnComputeStep(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    pBlock->mUnknownCHalf = pBlock->mUnknown0Word = 0;
    PlyrMoveCmd_t *pMove = &p->mUnknown512;
    State_800D7A4C *pState = (State_800D7A4C *)&p->mUnknown336;
    if (pMove->mUnknown14 == 6 && pState->mUnknown11) {
        int facing = p->mMotion.mFacing;
        if (pBlock->mUnknown24Float > 0.0f) {
            facing += (int)(pBlock->mUnknown1CWord * (pBlock->mUnknown24Float / pBlock->mUnknown20Float));
        }
        int turn = MathAngleDiff(facing, pMove->mUnknown8);
        if (((pMove->mUnknown8 - facing) & 0xFFFFFF) > 0x800000) {
            turn = -turn;
        }
        float frames = AnimSeqGetOpcodeTime(p->mpUnknown800[pBlock->mUnknown4Word].mUnknown4C.mpUnknown0, 0xC006);
        pBlock->mUnknown24Float -= 1.0f;
        turn = (int)(turn / frames);
        pBlock->mUnknown0Word = turn;
        pBlock->mUnknownCHalf = (int)frames;
    }
}

extern "C" void PlyrAnimTurnTowardCarrier(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    State_800D7A4C *pState = (State_800D7A4C *)&p->mUnknown336;

    if (pState->mUnknown5 == 3 && BallGetCurrentHolder() && pState->mUnknown11) {
        float count = pBlock->mUnknownCHalf;
        unsigned char saved = p->mUnknown512.mUnknown14;
        p->mUnknown512.mUnknown14 = 6;
        PlyrTackleAimAtCarrier(p, pState);
        PlyrAnimTurnComputeStep(p, pBlock);
        int n = (int)count;
        int value = pBlock->mUnknown0Word * pBlock->mUnknownCHalf / n;
        pBlock->mUnknownCHalf = n;
        pBlock->mUnknown0Word = value;
        if (value < 0) {
            if (pBlock->mUnknownCHalf <= 5) {
                int limit = (int)(-lbl_803EAD00 * 46603.38f);
                pBlock->mUnknown0Word = value < limit ? limit : value;
            } else {
                int limit = (int)(-lbl_803EAD04 * 46603.38f);
                pBlock->mUnknown0Word = value < limit ? limit : value;
            }
        } else {
            if (pBlock->mUnknownCHalf <= 5) {
                int limit = (int)(lbl_803EAD00 * 46603.38f);
                pBlock->mUnknown0Word = value < limit ? limit : value;
            } else {
                int limit = (int)(lbl_803EAD04 * 46603.38f);
                pBlock->mUnknown0Word = value > limit ? limit : value;
            }
        }
        p->mUnknown512.mUnknown14 = saved;
    }
}

extern "C" void PlyrAnimRampLevels(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    if (p->mUnknown560.mFlags.mBytes[0] != 0) {
        unsigned char k = p->mUnknown560.mUnknown54;
        if (k <= 10 && pBlock->mUnknown8 > 0.0f) {
            signed char *pLevels = pBlock->mUnknownE;
            if (pLevels[k] < lbl_802DA87C[k]) {
                float step = lbl_802DA87C[k] * 0.2f;
                signed char level = (int)(pLevels[k] + step);
                pLevels[k] = level > lbl_802DA87C[k] ? lbl_802DA87C[k] : level;
                pBlock->mUnknown8 -= step * 0.01f;
                float rest = pBlock->mUnknown8;
                if (!(rest >= 0.0f)) {
                    rest = 0.0f;
                }
                pBlock->mUnknown8 = rest;
                p->mpUnknown800[pBlock->mUnknown4Word].mUnknown2C = rest;
            }
        }
    }
}

extern "C" int fn_800D7E9C(Table_80089904 *pTable, unsigned short key, void *pRecord, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *pBlock = fn_801BE60C(p->mpUnknown792, key);
    State_800D7A4C *pState = (State_800D7A4C *)&p->mUnknown336;

    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        float scale;
        pBlock->mUnknown4Word = AnimChanStartAnim(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                                       pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        pBlock->mUnknown24Float = 0.0f;
        if (pState->mUnknown5 == 3) {
            Info_80089904 *pInfo = pTable->mEntries[index].mpInfo;
            pBlock->mUnknown1CWord = pInfo->mUnknown12;
            pBlock->mUnknown24Float = pInfo->mUnknown24;
            pBlock->mUnknown20Float = pInfo->mUnknown24;
            if (pState->mUnknown9 == 1) {
                scale = lbl_803EAD0C;
            } else {
                scale = lbl_803EAD10;
            }
        } else {
            scale = lbl_803EAD08;
        }
        if (fn_800CA5CC(p, 3, 1)) {
            scale *= PlayerGetActionScale(pState->mUnknown5 == 3 ? 11 : 10, p);
        }
        pBlock->mUnknown8 = scale;
        for (int i = 0; i != 11; i++) {
            pBlock->mUnknownE[i] = 0;
        }
        p->mpUnknown800[pBlock->mUnknown4Word].mUnknown2C = scale;
        AnimMomentumInit(&pBlock->mUnknown28, (AnimMomentumActor_t *)p, pBlock->mUnknown4Word);
        PlyrAnimTurnComputeStep(p, pBlock);
        if (pState->mUnknown5 == 3) {
            fn_800AE7F0(6, ScrmGetDefenseTeam(), p);
            if (pState->mUnknown5 == 3 && pBlock->mUnknownCHalf != 0) {
                pBlock->mUnknownCHalf += 6;
            }
        }
        pBlock->mUnknown19 = 0;
        break;
    }
    case 1:
        break;
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            PlyrAnimRampLevels(p, pBlock);
            if (pBlock->mUnknown0Word != 0) {
                if (--pBlock->mUnknownCHalf > 0) {
                    PlyrAnimTurnTowardCarrier(p, pBlock);
                    p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown0Word) & 0xFFFFFF;
                    p->mpUnknown800[pBlock->mUnknown4Word].mUnknownC =
                        (p->mpUnknown800[pBlock->mUnknown4Word].mUnknownC + pBlock->mUnknown0Word) & 0xFFFFFF;
                } else {
                    pBlock->mUnknown0Word = 0;
                    pBlock->mUnknownCHalf = 0;
                }
            }
            AnimMomentumUpdate(&pBlock->mUnknown28, (AnimMomentumActor_t *)p);
            if (p->mFlags & 1) {
                p->mFlags &= ~1;
            }
        }
        break;
    }
    return 0;
}
