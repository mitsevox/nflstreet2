#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802270D4.h"

/* View of the block at player +336 used by fn_800F8D2C and fn_800F9024. */
struct Block_800F8D2C {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
};

extern "C" {
int fn_8012CAB4(Object_80039F5C *p);
int fn_801CFFD0(int a, int b);
int fn_8009E9A4(void);
float fn_80178A2C(void);
extern float lbl_803EAE2C;
extern float lbl_803EAE4C;
extern float lbl_803EAE50;
extern float lbl_803EAE54;
}

extern "C" int fn_800F8D2C(Object_80039F5C *p) {
    Block_800F8D2C *pBlock = (Block_800F8D2C *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mRef);

    if (pOther) {
        Vector_80039F5C delta;
        int angle;
        int side;
        int direction;

        fn_802276B4(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (delta.mY > -2.5f) {
            return 0;
        }
        pBlock->mUnknown12 = 0.5f;
        if (pOther->mpState->mId == 20) {
            angle = fn_8012CAB4(pOther);
        } else if ((unsigned char)(pOther->mpState->mId - 51) <= 1) {
            angle = pOther->mMotion.mFacing;
        } else {
            angle = pOther->mMotion.mUnknown32;
        }
        if (angle > 0x800000) {
            angle = 0x1000000 - angle;
        }
        if (delta.mX < -2.0f) {
            side = 0;
            direction = 0x700000;
        } else if (delta.mX > 2.0f) {
            side = 1;
            direction = 0x100000;
        } else {
            side = 2;
            if (fn_801CFFD0(angle, 0x400000) <= 0xAAAAA) {
                direction = 0x400000;
                if (delta.mY < -6.0f) {
                    pBlock->mUnknown12 = 0.0f;
                }
            } else {
                direction = 0x700000;
                if (angle < 0x400000) {
                    direction = 0x100000;
                }
            }
        }
        if (p->mMotion.mPos.mY < fn_80177FE0().mY + 8.0f) {
            if (side == 2) {
                if (fn_801CFFD0(angle, 0x400000) <= 0x11C71B) {
                    pBlock->mUnknown22 = side;
                    return 1;
                }
                if (pBlock->mUnknown16 > 60) {
                    return 0;
                }
            } else if (side == 1 ? angle < 0x400000 : angle > 0x400000) {
                if (pBlock->mUnknown16 > 30) {
                    return 0;
                }
            } else if (fn_801CFFD0(angle, 0x400000) > 0x11C71B) {
                if (fabsf(delta.mX) < 2.0f) {
                    pBlock->mUnknown12 = 0.0f;
                }
                if (pBlock->mUnknown16 > 45) {
                    return 0;
                }
            } else {
                if (fabsf(delta.mX) < 1.0f) {
                    pBlock->mUnknown12 = 0.0f;
                }
                if (delta.mY > -5.0f) {
                    pBlock->mUnknown22 = 2;
                    return 1;
                }
            }
        } else {
            if (delta.mY < -9.0f) {
                return 0;
            }
            if ((fn_801CFFD0(angle, 0x400000) > 0x200000 || side != 2) && pBlock->mUnknown16 > 30) {
                return 0;
            }
        }
        pBlock->mUnknown8 = direction;
        pBlock->mUnknown4 = 0xC00000;
        return 1;
    }
    return 0;
}

extern "C" int fn_800F9024(Object_80039F5C *p) {
    Block_800F8D2C *pBlock = (Block_800F8D2C *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mRef);

    if (pOther) {
        Vector_80039F5C delta;
        Vector_80039F5C ball;
        int angle;
        float limit;
        float t;

        fn_802276B4(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (pOther->mpState->mId == 20) {
            angle = fn_8012CAB4(pOther);
            if (angle > 0x800000) {
                return 0;
            }
        } else {
            if ((unsigned char)(pOther->mpState->mId - 51) <= 1) {
                angle = pOther->mMotion.mFacing;
            } else {
                angle = pOther->mMotion.mUnknown32;
            }
            if (angle > 0x800000) {
                angle = 0x1000000 - angle;
            }
        }
        if (fn_801CFFD0(angle, 0x400000) > 0x1C71C7) {
            return 0;
        }
        delta.mX = pOther->mMotion.mUnknown40 * lbl_803EAE54 + delta.mX;
        if (fabsf(delta.mX) > lbl_803EAE2C) {
            return 0;
        }
        if ((p->mpState->mUnknown2 & 2) == 0) {
            limit = -2.0f;
        } else {
            limit = -1.0f;
        }
        if (delta.mY > limit) {
            return 0;
        }
        if (delta.mY < -7.0f && fn_8009E9A4() != 1) {
            return 0;
        }
        fn_80137D58(fn_801374BC(), &ball);
        if ((p->mpState->mUnknown2 & 1) == 0) {
            if (pOther->mMotion.mPos.mX > ball.mX) {
                float lo = pOther->mMotion.mPos.mX - lbl_803EAE50;

                if (p->mMotion.mPos.mX > lo) {
                    t = (p->mMotion.mPos.mX - lo) / (lbl_803EAE50 + lbl_803EAE2C);
                } else {
                    t = -((lo - p->mMotion.mPos.mX) / (lbl_803EAE2C - lbl_803EAE50));
                }
            } else {
                float hi = pOther->mMotion.mPos.mX + lbl_803EAE50;

                if (p->mMotion.mPos.mX < hi) {
                    t = -((hi - p->mMotion.mPos.mX) / (lbl_803EAE50 + lbl_803EAE2C));
                } else {
                    t = (p->mMotion.mPos.mX - hi) / (lbl_803EAE2C - lbl_803EAE50);
                }
            }
        } else {
            if (pOther->mMotion.mPos.mX > ball.mX) {
                float hi = pOther->mMotion.mPos.mX + lbl_803EAE50;

                if (p->mMotion.mPos.mX < hi) {
                    t = (hi - p->mMotion.mPos.mX) / (lbl_803EAE50 + lbl_803EAE2C);
                } else {
                    t = -((p->mMotion.mPos.mX - hi) / (lbl_803EAE2C - lbl_803EAE50));
                }
            } else {
                float lo = pOther->mMotion.mPos.mX - lbl_803EAE50;

                if (p->mMotion.mPos.mX > lo) {
                    t = (p->mMotion.mPos.mX - lo) / (lbl_803EAE50 + lbl_803EAE2C);
                } else {
                    t = -((lo - p->mMotion.mPos.mX) / (lbl_803EAE2C - lbl_803EAE50));
                }
            }
        }
        t = t < -1.0f ? -1.0f : (t > 1.0f ? 1.0f : t);
        if (t > 0.0f) {
            t = 1.0f - t;
        } else {
            t = -1.0f + t;
        }
        pBlock->mUnknown8 = (int)((t * lbl_803EAE4C + 90.0f) * 46603.38f);
        fn_80178A2C();
        pBlock->mUnknown4 = 0xC00000;
        pBlock->mUnknown12 = 0.5f;
        return 1;
    }
    return 0;
}
