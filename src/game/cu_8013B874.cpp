#include "game/cu_80136B1C.h"

/* Per-state handlers, indexed by State_80137ABC::mState. */
struct StateFuncs_802DBC28 {
    void (*mUnknown0)(Object_80137ABC *p, float dt);
    void (*mUnknown4)(Object_80137ABC *p, float dt);
    void (*mUnknown8)(Object_80137ABC *p, float dt);
    void (*mEnter)(Object_80137ABC *p);
    void (*mExit)(Object_80137ABC *p);
    int (*mUnknown14)(Object_80137ABC *p, void *pData, int value);
    void (*mUnknown18)(Object_80137ABC *p, float dt);
};

extern "C" {
void fn_8013A3BC(Object_80137ABC *p);
void fn_8013A494(Object_80137ABC *p, float dt);
void fn_8013A64C(Object_80137ABC *p, float dt);
void fn_8013A844(Object_80137ABC *p, float dt);
void fn_8013AF88(Object_80137ABC *p);
void fn_8013AFE8(Object_80137ABC *p);
void fn_8013B024(Object_80137ABC *p);
void fn_8013B068(Object_80137ABC *p);
void fn_8013B0B4(Object_80137ABC *p, float dt);
void fn_8013B198(Object_80137ABC *p, float dt);
void fn_8013B1E4(Object_80137ABC *p, float dt);
void fn_8013B230(Object_80137ABC *p);
void fn_8013B250(Object_80137ABC *p);
void fn_8013B2A0(Object_80137ABC *p, float dt);
void fn_8013B330(Object_80137ABC *p, float dt);
void fn_8013B350(Object_80137ABC *p, float dt);
int fn_8013B3EC(Object_80137ABC *p, void *pData, int value);
int fn_8013B52C(Object_80137ABC *p, void *pData, int value);
int fn_8013B5EC(Object_80137ABC *p, void *pData, int value);
int fn_8013B6A0(Object_80137ABC *p, void *pData, int value);
void fn_8013B730(Object_80137ABC *p, float dt);
void fn_8013B734(Object_80137ABC *p, float dt);
int fn_8013B86C(Object_80137ABC *p, void *pData, int value);
int fn_8013BAE0(Object_80137ABC *p, void *pData, int value);
}

static StateFuncs_802DBC28 lbl_802DBC28[9] = {
    { 0, fn_8013A494, 0, 0, 0, fn_8013BAE0, fn_8013A844 },
    { 0, 0, fn_8013B0B4, fn_8013AF88, fn_8013B250, fn_8013B3EC, fn_8013A844 },
    { 0, fn_8013B350, 0, 0, 0, fn_8013B6A0, fn_8013A844 },
    { 0, fn_8013B350, 0, 0, 0, fn_8013B6A0, fn_8013A844 },
    { 0, fn_8013B2A0, fn_8013B1E4, fn_8013AFE8, fn_8013B024, fn_8013B5EC, fn_8013A844 },
    { 0, fn_8013B330, 0, fn_8013B068, 0, fn_8013B52C, fn_8013A844 },
    { 0, fn_8013A494, fn_8013B198, fn_8013B230, 0, fn_8013B3EC, 0 },
    { 0, fn_8013A494, 0, 0, 0, fn_8013B6A0, fn_8013A844 },
    { 0, 0, fn_8013B730, 0, 0, fn_8013B86C, fn_8013B734 },
};

extern "C" {

void fn_8013B874(Object_80137ABC *p, float dt)
{
    if (lbl_802DBC28[p->mState.mState].mUnknown18) {
        lbl_802DBC28[p->mState.mState].mUnknown18(p, dt);
    }
}

void fn_8013B8C0(Object_80137ABC *p, float dt)
{
    if (lbl_802DBC28[p->mState.mState].mUnknown0) {
        lbl_802DBC28[p->mState.mState].mUnknown0(p, dt);
    }
}

void fn_8013B900(Object_80137ABC *p, float dt)
{
    if (lbl_802DBC28[p->mState.mState].mUnknown4) {
        lbl_802DBC28[p->mState.mState].mUnknown4(p, dt);
        fn_8013A3BC(p);
    }
    p->mState.mFlags |= 0x10;
}

void fn_8013B96C(Object_80137ABC *p, float dt)
{
    if (lbl_802DBC28[p->mState.mState].mUnknown8) {
        lbl_802DBC28[p->mState.mState].mUnknown8(p, dt);
    } else {
        fn_8013A64C(p, dt);
    }
}

void fn_8013B9C0(Object_80137ABC *p, int state, int arg)
{
    int prevState = p->mState.mState;
    int prevArg = p->mState.mStateArg;

    p->mState.mState = state;
    p->mState.mPrevStateArg = prevArg;
    p->mState.mStateArg = arg;
    p->mState.mPrevState = prevState;
    if (lbl_802DBC28[prevState].mExit) {
        lbl_802DBC28[prevState].mExit(p);
    }
    if (lbl_802DBC28[p->mState.mState].mEnter) {
        lbl_802DBC28[p->mState.mState].mEnter(p);
    }
}

int fn_8013BA58(Object_80137ABC *p, int *pArg)
{
    if (pArg) {
        *pArg = p->mState.mStateArg;
    }
    return p->mState.mState;
}

int fn_8013BA70(Object_80137ABC *p, int *pArg)
{
    if (pArg) {
        *pArg = p->mState.mPrevStateArg;
    }
    return p->mState.mPrevState;
}

int fn_8013BA88(Object_80137ABC *p, void *pData, int value)
{
    int result = 0;

    if (lbl_802DBC28[p->mState.mState].mUnknown14) {
        result = lbl_802DBC28[p->mState.mState].mUnknown14(p, pData, value);
    }
    return result;
}

int fn_8013BAE0(Object_80137ABC *p, void *pData, int value)
{
    return p == fn_801374BC();
}
}
