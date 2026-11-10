/* Pre-game coin toss: allocates the 'ctos' state, lines up three players per side through a scripted camera shot, runs the call / result / choice state machine and applies the outcome (offense team and field direction). */
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/fn_800B65A0.h"

/* 0x30-byte block allocated by CoinTossAllocState under the id 'ctos'. */
struct CoinTossState_t {
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

/* Easing value owned by the camera interpolation code. */
struct Interp_8013CC14;

struct CoinTossXY_t {
    float mX;
    float mY;
};

struct CoinTossSpot_t {
    CoinTossXY_t mPos;
    float mZ;
};

/* Entry kind 1 of a scripted camera shot list. */
struct CoinTossCamShot_t {
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

struct CoinTossCamEntry_t {
    int mKind;
    void *mpData;
};

extern "C" {
void fn_800CC560(int a);
void fn_800FF6D8(Object_80039F5C *p);
void fn_800A3B5C(Object_80039F5C *p);
void InGameSetInputPaused(int unknown);
int FELoopIsMainFEActive(void);
void fn_8009BD48(int *pRef, int a, int b, int c);
void fn_8013CC7C(Interp_8013CC14 *pInterp, int steps);
void fn_8013CD58(Interp_8013CC14 *pInterp, int steps);
void fn_8013F374(CoinTossCamEntry_t *pEntries);
void fn_8013F3FC(void);
void fn_80177E6C(int a, int b);
int fn_80178308(void);
int fn_80178320(void);
void fn_8017833C(int value);
int fn_801784C4(void);
void BannerClear(int a);
void UISGameLockPad(int value);
int UISGameUnlockPad(void);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8022DDB4(int tag, void *data);
float fn_80237260(int stream);
void *fn_8023816C(void *pHandle);

int CoinTossGetTeamSide(int a);
void CoinTossOnCallMade(void);
void CoinTossOnChoiceMade(void);
void CoinTossOnChoiceTimeout(void);
void CoinTossPlacePlayers(void);
void CoinTossSendPlayersToSpots(unsigned char *pUnused, CoinTossSpot_t *pA, CoinTossSpot_t *pB);
void CoinTossSnapPlayers(void);
int CoinTossDecide(int mode);
void CoinTossLockPlayer(Object_80039F5C *p);
void CoinTossUnlockPlayer(Object_80039F5C *p);
void CoinTossHoldPlayer(Object_80039F5C *p);
void CoinTossReleasePlayer(Object_80039F5C *p);
void CoinTossAllocState(void);
void CoinTossClearState(void);
void CoinTossStart(void);
int CoinTossUpdate(void);
void CoinTossFinish(void);
void CoinTossOnShotStart(void);
void CoinTossApplyResult(void);
void CoinTossApplyResultSwapped(void);
int CoinTossGetCallerPad(void);
int CoinTossGetWinnerPad(void);
int CoinTossGetLoserPad(void);
int CoinTossGetOffenseTeam(void);
}

static CoinTossState_t *_CoinToss_pState = 0;
static unsigned char _CoinToss_aPlaceArg[4] = {4, 0, 1, 2};

static CoinTossSpot_t _CoinToss_aStartSpotsSide0[3] = {
    {{-3.5f, 3.0f}, 0.0f},
    {{-6.0f, 0.0f}, 0.0f},
    {{-8.0f, -2.0f}, 0.0f},
};

static CoinTossSpot_t _CoinToss_aStartSpotsSide1[3] = {
    {{4.0f, 0.0f}, 0.0f},
    {{3.8f, -1.0f}, 0.0f},
    {{3.7f, -2.0f}, 0.0f},
};

static CoinTossSpot_t _CoinToss_aMeetSpotsSide0[3] = {
    {{-1.2f, 1.0f}, 0.0f},
    {{-1.5f, -0.2f}, 0.0f},
    {{-1.7f, -1.3f}, 0.0f},
};

static CoinTossSpot_t _CoinToss_aMeetSpotsSide1[3] = {
    {{1.2f, 1.0f}, 0.0f},
    {{1.5f, -0.2f}, 0.0f},
    {{1.7f, -1.3f}, 0.0f},
};

static CoinTossCamShot_t _CoinToss_CamShot = {
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
    CoinTossPlacePlayers,
};

static CoinTossCamEntry_t _CoinToss_aCamList[2] = {
    {1, &_CoinToss_CamShot},
    {1, 0},
};

int CoinTossGetTeamSide(int a)
{
    int result = 0;

    switch (_CoinToss_pState->mUnknown42) {
    case 0:
        break;
    case 3:
        result = 3;
        break;
    case 1:
    case 2:
        if (_CoinToss_pState->mUnknown43 == 0) {
            result = 3;
        }
        break;
    }
    if (a == 1) {
        if (_CoinToss_pState->mUnknown40 != _CoinToss_pState->mUnknown41) {
            result = result == 0 ? 3 : 0;
        }
    } else if (_CoinToss_pState->mUnknown40 == _CoinToss_pState->mUnknown41) {
        result = result == 0 ? 3 : 0;
    }
    return result;
}

void CoinTossOnCallMade(void)
{
}

void CoinTossOnChoiceMade(void)
{
}

void CoinTossOnChoiceTimeout(void)
{
}

void CoinTossPlacePlayers(void)
{
    fn_800CC560(0);
    CoinTossSendPlayersToSpots(_CoinToss_aPlaceArg, _CoinToss_aStartSpotsSide0, _CoinToss_aStartSpotsSide1);
    CoinTossSnapPlayers();
    CoinTossSendPlayersToSpots(_CoinToss_aPlaceArg, _CoinToss_aMeetSpotsSide0, _CoinToss_aMeetSpotsSide1);
}

void CoinTossSendPlayersToSpots(unsigned char *pUnused, CoinTossSpot_t *pA, CoinTossSpot_t *pB)
{
    unsigned char side;
    unsigned short i;
    Message_800F01CC message;

    for (side = 0; side < 2; side++) {
        int *pRefs = side == 0 ? _CoinToss_pState->mRefs0 : _CoinToss_pState->mRefs1;
        CoinTossSpot_t *pTable = side == 0 ? pA : pB;

        for (i = 0; i < 3; i++) {
            Object_80039F5C *p = fn_8009BCE8(&pRefs[i]);
            CoinTossXY_t dir;
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
            fn_800F053C(0, p->mQueue, &message, p);

            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 6;
            message.mUnknown1[0] = angle;
            fn_800F03D8(0, p->mQueue, &message, p);

            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 9;
            message.mUnknown1[0] = 0xCB;
            message.mUnknown1[1] = 0;
            message.mUnknown1[2] = 0xFF;
            fn_800F03D8(0, p->mQueue, &message, p);
        }
    }
}

void CoinTossSnapPlayers(void)
{
    unsigned char side;
    unsigned short i;

    for (side = 0; side < 2; side++) {
        int *pRefs = side == 0 ? _CoinToss_pState->mRefs0 : _CoinToss_pState->mRefs1;

        for (i = 0; i < 3; i++) {
            fn_800FF6D8(fn_8009BCE8(&pRefs[i]));
        }
    }
}

int CoinTossDecide(int mode)
{
    int result = 0;

    if (_CoinToss_pState->mUnknown45 == 0) {
        switch (mode) {
        case 2:
            _CoinToss_pState->mUnknown40 = fn_802372EC(0, 2);
            _CoinToss_pState->mUnknown41 = fn_802372EC(0, 2);
            _CoinToss_pState->mUnknown42 = 1;
            _CoinToss_pState->mUnknown43 = fn_802372EC(0, 2);
            break;
        case 0:
            _CoinToss_pState->mUnknown40 = 0;
            _CoinToss_pState->mUnknown41 = 1;
            _CoinToss_pState->mUnknown42 = 1;
            _CoinToss_pState->mUnknown43 = fn_802372EC(0, 2);
            break;
        case 1:
            _CoinToss_pState->mUnknown40 = 0;
            _CoinToss_pState->mUnknown41 = 0;
            _CoinToss_pState->mUnknown42 = mode;
            _CoinToss_pState->mUnknown43 = fn_802372EC(0, 2);
            break;
        }
        if (fn_800B65A0(fn_80178308()) != 0xFF || fn_800B65A0(fn_80178320()) != 0xFF) {
            fn_8013F3FC();
        }
        _CoinToss_pState->mState = 10;
        CoinTossApplyResult();
        result = 1;
    }
    return result;
}

void CoinTossLockPlayer(Object_80039F5C *p)
{
    p->mpUnknown4->mUnknown20 |= 0x10;
    fn_80237260(0);
}

void CoinTossUnlockPlayer(Object_80039F5C *p)
{
    if (p != 0) {
        fn_800A3B5C(p);
    }
}

void CoinTossHoldPlayer(Object_80039F5C *p)
{
    Block_80170E64 *pBlock = p->mpUnknown4;

    CoinTossLockPlayer(p);
    pBlock->mUnknown20 |= 0x400;
}

void CoinTossReleasePlayer(Object_80039F5C *p)
{
    Block_80170E64 *pBlock = p->mpUnknown4;

    CoinTossUnlockPlayer(p);
    pBlock->mUnknown20 &= ~0x400;
}

void CoinTossAllocState(void)
{
    void *pHandle = fn_80238174(0, (void **)&_CoinToss_pState, sizeof(CoinTossState_t), 0, 0x63746F73);

    fn_801C1F94(fn_8023816C(pHandle), 0, sizeof(CoinTossState_t));
    fn_802381E0(pHandle);
}

void CoinTossClearState(void)
{
    _CoinToss_pState = 0;
}

void CoinTossStart(void)
{
    _CoinToss_pState->mState = 1;
    _CoinToss_pState->mUnknown40 = -1;
    _CoinToss_pState->mUnknown44 = -1;
    _CoinToss_pState->mUnknown41 = -1;
    _CoinToss_pState->mUnknown42 = -1;
    _CoinToss_pState->mUnknown43 = -1;
    _CoinToss_pState->mUnknown45 = 0;
    _CoinToss_pState->mTimer = -1;
    fn_8009BD48(&_CoinToss_pState->mRefs0[0], 1, 0, 0);
    fn_8009BD48(&_CoinToss_pState->mRefs1[0], 1, 1, 0);
    fn_8009BD48(&_CoinToss_pState->mRefs0[1], 1, 0, 6);
    fn_8009BD48(&_CoinToss_pState->mRefs0[2], 1, 0, 7);
    fn_8009BD48(&_CoinToss_pState->mRefs1[1], 1, 1, 6);
    fn_8009BD48(&_CoinToss_pState->mRefs1[2], 1, 1, 7);
    CoinTossHoldPlayer(fn_8009BCE8(&_CoinToss_pState->mRefs0[0]));
    CoinTossHoldPlayer(fn_8009BCE8(&_CoinToss_pState->mRefs0[1]));
    CoinTossHoldPlayer(fn_8009BCE8(&_CoinToss_pState->mRefs0[2]));
    CoinTossHoldPlayer(fn_8009BCE8(&_CoinToss_pState->mRefs1[0]));
    CoinTossHoldPlayer(fn_8009BCE8(&_CoinToss_pState->mRefs1[1]));
    CoinTossHoldPlayer(fn_8009BCE8(&_CoinToss_pState->mRefs1[2]));
    BannerClear(7);
    CoinTossDecide(0);
    _CoinToss_pState->mState = 0;
}

int CoinTossUpdate(void)
{
    int result = 1;

    switch (_CoinToss_pState->mState) {
    case 1:
        CoinTossOnShotStart();
        fn_8013F374(_CoinToss_aCamList);
        UISGameLockPad((unsigned char)CoinTossGetCallerPad());
        _CoinToss_pState->mState = 2;
        break;
    case 2:
        if (_CoinToss_pState->mUnknown40 != -1) {
            _CoinToss_pState->mState = 3;
        }
        break;
    case 3:
        CoinTossOnCallMade();
        _CoinToss_pState->mState = 4;
        break;
    case 4:
        _CoinToss_pState->mState = 5;
        UISGameUnlockPad();
        UISGameLockPad((unsigned char)CoinTossGetWinnerPad());
        break;
    case 5:
        if (_CoinToss_pState->mUnknown42 != -1) {
            _CoinToss_pState->mState = 6;
            _CoinToss_pState->mTimer = 0;
            CoinTossOnChoiceMade();
            UISGameUnlockPad();
            UISGameLockPad((unsigned char)CoinTossGetLoserPad());
        }
        break;
    case 6:
        if (_CoinToss_pState->mUnknown43 != -1) {
            _CoinToss_pState->mState = 9;
            fn_8013F3FC();
            goto finish;
        }
        if (_CoinToss_pState->mTimer == 240) {
            CoinTossOnChoiceTimeout();
            _CoinToss_pState->mTimer = -1;
        }
        if (_CoinToss_pState->mTimer != -1) {
            _CoinToss_pState->mTimer++;
        }
        break;
    case 9:
    finish:
        fn_800CC560(0);
        _CoinToss_pState->mState = 10;
    case 0:
    case 10:
        _CoinToss_pState->mState = 0;
        result = 0;
        UISGameUnlockPad();
        break;
    }
    return result;
}

void CoinTossFinish(void)
{
    InGameSetInputPaused(0);
    CoinTossReleasePlayer(fn_8009BCE8(&_CoinToss_pState->mRefs0[0]));
    CoinTossReleasePlayer(fn_8009BCE8(&_CoinToss_pState->mRefs0[1]));
    CoinTossReleasePlayer(fn_8009BCE8(&_CoinToss_pState->mRefs0[2]));
    CoinTossReleasePlayer(fn_8009BCE8(&_CoinToss_pState->mRefs1[0]));
    CoinTossReleasePlayer(fn_8009BCE8(&_CoinToss_pState->mRefs1[1]));
    CoinTossReleasePlayer(fn_8009BCE8(&_CoinToss_pState->mRefs1[2]));
    _CoinToss_pState->mState = 0;
}

void CoinTossOnShotStart(void)
{
}

void CoinTossApplyResult(void)
{
    int team = CoinTossGetOffenseTeam();

    fn_8017833C(team);
    if (CoinTossGetTeamSide(team) == 0) {
        if (fn_801784C4() != 0) {
            fn_80177E6C(1, 1);
        }
    } else if (fn_801784C4() == 0) {
        fn_80177E6C(1, 1);
    }
    if (FELoopIsMainFEActive() == 0) {
        fn_8022DDB4(0x53544347, &_CoinToss_pState->mUnknown40);
    }
}

void CoinTossApplyResultSwapped(void)
{
    int team = CoinTossGetOffenseTeam() == 0;

    fn_8017833C(team);
    if (CoinTossGetTeamSide(team) == 0) {
        if (fn_801784C4() != 0) {
            fn_80177E6C(1, 1);
        }
    } else if (fn_801784C4() == 0) {
        fn_80177E6C(1, 1);
    }
}

int CoinTossGetCallerPad(void)
{
    int value = fn_800B65A0(1);

    return value == 0xFF ? -1 : value;
}

int CoinTossGetWinnerPad(void)
{
    int value;

    if (_CoinToss_pState->mUnknown41 == _CoinToss_pState->mUnknown40) {
        value = fn_800B65A0(1);
    } else {
        value = fn_800B65A0(0);
    }
    return value == 0xFF ? -1 : value;
}

int CoinTossGetLoserPad(void)
{
    int value;

    if (_CoinToss_pState->mUnknown41 == _CoinToss_pState->mUnknown40) {
        value = fn_800B65A0(0);
    } else {
        value = fn_800B65A0(1);
    }
    return value == 0xFF ? -1 : value;
}

int CoinTossGetOffenseTeam(void)
{
    int result = 0;

    if (_CoinToss_pState->mUnknown40 == _CoinToss_pState->mUnknown41) {
        switch (_CoinToss_pState->mUnknown42) {
        case 1:
            break;
        case 0:
        case 3:
            result = _CoinToss_pState->mUnknown43 != 2;
            break;
        case 2:
            result = 1;
            break;
        }
    } else {
        switch (_CoinToss_pState->mUnknown42) {
        case 2:
            break;
        case 0:
        case 3:
            result = _CoinToss_pState->mUnknown43 == 2;
            break;
        case 1:
            result = 1;
            break;
        }
    }
    return result;
}
