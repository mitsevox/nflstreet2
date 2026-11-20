#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802372EC.h"
#include "game/fn_801FCE10.h"

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
