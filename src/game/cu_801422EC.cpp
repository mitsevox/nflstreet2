#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"

struct CameraState_801422EC {
    char mPad00[0x18];
    float mUnknown18[3];
    int mUnknown24[3];
    float mUnknown30;
    float mUnknown34;
    float mUnknown38;
    char mPad3C[4];
    float mUnknown40;
    float mUnknown44;
    char mPad48[8];
    int mUnknown50;
    float mUnknown54[3];
    char mPad60[8];
    Point_8017886C mUnknown68;
    float mUnknown70;
    int mUnknown74;
};

struct Camera_801422EC {
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
    char mPad8C[0x14];
    int mUnknownA0;
    char mPadA4[0x54];
    CameraState_801422EC mUnknownF8;
};

struct Joint_802DCF8C {
    float mUnknown0;
    int mUnknown4;
};

extern "C" {
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
float fn_8013CEF4(float *pFrom, float *pTo, int *pAngles);
int fn_80177F70(void);
Point_8017886C fn_80177FE0(void);
float fn_80178298(void);
int fn_801784C4(void);
void fn_8017CFB4(int a);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
int fn_801C370C(int *pValue, int *pVel, int target, int a, int b);
int fn_801C384C(float *pValue, float *pVel, float target, float a, float b);
void fn_801C3990(Camera_801422EC *pCamera, float a, float b);
int fn_801CFE40(float y, float x);

void fn_801422EC(Camera_801422EC *pCamera);
void fn_801423D0(Camera_801422EC *pCamera);
void fn_801427E0(Camera_801422EC *pCamera, int smooth);
void fn_80142884(Object_80039F5C *pPlayer, Vector_80039F5C *pOut, float t);
void fn_8014294C(Camera_801422EC *pCamera, int *pAngles, int snap);
float fn_80142A00(Camera_801422EC *pCamera, float a, float b);
}

static int lbl_803EB1FC = 0;
static unsigned char lbl_803EB200 = 0;
static int lbl_803EB204 = 0;
static int lbl_803EB208 = 175;
static float lbl_803EB20C = 0.0015f;
static float lbl_803EB210 = 0.0f;
static float lbl_803EB214 = 0.0005f;
static unsigned char lbl_803EB218 = 0;
static unsigned char lbl_803EB219 = 0;

static float lbl_8031B6C4[3];

static Joint_802DCF8C lbl_802DCF8C[2] = {
    { 10.0f, 0 },
    { 0.0f, 26 },
};

extern "C" {

void fn_801422EC(Camera_801422EC *pCamera)
{
    CameraState_801422EC *pState = &pCamera->mUnknownF8;
    Object_80137ABC *pBall = fn_801374BC();
    Vector_80039F5C ballPos;
    int info[2];

    fn_80137D58(pBall, &ballPos);
    fn_8013BA58(pBall, info);
    pState->mUnknown68 = fn_80177FE0();
    pState->mUnknown70 = fn_80178298();
    pState->mUnknown74 = fn_80177F70();
    pState->mUnknown38 = 0.0f;
    switch (pCamera->mUnknownA0) {
    case 0:
        break;
    case 1:
        if (pState->mUnknown68.mY > 30.0f) {
            pState->mUnknown44 = 30.0f;
        } else {
            pState->mUnknown44 = pState->mUnknown68.mY < 30.0f ? -30.0f : 50.0f;
        }
        lbl_803EB200 = 1;
        break;
    case 2:
        break;
    }
}

void fn_801423D0(Camera_801422EC *pCamera)
{
    CameraState_801422EC *pState = &pCamera->mUnknownF8;
    int a = 0;
    int replay = fn_800AD9B4() == 3;
    int changed = 0;
    Object_80137ABC *pBall;
    Object_80039F5C *pPlayer;
    Vector_80039F5C ballPos;
    Vector_80039F5C mirrored;
    int info[2];
    int mode;
    float speed;
    float lag;
    int *pAngles;
    float *pFrom;

    pBall = fn_801374BC();
    mode = 0;
    fn_8013BA58(pBall, info);
    pPlayer = fn_80137AD0(pBall);
    fn_80177F70();
    fn_80137D58(pBall, &ballPos);
    lbl_803EB1FC = a;
    pState->mUnknown18[0] = 45.0f;
    pState->mUnknown18[1] = pState->mUnknown44;
    pState->mUnknown18[2] = 20.0f;
    speed = 24.0f;
    lag = 0.0f;
    switch (pCamera->mUnknownA0) {
    case 1:
        if (pPlayer) {
            fn_80142884(pPlayer, (Vector_80039F5C *)&pCamera->mUnknownF8.mUnknown54, pState->mUnknown30);
        } else {
            pState->mUnknown54[0] = ballPos.mX;
            pState->mUnknown54[1] = ballPos.mY;
            pState->mUnknown54[2] = ballPos.mZ;
        }
        mode = 0;
        speed = 8.0f;
        break;
    case 2:
        a = 0;
        if (lbl_803EB218 == 0 && fn_800AD9B4() != 1) {
            lbl_803EB218 = 1;
            fn_8017CFB4(7);
        }
        if (replay && (lbl_803EB208-- < 0 || a == 0)) {
            if (pPlayer) {
                fn_80142884(pPlayer, (Vector_80039F5C *)&pState->mUnknown54, pState->mUnknown30);
            } else {
                pState->mUnknown54[0] = ballPos.mX;
                pState->mUnknown54[1] = ballPos.mY;
                pState->mUnknown54[2] = ballPos.mZ;
            }
        } else {
            float t;
            Point_8017886C p1;
            Point_8017886C p2;

            lbl_803EB204 = lbl_803EB204 + 1;
            t = (float)lbl_803EB204;
            lbl_8031B6C4[0] = t * lbl_803EB20C + 8.0f;
            lbl_8031B6C4[2] = t * lbl_803EB214 + 0.5f;
            lbl_8031B6C4[1] = t * lbl_803EB210;
            if (a != 0) {
                mode = 4;
                p1 = fn_80177FE0();
                pState->mUnknown18[0] = lbl_8031B6C4[0] + p1.mX;
                p2 = fn_80177FE0();
                pState->mUnknown18[1] = lbl_8031B6C4[1] + p2.mY;
                pState->mUnknown18[2] = lbl_8031B6C4[2];
                if (fn_801784C4()) {
                    pState->mUnknown18[0] = -pState->mUnknown18[0];
                    pState->mUnknown18[1] = -pState->mUnknown18[1];
                }
            } else {
                mode = 0;
            }
            pState->mUnknown54[0] = pState->mUnknown68.mX;
            pState->mUnknown54[1] = pState->mUnknown68.mY;
            pState->mUnknown54[2] = 1.3f;
            lag = 8.0f;
        }
        lbl_803EB219 = 0;
        speed = 24.0f;
        break;
    default:
        pState->mUnknown54[0] = ballPos.mX;
        pState->mUnknown54[1] = ballPos.mY;
        pState->mUnknown54[2] = ballPos.mZ;
        lbl_803EB208 = 75;
        lbl_803EB218 = 0;
        lbl_803EB204 = 0;
        if (lbl_803EB219) {
            mode = 0;
            speed = 50.0f;
        }
        break;
    case 0:
        break;
    }
    if (pState->mUnknown50 != mode || lbl_803EB200) {
        lbl_803EB200 = 0;
        changed = 1;
    }
    mirrored.mX = pState->mUnknown54[0];
    mirrored.mY = pState->mUnknown54[1];
    mirrored.mZ = pState->mUnknown54[2];
    pState->mUnknown50 = mode;
    if (fn_801784C4()) {
        mirrored.mX = -mirrored.mX;
        mirrored.mY = -mirrored.mY;
    }
    pCamera->mUnknown04[0] = pState->mUnknown18[0];
    pCamera->mUnknown04[1] = pState->mUnknown18[1];
    pCamera->mUnknown04[2] = pState->mUnknown18[2];
    pAngles = pState->mUnknown24;
    pFrom = pState->mUnknown18;
    pState->mUnknown40 = fn_8013CEF4(pFrom, &mirrored.mX, pAngles);
    pState->mUnknown34 = fn_80142A00(pCamera, speed, pState->mUnknown40);
    pState->mUnknown40 = fn_8013CEF4(pFrom, &mirrored.mX, pAngles);
    fn_8014294C(pCamera, pAngles, !changed);
    if (changed) {
        pState->mUnknown30 = pState->mUnknown34 + lag;
    }
    fn_801427E0(pCamera, 1);
}

void fn_801427E0(Camera_801422EC *pCamera, int smooth)
{
    CameraState_801422EC *pState = &pCamera->mUnknownF8;
    float a;
    float b;

    if (fn_800AD9B4() == 3) {
        a = 0.04f;
        b = 0.03f;
    } else {
        a = 0.01f;
        b = 0.007f;
    }
    if (!smooth || (pState->mUnknown30 != pState->mUnknown34
        && fn_801C384C(&pState->mUnknown30, &pState->mUnknown38, pState->mUnknown34, a, b))) {
        pState->mUnknown30 = pState->mUnknown34;
    }
    fn_801C3990(pCamera, pState->mUnknown30, pCamera->mUnknown24);
}

void fn_80142884(Object_80039F5C *pPlayer, Vector_80039F5C *pOut, float t)
{
    Vector_80039F5C a;
    Vector_80039F5C b;

    if (t <= lbl_802DCF8C[0].mUnknown0) {
        Joint_802DCF8C *pEnd = &lbl_802DCF8C[1];
        float f;

        fn_8009BF5C(pPlayer, lbl_802DCF8C[0].mUnknown4, &a, 0);
        fn_8009BF5C(pPlayer, pEnd->mUnknown4, &b, 0);
        f = (t - lbl_802DCF8C[0].mUnknown0) / (lbl_802DCF8C[1].mUnknown0 - lbl_802DCF8C[0].mUnknown0);
        if (lbl_802DCF8C[1].mUnknown0 - lbl_802DCF8C[0].mUnknown0 == 0.0f) {
            f = 0.0f;
        }
        fn_80227930(pOut, &b, &a, f);
    } else {
        fn_8009BF5C(pPlayer, lbl_802DCF8C[0].mUnknown4, pOut, 0);
    }
}

void fn_8014294C(Camera_801422EC *pCamera, int *pAngles, int snap)
{
    pAngles[0] &= 0xFFFFFF;
    pAngles[1] &= 0xFFFFFF;
    pAngles[2] &= 0xFFFFFF;
    if (snap) {
        fn_801C370C(&pCamera->mUnknown14, &pCamera->mUnknown50, pAngles[0], pCamera->mUnknown74, pCamera->mUnknown80);
        fn_801C370C(&pCamera->mUnknown18, &pCamera->mUnknown54, pAngles[1], pCamera->mUnknown78, pCamera->mUnknown84);
        fn_801C370C(&pCamera->mUnknown1C, &pCamera->mUnknown58, pAngles[2], pCamera->mUnknown7C, pCamera->mUnknown88);
    } else {
        pCamera->mUnknown14 = pAngles[0];
        pCamera->mUnknown18 = pAngles[1];
        pCamera->mUnknown1C = pAngles[2];
    }
}

float fn_80142A00(Camera_801422EC *pCamera, float a, float b)
{
    return 2.0f * ((float)fn_801CFE40(a / (pCamera->mUnknown24 + pCamera->mUnknown24), b + b) * (360.0f / 16777216.0f));
}

void fn_80142A64(Camera_801422EC *pCamera, int msg)
{
    CameraState_801422EC *pState = &pCamera->mUnknownF8;

    switch (msg) {
    case 3:
        fn_801423D0(pCamera);
        break;
    case 1:
        fn_801422EC(pCamera);
        break;
    case 4:
        lbl_803EB200 = 1;
        pState->mUnknown44 = 30.0f;
        pState->mUnknown34 = 45.0f;
        fn_801427E0(pCamera, 0);
        fn_801422EC(pCamera);
        break;
    }
}

void fn_80142B00(void)
{
    lbl_803EB200 = 1;
}

}
