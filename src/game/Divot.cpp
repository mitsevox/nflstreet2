/* Turf divots: the marks players' feet leave in the field. A fixed pool of
   divots per type is placed where players step (DivotOnFootstep) or at random
   (DivotScatterRandom), grown and faded each frame, drawn with the newest
   ones brightest, and recorded for the instant replay under the channel name
   "Divots"; the per-surface variant tables come from the "surface"/"divot"
   data blocks. The file starts with a clamped linear map, also holds the
   on-field arrow objects (object type 16), and ends with the colour-entry
   parser used by the dynamic palette code that follows it. */
#include "game/DynClut_80044F20.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/bitstream.h"
#include "game/LevelSurface.h"
#include "game/fn_801D2B7C.h"
#include "game/ResLoad.h"
#include "game/fn_802372EC.h"

#define DIVOT_NUM_TYPES 1
#define DIVOT_TYPE_0 0
#define DIVOT_TYPE_1 1
#define DIVOT_NUM_SURFACES 14
#define DIVOT_SURFACE_NONE 15
#define DIVOT_MAX_REFS 16
#define DIVOT_MAX_RECORDS 1024
#define DIVOT_NUM_PLAYERS 14

/* Divot flags (mFlags). */
#define DIVOT_DONE 1
#define DIVOT_FADING 2
#define DIVOT_GROWN 4
#define DIVOT_NO_GROW_CHECK 8

/* How a grown divot goes away (mMode). */
enum DivotMode {
    DIVOT_MODE_FADE,
    DIVOT_MODE_TIMED,
    DIVOT_MODE_2
};

/* One divot of a pool (0x74 bytes). The +0x30 angle is a 24-bit word. */
struct Divot {
    Vector_80039F5C mPos;
    float mScale[3];
    float mScaleMax[3];
    float mScaleRate[3];
    unsigned int mAngle;
    float mAlpha;
    float mAlphaMax;
    float mAlphaRate;
    int mFlags;
    int mSurface;
    DivotMode mMode;
    float mTimer;
    void *mpOwner;
    char mUnknown54[12];
    int mUnknown60;
    int mIndex;
    int mType;
    int mVariant;
    unsigned char mActive;
};

/* Replay record of one divot (0x14 bytes). */
struct DivotRecord {
    float mPos[3];
    unsigned int mAngle;
    signed char mVariant;
    unsigned char mActive;
};

/* Per-type handlers: called when a divot is placed, removed and updated. */
struct DivotHandlers {
    void (*mpPlace)(Divot *p);
    void (*mpRemove)(Divot *p);
    void (*mpUpdate)(Divot *p);
};

#define FIELD_ARROW_MAX 40

/* Path of a field arrow as drawn by ArrowDraw (0x30 bytes). */
struct FieldArrowPath {
    unsigned int mCount;
    int mUnknown4;
    Vector_80039F5C *mpPoints;
    int mType;
    float mRadiusX;
    float mRadiusY;
    int mAngleOffset;
    float mWidth;
    unsigned char mColor[3];
    float mEndWidth;
    float mEndBrightness;
    unsigned char mDashed;
};

/* One field arrow object of object type 16 (0x60 bytes): its path and the two points the path
   draws through. */
struct FieldArrow {
    char mUnknown0[0x14];
    FieldArrowPath mPath;
    Vector_80039F5C mPoints[2];
    unsigned char mVisible;
};

/* Last stepped position of each of the two feet of one player. */
struct DivotFeet {
    float mFoot0[2];
    float mFoot1[2];
};

extern "C" {
extern void *lbl_803EA368;

void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030ACC(void (*pWrite)(BitStream_t *),
                 void (*pRead)(BitStream_t *, BitStream_t *, BitStream_t *, BitStream_t *, float),
                 unsigned int size, const char *pName);
int InGameIsPaused(void);
int InGameIsPlaying(void);
int fn_8002D060(void *p);
void ArrowInit(void *p);
void ArrowShutdown(void *p);
void ArrowSetPointBuffer(void *p, void *pData, int a);
void ArrowReset(void *p);
int PauseIsOpen(void);
void AudmonEventPostId(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
void *fn_800A336C(void);
int fn_800A33A4(void);
int fn_800C4E18(Object_80039F5C *pPlayer);
Object_80039F5C *BallGetCurrentHolder(void);
int fn_801784C4(void);
float fn_80178A08(void);
float fn_80178A44(void);
void ArrowDraw(void *p);
void DivotRenderLoadAll(void);
void DivotRenderFreeAll(void);
void DivotRenderOnPlace(Divot *p);
void DivotRenderOnRemove(Divot *p);
void DivotRenderOnRefresh(Divot *p);
void DivotRenderOnDraw(Divot *p);
void DivotRenderBeginType(int type);
void DivotRenderEndType(int type);
char *fn_801C3084(const char *pString, int c);
int fn_801C3214(const char *pA, const char *pB, int n);
int atoi(const char *pString);
void fn_801CE910(void);
void fn_801D0470(int a);
void *fn_801D2BB0(int a, int size, int c, int d);
int ObjNewType_(int a, int size, int c, void (*pInit)(void *), void (*pRelease)(void *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(void *));
int ObjNewInList(int handle, int type, int a, void *pInit);
void ObjRemoveFromList(int handle, int item);
void VptTrashObject(int handle);
double fabs(double x);
int ResFindIndexByName(void *pData, char *pName);
void *fn_80216860(int handle, const char *pName);
void *fn_80216BFC(void *pNode, const char *pName);
void *fn_80216E34(void *pNode);
int fn_80216F3C(void *pNode, const char *pName, char *pOut, int size, const char *pDefault);
int fn_80217070(void *pNode, const char *pName, int value);
float fn_80227890(Vector_80039F5C *pA, float *pB);
float fn_802278D0(Divot *pA, Divot *pB);
void fn_80227930(float *pOut, float *pA, float *pB, float t);
int VptGetMatrixStack(void);
void VptFlushObjectTrashSync(void);
float fn_80237260(int stream);

void DivotRemove(Divot *p);
int DivotIsAreaFree(Divot *pDivot, float radius);
void DivotLoadVariants(void);
int DivotGetPoolSize(int type);
int DivotGetLevelResource(void);
Divot *DivotAlloc(int type);
unsigned char DivotPlace(Divot *p);
void DivotStepPlace(Divot *p);
void DivotStepRemove(Divot *p);
void DivotStepUpdate(Divot *p);
void DivotReleaseAll(void);
}

static int _Divot_aiPoolSize[DIVOT_NUM_TYPES] = { 130 };
static float _Divot_afRadius[DIVOT_NUM_TYPES] = { 0.2f };
static int _Divot_aiRandomCount[DIVOT_NUM_TYPES] = { 0 };
static unsigned char _Divot_bDraw = 1;
static int _FieldArrow_iListHandle = 0;
static unsigned int _FieldArrow_nCount = 0;

static int _Divot_aiActiveCount[DIVOT_NUM_TYPES];
static Divot *_Divot_apPool[DIVOT_NUM_TYPES];
static DivotRecord *_Divot_pRecords;
static int _Divot_iRecordCount;
static int _Divot_iNextIndex;
static DivotRecord *_Divot_pSavedRecords;
static int _Divot_iSavedActiveCount;
static int _Divot_iSavedNextIndex;

static int _Divot_aaiTextureRefs[DIVOT_NUM_TYPES][DIVOT_MAX_REFS];
static unsigned char _Divot_aaucSurfaceVariants[DIVOT_NUM_TYPES][DIVOT_NUM_SURFACES];
static unsigned char _Divot_aaucSurfaceFirstVariant[DIVOT_NUM_TYPES][DIVOT_NUM_SURFACES + 1];
static DivotFeet _Divot_aFeet[DIVOT_NUM_PLAYERS];
static unsigned char _Divot_aabSkipStep[DIVOT_NUM_PLAYERS][2];

static DivotHandlers _Divot_aHandlers[DIVOT_NUM_TYPES] = {
    { DivotStepPlace, DivotStepRemove, DivotStepUpdate },
};

static FieldArrow *_FieldArrow_apItems[FIELD_ARROW_MAX] = { 0 };

static char _PlaDynClut_aszColorNames[25][15] = {
    "HATC1", "HATC2", "EYEC1", "EYEC2", "SHIRTC1", "SHIRTC2", "SHIRTC3",
    "PANTSC1", "PANTSC2", "PANTSC3", "UPPERARMC1", "ELBOWC1", "HANDC1",
    "WRISTC1", "SOCKC1", "SOCKC2", "SHOEC1", "SHOEC2", "HAIRC1", "FHAIRC1",
    "TEAMC1", "TEAMC2", "TEAMC3", "NUMDECALC1", "NUMDECALC2",
};

static char _PlaDynClut_aszLevelNames[4][15] = {
    "PRIMARY", "SHADOW", "MIDTONE", "HIGHLIGHT",
};

extern "C" {
/* Linear map of x from [lo, hi] onto [vlo, vhi], clamped at both ends. */
float MathMapRangeClamped(float x, float hi, float vhi, float lo, float vlo)
{
    if (x > hi) {
        return vhi;
    }
    if (x < lo) {
        return vlo;
    }
    if (hi == lo) {
        return 0.0f;
    }
    return (x - lo) / (hi - lo) * (vhi - vlo) + vlo;
}

void DivotReplayWriteOne(Divot *p, BitStream_t *pStream)
{
    if (p->mType != DIVOT_TYPE_0) {
        fn_80030554(pStream, p->mScale, 6, 10.0f);
        fn_80191068(pStream, (unsigned int)(int)(p->mAlpha * 15.0f), 4);
    }
}

void DivotReplayReadOne(Divot *p, BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3,
                 float t)
{
    float scale1[3];
    float scale0[3];
    float alpha1;
    float alpha0;

    if (p->mType != DIVOT_TYPE_0) {
        if (pStream2) {
            ReadBitStream(pStream2, 22);
        }
        if (pStream3) {
            ReadBitStream(pStream3, 22);
        }
        fn_800301C4(pStream1, scale1, 6, 10.0f);
        fn_800301C4(pStream0, scale0, 6, 10.0f);
        fn_80227930(p->mScale, scale0, scale1, t);
        alpha1 = (float)ReadBitStream(pStream1, 4) * (1.0f / 15.0f);
        alpha0 = (float)ReadBitStream(pStream0, 4) * (1.0f / 15.0f);
        p->mAlpha = (alpha0 - alpha1) * t + alpha1;
    }
}

int DivotReplayGetSize(void)
{
    DivotGetPoolSize(0);
    return 31;
}

void DivotReplayWrite(BitStream_t *pStream)
{
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        Divot *p = _Divot_apPool[type];

        for (int n = DivotGetPoolSize(type); n > 0; n--) {
            DivotReplayWriteOne(p, pStream);
            p++;
        }
    }
    fn_80191068(pStream, _Divot_iRecordCount, 31);
}

void DivotReplayRead(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    int count0;
    int count1;
    int count;
    int active;
    int n;
    Divot *p;

    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        p = _Divot_apPool[type];
        for (n = DivotGetPoolSize(type); n > 0; n--) {
            DivotReplayReadOne(p, pStream0, pStream1, pStream2, pStream3, t);
            p++;
        }
    }
    if (pStream2) {
        ReadBitStream(pStream2, 31);
    }
    if (pStream3) {
        ReadBitStream(pStream3, 31);
    }
    count1 = ReadBitStream(pStream1, 31);
    count0 = ReadBitStream(pStream0, 31);
    count = (int)((float)(count0 - count1) * t + (float)count1);
    active = 0;
    p = _Divot_apPool[0];
    for (n = DivotGetPoolSize(0); n > 0; n--, p++) {
        p->mPos.mX = _Divot_pRecords[count - n].mPos[0];
        p->mPos.mY = _Divot_pRecords[count - n].mPos[1];
        p->mPos.mZ = _Divot_pRecords[count - n].mPos[2];
        p->mAngle = _Divot_pRecords[count - n].mAngle;
        p->mVariant = _Divot_pRecords[count - n].mVariant;
        p->mActive = _Divot_pRecords[count - n].mActive;
        if (p->mActive) {
            p->mScale[0] = 1.0f;
            p->mScale[1] = 1.0f;
            p->mScale[2] = 1.0f;
            p->mAlpha = 1.0f;
            p->mFlags = DIVOT_GROWN;
            active++;
            DivotRenderOnRefresh(p);
        }
    }
    _Divot_aiActiveCount[0] = active;
    _Divot_iNextIndex = 0;
}

void DivotRemove(Divot *p)
{
    _Divot_aHandlers[p->mType].mpRemove(p);
    DivotRenderOnRemove(p);
    p->mActive = 0;
    p->mFlags = 0;
    _Divot_aiActiveCount[p->mType]--;
    p->mScale[0] = 0.0f;
    p->mScale[1] = 0.0f;
    p->mScale[2] = 0.0f;
    p->mAlpha = 0.0f;
}

void DivotRelease(Divot *p)
{
    if (p->mType != DIVOT_TYPE_0) {
        p->mFlags = DIVOT_FADING;
        p->mTimer = 2.0f;
        p->mActive = 0;
    } else {
        DivotRemove(p);
    }
}

void DivotUpdateFading(Divot *p)
{
    if (p->mTimer > 0.0f) {
        p->mTimer -= 1.0f;
    } else {
        DivotRemove(p);
    }
}

void DivotFlushFading(void)
{
    fn_801CE910();
    for (float frame = 0.0f; frame < 2.0f; frame += 1.0f) {
        for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
            for (int i = 0; i < DivotGetPoolSize(type); i++) {
                if (_Divot_apPool[type][i].mFlags & DIVOT_FADING) {
                    DivotUpdateFading(&_Divot_apPool[type][i]);
                }
            }
        }
    }
}

void DivotStepRemove(Divot *p) {}

void DivotStepPlace(Divot *p)
{
    p->mActive = 0;
    if (_Divot_iRecordCount < DIVOT_MAX_RECORDS) {
        if (p->mpOwner == BallGetCurrentHolder() || fn_80237260(1) < 0.75f) {
            p->mAngle = (p->mAngle + 0xC00000) & 0xFFFFFF;
            p->mActive = 1;
            p->mAlpha = p->mAlphaMax;
            p->mScale[0] = p->mScaleMax[0];
            p->mScale[1] = p->mScaleMax[1];
            p->mScale[2] = p->mScaleMax[2];
            _Divot_iNextIndex = p->mIndex + 1;
            if (_Divot_iNextIndex >= DivotGetPoolSize(0)) {
                _Divot_iNextIndex = 0;
            }
            _Divot_pRecords[_Divot_iRecordCount].mPos[0] = p->mPos.mX;
            _Divot_pRecords[_Divot_iRecordCount].mPos[1] = p->mPos.mY;
            _Divot_pRecords[_Divot_iRecordCount].mPos[2] = p->mPos.mZ;
            _Divot_pRecords[_Divot_iRecordCount].mAngle = p->mAngle;
            _Divot_pRecords[_Divot_iRecordCount].mVariant = p->mVariant;
            _Divot_pRecords[_Divot_iRecordCount].mActive = p->mActive;
            _Divot_iRecordCount++;
        }
    }
}

void DivotStepUpdate(Divot *p) {}

int DivotIsAreaFree(Divot *pDivot, float radius)
{
    int free = 1;

    for (int type = 0; type < DIVOT_NUM_TYPES && free; type++) {
        if (type != DIVOT_TYPE_0) {
            float range = radius + _Divot_afRadius[type];
            Divot *p = _Divot_apPool[type];

            range *= range;
            for (int i = _Divot_aiPoolSize[type] - 1; i >= 0; i--, p++) {
                if (p->mActive && fn_802278D0(pDivot, p) < range) {
                    free = 0;
                    break;
                }
            }
        }
    }
    return free;
}

int DivotCheckPlacement(Divot *p)
{
    int ok = 1;

    if (p->mType != DIVOT_TYPE_0) {
        float margin = _Divot_afRadius[p->mType] + 1.0f;

        if (p->mPos.mX - margin < -fn_80178A08() || p->mPos.mX + margin > fn_80178A08() ||
            p->mPos.mY - margin < -fn_80178A44() || p->mPos.mY + margin > fn_80178A44()) {
            ok = 0;
        }
    }
    if (ok) {
        p->mActive = 0;
        ok = DivotIsAreaFree(p, _Divot_afRadius[p->mType]);
    }
    p->mActive = ok;
    return ok;
}

void DivotUpdateDecay(Divot *p)
{
    if (p->mType == DIVOT_TYPE_0) {
        return;
    }
    switch (p->mMode) {
    case DIVOT_MODE_2:
        break;
    case DIVOT_MODE_FADE:
        if (p->mFlags & DIVOT_GROWN) {
            p->mAlpha += -0.00007f;
            if (p->mAlpha <= 0.01f) {
                p->mAlpha = 0.01f;
                p->mFlags |= DIVOT_DONE;
            }
            p->mScale[2] += -0.00007f;
            if (p->mScale[2] <= 0.01f) {
                p->mScale[2] = 0.01f;
                p->mFlags |= DIVOT_DONE;
            }
        }
        break;
    case DIVOT_MODE_TIMED:
        if (p->mTimer <= 0.0f) {
            p->mFlags |= DIVOT_DONE;
        } else {
            p->mTimer -= 1.0f;
        }
        break;
    }
}

void DivotLoadVariants(void)
{
    int counts[DIVOT_NUM_TYPES];
    char name[32];
    void *pSurface;
    void *pDivot;

    for (int i = 0; i < DIVOT_NUM_TYPES; i++) {
        counts[i] = 0;
    }
    for (pSurface = fn_80216860(ResLoad(fn_800A336C(), fn_800A33A4(), 1), "surface"); pSurface;
         pSurface = fn_80216E34(pSurface)) {
        int surface = fn_80217070(pSurface, "surfType", DIVOT_SURFACE_NONE);

        for (pDivot = fn_80216BFC(pSurface, "divot"); pDivot; pDivot = fn_80216E34(pDivot)) {
            int type = fn_80217070(pDivot, "type", DIVOT_TYPE_1);
            int ref;

            fn_80216F3C(pDivot, "tideRef", name, 31, "");
            ref = ResFindIndexByName((void *)DivotGetLevelResource(), name);
            if (surface != DIVOT_SURFACE_NONE && type != DIVOT_TYPE_1 && ref != -1) {
                _Divot_aaucSurfaceVariants[type][surface]++;
                _Divot_aaiTextureRefs[type][counts[type]] = ref;
                counts[type]++;
            }
        }
    }
    ResUnLoad(fn_800A336C(), fn_800A33A4());
}

void DivotInit(void)
{
    int i;
    int type;
    int surface;
    unsigned char start;

    for (i = 0; i < DIVOT_NUM_TYPES; i++) {
        _Divot_aiActiveCount[i] = 0;
    }
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        _Divot_apPool[type] = (Divot *)fn_801D2BB0(1, DivotGetPoolSize(type) * sizeof(Divot), 0, 0);
        for (i = 0; i < DivotGetPoolSize(type); i++) {
            _Divot_apPool[type][i].mIndex = i;
            _Divot_apPool[type][i].mActive = 0;
            _Divot_apPool[type][i].mType = type;
            _Divot_apPool[type][i].mUnknown60 = 0;
            _Divot_apPool[type][i].mFlags = 0;
            _Divot_apPool[type][i].mScale[0] = 0.0f;
            _Divot_apPool[type][i].mScale[1] = 0.0f;
            _Divot_apPool[type][i].mScale[2] = 0.0f;
            _Divot_apPool[type][i].mAlpha = 0.0f;
            _Divot_apPool[type][i].mpOwner = 0;
        }
    }
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (surface = 0; surface < DIVOT_NUM_SURFACES; surface++) {
            _Divot_aaucSurfaceVariants[type][surface] = 0;
        }
    }
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (i = 0; i < DIVOT_MAX_REFS; i++) {
            _Divot_aaiTextureRefs[type][i] = -1;
        }
    }
    DivotLoadVariants();
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        start = 0;
        for (surface = 0; surface < DIVOT_NUM_SURFACES; surface++) {
            _Divot_aaucSurfaceFirstVariant[type][surface] = start;
            start += _Divot_aaucSurfaceVariants[type][surface];
        }
        _Divot_aaucSurfaceFirstVariant[type][surface] = start;
    }
    _Divot_pRecords = (DivotRecord *)fn_801D2BB0(64, DIVOT_MAX_RECORDS * sizeof(DivotRecord), 0, 0);
    _Divot_iRecordCount = 0;
    _Divot_iNextIndex = 0;
    _Divot_pSavedRecords = (DivotRecord *)fn_801D2BB0(1, DivotGetPoolSize(0) * sizeof(DivotRecord), 0, 0);
    for (i = 0; i < DIVOT_NUM_PLAYERS; i++) {
        _Divot_aFeet[i].mFoot0[0] = 0.0f;
        _Divot_aFeet[i].mFoot0[1] = 0.0f;
        _Divot_aFeet[i].mFoot1[0] = 0.0f;
        _Divot_aFeet[i].mFoot1[1] = 0.0f;
    }
    DivotRenderLoadAll();
}

void DivotShutdown(void)
{
    DivotReleaseAll();
    DivotFlushFading();
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        fn_801D2BD0(_Divot_apPool[type]);
        _Divot_apPool[type] = 0;
    }
    fn_801D2BD0(_Divot_pRecords);
    _Divot_pRecords = 0;
    fn_801D2BD0(_Divot_pSavedRecords);
    _Divot_pSavedRecords = 0;
    DivotRenderFreeAll();
}

void DivotScatterRandom(void)
{
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        float width = fn_80178A08() - _Divot_afRadius[type] - 1.0f;
        float length = fn_80178A44() - _Divot_afRadius[type] - 1.0f;

        for (int i = 0; i < _Divot_aiRandomCount[type]; i++) {
            Vector_80039F5C pos;
            LevelSurface_t *pArea;

            pos.mX = (fn_80237260(1) * 2.0f - 1.0f) * width;
            pos.mY = (fn_80237260(1) * 2.0f - 1.0f) * length;
            pos.mZ = 0.0f;
            pArea = LevelFindArea(&pos.mX);
            if (pArea) {
                Divot *p = DivotAlloc(type);

                if (p) {
                    p->mpOwner = 0;
                    p->mSurface = pArea->mSurface;
                    p->mPos = pos;
                    p->mAngle = (int)(fn_80237260(1) * 16777216.0f);
                    DivotPlace(p);
                }
            }
        }
    }
}


void DivotUpdate(void)
{
    if (fn_8002D060(lbl_803EA368) || InGameIsPaused()) {
        return;
    }
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (int i = 0; i < DivotGetPoolSize(type); i++) {
            Divot *p = &_Divot_apPool[type][i];

            if (p->mFlags & DIVOT_FADING) {
                DivotUpdateFading(p);
            } else if (p->mActive && !(p->mFlags & DIVOT_DONE)) {
                _Divot_aHandlers[type].mpUpdate(p);
                if (!(p->mFlags & DIVOT_GROWN)) {
                    if (!(p->mFlags & DIVOT_NO_GROW_CHECK) && p->mAlpha >= p->mAlphaMax &&
                        p->mScale[0] >= p->mScaleMax[0] && p->mScale[1] >= p->mScaleMax[1] &&
                        p->mScale[2] >= p->mScaleMax[2]) {
                        p->mFlags |= DIVOT_GROWN;
                    }
                    p->mAlpha = p->mAlpha + p->mAlphaRate > p->mAlphaMax ? p->mAlphaMax : p->mAlpha + p->mAlphaRate;
                    p->mScale[0] = p->mScale[0] + p->mScaleRate[0] > p->mScaleMax[0] ? p->mScaleMax[0]
                                                                                     : p->mScale[0] + p->mScaleRate[0];
                    p->mScale[1] = p->mScale[1] + p->mScaleRate[1] > p->mScaleMax[1] ? p->mScaleMax[1]
                                                                                     : p->mScale[1] + p->mScaleRate[1];
                    p->mScale[2] = p->mScale[2] + p->mScaleRate[2] > p->mScaleMax[2] ? p->mScaleMax[2]
                                                                                     : p->mScale[2] + p->mScaleRate[2];
                }
                DivotUpdateDecay(p);
            }
        }
    }
}

void DivotDraw(void)
{
    Divot *pPool;
    float alpha;
    int index;
    int i;

    if (_Divot_bDraw) {
        fn_801D0470(VptGetMatrixStack());
        DivotRenderBeginType(0);
        pPool = _Divot_apPool[0];
        alpha = 0.1f;
        index = _Divot_iNextIndex;
        i = 0;
        while (i < DivotGetPoolSize(0)) {
            pPool[index].mAlpha = alpha;
            if (pPool[index].mActive) {
                DivotRenderOnDraw(&pPool[index]);
            }
            if (++index >= DivotGetPoolSize(0)) {
                index = 0;
            }
            if ((++i & 7) == 0) {
                alpha += 0.1f;
                if (alpha > 1.0f) {
                    alpha = 1.0f;
                }
            }
        }
        DivotRenderEndType(0);
    }
}


void DivotReleaseAll(void)
{
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (int i = 0; i < DivotGetPoolSize(type); i++) {
            if (_Divot_apPool[type][i].mActive) {
                DivotRelease(&_Divot_apPool[type][i]);
            }
        }
    }
}

void DivotRestartRecords(void)
{
    Divot *pBase;
    Divot *p;
    int i;
    int j;

    for (i = 0; i < DIVOT_NUM_TYPES; i++) {
        pBase = _Divot_apPool[i];
        for (j = 0; j < DivotGetPoolSize(i); j++, pBase++) {
            if (pBase->mFlags & DIVOT_DONE) {
                DivotRelease(pBase);
            }
        }
    }
    i = _Divot_iNextIndex;
    pBase = _Divot_apPool[0];
    p = (Divot *)(i * sizeof(Divot) + (int)pBase);
    for (j = 0; j < DivotGetPoolSize(0); j++) {
        _Divot_pRecords[j].mPos[0] = p->mPos.mX;
        _Divot_pRecords[j].mPos[1] = p->mPos.mY;
        _Divot_pRecords[j].mPos[2] = p->mPos.mZ;
        _Divot_pRecords[j].mAngle = p->mAngle;
        _Divot_pRecords[j].mVariant = p->mVariant;
        _Divot_pRecords[j].mActive = p->mActive;
        p++;
        if (++i >= DivotGetPoolSize(0)) {
            p = pBase;
            i = 0;
        }
    }
    _Divot_iRecordCount = DivotGetPoolSize(0);
}

void DivotReplayRegister(void)
{
    fn_80030ACC(DivotReplayWrite, DivotReplayRead, DivotReplayGetSize(), "Divots");
}

void DivotSaveState(void)
{
    Divot *pPool = _Divot_apPool[0];

    for (int i = DivotGetPoolSize(0) - 1; i >= 0; i--) {
        Divot *p = &pPool[i];

        _Divot_pSavedRecords[i].mPos[0] = p->mPos.mX;
        _Divot_pSavedRecords[i].mPos[1] = p->mPos.mY;
        _Divot_pSavedRecords[i].mPos[2] = p->mPos.mZ;
        _Divot_pSavedRecords[i].mAngle = p->mAngle;
        _Divot_pSavedRecords[i].mVariant = p->mVariant;
        _Divot_pSavedRecords[i].mActive = p->mActive;
    }
    _Divot_iSavedActiveCount = _Divot_aiActiveCount[0];
    _Divot_iSavedNextIndex = _Divot_iNextIndex;
}

void DivotRestoreState(void)
{
    Divot *pPool = _Divot_apPool[0];

    for (int i = DivotGetPoolSize(0) - 1; i >= 0; i--) {
        Divot *p = &pPool[i];

        p->mPos.mX = _Divot_pSavedRecords[i].mPos[0];
        p->mPos.mY = _Divot_pSavedRecords[i].mPos[1];
        p->mPos.mZ = _Divot_pSavedRecords[i].mPos[2];
        p->mAngle = _Divot_pSavedRecords[i].mAngle;
        p->mVariant = _Divot_pSavedRecords[i].mVariant;
        p->mActive = _Divot_pSavedRecords[i].mActive;
        if (p->mActive) {
            DivotRenderOnRefresh(p);
        }
    }
    _Divot_aiActiveCount[0] = _Divot_iSavedActiveCount;
    _Divot_iNextIndex = _Divot_iSavedNextIndex;
}

int DivotGetPoolSize(int type)
{
    return _Divot_aiPoolSize[type];
}

int DivotGetVariantCount(int type)
{
    return _Divot_aaucSurfaceFirstVariant[type][DIVOT_NUM_SURFACES];
}

int DivotGetLevelResource(void)
{
    return (int)fn_800A336C();
}

int DivotGetTextureRef(int type, int i)
{
    return _Divot_aaiTextureRefs[type][i];
}

Divot *DivotAlloc(int type)
{
    Divot *p = 0;

    if (InGameIsPlaying() && !fn_8002D060(lbl_803EA368)) {
        if (_Divot_aiActiveCount[type] < DivotGetPoolSize(type)) {
            int n;

            p = _Divot_apPool[type];
            n = DivotGetPoolSize(type);
            while (--n >= 0) {
                if (!p->mActive && !(p->mFlags & DIVOT_FADING)) {
                    break;
                }
                p++;
            }
            if (n >= 0) {
                _Divot_aiActiveCount[type]++;
            } else {
                p = 0;
            }
        } else if (type == 0) {
            p = &_Divot_apPool[0][_Divot_iNextIndex];
        }
    }
    if (p != 0) {
        p->mType = type;
        p->mVariant = -1;
        p->mActive = 0;
        p->mMode = DIVOT_MODE_FADE;
        p->mTimer = 0.0f;
        p->mSurface = DIVOT_SURFACE_NONE;
        p->mFlags = 0;
        p->mpOwner = 0;
        p->mScale[0] = 0.0f;
        p->mScale[1] = 0.0f;
        p->mScale[2] = 0.0f;
        p->mScaleMax[0] = 1.0f;
        p->mScaleMax[1] = 1.0f;
        p->mScaleMax[2] = 1.0f;
        p->mScaleRate[0] = 1.0f;
        p->mScaleRate[1] = 1.0f;
        p->mScaleRate[2] = 1.0f;
        p->mAlpha = 0.0f;
        p->mAlphaMax = 1.0f;
        p->mAlphaRate = 1.0f;
        return p;
    }
    return 0;
}


unsigned char DivotPlace(Divot *p)
{
    if (p->mType != DIVOT_TYPE_0 && fn_801784C4()) {
        p->mPos.mX = -p->mPos.mX;
        p->mPos.mY = -p->mPos.mY;
        p->mAngle = (p->mAngle + 0x800000) & 0xFFFFFF;
    }
    if (_Divot_aaucSurfaceVariants[p->mType][p->mSurface] && DivotCheckPlacement(p)) {
        p->mVariant = fn_802372EC(1, _Divot_aaucSurfaceVariants[p->mType][p->mSurface]);
        p->mVariant += _Divot_aaucSurfaceFirstVariant[p->mType][p->mSurface];
        _Divot_aHandlers[p->mType].mpPlace(p);
        if (p->mActive) {
            DivotRenderOnPlace(p);
            if (!p->mActive) {
                _Divot_aHandlers[p->mType].mpRemove(p);
            }
        }
    } else {
        p->mActive = 0;
    }
    if (!p->mActive) {
        _Divot_aiActiveCount[p->mType]--;
    }
    return p->mActive;
}

void DivotOnMomentum(void *p, void *pState) {}

void DivotOnFootstep(Object_80039F5C *pPlayer, Vector_80039F5C *pPos, int foot0)
{
    Object_8003DEC4 *pBody;
    int slot;
    float *pLast;
    unsigned char *pSkip;

    if (pPos->mZ < 0.09f) {
        pBody = (Object_8003DEC4 *)pPlayer->mpUnknown4;
        slot = pBody->mUnknown4968 * 7 + pBody->mUnknown4969;
        if (foot0) {
            pLast = _Divot_aFeet[slot].mFoot0;
            pSkip = &_Divot_aabSkipStep[slot][0];
        } else {
            pLast = _Divot_aFeet[slot].mFoot1;
            pSkip = &_Divot_aabSkipStep[slot][1];
        }
        if (fn_80227890(pPos, pLast) >= 0.65f * 0.65f) {
            pLast[0] = pPos->mX;
            pLast[1] = pPos->mY;
            if (!PauseIsOpen()) {
                if (*pSkip == 0) {
                    AudmonEventPostId(0x58, pPos, pPlayer->mId, 0, 0, 0);
                } else {
                    *pSkip = 0;
                }
            }
            if (pBody->mUnknown972) {
                Divot *p = DivotAlloc(0);

                if (p) {
                    p->mpOwner = pPlayer;
                    p->mSurface = fn_800C4E18(pPlayer);
                    p->mPos.mX = pPos->mX;
                    p->mPos.mY = pPos->mY;
                    p->mPos.mZ = 0.0f;
                    p->mAngle = pBody->mUnknown36;
                    DivotPlace(p);
                }
            }
        }
    }
}

void DivotSkipNextSteps(Object_80039F5C *pPlayer)
{
    Object_8003DEC4 *pBody = (Object_8003DEC4 *)pPlayer->mpUnknown4;
    int slot = pBody->mUnknown4968 * 7 + pBody->mUnknown4969;

    _Divot_aabSkipStep[slot][0] = _Divot_aabSkipStep[slot][1] = 1;
}

void FieldArrowObjInit(void *p)
{
    char *pObject = (char *)p;

    ArrowInit(pObject + 0x14);
    ArrowSetPointBuffer(pObject + 0x14, pObject + 0x44, 2);
    pObject[0x5C] = 0;
}

void FieldArrowObjRelease(void *p)
{
    char *pObject = (char *)p;

    ArrowReset(pObject + 0x14);
    ArrowShutdown(pObject + 0x14);
    pObject[0x5C] = 0;
}

int FieldArrowObjDraw(void *p)
{
    char *pObject = (char *)p;

    if (pObject[0x5C]) {
        ArrowDraw(pObject + 0x14);
    }
    return 0;
}

/* Creates the _FieldArrow_nCount arrow objects in the list _FieldArrow_iListHandle. */
static void _FieldArrowCreateAll(void)
{
    for (unsigned int i = 0; i < _FieldArrow_nCount; i++) {
        _FieldArrow_apItems[i] = (FieldArrow *)ObjNewInList(_FieldArrow_iListHandle, 16, 0, 0);
    }
}

/* Removes and trashes every arrow object and clears the count. */
static void _FieldArrowDeleteAll(void)
{
    unsigned int i;

    for (i = 0; i < _FieldArrow_nCount; i++) {
        FieldArrow *p = _FieldArrow_apItems[i];

        ObjRemoveFromList(_FieldArrow_iListHandle, (int)p);
        VptTrashObject((int)p);
        _FieldArrow_apItems[i] = 0;
    }
    _FieldArrow_nCount = 0;
}

void FieldArrowAddObjType(void)
{
    ObjNewType_(16, 0x60, 40, FieldArrowObjInit, FieldArrowObjRelease);
    ObjSetListObjFunc(_FieldArrow_iListHandle, 16, 0, FieldArrowObjDraw);
}

void FieldArrowRemoveObjType(void)
{
    VptFlushObjectTrashSync();
    ObjDelType(16);
}

/* Creates one arrow object in the list _FieldArrow_iListHandle. */
static FieldArrow *_FieldArrowCreate(void)
{
    return (FieldArrow *)ObjNewInList(_FieldArrow_iListHandle, 16, 0, 0);
}

/* Removes one arrow object from the list and trashes it. */
static void _FieldArrowDelete(FieldArrow *p)
{
    ObjRemoveFromList(_FieldArrow_iListHandle, (int)p);
    VptTrashObject((int)p);
}

void FieldArrowInit(int handle)
{
    _FieldArrow_iListHandle = handle;
    FieldArrowAddObjType();
}

void FieldArrowShutdown(void)
{
    FieldArrowRemoveObjType();
    _FieldArrow_iListHandle = 0;
}

/* Replaces the arrow objects by count new ones, at most FIELD_ARROW_MAX. */
static void _FieldArrowSetCount(unsigned int count)
{
    _FieldArrowDeleteAll();
    if (count > FIELD_ARROW_MAX) {
        count = FIELD_ARROW_MAX;
    }
    _FieldArrow_nCount = count;
    _FieldArrowCreateAll();
}

/* Shows arrow index as a two-point path from pPos to length above it in y, with the given width
   and one of five colours. */
static void _FieldArrowSet(unsigned int index, Vector_80039F5C *pPos, float length, float width, int color)
{
    if (index < _FieldArrow_nCount) {
        FieldArrow *p = _FieldArrow_apItems[index];
        float y = pPos->mY;
        float top = y + length;
        float x = pPos->mX;
        float z = pPos->mZ;

        p->mPath.mCount = 0;
        p->mPath.mDashed = 0;
        p->mPoints[0].mX = x;
        p->mPoints[0].mY = y;
        p->mPoints[0].mZ = z;
        p->mPath.mpPoints[p->mPath.mCount] = p->mPoints[0];
        p->mPath.mCount++;
        p->mPoints[1].mX = x;
        p->mPath.mType = 0;
        p->mPath.mRadiusX = 0.0f;
        p->mPath.mRadiusY = 0.0f;
        p->mPath.mAngleOffset = 0;
        if ((float)fabs(y - top) < 0.1f) {
            p->mPath.mType = 4;
            p->mPath.mRadiusX = 0.0f;
            p->mPath.mRadiusY = 0.0f;
            p->mPath.mAngleOffset = 0;
        }
        p->mPoints[1].mY = top;
        p->mPoints[1].mZ = z;
        p->mPath.mpPoints[p->mPath.mCount] = p->mPoints[1];
        p->mPath.mCount++;
        p->mPath.mWidth = width;
        p->mPath.mEndWidth = 1.0f;
        p->mPath.mEndBrightness = 1.0f;
        switch (color) {
        case 0:
            p->mPath.mColor[0] = 2;
            p->mPath.mColor[1] = 130;
            p->mPath.mColor[2] = 0;
            break;
        case 1:
            p->mPath.mColor[0] = 0;
            p->mPath.mColor[1] = 0;
            p->mPath.mColor[2] = 255;
            break;
        case 2:
            p->mPath.mColor[0] = 183;
            p->mPath.mColor[1] = 176;
            p->mPath.mColor[2] = 0;
            break;
        case 3:
            p->mPath.mColor[0] = 181;
            p->mPath.mColor[1] = 0;
            p->mPath.mColor[2] = 0;
            break;
        case 4:
            p->mPath.mColor[0] = 221;
            p->mPath.mColor[1] = 221;
            p->mPath.mColor[2] = 221;
            break;
        }
        p->mVisible = 1;
    }
}

/* Hides arrow index. */
static void _FieldArrowHide(unsigned int index)
{
    if (index < _FieldArrow_nCount) {
        _FieldArrow_apItems[index]->mVisible = 0;
    }
}

unsigned char PlaDynClutFindColorName(void *pNode)
{
    char name[16];
    unsigned char color = 0xFF;

    if (fn_80216F3C(pNode, "colorname", name, 15, 0) > 0) {
        for (int i = 0; i < 25; i++) {
            if (fn_801C3214(name, _PlaDynClut_aszColorNames[i], 15) == 0) {
                color = i;
                break;
            }
        }
    }
    return color;
}

unsigned char PlaDynClutFindLevelName(void *pNode)
{
    char name[16];
    unsigned char level = 0;

    if (fn_80216F3C(pNode, "levelname", name, 15, 0) > 0) {
        for (int i = 0; i < 4; i++) {
            if (fn_801C3214(name, _PlaDynClut_aszLevelNames[i], 15) == 0) {
                level = i;
                break;
            }
        }
    }
    return level;
}

void PlaDynClutParseEntry(void *pNode, ColorEntry *pEntry)
{
    char text[16];
    char *pTo;

    text[0] = 0;
    pEntry->mColor = fn_80217070(pNode, "colornum", 0xFF);
    if (pEntry->mColor == 0xFF) {
        pEntry->mColor = PlaDynClutFindColorName(pNode);
    }
    pEntry->mLevel = fn_80217070(pNode, "level", 0xFF);
    if (pEntry->mLevel == 0xFF) {
        pEntry->mLevel = PlaDynClutFindLevelName(pNode);
    }
    fn_80216F3C(pNode, "range", text, 15, 0);
    if ((pTo = fn_801C3084(text, '-')) != 0) {
        *pTo = 0;
        pTo++;
    } else {
        pTo = text;
    }
    pEntry->mFrom = atoi(text);
    pEntry->mTo = atoi(pTo);
    fn_80216F3C(pNode, "type", text, 15, 0);
    if (fn_801C3214(text, "set", 15) == 0) {
        if (pEntry->mColor == 0xFF) {
            pEntry->mColor = fn_80217070(pNode, "palindex", 0xFF);
            pEntry->mMode = 1;
        } else {
            pEntry->mMode = 0;
        }
    } else if (fn_801C3214(text, "blendfrom", 15) == 0) {
        if (pEntry->mColor == 0xFF) {
            pEntry->mColor = fn_80217070(pNode, "palindex", 0xFF);
            pEntry->mMode = 5;
        } else {
            pEntry->mMode = 3;
        }
    } else if (fn_801C3214(text, "blendto", 15) == 0) {
        if (pEntry->mColor == 0xFF) {
            pEntry->mColor = fn_80217070(pNode, "palindex", 0xFF);
            pEntry->mMode = 6;
        } else {
            pEntry->mMode = 4;
        }
    } else if (fn_801C3214(text, "blend", 15) == 0) {
        pEntry->mMode = 2;
    } else if (fn_801C3214(text, "mult", 15) == 0) {
        pEntry->mMode = 7;
    }
    if (pEntry->mFrom > pEntry->mTo) {
        unsigned char from = pEntry->mFrom;

        pEntry->mFrom = pEntry->mTo;
        pEntry->mTo = from;
        if (pEntry->mMode == 4) {
            pEntry->mMode = 3;
        } else if (pEntry->mMode == 3) {
            pEntry->mMode = 4;
        } else if (pEntry->mMode == 6) {
            pEntry->mMode = 5;
        } else if (pEntry->mMode == 5) {
            pEntry->mMode = 6;
        }
    }
}
}
