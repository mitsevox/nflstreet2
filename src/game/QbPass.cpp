/* Player state of the ball carrier behind the line before a pass. Normally it scores eight
   escape directions against the defenders, rates the three receivers, throws to one of them,
   moves in the pocket or decides to run; a player with flag 0x4000 only has the receiver
   options kept current until the state ends. */

#include <math.h>
#include <string.h>

#include "engine/cu_801B9F00.h"
#include "game/Queue_800EFE0C.h"
#include "game/Directions_8012430C.h"
#include "game/fn_80177FE0.h"
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/PlayBookTeam.h"
#include <string.h>
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

static float _QbPass_afDirWeights[7][8] = {
    {0, .75f, 1, .75f, 0, 2, 3, 2},
    {-1, 0, 0, 0, -1, 2, 3, 2},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 55, 60, 55},
    {1, 0, -1, 0, 1, 2, 3, 2},
    {7, 4, 0, -2, -1, 4, 12, 10},
    {-1, -2, 0, 4, 7, 10, 12, 4},
};
extern "C" float gPlyrMoveFwdSpeed;
extern "C" {
unsigned char _QbPass_cReadDelay = 3;
unsigned char _QbPass_bDroppedBack = 0;
unsigned char _QbPass_cMaxCoverScore = 0;
unsigned char _QbPass_bRandomPick = 1;
float _QbPass_fRunWeightA = 0.75f;
float _QbPass_fRunWeightB = 0.25f;
float _QbPass_fRunRoom = 2.0f;
float _QbPass_fRunConeDegrees = 60.0f;
float _QbPass_fRunConeRange = 25.0f;
float _QbPass_fRunConeLimit = 5.0f;
float _QbPass_fCrowdDepth = 5.0f;
float _QbPass_fMinMoveScore = 1.0f;
float _QbPass_fRunLineMargin = 1.5f;
}
extern "C" {
Object_80039F5C *BallGetCurrentHolder(void);
void QbPassResetTarget(Object_80039F5C *);
void fn_800D7A0C(Object_80039F5C *, int);
unsigned char PlayBookGetReceiver(int, unsigned char, unsigned char *);
unsigned int fn_802372EC(unsigned int, unsigned int);
int fn_80178320(void);
int fn_800AD9B4(void);
int PassIconsAreShown(void);
int PassIconsWereShown(void);
void PassIconsShow(int);
void CamGameSetModeAll(int);
void PassIconObjSetEnabled(int);
void fn_800B8344(Object_80039F5C *);

int fn_8010A2DC(Object_80039F5C *, int, short);
void fn_8012430C(Directions_8012430C *, int, Object_80039F5C *);
int MathAngleDiff(int, int);
unsigned char QbPassRateReceiver(Object_80039F5C *, Object_80039F5C *, int *, int, unsigned char *, unsigned char *);
int fn_80177F70(void);
void fn_800C146C(Vec2_t *, Object_80039F5C *, Object_80039F5C *, int, int, int, int, int);
int TutorialIsActive(void);
float fn_80178A2C(void);
void fn_80227538(Vec2_t *, int, float);
void fn_800FD68C(Message_800F01CC *, void *, void *);
void fn_800F00D4(int, State_80039F5C *, Message_800F01CC *, Object_80039F5C *);
void fn_80227690(void *, void *, void *);
int fn_80104688(Object_80039F5C *);
void fn_801024FC(Object_80039F5C *, int, int, int, int);
int QbPassHoldOrRun(Object_80039F5C *, float *, float *, unsigned char *);
void PlayerActionAnimSteerPassReady(Object_80039F5C *, int, float);
int fn_801783AC(int);
void fn_800A02B4(void);
void fn_800A02FC(void);

int fn_801486A0(void);
int fn_800C13A0(Object_80039F5C *, unsigned char *, unsigned char *);
Object_80039F5C *fn_801244F0(Object_80039F5C *, int, unsigned char, unsigned char, float *, int);
int fn_80178308(void);
void PlayBookSetReceiverOption(int, unsigned char, unsigned char);

int fn_801CFE40(float, float);
void SndgSpchSetPlayFlags(int);
unsigned int fn_800ABDA4(int);
Object_80039F5C *fn_80124E5C(Object_80039F5C *, int, float *, int, float, int, float);
float fn_80124FE0(Object_80039F5C *, int);
float fn_80125004(Object_80039F5C *, int, int);
float fn_80178298(void);
int fn_801787DC(int);
int fn_801788D8(int *);
float fn_80178A08(void);
float fn_80178A44(void);
float fn_80237260(int);


int QbPassInSpecialMode(void)
{
    int mode = fn_801486A0();
    int low = 3;
    int result = 0;
    if (mode <= 4) result = mode >= low;
    if (TutorialIsActive()) result = 1;
    return result;
}

void QbPassScoreDirections(Object_80039F5C *p, float *values)
{
    int team = fn_80178320();
    unsigned char count = fn_80178D18(fn_80178320());
    float distance;
    fn_801244F0(p, team, 0, count, &distance, 0);
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    s->mUnknown3 = 0;
    if (values[0] > 2.0f || values[1] > 2.0f || values[2] > 2.0f || values[3] > 2.0f ||
        values[4] > 2.0f || values[5] > 2.0f || values[6] > 2.0f || !(values[7] <= 2.0f)) {
        s->mUnknown3 = 1;
        s->mUnknown6 = 10;
        if (!(p->mMotion.mPos.mY >= fn_80177FE0().mY - 13.0f)) {
            values[5] += 3.0f;
            values[6] += 4.0f;
            values[7] += 3.0f;
        } else if (!(fabsf(p->mMotion.mPos.mY) <= fn_80178A44() - 4.0f)) {
            values[5] += 3.0f;
            values[6] += 4.0f;
            values[7] += 3.0f;
        }
    } else {
        s->mUnknown6 = 10;
        unsigned int n = fn_80178D18(fn_80178320());
        for (unsigned short i = 0; i < n; ++i) {
            Object_80039F5C *other = PlyrGet(fn_80178320(), i);
            float delta[2];
            fn_80227690(delta, &other->mMotion.mPos, &p->mMotion.mPos);
            if (!(fn_802270A4(delta) >= 3.0f)) {
                int angle = fn_801CFE40(delta[1], delta[0]);
                float *cost = &values[((angle + 0x100000) >> 21) & 7];
                *cost += 4.0f;
                s->mUnknown3 = 1;
            }
        }
    }
    if (s->mUnknown4 <= 0) s->mUnknown3 = 1;
}

void QbPassCheckSpeech(Object_80039F5C *p)
{
    float a = fn_80124FE0(p, 3);
    float b = fn_80125004(p, 3, 1);
    if (a > 7.0f || (!(a <= 5.0f) && !(b <= 5.0f)))
        SndgSpchSetPlayFlags(16);
}

int QbPassPickRandomReceiver(Object_80039F5C *p, PlyrModeState_t *s,
               Object_80039F5C **out, unsigned char *choice, unsigned char *indexes)
{
    if (_QbPass_bRandomPick) {
        float threshold = (float)p->mRatings[6] * 0.003921568859368563f;
        if (!fn_800ABDA4(p->mIdBytes[2])) threshold *= 0.5f;
        if (!(fn_80237260(0) <= threshold)) {
            *out = 0;
            do {
                unsigned int n = fn_802372EC(0, 3);
                if (indexes[n] != 255 && s->mUnknown30[n]) {
                    *out = PlyrGet(p->mIdBytes[2], indexes[n]);
                    *choice = s->mUnknown23[n];
                    break;
                }
            } while (!*out);
            return 1;
        }
    }
    return 0;
}

int QbPassShouldRun(Object_80039F5C *p)
{
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    if (!fn_801783AC(0)) {
        unsigned int kind = p->mUnknown2914;
        if (QbPassInSpecialMode() || !(kind <= 1 || kind == 3)) return 0;
        float threshold = (float)p->mRatings[4] * _QbPass_fRunWeightA + (float)p->mRatings[0] * _QbPass_fRunWeightB;
        threshold *= 0.003921568859368563f;
        if (fn_80237260(0) > threshold) return 0;
        int mode = fn_80177F70();
        float limit = (_QbPass_fRunRoom + fn_80177FE0().mY - p->mMotion.mPos.mY) * (2.0f - threshold);
        if (mode == 4 || mode == 6) {
            limit = (fn_80178298() - p->mMotion.mPos.mY) * (2.0f - threshold);
            if (mode == 6) {
                int time;
                if (!fn_801788D8(&time)) {
                    time -= fn_801787DC(fn_80178308());
                    if ((unsigned int)time <= 24 && !((time - 2) & 7)) return 0;
                }
            }
        }
        float distance;
        fn_80124E5C(p, fn_80178320(), &distance, (int)(_QbPass_fRunConeDegrees * 46603.37890625f), _QbPass_fRunConeRange, 0x400000, _QbPass_fRunConeLimit);
        if (distance > limit) {
            s->mUnknown18 = 1;
            return 1;
        }
    } else
        return 1;
    return 0;
}

float *QbPassGetDirectionWeights(Object_80039F5C *p, int *count)
{
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    float *values;
    if (s->mUnknown1 & 0x80) {
        if (s->mUnknown1C == 29)
            values = _QbPass_afDirWeights[1];
        else
            values = _QbPass_afDirWeights[0];
    } else
        values = _QbPass_afDirWeights[2];
    if (!(p->mMotion.mPos.mY >= -(fn_80178A2C() + 6.5f))) {
        values = _QbPass_afDirWeights[3];
        *count = -20;
        if (!(p->mMotion.mPos.mY >= -(fn_80178A2C() + 8.0f))) *count = -10;
    }
    if (!(p->mMotion.mPos.mX <= fn_80178A08() - 5.0f) && !(p->mMotion.mUnknown40 <= 0.0f))
        values = _QbPass_afDirWeights[5];
    else if (!(p->mMotion.mPos.mX >= 5.0f - fn_80178A08()) && !(p->mMotion.mUnknown40 >= 0.0f))
        values = _QbPass_afDirWeights[6];
    return values;
}

void QbPassUpdateReceiverOptions(Object_80039F5C *p, PlyrModeState_t *s)
{
    unsigned char i;
    if (!p || !s) return;
    unsigned char indexes[3];
    for (i = 0; i <= 2; ++i) indexes[i] = PlayBookGetReceiver(p->mIdBytes[2], i, 0);
    for (i = 0; i <= 2; ++i) {
        int disabled = 0;
        if (!s->mUnknown30[i] || indexes[i] == 255) continue;
        Object_80039F5C *other = PlyrGet(p->mIdBytes[2], indexes[i]);
        switch (other->mpState->mId) {
        case 10: case 11: case 16: case 31: case 32: disabled = 1; break;
        case 3: case 51:
            if (fn_800F06F4(0, other->mpState, 31, 0xFFFF) != 0xFFFF) disabled = 1;
            break;
        }
        if (other->mFlags & 0x800) disabled = 1;
        if (!(p->mMotion.mPos.mY <= other->mMotion.mPos.mY) &&
            !(fabsf(p->mMotion.mPos.mX - other->mMotion.mPos.mX) >= 3.0f) && fn_800B65A0(p->mIdBytes[2]) == 255)
            disabled = 1;
        if (s->mUnknown2D[i] && disabled) {
            s->mUnknown2D[i] = 0;
            PlayBookSetReceiverOption(p->mIdBytes[2], indexes[i], 0);
        } else if (s->mUnknown30[i] && !s->mUnknown2D[i] &&
                   (other->mpState->mId == 19 || other->mpState->mId == 21)) {
            s->mUnknown2D[i] = s->mUnknown30[i];
            PlayBookSetReceiverOption(p->mIdBytes[2], indexes[i], s->mUnknown30[i]);
        }
    }
}

int QbPassEnter(Object_80039F5C *player) {
    unsigned int count = 0;
    if (BallGetCurrentHolder() != player && !(player->mFlags & 0x4000)) {
        Message_800F01CC message;
        memset(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, player->mpState, &message, player);
        return 1;
    }
    PlyrModeState_t *state = (PlyrModeState_t *)&player->mUnknown336;
    state->mUnknown34 = 0;
    QbPassResetTarget(player);
    _QbPass_bDroppedBack = 0;
    if (player->mUnknown776 != 2 && player->mUnknown2913 == 0)
        fn_800D7A0C(player, 2);
    else if (player->mUnknown776 != 1 && player->mUnknown2913 == 1)
        fn_800D7A0C(player, 1);
    if (player->mFlags & 0x4000) {
        for (int i = 0; i < 3; ++i)
            PlayBookGetReceiver(player->mIdBytes[2], i, &state->mUnknown2D[i]);
        memcpy(state->mUnknown30, state->mUnknown2D, 3);
        QbPassResetTarget(player);
    } else {
        if ((unsigned char)player->mpState->mUnknown3[0] != 222) {
            state->mUnknown1 = _QbPass_cReadDelay;
            player->mpState->mUnknown3[0] = 222;
            QbPassResetTarget(player);
            state->mUnknown14 = -100.0f;
        } else
            state->mUnknown1 = -1;
        state->mUnknown0 = 0;
        state->mUnknown3 = 0;
        state->mUnknown6 = 0;
        if (player->mUnknown2913 == 1)
            state->mUnknown8 = state->mUnknown10 = 0x800000;
        else
            state->mUnknown8 = state->mUnknown10 = 0;
        state->mUnknown1A = state->mUnknown18 = 0;
        for (int i = 0; i < 3; ++i)
            PlayBookGetReceiver(player->mIdBytes[2], i, &state->mUnknown2D[i]);
        memcpy(state->mUnknown30, state->mUnknown2D, 3);
        float rating = (float)(player->mRatings[4] + player->mRatings[0]) * 0.5f;
        rating *= 0.0039215689f;
        state->mUnknown1B = (int)(rating * 29.0f);
        if (fn_802372EC(0, 31) <= state->mUnknown1B)
            state->mUnknown1C = 29;
        else
            state->mUnknown1C = 0;
        int team = fn_80178320();
        Point_8017886C point;
        point = fn_80177FE0();
        unsigned int size = fn_80178D18((unsigned char)team);
        for (int i = 0; i < (int)size; ++i) {
            Object_80039F5C *other = PlyrGet((unsigned char)team, (unsigned short)i);
            if (other->mUnknown8 != 255 || other->mpState->mId == 2 || other->mpState->mId == 30 ||
                other->mpState->mId == 32 || other->mpState->mId == 12 || other->mpState->mId == 5)
                if (other->mMotion.mPos.mY < point.mY + _QbPass_fCrowdDepth)
                    ++count;
        }
        if (count > 4) {
            state->mUnknown14 = 6.0f;
            state->mUnknown1 = -1;
            state->mUnknown19 = 1;
        } else
            state->mUnknown19 = 0;
    }
    int mode = fn_800AD9B4();
    if (!PassIconsAreShown() && !PassIconsWereShown() && fn_800B65A0(player->mIdBytes[2]) != 255 && mode == 3 &&
        BallFindHeldBy(player)) {
        PassIconsShow(0);
        CamGameSetModeAll(2);
    }
    PassIconObjSetEnabled(1);
    return mode != 3;
}

int QbPassUpdate(Object_80039F5C *player) {
    Message_800F01CC message;
    int i;
    Directions_8012430C values;
    unsigned char indices[3];
    unsigned char action = 20;
    float *weights = 0;
    Object_80039F5C *selected = 0;
    fn_800B8344(player);
    PlyrModeState_t *state = (PlyrModeState_t *)&player->mUnknown336;
    Object_80039F5C *candidate = 0;
    if (!_QbPass_bDroppedBack) {
        if (fn_80177FE0().mY - player->mMotion.mPos.mY > 4.5f)
            _QbPass_bDroppedBack = 1;
    }
    if (_QbPass_bDroppedBack)
        QbPassCheckSpeech(player);
    fn_8010A2DC(player, 0, -1);
    Point_8017886C point;
    point = fn_80177FE0();
    QbPassUpdateReceiverOptions(player, state);
    if (!(player->mFlags & 0x4000)) {
        if (player != BallGetCurrentHolder())
            return 1;
        if (state->mUnknown4 > 0)
            --state->mUnknown4;
        --state->mUnknown0;
        if ((unsigned char)state->mUnknown0 & 0x80) {
            int limit = 255 - player->mRatings[6];
            if (limit < 0)
                limit = 0;
            state->mUnknown0 = state->mUnknown0 + fn_802372EC(0, (limit >> 5) + 1) + 3;
            if (player->mUnknown2914)
                state->mUnknown0 *= 2;
            int value = 0;
            fn_8012430C(&values, 4, player);
            QbPassScoreDirections(player, values.mCost);
            if (player->mMotion.mPos.mY > fn_80177FE0().mY - 1.5f)
                weights = _QbPass_afDirWeights[4];
            else
                weights = QbPassGetDirectionWeights(player, &value);
            if (state->mUnknown3 == 1) {
                state->mUnknown14 = state->mUnknown14 > 5.0f ? 5.0f : state->mUnknown14;
                int best = 0;
                float minimum = 1000.0f;
                state->mUnknown10 = 65535;
                for (int i = 0; i < 8; ++i) {
                    if (values.mCost[i] > 3.0f) {
                        state->mUnknown1 = -1;
                        value -= 20;
                    }
                    float sum = values.mCost[i] + weights[i];
                    if (sum > state->mUnknown14) {
                        state->mUnknown14 = sum;
                        best = i;
                        state->mUnknownC = i * 0x200000;
                    } else if (sum == state->mUnknown14 && values.mCost[i] > values.mCost[best]) {
                        state->mUnknownC = i * 0x200000;
                        best = i;
                    }
                    if (sum <= minimum) {
                        if (sum == minimum) {
                            int base = player->mUnknown2913 == 1 ? 0x800000 : 0;
                            if (MathAngleDiff(base, state->mUnknown10) > MathAngleDiff(base, i * 0x200000))
                                state->mUnknown10 = i * 0x200000;
                        } else {
                            state->mUnknown10 = i * 0x200000;
                            minimum = sum;
                        }
                    }

                }
            }
            unsigned int size = fn_80178D18(fn_80178320());
            for (unsigned char n = 0; n < size; ++n) {
                Object_80039F5C *other = PlyrGet(fn_80178320(), n);
                int first = 13, last = 18;
                if (other->mUnknown8 != 255 && other->mUnknown2914 <= last && other->mUnknown2914 >= first) {
                    if (other->mMotion.mPos.mY < fn_80177FE0().mY)
                        state->mUnknown1 = -1;
                }
            }
            if ((unsigned char)state->mUnknown1 & 0x80) {
                int total = 0;
                for (i = 0; i < 3; ++i) {
                    indices[i] = PlayBookGetReceiver(player->mIdBytes[2], i, 0);
                    total += state->mUnknown2D[i];
                }
                total = fn_802372EC(0, total);
                if (!state->mUnknown28) {
                    for (i = 0; i < 3; ++i) {
                        total -= state->mUnknown2D[i];
                        if (total < 0 && indices[i] != 255) {

                            state->mUnknown28 = PlyrGet(player->mIdBytes[2], indices[i]);
                            state->mUnknown2C = i;
                            break;
                        }
                    }
                }
                if (state->mUnknown28) {
                for (i = 0; i < 3; ++i) {
                    if (indices[i] != 255 && state->mUnknown2D[i]) {
                        selected = PlyrGet(player->mIdBytes[2], indices[i]);
                        unsigned char a, b = 20;
                        state->mUnknown1D[i] =
                            QbPassRateReceiver(player, selected, &value, state->mUnknown2D[i], &a, &b);
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
                      state->mUnknown20[state->mUnknown2C] <= _QbPass_cMaxCoverScore))) {
                    found = 1;
                    if (!QbPassPickRandomReceiver(player, state, &selected, &action, indices)) {
                        selected = state->mUnknown28;
                        action = state->mUnknown23[state->mUnknown2C];
                    }
                } else {
                    unsigned int rank = 2, score = 100;
                    unsigned int weight = 0;
                    for (i = 0; i < 3; ++i) {
                        int better = 0;
                        if (state->mUnknown1D[i] > 1 && !state->mUnknown20[i])
                            continue;
                        if (!state->mUnknown2D[i])
                            continue;
                        if (state->mUnknown1D[i] < rank ||
                            (state->mUnknown1D[i] == rank && rank == 1 &&
                             (state->mUnknown20[i] < score ||
                              (state->mUnknown20[i] == score && state->mUnknown2D[i] > weight))))
                            better = 1;
                        if (!better)
                            continue;
                        Vec2_t predicted;
                        predicted.mX = 0.0f;
                        predicted.mY = 0.0f;
                        unsigned int bonus = 0;
                        candidate = PlyrGet(player->mIdBytes[2], indices[i]);
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
                            (state->mUnknown1D[i] == 0 ||
                             (state->mUnknown1D[i] == 1 && state->mUnknown20[i] <= _QbPass_cMaxCoverScore))) {

                            found = 1;
                            if (!QbPassPickRandomReceiver(player, state, &selected, &action, indices))
                                selected = candidate;
                            break;
                        }
                    }
                }
                if (!found && state->mUnknown14 > 5.0f) {
                    if (candidate && candidate->mpState->mId != 58) {
                        found = 1;
                        if (!QbPassPickRandomReceiver(player, state, &selected, &action, indices))
                            selected = candidate;
                    } else if (fn_80177F70() == 4 || TutorialIsActive()) {
                        float highest = -fn_80178A2C();
                        unsigned char best = 0;
                        for (i = 0; i < 3; ++i) {
                            Object_80039F5C *other = PlyrGet(player->mIdBytes[2], indices[i]);
                            if (other->mMotion.mPos.mY > highest) {
                                highest = other->mMotion.mPos.mY;
                                best = i;
                            }
                        }
                        found = 1;
                        selected = PlyrGet(player->mIdBytes[2], indices[best]);
                    }
                }
                if (found == 1) {
                    if (selected) {
                        if (selected->mpState->mId == 21) {
                            Vec2_t offset;
                            fn_80227538(&offset, selected->mMotion.mFacing, 10.0f);
                            offset.mX += selected->mMotion.mPos.mX;
                            offset.mY += selected->mMotion.mPos.mY;
                            Message_800F01CC message;
                            memset(&message, 0, 4);
                            message.mId = 19;
                            fn_800FD68C(&message, &selected->mMotion.mPos, &offset);
                            message.mUnknown1[2] = 255;
                            fn_800F00D4(0, selected->mpState, &message, selected);
                        }
                        Vec2_t diff;

                        fn_80227690(&diff, &selected->mMotion.mPos, &player->mMotion.mPos);
                        fn_802270A4(&diff);
                        if (TutorialIsActive())
                            action = 5;
                        fn_801024FC(player, 0, selected->mIdBytes[1], action, fn_80104688(player));
                        return 1;
                    }
                } else if (QbPassHoldOrRun(player, weights, values.mCost, indices))
                    return 0;
                } else {
                    memset(&message, 0, 4);
                    message.mId = 1;
                    fn_800F053C(0, player->mpState, &message, player);
                    return 1;
                }
            } else
                --state->mUnknown1;

        }
        if (QbPassInSpecialMode()) {
            if (player->mMotion.mPos.mY > fn_80177FE0().mY - 0.5f) {
                if (MathAngleDiff(state->mUnknown8, 0x400000) <= 0xE38E2)
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
            PlayerActionAnimSteerPassReady(player, state->mUnknown8, 1.0f);
        } else
            PlayerActionAnimSteerPassReady(player, state->mUnknown8, 0.0f);
        --state->mUnknown6;
    } else if (fn_801783AC(0) == 1) {

        fn_800A02B4();
        fn_800A02FC();
        memset(&message, 0, 4);
        message.mId = 1;
        fn_800F053C(0, player->mpState, &message, player);
        return 1;
    }
    return 0;
}

void QbPassResetTarget(Object_80039F5C *p)
{
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    s->mUnknown28 = 0;
    s->mUnknown2C = -1;
    for (unsigned int i = 3; i != 0; --i)
        s->mUnknown1D[i - 1] = 2;
    s->mUnknown4 = fn_802372EC(0, 255 - p->mRatings[4]);
}

int QbPassHoldOrRun(Object_80039F5C *p, float *values, float *costs, unsigned char *choices)
{
    Point_8017886C point = fn_80177FE0();
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    if (s->mUnknown3 == 1 && !(s->mUnknown14 <= _QbPass_fMinMoveScore)) {
        int angle = s->mUnknown10;
        if (values) {
            if (values[((angle + 0x100000) >> 21) & 7] == 0.0f)
                s->mUnknown8 = angle;
            else
                s->mUnknown8 = angle;
        }
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
    if (fn_801486A0() != 4 && fn_801486A0() != 3 && (s->mUnknown18 || QbPassShouldRun(p))) {
        if (!(p->mMotion.mPos.mY <= fn_80177FE0().mY - _QbPass_fRunLineMargin)) {
            Message_800F01CC m;
            memset(&m, 0, 4);
            m.mId = 1;
            fn_800F053C(0, p->mpState, &m, p);
            return 1;
        }
        s->mUnknown8 = 0x400000;
    }
    return 0;
}

unsigned char QbPassRateReceiver(Object_80039F5C *p, Object_80039F5C *other, int *count,
                         int, unsigned char *a, unsigned char *b)
{
    PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
    unsigned char result = 0;
    if (*count + s->mUnknown1 + 96 > 1 || s->mUnknown19) {
        result = fn_800C13A0(other, a, b);
        if (!(s->mUnknown14 < 5.0f) && !s->mUnknown19) {
            int team = p->mIdBytes[2] ^ 1;
            unsigned char n = fn_80178D18(team);
            float distance;
            Object_80039F5C *nearest = fn_801244F0(p, team, 0, n, &distance, 0);
            if (nearest && !(distance >= 4.0f) &&
                (p->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.4f ||
                 MathAngleDiff(p->mMotion.mUnknown32, nearest->mMotion.mUnknown32) > 0x2AAAAA)) {
                *count = 0;
                result = 2;
            }
        }
    }
    return result;
}

void QbPassRestoreReceiverOptions(Object_80039F5C *p)
{
    if (p && p->mpState->mId == 18) {
        PlyrModeState_t *s = (PlyrModeState_t *)&p->mUnknown336;
        unsigned char previous[3];
        for (unsigned char i = 0; i <= 2; ++i)
            previous[i] = PlayBookGetReceiver(p->mIdBytes[2], i, 0);
        for (unsigned char i = 0; i <= 2; ++i) {
            s->mUnknown2D[i] = s->mUnknown30[i];
            PlayBookSetReceiverOption(p->mIdBytes[2], previous[i], s->mUnknown30[i]);
        }
    }
}

int QbPassCarrierWillCross(void)
{
    Object_80039F5C *p = BallGetCurrentHolder();
    Vec2_t step, ahead;
    step.mX = step.mY = 0.0f;
    ahead.mX = ahead.mY = 0.0f;
    if (p && p->mpState->mId == 18) {
        if ((p->mFlags & 0x200000) && (p->mFlags & 0x8000) &&
            !(p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed < 0.4f))
            return 1;
        fn_80227538(&step, p->mMotion.mUnknown32, p->mMotion.mUnknown28 * 40.0f);
        ahead.mX = step.mX + p->mMotion.mPos.mX;
        ahead.mY = step.mY + p->mMotion.mPos.mY;
        return ahead.mY < fn_80177FE0().mY;
    }
    return 0;
}

}
