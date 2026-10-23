#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

extern "C" {
Object_80039F5C *fn_80137B40(void);
Point_8017886C fn_80177FE0(void);
int fn_80177F70(void);
float fn_80178298(void);
int fn_80178320(void);
unsigned int fn_80178D18(int team);
Object_80039F5C *fn_80039F5C(int team, unsigned short index);
int fn_800AD2CC(int team, int flag);
int fn_8009F0B8(Object_80039F5C *p, int angle);
float fn_80237260(int stream);
unsigned int fn_802372EC(int stream, int count);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_80227638(void *pOut, void *pA, void *pB);
void fn_80227538(void *pOut, int angle, float length);
void fn_80227248(void *pOut, void *pIn, float scale);
float fn_802270A4(void *pV);
float fn_80227B04(void *pA, void *pB, void *pC);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_800C146C(Point_8017886C *pOut, Object_80039F5C *pCarrier, Object_80039F5C *p, int kind,
                 Point_8017886C *pA, float *pB, float *pC, float *pD);
extern float lbl_803ECB08;
}

extern "C" int fn_800C0910(Object_80039F5C *p, int kind, unsigned char *pLevel)
{
    Point_8017886C delta;
    Point_8017886C target;
    Point_8017886C extra;
    float b, c, d;
    Point_8017886C goal;
    Point_8017886C offset;
    int targetHeading, carrierHeading, heading;
    unsigned char level = 0;
    Object_80039F5C *pCarrier = fn_80137B40();
    int result = 0;

    if (pCarrier != 0 && pCarrier->mIdBytes[2] == p->mIdBytes[2]) {
        goal = fn_80177FE0();

        if ((p->mFlags & 0x800) || pCarrier->mpState->mId == 52) {
            result = 2;
        } else {
            float dist;

            fn_80227690(&delta, &p->mMotion.mPos, &pCarrier->mMotion.mPos);
            dist = fn_802270A4(&delta);
            heading = delta.Heading();
            if (dist > 5.0f) {
                float carrierDist, rate;
                float targetDist;
                int team, count, i;

                fn_800C146C(&target, pCarrier, p, kind, &extra, &b, &c, &d);
                if ((fn_80177F70() == 4 && target.mY < fn_80178298()) ||
                    (target.mY - goal.mY < 3.0f && target.mX < goal.mX + 6.0f &&
                     target.mX > goal.mX - 6.0f)) {
                    return 2;
                }
                if (!(pCarrier->mFlags & 0x4000)) {
                    float skill = pCarrier->mRatings[6] * (1.0f / 255.0f);
                    float spread = (1.0f - skill) * 20.0f;

                    if (spread != 0.0f) {
                        spread *= fn_80237260(0);
                    }
                    fn_80227538(&offset, fn_802372EC(0, 0x1000000), spread);
                    fn_80227638(&target, &offset, &target);
                }
                fn_80227690(&delta, &target, &p->mMotion.mPos);
                targetHeading = delta.Heading();
                targetDist = fn_802270A4(&delta);
                team = fn_80178320();
                fn_80227690(&delta, &target, &pCarrier->mMotion.mPos);
                carrierHeading = delta.Heading();
                carrierDist = fn_802270A4(&delta);
                if (p->mIdBytes[3] == 1) {
                    rate = p->mRatings[4] * (1.0f / 255.0f);
                } else {
                    rate = 0.75000006f;
                }
                count = fn_80178D18((unsigned char)team);
                for (i = 0; i < count; i++) {
                    Object_80039F5C *q = fn_80039F5C((unsigned char)team, i);
                    unsigned char prev = level;
                    float qrate, qdist;
                    int id;

                    if (q->mIdBytes[3] == 1) {
                        qrate = q->mRatings[4] * (1.0f / 255.0f);
                    } else {
                        qrate = 0.75000006f;
                    }
                    id = q->mpState->mId;
                    fn_80227690(&delta, &p->mMotion.mPos, &q->mMotion.mPos);
                    qdist = fn_802270A4(&delta);
                    delta.Heading();
                    if (id == 22 || id == 40 || id == 92 || id == 85) {
                        float toTarget, toCarrier, ratio;
                        int targetAngle, carrierAngle, leadAngle;

                        fn_80227690(&delta, &target, &q->mMotion.mPos);
                        toTarget = fn_802270A4(&delta);
                        targetAngle = delta.Heading();
                        fn_80227690(&delta, &q->mMotion.mPos, &pCarrier->mMotion.mPos);
                        carrierAngle = delta.Heading();
                        toCarrier = fn_802270A4(&delta);
                        fn_80227248(&delta, &q->mMotion.mUnknown40, 0.0f);
                        fn_80227638(&delta, &delta, &q->mMotion.mPos);
                        fn_80227690(&delta, &delta, &pCarrier->mMotion.mPos);
                        leadAngle = delta.Heading();
                        fn_802270A4(&delta);
                        if (result == 2) {
                            break;
                        }
                        ratio = toTarget / carrierDist;
                        if (toTarget < targetDist) {
                            if (rate < qrate || rate / qrate < targetDist / toTarget) {
                                if (fn_801CFFD0(heading, carrierAngle) <= 0x105B04 && dist < toCarrier) {
                                    level++;
                                } else if (fn_8009F0B8(q, fn_800AD2CC(q->mIdBytes[2], 0))) {
                                    result = 2;
                                }
                            }
                        } else if (qrate > rate && qrate / rate > toTarget / targetDist) {
                            if (fn_801CFFD0(targetAngle, targetHeading) <= 0x155554 && carrierDist > dist) {
                                level++;
                            } else if (fn_8009F0B8(q, fn_800AD2CC(q->mIdBytes[2], 0))) {
                                result = 2;
                            }
                        }
                        if (result != 2 && toCarrier < carrierDist) {
                            int angle = fn_801CFFD0(carrierHeading, leadAngle);
                            Vector_80039F5C point;

                            point.mX = target.mX;
                            point.mY = target.mY;
                            point.mZ = 0.0f;

                            if (fn_80227B04(&pCarrier->mMotion.mPos, &point, &q->mMotion.mPos) < 5.0f) {
                                if (angle <= 0xAAAA9) {
                                    if (kind > 5 || fn_8009F0B8(q, fn_800AD2CC(q->mIdBytes[2], 0))) {
                                        result = 2;
                                    } else {
                                        level += 2;
                                    }
                                } else if (angle <= 0x11C71B) {
                                    if (kind > 5) {
                                        level += 2;
                                    } else if (fn_8009F0B8(q, fn_800AD2CC(q->mIdBytes[2], 0))) {
                                        level++;
                                    }
                                }
                            }
                        }
                        if (result != 2) {
                            if (ratio < qrate * 0.1f) {
                                if (fn_8009F0B8(q, fn_800AD2CC(q->mIdBytes[2], 0))) {
                                    level += 3;
                                } else {
                                    level++;
                                }
                            } else if (ratio < qrate * 0.35f) {
                                if (fn_8009F0B8(q, fn_800AD2CC(q->mIdBytes[2], 0))) {
                                    level += 2;
                                } else {
                                    level++;
                                }
                            } else if (ratio < qrate * 0.7f) {
                                if (fn_8009F0B8(q, fn_800AD2CC(q->mIdBytes[2], 0))) {
                                    level++;
                                }
                            }
                        }
                        if (qdist < 1.5f &&
                            (p->mMotion.mUnknown28 <= lbl_803ECB08 * 0.14f || qdist < 1.0f)) {
                            result = 2;
                        }
                        if (result == 2) {
                            break;
                        }
                        if (prev < level) {
                            if (q->mRatings[8] > 200) {
                                level++;
                            } else if (q->mRatings[8] <= 126 && level != 0) {
                                level--;
                            }
                        }
                    } else if (id != 10 && q->mUnknown8 != 255 && q->mUnknown1032 != 4 &&
                               q->mUnknown1032 != 6 && q->mUnknown1032 != 5 &&
                               q->mpState->mId != 32 && q->mpState->mId != 11 &&
                               q->mpState->mId != 17 && qdist < 5.0f) {
                        level += 2;
                    }
                    if (result == 2) {
                        break;
                    }
                }
            } else {
                result = 2;
            }
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
