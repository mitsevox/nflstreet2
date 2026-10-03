/* A value easing from mStart to mTarget; mUpdate advances it. */
struct Interp_8013CC14 {
    float mStart;
    float mTarget;
    float mValue;
    float mTime;
    float mRate;
    void (*mUpdate)(Interp_8013CC14 *pInterp, int steps);
};

/* Object handed to fn_8013E168. */
struct Object_8013E168 {
    char mPad00[4];
    int mUnknown04;
};

/* Timing block at Record_8002E7C0 +0x04. */
struct Timer_8002E7C0 {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
    int mUnknown10;
};

struct View_8002E7C0 {
    float mUnknown00[3];
    float mUnknown0C[3];
    char mPad18[4];
    float mUnknown1C[3];
    float mUnknown28[3];
    int mUnknown34;
    Object_8013E168 *mUnknown38;
    int mUnknown3C;
};

/* One 0x9C-byte entry of RecordList_8002E7C0. */
struct Record_8002E7C0 {
    char mPad00[4];
    Timer_8002E7C0 mUnknown04;
    int mUnknown18;
    View_8002E7C0 mUnknown1C;
    View_8002E7C0 mUnknown5C;
};

struct RecordList_8002E7C0 {
    Record_8002E7C0 mUnknown000[9];
    int mUnknown57C;
    int mUnknown580;
};

struct CameraState_8013D1C0 {
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

struct Camera_8013D1C0 {
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
    void (*mUnknownDC)(Camera_8013D1C0 *pCamera, int msg);
    char mPadE0[0x18];
    CameraState_8013D1C0 mUnknownF8;
    RecordList_8002E7C0 mUnknown128;
};

/* Object returned by fn_8013825C. */
struct Target_8013825C {
    char mPad00[4];
    float mUnknown04[3];
};

struct Mode_8013D1C0 {
    void (*mInit)(Camera_8013D1C0 *pCamera);
    void (*mExit)(Camera_8013D1C0 *pCamera);
    int mUnknown08;
};

struct Entry_8013E168 {
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
Object_8013E168 *fn_80030C70(int a, int b);
void fn_80042380(int a, int id, float *pOut, int b);
int fn_8007F828(int a);
void fn_8009BD2C(Object_8013E168 *pObject, int *pOut);
void *fn_801374BC(void);
Target_8013825C *fn_8013825C(void *p);
void fn_8013C624(Camera_8013D1C0 *pCamera, int mode, int a, int b);
int fn_801784C4(void);
int fn_801784E8(void);
void fn_8017CFB4(int a);
void fn_801C1F94(void *p, int c, int n);
void fn_801C3A3C(float aspect);
int fn_801C370C(int *pValue, int *pVel, int target, int a, int b);
int fn_801C384C(float *pValue, float *pVel, float target, float a, float b);
void fn_801C3990(Camera_8013D1C0 *pCamera, float a, float b);
int fn_801CEB40(void);
int fn_801CEB4C(void);
float fn_801CFB74(float x);
int fn_801CFE40(float y, float x);
float fn_802270D4(float *pV);
void fn_802272DC(float *pOut, float *pIn, float scale);
void fn_802273E8(float *pOut, float *pIn, int x, int y, int z);
void fn_80227490(float *pOut, float *pIn, int z, int y, int x);
void fn_80227638(float *pOut, float *pA, float *pB);
void fn_8022765C(float *pOut, float *pA, float *pB);
void fn_802276B4(float *pOut, float *pA, float *pB);
void fn_80227930(float *pOut, float *pA, float *pB, float t);
float fn_80260B1C(float x);

void fn_8013D1C0(Camera_8013D1C0 *pCamera);
void fn_8013D1F0(Camera_8013D1C0 *pCamera);
void fn_8013D1F4(Camera_8013D1C0 *pCamera);
void fn_8013D2A8(Camera_8013D1C0 *pCamera);
void fn_8013DA60(Record_8002E7C0 *pRecord, float *pOrigin, float *pOut);
void fn_8013DDF4(Camera_8013D1C0 *pCamera, Record_8002E7C0 *pRecord, float *pOut);
void fn_8013E0D0(Camera_8013D1C0 *pCamera, int smooth);
void fn_8013E168(Object_8013E168 *pObject, float *pOut, float t);
void fn_8013E1E4(Camera_8013D1C0 *pCamera, int *pAngles, int smooth);
float fn_8013E298(float *pFrom, float *pTo, int *pAngles);
void fn_8013E33C(float *pPos);
void fn_8013E434(Camera_8013D1C0 *pCamera, int msg);
}

extern "C" {
Mode_8013D1C0 lbl_802DBDB8 = { fn_8013D1C0, fn_8013D1F0, 0 };
}

static Entry_8013E168 lbl_802DBDC4[2] = { { 10.0f, 0 }, { 0.0f, 26 } };
static Camera_8013D1C0 *lbl_803EB1C8 = 0;
static int lbl_803EB1CC = 0;
static unsigned char lbl_803EC9F8;
static int lbl_803EC9FC;
static float lbl_8031B6A0[3];

extern "C" void fn_8013CD58(Interp_8013CC14 *pInterp, int steps)
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

extern "C" void fn_8013CE44(Interp_8013CC14 *pInterp, int steps)
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

extern "C" void fn_8013CEB8(Interp_8013CC14 *pInterp, int steps)
{
    while (steps--) {
        if (pInterp->mValue != pInterp->mTarget) {
            pInterp->mValue = pInterp->mTarget;
            pInterp->mTime = 0.0f;
        }
    }
}

extern "C" float fn_8013CEF4(float *pFrom, float *pTo, int *pAngles)
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

extern "C" void fn_8013CF98(void)
{
    int a = fn_801CEB40();
    int b = fn_801CEB4C();

    if (a == 0xFFFF && b == 0xFFFF) {
        if (fn_8007F828(6) == 0) {
            fn_801C3A3C(4.0f / 3.0f);
        } else {
            fn_801C3A3C(16.0f / 9.0f);
        }
    } else if (b == 0xFFFF) {
        if (a == 0 && fn_8007F828(6) == 0) {
            fn_801C3A3C(4.0f / 3.0f);
        } else {
            fn_801C3A3C(16.0f / 9.0f);
        }
    } else if (a == 1 || b == 1) {
        fn_801C3A3C(16.0f / 9.0f);
    } else {
        fn_801C3A3C(4.0f / 3.0f);
    }
}

extern "C" float fn_8013D050(void)
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

extern "C" int fn_8013D0D0(void)
{
    int a = fn_801CEB40();
    int b = fn_801CEB4C();

    if (b == 1) {
        return 1;
    }
    return a == 1 ? 2 : 3;
}

extern "C" float fn_8013D120(unsigned int a, unsigned int b, unsigned int c)
{
    float ratio = (float)a / ((float)b / (float)c * 60.0f);

    return ratio < 0.0f ? 0.0f : (ratio > 1.0f ? 1.0f : ratio);
}

extern "C" void fn_8013D1C0(Camera_8013D1C0 *pCamera)
{
    pCamera->mUnknownDC = fn_8013E434;
    lbl_803EB1C8 = pCamera;
    lbl_8031B6A0[0] = lbl_8031B6A0[1] = lbl_8031B6A0[2] = 0.0f;
}

extern "C" void fn_8013D1F0(Camera_8013D1C0 *pCamera)
{
}

extern "C" void fn_8013D1F4(Camera_8013D1C0 *pCamera)
{
    CameraState_8013D1C0 *pState = &pCamera->mUnknownF8;
    RecordList_8002E7C0 *pList = &pCamera->mUnknown128;
    Object_8013E168 *p;

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
            lbl_803EC9F8 = 1;
            fn_8009BD2C(p, &lbl_803EC9FC);
        } else {
            lbl_803EC9F8 = 0;
        }
        pState->mUnknown2C = 1.0f;
    }
}

extern "C" void fn_8013D2A8(Camera_8013D1C0 *pCamera)
{
    int angles[3];
    Timer_8002E7C0 timer;
    float target[3];
    float out[3];
    float diff[3];
    float pos[3];
    float dir4[3];
    float dir0[3];
    CameraState_8013D1C0 *pState = &pCamera->mUnknownF8;
    Record_8002E7C0 *pRecord;
    View_8002E7C0 *pView;
    float *pFrom;
    float *pPoint;
    int mode;
    int duration;
    Object_8013E168 *p;
    int smooth;
    Target_8013825C *pTarget;
    float dist;

    out[0] = out[1] = out[2] = 0.0f;
    p = fn_80030C70(0, 0);
    pTarget = fn_8013825C(fn_801374BC());
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
        fn_8013E168(pRecord->mUnknown1C.mUnknown38, pRecord->mUnknown1C.mUnknown1C, 0.5f);
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
        fn_8013E33C(pos);
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
        fn_8013DDF4(pCamera, pRecord, out);
        pState->mUnknown24 = fn_8013E298(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        fn_8013E0D0(pCamera, smooth);
        pState->mUnknown24 = fn_8013E298(pos, out, angles);
        break;
    case 2:
    case 3:
        pos[0] = pState->mUnknown00[0];
        pos[1] = pState->mUnknown00[1];
        pos[2] = pState->mUnknown00[2];
        fn_8013E33C(pos);
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        fn_8013DDF4(pCamera, pRecord, out);
        pState->mUnknown24 = fn_8013E298(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        fn_8013E0D0(pCamera, smooth);
        pState->mUnknown24 = fn_8013E298(pos, out, angles);
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
        fn_8013E33C(pos);
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        pState->mUnknown24 = fn_8013E298(pos, dir4, angles);
        pState->mUnknown1C = 45.0f;
        fn_8013E0D0(pCamera, smooth);
        pState->mUnknown24 = fn_8013E298(pos, dir4, angles);
        break;
    case 7:
    case 8:
    case 14:
        fn_8013DDF4(pCamera, pRecord, out);
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
        pState->mUnknown24 = fn_8013E298(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        fn_8013E0D0(pCamera, 0);
        break;
    case 5:
    case 6:
        fn_8013DDF4(pCamera, pRecord, out);
        smooth = 0;
        fn_8013DA60(pRecord, out, pos);
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        pState->mUnknown24 = fn_8013E298(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        fn_8013E0D0(pCamera, 0);
        break;
    case 9:
    case 10:
        fn_8013DDF4(pCamera, pRecord, out);
        pos[0] = out[0];
        pos[1] = out[1];
        pos[2] = out[2];
        pCamera->mUnknown04[0] = pos[0];
        pCamera->mUnknown04[1] = pos[1];
        pCamera->mUnknown04[2] = pos[2];
        pState->mUnknown24 = fn_8013E298(pos, out, angles);
        pState->mUnknown1C = 45.0f;
        fn_8013E0D0(pCamera, 0);
        break;
    case 11:
    case 12:
    case 13: {
        float t;

        if (duration == 0) {
            t = fn_8013D120(timer.mUnknown10, timer.mUnknown08, timer.mUnknown0C);
        } else {
            t = fn_8013D120(timer.mUnknown10, duration, timer.mUnknown0C);
        }
        pCamera->mUnknown04[0] = pState->mUnknown00[0];
        pCamera->mUnknown04[1] = pState->mUnknown00[1];
        pCamera->mUnknown04[2] = pState->mUnknown00[2];
        smooth = 0;
        switch (mode) {
        case 12:
            fn_8013E168(pRecord->mUnknown1C.mUnknown38, out, 0.0f);
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
        pState->mUnknown24 = fn_8013E298(pCamera->mUnknown04, out, angles);
        pState->mUnknown1C = 45.0f;
        fn_8013E0D0(pCamera, 0);
        pState->mUnknown24 = fn_8013E298(pCamera->mUnknown04, out, angles);
        break;
    }
    default:
        fn_801C1F94(out, 0, sizeof(out));
        break;
    }
    fn_8013E1E4(pCamera, angles, smooth);
    pView->mUnknown0C[0] = out[0];
    pView->mUnknown0C[1] = out[1];
    pView->mUnknown0C[2] = out[2];
}

extern "C" void fn_8013DA60(Record_8002E7C0 *pRecord, float *pOrigin, float *pOut)
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

extern "C" void fn_8013DDF4(Camera_8013D1C0 *pCamera, Record_8002E7C0 *pRecord, float *pOut)
{
    CameraState_8013D1C0 *pState = &pCamera->mUnknownF8;
    Object_8013E168 *pObject = fn_80030C70(0, 0);
    float target[3];
    float tracked[3];
    int id;
    float blend;
    Target_8013825C *pTarget;

    pTarget = fn_8013825C(fn_801374BC());
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
            if (!lbl_803EC9F8 || id != lbl_803EC9FC) {
                pState->mUnknown2C = 0.0f;
            }
            fn_8013E168(pObject, target, 0.0f);
            if (pState->mUnknown2C < 1.0f) {
                blend = pState->mUnknown2C + 1.0f / 90.0f;
                blend = blend > 1.0f ? 1.0f : blend;
                pState->mUnknown2C = blend;
                fn_80227930(pOut, target, lbl_8031B6A0, blend);
                lbl_8031B6A0[0] = pOut[0];
                lbl_8031B6A0[1] = pOut[1];
                lbl_8031B6A0[2] = pOut[2];
            } else {
                pOut[0] = target[0];
                pOut[1] = target[1];
                pOut[2] = target[2];
                lbl_8031B6A0[0] = pOut[0];
                lbl_8031B6A0[1] = pOut[1];
                lbl_8031B6A0[2] = pOut[2];
            }
            lbl_803EC9F8 = 1;
            fn_8009BD2C(pObject, &lbl_803EC9FC);
        } else {
            if (lbl_803EC9F8) {
                pState->mUnknown2C = 0.0f;
            }
            if (pState->mUnknown2C < 1.0f) {
                blend = pState->mUnknown2C + 1.0f / 90.0f;
                blend = blend > 1.0f ? 1.0f : blend;
                pState->mUnknown2C = blend;
                fn_80227930(pOut, tracked, lbl_8031B6A0, blend);
                lbl_8031B6A0[0] = pOut[0];
                lbl_8031B6A0[1] = pOut[1];
                lbl_8031B6A0[2] = pOut[2];
            } else {
                pOut[0] = tracked[0];
                pOut[1] = tracked[1];
                pOut[2] = tracked[2];
                lbl_8031B6A0[0] = pOut[0];
                lbl_8031B6A0[1] = pOut[1];
                lbl_8031B6A0[2] = pOut[2];
            }
            lbl_803EC9F8 = 0;
        }
        break;
    case 2:
    case 6:
    case 7:
    case 10:
        fn_8013E168(pRecord->mUnknown1C.mUnknown38, target, 0.0f);
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

extern "C" void fn_8013E0D0(Camera_8013D1C0 *pCamera, int smooth)
{
    float argA = 0.02f;
    float argB = 0.01f;
    CameraState_8013D1C0 *pState = &pCamera->mUnknownF8;

    if (!smooth
        || (pState->mUnknown18 != pState->mUnknown1C
            && fn_801C384C(&pState->mUnknown18, &pState->mUnknown20, pState->mUnknown1C, argA, argB))) {
        pState->mUnknown18 = pState->mUnknown1C;
    }
    fn_801C3990(pCamera, pState->mUnknown18 > 2796202.0f ? 2796202.0f : pState->mUnknown18, pCamera->mUnknown24);
}

extern "C" void fn_8013E168(Object_8013E168 *pObject, float *pOut, float t)
{
    Entry_8013E168 *pFirst = lbl_802DBDC4;
    Entry_8013E168 *pSecond = pFirst + 1;
    float a[3];
    float b[3];

    fn_80042380(pObject->mUnknown04, pFirst->mUnknown04, a, 0);
    fn_80042380(pObject->mUnknown04, pSecond->mUnknown04, b, 0);
    fn_80227930(pOut, b, a, 0.5f);
}

extern "C" void fn_8013E1E4(Camera_8013D1C0 *pCamera, int *pAngles, int smooth)
{
    pAngles[0] &= 0xffffff;
    pAngles[1] &= 0xffffff;
    pAngles[2] &= 0xffffff;
    if (smooth) {
        fn_801C370C(&pCamera->mUnknown14, &pCamera->mUnknown50, pAngles[0], pCamera->mUnknown74, pCamera->mUnknown80);
        fn_801C370C(&pCamera->mUnknown18, &pCamera->mUnknown54, pAngles[1], pCamera->mUnknown78, pCamera->mUnknown84);
        fn_801C370C(&pCamera->mUnknown1C, &pCamera->mUnknown58, pAngles[2], pCamera->mUnknown7C, pCamera->mUnknown88);
    } else {
        pCamera->mUnknown14 = pAngles[0];
        pCamera->mUnknown18 = pAngles[1];
        pCamera->mUnknown1C = pAngles[2];
    }
}

extern "C" float fn_8013E298(float *pFrom, float *pTo, int *pAngles)
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

extern "C" void fn_8013E33C(float *pPos)
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

extern "C" void fn_8013E434(Camera_8013D1C0 *pCamera, int msg)
{
    switch (msg) {
    case 3:
        fn_8013D2A8(pCamera);
        break;
    case 1:
        fn_8013D1F4(pCamera);
        break;
    case 4:
        break;
    }
}

extern "C" void fn_8013E474(void)
{
    void *p = lbl_803EA368;
    RecordList_8002E7C0 *pList = &lbl_803EB1C8->mUnknown128;

    if (fn_8002E7D0(pList)) {
        fn_8002E7EC(p, pList);
        fn_8013C624(lbl_803EB1C8, 8, 0, 0);
    } else if (lbl_803EB1CC) {
        fn_8013C624(lbl_803EB1C8, 8, 0, 0);
        fn_8002CFF4(lbl_803EA368);
    } else {
        fn_8002D198(p);
        fn_8017CFB4(3);
    }
}
