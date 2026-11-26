/* The sound library's AEMS module player (saems.c): the AEMS audio-effect modules that drive the
   game's sound effects (counters, random pickers, triggers, envelopes, tables, delay lines, math
   and player modules), the per-voice bank and play-option setters they feed, the bank players,
   the Csis class callbacks that create module instances, and the module bank registry. */

#include "engine/sndbank.h"
#include "engine/sndaems_state.h"

extern "C" {

typedef struct Range_80267114 {
    int mMin;
    int mMax;
} Range_80267114;

typedef struct Object_80267114 {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[2];
    Range_80267114 mUnknownC[1];
} Object_80267114;

typedef struct Object_8026739C {
    unsigned char mUnknown0[8];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
} Object_8026739C;

typedef struct Object_80267404 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    signed char mUnknownC;
    unsigned char mUnknownD[3];
    int mUnknown10;
    int mUnknown14;
} Object_80267404;

typedef struct Object_80267480 {
    int mUnknown0;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknownC;
} Object_80267480;

typedef struct Object_802674DC {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    signed char mUnknown3;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    int mUnknownC;
    union {
        unsigned char mBytes[1];
        unsigned short mShorts[1];
    } mUnknown10;
} Object_802674DC;

typedef struct Object_8026769C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12[2];
    int mUnknown14;
} Object_8026769C;

typedef struct Object_802677B4 {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    int mUnknown4;
    int mUnknown8[1];
} Object_802677B4;

typedef struct Object_80267814 {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    int mUnknown4[1];
} Object_80267814;

typedef struct Args_80267D84 {
    unsigned char mCount;
    unsigned char mUnknown1[3];
    int mValues[1];
} Args_80267D84;

typedef struct Object_80267DB4 {
    unsigned char mCount;
    unsigned char mUnknown1;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC[1];
} Object_80267DB4;

typedef struct Entry_802686CC {
    unsigned char mType;
    unsigned char mUnknown1[3];
    int mUnknown4;
    int mUnknown8;
} Entry_802686CC;

typedef struct Object_802686CC {
    unsigned char mUnknown0[8];
    int mUnknown8;
    unsigned char mUnknownC[2];
    unsigned char mUnknownE;
    unsigned char mUnknownF[13];
    Entry_802686CC mEntries[1];
} Object_802686CC;

typedef struct Owner_802685B8 {
    unsigned char mUnknown0[64];
    int mUnknown40;
} Owner_802685B8;

typedef struct Object_802685B8 {
    Owner_802685B8 *mUnknown0;
    unsigned char mUnknown4[10];
    unsigned char mUnknownE;
    unsigned char mUnknownF[13];
    Entry_802686CC mEntries[1];
} Object_802685B8;

typedef struct Result_802685B8 {
    int mUnknown0;
} Result_802685B8;

typedef struct Object_80268F54 {
    unsigned char mCount;
    unsigned char mUnknown1[3];
    int mUnknown4;
    int mValues[1];
} Object_80268F54;

typedef struct Object_80268FFC {
    unsigned char mUnknown0[24];
    int mUnknown18;
} Object_80268FFC;

typedef struct Object_80269008 {
    unsigned char mUnknown0[16];
    int mUnknown10;
} Object_80269008;

typedef struct Object_80269014 {
    unsigned char mUnknown0[16];
    unsigned char mUnknown10;
    unsigned char mUnknown11[3];
    int mUnknown14[1];
} Object_80269014;

typedef struct Object_80269048 {
    unsigned char mUnknown0[24];
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown1A[2];
    int mUnknown1C[1];
} Object_80269048;

typedef void (*SndAemsBankSetter_t)(int voice, int value);
typedef void (*SndAemsOptSetter_t)(SndPlayOpts_t *opts, int value);
typedef int (*SndAemsUpdateFn_t)(void *state);

extern SndAemsBankSetter_t playerinterfacefn[12];
extern SndAemsOptSetter_t SNDAEMSoptfn[12];
extern int fn_801B9B30(void *p, int *value);
extern int SNDvol(int handle, int value);
extern float lbl_80300028;
void SNDAEMSI_bankvol(int voice, int value);

/* An envelope module's state: the offset of its gate input word, the last gate value, the current
   segment, the time left and per-tick step of that segment, the output level, the segment count,
   the sustain segment, the start level and the segments' (time, level) pairs from +0x18. */
typedef struct EnvelopeSegment_80267858 {
    float mTime;
    float mLevel;
} EnvelopeSegment_80267858;

typedef struct EnvelopeState_80267858 {
    unsigned short mInputOffset;
    signed char mLastInput;
    unsigned char mSegment;
    float mTime;
    float mStep;
    float mLevel;
    unsigned char mNumSegments;
    unsigned char unk_0x11;
    short mSustainSegment;
    float mStartLevel;
    EnvelopeSegment_80267858 mSegments[1];
} EnvelopeState_80267858;

/* A scale module's inputs: the input count, the scale factor and the input values. */
typedef struct ScaleState_80267EC4 {
    unsigned char mCount;
    unsigned char mUnknown1[3];
    float mScale;
    int mValues[1];
} ScaleState_80267EC4;

typedef struct Scale2State_80267F80 {
    float mScale;
    int mA;
    int mB;
} Scale2State_80267F80;

/* A player module's output reset: the playing output +0xE, whether one plays +0xF and the
   output records from +0x1C. */
typedef struct PlayerOutput_80268774 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} PlayerOutput_80268774;

typedef struct PlayerState_80268774 {
    unsigned char mUnknown0[14];
    unsigned char mOutput;
    unsigned char mPlaying;
    signed char mUnknown10;
    unsigned char mUnknown11[11];
    PlayerOutput_80268774 mOutputs[1];
} PlayerState_80268774;

/* A loaded module bank on the bank list: its handle and, 20 bytes in, its list link. */
typedef struct ModuleBank_80269260 {
    int mHandle;
    unsigned char mUnknown4[16];
    void *mpLink;
} ModuleBank_80269260;

extern void *lbl_803A6BD0;
extern int fn_802692B8(int handle);
extern void SNDSYS_entercritical(void);
extern void SNDSYS_leavecritical(void);

int fn_80266E88(int *p)
{
    int value = p[4];

    p[4] = 0;
    return value;
}

int fn_80266E9C(int *p)
{
    return p[5];
}

int fn_80266EA4(int *p)
{
    return p[6];
}

int fn_80266EAC(int *p)
{
    int value = p[0];

    p[0] = 0;
    return value;
}

int fn_80267114(Object_80267114 *p)
{
    int *values;
    int i;

    if (p->mUnknown8) {
        values = (int *)&p->mUnknownC[p->mUnknown9];
        for (i = 0; i < p->mUnknown9; i++) {
            int value = values[i + 1];
            int clamped;

            if (value < p->mUnknownC[i].mMin) {
                clamped = p->mUnknownC[i].mMin;
            } else {
                clamped = value;
                if (value > p->mUnknownC[i].mMax)
                    clamped = p->mUnknownC[i].mMax;
            }
            values[i + 1] = clamped;
        }
    } else {
        values = (int *)p->mUnknownC;
    }
    if (values[0] != 0)
        fn_801B9410(p, values + 1);
    return 0;
}

int fn_8026739C(Object_8026739C *p)
{
    int value;
    int v = p->mUnknown14;
    int lo, hi;

    if (p->mUnknown10 != v) {
        p->mUnknown10 = v;
        lo = p->mUnknown8;
        hi = p->mUnknownC;
        if (v < lo)
            value = lo;
        else if (v > hi)
            value = hi;
        else
            value = v;
        fn_801B9B30(p, &value);
    }
    return 0;
}

int fn_80267404(Object_80267404 *p)
{
    int v = p->mUnknown14;

    if (v >= p->mUnknown0 && v <= p->mUnknown4)
        return v;
    if (p->mUnknown10 > 0) {
        p->mUnknown8 += p->mUnknownC;
        if (p->mUnknown8 > p->mUnknown4)
            p->mUnknown8 = p->mUnknown0;
        else if (p->mUnknown8 < p->mUnknown0)
            p->mUnknown8 = p->mUnknown4;
        return p->mUnknown8;
    }
    return p->mUnknown8;
}

int fn_80267480(Object_80267480 *p)
{
    int result;

    if (p->mUnknownC != 0) {
        result = iSNDrandom() % p->mUnknown4 + p->mUnknown0;
        p->mUnknown8 = result;
    } else {
        result = p->mUnknown8;
    }
    return result;
}

int fn_802674DC(Object_802674DC *p)
{
    unsigned int index;

    if (*(int *)((char *)p + p->mUnknown0) != 0) {
        index = iSNDrandom() % (unsigned int)(p->mUnknownA - p->mUnknown8 - p->mUnknown3) + p->mUnknown8;
        if (p->mUnknown2 == 1) {
            p->mUnknownC = p->mUnknown10.mBytes[index];
            p->mUnknown10.mBytes[index] = p->mUnknown10.mBytes[p->mUnknown8];
            p->mUnknown10.mBytes[p->mUnknown8] = p->mUnknownC;
        } else {
            p->mUnknownC = p->mUnknown10.mShorts[index];
            p->mUnknown10.mShorts[index] = p->mUnknown10.mShorts[p->mUnknown8];
            p->mUnknown10.mShorts[p->mUnknown8] = p->mUnknownC;
        }
        p->mUnknownC += p->mUnknown4;
        if (++p->mUnknown8 >= p->mUnknownA) {
            p->mUnknown8 = 0;
            p->mUnknown3 = 1;
        } else {
            p->mUnknown3 = 0;
        }
    }
    return p->mUnknownC;
}

/* A weighted random module's state: the weight table, the output base, the choice count, the
   output and the trigger input. */
typedef struct RandomWeightTable_t {
    unsigned char unk_0x0[16];
    signed char mWeights[1];
} RandomWeightTable_t;

typedef struct RandomWeightedState_t {
    RandomWeightTable_t *mpTable;
    int mBase;
    int mCount;
    int mValue;
    int mTrigger;
} RandomWeightedState_t;

int SNDAEMSI_updaterandomweighted(RandomWeightedState_t *p)
{
    if (p->mTrigger != 0) {
        unsigned int roll = iSNDrandom() % 100;
        RandomWeightTable_t *table = p->mpTable;
        unsigned int sum;
        int i;

        for (i = 0, sum = 0; i < p->mCount; i++) {
            sum += table->mWeights[i];
            if (sum > roll) {
                p->mValue = i + p->mBase;
                break;
            }
        }
    }
    return p->mValue;
}

int fn_8026769C(Object_8026769C *p)
{
    if (p->mUnknown14 >= p->mUnknown0 && p->mUnknown14 <= p->mUnknown4) {
        if (p->mUnknown10 == 0) {
            p->mUnknown10 = 1;
            p->mUnknown11 = 1;
            return 1;
        }
    } else if (p->mUnknown14 >= p->mUnknown8 && p->mUnknown14 <= p->mUnknownC) {
        p->mUnknown10 = 0;
    }
    p->mUnknown11 = 0;
    return 0;
}

/* A delay trigger's state: the running time, the output, the trigger input and the delay. */
typedef struct DelayTrigState_t {
    float mTime;
    unsigned char mOutput;
    unsigned char unk_0x5[3];
    int mTrigger;
    int mDelay;
} DelayTrigState_t;

int SNDAEMSI_updatedelaytrig(DelayTrigState_t *p)
{
    if (p->mTrigger != 0)
        p->mTime = 0.0f;
    if (!(p->mTime < 0.0f)) {
        if (!(p->mTime < (float)p->mDelay)) {
            p->mOutput = 1;
            p->mTime = -1.0f;
            return 1;
        }
        p->mTime += Snd::gVariableTimerPeriod;
    }
    p->mOutput = 0;
    return 0;
}

int fn_802677B4(Object_802677B4 *p)
{
    int *flags = (int *)((char *)p + p->mUnknown0);
    int i;

    for (i = 0; i < p->mUnknown2; i++) {
        if (flags[i] != 0) {
            p->mUnknown4 = p->mUnknown8[i];
            break;
        }
    }
    return p->mUnknown4;
}

int fn_80267814(Object_80267814 *p)
{
    int i;

    for (i = 0; i < p->mUnknown0; i++) {
        if (p->mUnknown4[i] != 0)
            return 1;
    }
    return 0;
}

void SNDAEMSI_envelopeprogramsegment(EnvelopeState_80267858 *p)
{
    p->mTime = p->mSegments[p->mSegment].mTime;
    p->mStep = Snd::gVariableTimerPeriod * ((p->mSegments[p->mSegment].mLevel - p->mLevel) / p->mTime);
}

int SNDAEMSI_updateenvelope(EnvelopeState_80267858 *p)
{
    int *input = (int *)((char *)p + p->mInputOffset);

    if (*input == 1 && p->mLastInput == 0) {
        p->mSegment = 0;
        p->mLevel = p->mStartLevel;
        SNDAEMSI_envelopeprogramsegment(p);
    } else if (*input == 3 && (unsigned char)p->mLastInput != 3 && p->mSegment < p->mSustainSegment) {
        p->mSegment = p->mSustainSegment;
        SNDAEMSI_envelopeprogramsegment(p);
    } else if ((*input == 1 || *input == 3) && p->mSegment < p->mNumSegments) {
        p->mTime -= Snd::gVariableTimerPeriod;
        if (!(p->mTime > 0.0f)) {
            p->mLevel = p->mSegments[p->mSegment].mLevel;
            p->mSegment++;
            if (p->mSegment < p->mNumSegments)
                SNDAEMSI_envelopeprogramsegment(p);
            else
                p->mLevel = 0.0f;
        } else {
            p->mLevel += p->mStep;
        }
    } else if (*input != 2) {
        p->mLevel = 0.0f;
    }
    p->mLastInput = *input;
    return (int)(!(p->mLevel < 0.0f) ? p->mLevel + 0.5f : p->mLevel - 0.5f);
}

/* A lookup table module: the table (entry type, entry count, input range, index scale and the
   entries), the last input, the output and the input. */
typedef struct TableData_t {
    unsigned char mType;
    unsigned char unk_0x1;
    unsigned short mCount;
    int mMin;
    int mMax;
    float mScale;
    union {
        signed char mBytes[1];
        short mShorts[1];
        int mInts[1];
    } mEntries;
} TableData_t;

typedef struct TableState_t {
    TableData_t *mpTable;
    int mLastInput;
    int mOutput;
    int mInput;
} TableState_t;

int SNDAEMSI_updatetable(TableState_t *p)
{
    int input = p->mInput;

    if (input != p->mLastInput) {
        TableData_t *t = p->mpTable;
        int index;
        int min;
        int max;

        p->mLastInput = input;
        min = t->mMin;
        max = t->mMax;
        if (input < min)
            index = min;
        else if (input > max)
            index = max;
        else
            index = input;
        index -= t->mMin;
        if (t->mScale == 1.0f) {
            if (t->mType == 2)
                p->mOutput = t->mEntries.mShorts[index];
            else if (t->mType == 1)
                p->mOutput = t->mEntries.mBytes[index];
            else
                p->mOutput = t->mEntries.mInts[index];
        } else {
            float pos = (float)index * t->mScale;
            float start = pos - 0.5f;
            int first = (int)(!(start < 0.0f) ? start + 0.5f : start - 0.5f);
            int next = first + 1;
            float a;
            float b;
            float value;

            pos -= (float)first;
            if (next >= t->mCount)
                next = t->mCount - 1;
            if (t->mType == 2) {
                a = t->mEntries.mShorts[first];
                b = t->mEntries.mShorts[next];
            } else if (t->mType == 1) {
                a = t->mEntries.mBytes[first];
                b = t->mEntries.mBytes[next];
            } else {
                a = t->mEntries.mInts[first];
                b = t->mEntries.mInts[next];
            }
            value = pos * (b - a) + a;
            index = (int)(!(value < 0.0f) ? value + 0.5f : value - 0.5f);
            p->mOutput = index;
        }
    }
    return p->mOutput;
}

/* A delay line: the offset of its (value, delay) inputs, the buffer length, the write and read
   cursors, the last delay and the buffer. */
typedef struct DelayLineState_t {
    unsigned short mInputOffset;
    unsigned short mLength;
    unsigned short mWrite;
    unsigned short mRead;
    int mLastDelay;
    int mBuffer[1];
} DelayLineState_t;

int SNDAEMSI_updatedelayline(DelayLineState_t *p)
{
    int *input = (int *)((char *)p + p->mInputOffset);
    int value;

    if (input[1] != p->mLastDelay) {
        int ticks;

        p->mLastDelay = input[1];
        if (input[1] < 0)
            input[1] = 0;
        ticks = (int)((float)input[1] / Snd::gVariableTimerPeriod + 0.5f);
        if (ticks >= p->mLength)
            ticks = p->mLength - 1;
        p->mWrite = p->mRead + ticks;
    }
    if (p->mWrite >= p->mLength)
        p->mWrite -= p->mLength;
    if (p->mRead >= p->mLength)
        p->mRead = 0;
    p->mBuffer[p->mWrite] = input[0];
    value = p->mBuffer[p->mRead];
    p->mWrite++;
    p->mRead++;
    return value;
}

int fn_80267D84(Args_80267D84 *p)
{
    int index = p->mValues[0];

    if (index <= 0 || index > p->mCount)
        return 0;
    return p->mValues[index];
}

int fn_80267DB4(Object_80267DB4 *p)
{
    int index;

    p->mUnknownC[p->mUnknown2 - 1] = 0;
    index = p->mUnknown4;
    if (index > 0 && index <= p->mCount) {
        p->mUnknownC[index - 1] = p->mUnknown8;
        p->mUnknown2 = p->mUnknown4;
    }
    return p->mUnknownC[0];
}

int fn_80267E04(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++) {
        if (p->mValues[i] < result)
            result = p->mValues[i];
    }
    return result;
}

int fn_80267E48(int *p)
{
    int a = p[0];
    int b = p[1];

    if (a < b)
        return a;
    return b;
}

int fn_80267E64(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++) {
        if (p->mValues[i] > result)
            result = p->mValues[i];
    }
    return result;
}

int fn_80267EA8(int *p)
{
    int a = p[0];
    int b = p[1];

    if (a > b)
        return a;
    return b;
}

int SNDAEMSI_updatescale(ScaleState_80267EC4 *p)
{
    float value = p->mValues[0];
    int i;

    for (i = 1; i < p->mCount; i++)
        value *= p->mValues[i];
    value *= p->mScale;
    return (int)(!(value < 0.0f) ? value + 0.5f : value - 0.5f);
}

int SNDAEMSI_updatescale2(Scale2State_80267F80 *p)
{
    float value = (float)p->mA * (float)p->mB * p->mScale;

    return (int)(!(value < 0.0f) ? value + 0.5f : value - 0.5f);
}

int fn_8026801C(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++)
        result += p->mValues[i];
    return result;
}

int fn_80268058(int *p)
{
    return p[0] + p[1];
}

int fn_80268068(int *p)
{
    return p[0] - p[1];
}

int fn_80268078(int *p)
{
    return p[0] * p[1];
}

int fn_80268088(int *p)
{
    if (p[1] != 0)
        return p[0] / p[1];
    return 0;
}

int fn_802680A8(int *p)
{
    if (p[1] != 0)
        return p[0] % p[1];
    return 0;
}

void fn_802680D0(void)
{
}

void fn_802680D4(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    lbl_803A6C24.m1CC[voice].m8E = value;
    SNDPLATFORM_setpitch(voice);
}

void fn_80268130(int voice, int value)
{
    if (value > 8192)
        value = 8192;
    else if (value < 2048)
        value = 2048;
    lbl_803A6C24.m1CC[voice].m6E = value;
    SNDPLATFORM_timemult(voice, value);
}

void SNDAEMSI_bankvol(int voice, int value)
{
    Record_803A6DF0 *v = &lbl_803A6C24.m1CC[voice];
    int clamped;
    int i;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    v->m38 = (float)clamped * (1.0f / 32767.0f);
    v->m48 = v->m38 * lbl_80300028;
    for (i = 0; i < v->m23; i++) {
        int index = v->m4[i];
        Record_803A6DF0 *sub = &lbl_803A6C24.m1CC[index];

        sub->m38 = v->m38;
        sub->m48 = v->m48;
        SndHalSetVol(index);
    }
}

void fn_80268270(int voice, int value)
{
    Record_803A6DF0 *v = &lbl_803A6C24.m1CC[voice];

    if (v->m23 == 1) {
        v->m1C = value;
        SndHalSetPan(voice);
    }
}

void SNDAEMSI_bankfxwet0(int voice, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    lbl_803A6C24.m1CC[voice].m60 = clamped >> 8;
    *lbl_803A6C24.m1CC[voice].m64 = (float)(signed char)lbl_803A6C24.m1CC[voice].m60 * (1.0f / 127.0f);
    SNDPLATFORM_setfxlevel(voice, 0);
}

void fn_80268354(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    SNDPLATFORM_lowpass(voice, value);
}

void fn_8026839C(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    SNDPLATFORM_highpass(voice, value);
}

void fn_802683E4(int voice, int value)
{
    Record_803A6DF0 *v = &lbl_803A6C24.m1CC[voice];
    int clamped;
    int i;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    value = clamped >> 8;
    for (i = 0; i < v->m23; i++) {
        int index = v->m4[i];
        lbl_803A6C24.m1CC[index].m5F = value;
        SndHalSetDry(index);
    }
}

void fn_80268480(SndPlayOpts_t *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->mC = value;
}

void fn_802684B0(SndPlayOpts_t *p, int value)
{
    if (value > 8192)
        value = 8192;
    else if (value < 2048)
        value = 2048;
    p->mE = value;
}

void fn_802684D4(SndPlayOpts_t *p, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    p->m0 = clamped >> 8;
}

void fn_802684FC(SndPlayOpts_t *p, int value)
{
    p->m8 = value;
}

void fn_80268504(SndPlayOpts_t *p, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    p->m5 = clamped >> 8;
}

void fn_8026852C(SndPlayOpts_t *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->m14 = value;
}

void fn_8026855C(SndPlayOpts_t *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->m16 = value;
}

void fn_8026858C(SndPlayOpts_t *p, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    p->m4 = clamped >> 8;
}

void fn_802685B4(void)
{
}

Result_802685B8 fn_802685B8(Object_802685B8 *p, int *q)
{
    SndPlayOpts_t params;
    Result_802685B8 result;
    Entry_802686CC *e;
    int i;

    SNDplaysetdef(&params);
    params.m5 = 0;
    e = p->mEntries;
    for (i = 0; i < p->mUnknownE; i++, e++) {
        SNDAEMSoptfn[e->mType](&params, e->mUnknown8);
        e->mUnknown4 = e->mUnknown8;
    }
    result.mUnknown0 = SNDBANK_play(p->mUnknown0->mUnknown40, q[1], &params);
    return result;
}

int fn_80268668(Object_802686CC *p)
{
    return SNDstop(p->mUnknown8);
}

int fn_8026868C(int *p)
{
    int handle = *p;

    SNDvol(handle, 0);
    return SNDpitchmult(handle, 0);
}

void fn_802686CC(Object_802686CC *p)
{
    int a = 4096;
    int b = 32767;
    int handle;
    int i;
    Entry_802686CC *e;

    handle = SNDVOICEI_get(p->mUnknown8);
    if (handle >= 0) {
        e = p->mEntries;
        for (i = 0; i < p->mUnknownE; i++, e++) {
            if (e->mType == 0) {
                a = e->mUnknown8;
                e->mUnknown4 = a;
            } else if (e->mType == 2) {
                b = e->mUnknown8;
                e->mUnknown4 = b;
            }
        }
        fn_802680D4(handle, a);
        SNDAEMSI_bankvol(handle, b);
    }
}

int SNDAEMSI_playerresetoutputs(PlayerState_80268774 *p)
{
    p->mUnknown10 = -1;
    if (p->mPlaying != 0) {
        PlayerOutput_80268774 *outputs = p->mOutputs;
        int output = p->mOutput;

        outputs[output].mUnknown4 = 0;
        outputs[output].mUnknown0 = 0;
    }
    return 0;
}

/* A bank player's inputs (type, last and current value, 12 bytes each, from +0x1C) and, after
   them, its two outputs: the time left and the play position, in milliseconds. */
typedef struct PlayerInput_t {
    unsigned char mType;
    unsigned char unk_0x1[3];
    int mLast;
    int mValue;
} PlayerInput_t;

typedef struct PlayerTimes_t {
    int mRemaining;
    int mPosition;
} PlayerTimes_t;

typedef struct PlayerSample_t {
    signed char mType;
    unsigned char unk_0x1[3];
    int mPatch;
    int unk_0x8;
} PlayerSample_t;

typedef struct PlayerSampleList_t {
    int mCount;
    PlayerSample_t mSamples[1];
} PlayerSampleList_t;

typedef struct PlayerHandle_t {
    int mHandle;
} PlayerHandle_t;

typedef struct PlayerState_t {
    void *mpOwner;
    PlayerSampleList_t *mpSamples;
    PlayerHandle_t mHandle;
    signed char mMode : 8;
    signed char mPrevMode : 8;
    unsigned char mNumInputs : 8;
    unsigned char mPlaying : 8;
    signed char mType;
    unsigned char unk_0x11[3];
    int mSample;
    int mModeInput;
    PlayerInput_t mInputs[1];
} PlayerState_t;

typedef PlayerHandle_t (*SndAemsPlayFn_t)(...);
typedef int (*SndAemsPlayerFn_t)(PlayerState_t *p);
typedef int (*SndAemsPauseFn_t)(PlayerHandle_t handle);

extern SndAemsPlayFn_t SNDAEMSplayerplayfn[4];
extern SndAemsPlayerFn_t SNDAEMSplayerstopfn[4];
extern SndAemsPauseFn_t SNDAEMSplayerpausefn[4];
extern SndAemsPlayerFn_t SNDAEMSplayerunpausefn[4];
extern SndAemsPlayerFn_t SNDAEMSplayerupdatefn[4];

int SNDAEMSI_playerupdatebank(PlayerState_t *p)
{
    int i;
    PlayerInput_t *input = p->mInputs;
    int voice = SNDVOICEI_get(p->mHandle.mHandle);

    if (voice < 0)
        return SNDAEMSI_playerresetoutputs((PlayerState_80268774 *)p);
    for (i = 0; i < p->mNumInputs; i++) {
        if (input->mValue != input->mLast) {
            playerinterfacefn[input->mType](voice, input->mValue);
            input->mLast = input->mValue;
        }
        input++;
    }
    if (p->mPlaying != 0) {
        Record_803A6DF0 *v = &lbl_803A6C24.m1CC[voice];
        float msPerFrame = 1000.0f / (float)v->m20;
        int frame = SNDPLATFORM_getcurframe(voice);
        float ms = (float)frame * msPerFrame;
        int value;

        value = (int)(!(ms < 0.0f) ? ms + 0.5f : ms - 0.5f);
        ((PlayerTimes_t *)input)->mPosition = value;
        if (v->m18 <= 0) {
            ms = (float)((unsigned int)v->m14 - frame) * msPerFrame;
            value = (int)(!(ms < 0.0f) ? ms + 0.5f : ms - 0.5f);
        } else {
            value = 0;
        }
        ((PlayerTimes_t *)input)->mRemaining = value;
    }
    return 1;
}

int SNDAEMSI_updateplayer(PlayerState_t *p)
{
    int input = p->mModeInput;
    int mode;

    if (input < 0)
        mode = 0;
    else if (input > 2)
        mode = 2;
    else
        mode = input;
    if (mode != p->mMode) {
        if (mode == 0) {
            if (p->mType >= 0) {
                SNDAEMSplayerstopfn[p->mType](p);
                SNDAEMSI_playerresetoutputs((PlayerState_80268774 *)p);
            }
        } else if (mode == 1) {
            if (p->mType >= 0) {
                SNDAEMSplayerunpausefn[p->mType](p);
            } else if (!(p->mMode == 2 && p->mPrevMode == 1)) {
                int index = p->mSample;
                PlayerSampleList_t *list = p->mpSamples;
                int count = list->mCount;

                if (index >= count)
                    index = count - 1;
                else if (index < 0)
                    index = 0;
                p->mType = list->mSamples[index].mType;
                p->mHandle = SNDAEMSplayerplayfn[p->mType](p, &list->mSamples[index]);
                if (p->mHandle.mHandle < 0)
                    SNDAEMSI_playerresetoutputs((PlayerState_80268774 *)p);
            }
        } else {
            if (p->mType >= 0)
                SNDAEMSplayerpausefn[p->mType](p->mHandle);
        }
        p->mPrevMode = p->mMode;
        p->mMode = mode;
    }
    if (mode == 1 && p->mType >= 0)
        mode = SNDAEMSplayerupdatefn[p->mType](p);
    if (p->mType < 0)
        mode = 0;
    return mode;
}

/* An oscillator: the waveform (0 sine, 1 square, 2 saw, else triangle), the phase in cycles,
   the period and the amplitude. */
typedef struct OscillatorState_t {
    unsigned char mWaveform;
    unsigned char unk_0x1[3];
    float mPhase;
    int mPeriod;
    int mAmplitude;
} OscillatorState_t;

int SNDAEMSI_updateoscillator(OscillatorState_t *p)
{
    float step;
    float amplitude;
    float value;

    if (p->mPeriod <= 0)
        return 0;
    step = Snd::gVariableTimerPeriod / (float)p->mPeriod;
    amplitude = (float)p->mAmplitude;
    if (!(p->mPhase < 1.0f)) {
        do {
            p->mPhase -= 1.0f;
        } while (p->mPhase >= 1.0f);
    }
    if (p->mWaveform == 0) {
        float angle = p->mPhase * 1024.0f;

        value = (float)iSNDsin((int)(!(angle < 0.0f) ? angle + 0.5f : angle - 0.5f)) * (1.0f / 65536.0f) * amplitude;
    } else if (p->mWaveform == 1) {
        if (!(p->mPhase < 0.5f))
            value = amplitude;
        else
            value = 0.0f;
    } else {
        float shape;

        if (p->mWaveform == 2)
            shape = p->mPhase;
        else if (!(p->mPhase >= 0.5f))
            shape = p->mPhase * 2.0f;
        else
            shape = (1.0f - p->mPhase) * 2.0f;
        value = shape * amplitude;
    }
    p->mPhase += step;
    return (int)(!(value < 0.0f) ? value + 0.5f : value - 0.5f);
}

/* A ramp: the current value, the per-tick rate, the target and time it was set up for, the ramp
   time, the rate multiplier and the target input. */
typedef struct RampState_t {
    float mValue;
    float mRate;
    int mLastTarget;
    int mLastTime;
    int mTime;
    int mScale;
    int mTarget;
} RampState_t;

int SNDAEMSI_updateramp(RampState_t *p)
{
    float target = (float)p->mTarget;

    if (target == p->mValue)
        return p->mTarget;
    if (p->mTarget != p->mLastTarget || p->mTime != p->mLastTime) {
        p->mLastTarget = p->mTarget;
        p->mLastTime = p->mTime;
        if (p->mTime <= 0) {
            p->mValue = target;
            return p->mTarget;
        }
        p->mRate = (target - p->mValue) * Snd::gVariableTimerPeriod / (float)p->mTime * (1.0f / 4096.0f);
    }
    p->mValue = p->mRate * (float)p->mScale + p->mValue;
    if (!(p->mRate < 0.0f)) {
        if (!(p->mValue <= (float)p->mTarget))
            p->mValue = (float)p->mTarget;
    } else {
        if (!(p->mValue >= (float)p->mTarget))
            p->mValue = (float)p->mTarget;
    }
    return (int)(!(p->mValue < 0.0f) ? p->mValue + 0.5f : p->mValue - 0.5f);
}

int fn_80268F54(Object_80268F54 *p)
{
    int i;
    int sum = p->mValues[0];

    for (i = 1; i < p->mCount; i++)
        sum += p->mValues[i];
    if (sum > p->mUnknown4)
        return p->mUnknown4;
    return sum;
}

int fn_80268FA0(int *p)
{
    int value = p[1] - p[2];

    if (value < p[0])
        return p[0];
    return value;
}

int fn_80268FC4(int *p)
{
    int value = p[1] * p[2];

    if (value > p[0])
        return p[0];
    return value;
}

int fn_80268FE8(Object_80269048 *p)
{
    int value = p->mUnknown19;

    p->mUnknown19 = 0;
    return value;
}

void fn_80268FFC(int *values, Object_80268FFC *p)
{
    p->mUnknown18 = values[0];
}

void fn_80269008(int *values, Object_80269008 *p)
{
    p->mUnknown10 = 1;
}

void fn_80269014(int *values, Object_80269014 *p)
{
    int i;

    for (i = 0; i < p->mUnknown10; i++)
        p->mUnknown14[i] = values[i];
}

void fn_80269048(int *values, Object_80269048 *p)
{
    int i;

    for (i = 0; i < p->mUnknown18; i++)
        p->mUnknown1C[i] = values[i];
    p->mUnknown19 = 1;
}

int fn_80266EC0(void *state);
int fn_802671D0(void *state);

SndAemsBankSetter_t playerinterfacefn[12] = {
    fn_802680D4, fn_80268130, SNDAEMSI_bankvol, fn_80268270,
    (SndAemsBankSetter_t)fn_802680D0, SNDAEMSI_bankfxwet0, fn_80268354, fn_8026839C,
    fn_802683E4, (SndAemsBankSetter_t)fn_802680D0, (SndAemsBankSetter_t)fn_802680D0,
    (SndAemsBankSetter_t)fn_802680D0,
};

SndAemsOptSetter_t SNDAEMSoptfn[12] = {
    fn_80268480, fn_802684B0, fn_802684D4, fn_802684FC,
    (SndAemsOptSetter_t)fn_802685B4, fn_80268504, fn_8026852C, fn_8026855C,
    fn_8026858C, (SndAemsOptSetter_t)fn_802685B4, (SndAemsOptSetter_t)fn_802685B4,
    (SndAemsOptSetter_t)fn_802685B4,
};

SndAemsPlayFn_t SNDAEMSplayerplayfn[4] = { (SndAemsPlayFn_t)fn_802685B8 };
SndAemsPlayerFn_t SNDAEMSplayerstopfn[4] = { (SndAemsPlayerFn_t)fn_80268668 };
SndAemsPauseFn_t SNDAEMSplayerpausefn[4] = { (SndAemsPauseFn_t)fn_8026868C };
SndAemsPlayerFn_t SNDAEMSplayerunpausefn[4] = { (SndAemsPlayerFn_t)fn_802686CC };
SndAemsPlayerFn_t SNDAEMSplayerupdatefn[4] = { (SndAemsPlayerFn_t)SNDAEMSI_playerupdatebank };

SndAemsUpdateFn_t sndaemsfuncs[40] = {
    (SndAemsUpdateFn_t)fn_80266E88, (SndAemsUpdateFn_t)fn_80266E9C, (SndAemsUpdateFn_t)fn_80266EA4,
    (SndAemsUpdateFn_t)fn_80266EAC, fn_80266EC0, (SndAemsUpdateFn_t)fn_80267114,
    (SndAemsUpdateFn_t)fn_80267404, (SndAemsUpdateFn_t)fn_80267480, (SndAemsUpdateFn_t)fn_802674DC,
    (SndAemsUpdateFn_t)SNDAEMSI_updaterandomweighted, (SndAemsUpdateFn_t)fn_8026769C,
    (SndAemsUpdateFn_t)SNDAEMSI_updatedelaytrig, (SndAemsUpdateFn_t)fn_802677B4,
    (SndAemsUpdateFn_t)fn_80267814, (SndAemsUpdateFn_t)SNDAEMSI_updateenvelope, (SndAemsUpdateFn_t)SNDAEMSI_updatetable, (SndAemsUpdateFn_t)SNDAEMSI_updatedelayline,
    (SndAemsUpdateFn_t)fn_80267D84, (SndAemsUpdateFn_t)fn_80267DB4, (SndAemsUpdateFn_t)fn_80267E04,
    (SndAemsUpdateFn_t)fn_80267E64, (SndAemsUpdateFn_t)SNDAEMSI_updatescale,
    (SndAemsUpdateFn_t)fn_8026801C, (SndAemsUpdateFn_t)fn_80268068, (SndAemsUpdateFn_t)fn_80268078,
    (SndAemsUpdateFn_t)fn_80268088, (SndAemsUpdateFn_t)fn_802680A8, (SndAemsUpdateFn_t)SNDAEMSI_updateplayer, (SndAemsUpdateFn_t)SNDAEMSI_updateoscillator,
    (SndAemsUpdateFn_t)SNDAEMSI_updateramp, (SndAemsUpdateFn_t)fn_80268F54, (SndAemsUpdateFn_t)fn_80268FA0,
    (SndAemsUpdateFn_t)fn_80268FC4, (SndAemsUpdateFn_t)fn_80267E48, (SndAemsUpdateFn_t)fn_80267EA8,
    (SndAemsUpdateFn_t)SNDAEMSI_updatescale2, (SndAemsUpdateFn_t)fn_80268058,
    (SndAemsUpdateFn_t)fn_80268FE8, fn_802671D0, (SndAemsUpdateFn_t)fn_8026739C,
};

void SNDAEMSI_restore(void)
{
    SNDSYS_entercritical();
    while (lbl_803A6BD0 != 0)
        fn_802692B8(((ModuleBank_80269260 *)((char *)lbl_803A6BD0 - 20))->mHandle);
    SNDSYS_leavecritical();
}

int SNDAEMSI_createmodulebankhandle(void)
{
    static int modulebankhandle = 0;

    modulebankhandle++;
    if (modulebankhandle < 0)
        modulebankhandle = 1;
    return modulebankhandle;
}
}
