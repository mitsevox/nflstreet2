#include "game/Camera_8013F738.h"

/* Camera fields used by this mode; +0x74..+0x88 are read and written as
   words here, +0xF8 begins the mode's own state. */
struct Camera_8013FD8C {
    char mPad00[0x5C];
    float mUnknown5C;
    float mUnknown60;
    float mUnknown64;
    float mUnknown68;
    float mUnknown6C;
    float mUnknown70;
    int mUnknown74;
    int mUnknown78;
    int mUnknown7C;
    int mUnknown80;
    int mUnknown84;
    int mUnknown88;
    char mPad8C[0x14];
    int mUnknownA0;
    char mPadA4[0x38];
    void (*mUnknownDC)(Camera_8013FD8C *pCamera, int msg);
    char mPadE0[0x18];
    int mUnknownF8[2];
};

struct Pair_8013FE30 {
    int mUnknown0;
    int mUnknown4;
};

/* Read by fn_8013C478 (the float) and fn_8013C4BC (the two words from +4
   and the shift +0xC). */
struct Preset_8013FE30 {
    float mUnknown0;
    Pair_8013FE30 mUnknown4;
    int mUnknownC;
};

struct Tuning_8013FF28 {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    int mUnknownC;
};

struct Mode_8013FD8C {
    void (*mUnknown00)(Camera_8013FD8C *pCamera);
    void (*mUnknown04)(Camera_8013FD8C *pCamera);
    int mUnknown08;
};

extern "C" {
int fn_800A34E0(void);
void fn_8013C478(void *pCamera, void *pValue);
void fn_8013C4BC(void *pCamera, void *pAngles, int shift);
void fn_8013C540(void *pCamera, int value);
void fn_8013C57C(void *pCamera, int value);
void fn_8013C6F0(Camera_8013F738 *pCamera);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013FA24(void);
void fn_8013FA8C(int a);
void fn_8013FBB4(int index, int id);
int fn_801784C4(void);
int fn_801CFE40(float y, float x);
void fn_80227490(float *pOut, float *pIn, int a0, int a1, int a2);

void fn_8013FD8C(Camera_8013FD8C *pCamera);
void fn_8013FD9C(Camera_8013FD8C *pCamera);
void fn_8013FDA0(Camera_8013FD8C *pCamera);
void fn_8013FDE0(Camera_8013FD8C *pCamera, int msg);
void fn_8013FE30(Camera_8013FD8C *pCamera);
}

static Preset_8013FE30 lbl_802DBDE0[6] = {
    { 8.0f, { -0x38E38E, 0 }, 5 },
    { 10.0f, { -0x2AAAAA, 0 }, 5 },
    { 14.0f, { -0x31C71C, 0 }, 5 },
    { 14.0f, { -0x31C71C, 0 }, 5 },
    { 6.0f, { -0x31C71C, 0x400000 }, 5 },
    { 10.0f, { -0x2AAAAA, 0 }, 5 },
};

static Pair_8013FE30 lbl_802DBE40[6] = {
    { -0x91A2, 0x369D },
    { 0, 0 },
    { -0xFEDC, 0x7F6E },
    { -0xFEDC, 0x7F6E },
    { 0, 0 },
    { 0, 0 },
};

extern "C" {
Mode_8013FD8C lbl_802DBE70 = { fn_8013FD8C, fn_8013FD9C, 0 };
}

static Tuning_8013FF28 lbl_802DBE7C[4] = {
    { 0.1f, 0.05f, 0xAAE60, 0xAAE60 },
    { 0.15f, 0.15f, 0xAAE60, 0xAAE60 },
    { 0.5f, 1.0f, 0xAAE60, 0xAAE60 },
    { 0.1f, 0.01f, 0x55730, 0x55730 },
};

extern "C" {

void fn_8013FC58(void)
{
    int id = 19;
    int b = 1;
    Camera_8013F738 *pCamera = fn_8013FA04(5);
    int next;

    if (pCamera) {
        b = pCamera->mUnknownA0;
        id = pCamera->mUnknown9C;
    }
    next = fn_800A34E0();
    if (next <= 18 && next != id) {
        fn_8013FBB4(0, next);
        fn_8013FA8C(b);
    }
    fn_8013FA24();
    fn_8013C6F0(fn_8013FA04(5));
}

int fn_8013FCD4(void)
{
    fn_8013FA04(0);
    return fn_801784C4() ? 0x800000 : 0;
}

int fn_8013FD0C(int index)
{
    float dir[3];
    float out[3];
    Camera_8013F738 *pCamera;

    dir[0] = dir[1] = dir[2] = out[0] = out[1] = out[2] = 0.0f;
    pCamera = fn_8013FA04(index);
    dir[2] = -1.0f;
    fn_80227490(out, dir, pCamera->mHeader.mUnknown1C, pCamera->mHeader.mUnknown18, pCamera->mHeader.mUnknown14);
    out[1] = -out[1];
    return fn_801CFE40(out[1], out[0]);
}

void fn_8013FD8C(Camera_8013FD8C *pCamera)
{
    pCamera->mUnknownDC = fn_8013FDE0;
}

void fn_8013FD9C(Camera_8013FD8C *pCamera)
{
}

void fn_8013FDA0(Camera_8013FD8C *pCamera)
{
    int *pState = pCamera->mUnknownF8;

    fn_8013C540(pCamera, pState[0]);
    fn_8013C57C(pCamera, pState[1]);
}

void fn_8013FDE0(Camera_8013FD8C *pCamera, int msg)
{
    switch (msg) {
    case 3:
        fn_8013FDA0(pCamera);
        break;
    case 1:
        fn_8013FE30(pCamera);
        break;
    case 0:
    case 2:
    case 4:
        break;
    }
}

void fn_8013FE30(Camera_8013FD8C *pCamera)
{
    int *pState = pCamera->mUnknownF8;

    if (pCamera->mUnknownA0 <= 5) {
        fn_8013C478(pCamera, &lbl_802DBDE0[pCamera->mUnknownA0]);
        fn_8013C4BC(pCamera, &lbl_802DBDE0[pCamera->mUnknownA0].mUnknown4, lbl_802DBDE0[pCamera->mUnknownA0].mUnknownC);
        pState[0] = lbl_802DBE40[pCamera->mUnknownA0].mUnknown0;
        pState[1] = lbl_802DBE40[pCamera->mUnknownA0].mUnknown4;
    }
    if (pCamera->mUnknownA0 == 8) {
        Pair_8013FE30 *pSrc = &lbl_802DBDE0[0].mUnknown4;
        Pair_8013FE30 angles;

        angles.mUnknown0 = pSrc->mUnknown0;
        angles.mUnknown4 = pSrc->mUnknown4;
        angles.mUnknown4 = fn_801784C4() ? 0x800000 : 0;
        fn_8013C478(pCamera, &lbl_802DBDE0[0]);
        fn_8013C4BC(pCamera, &angles, lbl_802DBDE0[0].mUnknownC);
        pState[0] = 0;
        pState[1] = 0;
    }
}

void fn_8013FF28(Camera_8013FD8C *pCamera, int index)
{
    pCamera->mUnknown5C = pCamera->mUnknown60 = pCamera->mUnknown64 = lbl_802DBE7C[index].mUnknown0;
    pCamera->mUnknown68 = pCamera->mUnknown6C = pCamera->mUnknown70 = lbl_802DBE7C[index].mUnknown4;
    pCamera->mUnknown80 = pCamera->mUnknown84 = pCamera->mUnknown88 = lbl_802DBE7C[index].mUnknown8;
    pCamera->mUnknown74 = pCamera->mUnknown78 = pCamera->mUnknown7C = lbl_802DBE7C[index].mUnknownC;
}

}
