/* Runs each play from huddle to whistle: sends players to the huddle and lines them up, decides when the
   ball can be snapped and snaps it, watches the ball carrier for touchdowns, tackles and line crossings, and
   tracks the forward-progress spot where the ball is marked. */

#include <math.h>
#include "game/StyleTracker.h"
#include "game/PreSnapPhase.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Challenge.h"
#include "game/ScrmPlayResult.h"
#include "game/Point2.h"
#include "game/Record_8011F4F8.h"
#include "game/Record_8011F518.h"
#include "game/Record_800B15FC.h"
#include "game/ReplayEvent.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/PlayBookGetPlay.h"
#include "game/ScrmGetBallSpot.h"
#include "game/ScrmGetTeamPlayerCount.h"
#include <string.h>
#include "game/SyncRandGetRange.h"
#include "game/PlayAlign.h"
#include "game/PlaySet.h"
#include "game/fn_800B65A0.h"
#include "game/fn_8009D990.h"
#include "game/Possession.h"
#include "game/Info_ScrmState.h"

/* Player block at +336 as written after HuddleGetSpot: the point and facing it
   returned and two flag bytes. */
struct ScrmHuddleSpot_t {
    char mUnknown0[8];
    FieldPoint_t mPoint;
    int mFacing;
    char mUnknown20[28];
    unsigned char mUnknown48;
    char mUnknown49[1];
    unsigned char mUnknown50;
};

/* Player block at +336 as read for the states checked by ScrmUpdateBallCarrier. */
struct ScrmCatchState_t {
    char mUnknown0[8];
    int mUnknown8;
    char mUnknown12[7];
    unsigned char mUnknown19;
};

extern "C" {
extern float gPlyrMoveFwdSpeed;

int ChallengeHasGoalType(Challenge_t *pRecord, int a, int b);
int ChallengeIsActive(void);
int ReplayHandleCommand(Type_803EA368 *p, int msg, int value);
void PlyrMgrStepStates(void);
Object_80039F5C *PlyrFindByRole(int team, int a, unsigned char n);
Object_80039F5C *PlyrFindNearest(Vector_80039F5C *pPos, float *pOut, int team);
void PlyrMgrResetAll(void);
void DivotRestartRecords(void);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009D888(int index, int value);
int GameClockIsTimerRunning(int index);
void DefCoverStartPlay(void);
void DefPredPostAudio(void);
int GamebreakerIsCutscenePlaying(void);
void fn_800A8F08(void);
int fn_800A937C(void);
int fn_800A9680(void);
void fn_800AD910(int a, float b);
void HotRtClearTeam(int team);
int fn_800B1200(void);
void fn_800B14E4(void);
void fn_800B2630(void);
void fn_800B6C98(void);
void fn_800B82AC(int team);
int fn_800BA6F8(void);
void fn_800C9FC0(void);
void fn_800CA3C4(void);
void PlayerMoveResetAll(void);
void PlayerActionAnimResetSteerFrames(void);
void HuddleGetSpot(FieldPoint_t *pOut, int *pFacing, Object_80039F5C *p, int value);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FAD2C(void);
void fn_800FAECC(int a);
void fn_800FF6D8(Object_80039F5C *p);
void fn_8010BEA4(void);
void fn_8011875C(void);
void fn_8011DF90(void);
void fn_8011E068(void);
void fn_8011F3A8(void);
void fn_8011F574(void);
void fn_80120618(void);
void BallPrimeKickUp(Ball_t *pBall);
int BallStateGet(Ball_t *pBall, int *pOut);
int CamGameGetCurrentSlot(void);
GameCamera_t *CamGameGetCamera(int index);
void CamGameSetModeAll(int a);
int fn_801486A0(void);
void PlyrStarSetShown(int a, int b);
void PlayAlignIssueTeamRoutes(PlayBookFormation_t *pObject, PlayBookPlay_t *pRecord, int team, int a);
int PlayAlignIsPlayType11To18(PlayBookPlay_t *pRecord);
PlayBookFormation_t *PlayBookGetFormation(int team);
void PlayTrackUpdateSummary(void);
void ClockRuleSnap(void);
void DriveLogUpdateTeam(void);
void PenaltyCheckOffside(void);
int ScrmGetDown(void);
int ScrmGetOffenseTeam(void);
int ScrmGetDefenseTeam(void);
int ScrmClassifyPosition(void *pPos, float *pOut, int a);
int ScrmGetTeamScore(int team);
float ScrmGetSidelineX(void);
float ScrmGetGoalLineY(void);
void BannerClear(int index);
void HudHidePressPrompt(int team);
void CamFreeClearVelocity(GameCamera_t *pCamera);
void AudmonEventPostId(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
int GamebreakerGetReadyType(int team);
int fn_800A8444(int team);
int GamebreakerGetSavedState(int team);
void fn_800B1698(Object_80039F5C *p, Object_80039F5C *pOther);
int PlayerMoveGetKind(Object_80039F5C *p);
void fn_8011DF90(void);
int fn_8011F1CC(void);
int fn_8011F2C4(void);
void PassIconsHide(void);
void PassIconsClearReplayFlag(void);
void PossTryJarBall(Object_80039F5C *p);
void PossLogBallResult(Object_80039F5C *p);
void ScrmChangePossession(int a);
void ScrmEndPlay(void);
int ScrmTestPlayFlag(int bit);
void ScrmSetPlayFlag(int bit, int on);
void ScrmSetTackler(Object_80039F5C *p);
Object_80039F5C *ScrmGetTackler(void);
int ScrmGetScoreGoal(unsigned int *pValue);
void ScrmStatAddTeamVt(unsigned short team, int value);
void ScrmStatAddTeamOg(unsigned short team, int value);
void ScrmStatAddTeamMoveScore(unsigned short team, int value);
void ScrmStatAddTeamSv(unsigned short team, int value);
void ScrmStatAddTeamWt(unsigned short team, int value);
int ScrmCarrierInEndZone(Object_80039F5C *p, Vector_80039F5C *pPos);
float ScrmSpotGetLine(void);
int MathAngleDiff(int a, int b);

void ScrmPlayerToHuddle(Object_80039F5C *p);
void ScrmPlayerSendLineUp(Object_80039F5C *p);
void ScrmTeamSendLineUp(int team);
void ScrmLogSnap(void);
int ScrmGetSnapFlag(Object_80039F5C *p);
void ScrmSnapBall(void);
int ScrmOffenseIsSet(void);
void ScrmSpotReset(void);
void ScrmSpotMark(void);
}

extern "C" void ScrmAlignTeam(int team)
{
    PlayAlignTeam(PlayBookGetFormation(team), team, gPlayAlignNormSet);
    ScrmTeamSendLineUp(team);
    PlyrStarSetShown(1, 1);
}

extern "C" void ScrmPlayerToHuddle(Object_80039F5C *p)
{
    Message_800F01CC message;
    Message_800F01CC ballMessage;

    memset(&message, 0, 4);
    memset(&ballMessage, 0, 4);
    message.mId = p->mIdBytes[2] == ScrmGetOffenseTeam() ? 13 : 14;
    p->mFlags &= ~0x40000;
    ballMessage.mId = 49;
    if (BallFindHeldBy(p) != 0) {
        if (BallGetCurrentHolder() == p) {
            fn_800F053C(0, p->mpState, &ballMessage, p);
            fn_800F03D8(0, p->mpState, &message, p);
        } else {
            BallReleaseStill(BallFindHeldBy(p), 5, 0);
        }
    } else {
        fn_800F053C(0, p->mpState, &message, p);
    }
}

extern "C" void ScrmTeamToHuddle(int team)
{
    unsigned char i;
    unsigned int count;

    if (ScrmGetDown() != 0 || fn_800BA6F8() != 0) {
        count = ScrmGetActivePlayerCount(team);
        for (i = 0; i < count; i++) {
            Object_80039F5C *p = PlyrGet(team, i);
            ScrmPlayerToHuddle(p);
            p->mFlags |= 0x10;
        }
    }
    fn_8011DF90();
}

extern "C" int ScrmIsHuddleFormed(void)
{
    int result = 1;

    if (ScrmGetDown() != 0) {
        int team = ScrmGetOffenseTeam();
        unsigned char i;
        unsigned int count = ScrmGetActivePlayerCount(team);

        for (i = 0; i < count; i++) {
            if ((PlyrGet(team, i)->mFlags & 0x40000) == 0) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

extern "C" void ScrmTeamPlaceInHuddle(int team)
{
    unsigned char i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        FieldPoint_t point;
        int facing;
        ScrmHuddleSpot_t *pState;

        switch (p->mpState->mId) {
        case 13:
        case 14:
            HuddleGetSpot(&point, &facing, p, 1);
            pState = (ScrmHuddleSpot_t *)&p->mUnknown336;
            pState->mPoint.mX = point.mX;
            pState->mPoint.mY = point.mY;
            pState->mFacing = facing;
            pState->mUnknown48 = 0;
            pState->mUnknown50 = 1;
            fn_800FF6D8(p);
            break;
        default:
            if (BallFindHeldBy(p) != 0 && BallGetCurrentHolder() == p) {
                BallReleaseStill(BallFindHeldBy(p), 5, 0);
            }
            fn_800EFE60(0, p->mpState, p);
            ScrmPlayerToHuddle(p);
            HuddleGetSpot(&point, &facing, p, 1);
            pState = (ScrmHuddleSpot_t *)&p->mUnknown336;
            pState->mPoint.mX = point.mX;
            pState->mPoint.mY = point.mY;
            pState->mFacing = facing;
            pState->mUnknown48 = 0;
            pState->mUnknown50 = 1;
            fn_800FF6D8(p);
            break;
        }
        p->mFlags |= 0x40000;
    }
}

extern "C" void ScrmPlayerSendLineUp(Object_80039F5C *p)
{
    if (fn_801486A0() != 0 && fn_801486A0() != 1) {
        if (ScrmGetOffenseTeam() == (p->mId >> 8 & 0xFF)) {
            if ((p->mId >> 16 & 0xFF) == 0) {
                Message_800F01CC message;

                memset(&message, 0, 4);
                message.mId = 70;
                fn_800F03D8(0, p->mpState, &message, p);
            } else {
                Message_800F01CC message;

                memset(&message, 0, 4);
                message.mId = 69;
                fn_800F03D8(0, p->mpState, &message, p);
            }
        } else {
            Message_800F01CC message;

            memset(&message, 0, 4);
            message.mId = 42;
            fn_800F03D8(0, p->mpState, &message, p);
        }
    }
}

extern "C" void ScrmTeamSendLineUp(int team)
{
    unsigned char i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        ScrmPlayerSendLineUp(PlyrGet(team, i));
    }
}

extern "C" void ScrmLogSnap(void)
{
    int team = ScrmGetOffenseTeam();
    FieldPoint_t pos;
    Record_800B15FC *pRecord;
    Object_80039F5C *p;

    pos = ScrmGetBallSpot();
    pRecord = fn_800B15FC();
    pRecord->mUnknown14 = 3;
    pRecord->mUnknownC = pos.mX;
    pRecord->mUnknown10 = pos.mY;
    pRecord->mUnknown4 = team;
    if (ScrmGetDown() != 0) {
        fn_8009BD2C(PlyrFindByRole(team, 7, 0), &pRecord->mUnknown0);
        if (pRecord->mUnknown0 == 0) {
            fn_8009BD2C(PlyrFindByRole(team, 24, 0), &pRecord->mUnknown0);
        }
    }
    p = fn_8009BCE8(&pRecord->mUnknown0);
    if (p != 0) {
        AudmonEventPostArgs(27, &p->mMotion.mPos, p->mpState->mUnknown2 == 8, 0, 0);
    }
    fn_800B1508();
}

extern "C" int ScrmGetSnapFlag(Object_80039F5C *p)
{
    return 1;
}

extern "C" void ScrmSnapBall(void)
{
    FieldPoint_t pos;

    pos = ScrmGetBallSpot();
    if (ScrmGetDown() != 0) {
        Message_800F01CC message;
        Ball_t *pBall = BallGetCurrent();
        Vector_80039F5C ballPos;
        Object_80039F5C *pCarrier;
        Object_80039F5C *pPasser;
        int defense;
        unsigned char team;

        BallGetPosition(pBall, &ballPos);
        pCarrier = PlyrFindNearest(&ballPos, 0, ScrmGetOffenseTeam());
        BallGiveToPlayer(pBall, pCarrier);
        pPasser = PlaySetGetKeyPlayer(PlayBookGetFormation(ScrmGetOffenseTeam()));
        if (pCarrier->mMotion.mPos.mY - pPasser->mMotion.mPos.mY < 2.5f) {
            memset(&message, 0, 4);
            message.mId = 26;
            message.mUnknown1[0] = pPasser->mIdBytes[1];
            message.mUnknown1[1] = 14;
            message.mUnknown1[2] = 0;
            fn_800F00D4(0, pCarrier->mpState, &message, pCarrier);
        } else {
            memset(&message, 0, 4);
            message.mId = 25;
            message.mUnknown1[0] = pPasser->mIdBytes[1];
            message.mUnknown1[1] = 8;
            fn_800F00D4(0, pCarrier->mpState, &message, pCarrier);
        }
        memset(&message, 0, 4);
        message.mId = 56;
        message.mUnknown1[0] = ScrmGetSnapFlag(pCarrier);
        fn_800F00D4(0, pPasser->mpState, &message, pPasser);

        defense = ScrmGetDefenseTeam();
        for (team = 0; team < 2; team++) {
            unsigned char i;
            unsigned int count = ScrmGetActivePlayerCount(team);

            for (i = 0; i < count; i++) {
                Object_80039F5C *p = PlyrGet(team, i);

                if (p != pCarrier && p != pPasser && p->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.1f &&
                    (p->mIdBytes[2] == defense || fabsf(pos.mY - p->mMotion.mPos.mY) < 2.0f ||
                     fabsf(pos.mX - p->mMotion.mPos.mX) > 6.0f)) {
                    float delay = 0.025098039f;

                    delay += SyncRandGetRange(0, 8) * 0.01f;
                    if (p->mIdBytes[2] == defense) {
                        delay += 0.075f;
                    } else {
                        delay += 0.025f;
                    }
                    memset(&message, 0, 4);
                    message.mId = 51;
                    message.mUnknown1[0] = (int)(delay * 32.0f);
                    fn_800F00D4(0, p->mpState, &message, p);
                }
            }
        }
    }
}

extern "C" void ScrmStartPlay(void)
{
    int team = ScrmGetOffenseTeam();
    unsigned short i = 0;
    int other = ScrmGetDefenseTeam();
    Vector_80039F5C ballPos;
    unsigned int count;
    int side;

    fn_8011F574();
    PlayerMoveResetAll();
    BallGetPosition(BallGetCurrent(), &ballPos);
    PlyrMgrResetAll();
    BannerClear(1);
    BannerClear(2);
    BannerClear(0);
    HudHidePressPrompt(ScrmGetOffenseTeam());
    HudHidePressPrompt(ScrmGetDefenseTeam());
    fn_800B14E4();
    DivotRestartRecords();
    AudmonEventClear();
    fn_800AD910(3, 0.0f);
    fn_8011F3A8();
    BallSetCurrentTarget(0);
    DefCoverStartPlay();
    fn_8011875C();
    fn_800FAD2C();
    PlayTrackUpdateSummary();
    fn_800FAECC(1);
    PlayAlignIssueTeamRoutes(PlayBookGetFormation(team), PlayBookGetPlay(team), team, 0);
    PlayAlignIssueTeamRoutes(PlayBookGetFormation(other), PlayBookGetPlay(other), other, 0);

    count = ScrmGetActivePlayerCount(team);
    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        unsigned char j;

        for (j = 0; j < 10; j++) {
            if (p->mQueue[j].mId == 18) {
                p->mFlags |= 0x10000000;
                break;
            }
        }
    }

    HotRtClearTeam(0);
    HotRtClearTeam(1);
    fn_800B6C98();
    ClockRuleSnap();
    ScrmSnapBall();
    fn_8011E068();
    PlyrMgrStepStates();
    ReplayHandleCommand(gpReplay, 1, 0);
    if (fn_800A937C() == 0 && fn_800A9680() == 0) {
        ReplayHandleCommand(gpReplay, 2, 0);
        ReplayEventAdd(gpReplay, 2, 0, &ballPos, 0);
    }
    ScrmLogSnap();
    fn_80120618();
    fn_800C9FC0();
    fn_800CA3C4();
    if (ChallengeIsActive() != 0 && ChalGetCurrent()->mUnknown1A4 != 0 && GameClockIsTimerRunning(4) == 0) {
        fn_8009D888(4, 0);
    }
    fn_800B2630();
    PenaltyCheckOffside();
    DriveLogUpdateTeam();

    side = ScrmGetOffenseTeam();
    BallPrimeKickUp(BallGetCurrent());
    fn_8010BEA4();
    PlayerActionAnimResetSteerFrames();
    if (fn_800B65A0(side) != 0xFF && ScrmGetDown() != 0) {
        GameCamera_t *pCamera = CamGameGetCamera(CamGameGetCurrentSlot());
        PlayBookPlay_t *pRecord = PlayBookGetPlay(side);

        if (PlayAlignIsPlayType11To18(pRecord) == 0 && pRecord->mUnknown14 != 4 && pRecord->mUnknown14 != 2) {
            CamGameSetModeAll(2);
            CamFreeClearVelocity(pCamera);
        }
    }
    fn_800B82AC(ScrmGetDefenseTeam());
    fn_800A8F08();
    DefPredPostAudio();
}

extern "C" int ScrmCanSnap(void)
{
    bool allowed = true;
    int mode = fn_801486A0();
    int result;

    switch (mode) {
    case 2:
    case 3:
        allowed = false;
        break;
    }
    result = 0;
    if (fn_800B65A0(ScrmGetOffenseTeam()) != 0xFF) {
        if (ScrmGetPlayResult()->mUnknown1D == -2 || BallStateGet(BallGetCurrent(), 0) == 6 || !allowed) {
            if (ScrmOffenseIsSet() != 0) {
                result = 1;
            }
        }
    } else if (ScrmGetPlayResult()->mUnknown1D == -2 || BallStateGet(BallGetCurrent(), 0) == 6 || !allowed) {
        Challenge_t *pRecord = ChalGetCurrent();

        if (ChallengeIsActive() != 0 && pRecord->mUnknown1A4 != 0 && ChallengeHasGoalType(pRecord, 55, 0) != 0 &&
            ScrmGetTeamScore(0) < ScrmGetTeamScore(1)) {
            result = 1;
        }
        if (result == 0 && (short)fn_8009D990(0) <= (short)lbl_803EABA4->fn_800C02E0() && fn_800B1200() != 0 &&
            ScrmOffenseIsSet() != 0) {
            result = 1;
        }
    }
    if (lbl_803EABA4->fn_800C0414() == 1 && fn_8009D990(0) > fn_8009D990(1) &&
        ScrmGetTeamScore(ScrmGetOffenseTeam()) > ScrmGetTeamScore(ScrmGetDefenseTeam())) {
        result = 0;
    }
    if (GamebreakerIsCutscenePlaying() == 1 || fn_800A937C() != 0) {
        result = 0;
    }
    return result;
}

extern "C" int ScrmOffenseIsSet(void)
{
    int team = ScrmGetOffenseTeam();
    int busy = 0;
    unsigned short moving = 0;
    int blocked = 0;
    unsigned short i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);

        if (p->mFlags & 0x40000) {
            continue;
        }
        switch (p->mUnknown2914) {
        case 0:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 24:
            blocked = 1;
            break;
        default:
            moving++;
            if (p->mMotion.mUnknown44 > gPlyrMoveFwdSpeed * 0.05f) {
                blocked = 1;
            }
            if (p->mpState->mId == 7) {
                busy = 1;
            }
            break;
        }
    }
    if (fn_800B65A0(0) == 0xFF && fn_800B65A0(1) == 0xFF && CamGameGetCurrentSlot() == 3) {
        blocked = 1;
    }
    if (moving > 1 || blocked || busy) {
        return 0;
    }
    return 1;
}

extern "C" int ScrmOffenseAllPlaced(void)
{
    int team = ScrmGetOffenseTeam();
    unsigned short i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        if ((PlyrGet(team, i)->mFlags & 0x40000) == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" int ScrmOffenseAnyPlaced(void)
{
    int team = ScrmGetOffenseTeam();
    unsigned short i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        if (PlyrGet(team, i)->mFlags & 0x40000) {
            return 1;
        }
    }
    return 0;
}

/* File-static: nothing on GameCube calls these, and the linker drops them. */
extern "C" {
static int ScrmDefenseIsStill(void);
static int ScrmDefenseIsStillNearLine(void);
}

static int ScrmDefenseIsStill(void)
{
    int team = ScrmGetDefenseTeam();
    int still = 1;
    unsigned short i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);

        if (p->mFlags & 0x40000) {
            continue;
        }
        if (p->mMotion.mUnknown40 != 0.0f || p->mMotion.mUnknown44 != 0.0f) {
            still = 0;
        }
    }
    return still;
}

static int ScrmDefenseIsStillNearLine(void)
{
    int team = ScrmGetDefenseTeam();
    FieldPoint_t los = ScrmGetBallSpot();
    int still = 1;
    unsigned short i;
    unsigned int count = ScrmGetActivePlayerCount(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);

        if (p->mFlags & 0x40000) {
            continue;
        }
        if (fabsf(p->mMotion.mPos.mX - los.mX) < 4.0f && fabsf(p->mMotion.mPos.mY - los.mY) < 3.0f) {
            if (p->mMotion.mUnknown40 != 0.0f || p->mMotion.mUnknown44 != 0.0f) {
                still = 0;
            }
        }
    }
    return still;
}

extern "C" int ScrmCarrierInEndZone(Object_80039F5C *p, Vector_80039F5C *pPos)
{
    Ball_t *pBall;

    if (ScrmClassifyPosition(pPos, 0, 0) == 1) {
        return 1;
    }
    if (p->mFlags & 0x800000) {
        return 1;
    }
    pBall = BallFindHeldBy(p);
    if (pBall != 0) {
        Vector_80039F5C ballPos;

        BallGetTopPosition(pBall, &ballPos);
        if (ScrmClassifyPosition(&ballPos, 0, 0) == 1) {
            pPos->mY = ballPos.mY;
            return 1;
        }
        if (ballPos.mY > ScrmGetGoalLineY() && fabsf(pPos->mX) > ScrmGetSidelineX() &&
            ScrmClassifyPosition(&p->mMotion.mPos, 0, 0) == 1) {
            return 1;
        }
    }
    return 0;
}

extern "C" void ScrmUpdateBallCarrier(Object_80039F5C *p)
{
    Object_80039F5C *pOwner = 0;
    float margin = 0.0f;
    unsigned int value = 0;
    int mode = fn_800AD9B4();
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C ballPos;
    FieldPoint_t pos;
    Record_800B15FC *pRecord;

    BallGetPosition(pBall, &ballPos);
    if (mode != 3) {
        return;
    }
    pos = ScrmGetBallSpot();
    if (p != 0 && p->mIdBytes[3] == 1) {
        pOwner = p;
    }
    if (!ScrmTestPlayFlag(0)) {
        int ref;

        if (fn_801486A0() != 3) {
            margin = 0.3f;
        }
        if (ballPos.mY > pos.mY + margin) {
            int crossed = 1;

            if (p != 0) {
                switch (p->mpState->mId) {
                case 26:
                    if (((ScrmCatchState_t *)&p->mUnknown336)->mUnknown8 == 14) {
                        crossed = 0;
                    }
                    break;
                case 25:
                    if (fn_8011F518()->mUnknown4 == 8) {
                        crossed = 0;
                    }
                    break;
                case 15:
                    break;
                }
            }
            if (p != 0 && p->mpState->mId == 15 &&
                fn_8011F4F8(BallGetIndex(BallGetCurrent()))->mUnknown1D != 4) {
                crossed = 0;
            }
            if (fn_801486A0() == 0) {
                crossed = 0;
            }
            if (crossed) {
                ScrmSetPlayFlag(0, 1);
                margin = 4.0f;
                if (ballPos.mX > pos.mX + margin) {
                    ScrmSetPlayFlag(5, 1);
                }
                if (ballPos.mX < pos.mX - margin) {
                    ScrmSetPlayFlag(6, 1);
                }
                if (ScrmTestPlayFlag(4)) {
                    ScrmSetPlayFlag(4, 0);
                    ScrmChangePossession(0);
                    fn_8011DF90();
                }
                pRecord = fn_800B15FC();
                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = ballPos.mX;
                pRecord->mUnknown10 = ballPos.mY;
                pRecord->mUnknown14 = 24;
                fn_800B1508();
                if (p != 0) {
                    CamGameSetModeAll(1);
                } else {
                    PassIconsHide();
                    PassIconsClearReplayFlag();
                }
            }
        }
        if (!ScrmTestPlayFlag(7) && ballPos.mX > pos.mX + 4.0f) {
            fn_8009BD2C(p, &ref);
            ScrmSetPlayFlag(7, 1);
            pRecord = fn_800B15FC();
            pRecord->mUnknown14 = 32;
            pRecord->mUnknown0 = ref;
            pRecord->mUnknownC = ballPos.mX;
            pRecord->mUnknown10 = ballPos.mY;
            pRecord->mUnknown4 = 7;
            fn_800B1508();
        }
        if (!ScrmTestPlayFlag(8) && ballPos.mX < pos.mX - 4.0f) {
            fn_8009BD2C(p, &ref);
            ScrmSetPlayFlag(8, 1);
            pRecord = fn_800B15FC();
            pRecord->mUnknown14 = 32;
            pRecord->mUnknown0 = ref;
            pRecord->mUnknownC = ballPos.mX;
            pRecord->mUnknown10 = ballPos.mY;
            pRecord->mUnknown4 = 8;
            fn_800B1508();
        }
    }

    if (p != 0 && ScrmCarrierInEndZone(p, &ballPos) && BallGetTransferKind(pBall) == 0) {
        int conversion = 0;

        if (GamebreakerGetSavedState(0) == 2 || GamebreakerGetSavedState(1) == 2) {
            conversion = 1;
        }
        if ((fn_801486A0() == 4 || fn_801486A0() == 3) && fn_8011F1CC() != 0 && !ScrmTestPlayFlag(13) &&
            !ScrmTestPlayFlag(1) && !ScrmTestPlayFlag(20) && !conversion) {
            return;
        }
        if (ScrmGetDown() != 6) {

            if (p->mpState->mId == 12) {
                int kind;

                ScrmStatAddTeamVt(p->mIdBytes[2], 1);
                kind = PlayerMoveGetKind(p);
                if (kind != 0) {
                    ScrmStatAddTeamMoveScore(p->mIdBytes[2], 1);
                    switch (kind) {
                    case 1:
                        ScrmStatAddTeamSv(p->mIdBytes[2], 1);
                        break;
                    case 4:
                        if (((ScrmCatchState_t *)&p->mUnknown336)->mUnknown19 != 0) {
                            AudmonEventPostId(52, &p->mMotion.mPos, p->mId, 0, 0, 0);
                            ScrmStatAddTeamWt(p->mIdBytes[2], 1);
                        }
                        break;
                    }
                }
            } else if (p->mpState->mId >= 34 && p->mpState->mId <= 36) {
                if (PlayerMoveGetKind(p) != 0) {
                    ScrmStatAddTeamMoveScore(p->mIdBytes[2], 1);
                }
            }
            if (fn_800A8444(p->mIdBytes[2]) != 0 && GamebreakerGetReadyType(p->mIdBytes[2]) == 0 &&
                GamebreakerGetSavedState(p->mIdBytes[2]) == 1) {
                ScrmStatAddTeamOg(p->mIdBytes[2], 1);
            }
        }
        ScrmSetPlayFlag(9, 1);
        AudmonEventPostId(95, &ballPos, p->mId, 0, 0, 0);
        switch (ScrmGetScoreGoal(&value)) {
        case 0:
            if (ScrmGetDown() != 6) {
                if (ScrmGetTeamScore(p->mIdBytes[2]) + 6 < value) {
                    AudmonEventPostArgs(89, &ballPos, p->mIdBytes[2], 0, 0);
                } else if (!ChallengeIsActive()) {
                    AudmonEventPostArgs(94, &ballPos, p->mIdBytes[2], 0, 0);
                }
            } else {
                if (ScrmGetTeamScore(p->mIdBytes[2]) + 2 < value) {
                    AudmonEventPostArgs(90, &ballPos, p->mIdBytes[2], 0, 0);
                } else if (!ChallengeIsActive()) {
                    AudmonEventPostArgs(94, &ballPos, p->mIdBytes[2], 0, 0);
                }
            }
            break;
        case 1:
            if (ScrmGetDown() != 6) {
                if (StyleTrackerGetWinner() == 2) {
                    AudmonEventPostArgs(89, &ballPos, p->mIdBytes[2], 0, 0);
                }
            } else {
                if (StyleTrackerGetWinner() == 2) {
                    AudmonEventPostArgs(90, &ballPos, p->mIdBytes[2], 0, 0);
                }
            }
            break;
        case 2:
            if (fn_801486A0() == 2) {
                AudmonEventPostArgs(89, &ballPos, p->mIdBytes[2], 0, 0);
            }
            break;
        }
        ReplayEventAdd(gpReplay, 11, p, &p->mMotion.mPos, &p->mMotion.mFacing);
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = ballPos.mX < 0.5f - ScrmGetSidelineX()
                                 ? 0.5f - ScrmGetSidelineX()
                                 : (ballPos.mX > ScrmGetSidelineX() - 0.5f ? ScrmGetSidelineX() - 0.5f : ballPos.mX);
        pRecord->mUnknown10 = ballPos.mY;
        pRecord->mUnknown14 = 22;
        fn_8009BD2C(p, &pRecord->mUnknown4);
        fn_800B1508();
        ScrmEndPlay();
    } else {
        Point2_t target;

        PossCalcBallSpot(p, pBall, &target, 0);
        if (!PossCheckBallOut(pBall, &target) || p == 0) {
            return;
        }
        if (pOwner->mMotion.mPos.mZ > 0.0f) {
            return;
        }
        if ((pOwner->mFlags & 0x800) &&
            ((pOwner->mFlags & 0x10000) || p->mUnknown560.mUnknown53 != 0)) {
            float x;
            float line;
            Object_80039F5C *pOther;
            int skip = 0;

            if (BallGetTransferKind(pBall) != 0) {
                PossLogBallResult(p);
            }
            if (ScrmGetTackler() == 0) {
                ScrmSetTackler(fn_8009BCE8(&pOwner->mUnknown560.mUnknown48));
            }
            x = p->mMotion.mPos.mX;
            line = ScrmSpotGetLine();
            if (line > ScrmGetGoalLineY()) {
                if (x < 0.5f - ScrmGetSidelineX() || x > ScrmGetSidelineX() - 0.5f) {
                    x = ScrmGetSidelineX() - 0.5f;
                }

                ScrmSetPlayFlag(9, 1);
                AudmonEventPostId(95, &ballPos, p->mId, 0, 0, 0);
                switch (ScrmGetScoreGoal(&value)) {
                case 0:
                    if (ScrmGetDown() != 6) {
                        if (ScrmGetTeamScore(p->mIdBytes[2]) + 6 < value) {
                            AudmonEventPostArgs(89, &ballPos, p->mIdBytes[2], 0, 0);
                        } else if (!ChallengeIsActive()) {
                            AudmonEventPostArgs(94, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    } else {
                        if (ScrmGetTeamScore(p->mIdBytes[2]) + 2 < value) {
                            AudmonEventPostArgs(90, &ballPos, p->mIdBytes[2], 0, 0);
                        } else if (!ChallengeIsActive()) {
                            AudmonEventPostArgs(94, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    }
                    break;
                case 1:
                    if (ScrmGetDown() != 6) {
                        if (StyleTrackerGetWinner() == 2) {
                            AudmonEventPostArgs(89, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    } else {
                        if (StyleTrackerGetWinner() == 2) {
                            AudmonEventPostArgs(90, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    }
                    break;
                case 2:
                    break;
                }
                ReplayEventAdd(gpReplay, 11, p, &p->mMotion.mPos, &p->mMotion.mFacing);
            }
            pOther = ScrmGetTackler();
            fn_800B1698(p, pOther);
            if (pOther != 0) {
                ReplayEventAdd(gpReplay, 7, pOther, &pOther->mMotion.mPos, &pOther->mMotion.mFacing);
                ReplayEventAdd(gpReplay, 25, pOther, &pOther->mMotion.mPos, &pOther->mMotion.mFacing);
            }
            if (!skip) {
                StyleTrackerOnTackle(p, line);
                ReplayEventAdd(gpReplay, 6, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                ScrmEndPlay();
            }
            pOwner->mFlags &= ~0x10000;
            ScrmSetTackler(0);
        }
        if (p->mUnknown2914 == 0 || (fn_8011F2C4() != 0 && (p->mUnknown2914 == 1 || p->mUnknown2914 == 3))) {
            if (!(p->mFlags & 0x8000)) {
                FieldPoint_t los;

                los = pos;
                if (p->mMotion.mPos.mY > los.mY || fabsf(p->mMotion.mPos.mX - los.mX) > 3.0f) {
                    p->mFlags |= 0x8000;
                }
            }
        }
        if (BallGetTransferKind(pBall) == 4) {
            if ((unsigned int)BallGetStateFrames(pBall) > 20) {
                PossLogBallResult(p);
            } else {
                PossTryJarBall(p);
            }
        } else if (BallGetTransferKind(pBall) == 1) {
            PossTryJarBall(p);
        }
    }
}

extern "C" void ScrmSpotReset(void)
{
    Info_ScrmState *pState = ScrmGetInfo();

    pState->mUnknown00 = 400.0f;
    pState->mUnknown04 = 400.0f;
    pState->mUnknown08 = 400.0f;
    pState->mUnknown10 = 0;
    pState->mUnknown0C = 0;
    pState->mUnknown18 = 400.0f;
    pState->mUnknown14 = -100;
    pState->mUnknown1C = 0;
}

extern "C" void ScrmSpotRecordHit(Object_80039F5C *p, int *pValue)
{
    Info_ScrmState *pState = ScrmGetInfo();
    Vector_80039F5C ballPos;

    BallGetPosition(BallGetCurrent(), &ballPos);
    if (ballPos.mY >= pState->mUnknown00 || pState->mUnknown14 == -100) {
        pState->mUnknown0C = p->mMotion.mFacing;
    }
    pState->mUnknown14 = 0;
    if (pState->mUnknown1C == 0) {
        pState->mUnknown1C = *pValue;
        pState->mUnknown18 = ballPos.mY;
    }
}

extern "C" void ScrmSpotCheckRetreat(void)
{
    int mode = fn_800AD9B4();
    Info_ScrmState *pState = ScrmGetInfo();

    if (mode == 3) {
        Object_80039F5C *p = BallGetCurrentHolder();

        if (p != 0 && p->mIdBytes[3] == 1 && p->mUnknown512.mUnknown14 != 0 &&
            MathAngleDiff(p->mUnknown512.mUnknown4, 0x400000) > 0x400000) {
            ScrmSpotMark();
        }
    }
}

extern "C" void ScrmSpotUpdate(void)
{
    int mode = fn_800AD9B4();
    Info_ScrmState *pState = ScrmGetInfo();
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C ballPos;
    Object_80039F5C *p;

    BallGetPosition(pBall, &ballPos);
    p = BallGetHolder(pBall);
    if (mode == 3) {
        if (p != 0) {
            if (p->mId == pState->mUnknown10) {
                if (pState->mUnknown14 != -100) {
                    pState->mUnknown14++;
                }
                pState->mUnknown04 = ballPos.mY;
                if (fabsf(ballPos.mX) > ScrmGetSidelineX() && ballPos.mY < ScrmGetGoalLineY()) {
                    if (pState->mUnknown08 == 400.0f) {
                        pState->mUnknown08 = ballPos.mY;
                    }
                    pState->mUnknown04 = pState->mUnknown04 > pState->mUnknown08 ? pState->mUnknown08
                                                                               : pState->mUnknown04;
                } else {
                    pState->mUnknown08 = 400.0f;
                }
                if (p->mUnknown1160.mUnknown0 != 0.0f || (p->mFlags & 0x10000)) {
                    if (pState->mUnknown04 > pState->mUnknown00) {
                        ScrmSpotMark();
                    }
                } else if (pState->mUnknown14 == -100 || pState->mUnknown14 > 5) {
                    ScrmSpotMark();
                } else {
                    pState->mUnknown00 = pState->mUnknown04;
                }
            } else {
                ScrmSpotReset();
                pState->mUnknown10 = p->mId;
                pState->mUnknown00 = pState->mUnknown04 = ballPos.mY;
                pState->mUnknown1C = 0;
                pState->mUnknown18 = 400.0f;
            }
        } else if (pState->mUnknown10 != 0) {
            ScrmSpotReset();
        }
    }
}

extern "C" void ScrmSpotMark(void)
{
    Info_ScrmState *pState = ScrmGetInfo();
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C ballPos;
    Object_80039F5C *p;

    BallGetPosition(pBall, &ballPos);
    p = BallGetHolder(pBall);
    if (fabsf(ballPos.mX) > ScrmGetSidelineX() && ballPos.mY > ScrmGetGoalLineY()) {
        pState->mUnknown00 = ScrmGetGoalLineY() - 0.33f;
        pState->mUnknown08 = 400.0f;
    } else {
        pState->mUnknown00 = ballPos.mY;
        if (fabsf(ballPos.mX) > ScrmGetSidelineX()) {
            if (pState->mUnknown08 == 400.0f) {
                pState->mUnknown08 = ballPos.mY;
            }
            pState->mUnknown00 = pState->mUnknown00 > pState->mUnknown08 ? pState->mUnknown08
                                                                       : pState->mUnknown00;
        } else {
            pState->mUnknown08 = 400.0f;
        }
    }
    pState->mUnknown0C = p->mMotion.mFacing;
    pState->mUnknown14 = -100;
}

extern "C" float ScrmSpotGetLine(void)
{
    return ScrmGetInfo()->mUnknown00;
}

extern "C" int ScrmSpotGetFirstHit(float *pOut)
{
    Info_ScrmState *pState = ScrmGetInfo();

    *pOut = pState->mUnknown18;
    return pState->mUnknown1C;
}
