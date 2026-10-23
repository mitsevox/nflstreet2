#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/State_803EB098.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

/* View of the block whose address fn_8011F4EC returns. */
struct Block_800FAD2C {
    char mUnknown0[409];
    unsigned char mUnknown409[3];
    char mUnknown412[3];
    unsigned char mUnknown415[3];
};

extern "C" {
Record_8011F4E0 *fn_8011F4E0(void);
int fn_80178308(void);
void *fn_8011F4EC(void);
unsigned char fn_80164B78(void);
int fn_80178320(void);
Object_80039F5C *fn_800FBF74(Object_80039F5C *pTarget, Object_80039F5C *pOther);
unsigned char fn_800FC128(Object_80039F5C *p);
unsigned char fn_800FC1DC(Object_80039F5C *p);
void fn_80104328(Object_80039F5C *p, unsigned int count, int *pTime, Vector_80039F5C *pPos, int *pAngle);
Object_80039F5C *fn_80137B40(void);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
}

extern "C" void fn_800FAD2C(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i = 0;
    int team;
    int mode;
    int swapped;

    pRecord->mUnknown0 = 1;
    pRecord->mUnknown2 = 150;
    team = fn_80178308();
    fn_8016871C(team);
    mode = fn_800AD9B4();
    for (; i <= 2; i++) {
        pRecord->mUnknown8[i] = ((Block_800FAD2C *)fn_8011F4EC())->mUnknown409[i];
        if (mode == 2 && fn_80039F5C(fn_80178308(), pRecord->mUnknown8[i])->mUnknown2914 == 0) {
            pRecord->mUnknown8[i] = fn_80164B78();
        }
    }
    do {
        swapped = 0;
        for (i = 0; i <= 1; i++) {
            float x0 = fn_80039F5C(team, pRecord->mUnknown8[i])->mMotion.mPos.mX;
            float x1 = fn_80039F5C(team, pRecord->mUnknown8[i + 1])->mMotion.mPos.mX;
            float y0 = fn_80039F5C(team, pRecord->mUnknown8[i])->mMotion.mPos.mY;
            float y1 = fn_80039F5C(team, pRecord->mUnknown8[i + 1])->mMotion.mPos.mY;

            if (x0 < x1 + 0.5f && (fabsf(x1 - x0) > 0.5f || y0 < y1)) {
                unsigned char slot = pRecord->mUnknown8[i];

                swapped = 1;
                pRecord->mUnknown8[i] = pRecord->mUnknown8[i + 1];
                pRecord->mUnknown8[i + 1] = slot;
            }
        }
    } while (swapped == 1);
    for (i = 0; i <= 2; i++) {
        pRecord->mUnknown12[i] = pRecord->mUnknown8[i];
    }
}

extern "C" void fn_800FB314(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char count = 0;
    Object_80039F5C *pBlocked = 0;
    signed char blocked = -2;
    unsigned char order[3];
    unsigned char i;
    int team;

    if (!(pRecord->mUnknown0 & 0x8000)) {
        pRecord->mUnknown0--;
        if (pRecord->mUnknown0 & 0x8000) {
            unsigned int n;
            int swapped;
            int total;

            fn_80178320();
            team = fn_80178308();
            n = fn_80178D18(fn_80178320());
            for (i = 0; i < 3; i++) {
                if (!(fn_80039F5C(fn_80178308(), pRecord->mUnknown8[i])->mFlags & 0x20000000)) {
                    order[count++] = pRecord->mUnknown8[i];
                } else {
                    unsigned char j;

                    blocked = i + 1;
                    for (j = 0; j < n; j++) {
                        if (pRecord->mUnknown32[j] == blocked) {
                            pBlocked = fn_80039F5C(fn_80178320(), j);
                        }
                    }
                }
            }
            do {
                unsigned char last = count - 1;

                swapped = 0;
                for (i = 0; i <= last - 1; i++) {
                    Vector_80039F5C posA;
                    Vector_80039F5C posB;
                    Object_80039F5C *pA = fn_80039F5C(team, order[i]);
                    Object_80039F5C *pB = fn_80039F5C(team, order[i + 1]);
                    float xA;
                    float xB;

                    fn_800FBF74(pA, (Object_80039F5C *)pA->mpState);
                    fn_800FBF74(pB, (Object_80039F5C *)pB->mpState);
                    xA = pA->mMotion.mPos.mX;
                    xB = pB->mMotion.mPos.mX;
                    if (!fn_80137B40()) {
                        Point_8017886C goal = fn_80177FE0();
                    }
                    int time = 0;
                    int angle;
                    int routeA = fn_800F06F4(0, pA->mpState, 0x15, 0xFFFF);
                    int routeB = fn_800F06F4(0, pB->mpState, 0x15, 0xFFFF);
                    if (routeA != 0 && routeA != 0xFFFF && routeB != 0 && routeB != 0xFFFF) {
                        float a;
                        float b;

                        fn_80104328(pA, (unsigned char)(routeA - 1), &time, &posA, &angle);
                        fn_80104328(pB, (unsigned char)(routeB - 1), &time, &posB, &angle);
                        a = posA.mX < xA - 1.5f ? xA - 1.5f : (posA.mX > xA + 1.5f ? xA + 1.5f : posA.mX);
                        b = posB.mX < xB - 1.5f ? xB - 1.5f : (posB.mX > xB + 1.5f ? xB + 1.5f : posB.mX);
                        if (a < b) {
                            unsigned char t = order[i];
                            swapped = 1;
                            order[i] = order[i + 1];
                            order[i + 1] = t;
                        }
                    }
                }
            } while (swapped == 1);
            total = fn_80178D18(fn_80178320());
            for (i = 0; i < total; i++) {
                Object_80039F5C *p = fn_80039F5C(fn_80178320(), i);
                unsigned short route = fn_800F06F4(0, p->mpState, 0x16, 0xFFFF);

                if (route != 0xFFFF && pRecord->mUnknown32[p->mIdBytes[1]] != blocked) {
                    unsigned char ahead = fn_800FC128(p);
                    unsigned char behind = fn_800FC1DC(p);
                    unsigned char slot;
                    unsigned char j;

                    if (pBlocked) {
                        if (pBlocked->mMotion.mPos.mX > p->mMotion.mPos.mX) {
                            ahead--;
                        } else {
                            behind--;
                        }
                    }
                    if (ahead < behind || (ahead <= behind && p->mMotion.mPos.mX <= fn_80177FE0().mX)) {
                        slot = ahead;
                    } else {
                        slot = count - behind - 1;
                    }
                    for (j = 0; j < 3; j++) {
                        if (pRecord->mUnknown8[j] == order[slot]) {
                            slot = j + 1;
                            break;
                        }
                    }
                    pRecord->mUnknown32[(p->mId >> 16) & 0xFF] = slot;
                    if (route == 0) {
                        fn_8009BD2C(fn_80039F5C(team, pRecord->mUnknown8[slot - 1]), &p->mUnknown336);
                    }
                }
            }
        }
    }
}
