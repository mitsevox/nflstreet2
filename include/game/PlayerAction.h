/* Declarations shared by src/game/PlayerActionAnim.cpp and src/game/PlayerActionStates.cpp: the player,
   animation-table and state-block views and the callees of both files. */
#ifndef GAME_PLAYERACTION_H
#define GAME_PLAYERACTION_H

#include "engine/fn_801C065C.h"
#include "engine/animchan.h"
#include "game/AnimChanStartAnim.h"
#include "game/AnimMomentumActor.h"
#include "game/fn_801BE60C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Record_800DB60C.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F4F8.h"
#include "game/Record_8011F518.h"
#include "game/Ball.h"
#include "game/SyncRandGetRange.h"
#include "game/fn_800B65A0.h"
#include "game/Table_80089904.h"

typedef Record_800DB60C Record_800DB074;

extern "C" {
extern float gPlyrMoveFwdSpeed;
extern float lbl_803EAD14;
extern unsigned char lbl_803EAD18;
extern unsigned char lbl_803EAD19;
int PlayerLocoGetLowerAnkle(Object_80039F5C *p);
int PlayerLocoFindTableEntry(Table_80089904 *pTable, int value, int a, unsigned char b);
float fn_8012506C(Object_80039F5C *p, int value);
int fn_800ACFA8(Object_80039F5C *p);
Object_80039F5C *fn_80105384(Object_80039F5C *p, int value, Point_8017886C *pOut);
int OptionRunCanPitchTo(Object_80039F5C *p, Point_8017886C *pPoint, Object_80039F5C *pOther);
int fn_801066D0(Object_80039F5C *p, Object_80039F5C *pOther, int value);
int fn_80178308(void);
unsigned int fn_800ABDA4(int team);
unsigned char fn_8011F59C(int index);
void fn_8011F5AC(int index);

int MathAngleDiff(int a, int b);
int fn_801CFE40(float y, float x);
void Vec2Sub(void *pOut, void *pA, void *pB);
void fn_801061E8(Object_80039F5C *p, Ball_t *pBall);
int fn_80106580(Object_80039F5C *p, int a);
int fn_80106618(Object_80039F5C *p);
int fn_80105FF8(Object_80039F5C *p, Ball_t *pBall, float value);
int fn_80103CB0(Object_80039F5C *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);

float AnimSeqGetKeyTime(void *p, int flags);
float AnimSeqGetTime(AnimSeq_t *p);
int fn_801787A0(void);
int SyncTimeGetGameTime(void);
void PlayerActionAnimArmPitch(Record_800DB074 *pRecord, Object_80039F5C *p, Ball_t *pBall);
}

#include "game/Block_801BE60C.h"
#include "game/Ball.h"
#include "game/PlayBookDb.h"
#include "game/fn_800AD9B4.h"

#include "game/Object_80039F5C.h"
#include "game/PlaySet.h"

struct Object_800DC36C {
    char mUnknown0[36];
    unsigned short mUnknown36;
    char mUnknown38[2];
    int mUnknown40;
};

struct Entry_800DC36C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Object_800DC36C *mpUnknown4;
};

struct List_800DC36C {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_800DC36C mEntries[1];
};

extern "C" {
extern float gPlyrMoveFwdSpeed;

void fn_8009BD60(Object_80039F5C *p);
int fn_800A7EF4(unsigned char a);
void fn_800ADB90(Object_80039F5C *p, int a, int b, int c);
float fn_800C495C(Object_80039F5C *p, float value);
void fn_800C89F0(Object_80039F5C *p, int a, int b, int c, float value);
void fn_800CABF4(Object_80039F5C *p, unsigned char *pOut, int a);
int PlayerMoveGetKind(Object_80039F5C *p);
int PlayerActionAnimIsPassReady(Object_80039F5C *p);
int fn_8011F1CC(void);
int fn_8011F1F4(void);
int fn_8011F2C4(void);
int PassIconsAreShown(void);
int PassIconsWereShown(void);
int fn_801486A0(void);
void TutorialSetMoveDone(int index, int value);
PlayBookFormation_t *PlayBookGetFormation(int team);
float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
int fn_801783AC(int bit);
void AnimSeqSetSpeed(void *p, float value);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float value, void *p);

void fn_801BE760(void *p, unsigned short key, unsigned short flags);
float MathInverse(float value);
int MathAngleDiff(int a, int b);
}

#include "game/Object_80039F5C.h"
#include "game/PlayerActionAnimShiftPartner.h"
#include "game/Object_800EA284.h"
#include "game/Object_801BBD5C.h"
#include "game/Block_801BE60C.h"
#include "game/InGame.h"
#include "game/Message_800F01CC.h"
#include "game/Table_80089904.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/PlaySet.h"
#include "game/PlayBookGetPlay.h"
#include "game/fn_80178D18.h"
#include <string.h>
#include "game/Vec3Magnitude.h"
#include "game/Vec2Add.h"
#include "game/Vec2Distance.h"
#include "game/SyncRandGetRange.h"
#include "game/fn_801BE60C.h"
#include "engine/llquat.h"
#include "game/fn_80094488.h"
#include <math.h>

struct Record_800DC584 {
    int mUnknown0;
};

/* Views of the fn_801BE60C record, whose layout depends on the key. */
struct Record_800DD5E4 {
    char mUnknown0[6];
    unsigned char mUnknown6;
};

struct Record_800DD648 {
    char mUnknown0[4];
    unsigned short mUnknown4;
};

struct Record_800DD780 {
    unsigned int mUnknown0;
    char mUnknown4[12];
    unsigned char mUnknown16;
};

struct Record_800DDCE4 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    short mUnknown14;
};

struct Record_800E1778 {
    unsigned char mUnknown0;
};

/* Views of the player block at +336, whose layout depends on the state. */
struct Block_800E0188 {
    float mUnknown0;
    float mUnknown4;
};

struct Block_800E0230 {
    float mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

struct Block_800E0E8C {
    char mUnknown0[2];
    unsigned short mUnknown2;
};

struct Block_800E0EF0 {
    unsigned char mUnknown0;
    char mUnknown1[6];
    unsigned char mUnknown7;
    char mUnknown8[8];
    unsigned char mUnknown16;
    char mUnknown17[11];
    unsigned char mUnknown28;
};

/* View of the bytes from +12 of the player block at +1160. */
struct Block_800DF654 {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknown12[8];
    float mUnknown20;
    float mUnknown24;
    int mUnknown28;
};

struct Block_800E1438 {
    char mUnknown0[6];
    unsigned char mUnknown6;
    char mUnknown7[1];
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12;
};

struct Block_800E1778 {
    char mUnknown0[24];
    unsigned char mUnknown24;
    char mUnknown25[5];
    unsigned short mUnknown30;
};

struct Block_800E13E4 {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12;
};

typedef Record_800EA284 Block_800E11C0;

extern "C" {
void PlayerActionAnimStartVariant(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, void *pA, void *pB,
                 Object_80039F5C *pOther, Record_800DDCE4 *pRecord, int mask);
int PlayerLocoFindSampleIndex(Object_801BBD5C *pObject, float value);
float PlayerLocoUpdateBlendWeights(int index, void *pA, Object_801BBD5C *pObject, int b, float value);
void fn_8009A260(Object_80039F5C *p);
int fn_8009B9A8(int a);
float fn_8009BB54(int a);
void fn_8009BD60(Object_80039F5C *p);
void fn_8009BFD0(Object_80039F5C *p, Vector_80039F5C *pPos, float *pRot);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009D1AC(Object_80039F5C *p);
int fn_8009D1F4(Object_80039F5C *p);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800AE7F0(int event, int team, Object_80039F5C *p);
void PlayerActionDropBallRelease(Object_80039F5C *p, Block_800E0230 *pBlock, int a);
void PlayerActionDropBallStart(Object_80039F5C *p, Block_800E0230 *pBlock);
void PlayerActionDropBallLetGo(Object_80039F5C *p, Block_800E0230 *pBlock);
void PlayerActionDropBallWait(Object_80039F5C *p, Block_800E0230 *pBlock);
int PlyrTackleContest(Object_80039F5C *p, int *pValue);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
unsigned int fn_8011E188(void);
int fn_80120794(Object_800B26B0 *pA, Object_800B26B0 *pB, float *pC, float e, float f, int d, float g);
int fn_801486A0(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
void PossReleaseBall(Object_80039F5C *p);
int fn_80178308(void);
int fn_801CFE08(float value);
int MathAngleDiff(int a, int b);
void Vec2Normalize(Vector_80039F5C *pOut, Vector_80039F5C *p);
void Vec2Scale(void *pOut, void *p, float scale);
void Vec2Sub(void *pOut, void *pA, void *pB);
float Vec3DistanceSqrToSegment(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
}

extern float gPlyrMoveFwdSpeed;

#include "game/fn_80177FE0.h"
#include "game/PostPlayPhase.h"
#include "game/cu_8008E978.h"

struct Block_800DFCEC {
    float mUnknown0, mUnknown4;
    unsigned char mUnknown8, mUnknown9, mUnknown10, mUnknown11, mUnknown12, mUnknown13;
};
extern "C" {
float fn_80178A2C(void);
Point_8017886C fn_80177FFC(int team);
int fn_801CFE40(float y, float x);
void PlyrClearPendingMsg(Object_80039F5C *p, int a);
void PlyrObjsSetDrawFlag(int a);
int FELoopIsMainFEActive(void);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
void fn_801BE67C(void *pA, void *pB, void *pC, Object_80039F5C *p);
void BallLaunchWithVelocity(Ball_t *pBall, Vector_80039F5C *pVelocity, int mode, float spin, float rate);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float a, float b, int facing);
void fn_800ACDE4(Object_80039F5C *p, float *pChance, float *pAngle);
int fn_80178348(void);
float SyncRandGetFloat(int a);
int PlayerActionCharAnimLoad(Object_80039F5C *p, float *pValue);
int fn_800B9A90(PostPlayPhase *p);
}

struct Record_800DE19C { int mUnknown0, mUnknown4; };
struct Info_800DDF34 {
    char mUnknown0[4];
    unsigned char mUnknown4[4];
    int mUnknown8, mUnknown12, mUnknown16, mUnknown20;
    float mUnknown24;
};
struct Block_800DE3B0 {
    float mUnknown0;
    Pair_802270A4 mUnknown4, mUnknownC;
    int mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C, mUnknown1D, mUnknown1E, mUnknown1F;
    AnimMomentum_t mUnknown20;
    int mUnknown38;
    unsigned char mUnknown3C, mUnknown3D;
    signed char mUnknown3E, mUnknown3F;
};
struct Command_800DE3B0 {
    Pair_802270A4 mUnknown0;
    char mUnknown8[4];
    Pair_802270A4 mUnknownC;
    char mUnknown14[4];
    float mUnknown18;
};
struct State_800DE3B0 {
    int mUnknown0;
    Pair_802270A4 mUnknown4;
    char mUnknownC[6];
    unsigned char mUnknown12;
    char mUnknown13[1];
    Pair_802270A4 mUnknown14;
    int mUnknown1C;
};
extern "C" {
void AnimSeqSetSpeed(void *p, float value);
float MathInverse(float value);
void Vec2Rotate(void *pOut, void *p, int angle);
}
extern float lbl_803EAD20;

#include "game/LocoBlendSet.h"
#include "game/FEPlyrModel.h"
struct Record_800DC6F4 {
    int mUnknown0, mUnknown4;
    unsigned char mUnknown8, mUnknown9, mUnknown10;
};
struct Record_800DCC14 {
    char mUnknown0[4];
    float mUnknown4;
    char mUnknown8[4];
    int mUnknown12;
    signed char mUnknown16;
};
extern "C" {
Object_801BBD5C *AnimFileGetStateData(unsigned short key, unsigned short id);
int AnimChanStartCopy(void *pA, AnimChannel_t *pEntries, AnimChannel_t *pEntry);
void AnimChanSwitchAnim(void *pA, AnimChannel_t *pEntries, int index, unsigned short a, int b, unsigned short key, Object_80039F5C *p);
void PlayerLocoStartBlendPair(LocoBlendSet_t *pObject, Block_801BE60C *pBlock, Object_80039F5C *p, int a, int index, int key, FEPlyrModel_t *pA, AnimChannel_t *pEntries);
void PlayerLocoSwitchBlendPair(LocoBlendSet_t *pObject, Block_801BE60C *pBlock, Object_80039F5C *p, int a, int index, unsigned short key, void *pA, AnimChannel_t *pEntries, unsigned char flag);
void PlayerLocoSetFadeFraction(Block_801BE60C *p, float a, float b);
void PlayerLocoFadeOldPair(Block_801BE60C *p, void *pA, AnimChannel_t *pEntries);
}

extern "C" {
int fn_80177F70(void);
int fn_801787A0(void);
int fn_80178320(void);
}
struct Record_800DD2E8 {
    unsigned short mUnknown0, mUnknown2, mUnknown4;
    unsigned char mUnknown6;
};

#include "game/Input_800B6D34.h"
#include "game/AudmonEvent.h"
struct Item_800E0694 {
    char mUnknown0[4];
    unsigned char mUnknown4;
};
struct Block_800E0850 {
    unsigned short mUnknown0, mUnknown2;
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
    int mUnknown20, mUnknown24;
    unsigned char mUnknown28, mUnknown29;
};
extern "C" {
Item_800E0694 *fn_8009A63C(int handle);
void fn_80099F04(Object_80039F5C *p, int handle, int index);
void fn_800A2190(int a);
void fn_8009A5DC(int a, int b, void *pKind, int *pHandle);
float fn_8009A270(int handle);
int fn_8009A578(int handle);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void PlayerMoveBegin(Object_80039F5C *p, int a, int b);
void fn_800B8344(Object_80039F5C *p);
int fn_8009A68C(Object_80039F5C *p);
unsigned char *fn_8009CC2C(Object_80039F5C *p, void (*callback)(int, Vector_80039F5C *, unsigned char *), int a, int b);
void PlyrPoseDelayBlink(Block_80170E64 *p);
int fn_800C4B6C(Object_80039F5C *p);
}
extern unsigned char lbl_803EAD34;
extern unsigned int lbl_803EAD2C;
extern int lbl_803EAD28;
extern float lbl_803EAD30;

#include "game/State_803EB098.h"
struct Block_800E1954 {
    unsigned char mUnknown0, mUnknown1;
    char mUnknown2[2];
    Point_8017886C mUnknown4, mUnknown12;
    unsigned short mUnknown20;
    unsigned char mUnknown22, mUnknown23, mUnknown24;
    char mUnknown25[11];
    Object_80039F5C *mpUnknown36;
    Point_8017886C mUnknown40;
    char mUnknown48[1];
    unsigned char mUnknown49;
    char mUnknown50[28];
    unsigned char mUnknown78;
};
struct Record_800E2ABC { char mUnknown0[4]; unsigned char mUnknown4, mUnknown5, mUnknown6; };
struct Record_80168EBC { char mUnknown0[48]; unsigned char mUnknown48; };
extern "C" {
Record_8011F4E0 *fn_8011F4E0(void);
Record_80168EBC *PlayBookGetTeam(int team);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_8009FE24(Object_80039F5C *p);
int fn_800B0F98(void);
int fn_800B146C(void);
void fn_800FE03C(Object_80039F5C *p, Point_8017886C *pOut);
int fn_8009F780(void);
int ScrmOffenseAnyPlaced(void);
void PlyrAlignGetCallTarget(Object_80039F5C *p, Point_8017886C *pOut);
void Vec2FromAngle(Point_8017886C *pOut, int angle, float magnitude);
void PlyrAlignAvoidTeammates(Object_80039F5C *p, Point_8017886C *pPoint);
int PlayerPathIsLaneClear(Object_80039F5C *p, Point_8017886C *pPoint);
}

#include "game/Command_800CEE74.h"
struct Entry_800DE51C { unsigned short mUnknown0; unsigned char mUnknown2; char mUnknown3[17]; };
#include "game/Frame_800DF7CC.h"
struct Attachment_800DF7CC { Vector_80039F5C mPos; QuatEulerAngles_t mAngles; int mFrame; };
struct Character_800DF7CC {
    int mUnknown0, mUnknown4; unsigned int mFlags;
    char mUnknown12[8]; struct Flags { char mUnknown0[12]; unsigned int mUnknown12; } *mpUnknown20;
    char mUnknown24[92]; Ball_t *mpBall[1];
};
extern "C" {
float AnimSequencerGetTicksPerSecond(Object_80039F5C *);
Attachment_800DF7CC *fn_80093C08(unsigned short);
int fn_800943B0(unsigned short);
void fn_8009134C(unsigned short);
int AnimFileGetSlotFromFileNum(int objectType, int fileNum);
void *AnimFileGetPtrFromSlot(unsigned int);
AnimScript_t *AnimFileGetAnimation(void *, int);
int AnimSeqHasOpcode(AnimSeq_t *, AnimScript_t *, unsigned short);
int AnimChanIsMirrored(AnimChannel_t *);
void AnimChanSetMirrored(AnimChannel_t *, int);
void fn_800D7A0C(Object_80039F5C *, int);
unsigned int AnimFileGetSiblingSlot(unsigned int, int);
int AnimFileGetStateQueryIndex(int state, unsigned int slot);
}
extern "C" int BallStateGet(Ball_t *, int);
extern "C" void fn_800ADBC0(Object_80039F5C *, int, int, int);
extern "C" void ScrmPlayerToHuddle(Object_80039F5C *);
extern float gFrameTimeScale;

struct Table_800DE51C { char mUnknown0[4]; unsigned short mCount; char mUnknown6[2]; Entry_800DE51C mEntries[1]; };
extern "C" {
Table_80089904 *fn_801BE72C(unsigned short, unsigned short);
void fn_800CEDA4(Entry_800DE51C *, Pair_802270A4 *, int *, Object_80039F5C *, int);
void AnimMomentumInit(AnimMomentum_t *, Object_80039F5C *, int);
void AnimMomentumUpdate(AnimMomentum_t *, Object_80039F5C *);
void AnimMomentumUpdateLinked(AnimMomentum_t *, Object_80039F5C *);
float fn_80114EE4(Object_80039F5C *, Object_80039F5C *);
int fn_800C854C(Object_80039F5C *, unsigned short, unsigned char);
void PlayerActionAnimUpdatePairAlign(Object_80039F5C *, Block_800DE3B0 *);
}

extern "C" int fn_801784C4(void);

extern "C" int fn_801784C4(void);
extern "C" void *BigObjFindNearestOfType(Vector_80039F5C *, int, float *);
extern "C" void HotspotFrameTouch(void *, Object_80039F5C *);

extern "C" int fn_8009F778(Object_80039F5C *);
extern "C" int fn_8009F6B4(void);
extern "C" void PlayAlignGetSetName(int);
extern "C" float Vec2Magnitude(void *);

extern "C" int PlayerActionAnimSetTurnAngle(Object_80039F5C *p, Record_800DC584 *pRecord);
extern "C" float PlayerActionAnimGetSignedSpeed(Object_801BBD5C *pObject, Object_80039F5C *p);
extern "C" int PlayerActionAnimFindSpeedSample(Object_801BBD5C *pObject, Object_80039F5C *p);
extern "C" float PlayerActionAnimUpdateSpeedBlend(Object_801BBD5C *pObject, Object_80039F5C *p, int index, void *pA, int b);
extern "C" int PlayerActionAnimTurnPhase(Table_80089904 *pTable, unsigned short key, void *pA, AnimChannel_t *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int PlayerActionAnimSpeedBlendPhase(Table_80089904 *pTable, unsigned short key, void *pA, AnimChannel_t *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int PlayerActionAnimScoreReaction(Object_80039F5C *p, unsigned char *pInfo);
extern "C" int PlayerActionAnimReactionPhase(Table_80089904 *pTable, unsigned short key, void *pA, AnimChannel_t *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int PlayerActionAnimIsReactionAlt(Object_80039F5C *p);
extern "C" int PlayerActionAnimGetReactionKind(Object_80039F5C *p);
extern "C" int PlayerActionAnimDepthPhase(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode);
extern "C" int PlayerActionAnimIsVariantFree(Object_80039F5C *p, int value, unsigned short key);
extern "C" int PlayerActionAnimVariantAllowed(void *p, int value);
extern "C" int PlayerActionAnimGetIdleMask(Object_80039F5C *p);
extern "C" void PlayerActionAnimLoadVariantList(Table_80089904 *pTable, unsigned short a, unsigned char value);
extern "C" void PlayerActionAnimStartVariant(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, void *pA, void *pB,
                            Object_80039F5C *pOther, Record_800DDCE4 *pRecord, int mask);
extern "C" void PlayerActionAnimApplyVariantFlag(Object_80039F5C *p, Record_800DDCE4 *pRecord);
extern "C" int PlayerActionAnimIdlePhase(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode);
extern "C" void PlayerActionAnimSetTurnKeys(Object_80039F5C *p);
extern "C" int PlayerActionAnimKeysMatch(unsigned char *pA, unsigned char *pB);
extern "C" unsigned short PlayerActionAnimFindTurnEntry(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, int *pAngle, float *pTime, float *pRate);
extern "C" int PlayerActionAnimTurnInPlacePhase(Table_80089904 *pTable, unsigned short key, void *pA, AnimChannel_t *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int PlayerActionAnimIsFlaggedKey(unsigned int id);
extern "C" void PlayerActionAnimSetupAlign(Block_800DE3B0 *pBlock, Object_80039F5C *p, Command_800DE3B0 *pCommand);
extern "C" void PlayerActionAnimFindAlignTarget(Object_80039F5C *p, Block_800DE3B0 *pBlock, int id);
extern "C" void PlayerActionAnimBlendAlign(Object_80039F5C *p, Block_800DE3B0 *pBlock);
extern "C" void PlayerActionAnimBuildAlignCommand(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key, void *pData, int angle, Entry_800DE51C *pRecord);
extern "C" void PlayerActionAnimUpdatePairAlign(Object_80039F5C *p, Block_800DE3B0 *pBlock);
extern "C" void PlayerActionAnimShiftPartner(Object_80039F5C *p, Point_8017886C offset, int angle, int key);
extern "C" int PlayerActionAnimGenericPhase(Table_80089904 *pTable, unsigned short key, void *pData, AnimChannel_t *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" void PlayerActionAnimMirrorAlign(Object_80039F5C *p, Block_801BE60C *pRecord);
extern "C" int PlayerActionTakeFlag1000(Object_80039F5C *p);
extern "C" void PlayerActionGetJointPose(Object_80039F5C *p, int joint, Vector_80039F5C *pPos, QuatEulerAngles_t *pAngles);
extern "C" void PlayerActionMoveBall(Ball_t *pBall, Vector_80039F5C *pPos, int *pAngles);
extern "C" void PlayerActionCharAnimUpdateAttachments(Object_80039F5C *p, Character_80093BCC *pCharacter, Attachment_800DF7CC *pAttachments, Frame_800DF7CC *pFrame, int index, unsigned int frame);
extern "C" void PlayerActionCharAnimNotify(Object_80039F5C *p, void *pRecord, unsigned int value);
extern "C" int PlayerActionCharAnimLoad(Object_80039F5C *p, float *pValue);
extern "C" void PlayerActionCharAnimEnter(Object_80039F5C *p);
extern "C" int PlayerActionCharAnimExit(Object_80039F5C *p);
extern "C" int PlayerActionCharAnimUpdate(Object_80039F5C *p);
extern "C" int PlayerActionCharAnimGetTime(Object_80039F5C *p, float *pA, float *pB);
extern "C" void PlayerActionDropBallRelease(Object_80039F5C *p, Block_800E0230 *pBlock, int a);
extern "C" void PlayerActionDropBallPickVariant(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" float PlayerActionDropBallGetSpeed(Object_80039F5C *p);
extern "C" void PlayerActionDropBallStart(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" void PlayerActionDropBallLetGo(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" void PlayerActionDropBallWait(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" int PlayerActionDropBallEnter(Object_80039F5C *p);
extern "C" int PlayerActionDropBallUpdate(Object_80039F5C *p);
extern "C" int PlayerActionDropBallExit(Object_80039F5C *p);
extern "C" void PlayerActionCatchResolve(Object_80039F5C *p, int handle, int index);
extern "C" void PlayerActionCatchGetBallPos(int a, Vector_80039F5C *pOut, unsigned char *pIndex);
extern "C" int PlayerActionCatchEnter(Object_80039F5C *p);
extern "C" int PlayerActionCatchUpdate(Object_80039F5C *p);
extern "C" int PlayerActionCatchExit(Object_80039F5C *p);
extern "C" int PlayerActionIsUserCatch(Object_80039F5C *p);
extern "C" int PlayerActionIsCatchBlocked(Object_80039F5C *p);
extern "C" int PlayerActionSegmentsCross(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
extern "C" int PlayerActionRunCrossesLine(Object_80039F5C *p, Vector_80039F5C *pTarget);
extern "C" int PlayerActionIsShallowPath(Object_80039F5C *p);
extern "C" int PlayerActionGetInterceptHeading(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int PlayerActionCanDive(Object_80039F5C *p);
extern "C" int PlayerActionTryDive(Object_80039F5C *p);
extern "C" int PlayerActionDiveEnter(Object_80039F5C *p);
extern "C" int PlayerActionDiveUpdate(Object_80039F5C *p);
extern "C" int PlayerActionDiveExit(Object_80039F5C *p);
extern "C" int PlayerActionDiveIsActive(Object_80039F5C *p);
extern "C" int PlayerActionAiConsiderDive(Object_80039F5C *p);
extern "C" int PlayerActionRollAlignChange(Object_80039F5C *p);
extern "C" int PlayerActionIsNearLine(Object_80039F5C *p);
extern "C" void PlayerActionAlignDefender(Object_80039F5C *p);
extern "C" void PlayerActionGetAlignSpot(Object_80039F5C *p, Point_8017886C *pOut, int *pAngle);
extern "C" int PlayerActionFindGap(Object_80039F5C *p, int count, float *pValues, float *pOut, float direction, float target);
extern "C" void PlayerActionPickLaneTarget(Object_80039F5C *p);
extern "C" int PlayerActionIsFacingPoint(Object_80039F5C *p, Point_8017886C *pPoint);

#endif
