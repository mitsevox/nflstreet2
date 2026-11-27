/* Dynamic field objects: the big objects read from their TIDE definition files (animation
   variants and replay poses, anim and swap-part events, particle emitters, behaviours, hit
   reactions), the dynamic objects drawn with their models and skeletons, and the field's
   rigid-body physics (players, ball and props as bodies of one physics world). */
#pragma implementation "phystime.h"
#include "engine/physconstraint.h"
#include "engine/TibNew.h"
#include "engine/physcollection.h"
#include "engine/physworld.h"
#include "engine/physcollide.h"
#include "engine/animchan.h"
#include "game/Object_8008044C.h"
#include "game/fn_80233CBC.h"
#include "game/BigObjDesc.h"
#include "game/ParticleSys.h"
#include "game/DynObjRender.h"
#include "game/Object_80235588.h"
#include "engine/llquat.h"
#include <math.h>
#include <string.h>

#include "game/BigObjNode.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/BigObj.h"
#include "game/InGame.h"
#include "game/bitstream.h"
#include "game/BigObjInst.h"
#include "game/AudmonEvent.h"
#include "game/cu_8008E978.h"
#include "game/Ball.h"
#include "game/ScrmGetBallSpot.h"
#include "game/AnimChanStartAnim.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/SyncRandGetRange.h"
#include "game/Vec3Magnitude.h"
#include "game/Vec2Add.h"

/* Record whose four key bytes at +4 BigObjAnimPickVariant and BigObjAnimPickMatchedVariant score. */
struct BigObjAnimVariant_t {
    char mUnknown0[4];
    unsigned char mKey[4];
};

/* Entry of a variant table: the two halfwords handed to AnimChanStartAnim and the
   scored record. */
struct BigObjAnimVariantEntry_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    BigObjAnimVariant_t *mpVariant;
};

struct BigObjAnimVariantTable_t {
    unsigned short mCount;
    char mUnknown2[2];
    BigObjAnimVariantEntry_t mEntries[1];
};

/* Name and id pair of the tables BigObjFindNameId searches; an id of -1 ends
   the table. */
struct BigObjNameId_t {
    char mName[64];
    int mId;
};

/* 0x24-byte name table entry of BigObjFindTypeId, BigObjFindBehaviorId and BigObjFindEventType. */
struct BigObjShortNameId_t {
    char mName[32];
    int mId;
};

/* 0x44-byte sound name table entry of BigObjFindSoundId. */
struct BigObjSoundNameId_t {
    char mName[64];
    unsigned short mId;
    char mUnknown66[2];
};

/* 0x84-byte name/state table entry of BigObjFindSwapState. */
struct BigObjSwapStateName_t {
    char mName[64];
    char mState[64];
    int mId;
};

/* Record of AnimSeqncrGetStaticPtr; its halfwords +42 and +14 are passed to AnimFileGetSlotFromFileNum. */
struct AnimSeqncrStatic_t {
    char mUnknown0[14];
    unsigned short mUnknown14;
    char mUnknown16[26];
    unsigned short mUnknown42;
};

typedef int (*BigObjAnimHandlerFunc)(BigObjAnimVariantTable_t *pTable, unsigned short c, void *a, void *b,
                                BigObjInst *pObject, int skip);

/* Handler set registered with fn_801BE030: a count and the handler array. */
struct BigObjAnimHandlerSet_t {
    unsigned short mCount;
    BigObjAnimHandlerFunc *mpHandlers;
};

extern "C" {
extern float gFrameTimeScale;
extern BigObjAnimHandlerFunc _BigObjAnim_aHandlers[102];
BigObjAnimHandlerSet_t _BigObjAnim_sHandlerSet = {102, _BigObjAnim_aHandlers};
unsigned char _BigObjHit_uRumbleMax = 0xFF;
unsigned char _BigObjHit_uRumbleMin = 0x50;
unsigned short _BigObjHit_uRumbleTime = 20;
unsigned char _BigObj_aOctantStates[8] = {9, 5, 6, 7, 1, 2, 3, 4};
BigObjInst *_BigObj_pAnimPalObject = 0;
/* Hitter passed to BigObjHit: an id word, a sound channel byte (0xFF for
   none) and the two floats whose product is the hit strength. */
struct BigObjHitter_t {
    int mId;
    char mUnknown4[4];
    unsigned char mChannel;
    char mUnknown9[443];
    float mUnknown452;
    char mUnknown456[52];
    float mUnknown508;
};

typedef void (*BigObjLoaderFunc)(int handle, BigObjInst *pObject);

int _BigObj_aiEffectTypes[8];
int _BigObj_aiEffectUsers[8];
float _BigObj_fBoundsMargin = 1.0f;
float _BigObj_fBoundsInset = 1.0f;
float _BigObj_fBoundsJitter = 2.0f;

void ReplayReadPacked3(void *pStream, float *pValues, int bits, float scale);
void ReplayWritePacked3(void *pStream, float *pValues, int bits, float scale);
void BigObjClearFlag(BigObj_t *pObject);
void BigObjSetFlag(BigObj_t *pObject);
int BigObjFindPartId(const char *pName);
int BigObjFindSwapState(const char *pName, const char *pState);
int BigObjFindEmotionState(const char *pName);
unsigned short BigObjFindSoundId(const char *pName);
int BigObjEffectSlotAcquire(int index);
void ObjParseRewind(int handle);
int ObjParseFindPath(int handle, const char *pKey);
int ObjParseFindChild(int handle, const char *pKey);
unsigned char PhysIsBall(int type);
int PhysIsPlayer(int type);
void RumbleStart(int a, int b, int c);
int ObjParseNext(int handle);
int ObjParseGetString(int handle, const char *pKey, char *pText, int size);
int ObjParseGetInt(int handle, const char *pKey);
float ObjParseGetFloat(int handle, const char *pKey);
unsigned char ObjParseGetFloats(int handle, const char *pKey, float *pValues, int count);
int ObjParseGetVector(int handle, const char *pKey, float *pValues);
int ObjParseGetCursor(int handle);
void ObjParseSetCursor(int handle, int position);
int fn_800C47C4(void);
void ParticleSysSetEffectFile(int type, int index);
int ResFindIndexByName(int set, const char *pName);
void BigObjEmitParticles(void *pData, float t, BigObjInst *pObject, BigObj_t *pOwner);
int fn_801BE068(void *pA, void *pB, void *pC, unsigned short key, float value, void *p);
unsigned short fn_801BE648(void *p);
void BigObjUpdatePartTimers(BigObj_t *pOwner);
void DynObjSetPartState(BigObj_t *pOwner, int a, int b);
void PhysSetBodyPose(int id, float *pA, float *pB);
void PhysSleepBody(int id);
void PhysApplyImpulse(BigObj_t *pOwner, float *p);
void PhysDampLinear(BigObj_t *pOwner, float value);
void PhysDampAngular(BigObj_t *pOwner, float value);
void PhysSetObjectPosition(BigObj_t *pOwner, float *pPos);
void LevelSetSurface(int a, int b);
int fn_800A3444(void);
int ScrmIsFieldFlipped(void);
float ScrmGetSidelineX(void);
float ScrmGetEndLineY(void);
void AnimBlendPose(AnimPose_t *pOut, AnimPose_t *pA, AnimPose_t *pB, AnimPose_t *pC, float t,
                 unsigned char a);
void BigObjAnimBlendPose(BigObjPhysics_t *pExtra, BigObj_t *pItem, int a, int b);
void BigObjAnimBlendRootAngles(BigObj_t *pItem, void *a, int b, void *c);
short *BigObjAnimAllocSamples(int count);
void AnimChanInitChannels(void *p, void *q);
int AnimFileLoadResident(int id, int a);
int AnimFileGetSlotFromFileNum(int a, int b);
void fn_801BE030(int type, BigObjAnimHandlerSet_t *pTable);
void AnimStInitStructure(void *p);
AnimSeqncrStatic_t *AnimSeqncrGetStaticPtr(Actor_801C009C *pActor, int index);
int MathArcTan2(float y, float x);
void Vec2Scale(void *pOut, void *p, float scale);
void Vec2Sub(void *pOut, void *pA, void *pB);
float SyncRandGetFloat(int stream);

struct DynObjSkeletonCache_t;
int BigObjOnAnimEvent(BigObjInst *pObject, BigObj_t *pOwner, int mode);
int BigObjPathedUpdate(BigObjInst *pObject, BigObj_t *pOwner, int mode);
int BigObjPathNodeUpdate(BigObjInst *pObject, BigObj_t *pOwner, int mode);
int BigObjBirdUpdate(BigObjInst *pObject, BigObj_t *pOwner, int mode);
int BigObjFenceUpdate(BigObjInst *pObject, BigObj_t *pOwner, int mode);
int BigObjHotspotSponsorUpdate(BigObjInst *pObject, BigObj_t *pOwner, int mode);
int BigObjHotspotFrameUpdate(BigObjInst *pObject, BigObj_t *pOwner, int mode);
void BigObjPathedLoad(int handle, BigObjInst *pObject);
void BigObjPathNodeLoad(int handle, BigObjInst *pObject);
void BigObjRestoreState(BigObj_t *pObject);
void BigObjKeepInBounds(BigObj_t *pObject);

BigObjShortNameId_t _BigObj_aTypeNames[8] = {
    {"NONE", 0},
    {"BASIC", 1},
    {"PATHED_OBJECT", 2},
    {"PATHNODE", 3},
    {"BIRD", 4},
    {"FENCE", 5},
    {"HOTSPOT_SPONSOR", 6},
    {"HOTSPOT_FRAME", 7},
};
BigObjBehaviorFunc _BigObj_apUpdateFuncs[8] = {
    0,
    BigObjOnAnimEvent,
    BigObjPathedUpdate,
    BigObjPathNodeUpdate,
    BigObjBirdUpdate,
    BigObjFenceUpdate,
    BigObjHotspotSponsorUpdate,
    BigObjHotspotFrameUpdate,
};
BigObjLoaderFunc _BigObj_apLoadFuncs[8] = {0, 0, BigObjPathedLoad, BigObjPathNodeLoad, 0, 0, 0, 0};
BigObjShortNameId_t _BigObj_aResetNames[3] = {
    {"NONE", 0},
    {"START_POS", 1},
    {"ON_FIELD_IF_OFF_FIELD", 2},
};
void (*_BigObj_apResetFuncs[3])(BigObj_t *pOwner) = {0, BigObjRestoreState, BigObjKeepInBounds};
BigObjShortNameId_t _BigObj_aEventTypeNames[4] = {
    {"NONE", 0},
    {"IDLE", 1},
    {"COLLIDE", 2},
    {"TRIGGER", 3},
};
BigObjNameId_t _BigObj_aEmotionStates[85] = {
    {"NONE", -1},
    {"ANIM_STATE_POLEIDLE", 0},
    {"ANIM_STATE_POLECOLLIDE", 1},
    {"ANIM_STATE_TREEIDLE", 2},
    {"ANIM_STATE_TREECOLLIDE", 3},
    {"ANIM_STATE_CARDRIVINGLOOP", 4},
    {"ANIM_STATE_BRONCROWDSTANDIDLES", 52},
    {"ANIM_STATE_BRONCROWDSITIDLES", 38},
    {"ANIM_STATE_BENCHIDLE", 6},
    {"ANIM_STATE_BENCHCOLLIDE", 7},
    {"ANIM_STATE_BENCHCOLLIDELEFT", 23},
    {"ANIM_STATE_BENCHCOLLIDERIGHT", 24},
    {"ANIM_STATE_PIGEONWALKA", 25},
    {"ANIM_STATE_PIGEONWALKB", 26},
    {"ANIM_STATE_PIGEONWALKC", 27},
    {"ANIM_STATE_PIGEONWALKD", 28},
    {"ANIM_STATE_PIGEONFLYA", 29},
    {"ANIM_STATE_PIGEONFLYB", 30},
    {"ANIM_STATE_PIGEONFLYC", 31},
    {"ANIM_STATE_PIGEONFLYD", 32},
    {"ANIM_STATE_FENCEIDLE", 16},
    {"ANIM_STATE_FENCECOLLIDELEFT", 17},
    {"ANIM_STATE_FENCECOLLIDERIGHT", 19},
    {"ANIM_STATE_GATEIDLE", 20},
    {"ANIM_STATE_GATECOLLIDELEFT", 21},
    {"ANIM_STATE_GATECOLLIDERIGHT", 22},
    {"ANIM_STATE_SEAGULLSHADOWA", 40},
    {"ANIM_STATE_SEAGULLSHADOWB", 41},
    {"ANIM_STATE_SEAGULLSHADOWC", 42},
    {"ANIM_STATE_SEAGULLSHADOWD", 43},
    {"ANIM_STATE_SEAGULLSHADOWE", 44},
    {"ANIM_STATE_SEAGULLWALKA", 45},
    {"ANIM_STATE_SEAGULLWALKB", 46},
    {"ANIM_STATE_SEAGULLWALKC", 47},
    {"ANIM_STATE_SEAGULLWALKD", 48},
    {"ANIM_STATE_SEAGULLFLYA", 49},
    {"ANIM_STATE_SEAGULLFLYB", 50},
    {"ANIM_STATE_SEAGULLFLYC", 51},
    {"ANIM_STATE_SEAGULLFLYD", 53},
    {"ANIM_STATE_ROOFFANIDLE", 56},
    {"ANIM_STATE_ACVENTIDLE", 55},
    {"ANIM_STATE_ROOSTERIDLE", 57},
    {"ANIM_STATE_ROOSTERFLY", 58},
    {"ANIM_STATE_DOGIDLE", 59},
    {"ANIM_STATE_DOGATTACK", 60},
    {"ANIM_STATE_WAREFANSPINIDLES", 61},
    {"ANIM_STATE_WAREFENCEIDLE", 62},
    {"ANIM_STATE_WAREFENCECOLLIDELEFT", 63},
    {"ANIM_STATE_WAREFENCECOLLIDERIGHT", 64},
    {"ANIM_STATE_WARERATA", 65},
    {"ANIM_STATE_WARERATB", 66},
    {"ANIM_STATE_WARERATC", 67},
    {"ANIM_STATE_WARERATD", 68},
    {"ANIM_STATE_CAG_CROWDGROUP01_IDLE", 69},
    {"ANIM_STATE_CAG_CROWDGROUP02_IDLE", 70},
    {"ANIM_STATE_CAG_CROWDGROUP03_IDLE", 71},
    {"ANIM_STATE_DTP_CROWDGROUP01_IDLE", 72},
    {"ANIM_STATE_DTP_CROWDGROUP02_IDLE", 73},
    {"ANIM_STATE_DTP_CROWDGROUP03_IDLE", 74},
    {"ANIM_STATE_CEN_CROWDGROUP01_IDLE", 75},
    {"ANIM_STATE_CEN_CROWDGROUP02_IDLE", 76},
    {"ANIM_STATE_CEN_CROWDGROUP03_IDLE", 77},
    {"ANIM_STATE_STR_CROWDGROUP01_IDLE", 81},
    {"ANIM_STATE_STR_CROWDGROUP02_IDLE", 82},
    {"ANIM_STATE_STR_CROWDGROUP03_IDLE", 83},
    {"ANIM_STATE_REC_CROWDGROUP01_IDLE", 84},
    {"ANIM_STATE_REC_CROWDGROUP02_IDLE", 85},
    {"ANIM_STATE_EAR_CROWDGROUP01_IDLE", 78},
    {"ANIM_STATE_EAR_CROWDGROUP02_IDLE", 79},
    {"ANIM_STATE_EAR_CROWDGROUP03_IDLE", 80},
    {"ANIM_STATE_TRN_CROWDGROUP01_IDLE", 86},
    {"ANIM_STATE_TRN_CROWDGROUP02_IDLE", 87},
    {"ANIM_STATE_TRN_CROWDGROUP03_IDLE", 88},
    {"ANIM_STATE_ALL_CROWDGROUP01_IDLE", 89},
    {"ANIM_STATE_ALL_CROWDGROUP02_IDLE", 90},
    {"ANIM_STATE_ALL_CROWDGROUP03_IDLE", 91},
    {"ANIM_STATE_IRT_CROWDGROUP01_IDLE", 92},
    {"ANIM_STATE_IRT_CROWDGROUP02_IDLE", 93},
    {"ANIM_STATE_IRT_CROWDGROUP03_IDLE", 94},
    {"ANIM_STATE_CON_CROWDGROUP01_IDLE", 95},
    {"ANIM_STATE_CON_CROWDGROUP02_IDLE", 96},
    {"ANIM_STATE_CON_CROWDGROUP03_IDLE", 97},
    {"ANIM_STATE_LEG_CROWDGROUP01_IDLE", 98},
    {"ANIM_STATE_LEG_CROWDGROUP02_IDLE", 99},
    {"ANIM_STATE_LEG_CROWDGROUP03_IDLE", 100},
};
BigObjNameId_t _BigObj_aPartNames[32] = {
    {"NONE", -1},
    {"Bron_GarbageCan", 0},
    {"Bron_FireHydrant", 0},
    {"Bron_Pigeon", 0},
    {"AQA_Oildrum01", 0},
    {"Lati_Melons", 0},
    {"Lati_Oranges", 0},
    {"BEAC_Seagull", 0},
    {"Junk_Oildrum", 0},
    {"Junk_crate", 0},
    {"ROOF_bucket01", 0},
    {"ROOF_bucket02", 0},
    {"Lati_Rooster", 0},
    {"Ware_Oildrum", 0},
    {"Ware_crate", 0},
    {"LEGE_GarbageCan", 0},
    {"Obj_Trash02", 0},
    {"Obj_Trash03", 0},
    {"Obj_Trash04", 0},
    {"Obj_Trash05", 0},
    {"Obj_Trash06", 0},
    {"Obj_Trash07", 0},
    {"Obj_Trash08", 0},
    {"Obj_Barre01", 0},
    {"Obj_Barre02", 0},
    {"Obj_Barre03", 0},
    {"Obj_Barre04", 0},
    {"Obj_Barre05", 0},
    {"Obj_Barre06", 0},
    {"Obj_Barre07", 0},
    {"Obj_Barre08", 0},
    {"Obj_Barre09", 0},
};
BigObjSwapStateName_t _BigObj_aSwapStates[63] = {
    {"NONE", "NONE", -1},
    {"Bron_GarbageCan", "Normal", 0},
    {"Bron_GarbageCan", "Damaged", 1},
    {"Bron_FireHydrant", "Closed", 0},
    {"Bron_FireHydrant", "Open", 1},
    {"Bron_Pigeon", "Normal", 0},
    {"Bron_Pigeon", "Flying", 1},
    {"AQA_Oildrum01", "Normal", 0},
    {"AQA_Oildrum01", "Damaged", 1},
    {"Lati_Melons", "Normal", 0},
    {"Lati_Melons", "Damaged", 1},
    {"Lati_Oranges", "Normal", 0},
    {"Lati_Oranges", "Damaged", 1},
    {"BEAC_Seagull", "Normal", 0},
    {"BEAC_Seagull", "Flying", 1},
    {"Junk_Oildrum", "Normal", 0},
    {"Junk_Oildrum", "Damaged", 1},
    {"Junk_crate", "Normal", 0},
    {"Junk_crate", "Damaged", 1},
    {"ROOF_bucket01", "Normal", 0},
    {"ROOF_bucket01", "Damaged", 1},
    {"ROOF_bucket02", "Normal", 0},
    {"ROOF_bucket02", "Damaged", 1},
    {"Lati_Rooster", "Normal", 0},
    {"Lati_Rooster", "Flying", 1},
    {"Ware_Oildrum", "Normal", 0},
    {"Ware_Oildrum", "Damaged", 1},
    {"Ware_crate", "Normal", 0},
    {"Ware_crate", "Damaged", 1},
    {"LEGE_GarbageCan", "Normal", 0},
    {"LEGE_GarbageCan", "Damaged", 1},
    {"Obj_Barre01", "Normal", 0},
    {"Obj_Barre01", "Damaged", 1},
    {"Obj_Barre02", "Normal", 0},
    {"Obj_Barre02", "Damaged", 1},
    {"Obj_Barre03", "Normal", 0},
    {"Obj_Barre03", "Damaged", 1},
    {"Obj_Barre04", "Normal", 0},
    {"Obj_Barre04", "Damaged", 1},
    {"Obj_Barre05", "Normal", 0},
    {"Obj_Barre05", "Damaged", 1},
    {"Obj_Barre06", "Normal", 0},
    {"Obj_Barre06", "Damaged", 1},
    {"Obj_Barre07", "Normal", 0},
    {"Obj_Barre07", "Damaged", 1},
    {"Obj_Barre08", "Normal", 0},
    {"Obj_Barre08", "Damaged", 1},
    {"Obj_Barre09", "Normal", 0},
    {"Obj_Barre09", "Damaged", 1},
    {"Obj_Trash02", "Normal", 0},
    {"Obj_Trash02", "Damaged", 1},
    {"Obj_Trash03", "Normal", 0},
    {"Obj_Trash03", "Damaged", 1},
    {"Obj_Trash04", "Normal", 0},
    {"Obj_Trash04", "Damaged", 1},
    {"Obj_Trash05", "Normal", 0},
    {"Obj_Trash05", "Damaged", 1},
    {"Obj_Trash06", "Normal", 0},
    {"Obj_Trash06", "Damaged", 1},
    {"Obj_Trash07", "Normal", 0},
    {"Obj_Trash07", "Damaged", 1},
    {"Obj_Trash08", "Normal", 0},
    {"Obj_Trash08", "Damaged", 1},
};
BigObjSoundNameId_t _BigObj_aSoundNames[38] = {
    {"NONE", 0},
    {"Hit_Barrel", 62},
    {"Hit_Chainlink_Fence", 63},
    {"Hit_Cone", 64},
    {"Hit_Container", 65},
    {"Hit_Grass", 66},
    {"Hit_Iron_Fence", 67},
    {"Hit_Metal_Large_Object", 68},
    {"Hit_Metal_Small_Object", 69},
    {"Hit_Pipe", 70},
    {"Hit_Player", 71},
    {"Hit_Sand", 72},
    {"Hit_Solid_Wall", 73},
    {"Hit_Tire", 74},
    {"Hit_Tree", 75},
    {"Hit_Wire", 76},
    {"Hit_Wood", 77},
    {"Hit_Wood_Fence", 78},
    {"Idle_Bus", 79},
    {"Idle_Truck", 80},
    {"Idle_Vehicle", 81},
    {"Idle_Police", 82},
    {"Idle_GolfCart", 83},
    {"Idle_IdleTruck", 84},
    {"Idle_LargeFan", 86},
    {"Idle_ACUnit", 87},
    {"Idle_Subway", 85},
    {"Hit_Fence", 63},
    {"Hit_ChainlinkFence", 63},
    {"Hit_Pipes", 70},
    {"Hit_Wall", 73},
    {"Hit_Metal_LargeObject", 68},
    {"Hit_Metal_SmallObject", 69},
    {"Hit_Metal", 69},
    {"Hit_Wood_Box", 77},
    {"Hit_Can", 62},
    {"Hit_Crowd", 71},
    {"Idle_Train", 85},
};
BigObjNameId_t _BigObj_aTravelDims[3] = {
    {"U", 0},
    {"V", 1},
    {"NULL", -1},
};
BigObjNameId_t _BigObj_aStepTypes[3] = {
    {"FULL_FRAME", 0},
    {"INC_FRAME", 1},
    {"NULL", -1},
};
DynObjSkeletonCache_t *_DynObj_apSkeletonCache[104] = {0};

BigObjAnimHandlerFunc _BigObjAnim_aHandlers[102];

void BigObjAnimReadPose(AnimPose_t *pPose, BitStream_t *pStream, unsigned int count)
{
    short *pValue = pPose->mUnknown48;
    unsigned int groups = count * 3 / 5;
    unsigned int rest = count * 3 % 5;
    unsigned int i;
    long long bits;

    for (i = 0; i < groups; i++) {
        bits = ReadBitStream(pStream, 60);
        pValue[0] = (bits << 4 >> 48) & ~15;
        pValue[1] = (bits << 16 >> 48) & ~15;
        pValue[2] = (bits << 28 >> 48) & ~15;
        pValue[3] = (bits << 40 >> 48) & ~15;
        pValue[4] = (bits << 52 >> 48) & ~15;
        pValue += 5;
    }
    bits = ReadBitStream(pStream, rest * 12);
    for (i = 0; i < rest; i++) {
        pValue[i] = (bits << (64 - (rest - i) * 12) >> 48) & ~15;
    }
    ReplayReadPacked3(pStream, pPose->mUnknown8, 16, 512.0f);
    pPose->mUnknown32 = (int)ReadBitStream(pStream, 16) << 8;
}

int BigObjAnimPickVariant(BigObjAnimVariantTable_t *pTable, unsigned char *pKey);
int BigObjAnimPickMatchedVariant(BigObjAnimVariantTable_t *pTable, unsigned char *pKey);

int BigObjAnimPlayVariant(BigObjAnimVariantTable_t *pTable, void *a, void *b, BigObjInst *pObject, unsigned short c)
{
    int index = BigObjAnimPickVariant(pTable, &pObject->mUnknown428->mUnknown1704);

    if (index >= 0) {
        AnimChanStartAnim(a, b, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, c, pObject, 1.0f);
    }
    return 0;
}

int BigObjAnimPlayMatchedVariant(BigObjAnimVariantTable_t *pTable, void *a, void *b, BigObjInst *pObject, unsigned short c)
{
    int index = BigObjAnimPickMatchedVariant(pTable, &pObject->mUnknown428->mUnknown1704);

    if (index >= 0) {
        AnimChanStartAnim(a, b, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, c, pObject, 1.0f);
    }
    return 0;
}

int BigObjAnimOnVariant(BigObjAnimVariantTable_t *pTable, unsigned short c, void *a, void *b, BigObjInst *pObject, int skip)
{
    if (!skip) {
        BigObjAnimPlayVariant(pTable, a, b, pObject, c);
    }
    return 0;
}

int BigObjAnimOnMatchedVariant(BigObjAnimVariantTable_t *pTable, unsigned short c, void *a, void *b, BigObjInst *pObject, int skip)
{
    if (!skip) {
        BigObjAnimPlayMatchedVariant(pTable, a, b, pObject, c);
    }
    return 0;
}

int BigObjAnimOnSequence(BigObjAnimVariantTable_t *pTable, unsigned short c, void *a, void *b, BigObjInst *pObject, int skip)
{
    if (!skip) {
        BigObjPhysics_t *pExtra = pObject->mUnknown428;
        unsigned char b0 = pExtra->mUnknown1704;
        unsigned char b1 = pExtra->mUnknown1705;
        unsigned char b2 = pExtra->mUnknown1706;
        unsigned char b3 = pExtra->mUnknown1707;
        AnimSeqncrStatic_t *pFrame = AnimSeqncrGetStaticPtr(fn_80093BAC(b0, b1), b2);

        AnimChanStartAnim(a, b, AnimFileGetSlotFromFileNum(pFrame->mUnknown42 | 0x4000, pFrame->mUnknown14), b3, c, pObject, 1.0f);
    }
    return 0;
}

void BigObjAnimPoseFromSkeleton(AnimPose_t *pPose, AnimSkeleton_t *pSkeleton)
{
    unsigned int i;

    for (i = 0; i < pSkeleton->mUnknown6; i++) {
        pPose->mUnknown48[i * 3 + 0] = pSkeleton->mUnknown1040[i][0] << 4;
        pPose->mUnknown48[i * 3 + 1] = pSkeleton->mUnknown1040[i][1] << 4;
        pPose->mUnknown48[i * 3 + 2] = pSkeleton->mUnknown1040[i][2] << 4;
    }
}

int BigObjAnimPickVariant(BigObjAnimVariantTable_t *pTable, unsigned char *pKey)
{
    int best = -1;
    signed char bestIndex = -1;
    int i;

    for (i = 0; i < pTable->mCount; i++) {
        BigObjAnimVariant_t *pVariant = pTable->mEntries[i].mpVariant;
        int score = SyncRandGetRange(1, 10);
        int j;

        for (j = 0; j < 4; j++) {
            if (pKey[j] == pVariant->mKey[j]) {
                score += (10 - j) * 10;
            }
        }
        if (score > best) {
            best = score;
            bestIndex = i;
        }
    }
    return bestIndex;
}

int BigObjAnimPickMatchedVariant(BigObjAnimVariantTable_t *pTable, unsigned char *pKey)
{
    int best = -1;
    signed char bestIndex = -1;
    int i;

    for (i = 0; i < pTable->mCount; i++) {
        BigObjAnimVariant_t *pVariant = pTable->mEntries[i].mpVariant;
        int score = SyncRandGetRange(0, 10);
        int j;

        for (j = 0; j < 4; j++) {
            if (pKey[j] == pVariant->mKey[j]) {
                score += (10 - j) * 10;
            } else if (j == 0) {
                score = 0;
                break;
            }
        }
        if (score > best) {
            best = score;
            bestIndex = i;
        }
    }
    return bestIndex;
}

void BigObjAnimInitHandlers(BigObjAnimHandlerFunc *pHandlers, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        pHandlers[i] = BigObjAnimOnVariant;
    }
    pHandlers[6] = BigObjAnimOnMatchedVariant;
    pHandlers[23] = BigObjAnimOnMatchedVariant;
    pHandlers[24] = BigObjAnimOnMatchedVariant;
    pHandlers[7] = BigObjAnimOnMatchedVariant;
    pHandlers[101] = BigObjAnimOnSequence;
}

void BigObjAnimBlend(BigObjPhysics_t *pExtra, BigObj_t *pItem, int a) { BigObjAnimBlendPose(pExtra, pItem, a, 0); }

void BigObjAnimBlendRoot(BigObj_t *pItem, void *a, int b, void *c) { BigObjAnimBlendRootAngles(pItem, a, b, c); }

void BigObjAnimInitObject(BigObjInst *pObject, int index)
{
    AnimSkeleton_t *pSkeleton = BigObjGetSkeleton(index);

    if (pSkeleton) {
        BigObj_t *pPlaced = BigObjGet(index);
        unsigned short count = pSkeleton->mUnknown6;
        int size = count * 64;

        pPlaced->mUnknown228 = fn_801D2B7C(size, 0, 0);
        memset(pPlaced->mUnknown228, 0, size);
        if (pPlaced) {
            pPlaced->mUnknown172.mUnknown4 = count + 1;
            pPlaced->mUnknown172.mUnknown0 = 0x100;
            pPlaced->mUnknown172.mUnknown2 = 0x202;
            pPlaced->mUnknown172.mUnknown48 = BigObjAnimAllocSamples(count);
            pPlaced->mUnknown172.mUnknown52 = (float (*)[4][4])pPlaced->mUnknown228;
            BigObjAnimPoseFromSkeleton(&pPlaced->mUnknown172, pSkeleton);
        }
        AnimInitHeader((AnimHeader_t *)pObject->mUnknown428->mUnknown48, 0, 10, 10);
        AnimChanInitChannels(pObject->mUnknown428->mUnknown48, pObject->mUnknown428->mUnknown60);
        AnimStInitStructure(pObject->mUnknown428->mUnknown1300);
        pObject->mUnknown428->mUnknown1708 = 0;
    }
}

void BigObjAnimRegisterHandlers(void)
{
    BigObjAnimInitHandlers(_BigObjAnim_aHandlers, 102);
    fn_801BE030(10, &_BigObjAnim_sHandlerSet);
}

void BigObjAnimWritePose(AnimPose_t *pPose, BitStream_t *pStream, unsigned int count)
{
    unsigned short *pValue = (unsigned short *)pPose->mUnknown48;
    unsigned int groups = count * 3 / 5;
    unsigned int rest = count * 3 % 5;
    unsigned int i;
    unsigned long long bits;

    for (i = 0; i < groups; i++) {
        bits = (unsigned long long)(pValue[0] >> 4) << 48;
        bits |= (unsigned long long)(pValue[1] >> 4) << 36;
        bits |= (unsigned long long)(pValue[2] >> 4) << 24;
        bits |= (unsigned long long)(pValue[3] >> 4) << 12;
        bits |= (unsigned long long)(pValue[4] >> 4);
        fn_80191068(pStream, bits, 60);
        pValue += 5;
    }
    bits = 0;
    for (i = 0; i < rest; i++) {
        bits |= (unsigned long long)(pValue[i] >> 4) << (rest - 1 - i) * 12;
    }
    fn_80191068(pStream, bits, rest * 12);
    ReplayWritePacked3(pStream, pPose->mUnknown8, 16, 512.0f);
    fn_80191068(pStream, pPose->mUnknown32 >> 8, 16);
}

void BigObjAnimReplayBlend(BigObj_t *pObject, BigObjInst *pLinked, BitStream_t *pStream0, BitStream_t *pStream1,
                 BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    short values1[192];
    short values2[192];
    short values3[192];
    AnimPose_t pose1;
    AnimPose_t pose3;
    AnimPose_t pose2;
    unsigned int count = pObject->mUnknown172.mUnknown4 - 1;

    pose1.mUnknown48 = values1;
    pose3.mUnknown48 = values3;
    pose2.mUnknown48 = values2;
    BigObjAnimReadPose(&pose1, pStream1, count);
    BigObjAnimReadPose(&pObject->mUnknown172, pStream0, count);
    if (pStream2) {
        BigObjAnimReadPose(&pose2, pStream2, count);
    }
    if (pStream3) {
        BigObjAnimReadPose(&pose3, pStream3, count);
    }
    if (!pStream2) {
        if (!pStream3) {
            AnimBlendPose(&pObject->mUnknown172, &pose1, 0, 0, t, 0);
        } else {
            AnimBlendPose(&pObject->mUnknown172, &pose1, 0, &pose3, t, 0);
        }
    } else if (!pStream3) {
        AnimBlendPose(&pObject->mUnknown172, &pose1, &pose2, 0, t, 0);
    } else {
        AnimBlendPose(&pObject->mUnknown172, &pose1, &pose2, &pose3, t, 0);
    }
}

void BigObjAnimLoadResident(int a)
{
    switch (fn_800A3444()) {
    case 4:
        AnimFileLoadResident(0x66, a);
        AnimFileLoadResident(0x67, a);
        AnimFileLoadResident(0x68, a);
        break;
    case 0:
        AnimFileLoadResident(0x69, a);
        AnimFileLoadResident(0x6A, a);
        AnimFileLoadResident(0x6B, a);
        break;
    case 3:
        AnimFileLoadResident(0x6C, a);
        AnimFileLoadResident(0x6D, a);
        AnimFileLoadResident(0x6E, a);
        break;
    case 5:
        AnimFileLoadResident(0x6F, a);
        AnimFileLoadResident(0x70, a);
        AnimFileLoadResident(0x71, a);
        break;
    case 7:
        AnimFileLoadResident(0x72, a);
        AnimFileLoadResident(0x73, a);
        break;
    case 10:
        AnimFileLoadResident(0x74, a);
        AnimFileLoadResident(0x75, a);
        AnimFileLoadResident(0x76, a);
        break;
    case 6:
        AnimFileLoadResident(0x7A, a);
        AnimFileLoadResident(0x7B, a);
        AnimFileLoadResident(0x7C, a);
        break;
    case 2:
        AnimFileLoadResident(0x77, a);
        AnimFileLoadResident(0x78, a);
        AnimFileLoadResident(0x79, a);
        break;
    case 1:
        AnimFileLoadResident(0x7D, a);
        AnimFileLoadResident(0x7E, a);
        AnimFileLoadResident(0x7F, a);
        break;
    case 8:
        AnimFileLoadResident(0x80, a);
        AnimFileLoadResident(0x81, a);
        AnimFileLoadResident(0x82, a);
        break;
    case 11:
        AnimFileLoadResident(0x74, a);
        AnimFileLoadResident(0x75, a);
        AnimFileLoadResident(0x76, a);
        break;
    }
}

void BigObjAnimClearFlags(BigObjPhysics_t *pExtra) { pExtra->mUnknown1708 &= ~0x78; }

/* Clears flag bits 0x78 of the Extra block and restarts its fn_801BE068 entry. */
static inline void _BigObjAnimRestartKey(BigObjInst *pObject, unsigned short key, float value)
{
    BigObjAnimClearFlags(pObject->mUnknown428);
    fn_801BE068(pObject->mUnknown428->mUnknown1300, pObject->mUnknown428->mUnknown48, pObject->mUnknown428->mUnknown60,
                key, value, pObject);
}

void BigObjAnimRestart(BigObjInst *pObject, unsigned char b1, unsigned char b0, unsigned char b3,
                 unsigned char b2)
{
    pObject->mUnknown428->mUnknown50 = 10;
    pObject->mUnknown428->mUnknown1704 = b0;
    pObject->mUnknown428->mUnknown1705 = b1;
    pObject->mUnknown428->mUnknown1706 = b2;
    pObject->mUnknown428->mUnknown1707 = b3;
    _BigObjAnimRestartKey(pObject, 0x65, 1.0f);
}

int BigObjFindNameId(const char *pName, BigObjNameId_t *pTable)
{
    int i;

    for (i = 0; pTable[i].mId != -1; i++) {
        if (strcmp(pName, pTable[i].mName) == 0) {
            return pTable[i].mId;
        }
    }
    return -1;
}

void BigObjRestoreState(BigObj_t *pObject)
{
    BigObjFlags_t *pFlags;
    BigObjNode_t *pNode;

    pObject->mUnknown472->mState.mUnknown0 = pObject->mUnknown472->mState.mUnknown104;
    pObject->mUnknown472->mState.mUnknown4 = pObject->mUnknown472->mState.mUnknown108;
    pObject->mUnknown472->mState.mUnknown8 = pObject->mUnknown472->mState.mUnknown112;
    pObject->mUnknown472->mState.mUnknown88 = pObject->mUnknown472->mState.mUnknown116;
    pObject->mUnknown472->mState.mUnknown92 = pObject->mUnknown472->mState.mUnknown120;
    pObject->mUnknown472->mState.mUnknown96 = pObject->mUnknown472->mState.mUnknown124;
    pObject->mUnknown472->mState.mUnknown100 = pObject->mUnknown472->mState.mUnknown128;
    pObject->mUnknown472->mState.mUnknown24 = pObject->mUnknown472->mState.mUnknown132;
    if (pObject->mUnknown472->mUnknown428) {
        pObject->mUnknown472->mUnknown428->mUnknown56 = pObject->mUnknown472->mState.mUnknown132;
    }
    BigObjSetFlag(pObject);
    pFlags = pObject->mUnknown476;
    if (pFlags && pFlags->mUnknown20 != -1) {
        PhysSetBodyPose(pFlags->mUnknown20, &pObject->mUnknown472->mState.mUnknown104, &pObject->mUnknown472->mState.mUnknown116);
        PhysSleepBody(pFlags->mUnknown20);
    }
    for (pNode = pObject->mUnknown472->mUnknown312; pNode; pNode = pNode->mpNext) {
        if (pNode->mUnknown104 != -1 && pNode->mUnknown108 != -1) {
            DynObjSetPartState(pObject, pNode->mUnknown104, 0);
        }
    }
}

void BigObjKeepInBounds(BigObj_t *pObject)
{
    float y = fabsf(pObject->mUnknown472->mState.mUnknown4);
    int outY = y > ScrmGetEndLineY() + _BigObj_fBoundsMargin;
    float x = fabsf(pObject->mUnknown472->mState.mUnknown0);
    int outX = x > ScrmGetSidelineX() + _BigObj_fBoundsMargin;

    if (outX || outY) {
        Vector_80039F5C pos;

        pos.mX = pObject->mUnknown472->mState.mUnknown0;
        pos.mY = pObject->mUnknown472->mState.mUnknown4;
        pos.mZ = pObject->mUnknown472->mState.mUnknown8;
        if (outX) {
            float margin = _BigObj_fBoundsJitter * SyncRandGetFloat(0);

            pos.mX = pObject->mUnknown472->mState.mUnknown0 < 0.0f ? _BigObj_fBoundsInset - ScrmGetSidelineX() + margin
                                                                 : ScrmGetSidelineX() - (_BigObj_fBoundsInset + margin);
        }
        if (outY) {
            float margin = _BigObj_fBoundsJitter * SyncRandGetFloat(0);

            pos.mY = pObject->mUnknown472->mState.mUnknown4 < 0.0f ? _BigObj_fBoundsInset - ScrmGetEndLineY() + margin
                                                                 : ScrmGetEndLineY() - (_BigObj_fBoundsInset + margin);
        }
        pObject->mUnknown472->mState.mUnknown0 = pos.mX;
        pObject->mUnknown472->mState.mUnknown4 = pos.mY;
        pObject->mUnknown472->mState.mUnknown8 = pos.mZ;
        BigObjSetFlag(pObject);
        if (pObject->mUnknown476 && pObject->mUnknown476->mUnknown20 != -1) {
            PhysSetBodyPose(pObject->mUnknown476->mUnknown20, &pos.mX, &pObject->mUnknown472->mState.mUnknown88);
        }
    }
}

int BigObjOnAnimEvent(BigObjInst *pObject, BigObj_t *pOwner, int mode)
{
    BigObjPhysics_t *pExtra = pObject->mUnknown428;

    if (mode == 0) {
        if (pObject->mUnknown196 != -1) {
            pExtra->mUnknown1704 = 1;
            _BigObjAnimRestartKey(pObject, pObject->mUnknown196, 1.0f);
        }
        pObject->mUnknown200.mStep = 0;
        pObject->mUnknown200.mPhase = 0;
        pObject->mUnknown200.mTime = 0.0f;
        if (pOwner->mUnknown476 && pOwner->mUnknown476->mUnknown20 != -1) {
            PhysSleepBody(pOwner->mUnknown476->mUnknown20);
        }
    } else if (mode == 2) {
        if (pObject->mUnknown192) {
            pObject->mUnknown192(pOwner);
        }
        if (pOwner->mUnknown476 && pOwner->mUnknown476->mUnknown20 != -1) {
            Vector_80039F5C from;
            Vector_80039F5C to;
            FieldPoint_t center;
            FieldPoint_t offset;

            from.mX = pObject->mState.mUnknown0;
            from.mY = pObject->mState.mUnknown4;
            from.mZ = pObject->mState.mUnknown8;
            to.mX = pObject->mState.mUnknown0;
            to.mY = pObject->mState.mUnknown4;
            to.mZ = pObject->mState.mUnknown8;
            if (ScrmIsFieldFlipped()) {
                from.mX = -from.mX;
                from.mY = -from.mY;
            }
            center = ScrmGetBallSpot();
            Vec2Sub(&offset, &from, &center);
            {
                float length = Vec2Magnitude(&offset);

                if (length < 6.0f) {
                    if (length <= 0.001f) {
                        offset.mY = 6.0f;
                        offset.mX = 0.0f;
                    } else {
                        Vec2Scale(&offset, &offset, 6.0f / length);
                    }
                    Vec2Add(&to, &center, &offset);
                    if (ScrmIsFieldFlipped()) {
                        to.mX = -to.mX;
                        to.mY = -to.mY;
                    }
                    pObject->mState.mUnknown0 = to.mX;
                    pObject->mState.mUnknown4 = to.mY;
                    pObject->mState.mUnknown8 = to.mZ;
                    PhysSetObjectPosition(pOwner, &pObject->mState.mUnknown0);
                }
            }
        }
    } else {
        BigObjUpdatePartTimers(pOwner);
        if (pObject->mUnknown408 != 0.0f) {
            PhysDampLinear(pOwner, pObject->mUnknown408);
        }
        if (pObject->mUnknown412 != 0.0f) {
            PhysDampAngular(pOwner, pObject->mUnknown412);
        }
        if (pExtra && (pExtra->mUnknown1708 & 1)) {
            if (pObject->mUnknown196 != -1) {
                pExtra->mUnknown1704 = pObject->mUnknown424;
                _BigObjAnimRestartKey(pObject, pObject->mUnknown196, 1.0f);
            }
            pExtra->mUnknown1708 &= ~1;
        }
        if (pObject->mUnknown380) {
            Vector_80039F5C pos;
            float t;
            BigObjNode_t *pNode;

            pObject->mUnknown380 = 0;
            pos.mX = pObject->mUnknown360.mX;
            pos.mY = pObject->mUnknown360.mY;
            pos.mZ = pObject->mUnknown360.mZ;
            t = pObject->mUnknown372;
            if (ScrmIsFieldFlipped()) {
                pos.mX = -pos.mX;
                pos.mY = -pos.mY;
            }
            if (pObject->mUnknown382) {
                PhysApplyImpulse(pOwner, &pObject->mUnknown348);
            }
            for (pNode = pObject->mUnknown312; pNode; pNode = pNode->mpNext) {
                unsigned int count;

                if (strcmp(pNode->mName, pObject->mUnknown316) != 0) {
                    continue;
                }
                if (!pObject->mUnknown381) {
                    if (pNode->mId != -1 && fn_801BE648(pObject->mUnknown428->mUnknown1300) == pObject->mUnknown196) {
                        pExtra->mUnknown1704 = pObject->mUnknown424;
                        pExtra->mUnknown1705 = _BigObj_aOctantStates[(((MathArcTan2(pObject->mUnknown352, pObject->mUnknown348) -
                                                               (pObject->mState.mUnknown24 + 0x400000)) &
                                                              0xFFFFFF) +
                                                             0x100000) >>
                                                                21 &
                                                            7];
                        _BigObjAnimRestartKey(pObject, pNode->mId, 1.0f);
                    }
                    if (pNode->mUnknown104 != -1 && pNode->mUnknown108 != -1 && t > pNode->mUnknown112) {
                        if (pNode->mUnknown116) {
                            pNode->mUnknown120 = pNode->mUnknown116;
                        } else {
                            DynObjSetPartState(pOwner, pNode->mUnknown104, pNode->mUnknown108);
                        }
                        if (pNode->mUnknown124) {
                            BigObjClearFlag(pOwner);
                        }
                    }
                    if (pNode->mUnknown100 != 15) {
                        LevelSetSurface(pNode->mUnknown96, pNode->mUnknown100);
                        pNode->mUnknown100 = 15;
                    }
                    if (pNode->mUnknown68) {
                        pNode->mUnknown68 = 0;
                        pObject->mUnknown200.mActive = 1;
                        pObject->mUnknown200.mPhase = 3;
                        pObject->mUnknown200.mUnknown8 = pNode->mUnknown76;
                        pObject->mUnknown200.mUnknown4 = pNode->mUnknown72;
                        pObject->mUnknown200.mTime = 0.0f;
                        pObject->mUnknown200.mStep = 0;
                    }
                    BigObjEmitParticles(pNode->mUnknown128, t, pObject, pOwner);
                    count = (unsigned int)pNode->mUnknown112;
                } else {
                    Ball_t *pBall = BallGetCurrent();

                    if (pBall) {
                        count = pBall->mState.mIndex;
                    } else {
                        count = (unsigned int)pNode->mUnknown112;
                    }
                }
                if (pNode->mUnknown92) {
                    AudmonEventPostId(pNode->mUnknown92, &pos, pObject->mUnknown376, (unsigned int)t, pObject->mUnknown381,
                                count);
                }
                break;
            }
        } else {
            Vector_80039F5C pos;

            pos.mX = pObject->mState.mUnknown0;
            pos.mY = pObject->mState.mUnknown4;
            pos.mZ = pObject->mState.mUnknown8;
            if (ScrmIsFieldFlipped()) {
                pos.mX = -pos.mX;
                pos.mY = -pos.mY;
            }
            if (pObject->mUnknown200.mActive) {
                BigObjCycle_t *pCycle = &pObject->mUnknown200;

                pCycle->mTime += gFrameTimeScale * (1.0f / 60.0f);
                switch (pCycle->mPhase) {
                case 0:
                    if (pCycle->mTime >= pCycle->mUnknown4) {
                        pCycle->mPhase = 2;
                        pCycle->mTime = 0.0f;
                    }
                    break;
                case 1:
                    if (pCycle->mTime >= pCycle->mUnknown4) {
                        pCycle->mPhase = 3;
                        pCycle->mTime = 0.0f;
                    }
                    break;
                case 2:
                    if (pCycle->mTime >= pCycle->mUnknown8) {
                        pCycle->mStep++;
                        pCycle->mPhase = 0;
                        pCycle->mTime = 0.0f;
                        pCycle->mStep %= pOwner->mUnknown248;
                    }
                    break;
                case 3:
                    if (pCycle->mTime >= pCycle->mUnknown8) {
                        pCycle->mStep++;
                        if (pCycle->mStep == pOwner->mUnknown248 - 1) {
                            pCycle->mPhase = 4;
                            pCycle->mActive = 0;
                        } else {
                            pCycle->mPhase = 1;
                            pCycle->mTime = 0.0f;
                        }
                    }
                    break;
                case 4:
                    break;
                }
            }
            if (pObject->mUnknown308) {
                AudmonEventPost(pObject->mUnknown308, &pos);
            }
        }
    }
    return 1;
}

void BigObjParseAnimEvent(int handle, BigObjInst *pObject)
{
    char text[64];
    char state[64];
    int position = ObjParseGetCursor(handle);

    ObjParseFindChild(handle, "anim");
    if (ObjParseGetString(handle, "emotion2State", state, 64)) {
        pObject->mUnknown196 = BigObjFindEmotionState(state);
    } else {
        pObject->mUnknown196 = -1;
    }
    ObjParseGetString(handle, "emotion2State", state, 64);
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "animPal")) {
        pObject->mUnknown200.mActive = 1;
        pObject->mUnknown200.mUnknown8 = ObjParseGetFloat(handle, "delay");
        pObject->mUnknown200.mUnknown4 = ObjParseGetFloat(handle, "rate");
    }
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "animUV")) {
        pObject->mUnknown224 = 1;
        pObject->mUnknown288 = 0;
        pObject->mUnknown268 = ObjParseGetFloat(handle, "delay");
        pObject->mUnknown272 = (unsigned int)ObjParseGetFloat(handle, "row");
        pObject->mUnknown276 = (unsigned int)ObjParseGetFloat(handle, "column");
        pObject->mUnknown292 = pObject->mUnknown272 * pObject->mUnknown276;
        ObjParseGetFloats(handle, "rate", pObject->mUnknown228, pObject->mUnknown292);
        ObjParseGetString(handle, "travelDim", text, 64);
        pObject->mUnknown300 = BigObjFindNameId(text, _BigObj_aTravelDims);
        ObjParseGetString(handle, "stepType", text, 64);
        pObject->mUnknown304 = BigObjFindNameId(text, _BigObj_aStepTypes);
        pObject->mUnknown296 = 0.0f;
        pObject->mUnknown280 = 0;
        pObject->mUnknown284 = 0;
    } else {
        pObject->mUnknown224 = 0;
    }
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "sound")) {
        unsigned short sound;

        ObjParseGetString(handle, "name", text, 64);
        sound = BigObjFindSoundId(text);
        pObject->mUnknown308 = sound;
        if ((unsigned short)(sound - 79) <= 8) {
            pObject->mUnknown310 = sound - 79;
        }
    } else {
        pObject->mUnknown308 = 0;
    }
    ObjParseSetCursor(handle, position);
}

void BigObjParseSwapEvent(int handle, BigObjInst *pObject)
{
    char text[64];
    char state[64];
    int position = ObjParseGetCursor(handle);
    BigObjNode_t *pNode = (BigObjNode_t *)fn_801D2B7C(sizeof(BigObjNode_t), 0, 0);

    memset(pNode, 0, sizeof(BigObjNode_t));
    pNode->mpNext = pObject->mUnknown312;
    pNode->mUnknown108 = -1;
    pNode->mUnknown112 = 0.0f;
    pNode->mUnknown124 = 0;
    pNode->mUnknown128 = 0;
    pNode->mId = -1;
    pNode->mUnknown104 = -1;
    pNode->mUnknown116 = 0;
    pNode->mUnknown120 = 0;
    strcpy(pNode->mName, "");
    pObject->mUnknown312 = pNode;
    if (ObjParseGetString(handle, "name", text, 64)) {
        strcpy(pNode->mName, text);
    }
    if (ObjParseFindChild(handle, "anim") && ObjParseGetString(handle, "emotion2State", text, 64)) {
        pNode->mId = BigObjFindEmotionState(text);
    }
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "swapPart")) {
        pNode->mUnknown112 = ObjParseGetFloat(handle, "force");
        if (ObjParseGetString(handle, "id", text, 64)) {
            pNode->mUnknown104 = BigObjFindPartId(text);
        }
        if (ObjParseGetString(handle, "swapState", state, 64)) {
            pNode->mUnknown108 = BigObjFindSwapState(text, state);
        }
        {
            float rate = gFrameTimeScale;

            pNode->mUnknown116 = (unsigned int)(60.0f / rate * ObjParseGetFloat(handle, "delay"));
        }
        pNode->mUnknown124 = ObjParseGetInt(handle, "bDisableCollisions");
    }
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "particle")) {
        do {
            BigObjEmitter_t *pEmitter = (BigObjEmitter_t *)fn_801D2B7C(sizeof(BigObjEmitter_t), 0, 0);

            memset(pEmitter, 0, sizeof(BigObjEmitter_t));
            pEmitter->mpNext = pNode->mUnknown128;
            pNode->mUnknown128 = pEmitter;
            pEmitter->mUnknown4 = -1;
            pEmitter->mUnknown8 = 0;
            pEmitter->mUnknown0 = -1;
            pEmitter->mUnknown40 = 0;
            pEmitter->mUnknown36 = 0.0f;
            if (ObjParseGetString(handle, "emitPoint", text, 64) && strcmp(text, "IMPACT") == 0) {
                pEmitter->mUnknown40 = 1;
            }
            if (ObjParseGetString(handle, "psf", text, 64)) {
                int index = ResFindIndexByName(fn_800C47C4(), text);

                if (index == -1) {
                    pEmitter->mUnknown0 = 21;
                } else {
                    pEmitter->mUnknown0 = BigObjEffectSlotAcquire(index);
                    if (pEmitter->mUnknown0 != 21) {
                        ParticleSysSetEffectFile(pEmitter->mUnknown0, index);
                    }
                }
            }
            pEmitter->mUnknown36 = ObjParseGetFloat(handle, "force");
            if (!pEmitter->mUnknown40) {
                float swap;

                ObjParseGetVector(handle, "emitTranslate", pEmitter->mUnknown12);
                swap = pEmitter->mUnknown12[1];
                pEmitter->mUnknown12[1] = pEmitter->mUnknown12[2];
                pEmitter->mUnknown12[2] = swap;
                ObjParseGetVector(handle, "emitRotate", pEmitter->mUnknown24);
                swap = pEmitter->mUnknown24[1];
                pEmitter->mUnknown24[1] = pEmitter->mUnknown24[2];
                pEmitter->mUnknown24[2] = swap;
            }
            pEmitter->mUnknown4 = ObjParseGetInt(handle, "occurances");
        } while (ObjParseNext(handle));
    }
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "animPal")) {
        pNode->mUnknown68 = 1;
        pNode->mUnknown88 = 4;
        pNode->mUnknown76 = ObjParseGetFloat(handle, "delay");
        pNode->mUnknown72 = ObjParseGetFloat(handle, "rate");
        _BigObj_pAnimPalObject = pObject;
    } else {
        pNode->mUnknown68 = 0;
    }
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "surface")) {
        pNode->mUnknown100 = ObjParseGetInt(handle, "surfType");
        pNode->mUnknown96 = ObjParseGetInt(handle, "polyGroupId");
    } else {
        pNode->mUnknown100 = 15;
        pNode->mUnknown96 = -1;
    }
    ObjParseSetCursor(handle, position);
    if (ObjParseFindChild(handle, "sound")) {
        ObjParseGetString(handle, "name", text, 64);
        pNode->mUnknown92 = BigObjFindSoundId(text);
    } else {
        pNode->mUnknown92 = 0;
    }
    ObjParseSetCursor(handle, position);
}

int BigObjFindPartId(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(_BigObj_aPartNames) / sizeof(_BigObj_aPartNames[0]); i++) {
        if (strcmp(pName, _BigObj_aPartNames[i].mName) == 0) {
            return _BigObj_aPartNames[i].mId;
        }
    }
    return -1;
}

int BigObjFindSwapState(const char *pName, const char *pState)
{
    int i;

    for (i = 0; i < sizeof(_BigObj_aSwapStates) / sizeof(_BigObj_aSwapStates[0]); i++) {
        if (strcmp(pName, _BigObj_aSwapStates[i].mName) == 0 &&
            strcmp(pState, _BigObj_aSwapStates[i].mState) == 0) {
            return _BigObj_aSwapStates[i].mId;
        }
    }
    return -1;
}

int BigObjFindEmotionState(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(_BigObj_aEmotionStates) / sizeof(_BigObj_aEmotionStates[0]); i++) {
        if (strcmp(pName, _BigObj_aEmotionStates[i].mName) == 0) {
            return _BigObj_aEmotionStates[i].mId;
        }
    }
    return -1;
}

int BigObjFindTypeId(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(_BigObj_aTypeNames) / sizeof(_BigObj_aTypeNames[0]); i++) {
        if (strcmp(pName, _BigObj_aTypeNames[i].mName) == 0) {
            return _BigObj_aTypeNames[i].mId;
        }
    }
    return 0;
}

int BigObjFindBehaviorId(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(_BigObj_aResetNames) / sizeof(_BigObj_aResetNames[0]); i++) {
        if (strcmp(pName, _BigObj_aResetNames[i].mName) == 0) {
            return _BigObj_aResetNames[i].mId;
        }
    }
    return 0;
}

int BigObjFindEventType(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(_BigObj_aEventTypeNames) / sizeof(_BigObj_aEventTypeNames[0]); i++) {
        if (strcmp(pName, _BigObj_aEventTypeNames[i].mName) == 0) {
            return _BigObj_aEventTypeNames[i].mId;
        }
    }
    return 0;
}

unsigned short BigObjFindSoundId(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(_BigObj_aSoundNames) / sizeof(_BigObj_aSoundNames[0]); i++) {
        if (strcmp(pName, _BigObj_aSoundNames[i].mName) == 0) {
            return _BigObj_aSoundNames[i].mId;
        }
    }
    return 0;
}

void BigObjParseEvents(int handle, BigObjInst *pObject)
{
    char text[32];

    ObjParseFindChild(handle, "event");
    if (ObjParseGetString(handle, "type", text, 32)) {
        do {
            switch (BigObjFindEventType(text)) {
            case 1:
                BigObjParseAnimEvent(handle, pObject);
                break;
            case 2:
                BigObjParseSwapEvent(handle, pObject);
                break;
            case 3:
                BigObjParseSwapEvent(handle, pObject);
                break;
            }
            ObjParseNext(handle);
        } while (ObjParseGetString(handle, "type", text, 32));
    }
}

int BigObjEffectSlotAcquire(int type)
{
    int i;
    unsigned int slot = 8;
    int result = 21;

    for (i = 0; i < 8; i++) {
        if (type == _BigObj_aiEffectTypes[i]) {
            _BigObj_aiEffectUsers[i]++;
            return i + 12;
        }
        if (_BigObj_aiEffectTypes[i] == -1 && slot == 8) {
            slot = i;
        }
    }
    if (result == 21 && slot < 8) {
        _BigObj_aiEffectTypes[slot] = type;
        _BigObj_aiEffectUsers[slot] = 1;
        result = slot + 12;
    }
    return result;
}

void BigObjParseBehavior(int handle, BigObjInst *pObject)
{
    char type[32];
    char reset[32];
    int hasType;
    int hasReset;

    ObjParseRewind(handle);
    ObjParseFindPath(handle, "behavior");
    hasType = ObjParseGetString(handle, "type", type, 32);
    hasReset = ObjParseGetString(handle, "reset", reset, 32);
    pObject->mUnknown188 = 0;
    pObject->mUnknown184 = _BigObj_apUpdateFuncs[pObject->mUnknown188];
    pObject->mUnknown196 = -1;
    pObject->mUnknown424 = 1;
    pObject->mUnknown312 = 0;
    pObject->mUnknown420 = 0;
    _BigObj_pAnimPalObject = 0;
    if (hasType) {
        pObject->mUnknown188 = BigObjFindTypeId(type);
        pObject->mUnknown184 = _BigObj_apUpdateFuncs[pObject->mUnknown188];
        if (_BigObj_apLoadFuncs[pObject->mUnknown188]) {
            _BigObj_apLoadFuncs[pObject->mUnknown188](handle, pObject);
        }
        BigObjParseEvents(handle, pObject);
    }
    pObject->mUnknown192 = 0;
    if (hasReset) {
        pObject->mUnknown192 = _BigObj_apResetFuncs[BigObjFindBehaviorId(reset)];
    }
    pObject->mUnknown380 = 0;
}

void BigObjFreeEvents(BigObjInst *pObject)
{
    BigObjNode_t *pNode = pObject->mUnknown312;

    while (pNode) {
        BigObjEmitter_t *pEmitter = pNode->mUnknown128;
        BigObjNode_t *pFreeNode;

        while (pEmitter) {
            BigObjEmitter_t *pFree = pEmitter;

            pEmitter = pEmitter->mpNext;
            fn_801D2BD0(pFree);
        }
        pNode->mUnknown128 = 0;
        pFreeNode = pNode;
        pNode = pNode->mpNext;
        fn_801D2BD0(pFreeNode);
    }
    pObject->mUnknown312 = 0;
    if (pObject->mUnknown420) {
        fn_801D2BD0(pObject->mUnknown420);
        pObject->mUnknown420 = 0;
    }
}

void BigObjHit(BigObj_t *pItem, float *pPos, float *pDir, const char *pName, int type,
                 BigObjHitter_t *pHitter)
{
    int fire = 1;
    unsigned int time = InGameGetFrameCount();
    BigObjInst *pObject = pItem->mUnknown472;
    unsigned char i;

    for (i = 0; i < 3; i++) {
        if (pObject->mUnknown384[i].mType == type) {
            break;
        }
    }
    if (i == 3) {
        for (i = 0; i < 2; i++) {
            pObject->mUnknown384[i + 1].mType = pObject->mUnknown384[i].mType;
            pObject->mUnknown384[i + 1].mTime = pObject->mUnknown384[i].mTime;
        }
        pObject->mUnknown384[0].mTime = time;
        pObject->mUnknown384[0].mType = type;
    } else {
        if (time - pObject->mUnknown384[i].mTime < 30) {
            fire = 0;
        }
        pObject->mUnknown384[i].mTime = time;
    }
    if (!fire) {
        return;
    }
    pObject->mUnknown380 = 1;
    pObject->mUnknown381 = PhysIsBall(type);
    strcpy(pObject->mUnknown316, pName);
    pObject->mUnknown360.mX = pPos[0];
    pObject->mUnknown360.mY = pPos[1];
    pObject->mUnknown360.mZ = pPos[2];
    pObject->mUnknown348 = pDir[0];
    pObject->mUnknown352 = pDir[1];
    pObject->mUnknown356 = pDir[2];
    if (pObject->mUnknown381) {
        pObject->mUnknown372 = Vec3Magnitude((char *)BallGetCurrent() + 0x54);
    } else if (PhysIsPlayer(type)) {
        if (pHitter) {
            pObject->mUnknown372 = pHitter->mUnknown508 * pHitter->mUnknown452;
        }
    } else {
        pObject->mUnknown372 = Vec3Magnitude(pDir);
    }
    if (pHitter) {
        float scale;

        pObject->mUnknown376 = pHitter->mId;
        scale = pObject->mUnknown372 * (1.0f / 70.0f);
        if (pHitter->mChannel != 0xFF) {
            int hi = _BigObjHit_uRumbleMax;
            int lo = _BigObjHit_uRumbleMin;
            float volume = (hi - lo) * scale + lo;

            if (volume > hi) {
                volume = hi;
            }
            RumbleStart(pHitter->mChannel, (unsigned char)(int)volume, _BigObjHit_uRumbleTime);
        }
    } else {
        pObject->mUnknown376 = 0;
    }
}

void BigObjHitStatic(BigObj_t *pItem, float *pPos, float *pDir, const char *pName, int type,
                 BigObjHitter_t *pHitter)
{
    BigObjInst *pObject = pItem->mUnknown472;
    BigObj_t **ppLinked = pObject->mUnknown152;
    float strength = 0.0f;
    unsigned int i;

    if (pHitter) {
        strength = pHitter->mUnknown508 * pHitter->mUnknown452;
    }
    pObject->mUnknown372 = strength;
    BigObjHit(pItem, pPos, pDir, pName, type, pHitter);
    for (i = 0; i < 8; i++) {
        if (ppLinked[i]) {
            if (pHitter) {
                ppLinked[i]->mUnknown472->mUnknown372 = strength;
            }
            BigObjHit(ppLinked[i], pPos, pDir, pName, type, pHitter);
        } else {
            break;
        }
    }
}

int BigObjEffectSlotCount(int type)
{
    return _BigObj_aiEffectUsers[type - 12];
}

void BigObjEffectSlotsReset(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        _BigObj_aiEffectUsers[i] = 0;
        _BigObj_aiEffectTypes[i] = -1;
    }
}

void BigObjEffectsUpdate(void)
{
}
}

struct ObjParseFile_t {
    char mName[256];
    void *mpData;
    void *mpCursor;
    int mId;
};

struct DynObjModelCache_t {
    int mHandle;
    char mName[256];
    char mUnknown260[48];
    int mReferences;
    void *mpArchive;
    int mId;
};

struct DynObjModelInstance_t {
    DynObjModelCache_t *mpCache;
    Object_80235588 mRender;
};

extern "C" {
DynObjChild **_DynObjChild_ppList = 0;
ObjParseFile_t *_ObjParse_pFiles = 0;
unsigned short _DynObjChild_uCount;
unsigned short _DynObjChild_uMax;
int _ObjParse_iFileCount;
void *_ObjParse_pBuffer;
char *_ObjParse_pBufferNext;
unsigned short _DynObj_uModelCount = 0;
DynObjModelCache_t *_DynObj_apModelCache[104];
extern void *gpReplay;
void QuatFromEuler(Quat_801EB488 *, int, int, int);
void QuatFromEulerYZX(Quat_801EB488 *, int, int, int);
void QuatMultiply(Quat_801EB488 *, Quat_801EB488 *, void *);
void MatPushUnit(void); void MatPop(void);
void MatRotQuat(void *); void MatTranslate(void *);
void MatSetStack(int); void MatPush(void); void MatRotX(int);
void Vec3Mat33Mul(void *, void *);
void Vec3Add(void *, void *, void *);
void Vec3Sub(void *, void *, void *);
void Vec3RotateZYX(void *, void *, int, int, int);
int MathAngleDiff(int, int);
int ObjNewType_(int, int, int, void *, void *);
int ObjDelType(int);
void ObjSetListObjFunc(int, int, int, int (*)(DynObjChild *));
DynObjChild *ObjNewInList(int, int, int, BigObjDesc_t *);
void ObjRemoveFromList(int, DynObjChild *);
void VptTrashObject(DynObjChild *); void VptFlushObjectTrash(void); void VptFlushObjectTrashSync(void);
int SysGetLastError(void);
BigObj_t *BigObjFindByKey(int, unsigned int);
void DynObjChildRefreshFrame(DynObjChild *);
void *ResLoadToBuffer(void *, int, char *);
int ResGetSize(void *, int);
void *XmlFindPath(void *, const char *);
void *XmlFindInElement(void *, const char *);
void *XmlFindNext(void *);
int XmlGetAttrString(void *, const char *, char *, int, const char *);
int XmlGetAttrInt(void *, const char *, int);
float XmlGetAttrFloat(void *, const char *, float);
int XmlGetAttrFloats(void *, const char *, float *, int);
int ReplayIsShowing(void *);
int ConGetCurrentContext(void);
void DynObjDrawEnvMap(DynObj *, int);
int VptGetMatrixStack(void);
void ModelObjSetAmbientColor(void *, int, float, float, float, float);
void ModelObjStoreMatrix(void *, int); void ModelObjDraw(void *, int);
int ResLoad(void *, int, int);
void ModelObjRelocateModelRes(int); void fn_80234DCC(int, void *, const char *, int);
void fn_80235588(void *, int); void ModelObjReset(void *);
void ModelObjSetModel(void *, int); void ModelObjSetTexturesDefault(void *, void *);
void ModelObjSetModeNop(void *, int); void fn_802353D8(void *, int); void fn_802353F8(void *, int);
void fn_80234EA0(void *, int); void ResUnLoad(void *, int);
void DynObjLoadSkeleton(void *, int, BigObj_t *);
void DynObjRenderInit(void *, int, DynObj *);
void DynObjLoadAnimPal(void *, DynObj *);
unsigned int LLLightGetProjectorColor(int);
void SimpShadowAdd(int, Vector_80039F5C *, float, float *);
int DynObjChildUpdate(DynObjChild *);
void DynObjChildDestroyList(int);
int DynObjFindModel(const char *);
void DynObjLoadModel(void *, int, BigObj_t *);

void BigObjEmitParticles(void *pData, float time, BigObjInst *pObject, BigObj_t *pOwner)
{
    BigObjEmitter_t *p = (BigObjEmitter_t *)pData;
    while (p) {
        if (!(time <= p->mUnknown36) && p->mUnknown0 != 21 &&
            (p->mUnknown4 == 0 || p->mUnknown8 < p->mUnknown4)) {
            p->mUnknown8++;
            Quat_801EB488 rotation;
            Vector_80039F5C position;
            if (p->mUnknown40) {
                Vector_80039F5C direction;
                direction.mX = -pObject->mUnknown348;
                direction.mY = -pObject->mUnknown352;
                direction.mZ = -pObject->mUnknown356;
                int angle = MathArcTan2(direction.mZ, direction.mX);
                int heading = MathArcTan2(direction.mY, direction.mX);
                QuatFromEulerYZX(&rotation, angle, heading, 0);
                position = pObject->mUnknown360;
            } else {
                QuatFromEuler(&rotation, (int)(p->mUnknown24[2] * 46603.3789f),
                            (int)(p->mUnknown24[1] * 46603.3789f), (int)(p->mUnknown24[0] * 46603.3789f));
                QuatMultiply(&rotation, &rotation, &pObject->mState.mUnknown88);
                MatPushUnit();
                MatRotQuat(&rotation);
                Vector_80039F5C offset;
                Vec3Mat33Mul(&offset, p->mUnknown12);
                MatPop();
                position.mX = pObject->mState.mUnknown0;
                position.mY = pObject->mState.mUnknown4;
                position.mZ = pObject->mState.mUnknown8;
                Vec3Add(&position, &position, &offset);
            }
            ParticlesSpawnAt(p->mUnknown0, &position.mX, &rotation.mX, (ParticleSource_t *)pOwner->mUnknown332);
            ParticleSpawnRecord_t record;
            record.mId = p->mUnknown0;
            record.mPos[0] = position.mX;
            record.mPos[1] = position.mY;
            record.mPos[2] = position.mZ;
            record.mRot[0] = rotation.mX;
            record.mRot[1] = rotation.mY;
            record.mRot[2] = rotation.mZ;
            record.mRot[3] = rotation.mW;
            record.mpSource = (ParticleSource_t *)pOwner->mUnknown332;
            ParticleSysReplayRecordSpawn(record);
        }
        p = p->mpNext;
    }
}

void BigObjUpdatePartTimers(BigObj_t *pOwner)
{
    BigObjNode_t *p = pOwner->mUnknown472->mUnknown312;
    while (p) {
        if (p->mUnknown116 && p->mUnknown120 && --p->mUnknown120 == 0)
            DynObjSetPartState(pOwner, p->mUnknown104, p->mUnknown108);
        p = p->mpNext;
    }
}

void DynObjChildFollow(DynObjChild *p)
{
    BigObjInst *pObject = p->mpObject54;
    BigObjPhysics_t *pExtra = pObject->mUnknown428;
    if (pExtra) {
        Vector_80039F5C delta;
        BigObjSpin_t *pSpin = &pExtra->mSpin;
        BigObjInstState_t *pState = &pObject->mState;
        if (pSpin->mUnknown0) {
            QuatEulerAngles_t angles;
            p->mAngle4C = (p->mAngle4C + pSpin->mUnknown4) & 0xFFFFFF;
            QuatToEuler(&angles, &p->mRotation3C.mX);
            angles.mUnknown8 = p->mAngle4C + 0x400000;
            QuatFromEuler(&p->mRotation3C, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
        }
        int angle = MathAngleDiff(p->mAngle4C, pState->mUnknown24);
        if (pSpin->mUnknown1) {
            Vec3Sub(&delta, &pState->mUnknown0, pState->mUnknown12);
            Vec3RotateZYX(&delta, &delta, angle, 0, 0);
            Vec3Add(&p->mUnknown30, &p->mUnknown30, &delta);
        }
    }
}

void DynObjChildCreateList(int handle, int count)
{
    ObjNewType_(31, 112, count, 0, 0);
    if (handle) ObjSetListObjFunc(handle, 31, 0, DynObjChildUpdate);
    _DynObjChild_ppList = (DynObjChild **)fn_801D2B7C(count * 4, 0, 0);
    memset(_DynObjChild_ppList, 0, count * 4);
    SysGetLastError();
    _DynObjChild_uCount = 0;
    _DynObjChild_uMax = count;
}

void DynObjChildDestroyList(int handle)
{
    if (_DynObjChild_ppList) {
        for (unsigned short i = 0; i < _DynObjChild_uCount; i++) {
            ObjRemoveFromList(handle, _DynObjChild_ppList[i]);
            VptTrashObject(_DynObjChild_ppList[i]);
        }
        VptFlushObjectTrash();
        fn_801D2BD0(_DynObjChild_ppList);
        _DynObjChild_ppList = 0;
    }
}

void DynObjChildInit(int handle) { DynObjChildCreateList(handle, 64); }
void DynObjChildShutdown(int handle) { DynObjChildDestroyList(handle); VptFlushObjectTrashSync(); ObjDelType(31); }

void DynObjChildSpawn(BigObjDesc_t *pDesc, int handle, int first)
{
    DynObjChild *p = ObjNewInList(handle, 31, 0, pDesc);
    _DynObjChild_ppList[_DynObjChild_uCount] = p;
    LightTrackerReset(&p->mTracker60);
    p->mWord68 = 0;
    p->mUnknown14.mX = pDesc->mUnknown132.mUnknown4;
    p->mUnknown14.mY = pDesc->mUnknown132.mUnknown8;
    p->mUnknown14.mZ = pDesc->mUnknown132.mUnknown12;
    p->mUnknown30.mX = p->mUnknown14.mX;
    p->mUnknown30.mY = p->mUnknown14.mY;
    p->mUnknown30.mZ = p->mUnknown14.mZ;
    QuatFromEulerYZX(&p->mRotation3C, (int)(pDesc->mUnknown132.mUnknown20 * 46603.3789f),
                (int)(pDesc->mUnknown132.mUnknown24 * 46603.3789f),
                (int)(pDesc->mUnknown132.mUnknown16 * 46603.3789f));
    p->mUnknown20.mX = p->mRotation3C.mX;
    p->mUnknown20.mY = p->mRotation3C.mY;
    p->mUnknown20.mZ = p->mRotation3C.mZ;
    p->mUnknown20.mW = p->mRotation3C.mW;
    p->mAngle4C = (int)((pDesc->mUnknown132.mUnknown24 - 90.0f) * 46603.3789f);
    p->mpOwner50 = 0;
    p->mpOwner50 = BigObjFindByKey(pDesc->mUnknown176, first);
    if (!p->mpOwner50) {
        p->mpObject54 = 0;
    } else {
        p->mpObject54 = p->mpOwner50->mUnknown472;
        DynObjChild *pFirst = (DynObjChild *)p->mpOwner50->mUnknown480;
        if (!pFirst) p->mpOwner50->mUnknown480 = (int)p;
        else {
            DynObjChild *pLast = pFirst;
            while (pLast->mpUnknown5C) pLast = pLast->mpUnknown5C;
            pLast->mpUnknown5C = p;
        }
    }
    p->mpUnknown58 = LevelFindArea(&pDesc->mUnknown132.mUnknown4);
    _DynObjChild_uCount++;
    p->mUnknown6C = 0;
    DynObjChildRefreshFrame(p);
}

int DynObjChildUpdate(DynObjChild *p) {
    if (!p->mpOwner50) return 0;
    DynObjChildFollow(p);
    return 0;
}

int ObjParseFind(const char *pName)
{
    for (int i = 0; i < _ObjParse_iFileCount; i++)
        if (strcmp(pName, _ObjParse_pFiles[i].mName) == 0) return i;
    return -1;
}

int ObjParseOpen(void *pData, char *pName)
{
    int id = ResFindIndexByName((int)pData, pName);
    if (id == -1) return -1;
    int index = ObjParseFind(pName);
    if (index == -1) {
        strcpy(_ObjParse_pFiles[_ObjParse_iFileCount].mName, pName);
        void *p = ResLoadToBuffer(pData, id, _ObjParse_pBufferNext);
        _ObjParse_pFiles[_ObjParse_iFileCount].mpData = p;
        _ObjParse_pFiles[_ObjParse_iFileCount].mpCursor = p;
        _ObjParse_pBufferNext = _ObjParse_pBufferNext + ResGetSize(pData, id) + 4;
        _ObjParse_pFiles[_ObjParse_iFileCount].mId = id;
        index = _ObjParse_iFileCount++;
    } else _ObjParse_pFiles[index].mpCursor = _ObjParse_pFiles[index].mpData;
    return index;
}

void ObjParseRewind(int handle) { _ObjParse_pFiles[handle].mpCursor = _ObjParse_pFiles[handle].mpData; }
int ObjParseFindPath(int handle, const char *pKey) {
    void *p = XmlFindPath(_ObjParse_pFiles[handle].mpCursor, pKey);
    _ObjParse_pFiles[handle].mpCursor = p;
    if (p) return 1;
    return 0;
}
int ObjParseFindChild(int handle, const char *pKey) {
    void *p = XmlFindInElement(_ObjParse_pFiles[handle].mpCursor, pKey);
    _ObjParse_pFiles[handle].mpCursor = p;
    if (p) return 1;
    return 0;
}
int ObjParseNext(int handle) {
    void *p = XmlFindNext(_ObjParse_pFiles[handle].mpCursor);
    _ObjParse_pFiles[handle].mpCursor = p;
    if (p) return 1;
    return 0;
}
int ObjParseGetString(int handle, const char *pKey, char *pText, int size) {
    return XmlGetAttrString(_ObjParse_pFiles[handle].mpCursor, pKey, pText, size, "");
}
int ObjParseGetInt(int handle, const char *pKey) { return XmlGetAttrInt(_ObjParse_pFiles[handle].mpCursor, pKey, 0); }
float ObjParseGetFloat(int handle, const char *pKey) { return XmlGetAttrFloat(_ObjParse_pFiles[handle].mpCursor, pKey, 0.0f); }
int ObjParseGetMatrix(int handle, const char *pKey, float *pValues) {
    float values[9];
    int i = 0;
    if (XmlGetAttrFloats(_ObjParse_pFiles[handle].mpCursor, pKey, values, 9)) {
        for (; i < 9; i++) pValues[i + i / 3] = values[i];
        return 1;
    }
    return 0;
}
unsigned char ObjParseGetFloats(int handle, const char *pKey, float *pValues, int count) {
    return XmlGetAttrFloats(_ObjParse_pFiles[handle].mpCursor, pKey, pValues, count);
}
int ObjParseGetVector(int handle, const char *pKey, float *pValues) {
    float values[3];
    if (XmlGetAttrFloats(_ObjParse_pFiles[handle].mpCursor, pKey, values, 3)) {
        pValues[0] = values[0]; pValues[1] = values[1]; pValues[2] = values[2]; return 1;
    }
    return 0;
}
void ObjParseInit(void) {
    _ObjParse_iFileCount = 0;
    _ObjParse_pFiles = (ObjParseFile_t *)fn_801D2B7C(0x4B60, 4, 0);
    memset(_ObjParse_pFiles, 0, 0x4B60);
    _ObjParse_pBuffer = fn_801D2B7C(0x18000, 4, 0);
    memset(_ObjParse_pBuffer, 0, 0x18000);
    _ObjParse_pBufferNext = (char *)_ObjParse_pBuffer;
    BigObjEffectSlotsReset();
}
void ObjParseShutdown(void) { fn_801D2BD0(_ObjParse_pFiles); _ObjParse_pFiles = 0; fn_801D2BD0(_ObjParse_pBuffer); }
int ObjParseGetCursor(int handle) { return (int)_ObjParse_pFiles[handle].mpCursor; }
void ObjParseSetCursor(int handle, int position) { _ObjParse_pFiles[handle].mpCursor = (void *)position; }

int DynObjDrawModel(DynObj *p, int mode)
{
    DynObjModelInstance_t *pInstance = p->mpRender12C;
    unsigned char flag;
    if (ReplayIsShowing(gpReplay)) flag = p->mUnknownE8.mBytes[3] & 4;
    else flag = p->mUnknownE8.mBytes[3] & 1;
    if (flag) {
        int context = ConGetCurrentContext();
        if (p->mFlagF0) DynObjSetAnimPalFrame(p, (int)((BigObjInst *)p->mpUnknown1D8)->mUnknown200.mStep);
        if (((BigObjInst *)p->mpUnknown1D8)->mUnknown224 == 1) DynObjScrollUVs(p, &((BigObjInst *)p->mpUnknown1D8)->mUnknown224);
        int index = VptGetMatrixStack();
        Object_80235588 *pRender = &pInstance->mRender;
        MatSetStack(index); MatPush();
        MatTranslate(&p->mUnknown4); MatRotQuat(&p->mUnknown18); MatRotX(0x400000);
        ModelObjSetAmbientColor(pRender, context, 0.5f, 0.5f, 0.5f, 0.51f);
        ModelObjStoreMatrix(pRender, context); MatPop(); ModelObjDraw(pRender, context);
    }
    if (p->mUnknownE8.mWord & 2) DynObjDrawEnvMap(p, mode);
    return 0;
}

int DynObjFindModel(const char *pName)
{
    for (int i = 0; i < _DynObj_uModelCount; i++)
        if (strcmp(pName, _DynObj_apModelCache[i]->mName) == 0) return i;
    return -1;
}

void DynObjLoadModel(void *pData, int handle, BigObj_t *pObject)
{
    DynObj *p = (DynObj *)pObject;
    char name[256];
    ObjParseGetString(handle, "tideRef", name, 256);
    int index = DynObjFindModel(name);
    p->mpRender12C = (DynObjModelInstance_t *)fn_801D2B7C(196, 0, 0);
    memset(p->mpRender12C, 0, 196);
    DynObjModelInstance_t *pInstance = p->mpRender12C;
    if (index != -1) {
        pInstance->mpCache = _DynObj_apModelCache[index];
        pInstance->mpCache->mReferences++;
    } else {
        _DynObj_apModelCache[_DynObj_uModelCount] = (DynObjModelCache_t *)fn_801D2B7C(320, 0, 0);
        memset(_DynObj_apModelCache[_DynObj_uModelCount], 0, 320);
        pInstance->mpCache = _DynObj_apModelCache[_DynObj_uModelCount++];
        pInstance->mpCache->mReferences = 1;
        strcpy(pInstance->mpCache->mName, name);
        pInstance->mpCache->mpArchive = pData;
        pInstance->mpCache->mId = ResFindIndexByName((int)pData, name);
        pInstance->mpCache->mHandle = ResLoad(pData, pInstance->mpCache->mId, 1);
        ModelObjRelocateModelRes(pInstance->mpCache->mHandle);
        fn_80234DCC(pInstance->mpCache->mHandle, pInstance->mpCache->mUnknown260, "Objects", 3);
    }
    Object_80235588 *pRender = &pInstance->mRender;
    fn_80235588(pRender, 6);
    ModelObjSetModel(pRender, pInstance->mpCache->mHandle);
    ModelObjSetTexturesDefault(pRender, pInstance->mpCache->mUnknown260);
    ModelObjSetModeNop(pRender, 8); fn_802353D8(pRender, 3); fn_802353F8(pRender, 0);
    p->mUnknownE8.mWord = 1;
    if (ObjParseGetString(handle, "tideEnvMapRef", name, 256)) p->mUnknownE8.mWord = 2;
    p->mUnknown14 = DynObjDrawModel;
}

void DynObjFreeModel(BigObj_t *pObject)
{
    DynObj *p = (DynObj *)pObject;
    DynObjModelInstance_t *pInstance = p->mpRender12C;
    ModelObjReset(&pInstance->mRender);
    pInstance->mpCache->mReferences--;
    if (pInstance->mpCache->mReferences <= 0) {
        fn_80234EA0(pInstance->mpCache->mUnknown260, 3);
        ResUnLoad(pInstance->mpCache->mpArchive, pInstance->mpCache->mId);
    }
    fn_801D2BD0(p->mpRender12C);
    p->mpRender12C = 0;
}

void DynObjParseRender(void *pData, int handle, BigObj_t *pObject)
{
    DynObj *p = (DynObj *)pObject;
    char type[32]; char name[128];
    p->mpUnknownA8 = pData;
    ObjParseRewind(handle);
    if (!ObjParseFindPath(handle, "render")) return;
    ObjParseGetString(handle, "type", type, 32);
    if (strcmp(type, "NO_RENDER") == 0) {
        p->mTypeEC = 0;
        DynObjLoadSkeleton(pData, handle, pObject);
        return;
    }
    if (strcmp(type, "STATIC_RENDER") == 0) {
        p->mTypeEC = 1;
        DynObjLoadModel(pData, handle, pObject);
    } else if (strcmp(type, "DYNAMIC_RENDER") == 0) {
        p->mTypeEC = 2;
        DynObjLoadSkeleton(pData, handle, pObject);
        ObjParseRewind(handle); ObjParseFindPath(handle, "render");
        DynObjRenderInit(pData, handle, p);
        ObjParseRewind(handle); ObjParseFindPath(handle, "render");
    }
    if (ObjParseGetInt(handle, "bFadeable")) p->mUnknown140 = 1;
    else p->mUnknown140 = 0;
    p->mScale144 = 1.0f;
    if (ObjParseFindChild(handle, "shadow")) {
        float size = ObjParseGetFloat(handle, "fShadowSize");
        unsigned int packed = LLLightGetProjectorColor(0);
        float color[4];
        color[0] = (packed & 0xFF) * 0.0078125f;
        color[1] = ((packed >> 8) & 0xFF) * 0.0078125f;
        color[2] = ((packed >> 16) & 0xFF) * 0.0078125f;
        color[3] = (packed >> 24) * 0.0078125f;
        if (size == 0.0f) size = 2.0f;
        SimpShadowAdd(0, &p->mUnknown4, size, color);
    }
    ObjParseRewind(handle);
    if (ObjParseFindPath(handle, "animPal")) {
        p->mFlagF0 = 1;
        ObjParseGetString(handle, "tideRef", name, 128);
        p->mUnknownF4 = ResFindIndexByName((int)pData, name);
        DynObjLoadAnimPal(pData, p);
    } else { p->mUnknownF8 = 0; p->mFlagF0 = 0; }
}
}

struct DynObjSkeletonCache_t {
    int mHandle;
    char mName[256];
    int mReferences;
    int mId;
    void *mpArchive;
};

struct PhysBodyOwner_t {
    unsigned char mKind;
    unsigned char mCount;
    unsigned short mUnknown2;
    char **mNames;
    BigObj_t *mpObject;
    Block_80170E64 *mpBlock;
    unsigned short mUnknown16;
    unsigned short mType;
    short mUnknown20;
    short mUnknown22;
};

/* The game's body group: every body of the field, stepped by one Euler integrator. */
class PhysBodyGroup : public BodyGroup {
public:
    virtual void ApplyForces(void *pStart);
    virtual int AfterStep(int start, int end) { return 1; }
};

/* The game's collision handler, installed in the world's contact system by PhysInit. */
class PhysCollisionHandler : public CollisionHandler {
public:
    virtual int IgnorePair(RigidBody *pA, RigidBody *pB);
    virtual int OnContacts(float dt, RigidBody *pA, RigidBody *pB, unsigned int count,
                           BodyContact *pContacts);
    virtual void OnImpulse(RigidBody *pA, unsigned int shapeA, RigidBody *pB, unsigned int shapeB,
                           Vec3_801DE1E0 *pPointA, Vec3_801DE1E0 *pPointB, Vec3_801DE1E0 *pNormal);
};

/* Engine classes defined in src/engine/physstep.cpp. */
class EulerIntegrator : public Integrator {
public:
    EulerIntegrator(IntegrableSystem *pSystem, int count);
    virtual ~EulerIntegrator();
    virtual int Step(void *pStart, void *pStep);
    virtual void Restore();

    int mCount;
    float *mpState;
    float *mpNext;
    float *mpRate;
};

class SleepFilter {
public:
    virtual int AllowStateChange(RigidBody *pBody, int wake) = 0;
};

class SleepController : public BodyController {
public:
    SleepController(float sleepTime, float maxSpeed, SleepFilter *pFilter);
    virtual void AddBody(RigidBody *pBody);
    virtual void RemoveBody(RigidBody *pBody);
    virtual void UpdateSleepState(RigidBody *pBody, float dt);
    int IsBodyResting(RigidBody *pBody);

    float mSleepTime;
    float mMaxSpeed;
    SleepFilter *mpFilter;
};

extern "C" {
unsigned short _DynObj_uSkeletonCount = 0;
CollisionShape *_Phys_apObjectShapes[166];
CollisionShape *_Phys_apPlayerShapes[14];
Vector_80039F5C *_Phys_apObjectPositions[128];
RigidBody *_Phys_apObjectBodies[128];
RigidBody *_Phys_apPlayerBodies[14];
PointConstraint *_Phys_apConstraints[8];
PhysBodyOwner_t _Phys_aBodyOwners[142];
ContactSystem *_Phys_pContacts = 0;
SleepController *_Phys_pSleep = 0;
PhysCollisionHandler *_Phys_pCollisionHandler = 0;
PhysicsWorld *_Phys_pWorld = 0;
Integrator *_Phys_pIntegrator = 0;
PhysBodyGroup *_Phys_pBodyGroup = 0;
CollisionShape *_Phys_pGroundShape = 0;
extern PhysicsTime _Phys_sTime;
CollisionShape *_Phys_pBallShape = 0;
int _Phys_iObjectCount = 0;
int _Phys_iBodyCount = 0;
int _Phys_iShapeCount = 0;
int _Phys_iConstraintCount = 0;
unsigned int _Phys_uBallHitTimer = 0;
RigidBody *_Phys_pBallBody;
RigidBody *_Phys_pGroundBody;
void DynObjRenderShutdown(DynObj *);
void DynObjCacheReset(void); void DynObjCacheFree(void); void DynObjFreeAnimPal(DynObj *);
int DebugPrintf(const char *, ...);
void CharRelocateSkeleton(int);
int CharSkelGetJointByName(AnimSkeleton_t *, const char *);
Object_80039F5C *PlyrObjsFindPlayer(Block_80170E64 *);
void Vec3RotateXYZ(void *, void *, int, int, int);
void Vec2Normalize(void *, void *);
void Vec3Scale(void *, void *, float);
int PlyrContactResolve(Object_80039F5C *, int, int);
void ScrmSetTackler(Object_80039F5C *);
void PlyrContactSendHitFrom(Object_80039F5C *, int, int *, int, int *);
int PlyrContactIsBeforeImpact(Object_80039F5C *);
float PlyrMoveGetRatedSpeed(Object_80039F5C *, float, float);
int BallStateGet(Ball_t *, int *);
int ScrmClassifyPosition(void *, int, int);
void BallApplyImpulse(Ball_t *, Vector_80039F5C *, Vector_80039F5C *);
void ScrmSetPlayFlag(int, int);
void ClearBodyForces(RigidBody *);
void AddBodyForceAtPoint(RigidBody *, Vector_80039F5C *, Vector_80039F5C *);
void SetBodyLinearMomentum(RigidBody *, Vector_80039F5C *);
void SetBodyLinearVelocity(RigidBody *, Vector_80039F5C *);
void DynObjFreeSkeleton(BigObj_t *);

void DynObjShutdown(BigObj_t *pObject)
{
    DynObj *p = (DynObj *)pObject;
    if (p->mTypeEC == 1) DynObjFreeModel(pObject);
    else if (p->mTypeEC == 2) { DynObjRenderShutdown(p); DynObjFreeSkeleton(pObject); }
    else DynObjFreeSkeleton(pObject);
    if (p->mFlagF0) DynObjFreeAnimPal(p);
}
void DynObjModelCacheReset(void)
{
    _DynObj_uModelCount = 0;
    memset(_DynObj_apModelCache, 0, 0x1A0);
    DynObjCacheReset();
}
void DynObjModelCacheFree(void)
{
    DynObjCacheFree();
    for (unsigned int i = 0; i < _DynObj_uModelCount; i++) fn_801D2BD0(_DynObj_apModelCache[i]);
    memset(_DynObj_apModelCache, 0, 0x1A0);
    _DynObj_uModelCount = 0;
}
void DynObjSetPartState(BigObj_t *p, int index, int value)
{
    fn_80233CBC((char *)p->mUnknown300 + 32, index, value);
    p->mWord316 = value;
}
void DynObjSetPart(BigObj_t *p, int index, int value)
{
    fn_80233CBC((char *)p->mUnknown300 + 32, index, value);
}
int DynObjFindSkeleton(const char *pName)
{
    for (int i = 0; i < _DynObj_uSkeletonCount; i++)
        if (strcmp(pName, _DynObj_apSkeletonCache[i]->mName) == 0) return i;
    return -1;
}
void DynObjLoadSkeleton(void *pData, int handle, BigObj_t *pObject)
{
    DynObj *p = (DynObj *)pObject;
    char name[256];
    DynObjSkeletonCache_t *pCache;
    int ok = ObjParseFindChild(handle, "skeleton");
    if (ok) ok = ObjParseGetString(handle, "tideRef", name, 256);
    if (ok) {
        int index = DynObjFindSkeleton(name);
        if (index != -1) {
            pCache = _DynObj_apSkeletonCache[index];
            pCache->mReferences++;
            p->mpSkeleton130 = pCache;
        } else {
            _DynObj_apSkeletonCache[_DynObj_uSkeletonCount] = (DynObjSkeletonCache_t *)fn_801D2B7C(272, 0, 0);
            memset(_DynObj_apSkeletonCache[_DynObj_uSkeletonCount], 0, 272);
            pCache = _DynObj_apSkeletonCache[_DynObj_uSkeletonCount++];
            p->mpSkeleton130 = pCache;
            strcpy(pCache->mName, name);
            pCache->mpArchive = pData;
            pCache->mId = ResFindIndexByName((int)pData, name);
            pCache->mReferences = 1;
            pCache->mHandle = ResLoad(pData, pCache->mId, 1);
            DebugPrintf("Loading Object Skeleton\n");
            CharRelocateSkeleton(pCache->mHandle);
        }
    } else {
        p->mpSkeleton130 = (DynObjSkeletonCache_t *)ok; // FAKEMATCH: ok is 0 here; storing it keeps the target's stw r3 of the failed call's result
    }
}
void DynObjFreeSkeleton(BigObj_t *pObject)
{
    DynObj *p = (DynObj *)pObject;
    DynObjSkeletonCache_t *pCache = p->mpSkeleton130;
    if (pCache) {
        pCache->mReferences--;
        if (pCache->mReferences <= 0) ResUnLoad(pCache->mpArchive, pCache->mId);
        fn_801D2BD0(pObject->mUnknown228);
        fn_801D2BD0(pObject->mpUnknown220);
    }
    p->mpSkeleton130 = 0;
}
void DynObjSkeletonCacheReset(void)
{
    _DynObj_uSkeletonCount = 0;
    memset(_DynObj_apSkeletonCache, 0, 0x1A0);
}
void DynObjSkeletonCacheFree(void)
{
    for (unsigned int i = 0; i < _DynObj_uSkeletonCount; i++) fn_801D2BD0(_DynObj_apSkeletonCache[i]);
    memset(_DynObj_apSkeletonCache, 0, 0x1A0);
    _DynObj_uSkeletonCount = 0;
}
void DynObjGetRootAngles(BigObj_t *pObject, int *pAngles)
{
    AnimSkeleton_t *pSkeleton = BigObjGetItemSkeleton(pObject);
    if (pSkeleton) {
        int index = CharSkelGetJointByName(pSkeleton, "main");
        if (index == -1) index = CharSkelGetJointByName(pSkeleton, "Main");
        pAngles[0] = pObject->mpUnknown220[index * 3] << 8;
        pAngles[1] = pObject->mpUnknown220[index * 3 + 1] << 8;
        pAngles[2] = pObject->mpUnknown220[index * 3 + 2] << 8;
    }
}
}

int PhysCollisionHandler::IgnorePair(RigidBody *pA, RigidBody *pB)
{
    PhysBodyOwner_t *a = (PhysBodyOwner_t *)pA->mpOwner;
    PhysBodyOwner_t *b = (PhysBodyOwner_t *)pB->mpOwner;
    if (!(a->mUnknown2 & 1) || !(b->mUnknown2 & 1)) return 1;
    if (pA->mState == 2 || pB->mState == 2 || pA->mState == 1 || pB->mState == 1) return 0;
    return 1;
}

extern "C" {
void PhysPushPlayer(float step, RigidBody *pBody, unsigned int index, RigidBody *pOther,
                 unsigned int otherIndex, unsigned int count, BodyContact *pContacts)
{
    Object_80039F5C *p = PlyrObjsFindPlayer(((PhysBodyOwner_t *)pBody->mpOwner)->mpBlock);
    CollisionShape *pShape = pBody->mpShapes->GetShape(index);
    for (unsigned int i = 0; i < count; i++) {
        Vector_80039F5C direction, normal, velocity, point, delta;
        float distance;
        GetBodyPointVelocity(pBody, &pContacts[i].mPoint, (Vec3_801DE1E0 *)&velocity);
        float speed = Vec3Magnitude(&velocity);
        float length = (speed + speed) * step;
        if (!(length >= 0.002f)) length = 0.002f;
        Vec3Scale(&delta, &velocity, -(length / speed));
        pShape->TestPoint((Vec3_801DE1E0 *)&pContacts[i].mPoint, pBody->mTransform, (Vec3_801DE1E0 *)&delta, (Vec3_801DE1E0 *)&normal, (Vec3_801DE1E0 *)&point, &distance, length);
        int code = fn_801BE648(p->mpUnknown792);
        int state = p->mpState->mId;
        if ((code == 0xB5 || code == 0xBA || code == 0xC5 || code == 0xC3 || code == 0xC4 ||
             code == 0xD2 || code == 0xE0 || code == 0xE5 || code == 0xE4 || code == 0xE6 ||
             code == 0xEB || code == 0xE1 || code == 0xED || code == 0xEC || state == 0x32) &&
            (p->mFlags & 8)) return;
        if (!ScrmIsFieldFlipped()) {
            Vec3RotateXYZ(&direction, &normal, 0, 0, 0x800000);
            Vec2Normalize(&direction, &direction);
        } else Vec2Normalize(&direction, &normal);
        direction.mZ = 0.0f;
        if (normal.mZ > 0.8f || !(normal.mZ >= -0.8f)) {
            p->mMotion.mPos.mX -= p->mMotion.mUnknown40 + p->mMotion.mUnknown40;
            p->mMotion.mPos.mY -= p->mMotion.mUnknown44 + p->mMotion.mUnknown44;
            Vec2Normalize(&direction, &p->mMotion.mUnknown40);
            direction.mX = -direction.mX;
            direction.mY = -direction.mY;
        } else {
            if (!(distance >= 0.0001f)) distance += 0.05555f;
            if (!(p->mMotion.mUnknown40 * direction.mX >= 0.0f) &&
                !(fabsf(distance * direction.mX) >= fabsf(p->mMotion.mUnknown40)))
                p->mMotion.mPos.mX = p->mMotion.mUnknown12.mX;
            else p->mMotion.mPos.mX += direction.mX * distance;
            if (!(p->mMotion.mUnknown44 * direction.mY >= 0.0f) &&
                !(fabsf(distance * direction.mY) >= fabsf(p->mMotion.mUnknown44)))
                p->mMotion.mPos.mY = p->mMotion.mUnknown12.mY;
            else p->mMotion.mPos.mY += direction.mY * distance;
        }
        int angle = MathArcTan2(direction.mY, direction.mX);
        int facing = (angle + 0x800000) & 0xFFFFFF;
        if (code != 0xB5 && code != 0xBA && code != 0xC5 && code != 0xC3 && code != 0xC4 &&
            code != 0xD2 && code != 0xE0 && code != 0xE5 && code != 0xE4 && code != 0xE6 && code != 0xED) {
            switch (p->mpState->mId) {
            case 5: case 10: case 11: case 12: case 15: case 20:
            case 25: case 26: case 27: case 57: case 58: case 93:
                break;
            case 16: {
                Object_80039F5C *pPartner = fn_8009BCE8(&p->mUnknown336);
                if (!PlyrContactResolve(p, angle, facing)) return;
                ScrmSetTackler(pPartner);
                p->mFlags = (p->mFlags | 0x10000) & ~0x80000;
                return;
            }
            case 17: {
                Object_80039F5C *pPartner = fn_8009BCE8(&p->mUnknown336);
                if (!PlyrContactResolve(p, angle, facing)) return;
                ScrmSetTackler(p);
                pPartner->mFlags = (pPartner->mFlags | 0x10000) & ~0x80000;
                return;
            }
            case 32:
                PlyrContactResolve(p, angle, facing);
                return;
            case 36:
                PlyrContactSendHitFrom(p, 10, &facing, 1, &angle);
                break;
            default:
                if (!PlyrContactIsBeforeImpact(p) && !(p->mMotion.mUnknown28 < PlyrMoveGetRatedSpeed(p, 0.5f, 1.0f)))
                    PlyrContactSendHitFrom(p, 58, &facing, 3, &angle);
                break;
            }
            if (!(fabsf(normal.mZ) >= 0.8f)) {
                if (MathAngleDiff(p->mMotion.mUnknown32, facing) > 0x200000) {
                    p->mUnknown512.mUnknown14 = 4;
                    p->mUnknown512.mUnknown4 = angle;
                    p->mUnknown512.mUnknown8 = angle;
                } else {
                    p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = 0.0f;
                }
            }
        }
    }
}

void PhysHitBall(Vector_80039F5C *pImpulse)
{
    Ball_t *pBall = BallGetCurrent();
    if (BallStateGet(pBall, 0) != 1) {
        Vector_80039F5C position, noise, impulse;
        BallGetPosition(pBall, &position);
        impulse.mX = pImpulse->mX;
        impulse.mY = pImpulse->mY;
        impulse.mZ = pImpulse->mZ;
        if (ScrmIsFieldFlipped()) { impulse.mX = -impulse.mX; impulse.mY = -impulse.mY; }
        if (BallStateGet(pBall, 0) == 4) {
            if (!(Vec3Magnitude(&impulse) <= 30.0f)) Vec3Scale(&impulse, &impulse, 4.15f);
            else Vec3Scale(&impulse, &impulse, 5.0f);
        } else Vec3Scale(&impulse, &impulse, 5.0f);
        float force = Vec3Magnitude(&impulse) * SyncRandGetFloat(0);
        noise.mX = force * (SyncRandGetFloat(0) - 0.5f);
        noise.mY = force * (SyncRandGetFloat(0) - 0.5f);
        noise.mZ = force * (SyncRandGetFloat(0) - 0.5f);
        if (!(fabsf(impulse.mX) >= 0.05f) && !(fabsf(impulse.mY) >= 0.05f) && !(impulse.mZ <= 0.0f)) {
            impulse.mX += pBall->mState.mUnknown54.mX;
            impulse.mY += pBall->mState.mUnknown54.mY;
            if (ScrmClassifyPosition(&pBall->mState.mPos, 0, 1) > 2 && !_Phys_uBallHitTimer) _Phys_uBallHitTimer = 1;
        }
        if (!(impulse.mX * pBall->mState.mUnknown54.mX >= 0.0f)) position.mX = pBall->mState.mUnknown28.mX;
        else impulse.mX = 0.0f;
        if (!(impulse.mY * pBall->mState.mUnknown54.mY >= 0.0f)) position.mY = pBall->mState.mUnknown28.mY;
        else impulse.mY = 0.0f;
        if (!(impulse.mZ * pBall->mState.mUnknown54.mZ >= 0.0f)) position.mZ = pBall->mState.mUnknown28.mZ;
        else impulse.mZ = 0.0f;
        Vec3Add(&impulse, &impulse, &noise);
        BallApplyImpulse(pBall, &impulse, &pBall->mState.mPos);
        BallSetPosition(pBall, &position);
        ScrmSetPlayFlag(24, 1);
    }
}

}

int PhysCollisionHandler::OnContacts(float step, RigidBody *pA, RigidBody *pB, unsigned int count,
                                     BodyContact *pContacts)
{
    PhysBodyOwner_t *a = (PhysBodyOwner_t *)pA->mpOwner;
    PhysBodyOwner_t *b = (PhysBodyOwner_t *)pB->mpOwner;
    if (a->mKind == 1 && b->mKind == 1) return 3;
    if (a->mKind != 6 && b->mKind != 6) {
        if (a->mKind == 1) {
            if (b->mKind == 2 || b->mKind == 4) PhysPushPlayer(step, pA, 0, pB, pContacts[0].mShapeB, count, pContacts);
            return 2;
        }
        if (b->mKind == 1) {
            if (a->mKind == 2 || a->mKind == 4) PhysPushPlayer(step, pB, 0, pA, pContacts[0].mShapeA, count, pContacts);
            return 1;
        }
    }
    return 0;
}

void PhysCollisionHandler::OnImpulse(RigidBody *pA, unsigned int indexA, RigidBody *pB, unsigned int indexB,
                                     Vec3_801DE1E0 *pPosA, Vec3_801DE1E0 *pPosB, Vec3_801DE1E0 *pNormal)
{
    PhysBodyOwner_t *a = ((PhysBodyOwner_t *)pA->mpOwner);
    PhysBodyOwner_t *b = ((PhysBodyOwner_t *)pB->mpOwner);
    Vector_80039F5C normal, position;
    if ((a->mKind == 3 || a->mKind == 5 || a->mKind == 4) &&
        (b->mKind == 1 || b->mKind == 6 || b->mKind == 0)) {
        normal.mX = pNormal->x; normal.mY = pNormal->y; normal.mZ = pNormal->z;
        position.mX = pPosA->x; position.mY = pPosA->y; position.mZ = pPosA->z;
        if (a->mKind == 5) BigObjHitStatic(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(b->mpBlock));
        else BigObjHit(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(b->mpBlock));
    } else if ((a->mKind == 1 || a->mKind == 6 || a->mKind == 0) &&
               (b->mKind == 3 || b->mKind == 5 || b->mKind == 4)) {
        normal.mX = -pNormal->x; normal.mY = -pNormal->y; normal.mZ = -pNormal->z;
        position.mX = pPosB->x; position.mY = pPosB->y; position.mZ = pPosB->z;
        if (b->mKind == 5) BigObjHitStatic(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(a->mpBlock));
        else BigObjHit(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(a->mpBlock));
    } else if ((a->mKind == 3 || a->mKind == 5 || a->mKind == 4) &&
               (b->mKind == 3 || b->mKind == 5 || b->mKind == 4)) {
        normal.mX = pNormal->x; normal.mY = pNormal->y; normal.mZ = pNormal->z;
        position.mX = pPosA->x; position.mY = pPosA->y; position.mZ = pPosA->z;
        if (a->mKind == 5) BigObjHitStatic(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(b->mpBlock));
        else BigObjHit(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(b->mpBlock));
        normal.mX = -pNormal->x; normal.mY = -pNormal->y; normal.mZ = -pNormal->z;
        if (b->mKind == 5) BigObjHitStatic(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(a->mpBlock));
        else BigObjHit(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, (BigObjHitter_t *)PlyrObjsFindPlayer(a->mpBlock));
    }
    if (a->mKind != 5 && b->mKind == 6) {
        Vector_80039F5C impulse;
        Vec3Scale(&impulse, pNormal, -1.0f);
        PhysHitBall(&impulse);
    } else if (a->mKind == 6 && b->mKind != 5) PhysHitBall((Vector_80039F5C *)pNormal);
}

void PhysBodyGroup::ApplyForces(void *pStart)
{
    for (unsigned int i = 0; i < (unsigned int)_Phys_iObjectCount; i++) {
        RigidBody *p = _Phys_apObjectBodies[i];
        if (p->mState == 2) {
            Vector_80039F5C force;
            force.mX = 0.0f;
            force.mY = 0.0f;
            force.mZ = -((1.0f / p->mInvMass) * 10.73f);
            ClearBodyForces(p);
            AddBodyForceAtPoint(p, &force, (Vector_80039F5C *)&p->mPosition);
        }
    }
}

extern "C" {
void PhysAddCapsule(int handle, ShapeCollection *pSet, BigObjInst *pObject,
                 Vector_80039F5C *pA, Vector_80039F5C *pB, float friction, float bounce, float radius)
{
    float y = pA->mY; pA->mY = -pA->mZ; pA->mZ = y;
    y = pB->mY; pB->mY = -pB->mZ; pB->mZ = y;
    _Phys_apObjectShapes[_Phys_iShapeCount] = new (0) CapsuleShape((Vec3_801DE1E0 *)pA, (Vec3_801DE1E0 *)pB, friction, bounce, radius);
    pSet->AddShape(_Phys_apObjectShapes[_Phys_iShapeCount++]);
}
void PhysAddBox(int handle, ShapeCollection *pSet, BigObjInst *pObject,
                 Vector_80039F5C *pA, Vector_80039F5C *pB, float friction, float bounce)
{
    float y = pA->mY; pA->mY = -pA->mZ; pA->mZ = y;
    y = pB->mY; pB->mY = -pB->mZ; pB->mZ = y;
    Vector_80039F5C center;
    Vec3Add(&center, pA, pB);
    Vec3Scale(&center, &center, 0.5f);
    _Phys_apObjectShapes[_Phys_iShapeCount] = new (0) BoxShape((Vec3_801DE1E0 *)&center, friction, bounce,
                                     fabsf(pA->mX - center.mX), fabsf(pA->mY - center.mY), fabsf(pA->mZ - center.mZ));
    pSet->AddShape(_Phys_apObjectShapes[_Phys_iShapeCount++]);
}
void PhysAddSphere(int handle, ShapeCollection *pSet, BigObjInst *pObject,
                 Vector_80039F5C *pPoint, float friction, float bounce, float radius)
{
    float y = pPoint->mY; pPoint->mY = -pPoint->mZ; pPoint->mZ = y;
    _Phys_apObjectShapes[_Phys_iShapeCount] = new (0) SphereShape((Vec3_801DE1E0 *)pPoint, friction, bounce, radius);
    pSet->AddShape(_Phys_apObjectShapes[_Phys_iShapeCount++]);
}
void PhysSetShapeNames(PhysBodyOwner_t *p, char (*pNames)[32], unsigned int count)
{
    p->mCount = count;
    if (count) {
        unsigned char map[20];
        char *unique[20];
        unsigned char names = 1;
        unsigned char i = 1;
        map[0] = 0;
        int bytes = strlen(pNames[0]) + 1;
        for (; i < count; i++) {
            int found = 0;
            for (unsigned char j = 0; j < names; j++) {
                if (!strcmp(pNames[j], pNames[i])) {
                    map[i] = j; found = 1; break;
                }
            }
            if (!found) {
                if (names != i) strncpy(pNames[names], pNames[i], 32);
                bytes += strlen(pNames[names]) + 1;
                map[i] = names++;
            }
        }
        p->mNames = (char **)fn_801D2B7C(bytes + count * 4, 0, 0);
        char *pText = (char *)(p->mNames + count);
        for (i = 0; i < names; i++) {
            unique[i] = pText;
            strcpy(pText, pNames[i]);
            pText += strlen(unique[i]) + 1;
        }
        for (i = 0; i < count; i++) p->mNames[i] = unique[map[i]];
    } else {
        p->mNames = 0;
    }
}
void PhysFreeShapeNames(PhysBodyOwner_t *p)
{
    if (p->mNames) {
        fn_801D2BD0(p->mNames);
        p->mNames = 0;
        p->mCount = 0;
    }
}
void PhysLoadObject(int handle, BigObj_t *pObject, int objectIndex)
{
    BigObjInst *pState = pObject->mUnknown472;
    float mass = 0.0f;
    pState->mUnknown382 = 0;
    pState->mUnknown408 = 0.0f;
    pState->mUnknown412 = 0.0f;
    ObjParseRewind(handle);
    if (ObjParseFindPath(handle, "physics")) mass = ObjParseGetFloat(handle, "mass");
    ObjParseRewind(handle);
    if (ObjParseFindPath(handle, "collision")) {
        Vector_80039F5C *pPos = (Vector_80039F5C *)&pState->mState.mUnknown0;
        void *pRot = &pState->mState.mUnknown88;
        Vector_80039F5C inertia, velocity, acceleration, initial;
        float matrix[16];
        char type[32];
        _Phys_apObjectPositions[_Phys_iObjectCount] = pPos;
        pState->mUnknown408 = ObjParseGetFloat(handle, "aeroConst");
        pState->mUnknown412 = ObjParseGetFloat(handle, "spinDamp");
        pState->mUnknown382 = ObjParseGetInt(handle, "helpOffGround");
        int cursor = ObjParseGetCursor(handle);
        if (ObjParseFindChild(handle, "primitive")) {
            while (ObjParseNext(handle)) {}
        }
        ObjParseSetCursor(handle, cursor);
        ShapeCollection *pSet;
        if (!(mass <= 0.0f)) pSet = new (0) ShapeCollection(20, 0);
        else pSet = new (0) ShapeCollection(20, 2);
        if (ObjParseFindChild(handle, "primitive")) {
            char names[20][32];
            Vector_80039F5C a, b, c;
            unsigned char count = 0;
            do {
                ObjParseGetString(handle, "name", names[count], 32);
                ObjParseGetString(handle, "PRIM_TYPE", type, 32);
                if (!strcmp(type, "CYLINDER")) {
                    ObjParseGetVector(handle, "PRIM_CYL_END1", &a.mX);
                    ObjParseGetVector(handle, "PRIM_CYL_END2", &b.mX);
                    float radius = ObjParseGetFloat(handle, "PRIM_CYL_RADIUS");
                    float friction = ObjParseGetFloat(handle, "friction");
                    float bounce = ObjParseGetFloat(handle, "bounce");
                    PhysAddCapsule(handle, pSet, pState, &a, &b, friction, bounce, radius);
                } else if (!strcmp(type, "BOX")) {
                    ObjParseGetVector(handle, "PRIM_BOX_MIN", &a.mX);
                    ObjParseGetVector(handle, "PRIM_BOX_MAX", &c.mX);
                    float friction = ObjParseGetFloat(handle, "friction");
                    float bounce = ObjParseGetFloat(handle, "bounce");
                    PhysAddBox(handle, pSet, pState, &a, &c, friction, bounce);
                } else if (!strcmp(type, "SPHERE")) {
                    ObjParseGetVector(handle, "PRIM_SPH_POS", &a.mX);
                    float radius = ObjParseGetFloat(handle, "PRIM_SPH_RADIUS");
                    float friction = ObjParseGetFloat(handle, "friction");
                    float bounce = ObjParseGetFloat(handle, "bounce");
                    PhysAddSphere(handle, pSet, pState, &a, friction, bounce, radius);
                }
                count++;
            } while (ObjParseNext(handle));
            PhysSetShapeNames(&_Phys_aBodyOwners[_Phys_iBodyCount], names, count);
        }
        ObjParseRewind(handle);
        RigidBody *pBody;
        if (ObjParseFindPath(handle, "physics")) {
            if (ObjParseGetMatrix(handle, "moi", matrix)) {
                inertia.mX = matrix[0] * 3.0f;
                inertia.mY = matrix[10] * 3.0f;
                inertia.mZ = matrix[5] * 3.0f;
            } else {
                inertia.mX = 0.6640654802322388f;
                inertia.mY = 1.3281309604644775f;
                inertia.mZ = 0.6640654802322388f;
            }
            mass = ObjParseGetFloat(handle, "mass");
            if (!(mass <= 0.0f)) _Phys_aBodyOwners[_Phys_iBodyCount].mKind = 3;
            else _Phys_aBodyOwners[_Phys_iBodyCount].mKind = 4;
            _Phys_aBodyOwners[_Phys_iBodyCount].mpObject = pObject;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown2 = 1;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown16 = objectIndex;
            _Phys_aBodyOwners[_Phys_iBodyCount].mType = _Phys_iBodyCount;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown22 = -1;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown20 = -1;
            pBody = new (0) RigidBody((Vec3_801DE1E0 *)&inertia, pSet, &_Phys_aBodyOwners[_Phys_iBodyCount], mass,
                                      ObjParseGetFloat(handle, "dThres"));
            if (ObjParseGetVector(handle, "iVel", &initial.mX)) SetBodyLinearVelocity(pBody, &initial);
            else {
                velocity.mX = 0.0f;
                velocity.mY = 0.0f;
                velocity.mZ = 0.0f;
                acceleration.mX = 0.0f;
                acceleration.mY = 0.0f;
                acceleration.mZ = 0.0f;
                SetBodyAngularMomentum(pBody, (Vec3_801DE1E0 *)&velocity); SetBodyLinearMomentum(pBody, &acceleration);
            }
            SetBodyPosition(pBody, (Vec3_801DE1E0 *)pPos); SetBodyOrientation(pBody, (Vec4_801DE1E0 *)pRot);
            if (!(mass <= 0.0f)) {
                if (ObjParseGetInt(handle, "enable")) SetBodyMotionState(pBody, 2);
                else SetBodyMotionState(pBody, 3);
            }
        } else {
            mass = 0.0f;
            inertia.mX = 0.6640654802322388f;
            inertia.mY = 1.3281309604644775f;
            inertia.mZ = 0.6640654802322388f;
            _Phys_aBodyOwners[_Phys_iBodyCount].mKind = 5;
            _Phys_aBodyOwners[_Phys_iBodyCount].mpObject = pObject;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown2 = 1;
            _Phys_aBodyOwners[_Phys_iBodyCount].mType = _Phys_iBodyCount;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown16 = objectIndex;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown22 = -1;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown20 = -1;
            pBody = new (0) RigidBody((Vec3_801DE1E0 *)&inertia, pSet, &_Phys_aBodyOwners[_Phys_iBodyCount], mass, 2.0f);
            velocity.mX = 0.0f;
            velocity.mY = 0.0f;
            velocity.mZ = 0.0f;
            acceleration.mX = 0.0f;
            acceleration.mY = 0.0f;
            acceleration.mZ = 0.0f;
            SetBodyAngularMomentum(pBody, (Vec3_801DE1E0 *)&velocity); SetBodyLinearMomentum(pBody, &acceleration);
            SetBodyPosition(pBody, (Vec3_801DE1E0 *)pPos); SetBodyOrientation(pBody, (Vec4_801DE1E0 *)pRot);
        }
        float damping = ObjParseGetFloat(handle, "rollDamp");
        if (damping == 0.0f) damping = 4.0f;
        pBody->mUnknown04C = damping;
        _Phys_pBodyGroup->AddBody(pBody);
        _Phys_apObjectBodies[_Phys_iObjectCount] = pBody;
        pObject->mUnknown476 = (BigObjFlags_t *)&_Phys_aBodyOwners[_Phys_iBodyCount];
        _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown20 = _Phys_iObjectCount;
        if (ObjParseFindPath(handle, "physics") && ObjParseFindChild(handle, "constraint")) {
            do {
                Vec3_801DE1E0 local, world;
                ObjParseGetVector(handle, "location", &local.x);
                float y = local.y; local.y = -local.z; local.z = y;
                Vec3Add(&world, &local, pPos);
                int index = _Phys_iConstraintCount;
                _Phys_apConstraints[index] = new (0) PointConstraint(pBody, _Phys_pGroundBody, &local, &world);
                _Phys_pWorld->AddConstraint(_Phys_apConstraints[_Phys_iConstraintCount]);
                _Phys_iConstraintCount++;
            } while (ObjParseNext(handle));
        }
        _Phys_iObjectCount++;
        _Phys_iBodyCount++;
    }
}

void PhysAddPlayers(void)
{
    Vector_80039F5C velocity, force, a, b, inertia;
    Quat_801EB488 rotation;
    Vector_80039F5C position = {0.0f, 0.0f, 3.0f};
    unsigned int team = 0;
    Object_8008044C query;
    PlayerCursorOpenDefault(&query, 0);
    for (; team < 2; team++) {
        for (unsigned int index = 0; index < 7; index++) {
            float radius = 0.45f;
            Object_80039F5C *pPlayer = PlyrGet((unsigned char)team, index);
            Block_80170E64 *pBlock = pPlayer->mpUnknown4;
            Object_8003DEC4 *pModel = (Object_8003DEC4 *)pBlock;
            PlayerDbSeekId(&query, pModel->mUnknown4956, 0);
            float height = PlayerDbGetHeight(&query) * 0.02631579f;
            float mass = 150.0f;
            int slot = team * 7 + index;
            inertia.mX = mass * height * height * (1.0f / 12.0f) + mass * (radius * 0.5f) * (radius * 0.5f);
            inertia.mY = mass * radius * radius * 0.5f;
            inertia.mZ = inertia.mX;
            a.mX = a.mZ = 0.0f;
            a.mY = height * 0.5f;
            b.mX = b.mZ = 0.0f;
            b.mY = -a.mY;
            _Phys_apPlayerShapes[slot] = new (0) CapsuleShape((Vec3_801DE1E0 *)&a, (Vec3_801DE1E0 *)&b, 0.5f, 0.6f, radius);
            ShapeCollection *pSet = new (0) ShapeCollection(1, 1);
            pSet->AddShape(_Phys_apPlayerShapes[slot]);
            _Phys_aBodyOwners[_Phys_iBodyCount].mpBlock = pBlock;
            _Phys_aBodyOwners[_Phys_iBodyCount].mKind = 1;
            _Phys_aBodyOwners[_Phys_iBodyCount].mpObject = 0;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown2 = 1;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown20 = -1;
            _Phys_aBodyOwners[_Phys_iBodyCount].mType = _Phys_iBodyCount;
            _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown22 = slot;
            RigidBody *pBody = new (0) RigidBody((Vec3_801DE1E0 *)&inertia, pSet, &_Phys_aBodyOwners[_Phys_iBodyCount], mass, 0.4f);
            velocity.mZ = velocity.mY = velocity.mX = 0.0f;
            force.mZ = force.mY = force.mX = 0.0f;
            QuatFromEuler(&rotation, 0, 0, 0);
            SetBodyPose(pBody, (Vec3_801DE1E0 *)&position, (Vec4_801DE1E0 *)&rotation);
            position.mZ += 5.0f;
            SetBodyMotionState(pBody, 1);
            SetBodyAngularMomentum(pBody, (Vec3_801DE1E0 *)&velocity); SetBodyLinearMomentum(pBody, &force);
            _Phys_pBodyGroup->AddBody(pBody);
            _Phys_apPlayerBodies[slot] = pBody;
            _Phys_iBodyCount++;
        }
    }
    PlayerCursorClose(&query);
}

void PhysAddBall(void)
{
    Vector_80039F5C velocity, force, center, center2, inertia;
    Quat_801EB488 rotation;
    Vector_80039F5C position = {0.0f, 0.0f, 3.0f};
    BallGetModel(BallGetCurrent());
    float radius = 0.12f;
    float length = 0.2f;
    float mass = 1.0f;
    inertia.mX = mass * (radius * radius * 0.25f + length * length * (1.0f / 12.0f));
    inertia.mY = inertia.mX;
    inertia.mZ = mass * radius * radius * 0.5f;
    center.mX = center.mY = center.mZ = 0.0f;
    center2.mX = center2.mY = center2.mZ = 0.0f;
    _Phys_pBallShape = new (0) SphereShape((Vec3_801DE1E0 *)&center, 0.1f, 1.0f, 0.15f);
    ShapeCollection *pSet = new (0) ShapeCollection(1, 1);
    pSet->AddShape(_Phys_pBallShape);
    _Phys_aBodyOwners[_Phys_iBodyCount].mpBlock = 0;
    _Phys_aBodyOwners[_Phys_iBodyCount].mpObject = 0;
    _Phys_aBodyOwners[_Phys_iBodyCount].mKind = 6;
    _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown22 = -1;
    _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown2 = 1;
    _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown20 = -1;
    _Phys_aBodyOwners[_Phys_iBodyCount].mType = _Phys_iBodyCount;
    RigidBody *pBody = new (0) RigidBody((Vec3_801DE1E0 *)&inertia, pSet, &_Phys_aBodyOwners[_Phys_iBodyCount], mass, 0.4f);
    velocity.mZ = velocity.mY = velocity.mX = 0.0f;
    force.mZ = force.mY = force.mX = 0.0f;
    SetBodyPosition(pBody, (Vec3_801DE1E0 *)&position);
    QuatFromEuler(&rotation, 0, 0, 0);
    SetBodyOrientation(pBody, (Vec4_801DE1E0 *)&rotation);
    SetBodyMotionState(pBody, 1);
    SetBodyAngularMomentum(pBody, (Vec3_801DE1E0 *)&velocity); SetBodyLinearMomentum(pBody, &force);
    _Phys_pBodyGroup->AddBody(pBody);
    _Phys_pBallBody = pBody;
    _Phys_uBallHitTimer = 0;
    _Phys_iBodyCount++;
}

void PhysInit(void)
{
    _Phys_iConstraintCount = 0;
    _Phys_iObjectCount = 0;
    _Phys_iBodyCount = 0;
    _Phys_iShapeCount = 0;
    memset(_Phys_aBodyOwners, 0, sizeof(PhysBodyOwner_t) * 142);
    _Phys_sTime.SetSeconds(0.0f);
    _Phys_pBodyGroup = new (0) PhysBodyGroup;
    Vector_80039F5C center;
    center.mX = center.mY = center.mZ = 0.0f;
    Vector_80039F5C position;
    Vector_80039F5C inertia;
    Quat_801EB488 rotation;
    float sizeX = 2000.0f;
    float sizeY = 2000.0f;
    float sizeZ = 2.0f;
    float mass = 40.0f;
    inertia.mX = (sizeY * sizeY + sizeZ * sizeZ) * mass * (1.0f / 12.0f);
    inertia.mY = (sizeX * sizeX + sizeZ * sizeZ) * mass * (1.0f / 12.0f);
    inertia.mZ = (sizeX * sizeX + sizeY * sizeY) * mass * (1.0f / 12.0f);
    _Phys_pGroundShape = new (0) BoxShape((Vec3_801DE1E0 *)&center, 0.85f, 0.4f, 300.0f, 300.0f, 1.0f);
    ShapeCollection *pShapes = new (0) ShapeCollection(1, 3);
    pShapes->AddShape(_Phys_pGroundShape);
    _Phys_aBodyOwners[_Phys_iBodyCount].mpObject = 0;
    _Phys_aBodyOwners[_Phys_iBodyCount].mKind = 0;
    _Phys_aBodyOwners[_Phys_iBodyCount].mType = _Phys_iBodyCount;
    _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown22 = -1;
    _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown20 = -1;
    _Phys_aBodyOwners[_Phys_iBodyCount].mUnknown2 = 1;
    RigidBody *pBody = new (0) RigidBody((Vec3_801DE1E0 *)&inertia, pShapes, &_Phys_aBodyOwners[_Phys_iBodyCount], 0.0f, 0.4f);
    position.mX = 0.0f;
    position.mY = 0.0f;
    position.mZ = -1.0f;
    QuatFromEuler(&rotation, 0, 0, 0);
    SetBodyPosition(pBody, (Vec3_801DE1E0 *)&position);
    SetBodyOrientation(pBody, (Vec4_801DE1E0 *)&rotation);
    _Phys_pBodyGroup->AddBody(pBody);
    _Phys_pGroundBody = pBody;
    _Phys_iBodyCount++;
    _Phys_pIntegrator = new (0) EulerIntegrator(_Phys_pBodyGroup, 1846);
    _Phys_pBodyGroup->SetIntegrator(_Phys_pIntegrator);
    _Phys_pCollisionHandler = new (0) PhysCollisionHandler;
    _Phys_pContacts = new (0) ContactSystem(142, 128, 0.3f, 0.002f, _Phys_pCollisionHandler);
    {
        Vec3_801DE1E0 max = {1000.0f, 1000.0f, 1000.0f};
        Vec3_801DE1E0 min = {-1000.0f, -1000.0f, 0.0f};
        _Phys_pContacts->SetCorrectionLimits(&min, &max);
    }
    _Phys_pSleep = new (0) SleepController(3.0f, 10.0f, 0);
    _Phys_pWorld = new (0) PhysicsWorld(1, 8, _Phys_pContacts, _Phys_pSleep);
    _Phys_pWorld->AddGroup(_Phys_pBodyGroup);
    {
        PhysicsTime next;
        next = _Phys_sTime;
        next.AddSeconds(1.0f / 60.0f);
        _Phys_pWorld->Step(&_Phys_sTime, &next);
        _Phys_sTime = next;
    }
}

void ApplyBodyAngularImpulse(RigidBody *, Vector_80039F5C *);



void GetBodyOrientation(RigidBody *, Quat_801EB488 *);
int Vec3Equal(void *, void *, float);
int QuatIsEqual(void *, void *, float);
void Vec3Normalize(void *, void *);
float Vec3Distance(void *, void *);
void ScrmEndPlay(void);
void PhysDebugLine(Vec3_801DE1E0 *, Vec3_801DE1E0 *, int, int, int);
int fn_800AD9B4(void);
unsigned char _Phys_bFrozen = 0;
unsigned int _Phys_uDebugDraw = 0;

void PhysUpdateBallRest(void)
{
    if (_Phys_uBallHitTimer) {
        Ball_t *pBall = BallGetCurrent();
        if (fn_800AD9B4() == 3 && ScrmClassifyPosition(&pBall->mState.mPos, 0, 1) > 2) {
            if (!((float)_Phys_uBallHitTimer++ <= gFrameTimeScale * 45.0f)) {
                _Phys_uBallHitTimer = 0;
                ScrmEndPlay();
            }
        } else _Phys_uBallHitTimer = 0;
    }
}

void PhysDebugLine(Vec3_801DE1E0 *pFrom, Vec3_801DE1E0 *pTo, int red, int green, int blue)
{
}

void PhysUpdatePlayers(void)
{
    for (unsigned int team = 0; team < 2; team++) {
        for (unsigned int index = 0; index < 7; index++) {
            RigidBody *pBody = _Phys_apPlayerBodies[index + team * 7];
            Object_80039F5C *pPlayer = PlyrObjsFindPlayer(((PhysBodyOwner_t *)pBody->mpOwner)->mpBlock);
            Vector_80039F5C velocity, direction;
            Quat_801EB488 rotation, oldRotation;
            QuatEulerAngles_t oldAngles;
            Vector_80039F5C a, b, c;
            QuatEulerAngles_t angles;
            velocity.mX = 0.0f;
            velocity.mY = 0.0f;
            velocity.mZ = 0.0f;
            fn_8009BF5C(pPlayer, 0, &a, &angles);
            fn_8009BF5C(pPlayer, 4, &b, 0);
            fn_8009BF5C(pPlayer, 8, &c, 0);
            Vec3Add(&c, &c, &b);
            Vec3Scale(&c, &c, 0.5f);
            fn_8009BF5C(pPlayer, 26, &b, 0);
            Vec3Add(&a, &b, &c);
            Vec3Scale(&a, &a, 0.5f);
            if (ScrmIsFieldFlipped()) {
                a.mX = -a.mX;
                a.mY = -a.mY;
                angles.mUnknown8 += 0x800000;
                QuatFromEuler(&rotation, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
            } else QuatFromEuler(&rotation, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
            Vec3_801DE1E0 *pPos = &pBody->mPosition;
            GetBodyOrientation(pBody, &oldRotation);
            Vec3Sub(&direction, &a, pPos);
            float length = Vec3Magnitude(&direction);
            if (!(length <= 0.5f)) Vec3Scale(&direction, &direction, 0.06f / length);
            Vec3Scale(&direction, &direction, 60.0f);
            velocity.mX = angles.mUnknown0 * 0.000021457672119140625f;
            velocity.mY = angles.mUnknown4 * 0.000021457672119140625f;
            velocity.mZ = angles.mUnknown8 * 0.000021457672119140625f;
            QuatToEuler(&oldAngles, &oldRotation.mX);
            velocity.mX -= oldAngles.mUnknown0 * 0.000021457672119140625f;
            velocity.mY -= oldAngles.mUnknown4 * 0.000021457672119140625f;
            velocity.mZ -= oldAngles.mUnknown8 * 0.000021457672119140625f;
            SetBodyPose(pBody, (Vec3_801DE1E0 *)&a, (Vec4_801DE1E0 *)&rotation);
            SetBodyLinearVelocity(pBody, &direction);
            SetBodyAngularMomentum(pBody, (Vec3_801DE1E0 *)&velocity);
        }
    }
}

void PhysUpdateBall(void)
{
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C zero;
    zero.mX = 0.0f;
    zero.mY = 0.0f;
    zero.mZ = 0.0f;
    Vector_80039F5C velocity, position;
    RigidBody *pBody = _Phys_pBallBody;
    BallGetVelocity(pBall, &velocity);
    Vec3Scale(&velocity, &velocity, 60.0f);
    BallGetPosition(pBall, &position);
    if (ScrmIsFieldFlipped()) {
        velocity.mX = -velocity.mX; velocity.mY = -velocity.mY;
        position.mX = -position.mX; position.mY = -position.mY;
    }
    SetBodyPosition(pBody, (Vec3_801DE1E0 *)&position);
    SetBodyLinearVelocity(pBody, &velocity);
    SetBodyAngularMomentum(pBody, (Vec3_801DE1E0 *)&zero);
}

void PhysUpdateObjects(void)
{
    for (unsigned int i = 0; i < (unsigned int)_Phys_iObjectCount; i++) {
        RigidBody *pBody = _Phys_apObjectBodies[i];
        if (!pBody) continue;
        PhysBodyOwner_t *pMetadata = ((PhysBodyOwner_t *)pBody->mpOwner);
        if (pMetadata->mKind == 3) {
            Vec3_801DE1E0 *pPos = &pBody->mPosition;
            _Phys_apObjectPositions[i]->mX = pPos->x;
            _Phys_apObjectPositions[i]->mY = pPos->y;
            _Phys_apObjectPositions[i]->mZ = pPos->z;
            GetBodyOrientation(pBody, (Quat_801EB488 *)((char *)_Phys_apObjectPositions[i] + 88));
        } else if (BigObjGetItemSkeleton(pMetadata->mpObject)) {
            int angles[3];
            Quat_801EB488 rotation;
            Vector_80039F5C position;
            Quat_801EB488 oldRotation;
            DynObjGetRootAngles(pMetadata->mpObject, angles);
            angles[2] = (*(int *)((char *)_Phys_apObjectPositions[i] + 24) + 0x400000) & 0xFFFFFF;
            QuatFromEuler(&rotation, angles[2], angles[1], angles[0]);
            position.mX = _Phys_apObjectPositions[i]->mX;
            position.mY = _Phys_apObjectPositions[i]->mY;
            position.mZ = pMetadata->mpObject->mUnknown172.mUnknown8[1];
            GetBodyOrientation(pBody, &oldRotation);
            if (!Vec3Equal(&position, &pBody->mPosition, 0.01f) ||
                !QuatIsEqual(&rotation, &oldRotation, 0.01f)) {
                SetBodyPose(pBody, (Vec3_801DE1E0 *)&position, (Vec4_801DE1E0 *)&rotation);
            }
        }
    }
}

void PhysDebugDraw(void)
{
    int renderState = VptGetMatrixStack();
    unsigned int index = 0;
    MatSetStack(renderState);
    MatPushUnit();
    Collision_pDebugLineProc = PhysDebugLine;
    BodyGroupNode *pNode = _Phys_pBodyGroup->FirstNode();
    RigidBody *pBody;
    for (pBody = _Phys_pBodyGroup->NextBody(&pNode); pBody != 0; pBody = _Phys_pBodyGroup->NextBody(&pNode)) {
        ShapeCollection *pShapes = pBody->mpShapes;
        if (!pShapes) continue;
        if ((unsigned int)pBody->mState <= 1) {
            switch (index % 7) {
            case 0:
                if (_Phys_uDebugDraw & 1) pShapes->DrawShapes(pBody->mTransform, 250, 0, 0);
                if (_Phys_uDebugDraw & 2) pShapes->DrawBounds(250, 0, 0, 1);
                break;
            case 1:
                if (_Phys_uDebugDraw & 1) pShapes->DrawShapes(pBody->mTransform, 0, 250, 0);
                if (_Phys_uDebugDraw & 2) pShapes->DrawBounds(0, 250, 0, 1);
                break;
            case 2:
                if (_Phys_uDebugDraw & 1) pShapes->DrawShapes(pBody->mTransform, 0, 0, 250);
                if (_Phys_uDebugDraw & 2) pShapes->DrawBounds(0, 0, 250, 1);
                break;
            case 3:
                if (_Phys_uDebugDraw & 1) pShapes->DrawShapes(pBody->mTransform, 250, 250, 250);
                if (_Phys_uDebugDraw & 2) pShapes->DrawBounds(250, 250, 250, 1);
                break;
            case 4:
                if (_Phys_uDebugDraw & 1) pShapes->DrawShapes(pBody->mTransform, 250, 250, 0);
                if (_Phys_uDebugDraw & 2) pShapes->DrawBounds(250, 250, 0, 1);
                break;
            case 5:
                if (_Phys_uDebugDraw & 1) pShapes->DrawShapes(pBody->mTransform, 0, 250, 250);
                if (_Phys_uDebugDraw & 2) pShapes->DrawBounds(0, 250, 250, 1);
                break;
            default:
                if (_Phys_uDebugDraw & 1) pShapes->DrawShapes(pBody->mTransform, 250, 0, 250);
                if (_Phys_uDebugDraw & 2) pShapes->DrawBounds(250, 0, 250, 1);
                break;
            }
            index++;
        } else if (pBody->mState == 2) pShapes->DrawShapes(pBody->mTransform, 250, 250, 250);
        else pShapes->DrawShapes(pBody->mTransform, 250, 150, 150);
    }
    MatPop();
}

PhysicsTime _Phys_sTime;

void PhysUpdate(float dt)
{
    PhysicsTime next;
    PhysUpdatePlayers();
    PhysUpdateBall();
    if (!_Phys_bFrozen) {
        next = _Phys_sTime;
        next.AddSeconds(dt * (1.0f / 60.0f));
        _Phys_pWorld->Step(&_Phys_sTime, &next);
        _Phys_sTime = next;
    }
    PhysUpdateBallRest();
    if (_Phys_uDebugDraw) PhysDebugDraw();
    PhysUpdateObjects();
}

void PhysShutdown(void)
{
    BodyGroupNode *pNode;
    RigidBody *pBody;

    _Phys_pWorld->RemoveGroup(_Phys_pBodyGroup);
    for (unsigned int i = 0; i < _Phys_iConstraintCount; i++) {
        _Phys_pWorld->RemoveConstraint(_Phys_apConstraints[i]);
        delete _Phys_apConstraints[i];
    }
    pNode = _Phys_pBodyGroup->FirstNode();
    pBody = _Phys_pBodyGroup->NextBody(&pNode);
    while (pBody) {
        _Phys_pBodyGroup->RemoveBody(pBody);
        pNode = _Phys_pBodyGroup->FirstNode();
        delete pBody->mpShapes;
        delete pBody;
        pBody = _Phys_pBodyGroup->NextBody(&pNode);
    }
    delete _Phys_pGroundShape;
    delete _Phys_pWorld;
    delete _Phys_pBodyGroup;
    delete _Phys_pIntegrator;
    delete _Phys_pContacts;
    delete _Phys_pCollisionHandler;
    delete _Phys_pSleep;
    for (int i = 0; i < 14; i++) {
        delete _Phys_apPlayerShapes[i];
    }
    delete _Phys_pBallShape;
    while (_Phys_iObjectCount) {
        _Phys_iObjectCount--;
    }
    while (_Phys_iBodyCount) {
        PhysFreeShapeNames(&_Phys_aBodyOwners[--_Phys_iBodyCount]);
    }
    while (_Phys_iShapeCount) {
        delete _Phys_apObjectShapes[--_Phys_iShapeCount];
    }
    _Phys_pGroundShape = 0;
    _Phys_pBodyGroup = 0;
    _Phys_pWorld = 0;
    _Phys_pIntegrator = 0;
    _Phys_pCollisionHandler = 0;
    _Phys_pContacts = 0;
    _Phys_pSleep = 0;
    _Phys_iObjectCount = 0;
    _Phys_iBodyCount = 0;
    _Phys_iConstraintCount = 0;
    _Phys_uBallHitTimer = 0;
}

unsigned char PhysIsBall(int type)
{
    unsigned char result = 0;
    if ((unsigned int)type < (unsigned int)_Phys_iBodyCount) {
        result = _Phys_aBodyOwners[type].mKind == 6;
    }
    return result;
}
int PhysIsPlayer(int type)
{
    int result = 0;
    if ((unsigned int)type < (unsigned int)_Phys_iBodyCount) {
        result = _Phys_aBodyOwners[type].mKind == 1;
    }
    return result;
}
void PhysSetBodyPose(int id, float *pA, float *pB)
{
    SetBodyPose(_Phys_apObjectBodies[id], (Vec3_801DE1E0 *)pA, (Vec4_801DE1E0 *)pB);
}
void PhysSleepBody(int id)
{
    RigidBody *pBody = _Phys_apObjectBodies[id];
    if (pBody->mState) SetBodyMotionState(pBody, 3);
}
void PhysApplyImpulse(BigObj_t *pOwner, float *p)
{
    BigObjFlags_t *pFlags = pOwner->mUnknown476;
    if (pFlags) {
        RigidBody *pBody = _Phys_apObjectBodies[pFlags->mUnknown20];
        Vector_80039F5C *pPos = (Vector_80039F5C *)&pBody->mPosition;
        if (pPos->mZ < 1.0f && p[2] < 0.0f) {
            Vector_80039F5C velocity;
            Vector_80039F5C impulse;
            Vector_80039F5C push = {0.0f};
            push.mZ = -p[2];
            impulse = push;
            ApplyBodyImpulseAtPoint(pBody, (Vec3_801DE1E0 *)&impulse, (Vec3_801DE1E0 *)pPos);
            Vec3Scale(&velocity, p, 0.1f);
            ApplyBodyAngularImpulse(pBody, &velocity);
        }
    }
}
void PhysDampLinear(BigObj_t *pOwner, float value)
{
    BigObjFlags_t *pFlags = pOwner->mUnknown476;
    if (pFlags) {
        RigidBody *pBody = _Phys_apObjectBodies[pFlags->mUnknown20];
        Vector_80039F5C impulse;
        Vec3Scale(&impulse, &pBody->mLinearVelocity, -value);
        impulse.mZ = 0.0f;
        ApplyBodyImpulseAtPoint(pBody, (Vec3_801DE1E0 *)&impulse, &pBody->mPosition);
    }
}
void PhysDampAngular(BigObj_t *pOwner, float value)
{
    BigObjFlags_t *pFlags = pOwner->mUnknown476;
    if (pFlags) {
        RigidBody *pBody = _Phys_apObjectBodies[pFlags->mUnknown20];
        Vector_80039F5C velocity;
        Vec3Scale(&velocity, &pBody->mAngularMomentum, -value);
        ApplyBodyAngularImpulse(pBody, &velocity);
    }
}
void PhysPlayerHitObject(Object_80039F5C *pPlayer)
{
    Vector_80039F5C position;
    int ownerIndex = 142;
    int nearestIndex = 142;
    unsigned int shapeIndex = 0;
    float nearest = 3.4028234663852886e+38f;
    position.mX = pPlayer->mMotion.mPos.mX;
    position.mY = pPlayer->mMotion.mPos.mY;
    position.mZ = pPlayer->mMotion.mPos.mZ;
    if (ScrmIsFieldFlipped()) { position.mX = -position.mX; position.mY = -position.mY; }
    Vector_80039F5C point;
    for (unsigned int i = 0; i < (unsigned int)_Phys_iBodyCount; i++) {
        if (_Phys_aBodyOwners[i].mKind == 4 || _Phys_aBodyOwners[i].mKind == 2) {
            RigidBody *pBody = _Phys_apObjectBodies[(short)_Phys_aBodyOwners[i].mUnknown20];
            unsigned int count = pBody->mpShapes->mCount;
            for (unsigned int j = 0; j < count; j++) {
                if (!(nearest <= 0.75f)) {
                    CollisionShape *pShape = pBody->mpShapes->GetShape(j);
                    Vector_80039F5C delta, normal, direction;
                    switch (pShape->mType) {
                    case 2:
                        ((BoxShape *)pShape)->ClosestSurfacePoint((Vec3_801DE1E0 *)&position, pBody->mTransform, (Vec3_801DE1E0 *)&delta, (Vec3_801DE1E0 *)&point);
                        break;
                    case 1: {
                        ((CapsuleShape *)pShape)->GetWorldSegment(pBody->mTransform, (Vec3_801DE1E0 *)&delta, (Vec3_801DE1E0 *)&normal, (Vec3_801DE1E0 *)&direction);
                        Vec3Normalize(&direction, &direction);
                        unsigned char hit;
                        ((CapsuleShape *)pShape)->ClosestSurfacePoint((Vec3_801DE1E0 *)&position, (Vec3_801DE1E0 *)&delta, (Vec3_801DE1E0 *)&normal, (Vec3_801DE1E0 *)&direction, (Vec3_801DE1E0 *)&point, &hit);
                        break;
                    }
                    }
                    float distance = Vec3Distance(&position, &point);
                    if (!(distance >= nearest)) {
                        nearest = distance;
                        nearestIndex = i;
                        shapeIndex = j;
                    }
                }
            }
        } else if (_Phys_aBodyOwners[i].mKind == 1 && PlyrObjsFindPlayer(_Phys_aBodyOwners[i].mpBlock) == pPlayer) {
            ownerIndex = i;
        }
    }
    if (nearestIndex != 142 && ownerIndex != 142) {
        Vector_80039F5C zero;
        zero.mX = zero.mY = zero.mZ = 0.0f;
        BigObjHit(_Phys_aBodyOwners[nearestIndex].mpObject, &point.mX, &zero.mX, _Phys_aBodyOwners[nearestIndex].mNames[shapeIndex],
                   _Phys_aBodyOwners[ownerIndex].mType, (BigObjHitter_t *)pPlayer);
    }
}

void PhysSetObjectPosition(BigObj_t *pOwner, float *pPos)
{
    BigObjFlags_t *pFlags = pOwner->mUnknown476;
    if (pFlags) {
        RigidBody *pBody = _Phys_apObjectBodies[pFlags->mUnknown20];
        if (pBody->mState) SetBodyPosition(pBody, (Vec3_801DE1E0 *)pPos);
    }
}
void PhysPushObjects(FieldPoint_t *pCenter, float radius)
{
    for (unsigned int i = 0; i < (unsigned int)_Phys_iObjectCount; i++) {
        RigidBody *pBody = _Phys_apObjectBodies[i];
        if (!pBody || ((PhysBodyOwner_t *)pBody->mpOwner)->mKind != 3) continue;
        Vec3_801DE1E0 *pPos = &pBody->mPosition;
        Vector_80039F5C position;
        Vector_80039F5C from;
        from.mX = pPos->x;
        from.mY = pPos->y;
        from.mZ = pPos->z;
        position.mX = from.mX;
        position.mY = from.mY;
        position.mZ = from.mZ;
        if (ScrmIsFieldFlipped()) { from.mX = -from.mX; from.mY = -from.mY; }
        FieldPoint_t offset;
        Vec2Sub(&offset, &from, pCenter);
        float length = Vec2Magnitude(&offset);
        if (!(length >= radius)) {
            if (!(length > 0.001f)) { offset.mY = radius; offset.mX = 0.0f; }
            else Vec2Scale(&offset, &offset, radius / length);
            Vec2Add(&position, pCenter, &offset);
            if (ScrmIsFieldFlipped()) { position.mX = -position.mX; position.mY = -position.mY; }
            if (pBody->mState) SetBodyPosition(pBody, (Vec3_801DE1E0 *)&position);
        }
    }
}
}
