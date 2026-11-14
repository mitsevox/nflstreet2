#include "game/cu_8002B8F8.h"
#include "game/StyleTracker.h"
#include "game/Ball.h"
#include "game/GameModeType.h"
#include "game/fn_800AD9B4.h"

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

extern "C" {
void fn_800BA7E8(float x, float y);
GameCamera_t *CamGameGetCamera(int index);
void fn_80178370(void);
int fn_801784C4(void);
float fn_80178A2C(void);
float fn_80178A5C(void);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void GameSetupInit(void);
void fn_8002D274(Type_803EA368 *p);
void PlyrMgrResetAll(void);
void BigObjNotifyTypes(unsigned int flags);
void fn_800588E0(void);
void fn_80071C34(int value);
void SndgMusicExitMode(int pauseAfter);
void SpchIGEndSceneLine(void);
unsigned char SpchIGIsSceneLineActive(void);
void SpchIGResumeChannel(int index);
void fn_8009D8CC(int index);
void fn_800A7A0C(int team);
void fn_800A7E68(void);
int fn_800A8740(void);
void fn_800AD910(int mode, float dt);
void fn_800B4184(int a);
void fn_800B63B0(void);
void fn_8013F3FC(void);
void PassIconsHide(void);
void PassIconsClearReplayFlag(void);
void PlayTrackReset(void);
void ClockRuleClearFlags(unsigned int mask);
void ClockRuleResetFlags(void);
void DriveLogInit(void);
void DriveLogEndDrive(void);
void ScoringLogInit(void);
void ScoringLogReset(void);
void fn_80177B7C(int a);
void fn_8017833C(int value);
void fn_80178354(int value);
int fn_80178AE0(void);
void HudReset(void);
int fn_8022BF68(void);
int fn_8022DD4C(int value);
int fn_8022DD80(int value);
void fn_8009D818(int state);
void fn_80162780(int a, int b);


extern unsigned char lbl_803EABB8;
extern unsigned char lbl_803EABB9;
}

extern "C" void fn_800C1CA0(void)
{
    unsigned char team;

    lbl_803EABB9 = 1;
    team = fn_80178AE0();
    lbl_803EABB8 = 1;
    ClockRuleResetFlags();
    DriveLogInit();
    ScoringLogInit();
    DriveLogEndDrive();
    ScoringLogReset();
    BigObjNotifyTypes(0x100);
    fn_8022DD4C(0);
    fn_8022DD80(0);
    if (GameModeTypeGet() == 6) {
        GameSetupInit();
    } else {
        fn_80177B7C(team);
    }
    fn_8002D274(lbl_803EA368);
    PlayTrackReset();
    fn_8022BF68();
    StyleTrackerEndPlay();
    StyleTrackerReset();
    fn_80071C34(0);
    if (SpchIGIsSceneLineActive()) {
        SpchIGEndSceneLine();
    }
    SpchIGResumeChannel(0);
    SpchIGResumeChannel(1);
    SpchIGResumeChannel(2);
    fn_80162780(0, 0);
    fn_8013F3FC();
    if (fn_800A8740() == 0) {
        fn_800A7A0C(0);
        fn_800A7A0C(1);
    }
    fn_800A7E68();
    if (fn_800AD9B4() == 7 || fn_800AD9B4() == 0) {
        fn_8009D818(0);
    } else {
        fn_800B4184(1);
        fn_800588E0();
        PlyrMgrResetAll();
        fn_800B63B0();
        fn_8009D818(0);
        fn_800AD910(1, 0.0f);
    }
    if (GameModeTypeGet() == 8) {
        fn_8017833C(1);
        fn_80178354(1);
    }
    ClockRuleClearFlags(0x800);
    fn_8009D8CC(1);
    fn_8009D8CC(5);
    fn_8009D8CC(0);
    HudReset();
    PassIconsHide();
    PassIconsClearReplayFlag();
    SndgMusicExitMode(0);
    lbl_803EABB9 = 0;
}

extern "C" void fn_800C1E5C(int a, unsigned int b, float c)
{
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C pos;
    Point_8017886C delta;

    BallGetPosition(pBall, &pos);
    delta.mX = 0.0f;
    delta.mY = 0.0f;
    const float step = 0.16f;
    switch (b) {
    case 0:
    case 7:
        if (c > 0.0f) {
            fn_800BA7E8(pos.mX, pos.mY);
            fn_80178370();
        }
        break;
    case 52:
        delta.mY = c * -step;
        break;
    case 53:
        delta.mX = c * -step;
        break;
    case 16:
    case 54:
        delta.mX = c * step;
        break;
    case 17:
    case 51:
        delta.mY = c * step;
        break;
    }
    if (fn_801784C4()) {
        delta.mX = -delta.mX;
        delta.mY = -delta.mY;
    }
    fn_80227384(&delta, &delta, (0x1000000 - CamGameGetCamera(0)->mHeader.mUnknown14[2]) & 0xFFFFFF);
    pos.mX += delta.mX;
    pos.mY += delta.mY;
    pos.mX = CLAMP(pos.mX, -fn_80178A5C(), fn_80178A5C());
    pos.mY = CLAMP(pos.mY, 0.33f - fn_80178A2C(), fn_80178A2C() - 0.33f);
    BallSetPosition(pBall, &pos);
}
