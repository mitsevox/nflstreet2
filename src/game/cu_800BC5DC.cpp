#include "game/PreGamePhase.h"
#include "game/StyleTracker.h"
#include "game/Challenge.h"
#include "game/Ball.h"

struct Slot_800BAE7C {
    int mUnknown0;
    /* Written as a word by fn_800BC190, read by its low byte. */
    union {
        int mTeamWord;
        struct {
            unsigned char mUnknown4[3];
            unsigned char mTeam;
        };
    };
    Object_80039F5C *mpObject;
};

struct Record_800BAE7C {
    int mUnknown0;
    Slot_800BAE7C mSlots[4];
    unsigned char mUnknown34[12];
    int mUnknown40;
    int mUnknown44;
    float mUnknown48;
    unsigned char mUnknown4C;
    unsigned char mUnknown4D[3];
};

struct Block_800BC538 {
    int mUnknown0;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    Record_800BAE7C *mpUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    int mUnknown24;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    signed char mUnknown2A;
    unsigned char mUnknown2B;
    int mUnknown2C;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    unsigned char mUnknown32;
    unsigned char mUnknown33;
};

extern "C" {
int ChallengeIsActive(void);
void fn_8003E174(int a);
void PlayerObjSetDrawReady(unsigned char value);
void PauseRequestCancel(void);
void fn_800940D8(unsigned short index, unsigned char value);
void fn_8009D888(int index, int value);
void fn_8009D964(int index, int value);
void fn_800A7B5C(void);
void fn_800AFDD4(void (*pCallback)(int, unsigned int, float));
void fn_800B2670(unsigned char value);
void fn_800BA674(void);
int fn_800BA6F8(void);
int fn_800BA71C(void);
void fn_800BB24C(void);
void fn_800BB694(int a, unsigned int b, float c);
void fn_800BBA2C(void);
void fn_800BBB4C(PreGamePhase *pThis);
void fn_800BC3F0(void);
int fn_800C1E40(void);
void fn_800C432C(void);
void fn_800CC448(void);
unsigned int TutorialGetLesson(void);
void ClockRuleNextPeriod(void);
void fn_801790D0(int team, float a, float b);
void HudStart(void);
void HudPost3AOff(void);

extern unsigned short lbl_802D9B14[];
extern unsigned char lbl_803EAB94;
extern unsigned char lbl_803EAB95;
extern unsigned int lbl_803EAB98;
extern unsigned int lbl_803EAB9C;
extern Block_800BC538 *lbl_803EC98C;
}

void PreGamePhase::OnEnter()
{
    int practice;
    unsigned char i;

    PauseRequestCancel();
    lbl_803EC98C->mUnknown32 = 0;
    practice = TutorialGetLesson() <= 4;
    fn_800BA674();
    ClockRuleNextPeriod();
    if (fn_800C1E40() != 0) {
        fn_8009D964(2, 0);
        PlayerObjSetDrawReady(1);
    }
    fn_8009D888(2, 0);
    fn_800CC448();
    fn_800BC3F0();
    lbl_803EAB98 = 0;
    lbl_803EAB9C = 0;
    fn_800BB24C();
    if (fn_800BA71C() == 1 || practice) {
        lbl_803EAB94 = 1;
    } else {
        Block_800BC538 *pBlock = lbl_803EC98C;

        pBlock->mUnknown18 = -1;
        pBlock->mUnknown1C = -1;
        pBlock->mUnknown20 = -1;
        pBlock->mUnknown28 = 0;
        lbl_803EAB95 = 0;
        if (fn_800BA6F8() == 0) {
            PlayerObjSetDrawReady(0);
        }
        BallsSetVisible(1);
        lbl_803EAB94 = 0;
        fn_800BBA2C();
    }
    if (fn_800C1E40() != 0) {
        fn_800BBA2C();
        fn_800BBB4C(this);
        lbl_803EAB94 = 1;
    }
    if (ChallengeIsActive() != 0) {
        fn_800BBB4C(this);
    }
    if (practice) {
        fn_800BBB4C(this);
    }
    fn_800AFDD4(fn_800BB694);
    fn_8003E174(0);
    fn_800B2670(0);
    fn_800C432C();
    if (fn_800C1E40() == 0) {
        HudStart();
    }
    if (ChallengeIsActive() != 0) {
        if (ChalGetCurrent()->mUnknown1C3 != 0) {
            StyleTrackerSetMeterFraction(0, 0.5f, 0);
            fn_800A7B5C();
        }
        if (ChalGetCurrent()->mUnknown1C2 != 0) {
            StyleTrackerSetMeterFraction(1, 0.5f, 0);
            fn_800A7B5C();
        }
    }
    HudPost3AOff();
    ShowIntroScreen();
    fn_801790D0(0, 0.0f, 0.0f);
    fn_801790D0(1, 0.0f, 0.0f);
    for (i = 0; i < lbl_803EC98C->mUnknown2B; i++) {
        fn_800940D8(i, lbl_802D9B14[i] != 0);
    }
}
