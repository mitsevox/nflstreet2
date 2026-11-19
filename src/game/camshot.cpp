/* Scripted camera shots. A camera mode (gCamShotMode) that plays a list of
   shots, used by the coin toss: each shot either moves the camera from a
   start to an end position while it aims at a fixed point, or eases the
   camera around a target that can follow a player. Each frame the current
   shot is updated until its duration ends, then the next one starts; when
   the list is done the game returns to the normal camera. */
#include "game/fn_80177FE0.h"
#include "game/ScreenTransition.h"
#include "game/GameCamera.h"
#include "game/CamInterp.h"
#include "game/CamEaseVec.h"
#include "game/cammain.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"

// FAKEMATCH: release form of an assert macro (empty loop, condition discarded).
#define CAMSHOT_ASSERT(e) do { } while (0)

struct CamShotEntry_t {
    int mType;
    void *mpData;
};

/* The two record kinds have distinct payloads; their common stride is 0x130. */
struct CamShotFixed_t {
    CamInterp_t mX, mY, mZ;
    Vector_80039F5C mTarget;
    CamInterp_t mFov;
    float mLimit;
    unsigned short mUnknown70, mUnknown72;
    int mUnknown74, mUnknown78;
    unsigned int mFlags;
    void (*mCallback)(CamShotEntry_t *);
    char mUnknown84[0xA4];
};
struct CamShotFollow_t {
    CamEaseVec_t mPosition, mTarget;
    CamInterp_t mFov;
    float mLimit;
    int mUnknown10C;
    int mRef;
    unsigned short mUnknown114, mUnknown116;
    int mUnknown118, mUnknown11C;
    unsigned int mFlags;
    void (*mCallback)(CamShotEntry_t *);
};
struct CamShotRecord_t {
    int mType;
    union { CamShotFixed_t m0; CamShotFollow_t m1; } mData;
    int mDuration;
};
struct CamShotState_t {
    CamShotRecord_t *mpCurrent;
    CamShotRecord_t mRecords[12];
    int mRead, mWrite, mFrame;
    CamShotEntry_t *mpList;
    Vector_80039F5C mTarget;
};
/* Mode-specific payload at +F8; the common leading camera block is shared. */
struct CamShotCamera_t {
    CamHdr_t mHeader;
    char mUnknown28[0xB4];
    void (*mCallback)(GameCamera_t *, int);
    char mUnknownE0[0x18];
    CamShotState_t mState;
};
struct CamShotFixedDesc_t {
    Vector_80039F5C mPosition, mEndPosition, mTarget;
    float mFov, mEndFov, mLimit, mRate, mDuration;
    CamInterpFunc_t mModeX, mModeY, mModeZ, mModeFov;
    unsigned short mUnknown48, mUnknown4A;
    int mUnknown4C, mUnknown50;
    unsigned int mFlags;
    void (*mCallback)(CamShotEntry_t *);
};
struct CamShotFollowDesc_t {
    Vector_80039F5C mPosition, mStartAngles, mEndAngles;
    float mStartScale, mEndScale;
    Vector_80039F5C mTarget, mTargetStartAngles, mTargetEndAngles;
    float mTargetStartScale, mTargetEndScale;
    int mUnknown58, mRef;
    float mFov, mEndFov, mLimit, mRate, mDuration;
    CamInterpFunc_t mModePosition, mModeTarget, mModeFov;
    unsigned short mUnknown80, mUnknown82;
    int mUnknown84, mUnknown88;
    unsigned int mFlags;
    void (*mCallback)(CamShotEntry_t *);
};

struct CamShotModeTable_t {
    void (*mpInit)(CamShotCamera_t *p);
    void (*mpUninit)(void);
    int mUnknown08;
};

extern "C" {
static int _CamShot_iFadeTime = 60;
static unsigned char _CamShot_bStopRequest = 0;
static CamShotCamera_t *_CamShot_pCamera = 0;
static CamShotState_t *_CamShot_pState = 0;
static unsigned char _CamShot_bActive = 0;
int InGameIsStopped(void);
void fn_800A3B5C(void);
int fn_800AD9B4(void);
void CamGameSelectCamera(int);
GameCamera_t *CamGameGetCamera(int);
void CamGameChangeType(int, int);
void CamBallRequestRestart(void);
int fn_801784C4(void);
void BannerShow(unsigned short, unsigned short, int, int);
void BannerClear(int);
void GameTextSetLastPlayer(unsigned short);
int ScreenTransCanCapture(int);
void CamSetFieldOfView(void *, float, float);
int fn_801CFE40(float, float);
void fn_80227490(void *, void *, int, int, int);
void CamShotHandleMsg(GameCamera_t *, int);
void CamShotSetTeamBlockFlag(int, int);
void CamShotSetTeamPlayerFlag(int, int);
void CamShotNextRecord(CamShotState_t *);
void CamShotHandleMsg1(CamShotCamera_t *);
void CamShotFinish(void);
void CamShotEndCurrent(void);
void CamShotRequestStop(void);
void CamShotInit(CamShotCamera_t *p);
void CamShotUninit(void);

CamShotModeTable_t gCamShotMode = { CamShotInit, CamShotUninit, 0 };
}

extern "C" void CamShotInit(CamShotCamera_t *p)
{
    _CamShot_pState = &p->mState;
    _CamShot_bStopRequest = 0;
    _CamShot_pCamera = p;
    p->mCallback = CamShotHandleMsg;
}
extern "C" void CamShotUninit(void)
{
    if (InGameIsStopped() == 0) CamShotEndCurrent();
    _CamShot_pCamera = 0;
    _CamShot_bActive = 0;
    // FAKEMATCH: compiled-out assert on the state pointer; the release macro's empty loop orders the stores.
    CAMSHOT_ASSERT(_CamShot_pState != 0);
    _CamShot_pState = 0;
}
extern "C" CamShotState_t *CamShotBegin(void)
{
    CamGameChangeType(3, 17);
    CamGameSelectCamera(3);
    CamShotState_t *p = _CamShot_pState;
    p->mRead = 0;
    p->mpCurrent = 0;
    p->mWrite = 0;
    p->mFrame = 0;
    _CamShot_bActive = 1;
    return p;
}
extern "C" void CamShotUpdateFollow(CamShotCamera_t *p)
{
    CamShotState_t *s = &p->mState;
    CamShotFollow_t *b = &s->mpCurrent->mData.m1;
    CamEaseVec_t *target = &b->mTarget;
    CamInterp_t *fov = &b->mFov;
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
    CamEaseVecUpdate(&b->mPosition, done);
    CamEaseVecUpdate(target, done);
    fov->mUpdate(fov, done);
    p->mHeader.mUnknown04[0] = b->mPosition.mResult.mX;
    p->mHeader.mUnknown04[1] = b->mPosition.mResult.mY;
    p->mHeader.mUnknown04[2] = b->mPosition.mResult.mZ;
    Vector_80039F5C v;
    fn_802276B4(&v, &target->mResult, p->mHeader.mUnknown04);
    s->mTarget.mX = target->mResult.mX;
    s->mTarget.mY = target->mResult.mY;
    s->mTarget.mZ = target->mResult.mZ;
    int yaw = -fn_801CFE40(v.mY, v.mX) + 0x400000;
    p->mHeader.mUnknown14[2] = yaw;
    fn_80227490(&v, &v, yaw, 0, 0);
    p->mHeader.mUnknown14[0] = -(fn_801CFE40(v.mZ, v.mY) + 0x400000);
    CamSetFieldOfView(p, fov->mValue, p->mHeader.mUnknown24);
    fn_802270D4(&v);
}
extern "C" void CamShotEndFollow(CamShotCamera_t *p)
{
    CamShotFollow_t *b = &p->mState.mpCurrent->mData.m1;
    if (b->mRef) {
        Object_80039F5C *o = fn_8009BCE8(&b->mRef);
        o->mpUnknown4->mUnknown20 &= ~0x400;
        fn_800A3B5C();
        if (b->mFlags & 0x20) {
            CamShotSetTeamBlockFlag(o->mIdBytes[2], 1);
            CamShotSetTeamPlayerFlag(o->mIdBytes[2], 1);
        }
    }
}
extern "C" void CamShotUpdateFixed(CamShotCamera_t *p)
{
    CamShotState_t *s = &p->mState;
    CamShotFixed_t *b = &s->mpCurrent->mData.m0;
    Vector_80039F5C *target = &b->mTarget;
    CamInterp_t *fov = &b->mFov;
    int done = (float)s->mFrame >= b->mLimit;
    b->mX.mUpdate(&b->mX, done); b->mY.mUpdate(&b->mY, done);
    b->mZ.mUpdate(&b->mZ, done); fov->mUpdate(fov, done);
    p->mHeader.mUnknown04[0] = b->mX.mValue;
    p->mHeader.mUnknown04[1] = b->mY.mValue;
    p->mHeader.mUnknown04[2] = b->mZ.mValue;
    Vector_80039F5C v;
    fn_802276B4(&v, target, p->mHeader.mUnknown04);
    s->mTarget.mX = target->mX; s->mTarget.mY = target->mY; s->mTarget.mZ = target->mZ;
    int yaw = -fn_801CFE40(v.mY, v.mX) + 0x400000;
    p->mHeader.mUnknown14[2] = yaw;
    fn_80227490(&v, &v, yaw, 0, 0);
    p->mHeader.mUnknown14[0] = -(fn_801CFE40(v.mZ, v.mY) + 0x400000);
    fn_802270D4(&v);
    CamSetFieldOfView(p, fov->mValue, p->mHeader.mUnknown24);
}
extern "C" void CamShotEndFixed(CamShotCamera_t *) {}
extern "C" CamShotRecord_t *CamShotAllocRecord(CamShotState_t *p)
{
    return &p->mRecords[p->mWrite++];
}
extern "C" void CamShotSetTeamBlockFlag(int team, int flag)
{
    int count = fn_80178D18((unsigned char)team);
    for (int i = 0; i < count; ++i) {
        Object_80039F5C *p = PlyrGet((unsigned char)team, (unsigned short)i);
        if (p) {
            Block_80170E64 *b = p->mpUnknown4;
            if (flag) b->mUnknown20 |= 1;
            else b->mUnknown20 &= ~1;
        }
    }
}
extern "C" void CamShotSetTeamPlayerFlag(int team, int flag)
{
    if (fn_800AD9B4() == 1) {
        int count = fn_80178D18((unsigned char)team);
        for (int i = 0; i < count; ++i) {
            Object_80039F5C *p = PlyrGet((unsigned char)team, (unsigned short)i);
            if (flag) p->mFlags &= ~0x10;
            else p->mFlags |= 0x10;
        }
    }
}
extern "C" void CamShotNextRecord(CamShotState_t *s)
{
    if (s->mRead < s->mWrite) {
        CamShotRecord_t *r = &s->mRecords[s->mRead++];
        CamShotEntry_t entry;
        s->mpCurrent = r; s->mFrame = 0;
        switch (r->mType) {
        case 1: {
            CamShotFollow_t *b = &r->mData.m1;
            if (b->mCallback) { entry.mType = 1; entry.mpData = b; b->mCallback(&entry); }
            if (b->mRef) {
                Object_80039F5C *p = fn_8009BCE8(&b->mRef);
                if (p && p->mIdBytes[3] == 1) {
                    GameTextSetLastPlayer(p->mUnknown2908);
                    if (b->mFlags & 0x20) { CamShotSetTeamBlockFlag(p->mIdBytes[2], 0); CamShotSetTeamPlayerFlag(p->mIdBytes[2], 0); }
                    p->mpUnknown4->mUnknown20 |= 1;
                }
            }
            if (b->mUnknown118) { BannerClear(7); BannerShow(b->mUnknown114, b->mUnknown116, b->mUnknown118, 0); }
            if ((b->mFlags & 8) && b->mRef) {
                Object_80039F5C *p = fn_8009BCE8(&b->mRef);
                // FAKEMATCH: the angle is converted, then flipped, in two assignments.
                float angle = (float)p->mMotion.mFacing * (360.0f / 16777216.0f);
                angle = 360.0f - angle;
                while (angle > 360.0f) angle -= 360.0f;
                b->mPosition.mZ.mStart += angle;
                b->mPosition.mZ.mTarget += angle;
                while (b->mPosition.mZ.mStart > 360.0f) b->mPosition.mZ.mStart -= 360.0f;
                while (b->mPosition.mZ.mTarget > 360.0f) b->mPosition.mZ.mTarget -= 360.0f;
            }
            if (fn_801784C4()) { CamEaseVecFlip(&b->mPosition); CamEaseVecFlip(&b->mTarget); }
            if ((b->mFlags & 2) && ScreenTransCanCapture(0x23000)) ScreenTransStart(1, _CamShot_iFadeTime, 0x808080, 0);
            if ((b->mFlags & 0x100) && ScreenTransCanCapture(0x23000)) ScreenTransStart(1, 12, 0x808080, 0);
            break;
        }
        case 0: {
            CamShotFixed_t *b = &r->mData.m0;
            if (b->mCallback) { entry.mType = 0; entry.mpData = b; b->mCallback(&entry); }
            if (fn_801784C4()) {
                b->mTarget.mX = -b->mTarget.mX; b->mTarget.mY = -b->mTarget.mY;
                b->mY.mStart = -b->mY.mStart; b->mY.mValue = -b->mY.mValue; b->mY.mTarget = -b->mY.mTarget;
            }
            if (b->mUnknown74) BannerShow(b->mUnknown70, b->mUnknown72, b->mUnknown74, b->mUnknown78);
            if ((b->mFlags & 2) && ScreenTransCanCapture(0x23000)) ScreenTransStart(1, _CamShot_iFadeTime, 0x808080, 0);
            break;
        }
        }
    } else CamShotRequestStop();
}
extern "C" void CamShotHandleMsg(GameCamera_t *camera, int msg)
{
    CamShotCamera_t *p = (CamShotCamera_t *)camera;
    CamShotState_t *s = &p->mState;
    switch (msg) {
    case 3:
        if (_CamShot_bStopRequest) CamShotFinish();
        else if (_CamShot_bActive && s->mpCurrent) {
            CamShotRecord_t *r = s->mpCurrent;
            if (r->mDuration == -1 || s->mFrame <= r->mDuration) {
                switch (r->mType) { case 0: CamShotUpdateFixed(p); break; case 1: CamShotUpdateFollow(p); break; }
            } else {
                switch (r->mType) { case 0: CamShotEndFixed(p); break; case 1: CamShotEndFollow(p); break; }
                CamShotNextRecord(s);
            }
            ++s->mFrame;
        }
        break;
    case 1: CamShotHandleMsg1(p); break;
    case 0: case 2: case 4: break;
    }
}
extern "C" void CamShotHandleMsg1(CamShotCamera_t *) {}
extern "C" void CamShotAddFixed(CamShotState_t *s, CamShotFixedDesc_t *d)
{
    CamShotRecord_t *r = CamShotAllocRecord(s); r->mType = 0; r->mDuration = (int)d->mDuration;
    CamShotFixed_t *b = &r->mData.m0;
    Vector_80039F5C *pTarget = &b->mTarget;
    Vector_80039F5C pos, end;
    pos.mX = d->mPosition.mX; pos.mY = d->mPosition.mY; pos.mZ = d->mPosition.mZ;
    end.mX = d->mEndPosition.mX; end.mY = d->mEndPosition.mY; end.mZ = d->mEndPosition.mZ;
    if (d->mFlags & 1) { Point_8017886C point; point = fn_80177FE0(); fn_80227638(&pos, &pos, &point); fn_80227638(&end, &end, &point); }
    b->mCallback = d->mCallback;
    pTarget->mX = d->mTarget.mX; pTarget->mY = d->mTarget.mY; pTarget->mZ = d->mTarget.mZ;
    b->mUnknown70 = d->mUnknown48; b->mUnknown72 = d->mUnknown4A;
    b->mUnknown74 = d->mUnknown4C; b->mUnknown78 = d->mUnknown50;
    b->mLimit = d->mLimit; b->mFlags = d->mFlags;
    CamInterpInit(&b->mX, pos.mX); CamInterpInit(&b->mY, pos.mY); CamInterpInit(&b->mZ, pos.mZ);
    CamInterpSetTarget(&b->mX, end.mX, d->mModeX, d->mRate);
    CamInterpSetTarget(&b->mY, end.mY, d->mModeY, d->mRate);
    CamInterpSetTarget(&b->mZ, end.mZ, d->mModeZ, d->mRate);
    CamInterpInit(&b->mFov, d->mFov); CamInterpSetTarget(&b->mFov, d->mEndFov, d->mModeFov, d->mRate);
}
extern "C" void CamShotAddFollow(CamShotState_t *s, CamShotFollowDesc_t *d)
{
    CamShotRecord_t *r = CamShotAllocRecord(s); r->mType = 1; r->mDuration = (int)d->mDuration;
    CamShotFollow_t *b = &r->mData.m1;
    CamEaseVec_t *pTarget = &b->mTarget;
    Vector_80039F5C pos, target, a, z;
    a.mX = d->mStartAngles.mX; a.mY = d->mStartAngles.mY; a.mZ = d->mStartAngles.mZ;
    z.mX = d->mEndAngles.mX; z.mY = d->mEndAngles.mY; z.mZ = d->mEndAngles.mZ;
    pos.mX = d->mPosition.mX; pos.mY = d->mPosition.mY; pos.mZ = d->mPosition.mZ;
    target.mX = d->mTarget.mX; target.mY = d->mTarget.mY; target.mZ = d->mTarget.mZ;
    if (d->mFlags & 1) { Point_8017886C point; point = fn_80177FE0(); fn_80227638(&pos, &pos, &point); fn_80227638(&target, &target, &point); }
    if (d->mRef) {
        Object_80039F5C *p = fn_8009BCE8(&d->mRef);
        if (p->mIdBytes[3] == 1) target.mZ += p->mUnknown2900 * 0.027777778f - 2.03f;
        p->mpUnknown4->mUnknown20 |= 0x410;
    }
    CamEaseVecStart(&b->mPosition, &pos, &a, &z, d->mStartScale, d->mEndScale, d->mModePosition, d->mRate);
    CamEaseVecStart(pTarget, &target, &d->mTargetStartAngles, &d->mTargetEndAngles, d->mTargetStartScale, d->mTargetEndScale, d->mModeTarget, d->mRate);
    b->mUnknown10C = d->mUnknown58; b->mRef = d->mRef; b->mLimit = d->mLimit;
    b->mFlags = d->mFlags; b->mCallback = d->mCallback;
    b->mUnknown114 = d->mUnknown80; b->mUnknown116 = d->mUnknown82;
    b->mUnknown118 = d->mUnknown84; b->mUnknown11C = d->mUnknown88;
    CamInterpInit(&b->mFov, d->mFov); CamInterpSetTarget(&b->mFov, d->mEndFov, d->mModeFov, d->mRate);
}
extern "C" void CamShotFinish(void)
{
    if (_CamShot_bActive) {
        CamShotEndCurrent(); _CamShot_bActive = 0; _CamShot_pState = 0; _CamShot_pCamera = 0;
        CamGameSelectCamera(0); CamGameGetCamera(5)->mUnknown94 |= 4; CamBallRequestRestart();
    }
    _CamShot_bStopRequest = 0;
}
extern "C" void CamShotEndCurrent(void)
{
    if (_CamShot_pCamera && _CamShot_pState->mpCurrent) {
        switch (_CamShot_pState->mpCurrent->mType) { case 0: CamShotEndFixed(_CamShot_pCamera); break; case 1: CamShotEndFollow(_CamShot_pCamera); break; }
    }
    CamShotSetTeamBlockFlag(0, 1); CamShotSetTeamBlockFlag(1, 1);
}
extern "C" void CamShotPlay(CamShotEntry_t *list)
{
    CamShotEndCurrent(); CamShotState_t *s = CamShotBegin(); s->mpList = list;
    for (CamShotEntry_t *e = list; e->mpData; ++e) {
        switch (e->mType) { case 1: CamShotAddFollow(s, (CamShotFollowDesc_t *)e->mpData); break; case 0: CamShotAddFixed(s, (CamShotFixedDesc_t *)e->mpData); break; }
    }
    CamShotNextRecord(s);
}
extern "C" void CamShotRequestStop(void) { _CamShot_bStopRequest = 1; }
extern "C" Object_80039F5C *CamShotGetPlayer(void)
{
    Object_80039F5C *p = 0; CamShotState_t *s = _CamShot_pState;
    if (_CamShot_bActive) {
        switch (s->mpCurrent->mType) {
        case 0: break;
        case 1: p = fn_8009BCE8(&s->mpCurrent->mData.m1.mRef); break;
        }
    }
    return p;
}
