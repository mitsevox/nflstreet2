/* Scrimmage rules and play statistics. The 'scru' state block holds the ball
   spot, the line to gain, the down, the offense team, the scores, the field
   dimensions and boundary walls and whether the field is flipped; its accessors
   are called by most of the game's on-field code. The rule sets (base and
   style-point scoring) decide the score limit, the winner, the game clock and
   where the ball is placed for a drive. After each play the stat tallies walk
   the play's event records and credit passing, rushing, receiving, kicking,
   return, down and style stats to players and teams. */
#include "game/ScrmGetBallSpot.h"
#include "game/StyleTracker.h"
#include <math.h>
#include <string.h>
#include "game/ScrmRuleSet.h"
#include "game/MiniGameC.h"
#include "game/FELoop.h"
#include "game/Object_80039F5C.h"
#include "game/LevelData.h"
#include "game/Challenge.h"
#include "game/ScrmPlayResult.h"
#include "game/Record_800B15FC.h"
#include "game/Collide.h"
#include "game/AudmonEvent.h"
#include "game/GameInfo.h"
#include "game/Ball.h"
#include "game/ReplayEvent.h"
#include "game/GameOptions.h"
#include "game/fn_800AD9B4.h"
#include "game/PlayBookGetPlay.h"
#include "game/ScrmGetTeamPlayerCount.h"
#include "game/GameModeType.h"
#include "game/TDbCompilePerformOp.h"
#include "game/SyncStateRegister.h"
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"
#include "game/Info_ScrmState.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

class ScrmStyleRuleSet : public ScrmRuleSet {
public:
    virtual int GetScoreLimit();
    virtual int GetWinner();
    virtual int IsNearWin(int team);
    virtual int GetScoreType();
    virtual int GetScore(int team);
};

struct Segment_ScrmState {
    FieldPoint_t mA;
    FieldPoint_t mB;
};

/* The 'scru' block allocated by ScrmInit; _Scrm_pState points to it. */
struct ScrmState {
    int mPlayTurnovers;
    float mPrevLineToGain;
    float mLineToGain;
    FieldPoint_t mBallSpot;
    FieldPoint_t mPlayStartSpot;
    FieldPoint_t mMarkerSpot;
    FieldPoint_t mDeadBallSpot;
    int mPlayDown;
    int mDown;
    unsigned int mPlayFlags;
    unsigned char mOffenseTeam;
    unsigned char mFieldFlipped;
    unsigned char mSnapFieldFlipped;
    unsigned char mUnknown3B;
    short mScore0;
    short mScore1;
    int mDriveBallPlaced;
    int mTacklerRef;
    unsigned char mTacklerInfo;
    Info_ScrmState mInfo;
    ScrmPlayResult_t mPlayResult;
    float mSidelineX;
    float mGoalLineY;
    float mEndLineY;
    float mSpotLimitX;
    float mFirstDownInterval;
    float mOffenseDepth;
    float mOffenseMinDepth;
    float mDefenseDepth;
    float mDefenseMinDepth;
    unsigned char mSnapOffense;
    unsigned char mNumWalls;
    unsigned short mDriveCount;
    Segment_ScrmState mWalls[50];
    float mDriveStartDistance;
    ScrmRuleSet *mpRuleSet;
    int mConversionKind;
    unsigned char mConversionPlaced;
};

/* A stat value saved by ScrmStatSaveOriginal before its first change in a play. The
   entry after the last one has mKind == -1. */
struct ScrmStatSaved_t {
    int mTag;
    int mHandle;
    int mValue;
    signed char mKind;
};

/* Per-team stat values that ScrmStatBeginTally reads before the play tallies. */
struct ScrmStatBaseline_t {
    int mTp;
    int mSp;
    int mFs;
};

extern "C" {
int ChallengeIsActive(void);
CollideSet_t *PlyrMgrGetCollideSet(void);
void PlyrMgrReverseAll(void);
void HotspotClearQueue(void);
void SndgSpchSetPlayFlags(int a);
void EnvSelect(int id);
void EnvRelease(void);
int EnvIsENVFSet(void);
void fn_80093C3C(int index, short value, Object_80039F5C *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
float fn_800A32B4(void);
float fn_800A32C0(void);
float fn_800A32CC(void);
float fn_800A32D8(void);
float fn_800A32E4(void);
int fn_800A3444(void);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800AD910(int a, float b);
void fn_800B1584(int a, const float *pPos);
int fn_800B2314(void);
int fn_800BA6F8(void);
FieldPoint_t fn_800BA7A0(void);
int fn_800BAAB8(void);
int fn_800C8704(int *pA, int *pB);
int fn_800C8744(int team);
void fn_800C87CC(int team, int value);
void fn_800C9FC0(void);
int PlayerMoveGetKind(Object_80039F5C *p);
void fn_8011DF90(void);
void fn_8011F574(void);
void fn_80120618(void);
void CamGameSuspendAll(void);
void CamGameResumeAll(void);
CollideSet_t *StatcollGetSet(void);
int fn_801486A0(void);
int PlayAlignHasSlots(PlayBookPlay_t *pRecord);
void ScrmSpotUpdate(void);
int ScrmSpotGetFirstHit(float *pOut);
void ClockRuleInit(void);
void ClockRuleShutdown(void);
void ClockRuleUpdate(unsigned int value);
void DriveLogEndDrive(void);
void DriveLogAddPlay(int type, short a, short b, int c, int d);
int DriveLogHasLongPlay(void);
void DriveLogSetLongPlay(void);
void PenaltyCheckPassInterference(void);
void ScoringLogAddScore(int type, short a, int b, int c);
void ScoringLogSetConversion(int a, int b, int c, int d);
int GameModeTypeIsSpecial(void);
void fn_8022B2CC(int handle, int tag, int value);
int fn_8022B414(int handle, int tag, int *pValue);
int fn_8022B580(int handle, int tag, int value);
int fn_8022B7A4(int handle, int tag, int *pValue);
int fn_8022B8C8(int handle, int tag, int value);
void fn_8022BAB4(int handle, int a, int b, int c);
void fn_8022BD30(int handle, int a, int b);
void *SyncStateGetData(void *pHandle);
}

extern "C" {
unsigned int ScrmGetBoundaryWallFlags(const FieldPoint_t *p);
void ScrmCollectBoundaryWalls(void);
FieldPoint_t ScrmClampSpot(FieldPoint_t point);
void ScrmInit(void);
void ScrmShutdown(void);
void ScrmResetGame(int a);
void ScrmUpdate(float value);
int ScrmGetPlayTurnovers(void);
void ScrmSetPlayTurnovers(int value);
void ScrmChangePossession(int a);
void ScrmSaveFieldFlip(void);
void ScrmRestoreFieldFlip(void);
void ScrmFlipForDrive(int a);
void ScrmMirrorField(int a, int flip);
int ScrmGetDown(void);
int ScrmGetPlayDown(void);
void ScrmSetDown(int value);
void ScrmSetPlayDown(int value);
FieldPoint_t ScrmGetTeamSetupSpot(int team);
FieldPoint_t ScrmGetPlayStartSpot(void);
FieldPoint_t ScrmGetMarkerSpot(void);
void ScrmSetBallSpot(FieldPoint_t pos);
void ScrmSetMarkerSpot(FieldPoint_t pos);
int ScrmGetYardsToGo(void);
void ScrmSetDeadBallSpot(FieldPoint_t pos);
float ScrmGetLineToGain(void);
float ScrmGetPrevLineToGain(void);
void ScrmSetFirstDownLine(void);
void ScrmSetLineToGain(float line);
static unsigned char IsShortOfLineToGain(float range, unsigned char *pWithinRange);
int ScrmGetOffenseTeam(void);
int ScrmGetDefenseTeam(void);
void ScrmSetOffenseTeam(int value);
unsigned char ScrmGetSnapOffense(void);
void ScrmSetSnapOffense(int value);
int ScrmGetSnapDefense(void);
void ScrmEndPlay(void);
int ScrmTestPlayFlag(int bit);
void ScrmSetPlayFlag(int bit, int on);
void ScrmResetPlay(void);
int ScrmIsFieldFlipped(void);
int ScrmHasFieldFlippedInPlay(void);
int ScrmClassifyPosition(FieldPoint_t *pPos, float *pOut, int skipFlags);
void ScrmSetTackler(Object_80039F5C *p);
Object_80039F5C *ScrmGetTackler(void);
unsigned char ScrmGetTacklerInfo(void);
int ScrmIsNotReplay(void);
int ScrmGetTeamScore(int team);
void ScrmSetTeamScore(int team, short value);
int ScrmGetRuleScore(int a);
void ScrmClearDriveBallPlaced(void);
void ScrmSetPlayResult(const ScrmPlayResult_t *p);
static int RoundToNearestInt(float value);
int ScrmGetScoreGoal(int *pValue);
void ScrmQuarterEnd(void);
void ScrmSetSidelineX(float value);
float ScrmGetSidelineX(void);
void ScrmSetGoalLineY(float value);
void ScrmSetFirstDownInterval(float value);
float ScrmGetGoalLineY(void);
void ScrmSetEndLineY(float value);
float ScrmGetEndLineY(void);
void ScrmSetSpotLimitX(float value);
float ScrmGetSpotLimitX(void);
float ScrmGetDistanceToBounds(FieldPoint_t *pPos);
int ScrmGetWinner(void);
void ScrmAwardWin(int a);
void ScrmLoadFieldDimensions(void);
int ScrmIsNearWin(int a);
int ScrmIsOpponentNearWin(int a);
int ScrmIsTimed(void);
int ScrmGetGameTime(void);
int ScrmUsesBothTeams(void);
void ScrmPlaceBallForDrive(int a);
unsigned int ScrmGetTeamPlayerCount(int team);
int ScrmGetActivePlayerCount(int team);
unsigned int ScrmGetRosterPlayerCount(void);
int ScrmAllowsAudibles(void);
int ScrmAllowsPrediction(void);
void ScrmSetDriveStartDistance(float v);
unsigned short ScrmGetDriveCount(void);
int ScrmGetGoalTotal(int a);
int ScrmGetGoalCount(int a);
void ScrmSetRuleSet(ScrmRuleSet *pRule);
void ScrmResetPlaySpot(void);
float ScrmGetSetupDepth(int team);
void ScrmSetSetupDepth(int team, float a, float b);
int ScrmGetConversionKind(void);
void ScrmSetConversionKind(int a);
void ScrmClearConversion(void);
void ScrmPlaceConversionBall(void);
int ScrmSnapPlayHasSlots(void);
void ScrmStatSaveOriginal(int handle, int tag, int value, int kind);
int ScrmStatGetPlayerHandle(int id);
int ScrmStatGetPlayerTeamHandle(int id);
void ScrmStatAddPlayer(int id, int tag, int value);
void ScrmStatAddHandle(int handle, int tag, int value);
void ScrmStatAddPlayerTeam(int id, int tag, int value);
void ScrmStatAddTeam(int team, int tag, int value);
void ScrmStatAddTeamPass(int id, int a, float b, float c);
void ScrmStatAddTeamRush(int id, float a, float b);
void ScrmStatAddPassing(int id, float from, float to);
void ScrmStatAddReceiving(int id, float from, float catchY, float to, float time);
void ScrmStatAddRushing(int id, float from, float to, float time);
void ScrmStatAddInterceptionReturn(int id, float from, float to);
void ScrmStatAddPunt(int id, float from, float to, float spot, int flag);
void ScrmStatAddPuntReturn(int id, float from, float to);
void ScrmStatAddKickReturn(int id, float from, float to);
void ScrmStatAddAssist(int ref);
int ScrmStatTallyPlay(unsigned char *pFlag);
int ScrmStatTallyConversion(void);
void ScrmStatTallyTeamPlay(ScrmPlayResult_t *pResult, int kind, unsigned char flag);
void ScrmStatPlayHook(void);
void ScrmStatEndPlay(ScrmPlayResult_t *pResult);
void ScrmStatAddPossessionTime(int value);
void ScrmStatAddDriveStart(unsigned short team, short value);
void ScrmStatAddLongPlay(unsigned short team);
void ScrmStatAddLongScore(unsigned short team, int play);
void ScrmStatAddPenalty(unsigned short team, short yards, int handle);
void ScrmStatBeginTally(void);
void ScrmStatAddTeamStyleGain(unsigned short team, int value);
void ScrmStatAddTeamStylePoints(unsigned short team, int value);
void ScrmStatAddTeamPitches(unsigned short team, int value);
void ScrmStatAddTeamStylePass(unsigned short team, int value);
void ScrmStatAddTeamVariantCatch(unsigned short team, int value);
void ScrmStatAddTeamWp(unsigned short team, int value);
void ScrmStatAddTeamSs(unsigned short team, int value, int also);
void ScrmStatAddTeamSd(unsigned short team, int value);
void ScrmStatAddTeamSh(unsigned short team, int value, int also);
void ScrmStatAddTeamWh(unsigned short team, int value);
void ScrmStatAddTeamStylePitch(unsigned short team, int value);
void ScrmStatAddTeamQbStopStreak(unsigned short team, int value);
void ScrmStatAddTeamUserQbStopStreak(unsigned short team, int value);
void ScrmStatAddTeamVt(unsigned short team, int value);
void ScrmStatAddTeamCatchStreak(unsigned short team, int value);
void ScrmStatAddTeamOg(unsigned short team, int value);
void ScrmStatAddTeamMoveScore(unsigned short team, int value);
void ScrmStatAddTeamStyleCatchStreak(unsigned short team, int value);
void ScrmStatAddTeamSv(unsigned short team, int value);
void ScrmStatAddTeamWt(unsigned short team, int value);
void ScrmStatAddTeamPitchChain(unsigned short team, int value);
void ScrmStatAddTeamInterceptMove(unsigned short team, int value);
void ScrmStatAddTeamStyleCatch(unsigned short team, int value);
void ScrmStatAddTeamNinjaCatch(unsigned short team, int value);
void ScrmStatAddHotspotCapture(int id, int value);
void ScrmStatAddTeamStrip(int team, int value);
void ScrmStatAddTeamGiveaway(unsigned short team, int value);
void ScrmStatSetEventCallback(void (*pCallback)(int kind, int a, int b));
}

static unsigned char _Scrm_bSavedFieldFlip = 0;
static ScrmState *_Scrm_pState = 0;
static float _Scrm_fWallTolerance = 1.0f;
static float _Scrm_fBoundaryTolerance = 0.33f;
static void (*_ScrmStat_pEventCallback)(int kind, int a, int b) = 0;
static unsigned char _ScrmStat_bStopAtIncomplete = 0;
static int _ScrmStat_iNumSaved = 0;

static ScrmRuleSet _Drive_ScrimmageRules;
static ScrmStyleRuleSet _Drive_AltScrimmageRules;
static ScrmPlayResult_t *_Drive_pPlayResult;

static ScrmStatSaved_t _Drive_aStatEvents[0x61];

static ScrmStatBaseline_t _ScrmStat_aTeamBaseline[2] = { { 0, 0, 0 }, { 0, 0, 0 } };

static inline void Negate(FieldPoint_t &v)
{
    v.mX = -v.mX;
    v.mY = -v.mY;
}

extern "C" unsigned int ScrmGetBoundaryWallFlags(const FieldPoint_t *p)
{
    unsigned int result = 0;
    unsigned char i;

    for (i = 0; i < _Scrm_pState->mNumWalls; i++) {
        FieldPoint_t a = _Scrm_pState->mWalls[i].mA;
        FieldPoint_t b = _Scrm_pState->mWalls[i].mB;

        if (ScrmIsFieldFlipped()) {
            Negate(a);
            Negate(b);
        }
        if (fabsf(p->mX - a.mX) < _Scrm_fWallTolerance && fabsf(p->mX - b.mX) < _Scrm_fWallTolerance) {
            if (a.mY > b.mY) {
                if (p->mY >= b.mY && p->mY <= a.mY) {
                    if (p->mX > 0.0f) {
                        result |= 1;
                    } else {
                        result |= 2;
                    }
                }
            } else {
                if (p->mY >= a.mY && p->mY <= b.mY) {
                    if (p->mX > 0.0f) {
                        result |= 1;
                    } else {
                        result |= 2;
                    }
                }
            }
        }
        if (fabsf(p->mY - a.mY) < _Scrm_fWallTolerance && fabsf(p->mY - b.mY) < _Scrm_fWallTolerance) {
            if (a.mX > b.mX) {
                if (p->mX >= b.mX && p->mX <= a.mX) {
                    if (p->mY > 0.0f) {
                        result |= 4;
                    } else {
                        result |= 8;
                    }
                }
            } else {
                if (p->mX >= a.mX && p->mX <= b.mX) {
                    if (p->mY > 0.0f) {
                        result |= 4;
                    } else {
                        result |= 8;
                    }
                }
            }
        }
    }
    return result;
}

extern "C" void ScrmCollectBoundaryWalls(void)
{
    unsigned char count = 0;

    if (LevelGetData()) {
        unsigned char i;
        unsigned char total = LevelGetData()->mUnknown136;
        LevelWall_t *pRecord = LevelGetData()->mUnknown140;

        for (i = 0; i < total; i++, pRecord++) {
            FieldPoint_t a;
            FieldPoint_t b;

            LevelGetWallBase(pRecord, &a, &b);
            if (ScrmIsFieldFlipped()) {
                Negate(a);
                Negate(b);
            }
            if ((fabs(a.mX - ScrmGetSidelineX()) < _Scrm_fBoundaryTolerance && fabs(b.mX - ScrmGetSidelineX()) < _Scrm_fBoundaryTolerance)
                || (fabs(a.mX + ScrmGetSidelineX()) < _Scrm_fBoundaryTolerance && fabs(b.mX + ScrmGetSidelineX()) < _Scrm_fBoundaryTolerance)
                || (fabs(a.mY - ScrmGetEndLineY()) < _Scrm_fBoundaryTolerance && fabs(b.mY - ScrmGetEndLineY()) < _Scrm_fBoundaryTolerance)
                || (fabs(a.mY + ScrmGetEndLineY()) < _Scrm_fBoundaryTolerance && fabs(b.mY + ScrmGetEndLineY()) < _Scrm_fBoundaryTolerance)) {
                _Scrm_pState->mWalls[count].mA = a;
                _Scrm_pState->mWalls[count].mB = b;
                count++;
            }
        }
    }
    _Scrm_pState->mNumWalls = count;
}

extern "C" FieldPoint_t ScrmClampSpot(FieldPoint_t point)
{
    FieldPoint_t result;

    if (fn_800BA6F8()) {
        result = fn_800BA7A0();
    } else {
        result = point;
    }
    result.mX = CLAMP(result.mX, -ScrmGetSpotLimitX(), ScrmGetSpotLimitX());
    result.mY = CLAMP(result.mY, 0.16f - ScrmGetGoalLineY(), ScrmGetGoalLineY() - 0.16f);
    return result;
}

int ScrmRuleSet::GetScoreLimit()
{
    return GameOptionsGet(1);
}

int ScrmRuleSet::GetWinner()
{
    unsigned short score0 = ScrmGetTeamScore(0);
    unsigned short score1 = ScrmGetTeamScore(1);
    unsigned int limit = GetScoreLimit();
    int result;

    if (score0 > score1 && score0 >= limit) {
        result = 0;
    } else if (score0 < score1 && score1 >= limit) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}

void ScrmRuleSet::AwardWin(int team)
{
    if (ChallengeIsActive()) {
        fn_8009D8CC(4);
        fn_8009D964(4, 0);
    } else {
        int value = 0;

        switch (ScrmGetScoreGoal(&value)) {
        case 0:
            ScrmSetTeamScore(team, (short)value);
            fn_800C87CC(team, value);
            break;
        case 1:
            StyleTrackerSetTotal(team, value);
            break;
        }
    }
}

int ScrmRuleSet::IsNearWin(int team)
{
    int result = 0;
    unsigned int limit = GetScoreLimit();

    if (ScrmGetDown() != 6) {
        if (ScrmGetOffenseTeam() == team && limit - ScrmGetTeamScore(team) <= 8) {
            result = 1;
        }
    } else {
        if (ScrmGetOffenseTeam() == team && limit - ScrmGetTeamScore(team) <= 2) {
            result = 1;
        }
    }
    return result;
}

int ScrmRuleSet::IsOpponentNearWin(int team)
{
    return IsNearWin(team ^ 1);
}

int ScrmRuleSet::GetScoreType()
{
    return 0;
}

int ScrmRuleSet::GetScore(int team)
{
    return ScrmGetTeamScore(team);
}

int ScrmRuleSet::IsTimed()
{
    return 0;
}

int ScrmRuleSet::IsWinAwarded()
{
    return 0;
}

int ScrmRuleSet::GetGameTime()
{
    return 900;
}

void ScrmRuleSet::ResetPlaySpot()
{
    ScrmPlayResult_t *p = ScrmGetPlayResult();

    ScrmSetPlayDown(ScrmGetDown());
    ScrmSetDown(p->mUnknown04);
    ScrmSetBallSpot(p->mUnknown08);
}

int ScrmRuleSet::GetTeamSize()
{
    return 7;
}

int ScrmRuleSet::AllowsAudibles()
{
    int result = 1;

    if (ChallengeIsActive()) {
        result = ChalGetCurrent()->mUnknown1B0 == 0;
    }
    return result;
}

int ScrmRuleSet::AllowsPrediction()
{
    int result = 1;

    if (ChallengeIsActive()) {
        result = ChalGetCurrent()->mUnknown1B4 == 0;
    }
    return result;
}

void ScrmRuleSet::ResetGame(int team)
{
    ScrmPlayResult_t info;

    ScrmClearConversion();
    ScrmSetTeamScore(0, 0);
    ScrmSetTeamScore(1, 0);
    ScrmClearDriveBallPlaced();
    memset(&info, 0, sizeof(info));
    ScrmSetPlayResult(&info);
    ScrmSetDown(1);
    _Scrm_pState->mDriveCount = 0;
    if (team != 2) {
        ScrmSetOffenseTeam(team);
        ScrmSetSnapOffense(team);
    }
}

int ScrmRuleSet::UsesBothTeams()
{
    return 1;
}


void ScrmRuleSet::EndPlay()
{
    int mode = fn_800AD9B4();

    if (mode == 4 || mode == 7) {
        return;
    }
    if (mode == 5 && GameModeTypeIsSpecial()) {
        return;
    }
    if (fn_801486A0() || ScrmGetPlayTurnovers() || ScrmTestPlayFlag(3)) {
        Record_800B15FC *p = fn_800B15FC();
        Object_80039F5C *pPlayer;

        p->mUnknown14 = 2;
        p->mUnknown10 = p->mUnknownC = 0.0f;
        fn_800B1508();
        fn_800A8954(0x16, ScrmGetOffenseTeam(), 0);
        HotspotClearQueue();
        pPlayer = BallGetCurrentHolder();
        if (pPlayer && fn_801BE648(pPlayer->mpUnknown792) == 0xED) {
            StyleTrackerAwardDive(pPlayer, PlayerMoveGetKind(pPlayer), 0xFF);
        }
        fn_800AD910(4, 0.0f);
    }
}

int ScrmStyleRuleSet::GetScoreLimit()
{
    return GameOptionsGet(2);
}

int ScrmStyleRuleSet::GetWinner()
{
    return StyleTrackerGetWinner();
}

int ScrmStyleRuleSet::IsNearWin(int team)
{
    int result = 0;
    unsigned int limit = GetScoreLimit();

    if (ScrmGetDown() != 6 && limit - StyleTrackerGetTotal(team) <= 50000) {
        result = 1;
    }
    return result;
}

int ScrmStyleRuleSet::GetScoreType()
{
    return 1;
}

int ScrmStyleRuleSet::GetScore(int team)
{
    return StyleTrackerGetTotal(team);
}

extern "C" void ScrmInit(void)
{
    void *pHandle = SyncStateRegister(0, (void **)&_Scrm_pState, sizeof(ScrmState), 0, 0x73637275);
    ScrmState *pState = (ScrmState *)SyncStateGetData(pHandle);

    int resume = 0;

    GameModeTypeGet();
    if (resume) {
        TDbCompilePerformOp(0, "select 'SRSG' into \x89 from 'NIBG'\n", pState);
    }
    pState->mLineToGain = 0.0f;
    pState->mBallSpot.mX = 0.0f;
    pState->mBallSpot.mY = 0.0f;
    pState->mSnapOffense = pState->mOffenseTeam = GameInfoGet(2);
    if (ChallengeIsActive()) {
        pState->mScore0 = ChalGetCurrent()->mUnknown1AC;
        pState->mScore1 = ChalGetCurrent()->mUnknown1A8;
        TDbCompilePerformOp(0, "update 'FNIG' set 'CSAG' = \x82 and 'CSHG' = \x82\n", pState->mScore1, pState->mScore0);
        pState->mDown = ChalGetCurrent()->mUnknown1C1;
    } else {
        pState->mDown = 1;
        pState->mScore0 = 0;
        pState->mScore1 = 0;
    }
    pState->mPrevLineToGain = 0.0f;
    pState->mPlayStartSpot.mX = 0.0f;
    pState->mPlayTurnovers = 0;
    pState->mPlayStartSpot.mY = 0.0f;
    pState->mPlayDown = 1;
    pState->mUnknown3B = 0;
    pState->mDriveCount = 0;
    pState->mNumWalls = 0;
    if (!FELoopIsMainFEActive()) {
        EnvSelect(fn_800A3444());
        if (EnvIsENVFSet() == 1) {
            pState->mFieldFlipped = 1;
        } else {
            pState->mFieldFlipped = 0;
        }
        EnvRelease();
    } else {
        pState->mFieldFlipped = 0;
    }
    pState->mDriveStartDistance = 7.0f;
    pState->mOffenseDepth = 0.0f;
    pState->mOffenseMinDepth = 0.0f;
    pState->mDefenseDepth = 0.0f;
    pState->mDefenseMinDepth = 0.0f;
    SyncStateCommit(pHandle);
    ScrmSetRuleSet(0);
    ClockRuleInit();
    ScrmClearConversion();
}

extern "C" void ScrmShutdown(void)
{
    ClockRuleShutdown();
    _Scrm_pState = 0;
}


extern "C" void ScrmResetGame(int a)
{
    fn_800C9FC0();
    _Scrm_pState->mpRuleSet->ResetGame(a);
}


extern "C" void ScrmUpdate(float value)
{
    ScrmSpotUpdate();
    ClockRuleUpdate(value);
    PenaltyCheckPassInterference();
}

static inline void FlipSides(void)
{
    ScrmState *s = _Scrm_pState;
    s->mBallSpot.mX = -s->mBallSpot.mX;
    s->mBallSpot.mY = -s->mBallSpot.mY;
    s->mPlayStartSpot.mX = -s->mPlayStartSpot.mX;
    s->mPlayStartSpot.mY = -s->mPlayStartSpot.mY;
    s->mMarkerSpot.mX = -s->mMarkerSpot.mX;
    s->mMarkerSpot.mY = -s->mMarkerSpot.mY;
    s->mLineToGain = -s->mLineToGain;
    s->mPrevLineToGain = -s->mPrevLineToGain;
    s->mDeadBallSpot.mX = -s->mDeadBallSpot.mX;
    s->mDeadBallSpot.mY = -s->mDeadBallSpot.mY;
}

extern "C" int ScrmGetPlayTurnovers(void)
{
    return _Scrm_pState->mPlayTurnovers;
}

extern "C" void ScrmSetPlayTurnovers(int value)
{
    _Scrm_pState->mPlayTurnovers = value;
}

extern "C" void ScrmChangePossession(int a)
{
    switch (fn_801486A0()) {
    case 3:
        _Scrm_pState->mPlayTurnovers++;
        ScrmSetOffenseTeam(_Scrm_pState->mOffenseTeam ^ 1);
        fn_800B1584(0x1E, 0);
        fn_8011DF90();
        break;
    case 0:
        _Scrm_pState->mPlayTurnovers++;
        ScrmSetOffenseTeam(_Scrm_pState->mOffenseTeam ^ 1);
        fn_8011DF90();
        ScrmEndPlay();
        break;
    case 1:
        break;
    default:
        fn_80120618();
        fn_8011F574();
        if (++_Scrm_pState->mPlayTurnovers > 3) {
            _Scrm_pState->mPlayTurnovers = 2;
        }
        ScrmSetOffenseTeam(_Scrm_pState->mOffenseTeam ^ 1);
        ScrmFlipForDrive(a);
        fn_8011DF90();
        ScrmSetPlayFlag(2, 0);
        _Scrm_pState->mDriveCount++;
        break;
    }
}

extern "C" void ScrmSaveFieldFlip(void)
{
    _Scrm_bSavedFieldFlip = ScrmIsFieldFlipped();
}

extern "C" void ScrmRestoreFieldFlip(void)
{
    _Scrm_pState->mFieldFlipped = _Scrm_bSavedFieldFlip;
}

extern "C" void ScrmFlipForDrive(int a)
{
    if (_Scrm_pState->mDriveBallPlaced == 0 || (fn_800B65A0(0) == 0xFF && fn_800B65A0(1) == 0xFF)) {
        ScrmMirrorField(a, 1);
    } else {
        FlipSides();
    }
}

extern "C" void ScrmMirrorField(int a, int flip)
{
    if (flip) {
        FlipSides();
    }
    PlyrMgrReverseAll();
    BallsMirror();
    CollideSetMirror(PlyrMgrGetCollideSet());
    CollideSetMirror(StatcollGetSet());
    CollideSetMirror(BallGetCollRecords());
    CamGameSuspendAll();
    if (_Scrm_pState->mFieldFlipped == 0) {
        _Scrm_pState->mFieldFlipped = 1;
    } else {
        _Scrm_pState->mFieldFlipped = 0;
    }
    fn_800B1584(0x1E, 0);
    if (a) {
        CamGameResumeAll();
    }
}

extern "C" int ScrmGetDown(void)
{
    return _Scrm_pState->mDown;
}

extern "C" int ScrmGetPlayDown(void)
{
    return _Scrm_pState->mPlayDown;
}

extern "C" void ScrmSetDown(int value)
{
    if (fn_800BA6F8()) {
        _Scrm_pState->mDown = fn_800BAAB8();
    } else {
        _Scrm_pState->mDown = value;
    }
}

extern "C" void ScrmSetPlayDown(int value)
{
    _Scrm_pState->mPlayDown = value;
}

extern "C" FieldPoint_t ScrmGetBallSpot(void)
{
    return _Scrm_pState->mBallSpot;
}

extern "C" FieldPoint_t ScrmGetTeamSetupSpot(int team)
{
    FieldPoint_t pos;
    pos = ScrmGetBallSpot();
    pos.mY += ScrmGetSetupDepth(team);
    return pos;
}

extern "C" FieldPoint_t ScrmGetPlayStartSpot(void)
{
    return _Scrm_pState->mPlayStartSpot;
}

extern "C" FieldPoint_t ScrmGetMarkerSpot(void)
{
    return _Scrm_pState->mMarkerSpot;
}

extern "C" void ScrmSetBallSpot(FieldPoint_t pos)
{
    _Scrm_pState->mPlayStartSpot = _Scrm_pState->mBallSpot;
    _Scrm_pState->mBallSpot = ScrmClampSpot(pos);
    _Scrm_pState->mMarkerSpot = ScrmClampSpot(pos);
}

extern "C" void ScrmSetMarkerSpot(FieldPoint_t pos)
{
    _Scrm_pState->mMarkerSpot = ScrmClampSpot(pos);
}

extern "C" int ScrmGetYardsToGo(void)
{
    float line = ScrmGetLineToGain();
    if (line >= ScrmGetGoalLineY()) {
        return -1;
    }
    FieldPoint_t pos;
    pos = ScrmGetBallSpot();
    return ((char)ScrmGetGoalLineY() - (char)pos.mY) - ((char)ScrmGetGoalLineY() - (char)line);
}

extern "C" void ScrmSetDeadBallSpot(FieldPoint_t pos)
{
    _Scrm_pState->mDeadBallSpot = pos;
}

extern "C" FieldPoint_t ScrmGetDeadBallSpot(void)
{
    return _Scrm_pState->mDeadBallSpot;
}

extern "C" float ScrmGetLineToGain(void)
{
    return _Scrm_pState->mLineToGain;
}

extern "C" float ScrmGetPrevLineToGain(void)
{
    return _Scrm_pState->mPrevLineToGain;
}

extern "C" void ScrmSetFirstDownLine(void)
{
    float line = -_Scrm_pState->mGoalLineY;
    while (line <= _Scrm_pState->mBallSpot.mY) {
        line += _Scrm_pState->mFirstDownInterval;
    }
    _Scrm_pState->mPrevLineToGain = _Scrm_pState->mLineToGain;
    _Scrm_pState->mLineToGain = line;
}

extern "C" void ScrmSetLineToGain(float line)
{
    _Scrm_pState->mPrevLineToGain = _Scrm_pState->mLineToGain;
    _Scrm_pState->mLineToGain = line;
}

static unsigned char IsShortOfLineToGain(float range, unsigned char *pWithinRange)
{
    unsigned char isShort = 0;
    float distance;

    *pWithinRange = 0;
    distance = _Scrm_pState->mBallSpot.mY - _Scrm_pState->mLineToGain;
    if (distance < 0.0f) {
        isShort = 1;
        distance = -distance;
    }
    if (distance < range) {
        *pWithinRange = 1;
    }
    return isShort;
}

extern "C" int ScrmGetOffenseTeam(void)
{
    int result = 0;
    if (_Scrm_pState != 0) {
        result = _Scrm_pState->mOffenseTeam;
    }
    return result;
}

extern "C" int ScrmGetDefenseTeam(void)
{
    int result = 0;
    if (_Scrm_pState != 0) {
        result = _Scrm_pState->mOffenseTeam ^ 1;
    }
    return result;
}

extern "C" void ScrmSetOffenseTeam(int value)
{
    _Scrm_pState->mOffenseTeam = value;
}

extern "C" unsigned char ScrmGetSnapOffense(void)
{
    return _Scrm_pState->mSnapOffense;
}

extern "C" void ScrmSetSnapOffense(int value)
{
    _Scrm_pState->mSnapOffense = value;
}

extern "C" int ScrmGetSnapDefense(void)
{
    return _Scrm_pState->mSnapOffense ^ 1;
}

extern "C" void ScrmEndPlay(void)
{
    _Scrm_pState->mpRuleSet->EndPlay();
}

extern "C" int ScrmTestPlayFlag(int bit)
{
    return (_Scrm_pState->mPlayFlags & (1 << bit)) != 0;
}

extern "C" void ScrmSetPlayFlag(int bit, int on)
{
    if (on == 1) {
        _Scrm_pState->mPlayFlags |= 1 << bit;
    } else {
        _Scrm_pState->mPlayFlags &= ~(1 << bit);
    }
}

extern "C" void ScrmResetPlay(void)
{
    int i;
    int saved11 = ScrmTestPlayFlag(0x11);
    int saved15 = ScrmTestPlayFlag(0x15);
    for (i = 0; i <= 0x18; i++) {
        ScrmSetPlayFlag(i, 0);
    }
    ScrmSetPlayFlag(0x15, saved15);
    if (ScrmGetDown() == 0) {
        ScrmSetPlayFlag(0x11, saved11);
    }
    ScrmSetPlayFlag(2, 1);
    ScrmSetPlayTurnovers(0);
    _Scrm_pState->mTacklerRef = 0;
    _Scrm_pState->mTacklerInfo = 0;
    _Scrm_pState->mSnapFieldFlipped = _Scrm_pState->mFieldFlipped;
    _Scrm_pState->mSnapOffense = _Scrm_pState->mOffenseTeam;
}

extern "C" int ScrmIsFieldFlipped(void)
{
    if (_Scrm_pState != 0) {
        return _Scrm_pState->mFieldFlipped == 1;
    }
    return 0;
}

extern "C" int ScrmHasFieldFlippedInPlay(void)
{
    return _Scrm_pState->mSnapFieldFlipped != _Scrm_pState->mFieldFlipped;
}

extern "C" int ScrmClassifyPosition(FieldPoint_t *pPos, float *pOut, int skipFlags)
{
    float dist = 0.0f;
    int result = 2;
    int flags = 0;
    float ax;
    float ay;

    if (!skipFlags) {
        flags = ScrmGetBoundaryWallFlags(pPos);
    }
    ax = fabsf(pPos->mX);
    ay = fabsf(pPos->mY);
    if (ay > ScrmGetGoalLineY()) {
        result = pPos->mY > 0.0f;
        dist = ay - ScrmGetGoalLineY();
        if (ay > ScrmGetEndLineY()) {
            if (pPos->mY > 0.0f && !(flags & 4)) {
                result = 4;
                dist = ay - ScrmGetEndLineY();
            }
            if (pPos->mY <= 0.0f && !(flags & 8)) {
                result = 4;
                dist = ay - ScrmGetEndLineY();
            }
        }
        if (ax > ScrmGetSidelineX()) {
            if (pPos->mX > 0.0f && !(flags & 1)) {
                result = 4;
                dist = MAX(dist, ax - ScrmGetSidelineX());
            }
            if (pPos->mX <= 0.0f && !(flags & 2)) {
                result = 4;
                dist = MAX(dist, ax - ScrmGetSidelineX());
            }
        }
    } else if (ax > ScrmGetSidelineX()) {
        if (pPos->mX > 0.0f && !(flags & 1)) {
            result = 3;
            dist = ax - ScrmGetSidelineX();
        }
        if (pPos->mX <= 0.0f && !(flags & 2)) {
            result = 3;
            dist = ax - ScrmGetSidelineX();
        }
    }
    if (pOut) {
        *pOut = dist;
    }
    return result;
}

extern "C" void ScrmSetTackler(Object_80039F5C *p)
{
    fn_8009BD2C(p, &_Scrm_pState->mTacklerRef);
    if (p) {
        _Scrm_pState->mTacklerInfo = p->mUnknown1160.mUnknown52;
    } else {
        _Scrm_pState->mTacklerInfo = 0;
    }
}

extern "C" Object_80039F5C *ScrmGetTackler(void)
{
    return fn_8009BCE8(&_Scrm_pState->mTacklerRef);
}

extern "C" unsigned char ScrmGetTacklerInfo(void)
{
    return _Scrm_pState->mTacklerInfo;
}

extern "C" int ScrmIsNotReplay(void)
{
    if (fn_800AD9B4() == 3) {
        return 0;
    }
    return 1;
}

extern "C" Info_ScrmState *ScrmGetInfo(void)
{
    return &_Scrm_pState->mInfo;
}

extern "C" int ScrmGetTeamScore(int team)
{
    if (team == 1) {
        return _Scrm_pState->mScore1;
    }
    return _Scrm_pState->mScore0;
}

extern "C" void ScrmSetTeamScore(int team, short value)
{
    if (team == 1) {
        _Scrm_pState->mScore1 = value;
    } else {
        _Scrm_pState->mScore0 = value;
    }
}

extern "C" int ScrmGetRuleScore(int a)
{
    return _Scrm_pState->mpRuleSet->GetScore(a);
}

extern "C" void ScrmClearDriveBallPlaced(void)
{
    _Scrm_pState->mDriveBallPlaced = 0;
}

extern "C" ScrmPlayResult_t *ScrmGetPlayResult(void)
{
    return &_Scrm_pState->mPlayResult;
}

extern "C" void ScrmSetPlayResult(const ScrmPlayResult_t *p)
{
    _Scrm_pState->mPlayResult = *p;
}

static int RoundToNearestInt(float value)
{
    if (value > 0.0f) {
        return (int)(value + 0.5f);
    }
    return (int)(value - 0.5f);
}

extern "C" int ScrmGetScoreGoal(int *pValue)
{
    int result = _Scrm_pState->mpRuleSet->GetScoreType();
    *pValue = _Scrm_pState->mpRuleSet->GetScoreLimit();
    return result;
}

void ScrmRuleSet::PlaceBallForDrive(int flip)
{
    FieldPoint_t pos = { 0.0f, 0.0f };
    _Scrm_pState->mDriveBallPlaced = 1;
    if (flip) {
        pos.mY = _Scrm_pState->mDriveStartDistance - ScrmGetGoalLineY();
        ScrmSetBallSpot(pos);
        ScrmSetFirstDownLine();
    } else {
        pos.mY = ScrmGetGoalLineY() - _Scrm_pState->mDriveStartDistance;
        ScrmSetBallSpot(pos);
        ScrmSetFirstDownLine();
    }
    ScrmSetDown(1);
}

extern "C" void ScrmQuarterEnd(void)
{
}

extern "C" void ScrmSetSidelineX(float value)
{
    _Scrm_pState->mSidelineX = value;
}

extern "C" float ScrmGetSidelineX(void)
{
    return _Scrm_pState->mSidelineX;
}

extern "C" void ScrmSetGoalLineY(float value)
{
    _Scrm_pState->mGoalLineY = value;
}

extern "C" void ScrmSetFirstDownInterval(float value)
{
    _Scrm_pState->mFirstDownInterval = value;
}

extern "C" float ScrmGetGoalLineY(void)
{
    return _Scrm_pState->mGoalLineY;
}

extern "C" void ScrmSetEndLineY(float value)
{
    _Scrm_pState->mEndLineY = value;
}

extern "C" float ScrmGetEndLineY(void)
{
    return _Scrm_pState->mEndLineY;
}

extern "C" void ScrmSetSpotLimitX(float value)
{
    _Scrm_pState->mSpotLimitX = value;
}

extern "C" float ScrmGetSpotLimitX(void)
{
    return _Scrm_pState->mSpotLimitX;
}

extern "C" float ScrmGetDistanceToBounds(FieldPoint_t *pPos)
{
    return ScrmGetSidelineX() - fabsf(pPos->mX) < ScrmGetEndLineY() - fabsf(pPos->mY)
               ? ScrmGetSidelineX() - fabsf(pPos->mX)
               : ScrmGetEndLineY() - fabsf(pPos->mY);
}

extern "C" int ScrmGetWinner(void)
{
    return _Scrm_pState->mpRuleSet->GetWinner();
}

extern "C" void ScrmAwardWin(int a)
{
    _Scrm_pState->mpRuleSet->AwardWin(a);
}

extern "C" void ScrmLoadFieldDimensions(void)
{
    ScrmSetSidelineX(fn_800A32B4());
    ScrmSetGoalLineY(fn_800A32C0());
    ScrmSetEndLineY(fn_800A32CC());
    ScrmSetSpotLimitX(fn_800A32D8());
    ScrmSetFirstDownInterval(fn_800A32E4());
    ScrmCollectBoundaryWalls();
}

extern "C" int ScrmIsNearWin(int a)
{
    return _Scrm_pState->mpRuleSet->IsNearWin(a);
}

extern "C" int ScrmIsOpponentNearWin(int a)
{
    return _Scrm_pState->mpRuleSet->IsOpponentNearWin(a);
}

extern "C" int ScrmIsTimed(void)
{
    return _Scrm_pState->mpRuleSet->IsTimed();
}

extern "C" int ScrmGetGameTime(void)
{
    return _Scrm_pState->mpRuleSet->GetGameTime();
}

extern "C" int ScrmUsesBothTeams(void)
{
    return _Scrm_pState->mpRuleSet->UsesBothTeams();
}

extern "C" void ScrmPlaceBallForDrive(int a)
{
    _Scrm_pState->mpRuleSet->PlaceBallForDrive(a);
}

extern "C" unsigned int ScrmGetTeamPlayerCount(int team)
{
    MiniGameC *p = MiniGameGetCurrent();
    if (p != 0) {
        return p->vfn_04(team);
    }
    return 7;
}

extern "C" int ScrmGetActivePlayerCount(int team)
{
    MiniGameC *p = MiniGameGetCurrent();
    if (p != 0) {
        return p->vfn_05(team);
    }
    return 7;
}

extern "C" unsigned int ScrmGetRosterPlayerCount(void)
{
    MiniGameC *p = MiniGameGetCurrent();
    if (p != 0) {
        return p->vfn_06();
    }
    return 7;
}

extern "C" int ScrmAllowsAudibles(void)
{
    return _Scrm_pState->mpRuleSet->AllowsAudibles();
}

extern "C" int ScrmAllowsPrediction(void)
{
    return _Scrm_pState->mpRuleSet->AllowsPrediction();
}

extern "C" void ScrmSetDriveStartDistance(float v)
{
    _Scrm_pState->mDriveStartDistance = v;
}

extern "C" unsigned short ScrmGetDriveCount(void)
{
    return _Scrm_pState->mDriveCount;
}

extern "C" int ScrmGetGoalTotal(int a)
{
    return _Scrm_pState->mpRuleSet->GetGoalTotal(a);
}

extern "C" int ScrmGetGoalCount(int a)
{
    return _Scrm_pState->mpRuleSet->GetGoalCount(a);
}

extern "C" void ScrmSetRuleSet(ScrmRuleSet *pRule)
{
    if (pRule == 0) {
        switch (GameOptionsGet(14)) {
        case 0:
            _Scrm_pState->mpRuleSet = &_Drive_ScrimmageRules;
            break;
        case 1:
            _Scrm_pState->mpRuleSet = &_Drive_AltScrimmageRules;
            break;
        case 2:
            _Scrm_pState->mpRuleSet = &_Drive_ScrimmageRules;
            break;
        default:
            _Scrm_pState->mpRuleSet = &_Drive_ScrimmageRules;
            break;
        }
    } else {
        _Scrm_pState->mpRuleSet = pRule;
    }
}

extern "C" void ScrmResetPlaySpot(void)
{
    _Scrm_pState->mpRuleSet->ResetPlaySpot();
}

extern "C" float ScrmGetSetupDepth(int team)
{
    float limit;

    if (team == ScrmGetOffenseTeam()) {
        limit = _Scrm_pState->mOffenseDepth;
        if (ScrmGetGoalLineY() + ScrmGetBallSpot().mY < limit) {
            limit = -ScrmGetGoalLineY() + ScrmGetBallSpot().mY;
        }
        if (limit < _Scrm_pState->mOffenseMinDepth) {
            limit = _Scrm_pState->mOffenseMinDepth;
        }
    } else {
        limit = _Scrm_pState->mDefenseDepth;
        if (ScrmGetLineToGain() - ScrmGetBallSpot().mY < limit) {
            limit = ScrmGetLineToGain() - ScrmGetBallSpot().mY;
        }
        if (limit < _Scrm_pState->mDefenseMinDepth) {
            limit = _Scrm_pState->mDefenseMinDepth;
        }
    }
    return limit;
}

extern "C" void ScrmSetSetupDepth(int team, float a, float b)
{
    if (team == ScrmGetOffenseTeam()) {
        _Scrm_pState->mOffenseDepth = a;
        _Scrm_pState->mOffenseMinDepth = b;
    } else {
        _Scrm_pState->mDefenseDepth = a;
        _Scrm_pState->mDefenseMinDepth = b;
    }
}

extern "C" int ScrmGetConversionKind(void)
{
    return _Scrm_pState->mConversionKind;
}

extern "C" void ScrmSetConversionKind(int a)
{
    _Scrm_pState->mConversionKind = a;
}

extern "C" void ScrmClearConversion(void)
{
    _Scrm_pState->mConversionPlaced = 0;
    _Scrm_pState->mConversionKind = 0;
}

extern "C" void ScrmPlaceConversionBall(void)
{
    int kind = _Scrm_pState->mConversionKind;

    if (kind == 1 || kind == 2) {
        float offset;
        FieldPoint_t pos;
        Ball_t *pBall;
        Vector_80039F5C ballPos;

        if (kind == 1) {
            offset = 5.0f;
        } else {
            offset = 10.0f;
        }
        pos.mX = 0.0f;
        pos.mY = ScrmGetGoalLineY() - offset;
        ScrmSetBallSpot(pos);
        pBall = BallGetCurrent();
        BallReleaseStill(pBall, 6, 0);
        ballPos.mX = pos.mX;
        ballPos.mY = pos.mY;
        ballPos.mZ = 0.0f;
        BallSetPosition(pBall, &ballPos);
        _Scrm_pState->mConversionPlaced = 1;
    }
}

extern "C" int ScrmSnapPlayHasSlots(void)
{
    return PlayAlignHasSlots(PlayBookGetPlay(ScrmGetSnapOffense()));
}

extern "C" void ScrmStatSaveOriginal(int handle, int tag, int value, int kind)
{
    int i;
    int isNew = 1;

    _Drive_aStatEvents[_ScrmStat_iNumSaved].mKind = -1;
    for (i = 0; i < _ScrmStat_iNumSaved; i++) {
        if (_Drive_aStatEvents[i].mHandle == handle && _Drive_aStatEvents[i].mKind == kind && _Drive_aStatEvents[i].mTag == tag) {
            isNew = 0;
        }
    }
    if (isNew && _ScrmStat_iNumSaved < 0x60) {
        _Drive_aStatEvents[_ScrmStat_iNumSaved].mKind = kind;
        _Drive_aStatEvents[_ScrmStat_iNumSaved].mValue = value;
        _Drive_aStatEvents[_ScrmStat_iNumSaved].mHandle = handle;
        _Drive_aStatEvents[_ScrmStat_iNumSaved].mTag = tag;
        _ScrmStat_iNumSaved++;
        _Drive_aStatEvents[_ScrmStat_iNumSaved].mKind = -1;
    }
}

extern "C" int ScrmStatGetPlayerHandle(int id)
{
    return PlyrGet(id >> 8 & 0xFF, id >> 16 & 0xFF)->mUnknown2908;
}

extern "C" int ScrmStatGetPlayerTeamHandle(int id)
{
    return fn_800C8744(id >> 8 & 0xFF);
}

extern "C" void ScrmStatAddPlayer(int id, int tag, int value)
{
    unsigned int mode = GameModeTypeGet();
    int handle = ScrmStatGetPlayerHandle(id);
    int old;
    int result = fn_8022B414(handle, tag, &old);

    if (result == 0 || result == 0x84) {
        if (mode != 1) {
            ScrmStatSaveOriginal(handle, tag, old, 1);
        }
        if (fn_8022B580(handle, tag, value) == 0) {
            int check;
            if (fn_8022B414(handle, tag, &check) == 0) {
                ScrmStatGetPlayerTeamHandle(id);
            }
        }
    }
}

extern "C" void ScrmStatAddHandle(int handle, int tag, int value)
{
    int old;
    int result = fn_8022B7A4(handle, tag, &old);

    if (result == 0 || result == 0x84) {
        ScrmStatSaveOriginal(handle, tag, old, 0);
        if (fn_8022B8C8(handle, tag, value) == 0) {
            int check;
            fn_8022B7A4(handle, tag, &check);
        }
    }
}

extern "C" void ScrmStatAddPlayerTeam(int id, int tag, int value)
{
    ScrmStatAddHandle(ScrmStatGetPlayerTeamHandle(id), tag, value);
}

extern "C" void ScrmStatAddTeam(int team, int tag, int value)
{
    ScrmStatAddHandle(fn_800C8744(team), tag, value);
}

extern "C" void ScrmStatAddTeamPass(int id, int a, float b, float c)
{
    fn_8022BAB4(ScrmStatGetPlayerTeamHandle(id), a, (int)b, (int)c);
}

extern "C" void ScrmStatAddTeamRush(int id, float a, float b)
{
    fn_8022BD30(ScrmStatGetPlayerTeamHandle(id), (int)a, (int)b);
}

extern "C" void ScrmStatAddPassing(int id, float from, float to)
{
    int total = 0;
    int yards;

    if (to > ScrmGetGoalLineY()) {
        to = ScrmGetGoalLineY();
    }
    fn_8022B414(ScrmStatGetPlayerHandle(id), 0x61796167, &total);
    yards = (int)(to - from);
    if (yards + total > 0x7FF) {
        yards = 0x7FF - total;
    } else if (yards + total < -0x7FF) {
        yards = -0x7FF - total;
    }
    ScrmStatAddPlayer(id, 0x61796167, yards);
    // FAKEMATCH: -from + to is the same IEEE value as to - from; the spelling keeps gcse from reusing the first difference
    ScrmStatAddPlayer(id, 0x4E6C6167, (int)(-from + to));
}

extern "C" void ScrmStatAddReceiving(int id, float from, float catchY, float to, float time)
{
    int total = 0;
    int yards;
    int gain;

    if (to > ScrmGetGoalLineY()) {
        to = ScrmGetGoalLineY();
    }
    ScrmStatAddPlayer(id, 0x61636367, 1);
    fn_8022B414(ScrmStatGetPlayerHandle(id), 0x61796367, &total);
    yards = (int)(to - from);
    if (yards + total > 0x3FF) {
        yards = 0x3FF - total;
    } else if (yards + total < -0x3FF) {
        yards = -0x3FF - total;
    }
    ScrmStatAddPlayer(id, 0x61796367, yards);
    // FAKEMATCH: -from + to is the same IEEE value as to - from; the spelling keeps gcse from reusing the first difference
    gain = (int)(-from + to);
    ScrmStatAddPlayer(id, 0x4C726367, gain);
    if (catchY < ScrmGetGoalLineY()) {
        ScrmStatAddPlayer(id, 0x63796367, (int)(to - catchY));
    }
    ScrmStatAddPlayerTeam(id, 0x706F7374, gain);
    ScrmStatAddPlayerTeam(id, 0x796F7374, gain);
    ScrmStatAddPlayerTeam(id, 0x79547374, gain);
    ScrmStatAddTeamPass(id, 1, time, gain);
}

extern "C" void ScrmStatAddRushing(int id, float from, float to, float time)
{
    int total = 0;
    int gain;
    int yards;

    fn_8022B414(ScrmStatGetPlayerHandle(id), 0x61797567, &total);
    if (to < -ScrmGetGoalLineY()) {
        to = -ScrmGetGoalLineY();
    }
    gain = (int)(to - from);
    yards = gain;
    if (yards + total > 0x3FF) {
        yards = 0x3FF - total;
    } else if (yards + total < -0x3FF) {
        yards = -0x3FF - total;
    }
    ScrmStatAddPlayer(id, 0x74617567, 1);
    ScrmStatAddPlayerTeam(id, 0x61727374, 1);
    ScrmStatAddPlayer(id, 0x61797567, yards);
    ScrmStatAddPlayer(id, 0x4E6C7567, gain);
    ScrmStatAddPlayerTeam(id, 0x726F7374, gain);
    ScrmStatAddPlayerTeam(id, 0x796F7374, gain);
    ScrmStatAddPlayerTeam(id, 0x79547374, gain);
    if (gain > 19) {
        ScrmStatAddPlayer(id, 0x79327567, 1);
    }
    if (ScrmGetPlayDown() != 6) {
        DriveLogAddPlay(1, (int)from, gain, id, 0);
    }
    ScrmStatAddTeamRush(id, time, (int)(to - from));
}

extern "C" void ScrmStatAddInterceptionReturn(int id, float from, float to)
{
    int yards = (int)(to - from);

    ScrmStatAddPlayer(id, 0x79697367, yards);
    ScrmStatAddPlayer(id, 0x526C7367, yards);
    if (ScrmGetPlayDown() != 6) {
        DriveLogAddPlay(4, (int)from, yards, id, 0);
    }
}

extern "C" void ScrmStatAddPunt(int id, float from, float to, float spot, int flag)
{
    int yards;

    if (spot < -ScrmGetGoalLineY()) {
        spot = -ScrmGetGoalLineY();
    }
    to = to < -ScrmGetGoalLineY() ? -ScrmGetGoalLineY() : to;
    yards = (int)(from - spot);
    ScrmStatAddPlayer(id, 0x4E6C7067, yards);
    ScrmStatAddPlayer(id, 0x61797067, yards);
    ScrmStatAddPlayerTeam(id, 0x64507374, yards);
    if (to <= -30.0f && to > -ScrmGetGoalLineY() && flag == 0) {
        ScrmStatAddPlayer(id, 0x74707067, 1);
    }
    if (to <= -ScrmGetGoalLineY() && flag == 0) {
        ScrmStatAddPlayer(id, 0x62747067, 1);
        to = 20.0f - ScrmGetGoalLineY();
    }
    ScrmStatAddPlayer(id, 0x796E7067, (int)(from - to));
}

extern "C" void ScrmStatAddPuntReturn(int id, float from, float to)
{
    int yards;

    ScrmStatAddPlayer(id, 0x61707267, 1);
    yards = (int)(to - from);
    ScrmStatAddPlayer(id, 0x79707267, yards);
    ScrmStatAddPlayer(id, 0x4C707267, yards);
    ScrmStatAddPlayerTeam(id, 0x72707374, yards);
    ScrmStatAddPlayerTeam(id, 0x79747374, yards);
    ScrmStatAddPlayerTeam(id, 0x79547374, yards);
    if (to >= ScrmGetGoalLineY()) {
        DriveLogAddPlay(7, (int)from, yards, id, 0);
        ScrmStatAddPlayer(id, 0x74707267, 1);
        ScoringLogAddScore(7, yards, id, 0);
    }
}

extern "C" void ScrmStatAddKickReturn(int id, float from, float to)
{
    int yards;

    ScrmStatAddPlayer(id, 0x616B7267, 1);
    yards = (int)(to - from);
    ScrmStatAddPlayer(id, 0x796B7267, yards);
    ScrmStatAddPlayer(id, 0x4C6B7267, yards);
    ScrmStatAddPlayerTeam(id, 0x726B7374, yards);
    ScrmStatAddPlayerTeam(id, 0x79747374, yards);
    ScrmStatAddPlayerTeam(id, 0x79547374, yards);
    if (to >= ScrmGetGoalLineY()) {
        DriveLogAddPlay(6, (int)from, yards, id, 0);
        ScrmStatAddPlayer(id, 0x746B7267, 1);
        ScoringLogAddScore(6, yards, id, 0);
    }
}

extern "C" void ScrmStatAddAssist(int ref)
{
    int other = fn_8009BCE8(&ref)->mUnknown1044;

    if (other != 0) {
        Object_80039F5C *p = fn_8009BCE8(&other);
        if (p->mUnknown1044 == ref && other == p->mId) {
            ScrmStatAddPlayer(other, 0x61736F67, 1);
        }
    }
}

extern "C" int ScrmStatTallyPlay(unsigned char *pOut)
{
    int result;
    int carrier;
    unsigned char flips;
    int flipped;
    int kicked;
    int mode;
    int state;
    int id;
    int receiver;
    int kicker;
    float toGo;
    float startY;
    float ballY;
    float markY;
    float catchY;
    float catchX;
    float sideX;
    int caught;
    int kickTeam;
    int kickOut;
    int recovered;
    int muffed;
    int dpFlag;
    int returned;
    int rdFlag;
    int taFlag;
    unsigned short count;
    unsigned short i;
    unsigned char turnovers;
    int lateral;
    int scored;
    int zeroFlagA;
    int zeroFlagB;

    markY = 0.0f;
    startY = 0.0f;
    ballY = 0.0f;
    toGo = 0.0f;
    mode = ScrmGetPlayDown();
    flips = 0;
    id = 0;
    carrier = 0;
    receiver = 0;
    kicker = 0;
    result = 0;
    kickOut = 0;
    muffed = 0;
    dpFlag = 0;
    recovered = 0;
    flipped = 0;
    returned = 0;
    rdFlag = 0;
    taFlag = 0;
    state = 0;
    caught = 0;
    lateral = 0;
    kicked = 0;
    count = fn_800B15D4();
    scored = 0;
    catchY = 0.0f;
    catchX = 0.0f;
    sideX = 0.0f;
    zeroFlagA = 0;
    zeroFlagB = 0;
    turnovers = 0;
    kickTeam = 0xFF;

    for (i = 0; i < count; i++) {
        Record_800B15FC *pRecord = fn_800B1648(i);

        switch (pRecord->mUnknown14) {
        case 3: {
            int who = pRecord->mUnknown0;

            markY = pRecord->mUnknown10;
            fn_8009BD2C(0, &id);
            state = 0;
            ScrmStatAddPlayerTeam(who, 0x6E737374, 1);
            startY = markY;
            ballY = markY;
            if (mode != 6 && ballY > 30.0f && !DriveLogHasLongPlay()) {
                DriveLogSetLongPlay();
                ScrmStatAddLongPlay(pRecord->mUnknown4);
            }
            break;
        }
        case 30:
            turnovers++;
            flips++;
            DriveLogEndDrive();
            startY = -startY;
            markY = -markY;
            ballY = -ballY;
            catchY = -catchY;
            if (!returned) {
                flipped = 1;
            } else {
                returned = 0;
                flipped = 0;
            }
            break;
        case 4:
            id = pRecord->mUnknown0;
            state = 0x61797567;
            break;
        case 5:
            if (ScrmTestPlayFlag(13)) {
                carrier = id = pRecord->mUnknown0;
                if (!taFlag) {
                    ScrmStatAddPlayer(carrier, 0x74616167, 1);
                    ScrmStatAddPlayerTeam(id, 0x61707374, 1);
                    state = 0x61796167;
                    result = 1;
                    taFlag = 1;
                }
            }
            break;
        case 43:
        case 51:
            i = count;
        case 28:
            if (fn_8009BCE8(&pRecord->mUnknown4)) {
                receiver = pRecord->mUnknown4;
                ScrmStatAddPlayer(receiver, 0x61746467, 1);
                if (pRecord->mUnknown8) {
                    ScrmStatAddPlayerTeam(receiver, 0x74757374, 1);
                    if (pRecord->mUnknown16) {
                        ScrmStatAddPlayerTeam(receiver, 0x70647374, 1);
                    }
                }
                if (pRecord->mUnknown10 < -ScrmGetGoalLineY() && !ScrmGetDown()) {
                    ScrmStatAddPlayer(receiver, 0x61736C67, 1);
                }
                if (pRecord->mUnknown10 < startY && turnovers == 0 && mode != 0) {
                    int handled = 0;

                    if (ScrmSnapPlayHasSlots() && (fn_8009BCE8(&pRecord->mUnknown0)->mFlags & 0x10000000) &&
                        !ScrmTestPlayFlag(13)) {
                        Object_80039F5C *p = fn_8009BCE8(&receiver);

                        fn_80093C3C(1, 5, fn_8009BCE8(&receiver));
                        ReplayEventAdd(gpReplay, 0x16, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                        if (!scored) {
                            ScrmStatAddPlayer(receiver, 0x6B736C67, 1);
                            ScrmStatAddPlayerTeam(receiver, 0x6B737374, 1);
                            ScrmStatAddPlayer(pRecord->mUnknown0, 0x61736167, 1);
                            if (pRecord->mUnknown8) {
                                ScrmStatAddPlayerTeam(receiver, 0x73757374, 1);
                            }
                            scored = 1;
                            ScrmStatAddAssist(receiver);
                        }
                        handled = 1;
                        result = 1;
                        AudmonEventPostArgs(0x63, 0, ScrmGetDefenseTeam(), 0, 0);
                        SndgSpchSetPlayFlags(1);
                        ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x706F7374, (int)(pRecord->mUnknown10 - startY));
                        ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x796F7374, (int)(pRecord->mUnknown10 - startY));
                        ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x79547374, (int)(pRecord->mUnknown10 - startY));
                        if (mode != 6) {
                            DriveLogAddPlay(12, startY, pRecord->mUnknown10 - startY, id, 0);
                        }
                        state = 0;
                    }
                    if (!handled) {
                        fn_80093C3C(1, 13, fn_8009BCE8(&receiver));
                        AudmonEventPostArgs(0x63, 0, ScrmGetDefenseTeam(), 0, 0);
                        SndgSpchSetPlayFlags(2);
                        ScrmStatAddPlayer(receiver, 0x6C746467, 1);
                    }
                }
            }
        case 31:
            ballY = pRecord->mUnknown10;
            break;
        case 39:
            i = count;
        case 22:
            ballY = pRecord->mUnknown10;
            if (state == 0x61796167) {
                if (mode != 6) {
                    DriveLogAddPlay(0, startY, 0, carrier, 0);
                }
                ScrmStatAddTeamPass(carrier, 0, pRecord->mUnknownC, 0.0f);
            }
            if (state == 0x61797067 && mode != 0) {
                ScrmStatAddPunt(kicker, startY, ballY, ballY, kicked);
            }
            break;
        case 41:
        case 45:
        case 49:
            i = count;
            if (pRecord->mUnknown14 == 45) {
                carrier = pRecord->mUnknown0;
            }
        case 21:
            ScrmStatAddTeamPass(carrier, 0, pRecord->mUnknownC, 0.0f);
            state = 0;
            if (mode != 6) {
                DriveLogAddPlay(0, startY, 0, carrier, 0);
                if (dpFlag) {
                    AudmonEventPostArgs(0x63, 0, ScrmGetDefenseTeam(), 0, 0);
                }
            }
            break;
        case 24:
            if (flips == 1 && id == kicker) {
                flips = 0;
            }
            if (state == 0x61797567) {
                sideX = pRecord->mUnknownC;
            }
            break;
        case 2:
            i = count;
            break;
        case 47:
            ballY = pRecord->mUnknown10;
            i = count;
        case 6:
            ScrmStatAddPlayer(id, 0x6D636167, 1);
            ScrmStatAddPlayerTeam(id, 0x63707374, 1);
            caught = 1;
            state = 0x61796367;
            id = pRecord->mUnknown0;
            catchX = pRecord->mUnknownC;
            catchY = pRecord->mUnknown10;
            break;
        case 20:
            state = 0x79697367;
            fn_80093C3C(1, 3, fn_8009BCE8(&pRecord->mUnknown0));
            returned = 1;
            ScrmStatAddPlayer(id, 0x6E696167, 1);
            ScrmStatAddPlayerTeam(id, 0x61677374, 1);
            ScrmStatAddPlayerTeam(id, 0x69707374, 1);
            ScrmStatAddTeamPass(carrier, 0, pRecord->mUnknownC, 0.0f);
            id = pRecord->mUnknown0;
            ScrmStatAddPlayer(id, 0x6E697367, 1);
            ScrmStatAddPlayerTeam(id, 0x61747374, 1);
            ScrmStatAddPlayerTeam(id, 0x69447374, 1);
            markY = pRecord->mUnknown10;
            if (_ScrmStat_pEventCallback) {
                _ScrmStat_pEventCallback(6, ScrmStatGetPlayerHandle(id), 0);
            }
            break;
        case 18:
            if ((id & 0xFF)) {
                if (pRecord->mUnknown0 && !scored && ScrmSnapPlayHasSlots() &&
                    (fn_8009BCE8(&id)->mFlags & 0x10000000) && pRecord->mUnknown10 < startY &&
                    !ScrmTestPlayFlag(13)) {
                    recovered = 1;
                }
                if ((id & 0xFF)) {
                    switch (state) {
                    case 0x61797567:
                        if (!recovered) {
                            result = 2;
                            ScrmStatAddRushing(id, startY, pRecord->mUnknown10, sideX);
                        }
                        break;
                    case 0x61796367:
                        ScrmStatAddPassing(carrier, startY, pRecord->mUnknown10);
                        ScrmStatAddReceiving(id, startY, catchY, pRecord->mUnknown10, catchX);
                        break;
                    case 0x796B7267:
                        if (ballY < -ScrmGetGoalLineY()) {
                            ScrmStatAddPlayer(kicker, 0x62746B67, 1);
                        } else if (!zeroFlagA) {
                            ScrmStatAddKickReturn(id, markY, pRecord->mUnknown10);
                        }
                        break;
                    case 0x79707267:
                        if (mode != 0 && !lateral) {
                            ScrmStatAddPunt(kicker, startY, pRecord->mUnknown10, markY, kicked);
                            lateral = 1;
                        }
                        if (pRecord->mUnknown10 > -ScrmGetGoalLineY() && !zeroFlagA) {
                            ScrmStatAddPuntReturn(id, markY, pRecord->mUnknown10);
                        }
                        break;
                    case 0x61797067:
                    case 0x79697367:
                        break;
                    }
                    ScrmStatAddPlayer(id, 0x75667567, 1);
                    ScrmStatAddPlayerTeam(id, 0x75667374, 1);
                }
            }
            state = 0;
            markY = pRecord->mUnknown10;
            if (pRecord->mUnknown0) {
                ScrmStatAddPlayer(pRecord->mUnknown0, 0x66666C67, 1);
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x66667374, 1);
                if ((id & 0xFF) && recovered == 1) {
                    ScrmStatAddPlayer(pRecord->mUnknown0, 0x6B736C67, 1);
                    ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x6B737374, 1);
                    ScrmStatAddPlayer(id, 0x61736167, 1);
                    if (pRecord->mUnknown4) {
                        ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x73757374, 1);
                    }
                    scored = 1;
                    ScrmStatAddAssist(pRecord->mUnknown0);
                }
            }
            break;
        case 19:
            if ((id & 0xFF) && flips && flipped) {
                if (muffed) {
                    ScrmStatAddPlayer(id, 0x75667567, 1);
                    ScrmStatAddPlayerTeam(id, 0x75667374, 1);
                }
                if (!kicked) {
                    ScrmStatAddPlayerTeam(id, 0x6C667374, 1);
                    ScrmStatAddPlayerTeam(id, 0x61677374, 1);
                } else {
                    ScrmStatAddPlayerTeam(kicker, 0x61677374, 1);
                }
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x61747374, 1);
                if (flips & 1) {
                    fn_80093C3C(1, 7, fn_8009BCE8(&pRecord->mUnknown0));
                } else {
                    fn_80093C3C(1, 6, fn_8009BCE8(&pRecord->mUnknown0));
                }
            }
            kicked = 0;
            if (flips && flipped) {
                ScrmStatAddPlayer(pRecord->mUnknown0, 0x72666C67, 1);
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x72667374, 1);
                if (_ScrmStat_pEventCallback) {
                    _ScrmStat_pEventCallback(7, ScrmStatGetPlayerHandle(pRecord->mUnknown0), 0);
                }
                state = 0x79666C67;
            } else if (!muffed) {
                state = 0x79666C67;
            }
            flipped = 0;
            muffed = 0;
            id = pRecord->mUnknown0;
            markY = pRecord->mUnknown10;
            break;
        case 8:
            if (fn_8009BCE8(&id)->mIdBytes[2] != fn_8009BCE8(&pRecord->mUnknown0)->mIdBytes[2]) {
                ScrmStatAddPlayer(id, 0x75667567, 1);
                ScrmStatAddPlayerTeam(id, 0x75667374, 1);
                ScrmStatAddPlayerTeam(id, 0x6C667374, 1);
                ScrmStatAddPlayerTeam(id, 0x61677374, 1);
                ScrmStatAddPlayer(pRecord->mUnknown0, 0x72666C67, 1);
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x72667374, 1);
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x61747374, 1);
                if (_ScrmStat_pEventCallback) {
                    _ScrmStat_pEventCallback(6, ScrmStatGetPlayerHandle(pRecord->mUnknown0), 0);
                }
                state = 0x79666C67;
            } else if (state != 0x79697367 && state != 0x61796367 && state != 0x79666C67) {
                state = 0x61797567;
            }
            id = pRecord->mUnknown0;
            break;
        case 32:
            if (pRecord->mUnknown4 == 7) {
                sideX = ScrmGetSidelineX();
            } else {
                sideX = -ScrmGetSidelineX();
            }
            break;
        case 14:
            result = 3;
            state = 0;
            id = kicker = pRecord->mUnknown0;
            toGo = ScrmGetEndLineY() - pRecord->mUnknown10;
            if (startY > 30.0f && !DriveLogHasLongPlay()) {
                DriveLogSetLongPlay();
                ScrmStatAddLongPlay(fn_8009BCE8(&kicker)->mId >> 8 & 0xFF);
            }
            ScrmStatAddPlayer(kicker, 0x61666B67, 1);
            break;
        case 17:
            id = pRecord->mUnknown0;
            ScrmStatAddPlayer(id, 0x6C626C67, 1);
            kicked = 1;
            if (state == 0x61797067) {
                state = 0;
                ScrmStatAddPunt(kicker, startY, startY, startY, 1);
                ScrmStatAddPlayer(kicker, 0x6C627067, 1);
            } else {
                ScrmStatAddPlayer(kicker, 0x62666B67, 1);
            }
            break;
        case 9:
            id = kicker = pRecord->mUnknown0;
            if (mode != 0) {
                ScrmStatAddPlayer(kicker, 0x74617067, 1);
                ScrmStatAddPlayerTeam(kicker, 0x75707374, 1);
            }
            state = 0x61797067;
            result = 3;
            break;
        case 12:
            id = kicker = pRecord->mUnknown0;
            kickTeam = id >> 8 & 0xFF;
            ScrmStatAddPlayer(id, 0x6B6E6B67, 1);
            state = 1;
            break;
        case 11:
            ballY = pRecord->mUnknown10;
            if (state == 0x61797067 && mode != 0) {
                ScrmStatAddPunt(kicker, startY, ballY, ballY, kicked);
                state = 0;
            }
            break;
        case 55:
            muffed = 1;
            id = pRecord->mUnknown0;
            ballY = pRecord->mUnknown10;
            if (state == 0x61797067 && mode != 0) {
                ScrmStatAddPunt(kicker, startY, ballY, ballY, kicked);
                lateral = 1;
            }
            state = 0x79707267;
            markY = pRecord->mUnknown10;
            break;
        case 10:
            id = pRecord->mUnknown0;
            markY = pRecord->mUnknown10;
            if (zeroFlagA) {
                ballY = markY;
            }
            state = 0x79707267;
            break;
        case 13:
            id = pRecord->mUnknown0;
            markY = pRecord->mUnknown10;
            if (kickTeam == (id >> 8 & 0xFF)) {
                kickOut = 1;
            }
            state = 0x796B7267;
            break;
        case 7:
        case 15:
        case 16:
        case 25:
        case 40:
        case 42:
        case 44:
        case 46:
        case 48:
        case 50:
        case 52:
        case 53:
        case 54:
        case 56:
        case 61:
            break;
        case 33:
            ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x68717374, 1);
            break;
        case 34:
            ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x6B717374, 1);
            break;
        case 35:
            ScrmStatAddPlayer(pRecord->mUnknown0, 0x64706467, 1);
            dpFlag = 1;
            ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x64707374, 1);
            break;
        case 36: {
            Record_800B15FC *pNext = fn_800B1648(i + 1);

            if (!((pNext->mUnknown14 == 6 || pNext->mUnknown14 == 36) && pNext->mUnknown0 == pRecord->mUnknown0) &&
                !rdFlag) {
                ScrmStatAddPlayer(pRecord->mUnknown0, 0x72646367, 1);
                rdFlag = 1;
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x70447374, 1);
            }
            if (pRecord->mUnknown4 == 1) {
                AudmonEventPostArgs(0x63, 0, ScrmGetDefenseTeam(), 0, 0);
            }
            break;
        }
        case 37:
            if (!zeroFlagB && mode != 0 && turnovers == 0) {
                ScrmStatAddPlayer(pRecord->mUnknown0, 0x61706F67, 1);
            }
            break;
        case 38:
            ScrmStatAddPlayer(pRecord->mUnknown0, 0x74627567, 1);
            break;
        case 57:
            ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x6A737374, 1);
            if (pRecord->mUnknown4) {
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x6F667374, 1);
            }
            if (pRecord->mUnknown8 == 4) {
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x6A777374, 1);
            }
            break;
        case 58:
            ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x61737374, 1);
            break;
        case 59:
            ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x68647374, 1);
            break;
        case 60:
            if (!scored) {
                ScrmStatAddPlayer(pRecord->mUnknown0, 0x6B736C67, 1);
                ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x6B737374, 1);
                ScrmStatAddPlayer(pRecord->mUnknown8, 0x61736167, 1);
                if (pRecord->mUnknown4) {
                    ScrmStatAddPlayerTeam(pRecord->mUnknown0, 0x73757374, 1);
                }
                scored = 1;
            }
            break;
        }
    }

    fn_80093C3C(6, fn_8009BCE8(&id) ? fn_8009BCE8(&id)->mIdBytes[2] << 8 | fn_8009BCE8(&id)->mIdBytes[1] : 0xFF, 0);

    switch (state) {
    case 0x61797567:
        result = 2;
        ScrmStatAddRushing(id, startY, ballY, sideX);
        if (ScrmSpotGetFirstHit(&toGo)) {
            ScrmStatAddPlayer(id, 0x68797567, (int)(ballY - toGo));
        }
        if (ballY > ScrmGetGoalLineY() && mode != 6) {
            ScrmStatAddPlayer(id, 0x64747567, 1);
            ScrmStatAddPlayerTeam(id, 0x74727374, 1);
            ScoringLogAddScore(1, ballY - startY, id, 0);
            if (_ScrmStat_pEventCallback) {
                _ScrmStat_pEventCallback(1, ScrmStatGetPlayerHandle(id), 0);
            }
        }
        break;
    case 0x61796367: {
        float endY;

        ScrmStatAddPassing(carrier, startY, ballY);
        ScrmStatAddReceiving(id, startY, catchY, ballY, catchX);
        if (ballY > ScrmGetGoalLineY()) {
            endY = ScrmGetGoalLineY();
        } else {
            endY = ballY;
        }
        if (mode != 6) {
            DriveLogAddPlay(0, startY, endY - startY, carrier, id);
        }
        if ((ballY >= ScrmGetGoalLineY() || (fn_8009BCE8(&id)->mFlags & 0x800000)) && mode != 6) {
            ScrmStatAddPlayer(carrier, 0x64746167, 1);
            ScrmStatAddPlayer(id, 0x64746367, 1);
            ScrmStatAddPlayerTeam(carrier, 0x74507374, 1);
            ScoringLogAddScore(0, ScrmGetGoalLineY() - startY, carrier, id);
            if (_ScrmStat_pEventCallback) {
                _ScrmStat_pEventCallback(0, ScrmStatGetPlayerHandle(id), 0);
            }
        }
        break;
    }
    case 0x79697367:
        ScrmStatAddInterceptionReturn(id, markY, ballY);
        if (ballY > ScrmGetGoalLineY() && mode != 6) {
            if (fn_801486A0() != 3) {
                ScrmStatAddPlayer(id, 0x74697367, 1);
                ScrmStatAddPlayerTeam(id, 0x72697374, 1);
                ScrmStatAddPlayerTeam(id, 0x64647374, 1);
            }
            ScoringLogAddScore(4, ballY - markY, id, 0);
            if (_ScrmStat_pEventCallback) {
                _ScrmStat_pEventCallback(2, ScrmStatGetPlayerHandle(id), 0);
            }
        }
        break;
    case 0x796B7267:
        if (ballY < -ScrmGetGoalLineY()) {
            ScrmStatAddPlayer(kicker, 0x62746B67, 1);
        } else if (!zeroFlagA && !kickOut) {
            ScrmStatAddKickReturn(id, markY, ballY);
        }
        break;
    case 0x79707267:
        if (mode != 0 && !lateral) {
            ScrmStatAddPunt(kicker, startY, ballY, markY, kicked);
        }
        if (ballY > -ScrmGetGoalLineY() && !zeroFlagA) {
            ScrmStatAddPuntReturn(id, markY, ballY);
        }
        break;
    case 0x79666C67:
        if (flips & 1) {
            float gain = ballY - markY;
            int yards;

            if (mode != 6) {
                DriveLogAddPlay(3, markY, gain, id, 0);
            }
            yards = (int)gain;
            ScrmStatAddPlayer(id, 0x79666C67, yards);
            if (ballY > ScrmGetGoalLineY() && mode != 6) {
                ScrmStatAddPlayer(id, 0x74666C67, 1);
                ScrmStatAddPlayerTeam(id, 0x64647374, 1);
                ScoringLogAddScore(3, yards, id, 0);
                if (_ScrmStat_pEventCallback) {
                    _ScrmStat_pEventCallback(2, ScrmStatGetPlayerHandle(id), 0);
                }
            }
        } else if (ballY > ScrmGetGoalLineY() && mode != 6) {
            ScrmStatAddPlayer(id, 0x64747567, 1);
            ScrmStatAddPlayerTeam(id, 0x74727374, 1);
            ScoringLogAddScore(3, ballY - markY, id, 0);
            if (_ScrmStat_pEventCallback) {
                _ScrmStat_pEventCallback(1, ScrmStatGetPlayerHandle(id), 0);
            }
        }
        break;
    case 1:
        if (ballY < -ScrmGetGoalLineY()) {
            ScrmStatAddPlayer(kicker, 0x62746B67, 1);
        }
        break;
    }

    if (carrier) {
        if (caught == 1) {
            ScrmStatAddPlayer(carrier, 0x63636167, 1);
        } else {
            fn_8022B2CC(ScrmStatGetPlayerHandle(carrier), 0x63636167, 0);
        }
    }
    *pOut = caught;
    return result;
}

extern "C" int ScrmStatTallyConversion(void)
{
    unsigned char flag = 0;
    int reported = 0;
    int result;
    int passer;
    signed char team;
    int sameTeam;
    int carrier;
    float yards;
    int kind;
    int tackler;
    unsigned short count;
    unsigned short i;

    ScrmStatTallyPlay(&flag);
    fn_8009BD2C(0, &passer);
    team = 2;
    ScrmGetPlayDown();
    sameTeam = 0;
    carrier = 0;
    result = 0;
    yards = 0.0f;
    kind = 0;
    count = fn_800B15D4();
    tackler = 0;

    for (i = 0; i < count; i++) {
        Record_800B15FC *pRecord = fn_800B1648(i);

        switch (pRecord->mUnknown14) {
        case 3:
            yards = pRecord->mUnknown10;
            kind = 0;
            fn_8009BD2C(0, &carrier);
            break;
        case 30:
            yards = -yards;
            break;
        case 4:
            carrier = pRecord->mUnknown0;
            kind = 0x61797567;
            break;
        case 5:
            passer = carrier = pRecord->mUnknown0;
            kind = 0x61796167;
            result = 1;
            break;
        case 22:
            if (_ScrmStat_bStopAtIncomplete) {
                i = count;
            }
        case 28:
            yards = pRecord->mUnknown10;
            break;
        case 2:
            i = count;
            DriveLogEndDrive();
            break;
        case 6:
            carrier = pRecord->mUnknown0;
            kind = 0x61796367;
            break;
        case 20:
            fn_80093C3C(1, 3, fn_8009BCE8(&pRecord->mUnknown0));
            kind = 0x79697367;
            carrier = pRecord->mUnknown0;
            break;
        case 18:
            if (team == 2) {
                team = pRecord->mUnknown0Bytes[2] ^ 1;
            }
            break;
        case 19:
            carrier = pRecord->mUnknown0;
            kind = 0x79666C67;
            sameTeam = team == (carrier >> 8 & 0xFF);
            break;
        case 8:
            carrier = pRecord->mUnknown0;
            if (kind != 0x79697367 && kind != 0x61796367 && kind != 0x79666C67) {
                kind = 0x61797567;
            }
            break;
        case 9:
        case 14:
            tackler = pRecord->mUnknown0;
            ScrmStatAddPlayer(tackler, 0x61656B67, 1);
            result = 3;
        case 21:
        case 55:
            kind = 0;
            break;
        case 15:
            ScrmStatAddPlayer(tackler, 0x6D656B67, 1);
            reported = 1;
            ScoringLogSetConversion(5, 1, tackler, 0);
            break;
        case 16:
            ScoringLogSetConversion(10, 1, tackler, 0);
            reported = 1;
            break;
        case 17:
            carrier = pRecord->mUnknown0;
            ScrmStatAddPlayer(carrier, 0x6C626C67, 1);
            if (kind == 0x61797067) {
                ScrmStatAddPlayer(tackler, 0x6C627067, 1);
            } else {
                ScrmStatAddPlayer(tackler, 0x62656B67, 1);
            }
            break;
        }
    }

    fn_80093C3C(6,
                fn_8009BCE8(&carrier) ? fn_8009BCE8(&carrier)->mIdBytes[2] << 8 |
                                            fn_8009BCE8(&carrier)->mIdBytes[1]
                                      : 0xFF,
                0);

    switch (kind) {
    case 0x61797567:
        result = 2;
        if (yards >= ScrmGetGoalLineY()) {
            ScrmStatAddPlayer(carrier, 0x70327567, 1);
            reported = 1;
            ScoringLogSetConversion(1, 0, carrier, 0);
        }
        break;
    case 0x61796367:
        if (yards >= ScrmGetGoalLineY() || (fn_8009BCE8(&carrier)->mFlags & 0x800000)) {
            ScrmStatAddPlayer(carrier, 0x70326367, 1);
            reported = 1;
            ScoringLogSetConversion(0, 0, passer, carrier);
        }
        break;
    case 0x79666C67:
        if (sameTeam && yards >= ScrmGetGoalLineY()) {
            ScrmStatAddPlayer(carrier, 0x70327567, 1);
            reported = 1;
            ScoringLogSetConversion(1, 0, carrier, 0);
        }
        break;
    case 0x79697367:
    case 0x796B7267:
    case 0x79707267:
        break;
    }

    if (!reported) {
        ScoringLogSetConversion(11, 0, carrier, 0);
    }

    if (_ScrmStat_pEventCallback) {
        int mode = ScrmGetConversionKind();
        int event = 11;
        int number = ScrmStatGetPlayerHandle(carrier);

        if (mode == 1) {
            event = 3;
        } else if (mode == 2) {
            event = 4;
        }
        _ScrmStat_pEventCallback(event, number, reported);
    }
    return result;
}

extern "C" void ScrmStatTallyTeamPlay(ScrmPlayResult_t *pResult, int kind, unsigned char flag)
{
    int offense;
    int defense;
    float spot;
    unsigned int down;
    int toGo;
    int gained;

    fn_800B2314();
    offense = ScrmGetSnapOffense();
    defense = ScrmGetSnapDefense();
    if (pResult->mUnknown04 != 6) {
        spot = pResult->mUnknown08.mY;
    } else {
        spot = ScrmGetGoalLineY();
    }
    down = ScrmGetPlayDown();
    toGo = (int)(ScrmGetLineToGain() - ScrmGetPlayStartSpot().mY);
    gained = (int)(spot - ScrmGetPlayStartSpot().mY);

    if (kind == 1 || kind == 2) {
        switch (down) {
        case 1:
            ScrmStatAddTeam(offense, 0x6C317374, 1);
            if (kind == 1) {
                ScrmStatAddTeam(offense, 0x70317374, 1);
            } else if (kind == 2) {
                ScrmStatAddTeam(offense, 0x72317374, 1);
            }
            ScrmStatAddTeam(offense, 0x79317374, gained);
            break;
        case 2:
            if (kind == 1) {
                ScrmStatAddTeam(offense, 0x70327374, 1);
            } else if (kind == 2) {
                ScrmStatAddTeam(offense, 0x72327374, 1);
            }
            break;
        case 3:
            ScrmStatAddTeam(offense, 0x64337374, 1);
            if (toGo <= 9) {
                if (toGo <= 3) {
                    ScrmStatAddTeam(offense, 0x79333374, 1);
                } else {
                    ScrmStatAddTeam(offense, 0x79343374, 1);
                }
            } else {
                ScrmStatAddTeam(offense, 0x79313374, 1);
            }
            if (kind == 1) {
                ScrmStatAddTeam(offense, 0x70337374, 1);
            } else if (kind == 2) {
                ScrmStatAddTeam(offense, 0x72337374, 1);
            }
            break;
        case 4:
            ScrmStatAddTeam(offense, 0x64347374, 1);
            if (kind == 1) {
                ScrmStatAddTeam(offense, 0x70347374, 1);
            } else if (kind == 2) {
                ScrmStatAddTeam(offense, 0x72347374, 1);
            }
            break;
        }

        if ((pResult->mUnknown04 == 1 || pResult->mUnknown04 == 6) && !(pResult->mUnknown18 & 4) &&
            (ScrmGetPlayTurnovers() & 1) == 0) {
            switch (down) {
            case 1:
            case 2:
                break;
            case 3:
                ScrmStatAddTeam(offense, 0x63337374, 1);
                if (toGo <= 9) {
                    if (toGo <= 3) {
                        ScrmStatAddTeam(offense, 0x63333374, 1);
                    } else {
                        ScrmStatAddTeam(offense, 0x63343374, 1);
                    }
                } else {
                    ScrmStatAddTeam(offense, 0x63313374, 1);
                }
                break;
            case 4:
                ScrmStatAddTeam(offense, 0x63347374, 1);
                break;
            }
            if (down >= 1 && down <= 5 && pResult->mUnknown04 != 6) {
                ScrmStatAddTeam(offense, 0x64317374, 1);
                if (!flag) {
                    ScrmStatAddTeam(offense, 0x66727374, 1);
                }
            }
        }

        if (down == 6 && kind != 3) {
            ScrmStatAddTeam(offense, 0x61327374, 1);
            if (pResult->mUnknown1D == 2) {
                ScrmStatAddTeam(offense, 0x63327374, 1);
            }
        }

        if ((pResult->mUnknown18 & 0x800) && _ScrmStat_pEventCallback) {
            _ScrmStat_pEventCallback(8, 0x7FFF, 0);
        }

        if (PlayBookGetPlay((unsigned char)defense)->mUnknown14 == 31) {
            ScrmStatAddTeam(defense, 0x7A627374, 1);
        }
    }

    if (pResult->mUnknown1D == -2) {
        ScrmStatAddTeam(ScrmGetDefenseTeam(), 0x74737374, 1);
        if (pResult->mUnknown00 == 0) {
            ScoringLogAddScore(9, 0, (ScrmGetDefenseTeam() & 0xFF) << 8 | 1, 0);
            if (_ScrmStat_pEventCallback) {
                _ScrmStat_pEventCallback(5, 0x7FFF, 0);
            }
        } else {
            ScoringLogAddScore(9, 0, pResult->mUnknown00, 0);
            if (_ScrmStat_pEventCallback) {
                _ScrmStat_pEventCallback(5, ScrmStatGetPlayerHandle(pResult->mUnknown00), 0);
            }
        }
        DriveLogEndDrive();
    }
}

extern "C" void ScrmStatPlayHook(void)
{
}

extern "C" void ScrmStatEndPlay(ScrmPlayResult_t *pResult)
{
    unsigned char flag = 0;
    int kind;

    _Drive_pPlayResult = pResult;
    ScrmStatBeginTally();
    ScrmStatPlayHook();
    _ScrmStat_bStopAtIncomplete = 0;
    if (ScrmGetPlayDown() != 6) {
        kind = ScrmStatTallyPlay(&flag);
    } else {
        kind = ScrmStatTallyConversion();
    }
    ScrmStatTallyTeamPlay(pResult, kind, flag);
}

extern "C" void ScrmStatAddPossessionTime(int value)
{
    ScrmStatAddTeam(ScrmGetOffenseTeam(), 0x74707374, value);
}

extern "C" void ScrmStatAddDriveStart(unsigned short team, short value)
{
    if (team <= 1) {
        ScrmStatAddTeam(team, 0x73707374, 1);
        ScrmStatAddTeam(team, 0x66737374, value);
    }
}

extern "C" void ScrmStatAddLongPlay(unsigned short team)
{
    if (team <= 1) {
        ScrmStatAddTeam(team, 0x7A6F7374, 1);
        ScrmStatAddTeam(team ^ 1, 0x72647374, 1);
    }
}

extern "C" void ScrmStatAddLongScore(unsigned short team, int play)
{
    if (team <= 1) {
        switch (play) {
        case 0:
        case 1:
            ScrmStatAddTeam(team, 0x746F7374, 1);
            ScrmStatAddTeam(team ^ 1, 0x74647374, 1);
            break;
        case 5:
            ScrmStatAddTeam(team, 0x666F7374, 1);
            ScrmStatAddTeam(team ^ 1, 0x66647374, 1);
            break;
        }
    }
}

extern "C" void ScrmStatAddPenalty(unsigned short team, short yards, int handle)
{
    if (team <= 1) {
        short spot;
        int mode;

        ScrmStatAddTeam(team, 0x65707374, 1);
        ScrmStatAddTeam(team, 0x79507374, yards);
        if (team == (unsigned short)ScrmGetOffenseTeam() && (unsigned short)ScrmGetSnapOffense() == team) {
            yards = -yards;
        }
        spot = (short)ScrmGetBallSpot().mY;
        mode = ScrmGetDown();
        if (mode != 0 && mode != 6) {
            DriveLogAddPlay(8, spot, yards, handle, 0);
        }
    }
}

extern "C" void ScrmStatBeginTally(void)
{
    _Drive_aStatEvents[0].mKind = -1;
    _ScrmStat_iNumSaved = 0;
    if (GameModeTypeGet() != 1) {
        int home;
        int away;

        fn_800C8704(&home, &away);
        _ScrmStat_aTeamBaseline[0].mTp = 0;
        _ScrmStat_aTeamBaseline[0].mSp = 0;
        _ScrmStat_aTeamBaseline[0].mFs = 0;
        _ScrmStat_aTeamBaseline[1].mTp = 0;
        _ScrmStat_aTeamBaseline[1].mSp = 0;
        _ScrmStat_aTeamBaseline[1].mFs = 0;
        fn_8022B7A4(home, 0x74707374, &_ScrmStat_aTeamBaseline[0].mTp);
        fn_8022B7A4(home, 0x73707374, &_ScrmStat_aTeamBaseline[0].mSp);
        fn_8022B7A4(home, 0x66737374, &_ScrmStat_aTeamBaseline[0].mFs);
        fn_8022B7A4(away, 0x74707374, &_ScrmStat_aTeamBaseline[1].mTp);
        fn_8022B7A4(away, 0x73707374, &_ScrmStat_aTeamBaseline[1].mSp);
        fn_8022B7A4(away, 0x66737374, &_ScrmStat_aTeamBaseline[1].mFs);
    }
}

extern "C" void ScrmStatAddTeamStyleGain(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x50747374, value);
}

extern "C" void ScrmStatAddTeamStylePoints(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x62737374, value);
}

extern "C" void ScrmStatAddTeamPitches(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x7A707374, value);
    ScrmStatAddTeam(team, 0x4F707374, value);
}

extern "C" void ScrmStatAddTeamStylePass(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x70737374, value);
}

extern "C" void ScrmStatAddTeamVariantCatch(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x63757374, value);
}

extern "C" void ScrmStatAddTeamWp(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x70777374, value);
}

extern "C" void ScrmStatAddTeamSs(unsigned short team, int value, int also)
{
    if (also) {
        ScrmStatAddTeam(team, 0x73327374, value);
    }
    ScrmStatAddTeam(team, 0x73737374, value);
}

extern "C" void ScrmStatAddTeamSd(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x64737374, value);
}

extern "C" void ScrmStatAddTeamSh(unsigned short team, int value, int also)
{
    if (also) {
        ScrmStatAddTeam(team, 0x68327374, value);
    }
    ScrmStatAddTeam(team, 0x68737374, value);
}

extern "C" void ScrmStatAddTeamWh(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x68777374, value);
}

extern "C" void ScrmStatAddTeamStylePitch(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x69737374, value);
}

extern "C" void ScrmStatAddTeamQbStopStreak(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x53637374, value);
}

extern "C" void ScrmStatAddTeamUserQbStopStreak(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x55637374, value);
}

extern "C" void ScrmStatAddTeamVt(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x74767374, value);
}

extern "C" void ScrmStatAddTeamCatchStreak(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x43637374, value);
}

extern "C" void ScrmStatAddTeamOg(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x676F7374, value);
}

extern "C" void ScrmStatAddTeamMoveScore(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x74537374, value);
}

extern "C" void ScrmStatAddTeamStyleCatchStreak(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x43737374, value);
}

extern "C" void ScrmStatAddTeamSv(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x76737374, value);
}

extern "C" void ScrmStatAddTeamWt(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x74777374, value);
}

extern "C" void ScrmStatAddTeamPitchChain(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x50637374, value);
}

extern "C" void ScrmStatAddTeamInterceptMove(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x69757374, value);
}

extern "C" void ScrmStatAddTeamStyleCatch(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x63777374, value);
}

extern "C" void ScrmStatAddTeamNinjaCatch(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x77777374, value);
}

extern "C" void ScrmStatAddHotspotCapture(int id, int value)
{
    ScrmStatAddPlayerTeam(id, 0x73687374, value);
}

extern "C" void ScrmStatAddTeamStrip(int team, int value)
{
    ScrmStatAddTeam(team, 0x6C627374, value);
}

extern "C" void ScrmStatAddTeamGiveaway(unsigned short team, int value)
{
    ScrmStatAddTeam(team, 0x61677374, value);
}

extern "C" void ScrmStatSetEventCallback(void (*pCallback)(int kind, int a, int b))
{
    _ScrmStat_pEventCallback = pCallback;
}
