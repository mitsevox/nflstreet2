/* Tracks style awards, combinations and Gamebreaker meters throughout a play. */

#include <string.h>
#include <math.h>
#include "game/cu_8017DD68.h"
#include "game/StyleTracker.h"
#include "game/StyleAwardRule.h"
#include "game/DbCursor.h"
#include "game/Entry_80219044.h"
#include "game/Object_80039F5C.h"
#include "game/Record_800B15FC.h"
#include "game/AudmonEvent.h"
#include "game/cu_8003108C.h"
#include "game/Ball.h"
#include "game/fn_80177FE0.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"
#include "game/fn_8017F584.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_80238174.h"

enum StyleMessage {};

struct StyleAwardStep_t {
    int mComboLabel;
    StyleMessage mMessage;
    int mPoints;
    char unk_0xC[4];
    unsigned int mThreshold;
    unsigned char mInterpolate;
    unsigned int mInterval;
};
struct StyleAwardGrowth_t {
    unsigned char mEnabled;
    int mPoints;
    char unk_0x8[4];
    unsigned int mInterval;
    char unk_0x10[8];
};
struct StyleAwardTable_t {
    const StyleAwardGrowth_t *mpGrowth;
    const StyleAwardStep_t *mpSteps;
};

/* Persistent award rules, per-play bookkeeping and per-team presentation state. */
struct StyleTrackerState_t {
    StyleAwardRule_t mRules[127];
    char unk_0x19CC[156];
    int mTeamZeroTotal;
    int mTeamOneTotal;
    int mTeamZeroMeter;
    int mTeamOneMeter;
    int mTeamZeroComboWeight;
    int mTeamOneComboWeight;
    unsigned short mTeamZeroEventCounts[127];
    unsigned short mTeamOneEventCounts[127];
    char mAwardText[80];
    Entry_80219044 mTextArg;
    char mTeamZeroComboText[251];
    char mTeamOneComboText[251];
    unsigned char unk_0x1ECE;
    union {
        unsigned char mPlayFlags[69];
        struct {
            char unk_0x1ECF[6];
            unsigned char mPassOccurred;
            unsigned char mOffenseLostBall;
            unsigned char mDefenseLostBall;
            unsigned char mIntercepted;
            unsigned char mPitchStolen;
            unsigned char mRunActive;
            unsigned char mRunRequested;
            unsigned char mRunCompleted;
            unsigned char mJukeActive;
            unsigned char mSpinActive;
            unsigned char mHurdleActive;
            unsigned char mStyleMove;
            unsigned char mPitchActive;
            unsigned char mStylePitch;
            unsigned char mPitchReleased;
            unsigned char mFakeout;
            unsigned char mPumpInteraction;
            unsigned char mPumpAwarded;
            unsigned char mStiffArmActive;
            unsigned char mStiffArmSucceeded;
            unsigned char mStylePassPending;
            unsigned char mStylePassReleased;
            unsigned char mPassReleased;
            unsigned char mDefensiveMoveActive;
            unsigned char mStyleDefensiveMove;
            unsigned char mSavedRunAwardPending;
            unsigned char mCatchPending;
            unsigned char mUserCatch;
            unsigned char mStyleCatch;
            unsigned char mCatchVariant;
            unsigned char mWallMove;
            unsigned char mNinjaPass;
            unsigned char mMoveFallback;
            unsigned char mOffenseTouchdown;
            unsigned char mDefenseTouchdown;
            unsigned char mTouchdownPending;
            unsigned char mConversion;
            unsigned char mDefensiveConversion;
            unsigned char mConversionPending;
            unsigned char mDefensiveConversionPending;
            unsigned char mFailedConversionPending;
            unsigned char mStyleFirstDown;
            unsigned char mFirstDown;
            unsigned char mTackleContest;
            unsigned char mTackleContestAwarded;
            unsigned char mTackleContestStop;
            unsigned char mSafety;
            unsigned char mQbStop;
            unsigned char mUserQbStop;
            unsigned char mLoss;
            unsigned char mNoControlLoss;
            unsigned char mUserLoss;
            unsigned char mTurnoverOnDowns;
            unsigned char mTouchback;
            unsigned char mValidYardage;
            char mQueueDisplay[1];
            unsigned char mApplySavedRunBonus;
            char mRunComboAdded[2];
            unsigned char mContactSeen;
            unsigned char mContactPending;
            unsigned char mPlaySettled;
            unsigned char mMatchSettled;
        };
    };
    float mPossessionStartY;
    unsigned int mUserPlayerCount;
    Object_80039F5C *mpUserPlayers[4];
    int mRunTime;
    int mRunTicks;
    int mRunAwardValue;
    int mRunMeterValue;
    int mRunTeam;
    Object_80039F5C *mpRunPlayer;
    int mRunEndTicks;
    int mCompletedRunTime;
    int mRunAction;
    unsigned char mRunSubtype;
    char unk_0x1F51[3];
    int mSavedRunAward;
    int mSavedRunMeter;
    unsigned char mPassSubtype;
    char mHurdleSubtype[1];
    unsigned char mSpinSubtype;
    unsigned char mDiveSubtype;
    unsigned char mJukeTeam;
    unsigned char mSpinTeam;
    unsigned char mStiffArmTeam;
    unsigned char mHurdleTeam;
    unsigned char mPitchTeam;
    char unk_0x1F65[3];
    Object_80039F5C *mpStiffArmPlayer;
    Object_80039F5C *mpDefensiveMovePlayer;
    int mDistanceToGoal;
    int mPlayYardage;
    int mTouchdownEvent;
    unsigned char mSafetyTeam;
    unsigned char mTouchbackTeam;
    char unk_0x1F7E[2];
    int mPitchCounts[2];
    char mPendingText[2][80];
    int mPendingCount[2];
    int mPendingCategory[2];
    int mPendingAward[2];
    int mPendingTotal[2];
    int mPendingMeter[2];
    int mPlayStartTotal[2];
    int mPlayStyleGain[2];
    Object_80039F5C *mpContactPlayer;
    unsigned char mMeterFilledThisPlay[2];
    char unk_0x2066[2];
    Object_80039F5C *mpRunEffectPlayer;
    unsigned char mRunEffectActive;
    char unk_0x206D[3];
};


extern "C" {
extern StyleAwardCallback _StyleTracker_pAwardCallback;
extern unsigned char _StyleTracker_bEnabled;
extern unsigned char _StyleTracker_bCombosEnabled;
extern int _StyleTracker_iDatabaseVariant;
extern int _StyleTracker_iMeterThreshold;
extern StyleTrackerState_t *_StyleTracker_pState;
extern unsigned char _StyleTracker_cWinner;
extern int _StyleTracker_aiPlayStylePoints[2];
extern int _StyleTracker_aiPlayPitches[2];
extern unsigned char _StyleTracker_acQbStopStreak[2], _StyleTracker_abQbStopThisPlay[2], _StyleTracker_acUserQbStopStreak[2], _StyleTracker_abUserQbStopThisPlay[2];
extern unsigned char _StyleTracker_acCatchStreak[2], _StyleTracker_abCatchThisPlay[2];
extern unsigned char _StyleTracker_abCatchOpportunity[2];
extern unsigned char _StyleTracker_acStyleCatchStreak[2];
extern unsigned char _StyleTracker_abStylePassThisPlay[2], _StyleTracker_acConsecutivePitches[2], _StyleTracker_acLongestPitchChain[2];
extern const StyleAwardTable_t _StyleTracker_aAwardTables[];
extern const char _StyleTracker_aszAwardMessages[][80];
extern const char _StyleTracker_aszComboLabels[][20];
extern const char _StyleTracker_szComboSeparator[4], _StyleTracker_szEmptyCombo[1];
extern float _StyleTracker_fProfilePointScale;
extern void *lbl_803EB688;

int ChallengeIsActive(void);
struct Challenge_t;
Challenge_t *ChalGetCurrent(void);
int ChallengeHasGoalType(Challenge_t *, int, int *);
void fn_800A20D0(int, signed char);
float fn_800A32B4(void);
void fn_800A72B4(void);
void fn_800A7B5C(void);
Object_80039F5C *fn_801244F0(Object_80039F5C *, int, unsigned char, unsigned char, float *, int);
Object_80039F5C *fn_801245DC(Object_80039F5C *, int, unsigned char, unsigned char, int, float *, int);
float fn_80178A2C(void);
Point_8017886C fn_80178070(void);
int fn_801787DC(int);
void fn_8017E3CC(int);
int fn_80186F7C(unsigned char);
int fn_8022F358(int);
void UserInfoAddPoints(int, unsigned int);
void fn_8018FB4C(DbCursor *, int);
void fn_8018FBC8(DbCursor *);
int fn_8018FBE8(DbCursor *, int);
void fn_8018FC1C(DbCursor *, StyleAwardRule_t *);
void fn_8017C5A0(unsigned short, int);
void fn_8017C5CC(unsigned short, int);
void fn_8017C5F8(unsigned short, int);
void fn_8017C648(unsigned short, int);
void fn_8017C6A0(unsigned short, int);
void fn_8017C6CC(unsigned short, int, int);
void fn_8017C724(unsigned short, int);
void fn_8017C750(unsigned short, int, int);
void fn_8017C7A8(unsigned short, int);
void fn_8017C7D4(unsigned short, int);
void fn_8017C800(unsigned short, int);
void fn_8017C82C(unsigned short, int);
void fn_8017C884(unsigned short, int);
void fn_8017C8DC(unsigned short, int);
void fn_8017C908(unsigned short, int);
void fn_8017C98C(unsigned short, int);

unsigned char CheatFlagsIsSet(int index);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_800A7A0C(int team);
int fn_800A8444(int team);
int fn_800A8488(int team);
int fn_800A84C8(void);
int fn_800A8740(void);
int fn_800A8F84(unsigned char index);
void fn_800AE7F0(int a, int b, Object_80039F5C *p);
void fn_800B1698(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801486A0(void);
void fn_80156C78(int a, int b);
int fn_801650DC(Record_80067338 *pRecord);
int fn_80177C38(void);
int fn_80177F70(void);
int fn_80177F7C(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
void fn_80178370(void);
int fn_801783AC(int bit);
Object_80039F5C *fn_8017876C(void);
int fn_801787A0(void);
int fn_801788D8(int *pValue);
int fn_80179138(void);
void fn_8017C674(unsigned short team, int value);
void fn_8017C9B8(unsigned short team, int value);
void fn_8017C9E4(unsigned short team, int value);
void fn_8017CA10(unsigned short team, int value);
void fn_8017CA68(int team, int value);
unsigned short fn_801BE648(void *p);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);

int PlayerMoveGetKind(Object_80039F5C *p);
void StyleTrackerTraceEvent(int a);
void StyleTrackerApplyAward(int, int, int, int, int, int, int, int, int, int);
void StyleTrackerSetEventCount(int, int, int);
int StyleTrackerGetMeter(int);
void StyleTrackerAppendCombo(int, int, int, int);
void StyleTrackerAccumulateRunTime(void);
void StyleTrackerShowMeter(int a, int b, int c, int d);
void StyleTrackerCalculateAward(int a, int b, int c, int *p0, int *p1, int *p2, int *p3, int *p4, int *p5, int *p6);
void StyleTrackerAwardEvent(int a, int b, int c);
void StyleTrackerSetComboWeight(int a, int b);
void StyleTrackerProcessEvent(int a, int b, int c);
void StyleTrackerCancelRun(int a);
void StyleTrackerFinishRun(void);

void StyleTrackerClearPendingDisplay(int i);
void StyleTrackerFlushPendingDisplay(int i, int a, int b);
void StyleTrackerQueueDisplay(int i, const char *pName, int a, int b, int c, int mode, int d);
int StyleTrackerResolveMessage(StyleMessage a);
void StyleTrackerShowAward(int i, const char *pName, int a, int mode);
void StyleTrackerShowTotal(int i, int a);
void StyleTrackerShowCombo(int i);
int StyleTrackerGetComboWeight(int i);
void StyleTrackerAwardImmediateEvent(int a, int b);
void StyleTrackerFinishPendingContact(int a);
void StyleTrackerFinishStylePass(void);
void StyleTrackerAwardCompletedRun(void);
void StyleTrackerResetRun(void);
int StyleTrackerCanAwardCombo(int a);
void StyleTrackerAwardCombo(int a, int b);
void StyleTrackerAwardTurnoverOnDowns(void);
void StyleTrackerAwardTouchback(void);
void StyleTrackerAwardDefensiveOutcome(void);
void StyleTrackerAwardFirstDown(void);
void StyleTrackerAwardConversion(void);
void StyleTrackerAwardVictory(int, unsigned int);
void StyleTrackerAwardFailedConversion(void);
void StyleTrackerAwardTouchdown(void);
void StyleTrackerAwardPassGain(void);
void StyleTrackerAwardRushGain(void);
void StyleTrackerOnPossessionLost(void);
void StyleTrackerOnPassReleased(void);
void StyleTrackerOnPitchReleased(void);
int StyleTrackerFinishStiffArm(int a);
void StyleTrackerFinishOtherMoves(int a);
void StyleTrackerFinishDefensiveMove(int a);
int StyleTrackerIsCurrentActorUserControlled(void);
int StyleTrackerIsFumbleForcerUserControlled(void);
}

extern "C" void StyleTrackerTraceEvent(int)
{
}

extern "C" void StyleTrackerClearPendingDisplay(int i) {
    StyleTrackerTraceEvent(86);
    _StyleTracker_pState->mPendingText[i][0] = 0;
    _StyleTracker_pState->mPendingCount[i] = 0;
    _StyleTracker_pState->mPendingAward[i] = 0;
    _StyleTracker_pState->mPendingTotal[i] = 0;
    _StyleTracker_pState->mPendingMeter[i] = 0;
}

extern "C" void StyleTrackerFlushPendingDisplay(int i, int a, int b) {
    if (_StyleTracker_bEnabled) {
        StyleTrackerTraceEvent(87);
        if (a && _StyleTracker_pState->mPendingTotal[i]) {
            StyleTrackerShowTotal(i, _StyleTracker_pState->mPendingTotal[i]);
        }
        if (b && _StyleTracker_pState->mPendingAward[i]) {
            StyleTrackerShowAward(i, _StyleTracker_pState->mPendingText[i], _StyleTracker_pState->mPendingAward[i],
                        _StyleTracker_pState->mPendingCategory[i]);
        }
    }
}

extern "C" void StyleTrackerQueueDisplay(int i, const char *pName, int a, int b, int c, int mode, int d) {
    switch (mode) {
    case 1:
        StyleTrackerTraceEvent(85);
        break;
    case 0:
        StyleTrackerTraceEvent(82);
        break;
    case 3:
        StyleTrackerTraceEvent(83);
        break;
    case 2:
        StyleTrackerTraceEvent(84);
        break;
    }
    if (strlen(pName) < 80) {
        _StyleTracker_pState->mPendingCount[i]++;
        _StyleTracker_pState->mPendingAward[i] += a;
        _StyleTracker_pState->mPendingTotal[i] = c;
        _StyleTracker_pState->mPendingMeter[i] = b;
        _StyleTracker_pState->mPendingMeter[i == 0] = d;
        strcpy(_StyleTracker_pState->mPendingText[i], pName);
        if (_StyleTracker_pState->mPendingCount[i] == 1) {
            _StyleTracker_pState->mPendingCategory[i] = mode;
        } else if (_StyleTracker_pState->mPendingCategory[i] != 3) {
            _StyleTracker_pState->mPendingCategory[i] = mode;
        }
    }
}

extern "C" int StyleTrackerResolveMessage(StyleMessage a) {
    switch (a) {
    case 104:
        switch (_StyleTracker_pState->mRunSubtype) {
        case 0:
            return 105;
        case 1:
            return 106;
        case 2:
            return 107;
        case 3:
            return 108;
        case 4:
            return 109;
        case 5:
            return 110;
        case 6:
            return 111;
        case 7:
            return 112;
        case 8:
            return 113;
        case 9:
            return 114;
        case 10:
            return 115;
        case 11:
            return 116;
        case 12:
            return 117;
        case 13:
            return 118;
        case 14:
            return 119;
        case 15:
            return 120;
        case 16:
            return 121;
        case 17:
            return 122;
        case 18:
            return 123;
        case 19:
            return 124;
        case 20:
            return 125;
        case 21:
            return 126;
        case 22:
            return 127;
        case 23:
            return 128;
        case 24:
            return 129;
        case 25:
            return 130;
        case 26:
            return 131;
        case 27:
            return 132;
        case 28:
            return 133;
        case 29:
            return 134;
        case 30:
            return 135;
        case 31:
            return 136;
        case 32:
            return 103;
        default:
            return 103;
        }
    case 10:
        switch (_StyleTracker_pState->mPassSubtype) {
        case 2:
            return 16;
        case 3:
            return 22;
        case 4:
            return 14;
        case 5:
            return 18;
        case 6:
            return 20;
        default:
            return 8;
        }
    case 11:
        switch (_StyleTracker_pState->mPassSubtype) {
        case 2:
            return 17;
        case 3:
            return 23;
        case 4:
            return 15;
        case 5:
            return 19;
        case 6:
            return 21;
        default:
            return 9;
        }
    case 60:
        switch (_StyleTracker_pState->mSpinSubtype) {
        case 0:
            return 61;
        case 1:
            return 62;
        case 4:
            return 63;
        case 5:
            return 64;
        case 8:
            return 65;
        case 9:
            return 66;
        case 12:
            return 67;
        case 13:
            return 68;
        case 16:
            return 69;
        case 17:
            return 70;
        default:
            return 59;
        }
    case 72:
        switch (_StyleTracker_pState->mSpinSubtype) {
        case 0:
            return 73;
        case 1:
            return 74;
        case 4:
            return 75;
        case 5:
            return 76;
        case 8:
            return 77;
        case 9:
            return 78;
        case 12:
            return 79;
        case 13:
            return 80;
        case 16:
            return 81;
        case 17:
            return 82;
        default:
            return 71;
        }
    case 85:
        switch (_StyleTracker_pState->mDiveSubtype) {
        case 0:
            return 87;
        case 1:
            return 88;
        case 2:
            return 89;
        case 3:
            return 90;
        case 4:
            return 91;
        case 5:
            return 92;
        case 6:
            return 93;
        case 7:
            return 94;
        case 8:
            return 95;
        default:
            return 86;
        }
    }
    return a;
}

extern "C" void StyleTrackerShowAward(int i, const char *pName, int a, int mode) {
    Arg_8021D7B8 args[4];

    if (_StyleTracker_bEnabled) {
        strcpy(_StyleTracker_pState->mAwardText, pName);
        switch (mode) {
        case 1:
            StyleTrackerTraceEvent(81);
            break;
        case 0:
            StyleTrackerTraceEvent(78);
            break;
        case 3:
            StyleTrackerTraceEvent(79);
            break;
        case 2:
            StyleTrackerTraceEvent(80);
            break;
        }
        args[0].i = i;
        args[1].p = &_StyleTracker_pState->mTextArg;
        ((Entry_80219044 *)args[1].p)->mpText = _StyleTracker_pState->mAwardText;
        ((Entry_80219044 *)args[1].p)->mLength = strlen(_StyleTracker_pState->mAwardText);
        args[2].i = a;
        args[3].i = mode;
        fn_8021D7B8(lbl_803EB688, 0x80000013, 4, args);
    }
}

extern "C" void StyleTrackerShowTotal(int i, int a) {
    Arg_8021D7B8 args[2];

    if (_StyleTracker_bEnabled) {
        args[0].i = i;
        args[1].i = a;
        fn_8021D7B8(lbl_803EB688, 0x8000001A, 2, args);
    }
}

extern "C" void StyleTrackerShowMeter(int side, int value, int a, int b) {
    if (_StyleTracker_bEnabled && fn_800A8740() == 0) {
        float t;
        if (value == 0) t = 0.0f;
        else if (value >= _StyleTracker_iMeterThreshold) t = 1.0f;
        else t = (float)value / (float)_StyleTracker_iMeterThreshold;
        fn_8017DE54((unsigned char)side, t, a, b);
    }
}

extern "C" void StyleTrackerShowCombo(int i) {
    Entry_80219044 *args[1];

    if (_StyleTracker_bEnabled) {
        args[0] = &_StyleTracker_pState->mTextArg;
        args[0]->mpText = i == 0 ? _StyleTracker_pState->mTeamZeroComboText : _StyleTracker_pState->mTeamOneComboText;
        args[0]->mLength = strlen(i == 0 ? _StyleTracker_pState->mTeamZeroComboText : _StyleTracker_pState->mTeamOneComboText);
        fn_8021D7B8(lbl_803EB688, 0x80000018, 1, args);
    }
}

/* Resolve fixed or tiered awards, with interpolation and growth beyond the final tier. */
extern "C" void StyleTrackerCalculateAward(int side, int id, int count, int *pScaled, int *pSubtract, int *pValue, int *pText, int *pExtra, int *pMode, int *pName) {
    int subtract, value, mode, name;
    int awardValue;
    if (_StyleTracker_pState->mRules[id].mTableIndex == -1) {
        subtract = _StyleTracker_pState->mRules[id].mMeterSteal;
        value = _StyleTracker_pState->mRules[id].mPoints;
        mode = _StyleTracker_pState->mRules[id].mComboLabel;
        name = StyleTrackerResolveMessage((StyleMessage)_StyleTracker_pState->mRules[id].mMessage);
    } else {
        const StyleAwardStep_t *steps = _StyleTracker_aAwardTables[_StyleTracker_pState->mRules[id].mTableIndex].mpSteps;
        subtract = 0;
        value = 0;
        mode = 0;
        name = 0;
        unsigned int i = 0;
        int found = 0, ended = 0;
        unsigned int threshold = 0;
        unsigned int distance;
        for (; i <= 9; i++) {
            awardValue = steps[i].mPoints;
            if (awardValue == 0) { ended = 1; break; }
            if ((unsigned int)count < steps[i].mThreshold) break;
            value = awardValue;
            mode = steps[i].mComboLabel;
            name = StyleTrackerResolveMessage(steps[i].mMessage);
            threshold = steps[i].mThreshold;
            found = 1;
        }
        if (i > 9) ended = 1;
        if (found && !ended) {
            if (steps[i - 1].mInterpolate) {
                distance = (unsigned int)count - steps[i - 1].mThreshold;
                unsigned int percent = (distance / steps[i - 1].mInterval) *
                    ((steps[i - 1].mInterval * 100) / (steps[i].mThreshold - steps[i - 1].mThreshold));
                if (percent >= 1 && percent <= 99) value += (percent * (steps[i].mPoints - steps[i - 1].mPoints)) / 100;
            }
        }
        const StyleAwardGrowth_t *increment = _StyleTracker_aAwardTables[_StyleTracker_pState->mRules[id].mTableIndex].mpGrowth;
        if (increment && ended && increment->mEnabled) {
            distance = (unsigned int)count - threshold;
            unsigned int repeats = distance / increment->mInterval;
            if (repeats) value += repeats * increment->mPoints;
        }
    }
    int extra = _StyleTracker_pState->mRules[id].mComboWeight;
    if (_StyleTracker_pState->mApplySavedRunBonus) value += _StyleTracker_pState->mSavedRunAward;
    int text = _StyleTracker_pState->mRules[id].mScoreDelta;
    if (pScaled) {
        awardValue = value * 10;
        awardValue /= 100;
        *pScaled = awardValue;
    }
    if (pSubtract) *pSubtract = subtract;
    if (pValue) *pValue = value;
    if (pText) *pText = text;
    if (pExtra) *pExtra = extra;
    if (pMode) *pMode = mode;
    if (pName) *pName = name;
}

extern "C" void StyleTrackerApplyAward(int side, int id, int scaled, int subtract, int value, int text, int extra, int mode, int name, int arg) {
    if (_StyleTracker_bEnabled) {
        if (_StyleTracker_pState->mRules[id].mEnabled) {
            if (value != 0 || _StyleTracker_pState->mRules[id].mAllowZero) {
                StyleTrackerSetEventCount(side, id, StyleTrackerGetEventCount(side, id) + 1);
                char message[80];
                strcpy(message, _StyleTracker_aszAwardMessages[name]);
                if (_StyleTracker_pAwardCallback) _StyleTracker_pAwardCallback(id, side, message, value, _StyleTracker_pState->mRules[id].mApply, arg, _StyleTracker_pState->mQueueDisplay[0] == 0);
                if (_StyleTracker_pState->mRules[id].mApply) {
                    if (fn_800A8488(side == 0) == 0 && subtract != 0) {
                        StyleTrackerSetMeter(side == 0, StyleTrackerGetMeter(side == 0) - subtract, 0);
                        StyleTrackerSetMeter(side, StyleTrackerGetMeter(side) + scaled, 1);
                    } else StyleTrackerSetMeter(side, StyleTrackerGetMeter(side) + scaled, 0);
                    StyleTrackerSetTotal(side, StyleTrackerGetTotal(side) + value);
                    StyleTrackerAppendCombo(side, id, mode, extra);
                } else {
                    if (fn_800A8488(side == 0) == 0 && subtract != 0) {
                        StyleTrackerShowMeter(side == 0, StyleTrackerGetMeter(side == 0) - subtract, 0, 1);
                        StyleTrackerShowMeter(side, StyleTrackerGetMeter(side) + scaled, 1, 1);
                    } else StyleTrackerShowMeter(side, StyleTrackerGetMeter(side) + scaled, 0, 1);
                }
                if (_StyleTracker_pState->mQueueDisplay[0]) {
                    int meter = StyleTrackerGetMeter(side);
                    int total = StyleTrackerGetTotal(side);
                    int other = StyleTrackerGetMeter(side == 0);
                    StyleTrackerQueueDisplay(side, message, value, meter, total, arg, other);
                } else {
                    StyleTrackerShowAward(side, message, value, arg);
                    StyleTrackerShowTotal(side, StyleTrackerGetTotal(side));
                }
                if (fn_801486A0() == 3 && text != 0) fn_800A20D0(fn_80178348(), (signed char)text);
            } else StyleTrackerTraceEvent(76);
        } else StyleTrackerTraceEvent(77);
    }
}

extern "C" void StyleTrackerAwardEvent(int side, int id, int count) {
    if (_StyleTracker_bEnabled) {
        int scaled, subtract, value, text, extra, mode, name;
        StyleTrackerCalculateAward(side, id, count, &scaled, &subtract, &value, &text, &extra, &mode, &name);
        switch (id) {
        case 67: case 68: fn_8017C8DC(side, 1); _StyleTracker_aiPlayStylePoints[side] += value; break;
        case 15:
            _StyleTracker_aiPlayPitches[side]++;
            _StyleTracker_acConsecutivePitches[side]++;
            if (_StyleTracker_acConsecutivePitches[side] > _StyleTracker_acLongestPitchChain[side]) _StyleTracker_acLongestPitchChain[side] = _StyleTracker_acConsecutivePitches[side];
            break;
        case 14: case 17: _StyleTracker_acConsecutivePitches[side] = 0; break;
        case 18:
            _StyleTracker_aiPlayPitches[side]++;
            _StyleTracker_acConsecutivePitches[side]++;
            if (_StyleTracker_acConsecutivePitches[side] > _StyleTracker_acLongestPitchChain[side]) _StyleTracker_acLongestPitchChain[side] = _StyleTracker_acConsecutivePitches[side];
            _StyleTracker_aiPlayStylePoints[side] += value;
            fn_8017C7D4(side, 1);
            break;
        case 10: case 11:
            if (id == 11) fn_8017C6A0(side, 1); else fn_8017C648(side, 1);
            _StyleTracker_abStylePassThisPlay[side] = 1;
            _StyleTracker_aiPlayStylePoints[side] += value;
            break;
        case 38: case 39: case 50: case 51:
            fn_8017C6CC(side, 1, 0); _StyleTracker_aiPlayStylePoints[side] += value; break;
        case 53: case 54:
            fn_8017C724(side, 1); _StyleTracker_aiPlayStylePoints[side] += value; break;
        case 63: fn_8017C7A8(side, 1); _StyleTracker_aiPlayStylePoints[side] += value; break;
        case 60: fn_8017C750(side, 1, 0); _StyleTracker_aiPlayStylePoints[side] += value; break;
        case 66: _StyleTracker_aiPlayStylePoints[side] += value; break;
        case 77: _StyleTracker_abQbStopThisPlay[side] = 1; _StyleTracker_abUserQbStopThisPlay[side] = 1; break;
        case 76: _StyleTracker_abQbStopThisPlay[side] = 1; break;
        case 19: case 20: case 21: case 22: case 23: case 24: _StyleTracker_abCatchThisPlay[side] = 1; break;
        }
        StyleTrackerApplyAward(side, id, scaled, subtract, value, text, extra, mode, name, _StyleTracker_pState->mRules[id].mCategory);
    }
}

extern "C" int StyleTrackerGetComboWeight(int i) {
    return *(i == 0 ? &_StyleTracker_pState->mTeamZeroComboWeight : &_StyleTracker_pState->mTeamOneComboWeight);
}

extern "C" void StyleTrackerSetComboWeight(int side, int value) {
    *(side == 0 ? &_StyleTracker_pState->mTeamZeroComboWeight : &_StyleTracker_pState->mTeamOneComboWeight) = value;
    if (value == 0) strcpy(side == 0 ? _StyleTracker_pState->mTeamZeroComboText : _StyleTracker_pState->mTeamOneComboText, _StyleTracker_szEmptyCombo);
}

extern "C" void StyleTrackerAppendCombo(int side, int id, int text, int value) {
    if (id == 66) {
        if (side == 0) {
            if (_StyleTracker_pState->mRunComboAdded[0]) text = 0;
            _StyleTracker_pState->mRunComboAdded[0] = 1;
        } else {
            if (_StyleTracker_pState->mRunComboAdded[1]) text = 0;
            _StyleTracker_pState->mRunComboAdded[1] = 1;
        }
    }
    if (text != 0) {
        unsigned int length = strlen(side == 0 ? _StyleTracker_pState->mTeamZeroComboText : _StyleTracker_pState->mTeamOneComboText);
        length += strlen(_StyleTracker_aszComboLabels[text]);
        length += strlen(_StyleTracker_szComboSeparator);
        length++;
        if (length <= 249) {
            int current = strlen(side == 0 ? _StyleTracker_pState->mTeamZeroComboText : _StyleTracker_pState->mTeamOneComboText);
            if (current != (int)strlen(_StyleTracker_szEmptyCombo)) strcat(side == 0 ? _StyleTracker_pState->mTeamZeroComboText : _StyleTracker_pState->mTeamOneComboText, _StyleTracker_szComboSeparator);
            strcat(side == 0 ? _StyleTracker_pState->mTeamZeroComboText : _StyleTracker_pState->mTeamOneComboText, _StyleTracker_aszComboLabels[text]);
        }
        StyleTrackerSetComboWeight(side, StyleTrackerGetComboWeight(side) + value);
    }
}

extern "C" void StyleTrackerAccumulateRunTime(void) {
    Object_80039F5C *p = _StyleTracker_pState->mpRunPlayer;
    int team = p->mIdBytes[2] ^ 1;
    float distance;
    fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
    unsigned int limit;
    if (distance < 5.0f) limit = 1;
    else if (distance < 10.0f) limit = 3;
    else limit = 5;
    if ((unsigned int)++_StyleTracker_pState->mRunTicks >= limit) {
        Object_80039F5C *carrier = BallGetCurrentHolder();
        if (carrier) {
            if (carrier->mMotion.mUnknown28 == 0.0f) _StyleTracker_pState->mRunTime += 3;
            else _StyleTracker_pState->mRunTime++;
        }
        _StyleTracker_pState->mRunTicks = 0;
    }
}

extern "C" void StyleTrackerProcessEvent(int id, int team, int count) {
    if (_StyleTracker_bEnabled == 0) return;
    int limit = 0;
    int flag = 0;
    if (id == 99) StyleTrackerFinishPendingContact(0);
    if (id <= 126) {
        StyleTrackerAwardEvent(team, id, count);
        if (id == 23 || id == 24 || id == 19 || id == 20 || id == 21 || id == 22) _StyleTracker_pState->mPassOccurred = 1;
        return;
    }
    if (id == 128) {
        _StyleTracker_aiPlayStylePoints[0] = 0; _StyleTracker_aiPlayStylePoints[1] = 0;
        _StyleTracker_aiPlayPitches[0] = 0; _StyleTracker_aiPlayPitches[1] = 0;
        _StyleTracker_acConsecutivePitches[0] = 0; _StyleTracker_acConsecutivePitches[1] = 0;
        _StyleTracker_acLongestPitchChain[0] = 0; _StyleTracker_acLongestPitchChain[1] = 0;
        _StyleTracker_pState->mPitchCounts[0] = 0; _StyleTracker_pState->mPitchCounts[1] = 0;
        _StyleTracker_abQbStopThisPlay[0] = 0; _StyleTracker_abQbStopThisPlay[1] = 0;
        _StyleTracker_abUserQbStopThisPlay[0] = 0; _StyleTracker_abUserQbStopThisPlay[1] = 0;
        _StyleTracker_abCatchThisPlay[0] = 0; _StyleTracker_abCatchThisPlay[1] = 0;
        _StyleTracker_abStylePassThisPlay[0] = 0; _StyleTracker_abStylePassThisPlay[1] = 0;
        _StyleTracker_abCatchOpportunity[0] = 0; _StyleTracker_abCatchOpportunity[1] = 0;
        StyleTrackerSetComboWeight(0, 0); StyleTrackerSetComboWeight(1, 0);
        signed char y = (signed char)(int)fn_80178A2C();
        _StyleTracker_pState->mDistanceToGoal = y - (signed char)(int)fn_80177FE0().mY;
        StyleTrackerResetRun();
        _StyleTracker_pState->mpContactPlayer = 0;
        _StyleTracker_pState->mUserPlayerCount = 0;
        _StyleTracker_pState->mSavedRunAward = 0;
        _StyleTracker_pState->mSavedRunMeter = 0;
        _StyleTracker_pState->mMeterFilledThisPlay[0] = _StyleTracker_pState->mMeterFilledThisPlay[1] = 0;
        _StyleTracker_pState->mPlayStartTotal[0] = StyleTrackerGetTotal(0);
        _StyleTracker_pState->mPlayStartTotal[1] = StyleTrackerGetTotal(1);
        for (int i = 6; i < 69; i++) _StyleTracker_pState->mPlayFlags[i] = 0;
        return;
    }
    if (id != 129 || _StyleTracker_pState->mPlaySettled) return;
    _StyleTracker_pState->mPlaySettled = 1;
    if (_StyleTracker_pState->mOffenseTouchdown) {
        _StyleTracker_pState->mPlayYardage = _StyleTracker_pState->mDistanceToGoal;
        _StyleTracker_pState->mValidYardage = 1;
    } else if (fn_80177F7C() != 6) {
        if (fn_80178348() == fn_80178308()) {
        float first = fn_80178A2C();
        float second = fn_80178A2C();
        _StyleTracker_pState->mPlayYardage = ((signed char)(int)first - (signed char)(int)fn_80178070().mY) -
                                     ((signed char)(int)second - (signed char)(int)fn_80177FE0().mY);
        _StyleTracker_pState->mValidYardage = 1;
        } else {
            _StyleTracker_pState->mValidYardage = 0;
        }
    } else {
        _StyleTracker_pState->mValidYardage = 0;
    }
    StyleTrackerFinishPendingContact(0);
    StyleTrackerFinishOtherMoves(67);
    StyleTrackerFinishDefensiveMove(0);
    StyleTrackerClearPendingDisplay(0); StyleTrackerClearPendingDisplay(1);
    _StyleTracker_pState->mQueueDisplay[0] = 1;
    StyleTrackerFinishRun(); StyleTrackerAwardCompletedRun();
    if (_StyleTracker_pState->mTouchdownPending) StyleTrackerAwardTouchdown();
    else if (_StyleTracker_pState->mConversionPending || _StyleTracker_pState->mDefensiveConversionPending) StyleTrackerAwardConversion();
    else { StyleTrackerAwardPassGain(); StyleTrackerAwardRushGain(); }
    StyleTrackerAwardDefensiveOutcome(); StyleTrackerAwardTurnoverOnDowns(); StyleTrackerAwardTouchback(); StyleTrackerAwardFirstDown(); StyleTrackerAwardFailedConversion();
    if (_StyleTracker_pState->mMatchSettled == 0) {
        switch (fn_801788D8(&limit)) {
        case 0:
            if (fn_801787DC(1) >= limit) StyleTrackerAwardVictory(1, limit - fn_801787DC(0));
            else if (fn_801787DC(0) >= limit) StyleTrackerAwardVictory(0, limit - fn_801787DC(1));
            break;
        case 1:
            if (_StyleTracker_cWinner == 1) StyleTrackerAwardVictory(1, limit - StyleTrackerGetTotal(0));
            else if (_StyleTracker_cWinner == 0) StyleTrackerAwardVictory(0, limit - StyleTrackerGetTotal(1));
            break;
        case 2:
            break;
        }
    }
    StyleTrackerAwardCombo(0, StyleTrackerCanAwardCombo(0)); StyleTrackerAwardCombo(1, StyleTrackerCanAwardCombo(1));
    if (ChallengeIsActive()) {
        Challenge_t *object = ChalGetCurrent();
        if (ChallengeHasGoalType(object, 20, 0) || ChallengeHasGoalType(object, 31, 0)) flag = 1;
    }
    if ((_StyleTracker_pState->mMatchSettled == 0 || flag) && fn_800A8740() == 0) { fn_800A72B4(); fn_800A7B5C(); }
    StyleTrackerShowMeter(0, _StyleTracker_pState->mTeamZeroMeter, 0, 1); StyleTrackerShowMeter(1, _StyleTracker_pState->mTeamOneMeter, 0, 1);
    StyleTrackerShowMeter(0, _StyleTracker_pState->mTeamZeroMeter, 0, 0); StyleTrackerShowMeter(1, _StyleTracker_pState->mTeamOneMeter, 0, 0);
    if (fn_80178348() != fn_80178308() || fn_80177C38() != 0) _StyleTracker_pState->unk_0x1ECE = 1;
    else _StyleTracker_pState->unk_0x1ECE = 0;
    _StyleTracker_pState->mPlayStyleGain[0] = StyleTrackerGetTotal(0) - _StyleTracker_pState->mPlayStartTotal[0];
    _StyleTracker_pState->mPlayStyleGain[1] = StyleTrackerGetTotal(1) - _StyleTracker_pState->mPlayStartTotal[1];
    if (_StyleTracker_pState->mPlayStyleGain[fn_80178320()] > _StyleTracker_pState->mPlayStyleGain[fn_80178308()]) {
        if (_StyleTracker_pState->mPlayStyleGain[fn_80178320()] > 0) fn_8017E3CC(fn_80178320());
    } else if (_StyleTracker_pState->mPlayStyleGain[fn_80178308()] > 0) fn_8017E3CC(fn_80178308());
    fn_8017C5A0(0, _StyleTracker_pState->mPlayStyleGain[0]); fn_8017C5A0(1, _StyleTracker_pState->mPlayStyleGain[1]);
    fn_8017C5CC(0, _StyleTracker_aiPlayStylePoints[0]); fn_8017C5CC(1, _StyleTracker_aiPlayStylePoints[1]);
    fn_8017C5F8(0, _StyleTracker_aiPlayPitches[0]); fn_8017C5F8(1, _StyleTracker_aiPlayPitches[1]);
    if (_StyleTracker_abQbStopThisPlay[0]) fn_8017C800(0, ++_StyleTracker_acQbStopStreak[0]); else if (fn_80178360() == 0) _StyleTracker_acQbStopStreak[0] = 0;
    if (_StyleTracker_abQbStopThisPlay[1]) fn_8017C800(1, ++_StyleTracker_acQbStopStreak[1]); else if (fn_80178360() == 1) _StyleTracker_acQbStopStreak[1] = 0;
    if (_StyleTracker_abUserQbStopThisPlay[0]) fn_8017C82C(0, ++_StyleTracker_acUserQbStopStreak[0]); else if (fn_80178360() == 0) _StyleTracker_acUserQbStopStreak[0] = 0;
    if (_StyleTracker_abUserQbStopThisPlay[1]) fn_8017C82C(1, ++_StyleTracker_acUserQbStopStreak[1]); else if (fn_80178360() == 1) _StyleTracker_acUserQbStopStreak[1] = 0;
    if (_StyleTracker_abCatchThisPlay[0]) fn_8017C884(0, ++_StyleTracker_acCatchStreak[0]); else if (_StyleTracker_abCatchOpportunity[0] && fn_80178348() == 0) _StyleTracker_acCatchStreak[0] = 0;
    if (_StyleTracker_abCatchThisPlay[1]) fn_8017C884(1, ++_StyleTracker_acCatchStreak[1]); else if (_StyleTracker_abCatchOpportunity[1] && fn_80178348() == 1) _StyleTracker_acCatchStreak[1] = 0;
    if (_StyleTracker_abCatchThisPlay[0] && _StyleTracker_abStylePassThisPlay[0]) fn_8017C908(0, ++_StyleTracker_acStyleCatchStreak[0]); else if (_StyleTracker_abCatchOpportunity[0] && fn_80178348() == 0) _StyleTracker_acStyleCatchStreak[0] = 0;
    if (_StyleTracker_abCatchThisPlay[1] && _StyleTracker_abStylePassThisPlay[1]) fn_8017C908(1, ++_StyleTracker_acStyleCatchStreak[1]); else if (_StyleTracker_abCatchOpportunity[1] && fn_80178348() == 1) _StyleTracker_acStyleCatchStreak[1] = 0;
    fn_8017C98C(0, _StyleTracker_acLongestPitchChain[0]); fn_8017C98C(1, _StyleTracker_acLongestPitchChain[1]);
}

extern "C" void StyleTrackerAwardImmediateEvent(int a, int b) {
    int flag = 0;

    switch (a) {
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 114:
        flag = 1;
        break;
    }
    StyleTrackerTraceEvent(62);
    StyleTrackerFinishPendingContact(1);
    if (flag) {
        StyleTrackerFinishStylePass();
    } else {
        StyleTrackerFinishOtherMoves(0);
        StyleTrackerFinishDefensiveMove(0);
    }
    StyleTrackerProcessEvent(a, b, 1);
}

extern "C" void StyleTrackerFinishPendingContact(int a) {
    int notify = 0;

    StyleTrackerTraceEvent(63);
    if (_StyleTracker_pState->mContactPending) {
        StyleTrackerTraceEvent(64);
        if (a == 0 || (a == 1 && _StyleTracker_pState->mpContactPlayer != BallGetCurrentHolder())) {
            notify = 1;
            StyleTrackerTraceEvent(65);
            StyleTrackerFinishDefensiveMove(0);
            StyleTrackerAwardEvent(fn_80178360(), 95, 1);
        }
        if (notify) {
            fn_800AE7F0(11, fn_80178360(), _StyleTracker_pState->mpContactPlayer);
        }
        _StyleTracker_pState->mContactSeen = 0;
        _StyleTracker_pState->mContactPending = 0;
    }
}

extern "C" void StyleTrackerFinishStylePass(void) {
    if (_StyleTracker_pState->mStylePassReleased) {
        _StyleTracker_pState->mStylePassReleased = 0;
        if (_StyleTracker_pState->mNinjaPass) {
            StyleTrackerProcessEvent(11, fn_80178348(), 1);
            _StyleTracker_pState->mNinjaPass = 0;
            fn_80156C78(24, 1);
        } else {
            StyleTrackerProcessEvent(10, fn_80178348(), 1);
        }
    }
}

extern "C" void StyleTrackerAwardCompletedRun(void) {
    if (_StyleTracker_pState->mRunCompleted) {
        StyleTrackerAwardEvent(_StyleTracker_pState->mRunTeam, 66, _StyleTracker_pState->mCompletedRunTime);
        StyleTrackerResetRun();
        _StyleTracker_pState->mRunCompleted = 0;
        fn_800AE7F0(5, (unsigned char)_StyleTracker_pState->mRunTeam, _StyleTracker_pState->mpRunPlayer);
    }
}

extern "C" void StyleTrackerResetRun(void) {
    StyleTrackerTraceEvent(50);
    _StyleTracker_pState->mRunTime = 0;
    _StyleTracker_pState->mRunTicks = 0;
    _StyleTracker_pState->mRunAwardValue = 0;
    _StyleTracker_pState->mRunMeterValue = 0;
    _StyleTracker_pState->mpRunPlayer = 0;
    _StyleTracker_pState->mRunActive = 0;
    _StyleTracker_pState->mRunRequested = 0;
    _StyleTracker_pState->mRunEndTicks = 0;
    AudmonEventPost(122, 0);
}

extern "C" int StyleTrackerCanAwardCombo(int a) {
    int result = 0;

    if (fn_80178360() == a) {
        if (_StyleTracker_pState->mDefensiveConversion || _StyleTracker_pState->mDefenseTouchdown) {
            result = 1;
        } else if (fn_80177F7C() == 6) {
            if (!_StyleTracker_pState->mConversionPending) {
                result = 1;
            }
        } else if (fn_80178360() == fn_80178308() || _StyleTracker_pState->mPlayYardage <= 0) {
            result = 1;
        }
    } else if (fn_80177F7C() == 6) {
        if (_StyleTracker_pState->mConversion) {
            result = 1;
        }
    } else if (_StyleTracker_pState->mPlayYardage > 0) {
        result = 1;
    }
    if (fn_801486A0() == 0) {
        result = a == 1;
    }
    return result;
}

extern "C" void StyleTrackerAwardCombo(int a, int b) {
    int found;

    if (_StyleTracker_bEnabled) {
        if (b && _StyleTracker_bCombosEnabled) {
            StyleTrackerCalculateAward(a, 108, StyleTrackerGetComboWeight(a), 0, 0, &found, 0, 0, 0, 0);
            if (found) {
                StyleTrackerShowCombo(a);
                StyleTrackerFlushPendingDisplay(a, 1, 1);
                StyleTrackerClearPendingDisplay(a);
                StyleTrackerAwardEvent(a, 108, StyleTrackerGetComboWeight(a));
                StyleTrackerFlushPendingDisplay(a, 1, 0);
            } else {
                StyleTrackerFlushPendingDisplay(a, 1, 1);
            }
        } else {
            StyleTrackerFlushPendingDisplay(a, 1, 1);
        }
    }
}

extern "C" void StyleTrackerAwardTurnoverOnDowns(void) {
    if (_StyleTracker_pState->mTurnoverOnDowns) {
        StyleTrackerAwardEvent(fn_80178360(), 99, 1);
    }
}

extern "C" void StyleTrackerAwardTouchback(void) {
    if (_StyleTracker_pState->mTouchback) {
        StyleTrackerAwardEvent(_StyleTracker_pState->mTouchbackTeam, 100, 1);
    }
}

extern "C" void StyleTrackerAwardDefensiveOutcome(void) {
    if (_StyleTracker_pState->mSafety && _StyleTracker_pState->mQbStop) {
        StyleTrackerAwardEvent(fn_80178360(), 102, 1);
    } else if (_StyleTracker_pState->mSafety && (_StyleTracker_pState->mUserQbStop || _StyleTracker_pState->mUserLoss)) {
        StyleTrackerAwardEvent(fn_80178360(), 103, 1);
    } else if (_StyleTracker_pState->mQbStop) {
        StyleTrackerAwardEvent(fn_80178360(), 76, 1);
    } else if (_StyleTracker_pState->mUserQbStop) {
        StyleTrackerAwardEvent(fn_80178360(), 77, 1);
    } else if (_StyleTracker_pState->mSafety) {
        StyleTrackerAwardEvent(_StyleTracker_pState->mSafetyTeam, 101, 1);
    } else if (_StyleTracker_pState->mLoss) {
        StyleTrackerAwardEvent(fn_80178360(), 96, 1);
    } else if (_StyleTracker_pState->mUserLoss) {
        StyleTrackerAwardEvent(fn_80178360(), 98, 1);
    } else if (_StyleTracker_pState->mTackleContestStop) {
        StyleTrackerAwardEvent(fn_80178360(), 78, 1);
    } else if (_StyleTracker_pState->mNoControlLoss) {
        StyleTrackerAwardEvent(fn_80178360(), 97, 1);
    }
}

extern "C" void StyleTrackerAwardFirstDown(void) {
    if (_StyleTracker_pState->mFirstDown) {
        if (_StyleTracker_pState->mStyleFirstDown) {
            StyleTrackerAwardEvent(fn_80178348(), 71, 1);
        } else {
            StyleTrackerAwardEvent(fn_80178348(), 70, 1);
        }
    }
}

extern "C" void StyleTrackerAwardVictory(int team, unsigned int value) {
    int limit = 0;

    fn_801788D8(&limit);
    if (fn_800A8740() == 0) {
        if (fn_800A8488(0)) {
            fn_800A7A0C(0);
        }
        if (fn_800A8488(1)) {
            fn_800A7A0C(1);
        }
    }
    unsigned int percent;
    if (value == limit) {
        percent = 100;
    } else {
        percent = value * 100 / limit;
    }
    if (ChallengeIsActive() == 0 && fn_801486A0() != 5) {
        if (fn_800A84C8() != 0 && fn_800A8444((unsigned char)team) != 0) {
            StyleTrackerAwardEvent(team, 107, percent);
        } else {
            StyleTrackerAwardEvent(team, 106, percent);
        }
    }
    _StyleTracker_pState->mMatchSettled = 1;
}

extern "C" void StyleTrackerAwardConversion(void) {
    int value = fn_80179138();

    if (_StyleTracker_pState->mConversionPending) {
        if (value == 2) {
            StyleTrackerAwardEvent(fn_80178348(), 2, 1);
        } else {
            StyleTrackerAwardEvent(fn_80178348(), 3, 1);
        }
    } else if (_StyleTracker_pState->mDefensiveConversionPending) {
        StyleTrackerAwardEvent(fn_80178360(), 4, 1);
    }
}

extern "C" void StyleTrackerAwardFailedConversion(void) {
    if (_StyleTracker_pState->mFailedConversionPending) {
        StyleTrackerAwardEvent(fn_80178360(), 5, 1);
    }
}

extern "C" void StyleTrackerAwardTouchdown(void) {
    switch (_StyleTracker_pState->mTouchdownEvent) {
    case 67:
        StyleTrackerAwardEvent(fn_80178348(), 67, 1);
        break;
    case 0:
        StyleTrackerAwardEvent(fn_80178348(), 0, _StyleTracker_pState->mDistanceToGoal);
        break;
    case 91:
        StyleTrackerAwardEvent(fn_80178360(), 91, 1);
        break;
    case 68:
        StyleTrackerAwardEvent(fn_80178348(), 68, 1);
        break;
    case 1:
        StyleTrackerAwardEvent(fn_80178348(), 1, _StyleTracker_pState->mDistanceToGoal);
        break;
    case 69:
        StyleTrackerAwardEvent(fn_80178348(), 69, 1);
        break;
    case 92:
        StyleTrackerAwardEvent(fn_80178360(), 92, 1);
        break;
    case 93:
        StyleTrackerAwardEvent(fn_80178360(), 93, 1);
        break;
    case 94:
        StyleTrackerAwardEvent(fn_80178348(), 94, 1);
        break;
    case 126:
        StyleTrackerAwardEvent(fn_80178348(), 126, 1);
        break;
    }
}

extern "C" void StyleTrackerAwardPassGain(void) {
    if (_StyleTracker_pState->mValidYardage && !fn_80177C38() && !_StyleTracker_pState->mOffenseLostBall &&
        _StyleTracker_pState->mPassOccurred && _StyleTracker_pState->mPlayYardage > 0) {
        StyleTrackerAwardEvent(fn_80178348(), 26, _StyleTracker_pState->mPlayYardage);
    }
}

extern "C" void StyleTrackerAwardRushGain(void) {
    if (_StyleTracker_pState->mValidYardage && !fn_80177C38() && !_StyleTracker_pState->mOffenseLostBall) {
        if (!_StyleTracker_pState->mPassOccurred && _StyleTracker_pState->mPlayYardage > 0) {
            StyleTrackerAwardEvent(fn_80178348(), 25, _StyleTracker_pState->mPlayYardage);
        }
    }
}

extern "C" void StyleTrackerOnPossessionLost(void) {
    if (_StyleTracker_pState->mRunRequested) {
        fn_800AE7F0(0, fn_80178308(), 0);
    }
    if ((fn_80177C38() & 1) == 0) {
        _StyleTracker_pState->mOffenseLostBall = 1;
        StyleTrackerSetComboWeight(fn_80178348(), 0);
    } else {
        _StyleTracker_pState->mDefenseLostBall = 1;
        StyleTrackerSetComboWeight(fn_80178360(), 0);
    }
    if (_StyleTracker_pState->mpRunPlayer) {
        if (!_StyleTracker_pState->mSavedRunAwardPending) {
            _StyleTracker_pState->mSavedRunAward = _StyleTracker_pState->mRunAwardValue;
            _StyleTracker_pState->mSavedRunMeter = _StyleTracker_pState->mRunMeterValue;
            _StyleTracker_pState->mSavedRunAwardPending = 1;
        }
        StyleTrackerCancelRun(_StyleTracker_pState->mpRunPlayer->mIdBytes[2]);
    }
    StyleTrackerFinishOtherMoves(0);
    StyleTrackerFinishDefensiveMove(0);
}

extern "C" void StyleTrackerOnPassReleased(void) {
    _StyleTracker_pState->mPassReleased = 1;
    _StyleTracker_pState->mFakeout = 0;
    if (_StyleTracker_pState->mStylePassPending) {
        StyleTrackerTraceEvent(9);
        _StyleTracker_pState->mStylePassReleased = 1;
        StyleTrackerProcessEvent(8, fn_80178348(), 1);
    }
}

extern "C" void StyleTrackerOnPitchReleased(void) {
    StyleTrackerTraceEvent(17);
    if (_StyleTracker_pState->mPitchActive || _StyleTracker_pState->mStylePitch) {
        _StyleTracker_pState->mPitchReleased = 1;
        _StyleTracker_pState->mPitchTeam = fn_80178308();
        StyleTrackerFinishOtherMoves(20);
        if (_StyleTracker_pState->mStylePitch) {
            StyleTrackerProcessEvent(16, fn_80178308(), _StyleTracker_pState->mPitchCounts[fn_80178308()] + 1);
        } else {
            StyleTrackerProcessEvent(13, fn_80178308(), _StyleTracker_pState->mPitchCounts[fn_80178308()] + 1);
        }
    }
}

extern "C" int StyleTrackerFinishStiffArm(int a) {
    int event = 28;

    StyleTrackerTraceEvent(48);
    if (_StyleTracker_pState->mStiffArmActive) {
        if (_StyleTracker_pState->mStiffArmSucceeded) {
            if (a) {
                event = 29;
            }
            if (event == 29) {
                Object_80039F5C *p = _StyleTracker_pState->mpStiffArmPlayer;
                Record_800B15FC *pRecord = fn_800B15FC();

                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = p->mMotion.mPos.mX;
                pRecord->mUnknown10 = p->mMotion.mPos.mY;
                pRecord->mUnknown14 = 58;
                fn_800B1508();
            }
        }
        StyleTrackerProcessEvent(event, fn_80178308(), 1);
        _StyleTracker_pState->mStiffArmSucceeded = 0;
        _StyleTracker_pState->mStiffArmActive = 0;
    }
    return event == 29;
}

extern "C" void StyleTrackerFinishOtherMoves(int a) {
    if (a != 67 && a != 11 && a != 1 && a != 14 && a != 15 && a != 16 && a != 24 && a != 18) {
        StyleTrackerFinishRun();
        _StyleTracker_pState->mStyleMove = 0;
        _StyleTracker_pState->mWallMove = 0;
    }
    if (_StyleTracker_pState->mJukeActive && a != 14) {
        if (_StyleTracker_pState->mWallMove) {
            StyleTrackerProcessEvent(41, _StyleTracker_pState->mJukeTeam, 1);
        } else if (_StyleTracker_pState->mStyleMove) {
            StyleTrackerProcessEvent(37, _StyleTracker_pState->mJukeTeam, 1);
        } else {
            StyleTrackerProcessEvent(33, _StyleTracker_pState->mJukeTeam, 1);
        }
        _StyleTracker_pState->mFakeout = 0;
        _StyleTracker_pState->mJukeActive = 0;
    }
    if (_StyleTracker_pState->mSpinActive && a != 15) {
        if (_StyleTracker_pState->mStyleMove) {
            StyleTrackerProcessEvent(49, _StyleTracker_pState->mSpinTeam, 1);
        } else {
            StyleTrackerProcessEvent(45, _StyleTracker_pState->mSpinTeam, 1);
        }
        _StyleTracker_pState->mFakeout = 0;
        _StyleTracker_pState->mSpinActive = 0;
    }
    if (_StyleTracker_pState->mStiffArmActive && a != 24 && a != 1) {
        StyleTrackerProcessEvent(28, _StyleTracker_pState->mStiffArmTeam, 1);
        _StyleTracker_pState->mStiffArmActive = 0;
        _StyleTracker_pState->mStiffArmSucceeded = 0;
    }
    if (_StyleTracker_pState->mHurdleActive && a != 16 && a != 1) {
        if (_StyleTracker_pState->mWallMove) {
            StyleTrackerProcessEvent(62, _StyleTracker_pState->mHurdleTeam, 1);
        } else if (_StyleTracker_pState->mStyleMove) {
            StyleTrackerProcessEvent(59, _StyleTracker_pState->mHurdleTeam, 1);
        } else {
            StyleTrackerProcessEvent(56, _StyleTracker_pState->mHurdleTeam, 1);
        }
        _StyleTracker_pState->mHurdleActive = 0;
    }
    if (_StyleTracker_pState->mPitchReleased && a != 20 && (a < 1 || a > 5)) {
        if (_StyleTracker_pState->mStylePitch) {
            StyleTrackerProcessEvent(17, _StyleTracker_pState->mPitchTeam, 1);
        } else {
            StyleTrackerProcessEvent(14, _StyleTracker_pState->mPitchTeam, 1);
        }
        _StyleTracker_pState->mPitchReleased = 0;
        _StyleTracker_pState->mPitchActive = 0;
        _StyleTracker_pState->mStylePitch = 0;
    }
    if (_StyleTracker_pState->mStylePassReleased && a != 27 && (a < 1 || a > 5)) {
        Object_80039F5C *p = BallGetCurrentHolder();

        if (p == 0 || p->mIdBytes[2] == fn_80178360() || fn_801787A0()) {
            StyleTrackerProcessEvent(9, fn_80178348(), 1);
            _StyleTracker_pState->mStylePassReleased = 0;
        }
    }
}

extern "C" void StyleTrackerFinishDefensiveMove(int a) {
    if (_StyleTracker_pState->mDefensiveMoveActive && a != 29) {
        if (_StyleTracker_pState->mStyleDefensiveMove) {
            StyleTrackerProcessEvent(83, fn_80178360(), 1);
        } else {
            StyleTrackerProcessEvent(82, fn_80178360(), 1);
        }
        _StyleTracker_pState->mDefensiveMoveActive = 0;
        _StyleTracker_pState->mStyleDefensiveMove = 0;
    }
}

extern "C" int StyleTrackerIsCurrentActorUserControlled(void) {
    int result = 0;
    Object_80039F5C *p = fn_8017876C();

    if (p) {
        result = (p->mFlags >> 14) & 1;
    }
    return result;
}

extern "C" int StyleTrackerIsFumbleForcerUserControlled(void) {
    Object_80039F5C *p = fn_8017876C();
    unsigned char result = 0;
    Object_80039F5C *pTarget = 0;

    if (!p) {
        Object_80039F5C *pBall = BallGetCurrentHolder();

        if (pBall || (pBall = BallGetCurrentLastHolder())) {
            if (pBall->mpState->mId == 16) {
                pTarget = fn_8009BCE8(&pBall->mUnknown336);
            }
        }
    }
    if (p) {
        result = (p->mFlags >> 14) & 1;
    } else if (pTarget) {
        result = pTarget->mUnknown8 != 255 ? 1 : 0;
    }
    return result;
}

extern "C" void StyleTrackerResetStateCallback() {
}

extern "C" int StyleTrackerCreateState(void *p, int value) {
    StyleTrackerResetStateCallback();
    return 0;
}

extern "C" int StyleTrackerDestroyState(void *p, int value) {
    return 0;
}

extern "C" int StyleTrackerCompareState(void *p, void *q) {
    if (q == 0) {
        return fn_80238278(p, sizeof(StyleTrackerState_t), 0);
    }
    return fn_80238258(p, q, sizeof(StyleTrackerState_t));
}

extern "C" int StyleTrackerSaveState(void *p, void *pBuffer) {
    *(StyleTrackerState_t *)pBuffer = *(StyleTrackerState_t *)p;
    return 1;
}

extern "C" int StyleTrackerLoadState(void *p, void *pBuffer) {
    *(StyleTrackerState_t *)p = *(StyleTrackerState_t *)pBuffer;
    return 1;
}

extern "C" int StyleTrackerGetStateSize(void *p) {
    return sizeof(StyleTrackerState_t);
}

extern "C" void StyleTrackerStartRunEffect(void) {
    Object_80039F5C *p = _StyleTracker_pState->mpRunEffectPlayer;

    if (p != 0) {
        fn_800310C0(lbl_803EA368, 56, p, &p->mMotion.mPos, &p->mMotion.mFacing);
    }
}

extern "C" unsigned short StyleTrackerGetEventCount(int side, int index) {
    return (side == 0 ? _StyleTracker_pState->mTeamZeroEventCounts : _StyleTracker_pState->mTeamOneEventCounts)[index];
}

extern "C" void StyleTrackerSetEventCount(int side, int index, int value) {
    (side == 0 ? _StyleTracker_pState->mTeamZeroEventCounts : _StyleTracker_pState->mTeamOneEventCounts)[index] = value;
}

extern "C" int StyleTrackerGetMeter(int side) {
    return *(side == 0 ? &_StyleTracker_pState->mTeamZeroMeter : &_StyleTracker_pState->mTeamOneMeter);
}

extern "C" float StyleTrackerGetMeterFraction(int side) {
    int value = StyleTrackerGetMeter(side);
    float result;
    if (value == 0) result = 0.0f;
    else if (value == _StyleTracker_iMeterThreshold) result = 1.0f;
    else result = (float)value / (float)_StyleTracker_iMeterThreshold;
    return result;
}

extern "C" void StyleTrackerSetMeter(int side, int value, int arg) {
    if (fn_800A8740() == 0) {
        if (value > _StyleTracker_iMeterThreshold) {
            value = _StyleTracker_iMeterThreshold;
        }
        if (value < 0) {
            value = 0;
        }
        if (fn_800A8F84(side) == 0 || value < *(side == 0 ? &_StyleTracker_pState->mTeamZeroMeter : &_StyleTracker_pState->mTeamOneMeter)) {
            if (value == 0 && StyleTrackerGetMeter(side) > 0) {
                AudmonEventPostArgs(6, 0, side, 0, 0);
            }
            if (value == _StyleTracker_iMeterThreshold && StyleTrackerGetMeter(side) < _StyleTracker_iMeterThreshold) {
                _StyleTracker_pState->mMeterFilledThisPlay[side] = 1;
                AudmonEventPostArgs(5, 0, side, 0, 0);
            }
            if (value < *(side == 0 ? &_StyleTracker_pState->mTeamZeroMeter : &_StyleTracker_pState->mTeamOneMeter)) {
                StyleTrackerShowMeter(side, value, arg, 0);
            }
            StyleTrackerShowMeter(side, value, arg, 1);
            *(side == 0 ? &_StyleTracker_pState->mTeamZeroMeter : &_StyleTracker_pState->mTeamOneMeter) = value;
        }
    } else {
        *(side == 0 ? &_StyleTracker_pState->mTeamZeroMeter : &_StyleTracker_pState->mTeamOneMeter) = 0;
    }
}

extern "C" void StyleTrackerSetMeterFraction(int side, float t, int arg) {
    int value = 0;
    if (!(t <= 0.0f)) {
        if (!(t < 1.0f)) value = _StyleTracker_iMeterThreshold;
        else value = (int)(t * (float)_StyleTracker_iMeterThreshold);
    }
    StyleTrackerSetMeter(side, value, arg);
}

extern "C" int StyleTrackerGetTotal(int side) {
    return *(side == 0 ? &_StyleTracker_pState->mTeamZeroTotal : &_StyleTracker_pState->mTeamOneTotal);
}

extern "C" void StyleTrackerSetTotal(int side, int value) {
    int limit = 0;

    if (value < 0) {
        value = 0;
    }
    if (_StyleTracker_cWinner == 2 && fn_801788D8(&limit) == 1 && value >= limit) {
        _StyleTracker_cWinner = side;
        if (ChallengeIsActive() == 0) {
            AudmonEventPostArgs(94, 0, _StyleTracker_cWinner, 0, 0);
            fn_80178370();
        }
    }
    *(side == 0 ? &_StyleTracker_pState->mTeamZeroTotal : &_StyleTracker_pState->mTeamOneTotal) = value;
}

extern "C" int StyleTrackerGetWinner() {
    return _StyleTracker_cWinner;
}

extern "C" void StyleTrackerOnTouchdown(void) {
    int value;

    StyleTrackerTraceEvent(44);
    if (fn_80178348() == fn_80178308()) {
        _StyleTracker_pState->mOffenseTouchdown = 1;
    } else {
        _StyleTracker_pState->mDefenseTouchdown = 1;
    }
    value = StyleTrackerUpdateRun(0, 0, 0);
    if (value == 0) {
        value = StyleTrackerUpdateRun(0, 0, 0);
    }
    if (fn_80177C38() == 1 && _StyleTracker_pState->mDefenseLostBall == 0) {
        _StyleTracker_pState->mTouchdownPending = 1;
        if (_StyleTracker_pState->mIntercepted != 0) {
            _StyleTracker_pState->mTouchdownEvent = 92;
        } else if (_StyleTracker_pState->mPitchStolen != 0) {
            _StyleTracker_pState->mTouchdownEvent = 93;
        } else {
            _StyleTracker_pState->mTouchdownEvent = 91;
        }
    } else if (fn_80177C38() == 0 && _StyleTracker_pState->mOffenseLostBall == 0) {
        if (fn_800A84C8() != 0 && fn_800A8444(fn_80178320()) != 0) {
            _StyleTracker_pState->mTouchdownPending = 1;
            _StyleTracker_pState->mTouchdownEvent = 94;
        } else if (_StyleTracker_pState->unk_0x1ECE != 0) {
            _StyleTracker_pState->mTouchdownPending = 1;
            _StyleTracker_pState->mTouchdownEvent = 69;
        } else if (_StyleTracker_pState->mPassOccurred != 0 && _StyleTracker_pState->mOffenseLostBall == 0) {
            if (value != 0) {
                _StyleTracker_pState->mTouchdownPending = 1;
                _StyleTracker_pState->mTouchdownEvent = 67;
            } else {
                _StyleTracker_pState->mTouchdownPending = 1;
                _StyleTracker_pState->mTouchdownEvent = 0;
            }
        } else if (value != 0) {
            _StyleTracker_pState->mTouchdownPending = 1;
            _StyleTracker_pState->mTouchdownEvent = 68;
        } else {
            _StyleTracker_pState->mTouchdownPending = 1;
            _StyleTracker_pState->mTouchdownEvent = 1;
        }
    } else {
        _StyleTracker_pState->mTouchdownPending = 1;
        _StyleTracker_pState->mTouchdownEvent = 126;
    }
}

extern "C" void StyleTrackerOnCarrierStopped(float a) {
    StyleTrackerTraceEvent(40);
    if (fn_8017876C() != 0) {
        fn_800B1698(BallGetHolder(BallGetCurrent()), fn_8017876C());
    }
    if (fn_80177C38() == 0) {
        if (a < fn_80177FE0().mY && fn_80177F70() != 6) {
            if (fn_8017876C() != 0) {
                StyleTrackerTraceEvent(74);
                if (StyleTrackerIsCurrentActorUserControlled() != 0) {
                    _StyleTracker_pState->mUserLoss = 1;
                } else {
                    _StyleTracker_pState->mLoss = 1;
                }
            } else {
                StyleTrackerTraceEvent(75);
                _StyleTracker_pState->mNoControlLoss = 1;
            }
        }
    }
}

extern "C" void StyleTrackerOnSafety(void) {
    StyleTrackerTraceEvent(43);
    _StyleTracker_pState->mSafety = 1;
    if ((fn_80177C38() & 1) == 0) {
        _StyleTracker_pState->mSafetyTeam = fn_80178360();
    } else {
        _StyleTracker_pState->mSafetyTeam = fn_80178348();
    }
}

extern "C" void StyleTrackerOnTackle(Object_80039F5C *p, float a) {
    StyleTrackerTraceEvent(41);
    if (p != 0) {
        StyleTrackerFinishStiffArm(0);
        if (fn_80177C38() == 0) {
            if (fn_801650DC(fn_8016871C(fn_80178348())) != 0 && fn_801783AC(0) == 0 &&
                a <= fn_80177FE0().mY && (p->mFlags & 0x10000000)) {
                if (StyleTrackerIsCurrentActorUserControlled() != 0) {
                    _StyleTracker_pState->mUserQbStop = 1;
                } else {
                    _StyleTracker_pState->mQbStop = 1;
                }
            } else {
                if (a < fn_80177FE0().mY && fn_80177F70() != 6) {
                    if (StyleTrackerIsCurrentActorUserControlled() != 0) {
                        _StyleTracker_pState->mUserLoss = 1;
                    } else {
                        _StyleTracker_pState->mLoss = 1;
                    }
                } else if (_StyleTracker_pState->mTackleContest != 0) {
                    _StyleTracker_pState->mTackleContestStop = 1;
                }
            }
        }
    }
}

extern "C" void StyleTrackerOnBrokenTackle(Object_80039F5C *p) {
    StyleTrackerTraceEvent(39);
    if (p != 0 && !(p->mFlags & 0x10000)) {
        if (fn_801787A0() == 0 && p == BallGetCurrentHolder()) {
            StyleTrackerFinishOtherMoves(0);
            if (_StyleTracker_pState->mTackleContestAwarded == 0) {
                StyleTrackerProcessEvent(30, p->mIdBytes[2], 1);
            }
            _StyleTracker_pState->mTackleContestAwarded = 0;
        }
    }
}

extern "C" void StyleTrackerOnTackleContest(int flag, Object_80039F5C *p) {
    StyleTrackerTraceEvent(38);
    if (p == BallGetCurrentHolder()) {
        if (flag != 0) {
            _StyleTracker_pState->mTackleContest = 1;
        } else if (fn_801787A0() == 0) {
            StyleTrackerProcessEvent(31, fn_80178308(), 1);
            _StyleTracker_pState->mTackleContestAwarded = 1;
        }
    }
}

extern "C" void StyleTrackerOnTurnoverOnDowns(void) {
    StyleTrackerTraceEvent(37);
    _StyleTracker_pState->mTurnoverOnDowns = 1;
}

extern "C" void StyleTrackerOnTouchback(int flag) {
    StyleTrackerTraceEvent(42);
    if (_StyleTracker_pState->mTouchback == 0) {
        _StyleTracker_pState->mTouchback = 1;
        if ((fn_80177C38() & 1) == 0) {
            _StyleTracker_pState->mTouchbackTeam = fn_80178348();
        } else {
            _StyleTracker_pState->mTouchbackTeam = fn_80178360();
        }
        if (flag != 0) {
            _StyleTracker_pState->mTouchbackTeam = _StyleTracker_pState->mTouchbackTeam == 0;
        }
    }
}

extern "C" void StyleTrackerOnFirstDown(void) {
    StyleTrackerTraceEvent(36);
    if (fn_80177C38() == 0) {
        _StyleTracker_pState->mFirstDown = 1;
    }
}

extern "C" void StyleTrackerOnStyleFirstDown(void) {
    StyleTrackerTraceEvent(35);
    StyleTrackerFinishOtherMoves(0);
    fn_800AE7F0(12, fn_80178308(), BallGetCurrentHolder());
    _StyleTracker_pState->mStyleFirstDown = 1;
}

extern "C" void StyleTrackerOnConversion(void) {
    StyleTrackerTraceEvent(33);
    _StyleTracker_pState->mConversion = 1;
    if (fn_80177C38() == 0 && _StyleTracker_pState->mOffenseLostBall == 0) {
        _StyleTracker_pState->mConversionPending = 1;
    }
}

extern "C" void StyleTrackerOnDefensiveConversion(void) {
    StyleTrackerTraceEvent(32);
    _StyleTracker_pState->mDefensiveConversion = 1;
    if (_StyleTracker_pState->mDefenseLostBall == 0) {
        _StyleTracker_pState->mDefensiveConversionPending = 1;
    }
}

extern "C" void StyleTrackerOnFailedConversion(void) {
    StyleTrackerTraceEvent(34);
    _StyleTracker_pState->mFailedConversionPending = 1;
}

extern "C" void StyleTrackerOnFumbleRecovery(Object_80039F5C *p) {
    StyleTrackerTraceEvent(31);
    if (p != 0 && fn_801787A0() == 0 && fn_801BE648(p->mpUnknown792) != 234 &&
        fn_801BE648(p->mpUnknown792) != 238) {
        if (fn_80177C38() == 0 && p->mIdBytes[2] == fn_80178360() && _StyleTracker_pState->mSavedRunAwardPending != 0 &&
            _StyleTracker_pState->mSavedRunAward != 0) {
            _StyleTracker_pState->mApplySavedRunBonus = 1;
            StyleTrackerProcessEvent(90, p->mIdBytes[2], 1);
            _StyleTracker_pState->mApplySavedRunBonus = 0;
            _StyleTracker_pState->mSavedRunAwardPending = 0;
            _StyleTracker_pState->mSavedRunAward = 0;
            _StyleTracker_pState->mSavedRunMeter = 0;
        } else if (p->mFlags & 0x4000) {
            if (p->mIdBytes[2] == fn_80178308()) {
                StyleTrackerProcessEvent(89, p->mIdBytes[2], 1);
            } else {
                StyleTrackerProcessEvent(87, p->mIdBytes[2], 1);
            }
        } else if (p->mIdBytes[2] == fn_80178308()) {
            StyleTrackerProcessEvent(88, p->mIdBytes[2], 1);
        } else {
            StyleTrackerProcessEvent(86, p->mIdBytes[2], 1);
        }
        if (p->mIdBytes[2] == fn_80178320()) {
            Vector_80039F5C pos;

            BallGetPosition(BallGetCurrent(), &pos);
            _StyleTracker_pState->mPossessionStartY = -pos.mY;
            _StyleTracker_pState->mPitchCounts[fn_80178308()] = 0;
        }
    }
}

extern "C" void StyleTrackerOnFumble(Object_80039F5C *p, int team) {
    StyleTrackerTraceEvent(30);
    if (_StyleTracker_pState->mRunRequested != 0) {
        fn_800AE7F0(0, fn_80178308(), 0);
    }
    if (_StyleTracker_pState->mpRunPlayer != 0) {
        if (_StyleTracker_pState->mSavedRunAwardPending == 0) {
            _StyleTracker_pState->mSavedRunAward = _StyleTracker_pState->mRunAwardValue;
            _StyleTracker_pState->mSavedRunMeter = _StyleTracker_pState->mRunMeterValue;
            _StyleTracker_pState->mSavedRunAwardPending = 1;
        }
        StyleTrackerCancelRun(_StyleTracker_pState->mpRunPlayer->mIdBytes[2]);
    }
    StyleTrackerFinishOtherMoves(0);
    StyleTrackerFinishDefensiveMove(0);
    if (fn_80177C38() == 0) {
        if (StyleTrackerIsFumbleForcerUserControlled() != 0) {
            StyleTrackerProcessEvent(85, team, 1);
        } else {
            StyleTrackerProcessEvent(84, team, 1);
        }
    }
}

extern "C" void StyleTrackerRefreshUserPlayers(void) {
    unsigned char team;

    _StyleTracker_pState->mUserPlayerCount = 0;
    for (team = 0; team <= 1; team++) {
        unsigned int count = fn_80178D18(team);
        unsigned short i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(team, i);

            if (p->mUnknown8 != 255) {
                if (_StyleTracker_pState->mUserPlayerCount <= 3) {
                    _StyleTracker_pState->mpUserPlayers[_StyleTracker_pState->mUserPlayerCount] = p;
                }
                _StyleTracker_pState->mUserPlayerCount++;
            }
        }
    }
}

extern "C" void StyleTrackerOnPumpFake(Object_80039F5C *p) {
    StyleTrackerTraceEvent(28);
    if (fn_801787A0() == 0) {
        if (PlayerMoveGetKind(p) == 0) fn_80156C78(3, 1);
        int team = p->mIdBytes[2] ^ 1;
        float distance;
        fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
        if (_StyleTracker_pState->mRules[6].mOpponentDistance == 0.0f || !(distance > _StyleTracker_pState->mRules[6].mOpponentDistance)) {
            if (_StyleTracker_pState->mFakeout) {
                _StyleTracker_pState->mFakeout = 0;
                StyleTrackerProcessEvent(7, fn_80178308(), 1);
            } else StyleTrackerProcessEvent(6, fn_80178308(), 1);
        }
    }
}

extern "C" void StyleTrackerSetStylePassPending(unsigned char flag) {
    StyleTrackerTraceEvent(7);
    if (flag != 0) {
        _StyleTracker_pState->mStylePassPending = 1;
        StyleTrackerTraceEvent(66);
    } else {
        StyleTrackerTraceEvent(68);
    }
}

extern "C" void StyleTrackerSetPassSubtype(int value) {
    StyleTrackerTraceEvent(8);
    _StyleTracker_pState->mPassSubtype = value;
    if (value != 1) {
        StyleTrackerTraceEvent(67);
        if (value == 6) {
            _StyleTracker_pState->mNinjaPass = 1;
        }
    } else {
        StyleTrackerTraceEvent(69);
        _StyleTracker_pState->mStylePassPending = 0;
    }
}

extern "C" void StyleTrackerBeginStiffArm(int flag) {
    StyleTrackerTraceEvent(5);
    StyleTrackerFinishOtherMoves(24);
    if (flag != 0) {
        Object_80039F5C *p = BallGetCurrentHolder();

        _StyleTracker_pState->mStiffArmActive = 1;
        _StyleTracker_pState->mStiffArmTeam = fn_80178308();
        StyleTrackerProcessEvent(27, fn_80178308(), 1);
        fn_800AE7F0(10, fn_80178308(), p);
    }
}

extern "C" void StyleTrackerResolveStiffArm(Object_80039F5C *p, int flag) {
    StyleTrackerTraceEvent(6);
    if (_StyleTracker_pState->mStiffArmActive != 0 && p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        if (flag != 0) {
            _StyleTracker_pState->mStiffArmSucceeded = 1;
            _StyleTracker_pState->mpStiffArmPlayer = p;
            StyleTrackerFinishStiffArm(1);
            fn_80156C78(16, 1);
        } else {
            StyleTrackerFinishStiffArm(0);
        }
    }
}

extern "C" void StyleTrackerBeginJuke(Object_80039F5C *p, int kind) {
    if (p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        int accept = 0;
        StyleTrackerTraceEvent(1);
        StyleTrackerFinishOtherMoves(14);
        fn_800AE7F0(7, fn_80178308(), p);
        int id = 34;
        switch (kind) {
        case 0:
            break;
        case 1:
            id = 38;
            break;
        case 4:
            id = 42;
            break;
        }
        if (_StyleTracker_pState->mRules[id].mOpponentDistance == 0.0f) {
            accept = 1;
        } else if (_StyleTracker_pState->mRules[id].mOpponentAngle == 0) {
            accept = 1;
        } else {
            int team = p->mIdBytes[2] ^ 1;
            float distance;
            if (fn_801245DC(p, team, 0, fn_80178D18(team), (int)((float)(unsigned int)_StyleTracker_pState->mRules[id].mOpponentAngle * 46603.37890625f), &distance, 0) && !(distance > _StyleTracker_pState->mRules[id].mOpponentDistance)) accept = 1;
        }
        if (accept == 0 && kind != 0) {
            if (PlayerMoveGetKind(p) == 0) fn_80156C78(4, 1);
            _StyleTracker_pState->mMoveFallback = 1;
            accept = 1;
        }
        Vector_80039F5C position;
        BallGetPosition(BallGetCurrent(), &position);
        float limit = fn_80177FE0().mY - 4.0f;
        if (!(position.mY >= limit) && (kind == 4 || kind == 1)) accept = 0;
        if (accept) {
            _StyleTracker_pState->mJukeActive = 1;
            _StyleTracker_pState->mStyleMove = kind == 1;
            _StyleTracker_pState->mWallMove = kind == 4;
            _StyleTracker_pState->mFakeout = 0;
            _StyleTracker_pState->mJukeTeam = fn_80178308();
            if (_StyleTracker_pState->mWallMove) StyleTrackerProcessEvent(40, fn_80178308(), 1);
            else if (_StyleTracker_pState->mStyleMove) StyleTrackerProcessEvent(36, fn_80178308(), 1);
            else StyleTrackerProcessEvent(32, fn_80178308(), 1);
        }
    }
}

extern "C" void StyleTrackerFinishJuke(Object_80039F5C *p) {
    StyleTrackerTraceEvent(2);
    if (_StyleTracker_pState->mJukeActive != 0 && p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        int b = 0;
        int id;
        int a;
        Record_800B15FC *pRecord;

        if (_StyleTracker_pState->mWallMove != 0) {
            id = 42;
            b = 4;
            fn_80156C78(6, 1);
        } else if (_StyleTracker_pState->mStyleMove != 0) {
            id = 38;
            b = 1;
            fn_80156C78(5, 1);
        } else {
            id = 34;
            if (PlayerMoveGetKind(p) == 0) {
                fn_80156C78(4, 1);
            }
        }
        if (_StyleTracker_pState->mFakeout != 0) {
            a = 1;
            id++;
        } else {
            if (_StyleTracker_pState->mMoveFallback != 0) {
                b = 0;
                if (id == 42) {
                    id = 110;
                    fn_80156C78(6, 1);
                } else if (id == 38) {
                    id = 109;
                    fn_80156C78(5, 1);
                }
            }
            a = 0;
        }
        StyleTrackerProcessEvent(id, fn_80178308(), 1);
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = p->mMotion.mPos.mX;
        pRecord->mUnknown10 = p->mMotion.mPos.mY;
        pRecord->mUnknown14 = 57;
        pRecord->mUnknown4 = a;
        pRecord->mUnknown8 = b;
        fn_800B1508();
        _StyleTracker_pState->mStyleMove = 0;
        _StyleTracker_pState->mWallMove = 0;
        _StyleTracker_pState->mFakeout = 0;
        _StyleTracker_pState->mJukeActive = 0;
        _StyleTracker_pState->mMoveFallback = 0;
    }
}

extern "C" void StyleTrackerBeginSpin(Object_80039F5C *p, int kind, unsigned char flag) {
    if (p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        int accept = 0;
        StyleTrackerTraceEvent(3);
        StyleTrackerFinishOtherMoves(15);
        fn_800AE7F0(7, fn_80178308(), p);
        int id = 46;
        switch (kind) {
        case 0:
            break;
        case 1:
        case 4:
            id = 50;
            break;
        }
        _StyleTracker_pState->mSpinSubtype = flag;
        if (_StyleTracker_pState->mRules[id].mOpponentDistance == 0.0f) {
            accept = 1;
        } else if (_StyleTracker_pState->mRules[id].mOpponentAngle == 0) {
            accept = 1;
        } else {
            int team = p->mIdBytes[2] ^ 1;
            float distance;
            if (fn_801245DC(p, team, 0, fn_80178D18(team), (int)((float)(unsigned int)_StyleTracker_pState->mRules[id].mOpponentAngle * 46603.37890625f), &distance, 0) && !(distance > _StyleTracker_pState->mRules[id].mOpponentDistance)) accept = 1;
        }
        if (accept == 0) {
            if (PlayerMoveGetKind(p) == 0) fn_80156C78(7, 1);
            if (kind != 0) { _StyleTracker_pState->mMoveFallback = accept = 1; }
        }
        Vector_80039F5C position;
        BallGetPosition(BallGetCurrent(), &position);
        float limit = fn_80177FE0().mY - 4.0f;
        if (!(position.mY >= limit) && (kind == 4 || kind == 1)) accept = 0;
        if (accept) {
            _StyleTracker_pState->mSpinActive = 1;
            _StyleTracker_pState->mStyleMove = kind != 0;
            _StyleTracker_pState->mFakeout = 0;
            _StyleTracker_pState->mSpinTeam = fn_80178308();
            if (_StyleTracker_pState->mStyleMove) StyleTrackerProcessEvent(48, fn_80178308(), 1);
            else StyleTrackerProcessEvent(44, fn_80178308(), 1);
        }
    }
}

extern "C" void StyleTrackerFinishSpin(Object_80039F5C *p) {
    StyleTrackerTraceEvent(4);
    if (_StyleTracker_pState->mSpinActive != 0 && p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        int b = 0;
        Record_800B15FC *pRecord;

        if (_StyleTracker_pState->mFakeout != 0) {
            if (_StyleTracker_pState->mStyleMove != 0) {
                b = 1;
                StyleTrackerProcessEvent(51, fn_80178308(), 1);
                fn_80156C78(8, 1);
            } else {
                StyleTrackerProcessEvent(47, fn_80178308(), 1);
                if (PlayerMoveGetKind(p) == 0) {
                    fn_80156C78(7, 1);
                }
            }
            pRecord = fn_800B15FC();
            fn_8009BD2C(p, &pRecord->mUnknown0);
            pRecord->mUnknownC = p->mMotion.mPos.mX;
            pRecord->mUnknown10 = p->mMotion.mPos.mY;
            pRecord->mUnknown14 = 57;
            pRecord->mUnknown4 = 1;
            pRecord->mUnknown8 = b;
            fn_800B1508();
        } else {
            if (_StyleTracker_pState->mStyleMove != 0) {
                if (_StyleTracker_pState->mMoveFallback != 0) {
                    StyleTrackerProcessEvent(111, fn_80178308(), 1);
                    fn_80156C78(8, 1);
                } else {
                    b = 1;
                    StyleTrackerProcessEvent(50, fn_80178308(), 1);
                    fn_80156C78(8, 1);
                }
            } else {
                StyleTrackerProcessEvent(46, fn_80178308(), 1);
                if (PlayerMoveGetKind(p) == 0) {
                    fn_80156C78(7, 1);
                }
            }
            pRecord = fn_800B15FC();
            fn_8009BD2C(p, &pRecord->mUnknown0);
            pRecord->mUnknownC = p->mMotion.mPos.mX;
            pRecord->mUnknown10 = p->mMotion.mPos.mY;
            pRecord->mUnknown14 = 57;
            pRecord->mUnknown4 = 0;
            pRecord->mUnknown8 = b;
            fn_800B1508();
        }
        _StyleTracker_pState->mStyleMove = 0;
        _StyleTracker_pState->mWallMove = 0;
        _StyleTracker_pState->mFakeout = 0;
        _StyleTracker_pState->mSpinActive = 0;
        _StyleTracker_pState->mMoveFallback = 0;
    }
}

extern "C" void StyleTrackerOnMoveResult(int value) {
    StyleTrackerTraceEvent(27);
    if (value == 4) {
        _StyleTracker_pState->mFakeout = 1;
    } else if (value == 5) {
        _StyleTracker_pState->mFakeout = 1;
    } else if (value == 2) {
        _StyleTracker_pState->mFakeout = 1;
    } else if (value == 1 && _StyleTracker_pState->mPumpInteraction != 0 && _StyleTracker_pState->mPumpAwarded == 0) {
        StyleTrackerProcessEvent(12, fn_80178308(), 1);
        _StyleTracker_pState->mPumpAwarded = value;
    }
}

extern "C" void StyleTrackerBeginPumpInteraction(void) {
    StyleTrackerTraceEvent(29);
    _StyleTracker_pState->mPumpInteraction = 1;
}

extern "C" void StyleTrackerCancelRun(int a) {
    StyleTrackerTraceEvent(49);
    if (_StyleTracker_pState->mRunAwardValue != 0) {
        StyleTrackerProcessEvent(65, a, 1);
    }
    StyleTrackerResetRun();
    _StyleTracker_pState->mRunCompleted = 0;
}

extern "C" void StyleTrackerFinishRun(void) {
    StyleTrackerTraceEvent(51);
    StyleTrackerUpdateRun(0, 0, 0);
    StyleTrackerUpdateRun(0, 0, 0);
}

extern "C" int StyleTrackerUpdateRun(int active, int a, int b) {
    int requested = active;
    int result = 0;
    if (active != 0) {
        if (fn_801787A0() != 0) active = 0;
        if (active != 0) {
            fn_80156C78(15, 1);
            if (fn_801787A0() == 0 && _StyleTracker_pState->mRunActive == 0) {
                StyleTrackerTraceEvent(53); StyleTrackerFinishOtherMoves(11);
            }
            if (active != 0) {
                Vector_80039F5C position;
                if (fn_80178348() == BallGetCurrentHolder()->mIdBytes[2]) {
                    BallGetPosition(BallGetCurrent(), &position);
                    if (_StyleTracker_pState->mRules[64].mAllowBehindLine == 0) {
                        if (!(position.mY >= fn_80177FE0().mY)) { active = 0; StyleTrackerCancelRun(BallGetCurrentHolder()->mIdBytes[2]); }
                    }
                } else {
                    BallGetPosition(BallGetCurrent(), &position);
                    if (_StyleTracker_pState->mRules[64].mAllowBehindLine == 0 && !(position.mY >= _StyleTracker_pState->mPossessionStartY)) {
                        active = 0; StyleTrackerCancelRun(BallGetCurrentHolder()->mIdBytes[2]);
                    }
                }
            }
        }
    }
    if (requested) _StyleTracker_pState->mRunRequested = 1;
    if (active) {
        _StyleTracker_pState->mRunEndTicks = 0;
        if (_StyleTracker_pState->mRunActive == 0) {
            _StyleTracker_pState->mRunActive = 1;
            _StyleTracker_pState->mpRunPlayer = BallGetCurrentHolder();
            _StyleTracker_pState->mRunTime = 0;
            StyleTrackerAccumulateRunTime();
            _StyleTracker_pState->mRunAction = a;
            _StyleTracker_pState->mRunSubtype = b;
            StyleTrackerTraceEvent(26);
            if (_StyleTracker_pState->mRunEffectActive == 0) {
                _StyleTracker_pState->mpRunEffectPlayer = _StyleTracker_pState->mpRunPlayer;
                StyleTrackerStartRunEffect();
                _StyleTracker_pState->mRunEffectActive = 1;
            }
        } else {
            if (_StyleTracker_pState->mpRunPlayer != BallGetCurrentHolder()) StyleTrackerTraceEvent(54);
            if (_StyleTracker_pState->mpRunPlayer == BallGetCurrentHolder()) {
                StyleTrackerAccumulateRunTime();
                _StyleTracker_pState->mRunAction = a;
                _StyleTracker_pState->mRunSubtype = b;
                int scaled, value;
                StyleTrackerCalculateAward(BallGetCurrentHolder()->mIdBytes[2], 64, _StyleTracker_pState->mRunTime, &scaled, 0, &value, 0, 0, 0, 0);
                if (value != _StyleTracker_pState->mRunAwardValue) {
                    _StyleTracker_pState->mRunAwardValue = value;
                    _StyleTracker_pState->mRunMeterValue = scaled;
                    StyleTrackerProcessEvent(64, BallGetCurrentHolder()->mIdBytes[2], _StyleTracker_pState->mRunTime);
                    if (_StyleTracker_pState->mRunAwardValue > 499) AudmonEventPost(121, 0);
                }
                if (_StyleTracker_pState->mRunEffectActive) {
                    float distance = (float)fabs(_StyleTracker_pState->mpRunPlayer->mMotion.mPos.mX) + 6.0f;
                    if (!(distance <= fn_800A32B4())) {
                        Object_80039F5C *p = _StyleTracker_pState->mpRunEffectPlayer;
                        fn_800310C0(lbl_803EA368, 57, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                        _StyleTracker_pState->mRunEffectActive = 0;
                    }
                }
            }
        }
    } else if (_StyleTracker_pState->mRunTime + _StyleTracker_pState->mRunTicks != 0) {
        if (_StyleTracker_pState->mpRunPlayer != BallGetCurrentHolder()) { StyleTrackerTraceEvent(55); _StyleTracker_pState->mRunEndTicks++; }
        if ((unsigned int)++_StyleTracker_pState->mRunEndTicks > 1) {
            int value;
            StyleTrackerCalculateAward(_StyleTracker_pState->mpRunPlayer->mIdBytes[2], 64, _StyleTracker_pState->mRunTime, 0, 0, &value, 0, 0, 0, 0);
            StyleTrackerTraceEvent(56);
            if (value) StyleTrackerTraceEvent(57);
            if (_StyleTracker_pState->mpRunPlayer == BallGetCurrentHolder()) StyleTrackerTraceEvent(58);
            if (fn_801787A0()) StyleTrackerTraceEvent(59);
            if (value) {
                if (_StyleTracker_pState->mPlaySettled || _StyleTracker_pState->mpRunPlayer == BallGetCurrentHolder()) {
                    _StyleTracker_pState->mRunTeam = _StyleTracker_pState->mpRunPlayer->mIdBytes[2];
                    _StyleTracker_pState->mCompletedRunTime = _StyleTracker_pState->mRunTime;
                    _StyleTracker_pState->mRunCompleted = 1;
                    if (fn_801787A0() == 0) StyleTrackerAwardCompletedRun();
                    result = 1;
                } else if (value && _StyleTracker_pState->mpRunPlayer != BallGetCurrentHolder()) {
                    if (_StyleTracker_pState->mSavedRunAwardPending == 0) {
                        _StyleTracker_pState->mSavedRunAward = _StyleTracker_pState->mRunAwardValue;
                        _StyleTracker_pState->mSavedRunMeter = _StyleTracker_pState->mRunMeterValue;
                        _StyleTracker_pState->mSavedRunAwardPending = 1;
                    }
                    StyleTrackerCancelRun(_StyleTracker_pState->mpRunPlayer->mIdBytes[2]);
                }
            }
            StyleTrackerResetRun();
            if (_StyleTracker_pState->mRunEffectActive) {
                Object_80039F5C *p = _StyleTracker_pState->mpRunEffectPlayer;
                fn_800310C0(lbl_803EA368, 57, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                _StyleTracker_pState->mRunEffectActive = 0;
            }
        }
    }
    return result;
}

extern "C" void StyleTrackerAwardDive(Object_80039F5C *p, int kind, unsigned char flag) {
    if (p == BallGetCurrentHolder()) { StyleTrackerTraceEvent(25); StyleTrackerFinishOtherMoves(0); }
    if (p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        StyleTrackerFinishOtherMoves(0);
        int id = 52;
        switch (kind) {
        case 0: if (PlayerMoveGetKind(p) == 0) fn_80156C78(12, 1); break;
        case 1: id = 53; fn_80156C78(13, 1); break;
        case 4: id = 54; fn_80156C78(14, 1); break;
        }
        _StyleTracker_pState->mDiveSubtype = flag;
        fn_800AE7F0(12, p->mIdBytes[2], p);
        int team = p->mIdBytes[2] ^ 1;
        float distance;
        fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
        if (p->mpState->mId == 12 && p->mUnknown355[0] == 0) return;
        if (_StyleTracker_pState->mRules[id].mOpponentDistance != 0.0f && distance > _StyleTracker_pState->mRules[id].mOpponentDistance) return;
        StyleTrackerProcessEvent(id, p->mIdBytes[2], 1);
        Record_800B15FC *record = fn_800B15FC();
        fn_8009BD2C(p, &record->mUnknown0);
        record->mUnknownC = p->mMotion.mPos.mX;
        record->mUnknown10 = p->mMotion.mPos.mY;
        record->mUnknown14 = 59;
        record->mUnknown4 = kind;
        fn_800B1508();
    }
}

extern "C" void StyleTrackerBeginHurdle(Object_80039F5C *p, int kind, unsigned char flag) {
    int accept = 0;
    if (p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        StyleTrackerTraceEvent(23);
        StyleTrackerFinishOtherMoves(16);
        int id = 57;
        switch (kind) {
        case 0:
            break;
        case 1:
            id = 60;
            break;
        case 4:
            id = 63;
            break;
        }
        _StyleTracker_pState->mHurdleSubtype[0] = flag;
        fn_800AE7F0(12, p->mIdBytes[2], p);
        accept = 0;
        if (_StyleTracker_pState->mRules[id].mOpponentDistance == 0.0f) {
            accept = 1;
        } else if (_StyleTracker_pState->mRules[id].mOpponentAngle == 0) {
            accept = 1;
        } else {
            float distance;
            int team = p->mIdBytes[2] ^ 1;
            if (fn_801245DC(p, team, 0, fn_80178D18(team), (int)((float)(unsigned int)_StyleTracker_pState->mRules[id].mOpponentAngle * 46603.37890625f), &distance, 0) && !(distance > _StyleTracker_pState->mRules[id].mOpponentDistance)) accept = 1;
            if (accept == 0) {
                if (fn_801245DC(p, p->mIdBytes[2], 0, fn_80178D18(p->mIdBytes[2]), (int)((float)(unsigned int)_StyleTracker_pState->mRules[id].mOpponentAngle * 46603.37890625f), &distance, 0) && !(distance > _StyleTracker_pState->mRules[id].mOpponentDistance)) accept = 1;
            }
        }
    }
    if (accept == 0) {
        if (PlayerMoveGetKind(p) == 0) fn_80156C78(9, 1);
        if (kind != 0) { _StyleTracker_pState->mMoveFallback = accept = 1; }
    }
    Vector_80039F5C position;
    BallGetPosition(BallGetCurrent(), &position);
    float limit = fn_80177FE0().mY - 4.0f;
    if (!(position.mY >= limit) && (kind == 4 || kind == 1)) accept = 0;
    if (accept) {
        _StyleTracker_pState->mHurdleActive = 1;
        _StyleTracker_pState->mStyleMove = kind == 1;
        _StyleTracker_pState->mWallMove = kind == 4;
        _StyleTracker_pState->mFakeout = 0;
        _StyleTracker_pState->mHurdleTeam = fn_80178308();
        if (_StyleTracker_pState->mWallMove) StyleTrackerProcessEvent(61, fn_80178308(), 1);
        else if (_StyleTracker_pState->mStyleMove) StyleTrackerProcessEvent(58, fn_80178308(), 1);
        else StyleTrackerProcessEvent(55, fn_80178308(), 1);
    }
}

extern "C" void StyleTrackerFinishHurdle(Object_80039F5C *p) {
    StyleTrackerTraceEvent(24);
    if (_StyleTracker_pState->mHurdleActive != 0 && p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        int a = 0;
        Record_800B15FC *pRecord;

        if (_StyleTracker_pState->mWallMove != 0) {
            if (_StyleTracker_pState->mMoveFallback != 0) {
                StyleTrackerProcessEvent(113, fn_80178308(), 1);
            } else {
                a = 4;
                StyleTrackerProcessEvent(63, fn_80178308(), 1);
            }
            fn_80156C78(11, 1);
        } else if (_StyleTracker_pState->mStyleMove != 0) {
            if (_StyleTracker_pState->mMoveFallback != 0) {
                StyleTrackerProcessEvent(112, fn_80178308(), 1);
            } else {
                a = 1;
                StyleTrackerProcessEvent(60, fn_80178308(), 1);
            }
            fn_80156C78(10, 1);
        } else {
            StyleTrackerProcessEvent(57, fn_80178308(), 1);
            if (PlayerMoveGetKind(p) == 0) {
                fn_80156C78(9, 1);
            }
        }
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = p->mMotion.mPos.mX;
        pRecord->mUnknown10 = p->mMotion.mPos.mY;
        pRecord->mUnknown14 = 59;
        pRecord->mUnknown4 = a;
        fn_800B1508();
        _StyleTracker_pState->mWallMove = 0;
        _StyleTracker_pState->mStyleMove = 0;
        _StyleTracker_pState->mFakeout = 0;
        _StyleTracker_pState->mHurdleActive = 0;
        _StyleTracker_pState->mMoveFallback = 0;
    }
}

extern "C" void StyleTrackerSetCatchFlags(int a, int b, unsigned char c) {
    StyleTrackerTraceEvent(18);
    if (fn_801787A0() == 0) {
        _StyleTracker_pState->mCatchPending = 1;
        _StyleTracker_pState->mUserCatch = a;
        _StyleTracker_pState->mStyleCatch = b;
        _StyleTracker_pState->mCatchVariant = c;
    }
}

extern "C" void StyleTrackerAwardCatch(Object_80039F5C *p) {
    int id;

    StyleTrackerTraceEvent(19);
    if (fn_801787A0() == 0 && _StyleTracker_pState->mCatchPending != 0) {
        if (_StyleTracker_pState->mUserCatch != 0) {
            if (_StyleTracker_pState->mStyleCatch != 0) {
                if (_StyleTracker_pState->mNinjaPass != 0) {
                    id = 114;
                    fn_8017CA10(p->mIdBytes[2], 1);
                } else {
                    id = 22;
                }
                fn_8017C9E4(p->mIdBytes[2], 1);
                fn_80156C78(38, 1);
            } else if (_StyleTracker_pState->mCatchVariant != 0) {
                id = 24;
                fn_8017C674(p->mIdBytes[2], 1);
                fn_80156C78(37, 1);
            } else {
                id = 20;
            }
        } else if (_StyleTracker_pState->mStyleCatch != 0) {
            id = 21;
            if (_StyleTracker_pState->mNinjaPass != 0) {
                id = 114;
            }
            fn_80156C78(38, 1);
        } else {
            id = 19;
            if (_StyleTracker_pState->mCatchVariant != 0) {
                id = 23;
            }
        }
        StyleTrackerAwardImmediateEvent(id, fn_80178308());
    }
}

extern "C" void StyleTrackerOnCarrierContact(Object_80039F5C *p) {
    StyleTrackerTraceEvent(22);
    if (_StyleTracker_pState->mContactSeen == 0) {
        if (fn_80178320() == p->mIdBytes[2]) {
            if (_StyleTracker_pState->mContactPending == 0) {
                StyleTrackerTraceEvent(61);
                _StyleTracker_pState->mContactPending = 1;
                _StyleTracker_pState->mpContactPlayer = p;
            }
        } else {
            StyleTrackerTraceEvent(60);
        }
    }
    _StyleTracker_pState->mContactSeen = 1;
}

extern "C" void StyleTrackerOnInterception(int a, Object_80039F5C *p) {
    Vector_80039F5C pos;

    StyleTrackerTraceEvent(21);
    StyleTrackerFinishOtherMoves(0);
    StyleTrackerSetComboWeight(fn_80178348(), 0);
    _StyleTracker_pState->mIntercepted = 1;
    _StyleTracker_pState->mCatchVariant = PlayerMoveGetKind(p);
    if (a != 0) {
        if (_StyleTracker_pState->mCatchVariant != 0) {
            StyleTrackerAwardImmediateEvent(75, fn_80178360());
            fn_80156C78(22, 1);
        } else {
            StyleTrackerAwardImmediateEvent(74, fn_80178360());
            fn_80156C78(22, 1);
        }
        fn_8017C9B8(p->mIdBytes[2], 1);
    } else if (_StyleTracker_pState->mCatchVariant != 0) {
        StyleTrackerAwardImmediateEvent(73, fn_80178360());
        fn_80156C78(22, 1);
    } else {
        StyleTrackerAwardImmediateEvent(72, fn_80178360());
        fn_80156C78(22, 1);
    }
    fn_800AE7F0(11, fn_80178360(), p);
    BallGetPosition(BallGetCurrent(), &pos);
    _StyleTracker_pState->mPossessionStartY = -pos.mY;
    _StyleTracker_pState->mPitchCounts[fn_80178348()] = 0;
}

extern "C" void StyleTrackerBeginPitch(int flag, Object_80039F5C *p) {
    StyleTrackerTraceEvent(15);
    if (p == BallGetCurrentHolder() && fn_801787A0() == 0) {
        _StyleTracker_pState->mPitchActive = 1;
        _StyleTracker_pState->mStylePitch = flag;
        if (flag != 0) {
            StyleTrackerTraceEvent(70);
        } else {
            StyleTrackerTraceEvent(71);
        }
        fn_800AE7F0(8, fn_80178308(), p);
    }
}

extern "C" void StyleTrackerFinishPitch(int team, int a, int b) {
    int flag;

    StyleTrackerTraceEvent(16);
    flag = _StyleTracker_pState->mPitchActive != 0 && _StyleTracker_pState->mPitchReleased != 0;
    if (a | flag) {
        if (a == 0) {
            int count = ++_StyleTracker_pState->mPitchCounts[team];

            if (_StyleTracker_pState->mStylePitch != 0) {
                StyleTrackerProcessEvent(18, team, count);
                fn_80156C78(18, 1);
            } else {
                StyleTrackerProcessEvent(15, team, count);
                fn_80156C78(17, 1);
            }
        } else {
            Vector_80039F5C pos;

            StyleTrackerFinishOtherMoves(0);
            StyleTrackerSetComboWeight(team == 0, 0);
            _StyleTracker_pState->mPitchStolen = 1;
            if (b != 0) {
                StyleTrackerProcessEvent(105, team, 1);
            } else {
                StyleTrackerProcessEvent(104, team, 1);
            }
            BallGetPosition(BallGetCurrent(), &pos);
            _StyleTracker_pState->mPossessionStartY = -pos.mY;
            _StyleTracker_pState->mPitchCounts[team == 0] = 0;
        }
        _StyleTracker_pState->mPitchReleased = 0;
        _StyleTracker_pState->mPitchActive = 0;
        _StyleTracker_pState->mStylePitch = 0;
    }
}

extern "C" void StyleTrackerBeginDefensiveMove(Object_80039F5C *p, int flag) {
    StyleTrackerTraceEvent(12);
    if (p != 0 && p->mIdBytes[2] == fn_80178360() && fn_80177C38() == 0 && fn_801787A0() == 0 &&
        _StyleTracker_pState->mOffenseLostBall == 0 && _StyleTracker_pState->mPassReleased == 0 && fn_801783AC(0) == 0 &&
        p->mUnknown8 != 255) {
        StyleTrackerTraceEvent(13);
        if (p->mUnknown8 == 255) {
            StyleTrackerProcessEvent(80, p->mIdBytes[2], 1);
        } else {
            if (flag != 0) {
                StyleTrackerTraceEvent(10);
            } else {
                StyleTrackerTraceEvent(11);
            }
            StyleTrackerFinishDefensiveMove(29);
            _StyleTracker_pState->mpDefensiveMovePlayer = p;
            _StyleTracker_pState->mDefensiveMoveActive = 1;
            _StyleTracker_pState->mStyleDefensiveMove = flag;
            if (flag != 0 && fn_801BE648(p->mpUnknown792) != 246 && fn_801BE648(p->mpUnknown792) != 242) {
                fn_80156C78(39, 1);
            }
            StyleTrackerProcessEvent(81, p->mIdBytes[2], 1);
        }
        fn_800AE7F0(9, p->mIdBytes[2], p);
    }
}

extern "C" void StyleTrackerEndDefensiveMove(Object_80039F5C *p) {
    if (p != 0 && _StyleTracker_pState->mDefensiveMoveActive != 0 && p == _StyleTracker_pState->mpDefensiveMovePlayer) {
        StyleTrackerTraceEvent(14);
        StyleTrackerFinishDefensiveMove(0);
    }
}

extern "C" void StyleTrackerOnCarrierActionTwo(Object_80039F5C *p) {
    if (p != 0 && p == BallGetCurrentHolder()) {
        StyleTrackerTraceEvent(46);
        StyleTrackerFinishOtherMoves(2);
    }
}

extern "C" void StyleTrackerOnCarrierActionFive(Object_80039F5C *p) {
    if (p != 0 && p == BallGetCurrentHolder()) {
        StyleTrackerTraceEvent(52);
        StyleTrackerFinishOtherMoves(5);
    }
}

extern "C" void StyleTrackerOnActionThree(void) {
    StyleTrackerTraceEvent(47);
    StyleTrackerFinishOtherMoves(3);
}

extern "C" void StyleTrackerAwardHotspot(Object_80039F5C *p, unsigned int count, int changed) {
    StyleTrackerTraceEvent(45);
    switch (count) {
    case 1:
        if (changed != 0) {
            StyleTrackerProcessEvent(121, p->mIdBytes[2], 1);
        } else {
            StyleTrackerProcessEvent(115, p->mIdBytes[2], 1);
        }
        break;
    case 2:
        if (changed != 0) {
            StyleTrackerProcessEvent(122, p->mIdBytes[2], 1);
        } else {
            StyleTrackerProcessEvent(116, p->mIdBytes[2], 1);
        }
        break;
    case 3:
        if (changed != 0) {
            StyleTrackerProcessEvent(123, p->mIdBytes[2], 1);
        } else {
            StyleTrackerProcessEvent(117, p->mIdBytes[2], 1);
        }
        break;
    case 4:
        if (changed != 0) {
            StyleTrackerProcessEvent(124, p->mIdBytes[2], 1);
        } else {
            StyleTrackerProcessEvent(118, p->mIdBytes[2], 1);
        }
        break;
    case 5:
        if (changed != 0) {
            StyleTrackerProcessEvent(125, p->mIdBytes[2], 1);
        } else {
            StyleTrackerProcessEvent(119, p->mIdBytes[2], 1);
        }
        break;
    }
}

extern "C" void StyleTrackerAwardStrip(int team) {
    StyleTrackerProcessEvent(120, team, 1);
    fn_8017CA68(team, 1);
}

extern "C" void StyleTrackerOnActionFour(void) {
    StyleTrackerTraceEvent(45);
    StyleTrackerFinishOtherMoves(4);
}

extern "C" void StyleTrackerEndPlay(void) {
    StyleTrackerTraceEvent(0);
    StyleTrackerProcessEvent(129, 0, 1);
}

extern "C" void StyleTrackerHandleGameEvent(Record_800B15FC *pRecord) {
    switch (pRecord->mUnknown14) {
    case 0: case 1: case 2:
        break;
    case 3:
        StyleTrackerTraceEvent(88);
        StyleTrackerProcessEvent(128, 0, 1);
        break;
    case 4:
        break;
    case 5:
        StyleTrackerTraceEvent(89);
        StyleTrackerFinishDefensiveMove(0);
        if (_StyleTracker_pState->mPitchActive != 0 || _StyleTracker_pState->mStylePitch != 0) {
            StyleTrackerOnPitchReleased();
        } else {
            StyleTrackerOnPassReleased();
        }
        break;
    case 6:
        break;
    case 7:
        StyleTrackerTraceEvent(90);
        StyleTrackerOnPitchReleased();
        break;
    case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 16: case 17:
        break;
    case 18:
        StyleTrackerTraceEvent(92);
        StyleTrackerOnPossessionLost();
        break;
    case 19: case 20: case 21: case 22: case 23:
        break;
    case 24:
        StyleTrackerTraceEvent(94);
        StyleTrackerFinishDefensiveMove(0);
        break;
    case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
    case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40:
    case 41: case 42: case 43: case 44: case 45: case 46: case 47: case 48:
    case 49: case 50: case 51: case 52: case 53: case 54: case 55:
        break;
    case 56:
        StyleTrackerTraceEvent(93);
        StyleTrackerFinishDefensiveMove(0);
        StyleTrackerProcessEvent(79, fn_80178320(), 1);
        break;
    case 57: case 58: case 59:
        break;
    case 60:
        StyleTrackerTraceEvent(95);
        if (pRecord->mUnknown4 != 0) {
            StyleTrackerTraceEvent(72);
            _StyleTracker_pState->mUserQbStop = 1;
        } else {
            StyleTrackerTraceEvent(73);
            _StyleTracker_pState->mQbStop = 1;
        }
        break;
    case 61: case 62:
        break;
    }
}

extern "C" void StyleTrackerHandleAudioEvent(AudmonEvent_t *pRecord) {
    switch (pRecord->mType) {
    case 37:
        StyleTrackerTraceEvent(96);
        StyleTrackerFinishDefensiveMove(0);
        StyleTrackerFinishOtherMoves(1);
        break;
    case 44:
        StyleTrackerTraceEvent(98);
        StyleTrackerFinishOtherMoves(1);
        break;
    case 100:
        StyleTrackerTraceEvent(100);
        StyleTrackerFinishOtherMoves(1);
        break;
    case 104:
        StyleTrackerTraceEvent(101);
        StyleTrackerFinishOtherMoves(0);
        break;
    }
}

extern "C" void StyleTrackerReset(void) {
    int changed = 0;
    int mode = fn_801486A0();
    if (mode == 0) {
        if (_StyleTracker_iDatabaseVariant != 1) { _StyleTracker_iDatabaseVariant = 1; changed = 1; }
    } else if (_StyleTracker_iDatabaseVariant != 0) { _StyleTracker_iDatabaseVariant = 0; changed = 1; }
    if (changed) {
        DbCursor cursor;
        fn_8018FB4C(&cursor, _StyleTracker_iDatabaseVariant);
        for (int i = 0; i <= 126; i++) {
            if (fn_8018FBE8(&cursor, i)) fn_8018FC1C(&cursor, &_StyleTracker_pState->mRules[i]);
            else memset(&_StyleTracker_pState->mRules[i], 0, sizeof(StyleAwardRule_t));
        }
        fn_8018FBC8(&cursor);
    }
    StyleTrackerSetTotal(0, 0); StyleTrackerSetTotal(1, 0);
    StyleTrackerSetMeter(0, 0, 0); StyleTrackerSetMeter(1, 0, 0);
    StyleTrackerSetComboWeight(0, 0); StyleTrackerSetComboWeight(1, 0);
    for (int i = 0; i <= 126; i++) { StyleTrackerSetEventCount(0, i, 0); StyleTrackerSetEventCount(1, i, 0); }
    _StyleTracker_pState->mMeterFilledThisPlay[0] = 0;
    _StyleTracker_pState->mMeterFilledThisPlay[1] = 0;
    _StyleTracker_pState->unk_0x1ECE = 1;
    _StyleTracker_pState->mPossessionStartY = 0.0f;
    _StyleTracker_pState->mPlayStartTotal[0] = 0;
    _StyleTracker_pState->mPlayStyleGain[0] = 0;
    _StyleTracker_pState->mPlayStartTotal[1] = 0;
    _StyleTracker_pState->mPlayStyleGain[1] = 0;
    _StyleTracker_aiPlayStylePoints[0] = 0;
    _StyleTracker_aiPlayStylePoints[1] = 0;
    _StyleTracker_aiPlayPitches[0] = 0;
    _StyleTracker_aiPlayPitches[1] = 0;
    _StyleTracker_acQbStopStreak[0] = 0;
    _StyleTracker_acQbStopStreak[1] = 0;
    _StyleTracker_abQbStopThisPlay[0] = 0;
    _StyleTracker_abQbStopThisPlay[1] = 0;
    _StyleTracker_acUserQbStopStreak[0] = 0;
    _StyleTracker_acUserQbStopStreak[1] = 0;
    _StyleTracker_abUserQbStopThisPlay[0] = 0;
    _StyleTracker_abUserQbStopThisPlay[1] = 0;
    _StyleTracker_acCatchStreak[0] = 0;
    _StyleTracker_acCatchStreak[1] = 0;
    _StyleTracker_abCatchThisPlay[0] = 0;
    _StyleTracker_abCatchThisPlay[1] = 0;
    _StyleTracker_abCatchOpportunity[0] = 0;
    _StyleTracker_abCatchOpportunity[1] = 0;
    _StyleTracker_acStyleCatchStreak[0] = 0;
    _StyleTracker_acStyleCatchStreak[1] = 0;
    _StyleTracker_abStylePassThisPlay[0] = 0;
    _StyleTracker_abStylePassThisPlay[1] = 0;
    _StyleTracker_acConsecutivePitches[0] = 0;
    _StyleTracker_acConsecutivePitches[1] = 0;
    _StyleTracker_acLongestPitchChain[0] = 0;
    _StyleTracker_acLongestPitchChain[1] = 0;
    for (int i = 6; i < 69; i++) _StyleTracker_pState->mPlayFlags[i] = 0;
    _StyleTracker_cWinner = 2;
    _StyleTracker_bEnabled = 1;
    if (mode == 2 || mode == 3) {
        _StyleTracker_bCombosEnabled = 0;
    } else {
        _StyleTracker_bCombosEnabled = 1;
    }
}

extern "C" void StyleTrackerInit(void) {
    void *pHandle;

    _StyleTracker_iMeterThreshold = 20000;
    if (fn_8017F584() == 0) {
        if (CheatFlagsIsSet(28)) {
            _StyleTracker_iMeterThreshold = 10000;
        } else if (CheatFlagsIsSet(29)) {
            _StyleTracker_iMeterThreshold = 2000;
        }
    }
    pHandle = fn_80238174(0, (void **)&_StyleTracker_pState, sizeof(StyleTrackerState_t), 0, 0x7472636B);
    fn_80238234(pHandle, StyleTrackerCreateState, StyleTrackerDestroyState, 0, StyleTrackerCompareState);
    fn_80238248(pHandle, StyleTrackerSaveState, StyleTrackerGetStateSize, StyleTrackerLoadState);
    fn_802381E0(pHandle);
    StyleTrackerReset();
}

extern "C" void StyleTrackerResetDefaults() {
    _StyleTracker_iDatabaseVariant = 2;
    _StyleTracker_iMeterThreshold = 20000;
}

extern "C" void StyleTrackerSetEnabled(int a) {
    _StyleTracker_bEnabled = a;
}

extern "C" unsigned char StyleTrackerGetCatchStreak(int team) {
    return _StyleTracker_acCatchStreak[team];
}

extern "C" void StyleTrackerMarkCatchOpportunity(int team) {
    _StyleTracker_abCatchOpportunity[team] = 1;
}

extern "C" unsigned char StyleTrackerGetStyleCatchStreak(int team) {
    return _StyleTracker_acStyleCatchStreak[team];
}

extern "C" unsigned int StyleTrackerAddProfilePoints(int side, unsigned int value) {
    int index = fn_80186F7C((unsigned char)side);
    unsigned int result = 0;
    if (index != -1) {
        result = (unsigned int)((float)value * _StyleTracker_fProfilePointScale);
        UserInfoAddPoints(fn_8022F358(index), result);
    }
    return result;
}

extern "C" void StyleTrackerSetAwardCallback(StyleAwardCallback a) {
    _StyleTracker_pAwardCallback = a;
}

extern "C" {
extern const StyleAwardGrowth_t _StyleTracker_sNoGrowth;
extern const StyleAwardGrowth_t _StyleTracker_sRunGrowth;
extern const StyleAwardGrowth_t _StyleTracker_sComboRunGrowth;
extern const StyleAwardStep_t _StyleTracker_aRunSteps[10];
extern const StyleAwardStep_t _StyleTracker_aComboRunSteps[10];
extern const StyleAwardStep_t _StyleTracker_aPassGainSteps[10];
extern const StyleAwardStep_t _StyleTracker_aRushGainSteps[10];
extern const StyleAwardStep_t _StyleTracker_aPassTouchdownSteps[10];
extern const StyleAwardStep_t _StyleTracker_aRushTouchdownSteps[10];
extern const StyleAwardStep_t _StyleTracker_aVictorySteps[10];
extern const StyleAwardStep_t _StyleTracker_aSpecialVictorySteps[10];
extern const StyleAwardStep_t _StyleTracker_aComboSteps[10];
extern const StyleAwardStep_t _StyleTracker_aStylePitchSteps[10];
extern const StyleAwardStep_t _StyleTracker_aPitchSteps[10];
const StyleAwardTable_t _StyleTracker_aAwardTables[13] = {
    {&_StyleTracker_sNoGrowth, _StyleTracker_aPassTouchdownSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aRushTouchdownSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aRushGainSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aPassGainSteps},
    {&_StyleTracker_sRunGrowth, _StyleTracker_aRunSteps},
    {&_StyleTracker_sComboRunGrowth, _StyleTracker_aComboRunSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aVictorySteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aSpecialVictorySteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aComboSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aPitchSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aPitchSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aStylePitchSteps},
    {&_StyleTracker_sNoGrowth, _StyleTracker_aStylePitchSteps},
};
const char _StyleTracker_aszAwardMessages[221][80] = {
    "",
    "Guts and Glory for Two",
    "Playing it Safe for One",
    "Stealing 4",
    "Save Face",
    "Pump Fake",
    "He fell for da Pump",
    "I still got it",
    "Show and Tell",
    "Show and Tell",
    "Show and Tell",
    "Show and Tell",
    "Show and Tell",
    "Show and Tell",
    "No Look",
    "No Look",
    "Off da Hook",
    "Off da Hook",
    "Callin' da Shots",
    "Callin' da Shots",
    "Ninja Pass!",
    "Ninja Pass!",
    "Look Away",
    "Look Away",
    "Drop Off",
    "Double Dish",
    "Hat Trick",
    "Grand Slam",
    "A Full Hand",
    "Pitch 6",
    "Did I just see 7?",
    "Great 8",
    "9 Times",
    "Pitch it Double Digit",
    "Dishin' the Rock",
    "Dishin' the Rock",
    "Nice Dash",
    "Nice Grip",
    "User Grip",
    "Off the Wall",
    "Verticality!",
    "Style Grab",
    "My Catch My Style",
    "Bruiser",
    "Bruiser",
    "Bustin' Loose",
    "Button Brawler",
    "Side Steppin'",
    "Side Steppin'",
    "He Got Shook",
    "Like Butta",
    "Like Butta",
    "Like Butta on Toast",
    "Trick off the Brick",
    "Trick off the Brick",
    "Where did he go?",
    "Scratchin'",
    "Scratchin'",
    "Used and Abused",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "Tornado",
    "...with a Twist",
    "Header",
    "Corkscrew",
    "Corkscrew",
    "Cannonball",
    "Flapping",
    "Flip",
    "Inside",
    "Outside",
    "Super Dive",
    "Torpedo",
    "Barrelroll",
    "Swan Dive",
    "Flyin' and Skyin'!",
    "Air Time",
    "Air Time",
    "Got Hops?",
    "Got Hops?",
    "What Gravity?",
    "What Gravity?",
    "Show and Tell",
    "Show and Tell",
    "Hoopin' it Up",
    "Around the World",
    "Figure Hate",
    "Comin' Through",
    "Wassup?",
    "Marchin' to da Beat",
    "Illin'",
    "Raise da Roof",
    "Car Wash",
    "Too Easy",
    "Bring tha Noise",
    "Omega",
    "The X",
    "Throwin' Bows",
    "Swole",
    "Word Up",
    "Cake Walk",
    "High Steppin'",
    "Strong like Ox",
    "Raise it up",
    "Chop Down",
    "Rollin'",
    "Finish Line",
    "Show Me the Credits",
    "Da Bird",
    "Who's da Man?",
    "Makin' it Pretty",
    "Spanning the Globe",
    "Follow Me",
    "Hoopsta",
    "Low Ridin'",
    "This Way",
    "No Soup for You",
    "...And What?",
    "To da Hizzy fo'Shizzy",
    "Quick Six",
    "Movin' da Chains",
    "Movin' da Chains",
    "Pick",
    "Pick with Style",
    "User Pick",
    "User Pick with Style",
    "Bumrushed!",
    "User Bumrush!",
    "Opening a Can",
    "QB Crush",
    "D-Line Move",
    "D-Line Move! User-Like",
    "D-Line Move! User-Like",
    "Poppin' tha Rock",
    "User Pop!",
    "Turnover",
    "User Turnover",
    "Pick Up",
    "User Pick Up",
    "Payback!",
    "Ice Cream",
    "Pick For Six",
    "Jack For Six",
    "Simply, Amazing!",
    "Batted",
    "Ambushed",
    "User Ambush!",
    "Self Inflicted",
    "Stonewalled!",
    "Touchback",
    "Defensive Deuce",
    "Defensive Deuce",
    "User Defensive Deuce!",
    "West Coast Jack Move",
    "West Coast Jack Move",
    "Victory!",
    "Excellent!",
    "Awesome!",
    "Domination!",
    "Perfect!",
    "Victory!",
    "Excellent!",
    "Awesome!",
    "Domination!",
    "Perfect!",
    "Combo x2",
    "Combo x3",
    "Combo x4",
    "Combo x5",
    "Combo x6",
    "Combo x7",
    "Combo x8",
    "Combo x9",
    "Combo x10",
    "West Coast",
    "Air Mail",
    "Pass Attack",
    "Cloud of Dust",
    "Makin' Head Room",
    "Marathon Man",
    "West Coast Six",
    "Air Mail for Six",
    "Pass Attack for Six",
    "Cloud of Dust for Six",
    "Makin' Head Room for Six",
    "Marathon Man for Six",
    "Keepin' it Real",
    "Keepin' it Real",
    "Makin' it Pretty",
    "Juggin' the Enemy",
    "Clownin' Fools",
    "Wall To Wall",
    "Showoff",
    "Hotspot",
    "Hotspot",
    "Hotspot",
    "Hotspot",
    "Hotspot",
    "I'll Take That",
    "What a Touchdown!",
};
const char _StyleTracker_aszComboLabels[44][20] = {
    "",
    "Catch",
    "Wall Catch",
    "Pass Gain",
    "Wall Pass",
    "Run",
    "Style Move",
    "TD",
    "Conversion",
    "4 Point",
    "Stopped Conversion",
    "Tackle",
    "Loss",
    "Sack",
    "1st Down",
    "1st Down",
    "Pump Fake",
    "Fakeout",
    "Fakeout",
    "Stiff Arm",
    "Pitch",
    "Broken Tackle",
    "Touchback",
    "Safety",
    "Safety",
    "Juke",
    "Spin",
    "Hurdle",
    "Dive",
    "Fakeout",
    "Fakeout",
    "INT",
    "Fumble",
    "Turnover",
    "Fumble Recovery",
    "QB Hit",
    "Rush Move",
    "Deflected",
    "Downs",
    "Jack",
    "Combo",
    "Hotspot",
    "Strip",
    "Wall Move",
};
const StyleAwardGrowth_t _StyleTracker_sNoGrowth = {0, 0, {0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0, 0, 0}};
const StyleAwardGrowth_t _StyleTracker_sRunGrowth = {1, 100, {0, 0, 0, 20}, 1, {0, 0, 0, 0, 0, 0, 0, 104}};
const StyleAwardGrowth_t _StyleTracker_sComboRunGrowth = {1, 100, {0, 0, 0, 20}, 1, {0, 0, 0, 6, 0, 0, 0, 211}};
const StyleAwardStep_t _StyleTracker_aRunSteps[10] = {
    {0, (StyleMessage)104, 10, {0, 0, 0, 1}, 5, 1, 1},
    {0, (StyleMessage)104, 160, {0, 0, 0, 16}, 20, 1, 1},
    {0, (StyleMessage)104, 560, {0, 0, 0, 56}, 40, 1, 1},
    {0, (StyleMessage)104, 1160, {0, 0, 0, 116}, 60, 1, 1},
    {0, (StyleMessage)104, 2660, {0, 0, 1, 10}, 90, 1, 1},
    {0, (StyleMessage)104, 4460, {0, 0, 1, 190}, 120, 1, 1},
    {0, (StyleMessage)104, 7660, {0, 0, 2, 254}, 160, 1, 1},
    {0, (StyleMessage)104, 12160, {0, 0, 4, 192}, 200, 1, 1},
    {0, (StyleMessage)104, 16160, {0, 0, 6, 80}, 240, 1, 1},
    {0, (StyleMessage)104, 23360, {0, 0, 9, 32}, 300, 1, 1},
};
const StyleAwardStep_t _StyleTracker_aComboRunSteps[10] = {
    {6, (StyleMessage)104, 10, {0, 0, 0, 1}, 5, 1, 1},
    {6, (StyleMessage)104, 160, {0, 0, 0, 16}, 20, 1, 1},
    {6, (StyleMessage)104, 560, {0, 0, 0, 56}, 40, 1, 1},
    {6, (StyleMessage)104, 1160, {0, 0, 0, 116}, 60, 1, 1},
    {6, (StyleMessage)104, 2660, {0, 0, 1, 10}, 90, 1, 1},
    {6, (StyleMessage)104, 4460, {0, 0, 1, 190}, 120, 1, 1},
    {6, (StyleMessage)104, 7660, {0, 0, 2, 254}, 160, 1, 1},
    {6, (StyleMessage)104, 12160, {0, 0, 4, 192}, 200, 1, 1},
    {6, (StyleMessage)104, 16160, {0, 0, 6, 80}, 240, 1, 1},
    {6, (StyleMessage)104, 23360, {0, 0, 9, 32}, 300, 1, 1},
};
const StyleAwardStep_t _StyleTracker_aPassGainSteps[10] = {
    {3, (StyleMessage)195, 1000, {0, 0, 0, 100}, 4, 0, 0},
    {3, (StyleMessage)196, 3000, {0, 0, 1, 44}, 10, 0, 0},
    {3, (StyleMessage)197, 7000, {0, 0, 2, 188}, 20, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aRushGainSteps[10] = {
    {5, (StyleMessage)199, 3000, {0, 0, 1, 44}, 8, 0, 0},
    {5, (StyleMessage)200, 7000, {0, 0, 2, 188}, 16, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aPassTouchdownSteps[10] = {
    {7, (StyleMessage)201, 2000, {0, 0, 0, 200}, 1, 0, 0},
    {7, (StyleMessage)202, 4000, {0, 0, 1, 144}, 10, 0, 0},
    {7, (StyleMessage)203, 7500, {0, 0, 2, 238}, 20, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aRushTouchdownSteps[10] = {
    {7, (StyleMessage)204, 2000, {0, 0, 0, 200}, 1, 0, 0},
    {7, (StyleMessage)205, 4000, {0, 0, 1, 144}, 8, 0, 0},
    {7, (StyleMessage)206, 7500, {0, 0, 2, 238}, 16, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aVictorySteps[10] = {
    {0, (StyleMessage)176, 10000, {0, 0, 0, 0}, 1, 0, 0},
    {0, (StyleMessage)177, 15000, {0, 0, 0, 0}, 25, 0, 0},
    {0, (StyleMessage)178, 20000, {0, 0, 0, 0}, 40, 0, 0},
    {0, (StyleMessage)179, 25000, {0, 0, 0, 0}, 70, 0, 0},
    {0, (StyleMessage)180, 30000, {0, 0, 0, 0}, 100, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aSpecialVictorySteps[10] = {
    {0, (StyleMessage)181, 35000, {0, 0, 0, 0}, 1, 0, 0},
    {0, (StyleMessage)182, 40000, {0, 0, 0, 0}, 25, 0, 0},
    {0, (StyleMessage)183, 45000, {0, 0, 0, 0}, 40, 0, 0},
    {0, (StyleMessage)184, 50000, {0, 0, 0, 0}, 70, 0, 0},
    {0, (StyleMessage)185, 55000, {0, 0, 0, 0}, 100, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aComboSteps[10] = {
    {0, (StyleMessage)186, 2000, {0, 0, 0, 200}, 2, 0, 0},
    {0, (StyleMessage)187, 3000, {0, 0, 1, 44}, 3, 0, 0},
    {0, (StyleMessage)188, 4000, {0, 0, 1, 144}, 4, 0, 0},
    {0, (StyleMessage)189, 6000, {0, 0, 2, 88}, 5, 0, 0},
    {0, (StyleMessage)190, 10000, {0, 0, 3, 232}, 6, 0, 0},
    {0, (StyleMessage)191, 15000, {0, 0, 5, 220}, 7, 0, 0},
    {0, (StyleMessage)192, 20000, {0, 0, 7, 208}, 8, 0, 0},
    {0, (StyleMessage)193, 30000, {0, 0, 11, 184}, 9, 0, 0},
    {0, (StyleMessage)194, 40000, {0, 0, 15, 160}, 10, 0, 0},
    {0, (StyleMessage)0, 0, {0, 0, 0, 0}, 0, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aStylePitchSteps[10] = {
    {20, (StyleMessage)24, 1500, {0, 0, 0, 150}, 1, 0, 0},
    {20, (StyleMessage)25, 2000, {0, 0, 0, 200}, 2, 0, 0},
    {20, (StyleMessage)26, 2500, {0, 0, 0, 250}, 3, 0, 0},
    {20, (StyleMessage)27, 3000, {0, 0, 1, 44}, 4, 0, 0},
    {20, (StyleMessage)28, 4500, {0, 0, 1, 194}, 5, 0, 0},
    {20, (StyleMessage)29, 6000, {0, 0, 2, 88}, 6, 0, 0},
    {20, (StyleMessage)30, 7750, {0, 0, 3, 7}, 7, 0, 0},
    {20, (StyleMessage)31, 9750, {0, 0, 3, 207}, 8, 0, 0},
    {20, (StyleMessage)32, 12000, {0, 0, 4, 176}, 9, 0, 0},
    {20, (StyleMessage)33, 14500, {0, 0, 5, 170}, 10, 0, 0},
};
const StyleAwardStep_t _StyleTracker_aPitchSteps[10] = {
    {20, (StyleMessage)24, 1000, {0, 0, 0, 100}, 1, 0, 0},
    {20, (StyleMessage)25, 1500, {0, 0, 0, 150}, 2, 0, 0},
    {20, (StyleMessage)26, 2000, {0, 0, 0, 200}, 3, 0, 0},
    {20, (StyleMessage)27, 2500, {0, 0, 0, 250}, 4, 0, 0},
    {20, (StyleMessage)28, 3500, {0, 0, 1, 94}, 5, 0, 0},
    {20, (StyleMessage)29, 5000, {0, 0, 1, 244}, 6, 0, 0},
    {20, (StyleMessage)30, 7500, {0, 0, 2, 238}, 7, 0, 0},
    {20, (StyleMessage)31, 9000, {0, 0, 3, 132}, 8, 0, 0},
    {20, (StyleMessage)32, 10000, {0, 0, 3, 232}, 9, 0, 0},
    {20, (StyleMessage)33, 12500, {0, 0, 4, 226}, 10, 0, 0},
};

StyleAwardCallback _StyleTracker_pAwardCallback = 0;
unsigned char _StyleTracker_bEnabled = 1;
unsigned char _StyleTracker_bCombosEnabled = 1;
int _StyleTracker_iDatabaseVariant = 2;
float _StyleTracker_fProfilePointScale = 0.0004f;
int _StyleTracker_iMeterThreshold = 20000;
StyleTrackerState_t *_StyleTracker_pState = 0;
unsigned char _StyleTracker_cWinner = 2;

int _StyleTracker_aiPlayStylePoints[2];
int _StyleTracker_aiPlayPitches[2];
unsigned char _StyleTracker_acQbStopStreak[2];
unsigned char _StyleTracker_abQbStopThisPlay[2];
unsigned char _StyleTracker_acUserQbStopStreak[2];
unsigned char _StyleTracker_abUserQbStopThisPlay[2];
unsigned char _StyleTracker_acCatchStreak[2];
unsigned char _StyleTracker_abCatchThisPlay[2];
unsigned char _StyleTracker_abCatchOpportunity[2];
unsigned char _StyleTracker_acStyleCatchStreak[2];
unsigned char _StyleTracker_abStylePassThisPlay[2];
unsigned char _StyleTracker_acConsecutivePitches[2];
unsigned char _StyleTracker_acLongestPitchChain[2];

const char _StyleTracker_szComboSeparator[4] = " + ";
const char _StyleTracker_szEmptyCombo[1] = "";
}
