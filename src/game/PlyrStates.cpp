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
#include "game/PlyrCollide.h"
#include "game/Ball.h"

#include "game/PlyrModeState.h"

/* One record of the player state handler tables: the enter, exit, update, input,
   notify and message-mirror slots, called through blrl. */
struct PlyrStateHandlers_t {
    void *mpSlots[6];
};

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
extern PlyrStateHandlers_t _PlyrStates_aHandlers[98], _PlyrStates_aAltHandlers[2];
Queue_800EFE0C _PlyrStates_qDefault = {98, 10, (Handlers_800EFC68 *)_PlyrStates_aHandlers};
Queue_800EFE0C _PlyrStates_qAlternate = {2, 10, (Handlers_800EFC68 *)_PlyrStates_aAltHandlers};
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
    PlyrCollideAddExempt(p, other);
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
        PlyrCollideAddExempt(p, other);
        PlyrCollideAddExempt(other, p);
    }
    if (p->mUnknown9[0] != 1) {
        p->mUnknown772 = 1.0f;
        PlyrEngageReleaseControl(p);
        PlyrCollideRemoveExempt(p, other);
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
            PlyrCollideRemoveExempt(p, other);
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
            PlyrCollideRemoveExempt(p, other);
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
            PlyrCollideRemoveExempt(p, other);
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

extern "C" {
/* Function declarations for the handler tables (register use of the slots only). */
void CarrierMoveEnter(void);
void CarrierMoveExit(void);
void CarrierMoveInput(void);
void CarrierMoveUpdate(void);
void DirectedRunEnter(void);
void DirectedRunUpdate(void);
void HandoffEnter(void);
void HandoffExit(void);
void HandoffMirrorMessage(void);
void HandoffUpdate(void);
void HuddleHoldExit(void);
void HuddleHoldUpdate(void);
void HuddleMoveAltEnter(void);
void HuddleMoveAltUpdate(void);
void HuddleMoveEnter(void);
void HuddleMoveUpdate(void);
void OptionRunEnter(void);
void OptionRunExit(void);
void OptionRunInput(void);
void OptionRunMirror(void);
void OptionRunUpdate(void);
void PursueEnter(void);
void PursueExit(void);
void PursueNotify(void);
void PursueUpdate(void);
void QbPassEnter(void);
void QbPassUpdate(void);
void RouteRunEnter(void);
void RouteRunExit(void);
void RouteRunUpdate(void);
void TurnToPlayEnter(void);
void TurnToPlayExit(void);
void TurnToPlayInput(void);
void TurnToPlayNotify(void);
void TurnToPlayUpdate(void);
void fn_800A5DD8(void);
void fn_800A5E20(void);
void fn_800B76E8(void);
void fn_800B78DC(void);
void fn_800B7E60(void);
void fn_800B7F88(void);
void fn_800DFCEC(void);
void fn_800DFD90(void);
void fn_800DFED0(void);
void fn_800E0574(void);
void fn_800E05C0(void);
void fn_800E068C(void);
void fn_800E0850(void);
void fn_800E0AD8(void);
void fn_800E0E8C(void);
void fn_800E13E4(void);
void fn_800E1438(void);
void fn_800E1544(void);
void fn_800E4494(void);
void fn_800E459C(void);
void fn_800E4EE4(void);
void fn_800E513C(void);
void fn_800E6F48(void);
void fn_800E705C(void);
void fn_800E7330(void);
void fn_800E8420(void);
void fn_800E8554(void);
void fn_800E86E4(void);
void fn_800E8740(void);
void fn_800E8748(void);
void fn_800E8BE8(void);
void fn_800E8E04(void);
void fn_800E9E18(void);
void fn_800E9FC0(void);
void fn_800E9FD8(void);
void fn_800EA1D0(void);
void fn_800EA1D8(void);
void LooseBallEnter(void);
void LooseBallExit(void);
void LooseBallUpdate(void);
void LooseBallInput(void);
void fn_800F08F8(void);
void fn_800F0900(void);
void fn_800F0908(void);
void fn_800F0C6C(void);
void fn_800F0CCC(void);
void fn_800F0E10(void);
void fn_800F23EC(void);
void fn_800F24D8(void);
void fn_800F268C(void);
void fn_800F2AA0(void);
void fn_800F2B8C(void);
void fn_800F2C14(void);
void fn_800F4A74(void);
void fn_800F4AD4(void);
void fn_800F6158(void);
void fn_800F62A4(void);
void fn_800F6370(void);
void fn_800F6790(void);
void fn_800F67CC(void);
void fn_800FA0DC(void);
void fn_800FA300(void);
void fn_800FAD10(void);
void fn_800FCA78(void);
void fn_800FCC24(void);
void fn_800FD2AC(void);
void fn_800FD3F0(void);
void fn_800FD41C(void);
void fn_800FD580(void);
void fn_800FD650(void);
void fn_800FD708(void);
void fn_800FDA58(void);
void fn_800FDAC8(void);
void fn_800FDFD8(void);
void fn_800FEFD4(void);
void fn_800FF094(void);
void fn_800FF538(void);
void fn_800FF7A8(void);
void fn_800FF7F4(void);
void fn_800FF860(void);
void fn_800FFDFC(void);
void fn_800FFE30(void);
void fn_800FFF78(void);
void fn_800FFFA0(void);
void fn_80101CB4(void);
void fn_801021C0(void);
void fn_80102470(void);
void fn_80102664(void);
void fn_8010279C(void);
void fn_80105898(void);
void fn_80105AF4(void);
void fn_80105DF0(void);
void fn_80106794(void);
void fn_80109150(void);
void fn_80109248(void);
void fn_8010A4E8(void);
void fn_8010A640(void);
void fn_8010AEA0(void);
void fn_8010AF48(void);
void fn_8010AFB8(void);
void fn_8010B1B4(void);
void fn_8010BA00(void);
void fn_8010BA90(void);
void fn_8010BC48(void);
void fn_8010BED4(void);
void fn_8010BF5C(void);
void fn_8010CAE8(void);
void fn_8010CB58(void);
void fn_8010D004(void);
void fn_8010D090(void);
void fn_8010D6D4(void);
void fn_8010D734(void);
void fn_8010F43C(void);
void fn_8010F654(void);
void fn_8010FB10(void);
void fn_8010FB4C(void);
void fn_8010FC40(void);
void fn_8010FD8C(void);
void fn_8010FD94(void);
void fn_8010FE40(void);
void fn_80110078(void);
void fn_801100A0(void);
void fn_801108D4(void);
void fn_801109A4(void);
void fn_80110B00(void);
void fn_80111104(void);
void fn_801111E8(void);
void fn_801112D8(void);
void fn_80111314(void);
void fn_801113DC(void);
void fn_80111528(void);
void fn_80111580(void);
void fn_80111794(void);
void fn_801117F8(void);
void fn_80111964(void);
void fn_80111974(void);
void fn_80111F80(void);
void fn_80111FBC(void);
void fn_80112E10(void);
void fn_80112E8C(void);
void fn_80112F8C(void);
void fn_80113478(void);
void fn_80113498(void);
void fn_80113510(void);
void fn_801135E4(void);
void fn_80113604(void);
void fn_80113680(void);
void fn_8011380C(void);
void fn_80113AAC(void);
void fn_80113B28(void);
void fn_80113C20(void);
void fn_80113E74(void);
void fn_801147D4(void);
void fn_80114838(void);
void fn_80116B98(void);
void fn_80116C34(void);
void fn_801170A0(void);
void fn_80118210(void);
void fn_801182C8(void);
void fn_80118778(void);
void fn_80125304(void);
void fn_801253A8(void);
void fn_80125494(void);
void fn_801254C8(void);
void fn_80125508(void);
void fn_80125DF0(void);
void fn_80125E20(void);
void GetOpenEnter(void);
void GetOpenUpdate(void);
void PlayerCutEnter(void);
void PlayerCutUpdate(void);
void PlayerCutExit(void);
void PlayerCutMirrorMessage(void);
void CarrierRunEnter(void);
void CarrierRunExit(void);
void CarrierRunUpdate(void);
void CarrierRunNotify(void);
void CarrierRunInput(void);
void fn_80133C50(void);
void fn_80133EE8(void);
void fn_80134370(void);
void fn_801343AC(void);

PlyrStateHandlers_t _PlyrStates_aHandlers[98] = {
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)CarrierRunEnter, (void *)CarrierRunExit, (void *)CarrierRunUpdate, (void *)CarrierRunInput, (void *)CarrierRunNotify, 0}},
    {{(void *)PursueEnter, (void *)PursueExit, (void *)PursueUpdate, (void *)fn_800A5E20, (void *)PursueNotify, 0}},
    {{(void *)fn_800FD2AC, (void *)fn_800FD3F0, (void *)fn_800FD41C, (void *)fn_800B7E60, (void *)fn_800FD650, (void *)fn_800FD708}},
    {{(void *)fn_800FD2AC, (void *)fn_800FD3F0, (void *)fn_800FD580, (void *)fn_800B76E8, (void *)fn_800FD650, (void *)fn_800FD708}},
    {{(void *)fn_800F2AA0, (void *)fn_800F2C14, (void *)fn_800F2B8C, (void *)fn_800B7F34, (void *)fn_800F0908, 0}},
    {{(void *)fn_800E8BE8, (void *)fn_800F0900, (void *)fn_800E8E04, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800FDA58, (void *)fn_800F0900, (void *)fn_800FDAC8, (void *)fn_800FDFD8, (void *)fn_800FF538, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010FC40, (void *)fn_800F0900, (void *)fn_8010FD8C, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800E9E18, (void *)fn_800E9FC0, (void *)fn_800E9FD8, (void *)fn_800EA1D8, (void *)fn_800EA1D0, 0}},
    {{(void *)TurnToPlayEnter, (void *)TurnToPlayExit, (void *)TurnToPlayUpdate, (void *)TurnToPlayInput, (void *)TurnToPlayNotify, 0}},
    {{(void *)fn_800E8420, (void *)fn_800E86E4, (void *)fn_800E8554, (void *)fn_800E8748, (void *)fn_800E8740, 0}},
    {{(void *)HuddleMoveEnter, (void *)fn_800F0900, (void *)HuddleMoveUpdate, (void *)fn_800F08F8, (void *)fn_800FF538, 0}},
    {{(void *)HuddleMoveAltEnter, (void *)fn_800F0900, (void *)HuddleMoveAltUpdate, (void *)fn_800F08F8, (void *)fn_800FF538, 0}},
    {{(void *)fn_80101CB4, (void *)fn_80102470, (void *)fn_801021C0, (void *)fn_80102664, (void *)fn_800F0908, 0}},
    {{(void *)fn_80113C20, (void *)fn_801147D4, (void *)fn_80113E74, (void *)fn_80114838, (void *)fn_800F0908, 0}},
    {{(void *)fn_80113680, (void *)fn_80113AAC, (void *)fn_8011380C, (void *)fn_80113B28, (void *)fn_800F0908, 0}},
    {{(void *)QbPassEnter, (void *)fn_800F0900, (void *)QbPassUpdate, (void *)fn_8010279C, (void *)fn_800F0908, 0}},
    {{(void *)RouteRunEnter, (void *)RouteRunExit, (void *)RouteRunUpdate, (void *)fn_800B7E60, (void *)fn_800F0908, (void *)fn_800FD708}},
    {{(void *)PlayerCutEnter, (void *)PlayerCutExit, (void *)PlayerCutUpdate, (void *)fn_800B7E60, (void *)fn_800F0908, (void *)PlayerCutMirrorMessage}},
    {{(void *)GetOpenEnter, (void *)fn_800F0900, (void *)GetOpenUpdate, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800FA0DC, (void *)fn_800F0900, (void *)fn_800FA300, (void *)fn_800A5DD8, (void *)fn_800F0908, (void *)fn_800FAD10}},
    {{(void *)fn_80111F80, (void *)fn_800F0900, (void *)fn_80111FBC, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_80109150, (void *)fn_800F0900, (void *)fn_80109248, (void *)fn_800B78DC, (void *)fn_800F0908, 0}},
    {{(void *)fn_80105898, (void *)fn_80106794, (void *)fn_80105AF4, (void *)fn_800F08F8, (void *)fn_800F0908, (void *)fn_80105DF0}},
    {{(void *)HandoffEnter, (void *)HandoffExit, (void *)HandoffUpdate, (void *)fn_800F08F8, (void *)fn_800F0908, (void *)HandoffMirrorMessage}},
    {{(void *)fn_8010CAE8, (void *)fn_800F0900, (void *)fn_8010CB58, (void *)fn_800F08F8, (void *)fn_800F0908, (void *)fn_800FD708}},
    {{(void *)fn_800E0850, (void *)fn_800E0E8C, (void *)fn_800E0AD8, (void *)fn_800B7F88, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)DirectedRunEnter, (void *)fn_800F0900, (void *)DirectedRunUpdate, (void *)fn_800A5DD8, (void *)fn_800F0908, (void *)fn_800FD708}},
    {{(void *)fn_80133C50, (void *)fn_80134370, (void *)fn_80133EE8, (void *)fn_801343AC, (void *)fn_800F0908, 0}},
    {{(void *)PlyrEngageEnter, (void *)PlyrEngageExit, (void *)PlyrEngageUpdate, (void *)PlyrEngageInput, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010F43C, (void *)fn_8010FB10, (void *)fn_8010F654, (void *)fn_8010FB4C, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F23EC, (void *)fn_800F0900, (void *)fn_800F24D8, (void *)fn_800F268C, (void *)fn_800F0908, 0}},
    {{(void *)fn_801108D4, (void *)fn_800F0900, (void *)fn_801109A4, (void *)fn_80110B00, (void *)fn_800F0908, 0}},
    {{(void *)CarrierMoveEnter, (void *)CarrierMoveExit, (void *)CarrierMoveUpdate, (void *)CarrierMoveInput, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_80116B98, (void *)fn_800F0900, (void *)fn_80116C34, (void *)fn_800A5DD8, (void *)fn_800F0908, (void *)fn_801170A0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800E4494, (void *)fn_800E4EE4, (void *)fn_800E459C, (void *)fn_800E513C, (void *)fn_800F0908, 0}},
    {{(void *)fn_80111104, (void *)fn_801112D8, (void *)fn_801111E8, (void *)fn_80111314, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F6158, (void *)fn_800F6790, (void *)fn_800F6370, (void *)fn_8010FB4C, (void *)fn_800F0908, (void *)fn_800F67CC}},
    {{(void *)fn_800F0900, (void *)fn_800F0900, (void *)fn_800F0900, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800E0574, (void *)fn_800E068C, (void *)fn_800E05C0, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800DFCEC, (void *)fn_800DFD90, (void *)fn_800DFED0, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800E6F48, (void *)fn_800F0900, (void *)fn_800E705C, (void *)fn_800E7330, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F0C6C, (void *)fn_800F0900, (void *)fn_800F0CCC, (void *)fn_800F08F8, (void *)fn_800F0908, (void *)fn_800F0E10}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010D6D4, (void *)fn_800F0900, (void *)fn_8010D734, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)LooseBallEnter, (void *)LooseBallExit, (void *)LooseBallUpdate, (void *)LooseBallInput, (void *)fn_800F0908, 0}},
    {{(void *)fn_801113DC, (void *)fn_80111580, (void *)fn_800E9FD8, (void *)fn_80111528, (void *)fn_800EA1D0, 0}},
    {{(void *)fn_80111794, (void *)fn_80111964, (void *)fn_801117F8, (void *)fn_80111974, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800FCA78, (void *)fn_800F0900, (void *)fn_800FCC24, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010A4E8, (void *)fn_8010AEA0, (void *)fn_8010A640, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800FEFD4, (void *)fn_800F0900, (void *)fn_800FF094, (void *)fn_800F08F8, (void *)fn_800FF538, 0}},
    {{(void *)fn_801100A0, (void *)fn_800F0900, (void *)fn_800F08F8, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010D004, (void *)fn_800FD3F0, (void *)fn_8010D090, (void *)fn_800F08F8, (void *)fn_800F0908, (void *)fn_800FD708}},
    {{(void *)fn_800FF7A8, (void *)fn_800FF860, (void *)fn_800FF7F4, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010AF48, (void *)fn_8010B1B4, (void *)fn_8010AFB8, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)HuddleHoldExit, (void *)HuddleHoldUpdate, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F62A4, (void *)fn_800F6790, (void *)fn_800F6370, (void *)fn_8010FB4C, (void *)fn_800F0908, (void *)fn_800F67CC}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)PlyrStateUpdateDefault, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_801135E4, (void *)fn_800F0900, (void *)fn_80113604, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010BED4, (void *)fn_800F0900, (void *)fn_8010BF5C, (void *)fn_800A5DD8, (void *)fn_800F0908, 0}},
    {{(void *)fn_80112E10, (void *)fn_800F0900, (void *)fn_80112E8C, (void *)fn_80112F8C, (void *)fn_800F0908, 0}},
    {{(void *)fn_8010FD94, (void *)fn_800F0900, (void *)fn_8010FE40, (void *)fn_80110078, (void *)fn_800F0908, 0}},
    {{(void *)fn_80113478, (void *)fn_800F0900, (void *)fn_80113498, (void *)fn_80113510, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F08F8, (void *)fn_800F08F8, (void *)PlyrStateUpdateClear, (void *)fn_800B7E60, (void *)fn_800F0908, 0}},
    {{(void *)fn_800FFDFC, (void *)fn_800FFF78, (void *)fn_800FFE30, (void *)fn_800B7E60, (void *)fn_800F0908, (void *)fn_800FFFA0}},
    {{(void *)OptionRunEnter, (void *)OptionRunExit, (void *)OptionRunUpdate, (void *)OptionRunInput, (void *)fn_800F0908, (void *)OptionRunMirror}},
    {{(void *)fn_80118210, (void *)fn_800F0900, (void *)fn_801182C8, (void *)fn_800A5DD8, (void *)fn_800F0908, (void *)fn_80118778}},
    {{(void *)fn_8010BA00, (void *)fn_8010BC48, (void *)fn_8010BA90, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800E13E4, (void *)fn_800E1544, (void *)fn_800E1438, (void *)fn_800B7F34, (void *)fn_800F0908, 0}},
    {{(void *)fn_800F4A74, (void *)fn_800F0900, (void *)fn_800F4AD4, (void *)fn_800A5DD8, (void *)fn_800F0908, 0}},
    {{(void *)fn_80125304, (void *)fn_80125494, (void *)fn_801253A8, (void *)fn_801254C8, (void *)fn_80125508, 0}},
    {{(void *)fn_80125DF0, (void *)fn_800F0900, (void *)fn_80125E20, (void *)fn_800B78DC, (void *)fn_800F0908, 0}},
};
PlyrStateHandlers_t _PlyrStates_aAltHandlers[2] = {
    {{(void *)fn_800F08F8, (void *)fn_800F0900, (void *)fn_800F08F8, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
    {{(void *)fn_800DFCEC, (void *)fn_800DFD90, (void *)fn_800DFED0, (void *)fn_800F08F8, (void *)fn_800F0908, 0}},
};
}
