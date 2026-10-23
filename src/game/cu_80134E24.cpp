#include "engine/cu_801B9F00.h"
#include "game/Queue_800EFE0C.h"
#include "game/Directions_8012430C.h"
#include "game/fn_80177FE0.h"
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/Team_80167A8C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_800B65A0.h"
#include "game/Record_800B15FC.h"
#include "game/Input_800B6D34.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801BE60C.h"
#include "game/cu_80142BB4.h"
#include "game/cu_80136B1C.h"

#include "game/State_80134E24.h"

struct Key_802DB1D4 { unsigned short mUnknown0, mKey; };
static Key_802DB1D4 keys_802DB1D4[43] = {
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
extern "C" float lbl_803EB188, lbl_803EB18C, lbl_803ECB08;
extern "C" Queue_800EFE0C lbl_803EB190, lbl_803EB198;
extern "C" unsigned char lbl_803EB168, lbl_803EB16A;
extern "C" float lbl_803EB184, lbl_802DB174[];
extern "C" unsigned char lbl_803EB169;
extern "C" {
Object_80039F5C *fn_80137B40(void);
void fn_80135CEC(Object_80039F5C *);
void fn_800D7A0C(Object_80039F5C *, int);
unsigned char fn_80168E00(int, unsigned char, unsigned char *);
unsigned int fn_802372EC(unsigned int, unsigned int);
int fn_80178320(void);
int fn_800AD9B4(void);
int fn_801481B0(void);
int fn_801483F8(void);
void fn_80148108(int);
void fn_8013FA8C(int);
void fn_8015A0D0(int);
void fn_800B8344(void);
void fn_8013474C(Object_80039F5C *);
int fn_8010A2DC(Object_80039F5C *, int, short);
void fn_80134C20(Object_80039F5C *, State_80134E24 *);
void fn_8012430C(Directions_8012430C *, int, Object_80039F5C *);
void fn_801344F8(Object_80039F5C *, float *);
float *fn_80134AD0(Object_80039F5C *, int *);
int fn_801CFFD0(int, int);
unsigned char fn_80135F14(Object_80039F5C *, Object_80039F5C *, int *, int, unsigned char *, unsigned char *);
int fn_801347D4(Object_80039F5C *, State_80134E24 *, Object_80039F5C **, unsigned char *, unsigned char *);
int fn_80177F70(void);
void fn_800C146C(Point_80167910 *, Object_80039F5C *, Object_80039F5C *, int, int, int, int, int);
int fn_80156704(void);
float fn_80178A2C(void);
void fn_80227538(Point_80167910 *, int, float);
void fn_800FD68C(Message_800F01CC *, void *, void *);
void fn_800F00D4(int, State_80039F5C *, Message_800F01CC *, Object_80039F5C *);
void fn_80227690(void *, void *, void *);
int fn_80104688(Object_80039F5C *);
void fn_801024FC(Object_80039F5C *, int, int, int, int);
int fn_80135D54(Object_80039F5C *, float *, float *, unsigned char *);
int fn_801344A0(void);
void fn_800DBC4C(Object_80039F5C *, int, float);
int fn_801783AC(int);
void fn_800A02B4(void);
void fn_800A02FC(void);

int fn_801348F0(Object_80039F5C *);
int fn_801486A0(void);
unsigned char fn_800C13A0(Object_80039F5C *, unsigned char *, unsigned char *);
Object_80039F5C *fn_801244F0(Object_80039F5C *, int, unsigned char, unsigned char, float *, int);
int fn_80178308(void);
void fn_8011E3EC(Object_80039F5C *, int);
void fn_8011E240(Object_80039F5C *);
void fn_80168E54(int, unsigned char, unsigned char);
void fn_8009BD2C(Object_80039F5C *, int *);
int fn_801BD934(float *, void *, unsigned short);
float fn_801BD660(void *pScript, int key);
float fn_801BD6D4(Block_801BD6D4 *);
int fn_800E6AC8(Object_80039F5C *, int);
int fn_8011EC68(Object_80039F5C *, Object_80039F5C *);
float fn_8022781C(void *, void *);
int fn_800E815C(Object_80039F5C *, int, int);
int fn_800F0490(int, State_80039F5C *, int);
void fn_800F05E4(int, State_80039F5C *, Message_800F01CC *, Object_80039F5C *);
int fn_801CFE40(float, float);
int fn_800B7248(Input_800B6D34 *, Object_80137ABC *, Object_80039F5C *, Object_80039F5C *);
int fn_800B7F34(Object_80039F5C *);
void fn_8003AB08(Object_80039F5C *, int);
void fn_801360D4(Object_80039F5C *);
void fn_80136134(Object_80039F5C *, unsigned int);

int fn_80134E24(Object_80039F5C *player) {
    unsigned int count = 0;
    if (fn_80137B40() != player && !(player->mFlags & 0x4000)) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, player->mpState, &message, player);
        return 1;
    }
    State_80134E24 *state = (State_80134E24 *)&player->mUnknown336;
    state->mUnknown34 = 0;
    fn_80135CEC(player);
    lbl_803EB169 = 0;
    unsigned char variant = player->mUnknown2913;
    if (player->mUnknown776 != 2 && variant == 0)
        fn_800D7A0C(player, 2);
    else if (player->mUnknown776 != 1 && variant == 1)
        fn_800D7A0C(player, 1);
    if (player->mFlags & 0x4000) {
        for (int i = 0; i < 3; ++i)
            fn_80168E00(player->mIdBytes[2], i, &state->mUnknown2D[i]);
        for (int i = 0; i < 3; ++i)
            state->mUnknown30[i] = state->mUnknown2D[i];
        fn_80135CEC(player);
    } else {
        if ((unsigned char)player->mpState->mUnknown3[0] != 222) {
            state->mUnknown1 = lbl_803EB168;
            player->mpState->mUnknown3[0] = 222;
            fn_80135CEC(player);
            state->mUnknown14 = -100.0f;
        } else
            state->mUnknown1 = -1;
        state->mUnknown3 = 0;
        state->mUnknown6 = 0;
        state->mUnknown0 = 0;
        state->mUnknown8 = state->mUnknown10 = player->mUnknown2913 == 1 ? 0x800000 : 0;
        state->mUnknown1A = state->mUnknown18 = 0;
        for (int i = 0; i < 3; ++i)
            fn_80168E00(player->mIdBytes[2], i, &state->mUnknown2D[i]);
        for (int i = 0; i < 3; ++i)
            state->mUnknown30[i] = state->mUnknown2D[i];
        state->mUnknown1B =
            (int)((float)(player->mRatings[6] + player->mRatings[2]) * 0.5f * 0.0039215689f * 29.0f);
        state->mUnknown1C = fn_802372EC(0, 31) <= state->mUnknown1B ? 29 : 0;
        int team = fn_80178320();
        Point_8017886C point = fn_80177FE0();
        unsigned int size = fn_80178D18((unsigned char)team);
        for (int i = 0; i < (int)size; ++i) {
            Object_80039F5C *other = fn_80039F5C((unsigned char)team, (unsigned short)i);
            if (other->mUnknown8 != 255 || other->mpState->mId == 2 || other->mpState->mId == 30 ||
                other->mpState->mId == 32 || other->mpState->mId == 12 || other->mpState->mId == 5)
                if (other->mMotion.mPos.mY < point.mY + lbl_803EB184)
                    ++count;
        }
        if (count > 4) {
            state->mUnknown19 = 1;
            state->mUnknown14 = 6.0f;
            state->mUnknown1 = -1;
        } else
            state->mUnknown19 = 0;
    }
    int mode = fn_800AD9B4();
    if (!fn_801481B0() && !fn_801483F8() && fn_800B65A0(player->mIdBytes[2]) != 255 && mode == 3 &&
        fn_80137C48(player)) {
        fn_80148108(0);
        fn_8013FA8C(2);
    }
    fn_8015A0D0(1);
    return mode != 3;
}

int fn_80135200(Object_80039F5C *player) {
    unsigned char action = 20;
    Object_80039F5C *selected = 0, *candidate = 0;
    float *weights = 0;
    fn_800B8344();
    State_80134E24 *state = (State_80134E24 *)&player->mUnknown336;
    if (!lbl_803EB169) {
        Point_8017886C point = fn_80177FE0();
        if (point.mY - player->mMotion.mPos.mY > 4.5f)
            lbl_803EB169 = 1;
    }
    if (lbl_803EB169)
        fn_8013474C(player);
    fn_8010A2DC(player, 0, -1);
    Point_8017886C point = fn_80177FE0();
    fn_80134C20(player, state);
    if (player->mFlags & 0x4000) {
        if (fn_801783AC(0) == 1) {
            fn_800A02B4();
            fn_800A02FC();
            Message_800F01CC message;
            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, player->mpState, &message, player);
            return 1;
        }
        return 0;
    }
    if (player != fn_80137B40())
        return 1;
    if (state->mUnknown4 > 0)
        --state->mUnknown4;
    --state->mUnknown0;
    if ((unsigned char)state->mUnknown0 & 0x80) {
        int limit = 255 - player->mRatings[8];
        if (limit < 0)
            limit = 0;
        state->mUnknown0 += fn_802372EC(0, (limit >> 5) + 1) + 3;
        if (player->mUnknown2914)
            state->mUnknown0 *= 2;
        int value = 0;
        Directions_8012430C values;
        fn_8012430C(&values, 4, player);
        fn_801344F8(player, values.mCost);
        Point_8017886C next = fn_80177FE0();
        if (player->mMotion.mPos.mY > next.mY - 1.5f)
            weights = lbl_802DB174;
        else
            weights = fn_80134AD0(player, &value);
        if (state->mUnknown3 == 1) {
            if (state->mUnknown14 > 5.0f)
                state->mUnknown14 = 5.0f;
            state->mUnknown10 = 65535;
            int best = 0;
            float minimum = 1000.0f;
            for (int i = 0; i < 8; ++i) {
                int angle = i * 0x200000;
                if (values.mCost[i] > 3.0f) {
                    state->mUnknown1 = -1;
                    value -= 20;
                }
                float sum = values.mCost[i] + weights[i];
                if (sum > state->mUnknown14) {
                    state->mUnknown14 = sum;
                    best = i;
                    state->mUnknownC = angle;
                } else if (sum == state->mUnknown14 && values.mCost[i] > values.mCost[best]) {
                    state->mUnknownC = angle;
                    best = i;
                }
                if (sum < minimum) {
                    state->mUnknown10 = angle;
                    minimum = sum;
                } else if (sum == minimum) {
                    int base = player->mUnknown2913 == 1 ? 0x800000 : 0;
                    if (fn_801CFFD0(base, state->mUnknown10) > fn_801CFFD0(base, angle))
                        state->mUnknown10 = angle;
                }
            }
        }
        unsigned int size = fn_80178D18(fn_80178320());
        for (unsigned char i = 0; i < size; ++i) {
            Object_80039F5C *other = fn_80039F5C(fn_80178320(), i);
            if (other->mUnknown8 != 255 && other->mUnknown2914 >= 13 && other->mUnknown2914 <= 18) {
                Point_8017886C next = fn_80177FE0();
                if (other->mMotion.mPos.mY < next.mY)
                    state->mUnknown1 = -1;
            }
        }
        if ((unsigned char)state->mUnknown1 & 0x80) {
            unsigned char indices[3];
            int total = 0;
            for (int i = 0; i < 3; ++i) {
                indices[i] = fn_80168E00(player->mIdBytes[2], i, 0);
                total += state->mUnknown2D[i];
            }
            int choice = fn_802372EC(0, total);
            if (!state->mUnknown28) {
                for (int i = 0; i < 3; ++i) {
                    choice -= state->mUnknown2D[i];
                    if (choice < 0 && indices[i] != 255) {
                        state->mUnknown28 = fn_80039F5C(player->mIdBytes[2], indices[i]);
                        state->mUnknown2C = i;
                        break;
                    }
                }
                if (!state->mUnknown28) {
                    Message_800F01CC message;
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 1;
                    fn_800F053C(0, player->mpState, &message, player);
                    return 1;
                }
            }
            for (int i = 0; i < 3; ++i) {
                if (indices[i] != 255 && state->mUnknown2D[i]) {
                    selected = fn_80039F5C(player->mIdBytes[2], indices[i]);
                    unsigned char a, b = 20;
                    state->mUnknown1D[i] =
                        fn_80135F14(player, selected, &value, state->mUnknown2D[i], &a, &b);
                    state->mUnknown20[i] = a;
                    state->mUnknown23[i] = b;
                } else
                    state->mUnknown1D[i] = 2;
            }
            int found = 0;
            if ((state->mUnknown14 >= 5.0f ||
                 (state->mUnknown28->mpState->mId != 58 && (state->mUnknown28->mpState[1].mId == 21 ||
                                                            state->mUnknown28->mpState[1].mId == 51))) &&
                (state->mUnknown1D[state->mUnknown2C] == 0 ||
                 (state->mUnknown1D[state->mUnknown2C] == 1 &&
                  state->mUnknown20[state->mUnknown2C] <= lbl_803EB16A))) {
                found = 1;
                if (!fn_801347D4(player, state, &selected, &action, indices)) {
                    selected = state->mUnknown28;
                    action = state->mUnknown23[state->mUnknown2C];
                }
            } else {
                int rank = 2, score = 100;
                unsigned int weight = 0;
                for (int i = 0; i < 3; ++i) {
                    if (state->mUnknown1D[i] > 1 && !state->mUnknown20[i])
                        continue;
                    if (!state->mUnknown2D[i])
                        continue;
                    int r = state->mUnknown1D[i];
                    if (!(r < rank || (r == rank && rank == 1 &&
                                       (state->mUnknown20[i] < score ||
                                        (state->mUnknown20[i] == score && state->mUnknown2D[i] > weight)))))
                        continue;
                    Point_80167910 predicted = {0.0f, 0.0f};
                    unsigned int bonus = 0;
                    candidate = fn_80039F5C(player->mIdBytes[2], indices[i]);
                    if (fn_80177F70() != 6) {
                        fn_800C146C(&predicted, player, candidate, 20, 0, 0, 0, 0);
                        if (predicted.mY > point.mY)
                            bonus = (unsigned int)(predicted.mY - point.mY) * fn_80177F70();
                    }
                    weight = state->mUnknown2D[i] + bonus;
                    action = state->mUnknown23[i];
                    rank = state->mUnknown1D[i];
                    score = state->mUnknown20[i];
                    if ((state->mUnknown14 >= 5.0f ||
                         (candidate->mpState->mId != 58 &&
                          (candidate->mpState[1].mId == 21 || candidate->mpState[1].mId == 51))) &&
                        (rank == 0 || (rank == 1 && score <= lbl_803EB16A))) {
                        found = 1;
                        if (!fn_801347D4(player, state, &selected, &action, indices))
                            selected = candidate;
                        break;
                    }
                }
            }
            if (!found && state->mUnknown14 > 5.0f) {
                if (candidate && candidate->mpState->mId != 58) {
                    found = 1;
                    if (!fn_801347D4(player, state, &selected, &action, indices))
                        selected = candidate;
                } else if (fn_80177F70() == 4 || fn_80156704()) {
                    float highest = -fn_80178A2C();
                    unsigned char best = 0;
                    for (int i = 0; i < 3; ++i) {
                        Object_80039F5C *other = fn_80039F5C(player->mIdBytes[2], indices[i]);
                        if (other->mMotion.mPos.mY > highest) {
                            highest = other->mMotion.mPos.mY;
                            best = i;
                        }
                    }
                    found = 1;
                    selected = fn_80039F5C(player->mIdBytes[2], indices[best]);
                }
            }
            if (found == 1) {
                if (selected) {
                    if (selected->mpState->mId == 21) {
                        Point_80167910 offset;
                        fn_80227538(&offset, selected->mMotion.mFacing, 10.0f);
                        offset.mX += selected->mMotion.mPos.mX;
                        offset.mY += selected->mMotion.mPos.mY;
                        Message_800F01CC message;
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 19;
                        fn_800FD68C(&message, &selected->mMotion.mPos, &offset);
                        message.mUnknown1[2] = 255;
                        fn_800F00D4(0, selected->mpState, &message, selected);
                    }
                    Vector_80039F5C diff;
                    fn_80227690(&diff, &selected->mMotion.mPos, &player->mMotion.mPos);
                    fn_802270A4(&diff);
                    if (fn_80156704())
                        action = 5;
                    int id = selected->mIdBytes[1];
                    int result = fn_80104688(player);
                    fn_801024FC(player, 0, id, action, result);
                    return 1;
                }
            } else if (fn_80135D54(player, weights, values.mCost, indices))
                return 0;
        } else
            --state->mUnknown1;
    }
    if (fn_801344A0()) {
        Point_8017886C next = fn_80177FE0();
        if (player->mMotion.mPos.mY > next.mY - 0.5f) {
            if (fn_801CFFD0(state->mUnknown8, 0x400000) <= 0xE38E2)
                state->mUnknown3 = 0;
            else {
                unsigned int angle = state->mUnknown8 & 0xFFFFFF;
                if (angle - 1 <= 0x3FFFFE)
                    state->mUnknown8 = 0;
                else if (angle - 0x400000 <= 0x3FFFFF)
                    state->mUnknown8 = 0x800000;
            }
        }
    }
    if (state->mUnknown3 == 1) {
        player->mUnknown512.mUnknown15 = 1;
        fn_800DBC4C(player, state->mUnknown8, 1.0f);
    } else
        fn_800DBC4C(player, state->mUnknown8, 0.0f);
    --state->mUnknown6;
    return 0;
}

void fn_80135CEC(Object_80039F5C *p)
{
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    s->mUnknown28 = 0;
    s->mUnknown2C = -1;
    for (int i = 2; i >= 0; --i)
        s->mUnknown1D[i] = 2;
    s->mUnknown4 = fn_802372EC(0, 255 - p->mRatings[4]);
}

int fn_80135D54(Object_80039F5C *p, float *values, float *, unsigned char *choices)
{
    Point_8017886C point = fn_80177FE0();
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    if (s->mUnknown3 == 1 && !(s->mUnknown14 <= lbl_803EB188) && values) {
        int angle = s->mUnknown10;
        s->mUnknown8 = angle;
    }
    int largest = 0;
    signed char selection = 0;
    for (int i = 0; i < 3; ++i) {
        if (s->mUnknown2D[i] > largest && i != s->mUnknown2C) {
            largest = s->mUnknown2D[i];
            selection = i;
        }
    }
    if (!fn_802372EC(0, 85) && !(s->mUnknown14 < 2.0f) && !(s->mUnknown14 > 3.0f)) {
        fn_801024FC(p, 4, choices[selection], 12, 0);
        return 1;
    }
    if (fn_801486A0() != 4 && fn_801486A0() != 3 && (s->mUnknown18 || fn_801348F0(p))) {
        Point_8017886C next = fn_80177FE0();
        if (!(p->mMotion.mPos.mY <= next.mY - lbl_803EB18C)) {
            Message_800F01CC m;
            fn_801C1F94(&m, 0, 4);
            m.mId = 1;
            fn_800F053C(0, p->mpState, &m, p);
            return 1;
        }
        s->mUnknown8 = 0x400000;
    }
    return 0;
}

unsigned char fn_80135F14(Object_80039F5C *p, Object_80039F5C *other, int *count,
                         int, unsigned char *a, unsigned char *b)
{
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    unsigned char result = 0;
    if (*count + s->mUnknown1 + 96 > 1 || s->mUnknown19) {
        result = fn_800C13A0(other, a, b);
        if (!(s->mUnknown14 < 5.0f) && !s->mUnknown19) {
            int team = p->mIdBytes[2] ^ 1;
            unsigned char n = fn_80178D18(team);
            float distance;
            Object_80039F5C *nearest = fn_801244F0(p, team, 0, n, &distance, 0);
            if (nearest && !(distance >= 4.0f) &&
                (p->mMotion.mUnknown28 < lbl_803ECB08 * 0.4f ||
                 fn_801CFFD0(p->mMotion.mUnknown32, nearest->mMotion.mUnknown32) > 0x2AAAAA)) {
                *count = 0;
                result = 2;
            }
        }
    }
    return result;
}

void fn_80136034(Object_80039F5C *p)
{
    if (p && p->mpState->mId == 18) {
        State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
        unsigned char previous[3];
        for (unsigned char i = 0; i <= 2; ++i)
            previous[i] = fn_80168E00(p->mIdBytes[2], i, 0);
        for (unsigned char i = 0; i <= 2; ++i) {
            s->mUnknown2D[i] = s->mUnknown30[i];
            fn_80168E54(p->mIdBytes[2], previous[i], s->mUnknown30[i]);
        }
    }
}

void fn_801360D4(Object_80039F5C *p)
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

void fn_80136134(Object_80039F5C *p, unsigned int count)
{
    int index = fn_800F06F4(0, p->mpState, 31, 0xFFFF);
    if (index != 0xFFFF) {
        State_80039F5C *m = p->mpState + index;
        unsigned char n = m->mUnknown1;
        if (n) {
            if (n <= count)
                count = n - 1;
            m->mUnknown1 = n - count;
        }
    }
    index = fn_800F06F4(0, p->mpState, 33, 0xFFFF);
    if (index != 0xFFFF) {
        State_80039F5C *m = p->mpState + index;
        unsigned char n = m->mUnknown1;
        if (n) {
            if (n <= count)
                count = n - 1;
            m->mUnknown1 = n - count;
        }
    }
}

int fn_80136210(Object_80039F5C *p)
{
    p->mUnknown9[0] = 1;
    State_80039F5C *m = p->mpState;
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
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
        index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, keys_802DB1D4[n].mKey, 0);
        ++n;
    } while (n <= 42 && index == 0xFFFF);
    s->mUnknown6 = index;
    if (index == 0xFFFF)
        s->mUnknown4 = 0;
    else {
        Block_801BD6D4 *block = &p->mpUnknown800[index].mUnknown4C;
        float value;
        if (fn_801BD934(&value, block->mpUnknown0, 0xC004))
            value = fn_801BD660(block->mpUnknown0, 0xC004);
        else
            value = fn_801BD60C(block->mpUnknown0);
        s->mUnknown4 = (short)(int)value;
    }
    s->mUnknown10 = 0;
    s->mUnknownCByte = 0;
    s->mUnknown8Bytes[0] = 0;
    s->mUnknown8Bytes[1] = 0;
    s->mUnknown8Bytes[2] = 0;
    s->mUnknown8Bytes[3] = 0;
    return 0;
}

int fn_801363A4(Object_80039F5C *p)
{
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    Object_80039F5C *other = fn_8009BCE8(&s->mUnknown0Word);
    s->mUnknown8Bytes[3] = 1;
    ++s->mUnknown10;
    int result = 0;
    if ((unsigned int)(p->mUnknown1032 - 6) <= 1)
        s->mUnknown8Bytes[0] = 1;
    if (p->mFlags & 0x800) {
        s->mUnknown8Bytes[0] = 0;
        fn_801360D4(p);
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
        fn_801360D4(p);
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
        Object_80039F5C *ball = fn_80137B40();
        if (ball) {
            int lower = ball->mMotion.mPos.mY + 2.0f > p->mMotion.mPos.mY;
            int action = 0;
            int attempted = 1;
            if (!ball->mUnknown2914) {
                if (ball->mFlags & 0x8000)
                    action = fn_800E6AC8(p, 4);
                else
                    action = fn_800E6AC8(p, 8);
            } else if (!lower)
                action = fn_800E6AC8(p, 4);
            else if (!(fn_8022781C(&p->mMotion.mPos, &ball->mMotion.mPos) > 5.0f)) {
                Object_80039F5C *linked = fn_8009BCE8(&p->mUnknown1036);
                if (linked) {
                    p->mUnknown344 = 1;
                    linked->mUnknown344 = 1;
                    action = fn_800E6AC8(p, 5);
                } else
                    attempted = 0;
            } else {
                Object_80039F5C *linked = fn_8009BCE8(&p->mUnknown1036);
                if (linked)
                    action = fn_8011EC68(linked, p);
                else
                    attempted = 0;
            }
            if (attempted && action) {
                s->mUnknownCByte = 1;
                return 0;
            }
        }
    }
    if (p->mFlags & 4) {
        if (fn_801BE648(p->mpUnknown792) == 242 && p->mIdBytes[2] == fn_80178320()) {
            p->mUnknown772 = 1.0f;
            fn_801360D4(p);
            fn_80143EBC(p, other);
            s->mUnknown8Bytes[0] = 1;
            if (fn_800E815C(p, 2, 0))
                fn_800F0490(0, p->mpState, 32);
            p->mFlags &= ~4;
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown772 = 1.0f;
            fn_80136134(p, (unsigned short)s->mUnknown4);
            p->mFlags &= ~0x800;
            fn_80143EBC(p, other);
            if (p->mUnknown1032 == 5) {
                p->mUnknown1032 = 6;
                s->mUnknown8Bytes[0] = 1;
            }
            result = 1;
            fn_801360D4(p);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown0 = 0.4f;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        }
    }
    return result;
}

int fn_80136820(Object_80039F5C *p)
{
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    if (!s->mUnknown8Bytes[0] && p->mUnknown1032 != 6)
        return 0;
    unsigned short index = s->mUnknown6;
    if (index != 0xFFFF)
        fn_80136134(p, (unsigned int)fn_801BD6D4(&p->mpUnknown800[index].mUnknown4C));
    p->mUnknown772 = 1.0f;
    fn_801360D4(p);
    Object_80039F5C *other = fn_8009BCE8(&s->mUnknown0Word);
    if (other)
        fn_80143EBC(p, other);
    return 1;
}

int fn_80136900(Object_80039F5C *p)
{
    float x = 0.0f, y = 0.0f;
    State_80134E24 *s = (State_80134E24 *)&p->mUnknown336;
    if (p->mIdBytes[2] == fn_80178320() &&
        (fn_801BE648(p->mpUnknown792) == 55 || fn_801BE648(p->mpUnknown792) == 49 || fn_801BE648(p->mpUnknown792) == 52)) {
        Input_800B6D34 input;
        fn_800B6D34(p, &input);
        if (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f) {
            x = input.mUnknown4;
            y = input.mUnknown8;
        } else {
            if (input.mUnknown0 & 1) y = 1.0f;
            if (input.mUnknown0 & 2) y = -1.0f;
            if (input.mUnknown0 & 4) x = -1.0f;
            if (input.mUnknown0 & 8) x = 1.0f;
        }
        if (x != 0.0f || y != 0.0f)
            p->mUnknown512.mUnknown4 = fn_801CFE40(y, x);
        if (s->mUnknown8Bytes[3]) {
            int result = fn_800B7248(&input, fn_801374BC(), p, p);
            if (result == 1)
                return 0;
        }
    }
    return fn_800B7F34(p);
}

int fn_80136A78(Object_80039F5C *p)
{
    fn_8010A2DC(p, 0, -1);
    return 0;
}

int fn_80136AA4(Object_80039F5C *p)
{
    fn_8003AB08(p, 0);
    p->mpState[1].mId = 0;
    return 0;
}

void fn_80136AE4(int kind, int enabled)
{
    fn_800EFE0C(kind, enabled ? &lbl_803EB198 : &lbl_803EB190);
}

}
