#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802372EC.h"
#include "game/fn_801FCE10.h"
#include "game/PlyrSlot.h"
#include "game/Ball.h"
#include "game/cu_8002B8F8.h"
#include "game/StyleTracker.h"
#include "game/GameModeType.h"
#include "game/fn_800AD9B4.h"

extern "C" {
Object_80039F5C *BallGetCurrentHolder(void);
Object_80039F5C *PlyrGet(int team, unsigned short index);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_80227638(void *pOut, void *pA, void *pB);
float fn_802270A4(void *p);
int fn_801CFE40(float y, float x);
int fn_80177F70(void);
float fn_80178298(void);
float fn_80237260(int stream);
void fn_80227538(Point_8017886C *pOut, int angle, float magnitude);
void fn_80227248(void *pOut, void *pIn, float scale);
float fn_80227B04(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
int fn_80178320(void);
unsigned int fn_80178D18(int team);
int fn_800AD2CC(int team, int flag);
int fn_8009F0B8(Object_80039F5C *p, int angle);
float fn_800C146C(Point_8017886C *pOut, Object_80039F5C *pPasser, Object_80039F5C *pReceiver, int ticks,
                  Point_8017886C *pLead, float *pSpeed, int *pAngle, Point_8017886C *pAim);

float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
int PlayerCutGetAnimTime(Object_80039F5C *p);
int PlayerCutGetTimeLeft(Object_80039F5C *p);
int PlayerCutGetAnimLength(unsigned char cut);
void PlayerCutGetAnimOffset(int cut, unsigned char kind, int angle, Point_8017886C *pOut);
void GetOpenGetRunOnPoint(Object_80039F5C *p, Point_8017886C *pOut);
float fn_80103DD8(Object_80039F5C *pPasser, Object_80039F5C *pReceiver, short *pTicks, float scale);
void fn_80103F80(Ball_t *pBall, Vector_80039F5C pos, Vector_80039F5C velocity, float speed, int angle, float time,
                 Vector_80039F5C *pOut, Object_80039F5C *p);
float fn_80178A08(void);
float fn_80178A44(void);

extern float gPlyrMoveFwdSpeed;
}

// FAKEMATCH: reconstructed unused AGLP query helpers. The target keeps their three query strings
// (.rodata 0x802974D0-0x8029756C) with no code that loads them; inline helpers that nothing calls
// emit the strings and no code, which also gives the doubles of 0x800C0910 their 8-byte alignment.
static inline QueryCursor _GameSetupDeclareAglp(int id)
{
    QueryCursor cursor;
    QueryResult result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (id >= 0) {
        fn_801FCE10(&result, "declare \x8a cursor for select * from 'AGLP' where ('DIGP' = \x84)\n", &cursor, id);
    } else {
        fn_801FCE10(&result, "declare \x8a cursor for select * from 'AGLP'\n", &cursor);
    }
    return cursor;
}

static inline int _GameSetupFetchAglp(QueryCursor *pCursor, int *pSkill, int *pForm)
{
    return fn_801FCE10(0, "fetch from \x8a 'IKSP' into \x82 and 'CFRP' into \x82\n", pCursor, pSkill, pForm);
}

// FAKEMATCH: release form of an assert macro whose empty inline keeps its float literals in the pool.
static inline void _PassLaneAssertRange(float, float, float)
{
}
#define PASSLANE_ASSERT_RANGE(v, lo, hi) _PassLaneAssertRange(v, lo, hi)

extern "C" int fn_800C0910(Object_80039F5C *p, int kind, unsigned char *pLevel)
{
    unsigned char level = 0;
    int result = 0;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();

    if (pCarrier != 0 && pCarrier->mIdBytes[2] == p->mIdBytes[2]) {
        Point_8017886C field;

        field = fn_80177FE0();

        if (!(p->mFlags & 0x800) && pCarrier->mpState->mId != 52) {
            Point_8017886C delta;
            int targetAngle;
            int carrierAngle;
            float distance;
            int angle;

            fn_80227690(&delta, &p->mMotion.mPos, &pCarrier->mMotion.mPos);
            distance = fn_802270A4(&delta);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (distance > 5.0f) {
                Point_8017886C target;
                Point_8017886C lead;
                float speed;
                int heading;
                Point_8017886C aim;
                float targetDistance;
                int other;
                float carrierDistance;
                float rating;
                int count;
                int i;

                fn_800C146C(&target, pCarrier, p, kind, &lead, &speed, &heading, &aim);
                if ((fn_80177F70() == 4 && target.mY < fn_80178298())
                    || (target.mY - field.mY < 3.0f && target.mX < field.mX + 6.0f && target.mX > field.mX - 6.0f)) {
                    return 2;
                }
                if (!(pCarrier->mFlags & 0x4000)) {
                    Point_8017886C offset;
                    float accuracy = pCarrier->mRatings[6] * 0.003921569f;
                    float spread;

                    // FAKEMATCH: compiled-out range assert on the rating fraction; its 0.0f enters the pool before 1.0f
                    PASSLANE_ASSERT_RANGE(accuracy, 0.0f, 1.0f);
                    spread = (1.0f - accuracy) * 20.0f;
                    if (spread != 0.0f) {
                        spread *= fn_80237260(0);
                    }
                    fn_80227538(&offset, fn_802372EC(0, 0x1000000), spread);
                    fn_80227638(&target, &offset, &target);
                }
                fn_80227690(&delta, &target, &p->mMotion.mPos);
                targetAngle = fn_801CFE40(delta.mY, delta.mX);
                targetDistance = fn_802270A4(&delta);
                other = fn_80178320();
                fn_80227690(&delta, &target, &pCarrier->mMotion.mPos);
                carrierAngle = fn_801CFE40(delta.mY, delta.mX);
                carrierDistance = fn_802270A4(&delta);
                if (p->mIdBytes[3] == 1) {
                    rating = p->mRatings[4] * 0.003921569f;
                } else {
                    rating = 0.75000006f;
                }
                count = fn_80178D18((unsigned char)other);
                for (i = 0; i < count; i++) {
                    unsigned char previous = level;
                    Object_80039F5C *pDefender = PlyrGet((unsigned char)other, i);
                    float defenderRating;
                    int state;
                    float defenderDistance;

                    if (pDefender->mIdBytes[3] == 1) {
                        defenderRating = pDefender->mRatings[4] * 0.003921569f;
                    } else {
                        defenderRating = 0.75000006f;
                    }
                    state = pDefender->mpState->mId;
                    fn_80227690(&delta, &p->mMotion.mPos, &pDefender->mMotion.mPos);
                    defenderDistance = fn_802270A4(&delta);
                    fn_801CFE40(delta.mY, delta.mX);
                    if (state == 22 || state == 40 || state == 92 || state == 85) {
                        float laneDistance;
                        int laneAngle;
                        int defenderAngle;
                        float defenderGap;
                        int leadAngle;
                        float ratio;

                        fn_80227690(&delta, &target, &pDefender->mMotion.mPos);
                        laneDistance = fn_802270A4(&delta);
                        laneAngle = fn_801CFE40(delta.mY, delta.mX);
                        fn_80227690(&delta, &pDefender->mMotion.mPos, &pCarrier->mMotion.mPos);
                        defenderAngle = fn_801CFE40(delta.mY, delta.mX);
                        defenderGap = fn_802270A4(&delta);
                        fn_80227248(&delta, &pDefender->mMotion.mUnknown40, 0.0f);
                        fn_80227638(&delta, &delta, &pDefender->mMotion.mPos);
                        fn_80227690(&delta, &delta, &pCarrier->mMotion.mPos);
                        leadAngle = fn_801CFE40(delta.mY, delta.mX);
                        fn_802270A4(&delta);
                        if (result != 2) {
                            ratio = laneDistance / carrierDistance;
                            if (laneDistance < targetDistance) {
                                if (rating < defenderRating
                                    || rating / defenderRating < targetDistance / laneDistance) {
                                    if (MathAngleDiff(angle, defenderAngle) <= 0x105B04 && distance < defenderGap) {
                                        level++;
                                    } else if (fn_8009F0B8(pDefender, fn_800AD2CC(pDefender->mIdBytes[2], 0))) {
                                        result = 2;
                                    }
                                }
                            } else if (defenderRating > rating
                                       && defenderRating / rating > laneDistance / targetDistance) {
                                if (MathAngleDiff(laneAngle, targetAngle) <= 0x155554 && carrierDistance > distance) {
                                    level++;
                                } else if (fn_8009F0B8(pDefender, fn_800AD2CC(pDefender->mIdBytes[2], 0))) {
                                    result = 2;
                                }
                            }
                            if (result != 2 && defenderGap < carrierDistance) {
                                int diff = MathAngleDiff(carrierAngle, leadAngle);
                                Vector_80039F5C lane;

                                lane.mX = target.mX;
                                lane.mY = target.mY;
                                lane.mZ = 0.0f;
                                if (fn_80227B04(&pCarrier->mMotion.mPos, &lane, &pDefender->mMotion.mPos) < 5.0f) {
                                    if (diff <= 0xAAAA9) {
                                        if (kind > 5
                                            || fn_8009F0B8(pDefender, fn_800AD2CC(pDefender->mIdBytes[2], 0))) {
                                            result = 2;
                                        } else {
                                            level += 2;
                                        }
                                    } else if (diff <= 0x11C71B) {
                                        if (kind > 5) {
                                            level += 2;
                                        } else if (fn_8009F0B8(pDefender, fn_800AD2CC(pDefender->mIdBytes[2], 0))) {
                                            level += 1;
                                        }
                                    }
                                }
                            }
                            if (result != 2) {
                                if (ratio < defenderRating * 0.1f) {
                                    if (fn_8009F0B8(pDefender, fn_800AD2CC(pDefender->mIdBytes[2], 0))) {
                                        level += 3;
                                    } else {
                                        level += 1;
                                    }
                                } else if (ratio < defenderRating * 0.35f) {
                                    if (fn_8009F0B8(pDefender, fn_800AD2CC(pDefender->mIdBytes[2], 0))) {
                                        level += 2;
                                    } else {
                                        level += 1;
                                    }
                                } else if (ratio < defenderRating * 0.7f) {
                                    if (fn_8009F0B8(pDefender, fn_800AD2CC(pDefender->mIdBytes[2], 0))) {
                                        level += 1;
                                    }
                                }
                            }
                            if (defenderDistance < 1.5f
                                && (p->mMotion.mUnknown28 <= gPlyrMoveFwdSpeed * 0.14f || defenderDistance < 1.0f)) {
                                result = 2;
                            }
                        }
                        if (result != 2 && previous < level) {
                            if (pDefender->mRatings[8] > 200) {
                                level++;
                            } else if (pDefender->mRatings[8] <= 126 && level != 0) {
                                level--;
                            }
                        }
                    } else if (state != 10 && pDefender->mUnknown8 != 255 && pDefender->mUnknown1032 != 4
                               && pDefender->mUnknown1032 != 6 && pDefender->mUnknown1032 != 5
                               && pDefender->mpState->mId != 32 && pDefender->mpState->mId != 11
                               && pDefender->mpState->mId != 17 && defenderDistance < 5.0f) {
                        level += 2;
                    }
                    if (result == 2) {
                        break;
                    }
                }
            } else {
                result = 2;
            }
        } else {
            result = 2;
        }
        if (result != 2) {
            if (level > 3) {
                result = 2;
            } else if (level != 0) {
                result = 1;
            }
        } else {
            level = 0;
        }
    } else {
        result = 2;
    }
    *pLevel = level;
    return result;
}

extern "C" float fn_800C146C(Point_8017886C *pOut, Object_80039F5C *pPasser, Object_80039F5C *pReceiver, int ticks,
                             Point_8017886C *pLead, float *pSpeed, int *pAngle, Point_8017886C *pAim)
{
    Vector_80039F5C landing;
    PlyrSlot_t passer = *(PlyrSlot_t *)pPasser;
    PlyrSlot_t receiver = *(PlyrSlot_t *)pReceiver;
    short passTicks = ticks;
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    Point_8017886C step;
    Point_8017886C point;
    Point_8017886C delta;
    Point_8017886C dir;
    Point_8017886C back;
    Point_8017886C span;
    float ratio = 1.0f;
    float flight;
    float distance;
    int remaining = 20;
    unsigned char i = 0;

    do {
        State_80039F5C *pState = &pReceiver->mpState[i];
        State_80039F5C *pNext = &pReceiver->mpState[i + 1];

        switch (pState->mId) {
        case 3:
        case 19: {
            int heading;
            int penalty;
            int frames;
            float length;
            float speed;

            if (i == 0) {
                Point_8017886C *pTarget = (Point_8017886C *)&pReceiver->mUnknown336Words[0];

                step.mX = pTarget->mX - receiver.mObject.mMotion.mPos.mX;
                step.mY = pTarget->mY - receiver.mObject.mMotion.mPos.mY;
                point.mX = pTarget->mX;
                point.mY = pTarget->mY;
                heading = (pState->mUnknown2 << 17) & 0xFFFFFF;
            } else {
                heading = (pState->mUnknown2 << 17) & 0xFFFFFF;
                fn_80227538(&step, heading, (unsigned int)pState->mUnknown1 * 0.125f);
                point.mX = receiver.mObject.mMotion.mPos.mX + step.mX;
                point.mY = receiver.mObject.mMotion.mPos.mY + step.mY;
            }
            penalty = 0;
            {
                int turn = MathAngleDiff(heading, receiver.mObject.mMotion.mUnknown32);

                if (turn > 0x1F49F4) {
                    penalty = (int)((float)(turn - 0x1F49F4) * (25.0f / (float)MathAngleDiff(0x1F49F4, 0x800000)));
                }
            }
            fn_80227690(&delta, &point, &receiver.mObject.mMotion.mPos);
            length = fn_802270A4(&delta);
            speed = PlyrMoveGetRatedSpeed(pReceiver, 1.0f, 1.0f);
            fn_80227538(&dir, heading, speed);
            frames = (int)(length / speed);
            remaining -= penalty;
            if (remaining < 0) {
                remaining = 0;
            }
            receiver.mObject.mMotion.mUnknown32 = heading;
            receiver.mObject.mMotion.mUnknown28 = speed;
            receiver.mObject.mMotion.mUnknown40 = dir.mX;
            receiver.mObject.mMotion.mUnknown44 = dir.mY;
            if (frames >= remaining) {
                receiver.mObject.mMotion.mPos.mX += dir.mX * remaining;
                receiver.mObject.mMotion.mPos.mY += dir.mY * remaining;
            } else {
                receiver.mObject.mMotion.mPos.mX = point.mX;
                receiver.mObject.mMotion.mPos.mY = point.mY;
            }
            remaining -= frames;
            break;
        }
        case 20: {
            State_80039F5C *pCut = &receiver.mObject.mpState[i];
            unsigned char kind = pCut->mUnknown1;
            unsigned char cut = pCut->mUnknown2;
            int length;
            int heading;
            float speed;

            if (i == 0) {
                PlayerCutGetAnimTime(pReceiver);
                length = PlayerCutGetTimeLeft(pReceiver);
            } else {
                length = PlayerCutGetAnimLength(cut);
            }
            if (remaining < length) {
                ratio = (float)length / (float)PlayerCutGetAnimLength(cut);
            } else {
                ratio = 1.0f;
            }
            PlayerCutGetAnimOffset(cut, kind, receiver.mObject.mMotion.mUnknown32, &step);
            step.mX *= ratio;
            step.mY *= ratio;
            heading = (pNext->mUnknown2 << 17) & 0xFFFFFF;
            speed = PlyrMoveGetRatedSpeed(pReceiver, 1.0f, 1.0f);
            fn_80227538(&dir, heading, speed);
            receiver.mObject.mMotion.mPos.mX += step.mX;
            receiver.mObject.mMotion.mUnknown40 = dir.mX;
            receiver.mObject.mMotion.mPos.mY += step.mY;
            receiver.mObject.mMotion.mUnknown32 = heading;
            receiver.mObject.mMotion.mUnknown28 = speed;
            receiver.mObject.mMotion.mUnknown44 = dir.mY;
            if (remaining < length) {
                fn_80227538(&back, heading, (float)(length - remaining) * speed * 0.95f);
                fn_80227690(&receiver.mObject.mMotion.mPos, &receiver.mObject.mMotion.mPos, &back);
            }
            remaining -= length;
            break;
        }
        case 21: {
            int heading;
            float speed;

            GetOpenGetRunOnPoint(&receiver.mObject, &step);
            speed = PlyrMoveGetRatedSpeed(pReceiver, 1.0f, 1.0f);
            fn_80227690(&step, &step, &receiver.mObject.mMotion.mPos);
            heading = fn_801CFE40(step.mY, step.mX);
            fn_80227538(&dir, heading, speed);
            receiver.mObject.mMotion.mUnknown40 = dir.mX;
            receiver.mObject.mMotion.mUnknown32 = heading;
            receiver.mObject.mMotion.mUnknown28 = speed;
            receiver.mObject.mMotion.mUnknown44 = dir.mY;
            receiver.mObject.mMotion.mPos.mX += dir.mX * remaining;
            receiver.mObject.mMotion.mPos.mY += dir.mY * remaining;
            remaining = 0;
            break;
        }
        case 13:
        case 51:
        case 52:
        default:
            remaining = 0;
            break;
        }
        i++;
    } while (remaining > 0);
    if (pLead != 0) {
        pLead->mX = receiver.mObject.mMotion.mPos.mX;
        pLead->mY = receiver.mObject.mMotion.mPos.mY;
    }
    if (pSpeed != 0) {
        *pSpeed = receiver.mObject.mMotion.mUnknown28;
    }
    if (pAngle != 0) {
        *pAngle = receiver.mObject.mMotion.mUnknown32;
    }
    if (pAim != 0) {
        pAim->mX = receiver.mObject.mMotion.mUnknown40;
        pAim->mY = receiver.mObject.mMotion.mUnknown44;
    }
    flight = fn_80103DD8(&passer.mObject, &receiver.mObject, &passTicks, 0.9f);
    pos = receiver.mObject.mMotion.mPos;
    velocity = *(Vector_80039F5C *)&receiver.mObject.mMotion.mUnknown40;
    fn_80103F80(BallGetCurrent(), pos, velocity, receiver.mObject.mMotion.mUnknown28, receiver.mObject.mMotion.mUnknown32,
                flight, &landing, &receiver.mObject);
    fn_80227690(&span, &pReceiver->mMotion.mPos, &pPasser->mMotion.mPos);
    distance = fn_802270A4(&span);
    pOut->mX = landing.mX;
    pOut->mY = landing.mY;
    pOut->mX = pOut->mX > fn_80178A08() ? fn_80178A08() : pOut->mX;
    pOut->mX = pOut->mX < -fn_80178A08() ? -fn_80178A08() : pOut->mX;
    pOut->mY = pOut->mY > fn_80178A44() ? fn_80178A44() : pOut->mY;
    return distance;
}
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
void CamShotRequestStop(void);
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
    CamShotRequestStop();
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
