/* Player state handlers: the state in which a player is engaged with an opponent (its enter,
   exit, update and input handlers), two update handlers shared by many player states, and the
   registration of the player handler table descriptors. */

#include <math.h>
#include <string.h>

#include "engine/cu_801B9F00.h"
#include "game/Queue_800EFE0C.h"
#include "game/Directions_8012430C.h"
#include "game/fn_80177FE0.h"
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/PlayBookTeam.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_800B65A0.h"
#include "game/Record_800B15FC.h"
#include "game/Input_800B6D34.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801BE60C.h"
#include "game/cu_80142BB4.h"
#include "game/Ball.h"

#include "game/PlyrModeState.h"

struct PlyrEngageKey_t { unsigned short mUnknown0, mKey; };
static PlyrEngageKey_t _PlyrEngage_aAnimKeys[43] = {
    {0, 55},
    {0, 61},
    {0, 49},
    {0, 56},
    {0, 50},
    {0, 66},
    {0, 59},
    {0, 107},
    {0, 106},
    {0, 63},
    {0, 62},
    {0, 52},
    {0, 51},
    {0, 60},
    {0, 54},
    {0, 53},
    {0, 25},
    {0, 79},
    {0, 150},
    {0, 149},
    {0, 151},
    {0, 148},
    {0, 147},
    {0, 146},
    {0, 123},
    {0, 120},
    {0, 121},
    {0, 119},
    {0, 125},
    {0, 118},
    {0, 131},
    {0, 130},
    {0, 124},
    {0, 122},
    {0, 241},
    {0, 242},
    {0, 183},
    {0, 182},
    {0, 184},
    {0, 161},
    {0, 231},
    {0, 233},
    {0, 243}
};
extern "C" {
extern unsigned char lbl_802DB280[], lbl_802DBBB0[];
Queue_800EFE0C _PlyrStates_qDefault = {98, 10, (Handlers_800EFC68 *)lbl_802DB280};
Queue_800EFE0C _PlyrStates_qAlternate = {2, 10, (Handlers_800EFC68 *)lbl_802DBBB0};
}

extern "C" {
Object_80039F5C *BallGetCurrentHolder(void);
int fn_80178320(void);

int fn_8010A2DC(Object_80039F5C *, int, short);

int fn_80178308(void);
void fn_8011E3EC(Object_80039F5C *, int);
void fn_8011E240(Object_80039F5C *);
void fn_8009BD2C(Object_80039F5C *, int *);
int AnimSeqHasOpcode(AnimSeq_t *, AnimScript_t *, unsigned short);
float AnimSeqGetOpcodeTime(AnimScript_t *, int);

float AnimSeqGetTime(AnimSeq_t *);
int fn_800E6AC8(Object_80039F5C *, int);
int fn_8011EC68(Object_80039F5C *, Object_80039F5C *);
float fn_8022781C(void *, void *);
int fn_800E815C(Object_80039F5C *, int, int);
int fn_800F0490(int, State_80039F5C *, int);
void fn_800F05E4(int, State_80039F5C *, Message_800F01CC *, Object_80039F5C *);
int fn_801CFE40(float, float);
int fn_800B7248(Input_800B6D34 *, Ball_t *, Object_80039F5C *, Object_80039F5C *);
int fn_800B7F34(Object_80039F5C *);
void fn_8003AB08(Object_80039F5C *, int);
void PlyrEngageReleaseControl(Object_80039F5C *);
void PlyrEngageShortenMessages(Object_80039F5C *, unsigned int);

void PlyrEngageReleaseControl(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    if (p->mIdBytes[2] == fn_80178308())
        fn_8011E240(p);
    else {
        Object_80039F5C *other = fn_8009BCE8(&p->mUnknown1036);
        if (other)
            fn_8011E240(other);
    }
}

void PlyrEngageShortenMessages(Object_80039F5C *p, unsigned int count)
{
    int index = fn_800F06F4(0, p->mpState, 31, 0xFFFF);
    if (index != 0xFFFF) {
        unsigned char n = p->mpState[index].mUnknown1;
        if (n) {
            if (n <= count)
                count = n - 1;
            p->mpState[index].mUnknown1 -= count;
        }
    }
    index = fn_800F06F4(0, p->mpState, 33, 0xFFFF);
    if (index != 0xFFFF) {
        unsigned char n = p->mpState[index].mUnknown1;
        if (n) {
            if (n <= count)
                count = n - 1;
            p->mpState[index].mUnknown1 -= count;
        }
    }
}

int PlyrEngageEnter(Object_80039F5C *p)
{
    p->mUnknown9[0] = 1;
    State_80039F5C *m = p->mpState;
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800,
               (m->mUnknown1 << 8) | m->mUnknown2, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    m = p->mpState;
    Object_80039F5C *other = fn_80039F5C(p->mIdBytes[2] ^ 1, m->mUnknown3[0]);
    fn_8009BD2C(other, &s->mUnknown0Word);
    fn_80143E14(p, other);
    unsigned short n = 0;
    unsigned short index;
    do {
        PlyrEngageKey_t *key = &_PlyrEngage_aAnimKeys[n];
        index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, key->mKey, 0);
        ++n;
    } while (n <= 42 && index == 0xFFFF);
    s->mUnknown6 = index;
    if (index == 0xFFFF)
        s->mUnknown4 = 0;
    else {
        AnimSeq_t seq;
        if (AnimSeqHasOpcode(&seq, p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0xC004))
            s->mUnknown4 = (short)AnimSeqGetOpcodeTime(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0xC004);
        else
            s->mUnknown4 = (short)AnimSeqGetLife(p->mpUnknown800[index].mUnknown4C.mpUnknown0);

    }
    s->mUnknown8Bytes[0] = 0;
    s->mUnknown8Bytes[1] = 0;
    s->mUnknown8Bytes[2] = 0;
    s->mUnknown8Bytes[3] = 0;
    s->mUnknownCByte = 0;
    s->mUnknown10 = 0;
    return 0;
}

int PlyrEngageUpdate(Object_80039F5C *p)
{
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    Object_80039F5C *other = fn_8009BCE8(&s->mUnknown0Word);
    s->mUnknown8Bytes[3] = 1;
    ++s->mUnknown10;
    int result = 0;
    if ((unsigned int)(p->mUnknown1032 - 6) <= 1)
        s->mUnknown8Bytes[0] = 1;
    if (p->mFlags & 0x800) {
        s->mUnknown8Bytes[0] = 0;
        PlyrEngageReleaseControl(p);
        if (!s->mUnknown8Bytes[1] && p->mIdBytes[2] == fn_80178308() && fn_801BE648(p->mpUnknown792) == 56) {
            Record_800B15FC *record = fn_800B15FC();
            fn_8009BD2C(p, &record->mUnknown0);
            record->mUnknownC = p->mMotion.mPos.mX;
            record->mUnknown10 = p->mMotion.mPos.mY;
            record->mUnknown14 = 37;
            fn_800B1508();
            s->mUnknown8Bytes[1] = 1;
        }
        if (!s->mUnknown8Bytes[2] && p->mIdBytes[2] == fn_80178308() && fn_801BE648(p->mpUnknown792) != 56)
            s->mUnknown8Bytes[2] = 1;
    }
    if (other && other->mpState->mId == 32 && fn_8009BCE8(&other->mUnknown336) == p) {
        fn_80143E14(p, other);
        fn_80143E14(other, p);
    }
    if (p->mUnknown9[0] != 1) {
        p->mUnknown772 = 1.0f;
        PlyrEngageReleaseControl(p);
        fn_80143EBC(p, other);
        s->mUnknown8Bytes[0] = 1;
        Message_800F01CC m;
        fn_801C1F94(&m, 0, 4);
        m.mId = 11;
        m.mUnknown1[0] = p->mUnknown9[0];
        fn_800F05E4(0, p->mpState, &m, p);
    }
    if ((unsigned int)s->mUnknown10 % 5 == 0 && (unsigned int)s->mUnknown10 > 4 &&
        p->mIdBytes[2] == fn_80178320() && !(p->mFlags & 0x400) && !s->mUnknownCByte &&
        (fn_801BE648(p->mpUnknown792) == 55 || fn_801BE648(p->mpUnknown792) == 49 ||
         fn_801BE648(p->mpUnknown792) == 52 || fn_801BE648(p->mpUnknown792) == 150 ||
         fn_801BE648(p->mpUnknown792) == 147) && (p->mUnknown1032 == 4 || p->mUnknown1032 == 6)) {
        Object_80039F5C *ball = BallGetCurrentHolder();
        if (ball) {
            int lower = ball->mMotion.mPos.mY + 2.0f > p->mMotion.mPos.mY;
            if (!ball->mUnknown2914 && !(ball->mFlags & 0x8000)) {
                if (fn_800E6AC8(p, 8)) {
                    s->mUnknownCByte = 1;
                    return 0;
                }
            } else if (!ball->mUnknown2914 || !lower) {
                if (fn_800E6AC8(p, 4)) {
                    s->mUnknownCByte = 1;
                    return 0;
                }
            } else if (!(fn_8022781C(&p->mMotion.mPos, &ball->mMotion.mPos) > 5.0f)) {
                Object_80039F5C *linked = fn_8009BCE8(&p->mUnknown1036);
                if (linked) {
                    p->mUnknown344 = 1;
                    linked->mUnknown344 = 1;
                    if (fn_800E6AC8(p, 5)) {
                        s->mUnknownCByte = 1;
                        return 0;
                    }
                }
            } else {
                Object_80039F5C *linked = fn_8009BCE8(&p->mUnknown1036);
                if (linked && fn_8011EC68(linked, p)) {
                    s->mUnknownCByte = 1;
                    return 0;
                }
            }
        }
    }
    if (p->mFlags & 4) {
        if (fn_801BE648(p->mpUnknown792) == 242 && p->mIdBytes[2] == fn_80178320()) {
            p->mUnknown772 = 1.0f;
            PlyrEngageReleaseControl(p);
            fn_80143EBC(p, other);
            s->mUnknown8Bytes[0] = 1;
            if (fn_800E815C(p, 2, 0))
                fn_800F0490(0, p->mpState, 32);
            p->mFlags &= ~4;
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown772 = 1.0f;
            PlyrEngageShortenMessages(p, (unsigned short)s->mUnknown4);
            p->mFlags &= ~0x800;
            fn_80143EBC(p, other);
            if (p->mUnknown1032 == 5) {
                p->mUnknown1032 = 6;
                s->mUnknown8Bytes[0] = 1;
            }
            PlyrEngageReleaseControl(p);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 0.4f;
            result = 1;
        }
    }
    return result;
}

int PlyrEngageExit(Object_80039F5C *p)
{
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    int result = 0;
    if (s->mUnknown8Bytes[0] || p->mUnknown1032 == 6) {
        unsigned short index = s->mUnknown6;
        if (index != 0xFFFF)
            PlyrEngageShortenMessages(p, (unsigned int)AnimSeqGetTime(&p->mpUnknown800[index].mUnknown4C));
        p->mUnknown772 = 1.0f;
        PlyrEngageReleaseControl(p);
        Object_80039F5C *other = fn_8009BCE8(&s->mUnknown0Word);
        if (other)
            fn_80143EBC(p, other);
        result = 1;
    }
    return result;
}

int PlyrEngageInput(Object_80039F5C *p)
{
    Input_800B6D34 input;
    Vector_80039F5C dir;
    dir.mY = 0.0f;
    dir.mX = 0.0f;
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    if (p->mIdBytes[2] == fn_80178320() &&
        (fn_801BE648(p->mpUnknown792) == 55 || fn_801BE648(p->mpUnknown792) == 49 || fn_801BE648(p->mpUnknown792) == 52)) {
        fn_800B6D34(p, &input);
        if (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f) {
            dir.mX = input.mUnknown4;
            dir.mY = input.mUnknown8;
        } else {
            if (input.mUnknown0 & 1) dir.mY = 1.0f;
            if (input.mUnknown0 & 2) dir.mY = -1.0f;
            if (input.mUnknown0 & 4) dir.mX = -1.0f;
            if (input.mUnknown0 & 8) dir.mX = 1.0f;
        }
        if (dir.mX != 0.0f || dir.mY != 0.0f)
            p->mUnknown512.mUnknown4 = fn_801CFE40(dir.mY, dir.mX);
        if (s->mUnknown8Bytes[3]) {
            int result = fn_800B7248(&input, BallGetCurrent(), p, p);
            if (result == 1)
                return 0;
        }
    }
    return fn_800B7F34(p);
}

int PlyrStateUpdateDefault(Object_80039F5C *p)
{
    fn_8010A2DC(p, 0, -1);
    return 0;
}

int PlyrStateUpdateClear(Object_80039F5C *p)
{
    fn_8003AB08(p, 0);
    p->mpState[1].mId = 0;
    return 0;
}

void PlyrStatesRegister(int kind, int enabled)
{
    if (enabled)
        fn_800EFE0C(kind, &_PlyrStates_qAlternate);
    else
        fn_800EFE0C(kind, &_PlyrStates_qDefault);
}

}
