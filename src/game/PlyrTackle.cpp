/* Player tackle and contact states: the defender alignment state before the snap (42), the timed
   wait-and-face state (51), the tackle state (12) with its button choice, rating contest and fumble
   try, the turn-in-place state (6), the ball-carrier momentum state (10) with its toss and pitch,
   the blocker shed moves, and the contact messages players send each other when they collide. */
#include "game/State_800E4494.h"
#include "game/StyleTracker.h"
#include "engine/animchan.h"
#include "game/Command_800CEE74.h"
#include "game/Block_801BE60C.h"
#include "game/Input_800B6D34.h"
#include "game/LevelData.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800EA284.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/Record_800B15FC.h"
#include "game/Record_800DB60C.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include <string.h>
#include "game/PlayBookDb.h"
#include "game/PlaySet.h"
#include "game/PlayBookGetPlay.h"
#include "game/fn_80178D18.h"
#include "game/Vec3Magnitude.h"
#include "game/Vec2Distance.h"
#include "game/Vec2Add.h"
#include "game/SyncRandGetRange.h"
#include <math.h>
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"
#include "game/AnimChanStartAnim.h"
#include "game/Table_80089904.h"
#include "game/Record_800CE608.h"
#include "game/AnimMomentumActor.h"
#include "engine/vec.h"
#include "game/PreSnapPhase.h"
#include "game/State_803EB098.h"
#include "game/State_800D7A4C.h"
#include "game/fn_80177FE0.h"

/* Player block at +336 as used by the functions of the state entry at
   0x802DB370. */
struct State_800E9E18 {
    int mUnknown0;
    float mUnknown4;
    char mUnknown8[4];
    unsigned char mUnknown12;
    char mUnknown13[3];
    int mUnknown16;
    char mUnknown20[20];
    float mUnknown40;
};

/* Player block at +336 as used by PlyrTurnEnter and PlyrTurnUpdate. */
struct State_800E8BE8 {
    int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

/* Bytes of the player block at +336 that PlyrContactSendHitFrom sets under states 32,
   17 and 16. */
struct State_800E954C {
    char mUnknown0[8];
    unsigned char mUnknown8;
    char mUnknown9[6];
    unsigned char mUnknown15;
    char mUnknown16[15];
    unsigned char mUnknown31;
};

struct Block_800E7588 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    short mUnknown6;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknown10;
    char mUnknown11[8];
    unsigned char mUnknown19;
};

extern "C" {
extern float gPlyrMoveFwdSpeed;
}

extern "C" void Vec2Sub(void *pOut, void *pA, void *pB);

extern "C" {
int fn_801CFE40(float y, float x);
}

extern "C" {
int MathAngleDiff(int a, int b);
}

extern "C" {
void fn_8009A5DC(int a, int b, void *pA, int *pB);
}

extern "C" {
int fn_8009A578(int handle);
}

extern "C" {
Object_80039F5C *fn_800B6544(int index);
}

extern "C" {
int fn_800B7FE8(Object_80039F5C *p);
}

extern "C" {
void fn_800CE674(Object_800CE674 *p);
}

extern "C" {
void fn_800CE684(Object_800CE674 *p);
}

extern "C" {
void fn_800EFE60(int a, void *p, Object_80039F5C *pObject);
}

extern "C" {
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
}

extern "C" {
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
}

extern "C" {
int AnimChanIsMirrored(AnimChannel_t *entry);
}

extern "C" {
void AnimChanSetMirrored(AnimChannel_t *entry, int value);
}

extern "C" void Vec2FromAngle(void *pOut, int angle, float length);

extern "C" {
void fn_8011E240(Object_80039F5C *p);
}

extern "C" {
void fn_8011E3EC(Object_80039F5C *p, int a);
}

extern "C" {
int fn_8011E9D8(State_80039F5C *pState);
}

extern "C" {
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
}

extern "C" {
int BallStateGet(Ball_t *pBall, int *pOut);
}

extern "C" {
int fn_801486A0(void);
}

extern "C" {
void PlyrCollideRemoveExempt(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
int fn_80178308(void);
}

extern "C" {
int fn_80178320(void);
}

extern "C" {
int fn_801787A0(void);
}

extern "C" {
float AnimSeqGetOpcodeTime(void *p, int key);
}

extern "C" {
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float f, void *e);
}

extern "C" {
float fn_80178A08(void);
}

extern "C" {
float fn_80178A44(void);
}

extern "C" {
int fn_80178348(void);
}

extern "C" {
int fn_800A2178(void);
}

extern "C" {
int fn_8009FE24(Object_80039F5C *p);
}

extern "C" {
void fn_800A3B58(Object_80039F5C *p, int a, int b);
}

extern "C" {
Point_8017886C fn_80177FFC(int team);
}

extern "C" {
Object_80039F5C *fn_8017876C(void);
}

extern "C" {
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
}

extern "C" {
float SyncRandGetFloat(int stream);
}

extern "C" {
int SyncTimeGetGameTime(void);
}

extern "C" {
int fn_800C4184(Object_80039F5C *p);
}

extern "C" {
void fn_800D7A18(Object_80039F5C *p);
}

extern "C" {
void PlayerActionAnimPitchInit(void *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, float value);
}

extern "C" {
void PlayerActionAnimTossUpdate(void *pBlock, Object_80039F5C *p);
}

extern "C" {
void PlayerActionAnimPitchUpdate(void *pBlock, Object_80039F5C *p);
}

extern "C" {
void PlayerActionAnimAiConsiderPitch(void *pBlock, Object_80039F5C *p);
}

extern "C" {
void fn_8009BD60(Object_80039F5C *p);
}

extern "C" {
void HudClearMashPlayers(int a, int b);
}

extern "C" {
void fn_80178718(Object_80039F5C *p);
}

extern "C" {
void TurnToPlayStartAnim(Object_80039F5C *p, int a, int b);
}

extern "C" {
void HuddleGetSpot(Point_8017886C *pOut, int *pFacing, Object_80039F5C *p, int value);
}

extern "C" {
int fn_800B5FEC(Object_80039F5C *p);
}

extern "C" {
int fn_800B76E8(Object_80039F5C *p);
}

extern "C" {
int fn_800B7F34(Object_80039F5C *p);
}

extern "C" {
int fn_800B7F88(Object_80039F5C *p);
}

extern "C" {
int fn_800B83A0(Object_80039F5C *p);
}

extern "C" {
int fn_800C05F4(void);
}

extern "C" {
int fn_800A8444(int team);
}

extern "C" {
int PlayerMoveGetKind(Object_80039F5C *p);
}

extern "C" {
void PlayerMoveBegin(Object_80039F5C *p, int a, int b);
}

extern "C" {
void PlayerMoveSetResult(Object_80039F5C *p, int a);
}

extern "C" {
void PlyrTackleStartAnim(Object_80039F5C *p, Block_800E7588 *pBlock);
}

extern "C" {
unsigned int fn_8011E188(void);
}

extern "C" {
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b);
}

extern "C" {
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int a);
}

extern "C" {
int fn_8011F1A4(void);
}

extern "C" {
PlayBookFormation_t *PlayBookGetFormation(int team);
}

extern "C" {
Point_8017886C fn_80177FE0(void);
}

extern "C" {
int fn_80177F70(void);
}

extern "C" {
int fn_801783AC(int bit);
}

extern "C" {
void PlayerActionGetAlignSpot(Object_80039F5C *p, Point_8017886C *pOut, int *pAngle);
}

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

extern "C" {
Message_800F01CC *fn_800AEE20(Object_80039F5C *p);
}

/* Player block at +336 as PlyrAlignStartShuffle sets it. */
struct State_800E4120 {
    char mUnknown0[3];
    unsigned char mUnknown3;
    char mUnknown4[20];
    unsigned char mUnknown24;
};

/* Player block at +336 as PlyrAlignTurnPhase uses it. */
struct State_800E4264 {
    char mUnknown0[56];
    int mUnknown56;
    int mUnknown60;
    float mUnknown64;
};

extern "C" {
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
}

extern "C" {
float AnimSeqGetTimeToOpcode(void *p, int key);
}

/* Play record bytes as PlyrAlignExit reads and writes them. */
struct Record_800E4EE4 {
    unsigned char mUnknown0;
    char mUnknown1[3];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
};

/* Player block at +336 as PlyrAlignExit tests it. */
struct State_800E4EE4 {
    char mUnknown0[32];
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    char mUnknown34[42];
    unsigned int mUnknown76;
};

extern "C" {
float fn_801CFB94(int angle);
}

extern "C" {
void PlayerReleaseJointCtrls(Object_80039F5C *p);
}

/* Player block at +336 as PlyrAlignInput uses it. */
struct State_800E513C {
    char mUnknown0[3];
    unsigned char mUnknown3;
};

extern "C" {
int fn_801784C4(void);
}

extern "C" {
int PlayerActionIsNearLine(Object_80039F5C *p);
}

extern "C" {
void PlayerPathStartSideAnim(Object_80039F5C *p, int a, int b);
}

/* Records passed to PlyrEngageAiWinsShed as its third and fourth arguments; only the
   float +28 and byte +55 are read. */
struct Record_800E5EA4 {
    char mUnknown0[28];
    float mUnknown28;
    char mUnknown32[23];
    unsigned char mUnknown55;
};

extern "C" {
Record_8011F4E0 *fn_8011F4E0(void);
}

extern "C" {
void fn_800FBB70(void);
}

extern "C" {
int fn_8009F778(Object_80039F5C *p);
}

extern "C" {
Object_80039F5C *fn_800FB844(Object_80039F5C *p);
}

extern "C" {
void fn_800FB824(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
void PlayerActionRollAlignChange(Object_80039F5C *p);
}

extern "C" {
int fn_800B146C(void);
}

extern "C" {
extern float gFrameTimeScale;
}

extern "C" {
int fn_800A7F58(int team);
}

extern "C" {
int fn_800AC074(int team, int value);
}

extern "C" {
float PlayTrackGetPlayIdRate(void);
}

extern "C" {
float fn_801CFB18(int angle);
}

extern "C" {
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
}

extern "C" {
float fn_800CA9B4(int kind, Object_80039F5C *p);
}

extern "C" {
int fn_801CFE08(float value);
}

extern "C" {
int fn_8011F1CC(void);
}

extern "C" float Vec2Distance(void *pA, void *pB);

extern "C" {
int fn_800ACD04(Object_80039F5C *p);
}

extern "C" {
float fn_80178298(void);
}

extern "C" {
float fn_80178A2C(void);
}

extern "C" {
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b);
}

extern "C" float Vec2Magnitude(void *p);

extern "C" {
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *message, Object_80039F5C *p);
}

/* Player block at +336 as used by PlyrTackleEnter and PlyrTackleUpdate. */
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
void PossTryFumble(Object_80039F5C *p, Object_80039F5C *pOther);
}



/* Static data of this file, in address order: the .data tables 0x802DA8BC-0x802DAAB4 and the .sdata
   objects 0x803EAD4C-0x803EADB8. */
extern "C" {
int _PlyrEngage_aRunMoveLists[7][2][3] = {
    {{62, 0xFFFF, 0}, {120, 0xFFFF, 0}},
    {{63, 0xFFFF, 0}, {121, 0xFFFF, 0}},
    {{122, 0xFFFF, 0}, {124, 0xFFFF, 0}},
    {{123, 0xFFFF, 0}, {125, 0xFFFF, 0}},
    {{241, 0xFFFF, 0}, {131, 0xFFFF, 0}},
    {{242, 0xFFFF, 0}, {131, 0xFFFF, 0}},
    {{130, 0xFFFF, 0}, {131, 0xFFFF, 0}}
};
int _PlyrEngage_aPassMoveLists[7][2][3] = {
    {{118, 62, 0xFFFF}, {120, 0xFFFF, 0}},
    {{119, 63, 0xFFFF}, {121, 0xFFFF, 0}},
    {{122, 0xFFFF, 0}, {124, 0xFFFF, 0}},
    {{123, 0xFFFF, 0}, {125, 0xFFFF, 0}},
    {{241, 0xFFFF, 0}, {131, 0xFFFF, 0}},
    {{242, 0xFFFF, 0}, {131, 0xFFFF, 0}},
    {{130, 0xFFFF, 0}, {131, 0xFFFF, 0}}
};
int _PlyrEngage_aRushMoveLists[7][2][3] = {
    {{231, 0xFFFF, 0}, {0xFFFF, 0, 0}},
    {{233, 0xFFFF, 0}, {0xFFFF, 0, 0}},
    {{231, 0xFFFF, 0}, {0xFFFF, 0, 0}},
    {{233, 0xFFFF, 0}, {0xFFFF, 0, 0}},
    {{231, 233, 0xFFFF}, {0xFFFF, 0, 0}},
    {{242, 0xFFFF, 0}, {131, 0xFFFF, 0}},
    {{231, 233, 0xFFFF}, {0xFFFF, 0, 0}}
};
float _PlyrAlign_fLineLimit = 1.5f;
float _PlyrWait_fBlockTime = 3e+01f;
short _PlyrTackle_iInputFrames = 12;
unsigned char _PlyrTackle_aAimOctants[8] = {1, 2, 3, 4, 9, 5, 6, 7};
unsigned char _PlyrTackle_aAnimOctants[8] = {6, 6, 2, 1, 1, 1, 7, 3};
unsigned char _PlyrTackle_aButtonKinds[5] = {7, 1, 6, 8, 9};
float _PlyrTackle_fReachAngle = 45.0f;
float _PlyrTackle_fReachDistance = 1e+01f;
unsigned int _PlyrTackle_uAimRate = 20;
float _PlyrTackle_fBehindLineScale = 0.2f;
unsigned int _PlyrTackle_uKindChance = 50;
float _PlyrTackle_fOtherRatingScale = 1.0f;
float _PlyrTackle_fOtherRollScale = 0.0f;
float _PlyrTackle_fRatingScale = 0.5f;
float _PlyrTackle_fRollScale = 0.0f;
float _PlyrTackle_fRollDamp = 0.5f;
float _PlyrTackle_fWinMargin = 0.65f;
unsigned char _PlyrContact_aDirOctants[8] = {6, 7, 1, 2, 3, 4, 9, 5};
unsigned char _PlyrContact_aSideOctants[8] = {1, 2, 3, 4, 9, 5, 6, 7};
float _PlyrContact_fBreakDistance = 2.0f;
float _PlyrContact_fEdgeMargin = 1.15f;
float _PlyrContact_fWallSpeed = 0.25f;
}

/* Forward declarations of the functions this file defines, in address order. */
extern "C" void PlyrAlignStartShuffle(Object_80039F5C *p, State_800E4120 *pState, int heading, float speed);
extern "C" void PlyrAlignReset(Object_80039F5C *p);
extern "C" int PlyrEngageGetBallSide(Object_80039F5C *p, int value);
extern "C" int PlyrEngageGetInputDir(Object_80039F5C *p);
extern "C" int PlyrTackleIsShallowPath(Object_80039F5C *p);
extern "C" int PlyrTackleCanReach(Object_80039F5C *p);
extern "C" void PlyrTackleStartMove(Object_80039F5C *p, Block_800E7588 *pBlock);
extern "C" int PlyrTackleCanStart(Object_80039F5C *p);
extern "C" int PlayerIsFreeOfBall(Object_80039F5C *p);
extern "C" void PlyrTackleAimAtCarrier(Object_80039F5C *p, State_800D7A4C *state);
extern "C" int PlyrTackleStart(Object_80039F5C *p, int unused, int mode);
extern "C" int PlyrTackleContest(Object_80039F5C *p, Object_80039F5C **ppLast);
extern "C" int PlyrContactCanReact(Object_80039F5C *p);
extern "C" int PlyrContactPickHeight(Object_80039F5C *p);
extern "C" void PlyrContactSendKnock(Object_80039F5C *p);
extern "C" int PlyrContactSendPush(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" void PlyrContactCollide(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int PlyrContactResolve(Object_80039F5C *p, int angle, int direction);
extern "C" int PlyrContactIsBeforeImpact(Object_80039F5C *p);

extern "C" const char gUpTorsoJointName[] = "up_torso";

extern "C" {
void PlyrAlignCheckSpot(Object_80039F5C *p)
{
    State_800E4494 *state = (State_800E4494 *)&p->mUnknown336;
    Object_80039F5C *pOther = state->mpUnknown36;
    Point_8017886C origin;
    origin = fn_80177FFC(p->mIdBytes[2]);
    if (pOther->mpState->mId == 7) {
        PlayBookFormation_t *pTeam = PlayBookGetFormation(fn_80178308());
        PlayBookPosition_t *pEntry = PlaySetGetEntry(pTeam, pOther->mIdBytes[1], 0);
        Point_8017886C point;
        point.mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
        point.mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;

        Vec2Add(&point, &point, &origin);
    }
    Point_8017886C target;
    int angle;
    PlayerActionGetAlignSpot(p, &target, &angle);
    if (!(Vec2Distance(&target, &p->mMotion.mPos) <= 2.0f)) {
        state->mUnknown1 = 1;
        p->mFlags |= 0x10;
    }
}
}

extern "C" void PlyrAlignGetCallTarget(Object_80039F5C *p, Point_8017886C *pOut)
{
    Point_8017886C target;
    Point_8017886C goal;
    Message_800F01CC *pMessage;

    target.mX = target.mY = 0.0f;
    pMessage = fn_800AEE20(p);
    if (pMessage) {
        if (pMessage->mId == 40) {
            goal = fn_80177FFC(p->mIdBytes[2]);
            switch (pMessage->mUnknown1[0]) {
            case 0:
            case 4:
                target.mX = goal.mX;
                target.mY = goal.mY + 8.0f;
                break;
            case 1:
                target.mX = goal.mX - 5.0f;
                target.mY = goal.mY + 8.0f;
                break;
            case 2:
                target.mX = goal.mX + 5.0f;
                target.mY = goal.mY + 8.0f;
                break;
            case 3:
                target.mX = goal.mX - 7.0f;
                target.mY = goal.mY + 8.0f;
                break;
            case 5:
                target.mX = goal.mX + 7.0f;
                target.mY = goal.mY + 8.0f;
                break;
            }
            target.mX = CLAMP(target.mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
            target.mY = CLAMP(target.mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
            *pOut = target;
        } else if (pMessage->mId == 92) {
            goal = fn_80177FFC(p->mIdBytes[2]);
            switch (pMessage->mUnknown1[0]) {
            case 0:
                target.mX = goal.mX;
                target.mY = goal.mY + 3.0f;
                break;
            case 1:
                target.mX = goal.mX - 6.0f;
                target.mY = goal.mY + 3.0f;
                break;
            case 2:
                target.mX = goal.mX + 6.0f;
                target.mY = goal.mY + 3.0f;
                break;
            }
            target.mX = CLAMP(target.mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
            target.mY = CLAMP(target.mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
            *pOut = target;
        }
    }
}

extern "C" void PlyrAlignStartShuffle(Object_80039F5C *p, State_800E4120 *pState, int heading, float speed)
{
    p->mpUnknown796->mUnknown8 = p->mMotion.mFacing = 0xC00000;
    fn_8009BD60(p);
    if (((heading - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        p->mUnknown1008.mUnknown0 = 6;
    } else {
        p->mUnknown1008.mUnknown0 = 3;
    }
    if (p->mMotion.mPos.mX > fn_80177FFC(p->mIdBytes[2]).mX) {
        p->mUnknown1008.mUnknown1 = 5;
    } else {
        p->mUnknown1008.mUnknown1 = 6;
    }
    p->mFlags &= ~4;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 28, 1.0f, p);
    if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 28)) {
        int index = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 28, 0);
        float rate = speed * 1.025641f;
        if (rate > 1.4f) {
            rate = 1.4f;
        }
        p->mpUnknown800[index].mUnknown2C = rate;
        p->mUnknown512.mUnknown14 = 0;
        pState->mUnknown3 = 1;
        pState->mUnknown24 = 0;
    }
}

extern "C" int PlyrAlignTurnPhase(Table_80089904 *pTable, unsigned short key, void *pRecord, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int phase)
{
    State_800E4264 *pState = (State_800E4264 *)&p->mUnknown336;

    switch (phase) {
    case 0: {
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        if (index >= 0) {
            p->mFlags &= ~4;
            AnimChanStartAnim(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                        pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        }
        int heading = pState->mUnknown56;
        if (MathAngleDiff(heading, p->mMotion.mFacing) > 46603) {
            fn_801BE760(p->mpUnknown792, key, 1);
            if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 189)) {
                AnimChannel_t *pChannels = p->mpUnknown800;
                int channel = AnimChanGetStateChannelByIndex(p->mpUnknown796, pChannels, 189, 0);
                pState->mUnknown64 = pChannels[channel].mUnknown48;
                if (pState->mUnknown64 == 0.0f) {
                    pState->mUnknown64 = AnimSeqGetTimeToOpcode(&pChannels[channel].mUnknown4C, 0xC004);
                    if (pState->mUnknown64 == 0.0f) {
                        break;
                    }
                }
                pState->mUnknown64 = pState->mUnknown64 > 50.0f ? 50.0f : pState->mUnknown64;
                pState->mUnknown60 = (int)(MathAngleDiff(heading, p->mMotion.mFacing) / pState->mUnknown64);
                if (((p->mMotion.mFacing - heading) & 0xFFFFFF) <= 0x7FFFFF) {
                    pState->mUnknown60 = -pState->mUnknown60;
                }
            }
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (pState->mUnknown64 > 0.0f) {
            pState->mUnknown64 -= 1.0f;
            p->mMotion.mFacing += pState->mUnknown60;
            p->mpUnknown796->mUnknown8 += pState->mUnknown60;
        }
        break;
    }
    return 0;
}

extern "C" int PlyrAlignEnter(Object_80039F5C *p) {
    State_800E4494 *state = (State_800E4494 *)&p->mUnknown336;
    p->mFlags &= ~4;
    memset(state, 0, sizeof(State_800E4494));
    state->mUnknown49 = state->mUnknown3 = state->mUnknown51 = state->mUnknown50 = 0;
    state->mUnknown36 = 0;
    state->mUnknown0 = 0;
    state->mUnknown76 = 0;
    state->mUnknown77 = 0;
    state->mUnknown56 = 0xC00000;
    PlyrAlignReset(p);
    state->mUnknown1 = 0;
    state->mUnknown2 = 0;
    state->mUnknown54 = 0;
    state->mUnknown55 = 0;
    state->mUnknown32 = 0;
    state->mUnknown33 = 0;
    PlayBookFormation_t *pObject = PlayBookGetFormation(fn_80178308());
    switch (p->mUnknown2914) {
    case 17:
    case 18:
        if (pObject->mUnknown8.mUnknown4 == 11)
            state->mUnknown78 = 1;
        else
            state->mUnknown78 = 0;
        break;
    default:
        if (fn_8009FE24(p))
            state->mUnknown78 = 0;
        else
            state->mUnknown78 = 1;
        break;
    }
    fn_800A3B58(p, 2, 0);
    state->mUnknown68 = p->mMotion.mPos.mX;
    state->mUnknown72 = p->mMotion.mPos.mY;
    return 0;
}

extern "C" int PlayerActionAnimIsReactionAlt(Object_80039F5C *p);
extern "C" void PlayerActionAlignDefender(Object_80039F5C *p);
extern "C" int fn_8009F780(void);
extern "C" int PlyrAlignIsFree(Object_80039F5C *p);
extern "C" void fn_800E2FE4(Object_80039F5C *player, Point_8017886C *target, int angle);
extern "C" void fn_800E36DC(Object_80039F5C *player);
extern "C" void PlayerActionPickLaneTarget(Object_80039F5C *p);
extern "C" void PlayerReleaseFlaggedJointCtrls(Object_80039F5C *p);
extern "C" Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width,
                                         int facing);
extern "C" unsigned short fn_801BE648(void *p);

extern "C" int PlyrAlignUpdate(Object_80039F5C *p)
{
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    State_800E4494 *pState = (State_800E4494 *)&p->mUnknown336;
    Point_8017886C target;
    int heading;
    if (p->mFlags & 0x4000) {
        pState->mUnknown76 = 0;
        pState->mUnknown77 = 0;
    }
    if (pState->mUnknown76 || pState->mUnknown77) {
        if (!(p->mFlags & 4)) {
            return 0;
        }
        p->mFlags &= ~4;
        if (pState->mUnknown76) {
            pState->mUnknown1 = 0;
            if (!(p->mFlags & 0x40000)) {
                int facing = p->mMotion.mFacing;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = facing;
                p->mUnknown512.mUnknown4 = facing;
                p->mUnknown512.mUnknown0 = 0.0f;
            } else {
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 73, 1.0f, p);
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 85, 1.0f, p);
            }
        } else if (pState->mUnknown77) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        }
        pState->mUnknown77 = 0;
        pState->mUnknown76 = 0;
    }
    if (!PlayerActionAnimIsReactionAlt(p)) {
        PlayerActionAlignDefender(p);
    }
    PlayerActionGetAlignSpot(p, &target, &heading);
    if ((fabsf(p->mMotion.mPos.mX - target.mX) > 1.0f || fabsf(p->mMotion.mPos.mY - target.mY) > 1.0f) &&
        !(pState->mUnknown24 && pState->mUnknown30) && !pState->mUnknown36 && !PlayerActionAnimIsReactionAlt(p) &&
        !(pState->mUnknown49 && fn_8009F780()) && !pState->mUnknown0) {
        pState->mUnknown1 = 1;
    }
    if (pState->mUnknown0 && p->mUnknown8 == 255) {
        Point_8017886C delta;
        Vec2Sub(&delta, &target, &p->mMotion.mPos);
        if (Vec2Magnitude(&delta) > 0.5f && !pState->mUnknown36) {
            if (PlyrAlignIsFree(p)) {
                fn_800E2FE4(p, &target, 0xC00000);
            }
        } else if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) > 0x71C71) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = 0xC00000;
            p->mUnknown512.mUnknown4 = 0xC00000;
            p->mUnknown512.mUnknown0 = 0.0f;
        }
    }
    fn_8010A2DC(p, 0, -1);
    if (!(p->mFlags & 0x4000)) {
        if (pState->mUnknown36) {
            if (pRecord && pRecord->mUnknown16[p->mIdBytes[1]] == 255) {
                pState->mUnknown36 = 0;
            } else {
                PlyrAlignCheckSpot(p);
            }
        }
        if (pState->mUnknown54) {
            float spot[2];
            Object_80039F5C *pOther = fn_80124C28(p, spot, 0xE38E3, 2.75f, 0.1f, p->mMotion.mFacing);
            if (pOther) {
                Point_8017886C delta;
                Vec2Sub(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
                int angle = delta.Heading();
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown0 = 1.0f;
            }
        } else if (pState->mUnknown1 == 1) {
            if ((signed char)--pState->mUnknown2 <= 0) {
                pState->mUnknown2 = 0;
                fn_800E2FE4(p, &target, heading);
                if (pState->mUnknown76 || pState->mUnknown77) {
                    return 0;
                }
            }
        } else {
            PlayerReleaseFlaggedJointCtrls(p);
            if (pState->mUnknown24 == 1 && !pState->mUnknown50 && --pState->mUnknown28 < 0) {
                if (!pState->mUnknown22[0]) {
                    PlayerActionPickLaneTarget(p);
                }
                fn_800E36DC(p);
            }
        }
    } else {
        if (p->mMotion.mUnknown28 > 0.1f) {
            p->mFlags &= ~0x40000;
        }
        pState->mUnknown33 = 0;
        pState->mUnknown24 = 0;
        pState->mUnknown0 = 1;
    }
    if (!pState->mUnknown24) {
        if (!pState->mUnknown54) {
            if (pState->mUnknown32 || pState->mUnknown33) {
                if (p->mFlags & 4) {
                    p->mFlags &= ~4;
                    p->mMotion.mFacing = heading;
                    fn_8009BD60(p);
                    if (pState->mUnknown32) {
                        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 203, 1.0f, p);
                    } else {
                        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 85, 1.0f, p);
                    }
                    pState->mUnknown32 = 0;
                    pState->mUnknown33 = 0;
                }
            } else if (pState->mUnknown3) {
                pState->mUnknown1 = 0;
                float limit = fn_80177FFC(p->mIdBytes[2]).mY + 0.15625f + 1.0f;
                if (p->mMotion.mPos.mY < limit) {
                    p->mMotion.mPos.mY = limit;
                }
                if (fn_801BE648(p->mpUnknown792) == 28) {
                    if (p->mFlags & 4) {
                        p->mFlags &= ~4;
                        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 86, 1.0f, p);
                    }
                } else if (MathAngleDiff(p->mMotion.mFacing, heading) <= 0x16C16) {
                    p->mMotion.mFacing = heading;
                    pState->mUnknown3 = 0;
                } else {
                    if (((heading - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                        p->mMotion.mFacing = (p->mMotion.mFacing - 0x16C16) & 0xFFFFFF;
                    } else {
                        p->mMotion.mFacing = (p->mMotion.mFacing + 0x16C16) & 0xFFFFFF;
                    }
                }
            } else if (p->mMotion.mPos.mZ == 0.0f && p->mMotion.mUnknown40 == 0.0f && p->mMotion.mUnknown44 == 0.0f) {
                int anim = fn_801BE648(p->mpUnknown792);
                if (anim == 74 || anim == 203 || anim == 100) {
                    if (MathAngleDiff(p->mMotion.mFacing, heading) <= 0xAAAAA) {
                        int inside = p->mMotion.mPos.mY < fn_80177FFC(p->mIdBytes[2]).mY + 2.0f &&
                                     p->mMotion.mPos.mY > fn_80177FFC(p->mIdBytes[2]).mY + 1.0f &&
                                     fabsf(p->mMotion.mPos.mX) < 8.0f &&
                                     (unsigned int)(p->mUnknown2914 - 4) <= 8;
                        if (inside) {
                            if (!(p->mFlags & 0x40000)) {
                                if (fn_801BE648(p->mpUnknown792) == 100) {
                                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
                                }
                                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 86, 1.0f, p);
                            }
                        } else {
                            int near = p->mMotion.mPos.mY < fn_80177FFC(p->mIdBytes[2]).mY + 2.5f &&
                                       fabsf(p->mMotion.mPos.mX) < 8.0f;
                            if (near) {
                                pState->mUnknown30 = 1;
                                PlayerPathStartSideAnim(p, 8, 1);
                            } else if (!(p->mFlags & 0x40000)) {
                                if (fn_801BE648(p->mpUnknown792) == 100) {
                                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
                                }
                                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 85, 1.0f, p);
                            }
                        }
                    } else if (pState->mpUnknown36) {
                        if (pState->mpUnknown36->mMotion.mUnknown40 == 0.0f && !pState->mUnknown1 &&
                            MathAngleDiff(p->mMotion.mFacing, heading) > 0x71C71) {
                            p->mUnknown512.mUnknown14 = 7;
                            p->mUnknown512.mUnknown4 = heading;
                            p->mUnknown512.mUnknown8 = heading;
                            p->mUnknown512.mUnknown0 = 2.0f;
                        }
                    } else {
                        if (!(p->mFlags & 0x4000)) {
                            p->mUnknown512.mUnknown14 = 7;
                            p->mUnknown512.mUnknown4 = heading;
                            p->mUnknown512.mUnknown8 = heading;
                            p->mUnknown512.mUnknown0 = 2.0f;
                        } else {
                            p->mUnknown512.mUnknown14 = 1;
                            p->mUnknown512.mUnknown8 = heading;
                            p->mUnknown512.mUnknown4 = heading;
                            p->mUnknown512.mUnknown0 = 0.0f;
                        }
                        pState->mUnknown1 = 0;
                    }
                }
            }
        }
        if (!pState->mUnknown24) {
            pState->mUnknown30 = 1;
        }
    }
    if (!pState->mUnknown3 && (p->mFlags & 4) && pState->mUnknown30 == 1 && fn_801BE648(p->mpUnknown792) == 189) {
        p->mFlags &= ~4;
        PlayerPathStartSideAnim(p, 8, 1);
    }
    return 0;
}

extern "C" int PlyrAlignExit(Object_80039F5C *p)
{
    State_800E4EE4 *pState = (State_800E4EE4 *)&p->mUnknown336;
    Record_800E4EE4 *pRecord =
        (Record_800E4EE4 *)fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);

    if ((pRecord->mUnknown0 & ~0x80) == 48 && fn_800AD9B4() == 3 && (pRecord->mUnknown4 & ~0x80) == 30) {
        Point_8017886C delta;
        Vec2Sub(&delta, (Point_8017886C *)&p->mMotion.mPos, (Point_8017886C *)&p->mUnknown403[1]);
        float yards = pRecord->mUnknown5 >> 3;
        yards += (pRecord->mUnknown5 & 7) * (1.0f / 7.0f);
        int angle = (pRecord->mUnknown6 << 17 & 0xFE0000) - 0xC00000;
        if (angle < 0) {
            angle = 0xC00000 - (pRecord->mUnknown6 << 17 & 0xFE0000);
        }
        float distance = yards * fn_801CFB94(angle);
        yards *= (distance + delta.mY) / distance;
        if (yards < 0.0f) {
            yards = 0.0f;
        }
        pRecord->mUnknown5 = (unsigned int)yards << 3;
        pRecord->mUnknown5 += (int)((yards - (unsigned int)yards) * 7.0f);
    }
    if ((pState->mUnknown76 & 0xFFFF0000) || pState->mUnknown33) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.0f;
    }
    if (pState->mUnknown32 == 0) {
        PlayerReleaseJointCtrls(p);
        return 1;
    }
    return 0;
}

extern "C" int PlyrAlignInput(Object_80039F5C *p)
{
    State_800E513C *pState = (State_800E513C *)&p->mUnknown336;
    Input_800B6D34 input;
    Point_8017886C dir;
    float limit;
    float speed;
    int near;

    if (fn_800C05F4() != 0) {
        return 0;
    }
    if (fn_800AD9B4() == 8) {
        return 0;
    }
    if (lbl_803EABA4->fn_800C043C(p->mIdBytes[2]) && p->mIdBytes[2] == fn_80178320() &&
        p == fn_800B6544(fn_800B65A0(p->mIdBytes[2]))) {
        return 0;
    }
    fn_800B6D34(p, &input);
    dir.mX = dir.mY = 0.0f;
    if (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f) {
        dir.mX = input.mUnknown4;
        dir.mY = input.mUnknown8;
    } else {
        if (input.mUnknown0 & 1) {
            dir.mY = 1.0f;
        }
        if (input.mUnknown0 & 2) {
            dir.mY = -1.0f;
        }
        if (input.mUnknown0 & 4) {
            dir.mX = -1.0f;
        }
        if (input.mUnknown0 & 8) {
            dir.mX = 1.0f;
        }
    }
    if (PlayerActionIsNearLine(p)) {
        limit = 2.25f;
    } else {
        limit = _PlyrAlign_fLineLimit;
    }
    near = 0;
    if (p->mIdBytes[2] == fn_80178320() &&
        !(fabsf(p->mMotion.mPos.mY - fn_80177FFC(p->mIdBytes[2]).mY) > limit)) {
        near = dir.mY < 0.0f;
    }
    if (near) {
        dir.mX = dir.mY = 0.0f;
    }
    speed = Vec2Magnitude(&dir) > 1.0f ? 1.0f : Vec2Magnitude(&dir);
    if (dir.mY != 0.0f || dir.mX != 0.0f) {
        p->mFlags = (p->mFlags | 0x400) & ~0x10;
        int heading = fn_801CFE40(dir.mY, dir.mX) - input.mUnknown20;
        if (fn_801784C4()) {
            heading -= 0x800000;
        }
        heading &= 0xFFFFFF;
        int turn = MathAngleDiff(heading, p->mMotion.mFacing);
        if (turn > 0x56C16B && speed > 0.6f) {
            speed = 0.6f;
        }
        int facing = p->mIdBytes[2] == fn_80178308() ? 0x400000 : 0xC00000;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown8 = facing;
        p->mUnknown512.mUnknown0 = speed;
        p->mUnknown512.mUnknown4 = heading;
        if (turn >= 0x200000 && turn <= 0x600000) {
            if (fn_801BE648(p->mpUnknown792) == 86) {
                if (pState->mUnknown3 == 0) {
                    PlyrAlignStartShuffle(p, (State_800E4120 *)pState, heading >= 0x400000 && heading <= 0xC00000 ? 0x800000 : 0, 0.975f);
                    return 0;
                }
            } else if (pState->mUnknown3 == 0) {
                p->mFlags &= ~0x40000;
                return 0;
            }
            p->mUnknown512.mUnknown14 = 0;
        } else {
            p->mFlags &= ~0x40000;
            pState->mUnknown3 = 0;
        }
    } else if (fn_801BE648(p->mpUnknown792) == 189 && (p->mFlags & 4)) {
        p->mFlags &= ~4;
        if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) > 0xAAAAA) {
            PlayerPathStartSideAnim(p, 8, 1);
        } else if (pState->mUnknown3 != 0 || PlayerActionIsNearLine(p)) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 86, 1.0f, p);
            pState->mUnknown3 = 0;
        } else {
            int close = 0;
            if (p->mMotion.mPos.mY < fn_80177FFC(p->mIdBytes[2]).mY + 2.5f) {
                close = fabsf(p->mMotion.mPos.mX) < 8.0f;
            }
            if (close) {
                PlayerPathStartSideAnim(p, 8, 1);
            } else if (!(p->mFlags & 0x40000)) {
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 85, 1.0f, p);
            }
        }
    }
    return 0;
}

extern "C" {
void PlyrAlignReset(Object_80039F5C *p)
{
    Message_800F01CC *pMessage = 0;
    Record_8011F4E0 *pInfo = fn_8011F4E0();
    State_800E4494 *state = (State_800E4494 *)&p->mUnknown336;
    PlayerReleaseJointCtrls(p);
    state->mUnknown1 = 1;
    state->mUnknown2 = SyncRandGetRange(0, 45);
    state->mUnknown0 = 0;
    state->mUnknown24 = 0;
    state->mUnknown26 = 15;
    state->mUnknown28 = (signed char)(int)(SyncRandGetFloat(0) * 240.0f + 150.0f);
    for (int i = 0; i < 2; i++) {
        state->mUnknown22[i] = 0;
    }

    if (pInfo->mUnknown5 == 0) {
        fn_800FBB70();
    }
    PlayBookFormation_t *pTeam = PlayBookGetFormation(p->mIdBytes[2]);
    pMessage = fn_800AEE20(p);
    if (pMessage == 0) {
        if (pTeam->mUnknown8.mUnknownF == 0) {
            pMessage = (Message_800F01CC *)fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]),
                (p->mId >> 8) & 255, (p->mId >> 16) & 255);
        } else {
            unsigned char index = PlaySetGetEntry(pTeam, p->mIdBytes[1], 0)->mUnknownB;
            pMessage = (Message_800F01CC *)fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]), p->mIdBytes[2], index);
        }
    }
    switch (pMessage->mId & ~0x80) {
    case 48:
        if (pMessage->mUnknown1[0] >= SyncRandGetRange(0, 100)) {
            state->mUnknown24 = 1;
            state->mUnknown30 = 0;
        }
        break;
    case 22:
        if ((fn_8009FE24(p) && state->mpUnknown36 == 0) ||
            (fn_8009F778(p) && state->mpUnknown36 == 0)) {
            Object_80039F5C *pOther = fn_800FB844(p);
            if (pOther) {
                fn_800FB824(p, pOther);
                state->mpUnknown36 = pOther;
            }
        } else {
            PlayerActionRollAlignChange(p);
        }
        break;
    default:
        PlayerActionRollAlignChange(p);
        break;
    }
}
}

extern "C" int PlyrAlignIsFree(Object_80039F5C *p) {
    int result = 1;
    void *pRecord;
    PlayBookFormation_t *pObject = PlayBookGetFormation(p->mIdBytes[2]);

    if (pObject->mUnknown8.mUnknownF == 0) {
        pRecord = fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
    } else {
        unsigned char index = PlaySetGetEntry(pObject, p->mIdBytes[1], 0)->mUnknownB;
        pRecord = fn_80164EC8(PlayBookGetPlay(p->mIdBytes[2]), p->mIdBytes[2], index);
    }
    if (fn_800F06F4(0, pRecord, 48, 0xFFFF) != 0xFFFF && fn_800F06F4(0, pRecord, 30, 0xFFFF) != 0xFFFF) {
        result = 0;
    }
    return result;
}

extern "C" {
void PlyrAlignAvoidTeammates(Object_80039F5C *p, float *pX)
{
    float best = 0.0f;
    int team = fn_80178320();
    signed char found = -1;
    unsigned char count = fn_80178D18(team);

    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther->mMotion.mPos.mY < p->mMotion.mPos.mY) {
            if (*pX > 0.0f) {
                int inside = pOther->mMotion.mPos.mX > fn_80177FE0().mX &&
                             pOther->mMotion.mPos.mX < fn_80177FE0().mX + 4.0f;
                if (inside && pOther->mMotion.mPos.mX + fn_80177FE0().mX > best) {
                    found = i;
                    best = pOther->mMotion.mPos.mX + fn_80177FE0().mX;
                }
            } else {
                int inside = pOther->mMotion.mPos.mX < fn_80177FE0().mX &&
                             pOther->mMotion.mPos.mX > fn_80177FE0().mX + -4.0f;
                if (inside && fabsf(pOther->mMotion.mPos.mX - fn_80177FE0().mX) > best) {
                    found = i;
                    best = fabsf(pOther->mMotion.mPos.mX + fn_80177FE0().mX);
                }
            }
        }
    }
    if (found > -1 && best > 0.0f) {
        Object_80039F5C *pOther = PlyrGet(team, found);
        if (*pX > fn_80177FE0().mX) {
            if (*pX > pOther->mMotion.mPos.mX && *pX < pOther->mMotion.mPos.mX + 1.75f) {
                *pX = pOther->mMotion.mPos.mX + 1.75f;
            }
        } else {
            if (*pX < pOther->mMotion.mPos.mX && *pX > pOther->mMotion.mPos.mX - 1.75f) {
                *pX = pOther->mMotion.mPos.mX - 1.75f;
            }
        }
    }
}
}

extern "C" int PlyrEngageTryAnims(Object_80039F5C *pOther, Object_80039F5C *p, int *pList) {
    int result = 0;

    if (BallFindHeldBy(pOther) == 0) {
        Query_800CE770 query;

        fn_800CE770(&query);
        query.mpUnknown0 = pOther;
        query.mpUnknown4 = p;
        if (fn_800A8444(p->mIdBytes[2]) != 0) {
            query.mUnknown54 = PlyrEngageGetInputDir(p);
        }
        while (result == 0 && *pList != 0xFFFF) {
            query.mUnknown52 = *pList;
            if (*pList == 241 || *pList == 242) {
                query.mUnknown54 = PlyrEngageGetBallSide(p, *pList);
            }
            pList++;
            result = fn_800CE510(&query);
        }
        if (result != 0) {
            fn_8011E1BC(pOther, p, 0, 5);
            fn_8011E33C(p, pOther, 6);
        }
    }
    return result;
}

extern "C" {
int PlyrEngageGetBallSide(Object_80039F5C *p, int value)
{
    Vector_80039F5C ball;
    int result = 1;

    if (BallGetCurrentHolder()) {
        ball.mX = BallGetCurrentHolder()->mMotion.mPos.mX;
        ball.mY = BallGetCurrentHolder()->mMotion.mPos.mY;
    } else {
        BallGetPosition(BallGetCurrent(), &ball);
    }
    int heading = p->mUnknown512.mUnknown4;
    unsigned int turn = (p->mMotion.mFacing - heading) & 0xFFFFFF;
    if (turn <= 0x105B04) {
        result = 1;
    } else if (turn >= 0x105B05 && turn <= 0x305B04) {
        result = 4;
    } else if (turn >= 0x305B05 && turn <= 0x505B05) {
        result = 7;
    } else if (turn >= 0x505B06 && turn <= 0x705B05) {
        result = 10;
    } else if (turn >= 0x705B06 && turn <= 0x905B05) {
        result = 13;
    } else if (turn >= 0x905B06 && turn <= 0xB05B05) {
        result = 16;
    } else if (turn >= 0xB05B06 && turn <= 0xD05B05) {
        result = 14;
    } else if (turn >= 0xD05B06 && turn <= 0xF05B05) {
        result = 15;
    } else if (turn >= 0xF05B06 && turn <= 0x1000000) {
        result = 1;
    }
    if ((result == 1 || result == 4) && value != 242) {
        if (p->mMotion.mPos.mX >= 0.0f) {
            result = 15;
            if (fabsf(p->mMotion.mPos.mX) + fabsf(ball.mX) > 10.0f ||
                fn_80178A08() - fabsf(p->mMotion.mPos.mX) < 2.0f) {
                result = 7;
            }
        } else {
            result = 7;
            if (fabsf(p->mMotion.mPos.mX) + fabsf(ball.mX) > 10.0f ||
                fn_80178A08() - fabsf(p->mMotion.mPos.mX) < 2.0f) {
                result = 15;
            }
        }
    }
    if (value == 241) {
        switch (result) {
        case 15:
            switch (SyncRandGetRange(0, 4)) {
            case 0:
            case 1:
                break;
            case 2:
                result = 14;
                break;
            case 3:
                result = 16;
                break;
            }
            break;
        case 4:
            switch (SyncRandGetRange(0, 4)) {
            case 0:
            case 1:
                break;
            case 2:
                result = 7;
                break;
            case 3:
                result = 10;
                break;
            }
            break;
        }
    }
    return result;
}
}

extern "C" {
int PlyrEngageAiWinsShed(Object_80039F5C *p, Object_80039F5C *pOther, Record_800E5EA4 *pA, Record_800E5EA4 *pB,
                unsigned int kind)
{
    if (fn_800A7F58(p->mIdBytes[2]) == 2) {
        return 1;
    }
    if (fn_800A7F58(p->mIdBytes[2]) == 0) {
        return 0;
    }
    Object_80039F5C *pBall = BallGetCurrentHolder();
    int defense = (int)(float)pOther->mRatings[7];
    int offense = p->mRatings[9];
    int facing = 0;
    if (kind <= 5) {
        if (pA->mUnknown28 > pB->mUnknown28) {
            defense = (int)(defense * 0.75f);
        } else {
            offense = (int)(offense * 0.75f);
        }
        facing = 1;
    } else if (pA->mUnknown55) {
        defense = (int)(defense * 0.8f);
    } else {
        offense = (int)(offense * 0.8f);
    }
    if (facing && pBall) {
        Point_8017886C delta;
        Vec2Sub(&delta, (Point_8017886C *)&pOther->mMotion.mPos, (Point_8017886C *)&p->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        Vec2Sub(&delta, (Point_8017886C *)&pBall->mMotion.mPos, (Point_8017886C *)&p->mMotion.mPos);
        int turn = MathAngleDiff(angle, fn_801CFE40(delta.mY, delta.mX));
        if (turn <= 0x3FFFFF) {
            defense -= (int)(defense * (fn_801CFB18(turn) * 0.5f));
        } else {
            defense = (int)(defense * 0.5f);
            defense += (int)(defense * (fn_801CFB94(turn) * 0.5f));
        }
    }
    offense = fn_800AC074(p->mIdBytes[2], offense);
    if (fn_800B65A0(p->mIdBytes[2]) == 255) {
        offense += (int)(offense * (PlayTrackGetPlayIdRate() * 0.5f));
    }
    if (offense < 0) {
        offense = 0;
    }
    if (defense < 0) {
        defense = 0;
    }
    if (fn_800CA5CC(p, 4, 1)) {
        offense = (int)(offense * fn_800CA9B4(6, p));
    }
    if (p->mFlags & 0x400) {
        offense = (int)(offense * 1.05f);
    }
    return SyncRandGetRange(0, offense) > SyncRandGetRange(0, defense);
}
}

extern "C" float fn_8011F4D4(void);

extern "C" int PlyrEngagePickMove(Object_80039F5C *p, Object_80039F5C *pOther, Block_8011E240 *pBlock)
{
    int heading = p->mUnknown512.mUnknown4;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    short *pRatings = p->mRatings;
    Input_800B6D34 input;
    int result = 8;
    float rating = 0.0f;
    fn_800B6D34(p, &input);
    if (pBlock->mUnknown0 == 4 || pBlock->mUnknown0 == 6) {
        if (fn_8011F1CC() && !fn_801783AC(0)) {
            if (pCarrier && (pCarrier->mFlags & 0x8000)) {
                result = SyncRandGetRange(0, 5);
            } else {
                float ratio = (float)pRatings[0] / (float)pRatings[9] * 128.0f;
                if (ratio >= 0.0f) {
                    rating = ratio;
                    if (rating > 255.0f) {
                        rating = 255.0f;
                    }
                } else {
                    rating = 0.0f;
                }
                if (rating > 192.0f && SyncRandGetRange(0, 100) <= 84) {
                    result = SyncRandGetRange(0, 5);
                } else if (rating < 84.0f && SyncRandGetRange(0, 100) <= 84) {
                    switch (SyncRandGetRange(0, 5)) {
                    case 0:
                        result = 0;
                        break;
                    case 1:
                        result = 1;
                        break;
                    case 2:
                    case 3:
                        result = 4;
                        break;
                    case 4:
                        result = 6;
                        break;
                    }
                } else {
                    result = SyncRandGetRange(0, 4);
                }
            }
            if ((unsigned int)result <= 1) {
                result = ((p->mMotion.mFacing - p->mUnknown512.mUnknown4) & 0xFFFFFF) <= 0x7FFFFF;
            } else if ((unsigned int)(result - 2) <= 1) {
                result = 2;
                if (((p->mMotion.mFacing - p->mUnknown512.mUnknown4) & 0xFFFFFF) <= 0x7FFFFF) {
                    result = 3;
                }
            }
        } else if (fn_8011F1A4()) {
            result = 4;
        }
    }
    if (result == 8) {
        if (pCarrier) {
            Point_8017886C delta;
            Vec2Sub(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            int angle = delta.Heading();
            int diff;
            if (pCarrier->mpState->mId == 26) {
                Point_8017886C goal;
                goal.mX = fn_8011F4D4();
                Point_8017886C origin = fn_80177FE0();
                goal.mY = origin.mY;
                int target = goal.Heading();
                if (SyncRandGetFloat(0) <= 0.5f) {
                    return 4;
                }
                diff = target - angle;
            } else {
                if (pCarrier->mMotion.mUnknown28 != 0.0f &&
                    MathAngleDiff(p->mMotion.mFacing, heading) <= 0x155554) {
                    heading = pCarrier->mMotion.mUnknown32;
                }
                diff = heading - angle;
            }
            result = (diff & 0xFFFFFF) > 0x800000;
        } else {
            float ratio = (float)pRatings[0] / (float)pRatings[9] * 128.0f;
            if (ratio >= 0.0f) {
                rating = ratio;
                if (rating > 255.0f) {
                    rating = 255.0f;
                }
            } else {
                rating = 0.0f;
            }
            if (rating > 192.0f && SyncRandGetRange(0, 100) > 85) {
                result = SyncRandGetRange(0, 5);
            } else if (rating < 84.0f && SyncRandGetRange(0, 100) > 85) {
                result = 6;
            } else {
                result = SyncRandGetRange(0, 6);
            }
        }
    }
    return result;
}

extern "C" int PlyrEngageCanShed(Object_80039F5C *p, Object_80039F5C *pOther) {
    int result = 1;

    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 25:
    case 26:
    case 27:
    case 34:
    case 35:
    case 36:
    case 43:
        result = 0;
        break;
    case 32:
        if (pOther == 0 || p->mUnknown1032 != 6 || pOther->mUnknown1032 != 6) {
            result = 0;
            break;
        }
    default:
        if (p->mIdBytes[2] != fn_80178320()) {
            result = 0;
        }
        if (fn_800AD9B4() != 3) {
            result = 0;
        }
        if (p->mUnknown1032 != 4 && p->mUnknown1032 != 6) {
            result = 0;
        }
        break;
    }
    return result;
}

extern "C" int *PlyrEngageGetMoveList(int flag, unsigned int index) {
    int *pList;

    if (index <= 6) {
        if (fn_800A8444(fn_80178320()) != 0) {
            pList = _PlyrEngage_aRushMoveLists[index][0];
        } else if (fn_8011F1A4() != 0 || fn_801783AC(0) != 0) {
            if (flag) {
                pList = _PlyrEngage_aRunMoveLists[index][0];
            } else {
                pList = _PlyrEngage_aRunMoveLists[index][1];
            }
        } else if (flag) {
            pList = _PlyrEngage_aPassMoveLists[index][0];
        } else {
            pList = _PlyrEngage_aPassMoveLists[index][1];
        }
    } else {
        pList = _PlyrEngage_aRunMoveLists[4][1];
    }
    return pList;
}

extern "C" {
int PlyrEngageGetInputDir(Object_80039F5C *p)
{
    int direction = 1;

    int angle = (int)(((0x1000000 - (p->mUnknown512.mUnknown4 - p->mMotion.mFacing)) & 0xFFFFFF)
                     * 0.000021457672119140625f);
    if (angle <= 179) {
        angle = angle < 0 ? 0 : angle > 135 ? 135 : angle;
    } else {
        angle = angle < 225 ? 225 : angle > 359 ? 359 : angle;
    }
    if (angle >= 225 && angle <= 247) direction = 16;
    else if (angle >= 248 && angle <= 292) direction = 14;
    else if (angle >= 293 && angle <= 337) direction = 15;
    else if (angle >= 338 && angle <= 358) return 1;
    else if (angle >= 0 && angle <= 22) return 1;
    else if (angle >= 23 && angle <= 67) direction = 4;
    else if (angle >= 68 && angle <= 112) direction = 4;
    else if (angle >= 113 && angle <= 157) direction = 4;
    else if (angle >= 113 && angle <= 135) direction = 4;
    return direction;
}
}

extern "C" void fn_8011E7CC(Object_80039F5C *p, int which, float amount);
extern "C" void fn_8011E884(Object_80039F5C *p, int a);
extern "C" void StyleTrackerBeginDefensiveMove(Object_80039F5C *p, int flag);
extern "C" int fn_8011E88C(Object_80039F5C *p);
extern "C" void fn_800A8954(int event, int team, Object_80039F5C *p);

extern "C" int PlyrEngageTryShed(Object_80039F5C *p, int mode)
{
    Block_8011E240 *pBlock = &p->mBlock1032;
    Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
    if (!PlyrEngageCanShed(p, pOther)) {
        return 0;
    }
    int done = 0;
    int human = 0;
    if (p->mUnknown8 != 255 && (p->mFlags & 0x4000)) {
        human = 1;
    }
    float push = 0.0f;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    Input_800B6D34 input;
    Vector_80039F5C target;
    fn_800B6D34(p, &input);
    if (human == 1 && (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f || (input.mUnknown0 & 0xF))) {

        Point_8017886C dir;
        if (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f) {
            dir.mX = input.mUnknown4;
            dir.mY = input.mUnknown8;
        } else {
            if (input.mUnknown0 & 1) {
                dir.mY = 1.0f;
            }
            if (input.mUnknown0 & 2) {
                dir.mY = -1.0f;
            }
            if (input.mUnknown0 & 4) {
                dir.mX = -1.0f;
            }
            if (input.mUnknown0 & 8) {
                dir.mX = 1.0f;
            }
        }
        Vec2Add(&target, &p->mMotion.mPos, &dir);
    } else if (fn_8011E188() > 30) {
        if (pCarrier) {
            if (pCarrier->mpState->mId == 26) {
                Point_8017886C lead;
                Object_80039F5C *pTarget = PlyrGet(fn_80178308(), pCarrier->mpState->mUnknown1);
                Vec2FromAngle(&lead, pTarget->mMotion.mUnknown32, pTarget->mMotion.mUnknown28 * 60.0f);
                Vec2Add(&target, &pTarget->mMotion.mPos, &lead);
            } else {
                Point_8017886C lead;
                Vec2FromAngle(&lead, pCarrier->mMotion.mUnknown32, pCarrier->mMotion.mUnknown28 * 60.0f);
                Vec2Add(&target, &pCarrier->mMotion.mPos, &lead);
            }
        } else {
            BallGetPosition(BallGetCurrent(), &target);
        }
    } else {
        target.mX = p->mMotion.mPos.mX;
        target.mY = p->mMotion.mPos.mY;
        if (target.mX > 0.0f) {
            target.mX += 1.0f;
            target.mY -= 1.0f;
        } else {
            target.mX -= 1.0f;
            target.mY -= 1.0f;
        }
    }
    target.mZ = 0.0f;
    Vec2Sub(&target, &target, &p->mMotion.mPos);
    p->mUnknown512.mUnknown4 = fn_801CFE40(target.mY, target.mX);
    if (mode == 8) {
        mode = PlyrEngagePickMove(p, pOther, pBlock);
    }
    if (pBlock->mUnknown0 == 4 || pBlock->mUnknown0 == 6) {
        Block_8011E240 *pOtherBlock = &pOther->mBlock1032;
        if (!done && !fn_8011E88C(p)) {
            int won = PlyrEngageAiWinsShed(p, pOther, (Record_800E5EA4 *)((char *)pBlock + 40),
                                  (Record_800E5EA4 *)&pOther->mUnknown1072, mode);
            done = PlyrEngageTryAnims(pOther, p, PlyrEngageGetMoveList(won, mode));
            if (!done) {
                push = won ? 0.075f : -0.075f;
                if (human) {
                    push += push;
                }
                float pull;
                if ((unsigned int)mode <= 5) {
                    fn_8011E7CC(p, 1, push);
                    fn_8011E7CC(pOther, 1, pull = -push);
                } else {
                    fn_8011E7CC(p, 0, push);
                    fn_8011E7CC(pOther, 0, pull = -push);
                }
                fn_8011E7CC(p, 2, push);
                fn_8011E7CC(pOther, 2, pull);
                if (human) {
                    fn_8011E884(p, 15);
                    fn_8011E884(pOther, 15);
                } else {
                    fn_8011E884(p, 30);
                    fn_8011E884(pOther, 30);
                }
                pOtherBlock->mUnknown94 = 1;
            } else {
                fn_800A8954(10, p->mIdBytes[2], p);
                AudmonEventPostArgs(96, &p->mMotion.mPos, mode, 0, 0);
                StyleTrackerBeginDefensiveMove(p, won);
            }
        }
    }
    return done;
}

extern "C" {
int PlyrWaitEnter(Object_80039F5C *p)
{
    int *pTimer = &p->mUnknown336;
    int value = p->mpState->mUnknown1;
    int seconds = value >> 5;
    unsigned int frames = (unsigned int)(60.0f / gFrameTimeScale);
    float fraction = (value & 31) / 31.0f;
    *pTimer = seconds * frames + (int)(fraction * 60.0f);
    if (!fn_800B146C()) {
        p->mUnknown512.mUnknown0 = 0.0f;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown14 = 1;
    }
    return 0;
}
}

extern "C" {
int PlyrWaitUpdate(Object_80039F5C *p)
{
    Object_80039F5C *carrier = BallGetCurrentHolder();
    int *pTimer = &p->mUnknown336;
    Message_800F01CC message;
    if (p->mIdBytes[3] == 1 && p->mUnknown1032 == 4) return 1;
    Ball_t *ball = BallGetCurrent();
    if (BallStateGet(ball, 0) == 4 && p == BallGetTarget(ball)) {
        memset(&message, 0, 4);
        message.mId = 23;
        message.mUnknown1[0] = BallGetIndex(ball);
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (!fn_801787A0() && BallGetCurrentHolder() && fn_801783AC(0) &&
        fn_801486A0() != 0 && fn_801486A0() != 1 && fn_801486A0() != 2) {
        memset(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if ((p->mFlags & 0x4000) && fn_801486A0()) return 1;
    (*pTimer)--;
    if (carrier && !((float)fn_8011E188() <= _PlyrWait_fBlockTime) && !fn_801787A0() &&
        !(p->mMotion.mUnknown28 >= 0.1f)) {
        int heading;
        if (fn_801486A0() != 1) {
            Vector_80039F5C delta;
            Vec2Sub(&delta, &carrier->mMotion.mPos, &p->mMotion.mPos);
            heading = fn_801CFE40(delta.mY, delta.mX);
        } else {
            heading = p->mUnknown2913 ? 0x800000 : 0;
        }
        if (MathAngleDiff(p->mMotion.mFacing, heading) > 0x38E38) {
            if (((p->mMotion.mFacing - heading) & 0xFFFFFF) > 0x800000)
                p->mMotion.mFacing += 0x38E38;
            else p->mMotion.mFacing -= 0x38E38;
        } else p->mMotion.mFacing = heading;
    }
    if (*pTimer < 0) return 1;

    if (fn_801486A0() == 0) {
        p->mUnknown512.mUnknown0 = 0.0f;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        unsigned short count = fn_80178D70(0);
        for (unsigned short i = 0; i < count; i++) {
            if (PlyrGet(0, i)->mpState->mId == 97) return 1;
        }
    }
    return 0;
}
}

extern "C" int PlyrWaitInput(Object_80039F5C *p) {
    if (fn_800AD9B4() != 2) {
        if (fn_80177F70() != 0) {
            if (fn_800B5FEC(p) != 0 && fn_800C05F4() == 0 && fn_801486A0() != 0) {
                fn_800B76E8(p);
            }
        } else if (p->mUnknown2914 != 19 && p->mUnknown2914 != 20 && p->mUnknown2914 != 23) {
            fn_800B7F34(p);
            p->mFlags &= ~0x4000;
        }
    }
    return 0;
}

extern "C" int PlyrTackleIsShallowPath(Object_80039F5C *p)
{
    int result = 0;
    Record_800EA284 *pRecord = p->mpUnknown3092->mpUnknown32;
    float distance = Vec2Distance(&pRecord->mUnknown32, &pRecord->mUnknown16);
    if (distance > 0.0f) {
        result = fn_801CFE08(fabsf(pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ) / distance) <= 0x155555;
    }
    return result;
}

extern "C" int PlyrTackleCanReach(Object_80039F5C *p)
{
    int result = 1;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    if (pCarrier) {
        Point_8017886C delta;
        Vec2Sub(&delta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
        float distance = Vec2Magnitude(&delta);
        int difference = MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing);
        if (fn_8011F1CC() && pCarrier->mMotion.mPos.mY < fn_80177FE0().mY) {
            int id = fn_800F06F4(0, pCarrier->mpState, 18, 0xFFFF);
            if (id != 0xFFFF || fn_800F06F4(0, pCarrier->mpState, 15, 0xFFFF) != id) {
                if (difference > (int)(_PlyrTackle_fReachAngle * 46603.3789f) || distance > _PlyrTackle_fReachDistance) {
                    result = 0;
                }
            }
        }
    } else {
        result = 0;
    }
    return result;
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern "C" void PlyrTackleStartAnim(Object_80039F5C *p, Block_800E7588 *pBlock)
{
    AudmonEventPostId(97, &p->mMotion.mPos, p->mId, p->mpState->mId, 0, 0);
    fn_800A8954(4, p->mIdBytes[2], p);
    fn_8009BD60(p);
    switch (pBlock->mUnknown5) {
    case 0:
        p->mUnknown1008.mUnknown0 = p == BallGetCurrentHolder() ? 1 : 2;
        p->mUnknown1008.mUnknown2 = 1;
        p->mUnknown1011 = pBlock->mUnknown9;
        switch (pBlock->mUnknown8) {
        case 1:
            p->mUnknown1008.mUnknown1 = 3;
            break;
        case 2:
            p->mUnknown1008.mUnknown1 = 2;
            break;
        case 3:
            p->mUnknown1008.mUnknown1 = 1;
            break;
        }
        break;
    case 3:
        p->mUnknown1008.mUnknown0 = 2;
        p->mUnknown1008.mUnknown2 = 4;
        p->mUnknown1011 = pBlock->mUnknown9;
        if (pBlock->mUnknown8 == 1) {
            p->mUnknown1008.mUnknown1 = 3;
        }
        break;
    case 1: {
        float x = fabsf(p->mMotion.mPos.mX);
        p->mUnknown1008.mUnknown0 = 1;
        p->mUnknown1008.mUnknown1 = 2;
        p->mUnknown1011 = 1;
        p->mUnknown1008.mUnknown2 = 2;
        if (x > fn_80178A08() - 3.0f && p->mMotion.mPos.mY > fn_80178A2C() - 7.0f && !PlayerMoveGetKind(p)) {
            if (p->mMotion.mPos.mX < 0.0f) {
                if ((unsigned int)(p->mMotion.mFacing - 0x400000 - 1) <= 0x3FFFFE) {
                    if (p->mUnknown776 == 2) {
                        p->mUnknown1008.mUnknown2 = 6;
                    } else {
                        p->mUnknown1008.mUnknown2 = 7;
                    }
                }
            } else if ((unsigned int)(p->mMotion.mFacing - 1) <= 0x3FFFFE) {
                if (p->mUnknown776 == 2) {
                    p->mUnknown1008.mUnknown2 = 7;
                } else {
                    p->mUnknown1008.mUnknown2 = 6;
                }
            }
        }
        if (p->mUnknown1008.mUnknown2 == 2) {
            unsigned int count = fn_80178D18(fn_80178320());
            int left = 1;
            int right = 1;
            int ahead = 1;
            for (unsigned int i = 0; i < count && (left || right); i++) {
                Object_80039F5C *pOther = PlyrGet(fn_80178320(), i);
                if (pOther) {
                    if (pOther->mMotion.mPos.mY > p->mMotion.mPos.mY) {
                        Point_8017886C delta;
                        Vec2Sub(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
                        int angle = (delta.Heading() - 0x800000) & 0xFFFFFF;
                        int facing = p->mMotion.mFacing;
                        int unused = delta.Heading();
                        if (Vec2Magnitude(&delta) < 4.0f) {
                            if (angle > ((facing - 0x155555) & 0xFFFFFF) && angle < ((facing + 0x155555) & 0xFFFFFF)) {
                                if (left && angle + 0x38E38 >= facing + 0x155555 && angle - 0x38E38 <= facing + 0x155555) {
                                    left = 0;
                                } else if (right && angle + 0x38E38 >= facing - 0x155555 &&
                                           angle - 0x38E38 <= facing - 0x155555) {
                                    right = 0;
                                } else if (ahead && angle + 0x71C71 >= facing && angle - 0x71C71 <= facing) {
                                    ahead = 0;
                                }
                            }
                        }
                    }
                } else {
                    left = 0;
                    right = 0;
                    ahead = 1;
                }
            }
            float edge = MIN(p->mMotion.mPos.mX - 4.0f, -fn_80178A08());
            if (PlayerMoveGetKind(p)) {
                p->mUnknown1011 = p->mpState->mUnknown3[0];
            }
        } else if (PlayerMoveGetKind(p)) {
            if (p->mUnknown1008.mUnknown2 == 6) {
                p->mUnknown1011 = 4;
            } else {
                p->mUnknown1011 = 5;
            }
        }
        pBlock->mUnknown10 = 1;
        break;
    }
    case 2:
        p->mUnknown1008.mUnknown0 = 1;
        p->mUnknown1008.mUnknown1 = 1;
        p->mUnknown1008.mUnknown2 = 3;
        p->mUnknown1011 = 1;
        pBlock->mUnknown10 = 1;
        break;
    case 4: {
        Vector_80039F5C velocity;
        p->mUnknown1008.mUnknown0 = 2;
        p->mUnknown1008.mUnknown2 = 5;
        p->mUnknown1008.mUnknown1 = 2;
        BallGetVelocity(BallGetCurrent(), &velocity);
        int heading = fn_801CFE40(velocity.mY, velocity.mX);
        p->mUnknown1011 = _PlyrTackle_aAnimOctants[(((heading - p->mMotion.mFacing) & 0xFFFFFF) + 0x100000) >> 21 & 7];
        break;
    }
    }
    if (pBlock->mUnknown5 == 3) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 207, 1.0f, p);
    } else if (PlayerMoveGetKind(p)) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 192, 1.0f, p);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 70, 1.0f, p);
    }
    if (p->mUnknown776 == 1 &&
        (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 70) ||
         AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 192) ||
         AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 207))) {
        AnimChannel_t *pChannels = p->mpUnknown800;
        int index;
        if (pBlock->mUnknown5 == 3) {
            index = AnimChanGetStateChannelByIndex(p->mpUnknown796, pChannels, 207, 0);
        } else if (PlayerMoveGetKind(p)) {
            index = AnimChanGetStateChannelByIndex(p->mpUnknown796, pChannels, 192, 0);
        } else {
            index = AnimChanGetStateChannelByIndex(p->mpUnknown796, pChannels, 70, 0);
        }
        AnimChannel_t *pChannel = &pChannels[index];
        AnimChanSetMirrored(pChannel, !AnimChanIsMirrored(pChannel));
    }
    if (PlayerMoveGetKind(p)) {
        PlayerMoveSetResult(p, p->mUnknown1011);
    } else {
        PlayerMoveSetResult(p, 0);
    }
    p->mUnknown512.mUnknown14 = 0;
}

extern "C" void PlyrTackleStartMove(Object_80039F5C *p, Block_800E7588 *pBlock) {
    unsigned char saved = p->mUnknown1008.mUnknown0;
    Command_800CEE74 command;
    int value;
    int unused;
    int flag;
    int index;

    if (fn_800B83A0(p) != 0) {
        p->mUnknown1008.mUnknown0 = 1;
        pBlock->mUnknown19 = 1;
    } else {
        p->mUnknown1008.mUnknown0 = 2;
    }
    flag = p->mUnknown776 == 1;
    fn_800CEE74(&command, p, 0, 0, 0, 237, flag);
    index = fn_800C3BEC(p, &command, &value, &unused);
    if (index != -1) {
        fn_800C39E0(p, 237, index, value, flag);
        PlayerMoveSetResult(p, 0);
        p->mFlags |= 8;
    } else {
        p->mUnknown1008.mUnknown0 = saved;
        PlayerMoveBegin(p, 1, 12);
        PlyrTackleStartAnim(p, pBlock);
    }
}

extern "C" int PlyrTackleCanStart(Object_80039F5C *p) {
    int result = 1;

    switch (p->mpState->mId) {
    case 32:
        if (fn_801BE648(p->mpUnknown792) != 242 || p->mIdBytes[2] != fn_80178320()) {
            result = 0;
        }
        break;
    case 36:
        break;
    default:
        result = p->mUnknown1032 != 4;
        if (fn_801787A0() != 0) {
            result = 0;
        }
        break;
    case 5:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 25:
    case 26:
    case 27:
    case 34:
    case 35:
    case 43:
        result = 0;
        break;
    }
    if (fn_8011E188() <= 30) {
        result = 0;
    }
    return result;
}

extern "C" int PlayerIsFreeOfBall(Object_80039F5C *p) {
    int result = 1;
    Ball_t *pBall = BallGetCurrent();

    if (p != 0 && pBall != 0) {
        if (BallStateGet(pBall, 0) == 4) {
            Vector_80039F5C pos;
            int ok;

            BallGetPosition(pBall, &pos);
            ok = 0;
            if (pos.mY <= fn_80177FE0().mY) {
                ok = !fn_801783AC(11);
            }
            if (ok && p->mIdBytes[3] == 1) {
                switch (p->mUnknown2914) {
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18: {
                    Point_8017886C delta;

                    Vec2Sub(&delta, &p->mMotion, &pos);
                    Vec2Magnitude(&delta);
                    break;
                }
                }
            }
        } else if (p == BallGetCurrentHolder() && fn_801486A0() == 0) {
            result = 0;
        }
    }
    return result;
}

extern "C" {
void PlyrTackleAimAtCarrier(Object_80039F5C *p, State_800D7A4C *state)
{
    if (state->mUnknown5 != 3) return;
    Vector_80039F5C point;
    Object_80039F5C *carrier = BallGetCurrentHolder();
    if (carrier) {
        point.mX = carrier->mMotion.mPos.mX;
        point.mY = carrier->mMotion.mPos.mY;
        float distance = Vec2Distance(&carrier->mMotion.mPos, &p->mMotion.mPos);
        if (!(distance <= 10.0f)) distance = 10.0f;
        float rate = _PlyrTackle_uAimRate * 0.1f;
        float scale = distance * rate;
        point.mX += carrier->mMotion.mUnknown40 * scale;
        point.mY += carrier->mMotion.mUnknown44 * scale;
    } else BallGetPosition(BallGetCurrent(), &point);
    Vector_80039F5C delta;
    Vec2Sub(&delta, &point, &p->mMotion.mPos);
    int heading = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    int limit = fn_800ACD04(p);
    if (!(point.mY >= fn_80177FE0().mY) && !fn_801783AC(0)) limit *= (int)_PlyrTackle_fBehindLineScale;

    int step;
    if (MathAngleDiff(heading, p->mMotion.mFacing) <= limit)
        step = MathAngleDiff(heading, p->mMotion.mFacing);
    else step = limit;
    int facing;
    if (((heading - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000)
        facing = p->mMotion.mFacing - step;
    else facing = p->mMotion.mFacing + step;
    facing &= 0xFFFFFF;
    int remaining = (heading - facing) & 0xFFFFFF;
    p->mUnknown512.mUnknown4 = facing;
    p->mUnknown512.mUnknown0 = 1.0f;
    p->mUnknown512.mUnknown14 = 6;
    p->mUnknown512.mUnknown8 = facing;
    state->mUnknown9 = _PlyrTackle_aAimOctants[((remaining + 0x100000) >> 21) & 7];
    if (p->mIdBytes[2] == fn_80178320()) {
        if (state->mUnknown9 == 2) state->mUnknown9 = 3;
        else if (state->mUnknown9 == 7) state->mUnknown9 = 6;
    }
}
}

extern "C" int PlyrTackleAiTry(Object_80039F5C *p, void *pArg)
{
    int result = 0;
    if (PlyrTackleCanStart(p) == 1) {
        Object_80039F5C *pCarrier = BallGetCurrentHolder();
        if (pCarrier && pCarrier->mpState->mId == 1) {
            Point_8017886C delta;
            Vec2Sub(&delta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
            if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing) <= 0x3FFFFF &&
                Vec2Magnitude(&delta) < 10.0f) {
                result = PlyrTackleStart(p, (int)pArg, 0);
            }
        }
    }
    return result;
}

extern "C" {
int PlyrTackleStart(Object_80039F5C *p, int unused, int mode)
{
    if (!PlyrTackleCanStart(p) || !PlayerIsFreeOfBall(p)) return 0;
    Message_800F01CC message;
    memset(&message, 0, 4);
    message.mId = 12;
    Object_80039F5C *carrier = BallGetCurrentHolder();
    unsigned char choice;
    unsigned char kind;
    if (p == carrier) {
        float distance = fn_80178298() - p->mMotion.mPos.mY;
        choice = 2;
        kind = 1;
        if (distance <= 0.0f || !(distance < 4.0f)) fn_80178A2C();
        int team = fn_80178320();
        unsigned char count = fn_80178D18(fn_80178320());
        float range;
        Object_80039F5C *other = fn_801245DC(p, team, 0, count, 0x18E38E, &range, 0);
        if (other && !(range >= 3.0f) && (other->mFlags & 0x800)) kind = 2;
    } else if (carrier && p->mIdBytes[2] == fn_80178320()) {
        Vector_80039F5C delta;
        Vec2Sub(&delta, &carrier->mMotion.mPos, &p->mMotion.mPos);
        kind = 3;
        choice = 1;
        int heading = fn_801CFE40(delta.mY, delta.mX);
        if (MathAngleDiff(heading, p->mMotion.mFacing) <= 0x3FFFFF) Vec2Magnitude(&delta);
    } else {
        Vector_80039F5C point;
        BallGetLandingPoint(BallGetCurrent(), &point);
        Vector_80039F5C delta;
        Vec2Sub(&delta, &point, &p->mMotion.mPos);
        if (!(Vec2Magnitude(&delta) >= 8.0f) && BallStateGet(BallGetCurrent(), 0) == 4) {
            Vector_80039F5C spot = p->mMotion.mPos;
            spot.mZ = (float)p->mMotion.mUnknown32;
        }
        choice = 2;
        kind = 4;
    }
    if (choice == 0) choice = SyncRandGetRange(0, 3) + 1;
    PlayerMoveBegin(p, mode, 12);
    message.mUnknown1[0] = kind;
    message.mUnknown1[1] = choice;
    message.mUnknown1[2] = mode == 0 ? 0 : _PlyrTackle_aButtonKinds[SyncRandGetRange(0, 5)];
    fn_800F00D4(0, p->mpState, &message, p);
    return 1;
}
}

extern "C" int PlyrTackleEnter(Object_80039F5C *p)
{
    State_800E8420 *pState = (State_800E8420 *)&p->mUnknown336;
    int mode = PlayerMoveGetKind(p);
    Input_800B6D34 input;

    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    pState->mUnknown11 = PlyrTackleCanReach(p);
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
    PlyrTackleAimAtCarrier(p, (State_800D7A4C *)pState);
    pState->mUnknown4 = 0;
    if (mode == 4) {
        PlyrTackleStartMove(p, (Block_800E7588 *)pState);
    } else {
        PlyrTackleStartAnim(p, (Block_800E7588 *)pState);
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

extern "C" int PlyrTackleUpdate(Object_80039F5C *p)
{
    State_800E8420 *pState = (State_800E8420 *)&p->mUnknown336;

    if (pState->mUnknown4 == 0) {
        if (pState->mUnknown18 == 0) {
            pState->mUnknown18 = PlyrTackleIsShallowPath(p);
        }
        if (pState->mUnknown10 && !(p->mFlags & 0x800) && p == BallGetCurrentHolder() && p->mUnknown560.mFlags.mBytes[0]) {
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
                    PossTryFumble(p, pOther);
                    pState->mUnknown10 = 0;
                    break;
                }
            }
        }
        if (pState->mUnknown17 == 0) {
            pState->mUnknown17 = PlyrTackleContest(p, (Object_80039F5C **)pState->mUnknown12);
        }
        if (p->mUnknown9[0] != 1 && (p->mFlags & 0x800)) {
            Message_800F01CC message;
            memset(&message, 0, 4);
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

extern "C" int PlyrTackleExit(Object_80039F5C *p) {
    if (p->mUnknown354 == 0 && p->mIdBytes[2] == fn_80178320()) {
        p->mFlags &= ~8;
        return 1;
    }
    return 0;
}

extern "C" int PlyrTackleNotify() {
    return 0;
}

extern "C" int PlyrTackleInput(Object_80039F5C *p) {
    int done = 0;
    Block_800E7588 *pBlock = (Block_800E7588 *)&p->mUnknown336;

    if (pBlock->mUnknown4 == 1) {
        pBlock->mUnknown6++;
        if (PlayerMoveGetKind(p) != 0) {
            Input_800B6D34 input;

            fn_800B6D34(p, &input);
            if (input.mBytes92[5] & 0x40) {
                done = 1;
                p->mpState->mUnknown3[0] = _PlyrTackle_aButtonKinds[1];
            } else if (input.mBytes92[5] & 0x80) {
                done = 1;
                p->mpState->mUnknown3[0] = _PlyrTackle_aButtonKinds[2];
            } else if (input.mBytes92[6] & 1) {
                done = 1;
                p->mpState->mUnknown3[0] = _PlyrTackle_aButtonKinds[3];
            } else if (input.mBytes92[6] & 2) {
                done = 1;
                p->mpState->mUnknown3[0] = _PlyrTackle_aButtonKinds[4];
            } else if (pBlock->mUnknown6 >= _PlyrTackle_iInputFrames) {
                done = 1;
            }
        } else {
            done = 1;
        }
        if (done) {
            pBlock->mUnknown4 = 0;
            PlyrTackleStartAnim(p, pBlock);
        }
    }
    fn_800B7F88(p);
    return 0;
}

extern "C" int PlyrTackleRollKind(void) {
    return SyncRandGetRange(0, 100) >= _PlyrTackle_uKindChance ? 4 : 0;
}

extern "C" int PlyrTackleContest(Object_80039F5C *p, Object_80039F5C **ppLast) {
    int result = 0;
    if (p->mUnknown560.mFlags.mBytes[0]) {
        switch (p->mUnknown560.mUnknown54) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4: {
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
            if (!pOther)
                pOther = fn_8009BCE8(&p->mUnknown560.mUnknown44);
            if (pOther && pOther != BallGetCurrentHolder() && pOther != *ppLast) {
                *ppLast = pOther;
                switch (pOther->mUnknown560.mUnknown54) {
                case 0:
                case 1:
                case 3:
                case 5:
                case 7:
                    switch (pOther->mpState->mId) {
                    case 5:
                    case 10:
                    case 12:
                    case 16:
                    case 17:
                    case 58:
                        break;
                    case 32: {
                        Object_80039F5C *pTarget = fn_8009BCE8(&pOther->mUnknown336);
                        if (pTarget && pTarget->mpState->mId == 32) {
                            PlyrContactCollide(pOther, p);
                            result = 1;
                        }
                        break;
                    }
                    default: {
                        short rollBase = (short)p->mUnknown2904Float;
                        short rating = p->mRatings[5];
                        short ratingMax = pOther->mRatings[2] >= pOther->mRatings[0] ? pOther->mRatings[2] : pOther->mRatings[0];
                        short otherRollBase = (short)pOther->mUnknown2904Float;
                        short otherLimit = (short)(ratingMax * _PlyrTackle_fOtherRatingScale + otherRollBase * _PlyrTackle_fOtherRollScale);
                        short limit = (short)(rating * _PlyrTackle_fRatingScale + rollBase * _PlyrTackle_fRollScale);
                        short roll = SyncRandGetRange(0, limit);
                        short otherRoll = SyncRandGetRange(0, otherLimit);
                        if (pOther->mMotion.mPos.mY < fn_80177FE0().mY)
                            roll = (short)(roll * _PlyrTackle_fRollDamp);
                        if (roll > otherRoll) {
                            if (roll * _PlyrTackle_fWinMargin > otherRoll) {
                                PlyrContactSendPush(pOther, p);
                                result = 1;
                            } else {
                                result = 1;
                                PlyrContactSendKnock(pOther);
                            }
                        }
                        break;
                    }
                    }
                    break;
                }
            }
            break;
        }
        }
    } else {
        *ppLast = 0;
    }
    return result;
}

extern "C" int PlyrTurnEnter(Object_80039F5C *p) {
    State_800E8BE8 *state = (State_800E8BE8 *)&p->mUnknown336;
    float limit;
    int far;
    state->mUnknown0 = p->mpState->mUnknown1 << 16;
    if (p->mIdBytes[2] == fn_80178308())
        limit = 3.0f;
    else
        limit = 2.0f;
    unsigned int scale = p->mpState->mUnknown3[0];
    if (scale == 0)
        state->mUnknown4 = 1.0f;
    else
        state->mUnknown4 = scale * 0.1f;
    far = !(p->mpState->mUnknown2 != 0 && fn_80177F70() != 0 &&
            fabsf(fn_80177FFC(p->mIdBytes[2]).mY - p->mMotion.mPos.mY) <= limit &&
            fabsf(fn_80177FFC(p->mIdBytes[2]).mX - p->mMotion.mPos.mX) <= 6.0f);
    if (far)
        state->mUnknown9 = 1;
    else
        state->mUnknown9 = 0;
    if (MathAngleDiff(p->mMotion.mFacing, state->mUnknown0) <= 0x71C70) {
        if (p->mFlags & 0x40000)
            return 1;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = state->mUnknown0;
        p->mUnknown512.mUnknown8 = state->mUnknown0;
        p->mUnknown512.mUnknown0 = 0.0f;
        state->mUnknown8 = 0;
    } else {
        if (state->mUnknown9)
            p->mUnknown512.mUnknown14 = 6;
        else
            p->mUnknown512.mUnknown14 = 7;
        p->mUnknown512.mUnknown4 = state->mUnknown0;
        p->mUnknown512.mUnknown8 = state->mUnknown0;
        p->mUnknown512.mUnknown0 = state->mUnknown4;
        p->mFlags &= ~4;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 100, 1.0f, p);
        state->mUnknown8 = 1;
    }
    p->mFlags &= ~0x40000;
    return 0;
}

extern "C" int PlyrTurnUpdate(Object_80039F5C *p) {
    State_800E8BE8 *state = (State_800E8BE8 *)&p->mUnknown336;
    unsigned int flags = p->mFlags;
    p->mFlags = flags & ~0x40000;
    if (p->mFlags & 0x4000)
        return 1;
    if (state->mUnknown8) {
        if (flags & 4) {
            p->mFlags &= ~4;
            state->mUnknown8 = 0;

            p->mUnknown512.mUnknown0 = 0.0f;
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown8 = state->mUnknown0;
            p->mUnknown512.mUnknown4 = state->mUnknown0;
        } else if (state->mUnknown9) {
            p->mUnknown512.mUnknown14 = 6;
            p->mUnknown512.mUnknown0 = 1.0f;
            p->mUnknown512.mUnknown8 = state->mUnknown0;
            p->mUnknown512.mUnknown4 = state->mUnknown0;
        } else {
            p->mUnknown512.mUnknown14 = 7;
            p->mUnknown512.mUnknown0 = 1.0f;
            p->mUnknown512.mUnknown8 = state->mUnknown0;
            p->mUnknown512.mUnknown4 = state->mUnknown0;
        }
    } else {
        if (p->mMotion.mFacing == state->mUnknown0)
            return 1;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown0 = 0.0f;
        p->mUnknown512.mUnknown8 = state->mUnknown0;
        p->mUnknown512.mUnknown4 = state->mUnknown0;
    }
    return 0;
}

extern "C" int PlyrContactIsActionAnim(int value) {
    switch (value) {
    case 25:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 66:
    case 79:
    case 93:
    case 94:
    case 95:
    case 96:
    case 106:
    case 107:
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
    case 164:
    case 172:
    case 173:
    case 174:
    case 175:
    case 181:
    case 182:
    case 183:
    case 184:
    case 186:
    case 211:
    case 231:
    case 233:
    case 234:
    case 238:
    case 241:
    case 242:
    case 247:
        return 1;
    }
    return 0;
}

extern "C" unsigned char PlyrContactGetSide(int angle, int difference) {
    return _PlyrContact_aSideOctants[((angle + 0x100000) >> 21) & 7];
}

extern "C" void PlyrContactSendHit(Object_80039F5C *p, int id) {
    if (PlyrContactCanReact(p)) {
        int heading = p->mMotion.mUnknown32;
        Message_800F01CC message;
        int difference;
        int relative;
        memset(&message, 0, 4);
        message.mId = id;
        message.mUnknown1[1] = 8;
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
        if (pOther) {
            Point_8017886C delta;
            Vec2Sub(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            difference = MathAngleDiff(p->mMotion.mFacing, angle);
            angle = (angle - p->mMotion.mFacing) & 0xFFFFFF;
            if (BallFindHeldBy(p) && p->mUnknown776 == 1)
                angle = 0x1000000 - angle;
            if (id == 58 && BallGetCurrentHolder() == p)
                message.mUnknown1[1] = _PlyrContact_aSideOctants[((angle + 0x100000) >> 21) & 7];
            else
                message.mUnknown1[1] = PlyrContactGetSide(angle, difference);
        }
        difference = MathAngleDiff(p->mMotion.mFacing, heading);
        relative = (heading - p->mMotion.mFacing) & 0xFFFFFF;
        if (BallFindHeldBy(p) && p->mUnknown776 == 1)
            relative = 0x1000000 - relative;
        int octant = ((relative + 0x100000) >> 21) & 7;
        message.mUnknown1[0] = PlyrContactGetSide(relative, difference) | _PlyrContact_aDirOctants[octant] << 4;
        message.mUnknown1[2] = PlyrContactPickHeight(p);
        if (p == BallGetCurrentHolder()) {
            if (id == 58 && message.mUnknown1[1] != 8) {
                // FAKEMATCH: the target loads the byte as li r0,-0x78 (0x800E91AC); a direct
                // constant store compiles to li r0,0x88, the int temporary to -0x78. Same byte stored.
                int neutral = 0x88;
                message.mUnknown1[0] = neutral;
            }
            int previous = fn_800F06F4(0, p->mpState, 18, 0xFFFF);
            fn_800EFE60(0, p->mpState, p);
            fn_800F053C(0, p->mpState, &message, p);
            p->mFlags &= ~0x2000;
            p->mFlags &= ~0x8;
            fn_800CE674(&p->mUnknown1240);
            fn_800CE684(&p->mUnknown1240);
            if (previous == 0xFFFF) {
                memset(&message, 0, 4);
                message.mId = 1;
                fn_800F03D8(0, p->mpState, &message, p);
            } else {
                memset(&message, 0, 4);
                message.mId = 18;
                fn_800F03D8(0, p->mpState, &message, p);
            }
        } else {
            switch (p->mpState->mId) {
            case 57:
            case 94:
                break;
            case 25:
            case 26:
                fn_800F05E4(0, p->mpState, &message, p);
                break;
            default:
                fn_800F00D4(0, p->mpState, &message, p);
                break;
            }
        }
    }
}

extern "C" int PlyrContactCanReact(Object_80039F5C *p) {
    int result;
    if (p->mFlags & 0x800)
        result = 0;
    else
        result = 1;
    switch (p->mpState->mId) {
    case 10:
    case 11:
    case 17:
    case 32:
    case 94:
        result = 0;
        break;
    case 28: {
        int unknown;
        int handle;
        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        if (fn_8009A578(handle) == 5 || fn_8009A578(handle) == 4)
            result = 0;
        break;
    }
    case 16:
        result = 0;
        if (p == BallGetCurrentHolder() && (p->mFlags & 0x80000))
            result = 1;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" int PlyrContactCanBeHit(Object_80039F5C *p) {
    int result = 1;
    switch (p->mpState->mId) {
    case 10:
    case 50:
    case 94:
        result = 0;
        break;
    case 28: {
        int unknown;
        int handle;
        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        if (fn_8009A578(handle) == 5)
            result = 0;
        if ((handle >> 29 & 3) == 1)
            result = 0;
        break;
    }
    case 16:
    case 17:
    case 32:
        result = 1;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" int PlyrContactPickHeight(Object_80039F5C *p) {
    if (p->mUnknown560.mFlags.mBytes[0]) {
        if (p->mContact560.mUnknown56.mZ >= 0.5f)
            return 1;
        return 3;
    }
    switch (SyncRandGetRange(0, 3)) {
    case 0:
        return 2;
    case 1:
        return 3;
    case 2:
        return 1;
    }
    return 2;
}

extern "C" void PlyrContactSendCarrierHit(Object_80039F5C *p) {
    PlyrContactSendHit(p, 10);
}

extern "C" void PlyrContactSendKnock(Object_80039F5C *p) {
    PlyrContactSendHit(p, 58);
}

extern "C" void PlyrContactSendHitFrom(Object_80039F5C *p, int id, int *pAngle, int value, int *pHeading) {
    if (PlyrContactCanBeHit(p)) {
        int heading = p->mMotion.mUnknown32;
        Message_800F01CC message;
        int difference;
        memset(&message, 0, 4);
        message.mId = id;
        message.mUnknown1[1] = _PlyrContact_aSideOctants[((((*pAngle - p->mMotion.mFacing) & 0xFFFFFF) + 0x100000) >> 21) & 7];
        if (pHeading) {
            heading = *pHeading;
            difference = MathAngleDiff(p->mMotion.mFacing, heading);
            message.mUnknown1[0] = PlyrContactGetSide(heading, difference);
        } else {
            heading = (heading - p->mMotion.mFacing) & 0xFFFFFF;
            difference = MathAngleDiff(p->mMotion.mFacing, heading);
            if (BallFindHeldBy(p) && p->mUnknown776 == 1)
                heading = 0x1000000 - heading;
            message.mUnknown1[0] = PlyrContactGetSide(heading, difference);
        }

        message.mUnknown1[0] |= _PlyrContact_aDirOctants[((heading + 0x100000) >> 21) & 7] << 4;
        message.mUnknown1[2] = value;
        switch (p->mpState->mId) {
        case 16:
            ((State_800E954C *)&p->mUnknown336)->mUnknown31 = 1;
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        case 17:
            ((State_800E954C *)&p->mUnknown336)->mUnknown15 = 1;
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        case 32:
            ((State_800E954C *)&p->mUnknown336)->mUnknown8 = 1;
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        case 34:
        case 35:
        case 36:
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        default:
            fn_800F00D4(0, p->mpState, &message, p);
            break;
        }
    }
}

extern "C" int PlyrContactSendPush(Object_80039F5C *p, Object_80039F5C *pOther) {
    if (PlyrContactCanReact(p)) {
        Message_800F01CC message;
        Point_8017886C delta;
        Object_800B26B0 *pOtherMotion = &pOther->mMotion;
        Object_800B26B0 *pMotion = &p->mMotion;
        Vec2Sub(&delta, &pOtherMotion->mPos, &pMotion->mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        int away = (angle - 0x800000) & 0xFFFFFF;
        int difference = MathAngleDiff(pOtherMotion->mUnknown32, away) * 2 / 3;
        if (((away - pOtherMotion->mUnknown32) & 0xFFFFFF) > 0x800000)
            away = (away + difference) & 0xFFFFFF;
        else
            away = (away - difference) & 0xFFFFFF;
        difference = MathAngleDiff(pMotion->mFacing, angle);
        angle = (angle - pMotion->mFacing) & 0xFFFFFF;
        memset(&message, 0, 4);
        message.mId = 10;
        message.mUnknown1[1] = PlyrContactGetSide(angle, difference);
        difference = MathAngleDiff(pMotion->mFacing, away);
        away = (away - pMotion->mFacing) & 0xFFFFFF;
        int octant = ((away + 0x100000) >> 21) & 7;
        message.mUnknown1[0] = PlyrContactGetSide(away, difference) | _PlyrContact_aDirOctants[octant] << 4;
        message.mUnknown1[2] = PlyrContactPickHeight(p);
        if (p->mpState->mId == 31) {
            if (fn_8011E9D8(p->mpState))
                fn_800F05E4(0, p->mpState, &message, p);
            else
                fn_800F00D4(0, p->mpState, &message, p);
        } else {
            fn_800F00D4(0, p->mpState, &message, p);
        }
        return 1;
    }
    return 0;
}

extern "C" int PlyrContactSendBump(Object_80039F5C *p, Object_80039F5C *pOther) {
    Message_800F01CC message;
    Point_8017886C delta;
    Object_800B26B0 *pMotion = &p->mMotion;
    Vec2Sub(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    int away = (angle - 0x800000) & 0xFFFFFF;
    int difference = MathAngleDiff(angle, away);
    memset(&message, 0, 4);
    message.mId = 10;
    message.mUnknown1[1] = PlyrContactGetSide(angle, difference);
    difference = MathAngleDiff(pMotion->mFacing, away);
    away = (away - pMotion->mFacing) & 0xFFFFFF;
    int octant = ((away + 0x100000) >> 21) & 7;
    message.mUnknown1[0] = PlyrContactGetSide(away, difference) | _PlyrContact_aDirOctants[octant] << 4;
    message.mUnknown1[2] = PlyrContactPickHeight(p);
    fn_800F00D4(0, p->mpState, &message, p);
    return p->mpState->mId == 10;
}

extern "C" void PlyrContactSendStumble(Object_80039F5C *p, int kind) {
    if (PlyrContactCanReact(p) && !fn_801787A0()) {
        Message_800F01CC message;
        Object_800B26B0 *pMotion = &p->mMotion;
        float angle;
        unsigned char value;
        memset(&message, 0, 4);
        message.mId = 58;
        message.mUnknown1[1] = 8;
        if (kind == 4) {
            angle = MathAngleDiff(pMotion->mFacing, p->mUnknown528.mUnknown4) * (360.0f / 16777216.0f);
            if (angle > 165.0f) {
                message.mUnknown1[0] = 1;
                message.mUnknown1[1] = 1;
            } else {
                value = p->mUnknown1008.mUnknown1;
                message.mUnknown1[0] = value;
                message.mUnknown1[1] = value;
            }
            message.mUnknown1[2] = kind << 4 | 3;
        } else if (kind == 3) {
            message.mUnknown1[2] = 51;
            value = p->mUnknown1008.mUnknown1;
            message.mUnknown1[0] = value;
            message.mUnknown1[1] = value;
        } else {
            angle = MathAngleDiff(pMotion->mFacing, pMotion->mUnknown32) * (360.0f / 16777216.0f);
            float heading = MathAngleDiff(pMotion->mUnknown32, p->mUnknown512.mUnknown4) * (360.0f / 16777216.0f);
            message.mUnknown1[0] = angle < 90.0f ? 1 : 9;
            message.mUnknown1[1] = heading < 90.0f ? 1 : 9;
            message.mUnknown1[2] = kind << 4 | 3;
        }
        fn_800F00D4(0, p->mpState, &message, p);
    }
}

extern "C" int PlyrContactSendCarrierAction(Object_80039F5C *p, int kind) {
    if (PlyrContactCanReact(p) && !fn_801787A0()) {
        Message_800F01CC message;
        Object_800B26B0 *pMotion = &p->mMotion;
        float angle;
        unsigned char value;
        AudmonEventPostId(38, &pMotion->mPos, p->mId, 0, 0, 0);
        StyleTrackerOnCarrierActionTwo(p);
        memset(&message, 0, 4);
        message.mId = 10;
        if (kind == 3) {
            value = p->mUnknown1008.mUnknown1;
            message.mUnknown1[1] = value;
            message.mUnknown1[0] = value;
            message.mUnknown1[2] = 51;
            fn_800F00D4(0, p->mpState, &message, p);
        } else if (kind == 4) {
            angle = MathAngleDiff(pMotion->mFacing, p->mUnknown528.mUnknown4) * (360.0f / 16777216.0f);
            if (angle > 165.0f) {
                message.mUnknown1[0] = 1;
                message.mUnknown1[1] = 1;
            } else {
                value = p->mUnknown1008.mUnknown1;
                message.mUnknown1[1] = value;
                message.mUnknown1[0] = value;
            }
            message.mUnknown1[2] = kind << 4 | 3;
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            angle = MathAngleDiff(pMotion->mFacing, pMotion->mUnknown32) * (360.0f / 16777216.0f);
            float heading = MathAngleDiff(pMotion->mUnknown32, p->mUnknown512.mUnknown4) * (360.0f / 16777216.0f);
            message.mUnknown1[0] = angle < 90.0f ? 1 : 9;
            message.mUnknown1[1] = heading < 90.0f ? 1 : 9;
            message.mUnknown1[2] = kind << 4 | 3;
            fn_800F00D4(0, p->mpState, &message, p);
        }
        return 1;
    }
    return 0;
}

extern "C" void PlyrContactCollide(Object_80039F5C *p, Object_80039F5C *pOther) {
    Point_8017886C delta;
    Vec2Sub(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    int direction = fn_801CFE40(delta.mY, delta.mX);
    PlyrContactResolve(p, (direction + 0x800000) & 0xFFFFFF, direction);
}

extern "C" int CarrierMomentumEnter(Object_80039F5C *p) {
    State_800E9E18 *state = (State_800E9E18 *)&p->mUnknown336;
    state->mUnknown0 = p->mUnknown560.mUnknown54;
    p->mUnknown9[0] = 1;
    state->mUnknown4 = p->mUnknown560.mUnknown28;
    state->mUnknown12 = BallFindHeldBy(p) != 0;
    state->mUnknown16 = 0;
    PlayerActionAnimPitchInit(state->mUnknown20, p, fn_8017876C(), state->mUnknown4);
    fn_8009BD60(p);
    State_80039F5C *pState = p->mpState;
    if ((pState->mUnknown3[0] >> 4) > 1) {
        p->mUnknown1008.mUnknown0 = pState->mUnknown1;
        p->mUnknown1008.mUnknown1 = pState->mUnknown2;
        p->mUnknown1008.mUnknown2 = pState->mUnknown3[0] >> 4;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 165, 1.0f, p);
    } else {
        p->mUnknown1008.mUnknown2 = pState->mUnknown1 & 15;
        p->mUnknown1011 = pState->mUnknown1 >> 4;
        p->mUnknown1008.mUnknown1 = pState->mUnknown3[0] & 15;
        p->mUnknown1008.mUnknown0 = pState->mUnknown2;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 43, 1.0f, p);
    }
    p->mFlags &= ~4;
    p->mUnknown512.mUnknown14 = 0;
    if (p->mIdBytes[3] == 1) {
        fn_8011E3EC(p, 0);
        if (p->mIdBytes[2] == fn_80178308()) {
            fn_8011E240(p);
        } else {
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
            if (pOther)
                fn_8011E240(pOther);
        }
    }
    if (state->mUnknown20[0] == 1 || state->mUnknown20[1] == 1)
        fn_800D7A18(p);
    return 0;
}

extern "C" int CarrierMomentumExit(Object_80039F5C *p) {
    p->mFlags &= ~0x4000000;
    return 0;
}

extern "C" int CarrierMomentumUpdate(Object_80039F5C *p) {
    int result;
    fn_8010A2DC(p, 0, -1);
    State_800E9E18 *state = (State_800E9E18 *)&p->mUnknown336;
    PlayerActionAnimTossUpdate(state->mUnknown20, p);
    PlayerActionAnimPitchUpdate(state->mUnknown20, p);
    result = 0;
    if (state->mUnknown12) {
        if (!BallFindHeldBy(p)) {
            p->mFlags |= 0x4000000;
            state->mUnknown12 = 0;
        } else if (p->mpState->mId == 10) {
            PlayerActionAnimAiConsiderPitch(state->mUnknown20, p);
        }
    }
    if (p->mUnknown9[0] != 1) {
        p->mFlags &= ~0x80000;
        if (p->mUnknown9[0] != 8) {
            Message_800F01CC message;
            memset(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            p->mFlags &= ~0x4000000;
        }
        result = 1;
    } else if (p->mFlags & 4) {
        if (!fn_801787A0() && state->mUnknown20[1]) {
            unsigned int now = SyncTimeGetGameTime();
            if (state->mUnknown40 > now) {
                now = SyncTimeGetGameTime();
                state->mUnknown40 = now - 1.0f;
                PlayerActionAnimPitchUpdate(state->mUnknown20, p);
            }
        }
        p->mFlags &= ~0x4080804;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.4f;

        result = 1;
    }
    if (result == 1)
        p->mFlags &= ~8;
    return result;
}

extern "C" int CarrierMomentumNotify() {
    return 0;
}

extern "C" int CarrierMomentumInput(Object_80039F5C *p) {
    int index = fn_800B65A0(p->mIdBytes[2]);
    Input_800B6D34 input;
    fn_800B6D34(p, &input);
    if (input.mUnknown95 & 0x40) {
        PlayerActionAnimPitchTryStart((Record_800DB60C *)((State_800E9E18 *)&p->mUnknown336)->mUnknown20, p);
    } else {
        int mode = fn_800AD9B4();
        if (p->mIdBytes[2] == fn_80178320() || mode == 3
            || (mode == 2 && index != 255 && fn_800B6544(index) != p))
            return fn_800B7FE8(p);
    }
    return 0;
}

extern "C" int PlyrContactResolve(Object_80039F5C *p, int angle, int direction) {
    Object_80039F5C *pOther = 0;
    int *pRef = &p->mUnknown336;
    int blocked = 0;
    int otherDirection = 0;
    int result = 0;
    int other = 0;
    int otherAngle;
    int near = MathAngleDiff(p->mMotion.mUnknown32, direction) <= 0x31C71C;
    int facing = near;
    int busy;
    switch (p->mpState->mId) {
    case 16:
        pOther = fn_8009BCE8(pRef);
        other = pOther->mId;
        if (pOther->mpState->mId != 17 || fn_8009BCE8(&pOther->mUnknown336) != p)
            pOther = 0;
        break;
    case 17:
        pOther = fn_8009BCE8(pRef);
        other = pOther->mId;
        if (pOther->mpState->mId == 16) {
            if (fn_8009BCE8(&pOther->mUnknown336) != p)
                pOther = 0;
        } else {
            pOther = 0;
        }
        break;
    case 32:
        pOther = fn_8009BCE8(pRef);
        other = pOther->mId;
        if (pOther->mpState->mId != 32 || fn_8009BCE8(&pOther->mUnknown336) != p)
            pOther = 0;
        break;
    }
    busy = 1;
    if (!fn_80114E7C(p))
        busy = 0;
    if (near) {
        Record_800EA284 *pRecord = p->mpUnknown3092->mpUnknown32;
        if (pRecord->mUnknown8 < 1.0f) {
            if (pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.65f)
                blocked = 1;
        } else {
            if (pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.0f)
                blocked = 1;
        }

        if (fn_80114E7C(p))
            blocked = 0;
        if (!blocked && !PlyrContactIsBeforeImpact(p) && !(p->mFlags & 0x800) && !(pOther && PlyrContactIsBeforeImpact(pOther))) {
            switch (p->mpState->mId) {
            case 16:
                result = 1;
                HudClearMashPlayers(p->mId, other);
                break;
            case 17:
                HudClearMashPlayers(other, p->mId);
                break;
            }
            PlyrContactSendHitFrom(p, 10, &direction, 1, &angle);
            if (pOther && p == BallGetCurrentHolder() && !(p->mFlags & 0x10000)) {
                fn_80178718(pOther);
                p->mFlags = (p->mFlags | 0x10000) & ~0x80000;
            }
        } else {
            unsigned short animation = fn_801BE648(p->mpUnknown792);
            if (PlyrContactIsActionAnim(animation)) {
                Block_801BE60C *pBlock = fn_801BE60C(p->mpUnknown792, animation);
                if (pBlock->mUnknown1C)
                    pBlock->mUnknown1C = 0;
            }
        }
        PlyrCollideRemoveExempt(p, pOther);
    }
    if (pOther && near) {
        if (!busy && Vec2Distance(&p->mMotion.mPos, &pOther->mMotion.mPos) > _PlyrContact_fBreakDistance)
            facing = 0;
        if (facing) {
            Point_8017886C delta;
            Vec2Sub(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            blocked = 0;
            otherDirection = fn_801CFE40(delta.mY, delta.mX);
            otherAngle = (otherDirection + 0x800000) & 0xFFFFFF;
            Record_800EA284 *pRecord = pOther->mpUnknown3092->mpUnknown32;
            if (pRecord->mUnknown8 < 1.0f)
                blocked = pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.65f;
            else if (pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.0f)
                blocked = 1;
            if (fn_80114E7C(pOther))
                blocked = 0;
            if (!blocked && !PlyrContactIsBeforeImpact(pOther) && !(pOther->mFlags & 0x800)) {
                result = 1;
                PlyrContactSendHitFrom(pOther, 10, &otherAngle, 1, &otherDirection);
                if (pOther == BallGetCurrentHolder() && !(pOther->mFlags & 0x10000)) {
                    fn_80178718(p);
                    pOther->mFlags = (pOther->mFlags | 0x10000) & ~0x80000;
                }
            } else {
                unsigned short animation = fn_801BE648(pOther->mpUnknown792);
                if (PlyrContactIsActionAnim(animation)) {
                    Block_801BE60C *pBlock = fn_801BE60C(pOther->mpUnknown792, animation);
                    if (pBlock->mUnknown1C)
                        pBlock->mUnknown1C = 0;
                }
            }
            PlyrCollideRemoveExempt(pOther, p);
        }
    }
    return result;
}

extern "C" void PlyrContactHitWall(Object_80039F5C *p) {
    int nearX = 0;
    int nearY = 0;
    int index = 0;
    if (!fn_800C4184(p))
        return;
    if (LevelGetData()->mUnknown136) {
        if (fabsf(p->mMotion.mPos.mX) > fn_80178A08() - _PlyrContact_fEdgeMargin)
            nearX = 1;
        else if (fabsf(p->mMotion.mPos.mY) > fn_80178A44() - _PlyrContact_fEdgeMargin)
            nearY = 1;
    }
    if (!nearX && !nearY)
        return;
    if (p->mMotion.mUnknown28 < _PlyrContact_fWallSpeed * gPlyrMoveFwdSpeed)
        return;
    if (nearX) {
        if (p->mMotion.mPos.mX > 0.0f) {
            if (MathAngleDiff(p->mMotion.mUnknown32, 0) > 0x2E38E3)
                return;
        } else {
            if (MathAngleDiff(p->mMotion.mUnknown32, 0x800000) > 0x2E38E3)
                return;
        }
    } else if (nearY) {
        if (p->mMotion.mPos.mY > 0.0f) {
            if (MathAngleDiff(p->mMotion.mUnknown32, 0x400000) > 0x2E38E3)
                return;
        } else {
            if (MathAngleDiff(p->mMotion.mUnknown32, 0xC00000) > 0x2E38E3)
                return;
        }
    }
    int flag = p->mUnknown776 == 1;
    Command_800CEE74 command;
    Message_800F01CC message;
    int id;
    int kind;
    float chance;
    memset(&message, 0, 4);
    if (BallGetCurrentHolder() == p) {
        chance = p->mRatings[0] / 510.0f + 0.5f;
        if (SyncRandGetFloat(0) < chance && !index) {
            id = 58;
            kind = 196;
        } else {
            id = 10;
            kind = 197;
        }
    } else {
        chance = p->mRatings[0] / 510.0f + 0.5f;
        if (SyncRandGetFloat(0) < chance && !index) {
            id = 58;
            kind = 210;
        } else {
            id = 10;
            kind = 195;
        }
    }
    message.mId = id;
    fn_800CEE74(&command, p, 0, 0, 0, kind, flag);
    p->mUnknown1008.mUnknown0 = 8;
    if (kind == 196) {
        if (nearX) {
            if (MathAngleDiff(p->mMotion.mFacing, 0) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = !flag ? 3 : 6;
            else if (MathAngleDiff(p->mMotion.mFacing, 0x800000) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = !flag ? 6 : 3;
        } else if (nearY) {
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0xE38E2 || MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = SyncRandGetFloat(0) >= 0.5f ? 3 : 6;
        }
    } else if (kind == 210) {
        if (nearX) {
            Vector_80039F5C pos;
            BallGetPosition(BallGetCurrent(), &pos);
            int ahead = pos.mY > p->mMotion.mPos.mY;
            if (MathAngleDiff(p->mMotion.mFacing, 0) <= 0xE38E2) {
                if (flag)
                    p->mUnknown1008.mUnknown0 = !ahead ? 3 : 6;
                else
                    p->mUnknown1008.mUnknown0 = !ahead ? 6 : 3;
            } else if (MathAngleDiff(p->mMotion.mFacing, 0x800000) <= 0xE38E2) {
                if (flag)
                    p->mUnknown1008.mUnknown0 = !ahead ? 6 : 3;
                else
                    p->mUnknown1008.mUnknown0 = !ahead ? 3 : 6;
            }
        } else if (nearY) {
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0xE38E2 || MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = SyncRandGetFloat(0) >= 0.5f ? 3 : 6;
        }
    }
    int value;
    index = fn_800C3BEC(p, &command, &value, 0);
    if (index == -1) {
        if (p != BallGetCurrentHolder()) {
            if (p->mUnknown1008.mUnknown0 == 3)
                p->mUnknown1008.mUnknown0 = 6;
            else if (p->mUnknown1008.mUnknown0 == 6)
                p->mUnknown1008.mUnknown0 = 3;
            fn_800CEE74(&command, p, 0, 0, 0, kind, flag);
            command.mUnknown62 = !command.mUnknown62;
            index = fn_800C3BEC(p, &command, &value, 0);
        }
        if (index == -1)
            return;
    }
    if (BallGetCurrentHolder() == p) {
        int previous = fn_800F06F4(0, p->mpState, 18, 0xFFFF);
        fn_800EFE60(0, p->mpState, p);
        fn_800F053C(0, p->mpState, &message, p);
        p->mFlags &= ~0x2000;
        p->mFlags &= ~0x8;
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        StyleTrackerOnActionThree();
        if (previous == 0xFFFF) {
            memset(&message, 0, 4);
            message.mId = 1;
        } else {
            memset(&message, 0, 4);
            message.mId = 18;
        }
        fn_800F03D8(0, p->mpState, &message, p);
    } else if (p->mpState->mId == 58) {
        fn_800F05E4(0, p->mpState, &message, p);
    } else {
        fn_800F00D4(0, p->mpState, &message, p);
    }
    p->mFlags |= 8;
    fn_800C39E0(p, kind, index, value, command.mUnknown62);
}

extern "C" int PlyrContactIsBeforeImpact(Object_80039F5C *p) {
    int result = 0;
    int animation = fn_801BE648(p->mpUnknown792);
    int index = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, animation, 0);
    if (index != 0xFFFF) {
        float start = AnimSeqGetOpcodeTime(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0xC001);
        result = start < AnimSeqGetOpcodeTime(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0x8000);
    }
    return result;
}
