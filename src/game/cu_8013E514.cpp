#include "game/Camera_8013F738.h"
#include "game/Interp_8013CC14.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"

struct Entry_8013F374 {
    int mType;
    void *mpData;
};

/* The two record kinds have distinct payloads; their common stride is 0x130. */
struct EaseVector_8013C9A4 {
    Vector_80039F5C mBase;
    Interp_8013CC14 mX;
    Interp_8013CC14 mY;
    Interp_8013CC14 mZ;
    Vector_80039F5C mResult;
    Interp_8013CC14 mScale;
};
struct Payload0_8013EEE4 {
    Interp_8013CC14 mX, mY, mZ;
    Vector_80039F5C mTarget;
    Interp_8013CC14 mFov;
    float mLimit;
    unsigned short mUnknown70, mUnknown72;
    int mUnknown74, mUnknown78;
    unsigned int mFlags;
    void (*mCallback)(Entry_8013F374 *);
    char mUnknown84[0xA4];
};
struct Payload1_8013F090 {
    EaseVector_8013C9A4 mPosition, mTarget;
    Interp_8013CC14 mFov;
    float mLimit;
    int mUnknown10C;
    int mRef;
    unsigned short mUnknown114, mUnknown116;
    int mUnknown118, mUnknown11C;
    unsigned int mFlags;
    void (*mCallback)(Entry_8013F374 *);
};
struct Record_8013E944 {
    int mType;
    union { Payload0_8013EEE4 m0; Payload1_8013F090 m1; } mData;
    int mDuration;
};
struct State_8013E574 {
    Record_8013E944 *mpCurrent;
    Record_8013E944 mRecords[12];
    int mRead, mWrite, mFrame;
    Entry_8013F374 *mpList;
    Vector_80039F5C mTarget;
};
/* Mode-specific payload at +F8; the common leading camera block is shared. */
struct ScriptCamera_8013E514 {
    CameraHeader_8013F628 mHeader;
    char mUnknown28[0xB4];
    void (*mCallback)(Camera_8013F738 *, int);
    char mUnknownE0[0x18];
    State_8013E574 mState;
};
struct Desc0_8013EEE4 {
    Vector_80039F5C mPosition, mEndPosition, mTarget;
    float mFov, mEndFov, mLimit, mRate, mDuration;
    int mModeX, mModeY, mModeZ, mModeFov;
    unsigned short mUnknown48, mUnknown4A;
    int mUnknown4C, mUnknown50;
    unsigned int mFlags;
    void (*mCallback)(Entry_8013F374 *);
};
struct Desc1_8013F090 {
    Vector_80039F5C mPosition, mStartAngles, mEndAngles;
    float mStartScale, mEndScale;
    Vector_80039F5C mTarget, mTargetStartAngles, mTargetEndAngles;
    float mTargetStartScale, mTargetEndScale;
    int mUnknown58, mRef;
    float mFov, mEndFov, mLimit, mRate, mDuration;
    int mModePosition, mModeTarget, mModeFov;
    unsigned short mUnknown80, mUnknown82;
    int mUnknown84, mUnknown88;
    unsigned int mFlags;
    void (*mCallback)(Entry_8013F374 *);
};

extern "C" {
extern int lbl_803EB1D0;
unsigned char lbl_803EB1D4 = 0;
ScriptCamera_8013E514 *lbl_803EB1D8 = 0;
State_8013E574 *lbl_803EB1DC = 0;
unsigned char lbl_803EB1E0 = 0;
int fn_80028310(void);
void fn_800A3B5C(void);
int fn_800AD9B4(void);
void fn_8013C9A4(EaseVector_8013C9A4 *, Vector_80039F5C *, Vector_80039F5C *, Vector_80039F5C *, int, float, float, float);
void fn_8013CAA4(EaseVector_8013C9A4 *, int);
void fn_8013CBC4(EaseVector_8013C9A4 *);
void fn_8013CC14(Interp_8013CC14 *, float);
void fn_8013CC40(Interp_8013CC14 *, int, float, float);
void fn_8013F97C(int);
Camera_8013F738 *fn_8013FA04(int);
void fn_8013FBB4(int, int);
void fn_80142B00(void);
Point_8017886C fn_80177FE0(void);
int fn_801784C4(void);
void fn_8017CFB0(unsigned short, unsigned short, int, int);
void fn_8017CFB4(int);
void fn_80187DD0(unsigned short);
void fn_80195EFC(int, int, int, int);
int fn_8019623C(int);
void fn_801C3990(void *, float, float);
int fn_801CFE40(float, float);
void fn_80227490(void *, void *, int, int, int);
void fn_8013EDE4(Camera_8013F738 *, int);
void fn_8013E960(int, int);
void fn_8013E9F0(int, int);
void fn_8013EA8C(State_8013E574 *);
void fn_8013EEE0(ScriptCamera_8013E514 *);
void fn_8013F298(void);
void fn_8013F300(void);
void fn_8013F3FC(void);
}

extern "C" void fn_8013E514(ScriptCamera_8013E514 *p)
{
    lbl_803EB1DC = &p->mState;
    lbl_803EB1D4 = 0;
    lbl_803EB1D8 = p;
    p->mCallback = fn_8013EDE4;
}
extern "C" void fn_8013E538(void)
{
    if (fn_80028310() == 0) fn_8013F300();
    lbl_803EB1D8 = 0;
    lbl_803EB1E0 = 0;
    lbl_803EB1DC = 0;
}
extern "C" State_8013E574 *fn_8013E574(void)
{
    fn_8013FBB4(3, 17);
    fn_8013F97C(3);
    State_8013E574 *p = lbl_803EB1DC;
    p->mFrame = 0; p->mRead = 0; p->mpCurrent = 0; p->mWrite = 0;
    lbl_803EB1E0 = 1;
    return p;
}
extern "C" void fn_8013E5C8(ScriptCamera_8013E514 *p)
{
    State_8013E574 *s = &p->mState;
    Payload1_8013F090 *b = &s->mpCurrent->mData.m1;
    EaseVector_8013C9A4 *target = &b->mTarget;
    Interp_8013CC14 *fov = &b->mFov;
    int done = (float)s->mFrame >= b->mLimit;
    if (b->mRef) {
        Object_80039F5C *o = fn_8009BCE8(&b->mRef);
        target->mBase.mX = o->mpUnknown4->mUnknown4.mX;
        target->mBase.mY = o->mpUnknown4->mUnknown4.mY;
        if (!(b->mFlags & 0x10)) {
            b->mPosition.mBase.mX = o->mpUnknown4->mUnknown4.mX;
            b->mPosition.mBase.mY = o->mpUnknown4->mUnknown4.mY;
        }
    }
    fn_8013CAA4(&b->mPosition, done);
    fn_8013CAA4(target, done);
    fov->mUpdate(fov, done);
    p->mHeader.mUnknown04[0] = b->mPosition.mResult.mX;
    p->mHeader.mUnknown04[1] = b->mPosition.mResult.mY;
    p->mHeader.mUnknown04[2] = b->mPosition.mResult.mZ;
    Vector_80039F5C v;
    fn_802276B4(&v, &target->mResult, p->mHeader.mUnknown04);
    s->mTarget.mX = target->mResult.mX;
    s->mTarget.mY = target->mResult.mY;
    s->mTarget.mZ = target->mResult.mZ;
    int yaw = 0x400000 - fn_801CFE40(v.mY, v.mX);
    p->mHeader.mUnknown1C = yaw;
    fn_80227490(&v, &v, yaw, 0, 0);
    p->mHeader.mUnknown14 = -(fn_801CFE40(v.mZ, v.mY) + 0x400000);
    fn_801C3990(p, fov->mValue, p->mHeader.mUnknown24);
    fn_802270D4(&v);
}
extern "C" void fn_8013E75C(ScriptCamera_8013E514 *p)
{
    Payload1_8013F090 *b = &p->mState.mpCurrent->mData.m1;
    if (b->mRef) {
        Object_80039F5C *o = fn_8009BCE8(&b->mRef);
        o->mpUnknown4->mUnknown20 &= ~0x400;
        fn_800A3B5C();
        if (b->mFlags & 0x20) {
            fn_8013E960(o->mIdBytes[2], 1);
            fn_8013E9F0(o->mIdBytes[2], 1);
        }
    }
}
extern "C" void fn_8013E7D8(ScriptCamera_8013E514 *p)
{
    State_8013E574 *s = &p->mState;
    Payload0_8013EEE4 *b = &s->mpCurrent->mData.m0;
    Vector_80039F5C *target = &b->mTarget;
    Interp_8013CC14 *fov = &b->mFov;
    int done = (float)s->mFrame >= b->mLimit;
    b->mX.mUpdate(&b->mX, done); b->mY.mUpdate(&b->mY, done);
    b->mZ.mUpdate(&b->mZ, done); fov->mUpdate(fov, done);
    p->mHeader.mUnknown04[0] = b->mX.mValue;
    p->mHeader.mUnknown04[1] = b->mY.mValue;
    p->mHeader.mUnknown04[2] = b->mZ.mValue;
    Vector_80039F5C v;
    fn_802276B4(&v, target, p->mHeader.mUnknown04);
    s->mTarget.mX = target->mX; s->mTarget.mY = target->mY; s->mTarget.mZ = target->mZ;
    int yaw = 0x400000 - fn_801CFE40(v.mY, v.mX);
    p->mHeader.mUnknown1C = yaw;
    fn_80227490(&v, &v, yaw, 0, 0);
    p->mHeader.mUnknown14 = -(fn_801CFE40(v.mZ, v.mY) + 0x400000);
    fn_802270D4(&v);
    fn_801C3990(p, fov->mValue, p->mHeader.mUnknown24);
}
extern "C" void fn_8013E940(ScriptCamera_8013E514 *) {}
extern "C" Record_8013E944 *fn_8013E944(State_8013E574 *p)
{
    return &p->mRecords[p->mWrite++];
}
extern "C" void fn_8013E960(int team, int flag)
{
    int count = fn_80178D18((unsigned char)team);
    for (int i = 0; i < count; ++i) {
        Object_80039F5C *p = fn_80039F5C((unsigned char)team, (unsigned short)i);
        if (p) {
            Block_80170E64 *b = p->mpUnknown4;
            if (flag) b->mUnknown20 |= 1;
            else b->mUnknown20 &= ~1;
        }
    }
}
extern "C" void fn_8013E9F0(int team, int flag)
{
    if (fn_800AD9B4() == 1) {
        int count = fn_80178D18((unsigned char)team);
        for (int i = 0; i < count; ++i) {
            Object_80039F5C *p = fn_80039F5C((unsigned char)team, (unsigned short)i);
            if (flag) p->mFlags &= ~0x10;
            else p->mFlags |= 0x10;
        }
    }
}
extern "C" void fn_8013EA8C(State_8013E574 *s)
{
    if (s->mRead < s->mWrite) {
        Record_8013E944 *r = &s->mRecords[s->mRead++];
        s->mpCurrent = r; s->mFrame = 0;
        switch (r->mType) {
        case 1: {
            Payload1_8013F090 *b = &r->mData.m1;
            if (b->mCallback) { Entry_8013F374 entry = {1, b}; b->mCallback(&entry); }
            if (b->mRef) {
                Object_80039F5C *p = fn_8009BCE8(&b->mRef);
                if (p && p->mIdBytes[3] == 1) {
                    fn_80187DD0(p->mUnknown2908);
                    if (b->mFlags & 0x20) { fn_8013E960(p->mIdBytes[2], 0); fn_8013E9F0(p->mIdBytes[2], 0); }
                    p->mpUnknown4->mUnknown20 |= 1;
                }
            }
            if (b->mUnknown118) { fn_8017CFB4(7); fn_8017CFB0(b->mUnknown114, b->mUnknown116, b->mUnknown118, 0); }
            if ((b->mFlags & 8) && b->mRef) {
                Object_80039F5C *p = fn_8009BCE8(&b->mRef);
                float angle = 360.0f - (float)p->mMotion.mFacing * 0.000021457672119140625f;
                while (angle > 360.0f) angle -= 360.0f;
                b->mPosition.mZ.mStart += angle;
                b->mPosition.mZ.mTarget += angle;
                while (b->mPosition.mZ.mStart > 360.0f) b->mPosition.mZ.mStart -= 360.0f;
                while (b->mPosition.mZ.mTarget > 360.0f) b->mPosition.mZ.mTarget -= 360.0f;
            }
            if (fn_801784C4()) { fn_8013CBC4(&b->mPosition); fn_8013CBC4(&b->mTarget); }
            if ((b->mFlags & 2) && fn_8019623C(0x23000)) fn_80195EFC(1, lbl_803EB1D0, 0x808080, 0);
            if ((b->mFlags & 0x100) && fn_8019623C(0x23000)) fn_80195EFC(1, 12, 0x808080, 0);
            break;
        }
        case 0: {
            Payload0_8013EEE4 *b = &r->mData.m0;
            if (b->mCallback) { Entry_8013F374 entry = {0, b}; b->mCallback(&entry); }
            if (fn_801784C4()) {
                b->mTarget.mX = -b->mTarget.mX; b->mTarget.mY = -b->mTarget.mY;
                b->mY.mStart = -b->mY.mStart; b->mY.mValue = -b->mY.mValue; b->mY.mTarget = -b->mY.mTarget;
            }
            if (b->mUnknown74) fn_8017CFB0(b->mUnknown70, b->mUnknown72, b->mUnknown74, b->mUnknown78);
            if ((b->mFlags & 2) && fn_8019623C(0x23000)) fn_80195EFC(1, lbl_803EB1D0, 0x808080, 0);
            break;
        }
        }
    } else fn_8013F3FC();
}
extern "C" void fn_8013EDE4(Camera_8013F738 *camera, int msg)
{
    ScriptCamera_8013E514 *p = (ScriptCamera_8013E514 *)camera;
    State_8013E574 *s = &p->mState;
    switch (msg) {
    case 0: case 2: break;
    case 1: fn_8013EEE0(p); break;
    case 3:
        if (lbl_803EB1D4) fn_8013F298();
        else if (lbl_803EB1E0 && s->mpCurrent) {
            Record_8013E944 *r = s->mpCurrent;
            if (r->mDuration == -1 || s->mFrame <= r->mDuration) {
                switch (r->mType) { case 0: fn_8013E7D8(p); break; case 1: fn_8013E5C8(p); break; }
            } else {
                switch (r->mType) { case 0: fn_8013E940(p); break; case 1: fn_8013E75C(p); break; }
                fn_8013EA8C(s);
            }
            ++s->mFrame;
        }
        break;
    }
}
extern "C" void fn_8013EEE0(ScriptCamera_8013E514 *) {}
extern "C" void fn_8013EEE4(State_8013E574 *s, Desc0_8013EEE4 *d)
{
    Record_8013E944 *r = fn_8013E944(s); r->mType = 0; r->mDuration = (int)d->mDuration;
    Payload0_8013EEE4 *b = &r->mData.m0;
    Vector_80039F5C pos, end;
    pos.mX = d->mPosition.mX; pos.mY = d->mPosition.mY; pos.mZ = d->mPosition.mZ;
    end.mX = d->mEndPosition.mX; end.mY = d->mEndPosition.mY; end.mZ = d->mEndPosition.mZ;
    if (d->mFlags & 1) { Point_8017886C point = fn_80177FE0(); fn_80227638(&pos, &pos, &point); fn_80227638(&end, &end, &point); }
    b->mCallback = d->mCallback;
    b->mTarget.mX = d->mTarget.mX; b->mTarget.mY = d->mTarget.mY; b->mTarget.mZ = d->mTarget.mZ;
    b->mUnknown70 = d->mUnknown48; b->mUnknown72 = d->mUnknown4A;
    b->mUnknown74 = d->mUnknown4C; b->mUnknown78 = d->mUnknown50;
    b->mLimit = d->mLimit; b->mFlags = d->mFlags;
    fn_8013CC14(&b->mX, pos.mX); fn_8013CC14(&b->mY, pos.mY); fn_8013CC14(&b->mZ, pos.mZ);
    fn_8013CC40(&b->mX, d->mModeX, end.mX, d->mRate);
    fn_8013CC40(&b->mY, d->mModeY, end.mY, d->mRate);
    fn_8013CC40(&b->mZ, d->mModeZ, end.mZ, d->mRate);
    fn_8013CC14(&b->mFov, d->mFov); fn_8013CC40(&b->mFov, d->mModeFov, d->mEndFov, d->mRate);
}
extern "C" void fn_8013F090(State_8013E574 *s, Desc1_8013F090 *d)
{
    Record_8013E944 *r = fn_8013E944(s); r->mType = 1; r->mDuration = (int)d->mDuration;
    Payload1_8013F090 *b = &r->mData.m1;
    Vector_80039F5C a, z, pos, target;
    a.mX = d->mStartAngles.mX; a.mY = d->mStartAngles.mY; a.mZ = d->mStartAngles.mZ;
    z.mX = d->mEndAngles.mX; z.mY = d->mEndAngles.mY; z.mZ = d->mEndAngles.mZ;
    pos.mX = d->mPosition.mX; pos.mY = d->mPosition.mY; pos.mZ = d->mPosition.mZ;
    target.mX = d->mTarget.mX; target.mY = d->mTarget.mY; target.mZ = d->mTarget.mZ;
    if (d->mFlags & 1) { Point_8017886C point = fn_80177FE0(); fn_80227638(&pos, &pos, &point); fn_80227638(&target, &target, &point); }
    if (d->mRef) {
        Object_80039F5C *p = fn_8009BCE8(&d->mRef);
        if (p->mIdBytes[3] == 1) target.mZ += p->mUnknown2900 * 0.027777778f - 2.03f;
        p->mpUnknown4->mUnknown20 |= 0x410;
    }
    fn_8013C9A4(&b->mPosition, &pos, &a, &z, d->mModePosition, d->mStartScale, d->mEndScale, d->mRate);
    fn_8013C9A4(&b->mTarget, &target, &d->mTargetStartAngles, &d->mTargetEndAngles, d->mModeTarget, d->mTargetStartScale, d->mTargetEndScale, d->mRate);
    b->mUnknown10C = d->mUnknown58; b->mRef = d->mRef; b->mLimit = d->mLimit;
    b->mFlags = d->mFlags; b->mCallback = d->mCallback;
    b->mUnknown114 = d->mUnknown80; b->mUnknown116 = d->mUnknown82;
    b->mUnknown118 = d->mUnknown84; b->mUnknown11C = d->mUnknown88;
    fn_8013CC14(&b->mFov, d->mFov); fn_8013CC40(&b->mFov, d->mModeFov, d->mEndFov, d->mRate);
}
extern "C" void fn_8013F298(void)
{
    if (lbl_803EB1E0) {
        fn_8013F300(); lbl_803EB1E0 = 0; lbl_803EB1D8 = 0; lbl_803EB1DC = 0;
        fn_8013F97C(0); fn_8013FA04(5)->mUnknown94 |= 4; fn_80142B00();
    }
    lbl_803EB1D4 = 0;
}
extern "C" void fn_8013F300(void)
{
    if (lbl_803EB1D8 && lbl_803EB1DC->mpCurrent) {
        switch (lbl_803EB1DC->mpCurrent->mType) { case 0: fn_8013E940(lbl_803EB1D8); break; case 1: fn_8013E75C(lbl_803EB1D8); break; }
    }
    fn_8013E960(0, 1); fn_8013E960(1, 1);
}
extern "C" void fn_8013F374(Entry_8013F374 *list)
{
    fn_8013F300(); State_8013E574 *s = fn_8013E574(); s->mpList = list;
    for (Entry_8013F374 *e = list; e->mpData; ++e) {
        switch (e->mType) { case 0: fn_8013EEE4(s, (Desc0_8013EEE4 *)e->mpData); break; case 1: fn_8013F090(s, (Desc1_8013F090 *)e->mpData); break; }
    }
    fn_8013EA8C(s);
}
extern "C" void fn_8013F3FC(void) { lbl_803EB1D4 = 1; }
extern "C" Object_80039F5C *fn_8013F408(void)
{
    Object_80039F5C *p = 0; State_8013E574 *s = lbl_803EB1DC;
    if (lbl_803EB1E0) {
        switch (s->mpCurrent->mType) {
        case 0: break;
        case 1: p = fn_8009BCE8(&s->mpCurrent->mData.m1.mRef); break;
        }
    }
    return p;
}
