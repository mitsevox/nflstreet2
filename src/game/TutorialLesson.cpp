/* The in-game tutorial: five lessons (Running the Ball, Passing, Styling, Defense, New Stuff),
   each a list of steps. For every step the tutorial sets up the plays and the ball, shows the
   step title and the button prompts, watches for the moves the step asks for, then shows the
   results popup with Retry, Quit or the next step, and at the end of a category sends the
   player to the matching game mode. */

#include "engine/cu_80229270.h"
#include "game/StyleTracker.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_801FCE10.h"
#include "game/Object_80039F5C.h"
#include "game/DepthChart.h"
#include "game/DepthChartSide.h"
#include "game/GameOptions.h"
#include "game/fn_801C1F94.h"
#include "game/GameModeType.h"
#include "game/MsgGame.h"
#include "game/ModuleGroup_8003450C.h"
#include "game/SndgCrowd.h"
#include "game/PauseMenu.h"
#include "game/GameCamera.h"
#include "game/Class_80148A58.h"
#include "game/InGame.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/fn_80178D18.h"
#include "game/fn_80218FC4.h"
#include "game/HudEvents.h"
#include "game/LivePlayPhase.h"
#include "game/PreGamePhase.h"
#include "game/PostPlayPhase.h"
#include "game/PreSnapPhase.h"
#include "game/ScrmRuleSet.h"
#include "game/fn_800B65A0.h"
#include "game/fn_8009D990.h"

/* One step of a tutorial lesson (32-byte records of the step tables). */
struct TutorialStep_t {
    unsigned long long mMask;
    unsigned int mDuration;
    float mUnknown12;
    unsigned int mPrompts;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
};

/* Base of the five tutorial lessons; the vtable pointer follows the one word
   of data. */
class TutorialLesson {
public:
    virtual void Begin() = 0;
    virtual int End() = 0;
    virtual int GetPromptCount();
    virtual int GetTeamSize();
    virtual int GetOffenseSize();
    virtual int GetDefenseSize();
    virtual TutorialStep_t *GetStep() = 0;
    virtual const char *GetIntroText() = 0;
    virtual const char *GetDoneText() = 0;

    int mUnknown0;
};

struct TutorialObjects;
struct TutorialNewStuffObjects;
struct TutorialStylingObjects;

struct TutorialObjectsPtr {
    TutorialObjectsPtr() : mp(0) {}
    TutorialObjects *mp;
};

struct TutorialNewStuffObjectsPtr {
    TutorialNewStuffObjectsPtr() : mp(0) {}
    TutorialNewStuffObjects *mp;
};

struct TutorialStylingObjectsPtr {
    TutorialStylingObjectsPtr() : mp(0) {}
    TutorialStylingObjects *mp;
};

class TutorialLessonRunning : public TutorialLesson {
public:
    virtual void Begin();
    virtual int End();
    virtual TutorialStep_t *GetStep();
    virtual const char *GetIntroText();
    virtual const char *GetDoneText();
    virtual ~TutorialLessonRunning() {}

    TutorialObjectsPtr mpGame;
};

class TutorialLessonNewStuff : public TutorialLesson {
public:
    virtual void Begin();
    virtual int End();
    virtual TutorialStep_t *GetStep();
    virtual const char *GetIntroText();
    virtual const char *GetDoneText();
    virtual ~TutorialLessonNewStuff() {}

    int mUnknown8;
    TutorialNewStuffObjectsPtr mpGame;
};

class TutorialLessonPassing : public TutorialLesson {
public:
    virtual void Begin();
    virtual int End();
    virtual TutorialStep_t *GetStep();
    virtual const char *GetIntroText();
    virtual const char *GetDoneText();
    virtual ~TutorialLessonPassing() {}

    TutorialObjectsPtr mpGame;
};

class TutorialLessonStyling : public TutorialLesson {
public:
    virtual void Begin();
    virtual int End();
    virtual TutorialStep_t *GetStep();
    virtual const char *GetIntroText();
    virtual const char *GetDoneText();
    virtual ~TutorialLessonStyling() {}

    TutorialStylingObjectsPtr mpGame;
};

class TutorialLessonDefense : public TutorialLesson {
public:
    virtual void Begin();
    virtual int End();
    virtual TutorialStep_t *GetStep();
    virtual const char *GetIntroText();
    virtual const char *GetDoneText();
    virtual ~TutorialLessonDefense() {}

    TutorialObjectsPtr mpGame;
};

class TutorialPreGame : public PreGamePhase {
public:
    virtual void OnEnter();
    virtual void OnUpdate(float dt);
    virtual void ShowIntroScreen();
    virtual void HideIntroScreen();
    virtual void EnterFirstPhase(float dt);

    int mUnknown4;
};

class TutorialPreSnap : public PreSnapPhase {
public:
    virtual ~TutorialPreSnap() {}
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit(float dt);
    virtual unsigned char AllowsPressPrompts() { return mUnknown4; }
    virtual int CanSnap();

    unsigned char mUnknown4;
};

class TutorialLivePlay : public LivePlayPhase {
public:
    virtual void OnEnter();
    virtual void OnUpdate(float dt);
};

class TutorialPostPlay : public PostPlayPhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit();
    virtual void OnSequenceStart();
    virtual void ShowResultText();
    virtual void UpdateCue(float dt);
    virtual int IsHeld(float dt);
    virtual int GetBusy(float dt);
    virtual void Finish(float dt);
    TutorialPostPlay() : mUnknown8(0) {}
    virtual ~TutorialPostPlay() {}
    void ShowResults();

    unsigned char mUnknown4;
    unsigned char mUnknown5;
    signed char mUnknown6;
    unsigned int mUnknown8;
    int mUnknown12;
};

class TutorialRuleSet : public ScrmRuleSet {
public:
    virtual int GetWinner();
    virtual int IsTimed();
    virtual void ResetPlaySpot();
    virtual void ResetGame(int a);
    virtual int UsesBothTeams();
    virtual int AllowsAudibles() { return 0; }
};

class TutorialLivePlayNewStuff : public TutorialLivePlay {
public:
    virtual void OnUpdate(float dt);
};

class TutorialPostPlayNewStuff : public TutorialPostPlay {
public:
    virtual void OnEnter(float dt);
};

/* Flag member of TutorialPreSnapNewStuff, cleared on construction. */
struct TutorialOnceFlag {
    TutorialOnceFlag() : m(0) {}
    unsigned char m;
};

class TutorialPreSnapNewStuff : public TutorialPreSnap {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);

    TutorialOnceFlag mUnknown8;
};

class TutorialLivePlayStyling : public TutorialLivePlay {
public:
    virtual void OnUpdate(float dt);
};

/* The game objects a lesson creates in its first entry. */
struct TutorialObjects {
    TutorialPreGame mObject0;
    TutorialPreSnap mObject8;
    TutorialLivePlay mObject16;
    TutorialPostPlay mObject20;
    TutorialRuleSet mObject36;
};

struct TutorialStylingObjects {
    TutorialPreGame mObject0;
    TutorialPreSnap mObject8;
    TutorialLivePlayStyling mObject16;
    TutorialPostPlay mObject20;
    TutorialRuleSet mObject36;
};

struct TutorialNewStuffObjects {
    TutorialPreGame mObject0;
    TutorialPreSnapNewStuff mObject8;
    TutorialLivePlayNewStuff mObject20;
    TutorialPostPlayNewStuff mObject24;
    TutorialRuleSet mObject40;
};


/* Two floats returned in memory by fn_80177FE0. */
struct FieldSpot_t {
    float mX;
    float mY;
};

struct PlaybookTeamView {
    char mUnknown0[0x40];
    int mUnknown40;
};

/* Text block posted with messages 0x80000080 and 0x80000081. */
struct TutorialTitleText_t {
    TutorialTitleText_t() {}
    int mUnknown0;
    int mSize;
    char *mpText;
};

void *operator new(unsigned int size, int unknown);

extern "C" {
void PlyrMgrClearStates(void);
void DepthChartRevertSide(int group);
void DepthChartSetSide(int group, int *values);
void BigObjNotifyTypes(int a);
void fn_8004730C(int a);
void PlyrNameTagEnable(unsigned char enable);
void MsgBoxShow(const char *pTitle, const char *pText, const char *pButtons);
int MsgBoxIsClosed(void);
void fn_80057F28(void);
void fn_800582D0(void);
void fn_8005BF18(void);
int fn_8005BFD4(void);
void PauseRequestCancel(void);
void SndgAmbPostCue(int type);
void SndgSetVolumeOption(int channel, unsigned int level);
void SndgApplyVolumeOptions(void);
void fn_8006F824(int a);
void SndgMusicFadeOut(int a, int b);
int SndgMusicIsPaused(void);
void SndgMusicResume(void);
void SndgMusicPumpFrame(int a);
void SpchIGSetCommentaryOn(unsigned char value);
int SpchIGIsNarratorIdle(void);
int fn_80085A34(int formation, int team);
unsigned char TutorialDbOpenPlays(void);
unsigned char TutorialDbClosePlays(void);
int TutorialGetStepCount(int id);
void TutorialSetStepCount(unsigned int id, unsigned int count);
int TutorialIsComplete(int id);
unsigned int TutorialGetPlayIndex(int a, int b, int flag);
unsigned int TutorialGetOtherPlayIndex(int a, int b, int flag);
int TutorialGetStepSide(int a, int b);
float TutorialGetStepOffset(int a, int b);
void fn_8009B924(void);
void fn_8009D888(int index, int a);
void fn_8009D8CC(int index);
void fn_8009D944(int index);
void fn_8009D964(int index, int value);
void fn_8009D984(int a);
void fn_8009E01C(void);
void fn_800A039C(LivePlayPhase *pObject);
void fn_800A7A0C(int a);
void fn_800A7B5C(void);
void fn_800A8F08(void);
void fn_800AD910(int a, float b);
void fn_800AE988(void);
void fn_800B3EFC(int team);
void fn_800B63B0(void);
int fn_800B81A4(void);
void fn_800B847C(int a, int b);
void fn_800B9598(PostPlayPhase *pObject);
void fn_800BC51C(PreGamePhase *pObject);
void fn_800BF658(int a);
void fn_800BF6CC(int a);
void fn_800BFAB4(PreSnapPhase *pObject);
void fn_800C1CA0(void);
void fn_800C1E50(void);
void fn_800C87CC(int a, int b);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_8011DF90(void);
void BallPrimeKickUp(Ball_t *pBall);
void fn_8013A910(Ball_t *pBall, int *pAngles);
void fn_8013AD9C(Ball_t *pBall, int a);
int BallStateGet(Ball_t *pBall, int *pOut);
void CamMainWarpToDest(GameCamera_t *pCamera);
void CamGameSelectCamera(int a);
GameCamera_t *CamGameGetCamera(int index);
void CamGameSetFocusAll(int a, int b);
void CamGameSetModeAll(int a);
void fn_801485B4(void);
void fn_801485EC(int mode);
int fn_801485F4(void);
void fn_80148644(void);
int fn_801486A0(void);
Class_80148A58 * fn_80148A58(void);
void fn_80149040(Object_80039F5C *pObject);
void fn_8014F3DC(int a);
void fn_8015C254(int a);
void PlayBookLoadCurrentPlay(int team);
void PlayBookLoadAudibleTable(void);
void PlayBookSetFormationType(int team, int kind);
void PlayBookSetIndices(int team, unsigned int a, unsigned int b, unsigned int c);
PlaybookTeamView * PlayBookGetTeam(int team);
void ClockRuleClearFlags(unsigned int mask);
void fn_80177C50(int a);
void fn_80177E6C(int a, int b);
int fn_80177F70(void);
void fn_80177F88(int a);
FieldSpot_t fn_80177FE0(void);
void fn_801780A8(FieldSpot_t pos);
void fn_801782B0(void);
int fn_80178320(void);
void fn_8017833C(int value);
void fn_80178370(void);
int fn_801784E8(void);
void fn_801787FC(int which, short value);
float fn_80178A2C(void);
int fn_80178C60(void);
void fn_80178CD8(int a);
void fn_80178F20(ScrmRuleSet *pObject);
void HudSetScore(int a, int b);
void HudShowPressPrompt(int a);
void HudStop(void);
int MsgGameTakePendingChoice(void);
void RumbleStopAll(void);
void RumbleEnable(unsigned char enabled);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
char * fn_801C2EF0(char *pDest, const char *pSource, int count);
unsigned int fn_801C3180(const char *pText);
void fn_802195E4(void *p, short a, short b);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void TutorialPostPrompt(int index, int value);
void TutorialSetupRosters(void);
void TutorialSetAnnounceStep(unsigned char value);
unsigned char TutorialGetAnnounceStep(void);
void TutorialInit(void);
void TutorialShutdown(void);
int TutorialIsActive(void);
void TutorialSetStep(unsigned int value);
void TutorialSetLesson(unsigned int value);
void TutorialSetActiveStep(unsigned int value);
void TutorialLessonStart(void);
void TutorialLessonStop(void);
unsigned int TutorialGetStep(void);
unsigned int TutorialGetLesson(void);
TutorialLesson * TutorialGetLessonObject(void);
void TutorialBlinkInit(unsigned int count, unsigned int total);
void TutorialBlinkRestart(void);
unsigned char TutorialBlinkUpdate(void);
unsigned char TutorialBlinkGetShown(void);
void TutorialBlinkSetShown(void);
int TutorialCompleteStep(unsigned int lesson);
void TutorialSetupPlays(void);
void TutorialClearMoves(void);
void TutorialSetMoveDone(int index, int value);
int TutorialAreMovesDone(unsigned long long mask);
unsigned char TutorialIsStepDone(void);
void TutorialSetStepDone(unsigned char value);
void TutorialTimerStart(unsigned int duration);
int TutorialTimerIsDone(void);
void TutorialGetHudPosition(float *pX, float *pY, float *pZ);
void TutorialShowPrompts(unsigned int mask, int value, int flag);
void TutorialHidePrompts(void);
float TutorialGetStartLine(void);
int TutorialFinishCategory(void);
short TutorialScaleCpuRating(int team, int unused, short value);
void TutorialSetHudVisible(int value);
void TutorialReleasePause(void);
unsigned char TutorialIsContinuing(void);
void TutorialShowTitles(int show);
void TutorialReloadRatings(void);
void TutorialSetupSession(void);
void TutorialBlinkPrompts(unsigned int mask);

extern void *gUISMainInfo;
extern const float lbl_803ED6A4;
extern const float lbl_803ED6A8;
}

#define TIME_HOURS(t) ((t) / 3600)
#define TIME_MINUTES(t) ((t) / 60 - TIME_HOURS(t) * 60)
#define TIME_SECONDS(t) ((t) - (TIME_HOURS(t) * 60 + TIME_MINUTES(t)) * 60)

extern "C" {
TutorialTitleText_t _Tutorial_CategoryText;
TutorialTitleText_t _Tutorial_StepText;
TutorialLessonRunning _Tutorial_LessonRunning;
TutorialLessonPassing _Tutorial_LessonPassing;
TutorialLessonStyling _Tutorial_LessonStyling;
TutorialLessonDefense _Tutorial_LessonDefense;
TutorialLessonNewStuff _Tutorial_LessonNewStuff;
int _Tutorial_aMoveDone[45];
char _Tutorial_szCategoryTitle[0x1C];
char _Tutorial_szStepTitle[0x20];

int _Tutorial_aPromptMsgIds[] = {
    0x8000005A, 0x8000005B, 0x8000005A, 0x80000060, 0x8000005E, 0x8000005C, 0x8000005D,
    0x8000005F, 0x80000066, 0x80000065, 0x80000061, 0x80000062, 0x80000063, 0x80000064,
};

TutorialLesson *_Tutorial_pLesson = 0;
unsigned int _Tutorial_uStep = 0xFFFF;
unsigned int _Tutorial_uLesson = 0xFFFF;
unsigned int _Tutorial_uActiveStep = 0xFFFF;
int _Tutorial_iSavedSetting0 = 1;
int _Tutorial_iSavedSetting14 = 0;
unsigned char _Tutorial_bAnnounceStep = 1;

TutorialTitleText_t *_Tutorial_pCategoryText;
TutorialTitleText_t *_Tutorial_pStepText;
int _Tutorial_iTitlesShown;
unsigned char _Tutorial_bStepDone;
unsigned int _Tutorial_uStartStep;
unsigned int _Tutorial_uBlinkStart;
unsigned int _Tutorial_uBlinkNext;
unsigned int _Tutorial_uBlinkPeriod;
unsigned char _Tutorial_bBlinkOn;
unsigned char _Tutorial_bBlinkShown;
unsigned int _Tutorial_uTimerStart;
unsigned int _Tutorial_uTimerEnd;
unsigned char _Tutorial_bContinuing;

TutorialStep_t _Tutorial_aDefenseSteps[] = {
    { 0x1ULL, 3, 1.0f, 0x2, 5, 0, 0 },
    { 0x1000000000ULL, 3, 1.0f, 0x20, 15, 0, 0 },
    { 0x8000000000ULL, 3, 1.0f, 0x10, 5, 0, 0 },
    { 0x800000ULL, 3, 1.0f, 0x80, 5, 0, 0 },
    { 0x400000ULL, 3, 1.0f, 0x40, 5, 0, 0 },
    { 0x20000000000ULL, 3, 1.0f, 0x81, 5, 0, 0 },
};

TutorialStep_t _Tutorial_aNewStuffSteps[] = {
    { 0x40ULL, 3, 1.0f, 0x21, 5, 0, 0 },
    { 0x800ULL, 3, 1.0f, 0x81, 5, 0, 0 },
    { 0x4000ULL, 6, 1.0f, 0x81, 5, 0, 0 },
    { 0x80001000000ULL, 3, 1.0f, 0xB1, 5, 0, 0 },
    { 0x4000000000ULL, 3, 1.0f, 0x41, 5, 0, 0 },
    { 0x600000000ULL, 3, 1.0f, 0x80, 5, 1, 0 },
    { 0x10000000000ULL, 3, 1.0f, 0x80, 5, 1, 0 },
    { 0xA00000000ULL, 15, 1.0f, 0x80, 5, 1, 0 },
    { 0x100000000000ULL, 3, 1.0f, 0xA1, 5, 0, 0 },
};

TutorialStep_t _Tutorial_aPassingSteps[] = {
    { 0x200000ULL, 3, 1.0f, 0x2, 0, 0, 0 },
    { 0x80024000000ULL, 3, 1.0f, 0x80, 15, 0, 0 },
    { 0x80030000000ULL, 3, 1.0f, 0x20, 15, 0, 0 },
    { 0x80028000000ULL, 3, 1.0f, 0x10, 15, 0, 0 },
    { 0xC0004000000ULL, 3, 1.0f, 0x80, 1, 0, 0 },
    { 0xC0010000000ULL, 3, 1.0f, 0x20, 1, 0, 0 },
    { 0xC0008000000ULL, 3, 1.0f, 0x10, 1, 0, 0 },
    { 0x8ULL, 3, 1.0f, 0x40, 5, 0, 0 },
    { 0x80000ULL, 3, 1.0f, 0x8, 5, 0, 0 },
};

TutorialStep_t _Tutorial_aRunningSteps[] = {
    { 0x1ULL, 3, 1.0f, 0x2, 0, 0, 0 },
    { 0x10000ULL, 3, 1.0f, 0x10, 5, 0, 0 },
    { 0x10ULL, 3, 1.0f, 0x20, 15, 0, 0 },
    { 0x80ULL, 3, 1.0f, 0x20, 0, 0, 0 },
    { 0x200ULL, 3, 1.0f, 0x80, 5, 0, 0 },
    { 0x1000ULL, 3, 1.0f, 0x80, 5, 0, 0 },
    { 0x20000ULL, 5, 1.0f, 0x40, 5, 0, 0 },
};

TutorialStep_t _Tutorial_aStylingSteps[] = {
    { 0x8000ULL, 3, 1.0f, 0x1, 0, 0, 0 },
    { 0x100000ULL, 3, 1.0f, 0x201, 5, 0, 0 },
    { 0x20ULL, 3, 1.0f, 0x21, 15, 0, 0 },
    { 0x100ULL, 3, 1.0f, 0x21, 5, 0, 0 },
    { 0x400ULL, 3, 1.0f, 0x81, 5, 0, 0 },
    { 0x2000ULL, 3, 1.0f, 0x81, 5, 0, 0 },
    { 0x80002000000ULL, 3, 1.0f, 0xB1, 5, 0, 0 },
    { 0x2000000000ULL, 3, 1.0f, 0x41, 5, 0, 0 },
};
char _Tutorial_szPassed[] = "You Passed.  Awesome!";
char _Tutorial_szNeedPractice[] = "You need more practice at this.";
char _Tutorial_szQuitConfirm[] = "Are you sure you want to quit?";
char _Tutorial_szCategoryDone[] = "Congratulations! You have completed this tutorial category.";

}


extern "C" {

void TutorialPostPrompt(int index, int value)
{
    fn_8021D7B8(gUISMainInfo, _Tutorial_aPromptMsgIds[index], 1, &value);
}

void TutorialSetupRosters(void)
{
    DepthChartSide_t records[2];
    int list[8];
    int home;
    int away;
    unsigned int team;
    unsigned int i;

    fn_801FCE10(0, "select 'GTHG' into \x82 and 'GTAG' into \x82 from 'FNIG'\n", &home, &away);
    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 6; i++) {
            list[i] = PlyrGet((unsigned char)team, i)->mUnknown2908;
        }
        list[7] = 0x7FFF;
        DepthChartAutoFill(team, list, 4);
        DepthChartRevertSide(team);
    }
    DepthChartGetSide(0, &records[0]);
    DepthChartGetSide(1, &records[1]);
    fn_801FCE10(0, "delete from 'AGCD'\n");
    /* 0x41474344 is 'AGCD', the table cleared by the query above. */
    fn_8022DA44(home, records[0].mUnknown, away, records[1].mUnknown, 0x41474344);
    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 6; i++) {
            Object_80039F5C *pObject = PlyrGet((unsigned char)team, i);
            pObject->mUnknown2908 = records[team].mUnknown[i];
            fn_80149040(pObject);
        }
    }
    for (i = 0; i < 14; i++) {
        fn_801FCE10(0, "select 'DIOP' into \x85 from 'YALP' where 'DIGP' = \x85 and 'DIGT' = \x85\n",
                    &records[0].mUnknown[i], records[0].mUnknown[i], home);
        fn_801FCE10(0, "select 'DIOP' into \x85 from 'YALP' where 'DIGP' = \x85 and 'DIGT' = \x85\n",
                    &records[1].mUnknown[i], records[1].mUnknown[i], away);
    }
    DepthChartSetSide(0, records[0].mUnknown);
    DepthChartSetSide(1, records[1].mUnknown);
}

void TutorialSetAnnounceStep(unsigned char value)
{
    _Tutorial_bAnnounceStep = value;
}

unsigned char TutorialGetAnnounceStep(void)
{
    return _Tutorial_bAnnounceStep;
}

void TutorialInit(void)
{
    _Tutorial_bContinuing = 0;
}

void TutorialShutdown(void)
{
    _Tutorial_bContinuing = 0;
}

int TutorialIsActive(void)
{
    return _Tutorial_uActiveStep != 0xFFFF;
}

void TutorialSetStep(unsigned int value)
{
    _Tutorial_uStep = value;
}

void TutorialSetLesson(unsigned int value)
{
    _Tutorial_uLesson = value;
}

void TutorialSetActiveStep(unsigned int value)
{
    _Tutorial_uActiveStep = value;
}

void TutorialLessonStart(void)
{
    unsigned int lesson = TutorialGetLesson();
    unsigned int step = TutorialGetStep();

    _Tutorial_uStartStep = step;
    switch (lesson) {
    case 0:
        _Tutorial_pLesson = &_Tutorial_LessonRunning;
        break;
    case 1:
        _Tutorial_pLesson = &_Tutorial_LessonPassing;
        break;
    case 2:
        _Tutorial_pLesson = &_Tutorial_LessonStyling;
        break;
    case 3:
        _Tutorial_pLesson = &_Tutorial_LessonDefense;
        break;
    case 4:
        _Tutorial_pLesson = &_Tutorial_LessonNewStuff;
        break;
    }
    _Tutorial_iSavedSetting14 = GameOptionsGet(14);
    GameOptionsSet(14, 0);
    fn_80178F20(0);
    _Tutorial_pLesson->mUnknown0 = step;
    _Tutorial_pLesson->Begin();
    _Tutorial_iSavedSetting0 = GameOptionsGet(0);
    GameOptionsSet(0, 0);
    TutorialDbOpenPlays();
    TutorialSetActiveStep(step);
    TutorialSetAnnounceStep(1);
}

void TutorialLessonStop(void)
{
    _Tutorial_pLesson->End();
    _Tutorial_pLesson = 0;
    TutorialDbClosePlays();
    GameOptionsSet(14, _Tutorial_iSavedSetting14);
    _Tutorial_iSavedSetting14 = 0;
    fn_80178F20(0);
    GameOptionsSet(0, _Tutorial_iSavedSetting0);
    _Tutorial_iSavedSetting0 = 1;
    SndgApplyVolumeOptions();
    _Tutorial_uActiveStep = 0xFFFF;
    _Tutorial_uStep = 0xFFFF;
    TutorialSetLesson(5);
}

unsigned int TutorialGetStep(void)
{
    return _Tutorial_uStep;
}

unsigned int TutorialGetLesson(void)
{
    return _Tutorial_uLesson;
}

TutorialLesson *TutorialGetLessonObject(void)
{
    return _Tutorial_pLesson;
}

void TutorialBlinkInit(unsigned int count, unsigned int total)
{
    if (count != 0) {
        _Tutorial_uBlinkPeriod = total / count;
    } else {
        _Tutorial_uBlinkPeriod = 0;
    }
    _Tutorial_bBlinkOn = 0;
    _Tutorial_bBlinkShown = 0;
}

void TutorialBlinkRestart(void)
{
    unsigned int time = InGameGetFrameCount();

    _Tutorial_uBlinkStart = time;
    if (_Tutorial_uBlinkPeriod != 0) {
        _Tutorial_uBlinkNext = time + _Tutorial_uBlinkPeriod;
    } else {
        _Tutorial_uBlinkNext = 0;
    }
}

unsigned char TutorialBlinkUpdate(void)
{
    if (_Tutorial_uBlinkNext != 0) {
        if (InGameGetFrameCount() >= _Tutorial_uBlinkNext) {
            TutorialBlinkRestart();
            _Tutorial_bBlinkOn ^= 1;
        }
    } else {
        _Tutorial_bBlinkOn = 1;
    }
    return _Tutorial_bBlinkOn;
}

unsigned char TutorialBlinkGetShown(void)
{
    return _Tutorial_bBlinkShown;
}

void TutorialBlinkSetShown(void)
{
    _Tutorial_bBlinkShown = _Tutorial_bBlinkOn;
}

int TutorialCompleteStep(unsigned int lesson)
{
    int done = 0;
    unsigned int step = TutorialGetStep() + 1;
    unsigned int count = 0;

    TutorialSetStepCount(lesson, step);
    step = TutorialGetStepCount(lesson);
    switch (lesson) {
    case 0:
        count = 7;
        break;
    case 2:
        count = 8;
        break;
    case 3:
        count = 6;
        break;
    case 1:
    case 4:
        count = 9;
        break;
    }
    if (step == 0 && TutorialIsComplete(lesson) != 0) {
        if (TutorialGetStep() + 1 >= count) {
            done = 1;
        } else {
            step = TutorialGetStep() + 1;
        }
    }
    TutorialSetStep(step);
    return done;
}

void TutorialSetupPlays(void)
{
    unsigned int team;
    unsigned short i;
    int side;
    unsigned int a;
    unsigned int b;

    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 6; i++) {
            Object_80039F5C *pObject = PlyrGet((unsigned char)team, i);
            fn_800EFE60(0, pObject->mQueue, pObject);
        }
    }
    side = TutorialGetStepSide(TutorialGetLesson(), TutorialGetStep());
    b = TutorialGetOtherPlayIndex(TutorialGetLesson(), TutorialGetStep(), side);
    a = TutorialGetPlayIndex(TutorialGetLesson(), TutorialGetStep(), side);
    if (side == 1) {
        fn_8017833C(0);
        PlayBookSetFormationType(0, 1);
        PlayBookSetIndices(0, 0, 0, (unsigned char)a);
        PlayBookLoadCurrentPlay(0);
        PlayBookSetFormationType(1, 11);
        PlayBookSetIndices(1, 0, 0, (unsigned char)b);
        PlayBookLoadCurrentPlay(1);
    } else {
        fn_8017833C(1);
        PlayBookSetFormationType(1, 1);
        PlayBookSetIndices(1, 0, 0, (unsigned char)b);
        PlayBookLoadCurrentPlay(1);
        PlayBookSetFormationType(0, 11);
        PlayBookSetIndices(0, 0, 0, (unsigned char)a);
        PlayBookLoadCurrentPlay(0);
    }
    fn_800B3EFC(0);
    fn_800B3EFC(1);
}

void TutorialClearMoves(void)
{
    fn_801C1F94(_Tutorial_aMoveDone, 0, sizeof(_Tutorial_aMoveDone));
}

void TutorialSetMoveDone(int index, int value)
{
    _Tutorial_aMoveDone[index] = value;
}

int TutorialAreMovesDone(unsigned long long mask)
{
    int result = 1;
    unsigned char i;

    for (i = 0; i <= 44; i++) {
        if ((mask >> i & 1) && _Tutorial_aMoveDone[i] == 0) {
            result = 0;
            break;
        }
    }
    return result;
}

unsigned char TutorialIsStepDone(void)
{
    return _Tutorial_bStepDone;
}

void TutorialSetStepDone(unsigned char value)
{
    _Tutorial_bStepDone = value;
}

void TutorialTimerStart(unsigned int duration)
{
    unsigned int seconds = TIME_SECONDS(fn_8009D990(2));

    _Tutorial_uTimerStart = seconds;
    _Tutorial_uTimerEnd = seconds + duration;
}

int TutorialTimerIsDone(void)
{
    unsigned int seconds = TIME_SECONDS(fn_8009D990(2));

    if (seconds < _Tutorial_uTimerStart) {
        seconds += 60;
    }
    return seconds >= _Tutorial_uTimerEnd;
}

void TutorialGetHudPosition(float *pX, float *pY, float *pZ)
{
    *pX = 620.0f;
    *pY = 408.0f;
    *pZ = 1.0f;
}

void TutorialShowPrompts(unsigned int mask, int value, int flag)
{
    unsigned int i;

    TutorialHidePrompts();
    for (i = 0; i <= 13; i++) {
        if (mask & 1 << i) {
            int arg;

            if (i < 3) {
                if (flag) {
                    arg = 1;
                } else {
                    arg = value;
                }
            } else {
                arg = value;
            }
            if (arg != 0) {
                TutorialPostPrompt(i, arg);
            }
        }
    }
}

void TutorialHidePrompts(void)
{
    TutorialPostPrompt(1, 0);
    TutorialPostPrompt(0, 0);
    TutorialPostPrompt(3, 0);
    TutorialPostPrompt(2, 0);
    TutorialPostPrompt(5, 0);
    TutorialPostPrompt(7, 0);
    TutorialPostPrompt(7, 0);
    TutorialPostPrompt(4, 0);
    TutorialPostPrompt(6, 0);
    TutorialPostPrompt(8, 0);
    TutorialPostPrompt(9, 0);
    TutorialPostPrompt(10, 0);
    TutorialPostPrompt(11, 0);
    TutorialPostPrompt(12, 0);
    TutorialPostPrompt(13, 0);
}

float TutorialGetStartLine(void)
{
    float base = fn_80178A2C();
    float offset = TutorialGetStepOffset(TutorialGetLesson(), TutorialGetStep());

    if (offset >= base + base) {
        offset = base + base;
    }
    return base - offset;
}

}

int TutorialLesson::GetPromptCount()
{
    return 14;
}

int TutorialLesson::GetTeamSize()
{
    return 7;
}

int TutorialLesson::GetOffenseSize()
{
    return 7;
}

int TutorialLesson::GetDefenseSize()
{
    return 7;
}

extern "C" {

int TutorialFinishCategory(void)
{
    int done = 0;
    unsigned int lesson = TutorialGetLesson();
    int mode = fn_801486A0();

    if (lesson != 5) {
        int modes[5] = { 2, 3, 0, 4, 15 };
        mode = modes[lesson];
        fn_800AD910(0, 0.0f);
        HudStop();
        fn_800582D0();
        TutorialLessonStop();
        TutorialSetLesson(5);
        fn_800C1CA0();
        fn_800C1E50();
        fn_8004730C(1);
        fn_8015C254(1);
        PlyrNameTagEnable(1);
        if (mode != 15) {
            fn_801485B4();
            fn_801485EC(mode);
            switch (mode) {
            case 2:
                SpchIGSetCommentaryOn(0);
                fn_80148A58()->vfn_07(0, 1);
                fn_80148A58()->vfn_07(1, 5);
                break;
            case 0:
                ClockRuleClearFlags(0x800);
                fn_8009D8CC(1);
                fn_8009D964(1, 0);
                SpchIGSetCommentaryOn(0);
                fn_8014F3DC(180);
                break;
            case 4:
                if (fn_800B65A0(fn_80178320()) == 0xFF) {
                    fn_80177C50(0);
                }
                fn_80148A58()->vfn_07(0, 21);
                PlayBookSetFormationType(1, 1);
                PlayBookSetIndices(1, 0, 0, 0);
                PlayBookLoadCurrentPlay(1);
                fn_80085A34(PlayBookGetTeam(1)->mUnknown40, 1);
                fn_800B3EFC(1);
                fn_800B63B0();
                fn_800B847C(fn_800B65A0(1), 0);
                break;
            }
            TutorialSetupRosters();
            fn_801485F4();
            SndgMusicResume();
            SndgApplyVolumeOptions();
            SndgMusicResume();
            _Tutorial_bContinuing = 0;
        }
        done = 1;
    } else if (mode != 15) {
        unsigned int next = 5;
        switch (mode) {
        case 2:
            next = 1;
            break;
        case 3:
            next = 2;
            break;
        case 0:
            next = 3;
            break;
        case 4:
            next = 4;
            break;
        }
        SpchIGSetCommentaryOn(1);
        if (next != 5) {
            done = 1;
            fn_800AD910(0, 0.0f);
            HudStop();
            fn_800582D0();
            fn_80148644();
            fn_800C1CA0();
            fn_800C1E50();
            fn_8004730C(1);
            fn_8015C254(1);
            PlyrNameTagEnable(1);
            TutorialSetLesson(next);
            TutorialSetActiveStep(0);
            TutorialSetStep(0);
            TutorialSetupRosters();
            TutorialLessonStart();
            _Tutorial_bContinuing = done;
        }
    } else {
        SndgMusicResume();
        SndgApplyVolumeOptions();
        SndgMusicResume();
    }

    if (done) {
        for (unsigned int team = 0; team <= 1; team++) {
            for (unsigned int i = 0; i <= 6; i++) {
                Object_80039F5C *pPlayer = PlyrGet((unsigned char)team, i);
                pPlayer->mUnknown9[2] = i < (unsigned int)fn_80178D70((unsigned char)team);
            }
        }
        gTurbo.fn_80035EE0();
        fn_8009D8CC(2);
        fn_8009D984(fn_80178C60());
        StyleTrackerReset();
        gPlayBook.fn_800355FC();
        fn_80057F28();
        fn_800AD910(1, 0.0f);
        PauseClearBlocks();
        SndgAmbPostCue(3);
        SndgMusicResume();
        SndgCrowdTriggerEvent(3, 0);
        PlayBookLoadAudibleTable();
    }
    return done;
}

short TutorialScaleCpuRating(int team, int unused, short value)
{
    if (GameModeTypeGet() == 11 && fn_800B65A0(team) == 0xFF) {
        value = (short)(value * 0.75f);
    }
    return value;
}

void TutorialSetHudVisible(int value)
{
    fn_8021D7B8(gUISMainInfo, 0x80000072, 1, &value);
}

void TutorialReleasePause(void)
{
    if (GameModeTypeGet() == 11) {
        PauseRequestCancel();
        if (PauseIsUnblocked() == 0) {
            PauseUnblock();
        }
    }
}

unsigned char TutorialIsContinuing(void)
{
    return _Tutorial_bContinuing;
}

}

void TutorialLessonDefense::Begin()
{
    mpGame.mp = new (0) TutorialObjects;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    mpGame.mp->mObject36.ResetGame(2);
    fn_80178F20(&mpGame.mp->mObject36);
    TutorialGetStep();
}

int TutorialLessonDefense::End()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

TutorialStep_t *TutorialLessonDefense::GetStep()
{
    return &_Tutorial_aDefenseSteps[TutorialGetStep()];
}

const char *TutorialLessonDefense::GetIntroText()
{
    return "Defense, defense, defense.  You need to stop the other team to win.";
}

const char *TutorialLessonDefense::GetDoneText()
{
    return "You now have the skills to make the big stop!  Try them out in the 4 on 4 Street Event to 21 points.";
}

void TutorialLessonNewStuff::Begin()
{
    mpGame.mp = new (0) TutorialNewStuffObjects;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject20);
    fn_800B9598(&mpGame.mp->mObject24);
    fn_80178F20(&mpGame.mp->mObject40);
}

int TutorialLessonNewStuff::End()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

TutorialStep_t *TutorialLessonNewStuff::GetStep()
{
    return &_Tutorial_aNewStuffSteps[TutorialGetStep()];
}

const char *TutorialLessonNewStuff::GetIntroText()
{
    return "There are a lot of new skills to learn in NFL STREET 2, and you are going to need to master them all.";
}

const char *TutorialLessonNewStuff::GetDoneText()
{
    return "Now that you know how to use the walls and GameBreakers, you are ready for a full game of 7-on-7 to 36 points.";
}

void TutorialPreSnapNewStuff::OnEnter(float dt)
{
    TutorialPreSnap::OnEnter(dt);
    mUnknown8.m = 0;
    unsigned int step = TutorialGetStep();
    if (step >= 5 && step <= 7) {
        fn_800A7A0C(1);
        fn_800A8F08();
        if (step == 7) {
            StyleTrackerSetMeterFraction(1, lbl_803ED6A8, 0);
        } else {
            StyleTrackerSetMeterFraction(1, lbl_803ED6A4 + 0.2f, 0);
        }
        fn_800A7B5C();
    } else {
        fn_800A7A0C(1);
        if (step == 8) {
            BigObjNotifyTypes(0xC0);
        }
    }
}

void TutorialPreSnapNewStuff::OnUpdate(float dt)
{
    unsigned int step = TutorialGetStep();
    if (step >= 5 && step <= 7 && mUnknown4 && !mUnknown8.m) {
        HudShowPressPrompt(1);
        mUnknown8.m = 1;
    }
    TutorialPreSnap::OnUpdate(dt);
}

void TutorialLivePlayNewStuff::OnUpdate(float dt)
{
    static unsigned int _TutorialLivePlayNewStuff_uPromptCycle = 0;
    unsigned int step = TutorialGetStep();
    TutorialStep_t *pStep;

    if (step == 3) {
        LivePlayPhase::OnUpdate(dt);
        unsigned char done = TutorialIsStepDone();
        if (done == 0) {
            unsigned char button = TutorialBlinkUpdate();
            pStep = TutorialGetLessonObject()->GetStep();
            unsigned int prompts = pStep->mPrompts;
            if (BallStateGet(BallGetCurrent(), 0) != 4) {
                if (button != TutorialBlinkGetShown()) {
                    TutorialShowPrompts(pStep->mPrompts, 0, 1);
                    if (++_TutorialLivePlayNewStuff_uPromptCycle > 2) {
                        _TutorialLivePlayNewStuff_uPromptCycle = done;
                    }
                    switch (_TutorialLivePlayNewStuff_uPromptCycle) {
                    case 0:
                        prompts = 0x20;
                        break;
                    case 1:
                        prompts = 0x10;
                        break;
                    case 2:
                        prompts = 0x80;
                        break;
                    }
                    TutorialShowPrompts(prompts | 1, 1, 1);
                    TutorialBlinkSetShown();
                }
            } else {
                TutorialHidePrompts();
                pStep->mPrompts = 1;
                TutorialShowPrompts(1, 1, 1);
            }
            if (TutorialAreMovesDone(pStep->mMask)) {
                TutorialShowPrompts(pStep->mPrompts, 1, 1);
                TutorialSetStepDone(1);
                TutorialTimerStart(pStep->mDuration);
            }
        } else {
            if (TutorialTimerIsDone()) {
                fn_80178370();
            }
            return;
        }
    } else if (step == 4) {
        LivePlayPhase::OnUpdate(dt);
        unsigned char done = TutorialIsStepDone();
        if (done != 0) {
            return;
        }
        unsigned char button = TutorialBlinkUpdate();
        pStep = TutorialGetLessonObject()->GetStep();
        unsigned int prompts = pStep->mPrompts;
        if (BallStateGet(BallGetCurrent(), 0) != 4) {
            if (button != TutorialBlinkGetShown()) {
                TutorialShowPrompts(pStep->mPrompts, 0, 0);
                if (++_TutorialLivePlayNewStuff_uPromptCycle > 1) {
                    _TutorialLivePlayNewStuff_uPromptCycle = done;
                }
                switch (_TutorialLivePlayNewStuff_uPromptCycle) {
                case 0:
                    prompts = 0x20;
                    break;
                case 1:
                    prompts = 0x80;
                    break;
                }
                TutorialShowPrompts(prompts, 1, 0);
                TutorialBlinkSetShown();
            }
        } else {
            Object_80039F5C *pPlayer = BallGetTarget(BallGetCurrent());
            int on = 0;
            if (pPlayer) {
                if (pPlayer->mUnknown8 == 0xFF) {
                    prompts = 0x20;
                } else {
                    on = 1;
                    prompts = 0x41;
                }
                if (button != TutorialBlinkGetShown()) {
                    TutorialShowPrompts(prompts, button, on);
                    TutorialBlinkSetShown();
                }
            } else {
                TutorialHidePrompts();
            }
        }
        if (TutorialAreMovesDone(pStep->mMask)) {
            TutorialShowPrompts(pStep->mPrompts, 1, 1);
            TutorialSetStepDone(1);
            TutorialTimerStart(pStep->mDuration);
        }
    } else {
        TutorialLivePlay::OnUpdate(dt);
    }
}

void TutorialPostPlayNewStuff::OnEnter(float dt)
{
    if (TutorialGetStep() == 3) {
        TutorialGetLessonObject()->GetStep()->mPrompts = 0xB1;
    } else if (TutorialGetStep() == 8) {
        TutorialStep_t *pStep = TutorialGetLessonObject()->GetStep();
        if (TutorialAreMovesDone(pStep->mMask)) {
            BigObjNotifyTypes(0xC0);
        }
    }
    TutorialPostPlay::OnEnter(dt);
}

void TutorialLessonPassing::Begin()
{
    mpGame.mp = new (0) TutorialObjects;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    fn_80178F20(&mpGame.mp->mObject36);
    TutorialGetStep();
}

int TutorialLessonPassing::End()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

TutorialStep_t *TutorialLessonPassing::GetStep()
{
    return &_Tutorial_aPassingSteps[TutorialGetStep()];
}

const char *TutorialLessonPassing::GetIntroText()
{
    return "Learn how to be the quarterback and lead your team to victory.";
}

const char *TutorialLessonPassing::GetDoneText()
{
    return "Now that you know how to pass the ball, see how you do in a game of 2 Minute Challenge.";
}

void TutorialLessonRunning::Begin()
{
    mpGame.mp = new (0) TutorialObjects;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    fn_80178F20(&mpGame.mp->mObject36);
    TutorialGetStep();
}

int TutorialLessonRunning::End()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

TutorialStep_t *TutorialLessonRunning::GetStep()
{
    return &_Tutorial_aRunningSteps[TutorialGetStep()];
}

const char *TutorialLessonRunning::GetIntroText()
{
    return "It's time to learn how to run with the rock.";
}

const char *TutorialLessonRunning::GetDoneText()
{
    return "Now that you have some running skills, try a 5 round game of Open Field Showdown.";
}

void TutorialLivePlayStyling::OnUpdate(float dt)
{
    static unsigned int _TutorialLivePlayStyling_uPromptCycle = 0;
    TutorialStep_t *pStep;

    if (TutorialGetStep() == 6) {
        LivePlayPhase::OnUpdate(dt);
        unsigned char done = TutorialIsStepDone();
        if (done != 0) {
            return;
        }
        unsigned char button = TutorialBlinkUpdate();
        pStep = TutorialGetLessonObject()->GetStep();
        unsigned int prompts = pStep->mPrompts;
        if (BallStateGet(BallGetCurrent(), 0) != 4) {
            if (button != TutorialBlinkGetShown()) {
                TutorialShowPrompts(pStep->mPrompts, 0, 1);
                if (++_TutorialLivePlayStyling_uPromptCycle > 2) {
                    _TutorialLivePlayStyling_uPromptCycle = done;
                }
                switch (_TutorialLivePlayStyling_uPromptCycle) {
                case 0:
                    prompts = 0x20;
                    break;
                case 1:
                    prompts = 0x10;
                    break;
                case 2:
                    prompts = 0x80;
                    break;
                }
                TutorialShowPrompts(prompts | 1, 1, 1);
                TutorialBlinkSetShown();
            }
        } else {
            TutorialHidePrompts();
            TutorialShowPrompts(pStep->mPrompts, 1, 1);
        }
        if (TutorialAreMovesDone(pStep->mMask)) {
            TutorialShowPrompts(pStep->mPrompts, 1, 1);
            TutorialSetStepDone(1);
            TutorialTimerStart(pStep->mDuration);
        }
    } else if (TutorialGetStep() == 7) {
        LivePlayPhase::OnUpdate(dt);
        unsigned char done = TutorialIsStepDone();
        if (done == 0) {
            unsigned char button = TutorialBlinkUpdate();
            pStep = TutorialGetLessonObject()->GetStep();
            unsigned int prompts = pStep->mPrompts;
            if (BallStateGet(BallGetCurrent(), 0) != 4) {
                if (button != TutorialBlinkGetShown()) {
                    TutorialShowPrompts(pStep->mPrompts, 0, 0);
                    if (++_TutorialLivePlayStyling_uPromptCycle > 2) {
                        _TutorialLivePlayStyling_uPromptCycle = done;
                    }
                    switch (_TutorialLivePlayStyling_uPromptCycle) {
                    case 0:
                        prompts = 0x20;
                        break;
                    case 1:
                        prompts = 0x10;
                        break;
                    case 2:
                        prompts = 0x80;
                        break;
                    }
                    TutorialShowPrompts(prompts, 1, 0);
                    TutorialBlinkSetShown();
                }
            } else {
                Object_80039F5C *pPlayer = BallGetTarget(BallGetCurrent());
                int on = 0;
                if (pPlayer) {
                    if (pPlayer->mUnknown8 == 0xFF) {
                        prompts = 0x20;
                    } else {
                        on = 1;
                        prompts = 0x41;
                    }
                    if (button != TutorialBlinkGetShown()) {
                        TutorialShowPrompts(prompts, button, on);
                        TutorialBlinkSetShown();
                    }
                } else {
                    TutorialHidePrompts();
                }
            }
            if (TutorialAreMovesDone(pStep->mMask)) {
                TutorialShowPrompts(pStep->mPrompts, 1, 1);
                TutorialSetStepDone(1);
                TutorialTimerStart(pStep->mDuration);
            }
        } else {
            if (TutorialTimerIsDone()) {
                fn_80178370();
            }
            return;
        }
    } else {
        TutorialLivePlay::OnUpdate(dt);
    }
}

void TutorialLessonStyling::Begin()
{
    mpGame.mp = new (0) TutorialStylingObjects;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    fn_80178F20(&mpGame.mp->mObject36);
    TutorialGetStep();
}

int TutorialLessonStyling::End()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

TutorialStep_t *TutorialLessonStyling::GetStep()
{
    return &_Tutorial_aStylingSteps[TutorialGetStep()];
}

const char *TutorialLessonStyling::GetIntroText()
{
    return "You are going to need to learn to show your Style and earn GameBreakers in order to be great.";
}

const char *TutorialLessonStyling::GetDoneText()
{
    return "Showcase your Style in a game of Crush the Carrier. To get the big points, stop Styling before you get tackled.";
}

extern "C" {

void TutorialShowTitles(int show)
{
    if (show) {
        if (TutorialGetLesson() == 0) {
            fn_801C2EF0(_Tutorial_szCategoryTitle, "Running the Ball", 25);
            switch (TutorialGetStep()) {
            case 0:
                fn_801C2EF0(_Tutorial_szStepTitle, "Turbo", 30);
                break;
            case 1:
                fn_801C2EF0(_Tutorial_szStepTitle, "Stiff Arm", 30);
                break;
            case 2:
                fn_801C2EF0(_Tutorial_szStepTitle, "Juke", 30);
                break;
            case 3:
                fn_801C2EF0(_Tutorial_szStepTitle, "Spin", 30);
                break;
            case 4:
                fn_801C2EF0(_Tutorial_szStepTitle, "Hurdle", 30);
                break;
            case 5:
                fn_801C2EF0(_Tutorial_szStepTitle, "Dive", 30);
                break;
            case 6:
                fn_801C2EF0(_Tutorial_szStepTitle, "Pitch", 30);
                break;
            }
        } else if (TutorialGetLesson() == 1) {
            fn_801C2EF0(_Tutorial_szCategoryTitle, "Passing", 25);
            switch (TutorialGetStep()) {
            case 0:
                fn_801C2EF0(_Tutorial_szStepTitle, "Turbo Roll Out", 30);
                break;
            case 1:
                fn_801C2EF0(_Tutorial_szStepTitle, "Touch Pass to B Button", 30);
                break;
            case 2:
                fn_801C2EF0(_Tutorial_szStepTitle, "Touch Pass to X Button", 30);
                break;
            case 3:
                fn_801C2EF0(_Tutorial_szStepTitle, "Touch Pass to A Button", 30);
                break;
            case 4:
                fn_801C2EF0(_Tutorial_szStepTitle, "Bullet Pass to B Button", 30);
                break;
            case 5:
                fn_801C2EF0(_Tutorial_szStepTitle, "Bullet Pass to X Button", 30);
                break;
            case 6:
                fn_801C2EF0(_Tutorial_szStepTitle, "Bullet Pass to A Button", 30);
                break;
            case 7:
                fn_801C2EF0(_Tutorial_szStepTitle, "Pump Fake", 30);
                break;
            case 8:
                fn_801C2EF0(_Tutorial_szStepTitle, "Drop Passing Icons", 30);
                break;
            }
        } else if (TutorialGetLesson() == 2) {
            fn_801C2EF0(_Tutorial_szCategoryTitle, "Styling", 25);
            switch (TutorialGetStep()) {
            case 0:
                fn_801C2EF0(_Tutorial_szStepTitle, "Styling", 30);
                break;
            case 1:
                fn_801C2EF0(_Tutorial_szStepTitle, "Signature Style", 30);
                break;
            case 2:
                fn_801C2EF0(_Tutorial_szStepTitle, "Juke", 30);
                break;
            case 3:
                fn_801C2EF0(_Tutorial_szStepTitle, "Spin", 30);
                break;
            case 4:
                fn_801C2EF0(_Tutorial_szStepTitle, "Hurdle", 30);
                break;
            case 5:
                fn_801C2EF0(_Tutorial_szStepTitle, "Dive", 30);
                break;
            case 6:
                fn_801C2EF0(_Tutorial_szStepTitle, "Pass", 30);
                break;
            case 7:
                fn_801C2EF0(_Tutorial_szStepTitle, "Catch", 30);
                break;
            }
        } else if (TutorialGetLesson() == 3) {
            fn_801C2EF0(_Tutorial_szCategoryTitle, "Defense", 25);
            switch (TutorialGetStep()) {
            case 0:
                fn_801C2EF0(_Tutorial_szStepTitle, "Turbo", 30);
                break;
            case 1:
                fn_801C2EF0(_Tutorial_szStepTitle, "Switch Players", 30);
                break;
            case 2:
                fn_801C2EF0(_Tutorial_szStepTitle, "Line Moves", 30);
                break;
            case 3:
                fn_801C2EF0(_Tutorial_szStepTitle, "Dive Tackle", 30);
                break;
            case 4:
                fn_801C2EF0(_Tutorial_szStepTitle, "Interception", 30);
                break;
            case 5:
                fn_801C2EF0(_Tutorial_szStepTitle, "Power Tackle", 30);
                break;
            }
        } else if (TutorialGetLesson() == 4) {
            fn_801C2EF0(_Tutorial_szCategoryTitle, "New Stuff", 25);
            switch (TutorialGetStep()) {
            case 0:
                fn_801C2EF0(_Tutorial_szStepTitle, "Wall Juke", 30);
                break;
            case 1:
                fn_801C2EF0(_Tutorial_szStepTitle, "Wall Hurdle", 30);
                break;
            case 2:
                fn_801C2EF0(_Tutorial_szStepTitle, "Wall Dive", 30);
                break;
            case 3:
                fn_801C2EF0(_Tutorial_szStepTitle, "Wall Pass", 30);
                break;
            case 4:
                fn_801C2EF0(_Tutorial_szStepTitle, "Wall Catch", 30);
                break;
            case 5:
                fn_801C2EF0(_Tutorial_szStepTitle, "GameBreaker on Offense", 30);
                break;
            case 6:
                fn_801C2EF0(_Tutorial_szStepTitle, "GameBreaker on Defense", 30);
                break;
            case 7:
                fn_801C2EF0(_Tutorial_szStepTitle, "GameBreaker 2", 30);
                break;
            case 8:
                fn_801C2EF0(_Tutorial_szStepTitle, "Hot Spots", 30);
                break;
            }
        }
        _Tutorial_CategoryText.mUnknown0 = 0;
        _Tutorial_CategoryText.mpText = _Tutorial_szCategoryTitle;
        _Tutorial_CategoryText.mSize = fn_801C3180(_Tutorial_szCategoryTitle) + 1;
        _Tutorial_pCategoryText = &_Tutorial_CategoryText;
        _Tutorial_StepText.mUnknown0 = 0;
        _Tutorial_StepText.mpText = _Tutorial_szStepTitle;
        _Tutorial_StepText.mSize = fn_801C3180(_Tutorial_szStepTitle) + 1;
        _Tutorial_pStepText = &_Tutorial_StepText;
        fn_8021D7B8(gUISMainInfo, 0x80000080, 1, &_Tutorial_pCategoryText);
        fn_8021D7B8(gUISMainInfo, 0x80000081, 1, &_Tutorial_pStepText);
    }
    _Tutorial_iTitlesShown = show;
    fn_8021D7B8(gUISMainInfo, 0x8000007F, 1, &_Tutorial_iTitlesShown);
}

void TutorialReloadRatings(void)
{
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned short i = 0; i <= 6; i++) {
            fn_80149040(PlyrGet(team, i));
        }
    }
}

void TutorialSetupSession(void)
{
    unsigned char volume;

    if (SndgMusicIsPaused()) {
        SndgMusicResume();
    }
    SndgSetVolumeOption(3, 100);
    SndgCrowdSetVolume(0);
    volume = GameOptionsGet(5) * 10;
    SndgSetVolumeOption(2, volume * 40u / 100);
    for (unsigned char team = 0; team <= 1; team++) {
        QueryCursor cursor;
        int a;
        int b;
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(0, "declare \x8a cursor for select * from 'YALP' where ('DIGT' = \x83) order by 'DIGP'\n", &cursor, team);
        for (unsigned short i = 0; i <= 6; i++) {
            fn_801FCE10(0, "fetch from \x8a 'DIGP' into \x82 and 'DIOP' into \x82\n", &cursor, &a, &b);
        }
        if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    }
}

void TutorialBlinkPrompts(unsigned int mask)
{
    unsigned char state = TutorialBlinkUpdate();
    if (state != TutorialBlinkGetShown()) {
        TutorialShowPrompts(mask, state, 1);
        TutorialBlinkSetShown();
    }
}

}

void TutorialPostPlay::ShowResults()
{
    PauseBlock();
    TutorialStep_t *pRecord = TutorialGetLessonObject()->GetStep();
    MsgGameSetMemCardActive(1);
    if (TutorialAreMovesDone(pRecord->mMask)) {
        TutorialShowPrompts(pRecord->mPrompts, 1, 1);
        TutorialSetStepDone(1);
    }
    if (TutorialIsStepDone()) {
        if (TutorialCompleteStep(TutorialGetLesson()) == 0) {
            MsgBoxShow("Tutorial Results", _Tutorial_szPassed, "|^Done");
            mUnknown12 = 0;
        } else {
            char text[256];
            const char *pName;
            mUnknown4 = 1;
            mUnknown12 = 0;
            pName = TutorialGetLessonObject()->GetDoneText();
            if (pName == 0) pName = "";
            fn_801C2D88(text, 255, "%s\n\n%s", _Tutorial_szCategoryDone, pName);
            MsgBoxShow("Tutorial Results", text, "|^Done");
        }
        mUnknown8 = 0;
        TutorialSetAnnounceStep(1);
    } else {
        mUnknown12 = 1;
        if (mUnknown8 > 2) {
            MsgBoxShow("Tutorial Results", _Tutorial_szNeedPractice, "|^Retry|Quit|Skip to Next Section");
        } else {
            MsgBoxShow("Tutorial Results", _Tutorial_szNeedPractice, "|^Retry|Quit");
        }
    }
}

static unsigned char _Tutorial_bAwaitCamera = 0;
static unsigned char _Tutorial_bKeyPromptShown = 0;

void TutorialPreGame::OnEnter()
{
    PreGamePhase::OnEnter();
    StyleTrackerSetEnabled(1);
    mUnknown4 = 1;
    TutorialSetupSession();
    PauseBlock();
}

void TutorialPreGame::OnUpdate(float dt)
{
    unsigned short id;
    unsigned short other;
    int busy;

    fn_80219650(gUISMainInfo, &id, &other);
    busy = 0;
    if (id == 1) {
        busy = other == 2;
    }
    if (!busy && MsgBoxIsClosed()) {
        int choice = MsgGameTakePendingChoice();

        if (choice == 2) {
            if (mUnknown4 == 2) {
                RumbleEnable(1);
                SndgMusicFadeOut(0xFA, 0);
                InGameStop();
            } else {
                mUnknown4 = choice;
                MsgBoxShow("Tutorial Results", _Tutorial_szQuitConfirm, "|^No|Yes");
            }
        } else {
            PreGamePhase::OnUpdate(dt);
        }
    }
}

void TutorialPreGame::EnterFirstPhase(float dt)
{
    fn_800AD910(2, dt);
}

void TutorialPreGame::ShowIntroScreen()
{
    char text[256];

    if (TutorialGetStep() == 0) {
        const char *pInfo = TutorialGetLessonObject()->GetIntroText();

        if (pInfo != 0) {
            TutorialSetHudVisible(0);
            if (TutorialIsContinuing()) {
                fn_801C2E18(text, "%s\n\nDo you want to continue?", pInfo);
                MsgBoxShow("Tutorial Information", text, "|^Continue|Quit");
            } else {
                MsgBoxShow("Tutorial Information", pInfo, "|^Done");
            }
        }
    } else {
        TutorialSetHudVisible(0);
        MsgBoxShow("Tutorial Information", "Back for more?", "|^Done");
    }
}

void TutorialPreGame::HideIntroScreen()
{
    TutorialSetHudVisible(1);
}

void TutorialPreSnap::OnEnter(float dt)
{
    FieldSpot_t start;
    FieldSpot_t point;
    Vector_80039F5C pos;
    int angles[3];
    int args[2];
    Ball_t *pBall;

    TutorialClearMoves();
    TutorialSetupPlays();
    TutorialReloadRatings();
    fn_8009D8CC(1);
    mUnknown4 = 0;
    TutorialTimerStart(3);
    _Tutorial_bAwaitCamera = 1;
    start.mX = 0.0f;
    start.mY = TutorialGetStartLine();
    if (TutorialGetAnnounceStep()) {
        AudmonEventPostArgs(0x85, 0, TutorialGetLesson(), TutorialGetStep(), 0);
        SndgMusicPumpFrame(1);
    }
    fn_801780A8(start);
    fn_801782B0();
    pBall = BallGetCurrent();
    BallReleaseStill(pBall, 6, 0);
    point = fn_80177FE0();
    pos.mX = point.mX;
    pos.mY = point.mY;
    pos.mZ = 0.3f;
    BallSetPosition(pBall, &pos);
    angles[0] = 0;
    angles[1] = 0xFFC00000;
    angles[2] = 0xFFC00000;
    fn_8013A910(pBall, angles);
    fn_8013AD9C(pBall, 0);
    BallPrimeKickUp(pBall);
    PreSnapPhase::OnEnter(dt);
    fn_8009E01C();
    fn_800BF658(1);
    StyleTrackerSetMeterFraction(1, 0.0f, 0);
    StyleTrackerSetMeterFraction(0, 0.0f, 0);
    HudSetGameBreakerMeter(1, 0.0f, 0, 0);
    HudSetGameBreakerMeter(0, 0.0f, 0, 0);
    args[0] = 1;
    args[1] = 0;
    fn_8021D7B8(gUISMainInfo, 0x8000001A, 2, args);
    args[0] = 0;
    fn_8021D7B8(gUISMainInfo, 0x8000001A, 2, args);
    TutorialShowPrompts(TutorialGetLessonObject()->GetStep()->mPrompts, 1, 0);
    PauseRequestCancel();
    if (!PauseIsUnblocked()) {
        PauseUnblock();
    }
    TutorialShowTitles(1);
}

void TutorialPreSnap::OnExit(float dt)
{
    TutorialShowTitles(0);
    PreSnapPhase::OnExit(dt);
}

void TutorialPreSnap::OnUpdate(float dt)
{
    if (TutorialTimerIsDone()) {
        GameCamera_t *pCamera = CamGameGetCamera(5);
        TutorialStep_t *pEntry = TutorialGetLessonObject()->GetStep();

        if (pCamera->mUnknownA0 == 5 && _Tutorial_bAwaitCamera != 0) {
            fn_800BF6CC(1);
            if (pEntry->mUnknown24 != 1) {
                TutorialHidePrompts();
            } else {
                TutorialBlinkInit(pEntry->mUnknown20, 60);
                TutorialBlinkRestart();
            }
            _Tutorial_bAwaitCamera = 0;
        }
        if (_Tutorial_bAwaitCamera == 0 && pEntry->mUnknown24 == 1) {
            if (TutorialAreMovesDone(0x400000000ULL)) {
                TutorialHidePrompts();
            } else {
                TutorialBlinkPrompts(pEntry->mPrompts);
            }
        }
        if (mUnknown4 == 0 && SpchIGIsNarratorIdle()) {
            fn_8009D888(0, 5);
            fn_8009D944(0);
            mUnknown4 = 1;
        }
        PreSnapPhase::OnUpdate(dt);
    }
}

int TutorialPreSnap::CanSnap()
{
    int result = 0;

    if (mUnknown4 != 0 && (unsigned int)fn_8009D990(0) <= 2) {
        result = PreSnapPhase::CanSnap();
    }
    return result;
}

void TutorialLivePlay::OnEnter()
{
    TutorialStep_t *pEntry;

    LivePlayPhase::OnEnter();
    TutorialSetStepDone(0);
    CamMainWarpToDest(CamGameGetCamera(5));
    pEntry = TutorialGetLessonObject()->GetStep();
    if (pEntry->mUnknown24 != 1) {
        TutorialBlinkInit(pEntry->mUnknown20, 60);
        TutorialBlinkRestart();
    } else {
        TutorialHidePrompts();
    }
}

void TutorialLivePlay::OnUpdate(float dt)
{
    LivePlayPhase::OnUpdate(dt);
    if (TutorialIsStepDone() == 0) {
        TutorialStep_t *pEntry = TutorialGetLessonObject()->GetStep();

        if (pEntry->mUnknown24 != 1) {
            TutorialBlinkPrompts(pEntry->mPrompts);
        }
        if (TutorialAreMovesDone(pEntry->mMask)) {
            TutorialShowPrompts(pEntry->mPrompts, 1, 1);
            TutorialSetStepDone(1);
            TutorialTimerStart(pEntry->mDuration);
        }
    } else if (TutorialTimerIsDone()) {
        fn_80178370();
    }
}

void TutorialPostPlay::OnEnter(float dt)
{
    TutorialStep_t *pEntry = TutorialGetLessonObject()->GetStep();

    mUnknown5 = 0;
    mUnknown6 = pEntry->mUnknown12 * 60.0f;
    mUnknown4 = 0;
    mUnknown12 = 0;
    PostPlayPhase::OnEnter(dt);
    TutorialHidePrompts();
}

void TutorialPostPlay::OnUpdate(float dt)
{
    unsigned short id;
    unsigned short other;

    if (mUnknown5 == 0) {
        if (mUnknown6 > 0) {
            if (mUnknown6 == 2) {
                if (TutorialIsStepDone()) {
                    AudmonEventPostArgs(0x86, 0, 0, 0, 0);
                } else {
                    AudmonEventPostArgs(0x87, 0, 0, 0, 0);
                }
                mUnknown6--;
            } else if (mUnknown6 == 1) {
                if (SpchIGIsNarratorIdle() || !TutorialIsStepDone()) {
                    mUnknown6--;
                    _Tutorial_bKeyPromptShown = 0;
                }
            } else {
                mUnknown6--;
            }
        } else {
            RumbleEnable(0);
            RumbleStopAll();
            fn_8006F824(1);
            ShowResults();
            mUnknown5 = 1;
        }
    } else {
        int key = fn_800B81A4();

        if (key != 0xFF || _Tutorial_bKeyPromptShown != 0) {
            if (_Tutorial_bKeyPromptShown == 0) {
                int args[2];

                args[0] = key;
                args[1] = 1;
                _Tutorial_bKeyPromptShown = 1;
                fn_80218FC4(gUISMainInfo, 1, 2, 2, args);
                fn_802195E4(gUISMainInfo, 1, 2);
            } else {
                int busy = 0;

                fn_80219650(gUISMainInfo, &id, &other);
                if (id == 1) {
                    busy = other == 2;
                }
                if (!busy) {
                    fn_802195E4(gUISMainInfo, 1, 3);
                    _Tutorial_bKeyPromptShown = 0;
                }
            }
        } else if (MsgBoxIsClosed()) {
            if (mUnknown12 != 0) {
                switch (MsgGameTakePendingChoice()) {
                case 1:
                    mUnknown8++;
                    TutorialSetAnnounceStep(0);
                    mUnknown12 = 0;
                    RumbleEnable(1);
                    ForceFinish();
                    break;
                case 2:
                    if (mUnknown12 == 1) {
                        mUnknown12 = 2;
                        MsgBoxShow("Tutorial Results", _Tutorial_szQuitConfirm, "|^No|Yes");
                    } else {
                        RumbleEnable(1);
                        SndgMusicFadeOut(0xFA, 0);
                        PlyrNameTagEnable(0);
                        fn_8004730C(0);
                        InGameStop();
                        mUnknown12 = 0;
                    }
                    break;
                case 3:
                    AudmonEventPostArgs(0x88, 0, 0, 0, 0);
                    mUnknown8 = 0;
                    TutorialSetAnnounceStep(1);
                    if (!TutorialCompleteStep(TutorialGetLesson())) {
                        mUnknown12 = 0;
                    } else {
                        char text[256];
                        const char *pInfo;

                        mUnknown12 = 0;
                        mUnknown4 = 1;
                        pInfo = TutorialGetLessonObject()->GetDoneText();
                        if (pInfo == 0) {
                            pInfo = "";
                        }
                        fn_801C2D88(text, 0xFF, "%s\n\n%s", _Tutorial_szCategoryDone, pInfo);
                        MsgBoxShow("Tutorial Results", text, "|^Done");
                    }
                    break;
                }
                StyleTrackerEndPlay();
            }
            PostPlayPhase::OnUpdate(dt);
        }
    }
}

void TutorialPostPlay::OnSequenceStart()
{
}

void TutorialPostPlay::OnExit()
{
    Ball_t *pBall;
    FieldSpot_t point;
    Vector_80039F5C pos;
    int angles[3];

    PostPlayPhase::OnExit();
    fn_8011DF90();
    if (BallGetCurrentHolder()) {
        BallReleaseStill(BallGetCurrent(), 5, 0);
    }
    if (fn_801784E8()) {
        fn_80177E6C(1, 1);
    }
    pBall = BallGetCurrent();
    BallReleaseStill(pBall, 6, 0);
    point = fn_80177FE0();
    pos.mX = point.mX;
    pos.mY = point.mY;
    pos.mZ = 0.3f;
    BallSetPosition(pBall, &pos);
    angles[0] = 0;
    angles[1] = 0xFFC00000;
    angles[2] = 0xFFC00000;
    fn_8013A910(pBall, angles);
    fn_8013AD9C(pBall, 0);
    BallPrimeKickUp(pBall);
    CamGameSetModeAll(1);
    CamGameSelectCamera(0);
    CamGameSetFocusAll(1, BallGetCurrentIndex());
}

void TutorialPostPlay::ShowResultText()
{
}

void TutorialPostPlay::UpdateCue(float dt)
{
}

int TutorialPostPlay::IsHeld(float dt)
{
    fn_800AE988();
    return 0;
}

int TutorialPostPlay::GetBusy(float dt)
{
    fn_8009B924();
    return 0;
}

void TutorialPostPlay::Finish(float dt)
{
    PlyrMgrClearStates();
    if (fn_8005BFD4() != 4) {
        fn_8005BF18();
    }
    if (mUnknown4 != 0) {
        if (!TutorialFinishCategory()) {
            SndgMusicFadeOut(0xFA, 0);
            InGameStop();
        }
    } else {
        fn_800AD910(2, dt);
    }
}

void TutorialRuleSet::ResetGame(int a)
{
    ScrmRuleSet::ResetGame(a);
}

int TutorialRuleSet::UsesBothTeams()
{
    return 1;
}

void TutorialRuleSet::ResetPlaySpot()
{
    fn_80177F88(1);
    ScrmRuleSet::ResetPlaySpot();
    if (fn_80177F70() == 6) {
        fn_801787FC(1, 0);
        fn_801787FC(0, 0);
        fn_800C87CC(1, 0);
        fn_800C87CC(0, 0);
        fn_80177F88(1);
        HudSetScore(1, 0);
        HudSetScore(0, 0);
    }
    fn_80178CD8(0);
}

int TutorialRuleSet::GetWinner()
{
    return 2;
}

int TutorialRuleSet::IsTimed()
{
    return 0;
}
