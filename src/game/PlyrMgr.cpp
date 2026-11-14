/* Player manager: creates the on-field players and saves, restores and
   checksums them with the save state, runs their per-frame motion, pose and
   animation passes, collision contacts and rumble, queued messages and
   control flags, finds players by team, id, role or distance, shows their
   play routes and updates their collision capsules. */
#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/PlyrSlot.h"
#include "game/Message_800F01CC.h"
#include "game/Collide.h"
#include "game/fn_80178D18.h"
#include "game/fn_8022781C.h"
#include "game/LevelSurface.h"
#include "game/fn_800AD9B4.h"
#include "game/Object_8017886C.h"
#include "game/Object_8003DEC4.h"
#include "game/LightTracker.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/fn_802270D4.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/PreSnapPhase.h"
#include "game/PlaySet.h"
#include "game/PlayBookGetPlay.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80227638.h"

/* Block that +4 of the manager points to (28 bytes). */
struct PlyrMgrCollideSet_t {
    void *mpUnknown0;
    int mUnknown4;
    char mUnknown8[4];
    int mUnknown12;
    char mUnknown16[4];
    void *mpUnknown20[2];
};

/* The player manager that _PlyrMgr_pManager points to (12 bytes). */
struct PlyrMgr_t {
    PlyrSlot_t *mpPlayers;
    PlyrMgrCollideSet_t *mpUnknown4;
    unsigned short mPerTeam;
    unsigned short mCount;
};

/* Local view of the block that +4 of a player points to. */
struct PlyrModelView_t {
    char mUnknown0[20];
    unsigned int mFlags;
    char mUnknown24[4];
    float mUnknown28;
    int mUnknown32;
    char mUnknown36[80];
    char mUnknown116[868];
    void *mpUnknown984;
    unsigned char *mpUnknown988;
};

/* Saved-state view of one 5336-byte player slot, as PlyrMgrLoadSnapshot restores
   it: whole-block copies and 124-byte entries restored through
   fn_801BA784. Bytes 0-1031 are not restored. */
struct PlyrSaveWords12_t {
    int mWords[3];
};

struct PlyrSaveWords196_t {
    int mWords[49];
};

struct PlyrSaveWords212_t {
    int mWords[53];
};

struct PlyrSaveWords404_t {
    int mWords[101];
};

struct PlyrSaveAnimEntry_t {
    char mUnknown0[124];
};

struct PlyrSaveView_t {
    char mUnknown0[1032];
    PlyrSaveWords212_t mUnknown1032;
    PlyrSaveWords12_t mUnknown1244;
    PlyrSaveAnimEntry_t mUnknown1256[10];
    PlyrSaveWords404_t mUnknown2496;
    PlyrSaveWords196_t mUnknown2900;
    PlyrSaveWords12_t mUnknown3096;
    PlyrSaveAnimEntry_t mUnknown3108[4];
    PlyrSaveWords404_t mUnknown3604;
    PlyrSaveWords12_t mUnknown4008[2];
    PlyrSaveAnimEntry_t mUnknown4032[2][2];
    PlyrSaveWords404_t mUnknown4528[2];
};

extern "C" {
extern PlyrMgr_t *_PlyrMgr_pManager;

Point_8017886C fn_80177FFC(int team);
int fn_800A7FD8(void);
int fn_801486A0(void);
int fn_80178320(void);
int fn_801784C4(void);
int fn_80178508(Vector_80039F5C *pPos, float *pOut, int a);
float fn_80178A08(void);
float fn_80178A44(void);
void PlyrRouteShow(int a, int team, int index);
void PlyrAnimUpdateOverlay(Object_80039F5C *p, PlyrModelView_t *pBlock, float f);
void PlyrAnimUpdateHands(Object_80039F5C *p, PlyrModelView_t *pBlock, float f);
void PlyrAnimPostUpdate(Object_80039F5C *p, PlyrModelView_t *pBlock);
void PlyrClampBehindLine(Object_80039F5C *p);
void PlyrKeepInBounds(Object_80039F5C *p);
void PlyrPoseBlendEntries(void *pBlock, int a);
void PlyrPoseBlendRootAngles(void *pBlock, void *a, unsigned short b, void *c);
void fn_800B2B90(Object_800B26B0 *pMotion);
void fn_800C3404(Object_80039F5C *p);
void fn_800C8270(Object_80039F5C *p);
void fn_800C82C0(Object_80039F5C *p);
void fn_800CE674(Object_800CE674 *p);
void fn_800CE684(Object_800CE674 *p);
void fn_800D782C(Object_80039F5C *p);
void PlyrCollideClearExempt(Object_80039F5C *p);
void fn_8015C244(void *p);
void PlyrMoveUpdate(Object_80039F5C *p, float f);
void fn_8016F780(void);
int fn_801BCA74(void *a, void *b, int c, void *d, int e, int f);
int fn_801BCCAC(void *a, void *b, int c, void *d, int e, int f);
unsigned short fn_801BE648(void *p);

void PlyrPoseBlendRawEntries(void *pBlock, int a, unsigned int index);
void PlyrPoseSetBlend(void *pBlock, int a);
int fn_800ADD7C(void *pElements, unsigned int index);
int fn_800ADEFC(void *pElements, unsigned int index);
void fn_800B2BC0(Object_800B26B0 *pMotion);
void fn_8009BEA8(Object_80039F5C *p);
int fn_800F0770(int a, State_80039F5C *pQueue, int which, int value, Object_80039F5C *p);
void PlyrMoveCmdReverse(PlyrMoveCmd_t *pObject);
void AnimInitHeader(void *p, int a, int b, int c);
void fn_801B9FEC(void *p, void *q);
void fn_801BA03C(void *a, void *b, float f, Object_80039F5C *p);
int fn_801BC7C0(void *a, void *b, void *c);
void fn_801BCEEC(void *a, void *b);
void fn_801BE040(void *p);
void fn_801BE420(void *a, void *b, void *c, Object_80039F5C *p, float f);

void PlyrClearPendingMsg(Object_80039F5C *p, int a);
CollideSet_t *PlyrMgrGetCollideSet(void);
void PlyrPoseSetFromModel(Object_80039F5C *p);
void PlyrPoseUpdate(void *p);
void fn_8008E978(Object_80039F5C *p);
void fn_8009C370(Object_80039F5C *p);
void fn_8009CDEC(Object_80039F5C *p);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009D00C(void *p, int *pRecord);
int fn_8011E8A4(void);
void fn_8011E8D8(Object_80039F5C *p);
CollideSet_t *StatcollGetSet(void);
}

extern "C" {
int CharSkelGetJointByName(void *p, const char *pName);
void fn_800ADB90(Object_80039F5C *p, int a, int b, int c);
void ParticlesAddPlayerEvent(int type, int a, int b, int c);
void PlyrInit(Object_80039F5C *p, PlyrSlot_t *pPlayer, unsigned char team, unsigned char index);
void fn_800EFE1C(int a, State_80039F5C *pQueue);
void fn_8009C158(Object_80039F5C *p, int a);
void PlyrInitAnimChannels(Object_80039F5C *p);
int fn_80178308(void);
Object_8003DEC4 *fn_8003DEE4(int value);
void fn_8009CF30(void *pDst, AnimPose_t *pPose);
extern unsigned char _PlyrMgr_aCapsuleBonePairs[11][2];
void PlyrCollideResetBlock(Block_80170374 *pBlock);
void fn_801D04C4(void);
void fn_801D06D4(void *p);
void fn_801D0544(void);
void fn_80227930(void *pOut, void *pA, void *pB, float t);
float fn_8022785C(void *pA, void *pB);
void fn_80227CC0(void *pOut, void *pIn);
void fn_80227264(void *pOut, void *pIn, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
extern unsigned char _PlyrMgr_uRumbleMax, _PlyrMgr_uRumbleBase, _PlyrMgr_uRumbleDuration;
extern float _PlyrMgr_fRumbleScale;
void PlyrCollideMotion(Object_80039F5C *pA, Object_80039F5C *pB);
void PlyrCollideContacts(Object_80039F5C *pA, CollideObject_t *pRecordA, Object_80039F5C *pB, CollideObject_t *pRecordB,
                 CollideContactList_t *pContacts);
void RumbleStart(int channel, int level, int duration);
int fn_8003DEBC(void);
void fn_8009BC38(Object_80039F5C *p, Object_8003DEC4 *pObject);
void fn_8009BD48(int *pRef, int a, int b, int c);
void PlyrMoveCmdClear(PlyrMoveCmd_t *pObject);
void fn_800AF804(void *p);
void SortListAdd(Object_8003DEC4 *pObject, short a, unsigned short b, int index);
int fn_8009C328(Object_80039F5C *pA, Object_80039F5C *pB);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);
int fn_800ABDA4(int team);
void *fn_8023816C(void *pHandle);
int PlyrMgrCompareSnapshot(PlyrMgr_t *pA, PlyrMgr_t *pB);
int PlyrMgrSaveSnapshot(PlyrMgr_t *pManager, char *pBuffer);
int PlyrMgrLoadSnapshot(PlyrMgr_t *pManager, char *pBuffer);
void fn_801BA784(void *pDest, void *pSrc);
void fn_8009C0B8(void *pDest, void *pSrc);
int fn_8016278C(void);
Object_80039F5C *fn_80163064(void);
int PassIconsAreShown(void);
int PassIconsAreLocked(void);
int PassIconGetSlot(int index, int force);
int fn_800B65A0(int team);
int fn_801787A0(void);
void fn_800F1700(void);
void fn_800C11B8(void);
void fn_800C845C(void);
void PlayerMoveTickAll(void);
void fn_800C8330(Object_80039F5C *p);
void fn_800C7794(Object_80039F5C *p);
void fn_800EA6F0(Object_80039F5C *p);
void fn_800C89BC(Object_80039F5C *p);
void fn_800EFFA0(int a, State_80039F5C *pQueue, Object_80039F5C *p, int flag);
void fn_800A5E68(Object_80039F5C *p);
void PlyrUpdateControlFlag(Object_80039F5C *p, int flag);
void fn_800C7D44(Object_80039F5C *p);
void fn_8011E13C(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
void *fn_800AEE20(Object_80039F5C *p);
void *fn_8015C170(Object_80039F5C *p, Point_8017886C *pPos, void *pRecord, unsigned char flag);
void fn_8015C218(void *p);
}

#if defined(DECOMP_COMPARE)
extern "C" void PlyrFixWristBones(Object_80039F5C *p)
{
    if (p->mFlags & 0x04000000) {
        Object_8003DEC4 *pObject = (Object_8003DEC4 *)p->mpUnknown4;
        int bone;

        bone = CharSkelGetJointByName(pObject->mUnknown100, "rwrist");
        pObject->mUnknown44.mUnknown48[bone * 3] = pObject->mUnknown100->mUnknown1040[bone][0] << 4;
        pObject->mUnknown44.mUnknown48[bone * 3 + 2] = pObject->mUnknown100->mUnknown1040[bone][2] << 4;
        bone = CharSkelGetJointByName(pObject->mUnknown100, "rforearm");
        pObject->mUnknown44.mUnknown48[bone * 3 + 1] = pObject->mUnknown100->mUnknown1040[bone][1] << 4;
        bone = CharSkelGetJointByName(pObject->mUnknown100, "lwrist");
        pObject->mUnknown44.mUnknown48[bone * 3] = pObject->mUnknown100->mUnknown1040[bone][0] << 4;
        pObject->mUnknown44.mUnknown48[bone * 3 + 2] = pObject->mUnknown100->mUnknown1040[bone][2] << 4;
        bone = CharSkelGetJointByName(pObject->mUnknown100, "lforearm");
        pObject->mUnknown44.mUnknown48[bone * 3 + 1] = pObject->mUnknown100->mUnknown1040[bone][1] << 4;
        fn_800ADB90(p, 0, 8, 1);
        fn_800ADB90(p, 0, 8, 0);
    }
}

extern "C" void PlyrAddParticleEvents(Object_80039F5C *p)
{
    float (*pMatrix)[4][4] = &((Object_8003DEC4 *)p->mpUnknown4)->mUnknown908;

    ParticlesAddPlayerEvent(0, (int)pMatrix, (int)p, 8);
    ParticlesAddPlayerEvent(0, (int)pMatrix, (int)p, 4);
    ParticlesAddPlayerEvent(2, (int)pMatrix, (int)p, 10);
    ParticlesAddPlayerEvent(1, (int)pMatrix, (int)p, 13);
}

extern "C" int PlyrMgrCreate(PlyrMgr_t *pManager)
{
    int i;

    pManager->mpPlayers = (PlyrSlot_t *)fn_801D2B7C(pManager->mCount * sizeof(PlyrSlot_t), 0, 0);
    memset(pManager->mpPlayers, 0, pManager->mCount * sizeof(PlyrSlot_t));
    pManager->mpUnknown4 = (PlyrMgrCollideSet_t *)CollideSetCreate(pManager->mCount, pManager->mCount * 11);
    for (i = 0; i < pManager->mCount; i++) {
        PlyrSlot_t *pPlayers = pManager->mpPlayers;
        Object_80039F5C *p = &pPlayers[i].mObject;

        PlyrInitAnimChannels(p);
        PlyrInit(p, &pPlayers[i], i / pManager->mPerTeam, i % pManager->mPerTeam);
        fn_800EFE1C(0, &p->mQueue[0]);
        PlyrClearPendingMsg(p, 0);
        p->mpUnknown3092 = (Object_800EA284 *)CollideSetAddObject((CollideSet_t *)pManager->mpUnknown4, 0,
                                                          pPlayers[i].mObject.mId);
        PlyrAddParticleEvents(p);
    }
    return 0;
}

extern "C" int PlyrMgrDestroy(PlyrMgr_t *pManager)
{
    unsigned short i;

    for (i = 0; i < pManager->mCount; i++) {
        Object_80039F5C *p = &pManager->mpPlayers[i].mObject;
        p->mpUnknown3092 = 0;
    }
    CollideSetDestroy((CollideSet_t *)pManager->mpUnknown4);
    fn_801D2BD0(pManager->mpPlayers);
    pManager->mpPlayers = 0;
    return 0;
}

extern "C" int PlyrMgrRefreshAll(PlyrMgr_t *pManager, int flags)
{
    unsigned int i;

    for (i = 0; i < pManager->mCount; i++) {
        PlyrSlot_t *pPlayer = &pManager->mpPlayers[i];
        Object_80039F5C *p = &pPlayer->mObject;

        if (flags & 1) {
            fn_8009C158(p, 1);
        } else {
            Object_8003DEC4 *pObject = (Object_8003DEC4 *)p->mpUnknown4;

            if (pObject != 0) {
                unsigned int j;

                for (j = 0; j <= 1; j++) {
                    if (pObject->mUnknown20 & 32) {
                        PlyrPoseBlendRawEntries(pObject, fn_801BC7C0(&pPlayer->mUnknown4008[j], pPlayer->mUnknown4032[j],
                                                         pPlayer->mUnknown4528[j]), j);
                    } else {
                        PlyrPoseBlendRawEntries(pObject, fn_800ADEFC(pObject->mUnknown116, j), j);
                    }
                }
                fn_8009C370(p);
                PlyrPoseSetFromModel(p);
                LightTrackerSnap(&((Object_8003DEC4 *)p->mpUnknown4)->mUnknown4960,
                            (LightSource_t *)pObject->mUnknown972);
            }
        }
    }
    return 0;
}

extern "C" int PlyrMgrCompareSnapshot(PlyrMgr_t *pA, PlyrMgr_t *pB)
{
    int result;
    int i;
    Object_80039F5C *a;
    Object_80039F5C *b;

    if (pB != 0) {
        result = pA->mCount != pB->mCount;
        result |= pA->mPerTeam != pB->mPerTeam;
        for (i = 0; i < pA->mCount; i++) {
            a = (Object_80039F5C *)((char *)&pA->mpPlayers[i] + ((char *)pA - (char *)_PlyrMgr_pManager));
            b = (Object_80039F5C *)((char *)&pB->mpPlayers[i] + ((char *)pB - (char *)_PlyrMgr_pManager));

            result |= fn_8009C328(a, b);
            result |= CollideCompareObjects((CollideObject_t *)((char *)a->mpUnknown3092 + ((char *)pA - (char *)_PlyrMgr_pManager)),
                                  (CollideObject_t *)((char *)b->mpUnknown3092 + ((char *)pB - (char *)_PlyrMgr_pManager)),
                                  (CollideObject_t *)a->mpUnknown3092);
            result |= fn_80238258(&a->mBlock1032, &b->mBlock1032, 0x80C);
        }
    } else {
        int value;

        result = fn_80238278(pA, sizeof(PlyrMgr_t), 0);
        for (i = 0; i < pA->mCount; i++) {
            a = (Object_80039F5C *)((char *)&pA->mpPlayers[i] + ((char *)pA - (char *)_PlyrMgr_pManager));

            result = fn_80238278(&a->mUnknown2900, 0xC0, result);
        }
        value = fn_800ABDA4(0);
        result = fn_80238278(&value, sizeof(value), result);
        value = fn_800ABDA4(1);
        result = fn_80238278(&value, sizeof(value), result);
    }
    return result;
}

// FAKEMATCH: memcpy called through a cast stays an ordinary call instead of the builtin copy
#define PLYRMGR_COPY ((void *(*)(void *, const void *, int))memcpy)

extern "C" int PlyrMgrSaveSnapshot(PlyrMgr_t *pManager, char *pBuffer)
{
    PlyrMgrCollideSet_t *pBlock;
    short i;

    PLYRMGR_COPY(pBuffer, pManager, sizeof(PlyrMgr_t));
    pBuffer += sizeof(PlyrMgr_t);
    PLYRMGR_COPY(pBuffer, pManager->mpPlayers, pManager->mCount * sizeof(PlyrSlot_t));
    pBuffer += pManager->mCount * sizeof(PlyrSlot_t);
    pBlock = pManager->mpUnknown4;
    PLYRMGR_COPY(pBuffer, pBlock, sizeof(PlyrMgrCollideSet_t));
    pBuffer += sizeof(PlyrMgrCollideSet_t);
    PLYRMGR_COPY(pBuffer, pBlock->mpUnknown0, pBlock->mUnknown4 * 48);
    pBuffer += pBlock->mUnknown4 * 48;
    for (i = 0; i <= 1; i++) {
        PLYRMGR_COPY(pBuffer, pBlock->mpUnknown20[i], pBlock->mUnknown12 * 48);
        pBuffer += pBlock->mUnknown12 * 48;
    }
    return 1;
}

extern "C" int PlyrMgrLoadSnapshot(PlyrMgr_t *pManager, char *pBuffer)
{
    PlyrSaveView_t *pDst;
    PlyrSaveView_t *pSrc;
    char *pData;
    short i;

    *pManager = *(PlyrMgr_t *)pBuffer;
    pDst = (PlyrSaveView_t *)pManager->mpPlayers;
    pSrc = (PlyrSaveView_t *)(pBuffer + sizeof(PlyrMgr_t));
    for (i = 0; i < pManager->mCount; i++) {
        short j;
        short k;

        pDst->mUnknown1244 = pSrc->mUnknown1244;
        pDst->mUnknown2496 = pSrc->mUnknown2496;
        for (j = 0; j <= 9; j++) {
            fn_801BA784(&pDst->mUnknown1256[j], &pSrc->mUnknown1256[j]);
        }
        pDst->mUnknown3096 = pSrc->mUnknown3096;
        pDst->mUnknown3604 = pSrc->mUnknown3604;
        for (j = 0; j <= 3; j++) {
            fn_801BA784(&pDst->mUnknown3108[j], &pSrc->mUnknown3108[j]);
        }
        for (k = 0; k <= 1; k++) {
            pDst->mUnknown4008[k] = pSrc->mUnknown4008[k];
            pDst->mUnknown4528[k] = pSrc->mUnknown4528[k];
            for (j = 0; j <= 1; j++) {
                fn_801BA784(&pDst->mUnknown4032[k][j], &pSrc->mUnknown4032[k][j]);
            }
        }
        pDst->mUnknown1032 = pSrc->mUnknown1032;
        pDst->mUnknown2900 = pSrc->mUnknown2900;
        fn_8009C0B8(pDst, pSrc);
        pDst++;
        pSrc++;
    }
    pData = (char *)pSrc + sizeof(PlyrMgrCollideSet_t);
    memcpy(pManager->mpUnknown4->mpUnknown0, pData, pManager->mpUnknown4->mUnknown4 * 48);
    pData += pManager->mpUnknown4->mUnknown4 * 48;
    for (i = 0; i <= 1; i++) {
        memcpy(pManager->mpUnknown4->mpUnknown20[i], pData, pManager->mpUnknown4->mUnknown12 * 48);
        pData += pManager->mpUnknown4->mUnknown12 * 48;
    }
    return 1;
}

extern "C" int PlyrMgrGetSnapshotSize(void)
{
    return sizeof(PlyrMgr_t) + _PlyrMgr_pManager->mCount * sizeof(PlyrSlot_t)
        + sizeof(PlyrMgrCollideSet_t) + _PlyrMgr_pManager->mpUnknown4->mUnknown4 * 48
        + _PlyrMgr_pManager->mpUnknown4->mUnknown12 * 48 * 2;
}

extern "C" void PlyrInit(Object_80039F5C *p, PlyrSlot_t *pPlayer, unsigned char team, unsigned char index)
{
    Object_8003DEC4 *pObject = fn_8003DF3C(team, index);
    Object_800CE674 *pReset = &pPlayer->mObject.mUnknown1240;

    fn_8009BC38(p, pObject);
    PlyrMoveCmdClear(&p->mUnknown512);
    PlyrMoveCmdClear(&p->mUnknown528);
    fn_8009BD48(&p->mId, 1, team, index);
    p->mUnknown9[0] = 1;
    p->mUnknown8 = 0xFF;
    p->mFlags = 16;
    p->mUnknown9[2] = index < (unsigned int)fn_80178D70(team);
    p->mpState = &pPlayer->mObject.mQueue[0];
    p->mpUnknown792 = pPlayer->mObject.mUnknown1244 + 1252;
    p->mpUnknown796 = (AnimHeader_t *)pPlayer->mObject.mUnknown1244;
    p->mpUnknown800 = (Record_800D81C8 *)(pPlayer->mObject.mUnknown1244 + 12);
    p->mpUnknown804 = pPlayer->mUnknown3604;
    p->mpUnknown808 = &pPlayer->mUnknown3096;
    p->mpUnknown812 = pPlayer->mUnknown3108;
    fn_800AF804(p->mUnknown816);
    p->mUnknown512.mUnknown14 = 1;
    p->mpUnknown56 = &pObject->mUnknown44;
    p->mpUnknown148 = &pObject->mUnknown44;
    p->mpUnknown240 = &pObject->mUnknown44;
    p->mMotion.mPos.mX = 11 - index * 2;
    p->mMotion.mPos.mY = team * 10 - 5;
    p->mMotion.mPos.mZ = 0.0f;
    p->mUnknown508 = 170.0f;
    p->mUnknown512.mUnknown8 = 0;
    p->mUnknown512.mUnknown4 = 0;
    p->mUnknown512.mUnknown0 = 0.0f;
    fn_800C8270(&pPlayer->mObject);
    fn_800C82C0(&pPlayer->mObject);
    fn_800CE674(pReset);
    fn_800CE684(pReset);
    PlyrCollideClearExempt(p);
    SortListAdd(pObject, 1, team * fn_8003DEBC() + index, 2);
}

extern "C" void PlyrContactCallback(CollideObject_t *pA, CollideObject_t *pB, CollideContactList_t *pContacts)
{
    Object_80039F5C *a = fn_8009BCE8(&pA->mUnknown28);
    Object_80039F5C *b = fn_8009BCE8(&pB->mUnknown28);

    if (a->mFlags & 16) {
        return;
    }
    if (b->mFlags & 16) {
        return;
    }
    if (pContacts == 0) {
        PlyrCollideMotion(a, b);
    } else {
        PlyrCollideContacts(a, pA, b, pB, pContacts);
    }
    if (a->mUnknown560.mUnknown28 > 1e-7f || b->mUnknown560.mUnknown28 > 1e-7f) {
        AudmonEventPostArgs(35, &a->mMotion.mPos, (int)a, (int)b, 0);
        if (a->mUnknown8 != 0xFF) {
            unsigned int limit = _PlyrMgr_uRumbleMax;
            unsigned int level = (unsigned int)(_PlyrMgr_fRumbleScale * a->mUnknown560.mUnknown28 + _PlyrMgr_uRumbleBase);

            if (level > limit) {
                level = limit;
            }
            RumbleStart(a->mUnknown8, (unsigned char)level, _PlyrMgr_uRumbleDuration);
        }
        if (b->mUnknown8 != 0xFF) {
            unsigned int limit = _PlyrMgr_uRumbleMax;
            unsigned int level = (unsigned int)(_PlyrMgr_fRumbleScale * b->mUnknown560.mUnknown28 + _PlyrMgr_uRumbleBase);

            if (level > limit) {
                level = limit;
            }
            RumbleStart(b->mUnknown8, (unsigned char)level, _PlyrMgr_uRumbleDuration);
        }
    }
}

extern "C" void PlyrUpdatePendingMsg(Object_80039F5C *p)
{
    if (p->mUnknown3044[0] != 0) {
        if (--p->mUnknown3040 <= 0) {
            p->mUnknown3040 = 0;
            if (fn_8011E8A4() != 0) {
                fn_8011E8D8(p);
                fn_800F053C(0, p->mQueue, (Message_800F01CC *)p->mUnknown3044, p);
                if (p->mQueue[0].mId == (unsigned char)p->mUnknown3044[0]) {
                    PlyrClearPendingMsg(p, p->mQueue[0].mId);
                }
            }
        }
    }
}

extern "C" void PlyrAnimUpdateOverlay(Object_80039F5C *p, PlyrModelView_t *pBlock, float f)
{
    PlyrSlot_t *pPlayer = (PlyrSlot_t *)p;

    fn_801BE420(pPlayer->mUnknown3604, &pPlayer->mUnknown3096, pPlayer->mUnknown3108, p, f);
    fn_801BA03C(&pPlayer->mUnknown3096, pPlayer->mUnknown3108, f, p);
    PlyrPoseSetBlend(pBlock, fn_801BC7C0(&pPlayer->mUnknown3096, pPlayer->mUnknown3108, pPlayer->mUnknown3604));
}

extern "C" void PlyrAnimUpdateHands(Object_80039F5C *p, PlyrModelView_t *pBlock, float f)
{
    PlyrSlot_t *pPlayer = (PlyrSlot_t *)p;
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        if (pBlock->mFlags & 32) {
            fn_801BE420(pPlayer->mUnknown4528[i], &pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i], p, f);
            fn_801BA03C(&pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i], f, p);
            PlyrPoseBlendRawEntries(pBlock, fn_801BC7C0(&pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i], pPlayer->mUnknown4528[i]), i);
        } else if (fn_800ADD7C(pBlock->mUnknown116, i) != 0) {
            PlyrPoseBlendRawEntries(pBlock, fn_800ADEFC(pBlock->mUnknown116, i), i);
        }
    }
}

extern "C" void PlyrAnimPostUpdate(Object_80039F5C *p, PlyrModelView_t *pBlock)
{
}

extern "C" void PlyrClampBehindLine(Object_80039F5C *p)
{
    if (fn_800AD9B4() == 2 && fn_801486A0() != 0 && fn_800A7FD8() == 0) {
        int team = fn_80178320();
        if (team == p->mIdBytes[2]) {
            float limit = fn_80177FFC(team).mY + 0.15625f + 1.1f;
            if (p->mMotion.mPos.mY < limit) {
                p->mMotion.mPos.mY = limit;
            }
        }
    }
}

extern "C" void PlyrKeepInBounds(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();

    if (p->mUnknown9[2] != 0
        && ((mode == 3 && fn_800A7FD8() == 0) || fn_801486A0() == 0 || fn_801486A0() == 1)
        && fn_80178508(&p->mMotion.mPos, 0, 0) > 2) {
        if (++p->mUnknown3090 > 299) {
            if (p->mMotion.mPos.mX >= fn_80178A08()) {
                p->mMotion.mPos.mX = fn_80178A08() - 1.0f;
            }
            if (p->mMotion.mPos.mX <= -fn_80178A08()) {
                p->mMotion.mPos.mX = 1.0f - fn_80178A08();
            }
            if (p->mMotion.mPos.mY >= fn_80178A44()) {
                p->mMotion.mPos.mY = fn_80178A44() - 1.0f;
            }
            if (p->mMotion.mPos.mY <= -fn_80178A44()) {
                p->mMotion.mPos.mY = 1.0f - fn_80178A44();
            }
        }
    } else {
        p->mUnknown3090 = 0;
    }
}

extern "C" void PlyrUpdateControlFlag(Object_80039F5C *p, int flag)
{
    unsigned char *pState = ((PlyrModelView_t *)p->mpUnknown4)->mpUnknown988;
    unsigned char value = 0;

    if ((flag != 0 && fn_8016278C() != 0) || p == fn_80163064()) {
        value = 1;
    }
    pState[28] = value;
    if (flag == 0 && (lbl_803EABA4->fn_800C0420(0) || lbl_803EABA4->fn_800C0420(1))
        && (fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF) && fn_8016278C() == 1
        && (((PlyrModelView_t *)p->mpUnknown4)->mFlags & 1) && PassIconsAreShown() && fn_80178308() == p->mIdBytes[2]) {
        unsigned char i;

        for (i = 0; i <= 2; i++) {
            int pad = PassIconGetSlot(i, 1);

            if (pad == 0xFF && PassIconsAreLocked() == 0) {
                continue;
            }
            if (pad == p->mIdBytes[1]) {
                pState[28] = 1;
                break;
            }
        }
        if (p->mUnknown2914 == 0) {
            pState[28] = 1;
        }
    }
}

extern "C" void PlyrMgrClearTeamFlag(int team)
{
    unsigned char i;

    for (i = 0; i < 7; i++) {
        PlyrGet(team, i)->mFlags &= ~0x40000;
    }
}

extern "C" void PlyrMgrRegister(unsigned int count)
{
    void *pHandle;
    PlyrMgr_t *pManager;

    CollideSetPairCallback(0, 0, PlyrContactCallback);
    pHandle = fn_80238174(0, (void **)&_PlyrMgr_pManager, sizeof(PlyrMgr_t), 1, 0x706C7972);
    fn_80238234(pHandle, (Callback_80238234)PlyrMgrCreate, (Callback_80238234)PlyrMgrDestroy,
                (Callback_80238234)PlyrMgrRefreshAll, (Callback1C_80238234)PlyrMgrCompareSnapshot);
    fn_80238248(pHandle, (Callback28_80238248)PlyrMgrSaveSnapshot, (Callback24_80238248)PlyrMgrGetSnapshotSize,
                (Callback20_80238248)PlyrMgrLoadSnapshot);
    pManager = (PlyrMgr_t *)fn_8023816C(pHandle);
    pManager->mCount = count;
    pManager->mPerTeam = count >> 1;
    fn_802381E0(pHandle);
}

extern "C" void PlyrMgrReset(void)
{
    _PlyrMgr_pManager = 0;
}

extern "C" int PlyrMgrExists(void)
{
    if (_PlyrMgr_pManager != 0) {
        return 1;
    }
    return 0;
}

extern "C" void PlyrMgrUpdate(void)
{
    int count = _PlyrMgr_pManager->mCount;
    int replay = fn_801787A0();
    int team = fn_80178320();
    int i;

    fn_800F1700();
    fn_800C11B8();
    fn_800C845C();
    PlayerMoveTickAll();
    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        int active;

        if (p->mFlags & 0x800) {
            if (p->mFlags & 0x08000000) {
                AudmonEventPostId(36, &p->mMotion.mPos, p->mId, 0, 0, 0);
                p->mFlags &= ~0x08000000;
            }
        } else if (!(p->mFlags & 0x08000000)) {
            p->mFlags |= 0x08000000;
        }
        active = 0;
        if (p->mUnknown8 != 0xFF) {
            active = 1;
        }
        if (replay == 0 && p->mIdBytes[2] == team && fn_801486A0() != 1) {
            fn_800C8330(p);
            fn_800C7794(p);
        }
        if (replay == 0) {
            fn_800EA6F0(p);
        }
        fn_800C89BC(p);
        fn_800EFFA0(0, &p->mQueue[0], p, active);
        fn_800A5E68(p);
        PlyrUpdatePendingMsg(p);
        PlyrUpdateControlFlag(p, active);
    }
    fn_800C7D44(BallGetCurrentHolder());
    fn_8011E13C();
}

extern "C" void PlyrMgrEmptyPass(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
    }
}

extern "C" void PlyrMgrUpdateSkeletons(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        void *pBlock = p->mpUnknown4;
        fn_8009CDEC(p);
        PlyrFixWristBones(p);
        PlyrPoseUpdate(pBlock);
    }
}

extern "C" void PlyrMgrStepStates(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        fn_8009CE88(p, &p->mUnknown108, 6);
        fn_8009CE88(p, &p->mUnknown200, 6);
        fn_8009CE88(p, &p->mUnknown16, 6);
    }
}

extern "C" void PlyrMgrUpdateMotion(float dt)
{
    int i;
    int count;
    Object_80039F5C *p;

    fn_8016F780();
    count = _PlyrMgr_pManager->mCount;
    for (i = 0; i < count; i++) {
        p = &_PlyrMgr_pManager->mpPlayers[i].mObject;

        PlyrMoveUpdate(p, dt);
        PlyrClampBehindLine(p);
        PlyrKeepInBounds(p);
        fn_800B2B90(&p->mMotion);
        fn_800C3404(p);
        fn_800D782C(p);
    }
    for (i = 0; i < count; i++) {
    }
    for (i = 0; i < count; i++) {
        p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        Vector_80039F5C pos;

        fn_8009BEA8(p);
        if (fn_801784C4()) {
            pos.mX = -p->mMotion.mPos.mX;
            pos.mY = -p->mMotion.mPos.mY;
            pos.mZ = p->mMotion.mPos.mZ;
        } else {
            pos = p->mMotion.mPos;
        }
        p->mpUnknown780 = LevelFindArea(&pos.mX);
    }
}

extern "C" void PlyrMgrTestCollisions(void)
{
    CollideSet_t *pSet = (CollideSet_t *)_PlyrMgr_pManager->mpUnknown4;
    CollideSetTest(pSet, pSet);
    CollideSetTest(PlyrMgrGetCollideSet(), StatcollGetSet());
}

extern "C" void PlyrMgrRunBrains(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
        fn_8008E978(&_PlyrMgr_pManager->mpPlayers[i].mObject);
    }
}

extern "C" void PlyrMgrUpdatePoses(float dt)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;
    Object_80039F5C *p;
    PlyrModelView_t *pBlock;

    for (i = 0; i < count; i++) {
        p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        pBlock = (PlyrModelView_t *)p->mpUnknown4;

        if (pBlock->mFlags & 0x10) {
            PlyrAnimUpdateOverlay(p, pBlock, dt);
        }
        PlyrAnimUpdateHands(p, pBlock, dt);
    }
    for (i = 0; i < count; i++) {
        p = &_PlyrMgr_pManager->mpPlayers[i].mObject;

        fn_801BE420(p->mUnknown1244 + 1252, p->mUnknown1244, p->mUnknown1244 + 12, p, dt);
    }
    for (i = 0; i < count; i++) {
        p = &_PlyrMgr_pManager->mpPlayers[i].mObject;

        fn_801BA03C(p->mUnknown1244, p->mUnknown1244 + 12, dt, p);
    }
    for (i = 0; i < count; i++) {
        p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        pBlock = (PlyrModelView_t *)p->mpUnknown4;
        int texture;

        pBlock->mUnknown28 = p->mUnknown772;
        pBlock->mUnknown32 = p->mUnknown776;
        texture = fn_801BC7C0(p->mUnknown1244, p->mUnknown1244 + 12, p->mUnknown1244 + 1252);
        PlyrPoseBlendEntries(pBlock, texture);
        p->mUnknown544 = fn_801BCA74(p->mUnknown1244, p->mUnknown1244 + 12, texture, &p->mUnknown548,
                                     fn_801BE648(p->mpUnknown792), (p->mFlags & 0x200) == 0);
        p->mUnknown545 = fn_801BCCAC(p->mUnknown1244, p->mUnknown1244 + 12, texture, p->mUnknown552,
                                     fn_801BE648(p->mpUnknown792), (p->mFlags & 0x200) == 0);
        PlyrPoseBlendRootAngles(pBlock, p->mUnknown1244 + 12, *(unsigned short *)(p->mUnknown1244 + 4), p->mUnknown1244 + 1252);
        PlyrAnimPostUpdate(p, pBlock);
    }
}

extern "C" void PlyrMgrUpdateModels(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
        PlyrPoseSetFromModel(&_PlyrMgr_pManager->mpPlayers[i].mObject);
    }
}

extern "C" Object_80039F5C *PlyrGet(int team, unsigned short index)
{
    PlyrMgr_t *pManager = _PlyrMgr_pManager;

    Object_80039F5C *p = 0;

    if (pManager != 0) {
        p = &pManager->mpPlayers[team * pManager->mPerTeam + index].mObject;
    }
    return p;
}

extern "C" int PlyrGetIndex(Object_80039F5C *p)
{
    int count = _PlyrMgr_pManager->mCount;
    int i;

    for (i = 0; i < count; i++) {
        if (p == &_PlyrMgr_pManager->mpPlayers[i].mObject) {
            break;
        }
    }
    if (i >= count) {
        i = -1;
    }
    return i;
}

extern "C" Object_80039F5C *PlyrFindByRole(int team, int a, unsigned char n)
{
    unsigned int count = fn_80178D18(team);
    Object_80039F5C *pResult = 0;
    unsigned short i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        if (p->mUnknown2914 == a) {
            if (n == 0) {
                pResult = p;
                break;
            }
            n--;
        }
    }
    return pResult;
}

extern "C" int PlyrMgrGetPerTeam(void)
{
    return _PlyrMgr_pManager->mPerTeam;
}

extern "C" CollideSet_t *PlyrMgrGetCollideSet(void)
{
    if (_PlyrMgr_pManager == 0) {
        return 0;
    }
    return (CollideSet_t *)_PlyrMgr_pManager->mpUnknown4;
}

extern "C" void PlyrMgrReverseAll(void)
{
    unsigned short i;

    for (i = 0; i < _PlyrMgr_pManager->mCount; i++) {
        PlyrSlot_t *pPlayer = &_PlyrMgr_pManager->mpPlayers[i];
        Object_80039F5C *p = &pPlayer->mObject;
        fn_800B2BC0(&p->mMotion);
        fn_801BCEEC(p->mUnknown1244, p->mUnknown1244 + 12);
        fn_800F0770(0, p->mQueue, 4, 1, p);
        PlyrMoveCmdReverse(&p->mUnknown528);
        PlyrMoveCmdReverse(&p->mUnknown512);
        fn_8009BEA8(p);
    }
}

extern "C" Object_80039F5C *PlyrFindNearest(Vector_80039F5C *pPos, float *pOut, int team)
{
    Object_80039F5C *pBest = 0;
    float best = 10000.0f;
    unsigned short i;

    for (i = 0; i < _PlyrMgr_pManager->mCount; i++) {
        Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        if (((p->mId >> 8) & 0xFF) == (unsigned char)team) {
            float d = fn_8022781C(&p->mMotion.mPos, pPos);
            if (d < best) {
                pBest = p;
                best = d;
            }
        }
    }
    if (pOut != 0) {
        *pOut = best;
    }
    return pBest;
}

extern "C" void PlyrRouteShow(int on, int team, int index)
{
    Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[index + team * _PlyrMgr_pManager->mPerTeam].mObject;
    PlyrModelView_t *pBlock = (PlyrModelView_t *)p->mpUnknown4;

    if (on != 0) {
        if (pBlock->mpUnknown984 == 0) {
            PlayBookFormation_t *pPlay = PlayBookGetFormation((unsigned char)team);
            PlayBookPosition_t *pEntry = (PlayBookPosition_t *)PlaySetGetEntry(pPlay, (unsigned char)index, 0);
            Point_8017886C offset;
            Point_8017886C pos;
            unsigned char flip;
            void *pRecord;

            offset = fn_80177FE0();
            if (fn_80178308() == ((p->mId >> 8) & 0xFF)) {
                pos.mX = (pPlay->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
                pos.mY = (pPlay->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
                fn_80227638(&pos, &pos, &offset);
            } else {
                pos.mX = p->mMotion.mPos.mX;
                pos.mY = p->mMotion.mPos.mY;
            }
            flip = pPlay->mUnknown8.mUnknownF;
            pRecord = fn_800AEE20(p);
            if (pRecord == 0) {
                int entry;

                if (flip) {
                    entry = PlaySetGetEntry(PlayBookGetFormation((unsigned char)team), (unsigned char)index, 0)->mUnknownB;
                } else {
                    entry = index;
                }
                pRecord = fn_80164EC8(PlayBookGetPlay((unsigned char)team), (unsigned char)team, entry);
            } else {
                flip = 0;
            }
            pBlock->mpUnknown984 = fn_8015C170(p, &pos, pRecord, flip);
        }
    } else if (pBlock->mpUnknown984 != 0) {
        fn_8015C218(pBlock->mpUnknown984);
        pBlock->mpUnknown984 = 0;
    }
}

#endif

extern "C" void PlyrRouteShowHighlighted(int a, int team, int index)
{
    Object_80039F5C *p;
    PlyrModelView_t *pBlock;

    PlyrRouteShow(a, team, index);
    p = &_PlyrMgr_pManager->mpPlayers[index + team * _PlyrMgr_pManager->mPerTeam].mObject;
    pBlock = (PlyrModelView_t *)p->mpUnknown4;
    if (pBlock->mpUnknown984 != 0) {
        fn_8015C244(pBlock->mpUnknown984);
    }
}

extern "C" void PlyrRouteShowTeam(int a, int team)
{
    int i;
    int count = _PlyrMgr_pManager->mPerTeam;

    for (i = 0; i < count; i++) {
        PlyrRouteShow(a, team, i);
    }
}

extern "C" void PlyrMgrClearStates(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        fn_8009D00C(p, &p->mUnknown108);
        fn_8009D00C(p, &p->mUnknown200);
        fn_8009D00C(p, &p->mUnknown16);
        p->mFlags &= ~0x04000000;
        p->mFlags &= ~0x00800000;
        p->mFlags &= ~0x00200000;
        p->mFlags &= ~0x00080000;
        p->mFlags &= ~0x0003F800;
    }
}

extern "C" void PlyrMgrResetAll(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        p->mFlags &= ~0x80000000;
        p->mFlags &= ~0x10000000;
        p->mFlags &= ~0x04000000;
        p->mFlags &= ~0x00E00000;
        p->mFlags &= ~0x00080000;
        p->mFlags &= ~0x0003F800;
        p->mFlags &= ~0x0000001C;
        fn_8009D00C(p, &p->mUnknown108);
        fn_8009D00C(p, &p->mUnknown200);
        fn_8009D00C(p, &p->mUnknown16);
        PlyrCollideClearExempt(p);
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        p->mUnknown772 = 1.0f;
        fn_800C8270(p);
        fn_800C82C0(p);
    }
}

extern "C" void PlyrMgrSetLeadFlags(void)
{
    PlyrMgr_t *pManager = _PlyrMgr_pManager;
    ((PlyrModelView_t *)pManager->mpPlayers[0].mObject.mpUnknown4)->mFlags |= 0x4000;
    ((PlyrModelView_t *)pManager->mpPlayers[pManager->mCount / 2].mObject.mpUnknown4)->mFlags |= 0x4000;
}

extern "C" void PlyrMgrClearLeadFlags(void)
{
    PlyrMgr_t *pManager = _PlyrMgr_pManager;
    ((PlyrModelView_t *)pManager->mpPlayers[0].mObject.mpUnknown4)->mFlags &= ~0x4000;
    ((PlyrModelView_t *)pManager->mpPlayers[pManager->mCount / 2].mObject.mpUnknown4)->mFlags &= ~0x4000;
}

extern "C" void PlyrUpdateCollRecord(CollideObject_t *pRecord)
{
    Object_80039F5C *p = fn_8009BCE8(&pRecord->mUnknown28);
    Object_8003DEC4 *pObject = (Object_8003DEC4 *)p->mpUnknown4;
    float radius;
    unsigned char i;
    CollideShape_t *pSub;
    CollideShape_t *pOther;

    PlyrCollideResetBlock(&p->mUnknown560);
    pRecord->mUnknown0 = p->mMotion.mPos.mX;
    pRecord->mUnknown4 = p->mMotion.mPos.mY;
    pRecord->mUnknown8 = p->mMotion.mPos.mZ + 1.0f;
    pRecord->mUnknown10 = p->mMotion.mPos.mZ;
    pRecord->mUnknown14 = p->mMotion.mPos.mZ + 6.0f;
    fn_801D04C4();
    fn_801D06D4(p->mUnknown640);
    radius = 0.0f;
    int mode = fn_800AD9B4();
    if ((pRecord->mUnknown2C & 2) && (mode == 2 || mode == 6 || mode == 7) && !(p->mFlags & 0x4000)) {
        pSub = pRecord->mpUnknown20;
        pRecord->mUnknown2F = 1;
        pOther = pRecord->mpUnknown24;
        pSub->mUnknown10 = p->mMotion.mPos.mX;
        pSub->mUnknown14 = p->mMotion.mPos.mY;
        pSub->mUnknown18 = p->mMotion.mPos.mZ;
        pSub->mUnknown20 = pSub->mUnknown10;
        pSub->mUnknown24 = pSub->mUnknown14;
        pSub->mUnknown28 = pSub->mUnknown18;
        pSub->mUnknown28 = p->mMotion.mPos.mZ + 1.5f;
        fn_80227930(pSub, &pSub->mUnknown10, &pSub->mUnknown20, 0.5f);
        pSub->mUnknownC = fn_8022785C(pSub, &pSub->mUnknown10) + pSub->mUnknown1C;
        pOther->mUnknownC = pSub->mUnknownC;
    } else {
        int single = pRecord->mUnknown2F == 1;

        switch (fn_801BE648(p->mpUnknown792)) {
        case 0x25:
        case 0x2B:
        case 0x30:
        case 0x43:
        case 0x44:
        case 0x46:
        case 0x5D:
        case 0x5E:
        case 0x5F:
        case 0x60:
        case 0xA4:
        case 0xAC:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xB0:
        case 0xB5:
        case 0xBA:
        case 0xC0:
        case 0xCF:
        case 0xE1:
        case 0xE3:
        case 0xEA:
            pRecord->mUnknown2F = 11;
            break;
        default:
            if ((unsigned char)(p->mUnknown528.mUnknown15 - 15) <= 1) {
                pRecord->mUnknown2F = 11;
            } else {
                pRecord->mUnknown2F = 9;
            }
            break;
        }
        for (i = 0; i < pRecord->mUnknown2F; i++) {
            float (*pMatrices)[4][4] = pObject->mUnknown112;
            Vector_80039F5C a;
            Vector_80039F5C b;
            float d;
            float e;
            float (*pA)[4];
            float (*pB)[4];

            pSub = &pRecord->mpUnknown20[i];
            pA = pMatrices[_PlyrMgr_aCapsuleBonePairs[i][0]];
            pB = pMatrices[_PlyrMgr_aCapsuleBonePairs[i][1]];
            a.mX = pA[0][3];
            a.mY = pA[1][3];
            a.mZ = pA[2][3];
            b.mX = pB[0][3];
            b.mY = pB[1][3];
            b.mZ = pB[2][3];
            fn_80227CC0(&pSub->mUnknown10, &a);
            fn_80227CC0(&pSub->mUnknown20, &b);
            d = fabsf(pSub->mUnknown10 - pRecord->mUnknown0);
            if (d < radius) {
                d = radius;
            }
            radius = d;
            e = fabsf(pSub->mUnknown20 - pRecord->mUnknown0);
            if (e < radius) {
                e = radius;
            }
            radius = e;
            switch (i) {
            case 0:
                if (single) {
                    pSub->mUnknownC = fn_8022785C(pSub, &pSub->mUnknown10) + pSub->mUnknown1C;
                    pOther = pRecord->mpUnknown24;
                    pOther->mUnknownC = pSub->mUnknownC;
                }
                break;
            case 9:
            case 10:
                fn_802276B4(&a, &pSub->mUnknown20, &pSub->mUnknown10);
                fn_80227264(&a, &a, 2.15f);
                fn_8022765C(&pSub->mUnknown10, &a, &pSub->mUnknown10);
                break;
            }
            fn_80227930(pSub, &pSub->mUnknown10, &pSub->mUnknown20, 0.5f);
        }
    }
    fn_801D0544();
    pRecord->mUnknown18 = radius;
    if (!(pRecord->mUnknown2C & 2)) {
        for (i = 0; i <= 10; i++) {
            pSub = &pRecord->mpUnknown20[i];
            pOther = &pRecord->mpUnknown24[i];

            switch (i) {
            case 0:
                pSub->mUnknown1C = 0.2f;
                break;
            case 1:
                pSub->mUnknown1C = 0.1f;
                break;
            case 2:
                pSub->mUnknown1C = 0.06f;
                break;
            case 3:
                pSub->mUnknown1C = 0.1f;
                break;
            case 4:
                pSub->mUnknown1C = 0.06f;
                break;
            case 5:
                pSub->mUnknown1C = 0.1f;
                break;
            case 6:
                pSub->mUnknown1C = 0.1f;
                break;
            case 7:
                pSub->mUnknown1C = 0.1f;
                break;
            case 8:
                pSub->mUnknown1C = 0.1f;
                break;
            case 9:
                pSub->mUnknown1C = 0.11f;
                break;
            case 10:
                pSub->mUnknown1C = 0.11f;
                break;
            }
            pOther->mUnknown1C = pSub->mUnknown1C;
            pSub->mUnknownC = fn_8022785C(pSub, &pSub->mUnknown10) + pSub->mUnknown1C;
            pOther->mUnknownC = pSub->mUnknownC;
        }
        pRecord->mUnknown2C |= 2;
    }
}

extern "C" void PlyrClearPendingMsg(Object_80039F5C *p, int a)
{
    if (a == 0 || (unsigned char)p->mUnknown3044[0] == a) {
        p->mUnknown3044[0] = 0;
    }
}

extern "C" void PlyrSetPendingMsg(Object_80039F5C *p, Message_800F01CC *pMessage, int value)
{
    *(Message_800F01CC *)p->mUnknown3044 = *pMessage;
    p->mUnknown3040 = value;
}

extern "C" unsigned char *PlyrGetPendingMsg(Object_80039F5C *p)
{
    return (unsigned char *)p->mUnknown3044;
}

extern "C" void PlyrInitAnimChannels(Object_80039F5C *p)
{
    PlyrSlot_t *pPlayer = (PlyrSlot_t *)p;
    unsigned int i;

    AnimInitHeader(p->mUnknown1244, 0, 1, 10);
    fn_801B9FEC(p->mUnknown1244, p->mUnknown1244 + 12);
    fn_801BE040(p->mUnknown1244 + 1252);
    AnimInitHeader(&pPlayer->mUnknown3096, 2, 3, 4);
    fn_801B9FEC(&pPlayer->mUnknown3096, pPlayer->mUnknown3108);
    fn_801BE040(pPlayer->mUnknown3604);
    for (i = 0; i <= 1; i++) {
        AnimInitHeader(&pPlayer->mUnknown4008[i], 0, 4, 2);
        fn_801B9FEC(&pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i]);
        fn_801BE040(pPlayer->mUnknown4528[i]);
    }
}

extern "C" void PlyrMgrRefreshModels(void)
{
    int i;
    int count = _PlyrMgr_pManager->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &_PlyrMgr_pManager->mpPlayers[i].mObject;
        PlyrModelView_t *pBlock = (PlyrModelView_t *)p->mpUnknown4;
        fn_8009C370(p);
        PlyrPoseSetFromModel(p);
        pBlock->mFlags |= 1;
    }
}

extern "C" Object_80039F5C *PlyrFindById(int id)
{
    Object_80039F5C *pResult = 0;
    int team = fn_80178308();
    unsigned int i;

    for (i = 0; i < 7; i++) {
        Object_80039F5C *p = PlyrGet((unsigned char)team, i);
        if (id == p->mUnknown2908) {
            pResult = p;
            break;
        }
    }
    if (pResult == 0) {
        team = fn_80178320();
        for (i = 0; i < 7; i++) {
            Object_80039F5C *p = PlyrGet((unsigned char)team, i);
            if (id == p->mUnknown2908) {
                pResult = p;
                break;
            }
        }
    }
    return pResult;
}

extern "C" Object_80039F5C *PlyrFindByPoid(int id)
{
    Object_80039F5C *pResult = 0;
    int value;
    int status;
    int code = 0;

    status = fn_801FCE10(0, "use 'EMAG' select 'DIGP' into \x85 from 'YALP' where 'DIOP' = \x82\n", &value, id);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status != 23) {
        Object_8003DEC4 *pObject = fn_8003DEE4(value);
        if (pObject != 0) {
            int team = fn_80178308();
            unsigned int i;

            for (i = 0; i < 7; i++) {
                Object_80039F5C *p = PlyrGet((unsigned char)team, i);
                if (p != 0 && p->mpUnknown4 == (Block_80170E64 *)pObject) {
                    pResult = p;
                    break;
                }
            }
            if (pResult == 0) {
                team = fn_80178320();
                for (i = 0; i < 7; i++) {
                    Object_80039F5C *p = PlyrGet((unsigned char)team, i);
                    if (p != 0 && p->mpUnknown4 == (Block_80170E64 *)pObject) {
                        pResult = p;
                        break;
                    }
                }
            }
        }
    }
    return pResult;
}

extern "C" void PlyrAttachModel(Object_80039F5C *p)
{
    Object_8003DEC4 *pObject = fn_8003DEE4(p->mUnknown2908);

    if (pObject == 0) {
        pObject = fn_8003DEC4((p->mId >> 8 & 0xFF) * 7 + (p->mId >> 16 & 0xFF));
    }
    p->mpUnknown4 = (Block_80170E64 *)pObject;
    fn_8009CF30(&p->mUnknown16, &pObject->mUnknown44);
    fn_8009CF30(&p->mUnknown108, &pObject->mUnknown44);
    fn_8009CF30(&p->mUnknown200, &pObject->mUnknown44);
}
