#include "game/fn_80177FE0.h"
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/Team_80167A8C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_800B65A0.h"

/* This mode overlays the opaque block at player+0x150. */
struct State_80134E24 {
    signed char mUnknown0, mUnknown1;
    unsigned char mUnknown2, mUnknown3;
    short mUnknown4, mUnknown6;
    int mUnknown8, mUnknownC, mUnknown10;
    float mUnknown14;
    unsigned char mUnknown18, mUnknown19, mUnknown1A, mUnknown1B, mUnknown1C;
    unsigned char mUnknown1D[3], mUnknown20[3], mUnknown23[3];
    unsigned char mUnknown26[2];
    Object_80039F5C *mUnknown28;
    signed char mUnknown2C;
    unsigned char mUnknown2D[3], mUnknown30[3];
    unsigned char mUnknown33;
    short mUnknown34;
};
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
int fn_80137C48(Object_80039F5C *);
void fn_80148108(int);
void fn_8013FA8C(int);
void fn_8015A0D0(int);
void fn_800B8344(void);
void fn_8013474C(Object_80039F5C *);
void fn_8010A2DC(Object_80039F5C *, int, int);
void fn_80134C20(Object_80039F5C *, State_80134E24 *);
void fn_8012430C(float *, int, Object_80039F5C *);
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
        float values[8];
        fn_8012430C(values, 4, player);
        fn_801344F8(player, values);
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
                if (values[i] > 3.0f) {
                    state->mUnknown1 = -1;
                    value -= 20;
                }
                float sum = values[i] + weights[i];
                if (sum > state->mUnknown14) {
                    state->mUnknown14 = sum;
                    best = i;
                    state->mUnknownC = angle;
                } else if (sum == state->mUnknown14 && values[i] > values[best]) {
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
            } else if (fn_80135D54(player, weights, values, indices))
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
}
