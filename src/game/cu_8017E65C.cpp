#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"

/* 0x30-byte block allocated by fn_8017EB94 under the id 'ctos'. */
struct State_8017EB94 {
    int mState;
    int mRefs0[3];
    int mRefs1[3];
    char mUnknown28[12];
    signed char mUnknown40;
    signed char mUnknown41;
    signed char mUnknown42;
    signed char mUnknown43;
    signed char mUnknown44;
    unsigned char mUnknown45;
    short mTimer;
};

/* Easing value of src/game/cu_8013CD58.cpp; fn_8013CC7C and fn_8013CD58
   update it. */
struct Interp_8013CC14;

struct Pair_8017E754 {
    float mX;
    float mY;
};

struct Spot_8017E754 {
    Pair_8017E754 mPos;
    float mZ;
};

/* Entry kind 1 of the list that fn_8013F374 reads (fn_8013F090 copies it). */
struct Shot_8013F090 {
    float mUnknown00[3];
    float mUnknown0C[3];
    float mUnknown18[3];
    float mUnknown24;
    float mUnknown28;
    float mUnknown2C[3];
    float mUnknown38[3];
    float mUnknown44[3];
    float mUnknown50;
    float mUnknown54;
    int mUnknown58;
    int mUnknown5C;
    float mUnknown60;
    float mUnknown64;
    float mUnknown68;
    float mUnknown6C;
    float mUnknown70;
    void (*mpUnknown74)(Interp_8013CC14 *pInterp, int steps);
    void (*mpUnknown78)(Interp_8013CC14 *pInterp, int steps);
    void (*mpUnknown7C)(Interp_8013CC14 *pInterp, int steps);
    short mUnknown80;
    short mUnknown82;
    int mUnknown84;
    int mUnknown88;
    int mFlags;
    void (*mpCallback)(void);
};

struct ShotEntry_8013F374 {
    int mKind;
    void *mpData;
};

extern "C" {
void fn_800CC560(int a);
void fn_800FF6D8(Object_80039F5C *p);
void fn_800A3B5C(Object_80039F5C *p);
void fn_80028918(int unknown);
int fn_80027DF0(void);
void fn_8009BD48(int *pRef, int a, int b, int c);
int fn_800B65A0(int unknown);
void fn_8013CC7C(Interp_8013CC14 *pInterp, int steps);
void fn_8013CD58(Interp_8013CC14 *pInterp, int steps);
void fn_8013F374(ShotEntry_8013F374 *pEntries);
void fn_8013F3FC(void);
void fn_80177E6C(int a, int b);
int fn_80178308(void);
int fn_80178320(void);
void fn_8017833C(int value);
int fn_801784C4(void);
void fn_8017CFB4(int a);
void fn_8018A798(int value);
int fn_8018A7A0(void);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8022DDB4(int tag, void *data);
float fn_80237260(int stream);
void *fn_8023816C(void *pHandle);

int fn_8017E65C(int a);
void fn_8017E6F0(void);
void fn_8017E6F4(void);
void fn_8017E6F8(void);
void fn_8017E6FC(void);
void fn_8017E754(unsigned char *pUnused, Spot_8017E754 *pA, Spot_8017E754 *pB);
void fn_8017E92C(void);
int fn_8017E9A4(int mode);
void fn_8017EAC0(Object_80039F5C *p);
void fn_8017EAF4(Object_80039F5C *p);
void fn_8017EB1C(Object_80039F5C *p);
void fn_8017EB58(Object_80039F5C *p);
void fn_8017EB94(void);
void fn_8017EBF0(void);
void fn_8017EBFC(void);
int fn_8017ED6C(void);
void fn_8017EF20(void);
void fn_8017EFB0(void);
void fn_8017EFB4(void);
void fn_8017F048(void);
int fn_8017F0C4(void);
int fn_8017F0FC(void);
int fn_8017F154(void);
int fn_8017F1AC(void);
}

static State_8017EB94 *lbl_803EB498 = 0;
static unsigned char lbl_803EB49C[4] = {4, 0, 1, 2};

static Spot_8017E754 lbl_802E9AF4[3] = {
    {{-3.5f, 3.0f}, 0.0f},
    {{-6.0f, 0.0f}, 0.0f},
    {{-8.0f, -2.0f}, 0.0f},
};

static Spot_8017E754 lbl_802E9B18[3] = {
    {{4.0f, 0.0f}, 0.0f},
    {{3.8f, -1.0f}, 0.0f},
    {{3.7f, -2.0f}, 0.0f},
};

static Spot_8017E754 lbl_802E9B3C[3] = {
    {{-1.2f, 1.0f}, 0.0f},
    {{-1.5f, -0.2f}, 0.0f},
    {{-1.7f, -1.3f}, 0.0f},
};

static Spot_8017E754 lbl_802E9B60[3] = {
    {{1.2f, 1.0f}, 0.0f},
    {{1.5f, -0.2f}, 0.0f},
    {{1.7f, -1.3f}, 0.0f},
};

static Shot_8013F090 lbl_802E9B84 = {
    {0.0f, 0.0f, 0.5f},
    {75.0f, 0.0f, 210.0f},
    {80.0f, 0.0f, 190.0f},
    7.0f,
    5.0f,
    {0.0f, 0.0f, 1.1f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    0.0f,
    0.0f,
    0,
    0,
    40.0f,
    50.0f,
    0.0f,
    350.0f,
    -1.0f,
    fn_8013CD58,
    fn_8013CD58,
    fn_8013CC7C,
    0,
    0,
    0,
    0,
    2,
    fn_8017E6FC,
};

static ShotEntry_8013F374 lbl_802E9C18[2] = {
    {1, &lbl_802E9B84},
    {1, 0},
};

int fn_8017E65C(int a)
{
    int result = 0;

    switch (lbl_803EB498->mUnknown42) {
    case 0:
        break;
    case 3:
        result = 3;
        break;
    case 1:
    case 2:
        if (lbl_803EB498->mUnknown43 == 0) {
            result = 3;
        }
        break;
    }
    if (a == 1) {
        if (lbl_803EB498->mUnknown40 != lbl_803EB498->mUnknown41) {
            result = result == 0 ? 3 : 0;
        }
    } else if (lbl_803EB498->mUnknown40 == lbl_803EB498->mUnknown41) {
        result = result == 0 ? 3 : 0;
    }
    return result;
}

void fn_8017E6F0(void)
{
}

void fn_8017E6F4(void)
{
}

void fn_8017E6F8(void)
{
}

void fn_8017E6FC(void)
{
    fn_800CC560(0);
    fn_8017E754(lbl_803EB49C, lbl_802E9AF4, lbl_802E9B18);
    fn_8017E92C();
    fn_8017E754(lbl_803EB49C, lbl_802E9B3C, lbl_802E9B60);
}

void fn_8017E754(unsigned char *pUnused, Spot_8017E754 *pA, Spot_8017E754 *pB)
{
    unsigned char side;
    unsigned short i;
    Message_800F01CC message;

    for (side = 0; side < 2; side++) {
        int *pRefs = side == 0 ? lbl_803EB498->mRefs0 : lbl_803EB498->mRefs1;
        Spot_8017E754 *pTable = side == 0 ? pA : pB;

        for (i = 0; i < 3; i++) {
            Object_80039F5C *p = fn_8009BCE8(&pRefs[i]);
            Pair_8017E754 dir;
            int angle;

            p->mFlags |= 0x10;
            dir.mX = pTable[i].mPos.mX;
            dir.mY = pTable[i].mPos.mY;
            dir.mX = -dir.mX;
            dir.mY = -dir.mY;
            fn_80227690(&dir, &dir, &pTable[i].mPos);
            angle = fn_801CFE40(dir.mY, dir.mX);

            fn_801C1F94(&message, 0, sizeof(message));
            angle >>= 16;
            message.mUnknown1[0] = (int)(pTable[i].mPos.mX * 4.0f);
            message.mUnknown1[1] = (int)(pTable[i].mPos.mY + pTable[i].mPos.mY);
            message.mId = 0x3F;
            message.mUnknown1[2] = angle;
            fn_800F053C(0, &p->mUnknown3048, &message, p);

            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 6;
            message.mUnknown1[0] = angle;
            fn_800F03D8(0, &p->mUnknown3048, &message, p);

            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 9;
            message.mUnknown1[0] = 0xCB;
            message.mUnknown1[1] = 0;
            message.mUnknown1[2] = 0xFF;
            fn_800F03D8(0, &p->mUnknown3048, &message, p);
        }
    }
}

void fn_8017E92C(void)
{
    unsigned char side;
    unsigned short i;

    for (side = 0; side < 2; side++) {
        int *pRefs = side == 0 ? lbl_803EB498->mRefs0 : lbl_803EB498->mRefs1;

        for (i = 0; i < 3; i++) {
            fn_800FF6D8(fn_8009BCE8(&pRefs[i]));
        }
    }
}

int fn_8017E9A4(int mode)
{
    int result = 0;

    if (lbl_803EB498->mUnknown45 == 0) {
        switch (mode) {
        case 2:
            lbl_803EB498->mUnknown40 = fn_802372EC(0, 2);
            lbl_803EB498->mUnknown41 = fn_802372EC(0, 2);
            lbl_803EB498->mUnknown42 = 1;
            lbl_803EB498->mUnknown43 = fn_802372EC(0, 2);
            break;
        case 0:
            lbl_803EB498->mUnknown40 = 0;
            lbl_803EB498->mUnknown41 = 1;
            lbl_803EB498->mUnknown42 = 1;
            lbl_803EB498->mUnknown43 = fn_802372EC(0, 2);
            break;
        case 1:
            lbl_803EB498->mUnknown40 = 0;
            lbl_803EB498->mUnknown41 = 0;
            lbl_803EB498->mUnknown42 = mode;
            lbl_803EB498->mUnknown43 = fn_802372EC(0, 2);
            break;
        }
        if (fn_800B65A0(fn_80178308()) != 0xFF || fn_800B65A0(fn_80178320()) != 0xFF) {
            fn_8013F3FC();
        }
        lbl_803EB498->mState = 10;
        fn_8017EFB4();
        result = 1;
    }
    return result;
}

void fn_8017EAC0(Object_80039F5C *p)
{
    p->mpUnknown4->mUnknown20 |= 0x10;
    fn_80237260(0);
}

void fn_8017EAF4(Object_80039F5C *p)
{
    if (p != 0) {
        fn_800A3B5C(p);
    }
}

void fn_8017EB1C(Object_80039F5C *p)
{
    Block_80170E64 *pBlock = p->mpUnknown4;

    fn_8017EAC0(p);
    pBlock->mUnknown20 |= 0x400;
}

void fn_8017EB58(Object_80039F5C *p)
{
    Block_80170E64 *pBlock = p->mpUnknown4;

    fn_8017EAF4(p);
    pBlock->mUnknown20 &= ~0x400;
}

void fn_8017EB94(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB498, sizeof(State_8017EB94), 0, 0x63746F73);

    fn_801C1F94(fn_8023816C(pHandle), 0, sizeof(State_8017EB94));
    fn_802381E0(pHandle);
}

void fn_8017EBF0(void)
{
    lbl_803EB498 = 0;
}

void fn_8017EBFC(void)
{
    lbl_803EB498->mState = 1;
    lbl_803EB498->mUnknown40 = -1;
    lbl_803EB498->mUnknown44 = -1;
    lbl_803EB498->mUnknown41 = -1;
    lbl_803EB498->mUnknown42 = -1;
    lbl_803EB498->mUnknown43 = -1;
    lbl_803EB498->mUnknown45 = 0;
    lbl_803EB498->mTimer = -1;
    fn_8009BD48(&lbl_803EB498->mRefs0[0], 1, 0, 0);
    fn_8009BD48(&lbl_803EB498->mRefs1[0], 1, 1, 0);
    fn_8009BD48(&lbl_803EB498->mRefs0[1], 1, 0, 6);
    fn_8009BD48(&lbl_803EB498->mRefs0[2], 1, 0, 7);
    fn_8009BD48(&lbl_803EB498->mRefs1[1], 1, 1, 6);
    fn_8009BD48(&lbl_803EB498->mRefs1[2], 1, 1, 7);
    fn_8017EB1C(fn_8009BCE8(&lbl_803EB498->mRefs0[0]));
    fn_8017EB1C(fn_8009BCE8(&lbl_803EB498->mRefs0[1]));
    fn_8017EB1C(fn_8009BCE8(&lbl_803EB498->mRefs0[2]));
    fn_8017EB1C(fn_8009BCE8(&lbl_803EB498->mRefs1[0]));
    fn_8017EB1C(fn_8009BCE8(&lbl_803EB498->mRefs1[1]));
    fn_8017EB1C(fn_8009BCE8(&lbl_803EB498->mRefs1[2]));
    fn_8017CFB4(7);
    fn_8017E9A4(0);
    lbl_803EB498->mState = 0;
}

int fn_8017ED6C(void)
{
    int result = 1;

    switch (lbl_803EB498->mState) {
    case 1:
        fn_8017EFB0();
        fn_8013F374(lbl_802E9C18);
        fn_8018A798((unsigned char)fn_8017F0C4());
        lbl_803EB498->mState = 2;
        break;
    case 2:
        if (lbl_803EB498->mUnknown40 != -1) {
            lbl_803EB498->mState = 3;
        }
        break;
    case 3:
        fn_8017E6F0();
        lbl_803EB498->mState = 4;
        break;
    case 4:
        lbl_803EB498->mState = 5;
        fn_8018A7A0();
        fn_8018A798((unsigned char)fn_8017F0FC());
        break;
    case 5:
        if (lbl_803EB498->mUnknown42 != -1) {
            lbl_803EB498->mState = 6;
            lbl_803EB498->mTimer = 0;
            fn_8017E6F4();
            fn_8018A7A0();
            fn_8018A798((unsigned char)fn_8017F154());
        }
        break;
    case 6:
        if (lbl_803EB498->mUnknown43 != -1) {
            lbl_803EB498->mState = 9;
            fn_8013F3FC();
            goto finish;
        }
        if (lbl_803EB498->mTimer == 240) {
            fn_8017E6F8();
            lbl_803EB498->mTimer = -1;
        }
        if (lbl_803EB498->mTimer != -1) {
            lbl_803EB498->mTimer++;
        }
        break;
    case 9:
    finish:
        fn_800CC560(0);
        lbl_803EB498->mState = 10;
    case 0:
    case 10:
        lbl_803EB498->mState = 0;
        result = 0;
        fn_8018A7A0();
        break;
    }
    return result;
}

void fn_8017EF20(void)
{
    fn_80028918(0);
    fn_8017EB58(fn_8009BCE8(&lbl_803EB498->mRefs0[0]));
    fn_8017EB58(fn_8009BCE8(&lbl_803EB498->mRefs0[1]));
    fn_8017EB58(fn_8009BCE8(&lbl_803EB498->mRefs0[2]));
    fn_8017EB58(fn_8009BCE8(&lbl_803EB498->mRefs1[0]));
    fn_8017EB58(fn_8009BCE8(&lbl_803EB498->mRefs1[1]));
    fn_8017EB58(fn_8009BCE8(&lbl_803EB498->mRefs1[2]));
    lbl_803EB498->mState = 0;
}

void fn_8017EFB0(void)
{
}

void fn_8017EFB4(void)
{
    int team = fn_8017F1AC();

    fn_8017833C(team);
    if (fn_8017E65C(team) == 0) {
        if (fn_801784C4() != 0) {
            fn_80177E6C(1, 1);
        }
    } else if (fn_801784C4() == 0) {
        fn_80177E6C(1, 1);
    }
    if (fn_80027DF0() == 0) {
        fn_8022DDB4(0x53544347, &lbl_803EB498->mUnknown40);
    }
}

void fn_8017F048(void)
{
    int team = fn_8017F1AC() == 0;

    fn_8017833C(team);
    if (fn_8017E65C(team) == 0) {
        if (fn_801784C4() != 0) {
            fn_80177E6C(1, 1);
        }
    } else if (fn_801784C4() == 0) {
        fn_80177E6C(1, 1);
    }
}

int fn_8017F0C4(void)
{
    int value = fn_800B65A0(1);

    return value == 0xFF ? -1 : value;
}

int fn_8017F0FC(void)
{
    int value;

    if (lbl_803EB498->mUnknown41 == lbl_803EB498->mUnknown40) {
        value = fn_800B65A0(1);
    } else {
        value = fn_800B65A0(0);
    }
    return value == 0xFF ? -1 : value;
}

int fn_8017F154(void)
{
    int value;

    if (lbl_803EB498->mUnknown41 == lbl_803EB498->mUnknown40) {
        value = fn_800B65A0(0);
    } else {
        value = fn_800B65A0(1);
    }
    return value == 0xFF ? -1 : value;
}

int fn_8017F1AC(void)
{
    int result = 0;

    if (lbl_803EB498->mUnknown40 == lbl_803EB498->mUnknown41) {
        switch (lbl_803EB498->mUnknown42) {
        case 1:
            break;
        case 0:
        case 3:
            result = lbl_803EB498->mUnknown43 != 2;
            break;
        case 2:
            result = 1;
            break;
        }
    } else {
        switch (lbl_803EB498->mUnknown42) {
        case 2:
            break;
        case 0:
        case 3:
            result = lbl_803EB498->mUnknown43 == 2;
            break;
        case 1:
            result = 1;
            break;
        }
    }
    return result;
}
