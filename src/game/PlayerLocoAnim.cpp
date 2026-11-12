/* Player locomotion animation states: picks the two locomotion categories
   of a player, runs the phases of the locomotion cycle and move-command
   states, and keeps the pair of blended cycle animations (start, switch,
   fade and weights). The turn-in-place functions after
   PlayerLocoGetRunCategory are not referenced and do not reach the game. */

#include "engine/cu_801B9F00.h"
#include "game/fn_801BA2A8.h"
#include "game/LocoBlendSet.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/Block_801BE60C.h"
#include "game/FEPlyrModel.h"
#include "game/Table_80089904.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include "game/Object_8017886C.h"
#include <math.h>

extern "C" {

struct PlayerLocoTrimKey_t { unsigned short mUnknown0; unsigned short mUnknown2; };
int fn_801486A0(void);
int PassIconsAreShown(void);
int fn_801787A0(void);
int PlayerMoveGetKind(Object_80039F5C *p);
int PlayerMoveGetRunVariant(Object_80039F5C *p);
int PlayerLocoUseAltCategory(Object_80039F5C *p, Object_80039F5C *pOther, int team, int flag);
int PlayerLocoUseSpecialCategory(Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
int PlayerLocoIsEngaged(Object_80039F5C *p, int flag);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227638(Point_8017886C *pOut, Point_8017886C *pA, Point_8017886C *pB);
void fn_80227690(Point_8017886C *pOut, Point_8017886C *pA, Point_8017886C *pB);
void fn_80227248(Point_8017886C *pOut, Point_8017886C *pIn, float scale);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
Point_8017886C fn_80177FFC(int team);
void fn_8009BEFC(Object_80039F5C *p, int joint, Vector_80039F5C *out, int *scratch);
int CharSkelGetJointByName(void *p, const char *name);
int PlayerLocoGetBlendIndex(Object_80039F5C *p, Object_801BBD5C *object);
int PlayerLocoSelectBlendSet(Object_80039F5C *p, Block_801BE60C *block, unsigned char *value);
void PlayerLocoSetCycleDuration(float value, Block_801BE60C *block, LocoBlendSet_t *object, Record_800D81C8 *entries);
unsigned char fn_800D78C4(Object_80039F5C *p, unsigned short key);
void fn_800ADBC0(Object_80039F5C *p, int a, int b, int c);
int fn_8009C4B0(Table_80089904 *table, Key_80110630 *key);
int fn_801BA6B0(Record_800D81C8 *entry);
void fn_801BA6BC(Record_800D81C8 *entry, int value);
float MathInverse(float value);
void AnimSeqSetSpeed(void *p, float value);
void PlayerLocoTrimBlendEntries(FEPlyrModel_t *record, Record_800D81C8 *entries, int key);
void PlayerLocoStartBlendPair(LocoBlendSet_t *object, Block_801BE60C *block, Object_80039F5C *p, int value, int index, int key, FEPlyrModel_t *record, Record_800D81C8 *entries);
void PlayerLocoSwitchBlendPair(LocoBlendSet_t *, Block_801BE60C *, Object_80039F5C *, int, int, unsigned short, void *, Record_800D81C8 *, unsigned char);
void PlayerLocoSetFadeFraction(Block_801BE60C *, float, float);
void PlayerLocoFadeOldPair(Block_801BE60C *, void *, Record_800D81C8 *);
int PlayerLocoGetStartSide(Object_80039F5C *, int, int);

int PlayerLocoUpdateCategories(void *, Block_801BE60C *, Object_80039F5C *, Object_80039F5C *, int);
int PlayerLocoNotInState84(Object_80039F5C *);

extern float gFrameTimeScale;

int fn_80178308(void);
int PlayerLocoGetPrimaryCategory(Object_80039F5C *p, int team, int flag, unsigned char *pValue);
int PlayerLocoGetSecondaryCategory(Object_80039F5C *p, Object_80039F5C *pOther, int team, int flag, unsigned char value);
void PlayerLocoSelectStates(void *a, Block_801BE60C *pBlock, Object_80039F5C *p, int value);
int fn_801BA2D0(void *a, Record_800D81C8 *pEntries, Record_800D81C8 *pEntry);
void fn_801BA418(void *a, Record_800D81C8 *pEntries, int index, unsigned short b,
                 int c, unsigned short d, Object_80039F5C *pRecord);
void AnimSeqSetDuration(AnimSeq_t *p, float value);

static unsigned char _PlayerLoco_aRunCategories[36] = {
    0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
    0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x47, 0x42, 0x43, 0x45, 0x46, 0x44, 0x4A, 0x49, 0x48, 0x4C,
    0x01, 0x00, 0x00, 0x00,
};

static PlayerLocoTrimKey_t _PlayerLoco_aTrimKeys[4] = {
    { 0, 0x4A }, { 0, 0xA0 }, { 0, 0x9F }, { 0, 0x9D },
};

int PlayerLocoGetSecondaryCategory(Object_80039F5C *p, Object_80039F5C *pOther, int team, int flag, unsigned char value)
{
    int result = value;
    if (p->mIdBytes[3] == 1) {
        if (pOther == p || (fn_801486A0() == 1 && BallFindHeldBy(p))) {
            switch (p->mUnknown528.mUnknown15) {
            case 10: case 11: result = 34; goto finish;
            case 20: case 21:
                if (PlayerMoveGetKind(p) == 2) {
                    result = (unsigned char)PlayerMoveGetRunVariant(p);
                    result = _PlayerLoco_aRunCategories[result];
                }
                else result = 1;
                goto finish;
            case 6: case 7: result = 11; goto finish;
            case 8: case 9: result = 12; goto finish;
            case 29: result = 1; goto finish;
            case 13: result = 17; goto finish;
            case 14: result = 16; goto finish;
            case 26: result = 37; goto finish;
            case 27: result = 41; goto finish;
            case 22: case 23: result = 33; goto finish;
            case 3: result = 40; goto finish;
            case 2: result = 42; goto finish;
            }
            result = PlayerLocoUseAltCategory(p, pOther, team, flag) ? 19 : 1;
            if (PlayerLocoUseSpecialCategory(p)) result = 38;
            if (p->mUnknown2914 != 0 && p->mUnknown2914 != 20 &&
                p->mUnknown2914 != 1 && p->mUnknown2914 != 3) goto finish;
            if (fn_800DC080(p)) {
                int direction = fn_801CFE40(p->mMotion.mUnknown44, p->mMotion.mUnknown40) & 0xFFFFFF;
                Block_801BE60C *block = fn_801BE60C(p->mpUnknown792, 74);
                int angle;
                if (p->mUnknown2913 == 0) {
                    angle = block->mUnknown3D == 9 ? 95 : 85;
                    result = 6;
                    if (MathAngleDiff(direction, 0) < (int)(angle * 46603.37890625f)) result = 9;
                } else {
                    angle = block->mUnknown3D == 9 ? 85 : 95;
                    result = 9;
                    if (MathAngleDiff(direction, 0) < (int)(angle * 46603.37890625f)) result = 6;
                    if (!(p->mMotion.mUnknown28 > 0.0000001f)) result = 9;
                }
            } else if (PassIconsAreShown() || !(p->mFlags & 0x400)) {
                result = !p->mUnknown2913 ? 23 : 22;
            }
            goto finish;
        }
        if (p->mUnknown1052 && (result == 1 || (result == 2 && PlayerLocoIsEngaged(p, flag)))) {
            switch (p->mUnknown1032) {
            case 2: case 3: result = 4; break;
            case 4: result = 5; break;
            case 7: result = 5; break;
            case 1:
            default: result = 3; break;
            }
            goto finish;
        }
        switch (p->mUnknown528.mUnknown15) {
        case 15: result = 24; break;
        case 16: result = 25; break;
        case 12: result = 14; break;
        case 18: result = 26; break;
        case 19: result = 27; break;
        case 24: result = 36; break;
        case 25: result = 36; break;
        case 30: result = 77; break;
        default: result = PlayerLocoUseAltCategory(p, pOther, team, flag) ? 20 : 2; break;
        }
        if (p->mUnknown528.mUnknown14 == 9) result = PlayerLocoUseAltCategory(p, pOther, team, flag) ? 20 : 2;
        if (p->mpState->mId == 42 && MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0x2AAAA9) {
            Point_8017886C point;
            point = fn_80177FFC(p->mIdBytes[2]);
            if (!(p->mMotion.mPos.mY - point.mY >= 6.0f)) {
                result = 15;
                if (!(fabsf(p->mMotion.mPos.mX - point.mX) >= 9.0f)) result = 13;
            }
        }
    } else {
        result = 2;
    }
finish:
    if (fn_801787A0()) {
        switch (result) {
        case 2: result = 18; break;
        case 1: result = 43; break;
        }
    }
    return result;
}


int PlayerLocoUpdateCategories(void *a, Block_801BE60C *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, int value)
{
    int changed = 0;
    int first;
    int second;

    if (p->mIdBytes[3] == 1) {
        int team = fn_80178308();
        int flag = 1;
        if (fn_800AD9B4() == 3) {
            flag = 0;
        }
        unsigned char result = 2;
        first = PlayerLocoGetPrimaryCategory(p, team, flag, &result);
        second = PlayerLocoGetSecondaryCategory(p, pOther, team, flag, result);
    } else {
        first = 2;
        second = BallFindHeldBy(p) ? 1 : 2;
    }
    if (pBlock->mUnknown3C != first || pBlock->mUnknown3D != second) {
        pBlock->mUnknown3C = first;
        pBlock->mUnknown3D = second;
        PlayerLocoSelectStates(a, pBlock, p, value);
        changed = 1;
    }
    return changed;
}

int PlayerLocoGetStartSide(Object_80039F5C *p, int check, int value)
{
    if (p->mIdBytes[3] == 1) {
        switch (p->mUnknown528.mUnknown15) {
        case 6:
        case 7:
        case 16:
        case 19:
            return 1;
        case 8:
        case 9:
        case 15:
        case 18:
            return 0;
        }
        switch (p->mUnknown512.mUnknown15) {
        case 6:
        case 7:
        case 16:
        case 19:
            return 1;
        case 8:
        case 9:
        case 15:
        case 18:
            return 0;
        }
        if (BallFindHeldBy(p) == 0) {
            if (check != 0 && fn_800AD9B4() != 2) {
                value = fn_802372EC(0, 100) < 50;
            }
        } else {
            value = p->mUnknown776 == 1;
        }
    } else {
        return 0;
    }
    return value;
}

int PlayerLocoNotInState84(Object_80039F5C *p)
{
    int result = 1;
    if (fn_801BE648(p->mpUnknown792) == 84) {
        result = 0;
    }
    return result;
}

static inline Record_800D81C8 *AnimEntryAt(Record_800D81C8 *pEntries, int index)
{
    return &pEntries[index];
}

static inline void PlayerLocoUpdateCycle(Object_80039F5C *p, Block_801BE60C *block, Record_800D81C8 *entries)
{
    if (MathAngleDiff(p->mMotion.mFacing, p->mMotion.mUnknown32) > 0x56C16C)
        PlayerLocoSetCycleDuration(-block->mUnknown20.mUnknownC, block, (LocoBlendSet_t *)block->mpUnknownC, entries);
    else PlayerLocoSetCycleDuration(block->mUnknown20.mUnknownC, block, (LocoBlendSet_t *)block->mpUnknownC, entries);
}

static inline float AnimEntryGetRate(Record_800D81C8 *pEntry)
{
    return pEntry->mUnknown4C.mUnknown4 / ((float)((unsigned char *)pEntry->mUnknown4C.mpUnknown0)[0] * 0.0625f);
}

int PlayerLocoCyclePhase(Table_80089904 *table, unsigned short key, FEPlyrModel_t *record,
                 Record_800D81C8 *entries, Object_80039F5C *p, unsigned int phase)
{
    unsigned char frames = 8;
    Vector_80039F5C left, right;
    int scratch[3];
    unsigned char value = 0;
    int index;
    int mode;
    Object_80039F5C *other;
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown792, key);
    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        mode = PlayerLocoGetStartSide(p, 1, 0);
        other = BallGetCurrentHolder();
        int team = fn_80178308();
        int flag = 1;
        if (fn_800AD9B4() == 3) {
            flag = 0;
        }
        block->mUnknown3C = PlayerLocoGetPrimaryCategory(p, team, flag, &value);
        block->mUnknown3D = PlayerLocoGetSecondaryCategory(p, other, team, flag, value);
        PlayerLocoSelectStates(table, block, p, mode);
        block->mUnknown4 = 1.0f;
        index = PlayerLocoGetBlendIndex(p, block->mpUnknownC);
        block->mUnknown20.mUnknown14Half = index;
        PlayerLocoStartBlendPair((LocoBlendSet_t *)block->mpUnknownC, block, p,
                   block->mUnknown20.mUnknown16, (signed char)index, key, record, entries);
        block->mUnknown20.mUnknown8Bytes[0] = 255;
        block->mUnknown20.mUnknown8Bytes[1] = 255;
        fn_8009BEFC(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "lankle"), &left, scratch);
        fn_8009BEFC(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "rankle"), &right, scratch);
        if (mode) {
            fn_801BA6BC(&entries[block->mUnknown0], 1);
            fn_801BA6BC(&entries[block->mUnknown1], 1);
            if (!(left.mZ >= right.mZ)) {
                Record_800D81C8 *entry = AnimEntryAt(entries, block->mUnknown0);
                float duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
                float scale;
                scale = AnimEntryGetRate(&entries[block->mUnknown0]);
                scale *= 0.6f;
                fn_801BA650(entry, duration * scale, p);
                entry = AnimEntryAt(entries, block->mUnknown1);
                duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
                scale = AnimEntryGetRate(&entries[block->mUnknown1]);
                scale *= 0.6f;
                fn_801BA650(entry, duration * scale, p);
            }
        } else if (!(right.mZ >= left.mZ)) {
            Record_800D81C8 *entry = AnimEntryAt(entries, block->mUnknown0);
            float duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
            float scale;
            scale = AnimEntryGetRate(&entries[block->mUnknown0]);
            scale *= 0.6f;
            fn_801BA650(entry, duration * scale, p);
            entry = AnimEntryAt(entries, block->mUnknown1);
            duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
            scale = AnimEntryGetRate(&entries[block->mUnknown1]);
            scale *= 0.6f;
            fn_801BA650(entry, duration * scale, p);
        }
        block->mUnknown20.mUnknownC = p->mMotion.mUnknown28;
        PlayerLocoUpdateCycle(p, block, entries);
        break;
    }
    case 1:
        break;
    case 2: {
        if (fn_801BE648(p->mpUnknown792) != key) return 0;
        other = BallGetCurrentHolder();
        if ((signed char)block->mUnknown3A[1] <= 0) {
            mode = fn_801BA6B0(&entries[block->mUnknown0]);
            unsigned char changed = PlayerLocoUpdateCategories(table, block, p, other, mode) | PlayerLocoSelectBlendSet(p, block, &frames);
            index = PlayerLocoGetBlendIndex(p, block->mpUnknownC);
            if ((index != block->mUnknown20.mUnknown14Half || changed) && block->mUnknown20.mUnknown14Half != -1) {
                PlayerLocoSwitchBlendPair((LocoBlendSet_t *)block->mpUnknownC, block, p,
                           block->mUnknown20.mUnknown16, (signed char)index, key, record, entries, frames);
                fn_801BA6BC(&entries[block->mUnknown0], mode);
                fn_801BA6BC(&entries[block->mUnknown1], mode);
                if (mode == 1) {
                    if (PlayerLocoGetStartSide(p, 0, 1) == 0) {
                        Record_800D81C8 *entry = AnimEntryAt(entries, block->mUnknown0);
                        float duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
                        float scale;
                        scale = AnimEntryGetRate(&entries[block->mUnknown0]);
                        scale *= 0.5f;
                        fn_801BA650(entry, duration * scale, p);
                        entry = AnimEntryAt(entries, block->mUnknown1);
                        duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
                        scale = AnimEntryGetRate(&entries[block->mUnknown1]);
                        scale *= 0.5f;
                        fn_801BA650(entry, duration * scale, p);
                        fn_801BA6BC(&entries[block->mUnknown0], 0);
                        fn_801BA6BC(&entries[block->mUnknown1], 0);
                    }
                } else if (PlayerLocoGetStartSide(p, 0, mode) == 1) {
                    Record_800D81C8 *entry = AnimEntryAt(entries, block->mUnknown0);
                    float duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
                    float scale;
                    scale = AnimEntryGetRate(&entries[block->mUnknown0]);
                    scale *= 0.5f;
                    fn_801BA650(entry, duration * scale, p);
                    entry = AnimEntryAt(entries, block->mUnknown1);
                    duration = AnimSeqGetLife(entry->mUnknown4C.mpUnknown0);
                    scale = AnimEntryGetRate(&entries[block->mUnknown1]);
                    scale *= 0.5f;
                    fn_801BA650(entry, duration * scale, p);
                    fn_801BA6BC(&entries[block->mUnknown0], 1);
                    fn_801BA6BC(&entries[block->mUnknown1], 1);
                }
                block->mUnknown20.mUnknown14Half = index;
                block->mUnknown3A[1] = block->mUnknown3A[0] = frames;
            }
        } else if (p == other) {
            unsigned char state = p->mUnknown528.mUnknown15;
            if (state != 6 && state != 8 && state != 7 && state != 9 &&
                fn_800D78C4(p, key) != p->mUnknown776) p->mUnknown778 = -1;
        }
        block->mUnknown20.mUnknownC = p->mMotion.mUnknown28;
        if ((signed char)block->mUnknown3A[1] > 0) {
            block->mUnknown3A[1]--;
            PlayerLocoSetFadeFraction(block, (float)(signed char)block->mUnknown3A[0], (float)(signed char)block->mUnknown3A[1]);
            PlayerLocoFadeOldPair(block, record, entries);
        } else {
            block->mUnknown3A[0] = 0;
            block->mUnknown4 = 1.0f;
        }
        PlayerLocoUpdateCycle(p, block, entries);
        break;
    }
    case 3:
        if (p->mIdBytes[3] == 1 && p->mpState->mId != 50 && PlayerLocoNotInState84(p)) {
            fn_800ADBC0(p, 1, 8, 0);
            fn_800ADBC0(p, 1, 8, 1);
        }
        return 0;
    default: return 0;
    }
    return 0;
}


unsigned char PlayerLocoGetRunCategory(unsigned short index)
{
    return _PlayerLoco_aRunCategories[index];
}

/* Payload of the turn-in-place animation state. */
struct LocoTurnBlock_t {
    unsigned char mUnknown0;
    int mUnknown4;
    int mUnknown8;
    Point_8017886C mUnknownC;
};

/* True when the first two bytes of the key match those of the reference;
   0xFF in the key matches anything. */
unsigned char PlayerLocoKeyMatches(Key_80110630 *pKey, Key_80110630 *pRef)
{
    unsigned char *pA = &pKey->mUnknown0;
    unsigned char *pB = &pRef->mUnknown0;

    for (int i = 0; i < 2; i++) {
        if (pA[i] != 0xFF && pB[i] != pA[i]) {
            return 0;
        }
    }
    return 1;
}

/* Picks the turn animation whose angle window holds the turn the player
   needs and returns its table index, with the turn, the playback scale and
   the offset the turn moves the player by. */
unsigned short PlayerLocoSelectTurnEntry(Table_80089904 *table, Object_80039F5C *p, int *pTurn, float *pScale,
                                         Point_8017886C *pOffset)
{
    Point_8017886C dir;
    Point_8017886C off;
    Info_80089904 *best;
    unsigned int bestIndex;
    unsigned int i;
    int facing;
    int heading;
    int diff;
    signed char side;

    dir.mX = (float)(signed char)p->mUnknown1008.mUnknown2 * 0.25f;
    dir.mY = (float)(signed char)p->mUnknown1011 * 0.5f;
    facing = p->mMotion.mFacing & 0xFFFFFF;
    fn_80227690(&dir, &dir, (Point_8017886C *)&p->mMotion.mPos);
    heading = dir.Heading();
    if (p->mUnknown1008.mUnknown1 == 1 && (p->mpState->mId == 7 || p->mpState->mId == 63)) {
        heading = p->mUnknown352Heading;
    }
    *pTurn = 0;
    *pScale = 1.0f;
    pOffset->mY = 0.0f;
    pOffset->mX = 0.0f;
    best = 0;
    bestIndex = 0;
    diff = MathAngleDiff(facing, heading);
    side = ((heading - facing) & 0xFFFFFF) <= 0x800000 ? 1 : -1;
    for (i = 0; i < table->mCount; i++) {
        Info_80089904 *info = table->mEntries[i].mpInfo;

        if (!PlayerLocoKeyMatches(&p->mUnknown1008, &info->mKey)) {
            continue;
        }
        if (diff < info->mUnknown16 || diff > info->mUnknown20) {
            continue;
        }
        if ((side > 0 && info->mUnknown12 > 0) || (side < 0 && info->mUnknown12 < 0)) {
            if (!best || fn_802372EC(0, 100) < 50) {
                best = info;
                bestIndex = i;
            }
        }
    }
    if (!best || bestIndex >= table->mCount) {
        return 0;
    }
    int turn = best->mUnknown12 < 0 ? -best->mUnknown12 : best->mUnknown12;
    *pScale = (float)turn / (float)diff;
    if (*pScale < 1.0f) {
        *pScale = 1.0f;
    }
    *pTurn = MathAngleDiff(best->mUnknown12 < 0 ? -best->mUnknown12 : best->mUnknown12, diff);
    int target = (best->mUnknown12 + facing) & 0xFFFFFF;
    off.mX = best->mUnknown28;
    off.mY = best->mUnknown32;
    fn_80227384(&off, &off, p->mMotion.mFacing);
    fn_80227690(&dir, &dir, &off);
    if (((target - dir.Heading()) & 0xFFFFFF) < 0x800000) {
        *pTurn = -*pTurn;
    }
    float rate = 1.0f / best->mUnknown24;
    *pTurn = (int)((float)*pTurn * rate);
    fn_80227248(pOffset, &dir, rate);
    return bestIndex;
}

/* Turn-in-place animation state: phase 0 starts the turn animation picked
   by PlayerLocoSelectTurnEntry, phase 2 applies the turn once the state is
   current. */
int PlayerLocoTurnPhase(Table_80089904 *table, unsigned short key, FEPlyrModel_t *record,
                        Record_800D81C8 *entries, Object_80039F5C *p, unsigned int phase)
{
    LocoTurnBlock_t *block = (LocoTurnBlock_t *)fn_801BE60C(p->mpUnknown792, key);
    int turn;
    float scale;

    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        int index = PlayerLocoSelectTurnEntry(table, p, &turn, &scale, &block->mUnknownC);
        block->mUnknown4 = fn_801BA2A8(record, entries, table->mEntries[index].mUnknown0,
                                       table->mEntries[index].mUnknown2, key, p, 1.0f);
        block->mUnknown8 = turn;
        block->mUnknown0 = p->mUnknown1008.mUnknown1 == 1;
        p->mFlags &= ~4;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) != key) {
            return 0;
        }
        p->mMotion.mFacing = (p->mMotion.mFacing + block->mUnknown8) & 0xFFFFFF;
        if (!block->mUnknown0) {
            Record_800D81C8 *pEntry = &p->mpUnknown800[block->mUnknown4];
            pEntry->mUnknownC = (pEntry->mUnknownC + block->mUnknown8) & 0xFFFFFF;
        } else {
            fn_80227638((Point_8017886C *)&p->mMotion.mPos, (Point_8017886C *)&p->mMotion.mPos,
                        &block->mUnknownC);
        }
        if (p->mFlags & 4) {
            p->mMotion.mFacing &= 0xFFFFFF;
            block->mUnknown8 = 0;
        }
        break;
    }
    return 0;
}

int PlayerLocoMoveCmdPhase(Table_80089904 *table, unsigned short key, FEPlyrModel_t *record,
                 Record_800D81C8 *entries, Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown792, key);
    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        block->mUnknown1 = p->mUnknown1008.mUnknown0;
        block->mUnknown2 = p->mUnknown1008.mUnknown1;
        int index = fn_8009C4B0(table, &p->mUnknown1008);
        block->mUnknown0 = fn_801BA2A8(record, entries, table->mEntries[index].mUnknown0,
                                       table->mEntries[index].mUnknown2, key, p, 1.0f);
        if (block->mUnknown2 == 2 && p->mUnknown528.mUnknown0 != 0.0f)
            AnimSeqSetSpeed(&entries[block->mUnknown0].mUnknown4C, MathInverse(p->mUnknown528.mUnknown0));
        break;
    }
    case 1:
        break;
    case 2:
        if (block->mUnknown2 == 2 && p->mUnknown528.mUnknown0 != 0.0f) {
            p->mpUnknown800[block->mUnknown0].mUnknownC = p->mUnknown528.mUnknown8;
            AnimSeqSetSpeed(&entries[block->mUnknown0].mUnknown4C, MathInverse(p->mUnknown528.mUnknown0));
        }
        break;
    }
    return 0;
}

void PlayerLocoTrimBlendEntries(FEPlyrModel_t *record, Record_800D81C8 *entries, int)
{
    for (unsigned int i = 0; i <= 3; i++) {
        PlayerLocoTrimKey_t *pKey = &_PlayerLoco_aTrimKeys[i];
        unsigned int count = fn_801BA568((AnimHeader_t *)record, entries, pKey->mUnknown2);
        while (count > 2) {
            unsigned int selected = 0xFFFF;
            float best = 1.0f;
            for (unsigned int j = 0; j < count; j++) {
                PlayerLocoTrimKey_t *pLoopKey = &_PlayerLoco_aTrimKeys[i];
                unsigned int index = fn_801BA5A8((AnimHeader_t *)record, entries, pLoopKey->mUnknown2, (unsigned short)j);
                float weight = entries[index].mUnknown30.mUnknown0;
                if (!(best <= weight)) {
                    best = weight;
                    selected = index;
                }
            }
            fn_801BA384((AnimHeader_t *)record, entries, selected);
            count--;
        }
    }
}

int PlayerLocoFindSampleIndex(Object_801BBD5C *pObject, float value)
{
    int index = 0;
    while (index < (int)(pObject->mCount - 2)) {
        float end = pObject->mValues[index + 1].mValue * gFrameTimeScale;
        if (!(fabsf(end) >= 0.000001f)) end = 0.0f;
        if (!(end <= value)) break;
        index++;
    }
    return index;
}

void PlayerLocoStartBlendPair(LocoBlendSet_t *object, Block_801BE60C *block, Object_80039F5C *p,
                 int value, int index, int key, FEPlyrModel_t *record,
                 Record_800D81C8 *entries)
{
    PlayerLocoTrimBlendEntries(record, entries, key);
    int first = object->mUnknown24[index].mUnknown8;
    int second = object->mUnknown24[index + 1].mUnknown8;
    block->mUnknown0 = fn_801BA2A8(record, entries, (unsigned short)value, first, key, p, 1.0f);
    block->mUnknown1 = fn_801BA2A8(record, entries, (unsigned short)value, second, key, p, 1.0f);
    block->mUnknown2 = 255;
    block->mUnknown3 = 255;
}

void PlayerLocoSwitchBlendPair(LocoBlendSet_t *pObject, Block_801BE60C *pBlock, Object_80039F5C *pRecord, int b,
                 int index, unsigned short d, void *a, Record_800D81C8 *pEntries, unsigned char flag)
{
    int first = fn_801BA2D0(a, pEntries, &pEntries[pBlock->mUnknown0]);
    int second = fn_801BA2D0(a, pEntries, &pEntries[pBlock->mUnknown1]);

    pBlock->mUnknown2 = pBlock->mUnknown0;
    pBlock->mUnknown3 = pBlock->mUnknown1;
    pBlock->mUnknown8 = pEntries[pBlock->mUnknown0].mUnknown30.mUnknown0;
    pBlock->mUnknown0 = first;
    pBlock->mUnknown1 = second;

    fn_801BA418(a, pEntries, pBlock->mUnknown0, b, pObject->mUnknown24[index].mUnknown8, d, pRecord);
    fn_801BF3C8(&pEntries[pBlock->mUnknown0].mUnknown30, 0, 0.0f, 0, 0.0f);
    fn_801BF4A8(&pEntries[pBlock->mUnknown0].mUnknown30, flag, -1.0f, 1.0f);
    fn_801BA418(a, pEntries, pBlock->mUnknown1, b, pObject->mUnknown24[index + 1].mUnknown8, d, pRecord);
    fn_801BF3C8(&pEntries[pBlock->mUnknown1].mUnknown30, 0, 0.0f, 0, 0.0f);
    fn_801BF4A8(&pEntries[pBlock->mUnknown1].mUnknown30, flag, -1.0f, 1.0f);
}

float PlayerLocoUpdateBlendWeights(int index, Block_801BE60C *pBlock, LocoBlendSet_t *pObject, Record_800D81C8 *pEntries,
                  float value)
{
    float start = pObject->mUnknown24[index].mUnknown4 * gFrameTimeScale;
    float ratio = (value - start) / (pObject->mUnknown24[index + 1].mUnknown4 * gFrameTimeScale - start);
    float t = ratio < 0.0f ? 0.0f : (ratio > 1.0f ? 1.0f : ratio);

    pObject->mUnknown24[index + 1].mUnknown0 = fabsf(pObject->mUnknown24[index + 1].mUnknown0);
    pObject->mUnknown24[index].mUnknown0 = fabsf(pObject->mUnknown24[index].mUnknown0);
    float result = (pObject->mUnknown24[index + 1].mUnknown0 - pObject->mUnknown24[index].mUnknown0) * t +
                   pObject->mUnknown24[index].mUnknown0;

    AnimSeqSetDuration(&pEntries[pBlock->mUnknown0].mUnknown4C, result);
    AnimSeqSetDuration(&pEntries[pBlock->mUnknown1].mUnknown4C, result);
    if (pBlock->mUnknown2 != 255) {
        AnimSeqSetDuration(&pEntries[pBlock->mUnknown2].mUnknown4C, result);
    }
    if (pBlock->mUnknown3 != 255) {
        AnimSeqSetDuration(&pEntries[pBlock->mUnknown3].mUnknown4C, result);
    }

    float first = 1.0f - t;
    first *= pBlock->mUnknown4;
    float second = t * pBlock->mUnknown4;
    float a = pEntries[pBlock->mUnknown0].mUnknown30.mUnknown0;
    float b = pEntries[pBlock->mUnknown1].mUnknown30.mUnknown0;
    if (a + b == 1.0f) {
        if (fabsf(a - first) > 0.33f || fabsf(b - second) > 0.33f) {
            first = (first - a) * 0.22f + a;
            second = b + (a - first);
        }
    }
    fn_801BF3C8(&pEntries[pBlock->mUnknown0].mUnknown30, 0, first, 0, first);
    fn_801BF3C8(&pEntries[pBlock->mUnknown1].mUnknown30, 0, second, 0, second);
    return result;
}

void PlayerLocoSetFadeFraction(Block_801BE60C *p, float a, float b)
{
    p->mUnknown4 = (a - b) / a;
}

void PlayerLocoFadeOldPair(Block_801BE60C *pBlock, void *a, Record_800D81C8 *pEntries)
{
    float weight = 1.0f - pBlock->mUnknown4;

    if (pBlock->mUnknown2 != 255) {
        if (weight != 0.0f) {
            fn_801BF3C8(&pEntries[pBlock->mUnknown2].mUnknown30, 0, weight * pBlock->mUnknown8, 0,
                        weight * pBlock->mUnknown8);
        } else {
            fn_801BA384((AnimHeader_t *)a, pEntries, pBlock->mUnknown2);
            pBlock->mUnknown2 = 255;
        }
    }
    if (pBlock->mUnknown3 != 255) {
        if (weight != 0.0f) {
            fn_801BF3C8(&pEntries[pBlock->mUnknown3].mUnknown30, 0, weight * (1.0f - pBlock->mUnknown8), 0,
                        weight * (1.0f - pBlock->mUnknown8));
        } else {
            fn_801BA384((AnimHeader_t *)a, pEntries, pBlock->mUnknown3);
            pBlock->mUnknown3 = 255;
        }
    }
}

int PlayerLocoFindTableEntry(Table_80089904 *pTable, int value, int a, unsigned char b)
{
    float best = 0.0f;
    int result = 0xFFFF;

    for (unsigned short i = 0; i < pTable->mCount; i++) {
        Info_80089904 *pInfo = pTable->mEntries[i].mpInfo;
        if (pInfo->mValue == a && pInfo->mUnknown6 == 1 && value >= pInfo->mUnknown16 &&
            value <= pInfo->mUnknown20) {
            float weight = 0.5f;
            if (pInfo->mType == b) {
                weight += weight;
            }
            if (weight > best) {
                best = weight;
                result = i;
            }
        }
    }
    if (result == 0xFFFF) {
        result = 0;
    }
    return result;
}

int PlayerLocoGetLowerAnkle(Object_80039F5C *p)
{
    Vector_80039F5C left, right;
    int scratch[3];
    fn_8009BEFC(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "lankle"), &left, scratch);
    fn_8009BEFC(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "rankle"), &right, scratch);
    int result = 1;
    if (!(left.mZ >= right.mZ)) result = 2;
    return result;
}

}
