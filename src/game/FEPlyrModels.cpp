/* Front-end player models: the 3D players shown on the menu screens
   (create-a-player, gear, shops, player pick-up). Places, turns, scales and
   animates up to 14 models, moves them smoothly between positions, lets the player
   spin them and, in pair mode, keeps a second model ready so that an appearance
   change swaps in without a pop. */

#include "engine/viewport.h"
#include "game/Object_8003DEC4.h"
#include "game/FEPlyrModel.h"
#include "game/Object_8008044C.h"
#include "game/cu_8015C25C.h"
#include "game/fn_8007F828.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_801BE60C.h"
#include <string.h>

/* Object returned by ObjNew. */
struct FEPlyrScene_t {
    char mUnknown0[4];
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[84];
    char mUnknown108[4];
};

/* Third argument of ObjNew. */
struct FEPlyrSceneDesc_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
};

/* Element of _FEPlyr_aPlacement, _FEPlyr_aMoveFrom and _FEPlyr_aMoveTo. */
struct FEPlyrPlacement_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
    unsigned int mUnknown24;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
};

extern "C" {
extern float gFrameTimeScale;
extern void *gUISMainInfo;

void fn_8003AB40(FEPlyrModel_t *pRecord);
int fn_8003DA94(unsigned short count, int a, int b);
int fn_8003DCC0(int a);
void fn_8003E174(int a);
void fn_8003FAC4(int a);
void fn_8003FB2C(void);
int fn_8003FBF0(FEPlyrScene_t *pObject, int a);
void fn_80042270(FEPlyrModel_t *pRecord);
void fn_800423F8(Object_8003DEC4 *pObject, void *a, void *b);
void fn_800424C0(Object_8003DEC4 *pObject, int a);
void fn_800424E8(Object_8003DEC4 *pObject, void *a, unsigned short b, void *c);
void fn_80042508(Object_8003DEC4 *pObject, int a, unsigned int b);
void fn_80042530(Object_8003DEC4 *pObject, int a);
void fn_80042928(Object_8003DEC4 *pObject);
void PlayerLookSetGear(int index, int a, int b);
void fn_80089A84(FEPlyrModel_t *pRecord, unsigned int a);
void fn_8008A248(void);
void fn_8008FCB4(int a);
void fn_8008FD88(int a);
void fn_8008FE60(void);
void fn_8008FED4(void);
void fn_8009BD48(int *pRef, int a, int b, int c);
void fn_8009CDEC(FEPlyrModel_t *pRecord);
int fn_800ADD7C(void *pObject, unsigned int a);
int fn_800ADEFC(void *pObject, unsigned int a);
void fn_800B267C(Object_800B267C *pObject);
void fn_800B26E0(Object_800B267C *pObject);
void fn_800B2A14(Object_800B267C *pObject, unsigned char *a);
int fn_800C47C4(void);
void fn_800D7A0C(FEPlyrModel_t *pRecord, int a);
void fn_800EFD70(int a);
void fn_800EFDD8(void);
struct State_80039F5C;
void fn_800EFFA0(int a, State_80039F5C *pQueue, FEPlyrModel_t *pRecord, int c);
void fn_80161168(void);
void fn_8016D8B0(void *pObject);
void UISGameSetDrawMode(int a);
void UISViewObjSetDrawFunc(void (*pCallback)(int, float, float, float, float));
void fn_801BA03C(AnimHeader_t *pObject, void *a, float b, FEPlyrModel_t *pRecord);
int fn_801BC7C0(AnimHeader_t *pObject, void *a, void *b);
int fn_801BCA74(AnimHeader_t *pObject, void *a, int b, void *c, int d, int e);
int fn_801BCCAC(AnimHeader_t *pObject, void *a, int b, void *c, int d, int e);
void fn_801BE420(void *a, AnimHeader_t *pObject, void *b, FEPlyrModel_t *pRecord, float c);
void fn_801CE9E0(int a);
float fn_801CFD28(int a);
int MathRLerp(int a, int b, float c);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D08FC(int a);
void fn_801D0ADC(int a);
void fn_801D0C58(void *a);
void fn_801D0F80(void *a);
void fn_801D1258(int which, float (*pMatrix)[4]);
void fn_801D1288(int which, float (*pMatrix)[4]);
void fn_801D12BC(int a);
void fn_801D12EC(int a);
void fn_801D131C(int a);
FEPlyrScene_t *ObjNew(int a, int b, FEPlyrSceneDesc_t *pDesc);
void fn_80227490(float *pOut, float *pIn, int a, int b, int c);
void fn_80234424(int a);
}

static Object_8008044C _FEPlyr_PlayerCursor;
/* Matrix built by VptPerspective and passed to fn_801D1258. */
static float _FEPlyr_Projection[4][4];
static FEPlyrModel_t _FEPlyr_aModels[14];
/* Current values; FEPlyrUpdateMoves interpolates them from _FEPlyr_aMoveFrom towards
   _FEPlyr_aMoveTo by the factor in _FEPlyr_afMoveTime. */
static FEPlyrPlacement_t _FEPlyr_aPlacement[14];
static FEPlyrPlacement_t _FEPlyr_aMoveFrom[14];
static FEPlyrPlacement_t _FEPlyr_aMoveTo[14];
static float _FEPlyr_afMoveTime[14];

static unsigned char _FEPlyr_aPriority[14] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };

/* Number of records set up by FEPlyrInit. */
static int _FEPlyr_iCount = 0;
static unsigned char _FEPlyr_bActive = 0;
/* Set by FEPlyrSetPairMode together with the indices _FEPlyr_iFrontIndex and _FEPlyr_iBackIndex. */
static unsigned char _FEPlyr_bPairMode = 0;
static unsigned char _FEPlyr_bSwapPending = 0;
static FEPlyrScene_t *_FEPlyr_pScene = 0;
static int _FEPlyr_iSpinSpeed = 4;

static int _FEPlyr_iFrontIndex;
static int _FEPlyr_iBackIndex;

extern "C" {
void FEPlyrPlayAnim(int index, int a, int b);
static void _FEPlyrStopMove(int index);

static void _FEPlyrSetupModel(int index, Object_8003DEC4 *pObject)
{
    FEPlyrPlacement_t *pState = &_FEPlyr_aPlacement[index];
    FEPlyrModel_t *pRecord;

    memset(pState, 0, sizeof(FEPlyrPlacement_t));
    pState->mUnknown16 = 1.0f;
    pState->mUnknown24 = 72;
    pRecord = &_FEPlyr_aModels[index];
    memset(pRecord, 0, sizeof(FEPlyrModel_t));
    pRecord->mUnknown4 = pObject;
    fn_8003AB40(pRecord);
    fn_800B267C(&pRecord->mUnknown424);
    fn_8016D8B0(pRecord->mUnknown512);
    fn_8016D8B0(pRecord->mUnknown528);
    fn_8009BD48((int *)pRecord, 3, 0, (unsigned char)index);
    pRecord->mUnknown8 = 0;
    pRecord->mUnknown12 = 0;
    pRecord->mUnknown9 = 0;
    pRecord->mUnknown784 = pRecord->mUnknown3048;
    pRecord->mUnknown792 = pRecord->mUnknown2496;
    pRecord->mUnknown796 = &pRecord->mUnknown1244;
    pRecord->mUnknown800 = pRecord->mUnknown1256;
    pRecord->mUnknown804 = pRecord->mUnknown3604;
    pRecord->mUnknown808 = &pRecord->mUnknown3096;
    pRecord->mUnknown812 = pRecord->mUnknown3108;
    pRecord->mUnknown508 = 170.0f;
    FEPlyrPlayAnim(index, 82, 0);
}

static void _FEPlyrUpdatePartAnims(FEPlyrModel_t *pRecord, Object_8003DEC4 *pObject, float step)
{
    unsigned int i;

    if (pRecord == 0 || pObject == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (pObject->mUnknown20 & 0x20) {
            fn_801BE420(pRecord->mUnknown4528[i], &pRecord->mUnknown4008[i], pRecord->mUnknown4032[i], pRecord, step);
            fn_801BA03C(&pRecord->mUnknown4008[i], pRecord->mUnknown4032[i], step, pRecord);
            fn_80042508(pObject, fn_801BC7C0(&pRecord->mUnknown4008[i], pRecord->mUnknown4032[i], pRecord->mUnknown4528[i]), i);
        } else if (fn_800ADD7C(pObject->mUnknown116, i)) {
            fn_80042508(pObject, fn_800ADEFC(pObject->mUnknown116, i), i);
        }
    }
}

static void _FEPlyrUpdateAnims(FEPlyrModel_t *pRecord, float step)
{
    Object_8003DEC4 *pObject = pRecord->mUnknown4;
    int result;

    fn_800EFFA0(0, (State_80039F5C *)pRecord->mUnknown3048, pRecord, 0);
    if (pObject->mUnknown20 & 0x10) {
        fn_801BE420(pRecord->mUnknown3604, &pRecord->mUnknown3096, pRecord->mUnknown3108, pRecord, step);
        fn_801BA03C(&pRecord->mUnknown3096, pRecord->mUnknown3108, step, pRecord);
        result = fn_801BC7C0(&pRecord->mUnknown3096, pRecord->mUnknown3108, pRecord->mUnknown3604);
        fn_80042530(pObject, result);
    }
    _FEPlyrUpdatePartAnims(pRecord, pObject, step);
    fn_801BE420(pRecord->mUnknown2496, &pRecord->mUnknown1244, pRecord->mUnknown1256, pRecord, step);
    fn_801BA03C(&pRecord->mUnknown1244, pRecord->mUnknown1256, step, pRecord);
    result = fn_801BC7C0(&pRecord->mUnknown1244, pRecord->mUnknown1256, pRecord->mUnknown2496);
    fn_800424C0(pObject, result);
    pRecord->mUnknown544 = fn_801BCA74(&pRecord->mUnknown1244, pRecord->mUnknown1256, result, pRecord->mUnknown548, 0xFFFF, 1);
    pRecord->mUnknown545 = fn_801BCCAC(&pRecord->mUnknown1244, pRecord->mUnknown1256, result, pRecord->mUnknown552,
                                       fn_801BE648(pRecord->mUnknown792), (pRecord->mUnknown12 & 0x200) == 0);
    fn_800424E8(pObject, pRecord->mUnknown1256, pRecord->mUnknown1244.mUnknown4, pRecord->mUnknown2496);
}

static void _FEPlyrScreenToWorld(float x, float y, float z, float *pOut)
{
    float limit = -(240.0f / fn_801CFD28(0x100000));
    float offset = 240.0f / fn_801CFD28(0x100000);
    float scale;

    pOut[2] = 1.0f - offset + 1.0f + 10.0f - z;
    scale = (limit - pOut[2]) / limit;
    pOut[0] = (x - 427.0f) * scale + 427.0f;
    pOut[1] = (y - 240.0f) * scale + 240.0f;
    fn_80227490(pOut, pOut, 0x400000, 0, -0x400000);
}

static void _FEPlyrBuildTransform(Object_8003DEC4 *pObject);

static void _FEPlyrUpdateModel(int index, unsigned int step)
{
    FEPlyrPlacement_t *pState = &_FEPlyr_aPlacement[index];
    FEPlyrModel_t *pRecord = &_FEPlyr_aModels[index];
    Object_8003DEC4 *pObject = pRecord->mUnknown4;

    pObject->mUnknown24 = pState->mUnknown16 * (float)pState->mUnknown24 * (1.0f / 72.0f);
    pObject->mUnknown24 = (pObject->mUnknown24 - pState->mUnknown16) * pState->mUnknown20 + pState->mUnknown16;
    pObject->mUnknown20 |= 9;
    _FEPlyrUpdateAnims(pRecord, step);
    if (pRecord->mUnknown545 == 0) {
        pRecord->mUnknown424.mUnknown36 = pRecord->mUnknown424.mUnknown28;
        fn_800B26E0(&pRecord->mUnknown424);
    } else {
        fn_800B2A14(&pRecord->mUnknown424, &pRecord->mUnknown544);
    }
    if (pState->mUnknown29) {
        pRecord->mUnknown424.mUnknown24 = pState->mUnknown12;
    }
    if (pState->mUnknown28) {
        pRecord->mUnknown424.mUnknown0 = pRecord->mUnknown424.mUnknown12;
        pRecord->mUnknown424.mUnknown4 = pRecord->mUnknown424.mUnknown16;
        pRecord->mUnknown424.mUnknown8 = pRecord->mUnknown424.mUnknown20;
    }
    fn_80042270(pRecord);
    fn_8009CDEC(pRecord);
    fn_80042928(pObject);
    _FEPlyrBuildTransform(pObject);
    if (_FEPlyr_bPairMode ? index == _FEPlyr_iFrontIndex : index == 0) {
        FEPlyrScene_t *pView = _FEPlyr_pScene;

        pObject->mUnknown32 = pRecord->mUnknown776;
        fn_800423F8(pObject, pView->mUnknown4, pView->mUnknown108);
    }
}

static void _FEPlyrBuildTransform(Object_8003DEC4 *pObject)
{
    fn_801D0508();
    fn_801D08FC(0x400000);
    fn_801D0ADC(-0x400000);
    fn_801D0C58(pObject->mUnknown4);
    fn_801D0ADC(pObject->mUnknown36 + 0x400000);
    fn_801D08FC(0x400000);
    fn_801D0F80(pObject->mUnknown908);
    fn_801D0544();
}

static void _FEPlyrDrawModel(int index, float a, float b, float c, float d)
{
    FEPlyrModel_t *pRecord = &_FEPlyr_aModels[index];
    Object_8003DEC4 *pObject = pRecord->mUnknown4;
    float projection[4][4];
    float view[4][4];

    UISGameSetDrawMode(3);
    fn_801CE9E0(1);
    fn_801D0470(VptGetMatrixStack());
    fn_801D1288(2, projection);
    fn_801D1288(6, view);
    fn_801D04C4();
    fn_801D1258(2, _FEPlyr_Projection);
    fn_801D12BC(1);
    fn_801D131C(2);
    fn_801D12EC(6);
    fn_801D0544();
    fn_80234424(0);
    PlayerObjDraw(pObject, 1);
    if (_FEPlyr_bPairMode ? index == _FEPlyr_iFrontIndex : index == 0) {
        if (fn_8015D2E8(pObject)) {
            fn_8003FBF0(_FEPlyr_pScene, 1);
        }
    }
    fn_801D1258(2, projection);
    fn_801D1258(6, view);
    fn_801CE9E0(0);
}

static void _FEPlyrRender(int index, float a, float b, float c, float d)
{
    unsigned int step = (unsigned int)gFrameTimeScale;
    int i = index;

    if (_FEPlyr_bPairMode) {
        i = _FEPlyr_iBackIndex;
        if (i >= 0 && i < _FEPlyr_iCount) {
            _FEPlyrUpdateModel(i, step);
        }
        i = _FEPlyr_iFrontIndex;
    }
    if (i >= 0 && i < _FEPlyr_iCount) {
        _FEPlyrUpdateModel(i, step);
        _FEPlyrDrawModel(i, a, b, c, d);
    }
}

static void _FEPlyrSetHoldFlag(int index, int enable)
{
    FEPlyrModel_t *pRecord;
    Object_8003DEC4 *pObject;

    if (index < 0 || index >= _FEPlyr_iCount) {
        return;
    }
    pRecord = &_FEPlyr_aModels[index];
    pObject = pRecord->mUnknown4;
    if (enable) {
        pObject->mUnknown20 |= 0x400;
    } else {
        pObject->mUnknown20 &= ~0x400;
    }
}

void FEPlyrSetPosition(int index, float x, float y, float z);
void FEPlyrSetAngle(int index, float angle);
void FEPlyrSetScale(int index, float scale);

void FEPlyrInit(int count)
{
    int i;
    FEPlyrSceneDesc_t desc;
    FEPlyrScene_t *pView;

    fn_8008044C(&_FEPlyr_PlayerCursor, 0, 0x54415453);
    _FEPlyr_iCount = count;
    VptPerspective(_FEPlyr_Projection, 45.0f, 4.0f / 3.0f, 1.0f, 200.0f);
    fn_8008FCB4(0);
    fn_8008FE60();
    fn_800EFD70(0x21);
    fn_8003DA94(_FEPlyr_iCount, 0, 1);
    fn_8003E174(0);
    for (i = 0; i < _FEPlyr_iCount; i++) {
        _FEPlyrSetupModel(i, fn_8003DEC4(i));
        FEPlyrSetPosition(i, 427.0f, 440.0f, 5.0f);
        FEPlyrSetScale(i, 1.0f);
        FEPlyrSetAngle(i, 0.0f);
    }
    fn_8015CBC8();
    fn_8003FAC4(0);
    desc.mUnknown0 = fn_800C47C4();
    desc.mUnknown8 = 0;
    desc.mUnknown12 = 0;
    pView = ObjNew(3, 0, &desc);
    _FEPlyr_pScene = pView;
    pView->mUnknown20 = (pView->mUnknown20 | 2) & ~1;
    _FEPlyr_bActive = 1;
}

void FEPlyrShutdown(void)
{
    _FEPlyr_bActive = 0;
    fn_8015CC1C();
    fn_8003DCC0(0);
    fn_800EFDD8();
    fn_8008FED4();
    fn_8008FD88(1);
    fn_8008056C(&_FEPlyr_PlayerCursor);
    _FEPlyr_pScene->mUnknown20 &= ~2;
    VptTrashObject((int)_FEPlyr_pScene);
    _FEPlyr_pScene = 0;
    fn_8003FB2C();
}

void FEPlyrShow(void)
{
    UISViewObjSetDrawFunc(_FEPlyrRender);
}

void FEPlyrHide(void)
{
    UISViewObjSetDrawFunc(0);
}

void FEPlyrSetPosition(int index, float x, float y, float z)
{
    _FEPlyrStopMove(index);
    _FEPlyr_aPlacement[index].mUnknown0 = x;
    _FEPlyr_aPlacement[index].mUnknown4 = y;
    _FEPlyr_aPlacement[index].mUnknown8 = z;
    _FEPlyrScreenToWorld(x, y, z, &_FEPlyr_aModels[index].mUnknown424.mUnknown0);
    _FEPlyrScreenToWorld(x, y, z, &_FEPlyr_aModels[index].mUnknown424.mUnknown12);
}

void FEPlyrSetHoldPosition(int index, unsigned char value)
{
    _FEPlyr_aPlacement[index].mUnknown28 = value;
}

void FEPlyrSetAngle(int index, float angle)
{
    int value;

    _FEPlyrStopMove(index);
    value = (int)(angle * 46603.38f);
    _FEPlyr_aPlacement[index].mUnknown12 = value;
    _FEPlyr_aModels[index].mUnknown424.mUnknown24 = value;
}

void FEPlyrSetHoldAngle(int index, unsigned char value)
{
    _FEPlyr_aPlacement[index].mUnknown29 = value;
}

void FEPlyrSetScale(int index, float scale)
{
    _FEPlyrStopMove(index);
    _FEPlyr_aPlacement[index].mUnknown16 = scale;
}

void FEPlyrPlayAnim(int index, int a, int b)
{
    FEPlyrModel_t *pRecord;

    _FEPlyrSetHoldFlag(index, 0);
    pRecord = &_FEPlyr_aModels[index];
    if (a == 82) {
        pRecord->mUnknown1008 = 6;
    }
    fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796, pRecord->mUnknown800, a, 1.0f, pRecord);
}

void FEPlyrSetPose(int index, unsigned int value)
{
    FEPlyrModel_t *pRecord = &_FEPlyr_aModels[index];

    if (value > 30) {
        _FEPlyr_pScene->mUnknown20 |= 1;
        fn_800D7A0C(pRecord, 2);
    } else {
        _FEPlyr_pScene->mUnknown20 &= ~1;
    }
    fn_80089A84(pRecord, value);
    _FEPlyrSetHoldFlag(index, 1);
}

void FEPlyrSetHeight(int index, unsigned int value);

void FEPlyrSetPlayer(int index, int a, int b)
{
    Object_8003DEC4 *pObject = fn_8003DEC4(index);
    char buffer[28];

    PlayerDbSeekId(&_FEPlyr_PlayerCursor, a, 0);
    pObject->mUnknown4956 = a;
    pObject->mUnknown4968 = PlayerDbGetTeamId(&_FEPlyr_PlayerCursor);
    PlayerDbGetNameKey(&_FEPlyr_PlayerCursor, buffer, 27);
    PlayerDbGetPybt(&_FEPlyr_PlayerCursor);
    FEPlyrSetHeight(index, PlayerDbGetHeight(&_FEPlyr_PlayerCursor));
    if (fn_8015CD9C()) {
        fn_8015D060(index, buffer, _FEPlyr_aPriority[index], b);
    }
}

void FEPlyrSetPriority(int index, int value)
{
    _FEPlyr_aPriority[index] = value;
    fn_8015D1CC(index, value);
}

void FEPlyrSetHeight(int index, unsigned int value)
{
    _FEPlyr_aPlacement[index].mUnknown24 = value;
}

void FEPlyrUpdate(void)
{
    if (_FEPlyr_bActive) {
        if (fn_8007F828(6) == 2) {
            VptPerspective(_FEPlyr_Projection, 45.0f, 16.0f / 9.0f, 1.0f, 200.0f);
        } else {
            VptPerspective(_FEPlyr_Projection, 45.0f, 4.0f / 3.0f, 1.0f, 200.0f);
        }
        fn_80161168();
        if (_FEPlyr_bPairMode && _FEPlyr_bSwapPending) {
            Object_8003DEC4 *pObject = fn_8003DEC4(_FEPlyr_iBackIndex);

            if (fn_8015D1FC(_FEPlyr_iBackIndex) == 0 && fn_8015D2E8(pObject)) {
                int index = _FEPlyr_iFrontIndex;

                _FEPlyr_iFrontIndex = _FEPlyr_iBackIndex;
                _FEPlyr_iBackIndex = index;
                _FEPlyr_bSwapPending = 0;
            }
        }
    }
}

void FEPlyrMoveTo(int index, float x, float y, float z, float angle, float scale, int flag)
{
    int value;

    _FEPlyr_afMoveTime[index] = 0.0f;
    _FEPlyr_aMoveFrom[index].mUnknown0 = _FEPlyr_aPlacement[index].mUnknown0;
    _FEPlyr_aMoveFrom[index].mUnknown4 = _FEPlyr_aPlacement[index].mUnknown4;
    _FEPlyr_aMoveFrom[index].mUnknown8 = _FEPlyr_aPlacement[index].mUnknown8;
    _FEPlyr_aMoveFrom[index].mUnknown12 = _FEPlyr_aPlacement[index].mUnknown12;
    _FEPlyr_aMoveFrom[index].mUnknown16 = _FEPlyr_aPlacement[index].mUnknown16;
    _FEPlyr_aMoveFrom[index].mUnknown20 = _FEPlyr_aPlacement[index].mUnknown20;
    _FEPlyr_aMoveTo[index].mUnknown0 = x;
    _FEPlyr_aMoveTo[index].mUnknown4 = y;
    _FEPlyr_aMoveTo[index].mUnknown8 = z;
    _FEPlyr_aMoveTo[index].mUnknown16 = scale;
    _FEPlyr_aMoveTo[index].mUnknown12 = (int)(angle * 46603.38f);
    if (flag) {
        _FEPlyr_aMoveTo[index].mUnknown20 = 1.0f;
    } else {
        _FEPlyr_aMoveTo[index].mUnknown20 = 0.0f;
    }
    value = 16;
    fn_8021D7B8(gUISMainInfo, 0x8000002B, 1, &value);
}

static void _FEPlyrStopMove(int index)
{
    _FEPlyr_afMoveTime[index] = 1.1f;
    _FEPlyr_aPlacement[index].mUnknown20 = 1.0f;
}

int FEPlyrUpdateMoves(void)
{
    int moving = 0;
    int i;

    for (i = 0; i < _FEPlyr_iCount; i++) {
        float t = _FEPlyr_afMoveTime[i];

        if (t <= 1.0f) {
            moving = 1;
            _FEPlyr_aPlacement[i].mUnknown0 = _FEPlyr_aMoveFrom[i].mUnknown0 + (_FEPlyr_aMoveTo[i].mUnknown0 - _FEPlyr_aMoveFrom[i].mUnknown0) * t;
            _FEPlyr_aPlacement[i].mUnknown4 = _FEPlyr_aMoveFrom[i].mUnknown4 + (_FEPlyr_aMoveTo[i].mUnknown4 - _FEPlyr_aMoveFrom[i].mUnknown4) * t;
            _FEPlyr_aPlacement[i].mUnknown8 = _FEPlyr_aMoveFrom[i].mUnknown8 + (_FEPlyr_aMoveTo[i].mUnknown8 - _FEPlyr_aMoveFrom[i].mUnknown8) * t;
            _FEPlyr_aPlacement[i].mUnknown16 = _FEPlyr_aMoveFrom[i].mUnknown16 + (_FEPlyr_aMoveTo[i].mUnknown16 - _FEPlyr_aMoveFrom[i].mUnknown16) * t;
            _FEPlyr_aPlacement[i].mUnknown20 = _FEPlyr_aMoveFrom[i].mUnknown20 + (_FEPlyr_aMoveTo[i].mUnknown20 - _FEPlyr_aMoveFrom[i].mUnknown20) * t;
            _FEPlyr_aPlacement[i].mUnknown12 = MathRLerp(_FEPlyr_aMoveFrom[i].mUnknown12, _FEPlyr_aMoveTo[i].mUnknown12, t);
            _FEPlyr_afMoveTime[i] += 0.05f;
        } else {
            _FEPlyr_aPlacement[i].mUnknown0 = _FEPlyr_aMoveTo[i].mUnknown0;
            _FEPlyr_aPlacement[i].mUnknown4 = _FEPlyr_aMoveTo[i].mUnknown4;
            _FEPlyr_aPlacement[i].mUnknown8 = _FEPlyr_aMoveTo[i].mUnknown8;
            _FEPlyr_aPlacement[i].mUnknown16 = _FEPlyr_aMoveTo[i].mUnknown16;
            _FEPlyr_aPlacement[i].mUnknown20 = _FEPlyr_aMoveTo[i].mUnknown20;
            _FEPlyr_aPlacement[i].mUnknown12 = _FEPlyr_aMoveTo[i].mUnknown12;
        }
        _FEPlyrScreenToWorld(_FEPlyr_aPlacement[i].mUnknown0, _FEPlyr_aPlacement[i].mUnknown4, _FEPlyr_aPlacement[i].mUnknown8,
                    &_FEPlyr_aModels[i].mUnknown424.mUnknown0);
        _FEPlyr_aModels[i].mUnknown424.mUnknown24 = _FEPlyr_aPlacement[i].mUnknown12;
    }
    return moving;
}

float FEPlyrSpin(float turn)
{
    if (_FEPlyr_afMoveTime[0] > 1.0f) {
        if ((turn < 0.0f ? -turn : turn) > 0.01) {
            int delta = (int)((float)_FEPlyr_iSpinSpeed * turn * 46603.38f);
            int angle = _FEPlyr_aModels[0].mUnknown424.mUnknown24 + delta;

            _FEPlyr_aModels[0].mUnknown424.mUnknown24 = angle;
            _FEPlyr_aPlacement[0].mUnknown12 = angle;
            if (_FEPlyr_bPairMode) {
                _FEPlyr_aModels[_FEPlyr_iFrontIndex].mUnknown424.mUnknown24 = angle;
                _FEPlyr_aModels[_FEPlyr_iBackIndex].mUnknown424.mUnknown24 = _FEPlyr_aModels[0].mUnknown424.mUnknown24;
                _FEPlyr_aPlacement[_FEPlyr_iFrontIndex].mUnknown12 = _FEPlyr_aModels[0].mUnknown424.mUnknown24;
                _FEPlyr_aPlacement[_FEPlyr_iBackIndex].mUnknown12 = _FEPlyr_aModels[0].mUnknown424.mUnknown24;
            }
        }
        if (turn > 0.01) {
            turn -= 0.05;
            if (turn < 0.0f) {
                turn = 0.0f;
            }
        } else if (turn < -0.01) {
            turn += 0.05;
            if (turn > 0.0f) {
                turn = 0.0f;
            }
        }
    }
    return turn;
}

void FEPlyrResetPose(int index)
{
    fn_800B267C(&_FEPlyr_aModels[index].mUnknown424);
}

unsigned char FEPlyrSetPairMode(unsigned char enable, int a, int b)
{
    unsigned char previous = _FEPlyr_bPairMode;

    if (previous != enable) {
        _FEPlyr_bPairMode = enable;
        if (enable) {
            _FEPlyr_iFrontIndex = a;
            _FEPlyr_bSwapPending = 0;
            _FEPlyr_iBackIndex = b;
        }
    }
    return previous;
}

void FEPlyrRequestSwap(void)
{
    _FEPlyr_bSwapPending = 1;
}

int FEPlyrGetBackIndex(void)
{
    return _FEPlyr_iBackIndex;
}

int FEPlyrGetFrontIndex(void)
{
    return _FEPlyr_iFrontIndex;
}

void FEPlyrPlayPairAnim(void)
{
    FEPlyrModel_t *pFirst = &_FEPlyr_aModels[_FEPlyr_iFrontIndex];
    FEPlyrModel_t *pSecond = &_FEPlyr_aModels[_FEPlyr_iBackIndex];

    FEPlyrPlayAnim(_FEPlyr_iFrontIndex, 214, 0);
    FEPlyrPlayAnim(_FEPlyr_iBackIndex, 214, 0);
    FEPlyrSetPose(_FEPlyr_iFrontIndex, 2);
    FEPlyrSetPose(_FEPlyr_iBackIndex, 2);
    fn_8008A248();
    fn_801BE068(pFirst->mUnknown792, pFirst->mUnknown796, pFirst->mUnknown800, 214, 1.0f, pFirst);
    fn_801BE068(pSecond->mUnknown792, pSecond->mUnknown796, pSecond->mUnknown800, 214, 1.0f, pSecond);
}

void FEPlyrSetPairSlot(int a, int b)
{
    PlayerLookSetGear(_FEPlyr_iFrontIndex, a, b);
    PlayerLookSetGear(_FEPlyr_iBackIndex, a, b);
}
}
