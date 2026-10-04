struct Object_8013B874;

/* Per-state handlers, indexed by Object_8013B874::mState. */
struct StateFuncs_802DBC28 {
    void (*mUnknown0)(Object_8013B874 *p, float dt);
    void (*mUnknown4)(Object_8013B874 *p, float dt);
    void (*mUnknown8)(Object_8013B874 *p, float dt);
    void (*mEnter)(Object_8013B874 *p);
    void (*mExit)(Object_8013B874 *p);
    int (*mUnknown14)(Object_8013B874 *p, void *pData, int value);
    void (*mUnknown18)(Object_8013B874 *p, float dt);
};

struct Object_8013B874 {
    char mUnknown0[8];
    unsigned int mFlags;
    char mUnknownC[152];
    int mState;
    int mStateArg;
    int mPrevState;
    int mPrevStateArg;
};

extern "C" {
void fn_8013A3BC(Object_8013B874 *p);
void fn_8013A494(Object_8013B874 *p, float dt);
void fn_8013A64C(Object_8013B874 *p, float dt);
void fn_8013A844(Object_8013B874 *p, float dt);
void fn_8013AF88(Object_8013B874 *p);
void fn_8013AFE8(Object_8013B874 *p);
void fn_8013B024(Object_8013B874 *p);
void fn_8013B068(Object_8013B874 *p);
void fn_8013B0B4(Object_8013B874 *p, float dt);
void fn_8013B198(Object_8013B874 *p, float dt);
void fn_8013B1E4(Object_8013B874 *p, float dt);
void fn_8013B230(Object_8013B874 *p);
void fn_8013B250(Object_8013B874 *p);
void fn_8013B2A0(Object_8013B874 *p, float dt);
void fn_8013B330(Object_8013B874 *p, float dt);
void fn_8013B350(Object_8013B874 *p, float dt);
int fn_8013B3EC(Object_8013B874 *p, void *pData, int value);
int fn_8013B52C(Object_8013B874 *p, void *pData, int value);
int fn_8013B5EC(Object_8013B874 *p, void *pData, int value);
int fn_8013B6A0(Object_8013B874 *p, void *pData, int value);
void fn_8013B730(Object_8013B874 *p, float dt);
void fn_8013B734(Object_8013B874 *p, float dt);
int fn_8013B86C(Object_8013B874 *p, void *pData, int value);
int fn_8013BAE0(Object_8013B874 *p, void *pData, int value);
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

void fn_8013B874(Object_8013B874 *p, float dt)
{
    if (lbl_802DBC28[p->mState].mUnknown18) {
        lbl_802DBC28[p->mState].mUnknown18(p, dt);
    }
}

void fn_8013B8C0(Object_8013B874 *p, float dt)
{
    if (lbl_802DBC28[p->mState].mUnknown0) {
        lbl_802DBC28[p->mState].mUnknown0(p, dt);
    }
}

void fn_8013B900(Object_8013B874 *p, float dt)
{
    if (lbl_802DBC28[p->mState].mUnknown4) {
        lbl_802DBC28[p->mState].mUnknown4(p, dt);
        fn_8013A3BC(p);
    }
    p->mFlags |= 0x10;
}

void fn_8013B96C(Object_8013B874 *p, float dt)
{
    if (lbl_802DBC28[p->mState].mUnknown8) {
        lbl_802DBC28[p->mState].mUnknown8(p, dt);
    } else {
        fn_8013A64C(p, dt);
    }
}

void fn_8013B9C0(Object_8013B874 *p, int state, int arg)
{
    int prevState = p->mState;
    int prevArg = p->mStateArg;

    p->mState = state;
    p->mPrevStateArg = prevArg;
    p->mStateArg = arg;
    p->mPrevState = prevState;
    if (lbl_802DBC28[prevState].mExit) {
        lbl_802DBC28[prevState].mExit(p);
    }
    if (lbl_802DBC28[p->mState].mEnter) {
        lbl_802DBC28[p->mState].mEnter(p);
    }
}

int fn_8013BA58(Object_8013B874 *p, int *pArg)
{
    if (pArg) {
        *pArg = p->mStateArg;
    }
    return p->mState;
}

int fn_8013BA70(Object_8013B874 *p, int *pArg)
{
    if (pArg) {
        *pArg = p->mPrevStateArg;
    }
    return p->mPrevState;
}

int fn_8013BA88(Object_8013B874 *p, void *pData, int value)
{
    int result = 0;

    if (lbl_802DBC28[p->mState].mUnknown14) {
        result = lbl_802DBC28[p->mState].mUnknown14(p, pData, value);
    }
    return result;
}
}
