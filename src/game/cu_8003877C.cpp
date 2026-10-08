#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_8003EC04.h"
#include "game/fn_80178D18.h"
#include "game/fn_8022781C.h"
#include "game/fn_80054138.h"
#include "game/fn_800AD9B4.h"
#include "game/Object_8017886C.h"

/* Player slot of the array that lbl_803EA3F8 points to: the shared player
   object followed by bytes not declared there, padded to the 5336-byte
   stride used by every walk of the array. */
struct Player_8003877C {
    Object_80039F5C mObject;
    int mUnknown3092;
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

void fn_8003830C(Object_80039F5C *p);
void fn_8003AB08(Object_80039F5C *p, int a);
Set_8003EE6C *fn_8003A078(void);
void fn_80042270(Object_80039F5C *p);
void fn_80042928(void *p);
void fn_8008E978(Object_80039F5C *p);
void fn_8009C370(Object_80039F5C *p);
void fn_8009CDEC(Object_80039F5C *p);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009D00C(Object_80039F5C *p, int *pRecord);
int fn_8011E8A4(void);
void fn_8011E8D8(Object_80039F5C *p);
Set_8003EE6C *fn_801442F0(void);
}

extern "C" int fn_80038E50(void)
{
    return sizeof(Manager_803EA3F8) + lbl_803EA3F8->mCount * sizeof(Player_8003877C)
        + sizeof(Block_8003877C) + lbl_803EA3F8->mpUnknown4->mUnknown4 * 48
        + lbl_803EA3F8->mpUnknown4->mUnknown12 * 48 * 2;
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
        *(float *)p->mUnknown772 = 1.0f;
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
