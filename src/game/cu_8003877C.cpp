#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_8003EC04.h"
#include "game/fn_80178D18.h"
#include "game/fn_8022781C.h"
#include "game/fn_80054138.h"
#include "game/fn_800AD9B4.h"
#include "game/Object_8017886C.h"
#include "game/Object_8003DEC4.h"
#include "game/cu_801442FC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_802270D4.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/Class_80297CE8.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80227638.h"

/* Player slot of the array that lbl_803EA3F8 points to: the shared player
   object followed by bytes not declared there, padded to the 5336-byte
   stride used by every walk of the array. */
struct Player_8003877C {
    Object_80039F5C mObject;
    char mUnknown3096[12];
    char mUnknown3108[496];
    char mUnknown3604[404];
    char mUnknown4008[2][12];
    char mUnknown4032[2][248];
    char mUnknown4528[2][404];
};

/* Block that +4 of the manager points to (28 bytes). */
struct Block_8003877C {
    void *mpUnknown0;
    int mUnknown4;
    char mUnknown8[4];
    int mUnknown12;
    char mUnknown16[4];
    void *mpUnknown20[2];
};

/* The player manager that lbl_803EA3F8 points to (12 bytes). */
struct Manager_803EA3F8 {
    Player_8003877C *mpPlayers;
    Block_8003877C *mpUnknown4;
    unsigned short mPerTeam;
    unsigned short mCount;
};

/* Local view of the block that +4 of a player points to. */
struct Block_8003A1EC {
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

/* Saved-state view of one 5336-byte player slot, as fn_80038A00 restores
   it: whole-block copies and 124-byte entries restored through
   fn_801BA784. Bytes 0-1031 are not restored. */
struct Copy12_80038A00 {
    int mWords[3];
};

struct Copy196_80038A00 {
    int mWords[49];
};

struct Copy212_80038A00 {
    int mWords[53];
};

struct Copy404_80038A00 {
    int mWords[101];
};

struct Entry124_80038A00 {
    char mUnknown0[124];
};

struct PlayerView_80038A00 {
    char mUnknown0[1032];
    Copy212_80038A00 mUnknown1032;
    Copy12_80038A00 mUnknown1244;
    Entry124_80038A00 mUnknown1256[10];
    Copy404_80038A00 mUnknown2496;
    Copy196_80038A00 mUnknown2900;
    Copy12_80038A00 mUnknown3096;
    Entry124_80038A00 mUnknown3108[4];
    Copy404_80038A00 mUnknown3604;
    Copy12_80038A00 mUnknown4008[2];
    Entry124_80038A00 mUnknown4032[2][2];
    Copy404_80038A00 mUnknown4528[2];
};

extern "C" {
extern Manager_803EA3F8 *lbl_803EA3F8;

Point_8017886C fn_80177FFC(int team);
int fn_800A7FD8(void);
int fn_801486A0(void);
int fn_80178320(void);
int fn_801784C4(void);
int fn_80178508(Vector_80039F5C *pPos, float *pOut, int a);
float fn_80178A08(void);
float fn_80178A44(void);
void fn_8003A1EC(int a, int team, int index);
void fn_800392DC(Object_80039F5C *p, Block_8003A1EC *pBlock, float f);
void fn_80039364(Object_80039F5C *p, Block_8003A1EC *pBlock, float f);
void fn_80039454(Object_80039F5C *p, Block_8003A1EC *pBlock);
void fn_80039458(Object_80039F5C *p);
void fn_800394F4(Object_80039F5C *p);
void fn_800424C0(void *pBlock, int a);
void fn_800424E8(void *pBlock, void *a, unsigned short b, void *c);
void fn_800B2B90(Object_800B26B0 *pMotion);
void fn_800C3404(Object_80039F5C *p);
void fn_800C8270(Object_80039F5C *p);
void fn_800C82C0(Object_80039F5C *p);
void fn_800CE674(Object_800CE674 *p);
void fn_800CE684(Object_800CE674 *p);
void fn_800D782C(Object_80039F5C *p);
void fn_80143DC4(Object_80039F5C *p);
void fn_8015C244(void *p);
void fn_8016D8F0(Object_80039F5C *p, float f);
void fn_8016F780(void);
int fn_801BCA74(void *a, void *b, int c, void *d, int e, int f);
int fn_801BCCAC(void *a, void *b, int c, void *d, int e, int f);
int fn_801BE648(void *p);

void fn_80042508(void *pBlock, int a, unsigned int index);
void fn_80042530(void *pBlock, int a);
int fn_800ADD7C(void *pElements, unsigned int index);
int fn_800ADEFC(void *pElements, unsigned int index);
void fn_800B2BC0(Object_800B26B0 *pMotion);
void fn_8009BEA8(Object_80039F5C *p);
int fn_800F0770(int a, State_80039F5C *pQueue, int which, int value, Object_80039F5C *p);
void fn_8016D9D0(Object_8016D8B0 *pObject);
void fn_801B9EDC(void *p, int a, int b, int c);
void fn_801B9FEC(void *p, void *q);
void fn_801BA03C(void *a, void *b, float f, Object_80039F5C *p);
int fn_801BC7C0(void *a, void *b, void *c);
void fn_801BCEEC(void *a, void *b);
void fn_801BE040(void *p);
void fn_801BE420(void *a, void *b, void *c, Object_80039F5C *p, float f);

void fn_8003AB08(Object_80039F5C *p, int a);
Set_8003EE6C *fn_8003A078(void);
void fn_80042270(Object_80039F5C *p);
void fn_80042928(void *p);
void fn_8008E978(Object_80039F5C *p);
void fn_8009C370(Object_80039F5C *p);
void fn_8009CDEC(Object_80039F5C *p);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009D00C(void *p, int *pRecord);
int fn_8011E8A4(void);
void fn_8011E8D8(Object_80039F5C *p);
Set_8003EE6C *fn_801442F0(void);
}

extern "C" {
int fn_801C4E98(void *p, const char *pName);
void fn_800ADB90(Object_80039F5C *p, int a, int b, int c);
void fn_80145D64(int type, int a, int b, int c);
void fn_80038E80(Object_80039F5C *p, Player_8003877C *pPlayer, unsigned char team, unsigned char index);
void fn_800EFE1C(int a, State_80039F5C *pQueue);
void fn_8009C158(Object_80039F5C *p, int a);
void fn_8003AB40(Object_80039F5C *p);
int fn_80178308(void);
Object_8003DEC4 *fn_8003DEE4(int value);
void fn_8009CF30(void *pDst, Pose_80041930 *pPose);
extern unsigned char lbl_802CCC94[11][2];
void fn_80143D3C(Block_80170374 *pBlock);
void fn_801D04C4(void);
void fn_801D06D4(void *p);
void fn_801D0544(void);
void fn_80227930(void *pOut, void *pA, void *pB, float t);
float fn_8022785C(void *pA, void *pB);
void fn_80227CC0(void *pOut, void *pIn);
void fn_80227264(void *pOut, void *pIn, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
extern unsigned char lbl_803EA3F0, lbl_803EA3F1, lbl_803EA3F2;
extern float lbl_803EA3F4;
void fn_801437FC(Object_80039F5C *pA, Object_80039F5C *pB);
void fn_801438EC(Object_80039F5C *pA, Record_8003EC04 *pRecordA, Object_80039F5C *pB, Record_8003EC04 *pRecordB,
                 ContactList_8030BD74 *pContacts);
void fn_80194C5C(int channel, int level, int duration);
Object_8003DEC4 *fn_8003DF3C(int side, int index);
int fn_8003DEBC(void);
void fn_8009BC38(Object_80039F5C *p, Object_8003DEC4 *pObject);
void fn_8009BD48(int *pRef, int a, int b, int c);
void fn_8016D8B0(Object_8016D8B0 *pObject);
void fn_800AF804(void *p);
void fn_800C3130(Object_8003DEC4 *pObject, short a, unsigned short b, int index);
int fn_8009C328(Object_80039F5C *pA, Object_80039F5C *pB);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);
int fn_800ABDA4(int team);
void fn_801C1FBC(void *pDest, void *pSrc, unsigned int size);
void *fn_8023816C(void *pHandle);
int fn_8003877C(Manager_803EA3F8 *pA, Manager_803EA3F8 *pB);
int fn_80038928(Manager_803EA3F8 *pManager, char *pBuffer);
int fn_80038A00(Manager_803EA3F8 *pManager, char *pBuffer);
void fn_801BA784(void *pDest, void *pSrc);
void fn_8009C0B8(void *pDest, void *pSrc);
int fn_8016278C(void);
Object_80039F5C *fn_80163064(void);
int fn_801481B0(void);
int fn_801481DC(void);
int fn_80148208(int index, int force);
int fn_800B65A0(int team);
int fn_801787A0(void);
void fn_800F1700(void);
void fn_800C11B8(void);
void fn_800C845C(void);
void fn_800D0A38(void);
void fn_800C8330(Object_80039F5C *p);
void fn_800C7794(Object_80039F5C *p);
void fn_800EA6F0(Object_80039F5C *p);
void fn_800C89BC(Object_80039F5C *p);
void fn_800EFFA0(int a, State_80039F5C *pQueue, Object_80039F5C *p, int flag);
void fn_800A5E68(Object_80039F5C *p);
void fn_8003962C(Object_80039F5C *p, int flag);
void fn_800C7D44(void);
void fn_8011E13C(void);
Object_800670B4 *fn_80168708(int team);
void *fn_800AEE20(Object_80039F5C *p);
void *fn_8015C170(Object_80039F5C *p, Point_8017886C *pPos, void *pRecord, int flag);
void fn_8015C218(void *p);
}

#if defined(DECOMP_COMPARE)
extern "C" void fn_8003830C(Object_80039F5C *p)
{
    if (p->mFlags & 0x04000000) {
        Object_8003DEC4 *pObject = (Object_8003DEC4 *)p->mpUnknown4;
        int bone;

        bone = fn_801C4E98(pObject->mUnknown100, "rwrist");
        pObject->mUnknown44.mUnknown48[bone * 3] = pObject->mUnknown100->mUnknown1040[bone][0] << 4;
        pObject->mUnknown44.mUnknown48[bone * 3 + 2] = pObject->mUnknown100->mUnknown1040[bone][2] << 4;
        bone = fn_801C4E98(pObject->mUnknown100, "rforearm");
        pObject->mUnknown44.mUnknown48[bone * 3 + 1] = pObject->mUnknown100->mUnknown1040[bone][1] << 4;
        bone = fn_801C4E98(pObject->mUnknown100, "lwrist");
        pObject->mUnknown44.mUnknown48[bone * 3] = pObject->mUnknown100->mUnknown1040[bone][0] << 4;
        pObject->mUnknown44.mUnknown48[bone * 3 + 2] = pObject->mUnknown100->mUnknown1040[bone][2] << 4;
        bone = fn_801C4E98(pObject->mUnknown100, "lforearm");
        pObject->mUnknown44.mUnknown48[bone * 3 + 1] = pObject->mUnknown100->mUnknown1040[bone][1] << 4;
        fn_800ADB90(p, 0, 8, 1);
        fn_800ADB90(p, 0, 8, 0);
    }
}

extern "C" void fn_8003845C(Object_80039F5C *p)
{
    float (*pMatrix)[4][4] = &((Object_8003DEC4 *)p->mpUnknown4)->mUnknown908;

    fn_80145D64(0, (int)pMatrix, (int)p, 8);
    fn_80145D64(0, (int)pMatrix, (int)p, 4);
    fn_80145D64(2, (int)pMatrix, (int)p, 10);
    fn_80145D64(1, (int)pMatrix, (int)p, 13);
}

extern "C" int fn_800384DC(Manager_803EA3F8 *pManager)
{
    int i;

    pManager->mpPlayers = (Player_8003877C *)fn_801D2B7C(pManager->mCount * sizeof(Player_8003877C), 0, 0);
    fn_801C1F94(pManager->mpPlayers, 0, pManager->mCount * sizeof(Player_8003877C));
    pManager->mpUnknown4 = (Block_8003877C *)fn_8003EE6C(pManager->mCount, pManager->mCount * 11);
    for (i = 0; i < pManager->mCount; i++) {
        Player_8003877C *pPlayers = pManager->mpPlayers;
        Object_80039F5C *p = &pPlayers[i].mObject;

        fn_8003AB40(p);
        fn_80038E80(p, &pPlayers[i], i / pManager->mPerTeam, i % pManager->mPerTeam);
        fn_800EFE1C(0, &p->mUnknown3048);
        fn_8003AB08(p, 0);
        p->mpUnknown3092 = (Object_800EA284 *)fn_8003EFB8((Set_8003EE6C *)pManager->mpUnknown4, 0,
                                                          pPlayers[i].mObject.mId);
        fn_8003845C(p);
    }
    return 0;
}

extern "C" int fn_800385D4(Manager_803EA3F8 *pManager)
{
    unsigned short i;

    for (i = 0; i < pManager->mCount; i++) {
        Object_80039F5C *p = &pManager->mpPlayers[i].mObject;
        p->mpUnknown3092 = 0;
    }
    fn_8003EF5C((Set_8003EE6C *)pManager->mpUnknown4);
    fn_801D2BD0(pManager->mpPlayers);
    pManager->mpPlayers = 0;
    return 0;
}

extern "C" int fn_80038650(Manager_803EA3F8 *pManager, int flags)
{
    unsigned int i;

    for (i = 0; i < pManager->mCount; i++) {
        Player_8003877C *pPlayer = &pManager->mpPlayers[i];
        Object_80039F5C *p = &pPlayer->mObject;

        if (flags & 1) {
            fn_8009C158(p, 1);
        } else {
            Object_8003DEC4 *pObject = (Object_8003DEC4 *)p->mpUnknown4;

            if (pObject != 0) {
                unsigned int j;

                for (j = 0; j <= 1; j++) {
                    if (pObject->mUnknown20 & 32) {
                        fn_80042508(pObject, fn_801BC7C0(pPlayer->mUnknown4008[j], pPlayer->mUnknown4032[j],
                                                         pPlayer->mUnknown4528[j]), j);
                    } else {
                        fn_80042508(pObject, fn_800ADEFC(pObject->mUnknown116, j), j);
                    }
                }
                fn_8009C370(p);
                fn_80042270(p);
                fn_801444A0((Tracker_801442FC *)((Object_8003DEC4 *)p->mpUnknown4)->mUnknown4960,
                            (Object_80144310 *)pObject->mUnknown972);
            }
        }
    }
    return 0;
}

extern "C" int fn_8003877C(Manager_803EA3F8 *pA, Manager_803EA3F8 *pB)
{
    int result;
    int i;
    Object_80039F5C *a;
    Object_80039F5C *b;

    if (pB != 0) {
        result = pA->mCount != pB->mCount;
        result |= pA->mPerTeam != pB->mPerTeam;
        for (i = 0; i < pA->mCount; i++) {
            a = (Object_80039F5C *)((char *)&pA->mpPlayers[i] + ((char *)pA - (char *)lbl_803EA3F8));
            b = (Object_80039F5C *)((char *)&pB->mpPlayers[i] + ((char *)pB - (char *)lbl_803EA3F8));

            result |= fn_8009C328(a, b);
            result |= fn_8003F4E8((Record_8003EC04 *)((char *)a->mpUnknown3092 + ((char *)pA - (char *)lbl_803EA3F8)),
                                  (Record_8003EC04 *)((char *)b->mpUnknown3092 + ((char *)pB - (char *)lbl_803EA3F8)),
                                  (Record_8003EC04 *)a->mpUnknown3092);
            result |= fn_80238258(&a->mBlock1032, &b->mBlock1032, 0x80C);
        }
    } else {
        int value;

        result = fn_80238278(pA, sizeof(Manager_803EA3F8), 0);
        for (i = 0; i < pA->mCount; i++) {
            a = (Object_80039F5C *)((char *)&pA->mpPlayers[i] + ((char *)pA - (char *)lbl_803EA3F8));

            result = fn_80238278(&a->mUnknown2900, 0xC0, result);
        }
        value = fn_800ABDA4(0);
        result = fn_80238278(&value, sizeof(value), result);
        value = fn_800ABDA4(1);
        result = fn_80238278(&value, sizeof(value), result);
    }
    return result;
}

extern "C" int fn_80038928(Manager_803EA3F8 *pManager, char *pBuffer)
{
    Block_8003877C *pBlock;
    short i;

    fn_801C1FBC(pBuffer, pManager, sizeof(Manager_803EA3F8));
    pBuffer += sizeof(Manager_803EA3F8);
    fn_801C1FBC(pBuffer, pManager->mpPlayers, pManager->mCount * sizeof(Player_8003877C));
    pBuffer += pManager->mCount * sizeof(Player_8003877C);
    pBlock = pManager->mpUnknown4;
    fn_801C1FBC(pBuffer, pBlock, sizeof(Block_8003877C));
    pBuffer += sizeof(Block_8003877C);
    fn_801C1FBC(pBuffer, pBlock->mpUnknown0, pBlock->mUnknown4 * 48);
    pBuffer += pBlock->mUnknown4 * 48;
    for (i = 0; i <= 1; i++) {
        fn_801C1FBC(pBuffer, pBlock->mpUnknown20[i], pBlock->mUnknown12 * 48);
        pBuffer += pBlock->mUnknown12 * 48;
    }
    return 1;
}

extern "C" int fn_80038A00(Manager_803EA3F8 *pManager, char *pBuffer)
{
    PlayerView_80038A00 *pDst;
    PlayerView_80038A00 *pSrc;
    char *pData;
    short i;

    *pManager = *(Manager_803EA3F8 *)pBuffer;
    pDst = (PlayerView_80038A00 *)pManager->mpPlayers;
    pSrc = (PlayerView_80038A00 *)(pBuffer + sizeof(Manager_803EA3F8));
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
    pData = (char *)pSrc + sizeof(Block_8003877C);
    fn_801C1FBC(pManager->mpUnknown4->mpUnknown0, pData, pManager->mpUnknown4->mUnknown4 * 48);
    pData += pManager->mpUnknown4->mUnknown4 * 48;
    for (i = 0; i <= 1; i++) {
        fn_801C1FBC(pManager->mpUnknown4->mpUnknown20[i], pData, pManager->mpUnknown4->mUnknown12 * 48);
        pData += pManager->mpUnknown4->mUnknown12 * 48;
    }
    return 1;
}

extern "C" int fn_80038E50(void)
{
    return sizeof(Manager_803EA3F8) + lbl_803EA3F8->mCount * sizeof(Player_8003877C)
        + sizeof(Block_8003877C) + lbl_803EA3F8->mpUnknown4->mUnknown4 * 48
        + lbl_803EA3F8->mpUnknown4->mUnknown12 * 48 * 2;
}

extern "C" void fn_80038E80(Object_80039F5C *p, Player_8003877C *pPlayer, unsigned char team, unsigned char index)
{
    Object_8003DEC4 *pObject = fn_8003DF3C(team, index);
    Object_800CE674 *pReset = &pPlayer->mObject.mUnknown1240;

    fn_8009BC38(p, pObject);
    fn_8016D8B0(&p->mUnknown512);
    fn_8016D8B0(&p->mUnknown528);
    fn_8009BD48(&p->mId, 1, team, index);
    p->mUnknown9[0] = 1;
    p->mUnknown8 = 0xFF;
    p->mFlags = 16;
    p->mUnknown9[2] = index < (unsigned int)fn_80178D70(team);
    p->mpState = &pPlayer->mObject.mUnknown3048;
    p->mpUnknown792 = pPlayer->mObject.mUnknown1244 + 1252;
    p->mpUnknown796 = (Object_8016D9B8 *)pPlayer->mObject.mUnknown1244;
    p->mpUnknown800 = (Record_800D81C8 *)(pPlayer->mObject.mUnknown1244 + 12);
    p->mpUnknown804 = pPlayer->mUnknown3604;
    p->mpUnknown808 = pPlayer->mUnknown3096;
    p->mpUnknown812 = pPlayer->mUnknown3108;
    fn_800AF804(p->mUnknown816);
    p->mUnknown512.mUnknown14 = 1;
    p->mMotion.mPos.mX = 11 - index * 2;
    p->mMotion.mPos.mY = team * 10 - 5;
    p->mMotion.mPos.mZ = 0.0f;
    p->mUnknown508 = 170.0f;
    p->mUnknown512.mUnknown0 = 0.0f;
    p->mUnknown512.mUnknown4 = 0;
    p->mUnknown512.mUnknown8 = 0;
    p->mpUnknown56 = &pObject->mUnknown44;
    p->mpUnknown148 = &pObject->mUnknown44;
    p->mpUnknown240 = &pObject->mUnknown44;
    fn_800C8270(&pPlayer->mObject);
    fn_800C82C0(&pPlayer->mObject);
    fn_800CE674(pReset);
    fn_800CE684(pReset);
    fn_80143DC4(p);
    fn_800C3130(pObject, 1, team * fn_8003DEBC() + index, 2);
}

extern "C" void fn_80039044(Record_8003EC04 *pA, Record_8003EC04 *pB, ContactList_8030BD74 *pContacts)
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
        fn_801437FC(a, b);
    } else {
        fn_801438EC(a, pA, b, pB, pContacts);
    }
    if (a->mUnknown560.mUnknown28 > 1e-7f || b->mUnknown560.mUnknown28 > 1e-7f) {
        fn_80067DB8(35, &a->mMotion.mPos, (int)a, (int)b, 0);
        if (a->mUnknown8 != 0xFF) {
            unsigned int limit = lbl_803EA3F0;
            unsigned int level = (unsigned int)(lbl_803EA3F4 * a->mUnknown560.mUnknown28 + lbl_803EA3F1);

            if (level > limit) {
                level = limit;
            }
            fn_80194C5C(a->mUnknown8, (unsigned char)level, lbl_803EA3F2);
        }
        if (b->mUnknown8 != 0xFF) {
            unsigned int limit = lbl_803EA3F0;
            unsigned int level = (unsigned int)(lbl_803EA3F4 * b->mUnknown560.mUnknown28 + lbl_803EA3F1);

            if (level > limit) {
                level = limit;
            }
            fn_80194C5C(b->mUnknown8, (unsigned char)level, lbl_803EA3F2);
        }
    }
}

extern "C" void fn_8003924C(Object_80039F5C *p)
{
    if (p->mUnknown3044[0] != 0) {
        if (--p->mUnknown3040 <= 0) {
            p->mUnknown3040 = 0;
            if (fn_8011E8A4() != 0) {
                fn_8011E8D8(p);
                fn_800F053C(0, &p->mUnknown3048, (Message_800F01CC *)p->mUnknown3044, p);
                if (p->mUnknown3048.mId == (unsigned char)p->mUnknown3044[0]) {
                    fn_8003AB08(p, p->mUnknown3048.mId);
                }
            }
        }
    }
}

extern "C" void fn_800392DC(Object_80039F5C *p, Block_8003A1EC *pBlock, float f)
{
    Player_8003877C *pPlayer = (Player_8003877C *)p;

    fn_801BE420(pPlayer->mUnknown3604, pPlayer->mUnknown3096, pPlayer->mUnknown3108, p, f);
    fn_801BA03C(pPlayer->mUnknown3096, pPlayer->mUnknown3108, f, p);
    fn_80042530(pBlock, fn_801BC7C0(pPlayer->mUnknown3096, pPlayer->mUnknown3108, pPlayer->mUnknown3604));
}

extern "C" void fn_80039364(Object_80039F5C *p, Block_8003A1EC *pBlock, float f)
{
    Player_8003877C *pPlayer = (Player_8003877C *)p;
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        if (pBlock->mFlags & 32) {
            fn_801BE420(pPlayer->mUnknown4528[i], pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i], p, f);
            fn_801BA03C(pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i], f, p);
            fn_80042508(pBlock, fn_801BC7C0(pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i], pPlayer->mUnknown4528[i]), i);
        } else if (fn_800ADD7C(pBlock->mUnknown116, i) != 0) {
            fn_80042508(pBlock, fn_800ADEFC(pBlock->mUnknown116, i), i);
        }
    }
}

extern "C" void fn_80039454(Object_80039F5C *p, Block_8003A1EC *pBlock)
{
}

extern "C" void fn_80039458(Object_80039F5C *p)
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

extern "C" void fn_800394F4(Object_80039F5C *p)
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

extern "C" void fn_8003962C(Object_80039F5C *p, int flag)
{
    unsigned char *pState = ((Block_8003A1EC *)p->mpUnknown4)->mpUnknown988;
    unsigned char value = 0;

    if ((flag != 0 && fn_8016278C() != 0) || p == fn_80163064()) {
        value = 1;
    }
    pState[28] = value;
    if (flag == 0 && (lbl_803EABA4->fn_800C0420(0) || lbl_803EABA4->fn_800C0420(1))
        && (fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF) && fn_8016278C() == 1
        && (((Block_8003A1EC *)p->mpUnknown4)->mFlags & 1) && fn_801481B0() && fn_80178308() == p->mIdBytes[2]) {
        unsigned char i;

        for (i = 0; i <= 2; i++) {
            int pad = fn_80148208(i, 1);

            if (pad == 0xFF && fn_801481DC() == 0) {
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

extern "C" void fn_8003977C(int team)
{
    unsigned char i;

    for (i = 0; i < 7; i++) {
        fn_80039F5C(team, i)->mFlags &= ~0x40000;
    }
}

extern "C" void fn_800397D0(unsigned int count)
{
    void *pHandle;
    Manager_803EA3F8 *pManager;

    fn_8003EE2C(0, 0, fn_80039044);
    pHandle = fn_80238174(0, (void **)&lbl_803EA3F8, sizeof(Manager_803EA3F8), 1, 0x706C7972);
    fn_80238234(pHandle, (Callback_80238234)fn_800384DC, (Callback_80238234)fn_800385D4,
                (Callback_80238234)fn_80038650, (Callback1C_80238234)fn_8003877C);
    fn_80238248(pHandle, (Callback28_80238248)fn_80038928, (Callback24_80238248)fn_80038E50,
                (Callback20_80238248)fn_80038A00);
    pManager = (Manager_803EA3F8 *)fn_8023816C(pHandle);
    pManager->mCount = count;
    pManager->mPerTeam = count >> 1;
    fn_802381E0(pHandle);
}

extern "C" void fn_80039890(void)
{
    lbl_803EA3F8 = 0;
}

extern "C" int fn_8003989C(void)
{
    if (lbl_803EA3F8 != 0) {
        return 1;
    }
    return 0;
}

extern "C" void fn_800398B4(void)
{
    int count = lbl_803EA3F8->mCount;
    int replay = fn_801787A0();
    int team = fn_80178320();
    int i;

    fn_800F1700();
    fn_800C11B8();
    fn_800C845C();
    fn_800D0A38();
    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[i].mObject;
        int active;

        if (p->mFlags & 0x800) {
            if (p->mFlags & 0x08000000) {
                fn_80067E3C(36, &p->mMotion.mPos, p->mId, 0, 0, 0);
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
        fn_800EFFA0(0, &p->mUnknown3048, p, active);
        fn_800A5E68(p);
        fn_8003924C(p);
        fn_8003962C(p, active);
    }
    fn_80137B40();
    fn_800C7D44();
    fn_8011E13C();
}

extern "C" void fn_80039A1C(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
    }
}

extern "C" void fn_80039A38(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[i].mObject;
        void *pBlock = p->mpUnknown4;
        fn_8009CDEC(p);
        fn_8003830C(p);
        fn_80042928(pBlock);
    }
}

extern "C" void fn_80039AA8(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[i].mObject;
        fn_8009CE88(p, &p->mUnknown108, 6);
        fn_8009CE88(p, &p->mUnknown200, 6);
        fn_8009CE88(p, &p->mUnknown16, 6);
    }
}

extern "C" void fn_80039B2C(float dt)
{
    int i;
    int count;
    Object_80039F5C *p;

    fn_8016F780();
    count = lbl_803EA3F8->mCount;
    for (i = 0; i < count; i++) {
        p = &lbl_803EA3F8->mpPlayers[i].mObject;

        fn_8016D8F0(p, dt);
        fn_80039458(p);
        fn_800394F4(p);
        fn_800B2B90(&p->mMotion);
        fn_800C3404(p);
        fn_800D782C(p);
    }
    for (i = 0; i < count; i++) {
    }
    for (i = 0; i < count; i++) {
        p = &lbl_803EA3F8->mpPlayers[i].mObject;
        Vector_80039F5C pos;

        fn_8009BEA8(p);
        if (fn_801784C4()) {
            pos.mX = -p->mMotion.mPos.mX;
            pos.mY = -p->mMotion.mPos.mY;
            pos.mZ = p->mMotion.mPos.mZ;
        } else {
            pos = p->mMotion.mPos;
        }
        p->mpUnknown780 = (Record_800C4E18 *)fn_80054138(&pos.mX);
    }
}

extern "C" void fn_80039C64(void)
{
    Set_8003EE6C *pSet = (Set_8003EE6C *)lbl_803EA3F8->mpUnknown4;
    fn_8003F0AC(pSet, pSet);
    fn_8003F0AC(fn_8003A078(), fn_801442F0());
}

extern "C" void fn_80039CB0(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
        fn_8008E978(&lbl_803EA3F8->mpPlayers[i].mObject);
    }
}

extern "C" void fn_80039D08(float dt)
{
    int i;
    int count = lbl_803EA3F8->mCount;
    Object_80039F5C *p;
    Block_8003A1EC *pBlock;

    for (i = 0; i < count; i++) {
        p = &lbl_803EA3F8->mpPlayers[i].mObject;
        pBlock = (Block_8003A1EC *)p->mpUnknown4;

        if (pBlock->mFlags & 0x10) {
            fn_800392DC(p, pBlock, dt);
        }
        fn_80039364(p, pBlock, dt);
    }
    for (i = 0; i < count; i++) {
        p = &lbl_803EA3F8->mpPlayers[i].mObject;

        fn_801BE420(p->mUnknown1244 + 1252, p->mUnknown1244, p->mUnknown1244 + 12, p, dt);
    }
    for (i = 0; i < count; i++) {
        p = &lbl_803EA3F8->mpPlayers[i].mObject;

        fn_801BA03C(p->mUnknown1244, p->mUnknown1244 + 12, dt, p);
    }
    for (i = 0; i < count; i++) {
        p = &lbl_803EA3F8->mpPlayers[i].mObject;
        pBlock = (Block_8003A1EC *)p->mpUnknown4;
        int texture;

        pBlock->mUnknown28 = p->mUnknown772;
        pBlock->mUnknown32 = p->mUnknown776;
        texture = fn_801BC7C0(p->mUnknown1244, p->mUnknown1244 + 12, p->mUnknown1244 + 1252);
        fn_800424C0(pBlock, texture);
        p->mUnknown544 = fn_801BCA74(p->mUnknown1244, p->mUnknown1244 + 12, texture, &p->mUnknown548,
                                     fn_801BE648(p->mpUnknown792), (p->mFlags & 0x200) == 0);
        p->mUnknown545 = fn_801BCCAC(p->mUnknown1244, p->mUnknown1244 + 12, texture, p->mUnknown552,
                                     fn_801BE648(p->mpUnknown792), (p->mFlags & 0x200) == 0);
        fn_800424E8(pBlock, p->mUnknown1244 + 12, *(unsigned short *)(p->mUnknown1244 + 4), p->mUnknown1244 + 1252);
        fn_80039454(p, pBlock);
    }
}

extern "C" void fn_80039F04(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
        fn_80042270(&lbl_803EA3F8->mpPlayers[i].mObject);
    }
}

extern "C" Object_80039F5C *fn_80039F5C(int team, unsigned short index)
{
    Manager_803EA3F8 *pManager = lbl_803EA3F8;

    Object_80039F5C *p = 0;

    if (pManager != 0) {
        p = &pManager->mpPlayers[team * pManager->mPerTeam + index].mObject;
    }
    return p;
}

extern "C" int fn_80039F8C(Object_80039F5C *p)
{
    Manager_803EA3F8 *pManager = lbl_803EA3F8;
    int count = pManager->mCount;
    int i;

    for (i = 0; i < count; i++) {
        if (p == &pManager->mpPlayers[i].mObject) {
            break;
        }
    }
    if (i < count) {
        return i;
    }
    return -1;
}

extern "C" Object_80039F5C *fn_80039FE8(int team, int a, unsigned char n)
{
    unsigned int count = fn_80178D18(team);
    Object_80039F5C *pResult = 0;
    unsigned short i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
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

extern "C" int fn_8003A06C(void)
{
    return lbl_803EA3F8->mPerTeam;
}

extern "C" Set_8003EE6C *fn_8003A078(void)
{
    if (lbl_803EA3F8 == 0) {
        return 0;
    }
    return (Set_8003EE6C *)lbl_803EA3F8->mpUnknown4;
}

extern "C" void fn_8003A090(void)
{
    unsigned short i;

    for (i = 0; i < lbl_803EA3F8->mCount; i++) {
        Player_8003877C *pPlayer = &lbl_803EA3F8->mpPlayers[i];
        Object_80039F5C *p = &pPlayer->mObject;
        fn_800B2BC0(&p->mMotion);
        fn_801BCEEC(p->mUnknown1244, p->mUnknown1244 + 12);
        fn_800F0770(0, &p->mUnknown3048, 4, 1, p);
        fn_8016D9D0(&p->mUnknown528);
        fn_8016D9D0(&p->mUnknown512);
        fn_8009BEA8(p);
    }
}

extern "C" Object_80039F5C *fn_8003A130(Vector_80039F5C *pPos, float *pOut, int team)
{
    Object_80039F5C *pBest = 0;
    float best = 10000.0f;
    unsigned short i;

    for (i = 0; i < lbl_803EA3F8->mCount; i++) {
        Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[i].mObject;
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

extern "C" void fn_8003A1EC(int on, int team, int index)
{
    Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[index + team * lbl_803EA3F8->mPerTeam].mObject;
    Block_8003A1EC *pBlock = (Block_8003A1EC *)p->mpUnknown4;

    if (on != 0) {
        if (pBlock->mpUnknown984 == 0) {
            unsigned char side = team;
            unsigned char slot = index;
            Object_800670B4 *pPlay = fn_80168708(side);
            Entry_8006719C *pEntry = (Entry_8006719C *)fn_80163E94(pPlay, slot, 0);
            Point_8017886C offset = fn_80177FE0();
            Point_8017886C pos;
            unsigned char flip;
            void *pRecord;

            if (fn_80178308() == p->mIdBytes[2]) {
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
                    entry = fn_80163E94(fn_80168708(side), slot, 0)->mUnknownB;
                } else {
                    entry = index;
                }
                pRecord = fn_80164EC8(fn_8016871C(side), side, entry);
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

extern "C" void fn_8003A394(int a, int team, int index)
{
    Block_8003A1EC *pBlock;

    fn_8003A1EC(a, team, index);
    pBlock = (Block_8003A1EC *)(lbl_803EA3F8->mpPlayers + (index + team * lbl_803EA3F8->mPerTeam))->mObject.mpUnknown4;
    if (pBlock->mpUnknown984 != 0) {
        fn_8015C244(pBlock->mpUnknown984);
    }
}

extern "C" void fn_8003A3F4(int a, int team)
{
    int i;
    int count = lbl_803EA3F8->mPerTeam;

    for (i = 0; i < count; i++) {
        fn_8003A1EC(a, team, i);
    }
}

extern "C" void fn_8003A450(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[i].mObject;
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

extern "C" void fn_8003A4DC(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[i].mObject;
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
        fn_80143DC4(p);
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        p->mUnknown772 = 1.0f;
        fn_800C8270(p);
        fn_800C82C0(p);
    }
}

extern "C" void fn_8003A5A8(void)
{
    Manager_803EA3F8 *pManager = lbl_803EA3F8;
    ((Block_8003A1EC *)pManager->mpPlayers[0].mObject.mpUnknown4)->mFlags |= 0x4000;
    ((Block_8003A1EC *)pManager->mpPlayers[pManager->mCount / 2].mObject.mpUnknown4)->mFlags |= 0x4000;
}

extern "C" void fn_8003A5E8(void)
{
    Manager_803EA3F8 *pManager = lbl_803EA3F8;
    ((Block_8003A1EC *)pManager->mpPlayers[0].mObject.mpUnknown4)->mFlags &= ~0x4000;
    ((Block_8003A1EC *)pManager->mpPlayers[pManager->mCount / 2].mObject.mpUnknown4)->mFlags &= ~0x4000;
}

extern "C" void fn_8003A628(Record_8003EC04 *pRecord)
{
    Object_80039F5C *p = fn_8009BCE8(&pRecord->mUnknown28);
    Object_8003DEC4 *pObject = (Object_8003DEC4 *)p->mpUnknown4;
    float radius;
    unsigned char i;

    fn_80143D3C(&p->mUnknown560);
    pRecord->mUnknown0 = p->mMotion.mPos.mX;
    pRecord->mUnknown4 = p->mMotion.mPos.mY;
    pRecord->mUnknown8 = p->mMotion.mPos.mZ + 1.0f;
    pRecord->mUnknown10 = p->mMotion.mPos.mZ;
    pRecord->mUnknown14 = p->mMotion.mPos.mZ + 6.0f;
    fn_801D04C4();
    fn_801D06D4(p->mUnknown628 + 12);
    radius = 0.0f;
    int mode = fn_800AD9B4();
    if ((pRecord->mUnknown2C & 2) && (mode == 2 || mode == 6 || mode == 7) && !(p->mFlags & 0x4000)) {
        Sub_8003EC54 *pSub = pRecord->mpUnknown20;
        Sub_8003EC54 *pOther;

        pRecord->mUnknown2F = 1;
        pOther = pRecord->mpUnknown24;
        pSub->mUnknown10 = p->mMotion.mPos.mX;
        pSub->mUnknown14 = p->mMotion.mPos.mY;
        pSub->mUnknown18 = p->mMotion.mPos.mZ;
        pSub->mUnknown20 = p->mMotion.mPos.mX;
        pSub->mUnknown24 = p->mMotion.mPos.mY;
        pSub->mUnknown28 = p->mMotion.mPos.mZ;
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
            pRecord->mUnknown2F = (unsigned char)(p->mUnknown528.mUnknown15 - 15) <= 1 ? 11 : 9;
            break;
        }
        for (i = 0; i < pRecord->mUnknown2F; i++) {
            float (*pMatrices)[4][4] = pObject->mUnknown112;
            Sub_8003EC54 *pSub = &pRecord->mpUnknown20[i];
            Vector_80039F5C a;
            Vector_80039F5C b;
            float d;

            a.mX = pMatrices[lbl_802CCC94[i][0]][0][3];
            a.mY = pMatrices[lbl_802CCC94[i][0]][1][3];
            a.mZ = pMatrices[lbl_802CCC94[i][0]][2][3];
            b.mX = pMatrices[lbl_802CCC94[i][1]][0][3];
            b.mY = pMatrices[lbl_802CCC94[i][1]][1][3];
            b.mZ = pMatrices[lbl_802CCC94[i][1]][2][3];
            fn_80227CC0(&pSub->mUnknown10, &a);
            fn_80227CC0(&pSub->mUnknown20, &b);
            d = fabsf(pSub->mUnknown10 - pRecord->mUnknown0);
            if (d < radius) {
                d = radius;
            }
            radius = d;
            d = fabsf(pSub->mUnknown20 - pRecord->mUnknown0);
            if (d < radius) {
                d = radius;
            }
            radius = d;
            switch (i) {
            case 0:
                if (single) {
                    pSub->mUnknownC = fn_8022785C(pSub, &pSub->mUnknown10) + pSub->mUnknown1C;
                    pRecord->mpUnknown24->mUnknownC = pSub->mUnknownC;
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
            Sub_8003EC54 *pSub = &pRecord->mpUnknown20[i];
            Sub_8003EC54 *pOther = &pRecord->mpUnknown24[i];

            switch (i) {
            case 0:
                pSub->mUnknown1C = 0.2f;
                break;
            case 1:
            case 3:
            case 5:
            case 6:
            case 7:
            case 8:
                pSub->mUnknown1C = 0.1f;
                break;
            case 2:
            case 4:
                pSub->mUnknown1C = 0.06f;
                break;
            case 9:
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

extern "C" void fn_8003AB08(Object_80039F5C *p, int a)
{
    if (a == 0 || (unsigned char)p->mUnknown3044[0] == a) {
        p->mUnknown3044[0] = 0;
    }
}

extern "C" void fn_8003AB28(Object_80039F5C *p, Message_800F01CC *pMessage, int value)
{
    *(Message_800F01CC *)p->mUnknown3044 = *pMessage;
    p->mUnknown3040 = value;
}

extern "C" unsigned char *fn_8003AB38(Object_80039F5C *p)
{
    return (unsigned char *)p->mUnknown3044;
}

extern "C" void fn_8003AB40(Object_80039F5C *p)
{
    Player_8003877C *pPlayer = (Player_8003877C *)p;
    unsigned int i;

    fn_801B9EDC(p->mUnknown1244, 0, 1, 10);
    fn_801B9FEC(p->mUnknown1244, p->mUnknown1244 + 12);
    fn_801BE040(p->mUnknown1244 + 1252);
    fn_801B9EDC(pPlayer->mUnknown3096, 2, 3, 4);
    fn_801B9FEC(pPlayer->mUnknown3096, pPlayer->mUnknown3108);
    fn_801BE040(pPlayer->mUnknown3604);
    for (i = 0; i <= 1; i++) {
        fn_801B9EDC(pPlayer->mUnknown4008[i], 0, 4, 2);
        fn_801B9FEC(pPlayer->mUnknown4008[i], pPlayer->mUnknown4032[i]);
        fn_801BE040(pPlayer->mUnknown4528[i]);
    }
}

extern "C" void fn_8003AC10(void)
{
    int i;
    int count = lbl_803EA3F8->mCount;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = &lbl_803EA3F8->mpPlayers[i].mObject;
        Block_8003A1EC *pBlock = (Block_8003A1EC *)p->mpUnknown4;
        fn_8009C370(p);
        fn_80042270(p);
        pBlock->mFlags |= 1;
    }
}
#endif

extern "C" Object_80039F5C *fn_8003AC84(int id)
{
    Object_80039F5C *pResult = 0;
    int team = fn_80178308();
    unsigned int i;

    for (i = 0; i < 7; i++) {
        Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
        if (id == p->mUnknown2908) {
            pResult = p;
            break;
        }
    }
    if (pResult == 0) {
        team = fn_80178320();
        for (i = 0; i < 7; i++) {
            Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
            if (id == p->mUnknown2908) {
                pResult = p;
                break;
            }
        }
    }
    return pResult;
}

extern "C" Object_80039F5C *fn_8003AD2C(int id)
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
                Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
                if (p != 0 && p->mpUnknown4 == (Block_80170E64 *)pObject) {
                    pResult = p;
                    break;
                }
            }
            if (pResult == 0) {
                team = fn_80178320();
                for (i = 0; i < 7; i++) {
                    Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
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

extern "C" void fn_8003AE24(Object_80039F5C *p)
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
