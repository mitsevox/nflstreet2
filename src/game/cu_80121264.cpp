#include "game/Object_80039F5C.h"
#include "game/Plan_80121264.h"
#include "game/fn_801C1F94.h"

extern "C" {

void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_80120B4C(int value, int *pList, unsigned char i, unsigned char count);
void fn_80120CDC(Object_80039F5C *p, Object_80039F5C *pOther, Entry_80120E98 *pEntry);
void fn_80120D98(Object_80039F5C *p, Point_8017886C *pMin, Point_8017886C *pMax);
void fn_80120EF8(Plan_80121264 *pPlan, Vector_80039F5C *pPos);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
float fn_80178A08(void);
int fn_80178D70(int team);
int fn_801783AC(int bit);
float fn_802270A4(void *p);
void fn_80227690(void *pOut, void *pA, void *pB);

void fn_80121264(Object_80039F5C *p, Plan_80121264 *pPlan)
{
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    Object_80039F5C *players[14];
    unsigned char count = 0;
    unsigned char team;
    unsigned char i;
    float range;
    Object_80039F5C *pPlayer;
    Entry_80120E98 *pLast;

    fn_801C1F94(pPlan, 0, sizeof(Plan_80121264));
    fn_801C1F94(players, 0, sizeof(players));
    if (fn_8011F1A4() && fn_8011F1A4() && fn_8011F4C8() <= 3 && !fn_801783AC(0)) {
        range = 5.0f;
    } else {
        range = 8.0f;
    }
    for (team = 0; team <= 1; team++) {
        unsigned int n = fn_80178D70(team);

        for (i = 0; i < n; i++) {
            pPlayer = fn_80039F5C(team, i);

            if (pPlayer->mMotion.mPos.mY > pPos->mY && pPlayer->mMotion.mPos.mY - pPos->mY < range) {
                players[count] = pPlayer;
                count++;
            }
        }
    }
    pPlan->mUnknown1440 = 1;
    for (i = 0; i < count; i++) {
        Object_80039F5C *pPartner;
        Entry_80120E98 *pA;
        Entry_80120E98 *pB;
        Point_8017886C min;
        Point_8017886C max;
        Point_8017886C partnerMin;
        Point_8017886C partnerMax;

        pPlayer = players[i];
        if (!pPlayer) {
            continue;
        }
        pA = &pPlan->mUnknown0[pPlan->mUnknown1440];
        pB = &pPlan->mUnknown0[pPlan->mUnknown1440 + 1];
        pB->mUnknown36 = 0;
        pA->mUnknown36 = 0;
        fn_8009BD2C(0, &pA->mUnknown40);
        fn_8009BD2C(0, &pA->mUnknown44);
        pB->mUnknown40 = pA->mUnknown40;
        pB->mUnknown44 = pA->mUnknown44;
        switch (pPlayer->mUnknown1032) {
        case 4:
        case 5:
        case 6:
            pPartner = fn_8009BCE8(&pPlayer->mUnknown1036);
            fn_80120D98(pPlayer, &min, &max);
            fn_80120D98(pPartner, &partnerMin, &partnerMax);
            pA->mUnknown8.mX = max.mX >= partnerMax.mX ? max.mX : partnerMax.mX;
            pB->mUnknown8.mX = min.mX <= partnerMin.mX ? min.mX : partnerMin.mX;
            pA->mUnknown8.mY = min.mY <= partnerMin.mY ? min.mY : partnerMin.mY;
            if (pPos->mY > pA->mUnknown8.mY) {
                pA->mUnknown8.mY = max.mY >= partnerMax.mY ? max.mY : partnerMax.mY;
                if (pPos->mY < pA->mUnknown8.mY) {
                    pA->mUnknown8.mY = (pA->mUnknown8.mY + pPos->mY) * 0.5f;
                }
            }
            pB->mUnknown8.mY = pA->mUnknown8.mY;
            fn_80120CDC(p, pPartner, pA);
            fn_80120CDC(p, pPartner, pB);
            fn_80120CDC(p, pPlayer, pA);
            fn_80120CDC(p, pPlayer, pB);
            if (pPartner->mIdBytes[2] == p->mIdBytes[2]) {
                pA->mpUnknown0 = (Point_8017886C *)&pPartner->mMotion.mPos;
                pA->mpUnknown4 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                pA->mUnknown16 = pPlayer->mMotion.mFacing;
            } else {
                pA->mpUnknown0 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                pA->mpUnknown4 = (Point_8017886C *)&pPartner->mMotion.mPos;
                pA->mUnknown16 = pPartner->mMotion.mFacing;
            }
            pB->mpUnknown0 = pA->mpUnknown0;
            pB->mpUnknown4 = pA->mpUnknown4;
            pB->mUnknown16 = pA->mUnknown16;
            pA->mUnknown40 = pPlayer->mId;
            pA->mUnknown44 = pPartner->mId;
            pB->mUnknown40 = pA->mUnknown40;
            pB->mUnknown44 = pA->mUnknown44;
            fn_80120B4C((int)pPartner, (int *)players, i, count);
            break;
        default:
            fn_80120D98(pPlayer, &min, &max);
            pA->mUnknown8.mX = max.mX;
            pB->mUnknown8.mX = min.mX;
            pA->mUnknown8.mY = min.mY;
            if (pPos->mY > pA->mUnknown8.mY) {
                pA->mUnknown8.mY = max.mY;
                if (pPos->mY < pA->mUnknown8.mY) {
                    pA->mUnknown8.mY = (pA->mUnknown8.mY + pPos->mY) * 0.5f;
                }
            }
            pB->mUnknown8.mY = pA->mUnknown8.mY;
            pA->mUnknown40 = pPlayer->mId;
            pPartner = fn_8009BCE8(&pPlayer->mUnknown1036);
            if (pPartner) {
                if (pPartner->mIdBytes[2] == p->mIdBytes[2]) {
                    pA->mpUnknown0 = (Point_8017886C *)&pPartner->mMotion.mPos;
                    pA->mpUnknown4 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                } else {
                    pA->mpUnknown0 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                    pA->mpUnknown4 = (Point_8017886C *)&pPartner->mMotion.mPos;
                }
                pA->mUnknown44 = pPartner->mId;
            } else {
                pA->mpUnknown0 = 0;
                pA->mpUnknown4 = 0;
            }
            pB->mpUnknown0 = pA->mpUnknown0;
            pB->mpUnknown4 = pA->mpUnknown4;
            fn_80120CDC(p, pPlayer, pA);
            fn_80120CDC(p, pPlayer, pB);
            pA->mUnknown16 = pPlayer->mMotion.mFacing;
            pB->mUnknown16 = pPlayer->mMotion.mFacing;
            pB->mUnknown40 = pA->mUnknown40;
            pB->mUnknown44 = pA->mUnknown44;
            break;
        }
        if (pA->mUnknown8.mY < pPos->mY || pB->mUnknown8.mY < pPos->mY) {
            continue;
        }
        if (pA->mpUnknown0 && pA->mpUnknown4 && pB->mpUnknown0 && pB->mpUnknown4) {
            Point_8017886C delta;
            int heading;
            float distance;

            fn_80227690(&delta, pPos, pA->mpUnknown0);
            pA->mUnknown20 = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            pA->mUnknown28 = fn_802270A4(&delta);
            pB->mUnknown20 = pA->mUnknown20;
            pB->mUnknown28 = pA->mUnknown28;
            fn_80227690(&delta, pA->mpUnknown4, pA->mpUnknown0);
            heading = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            pA->mUnknown24 = heading;
            pB->mUnknown24 = heading;
            fn_80227690(&delta, pPos, pA->mpUnknown4);
            distance = fn_802270A4(&delta);
            pA->mUnknown32 = distance;
            pB->mUnknown32 = distance;
        }
        pPlan->mUnknown1440 += 2;
    }
    pPlan->mUnknown0[0].mUnknown36 = 0x40;
    pPlan->mUnknown0[0].mUnknown16 = 0;
    pPlan->mUnknown0[0].mpUnknown0 = 0;
    pPlan->mUnknown0[0].mpUnknown4 = 0;
    fn_8009BD2C(0, &pPlan->mUnknown0[0].mUnknown40);
    fn_8009BD2C(0, &pPlan->mUnknown0[0].mUnknown44);
    pPlan->mUnknown0[0].mUnknown8.mX = -fn_80178A08();
    if (pPlan->mUnknown1440 > 1) {
        pPlan->mUnknown0[0].mUnknown8.mY = pPlan->mUnknown0[1].mUnknown8.mY >= pPos->mY + 5.0f
                                               ? pPlan->mUnknown0[1].mUnknown8.mY
                                               : pPos->mY + 5.0f;
    } else {
        pPlan->mUnknown0[0].mUnknown8.mY = pPos->mY + 5.0f;
    }
    pLast = &pPlan->mUnknown0[pPlan->mUnknown1440];
    pLast->mUnknown36 = 0x40;
    pLast->mUnknown16 = 0;
    pLast->mpUnknown0 = 0;
    pLast->mpUnknown4 = 0;
    fn_8009BD2C(0, &pLast->mUnknown40);
    fn_8009BD2C(0, &pLast->mUnknown44);
    pLast->mUnknown8.mX = fn_80178A08();
    pLast->mUnknown8.mY = pPlan->mUnknown0[pPlan->mUnknown1440 - 1].mUnknown8.mY >= pPos->mY + 5.0f
                              ? pPlan->mUnknown0[pPlan->mUnknown1440 - 1].mUnknown8.mY
                              : pPos->mY + 5.0f;
    pPlan->mUnknown1440++;
    fn_80120EF8(pPlan, pPos);
}

}
