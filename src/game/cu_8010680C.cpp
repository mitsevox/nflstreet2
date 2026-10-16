#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Class_80297CE8.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"

struct Block_800F4A74 {
    char mUnknown0[20];
    int mUnknown20;
    int mUnknown24;
    float mUnknown28;
    float mUnknown32;
    int mUnknown36;
    int mUnknown40;
    float mUnknown44;
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    short mUnknown58;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    unsigned char mUnknown64;
    char mUnknown65[23];
};

/* Object pointer, three positions, a pair and a float filled by fn_800F39FC
   and passed to fn_800F2EC8, fn_800F30AC, fn_800F3284, fn_800F3838,
   fn_800F3A6C, fn_800F3B54, fn_800F3D38, fn_800F3F90 and fn_800F4038. Only
   the accessed prefix is declared; the size is unknown. */
struct Points_800F3A6C {
    Object_80137ABC *mpUnknown0;
    Vector_80039F5C mUnknown4;
    Vector_80039F5C mUnknown16;
    Vector_80039F5C mUnknown28;
    Point_8017886C mUnknown40;
    float mUnknown48;
};

/* View of another player's +336 block read by fn_800F3344 while that player
   is in state 28. Only the accessed prefix is declared; the size is unknown. */
struct Block_800F3344 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
};
extern "C" {
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
extern float lbl_803ECB08;
extern const float lbl_803ED6CC;
unsigned int fn_80178D18(int team);
int fn_801BA5A8(void *pA, void *pB, unsigned short id, int index);
int fn_801BA568(void *pA, void *pB, int id);
int fn_801BA5A8(void *pA, void *pB, unsigned short id, int index);
int fn_801BA2A8(void *a, void *b, unsigned short c, unsigned short d, unsigned short e, void *p, float f);
extern const float lbl_803ED6CC;
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
void fn_8013AA00(Object_80137ABC *pBall, float height, float *pTime, Vector_80039F5C *pLanding);
}

extern "C" float fn_801BD690(Block_801BD6D4 *p, int key);

struct Turn_8010680C {
    int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

extern "C" int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);

extern "C" Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);

extern "C" int fn_8010680C(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int phase) {
    Turn_8010680C *pTurn = (Turn_8010680C *)fn_801BE60C(p->mpUnknown792, key);

    switch (phase) {
    case 0: {
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        int facing;

        if (index >= 0) {
            p->mFlags &= ~4;
            pTurn->mUnknown8 = fn_801BA2A8(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                                           pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        }
        facing = p->mUnknown512.mUnknown8;
        if (fn_801CFFD0(facing, p->mMotion.mFacing) > 0xB60B) {
            fn_801BE760(p->mpUnknown792, key, 1);
            if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 204)) {
                int entry;

                pEntries = p->mpUnknown800;
                entry = fn_801BA5A8(p->mpUnknown796, pEntries, 204, 0);

                pTurn->mUnknown4 = pEntries[entry].mUnknown48;
                if (pTurn->mUnknown4 != 0.0f ||
                    (pTurn->mUnknown4 = fn_801BD690(&pEntries[entry].mUnknown4C, 0xC003)) != 0.0f) {
                    pTurn->mUnknown4 = pTurn->mUnknown4 > 50.0f ? 50.0f : pTurn->mUnknown4;
                    pTurn->mUnknown0 = (int)(fn_801CFFD0(facing, p->mMotion.mFacing) / pTurn->mUnknown4);
                    if (((p->mMotion.mFacing - facing) & 0xFFFFFF) <= 0x7FFFFF) {
                        pTurn->mUnknown0 = -pTurn->mUnknown0;
                    }
                    /* The shipped code discards the rate it just computed. */
                    pTurn->mUnknown0 = 0;
                }
            }
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (pTurn->mUnknown4 > 0.0f) {
            pTurn->mUnknown4 -= 1.0f;
            p->mMotion.mFacing += pTurn->mUnknown0;
            p->mpUnknown800[pTurn->mUnknown8].mUnknownC += pTurn->mUnknown0;
        }
        break;
    }
    return 0;
}

extern "C" void fn_80106A60(Object_80039F5C *p) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Object_80137ABC *pBall = fn_80137ABC(pBlock->mUnknown64);
    Object_80039F5C *pCarrier;
    Vector_80039F5C pos;
    Vector_80039F5C landing;
    Point_8017886C delta;
    int heading;
    int angle;
    int diff;

    fn_80137D58(pBall, &pos);
    fn_80138064(pBall, &landing);
    fn_80227690(&delta, &landing, &pos);
    heading = fn_801CFE40(delta.mY, delta.mX);
    pCarrier = fn_80137B88(pBall);
    if (pCarrier != 0) {
        fn_80227690(&delta, &landing, &pCarrier->mMotion.mPos);
        if (fn_802270A4(&delta) > 2.0f) {
            angle = fn_801CFE40(delta.mY, delta.mX);
            diff = fn_801CFFD0(heading, angle);
            if (diff <= 0x1FFFFF) {
                pBlock->mUnknown24 = 0;
            } else if (diff > 0x600000) {
                pBlock->mUnknown24 = 1;
            } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
                pBlock->mUnknown24 = 2;
            } else {
                pBlock->mUnknown24 = 3;
            }
        } else {
            pBlock->mUnknown24 = 4;
        }
    } else {
        pBlock->mUnknown24 = 1;
    }
    fn_80227690(&delta, &landing, &p->mMotion.mPos);
    if (fn_802270A4(&delta) > 2.0f) {
        angle = fn_801CFE40(delta.mY, delta.mX);
        diff = fn_801CFFD0(heading, angle);
        if (diff <= 0x1FFFFF) {
            pBlock->mUnknown20 = 0;
        } else if (diff > 0x600000) {
            pBlock->mUnknown20 = 1;
        } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
            pBlock->mUnknown20 = 2;
        } else {
            pBlock->mUnknown20 = 3;
        }
    } else {
        pBlock->mUnknown20 = 4;
    }
}

extern "C" void fn_80106C24(Object_80039F5C *p, Block_800F4A74 *pBlock) {
    Object_80137ABC *pBall = fn_80137ABC(pBlock->mUnknown64);
    Object_80039F5C *pOther = fn_80137B88(pBall);
    int result = pBlock->mUnknown49;
    Vector_80039F5C start;
    Vector_80039F5C target;
    Vector_80039F5C velocity;
    Point_8017886C delta;
    Point_8017886C apart;
    Point_8017886C ahead;
    float ballTime;
    float otherTime;
    float time;
    float distance;

    fn_80138064(pBall, &start);
    fn_80137D58(pBall, &target);
    fn_80137EC4(pBall, &velocity);
    fn_80227690(&delta, &start, &target);
    ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
    if (pOther != 0) {
        fn_80227690(&delta, &start, &pOther->mMotion.mPos);
        otherTime = fn_802270A4(&delta)
            / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &start, &p->mMotion.mPos);
        time = fn_802270A4(&delta) / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        distance = fn_802270A4(&delta);
        fn_80227690(&apart, &p->mMotion.mPos, &pOther->mMotion.mPos);
        fn_80227690(&ahead, &target, &pOther->mMotion.mPos);
        if (pOther->mpState->mId == 28 && fn_80137B40() != pOther) {
            Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

            if (pPass->mUnknown0 < pPass->mUnknown16) {
                otherTime = pPass->mUnknown16 - pPass->mUnknown0;
                fn_80227690(&delta, &pPass->mUnknown4, &target);
                ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
                fn_80227690(&delta, &pPass->mUnknown4, &p->mMotion.mPos);
                time = fn_802270A4(&delta)
                    / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            }
        }
        switch (pBlock->mUnknown20) {
        case 0:
            if (ballTime > time - 5.0f) {
                switch (pBlock->mUnknown24) {
                case 0:
                    if (time < otherTime) {
                        if ((time > 20.0f
                             && fn_801CFFD0(fn_801CFE40(ahead.mY, ahead.mX), fn_801CFE40(apart.mY, apart.mX)) <= 0x71C71B)
                            || (fn_801CFFD0(pOther->mMotion.mUnknown32, 0) <= 0x11C71B
                                && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX)
                            || (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x800000) <= 0x11C71B
                                && p->mMotion.mPos.mX < pOther->mMotion.mPos.mX)
                            || p->mMotion.mPos.mY < pOther->mMotion.mPos.mY) {
                            result = 2;
                        } else {
                            result = 3;
                        }
                    } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f || pBlock->mUnknown49 == 3) {
                        result = 3;
                    } else {
                        result = 2;
                    }
                    break;
                case 2:
                case 3:
                    result = 0;
                    if (pBlock->mUnknown54 == 1) {
                        result = 3;
                    }
                    break;
                case 1:
                case 4:
                    result = 3;
                    if (pBlock->mUnknown56 <= 79) {
                        result = 0;
                    }
                    break;
                }
            } else {
                if (time < otherTime && pBlock->mUnknown51 != 1 && pOther->mpState->mId != 28) {
                    result = 0;
                } else if (pOther->mpState->mId == 28 && (pBlock->mUnknown50 == 3 || pBlock->mUnknown49 == 3)) {
                    result = 3;
                } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f || pBlock->mUnknown49 == 3) {
                    result = 3;
                } else {
                    result = 2;
                }
            }
            break;
        case 1:
            switch (pBlock->mUnknown24) {
            case 0:
            case 4:
                result = 3;
                break;
            case 2:
            case 3:
                result = 3;
                if (time < otherTime && pBlock->mUnknown54 == 0) {
                    result = 0;
                }
                break;
            case 1:
                result = 3;
                if (time < otherTime && pBlock->mUnknown54 == 0) {
                    result = 0;
                }
                break;
            }
            break;
        case 4:
            switch (pBlock->mUnknown24) {
            case 0:
                result = 3;
                break;
            case 1:
                result = 0;
                break;
            case 2:
            case 3:
                result = 0;
                if (pBlock->mUnknown54 != 0) {
                    result = 3;
                }
                break;
            case 4:
                result = 2;
                break;
            }
            break;
        case 2:
        case 3:
            switch (pBlock->mUnknown24) {
            case 0:
                {
                    int angle = fn_801CFE40(velocity.mY, velocity.mX);

                    if ((fn_801CFFD0(angle, pOther->mMotion.mUnknown32) <= 0x3FFFFF
                         && fn_801CFFD0(angle, p->mMotion.mUnknown32) > 0x400000 && distance > 2.0f)
                        || (pBlock->mUnknown49 == 0 && velocity.mZ < 0.0f)) {
                        result = pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY ? 2 : 0;
                    } else {
                        result = 3;
                        if (time < ballTime && pBlock->mUnknown56 <= 49) {
                            result = 2;
                        }
                    }
                }
                break;
            case 2:
            case 3:
                if (ballTime > time - 5.0f || distance < 5.0f) {
                    if (pBlock->mUnknown24 == pBlock->mUnknown20) {
                        if (pBlock->mUnknown54 == 0) {
                            result = 2;
                        } else {
                            result = 3;
                        }
                    } else {
                        result = 3;
                        if (time < otherTime) {
                            result = 2;
                        }
                    }
                } else {
                    result = 1;
                }
                break;
            case 4:
                result = 3;
                break;
            case 1:
                result = 3;
                if (time < otherTime) {
                    result = 0;
                }
                break;
            }
            break;
        }
    }
    if (pOther != 0 && result == 3) {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pMate = fn_80039F5C(p->mIdBytes[2], i);

            if (pMate != p) {
                Point_8017886C gap;
                Block_800F4A74 *pMateBlock;

                fn_80227690(&gap, &pOther->mMotion.mPos, &pMate->mMotion.mPos);
                pMateBlock = (Block_800F4A74 *)&pMate->mUnknown336;
                if (pMateBlock->mUnknown49 == 3
                    && pMate->mMotion.mPos.mY > p->mMotion.mPos.mY && fn_802270A4(&gap) < 4.5f) {
                    result = 2;
                    break;
                }
            }
        }
    }
    if (pOther != 0 && result == 2 && p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pMate = fn_80039F5C(p->mIdBytes[2], i);
            Object_80039F5C *pMark = fn_800FB9D4(pOther);

            if (pMate != p) {
                Point_8017886C gap;
                Block_800F4A74 *pMateBlock;

                fn_80227690(&gap, &pOther->mMotion.mPos, &pMate->mMotion.mPos);
                pMateBlock = (Block_800F4A74 *)&pMate->mUnknown336;
                if (pMateBlock->mUnknown49 == 2 && pMate->mMotion.mPos.mY < p->mMotion.mPos.mY
                    && fn_802270A4(&gap) < 3.5f) {
                    result = 3;
                    break;
                }
                if (pMark == pMate && pMate->mMotion.mPos.mY < p->mMotion.mPos.mY && fn_802270A4(&gap) < 3.5f) {
                    result = 3;
                    break;
                }
            }
        }
    }
    if (pOther != 0 && otherTime > ballTime + 5.0f) {
        result = 0;
    }
    if (result != pBlock->mUnknown49) {
        pBlock->mUnknown50 = pBlock->mUnknown49;
        pBlock->mUnknown49 = result;
    }
}

extern "C" void fn_801074B4(Object_80039F5C *p, Points_800F3A6C *pInfo) {
    Object_800B26B0 *pMotion;
    Point_8017886C delta;
    int angle;
    float distance;
    float strength;
    Object_80039F5C *pOther = fn_80137B88(pInfo->mpUnknown0);

    if (pOther == 0) {
        return;
    }
    pMotion = &p->mMotion;
    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    distance = fn_802270A4(&delta);
    if (fn_801CFFD0(angle, pMotion->mFacing) > 0x555554 && distance >= 3.5f) {
        return;
    }
    strength = 0.0f;
    if (pMotion->mPos.mY > pOther->mMotion.mPos.mY) {
        if (distance < 8.0f) {
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            strength = distance / 8.0f;
            strength = 1.0f - strength;
        }
        if (fn_801CFFD0(pMotion->mFacing, 0x400000) <= 0x1FFFFF && fn_8013BA58(pInfo->mpUnknown0, 0) == 4) {
            fn_80227690(&delta, &pInfo->mUnknown16, &pMotion->mPos);
            angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        }
    } else if (distance < 2.5f) {
        distance -= 1.0f;
        if (distance < 0.0f) {
            distance = 0.0f;
        }
        strength = distance / 2.5f;
        strength = 1.0f - strength;
    }
    if (strength != 0.0f) {
        fn_800C89F0(p, angle, 2, 0, strength);
    }
}

extern "C" void fn_80107680(Points_800F3A6C *pInfo, int index) {
    pInfo->mpUnknown0 = fn_80137ABC(index);
    fn_80138064(pInfo->mpUnknown0, &pInfo->mUnknown4);
    fn_8013AA00(pInfo->mpUnknown0, 1.5f, &pInfo->mUnknown48, (Vector_80039F5C *)&pInfo->mUnknown40);
    fn_80137EC4(pInfo->mpUnknown0, &pInfo->mUnknown28);
    fn_80137D58(pInfo->mpUnknown0, &pInfo->mUnknown16);
}
