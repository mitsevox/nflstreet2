/* A clamped linear map, then turf divots: a fixed pool of marks per divot
   type, placed where players step (fn_80044858) or at random (fn_80043DD8),
   grown and faded each frame, recorded for the instant replay under the
   channel name "Divots", and the per-surface variant tables read from the
   "surface"/"divot" data blocks. The file ends with the colour-entry parser
   used by the dynamic palette code that follows it. */
#include "game/DynClut_80044F20.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/bitstream.h"
#include "game/fn_80054138.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"
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
    DIVOT_MODE_TIMED
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
int fn_80028934(void);
int fn_8002894C(void);
int fn_8002D060(void *p);
void fn_8003F66C(void *p);
void fn_8003F6B0(void *p);
void fn_8003F6B4(void *p, void *pData, int a);
void fn_8003F744(void *p);
int fn_8006560C(void);
void fn_80067E3C(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
void *fn_800A336C(void);
int fn_800A33A4(void);
int fn_800C4E18(Object_80039F5C *pPlayer);
Object_80039F5C *fn_80137B40(void);
int fn_801784C4(void);
float fn_80178A08(void);
float fn_80178A44(void);
void fn_8019CBC0(void *p);
void fn_8019F9F0(void);
void fn_8019FA3C(void);
void fn_8019FA8C(Divot *p);
void fn_8019FAC8(Divot *p);
void fn_8019FB04(Divot *p);
void fn_8019FB40(Divot *p);
void fn_8019FB7C(int type);
void fn_8019FBB4(int type);
char *fn_801C3084(const char *pString, int c);
int fn_801C3214(const char *pA, const char *pB, int n);
int fn_801C333C(const char *pString);
void fn_801CE910(void);
void fn_801D0470(int a);
void *fn_801D2BB0(int a, int size, int c, int d);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(void *), void (*pRelease)(void *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(void *));
int fn_801F0A8C(void *pData, char *pName);
void *fn_80216860(int handle, const char *pName);
void *fn_80216BFC(void *pNode, const char *pName);
void *fn_80216E34(void *pNode);
int fn_80216F3C(void *pNode, const char *pName, char *pOut, int size, const char *pDefault);
int fn_80217070(void *pNode, const char *pName, int value);
float fn_80227890(Vector_80039F5C *pA, float *pB);
float fn_802278D0(Divot *pA, Divot *pB);
void fn_80227930(float *pOut, float *pA, float *pB, float t);
int fn_80228668(void);
void fn_80228E18(void);
float fn_80237260(int stream);

void fn_800433D4(Divot *p);
int fn_800436DC(Divot *pDivot, float radius);
void fn_80043954(void);
int fn_80044518(int type);
int fn_80044544(void);
Divot *fn_80044580(int type);
unsigned char fn_800446E0(Divot *p);
void fn_800435B4(Divot *p);
void fn_800435B0(Divot *p);
void fn_800436D8(Divot *p);
void fn_800441F0(void);
}

static int lbl_803EA494[DIVOT_NUM_TYPES] = { 130 };
static float lbl_803EA498[DIVOT_NUM_TYPES] = { 0.2f };
static int lbl_803EA49C[DIVOT_NUM_TYPES] = { 0 };
static unsigned char lbl_803EA4A0 = 1;
static int lbl_803EA4A4 = 0;

static int lbl_803EC790[DIVOT_NUM_TYPES];
static Divot *lbl_803EC794[DIVOT_NUM_TYPES];
static DivotRecord *lbl_803EC798;
static int lbl_803EC79C;
static int lbl_803EC7A0;
static DivotRecord *lbl_803EC7A4;
static int lbl_803EC7A8;
static int lbl_803EC7AC;

static int lbl_80307778[DIVOT_NUM_TYPES][DIVOT_MAX_REFS];
static unsigned char lbl_803077B8[DIVOT_NUM_TYPES][DIVOT_NUM_SURFACES];
static unsigned char lbl_803077C6[DIVOT_NUM_TYPES][DIVOT_NUM_SURFACES + 1];
static DivotFeet lbl_803077D8[DIVOT_NUM_PLAYERS];
static unsigned char lbl_803078B8[DIVOT_NUM_PLAYERS][2];

static DivotHandlers lbl_802CCF30[DIVOT_NUM_TYPES] = {
    { fn_800435B4, fn_800435B0, fn_800436D8 },
};

static char lbl_802CCFDC[25][15] = {
    "HATC1", "HATC2", "EYEC1", "EYEC2", "SHIRTC1", "SHIRTC2", "SHIRTC3",
    "PANTSC1", "PANTSC2", "PANTSC3", "UPPERARMC1", "ELBOWC1", "HANDC1",
    "WRISTC1", "SOCKC1", "SOCKC2", "SHOEC1", "SHOEC2", "HAIRC1", "FHAIRC1",
    "TEAMC1", "TEAMC2", "TEAMC3", "NUMDECALC1", "NUMDECALC2",
};

static char lbl_802CD153[4][15] = {
    "PRIMARY", "SHADOW", "MIDTONE", "HIGHLIGHT",
};

extern "C" {
/* Linear map of x from [lo, hi] onto [vlo, vhi], clamped at both ends. */
float fn_80042F54(float x, float hi, float vhi, float lo, float vlo)
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

void fn_80042FA8(Divot *p, BitStream_t *pStream)
{
    if (p->mType != DIVOT_TYPE_0) {
        fn_80030554(pStream, p->mScale, 6, 10.0f);
        fn_80191068(pStream, (unsigned int)(int)(p->mAlpha * 15.0f), 4);
    }
}

void fn_80043028(Divot *p, BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3,
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

int fn_80043130(void)
{
    fn_80044518(0);
    return 31;
}

void fn_80043158(BitStream_t *pStream)
{
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        Divot *p = lbl_803EC794[type];

        for (int n = fn_80044518(type); n > 0; n--) {
            fn_80042FA8(p, pStream);
            p++;
        }
    }
    fn_80191068(pStream, lbl_803EC79C, 31);
}

void fn_800431DC(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    int count0;
    int count1;
    int count;
    int active;
    int n;
    Divot *p;

    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        p = lbl_803EC794[type];
        for (n = fn_80044518(type); n > 0; n--) {
            fn_80043028(p, pStream0, pStream1, pStream2, pStream3, t);
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
    p = lbl_803EC794[0];
    for (n = fn_80044518(0); n > 0; n--, p++) {
        p->mPos.mX = lbl_803EC798[count - n].mPos[0];
        p->mPos.mY = lbl_803EC798[count - n].mPos[1];
        p->mPos.mZ = lbl_803EC798[count - n].mPos[2];
        p->mAngle = lbl_803EC798[count - n].mAngle;
        p->mVariant = lbl_803EC798[count - n].mVariant;
        p->mActive = lbl_803EC798[count - n].mActive;
        if (p->mActive) {
            p->mScale[0] = 1.0f;
            p->mScale[1] = 1.0f;
            p->mScale[2] = 1.0f;
            p->mAlpha = 1.0f;
            p->mFlags = DIVOT_GROWN;
            active++;
            fn_8019FB04(p);
        }
    }
    lbl_803EC790[0] = active;
    lbl_803EC7A0 = 0;
}

void fn_800433D4(Divot *p)
{
    lbl_802CCF30[p->mType].mpRemove(p);
    fn_8019FAC8(p);
    p->mActive = 0;
    p->mFlags = 0;
    lbl_803EC790[p->mType]--;
    p->mScale[0] = 0.0f;
    p->mScale[1] = 0.0f;
    p->mScale[2] = 0.0f;
    p->mAlpha = 0.0f;
}

void fn_80043464(Divot *p)
{
    if (p->mType != DIVOT_TYPE_0) {
        p->mFlags = DIVOT_FADING;
        p->mTimer = 2.0f;
        p->mActive = 0;
    } else {
        fn_800433D4(p);
    }
}

void fn_800434B0(Divot *p)
{
    if (p->mTimer > 0.0f) {
        p->mTimer -= 1.0f;
    } else {
        fn_800433D4(p);
    }
}

void fn_800434FC(void)
{
    fn_801CE910();
    for (float frame = 0.0f; frame < 2.0f; frame += 1.0f) {
        for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
            for (int i = 0; i < fn_80044518(type); i++) {
                if (lbl_803EC794[type][i].mFlags & DIVOT_FADING) {
                    fn_800434B0(&lbl_803EC794[type][i]);
                }
            }
        }
    }
}

void fn_800435B0(Divot *p) {}

void fn_800435B4(Divot *p)
{
    p->mActive = 0;
    if (lbl_803EC79C < DIVOT_MAX_RECORDS) {
        if (p->mpOwner == fn_80137B40() || fn_80237260(1) < 0.75f) {
            p->mAngle = (p->mAngle + 0xC00000) & 0xFFFFFF;
            p->mActive = 1;
            p->mAlpha = p->mAlphaMax;
            p->mScale[0] = p->mScaleMax[0];
            p->mScale[1] = p->mScaleMax[1];
            p->mScale[2] = p->mScaleMax[2];
            lbl_803EC7A0 = p->mIndex + 1;
            if (lbl_803EC7A0 >= fn_80044518(0)) {
                lbl_803EC7A0 = 0;
            }
            lbl_803EC798[lbl_803EC79C].mPos[0] = p->mPos.mX;
            lbl_803EC798[lbl_803EC79C].mPos[1] = p->mPos.mY;
            lbl_803EC798[lbl_803EC79C].mPos[2] = p->mPos.mZ;
            lbl_803EC798[lbl_803EC79C].mAngle = p->mAngle;
            lbl_803EC798[lbl_803EC79C].mVariant = p->mVariant;
            lbl_803EC798[lbl_803EC79C].mActive = p->mActive;
            lbl_803EC79C++;
        }
    }
}

void fn_800436D8(Divot *p) {}

int fn_800436DC(Divot *pDivot, float radius)
{
    int free = 1;

    for (int type = 0; type < DIVOT_NUM_TYPES && free; type++) {
        if (type != DIVOT_TYPE_0) {
            float range = radius + lbl_803EA498[type];
            Divot *p = lbl_803EC794[type];

            range *= range;
            for (int i = lbl_803EA494[type] - 1; i >= 0; i--, p++) {
                if (p->mActive && fn_802278D0(pDivot, p) < range) {
                    free = 0;
                    break;
                }
            }
        }
    }
    return free;
}

int fn_800437A8(Divot *p)
{
    int ok = 1;

    if (p->mType != DIVOT_TYPE_0) {
        float margin = lbl_803EA498[p->mType] + 1.0f;

        if (p->mPos.mX - margin < -fn_80178A08() || p->mPos.mX + margin > fn_80178A08() ||
            p->mPos.mY - margin < -fn_80178A44() || p->mPos.mY + margin > fn_80178A44()) {
            ok = 0;
        }
    }
    if (ok) {
        p->mActive = 0;
        ok = fn_800436DC(p, lbl_803EA498[p->mType]);
    }
    p->mActive = ok;
    return ok;
}

void fn_8004389C(Divot *p)
{
    if (p->mType == DIVOT_TYPE_0) {
        return;
    }
    switch (p->mMode) {
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

void fn_80043954(void)
{
    int counts[DIVOT_NUM_TYPES];
    char name[32];
    void *pSurface;
    void *pDivot;

    for (int i = 0; i < DIVOT_NUM_TYPES; i++) {
        counts[i] = 0;
    }
    for (pSurface = fn_80216860(fn_801EF390(fn_800A336C(), fn_800A33A4(), 1), "surface"); pSurface;
         pSurface = fn_80216E34(pSurface)) {
        int surface = fn_80217070(pSurface, "surfType", DIVOT_SURFACE_NONE);

        for (pDivot = fn_80216BFC(pSurface, "divot"); pDivot; pDivot = fn_80216E34(pDivot)) {
            int type = fn_80217070(pDivot, "type", DIVOT_TYPE_1);
            int ref;

            fn_80216F3C(pDivot, "tideRef", name, 31, "");
            ref = fn_801F0A8C((void *)fn_80044544(), name);
            if (surface != DIVOT_SURFACE_NONE && type != DIVOT_TYPE_1 && ref != -1) {
                lbl_803077B8[type][surface]++;
                lbl_80307778[type][counts[type]] = ref;
                counts[type]++;
            }
        }
    }
    fn_801F010C(fn_800A336C(), fn_800A33A4());
}

void fn_80043AE4(void)
{
    int i;
    int type;
    int surface;
    unsigned char start;

    for (i = 0; i < DIVOT_NUM_TYPES; i++) {
        lbl_803EC790[i] = 0;
    }
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        lbl_803EC794[type] = (Divot *)fn_801D2BB0(1, fn_80044518(type) * sizeof(Divot), 0, 0);
        for (i = 0; i < fn_80044518(type); i++) {
            lbl_803EC794[type][i].mIndex = i;
            lbl_803EC794[type][i].mActive = 0;
            lbl_803EC794[type][i].mType = type;
            lbl_803EC794[type][i].mUnknown60 = 0;
            lbl_803EC794[type][i].mFlags = 0;
            lbl_803EC794[type][i].mScale[0] = 0.0f;
            lbl_803EC794[type][i].mScale[1] = 0.0f;
            lbl_803EC794[type][i].mScale[2] = 0.0f;
            lbl_803EC794[type][i].mAlpha = 0.0f;
            lbl_803EC794[type][i].mpOwner = 0;
        }
    }
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (surface = 0; surface < DIVOT_NUM_SURFACES; surface++) {
            lbl_803077B8[type][surface] = 0;
        }
    }
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (i = 0; i < DIVOT_MAX_REFS; i++) {
            lbl_80307778[type][i] = -1;
        }
    }
    fn_80043954();
    for (type = 0; type < DIVOT_NUM_TYPES; type++) {
        start = 0;
        for (surface = 0; surface < DIVOT_NUM_SURFACES; surface++) {
            lbl_803077C6[type][surface] = start;
            start += lbl_803077B8[type][surface];
        }
        lbl_803077C6[type][surface] = start;
    }
    lbl_803EC798 = (DivotRecord *)fn_801D2BB0(64, DIVOT_MAX_RECORDS * sizeof(DivotRecord), 0, 0);
    lbl_803EC79C = 0;
    lbl_803EC7A0 = 0;
    lbl_803EC7A4 = (DivotRecord *)fn_801D2BB0(1, fn_80044518(0) * sizeof(DivotRecord), 0, 0);
    for (i = 0; i < DIVOT_NUM_PLAYERS; i++) {
        lbl_803077D8[i].mFoot0[0] = 0.0f;
        lbl_803077D8[i].mFoot0[1] = 0.0f;
        lbl_803077D8[i].mFoot1[0] = 0.0f;
        lbl_803077D8[i].mFoot1[1] = 0.0f;
    }
    fn_8019F9F0();
}

void fn_80043D68(void)
{
    fn_800441F0();
    fn_800434FC();
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        fn_801D2BD0(lbl_803EC794[type]);
        lbl_803EC794[type] = 0;
    }
    fn_801D2BD0(lbl_803EC798);
    lbl_803EC798 = 0;
    fn_801D2BD0(lbl_803EC7A4);
    lbl_803EC7A4 = 0;
    fn_8019FA3C();
}

void fn_80043DD8(void)
{
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        float width = fn_80178A08() - lbl_803EA498[type] - 1.0f;
        float length = fn_80178A44() - lbl_803EA498[type] - 1.0f;

        for (int i = 0; i < lbl_803EA49C[type]; i++) {
            Vector_80039F5C pos;
            Area_80054138 *pArea;

            pos.mX = (fn_80237260(1) * 2.0f - 1.0f) * width;
            pos.mY = (fn_80237260(1) * 2.0f - 1.0f) * length;
            pos.mZ = 0.0f;
            pArea = fn_80054138(&pos.mX);
            if (pArea) {
                Divot *p = fn_80044580(type);

                if (p) {
                    p->mpOwner = 0;
                    p->mSurface = pArea->mSurface;
                    p->mPos = pos;
                    p->mAngle = (int)(fn_80237260(1) * 16777216.0f);
                    fn_800446E0(p);
                }
            }
        }
    }
}


void fn_80043F50(void)
{
    if (fn_8002D060(lbl_803EA368) || fn_80028934()) {
        return;
    }
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (int i = 0; i < fn_80044518(type); i++) {
            Divot *p = &lbl_803EC794[type][i];

            if (p->mFlags & DIVOT_FADING) {
                fn_800434B0(p);
            } else if (p->mActive && !(p->mFlags & DIVOT_DONE)) {
                lbl_802CCF30[type].mpUpdate(p);
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
                fn_8004389C(p);
            }
        }
    }
}

void fn_80044114(void)
{
    Divot *pPool;
    float alpha;
    int index;
    int i;

    if (lbl_803EA4A0) {
        fn_801D0470(fn_80228668());
        fn_8019FB7C(0);
        pPool = lbl_803EC794[0];
        alpha = 0.1f;
        index = lbl_803EC7A0;
        i = 0;
        while (i < fn_80044518(0)) {
            pPool[index].mAlpha = alpha;
            if (pPool[index].mActive) {
                fn_8019FB40(&pPool[index]);
            }
            if (++index >= fn_80044518(0)) {
                index = 0;
            }
            if ((++i & 7) == 0) {
                alpha += 0.1f;
                if (alpha > 1.0f) {
                    alpha = 1.0f;
                }
            }
        }
        fn_8019FBB4(0);
    }
}


void fn_800441F0(void)
{
    for (int type = 0; type < DIVOT_NUM_TYPES; type++) {
        for (int i = 0; i < fn_80044518(type); i++) {
            if (lbl_803EC794[type][i].mActive) {
                fn_80043464(&lbl_803EC794[type][i]);
            }
        }
    }
}

void fn_80044264(void)
{
    Divot *pBase;
    Divot *p;
    int i;
    int j;

    for (i = 0; i < DIVOT_NUM_TYPES; i++) {
        pBase = lbl_803EC794[i];
        for (j = 0; j < fn_80044518(i); j++, pBase++) {
            if (pBase->mFlags & DIVOT_DONE) {
                fn_80043464(pBase);
            }
        }
    }
    i = lbl_803EC7A0;
    pBase = lbl_803EC794[0];
    p = &pBase[i];
    for (j = 0; j < fn_80044518(0); j++) {
        lbl_803EC798[j].mPos[0] = p->mPos.mX;
        lbl_803EC798[j].mPos[1] = p->mPos.mY;
        lbl_803EC798[j].mPos[2] = p->mPos.mZ;
        lbl_803EC798[j].mAngle = p->mAngle;
        lbl_803EC798[j].mVariant = p->mVariant;
        lbl_803EC798[j].mActive = p->mActive;
        p++;
        if (++i >= fn_80044518(0)) {
            p = pBase;
            i = 0;
        }
    }
    lbl_803EC79C = fn_80044518(0);
}

void fn_80044378(void)
{
    fn_80030ACC(fn_80043158, fn_800431DC, fn_80043130(), "Divots");
}

void fn_800443B8(void)
{
    Divot *pPool = lbl_803EC794[0];

    for (int i = fn_80044518(0) - 1; i >= 0; i--) {
        Divot *p = &pPool[i];

        lbl_803EC7A4[i].mPos[0] = p->mPos.mX;
        lbl_803EC7A4[i].mPos[1] = p->mPos.mY;
        lbl_803EC7A4[i].mPos[2] = p->mPos.mZ;
        lbl_803EC7A4[i].mAngle = p->mAngle;
        lbl_803EC7A4[i].mVariant = p->mVariant;
        lbl_803EC7A4[i].mActive = p->mActive;
    }
    lbl_803EC7A8 = lbl_803EC790[0];
    lbl_803EC7AC = lbl_803EC7A0;
}

void fn_80044460(void)
{
    Divot *pPool = lbl_803EC794[0];

    for (int i = fn_80044518(0) - 1; i >= 0; i--) {
        Divot *p = &pPool[i];

        p->mPos.mX = lbl_803EC7A4[i].mPos[0];
        p->mPos.mY = lbl_803EC7A4[i].mPos[1];
        p->mPos.mZ = lbl_803EC7A4[i].mPos[2];
        p->mAngle = lbl_803EC7A4[i].mAngle;
        p->mVariant = lbl_803EC7A4[i].mVariant;
        p->mActive = lbl_803EC7A4[i].mActive;
        if (p->mActive) {
            fn_8019FB04(p);
        }
    }
    lbl_803EC790[0] = lbl_803EC7A8;
    lbl_803EC7A0 = lbl_803EC7AC;
}

int fn_80044518(int type)
{
    return lbl_803EA494[type];
}

int fn_80044528(int type)
{
    return lbl_803077C6[type][DIVOT_NUM_SURFACES];
}

int fn_80044544(void)
{
    return (int)fn_800A336C();
}

int fn_80044564(int type, int i)
{
    return lbl_80307778[type][i];
}

Divot *fn_80044580(int type)
{
    Divot *p = 0;

    if (fn_8002894C() && !fn_8002D060(lbl_803EA368)) {
        if (lbl_803EC790[type] < fn_80044518(type)) {
            int n;

            p = lbl_803EC794[type];
            n = fn_80044518(type);
            while (--n >= 0) {
                if (!p->mActive && !(p->mFlags & DIVOT_FADING)) {
                    break;
                }
                p++;
            }
            if (n >= 0) {
                lbl_803EC790[type]++;
            } else {
                p = 0;
            }
        } else if (type == 0) {
            p = &lbl_803EC794[0][lbl_803EC7A0];
        }
    }
    if (p != 0) {
        p->mType = type;
        p->mVariant = -1;
        p->mActive = 0;
        p->mSurface = DIVOT_SURFACE_NONE;
        p->mpOwner = 0;
        p->mAlpha = 0.0f;
        p->mAlphaRate = 1.0f;
        p->mMode = DIVOT_MODE_FADE;
        p->mTimer = 0.0f;
        p->mFlags = 0;
        p->mScale[0] = 0.0f;
        p->mScale[1] = 0.0f;
        p->mScale[2] = 0.0f;
        p->mScaleMax[0] = 1.0f;
        p->mScaleMax[1] = 1.0f;
        p->mScaleMax[2] = 1.0f;
        p->mScaleRate[0] = 1.0f;
        p->mScaleRate[1] = 1.0f;
        p->mScaleRate[2] = 1.0f;
        p->mAlphaMax = 1.0f;
        return p;
    }
    return 0;
}


unsigned char fn_800446E0(Divot *p)
{
    if (p->mType != DIVOT_TYPE_0 && fn_801784C4()) {
        p->mPos.mX = -p->mPos.mX;
        p->mPos.mY = -p->mPos.mY;
        p->mAngle = (p->mAngle + 0x800000) & 0xFFFFFF;
    }
    if (lbl_803077B8[p->mType][p->mSurface] && fn_800437A8(p)) {
        p->mVariant = fn_802372EC(1, lbl_803077B8[p->mType][p->mSurface]);
        p->mVariant += lbl_803077C6[p->mType][p->mSurface];
        lbl_802CCF30[p->mType].mpPlace(p);
        if (p->mActive) {
            fn_8019FA8C(p);
            if (!p->mActive) {
                lbl_802CCF30[p->mType].mpRemove(p);
            }
        }
    } else {
        p->mActive = 0;
    }
    if (!p->mActive) {
        lbl_803EC790[p->mType]--;
    }
    return p->mActive;
}

void fn_80044854(void *p, void *pState) {}

void fn_80044858(Object_80039F5C *pPlayer, Vector_80039F5C *pPos, int foot0)
{
    Object_8003DEC4 *pBody;
    int slot;
    float *pLast;
    unsigned char *pSkip;

    if (pPos->mZ < 0.09f) {
        pBody = (Object_8003DEC4 *)pPlayer->mpUnknown4;
        slot = pBody->mUnknown4968 * 7 + pBody->mUnknown4969;
        if (foot0) {
            pLast = lbl_803077D8[slot].mFoot0;
            pSkip = &lbl_803078B8[slot][0];
        } else {
            pLast = lbl_803077D8[slot].mFoot1;
            pSkip = &lbl_803078B8[slot][1];
        }
        if (fn_80227890(pPos, pLast) >= 0.65f * 0.65f) {
            pLast[0] = pPos->mX;
            pLast[1] = pPos->mY;
            if (!fn_8006560C()) {
                if (*pSkip == 0) {
                    fn_80067E3C(0x58, pPos, pPlayer->mId, 0, 0, 0);
                } else {
                    *pSkip = 0;
                }
            }
            if (pBody->mUnknown972) {
                Divot *p = fn_80044580(0);

                if (p) {
                    p->mpOwner = pPlayer;
                    p->mSurface = fn_800C4E18(pPlayer);
                    p->mPos.mX = pPos->mX;
                    p->mPos.mY = pPos->mY;
                    p->mPos.mZ = 0.0f;
                    p->mAngle = pBody->mUnknown36;
                    fn_800446E0(p);
                }
            }
        }
    }
}

void fn_800449B4(Object_80039F5C *pPlayer)
{
    Object_8003DEC4 *pBody = (Object_8003DEC4 *)pPlayer->mpUnknown4;
    int slot = pBody->mUnknown4968 * 7 + pBody->mUnknown4969;

    lbl_803078B8[slot][0] = lbl_803078B8[slot][1] = 1;
}

void fn_800449EC(void *p)
{
    char *pObject = (char *)p;

    fn_8003F66C(pObject + 0x14);
    fn_8003F6B4(pObject + 0x14, pObject + 0x44, 2);
    pObject[0x5C] = 0;
}

void fn_80044A38(void *p)
{
    char *pObject = (char *)p;

    fn_8003F744(pObject + 0x14);
    fn_8003F6B0(pObject + 0x14);
    pObject[0x5C] = 0;
}

int fn_80044A7C(void *p)
{
    char *pObject = (char *)p;

    if (pObject[0x5C]) {
        fn_8019CBC0(pObject + 0x14);
    }
    return 0;
}

void fn_80044AB0(void)
{
    fn_801DCF0C(16, 0x60, 40, fn_800449EC, fn_80044A38);
    fn_801DD0C8(lbl_803EA4A4, 16, 0, fn_80044A7C);
}

void fn_80044B04(void)
{
    fn_80228E18();
    fn_801DCF8C(16);
}

void fn_80044B2C(int handle)
{
    lbl_803EA4A4 = handle;
    fn_80044AB0();
}

void fn_80044B50(void)
{
    fn_80044B04();
    lbl_803EA4A4 = 0;
}

unsigned char fn_80044B78(void *pNode)
{
    char name[16];
    unsigned char color = 0xFF;

    if (fn_80216F3C(pNode, "colorname", name, 15, 0) > 0) {
        for (int i = 0; i < 25; i++) {
            if (fn_801C3214(name, lbl_802CCFDC[i], 15) == 0) {
                color = i;
                break;
            }
        }
    }
    return color;
}

unsigned char fn_80044C00(void *pNode)
{
    char name[16];
    unsigned char level = 0;

    if (fn_80216F3C(pNode, "levelname", name, 15, 0) > 0) {
        for (int i = 0; i < 4; i++) {
            if (fn_801C3214(name, lbl_802CD153[i], 15) == 0) {
                level = i;
                break;
            }
        }
    }
    return level;
}

void fn_80044C88(void *pNode, ColorEntry *pEntry)
{
    char text[16];
    char *pTo;

    text[0] = 0;
    pEntry->mColor = fn_80217070(pNode, "colornum", 0xFF);
    if (pEntry->mColor == 0xFF) {
        pEntry->mColor = fn_80044B78(pNode);
    }
    pEntry->mLevel = fn_80217070(pNode, "level", 0xFF);
    if (pEntry->mLevel == 0xFF) {
        pEntry->mLevel = fn_80044C00(pNode);
    }
    fn_80216F3C(pNode, "range", text, 15, 0);
    if ((pTo = fn_801C3084(text, '-')) != 0) {
        *pTo = 0;
        pTo++;
    } else {
        pTo = text;
    }
    pEntry->mFrom = fn_801C333C(text);
    pEntry->mTo = fn_801C333C(pTo);
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
