#include "game/Block_800BFAD0.h"
#include "game/Class_80297CE8.h"
#include "game/fn_800B65A0.h"
#include "game/PadInput.h"
#include "game/AudmonEvent.h"

struct EngineParamWords {
    int mUnknown0;
    int mUnknown4;
};

extern "C" {
void fn_800BE808(int a, unsigned char index);
void fn_800BE944(int index, int a, unsigned int msg, float value);
void fn_8003A3F4(int a, int index);
void fn_800BD774(int index, int kind);
void fn_800BED54(unsigned char index);
void fn_800BEFAC(int index);
void fn_800BD830(void);
int fn_800BF824(void);
int fn_800BF8A8(Class_80297CE8 *p);
void fn_800BF9DC(Class_80297CE8 *p);
void fn_800BE798(Class_80297CE8 *p);
void SpchIGUpdatePreSnap(void);
void HudCycleMashPrompt(void);
int fn_8016EA68(void);
void fn_800B0E18(void);
void fn_8009E01C(void);
void SpchIGPickTeamPlayer(int side);
void SpchIGResetPreSnap(void);
void fn_800ABE00(void);
unsigned char InGameIsDemo(void);
unsigned char GameEventFlagsSetFlag3(unsigned char value);
unsigned char GameEventFlagsSetFlag4(unsigned char value);
unsigned char GameEventFlagsSetFlag5(unsigned char value);
void fn_8015C254(int value);
void PassIconObjSetEnabled(int value);
void ParticlesResetEvents(void);
void fn_8010A220(void);
void fn_8009DE9C(void);
int fn_801486A0(void);
void fn_8016DB94(int team);
void fn_8009DEFC(int flag);
void fn_8011DF90(void);
void fn_8017840C(void);
void fn_800AEEDC(int team);
void fn_8016F6A4(void);
void fn_8011F3A8(void);
void fn_800AFDD4(void (*pCallback)(int, unsigned int, float));
int ConSetChannelInfo(int a, int b, void *p);
void fn_800BF07C(void);
void fn_800BF174(void);
void fn_800BF3F4(int team);
void fn_800BD99C(int team);
int fn_800BA6F8(void);
void fn_8009D888(int index, int value);
void fn_801789F8(void);
void fn_800BF4B8(void);
void BallsSetVisible(int on);
void fn_800C9BB0(void);
int fn_800A8488(int team);
int fn_800A8444(int team);
int ConGetChannelInfo(int a, int b);
int fn_801E195C(int a);
int fn_800B6644(int index);
void RumbleStartPulse(int channel, int onTime, int offTime, int duration, int force);
void HudShowPressPrompt(int team);
void fn_8017885C(void);
void fn_800BD958(void);
void SpchIGEndPreSnap(void);
void BallsResetScales(void);
unsigned char InGameStateSetActive(unsigned char value);
void ChallengeSendGoalList(int flag);
void fn_800A87E8(void);
void fn_80094DF0(void);
int fn_8009D86C(void);
unsigned int fn_8009D990(int index);
unsigned char GameEventFlagsSetFlag0(unsigned char value);
void fn_800AFE20(void (*pCallback)(int, unsigned int, float));
void fn_800BE4C8(int a, unsigned int msg, float value);
void fn_800B0DA4(void);
void fn_800BD568(int index);
void BannerClear(int index);
void fn_800AEF38(int team);
void HudHideEvent3D(int index);
void PassIconsHide(void);
void PassIconsClearReplayFlag(void);
unsigned char fn_801478F0(unsigned char a);
int fn_80178308(void);
int fn_80178320(void);
void fn_800BD2F8(int team);
void fn_802345C4(EngineParamWords *pDesc, int count);

extern float lbl_803EABAC[2];
extern unsigned char lbl_803EABB4;
extern unsigned char lbl_803EABB5;
extern unsigned char lbl_803EABB6;
extern unsigned char lbl_803EABB7;
extern char lbl_802ECD44[];
}

extern "C" void fn_800BF658(int index)
{
    int team = fn_800B65A0(index);

    lbl_803EABA8->mSlots[index].mUnknown1C = 1;
    fn_800BE808(team, index);
    fn_800BE944((unsigned char)index, team, 132, 1.0f);
    fn_8003A3F4(1, index);
}

extern "C" void fn_800BF72C(Class_80297CE8 *p, float dt)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        Slot_800BFAD0 *pSlot = &lbl_803EABA8->mSlots[i];

        switch (pSlot->mUnknown0) {
        case 4:
        case 5:
            fn_800BD774((unsigned char)i, pSlot->mUnknown0);
            break;
        case 8:
            lbl_803EABAC[i] -= dt;
            if (lbl_803EABAC[i] > 0.0f) {
                break;
            }
        case 2:
            pSlot->mUnknown0 = 0;
            break;
        case 6:
            fn_800BED54(i);
            break;
        case 7:
            fn_800BEFAC((unsigned char)i);
            break;
        }
    }
    if (lbl_803EABA8->mUnknownC0 > 0) {
        lbl_803EABA8->mUnknownC0--;
    }
    fn_800BD830();
}


void Class_80297CE8::vfn_04(float dt)
{
    unsigned char i;

    lbl_803EABB4 = 0;
    SpchIGPickTeamPlayer(0);
    SpchIGPickTeamPlayer(1);
    SpchIGResetPreSnap();
    fn_800ABE00();
    vfn_09();
    InGameStateSetActive(1);
    if ((fn_8009D86C() == 2 || fn_8009D86C() > 3) && fn_8009D990(1) <= 120 && fn_8009D990(1) != 0
        && InGameIsDemo() == 0) {
        GameEventFlagsSetFlag3(0);
        GameEventFlagsSetFlag4(0);
        GameEventFlagsSetFlag5(1);
    } else {
        GameEventFlagsSetFlag4(1);
    }
    if (GameEventFlagsSetFlag0(1) == 1) {
        GameEventFlagsSetFlag5(1);
    }
    PassIconsHide();
    fn_8015C254(1);
    PassIconObjSetEnabled(1);
    ParticlesResetEvents();
    fn_8010A220();
    fn_8009DE9C();
    if (fn_801486A0() != 0 && fn_801486A0() != 1) {
        fn_8016DB94(fn_80178308());
        fn_8016DB94(fn_80178320());
    }
    fn_8009DEFC(1);
    if (fn_801486A0() != 0) {
        vfn_11();
    }
    fn_8011DF90();
    fn_8017840C();
    fn_800B0DA4();
    fn_800AEEDC(0);
    fn_800AEEDC(1);
    fn_8016F6A4();
    vfn_10();
    fn_8011F3A8();
    fn_800AFDD4(fn_800BE4C8);
    PadInputSaveHandlers(lbl_803EABA8->mUnknown48);
    ConSetChannelInfo(-1, 3, lbl_802ECD44);
    for (i = 0; i <= 1; i++) {
        Slot_800BFAD0 *pSlot = &lbl_803EABA8->mSlots[i];

        pSlot->mUnknown0 = 0;
        pSlot->mUnknown4 = 0;
        pSlot->mUnknown8 = 0;
        pSlot->mUnknownC = 0.0f;
        pSlot->mUnknown10 = 0.0f;
        pSlot->mUnknown14 = 0;
        pSlot->mUnknown15[0] = 0;
        pSlot->mUnknown15[1] = 0;
        pSlot->mUnknown15[2] = 0;
        pSlot->mUnknown18 = 0;
        pSlot->mUnknown19 = 0;
        pSlot->mUnknown1C = 0;
    }
    lbl_803EABA8->mUnknownC7 = 0;
    lbl_803EABA8->mUnknown98 = 0;
    lbl_803EABA8->mUnknownC4 = 0;
    lbl_803EABA8->mUnknownC5 = 0;
    lbl_803EABA8->mUnknownC6 = 1;
    fn_800BF07C();
    lbl_803EABA8->mUnknownA0 = 120;
    lbl_803EABA8->mUnknown44 = -1;
    lbl_803EABA8->mUnknownA8 = 0;
    lbl_803EABA8->mUnknownB0 = 2;
    lbl_803EABA8->mUnknownB4 = 0;
    lbl_803EABA8->mUnknownB8 = 0;
    lbl_803EABA8->mUnknownA9 = 0;
    lbl_803EABA8->mUnknownAA = 0;
    fn_800BF174();
    fn_8003A3F4(0, 0);
    fn_8003A3F4(0, 1);
    PassIconsClearReplayFlag();
    fn_800BF3F4(fn_80178308());
    fn_800BF3F4(fn_80178320());
    fn_800BD99C(fn_80178308());
    fn_800BD99C(fn_80178320());
    switch (fn_801486A0()) {
    case 0:
    case 1:
        break;
    default:
        fn_800BD958();
        break;
    }
    if (fn_800BA6F8() != 0) {
        fn_8009D888(0, 10);
    }
    fn_801789F8();
    fn_800BF4B8();
    BallsSetVisible(1);
    EngineParamWords desc = { 0, 14 };
    fn_802345C4(&desc, 2);
    AudmonEventPost(115, 0);
    fn_800C9BB0();
    for (i = 0; i <= 1; i++) {
        if (fn_800A8488(i) && !fn_800A8444(i)) {
            unsigned int j;

            for (j = 0; j <= 9; j++) {
                if (fn_801E195C(ConGetChannelInfo(j, 0)) == 2 && fn_800B6644(j) == i) {
                    RumbleStartPulse(j, lbl_803EABB5, lbl_803EABB6, lbl_803EABB7, 1);
                }
            }
            HudShowPressPrompt(i);
        }
    }
    ChallengeSendGoalList(1);
    lbl_803EABA8->mUnknownAC = 0;
    lbl_803EABA8->mUnknownAB = 0;
    fn_8017885C();
    if (fn_801486A0() == 1) {
        for (i = 0; i <= 1; i++) {
            unsigned short k;

            for (k = 0; k <= 6; k++) {
                if (fn_80039F5C(i, k)->mUnknown8 != 0xFF) {
                    fn_80039F5C(i, k)->mMotion.mFacing = 0xC00000;
                }
            }
        }
    }
}

void Class_80297CE8::vfn_05(float dt)
{
    if (fn_800BF824() != 0) {
        return;
    }
    SpchIGUpdatePreSnap();
    HudCycleMashPrompt();
    if (fn_800BF8A8(this) == 0 && lbl_803EABA8->mUnknownB8 == -1) {
        fn_800BF9DC(this);
        if (lbl_803EABA8->mUnknownC5 == 0) {
            lbl_803EABA8->mUnknownC5 = fn_8016EA68() != 0 && lbl_803EABA8->mUnknownC6 != 0;
            if (lbl_803EABA8->mUnknownC5 != 0) {
                AudmonEventPost(117, 0);
            }
        }
        fn_800B0E18();
        fn_8009E01C();
        fn_800BE798(this);
        fn_800BF72C(this, dt);
    }
    if (fn_8016EA68() != 0) {
        EngineParamWords desc = { 0, 14 };
        fn_802345C4(&desc, 2);
    }
    if (lbl_803EABA8->mUnknownB8 != -1) {
        lbl_803EABA8->mUnknownB8++;
    }
    if (lbl_803EABA8->mUnknownB4 != -1) {
        lbl_803EABA8->mUnknownB4++;
    }
    if (lbl_803EABA8->mUnknownA9 > 0 && --lbl_803EABA8->mUnknownA9 == 0) {
        fn_800BD2F8(fn_80178308());
    }
    if (lbl_803EABA8->mUnknownAA > 0 && --lbl_803EABA8->mUnknownAA == 0) {
        fn_800BD2F8(fn_80178320());
    }
}

void Class_80297CE8::vfn_06(float dt)
{
    SpchIGEndPreSnap();
    lbl_803EABA8->mUnknown40 = 0;
    BallsResetScales();
    InGameStateSetActive(0);
    ChallengeSendGoalList(0);
    fn_800A87E8();
    fn_80094DF0();
    if ((fn_8009D86C() != 2 && fn_8009D86C() <= 3) || fn_8009D990(1) > 120 || fn_8009D990(1) == 0) {
        GameEventFlagsSetFlag0(0);
    }
    fn_800AFE20(fn_800BE4C8);
    PadInputRestoreHandlers(lbl_803EABA8->mUnknown48);
    PadInputResetSlot(-1);
    fn_800B0DA4();
    fn_800BD568(0);
    fn_800BD568(1);
    fn_8003A3F4(0, 0);
    fn_8003A3F4(0, 1);
    BannerClear(1);
    BannerClear(2);
    fn_800AEF38(0);
    fn_800AEF38(1);
    HudHideEvent3D(0);
    HudHideEvent3D(1);
    PassIconsHide();
    PassIconsClearReplayFlag();
    fn_801478F0(1);
    fn_800BD2F8(fn_80178308());
    fn_800BD2F8(fn_80178320());
    lbl_803EABA8->mUnknownC5 = 0;
    EngineParamWords desc = { 0, 14 };
    fn_802345C4(&desc, 2);
}
