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
#include "game/fn_802270D4.h"
#include "game/fn_801FCE10.h"

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

extern "C" void fn_8003977C(int team)
{
    unsigned char i;

    for (i = 0; i < 7; i++) {
        fn_80039F5C(team, i)->mFlags &= ~0x40000;
    }
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
        unsigned char count = pRecord->mUnknown2F;

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
            break;
        default:
            count = (unsigned char)(p->mUnknown528.mUnknown15 - 15) <= 1 ? 11 : 9;
            break;
        }
        pRecord->mUnknown2F = count;
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
                fn_80227930(pSub, &pSub->mUnknown10, &pSub->mUnknown20, 0.5f);
                break;
            }
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
