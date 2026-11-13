#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Block_800A70F4.h"
#include "game/Block_8030F42C.h"
#include "game/cu_8002B8F8.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/Object_8003DEC4.h"
#include "game/StyleTracker.h"

extern "C" {
void *fn_800A3360(void);
void ScreenTintSetActive(int index, unsigned char value);
void ScreenTintSetMode(int index, int value);
void ScreenTintFadeTo(int index, unsigned int color, float value, unsigned int count);

extern Block_800A70F4 *lbl_803EC954[2];
}

extern "C" void fn_800A8570(void)
{
    unsigned char *pColor = (unsigned char *)fn_800A3360();
    unsigned int color = (pColor[2] << 16) + (pColor[1] << 8) + pColor[0];
    float alpha = (unsigned int)pColor[3] * (1.0f / 255.0f);

    ScreenTintSetActive(0, 1);
    ScreenTintFadeTo(0, color, alpha, 60);
    ScreenTintSetMode(0, 1);
}

extern "C" void fn_800A866C(void)
{
    if (lbl_803EC954[0]->mUnknown68 != 0 || lbl_803EC954[1]->mUnknown68 != 0) {
        unsigned char *pColor = (unsigned char *)fn_800A3360();
        unsigned int color = (pColor[2] << 16) + (pColor[1] << 8) + pColor[0];
        float alpha = (unsigned int)pColor[3] * (1.0f / 255.0f);

        ScreenTintSetActive(0, 1);
        ScreenTintFadeTo(0, color, alpha, 1);
        ScreenTintSetMode(0, 1);
    }
}

/* 12-byte per-event records of the table at 0x80297E84. */
struct Entry_80297E84 {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

extern "C" {
int fn_80178348(void);
int fn_800A8444(int team);
int fn_800A8EA4(int team);
int fn_800A9680(void);
void fn_800A636C(int team, Object_80039F5C **ppOut);
void fn_800A7A0C(int team);
void fn_80071C34(int a);

extern Entry_80297E84 lbl_80297E84[];
}

extern "C" void fn_800A8954(int event, int team, Object_80039F5C *p)
{
    int other = team == 0;
    int isUser = team == fn_80178348();
    Object_80039F5C *pair[2];
    unsigned int amount;

    if (fn_800A8444(team)) {
        if (p != 0 && lbl_80297E84[event].mUnknown9 != 0) {
            fn_800A636C(team, pair);
            if (fn_800A9680() == 0 && (p == pair[0] || p == pair[1])) {
                fn_801477F0((Object_8003DEC4 *)p->mpUnknown4);
                AudmonEventPost(14, &p->mMotion.mPos);
            }
        }
        if (isUser) {
            amount = lbl_80297E84[event].mUnknown0 * 2.0f;
        } else {
            amount = lbl_80297E84[event].mUnknown4 * 2.0f;
        }
        if (fn_800A8EA4(team) == 2) {
            amount = amount * 0.5f;
        }
        if (amount > lbl_803EC954[team]->mUnknown54) {
            amount = lbl_803EC954[team]->mUnknown54;
        }
        lbl_803EC954[team]->mUnknown54 -= amount;
        StyleTrackerSetMeterFraction(team, 0.5f * ((float)lbl_803EC954[team]->mUnknown54 / (float)lbl_803EC954[team]->mUnknown10),
                    0);
        if (lbl_803EC954[team]->mUnknown54 == 0) {
            if (event == 9 || event == 14 || event == 16) {
                fn_80071C34(1);
            }
            fn_800A7A0C(team);
        }
    }
    if (lbl_80297E84[event].mUnknown8 != 0 && fn_800A8444(other)) {
        if (lbl_80297E84[event].mUnknown9 != 0) {
            fn_800A636C(other, pair);
            if (fn_800A9680() == 0 && (p == pair[0] || p == pair[1])) {
                fn_801477F0((Object_8003DEC4 *)p->mpUnknown4);
                AudmonEventPost(14, &p->mMotion.mPos);
            }
        }
        if (!isUser) {
            amount = lbl_80297E84[event].mUnknown0 * 2.0f;
        } else {
            amount = lbl_80297E84[event].mUnknown4 * 2.0f;
        }
        if (fn_800A8EA4(other) == 2) {
            amount = amount * 0.5f;
        }
        if (amount > lbl_803EC954[other]->mUnknown54) {
            amount = lbl_803EC954[other]->mUnknown54;
        }
        lbl_803EC954[other]->mUnknown54 -= amount;
        StyleTrackerSetMeterFraction(other, 0.5f * ((float)lbl_803EC954[other]->mUnknown54 / (float)lbl_803EC954[other]->mUnknown10),
                    0);
        if (lbl_803EC954[other]->mUnknown54 == 0) {
            if (event == 9 || event == 14 || event == 16) {
                fn_80071C34(1);
            }
            fn_800A7A0C(other);
        }
    }
}

extern "C" {
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);
int fn_800927BC(unsigned char index);
void fn_80094598(int index);
void fn_80093410(int handle);
int fn_80178508(Point_8017886C *pPos, float *pOut, int skipFlags);
void PlyrMgrUpdate(void);
void PlyrMgrRunBrains(float dt);
void PlyrMgrUpdatePoses(float dt);
void PlyrMgrUpdateMotion(float dt);
void PlyrMgrUpdateSkeletons(float dt);
void CamGameResumeAll(void);
void HudPost3AOn(void);
int TutorialIsActive(void);
void TutorialSetHudVisible(int value);
int fn_800A8468(int team);
void fn_800A981C(void);
void fn_800A9854(void);

extern float gFrameTimeScale;
extern unsigned char lbl_803EAA84;
extern unsigned char lbl_803EAA85;
extern Block_8030F42C lbl_8030F42C;
}

extern "C" void fn_800A9478(int skipPlayerReset)
{
    if (lbl_803EAA84 != 0) {
        int lost = 0;
        unsigned int i;
        unsigned int step;
        Vector_80039F5C pos;

        fn_8002C9A8(lbl_803EA368, 3, 0);
        fn_8002C9A8(lbl_803EA368, 1, 0);
        BallGetPosition(BallGetCurrent(), &pos);
        if (fn_80178508((Point_8017886C *)&pos, 0, 0) != 1) {
            lost = 1;
        }
        for (i = 0; i <= 1; i++) {
            if (lbl_8030F42C.mUnknown1C[i] != 0) {
                if (fn_800927BC(lbl_8030F42C.mUnknown14[i]) == 0) {
                    fn_80094598((unsigned char)lbl_8030F42C.mUnknown14[i]);
                }
                fn_80093410(lbl_8030F42C.mUnknown14[i]);
                lbl_8030F42C.mpUnknown24[i] = 0;
                lbl_8030F42C.mUnknown1C[i] = 0;
            }
        }
        lbl_803EAA84 = 0;
        lbl_803EAA85 = 0;
        fn_800A981C();
        if (skipPlayerReset == 0) {
            fn_800A9854();
        }
        for (step = 0; step <= 19; step++) {
            PlyrMgrUpdate();
            BallsProcessMotion(1.0f);
            PlyrMgrRunBrains(gFrameTimeScale);
            PlyrMgrUpdatePoses(gFrameTimeScale);
            PlyrMgrUpdateMotion(gFrameTimeScale);
            PlyrMgrUpdateSkeletons(gFrameTimeScale);
            BallsProcessStates(gFrameTimeScale);
            BallsProcessCollision(gFrameTimeScale);
        }
        if (TutorialIsActive()) {
            TutorialSetHudVisible(1);
        }
        if (lost) {
            fn_8002C9A8(lbl_803EA368, 2, 0);
        }
        CamGameResumeAll();
        HudPost3AOn();
        if (fn_800A8468(0) || fn_800A8468(1)) {
            AudmonEventPostArgs(13, 0, 0, 0, 0);
        }
    }
}
