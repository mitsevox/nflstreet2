#include "game/Step_800C4460.h"
#include "game/Block_8030E6E8.h"
#include "game/Record_800A0624.h"
#include "game/Command_800CEE74.h"
#include "game/Record_803EA558.h"
#include "game/Level_80054130.h"
#include "game/cu_80142BB4.h"
#include "game/Object_800EA284.h"
#include "game/Object_8017886C.h"
#include "game/fn_8022781C.h"
#include "game/Block_800C9D6C.h"
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/fn_8009D990.h"
#include "engine/vptmanager.h"
#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/Class_80297BF8.h"
#include "game/Entry_800B206C.h"
#include "game/Entry_80219044.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_803EC99C.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Input_800B6D34.h"
#include "game/ModuleGroup_80033A5C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/RecordList_8002E7C0.h"
#include "game/Record_800B15FC.h"
#include "game/Table_80089904.h"
#include "game/Team_80167A8C.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80041210.h"
#include "game/cu_8003108C.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/Block_801BE60C.h"
#include "game/Record_8011F518.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8008E978.h"
#include "game/fn_8007F828.h"
#include "game/fn_800670B4.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_80195EFC.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801C3284.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"
#include "game/fn_80054138.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_802372EC.h"
#include "game/fn_80218FC4.h"
#include "game/fn_802270D4.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/fn_80094488.h"
#include "game/cu_80164568.h"
#include "game/Entry_802F394C.h"

extern "C" {
void fn_8006F0B8(int kind);
int fn_8009A578(int handle);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009B0CC(int team, int value);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
int fn_800A7F30(int team);
int fn_800A8444(int team);
int fn_800A851C(int team, Object_80039F5C *p);
void fn_800A8954(int event, int team, Object_80039F5C *p);
int fn_800AC584(int team, int value);
int fn_800ACA70(int team, int value);
int fn_800C4E30(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800C4EE8(Object_80039F5C *p, Object_80039F5C *pOther, int roll, int chance);
void fn_800C51DC(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800C5234(Query_800CE770 *pQuery, Object_80039F5C *pTarget);
int fn_800C53D8(Object_80039F5C *p);
void fn_800C561C(Object_80039F5C *p, int value);
void fn_800C5B20(Object_80039F5C *p, int value);
int fn_800C5BF0(Object_80039F5C *p, int value);
void fn_800C5F80(Object_80039F5C *p, int value, int *pA, int *pB, int *pC);
int fn_800C6640(Object_80039F5C *p, Object_800C6640 *pSource, Object_80039F5C *pOther, int value, int chance);
int fn_800C6738(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800C68B8(Object_80039F5C *p, Object_80039F5C *pOther, int value);
int fn_800C68BC(Object_800C6640 *pSource, int value);
int fn_800C7084(Object_80039F5C *p, Object_80039F5C *pOther, int a, float value, int b);
int fn_800C769C(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800C76D8(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b);
void fn_800C7708(Object_80039F5C *p);
int fn_800C7720(Object_80039F5C *pOther, Object_80039F5C *p);
int fn_800C8420(Object_80039F5C *p, float value);
void fn_800C8688(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b);
int fn_800CA5CC(Object_80039F5C *p, int kind, int apply);
float fn_800CA9B4(int kind, Object_80039F5C *p);
int fn_800CAA6C(int value);
int fn_800CD2B4(int kind, Object_80039F5C *p);
int fn_800CD35C(int mode, Object_80039F5C *p);
int fn_800CE438(Query_800CE770 *pQuery);
int fn_800CF090(Object_80039F5C *p);
int fn_800D0B90(Object_80039F5C *p);
void fn_800D4748(Object_80039F5C *p);
void fn_800D4FBC(Object_80039F5C *p, int flag);
void fn_800D60BC(Object_80039F5C *p, int kind, unsigned char flag);
int fn_800E1554(Object_80039F5C *p);
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800EC640(Object_80039F5C *p);
int fn_801045BC(Object_80039F5C *p);
int fn_80104610(Object_80039F5C *p);
int fn_8010CE2C(Object_80039F5C *p);
void fn_80111354(Object_80039F5C *p);
int fn_80114A30(Object_80039F5C *p, int a);
int fn_80114DE0(Object_80039F5C *p);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
int fn_8011E9B4(Object_80039F5C *p);
int fn_8011F1CC(void);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **ppBlocker);
int fn_801486A0(void);
void fn_80156C78(int id, int value);
float fn_8016B938(void);
float fn_8016B974(void);
void fn_8016F6F4(Object_80039F5C *p, int *pValue);
void fn_801718E8(Object_80039F5C *p, Object_80039F5C *pTackler);
int fn_80177C38(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801783AC(int bit);
void fn_80178718(Object_80039F5C *p);
int fn_801787A0(void);
float fn_80178A08(void);
float fn_80178A2C(void);
Block_801BE60C *fn_801BE60C(void *p, unsigned short key);
int fn_801BE648(void *p);
void fn_801BE67C(void *pA, void *pB, void *pC, Object_80039F5C *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227890(void *, void *);
extern Object_80039F5C *lbl_80317AD8[7];
extern float lbl_803EABF4;
extern unsigned int lbl_803EABF8;
extern float lbl_803EAC0C;
extern float lbl_803EAC10;
extern float lbl_803EAC14;
extern float lbl_803EAC18;
extern float lbl_803EAC1C;
extern float lbl_803EAC20;
extern float lbl_803EAC24;
extern float lbl_803EAC28;
extern float lbl_803ECB08;
extern float lbl_803ED6B4;
extern float lbl_803ED6BC;
}

extern "C" int fn_800C52C8(Object_80039F5C *p, Object_80039F5C *pOther, int value, int useModifier)
{
    int rating;
    float scale;

    rating = p->mRatings[2] < 0 ? 0 : (p->mRatings[2] > 255 ? 255 : p->mRatings[2]);
    scale = rating * 0.00078431377f + 0.05f;
    scale = scale < 0.05f ? 0.05f : (scale > 0.25f ? 0.25f : scale);
    if (useModifier) {
        scale *= fn_800CA9B4(5, p);
    }
    return value * scale;
}

extern "C" int fn_800C5418(Object_80039F5C *p, Object_80039F5C *pOther, int value)
{
    Block_8011E240 *pBlock;
    Point_8017886C delta;
    int angle;
    int reduction;

    switch (pOther->mpState->mId) {
    case 28:
        if (fn_801BE648(p->mpUnknown792) == 225) {
            value = value * 0.5f;
        }
        break;
    case 12:
        value += value >> 5;
        break;
    case 10:
        value >>= 1;
        break;
    }
    if (pOther->mMotion.mPos.mZ > 0.0f) {
        value -= value >> 2;
    }
    pBlock = &pOther->mBlock1032;
    if (pBlock->mUnknown0 == 4) {
        value -= value >> 2;
        fn_8009BCE8(&pBlock->mUnknown4);
        if (pBlock->mUnknown95[1] == 0 || pBlock->mUnknown95[0] == 0) {
            value >>= 1;
        }
    }
    if (fn_800E1554(pOther)) {
        value = 100;
    }
    reduction = 0;
    if (value > 0) {
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        switch (p->mUnknown528.mUnknown15) {
        case 6:
        case 7:
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                reduction = fn_800C52C8(p, pOther, value, 0);
            }
            break;
        case 8:
        case 9:
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) < 0x800000) {
                reduction = fn_800C52C8(p, pOther, value, 0);
            }
            break;
        default:
            switch (p->mpState->mId) {
            case 35:
                reduction = value >> 2;
                break;
            case 34:
                reduction = value >> 3;
                break;
            }
            break;
        }
        reduction = fn_800ACA70(p->mIdBytes[2], reduction);
    }
    return value - reduction;
}

extern "C" void fn_800C56C0(Object_80039F5C *p, int value, int chance)
{
    Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
    int contactApplied = 0;
    int mode = 12;
    int fromBehind = 0;
    int stripped = 0;
    int canStrip;
    int canKnock;
    Point_8017886C delta;
    int angle;
    int stripChance;
    int knockChance;
    int roll;
    Record_800B15FC *pRecord;
    int ok;

    if (pOther != 0 && fn_800C5BF0(pOther, value)) {
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        canStrip = 0;
        canKnock = 0;
        angle = fn_801CFE40(delta.mY, delta.mX);
        switch (p->mUnknown528.mUnknown15) {
        case 6:
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                fromBehind = 1;
                canStrip = 1;
                canKnock = 1;
            }
            break;
        case 8:
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) < 0x800000) {
                fromBehind = 1;
                canStrip = 1;
                canKnock = 1;
            }
            break;
        }
        if (fn_800CAA6C(p->mUnknown528.mUnknown15)) {
            mode = 2;
        }
        if (canStrip || canKnock) {
            stripChance = p->mRatings[2] / 4 + p->mUnknown2904 * 0.25f;
            stripChance -= (int)(pOther->mRatings[5] / 4 + pOther->mUnknown2904 * 0.25f);
            stripChance += fn_802372EC(0, 100 - chance);
            if (stripChance > 50) {
                stripChance = 50;
            }
            if (mode == 2 && fromBehind) {
                stripChance = stripChance * fn_800CA9B4(5, p);
            }
            if (fn_800CA5CC(pOther, 9, 0)) {
                stripChance = stripChance * fn_800CA9B4(7, pOther);
            }
            if (fn_800C53D8(p)) {
                stripChance = lbl_803EAC0C * 100.0f;
            }
            knockChance = stripChance * 2 / 3;
            roll = fn_802372EC(0, 100);
            if (stripChance > 0 && stripChance > roll && canStrip && fn_800E96EC(pOther, p)) {
                fn_800C51DC(p, pOther);
                contactApplied = 1;
                stripped = 1;
                if (fn_800C53D8(p) == 0) {
                    pRecord = fn_800B15FC();
                    fn_8009BD2C(p, &pRecord->mUnknown0);
                    pRecord->mUnknownC = p->mMotion.mPos.mX;
                    pRecord->mUnknown10 = p->mMotion.mPos.mY;
                    pRecord->mUnknown14 = 38;
                    pRecord->mUnknown16 = 0;
                    fn_800B1508();
                }
                p->mUnknown1160.mUnknown44++;
                fn_800D4748(p);
                fn_800A8954(13, p->mIdBytes[2], p);
            }
            if (knockChance > 0 && knockChance > roll && canKnock && !stripped && fn_800C5BF0(pOther, value)) {
                if (!contactApplied) {
                    fn_800C51DC(p, pOther);
                    contactApplied = 1;
                }
                fn_80111354(pOther);
            }
        }
    }
    if (!stripped) {
        ok = 1;
        if (!fn_801486A0() && (pOther == 0 || fn_800F06F4(0, pOther->mpState, 51, 0xFFFF) != 0xFFFF)) {
            ok = 0;
        }
        if (ok) {
            fn_800C5B20(p, value);
            if (!contactApplied) {
                fn_800C51DC(p, pOther);
            }
        }
    }
    fn_800C8688(p, pOther, 0, 0);
}

extern "C" int fn_800C5BF0(Object_80039F5C *p, int value)
{
    State_80039F5C *pState = p->mpState;
    int result = 1;
    Vector_80039F5C pos;
    void *pKind;
    int handle;

    if (fn_8011E9B4(p) != 0) {
        result = 0;
    } else {
        switch (pState->mId) {
        case 28:
            fn_8009A5DC(pState->mUnknown1, pState->mUnknown2, &pKind, &handle);
            if (fn_8009A578(handle) == 5) {
                result = 0;
            }
            fn_8009BF5C(p, 0, &pos, 0);
            if (pos.mZ > 2.25f) {
                result = 0;
            }
            break;
        case 36:
            if (fn_801BE648(p->mpUnknown792) == 228) {
                fn_8009BF5C(p, 0, &pos, 0);
                if (pos.mZ > 1.75f) {
                    result = 0;
                }
            }
            break;
        case 12:
            if (fn_801BE648(p->mpUnknown792) == 237) {
                fn_8009BF5C(p, 0, &pos, 0);
                if (pos.mZ > 1.75f) {
                    result = 0;
                }
            } else {
                result = 0;
            }
            break;
        case 15:
            fn_8009BF5C(p, 0, &pos, 0);
            if (pos.mZ > 1.75f) {
                result = 0;
            }
            break;
        case 50:
            result = 0;
            break;
        case 16:
            if (fn_80114DE0(p) != 0) {
                break;
            }
            /* fall through */
        case 10:
        case 11:
        case 32:
            result = (p->mFlags & 0x80000) != 0;
            break;
        case 57:
            result = fn_800EC640(p);
            break;
        case 26:
            if (value == 7 || value == 24) {
                result = 0;
            } else {
                result = p->mUnknown344Word != 14;
            }
            break;
        case 25:
            if (value == 7 || value == 24) {
                result = 0;
            } else {
                result = fn_8011F518()->mUnknown4 != 8;
            }
            break;
        default:
            result = !(p->mFlags & 0x800);
            break;
        }
    }
    return result;
}

extern "C" int fn_800C5DE4(Object_80039F5C *p, Object_80039F5C *pOther)
{
    State_80039F5C *pState = p->mpState;
    int result = 1;
    Object_80039F5C *pBlocker = 0;

    switch (fn_801BE648(p->mpUnknown792)) {
    case 67:
    case 224:
    case 225:
    case 227:
        if (fn_80137B40() == 0) {
            result = 0;
        }
        break;
    }
    switch (pState->mId) {
    case 17:
        if (fn_80114E7C(pOther) != p) {
            result = 0;
        }
        break;
    case 10:
        if (fn_8009BCE8(&p->mUnknown560.mUnknown40) != pOther) {
            result = 0;
        }
        break;
    case 12:
    case 94:
        switch (fn_801BE648(pOther->mpUnknown792)) {
        case 228:
        case 229:
        case 237:
            result = 0;
            break;
        }
        if (!fn_80124714(p, pOther, &pBlocker) && pBlocker != 0 && !(pBlocker->mFlags & 0x800)) {
            result = 0;
        }
        break;
    default:
        if (fn_8022781C(&pOther->mMotion.mPos, &p->mMotion.mPos) > 3.0f) {
            result = 0;
        } else if (!fn_80124714(p, pOther, &pBlocker)) {
            if (pBlocker != 0 && !(pBlocker->mFlags & 0x800)) {
                result = 0;
            }
        } else if (p->mFlags & 0x20000) {
            result = 0;
        }
        break;
    case 51:
    case 89:
        result = 0;
        break;
    }
    return result;
}

extern "C" int fn_800C6048(Object_80039F5C *p, Object_800C6640 *pSource, Object_80039F5C *pOther, int value)
{
    Object_80039F5C *pTarget;
    float *pStats;
    float *pTargetStats;
    int diff;
    int ratingScore;
    int speedScore;
    float speedDiff;
    int total;
    int chance;
    float bonus;
    float partnerRating;
    float scale;
    Object_80039F5C *pPartner;
    unsigned char shift;

    if (fn_801787A0() == 0) {
        if (pSource != 0 && pOther == 0) {
            pTarget = fn_8009BCE8(&pSource->mUnknown40);
        } else {
            pTarget = pOther;
        }
        if ((fn_801486A0() || (pTarget != 0 && fn_800F06F4(0, pTarget->mpState, 51, 0xFFFF) == 0xFFFF))
            && pTarget != 0 && fn_800C5BF0(p, value) && fn_800C5DE4(pTarget, p)) {
            if (fn_800C769C(pTarget, p)) {
                return pTarget->mUnknown1221;
            }
            pStats = &p->mUnknown2900;
            pTargetStats = &pTarget->mUnknown2900;
            diff = pTarget->mRatings[5] - p->mRatings[2];
            if (diff > 0) {
                ratingScore = diff * 30 / 255.0f + 70.0f;
            } else {
                ratingScore = diff * 70 / 255.0f + 70.0f;
            }
            ratingScore *= 0.5f;
            speedDiff = pTargetStats[1] * pTarget->mMotion.mUnknown28 - pStats[1] * p->mMotion.mUnknown28;
            if (speedDiff > 0.0f) {
                speedScore = speedDiff * 30.0f / (lbl_803ECB08 * 415.0f) + 70.0f;
            } else {
                speedScore = speedDiff * 70.0f / (lbl_803ECB08 * 415.0f) + 70.0f;
            }
            speedScore *= 0.5f;
            total = ratingScore + speedScore;
            chance = total < 0 ? 0 : (total > 100 ? 100 : total);
            if (pSource == 0 || pSource->mUnknown0 == 0
                || (fn_8016F6F4(p, &pTarget->mId), !fn_800C68BC(pSource, pTarget->mpState->mId))
                || fn_800C8420(pTarget, pSource->mUnknown32)) {
                if (chance != 0) {
                    chance = fn_800AC584(pTarget->mIdBytes[2], chance);
                    chance = fn_800C5418(p, pTarget, chance);
                    if (fn_800B65A0(p->mIdBytes[2]) != 255 && fn_800B65A0(pTarget->mIdBytes[2]) == 255) {
                        bonus = fn_8016B938() * 0.25f;
                        chance += (int)(chance * bonus);
                        if (!fn_80177C38() && fn_8011F1CC() && (p->mFlags & 0x8000)) {
                            bonus = fn_8016B974() * 0.25f;
                            chance += (int)(chance * bonus);
                        }
                    }
                    if (pSource != 0) {
                        chance += (pSource->mUnknown53 - 1) * 5;
                    }
                    pPartner = fn_80114E7C(p);
                    if (pPartner != 0) {
                        partnerRating = pPartner->mRatings[5] / 255.0f;
                        chance += (int)(partnerRating * 40.0f);
                    }
                    chance = fn_8009B0CC(p->mIdBytes[2], chance);
                    if (p->mpState->mId == 28 && (fn_801783AC(11) == 1 || fn_801783AC(12) == 1)) {
                        chance += chance / 2;
                    }
                }
                scale = 0.0f;
                if (fn_800CA5CC(pTarget, 9, 0)) {
                    scale = fn_800CA9B4(7, pTarget) - 1.0f;
                }
                if (fn_800CA5CC(p, 10, 0)) {
                    scale -= fn_800CA9B4(8, p) - 1.0f;
                }
                chance = chance + chance * scale;
                if (!fn_800C53D8(p)) {
                    shift = p->mUnknown1160.mUnknown48 / lbl_803EABF8;
                    if (shift != 0) {
                        chance = chance < 0 ? 0 : (chance > 95 ? 95 : chance);
                        chance += (100 - chance) >> shift;
                    }
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
    return chance < 20 ? 20 : (chance > 95 ? 95 : chance);
}

extern "C" int fn_800C6A3C(Object_80039F5C *p, Object_80039F5C *pOther, int type)
{
    Query_800CE770 query;
    int result = 0;
    int kind = fn_801BE648(p->mpUnknown792);

    if (kind != 196 && type != -1) {
        fn_800CE770(&query);
        query.mUnknown56 = 0;
        query.mpUnknown0 = p;
        if (kind == 173) {
            if (fn_80114E7C(p) == pOther) {
                query.mUnknown36 = 0x18E38E;
                query.mUnknown44 = 2.0f;
            } else {
                return 0;
            }
        } else {
            query.mUnknown60 = 1;
            query.mUnknown36 = (int)(lbl_803ED6B4 * 46603.378f) * 4.0f;
            query.mUnknown44 = lbl_803ED6BC * 4.0f;
        }
        query.mUnknown52 = type;
        if (type == 247) {
            query.mUnknown54 = fn_801BE60C(p->mpUnknown792, kind)->mUnknown3C;
        } else {
            query.mUnknown54 = 1;
        }
        if (!fn_8011E9B4(pOther) && fn_801CFFD0(p->mMotion.mUnknown32, pOther->mMotion.mFacing) <= 0x2AAAA9) {
            query.mUnknown32 = 0x800000;
        }
        fn_800C5234(&query, pOther);
        result = fn_800CE2B8(&query);
    }
    if (result != 0) {
        p->mUnknown1219 = 0;
    }
    return result;
}

extern "C" int fn_800C6BD8(Object_80039F5C *p, Object_80039F5C *pOther, int)
{
    Query_800CE770 query;
    int result = 0;

    if (fn_801BE648(p->mpUnknown792) != 196 && fn_80054130()->mUnknown136 != 0
        && fabsf(p->mMotion.mPos.mX) > fn_80178A08() - lbl_803EAC18) {
        fn_800CE770(&query);
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        query.mUnknown36 = lbl_803EAC10 * 46603.378f;
        query.mUnknown44 = lbl_803EAC14;
        query.mUnknown52 = 181;
        query.mUnknown59 = 1;
        query.mUnknown60 = 1;
        result = fn_800CE2B8(&query);
    }
    if (result != 0) {
        fn_80067DB8(44, &p->mMotion.mPos, 0, 0, 0);
        fn_8006F0B8(8);
        p->mUnknown1219 = 0;
    }
    return result;
}

extern "C" int fn_800C6CDC(Object_80039F5C *p, Object_80039F5C *pOther, int)
{
    Query_800CE770 query;
    int result = 0;

    if (fn_801BE648(p->mpUnknown792) != 196 && fn_80054130()->mUnknown136 != 0
        && fabsf(p->mMotion.mPos.mX) > fn_80178A08() - lbl_803EAC18) {
        fn_800CE770(&query);
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        query.mUnknown36 = lbl_803EAC10 * 46603.378f;
        query.mUnknown44 = lbl_803EAC14;
        query.mUnknown52 = 186;
        query.mUnknown59 = 1;
        query.mUnknown60 = 1;
        result = fn_800CE2B8(&query);
    }
    if (result != 0) {
        fn_800D4748(p);
        fn_800A8954(13, p->mIdBytes[2], p);
        fn_80067DB8(44, &p->mMotion.mPos, 0, 0, 0);
        fn_8006F0B8(8);
        p->mUnknown1219 = 1;
    }
    return result;
}

extern "C" int fn_800C6DF8(Object_80039F5C *p, Object_80039F5C *pOther, int type, int angle, unsigned int chance,
                           float distance)
{
    int result = 0;
    int count = 0;
    int otherBlocking = 0;
    int special = 0;
    Query_800CE770 query;
    int kinds[5];
    unsigned int i;

    if (p->mpState->mId == 36 || fn_801BE648(p->mpUnknown792) == 229 || fn_801BE648(p->mpUnknown792) == 237) {
        special = 1;
    }
    if (pOther->mpState->mId == 12 || pOther->mpState->mId == 94) {
        otherBlocking = 1;
    }
    fn_800CE770(&query);
    query.mpUnknown0 = p;
    query.mpUnknown4 = pOther;
    query.mUnknown52 = type;
    if (special == 1) {
        query.mUnknown36 = 0xE38E3;
        query.mUnknown44 = 1.0f;
    } else if (otherBlocking == 1 && fn_800CD2B4(1, pOther)) {
        query.mUnknown36 = 0xAAAAA;
        query.mUnknown44 = 0.45f;
    } else {
        query.mUnknown44 = distance;
        query.mUnknown36 = angle * 46603.378f;
    }
    if (!fn_8011E9B4(pOther) && fn_801CFFD0(p->mMotion.mUnknown32, pOther->mMotion.mFacing) <= 0x2AAAA9) {
        query.mUnknown32 = 0x800000;
    }
    if (type != 94 && type != 234 && !(otherBlocking && fn_800CD2B4(1, pOther)) && !special) {
        if (fn_802372EC(0, 100) < chance) {
            kinds[count] = 3;
        } else {
            kinds[count] = 2;
        }
        if (fn_800C7720(pOther, p)) {
            kinds[count] = 3;
        }
    } else {
        kinds[count] = 1;
    }
    count++;
    for (i = 0; i < count; i++) {
        query.mUnknown54 = kinds[i];
        result = fn_800CE2B8(&query);
        if (result != 0) {
            break;
        }
    }
    if (result != 0) {
        p->mUnknown1219 = 0;
        p->mUnknown1216[1] = query.mUnknown54;
        pOther->mUnknown1216[1] = p->mUnknown1216[1];
    }
    return result;
}

extern "C" int fn_800C7118(Object_80039F5C *p, Object_80039F5C *pOther, int a, float value, int b, unsigned int c)
{
    Query_800CE770 query;
    int types[5];
    int count = 0;
    int result = 0;
    int special = 0;
    int isTwo;
    unsigned int i;

    if (pOther->mpState->mId == 12 || pOther->mpState->mId == 94) {
        special = 1;
    }
    fn_800CE770(&query);
    query.mpUnknown0 = p;
    query.mpUnknown4 = pOther;
    if (special == 1 && fn_800CD2B4(1, pOther)) {
        query.mUnknown36 = 0xAAAAA;
        query.mUnknown44 = 0.45f;
    } else {
        query.mUnknown36 = b;
        query.mUnknown44 = value;
    }
    query.mUnknown52 = a;
    if (!fn_8011E9B4(pOther) && fn_801CFFD0(p->mMotion.mUnknown32, pOther->mMotion.mFacing) < 0x2AAAAA) {
        query.mUnknown32 = 0x800000;
    }
    if (p->mpState->mId == 43) {
        if (c <= 32) {
            types[count] = 6;
            types[count + 1] = 5;
        } else if (c > 67) {
            types[count] = 5;
            types[count + 1] = 6;
        } else if (fn_802372EC(0, 100) < 50) {
            types[count] = 5;
            types[count + 1] = 6;
        } else {
            types[count] = 6;
            types[count + 1] = 5;
        }
        count += 2;
    }
    if (fn_800A8444(fn_80178308())) {
        types[count] = 10;
        count++;
    }
    types[count] = 1;
    isTwo = fn_800CF090(p) == 2;
    count++;
    for (i = 0; i < count; i++) {
        query.mUnknown54 = types[i];
        result = fn_800CE2B8(&query);
        if (result != 0) {
            if (types[i] == 5 || types[i] == 6) {
                fn_800D4FBC(p, 1);
                fn_800A8954(2, p->mIdBytes[2], p);
                fn_80067E3C(97, &p->mMotion.mPos, p->mId, p->mpState->mId, 0, 0);
                fn_800310C0(lbl_803EA368, 59, p, &p->mMotion.mPos, &p->mMotion.mFacing);
            } else if (isTwo) {
                fn_800D60BC(p, fn_800D0B90(p), 255);
            } else {
                fn_800D4748(p);
                fn_800A8954(13, p->mIdBytes[2], p);
            }
            p->mUnknown1219 = 1;
            break;
        }
    }
    return result;
}

extern "C" int fn_800C73E0(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Vector_80039F5C ballPos;
    Vector_80039F5C ballDir;
    Point_8017886C delta;
    Object_80137ABC *pBall;

    if (pOther->mpUnknown4->mUnknown20 & 1) {
        if (pOther == fn_80137B40() || pOther->mpState->mId == 91 || pOther->mpState->mId == 25
            || (pOther->mpState->mId == 15 && fn_801045BC(pOther) < fn_80104610(pOther))
            || (pOther->mpState->mId == 27 && fn_8010CE2C(pOther))
            || ((p->mFlags & 0x20000) && p->mUnknown1154 <= 1 && p->mUnknown1140 == pOther->mId)) {
            return 1;
        }
        if (pOther->mpState->mId == 28 || pOther->mpState->mId == 23) {
            pBall = fn_801374BC();
            fn_80137D58(pBall, &ballPos);
            if (fn_801783AC(11) == 1 || fn_801783AC(12) == 1) {
                if (ballPos.mZ > 0.75f && fn_8022781C(&ballPos, &pOther->mMotion.mPos) < lbl_803EABF4) {
                    return 1;
                }
            } else {
                fn_80137EC4(pBall, &ballDir);
                fn_80227690(&delta, &ballPos, &pOther->mMotion.mPos);
                if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), fn_801CFE40(ballDir.mY, ballDir.mX))
                        < (int)(lbl_803EAC1C * (16777216.0f / 360.0f))
                    && fn_8022781C(&ballPos, &pOther->mMotion.mPos) < lbl_803EABF4) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

extern "C" Object_80039F5C *fn_800C75C0(Object_80039F5C *p)
{
    Object_80039F5C *pBest = 0;
    float bestDistance = 500000.0f;
    unsigned short i = 0;
    unsigned int count = fn_80178D18(p->mIdBytes[2] ^ 1);

    for (; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, i);
        float distance = fn_80227890(&pOther->mMotion.mPos, &p->mMotion.mPos);

        if (distance < 16.0f && distance < bestDistance && fn_800C73E0(p, pOther)) {
            pBest = pOther;
            bestDistance = distance;
        }
    }
    return pBest;
}

extern "C" void fn_800C7794(Object_80039F5C *p)
{
    int kindA;
    int kindB;
    int kindC;
    unsigned int chance;
    int result = 0;
    Object_80039F5C *pOther = fn_800C75C0(p);
    unsigned char key;
    unsigned char blocked;
    unsigned int roll;
    int tackle;

    if (!fn_800C6738(p, pOther)) {
        return;
    }
    key = pOther->mUnknown2914;
    chance = fn_800C6048(pOther, 0, p, key);
    if (chance != 0 && !fn_800A7F30(pOther->mIdBytes[2]) && fn_800A851C(p->mIdBytes[2], p)) {
        chance = 100;
    }
    blocked = fn_800D0B90(pOther);
    if (fn_800C769C(p, pOther)) {
        roll = p->mUnknown1222;
    } else {
        roll = fn_802372EC(0, 100);
    }
    if (blocked) {
        roll = 0;
    }
    fn_800C5F80(pOther, key, &kindA, &kindB, &kindC);
    if (roll >= chance && !fn_800C7720(p, pOther)) {
        unsigned int chance2 = fn_800C6640(pOther, 0, p, key, chance);

        if (chance2 != 0) {
            if (fn_800C4EE8(p, pOther, fn_802372EC(0, 100), chance2)) {
                result = fn_800C7084(pOther, p, 172, 0.9f, 0x88888);
                if (result) {
                    pOther->mFlags &= ~0x80000;
                }
            }
            if (!result) {
                result = fn_800C6CDC(pOther, p, 0);
                if (!result) {
                    result = fn_800C7118(pOther, p, kindB, 0.45f, 0x66666, chance);
                    if (!result && kindB == 93 && (p->mpState->mId == 12 || p->mpState->mId == 94)
                        && fn_800CD2B4(1, p)) {
                        fn_800C5F80(pOther, 31, &kindA, &kindB, &kindC);
                        result = fn_800C7118(pOther, p, kindB, 0.45f, 0x66666, chance);
                        fn_800C5F80(pOther, key, &kindA, &kindB, &kindC);
                    }
                }
            }
            if (result) {
                int bonus;

                pOther->mFlags &= ~0x80000;
                pOther->mUnknown1160.mUnknown44++;
                bonus = p->mRatings[5] - pOther->mRatings[2];
                bonus = bonus / 2 + 127;
                if (bonus >= 0) {
                    if (bonus > 255) {
                        bonus = 255;
                    }
                } else {
                    bonus = 0;
                }
                pOther->mUnknown1160.mUnknown48 += bonus;
                if (!fn_800C53D8(pOther)) {
                    Record_800B15FC *pRecord;

                    fn_800C51DC(pOther, p);
                    fn_800C68B8(p, pOther, kindB);
                    pRecord = fn_800B15FC();
                    fn_8009BD2C(pOther, &pRecord->mUnknown0);
                    pRecord->mUnknownC = pOther->mMotion.mPos.mX;
                    pRecord->mUnknown10 = pOther->mMotion.mPos.mY;
                    pRecord->mUnknown14 = 38;
                    pRecord->mUnknown16 = 1;
                    fn_800B1508();
                }
                fn_800C7708(p);
            } else {
                fn_800C76D8(p, pOther, chance, roll);
            }
        }
        tackle = 0;
    } else {
        tackle = 1;
    }
    if (tackle) {
        if (fn_800C4EE8(p, pOther, roll, chance)) {
            result = fn_800C7084(pOther, p, 172, 0.9f, 0x88888);
            if (result) {
                pOther->mFlags &= ~0x80000;
            }
        }
        if (!result && !fn_800C53D8(pOther)) {
            if (!result) {
                if (fn_800C4E30(p, pOther)) {
                    result = fn_800C6DF8(pOther, p, 234, (int)(lbl_803ED6B4 * 2.0f), chance, lbl_803ED6BC * 2.0f);
                } else {
                    result = fn_800C6BD8(pOther, p, 0);
                    if (!result) {
                        result = fn_800C6A3C(pOther, p, kindC);
                    }
                    if (!result) {
                        int reach = (int)(lbl_803ED6B4 * 1.5f);
                        float speed = lbl_803ED6BC * 1.5f;

                        result = fn_800C6DF8(pOther, p, kindA, reach, chance, speed);
                        if (!result && kindA == 94 && (p->mpState->mId == 12 || p->mpState->mId == 94)
                            && fn_800CD2B4(1, p)) {
                            fn_800C5F80(pOther, 31, &kindA, &kindB, &kindC);
                            result = fn_800C6DF8(pOther, p, kindA, reach, chance, speed);
                            fn_800C5F80(pOther, key, &kindA, &kindB, &kindC);
                        }
                    }
                }
            }
            if (result) {
                fn_800C51DC(pOther, p);
                pOther->mFlags &= ~0x80000;
                fn_80178718(p);
                fn_800C68B8(p, pOther, kindA);
                fn_800C7708(p);
            } else {
                fn_800C76D8(p, pOther, chance, roll);
            }
        }
    }
    if (result && p->mUnknown8 != 255 && fn_800CD35C(1, p)) {
        fn_80156C78(23, 1);
    }
}

extern "C" void fn_800C7D44(Object_80039F5C *p)
{
    int kindA;
    int kindB;
    int kindC;
    int result = 0;
    int stolen = 0;
    Object_80039F5C *pOther;
    unsigned char key;
    unsigned int chance;
    unsigned char blocked;
    unsigned int roll;

    if (fn_800AD9B4() != 3 || p == 0 || p->mIdBytes[3] != 1 || p != fn_80137B40()) {
        return;
    }
    pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
    key = p->mUnknown2914;
    chance = fn_800C6048(p, (Object_800C6640 *)&p->mUnknown560, 0, key);
    if (chance != 0) {
        if (!fn_800A7F30(p->mIdBytes[2]) && pOther != 0 && fn_800A851C(pOther->mIdBytes[2], pOther)) {
            chance = 100;
        }
        if (chance != 0 && p->mpState->mId == 58
            && p->mpUnknown352 == fn_8009BCE8(&p->mUnknown560.mUnknown40)) {
            chance = 0;
        }
    }
    blocked = fn_800D0B90(p);
    if (chance == 0) {
        return;
    }
    if (fn_800C769C(pOther, p)) {
        roll = pOther->mUnknown1222;
    } else {
        roll = fn_802372EC(0, 100);
    }
    if (blocked) {
        roll = 0;
    }
    if (roll < chance && !fn_800C53D8(p)) {
        fn_800C5F80(p, p->mUnknown2914, &kindA, &kindB, &kindC);
        if (pOther != 0 && fn_800C6738(pOther, p)) {
            if (!result && fn_800C4E30(pOther, p)) {
                result = fn_800C6DF8(p, pOther, 234, (int)(lbl_803ED6B4 * 2.0f * lbl_803EAC20), chance,
                                     lbl_803ED6BC * 2.0f * lbl_803EAC20);
            }
            if (!result) {
                if (fn_800C4EE8(pOther, p, roll, chance)) {
                    stolen = fn_800C7084(p, pOther, 172, 0.9f, 0x88888);
                }
                if (!stolen) {
                    result = fn_800C6BD8(p, pOther, 1);
                }
                if (!result) {
                    if (!stolen) {
                        result = fn_800C6A3C(p, pOther, kindC);
                    }
                    if (!result && !stolen) {
                        unsigned char scale;
                        unsigned char count;

                        if (kindA == 94) {
                            scale = (unsigned char)lbl_803EAC24;
                            count = (unsigned char)lbl_803EAC28;
                        } else if (fn_8011E9B4(pOther) == 1) {
                            scale = 1;
                            count = 2;
                        } else {
                            scale = count = (unsigned char)lbl_803EAC20;
                        }
                        float speed = scale * 1.5f;
                        int reach = (int)(lbl_803ED6B4 * 1.5f);

                        result = fn_800C6DF8(p, pOther, kindA, reach * count, chance, lbl_803ED6BC * speed);
                    }
                }
            }
            if (result) {
                p->mFlags &= ~0x80000;
                fn_800C51DC(p, pOther);
                fn_80178718(pOther);
                fn_800C68B8(pOther, p, kindA);
            } else if (stolen) {
                p->mFlags &= ~0x80000;
            }
        }
        if (!result && !stolen) {
            if (fn_8011E9B4(pOther)) {
                fn_800C56C0(p, key, chance);
            } else {
                fn_800C561C(p, key);
                fn_800C51DC(p, pOther);
                fn_801718E8(p, pOther);
                fn_80067E3C(37, &p->mMotion.mPos, p->mId, (unsigned int)p->mUnknown560.mUnknown28,
                            p->mUnknown560.mUnknown54, p->mUnknown560.mUnknown55);
                fn_800A3B58(p, 1, 0);
            }
            if (pOther->mUnknown8 != 255 && fn_800F06F4(0, pOther->mpState, 12, 0xFFFF) != 0xFFFF) {
                fn_80156C78(23, 1);
            }
        }
    } else {
        int bonus = 0;

        if (pOther != 0) {
            bonus = pOther->mRatings[5] - p->mRatings[2];
            bonus = bonus / 2 + 127;
            bonus = bonus < 0 ? 0 : (bonus > 255 ? 255 : bonus);
        }
        p->mUnknown1160.mUnknown48 += bonus;
        fn_800C56C0(p, key, chance);
    }
    fn_800C7708(pOther);
}

extern "C" void fn_800C8270(Object_80039F5C *p)
{
    p->mUnknown1160.mUnknown4 = p->mUnknown1160.mUnknown0 = 0.0f;
    p->mUnknown1160.mUnknown8 = 0;
    p->mUnknown1160.mUnknown44 = 0;
    p->mUnknown1160.mUnknown48 = 0;
    p->mUnknown1160.mUnknown52 = 0;
    p->mUnknown1160.mUnknown53 = 0;
    p->mUnknown1160.mUnknown54 = 0;
    p->mUnknown1160.mUnknown55[0] = 0;
    p->mUnknown1216[0] = 0;
    p->mUnknown1218 = 0;
    p->mUnknown1219 = 0;
    p->mpUnknown1224 = 0;
    p->mUnknown1220 = 0;
    p->mUnknown1221 = 0;
    p->mUnknown1222 = 0;
}

extern "C" void fn_800C82C0(Object_80039F5C *p)
{
    p->mUnknown1160.mUnknown12Word = 0x400000;
    p->mUnknown1160.mUnknown16 = 0.0f;
    p->mUnknown1160.mUnknown20 = fn_80178A2C();
    p->mUnknown1160.mUnknown24 = 0.0f;
    p->mUnknown1160.mUnknown30 = 1;
    p->mUnknown1160.mUnknown28 = -1;
    p->mUnknown1160.mUnknown36 = 0.0f;
    p->mUnknown1160.mUnknown32 = 0.0f;
    p->mUnknown1160.mUnknown40 = 0;
}

extern "C" void fn_800C8330(Object_80039F5C *p)
{
    Block_801718E8 *pBlock = &p->mUnknown1160;

    if (p->mUnknown1220 != 0) {
        p->mUnknown1220--;
    }
    if (pBlock->mUnknown0 != 0.0f) {
        pBlock->mUnknown0 -= pBlock->mUnknown4;
        if (--pBlock->mUnknown8 < 0) {
            fn_800C8270(p);
        }
    }
    if (pBlock->mUnknown53) {
        if (fn_80137B40() != p) {
            pBlock->mUnknown53 = 0;
            pBlock->mUnknown54 = 0;
        }
        if (!fn_801383A0(fn_801374BC())) {
            pBlock->mUnknown53 = 0;
            pBlock->mUnknown54 = 0;
        }
    }
    switch (p->mpState->mId) {
    case 10:
    case 16:
    case 17:
    case 28:
    case 58:
        break;
    default:
        fn_800C82C0(p);
        break;
    }
}

extern "C" int fn_800C8420(Object_80039F5C *p, float value)
{
    Block_801718E8 *pBlock = &p->mUnknown1160;

    if (value > pBlock->mUnknown0) {
        pBlock->mUnknown0 = value;
        pBlock->mUnknown8 = 12;
        pBlock->mUnknown4 = value * (1.0f / 12.0f);
        return 1;
    }
    return 0;
}

extern "C" void fn_800C845C(void)
{
    Object_80039F5C *pCarrier;

    fn_801C1F94(lbl_80317AD8, 0, sizeof(lbl_80317AD8));
    pCarrier = fn_80137B40();
    if (pCarrier != 0) {
        unsigned short i = 0;
        int team = fn_80178320();
        unsigned short found = 0;
        unsigned int count = fn_80178D18(team);

        for (; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(team, i);

            if (fn_80227890(&p->mMotion.mPos, &pCarrier->mMotion.mPos) < 16.0f && fn_800C6738(p, pCarrier)
                && fn_800C5DE4(p, pCarrier) && found < 7) {
                lbl_80317AD8[found] = p;
                found++;
            }
        }
    }
}

extern "C" int fn_800C854C(Object_80039F5C *p, unsigned short key, unsigned char a)
{
    Query_800CE770 query;
    Object_80039F5C *pOther;
    short kind;
    int result = 0;

    if (p->mpState->mId == 16) {
        switch (fn_80114A30(p, a)) {
        case 1:
            kind = 173;
            break;
        case 2:
            kind = 174;
            break;
        case 5:
            kind = 238;
            break;
        case 3:
        default:
            kind = 175;
            break;
        }
        pOther = fn_80039F5C((unsigned char)(1 - p->mIdBytes[2]), p->mpState->mUnknown3[0]);
        if (pOther->mpState->mId == 17) {
            fn_800CE770(&query);
            query.mpUnknown0 = p;
            query.mpUnknown4 = pOther;
            query.mUnknown36 = 0x800000;
            query.mUnknown32 = 0x800000;
            query.mUnknown44 = 20.0f;
            query.mUnknown52 = kind;
            query.mUnknown54 = a;
            query.mUnknown56 = 0;
            query.mUnknown58 = 0;
            result = fn_800CE438(&query);
            fn_8002892C();
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            fn_801BE67C(pOther->mpUnknown792, pOther->mpUnknown796, pOther->mpUnknown800, pOther);
        } else {
            result = 0;
        }
    }
    return result;
}
