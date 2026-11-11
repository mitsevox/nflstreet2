/* Replay camera mode and camera helpers. The update functions of the camera
   easing values (ease in-out, sine, linear, snap), look-angle and screen
   aspect helpers, and camera mode 8, which follows the replay script's
   records: each frame it places the camera by the record's view mode,
   aims it at the ball, a tracked player or a script point, and eases its
   angles and field of view; at the end of a record it moves to the next. */
#include "game/fn_8007F828.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/RecordList_8002E7C0.h"

#include "game/CamInterp.h"

struct CamReplayState_t {
    float mUnknown00[3];
    float mUnknown0C[3];
    float mUnknown18;
    float mUnknown1C;
    float mUnknown20;
    float mUnknown24;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    char mPad2A[2];
    float mUnknown2C;
};

struct CamReplayCamera_t {
    char mPad00[4];
    float mUnknown04[3];
    char mPad10[4];
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    char mPad20[4];
    float mUnknown24;
    char mPad28[0x28];
    int mUnknown50;
    int mUnknown54;
    int mUnknown58;
    char mPad5C[0x18];
    int mUnknown74;
    int mUnknown78;
    int mUnknown7C;
    int mUnknown80;
    int mUnknown84;
    int mUnknown88;
    char mPad8C[0x10];
    int mUnknown9C;
    int mUnknownA0;
    char mPadA4[0x38];
    void (*mUnknownDC)(CamReplayCamera_t *pCamera, int msg);
    char mPadE0[0x18];
    CamReplayState_t mUnknownF8;
    RecordList_8002E7C0 mUnknown128;
};

/* Object returned by BallGetModel. */
struct CamReplayBallModel_t {
    char mPad00[4];
    float mUnknown04[3];
};

struct CamReplayModeTable_t {
    void (*mUnknown00)(CamReplayCamera_t *pCamera);
    void (*mUnknown04)(CamReplayCamera_t *pCamera);
    int mUnknown08;
};

struct CamReplayPart_t {
    float mUnknown00;
    int mUnknown04;
};

extern "C" {
extern void *lbl_803EA368;

double fabs(double);

void fn_8002CFF4(void *p);
void fn_8002D198(void *p);
Record_8002E7C0 *fn_8002E7C0(RecordList_8002E7C0 *pList);
int fn_8002E7D0(RecordList_8002E7C0 *pList);
void fn_8002E7EC(void *p, RecordList_8002E7C0 *pList);
Object_80039F5C *fn_80030C70(Object_80039F5C **ppA, Object_80039F5C **ppB);
void fn_80042380(Block_80170E64 *pBlock, int id, float *pOut, int b);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void *BallGetCurrent(void);
CamReplayBallModel_t *BallGetModel(void *p);
void fn_8013C624(CamReplayCamera_t *pCamera, int mode, int a, int b);
int fn_801784C4(void);
int fn_801784E8(void);
void BannerClear(int a);
void CamSetDefaultAspect(float aspect);
int CamRLerp(int *pValue, int *pVel, int target, int a, int b);
int CamLerp(float *pValue, float *pVel, float target, float a, float b);
void CamSetFieldOfView(CamReplayCamera_t *pCamera, float a, float b);
int fn_801CEB40(void);
int fn_801CEB4C(void);
float fn_801CFB74(float x);
int fn_801CFE40(float y, float x);
void fn_802272DC(float *pOut, float *pIn, float scale);
void fn_802273E8(float *pOut, float *pIn, int a0, int a1, int a2);
void fn_80227490(float *pOut, float *pIn, int a0, int a1, int a2);
void fn_8022765C(float *pOut, float *pA, float *pB);
void fn_80227930(float *pOut, float *pA, float *pB, float t);
float fn_80260B1C(float x);

void CamReplayInit(CamReplayCamera_t *pCamera);
void CamReplayUninit(CamReplayCamera_t *pCamera);
void CamReplayStart(CamReplayCamera_t *pCamera);
void CamReplayUpdate(CamReplayCamera_t *pCamera);
void CamReplayOrbitPos(Record_8002E7C0 *pRecord, float *pOrigin, float *pOut);
void CamReplayGetTarget(CamReplayCamera_t *pCamera, Record_8002E7C0 *pRecord, float *pOut);
void CamReplayUpdateFov(CamReplayCamera_t *pCamera, int smooth);
void CamReplayObjectCenter(Object_80039F5C *pObject, float *pOut, float t);
void CamReplaySetAngles(CamReplayCamera_t *pCamera, int *pAngles, int smooth);
float CamReplayCalcAngles(float *pFrom, float *pTo, int *pAngles);
void CamReplayClampPos(float *pPos);
void CamReplayHandleMsg(CamReplayCamera_t *pCamera, int msg);
}

extern "C" {
CamReplayModeTable_t gCamReplayMode = { CamReplayInit, CamReplayUninit, 0 };
}

static CamReplayPart_t _CamReplay_aCenterParts[2] = { { 10.0f, 0 }, { 0.0f, 26 } };
static CamReplayCamera_t *_CamReplay_pCamera = 0;
static int _CamReplay_bRepeat = 0;
static unsigned char _CamReplay_bTrackedPlayer;
static int _CamReplay_iTrackedId;
static float _CamReplay_vTarget[3];

#if defined(DECOMP_COMPARE)
/* accelerate to mid-way, then decelerate (peak speed 2 over the split point 0.5). */
extern "C" void CamInterpUpdateEaseInOut(CamInterp_t *pInterp, int steps)
{
    float split = 0.5f;
    float speed = 2.0f;

    while (steps--) {
        if (pInterp->mValue != pInterp->mTarget) {
            pInterp->mTime += pInterp->mRate;
            if (pInterp->mTime < 1.0f) {
                float t = pInterp->mTime;
                float ease;
                if (t < split) {
                    ease = speed * t * t / (split + split);
                } else {
                    ease = speed * split * 0.5f +
                           (t - t * t * 0.5f - split + split * split * 0.5f) * speed / (1.0f - split);
                }
                pInterp->mValue = pInterp->mStart + (pInterp->mTarget - pInterp->mStart) * ease;
            } else {
                pInterp->mValue = pInterp->mTarget;
                pInterp->mTime = 0.0f;
            }
        }
    }
}
#endif

extern "C" void CamInterpUpdateSine(CamInterp_t *pInterp, int steps)
{
    while (steps--) {
        if (pInterp->mValue != pInterp->mTarget) {
            pInterp->mTime += pInterp->mRate;
            if (pInterp->mTime < 1.0f) {
                float ease = (fn_801CFB74(pInterp->mTime * 3.14159265f - 1.57079633f) + 1.0f) * 0.5f;
                pInterp->mValue = pInterp->mStart + (pInterp->mTarget - pInterp->mStart) * ease;
            } else {
                pInterp->mValue = pInterp->mTarget;
                pInterp->mTime = 0.0f;
            }
        }
    }
}

extern "C" void CamInterpUpdateLinear(CamInterp_t *pInterp, int steps)
{
    while (steps--) {
        if (pInterp->mValue != pInterp->mTarget) {
            pInterp->mTime += pInterp->mRate;
            if (pInterp->mTime < 1.0f) {
                pInterp->mValue = pInterp->mStart + (pInterp->mTarget - pInterp->mStart) * pInterp->mTime;
            } else {
                pInterp->mValue = pInterp->mTarget;
                pInterp->mTime = 0.0f;
            }
        }
    }
}

extern "C" void CamInterpUpdateSnap(CamInterp_t *pInterp, int steps)
{
    while (steps--) {
        if (pInterp->mValue != pInterp->mTarget) {
            pInterp->mValue = pInterp->mTarget;
            pInterp->mTime = 0.0f;
        }
    }
}

extern "C" float CamCalcLookAngles(float *pFrom, float *pTo, int *pAngles)
{
    float v[3];
    int yaw;
    int pitch;

    fn_802276B4(v, pTo, pFrom);
    yaw = -fn_801CFE40(v[1], v[0]) + 0x400000;
    fn_80227490(v, v, yaw, 0, 0);
    pitch = -(fn_801CFE40(v[2], v[1]) + 0x400000);
    fn_80227490(v, v, 0, 0, pitch);
    pAngles[1] = 0;
    pAngles[2] = yaw;
    pAngles[0] = pitch;
    return fabs(v[2]);
}

extern "C" void CamSetupAspect(void)
{
    int a = fn_801CEB40();
    int b = fn_801CEB4C();

    if (a == 0xFFFF && b == 0xFFFF) {
        if (fn_8007F828(6) == 0) {
            CamSetDefaultAspect(4.0f / 3.0f);
        } else {
            CamSetDefaultAspect(16.0f / 9.0f);
        }
    } else if (b == 0xFFFF) {
        if (a == 0 && fn_8007F828(6) == 0) {
            CamSetDefaultAspect(4.0f / 3.0f);
        } else {
            CamSetDefaultAspect(16.0f / 9.0f);
        }
    } else if (a == 1 || b == 1) {
        CamSetDefaultAspect(16.0f / 9.0f);
    } else {
        CamSetDefaultAspect(4.0f / 3.0f);
    }
}

extern "C" float CamGetAspect(void)
{
    int a = fn_801CEB40();
    int b = fn_801CEB4C();
    float aspect;

    if (a == 0xFFFF && b == 0xFFFF) {
        if (fn_8007F828(6) == 0) {
            aspect = 4.0f / 3.0f;
        } else {
            aspect = 16.0f / 9.0f;
        }
    } else if (a == 1 || b == 1) {
        aspect = 16.0f / 9.0f;
    } else {
        aspect = 4.0f / 3.0f;
    }
    return aspect;
}

extern "C" int CamGetDisplayModeIndex(void)
{
    int a = fn_801CEB40();
    int b = fn_801CEB4C();

    if (b == 1) {
        return 1;
    }
    return a == 1 ? 2 : 3;
}

extern "C" float CamReplayGetProgress(unsigned int a, unsigned int b, unsigned int c)
{
    float ratio = (float)a / ((float)b / (float)c * 60.0f);

    return ratio < 0.0f ? 0.0f : (ratio > 1.0f ? 1.0f : ratio);
}

extern "C" void CamReplayInit(CamReplayCamera_t *pCamera)
{
    pCamera->mUnknownDC = CamReplayHandleMsg;
    _CamReplay_pCamera = pCamera;
    _CamReplay_vTarget[0] = _CamReplay_vTarget[1] = _CamReplay_vTarget[2] = 0.0f;
}

extern "C" void CamReplayUninit(CamReplayCamera_t *pCamera)
{
}

extern "C" void CamReplayStart(CamReplayCamera_t *pCamera)
{
    CamReplayState_t *pState = &pCamera->mUnknownF8;
    RecordList_8002E7C0 *pList = &pCamera->mUnknown128;
    Object_80039F5C *p;

    pState->mUnknown28 = 1;
    pState->mUnknown29 = 0;
    pState->mUnknown20 = 0.0f;
    p = fn_80030C70(0, 0);
    if (pCamera->mUnknownA0 == 8) {
        Record_8002E7C0 *pRecord = fn_8002E7C0(pList);

        pState->mUnknown00[0] = pRecord->mUnknown1C.mUnknown00[0];
        pState->mUnknown00[1] = pRecord->mUnknown1C.mUnknown00[1];
        pState->mUnknown00[2] = pRecord->mUnknown1C.mUnknown00[2];
        if (p) {
            _CamReplay_bTrackedPlayer = 1;
            fn_8009BD2C(p, &_CamReplay_iTrackedId);
        } else {
            _CamReplay_bTrackedPlayer = 0;
        }
        pState->mUnknown2C = 1.0f;
    }
}

extern "C" void CamReplayUpdate(CamReplayCamera_t *pCamera)
{
    int angles[3];
    Timer_8002E7C0 timer;
    float target[3];
    float out[3];
    float diff[3];
    float pos[3];
    float dir4[3];
    float dir0[3];
    CamReplayState_t *pState = &pCamera->mUnknownF8;
    Record_8002E7C0 *pRecord;
    View_8002E7C0 *pView;
    float *pFrom;
    float *pPoint;
    int mode;
    int duration;
    Object_80039F5C *p;
    int smooth;
    CamReplayBallModel_t *pTarget;
    float dist;

    out[0] = out[1] = out[2] = 0.0f;
    p = fn_80030C70(0, 0);
    pTarget = BallGetModel(BallGetCurrent());
    target[0] = pTarget->mUnknown04[0];
    target[1] = pTarget->mUnknown04[1];
    target[2] = pTarget->mUnknown04[2];
    smooth = !pState->mUnknown28;
    pState->mUnknown28 = 0;
    pRecord = fn_8002E7C0(&pCamera->mUnknown128);
    timer = pRecord->mUnknown04;
    pRecord->mUnknown04.mUnknown10++;
    if (pCamera->mUnknown9C == 15) {
        mode = pRecord->mUnknown1C.mUnknown34;
        pView = &pRecord->mUnknown1C;
        pFrom = pRecord->mUnknown1C.mUnknown1C;
        pPoint = pRecord->mUnknown1C.mUnknown28;
        duration = pRecord->mUnknown1C.mUnknown3C;
    } else {
        mode = pRecord->mUnknown5C.mUnknown34;
        pView = &pRecord->mUnknown5C;
        pFrom = pRecord->mUnknown5C.mUnknown1C;
        pPoint = pRecord->mUnknown5C.mUnknown28;
        duration = pRecord->mUnknown5C.mUnknown3C;
    }
    if (pRecord->mUnknown18 & 0x20) {
        pRecord->mUnknown18 &= ~0x20;
        CamReplayObjectCenter(pRecord->mUnknown1C.mUnknown38, pRecord->mUnknown1C.mUnknown1C, 0.5f);
    }
    fn_802276B4(diff, pState->mUnknown00, target);
    dist = fn_802270D4(diff);
    if (dist < 2.0f) {
        pState->mUnknown00[1] += 8.0f;
    }

    switch (mode) {
    case 0:
    case 1:
        pos[0] = pState->mUnknown00[0];
        pos[1] = pState->mUnknown00[1];
        pos[2] = pState->mUnknown00[2];
        CamReplayClampPos(pos);
        if (p == 0 && target[2] > 2.0f) {
            target[2] = 0.0f;
            dir0[0] = pFrom[0];
            dir0[1] = pFrom[1];
            dir0[2] = pFrom[2];
            if (fn_801784C4()) {
                dir0[0] = -dir0[0];
                dir0[1] = -dir0[1];
            }
            fn_802276B4(diff, dir0, target);
            dist = fn_802270D4(diff);
        }
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        CamReplayGetTarget(pCamera, pRecord, out);
        pState->mUnknown24 = CamReplayCalcAngles(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        CamReplayUpdateFov(pCamera, smooth);
        pState->mUnknown24 = CamReplayCalcAngles(pos, out, angles);
        break;
    case 2:
    case 3:
        pos[0] = pState->mUnknown00[0];
        pos[1] = pState->mUnknown00[1];
        pos[2] = pState->mUnknown00[2];
        CamReplayClampPos(pos);
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        CamReplayGetTarget(pCamera, pRecord, out);
        pState->mUnknown24 = CamReplayCalcAngles(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        CamReplayUpdateFov(pCamera, smooth);
        pState->mUnknown24 = CamReplayCalcAngles(pos, out, angles);
        break;
    case 4:
        dir4[0] = pPoint[0];
        dir4[1] = pPoint[1];
        dir4[2] = pPoint[2];
        if (fn_801784C4()) {
            dir4[0] = -dir4[0];
            dir4[1] = -dir4[1];
        }
        pos[0] = pState->mUnknown00[0];
        pos[1] = pState->mUnknown00[1];
        pos[2] = pState->mUnknown00[2];
        CamReplayClampPos(pos);
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        pState->mUnknown24 = CamReplayCalcAngles(pos, dir4, angles);
        pState->mUnknown1C = 45.0f;
        CamReplayUpdateFov(pCamera, smooth);
        pState->mUnknown24 = CamReplayCalcAngles(pos, dir4, angles);
        break;
    case 7:
    case 8:
    case 14:
        CamReplayGetTarget(pCamera, pRecord, out);
        smooth = 0;
        pos[0] = out[0];
        pos[1] = out[1];
        pos[2] = out[2];
        if (fn_801784C4()) {
            pos[0] -= pView->mUnknown00[0];
            pos[1] -= pView->mUnknown00[1];
        } else {
            pos[0] += pView->mUnknown00[0];
            pos[1] += pView->mUnknown00[1];
        }
        pos[2] = pView->mUnknown00[2];
        pos[0] = pos[0] < -11.0f ? -11.0f : (pos[0] > 11.0f ? 11.0f : pos[0]);
        pos[1] = pos[1] < -45.0f ? -45.0f : (pos[1] > 45.0f ? 45.0f : pos[1]);
        pos[2] = pos[2] < 0.0f ? 0.0f : pos[2];
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        pState->mUnknown24 = CamReplayCalcAngles(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        CamReplayUpdateFov(pCamera, 0);
        break;
    case 5:
    case 6:
        CamReplayGetTarget(pCamera, pRecord, out);
        smooth = 0;
        CamReplayOrbitPos(pRecord, out, pos);
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        pState->mUnknown24 = CamReplayCalcAngles(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        CamReplayUpdateFov(pCamera, 0);
        break;
    case 9:
    case 10:
        CamReplayGetTarget(pCamera, pRecord, out);
        pos[0] = out[0];
        pos[1] = out[1];
        pos[2] = out[2];
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        pState->mUnknown24 = CamReplayCalcAngles(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        CamReplayUpdateFov(pCamera, 0);
        break;
    case 11:
    case 12:
    case 13: {
        float t;

        if (duration == 0) {
            t = CamReplayGetProgress(timer.mUnknown10, timer.mUnknown08, timer.mUnknown0C);
        } else {
            t = CamReplayGetProgress(timer.mUnknown10, duration, timer.mUnknown0C);
        }
        pCamera->mUnknown04[0] = pState->mUnknown00[0];
        pCamera->mUnknown04[1] = pState->mUnknown00[1];
        pCamera->mUnknown04[2] = pState->mUnknown00[2];
        smooth = 0;
        switch (mode) {
        case 12:
            CamReplayObjectCenter(pRecord->mUnknown1C.mUnknown38, out, 0.0f);
            fn_8022765C(out, out, pPoint);
            break;
        case 13:
            out[0] = target[0];
            out[1] = target[1];
            out[2] = target[2];
            fn_8022765C(out, out, pPoint);
            break;
        case 11:
        default:
            out[0] = pPoint[0];
            out[1] = pPoint[1];
            out[2] = pPoint[2];
            break;
        }
        out[0] = pFrom[0] * (1.0f - t) + out[0] * t;
        out[1] = pFrom[1] * (1.0f - t) + out[1] * t;
        out[2] = pFrom[2] * (1.0f - t) + out[2] * t;
        pState->mUnknown24 = CamReplayCalcAngles(pCamera->mUnknown04, out, angles);
        pState->mUnknown1C = 45.0f;
        CamReplayUpdateFov(pCamera, 0);
        pState->mUnknown24 = CamReplayCalcAngles(pCamera->mUnknown04, out, angles);
        break;
    }
    default:
        fn_801C1F94(out, 0, sizeof(out));
        break;
    }
    CamReplaySetAngles(pCamera, angles, smooth);
    pView->mUnknown0C[0] = out[0];
    pView->mUnknown0C[1] = out[1];
    pView->mUnknown0C[2] = out[2];
}

extern "C" void CamReplayOrbitPos(Record_8002E7C0 *pRecord, float *pOrigin, float *pOut)
{
    Timer_8002E7C0 timer = pRecord->mUnknown04;
    float t = (float)timer.mUnknown10 / ((float)timer.mUnknown08 / (float)timer.mUnknown0C * 60.0f);
    float from[3];
    float to[3];
    float v[3];
    float lenFrom, len;
    int yawFrom, yawTo, pitchFrom, pitchTo;
    int yaw, pitch;

    from[0] = pRecord->mUnknown1C.mUnknown00[0];
    from[1] = pRecord->mUnknown1C.mUnknown00[1];
    from[2] = pRecord->mUnknown1C.mUnknown00[2];
    to[0] = pRecord->mUnknown1C.mUnknown28[0];
    to[1] = pRecord->mUnknown1C.mUnknown28[1];
    to[2] = pRecord->mUnknown1C.mUnknown28[2];
    if (fn_801784C4()) {
        from[0] = -from[0];
        from[1] = -from[1];
        to[0] = -to[0];
        to[1] = -to[1];
    }

    lenFrom = fn_802270D4(from);
    len = t * fn_802270D4(to) + (1.0f - t) * lenFrom;

    yawFrom = fn_801CFE40(from[1], from[0]) & 0xffffff;
    yawTo = fn_801CFE40(to[1], to[0]) & 0xffffff;
    if (pRecord->mUnknown1C.mUnknown3C == 1) {
        while (yawTo < yawFrom) {
            yawTo += 0x1000000;
        }
    } else {
        while (yawFrom < yawTo) {
            yawFrom += 0x1000000;
        }
    }
    yaw = (int)(t * yawTo + (1.0f - t) * yawFrom);

    pitchFrom = fn_801CFE40(from[2], fn_80260B1C(from[0] * from[0] + from[1] * from[1])) & 0xffffff;
    pitchTo = fn_801CFE40(to[2], fn_80260B1C(to[0] * to[0] + to[1] * to[1])) & 0xffffff;
    pitch = (int)(t * pitchTo + (1.0f - t) * pitchFrom - pitchFrom);

    fn_802273E8(v, from, 0, 0, -yawFrom);
    fn_802273E8(v, v, 0, -pitch, 0);
    fn_802273E8(v, v, 0, 0, yaw);
    fn_802272DC(v, v, len);
    fn_80227638(v, v, pOrigin);
    pOut[0] = v[0];
    pOut[1] = v[1];
    pOut[2] = v[2];
}

extern "C" void CamReplayGetTarget(CamReplayCamera_t *pCamera, Record_8002E7C0 *pRecord, float *pOut)
{
    CamReplayState_t *pState = &pCamera->mUnknownF8;
    Object_80039F5C *pObject = fn_80030C70(0, 0);
    float target[3];
    float tracked[3];
    int id;
    float blend;
    CamReplayBallModel_t *pTarget;

    pTarget = BallGetModel(BallGetCurrent());
    tracked[0] = pTarget->mUnknown04[0];
    tracked[1] = pTarget->mUnknown04[1];
    tracked[2] = pTarget->mUnknown04[2];

    switch (pRecord->mUnknown1C.mUnknown34) {
    case 0:
    case 1:
    case 5:
    case 14:
        if (pObject) {
            fn_8009BD2C(pObject, &id);
            if (!_CamReplay_bTrackedPlayer || id != _CamReplay_iTrackedId) {
                pState->mUnknown2C = 0.0f;
            }
            CamReplayObjectCenter(pObject, target, 0.0f);
            if (pState->mUnknown2C < 1.0f) {
                blend = pState->mUnknown2C + 1.0f / 90.0f;
                blend = blend > 1.0f ? 1.0f : blend;
                pState->mUnknown2C = blend;
                fn_80227930(pOut, target, _CamReplay_vTarget, blend);
                _CamReplay_vTarget[0] = pOut[0];
                _CamReplay_vTarget[1] = pOut[1];
                _CamReplay_vTarget[2] = pOut[2];
            } else {
                pOut[0] = target[0];
                pOut[1] = target[1];
                pOut[2] = target[2];
                _CamReplay_vTarget[0] = pOut[0];
                _CamReplay_vTarget[1] = pOut[1];
                _CamReplay_vTarget[2] = pOut[2];
            }
            _CamReplay_bTrackedPlayer = 1;
            fn_8009BD2C(pObject, &_CamReplay_iTrackedId);
        } else {
            if (_CamReplay_bTrackedPlayer) {
                pState->mUnknown2C = 0.0f;
            }
            if (pState->mUnknown2C < 1.0f) {
                blend = pState->mUnknown2C + 1.0f / 90.0f;
                blend = blend > 1.0f ? 1.0f : blend;
                pState->mUnknown2C = blend;
                fn_80227930(pOut, tracked, _CamReplay_vTarget, blend);
                _CamReplay_vTarget[0] = pOut[0];
                _CamReplay_vTarget[1] = pOut[1];
                _CamReplay_vTarget[2] = pOut[2];
            } else {
                pOut[0] = tracked[0];
                pOut[1] = tracked[1];
                pOut[2] = tracked[2];
                _CamReplay_vTarget[0] = pOut[0];
                _CamReplay_vTarget[1] = pOut[1];
                _CamReplay_vTarget[2] = pOut[2];
            }
            _CamReplay_bTrackedPlayer = 0;
        }
        break;
    case 2:
    case 6:
    case 7:
    case 10:
        CamReplayObjectCenter(pRecord->mUnknown1C.mUnknown38, target, 0.0f);
        pOut[0] = target[0];
        pOut[1] = target[1];
        pOut[2] = target[2];
        break;
    case 3:
    case 8:
    case 9:
        pOut[0] = tracked[0];
        pOut[1] = tracked[1];
        pOut[2] = tracked[2];
        break;
    }
    pState->mUnknown0C[0] = pOut[0];
    pState->mUnknown0C[1] = pOut[1];
    pState->mUnknown0C[2] = pOut[2];
}

extern "C" void CamReplayUpdateFov(CamReplayCamera_t *pCamera, int smooth)
{
    float argA = 0.02f;
    float argB = 0.01f;
    CamReplayState_t *pState = &pCamera->mUnknownF8;

    if (!smooth
        || (pState->mUnknown18 != pState->mUnknown1C
            && CamLerp(&pState->mUnknown18, &pState->mUnknown20, pState->mUnknown1C, argA, argB))) {
        pState->mUnknown18 = pState->mUnknown1C;
    }
    CamSetFieldOfView(pCamera, pState->mUnknown18 > 2796202.0f ? 2796202.0f : pState->mUnknown18, pCamera->mUnknown24);
}

extern "C" void CamReplayObjectCenter(Object_80039F5C *pObject, float *pOut, float t)
{
    CamReplayPart_t *pFirst = _CamReplay_aCenterParts;
    CamReplayPart_t *pSecond = pFirst + 1;
    float a[3];
    float b[3];

    fn_80042380(pObject->mpUnknown4, pFirst->mUnknown04, a, 0);
    fn_80042380(pObject->mpUnknown4, pSecond->mUnknown04, b, 0);
    fn_80227930(pOut, b, a, 0.5f);
}

extern "C" void CamReplaySetAngles(CamReplayCamera_t *pCamera, int *pAngles, int smooth)
{
    pAngles[0] &= 0xffffff;
    pAngles[1] &= 0xffffff;
    pAngles[2] &= 0xffffff;
    if (smooth) {
        CamRLerp(&pCamera->mUnknown14, &pCamera->mUnknown50, pAngles[0], pCamera->mUnknown74, pCamera->mUnknown80);
        CamRLerp(&pCamera->mUnknown18, &pCamera->mUnknown54, pAngles[1], pCamera->mUnknown78, pCamera->mUnknown84);
        CamRLerp(&pCamera->mUnknown1C, &pCamera->mUnknown58, pAngles[2], pCamera->mUnknown7C, pCamera->mUnknown88);
    } else {
        pCamera->mUnknown14 = pAngles[0];
        pCamera->mUnknown18 = pAngles[1];
        pCamera->mUnknown1C = pAngles[2];
    }
}

extern "C" float CamReplayCalcAngles(float *pFrom, float *pTo, int *pAngles)
{
    float d[3];
    int yaw, pitch;

    fn_802276B4(d, pTo, pFrom);
    yaw = -fn_801CFE40(d[1], d[0]) + 0x400000;
    fn_80227490(d, d, yaw, 0, 0);
    pitch = -(fn_801CFE40(d[2], d[1]) + 0x400000);
    fn_80227490(d, d, 0, 0, pitch);
    pAngles[1] = 0;
    pAngles[2] = yaw;
    pAngles[0] = pitch;
    return fabs(d[2]);
}

extern "C" void CamReplayClampPos(float *pPos)
{
    if (fn_801784C4()) {
        pPos[0] = -pPos[0];
        pPos[1] = -pPos[1];
    }
    if (fn_801784E8()) {
        pPos[0] = -pPos[0];
        pPos[1] = -pPos[1];
    }
    pPos[0] = pPos[0] < -11.0f ? -11.0f : (pPos[0] > 11.0f ? 11.0f : pPos[0]);
    pPos[1] = pPos[1] < -65.0f ? -65.0f : (pPos[1] > 65.0f ? 65.0f : pPos[1]);
    pPos[2] = pPos[2] < 0.0f ? 0.0f : pPos[2];
}

extern "C" void CamReplayHandleMsg(CamReplayCamera_t *pCamera, int msg)
{
    switch (msg) {
    case 3:
        CamReplayUpdate(pCamera);
        break;
    case 1:
        CamReplayStart(pCamera);
        break;
    case 4:
        break;
    }
}

extern "C" void CamReplayNextRecord(void)
{
    void *p = lbl_803EA368;
    RecordList_8002E7C0 *pList = &_CamReplay_pCamera->mUnknown128;

    if (fn_8002E7D0(pList)) {
        fn_8002E7EC(p, pList);
        fn_8013C624(_CamReplay_pCamera, 8, 0, 0);
    } else if (_CamReplay_bRepeat) {
        fn_8013C624(_CamReplay_pCamera, 8, 0, 0);
        fn_8002CFF4(lbl_803EA368);
    } else {
        fn_8002D198(p);
        BannerClear(3);
    }
}
