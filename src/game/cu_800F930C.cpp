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

/* View of the block at player +336 used by fn_800F846C, fn_800F8828,
   fn_800F8A88 and fn_800FA0DC. */
struct Block_800F8A88 {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

/* View of the block at player +336 used by fn_800F930C. */
struct Block_800F930C {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
};

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
int fn_80178320(void);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
unsigned char fn_800FC0C4(Object_80039F5C *p);
int fn_80168E00(int team, int index, unsigned char *pOut);
void *fn_8011F4EC(void);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
extern float lbl_803EAE60;
}

extern "C" int fn_800F930C(Object_80039F5C *p) {
    Block_800F930C *pBlock = (Block_800F930C *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mRef);

    if (pOther) {
        Vector_80039F5C delta;

        fn_802276B4(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (fabsf(delta.mX) <= 4.0f && delta.mY <= -3.0f && pBlock->mUnknown16 <= 60) {
            if (delta.mX > 0.0f) {
                pBlock->mUnknown8 = 0x100000;
            } else {
                pBlock->mUnknown8 = 0x700000;
            }
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.33f;
            return 1;
        }
    }
    return 0;
}

extern "C" Object_80039F5C *fn_800F9480(Object_80039F5C *p) {
    int ref = 0;
    float best = -1000.0f;
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Point_8017886C origin;
    Block_800FAD2C *pBlock;
    int n;
    int i;

    origin = fn_80177FE0();
    pBlock = (Block_800FAD2C *)fn_8011F4EC();
    n = fn_80178D18(p->mIdBytes[2]);
    for (i = 0; i <= 2; i++) {
        Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, pBlock->mUnknown415[i]);

        if (pOther->mUnknown1032 == 0 && fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX) < 20.0f) {
            unsigned int count = 0;
            int j;

            for (j = 0; j < n; j++) {
                int valid = 1;
                Object_80039F5C *pMate = fn_80039F5C(p->mIdBytes[2], j);
                int slot = fn_800F06F4(0, pMate->mpState, 22, 0xFFFF);

                if (slot != 0xFFFF) {
                    if (pMate->mpState[slot].mId == 22) {
                        ref = pMate->mUnknown336;
                    } else {
                        State_80039F5C *pState = &pOther->mpState[slot];

                        if (pState->mUnknown1 >= 1 && pState->mUnknown1 <= 5) {
                            fn_80039F5C(p->mIdBytes[2] ^ 1, pRecord->mUnknown8[pState->mUnknown1 - 1]);
                            fn_8009BD2C(pOther, &ref);
                        } else {
                            valid = 0;
                        }
                    }
                    if (valid && pOther->mId == ref) {
                        count++;
                    }
                }
            }
            if (count <= 1) {
                float score = (pOther->mMotion.mPos.mY - origin.mY) * 1.5f
                            - fabsf(pOther->mMotion.mPos.mX - p->mMotion.mPos.mX);

                if (score > best) {
                    best = score;
                    pResult = pOther;
                }
            }
        }
    }
    return pResult;
}

extern "C" Object_80039F5C *fn_800F9688(Object_80039F5C *p) {
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    int n = fn_80178D18(p->mIdBytes[2]);
    int i;

    for (i = 0; i <= 2; i++) {
        Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, pRecord->mUnknown8[i]);

        if (pOther->mUnknown1032 == 0 && fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX) < 10.0f) {
            int count = 0;
            int j;

            for (j = 0; j < n; j++) {
                Object_80039F5C *pMate = fn_80039F5C(p->mIdBytes[2], j);
                int index = fn_800F06F4(0, pMate->mpState, 22, 0xFFFF);

                if (index != 0xFFFF && pMate->mpState[index].mUnknown1 == i + 1) {
                    count++;
                }
            }
            if (count == 0) {
                pResult = pOther;
            }
        }
    }
    return pResult;
}

extern "C" int fn_800F9CB4(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char ahead = 0;
    unsigned char behind = 0;
    unsigned char aheadKind3 = 0;
    int team = fn_80178308();
    unsigned char behindKind3 = 0;
    Point_8017886C origin;
    int aheadKind4 = 0;
    int behindKind4 = 0;
    unsigned char i;

    origin = fn_80177FE0();
    for (i = 0; i <= 2; i++) {
        Object_80039F5C *pOther = fn_80039F5C(team, pRecord->mUnknown8[i]);
        float x = pOther->mMotion.mPos.mX;
        unsigned char kind = pOther->mUnknown2914;

        if (fabsf(x - origin.mX) > 1.0f) {
            if (x > origin.mX) {
                if (kind == 4) {
                    aheadKind4 = 1;
                } else if (kind == 3) {
                    aheadKind3++;
                }
                ahead++;
            } else {
                if (kind == 4) {
                    behindKind4 = 1;
                } else if (kind == 3) {
                    behindKind3++;
                }
                behind++;
            }
        }
    }
    if (behind > ahead) {
        return 0;
    }
    if (ahead > behind) {
        return 1;
    }
    if (behindKind3 > aheadKind3) {
        return 0;
    }
    if (aheadKind3 > behindKind3) {
        return 1;
    }
    if (aheadKind4 && !behindKind4) {
        return 1;
    }
    if (behindKind4 && !aheadKind4) {
        return 0;
    }
    return origin.mX >= 0.0f;
}

extern "C" Object_80039F5C *fn_800F9E3C(Object_80039F5C *p, int flag) {
    Object_80039F5C *pResult = 0;
    int team = fn_80178308();
    unsigned char i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i <= 2; i++) {
        unsigned char valid;
        int index = fn_80168E00(team, i, &valid);

        if (valid && index != 0xFF) {
            Object_80039F5C *pTarget = fn_80039F5C(team, index);
            unsigned char kind = pTarget->mUnknown2914;

            if (((kind == 1 || kind == 2) && !flag) || kind == 4) {
                int count = 0;
                unsigned char j;

                for (j = 0; j < n; j++) {
                    Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), j);
                    int slot = fn_800F06F4(0, pOther->mpState, 22, 0xFFFF);

                    if (slot != 0xFFFF && pOther->mpState[slot].mUnknown1 == fn_800FC0C4(pTarget)) {
                        count++;
                        if (fabsf(pOther->mMotion.mPos.mX - pTarget->mMotion.mPos.mX) > 5.5f
                            && fabsf(p->mMotion.mPos.mX - pTarget->mMotion.mPos.mX) < 5.0f) {
                            p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                            pResult = pTarget;
                            break;
                        }
                    }
                }
                if (count == 0 && fabsf(p->mMotion.mPos.mX - pTarget->mMotion.mPos.mX) < lbl_803EAE60) {
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    pResult = pTarget;
                }
            }
        }
    }
    return pResult;
}

extern "C" int fn_800FA0DC(Object_80039F5C *p) {
    unsigned char slot = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
    Object_80039F5C *pTarget;

    pBlock->mUnknown24 = slot;
    if (pRecord->mUnknown4) {
        slot = pRecord->mUnknown32[p->mIdBytes[1]];
        if (slot == 0xFF) {
            slot = 0xFD;
        }
    } else {
        slot = p->mpState->mUnknown1;
    }
    if (slot == 0xFE) {
        Message_800F01CC message;

        fn_801C1F94(&message, 0, 4);
        message.mId = 85;
        message.mUnknown1[0] = 48;
        fn_800F00D4(0, p->mpState, &message, p);
        return 1;
    }
    if (slot == 0xFD) {
        Message_800F01CC message;

        fn_801C1F94(&message, 0, 4);
        message.mId = 2;
        fn_800F00D4(0, p->mpState, &message, p);
        return 1;
    }
    if (slot) {
        pTarget = fn_80039F5C(fn_80178308(), pRecord->mUnknown8[slot - 1]);
        p->mpState->mUnknown1 = slot;
        if (pTarget->mUnknown2914 == 3 && p->mpState->mUnknown3[0] == 0) {
            float distance = fabsf(p->mMotion.mPos.mX - pTarget->mMotion.mPos.mX);

            if (distance < 3.5f) {
                p->mpState->mUnknown3[0] = 2;
            } else if (distance < 5.5f) {
                p->mpState->mUnknown3[0] = 1;
            }
        }
    } else {
        pTarget = 0;
    }
    fn_8009BD2C(pTarget, &pBlock->mRef);
    pBlock->mUnknown22 = p->mpState->mUnknown3[0];
    pBlock->mUnknown23 = 1;
    pBlock->mUnknown25 = p->mpState->mUnknown2 & 2;
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown4 = p->mMotion.mFacing;
    pBlock->mUnknown8 = p->mMotion.mFacing;
    pBlock->mUnknown12 = 0.0f;
    pBlock->mUnknown26 = 7;
    pBlock->mUnknown27 = fn_802372EC(0, 20) + 20;
    pBlock->mUnknown21 = 0;
    pBlock->mUnknown16 = 0;
    if (fn_8011F4E0()->mUnknown0 < 0) {
        pBlock->mUnknown16 = 1;
    }
    if (p->mFlags & 0x4000) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.0f;
    }
    return 0;
}
