/* The sound library's AEMS module player (saems.c): the AEMS audio-effect modules that drive the
   game's sound effects (counters, random pickers, triggers, envelopes, tables, delay lines, math
   and player modules), the per-voice bank and play-option setters they feed, the bank players,
   the Csis class callbacks that create module instances, and the module bank registry. */

#include "engine/sndbank.h"
#include "engine/sndaems_state.h"
#include "engine/csis.h"

extern "C" {

typedef struct CounterState_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    signed char mUnknownC;
    unsigned char mUnknownD[3];
    int mUnknown10;
    int mUnknown14;
} CounterState_t;

typedef struct RandomState_t {
    int mUnknown0;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknownC;
} RandomState_t;

typedef struct RandomShuffleState_t {
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
} RandomShuffleState_t;

typedef struct RangeTrigState_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12[2];
    int mUnknown14;
} RangeTrigState_t;

typedef struct StateGenState_t {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    int mUnknown4;
    int mUnknown8[1];
} StateGenState_t;

typedef struct MergeTrigState_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    int mUnknown4[1];
} MergeTrigState_t;

typedef struct Args_80267D84 {
    unsigned char mCount;
    unsigned char mUnknown1[3];
    int mValues[1];
} Args_80267D84;

typedef struct DemuxState_t {
    unsigned char mCount;
    unsigned char mUnknown1;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC[1];
} DemuxState_t;

typedef struct Entry_802686CC {
    unsigned char mType;
    unsigned char mUnknown1[3];
    int mUnknown4;
    int mUnknown8;
} Entry_802686CC;

typedef struct BankPlayerState_t {
    unsigned char mUnknown0[8];
    int mUnknown8;
    unsigned char mUnknownC[2];
    unsigned char mUnknownE;
    unsigned char mUnknownF[13];
    Entry_802686CC mEntries[1];
} BankPlayerState_t;

typedef struct Owner_802685B8 {
    unsigned char mUnknown0[64];
    int mUnknown40;
} Owner_802685B8;

typedef struct BankPlayerStartState_t {
    Owner_802685B8 *mUnknown0;
    unsigned char mUnknown4[10];
    unsigned char mUnknownE;
    unsigned char mUnknownF[13];
    Entry_802686CC mEntries[1];
} BankPlayerStartState_t;

typedef struct Result_802685B8 {
    int mUnknown0;
} Result_802685B8;

typedef struct AddMaxState_t {
    unsigned char mCount;
    unsigned char mUnknown1[3];
    int mUnknown4;
    int mValues[1];
} AddMaxState_t;

typedef void (*SndAemsBankSetter_t)(int voice, int value);
typedef void (*SndAemsOptSetter_t)(SndPlayOpts_t *opts, int value);
typedef int (*SndAemsUpdateFn_t)(void *state);

extern SndAemsBankSetter_t playerinterfacefn[12];
extern SndAemsOptSetter_t SNDAEMSoptfn[12];
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

/* A parameter range of a call or class module, and the inputs that follow the ranges: the trigger
   (create for a class), the release request of a class, then the parameters. */
typedef struct AemsRange_t {
    int mMin;
    int mMax;
} AemsRange_t;

typedef struct CallFunctionInput_t {
    int mTrigger;
    int mParams[1];
} CallFunctionInput_t;

typedef struct CallFunctionState_t {
    Csis::FunctionHandle mHandle;
    unsigned char mClamp;
    unsigned char mNumParams;
    unsigned char unk_0xA[2];
    AemsRange_t mRanges[1];
} CallFunctionState_t;

typedef struct ControlClassInput_t {
    int mCreate;
    int mRelease;
    int mParams[1];
} ControlClassInput_t;

typedef struct ControlClassState_t {
    Csis::ClassHandle mHandle;
    Csis::Class *mpObject;
    unsigned char mClamp;
    unsigned char mNumParams;
    unsigned char unk_0xE[2];
    AemsRange_t mRanges[1];
} ControlClassState_t;

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

/* A module class of a bank (60 bytes, then one offset word per player state and per class state
   of an instance): its Csis class handle and constructor client, the instance count and limit,
   the instance's global variable, function, player and class state counts and whether it has a
   destructor and member data, the instance update callback, the instance template and its size,
   the offset of the destroy state and the list of live instances. */
typedef struct AemsInstance_t AemsInstance_t;

typedef struct AemsClass_t {
    int unk_0x0;
    Csis::ClassHandle mHandle;
    Csis::ClassConstructorClient mConstructor;
    short mNumInstances;
    short mMaxInstances;
    unsigned short mNumGlobals;
    unsigned short mNumFunctions;
    unsigned char mNumPlayers;
    unsigned char mHasDestructor;
    unsigned char mHasMemberData;
    unsigned char mNumClasses;
    void (*mpUpdate)(void *context);
    void *mpTemplate;
    int mInstanceSize;
    int mDestroyOffset;
    AemsInstance_t *mpInstances;
    int mStateOffsets[1];
} AemsClass_t;

/* A module instance: its link on the class's instance list, its client on the module timer list,
   then the template's data (the Csis client records first). */
struct AemsInstance_t {
    AemsInstance_t *mpNext;
    AemsInstance_t *mpPrev;
    SndAemsTimerClient_t mTimer;
    unsigned char mData[1];
};

/* The destroy state of an instance: its class, the instance, its Csis object and the request. */
typedef struct DestroyState_t {
    AemsClass_t *mpClass;
    AemsInstance_t *mpInstance;
    Csis::Class *mpObject;
    int mDestroy;
} DestroyState_t;

/* A Csis client record of an instance: a handle and a function client, then (for functions and
   member data) a count of parameter words. */
typedef struct AemsVariableClient_t {
    Csis::GlobalVariableHandle mHandle;
    Csis::FunctionClient mClient;
    int mValue;
} AemsVariableClient_t;

typedef struct AemsFunctionClient_t {
    Csis::FunctionHandle mHandle;
    Csis::FunctionClient mClient;
    unsigned char mNumParams;
    unsigned char mCalled;
    unsigned char unk_0x1A[2];
    int mParams[1];
} AemsFunctionClient_t;

typedef struct AemsMemberDataClient_t {
    Csis::FunctionClient mClient;
    unsigned char mNumParams;
    unsigned char unk_0x11[3];
    int mParams[1];
} AemsMemberDataClient_t;

typedef struct AemsDestructorClient_t {
    Csis::ClassDestructorClient mClient;
    int mDestroyed;
} AemsDestructorClient_t;

/* A resolved module bank: its class count, code size, class table offset, fixup header offset,
   handle, sound banks, name and user word, and its link on sndaems.mpModuleBanks. */
typedef struct AemsModuleBank_t {
    unsigned char unk_0x0[10];
    unsigned short mNumClasses;
    unsigned char unk_0xC[8];
    int mSize;
    unsigned char unk_0x18[4];
    int mClassOffset;
    unsigned char unk_0x20[16];
    int mFixupHeaderOffset;
    int mRelocOffset;
    int mCsisOffset;
    int mHandle;
    int mBankA;
    int mBankB;
    char *mpName;
    int mUser;
    SndAemsModuleBankLink_t mLink;
} AemsModuleBank_t;

#define AEMS_BANK_FROM_LINK(link) ((AemsModuleBank_t *)((char *)(link) - 80))
// FAKEMATCH: the module bank list head read through a constant address (sndaems + 4) instead of sndaems.mpModuleBanks, for the target's folded sndaems+4 accesses
#define AEMS_MODULE_BANKS (*(SndAemsModuleBankLink_t **)((char *)&sndaems + 4))

static __inline int _SNDAEMSI_round(float x)
{
    return (int)(!(x < 0.0f) ? x + 0.5f : x - 0.5f);
}

static __inline int _SNDAEMSI_clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

int SNDAEMS_removemodulebank(int handle);
int SNDAEMSI_updatedestroy(DestroyState_t *p);
void SNDAEMSI_timerupdate(void *unused);
extern void SNDSYS_entercritical(void);
extern void SNDSYS_leavecritical(void);
unsigned int strlen(const char *s);
char *strcpy(char *dst, const char *src);

int SNDAEMSI_UpdateClassDestructor(int *p)
{
    int value = p[4];

    p[4] = 0;
    return value;
}

int SNDAEMSI_UpdateClassData(int *p)
{
    return p[5];
}

int SNDAEMSI_UpdateGlobalVariable(int *p)
{
    return p[6];
}

int SNDAEMSI_updatecreate(int *p)
{
    int value = p[0];

    p[0] = 0;
    return value;
}

int SNDAEMSI_updatedestroy(DestroyState_t *p)
{
    if (p->mDestroy != 0) {
        AemsInstance_t *inst;
        unsigned char *data;
        unsigned char *client;
        int *offsets;
        int i;

        {
            AemsInstance_t **head = &p->mpClass->mpInstances;
            AemsInstance_t *unlinked = p->mpInstance;

            if (unlinked == *head)
                *head = unlinked->mpNext;
            if (unlinked->mpPrev != 0)
                unlinked->mpPrev->mpNext = unlinked->mpNext;
            if (unlinked->mpNext != 0)
                unlinked->mpNext->mpPrev = unlinked->mpPrev;
        }
        {
            SndAemsTimerClient_t **head = &sndaems.mpTimerClients;
            SndAemsTimerClient_t *unlinked = &p->mpInstance->mTimer;

            if (unlinked == *head)
                *head = unlinked->mpNext;
            if (unlinked->mpPrev != 0)
                unlinked->mpPrev->mpNext = unlinked->mpNext;
            if (unlinked->mpNext != 0)
                unlinked->mpNext->mpPrev = unlinked->mpPrev;
        }
        inst = p->mpInstance;
        data = inst->mData;
        if (p->mpClass->mHasDestructor) {
            p->mpObject->UnsubscribeDestructorFast(&((AemsDestructorClient_t *)data)->mClient);
            data = inst->mData + sizeof(AemsDestructorClient_t);
        }
        client = data;
        for (i = 0; i < p->mpClass->mNumGlobals; i++) {
            Csis::GlobalVariable::UnsubscribeFast(&((AemsVariableClient_t *)client)->mHandle,
                                                  &((AemsVariableClient_t *)client)->mClient);
            client += sizeof(AemsVariableClient_t);
        }
        if (p->mpClass->mHasMemberData) {
            p->mpObject->UnsubscribeMemberDataFast(&((AemsMemberDataClient_t *)client)->mClient);
            client += ((AemsMemberDataClient_t *)client)->mNumParams * 4 + 20;
        }
        for (i = 0; i < p->mpClass->mNumFunctions; i++) {
            Csis::Function::UnsubscribeFast(&((AemsFunctionClient_t *)client)->mHandle,
                                            &((AemsFunctionClient_t *)client)->mClient);
            client += ((AemsFunctionClient_t *)client)->mNumParams * 4 + 28;
        }
        offsets = p->mpClass->mStateOffsets;
        for (i = 0; i < p->mpClass->mNumPlayers; i++) {
            PlayerState_t *player = (PlayerState_t *)((char *)p->mpInstance + *offsets++);

            if (player->mType >= 0)
                SNDAEMSplayerstopfn[player->mType](player);
        }
        for (i = 0; i < p->mpClass->mNumClasses; i++) {
            ControlClassState_t *object = (ControlClassState_t *)((char *)p->mpInstance + *offsets++);

            if (object->mpObject != 0)
                object->mpObject->Release();
        }
        p->mpClass->mNumInstances--;
        SNDMEMI_free(p->mpInstance);
    }
    return 0;
}

int UpdateCallFunction(CallFunctionState_t *p)
{
    CallFunctionInput_t *input;

    if (p->mClamp) {
        AemsRange_t *ranges = p->mRanges;
        int i;

        input = (CallFunctionInput_t *)&ranges[p->mNumParams];
        for (i = 0; i < p->mNumParams; i++) {
            input->mParams[i] = _SNDAEMSI_clamp(input->mParams[i], ranges[i].mMin, ranges[i].mMax);
        }
    } else {
        input = (CallFunctionInput_t *)p->mRanges;
    }
    if (input->mTrigger != 0)
        Csis::Function::CallFast(&p->mHandle, input->mParams);
    return 0;
}

int UpdateControlClass(ControlClassState_t *p)
{
    AemsRange_t *ranges = 0;
    ControlClassInput_t *input;
    int refs;
    int i;

    if (p->mClamp) {
        ranges = p->mRanges;
        input = (ControlClassInput_t *)&ranges[p->mNumParams];
    } else {
        input = (ControlClassInput_t *)p->mRanges;
    }
    if (input->mRelease != 0) {
        if (p->mpObject == 0)
            return 0;
        p->mpObject->Release();
        p->mpObject = 0;
    } else if (input->mCreate != 0) {
        if (p->mpObject == 0) {
            if (p->mClamp) {
                for (i = 0; i < p->mNumParams; i++) {
                    input->mParams[i] = _SNDAEMSI_clamp(input->mParams[i], ranges[i].mMin, ranges[i].mMax);
                }
            }
            if (Csis::Class::CreateInstanceFast(&p->mHandle, input->mParams, &p->mpObject) < 0)
                p->mpObject = 0;
        }
    } else {
        if (p->mpObject == 0)
            return 0;
        if (p->mClamp) {
            for (i = 0; i < p->mNumParams; i++) {
                input->mParams[i] = _SNDAEMSI_clamp(input->mParams[i], ranges[i].mMin, ranges[i].mMax);
            }
        }
        p->mpObject->SetMemberDataFast(input->mParams);
    }
    if (p->mpObject != 0) {
        p->mpObject->GetRefCount(&refs);
        return refs;
    }
    return 0;
}

/* A set-global-variable module: the Csis handle, the value range, the last input and the input. */
typedef struct SetGlobalVariableState_t {
    Csis::GlobalVariableHandle mHandle;
    int mMin;
    int mMax;
    int mLast;
    int mInput;
} SetGlobalVariableState_t;

int UpdateSetGlobalVariable(SetGlobalVariableState_t *p)
{
    int value;
    int v = p->mInput;
    int lo, hi;

    if (p->mLast != v) {
        p->mLast = v;
        lo = p->mMin;
        hi = p->mMax;
        if (v < lo)
            value = lo;
        else if (v > hi)
            value = hi;
        else
            value = v;
        Csis::GlobalVariable::SetFast(&p->mHandle, &value);
    }
    return 0;
}

int SNDAEMSI_updatecounter(CounterState_t *p)
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

int SNDAEMSI_updaterandom(RandomState_t *p)
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

int SNDAEMSI_updaterandomshuffle(RandomShuffleState_t *p)
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

int SNDAEMSI_updaterangetrig(RangeTrigState_t *p)
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

int SNDAEMSI_updatestategen(StateGenState_t *p)
{
    int *flags = (int *)((char *)p + p->mUnknown0);
    int i;

    for (i = 0; i < p->mUnknown2; i++) {
        int *flag = &flags[i];

        if (*flag != 0) {
            p->mUnknown4 = p->mUnknown8[i];
            break;
        }
    }
    return p->mUnknown4;
}

int SNDAEMSI_updatemerge(MergeTrigState_t *p)
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
    p->mStep = (p->mSegments[p->mSegment].mLevel - p->mLevel) / p->mTime;
    p->mStep *= Snd::gVariableTimerPeriod;
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
    return _SNDAEMSI_round(p->mLevel);
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
            int first = _SNDAEMSI_round(start);
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
            index = _SNDAEMSI_round(value);
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

int SNDAEMSI_updatemux(Args_80267D84 *p)
{
    int index = p->mValues[0];

    if (index <= 0 || index > p->mCount)
        return 0;
    return p->mValues[index];
}

int SNDAEMSI_updatedemux(DemuxState_t *p)
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

int SNDAEMSI_updatemin(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++) {
        if (p->mValues[i] < result)
            result = p->mValues[i];
    }
    return result;
}

int SNDAEMSI_updatemin2(int *p)
{
    int a = p[0];
    int b = p[1];

    if (a < b)
        return a;
    return b;
}

int SNDAEMSI_updatemax(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++) {
        if (p->mValues[i] > result)
            result = p->mValues[i];
    }
    return result;
}

int SNDAEMSI_updatemax2(int *p)
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
    return _SNDAEMSI_round(value);
}

int SNDAEMSI_updatescale2(Scale2State_80267F80 *p)
{
    float value = (float)p->mA * (float)p->mB * p->mScale;

    return _SNDAEMSI_round(value);
}

int SNDAEMSI_updateadd(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++)
        result += p->mValues[i];
    return result;
}

int SNDAEMSI_updateadd2(int *p)
{
    return p[0] + p[1];
}

int SNDAEMSI_updatesubtract(int *p)
{
    return p[0] - p[1];
}

int SNDAEMSI_updatemultiply(int *p)
{
    return p[0] * p[1];
}

int SNDAEMSI_updatedivide(int *p)
{
    if (p[1] != 0)
        return p[0] / p[1];
    return 0;
}

int SNDAEMSI_updatemodulo(int *p)
{
    if (p[1] != 0)
        return p[0] % p[1];
    return 0;
}

void SNDAEMSI_bankinputstub(void)
{
}

void SNDAEMSI_bankpitchmult(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    lbl_803A6C24.m1CC[voice].m8E = value;
    SNDPLATFORM_setpitch(voice);
}

void SNDAEMSI_banktimemult(int voice, int value)
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

void SNDAEMSI_bankazimuth(int voice, int value)
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

void SNDAEMSI_banklowpass(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    SNDPLATFORM_lowpass(voice, value);
}

void SNDAEMSI_bankhighpass(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    SNDPLATFORM_highpass(voice, value);
}

void SNDAEMSI_bankdrylevel(int voice, int value)
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

void SNDAEMSI_optpitchmult(SndPlayOpts_t *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->mC = value;
}

void SNDAEMSI_opttimemult(SndPlayOpts_t *p, int value)
{
    if (value > 8192)
        value = 8192;
    else if (value < 2048)
        value = 2048;
    p->mE = value;
}

void SNDAEMSI_optvol(SndPlayOpts_t *p, int value)
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

void SNDAEMSI_optazimuth(SndPlayOpts_t *p, int value)
{
    p->m8 = value;
}

void SNDAEMSI_optfxwet0(SndPlayOpts_t *p, int value)
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

void SNDAEMSI_optlowpass(SndPlayOpts_t *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->m14 = value;
}

void SNDAEMSI_opthighpass(SndPlayOpts_t *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->m16 = value;
}

void SNDAEMSI_optdrylevel(SndPlayOpts_t *p, int value)
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

void SNDAEMSI_optstub(void)
{
}

Result_802685B8 SNDAEMSI_playerplaybank(BankPlayerStartState_t *p, int *q)
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

int SNDAEMSI_playerstopbank(BankPlayerState_t *p)
{
    return SNDstop(p->mUnknown8);
}

int SNDAEMSI_playerpausebank(int *p)
{
    int handle = *p;

    SNDvol(handle, 0);
    return SNDpitchmult(handle, 0);
}

void SNDAEMSI_playerunpausebank(BankPlayerState_t *p)
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
        SNDAEMSI_bankpitchmult(handle, a);
        SNDAEMSI_bankvol(handle, b);
    }
}

int SNDAEMSI_playerresetoutputs(PlayerState_80268774 *p)
{
    p->mUnknown10 = -1;
    if (p->mPlaying != 0) {
        PlayerOutput_80268774 *outputs = p->mOutputs;
        PlayerOutput_80268774 *output = &outputs[p->mOutput];

        output->mUnknown4 = 0;
        output->mUnknown0 = 0;
    }
    return 0;
}

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

        ((PlayerTimes_t *)input)->mPosition = _SNDAEMSI_round(ms);
        if (v->m18 <= 0) {
            ms = (float)((unsigned int)v->m14 - frame) * msPerFrame;
            ((PlayerTimes_t *)input)->mRemaining = _SNDAEMSI_round(ms);
        } else {
            ((PlayerTimes_t *)input)->mRemaining = 0;
        }
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

                if (index >= p->mpSamples->mCount)
                    index = p->mpSamples->mCount - 1;
                else if (index < 0)
                    index = 0;
                p->mType = p->mpSamples->mSamples[index].mType;
                p->mHandle = SNDAEMSplayerplayfn[p->mType](p, &p->mpSamples->mSamples[index]);
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
    while (p->mPhase >= 1.0f)
        p->mPhase -= 1.0f;
    if (p->mWaveform == 0) {
        float angle = p->mPhase * 1024.0f;

        value = (float)iSNDsin(_SNDAEMSI_round(angle)) * (1.0f / 65536.0f) * amplitude;
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
    return _SNDAEMSI_round(value);
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
        p->mRate = target - p->mValue;
        p->mRate *= Snd::gVariableTimerPeriod;
        p->mRate /= (float)p->mTime;
        p->mRate *= 1.0f / 4096.0f;
    }
    p->mValue = p->mRate * (float)p->mScale + p->mValue;
    if (!(p->mRate < 0.0f)) {
        if (!(p->mValue <= (float)p->mTarget))
            p->mValue = (float)p->mTarget;
    } else {
        if (!(p->mValue >= (float)p->mTarget))
            p->mValue = (float)p->mTarget;
    }
    return _SNDAEMSI_round(p->mValue);
}

int SNDAEMSI_updateaddmax(AddMaxState_t *p)
{
    int i;
    int sum = p->mValues[0];

    for (i = 1; i < p->mCount; i++)
        sum += p->mValues[i];
    if (sum > p->mUnknown4)
        return p->mUnknown4;
    return sum;
}

int SNDAEMSI_updatesubtractmin(int *p)
{
    int value = p[1] - p[2];

    if (value < p[0])
        return p[0];
    return value;
}

int SNDAEMSI_updatemultiplymax(int *p)
{
    int value = p[1] * p[2];

    if (value > p[0])
        return p[0];
    return value;
}

int UpdateFunction(AemsFunctionClient_t *p)
{
    int value = p->mCalled;

    p->mCalled = 0;
    return value;
}

void SNDAEMSI_SetGlobalVariable(int *values, AemsVariableClient_t *p)
{
    p->mValue = values[0];
}

void SNDAEMSI_SetClassDestructor(int *values, AemsDestructorClient_t *p)
{
    p->mDestroyed = 1;
}

void SNDAEMSI_SetClassData(int *values, AemsMemberDataClient_t *p)
{
    int i;

    for (i = 0; i < p->mNumParams; i++)
        p->mParams[i] = values[i];
}

void CsisFunctionCallback(int *values, AemsFunctionClient_t *p)
{
    int i;

    for (i = 0; i < p->mNumParams; i++)
        p->mParams[i] = values[i];
    p->mCalled = 1;
}

void SNDAEMSI_CreateModuleInstance(Csis::Class *object, Csis::Parameter *params, void *context)
{
    AemsClass_t *c = (AemsClass_t *)context;
    AemsInstance_t *inst;
    DestroyState_t *destroy;
    unsigned char *data;
    unsigned char *cursor;
    int i;

    SNDSYS_entercritical();
    if (c->mNumInstances >= c->mMaxInstances || (inst = (AemsInstance_t *)SNDMEMI_allocz(c->mInstanceSize)) == 0) {
        SNDSYS_leavecritical();
        return;
    }
    SNDI_memcpy(inst, c->mpTemplate, c->mInstanceSize);
    destroy = (DestroyState_t *)((char *)inst + c->mDestroyOffset);
    destroy->mpClass = c;
    destroy->mpInstance = inst;
    destroy->mpObject = object;
    inst->mpNext = c->mpInstances;
    inst->mpPrev = 0;
    if (c->mpInstances != 0)
        c->mpInstances->mpPrev = inst;
    c->mpInstances = inst;
    inst->mTimer.mpCallback = c->mpUpdate;
    inst->mTimer.mpContext = inst->mData;
    {
        SndAemsTimerClient_t **head = &sndaems.mpTimerClients;
        SndAemsTimerClient_t *linked = &inst->mTimer;

        linked->mpNext = *head;
        linked->mpPrev = 0;
        if (*head != 0)
            (*head)->mpPrev = linked;
        *head = linked;
    }
    data = inst->mData;
    if (c->mHasDestructor) {
        AemsDestructorClient_t *client = (AemsDestructorClient_t *)data;

        client->mClient.mContext = client;
        client->mClient.mCallback = (void (*)(Csis::Class *, void *))SNDAEMSI_SetClassDestructor;
        object->SubscribeDestructorFast(&client->mClient);
        data = inst->mData + sizeof(AemsDestructorClient_t);
    }
    cursor = data;
    for (i = 0; i < c->mNumGlobals; i++) {
        AemsVariableClient_t *client = (AemsVariableClient_t *)cursor;

        client->mClient.mCallback = (void (*)(Csis::Parameter *, void *))SNDAEMSI_SetGlobalVariable;
        client->mClient.mContext = client;
        Csis::GlobalVariable::SubscribeFast(&client->mHandle, &client->mClient);
        cursor += sizeof(AemsVariableClient_t);
    }
    if (c->mHasMemberData) {
        AemsMemberDataClient_t *client = (AemsMemberDataClient_t *)cursor;

        client->mClient.mContext = client;
        client->mClient.mCallback = (void (*)(Csis::Parameter *, void *))SNDAEMSI_SetClassData;
        object->SubscribeMemberDataFast(&client->mClient);
        cursor += client->mNumParams * 4 + 20;
    }
    for (i = 0; i < c->mNumFunctions; i++) {
        AemsFunctionClient_t *client = (AemsFunctionClient_t *)cursor;

        client->mClient.mCallback = (void (*)(Csis::Parameter *, void *))CsisFunctionCallback;
        client->mClient.mContext = client;
        Csis::Function::SubscribeFast(&client->mHandle, &client->mClient);
        cursor += client->mNumParams * 4 + 28;
    }
    c->mNumInstances++;
    SNDSYS_leavecritical();
}


SndAemsBankSetter_t playerinterfacefn[12] = {
    SNDAEMSI_bankpitchmult, SNDAEMSI_banktimemult, SNDAEMSI_bankvol, SNDAEMSI_bankazimuth,
    (SndAemsBankSetter_t)SNDAEMSI_bankinputstub, SNDAEMSI_bankfxwet0, SNDAEMSI_banklowpass, SNDAEMSI_bankhighpass,
    SNDAEMSI_bankdrylevel, (SndAemsBankSetter_t)SNDAEMSI_bankinputstub, (SndAemsBankSetter_t)SNDAEMSI_bankinputstub,
    (SndAemsBankSetter_t)SNDAEMSI_bankinputstub,
};

SndAemsOptSetter_t SNDAEMSoptfn[12] = {
    SNDAEMSI_optpitchmult, SNDAEMSI_opttimemult, SNDAEMSI_optvol, SNDAEMSI_optazimuth,
    (SndAemsOptSetter_t)SNDAEMSI_optstub, SNDAEMSI_optfxwet0, SNDAEMSI_optlowpass, SNDAEMSI_opthighpass,
    SNDAEMSI_optdrylevel, (SndAemsOptSetter_t)SNDAEMSI_optstub, (SndAemsOptSetter_t)SNDAEMSI_optstub,
    (SndAemsOptSetter_t)SNDAEMSI_optstub,
};

SndAemsPlayFn_t SNDAEMSplayerplayfn[4] = { (SndAemsPlayFn_t)SNDAEMSI_playerplaybank };
SndAemsPlayerFn_t SNDAEMSplayerstopfn[4] = { (SndAemsPlayerFn_t)SNDAEMSI_playerstopbank };
SndAemsPauseFn_t SNDAEMSplayerpausefn[4] = { (SndAemsPauseFn_t)SNDAEMSI_playerpausebank };
SndAemsPlayerFn_t SNDAEMSplayerunpausefn[4] = { (SndAemsPlayerFn_t)SNDAEMSI_playerunpausebank };
SndAemsPlayerFn_t SNDAEMSplayerupdatefn[4] = { (SndAemsPlayerFn_t)SNDAEMSI_playerupdatebank };

SndAemsUpdateFn_t sndaemsfuncs[40] = {
    (SndAemsUpdateFn_t)SNDAEMSI_UpdateClassDestructor, (SndAemsUpdateFn_t)SNDAEMSI_UpdateClassData, (SndAemsUpdateFn_t)SNDAEMSI_UpdateGlobalVariable,
    (SndAemsUpdateFn_t)SNDAEMSI_updatecreate, (SndAemsUpdateFn_t)SNDAEMSI_updatedestroy, (SndAemsUpdateFn_t)UpdateCallFunction,
    (SndAemsUpdateFn_t)SNDAEMSI_updatecounter, (SndAemsUpdateFn_t)SNDAEMSI_updaterandom, (SndAemsUpdateFn_t)SNDAEMSI_updaterandomshuffle,
    (SndAemsUpdateFn_t)SNDAEMSI_updaterandomweighted, (SndAemsUpdateFn_t)SNDAEMSI_updaterangetrig,
    (SndAemsUpdateFn_t)SNDAEMSI_updatedelaytrig, (SndAemsUpdateFn_t)SNDAEMSI_updatestategen,
    (SndAemsUpdateFn_t)SNDAEMSI_updatemerge, (SndAemsUpdateFn_t)SNDAEMSI_updateenvelope, (SndAemsUpdateFn_t)SNDAEMSI_updatetable, (SndAemsUpdateFn_t)SNDAEMSI_updatedelayline,
    (SndAemsUpdateFn_t)SNDAEMSI_updatemux, (SndAemsUpdateFn_t)SNDAEMSI_updatedemux, (SndAemsUpdateFn_t)SNDAEMSI_updatemin,
    (SndAemsUpdateFn_t)SNDAEMSI_updatemax, (SndAemsUpdateFn_t)SNDAEMSI_updatescale,
    (SndAemsUpdateFn_t)SNDAEMSI_updateadd, (SndAemsUpdateFn_t)SNDAEMSI_updatesubtract, (SndAemsUpdateFn_t)SNDAEMSI_updatemultiply,
    (SndAemsUpdateFn_t)SNDAEMSI_updatedivide, (SndAemsUpdateFn_t)SNDAEMSI_updatemodulo, (SndAemsUpdateFn_t)SNDAEMSI_updateplayer, (SndAemsUpdateFn_t)SNDAEMSI_updateoscillator,
    (SndAemsUpdateFn_t)SNDAEMSI_updateramp, (SndAemsUpdateFn_t)SNDAEMSI_updateaddmax, (SndAemsUpdateFn_t)SNDAEMSI_updatesubtractmin,
    (SndAemsUpdateFn_t)SNDAEMSI_updatemultiplymax, (SndAemsUpdateFn_t)SNDAEMSI_updatemin2, (SndAemsUpdateFn_t)SNDAEMSI_updatemax2,
    (SndAemsUpdateFn_t)SNDAEMSI_updatescale2, (SndAemsUpdateFn_t)SNDAEMSI_updateadd2,
    (SndAemsUpdateFn_t)UpdateFunction, (SndAemsUpdateFn_t)UpdateControlClass, (SndAemsUpdateFn_t)UpdateSetGlobalVariable,
};

void SNDAEMSI_restore(void)
{
    SNDSYS_entercritical();
    while (AEMS_MODULE_BANKS != 0)
        SNDAEMS_removemodulebank(AEMS_BANK_FROM_LINK(AEMS_MODULE_BANKS)->mHandle);
    SNDSYS_leavecritical();
}

int SNDAEMS_removemodulebank(int handle)
{
    AemsModuleBank_t *bank;

    if (sndaems.mpBeforeRemoveBank != 0)
        sndaems.mpBeforeRemoveBank();
    SNDSYS_entercritical();
    for (bank = AEMS_BANK_FROM_LINK(AEMS_MODULE_BANKS); bank != 0;
         bank = AEMS_BANK_FROM_LINK(bank->mLink.mpNext)) {
        if (handle == bank->mHandle) {
            AemsClass_t *c = (AemsClass_t *)((char *)bank + bank->mClassOffset);
            int i;

            for (i = 0; i < bank->mNumClasses; i++) {
                AemsInstance_t *inst;
                int *offsets = c->mStateOffsets;

                Csis::Class::UnsubscribeConstructorFast(&c->mHandle, &c->mConstructor);
                inst = c->mpInstances;
                while (inst != 0) {
                    AemsInstance_t *next = inst->mpNext;
                    DestroyState_t *destroy = (DestroyState_t *)((char *)inst + c->mDestroyOffset);

                    destroy->mDestroy = 1;
                    SNDAEMSI_updatedestroy(destroy);
                    inst = next;
                }
                c = (AemsClass_t *)((char *)offsets + (c->mNumPlayers + c->mNumClasses) * 4);
            }
            if (bank->mpName != 0)
                SNDMEMI_free(bank->mpName);
            if (bank->mBankA >= 0)
                SNDbankremove(bank->mBankA);
            if (bank->mBankB >= 0)
                SNDbankremove(bank->mBankB);
            {
                SndAemsModuleBankLink_t **head = &AEMS_MODULE_BANKS;
                SndAemsModuleBankLink_t *unlinked = &bank->mLink;

                if (unlinked == *head)
                    *head = unlinked->mpNext;
                if (unlinked->mpPrev != 0)
                    unlinked->mpPrev->mpNext = unlinked->mpNext;
                if (unlinked->mpNext != 0)
                    unlinked->mpNext->mpPrev = unlinked->mpPrev;
            }
            if (AEMS_MODULE_BANKS == 0)
                Snd::gVariableTimerList.Remove((SndStreamFader_t *)&sndaems.mTimerClient);
            SNDSYS_leavecritical();
            return 0;
        }
    }
    SNDSYS_leavecritical();
    return -8;
}

int SNDAEMSI_createmodulebankhandle(void)
{
    static int modulebankhandle = 0;

    modulebankhandle++;
    if (modulebankhandle < 0)
        modulebankhandle = 1;
    return modulebankhandle;
}

/* A bank's fixup header: the count and bank offsets of the module function ids to patch. */
typedef struct AemsFixupHeader_t {
    int mCount;
    int mOffsets[1];
} AemsFixupHeader_t;

/* A Csis interface fixup: the handle's bank offset, the offset of its (hash, name) record and
   the handle kind (0 global variable, 1 class, else function). */
typedef struct AemsCsisFixup_t {
    int mHandleOffset;
    int mNameOffset;
    unsigned char mKind;
    unsigned char unk_0x9[3];
} AemsCsisFixup_t;

typedef struct AemsCsisFixups_t {
    int mCount;
    AemsCsisFixup_t mFixups[1];
} AemsCsisFixups_t;

void SNDAEMSI_resolvemodulebank(AemsModuleBank_t *bank, AemsFixupHeader_t *fixups, char *name, int user)
{
    int first;
    int i;
    unsigned char *base;
    int offset;
    AemsFixupHeader_t *relocs;
    AemsCsisFixups_t *csis;
    AemsClass_t *c;

    lbl_803A6C24.m1B4[0] = SNDAEMSI_restore;
    SNDSYS_entercritical();
    first = AEMS_MODULE_BANKS == 0;
    {
        SndAemsModuleBankLink_t **head = &AEMS_MODULE_BANKS;
        SndAemsModuleBankLink_t *linked = &bank->mLink;

        linked->mpNext = *head;
        linked->mpPrev = 0;
        if (*head != 0)
            (*head)->mpPrev = linked;
        *head = linked;
    }
    for (i = 0; i < fixups->mCount; i++) {
        unsigned short *id = (unsigned short *)((char *)bank + fixups->mOffsets[i]);
        unsigned short *fn = (unsigned short *)&sndaemsfuncs[(id[0] << 16) | id[2]];

        id[0] = fn[0];
        id[2] = fn[1];
    }
    // FAKEMATCH: the fixup base through the bank-relative offset of the fixups, for the target's subf/add pair
    offset = (unsigned char *)fixups - (unsigned char *)bank;
    base = (unsigned char *)bank + offset - bank->mFixupHeaderOffset;
    relocs = (AemsFixupHeader_t *)(base + bank->mRelocOffset);
    for (i = 0; i < relocs->mCount; i++)
        *(int *)((char *)bank + relocs->mOffsets[i]) += (int)bank;
    csis = (AemsCsisFixups_t *)(base + bank->mCsisOffset);
    for (i = 0; i < csis->mCount; i++) {
        AemsCsisFixup_t *fixup = &csis->mFixups[i];
        Csis::InterfaceId id;
        unsigned short *record = (unsigned short *)(base + fixup->mNameOffset);

        ((unsigned short *)&id.mHash)[0] = record[0];
        ((unsigned short *)&id.mHash)[1] = record[1];
        id.mName = (const char *)(record + 2);
        if (fixup->mKind == 0)
            ((Csis::GlobalVariableHandle *)((char *)bank + fixup->mHandleOffset))->SetFast(&id);
        else if (fixup->mKind == 1)
            ((Csis::ClassHandle *)((char *)bank + fixup->mHandleOffset))->SetFast(&id);
        else
            ((Csis::FunctionHandle *)((char *)bank + fixup->mHandleOffset))->SetFast(&id);
    }
    c = (AemsClass_t *)((char *)bank + bank->mClassOffset);
    for (i = 0; i < bank->mNumClasses; i++) {
        int *offsets;
        int j;

        c->mConstructor.mCallback = SNDAEMSI_CreateModuleInstance;
        c->mConstructor.mContext = c;
        c->mpUpdate = (void (*)(void *))((char *)bank + (int)c->mpUpdate);
        c->mpTemplate = (char *)bank + (int)c->mpTemplate;
        Csis::Class::SubscribeConstructorFast(&c->mHandle, &c->mConstructor);
        offsets = c->mStateOffsets;
        for (j = 0; j < c->mNumPlayers; j++)
            *(AemsModuleBank_t **)((char *)c->mpTemplate + offsets[j]) = bank;
        c = (AemsClass_t *)((char *)offsets + (c->mNumPlayers + c->mNumClasses) * 4);
    }
    if (name != 0 && name[0] != 0) {
        bank->mpName = (char *)SNDMEMI_allocz(strlen(name) + 1);
        strcpy(bank->mpName, name);
        bank->mUser = user;
    } else {
        bank->mpName = 0;
    }
    if (first) {
        // FAKEMATCH: callback and next through a state pointer and the rest through client, for the target's base-relative stores
        SndAemsState_t *state = &sndaems;
        SndAemsTimerClient_t *client = &state->mTimerClient;

        state->mTimerClient.mpCallback = SNDAEMSI_timerupdate;
        state->mTimerClient.mpNext = (SndAemsTimerClient_t *)Snd::gVariableTimerList.mpHead;
        client->mpPrev = 0;
        if (Snd::gVariableTimerList.mpHead != 0)
            Snd::gVariableTimerList.mpHead->mpPrev = (SndStreamFader_t *)client;
        Snd::gVariableTimerList.mpHead = (SndStreamFader_t *)client;
    }
    ICInvalidateRange(bank, bank->mSize);
    DCFlushRange(bank, bank->mSize);
    SNDSYS_leavecritical();
}
}
