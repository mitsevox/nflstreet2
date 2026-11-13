/* Level glows and player trails. The glows are the sprites placed in the level data, each with a
   preset chosen by name (junkyard, Bronx, rooftop and beach glows, blooms) and an on/off flicker
   that the environment object also fades by, plus the lens flare of the environment light with
   its ghost sprites. The trails are the coloured ribbons drawn behind four joints of each player
   body, and the afterimage that keeps two of the body's earlier poses for a while. */

#include "game/Glow.h"
#include "engine/viewport.h"
#include "game/LevelData.h"
#include "game/Object_8003DEC4.h"
#include "game/DbCursor.h"
#include "game/PaletteColor.h"

/* 0x38-byte glow entry of the level data list at +84 (count at +80): position, rotation, the index
   of its preset name in the name list at +36, the flicker mode and the flicker times. */
struct LevelGlow_t {
    Vector_80039F5C mUnknown0, mUnknownC;
    unsigned short mUnknown18;
    char mUnknown1A[12];
    unsigned short mUnknown26;
    float mUnknown28, mUnknown2C, mUnknown30, mUnknown34;
};

/* A glow preset: its main sprite, mode words and the values copied into a new Glow_t. */
struct GlowDesc_t {
    GlowElement_t mUnknown0;
    int mUnknown18, mUnknown1C, mUnknown20;
    float mUnknown24, mUnknown28, mUnknown2C, mUnknown30, mUnknown34, mUnknown38, mUnknown3C;
    unsigned char mUnknown40;
    char mUnknown41[3];
    float mUnknown44;
};
/* A ghost sprite preset: the sprite and its position on the line through the screen centre. */
struct GlowGhostDesc_t { GlowElement_t mUnknown0; float mUnknown18; };

/* A run of glows taken from the glow pool: count, capacity, first glow and an in-use flag. */
struct GlowGroup_t { unsigned int mUnknown0; int mUnknown4; Glow_t *mUnknown8; unsigned char mUnknownC; char mUnknownD[3]; };

extern "C" {
extern LevelData_t *gLevelData;
extern const Vector_80039F5C gParticleSys_vUp;
unsigned int fn_802372EC(int, unsigned int);
int fn_801C2FE4(const char *, const char *);
void *fn_801D2B7C(unsigned int, int, int);
void fn_801D2BD0(void *);
void MemFill(void *, unsigned int, int, int);
void fn_80197E64(void);
void fn_80197E68(void);
void fn_80197E6C(void *);
void fn_80197F84(void *);
void fn_80197FDC(void *, void *);
void EffectBlendBegin(void *, int);
void EffectBlendEnd(void *, int);
int fn_800A33B0(void);
int fn_800A33B8(void);
int fn_800A3420(void);
Vector_80039F5C *fn_800A3438(void);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0558(void);
void fn_801D0544(void);
void fn_801D0ADC(int);
void fn_801D09EC(int);
void fn_801D08FC(int);
void fn_801D12BC(int);
void fn_80227C2C(Vector_80039F5C *, Vector_80039F5C *);
void fn_80227D6C(Vector_80039F5C *, Vector_80039F5C *);
Glow_t *GlowCreate(int, GlowDesc_t *);
void GlowInitGroup(int, int);
void GlowAddGhost(Glow_t *, GlowGhostDesc_t *);
void FieldMarkerInitEffect(Glow_t *);
}

static int _Glow_aTextureIds[11] = { 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114 };
static GlowDesc_t _Glow_Bloom01Desc = { { 10, 9.5f, 0.59f, 0.95f, 0.97f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_Bloom02Desc = { { 10, 6.5f, 0.874f, 0.99f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_Bloom03Desc = { { 10, 4.5f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_Junkyard01Desc = { { 6, 7.0f, 1.0f, 1.0f, 1.0f, 1.0f }, 1, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_Junkyard02Desc = { { 6, 5.5f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_Junkyard03Desc = { { 6, 9.0f, 1.0f, 1.0f, 1.0f, 1.0f }, 1, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_Bronx02Desc = { { 7, 2.0f, 1.0f, 0.9f, 0.9f, 0.3f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_SpareEnvDesc = { { 0, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 0, 1, -550.0f, -2000.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowDesc_t _Glow_EnvFlareDesc = { { 1, 300.0f, 1.0f, 0.7f, 0.6f, 1.0f }, 0, 0, 1, -700.0f, -2000.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static GlowGhostDesc_t _Glow_EnvGhost0Desc = { { 2, 76.0f, 0.04f, 0.023f, 0.04f, 1.0f }, 1.71f };
static GlowGhostDesc_t _Glow_EnvGhost1Desc = { { 4, 37.0f, 0.046f, 0.08f, 0.08f, 1.0f }, 1.49f };
static GlowGhostDesc_t _Glow_EnvGhost2Desc = { { 2, 11.0f, 0.13f, 0.06f, 0.13f, 1.0f }, 0.62f };
static GlowGhostDesc_t _Glow_EnvGhost3Desc = { { 4, 40.0f, 0.092f, 0.031f, 0.085f, 1.0f }, 0.52f };
static GlowGhostDesc_t _Glow_EnvGhost4Desc = { { 3, 36.0f, 0.03f, 0.082f, 0.046f, 1.0f }, 0.42f };
static GlowGhostDesc_t _Glow_EnvGhost5Desc = { { 4, 30.0f, 0.164f, 0.12f, 0.12f, 1.0f }, 0.3f };
static GlowGhostDesc_t _Glow_EnvGhost6Desc = { { 3, 20.0f, 0.082f, 0.04f, 0.036f, 1.0f }, 0.2f };
static GlowGhostDesc_t _Glow_EnvGhost7Desc = { { 2, 60.0f, 0.092f, 0.04f, 0.04f, 1.0f }, -0.17f };
static GlowGhostDesc_t _Glow_EnvGhost8Desc = { { 3, 16.0f, 0.08f, 0.046f, 0.092f, 1.0f }, -0.32f };
static GlowGhostDesc_t _Glow_EnvGhost9Desc = { { 5, 150.0f, 0.125f, 0.125f, 0.125f, 1.0f }, -0.48f };
static GlowDesc_t _Glow_Rooftop01Desc = { { 6, 5.5f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static char _Glow_aPresetNames[11][24] = {
    "JUNKYARD_GLOW01", "JUNKYARD_GLOW02", "JUNKYARD_GLOW03", "BRONX_GLOW02", "ROOFTOP_GLOW01", "LEGE_GLOW02",
    "BEACH_GLOW01", "BLOOM01", "BLOOM02", "BLOOM03", "DIRECTIONAL",
};

static unsigned char _Glow_bActive = 0;
static GlowFlicker_t *_Glow_pFlickers = 0;
static unsigned int _Glow_nFlickers = 0;
static Glow_t *_Glow_pPool = 0;
static GlowElement_t *_Glow_pElementPool = 0;
static int _Glow_iNextElement = 0, _Glow_iNextGlow = 0;
static float _Glow_fScale = 1.0f;
static Glow_t *_Glow_pEnvFlare = 0;
static Glow_t *_Glow_apLevelGlows[40];
static GlowGroup_t _Glow_Group;
static GlowTexture_t _Glow_aTextures[11];

extern "C" {
void ParticleTrailStartFlash(ParticleTrailSet_t *pObject)
{
    pObject->mUnknown56C = 8.0f;
    pObject->mUnknown570 = 8.0f;
    pObject->mUnknown574 = 8.0f;
    pObject->mUnknown5A8 = 0;
    pObject->mUnknown5A4 = 1;
}
GlowElement_t *GlowAllocElement(void) { GlowElement_t *p = &_Glow_pElementPool[_Glow_iNextElement]; _Glow_iNextElement++; return p; }
void GlowFlickerInit(GlowFlicker_t *p, LevelGlow_t *q)
{
    p->mUnknown4 = 0; p->mUnknown0 = 2; p->mUnknown8 = q->mUnknown26;
    p->mUnknownC = q->mUnknown28; p->mUnknown10 = q->mUnknown2C;
    p->mUnknown14 = q->mUnknown30; p->mUnknown18 = q->mUnknown34;
    p->mUnknown1C = q->mUnknown28; p->mUnknown20 = q->mUnknown2C;
}
void GlowFlickerUpdate(GlowFlicker_t *p)
{
    if (p->mUnknown0 == 2) {
        if (!(p->mUnknown1C < p->mUnknown20)) {
            unsigned int range, base;
            p->mUnknown1C = 0.0f;
            if (p->mUnknown4 == 0) {
                p->mUnknown4 = 1;
                range = (unsigned int)((p->mUnknown18 - p->mUnknown14) * 100.0f);
                base = (unsigned int)(p->mUnknown14 * 100.0f);
            } else {
                p->mUnknown4 = 0;
                range = (unsigned int)((p->mUnknown10 - p->mUnknownC) * 100.0f);
                base = (unsigned int)(p->mUnknownC * 100.0f);
            }
            p->mUnknown20 = (float)(fn_802372EC(1, range) + base) * 0.01f;
        } else p->mUnknown1C += 0.01666666753590107f;
    }
}
unsigned int GlowFindPreset(const char *name)
{
    for (unsigned int i = 0; i <= 10; ++i) if (fn_801C2FE4(name, _Glow_aPresetNames[i]) == 0) return i;
    return 12;
}
GlowDesc_t *GlowGetPreset(const char *name)
{
    GlowDesc_t *p = 0;
    switch ((int)GlowFindPreset(name)) {
    case 0: p = &_Glow_Junkyard01Desc; break;
    case 2: p = &_Glow_Junkyard03Desc; break;
    case 4: p = &_Glow_Rooftop01Desc; break;
    case 3: case 5: p = &_Glow_Bronx02Desc; break;
    case 1: case 6: p = &_Glow_Junkyard02Desc; break;
    case 7: p = &_Glow_Bloom01Desc; break;
    case 8: p = &_Glow_Bloom02Desc; break;
    case 9: p = &_Glow_Bloom03Desc; break;
    case 10: break;
    }
    return p;
}
}
static inline void _GlowCreateEnvFlare(void)
{
    _Glow_pEnvFlare = GlowCreate(0, &_Glow_EnvFlareDesc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost0Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost1Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost2Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost3Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost4Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost5Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost6Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost7Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost8Desc);
    GlowAddGhost(_Glow_pEnvFlare, &_Glow_EnvGhost9Desc);
}
extern "C" {
void GlowInit(void *owner)
{
    Vector_80039F5C out;
    Vector_80039F5C v = gParticleSys_vUp;
    _Glow_pPool = (Glow_t *)fn_801D2B7C(7840, 0, 0);
    _Glow_pElementPool = (GlowElement_t *)fn_801D2B7C(960, 0, 0);
    _Glow_bActive = 1;
    MemFill(_Glow_pPool, 7840, 0, 1); MemFill(_Glow_pElementPool, 960, 0, 1);
    for (int i = 0; i < 11; ++i) {
        _Glow_aTextures[i].mUnknown0 = owner; _Glow_aTextures[i].mUnknown4 = _Glow_aTextureIds[i];
        _Glow_aTextures[i].mUnknownC = 0; _Glow_aTextures[i].mUnknown8 = 0;
    }
    for (unsigned int i = 0; i < 40; ++i) _Glow_apLevelGlows[i] = 0;
    GlowInitGroup(0, gLevelData->mUnknown80 + 17);
    _Glow_iNextElement = 0; _Glow_iNextGlow = 0; fn_80197E64(); _Glow_nFlickers = 0;
    if (fn_800A33B0()) {
        if (fn_800A3420() == 1) { if (fn_800A33B8() == 0) _GlowCreateEnvFlare(); }
        else if (fn_800A3420() == 2) { if (fn_800A33B8() == 0) _GlowCreateEnvFlare(); }
        if (_Glow_pEnvFlare) {
            _Glow_pEnvFlare->mUnknown18.mX = fn_800A3438()->mX;
            _Glow_pEnvFlare->mUnknown18.mY = fn_800A3438()->mY;
            _Glow_pEnvFlare->mUnknown18.mZ = fn_800A3438()->mZ;
        }
    }
    if (gLevelData->mUnknown80 != 0) {
        _Glow_pFlickers = (GlowFlicker_t *)fn_801D2B7C(gLevelData->mUnknown80 * 36, 0, 0);
        _Glow_nFlickers = gLevelData->mUnknown80;
        for (unsigned int i = 0; i < _Glow_nFlickers && i <= 39; ++i) {
            LevelGlow_t *input = &((LevelGlow_t *)gLevelData->mUnknown84)[i];
            GlowFlickerInit(&_Glow_pFlickers[i], input);
            GlowDesc_t *desc = GlowGetPreset(((char (*)[24])gLevelData->mUnknown36)[input->mUnknown18]);
            if (desc) {
                int angle[3];
                _Glow_apLevelGlows[i] = GlowCreate(0, desc);
                fn_801D0470(VptGetMatrixStack()); fn_801D04C4(); fn_801D0558();
                angle[0] = (int)(input->mUnknownC.mX * 46603.37890625f);
                angle[1] = (int)(input->mUnknownC.mY * 46603.37890625f);
                angle[2] = (int)((input->mUnknownC.mZ + 90.0f) * 46603.37890625f);
                fn_801D0ADC(-angle[2]); fn_801D09EC(-angle[1]); fn_801D08FC(-angle[0]);
                fn_80227C2C(&out, &v); fn_801D0544();
                _Glow_apLevelGlows[i]->mUnknown18.mX = input->mUnknown0.mX;
                _Glow_apLevelGlows[i]->mUnknown18.mY = input->mUnknown0.mY;
                _Glow_apLevelGlows[i]->mUnknown18.mZ = input->mUnknown0.mZ;
                _Glow_apLevelGlows[i]->mUnknown24.mX = out.mX;
                _Glow_apLevelGlows[i]->mUnknown24.mY = out.mY;
                _Glow_apLevelGlows[i]->mUnknown24.mZ = out.mZ;
            }
        }
    }
}
void GlowShutdown(void)
{
    fn_80197E68();
    for (unsigned int i = 0; i < 1; ++i) {
        (&_Glow_Group)[i].mUnknown0 = 0; (&_Glow_Group)[i].mUnknown4 = 0;
        (&_Glow_Group)[i].mUnknown8 = 0; (&_Glow_Group)[i].mUnknownC = 0;
    }
    GlowTexture_t *p = _Glow_aTextures;
    do {
        if (p->mUnknownC) { fn_80197F84(p); p->mUnknownC = 0; }
        ++p;
    } while (p <= &_Glow_aTextures[10]);
    _Glow_pEnvFlare = 0; fn_801D2BD0(_Glow_pPool); _Glow_pPool = 0;
    fn_801D2BD0(_Glow_pElementPool); _Glow_pElementPool = 0; _Glow_iNextElement = 0; _Glow_iNextGlow = 0;
    if (_Glow_pFlickers) fn_801D2BD0(_Glow_pFlickers);
    _Glow_pFlickers = 0; _Glow_nFlickers = 0; _Glow_bActive = 0;
}
void GlowAddGhost(Glow_t *p, GlowGhostDesc_t *q)
{
    GlowGhost_t *slot = &p->mUnknown3C[p->mUnknown36];
    slot->mUnknown0 = GlowAllocElement();
    slot->mUnknown0->mUnknown0 = q->mUnknown0.mUnknown0;
    slot->mUnknown0->mUnknown4 = q->mUnknown0.mUnknown4;
    slot->mUnknown0->mUnknown8 = q->mUnknown0.mUnknown8;
    slot->mUnknown0->mUnknownC = q->mUnknown0.mUnknownC;
    slot->mUnknown0->mUnknown10 = q->mUnknown0.mUnknown10;
    slot->mUnknown0->mUnknown14 = q->mUnknown0.mUnknown14;
    slot->mUnknown4 = q->mUnknown18;
    if (!_Glow_aTextures[q->mUnknown0.mUnknown0].mUnknownC) {
        fn_80197E6C(&_Glow_aTextures[q->mUnknown0.mUnknown0]);
        _Glow_aTextures[q->mUnknown0.mUnknown0].mUnknownC = 1;
    }
    ++p->mUnknown36;
}
void GlowTransformPoint(Vector_80039F5C *out, Vector_80039F5C *in)
{
    Vector_80039F5C v;
    fn_801D0470(VptGetMatrixStack()); fn_801D04C4(); fn_801D12BC(3);
    fn_80227D6C(&v, in); out->mX = v.mX; out->mY = v.mY; out->mZ = v.mZ; fn_801D0544();
}
int GlowIsOnScreen(Vector_80039F5C *p)
{
    if (p->mX > -1.0f && p->mX < 1.0f && p->mY > -1.0f && p->mY < 1.0f) return 1;
    return 0;
}
void GlowSetScale(float value) { _Glow_fScale = value; }
void GlowInitGroup(int index, int count)
{
    GlowGroup_t *p = &(&_Glow_Group)[index];
    if (!p->mUnknownC) {
        p->mUnknown0 = 0; p->mUnknownC = 1; p->mUnknown4 = count;
        p->mUnknown8 = &_Glow_pPool[_Glow_iNextGlow]; _Glow_iNextGlow += count;
    }
}
Glow_t *GlowCreate(int index, GlowDesc_t *q)
{
    GlowGroup_t *group = &(&_Glow_Group)[index];
    Glow_t *p = &group->mUnknown8[group->mUnknown0++];
    p->mUnknown0 = GlowAllocElement();
    p->mUnknown4 = q->mUnknown18; p->mUnknown8 = q->mUnknown1C;
    p->mUnknown4 = q->mUnknown18; p->mUnknownC = q->mUnknown20;
    p->mUnknown18.mX = q->mUnknown24; p->mUnknown18.mY = q->mUnknown28; p->mUnknown18.mZ = q->mUnknown2C;
    p->mUnknown24.mX = q->mUnknown30; p->mUnknown24.mY = q->mUnknown34; p->mUnknown24.mZ = q->mUnknown38;
    p->mUnknown30 = q->mUnknown3C; p->mUnknown34 = q->mUnknown40; p->mUnknown38 = q->mUnknown44;
    p->mUnknown0->mUnknown0 = q->mUnknown0.mUnknown0;
    p->mUnknown0->mUnknown4 = q->mUnknown0.mUnknown4; p->mUnknown0->mUnknown8 = q->mUnknown0.mUnknown8;
    p->mUnknown0->mUnknownC = q->mUnknown0.mUnknownC; p->mUnknown0->mUnknown10 = q->mUnknown0.mUnknown10;
    p->mUnknown0->mUnknown14 = q->mUnknown0.mUnknown14;
    if (!_Glow_aTextures[p->mUnknown0->mUnknown0].mUnknownC) {
        fn_80197E6C(&_Glow_aTextures[p->mUnknown0->mUnknown0]);
        _Glow_aTextures[p->mUnknown0->mUnknown0].mUnknownC = 1;
    }
    p->mUnknown36 = 0; p->mUnknown35 = 0; p->mUnknown10 = 1; p->mUnknown11 = 0; p->mUnknown14 = 0.0f;
    FieldMarkerInitEffect(p); return p;
}
/* The blend state a group draw opens and closes around its glows. */
struct EffectBlendScope_t {
    void Begin(int main) { EffectBlendBegin(this, main); }
    void Draw(Glow_t *p) { fn_80197FDC(this, p); }
    void End(int main) { EffectBlendEnd(this, main); }
};
void GlowDrawGroup(int index)
{
    GlowGroup_t *group = &(&_Glow_Group)[index];
    EffectBlendScope_t scope;
    scope.Begin(index == 0);
    for (unsigned short i = 0; i < group->mUnknown0; ++i) {
        Glow_t *p = &group->mUnknown8[i];
        if (p->mUnknown10) scope.Draw(p);
    }
    scope.End(index == 0);
}
GlowTexture_t *GlowGetTexture(int index) { return &_Glow_aTextures[index]; }
void GlowUpdateFlickers(void) { if (_Glow_pFlickers) for (unsigned int i = 0; i < _Glow_nFlickers; ++i) GlowFlickerUpdate(&_Glow_pFlickers[i]); }
int GlowGetFlickerState(unsigned int index) { if (_Glow_pFlickers && index < _Glow_nFlickers) return _Glow_pFlickers[index].mUnknown4; return 1; }
float GlowGetFlickerTime(unsigned int index) { if (_Glow_pFlickers && index < _Glow_nFlickers) return _Glow_pFlickers[index].mUnknown1C; return 0.0f; }
}
/* Three bytes that fn_800840A4 reads from the team's row; the first is the palette index of the
   team colour. */
struct TeamColorRow_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

extern "C" {
int fn_8003DEB4(void);
void fn_80083E1C(DbCursor *pObject, int a);
void fn_800840A4(DbCursor *pObject, void *pBuffer);
int fn_800A7EF4(unsigned char a);
int fn_800C8744(int team);
int GameTextGetPadPlayer(int a);
void fn_801D0424(void *p, float (*m)[4]);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(float (*m)[4]);
void fn_801D06D4(void *p);
void fn_801D0FB8(Vector_80039F5C *pOut);

}

static ParticleTrailColor_t _ParticleTrail_aColors[10] = {
    { 1.0f, 0.0f, 0.0f, 0.25f },
    { 0.0f, 0.0f, 1.0f, 0.25f },
    { 0.0f, 1.0f, 0.0f, 0.25f },
    { 1.0f, 0.8f, 0.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 1.0f, 1.0f, 1.0f, 0.25f },
    { 0.25f, 0.25f, 1.0f, 0.45f },
};

/* Eight colours, red through yellow, one per point of a trail drawn in the second style, read by
   the trail draw. */
extern "C" {
ParticleTrailColor_t gParticleTrail_aPointColors[8] = {
    { 1.0f, 0.0f, 0.0f, 0.4f },
    { 1.0f, 0.0f, 0.0f, 0.4f },
    { 1.0f, 0.59215f, 0.03137f, 0.4f },
    { 1.0f, 0.83137f, 0.04705f, 0.4f },
    { 1.0f, 0.91764f, 0.0549f, 0.4f },
    { 1.0f, 0.98882f, 0.05882f, 0.2f },
    { 1.0f, 0.98882f, 0.05882f, 0.2f },
    { 1.0f, 0.98882f, 0.05882f, 0.1f },
};
}

static unsigned char _ParticleTrail_bEnabled = 1;
static float _ParticleTrail_fTeamAlpha = 0.45f;

/* Maps x in x0..x1 linearly onto y0..y1. */
static inline float _ParticleTrailMapRange(float x, float x0, float x1, float y0, float y1)
{
    return (x - x0) * (y1 - y0) / (x1 - x0) + y0;
}

extern "C" {

float GlowGetFlickerDuration(unsigned int index)
{
    if (_Glow_pFlickers != 0 && index < _Glow_nFlickers) {
        return _Glow_pFlickers[index].mUnknown20;
    }
    return 0.0f;
}

void ParticleTrailGetJointPoint(Object_8003DEC4 *pObject, int index, Vector_80039F5C *pOut)
{
    fn_801D04C4();
    fn_801D06D4(pObject->mUnknown908);
    fn_801D0664(pObject->mUnknown44.mUnknown52[index]);
    fn_801D0FB8(pOut);
    fn_801D0544();
}

void ParticleTrailStartup(void)
{
    _ParticleTrail_bEnabled = 1;
}

void ParticleTrailShutdown(void)
{
}

void ParticleTrailInit(ParticleTrailSet_t *pObject)
{
    unsigned int i;

    pObject->mUnknown230 = 1.0f;
    pObject->mUnknown234 = 0;
    pObject->mUnknown238 = -1;
    pObject->mUnknown240 = _ParticleTrail_aColors[8];
    pObject->mUnknown23C = 0;
    pObject->mUnknown554 = 1;
    pObject->mUnknown558 = 0;
    pObject->mUnknown560 = 0;
    for (i = 0; i < 4; i++) {
        ParticleTrail_t *pTrail = &pObject->mTrails[i];

        pTrail->mCount = 0;
        pTrail->mHead = 7;
        pTrail->mToggle = 0;
        switch (i) {
        case 0:
            pTrail->mIndex[0] = 18;
            pTrail->mIndex[1] = 16;
            break;
        case 1:
            pTrail->mIndex[0] = 3;
            pTrail->mIndex[1] = 2;
            break;
        case 2:
            pTrail->mIndex[0] = 24;
            pTrail->mIndex[1] = 22;
            break;
        case 3:
            pTrail->mIndex[0] = 7;
            pTrail->mIndex[1] = 6;
            break;
        }
    }
}

void ParticleTrailUpdate(Object_8003DEC4 *pObject)
{
    ParticleTrailSet_t *pData = &pObject->mUnknown5188;
    unsigned int i;

    if (--pData->mUnknown55C < 0) {
        pData->mUnknown55C = 3;
        if (--pData->mUnknown554 < 0) {
            pData->mUnknown554 = 1;
        }
        fn_801D0424(pData->mUnknown260[pData->mUnknown554], pObject->mUnknown908);
        pData->mUnknown2E0[pData->mUnknown554] = *(ParticleTrailBodyPose_t *)pObject->mUnknown44.mUnknown48;
        (pData->mUnknown448 + pData->mUnknown554)->mX = pObject->mUnknown44.mUnknown8[0];
        (pData->mUnknown448 + pData->mUnknown554)->mY = pObject->mUnknown44.mUnknown8[1];
        (pData->mUnknown448 + pData->mUnknown554)->mZ = pObject->mUnknown44.mUnknown8[2];
        pData->mUnknown460[pData->mUnknown554] = pObject->mUnknown44.mUnknown32;
        pData->mUnknown468[pData->mUnknown554] = *(ParticleTrailSubPose_t *)pObject->mUnknown280.mUnknown256.mUnknown48;
        fn_801D0424(pData->mUnknown4D4[pData->mUnknown554], pObject->mUnknown44.mUnknown52[13]);
        if (pData->mUnknown560 == 0) {
            if (pData->mUnknown558 != 0) {
                pData->mUnknown558--;
            } else {
                pObject->mUnknown20 &= ~0x20000;
            }
        } else if (pData->mUnknown558 <= 1) {
            pData->mUnknown558++;
        }
    }

    if (fn_800A7EF4(pObject->mUnknown4968) == 0) {
        pData->mUnknown240 = _ParticleTrail_aColors[9];
    } else if (pData->mUnknown238 == -1) {
        pData->mUnknown240 = _ParticleTrail_aColors[8];
    } else {
        pData->mUnknown240 = _ParticleTrail_aColors[pData->mUnknown238];
    }

    if (pObject->mUnknown20 & 0x10000) {
        float count = pData->mUnknown234 + 1;

        if (count > 35.0f) {
            count = 35.0f;
        }
        pData->mUnknown234 = (unsigned int)count;
        pData->mUnknown230 = _ParticleTrailMapRange(pData->mUnknown234, 0.0f, 35.0f, 0.05f, 1.0f);
    } else if (pData->mUnknown234 != 0) {
        pObject->mUnknown20 |= 0x10000;
        pData->mUnknown234--;
        pData->mUnknown230 = _ParticleTrailMapRange(pData->mUnknown234, 0.0f, 35.0f, 0.05f, 1.0f);
    } else {
        pData->mUnknown234 = 0;
        pData->mUnknown230 = 0.0f;
    }

    for (i = 0; i < 4; i++) {
        ParticleTrail_t *pTrail = &pData->mTrails[i];

        if (pTrail->mCount < 8) {
            pTrail->mCount++;
        }
        ParticleTrailGetJointPoint(pObject, pTrail->mIndex[0], &pTrail->mSource[0]);
        ParticleTrailGetJointPoint(pObject, pTrail->mIndex[1], &pTrail->mSource[1]);
        if (--pTrail->mHead < 0) {
            pTrail->mHead = 7;
        }
        pTrail->mToggle = pTrail->mToggle == 1 ? 0 : 1;
        pTrail->mPoints[pTrail->mHead] = pTrail->mSource[pTrail->mToggle];
    }
}

void ParticleTrailStart(Object_8003DEC4 *pObject, int bit, unsigned int slot, unsigned char flag)
{
    ParticleTrailSet_t *pData = &pObject->mUnknown5188;
    int index;

    pObject->mUnknown20 |= 1 << bit;
    index = -1;
    if (slot <= 8) {
        index = GameTextGetPadPlayer(slot);
    }
    pData->mUnknown238 = index;
    pData->mUnknown23C = flag;
}

void ParticleTrailResetAll(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        Object_8003DEC4 *pObject = fn_8003DEC4(i);
        ParticleTrailSet_t *pData = &pObject->mUnknown5188;
        ParticleTrail_t *pTrail;
        int j;

        pData->mUnknown230 = 1.0f;
        pData->mUnknown234 = 0;
        pData->mUnknown238 = -1;
        pData->mUnknown240 = _ParticleTrail_aColors[8];
        pData->mUnknown554 = 1;
        pData->mUnknown558 = 0;
        pData->mUnknown560 = 0;
        pTrail = pData->mTrails;
        for (j = 0; j < 4; j++) {
            pTrail->mCount = 0;
            pTrail->mHead = 7;
            pTrail->mToggle = 0;
            pTrail++;
        }
    }
}

void ParticleTrailSetTeamColor(Object_80039F5C *pPlayer)
{
    DbCursor cursor;
    TeamColorRow_t row;
    PaletteColor color;
    Object_8003DEC4 *pObject = (Object_8003DEC4 *)pPlayer->mpUnknown4;
    int id = fn_800C8744(pPlayer->mIdBytes[2]);

    fn_80083E1C(&cursor, 0);
    fn_80084034(&cursor, id, 0);
    fn_800840A4(&cursor, &row);
    fn_80083F68(&cursor);
    DbColPalGetPrimaryColor(row.mUnknown0, &color);
    pObject->mUnknown5188.mUnknown250.mUnknown0 = color.r / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknown4 = color.g / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknown8 = color.b / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknownC = _ParticleTrail_fTeamAlpha;
}

void ParticleTrailStartAfterimage(Object_8003DEC4 *pObject)
{
    if (pObject->mUnknown5188.mUnknown560 == 0) {
        pObject->mUnknown20 |= 0x20000;
        pObject->mUnknown5188.mUnknown560 = 1;
        pObject->mUnknown5188.mUnknown558 = 1;
        pObject->mUnknown5188.mUnknown55C = 3;
        pObject->mUnknown5188.mUnknown564 = 0.0f;
    } else {
        pObject->mUnknown5188.mUnknown564 = 0.0f;
    }
}

void ParticleTrailStopAfterimage(Object_8003DEC4 *pObject)
{
    pObject->mUnknown5188.mUnknown560 = 0;
    pObject->mUnknown5188.mUnknown558 = 0;
    pObject->mUnknown20 &= ~0x20000;
}

void ParticleTrailUpdateAfterimage(Object_8003DEC4 *pObject, float step)
{
    if (pObject->mUnknown5188.mUnknown560 == 1) {
        pObject->mUnknown5188.mUnknown564 += step;
        if (pObject->mUnknown5188.mUnknown564 >= 30.0f) {
            ParticleTrailStopAfterimage(pObject);
        }
    }
}

void ParticleTrailUpdateAll(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        ParticleTrailUpdate(fn_8003DEC4(i));
    }
}

unsigned char ParticleTrailSetEnabled(unsigned char a)
{
    unsigned char previous = _ParticleTrail_bEnabled;

    _ParticleTrail_bEnabled = a;
    return previous;
}

unsigned char ParticleTrailIsEnabled(void)
{
    return _ParticleTrail_bEnabled;
}

}
