#include "game/Effects_80146134.h"
#include "engine/viewport.h"
#include "game/Record_803EB25C.h"
#include "game/Object_8003DEC4.h"
#include "game/DbCursor.h"
#include "game/PaletteColor.h"

/* Local access views. Preset and input identities remain unknown. */

struct Input_80146150 {
    Vector_80146134 mUnknown0, mUnknownC;
    unsigned short mUnknown18;
    char mUnknown1A[12];
    unsigned short mUnknown26;
    float mUnknown28, mUnknown2C, mUnknown30, mUnknown34;
};
struct Config_803EA554 {
    char mUnknown0[0x24];
    char (*mUnknown24)[24];
    char mUnknown28[0x28];
    unsigned int mUnknown50;
    Input_80146150 *mUnknown54;
};

struct Description_801463D8 {
    Subrecord_80146134 mUnknown0;
    int mUnknown18, mUnknown1C, mUnknown20;
    float mUnknown24, mUnknown28, mUnknown2C, mUnknown30, mUnknown34, mUnknown38, mUnknown3C;
    unsigned char mUnknown40;
    char mUnknown41[3];
    float mUnknown44;
};
struct SlotDescription_80146A6C { Subrecord_80146134 mUnknown0; float mUnknown18; };


struct Group_80146C00 { unsigned int mUnknown0; int mUnknown4; Entry_80146C4C *mUnknown8; unsigned char mUnknownC; char mUnknownD[3]; };


extern "C" {
struct LevelData_t;
extern LevelData_t *gLevelData;
extern Vector_80146134 gParticleSys_vUp;
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
Vector_80146134 *fn_800A3438(void);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0558(void);
void fn_801D0544(void);
void fn_801D0ADC(int);
void fn_801D09EC(int);
void fn_801D08FC(int);
void fn_801D12BC(int);
void fn_80227C2C(Vector_80146134 *, Vector_80146134 *);
void fn_80227D6C(Vector_80146134 *, Vector_80146134 *);
Entry_80146C4C *fn_80146C4C(int, Description_801463D8 *);
void fn_80146C00(int, int);
void fn_80146A6C(Entry_80146C4C *, SlotDescription_80146A6C *);
void FieldMarkerInitEffect(Entry_80146C4C *);
}

static int lbl_802DD170[11] = { 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114 };
static Description_801463D8 lbl_802DD19C = { { 10, 9.5f, 0.59f, 0.95f, 0.97f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD1E4 = { { 10, 6.5f, 0.874f, 0.99f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD22C = { { 10, 4.5f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD274 = { { 6, 7.0f, 1.0f, 1.0f, 1.0f, 1.0f }, 1, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD2BC = { { 6, 5.5f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD304 = { { 6, 9.0f, 1.0f, 1.0f, 1.0f, 1.0f }, 1, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD34C = { { 7, 2.0f, 1.0f, 0.9f, 0.9f, 0.3f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD394 = { { 0, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 0, 1, -550.0f, -2000.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static Description_801463D8 lbl_802DD3DC = { { 1, 300.0f, 1.0f, 0.7f, 0.6f, 1.0f }, 0, 0, 1, -700.0f, -2000.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static SlotDescription_80146A6C lbl_802DD424 = { { 2, 76.0f, 0.04f, 0.023f, 0.04f, 1.0f }, 1.71f };
static SlotDescription_80146A6C lbl_802DD440 = { { 4, 37.0f, 0.046f, 0.08f, 0.08f, 1.0f }, 1.49f };
static SlotDescription_80146A6C lbl_802DD45C = { { 2, 11.0f, 0.13f, 0.06f, 0.13f, 1.0f }, 0.62f };
static SlotDescription_80146A6C lbl_802DD478 = { { 4, 40.0f, 0.092f, 0.031f, 0.085f, 1.0f }, 0.52f };
static SlotDescription_80146A6C lbl_802DD494 = { { 3, 36.0f, 0.03f, 0.082f, 0.046f, 1.0f }, 0.42f };
static SlotDescription_80146A6C lbl_802DD4B0 = { { 4, 30.0f, 0.164f, 0.12f, 0.12f, 1.0f }, 0.3f };
static SlotDescription_80146A6C lbl_802DD4CC = { { 3, 20.0f, 0.082f, 0.04f, 0.036f, 1.0f }, 0.2f };
static SlotDescription_80146A6C lbl_802DD4E8 = { { 2, 60.0f, 0.092f, 0.04f, 0.04f, 1.0f }, -0.17f };
static SlotDescription_80146A6C lbl_802DD504 = { { 3, 16.0f, 0.08f, 0.046f, 0.092f, 1.0f }, -0.32f };
static SlotDescription_80146A6C lbl_802DD520 = { { 5, 150.0f, 0.125f, 0.125f, 0.125f, 1.0f }, -0.48f };
static Description_801463D8 lbl_802DD53C = { { 6, 5.5f, 1.0f, 1.0f, 1.0f, 1.0f }, 0, 1, 2, 108.0f, -22.0f, 70.0f, 1.0f, 0.0f, 0.0f, 0.042f, 4, {0}, 0.1f };
static char lbl_802DD584[11][24] = {
    "JUNKYARD_GLOW01", "JUNKYARD_GLOW02", "JUNKYARD_GLOW03", "BRONX_GLOW02", "ROOFTOP_GLOW01", "LEGE_GLOW02",
    "BEACH_GLOW01", "BLOOM01", "BLOOM02", "BLOOM03", "DIRECTIONAL",
};

static unsigned char lbl_803EB258 = 0;
extern "C" { Record_803EB25C *lbl_803EB25C = 0; unsigned int lbl_803EB260 = 0; }
static Entry_80146C4C *lbl_803EB264 = 0;
static Subrecord_80146134 *lbl_803EB268 = 0;
static int lbl_803EB26C = 0, lbl_803EB270 = 0;
static float lbl_803EB274 = 1.0f;
static Entry_80146C4C *lbl_803EB278 = 0;
static Entry_80146C4C *lbl_8031B7DC[40];
static Group_80146C00 lbl_8031B87C; /* Only group zero storage established here. */
static Resource_80146E64 lbl_8031B88C[11];

extern "C" {
void ParticleTrailStartFlash(ParticleTrailSet_t *pObject)
{
    pObject->mUnknown56C = 8.0f;
    pObject->mUnknown570 = 8.0f;
    pObject->mUnknown574 = 8.0f;
    pObject->mUnknown5A8 = 0;
    pObject->mUnknown5A4 = 1;
}
Subrecord_80146134 *fn_80146134(void) { Subrecord_80146134 *p = &lbl_803EB268[lbl_803EB26C]; lbl_803EB26C++; return p; }
void fn_80146150(Record_803EB25C *p, Input_80146150 *q)
{
    p->mUnknown4 = 0; p->mUnknown0 = 2; p->mUnknown8 = q->mUnknown26;
    p->mUnknownC = q->mUnknown28; p->mUnknown10 = q->mUnknown2C;
    p->mUnknown14 = q->mUnknown30; p->mUnknown18 = q->mUnknown34;
    p->mUnknown1C = q->mUnknown28; p->mUnknown20 = q->mUnknown2C;
}
void fn_8014619C(Record_803EB25C *p)
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
unsigned int fn_80146374(const char *name)
{
    for (unsigned int i = 0; i <= 10; ++i) if (fn_801C2FE4(name, lbl_802DD584[i]) == 0) return i;
    return 12;
}
Description_801463D8 *fn_801463D8(const char *name)
{
    Description_801463D8 *p = 0;
    switch ((int)fn_80146374(name)) {
    case 0: p = &lbl_802DD274; break;
    case 2: p = &lbl_802DD304; break;
    case 4: p = &lbl_802DD53C; break;
    case 3: case 5: p = &lbl_802DD34C; break;
    case 1: case 6: p = &lbl_802DD2BC; break;
    case 7: p = &lbl_802DD19C; break;
    case 8: p = &lbl_802DD1E4; break;
    case 9: p = &lbl_802DD22C; break;
    case 10: break;
    }
    return p;
}
}
static inline void InitializeSpecial(void)
{
    lbl_803EB278 = fn_80146C4C(0, &lbl_802DD3DC);
    fn_80146A6C(lbl_803EB278, &lbl_802DD424);
    fn_80146A6C(lbl_803EB278, &lbl_802DD440);
    fn_80146A6C(lbl_803EB278, &lbl_802DD45C);
    fn_80146A6C(lbl_803EB278, &lbl_802DD478);
    fn_80146A6C(lbl_803EB278, &lbl_802DD494);
    fn_80146A6C(lbl_803EB278, &lbl_802DD4B0);
    fn_80146A6C(lbl_803EB278, &lbl_802DD4CC);
    fn_80146A6C(lbl_803EB278, &lbl_802DD4E8);
    fn_80146A6C(lbl_803EB278, &lbl_802DD504);
    fn_80146A6C(lbl_803EB278, &lbl_802DD520);
}
extern "C" {
void fn_801464D0(void *owner)
{
    Vector_80146134 out;
    Vector_80146134 v = gParticleSys_vUp;
    lbl_803EB264 = (Entry_80146C4C *)fn_801D2B7C(7840, 0, 0);
    lbl_803EB268 = (Subrecord_80146134 *)fn_801D2B7C(960, 0, 0);
    lbl_803EB258 = 1;
    MemFill(lbl_803EB264, 7840, 0, 1); MemFill(lbl_803EB268, 960, 0, 1);
    for (int i = 0; i < 11; ++i) {
        lbl_8031B88C[i].mUnknown0 = owner; lbl_8031B88C[i].mUnknown4 = lbl_802DD170[i];
        lbl_8031B88C[i].mUnknownC = 0; lbl_8031B88C[i].mUnknown8 = 0;
    }
    for (unsigned int i = 0; i < 40; ++i) lbl_8031B7DC[i] = 0;
    fn_80146C00(0, ((Config_803EA554 *)gLevelData)->mUnknown50 + 17);
    lbl_803EB26C = 0; lbl_803EB270 = 0; fn_80197E64(); lbl_803EB260 = 0;
    if (fn_800A33B0()) {
        if (fn_800A3420() == 1) { if (fn_800A33B8() == 0) InitializeSpecial(); }
        else if (fn_800A3420() == 2) { if (fn_800A33B8() == 0) InitializeSpecial(); }
        if (lbl_803EB278) {
            lbl_803EB278->mUnknown18.x = fn_800A3438()->x;
            lbl_803EB278->mUnknown18.y = fn_800A3438()->y;
            lbl_803EB278->mUnknown18.z = fn_800A3438()->z;
        }
    }
    if (((Config_803EA554 *)gLevelData)->mUnknown50 != 0) {
        lbl_803EB25C = (Record_803EB25C *)fn_801D2B7C(((Config_803EA554 *)gLevelData)->mUnknown50 * 36, 0, 0);
        lbl_803EB260 = ((Config_803EA554 *)gLevelData)->mUnknown50;
        for (unsigned int i = 0; i < lbl_803EB260 && i <= 39; ++i) {
            Input_80146150 *input = &((Config_803EA554 *)gLevelData)->mUnknown54[i];
            fn_80146150(&lbl_803EB25C[i], input);
            Description_801463D8 *desc = fn_801463D8(((Config_803EA554 *)gLevelData)->mUnknown24[input->mUnknown18]);
            if (desc) {
                int angle[3];
                lbl_8031B7DC[i] = fn_80146C4C(0, desc);
                fn_801D0470(VptGetMatrixStack()); fn_801D04C4(); fn_801D0558();
                angle[0] = (int)(input->mUnknownC.x * 46603.37890625f);
                angle[1] = (int)(input->mUnknownC.y * 46603.37890625f);
                angle[2] = (int)((input->mUnknownC.z + 90.0f) * 46603.37890625f);
                fn_801D0ADC(-angle[2]); fn_801D09EC(-angle[1]); fn_801D08FC(-angle[0]);
                fn_80227C2C(&out, &v); fn_801D0544();
                lbl_8031B7DC[i]->mUnknown18.x = input->mUnknown0.x;
                lbl_8031B7DC[i]->mUnknown18.y = input->mUnknown0.y;
                lbl_8031B7DC[i]->mUnknown18.z = input->mUnknown0.z;
                lbl_8031B7DC[i]->mUnknown24.x = out.x;
                lbl_8031B7DC[i]->mUnknown24.y = out.y;
                lbl_8031B7DC[i]->mUnknown24.z = out.z;
            }
        }
    }
}
void fn_801469A0(void)
{
    fn_80197E68();
    for (unsigned int i = 0; i < 1; ++i) {
        (&lbl_8031B87C)[i].mUnknown0 = 0; (&lbl_8031B87C)[i].mUnknown4 = 0;
        (&lbl_8031B87C)[i].mUnknown8 = 0; (&lbl_8031B87C)[i].mUnknownC = 0;
    }
    Resource_80146E64 *p = lbl_8031B88C;
    do {
        if (p->mUnknownC) { fn_80197F84(p); p->mUnknownC = 0; }
        ++p;
    } while (p <= &lbl_8031B88C[10]);
    lbl_803EB278 = 0; fn_801D2BD0(lbl_803EB264); lbl_803EB264 = 0;
    fn_801D2BD0(lbl_803EB268); lbl_803EB268 = 0; lbl_803EB26C = 0; lbl_803EB270 = 0;
    if (lbl_803EB25C) fn_801D2BD0(lbl_803EB25C);
    lbl_803EB25C = 0; lbl_803EB260 = 0; lbl_803EB258 = 0;
}
void fn_80146A6C(Entry_80146C4C *p, SlotDescription_80146A6C *q)
{
    Slot_80146A6C *slot = &((Slot_80146A6C *)p->mUnknown3C)[p->mUnknown36];
    slot->mUnknown0 = fn_80146134();
    slot->mUnknown0->mUnknown0 = q->mUnknown0.mUnknown0;
    slot->mUnknown0->mUnknown4 = q->mUnknown0.mUnknown4;
    slot->mUnknown0->mUnknown8 = q->mUnknown0.mUnknown8;
    slot->mUnknown0->mUnknownC = q->mUnknown0.mUnknownC;
    slot->mUnknown0->mUnknown10 = q->mUnknown0.mUnknown10;
    slot->mUnknown0->mUnknown14 = q->mUnknown0.mUnknown14;
    slot->mUnknown4 = q->mUnknown18;
    if (!lbl_8031B88C[q->mUnknown0.mUnknown0].mUnknownC) {
        fn_80197E6C(&lbl_8031B88C[q->mUnknown0.mUnknown0]);
        lbl_8031B88C[q->mUnknown0.mUnknown0].mUnknownC = 1;
    }
    ++p->mUnknown36;
}
void fn_80146B40(Vector_80146134 *out, Vector_80146134 *in)
{
    Vector_80146134 v;
    fn_801D0470(VptGetMatrixStack()); fn_801D04C4(); fn_801D12BC(3);
    fn_80227D6C(&v, in); out->x = v.x; out->y = v.y; out->z = v.z; fn_801D0544();
}
int fn_80146BA8(Vector_80146134 *p)
{
    if (p->x > -1.0f && p->x < 1.0f && p->y > -1.0f && p->y < 1.0f) return 1;
    return 0;
}
void fn_80146BF8(float value) { lbl_803EB274 = value; }
void fn_80146C00(int index, int count)
{
    Group_80146C00 *p = &(&lbl_8031B87C)[index];
    if (!p->mUnknownC) {
        p->mUnknown0 = 0; p->mUnknownC = 1; p->mUnknown4 = count;
        p->mUnknown8 = &lbl_803EB264[lbl_803EB270]; lbl_803EB270 += count;
    }
}
Entry_80146C4C *fn_80146C4C(int index, Description_801463D8 *q)
{
    Group_80146C00 *group = &(&lbl_8031B87C)[index];
    Entry_80146C4C *p = &group->mUnknown8[group->mUnknown0++];
    p->mUnknown0 = fn_80146134();
    p->mUnknown4 = q->mUnknown18; p->mUnknown8 = q->mUnknown1C;
    p->mUnknown4 = q->mUnknown18; p->mUnknownC = q->mUnknown20;
    p->mUnknown18.x = q->mUnknown24; p->mUnknown18.y = q->mUnknown28; p->mUnknown18.z = q->mUnknown2C;
    p->mUnknown24.x = q->mUnknown30; p->mUnknown24.y = q->mUnknown34; p->mUnknown24.z = q->mUnknown38;
    p->mUnknown30 = q->mUnknown3C; p->mUnknown34 = q->mUnknown40; p->mUnknown38 = q->mUnknown44;
    p->mUnknown0->mUnknown0 = q->mUnknown0.mUnknown0;
    p->mUnknown0->mUnknown4 = q->mUnknown0.mUnknown4; p->mUnknown0->mUnknown8 = q->mUnknown0.mUnknown8;
    p->mUnknown0->mUnknownC = q->mUnknown0.mUnknownC; p->mUnknown0->mUnknown10 = q->mUnknown0.mUnknown10;
    p->mUnknown0->mUnknown14 = q->mUnknown0.mUnknown14;
    if (!lbl_8031B88C[p->mUnknown0->mUnknown0].mUnknownC) {
        fn_80197E6C(&lbl_8031B88C[p->mUnknown0->mUnknown0]);
        lbl_8031B88C[p->mUnknown0->mUnknown0].mUnknownC = 1;
    }
    p->mUnknown36 = 0; p->mUnknown35 = 0; p->mUnknown10 = 1; p->mUnknown11 = 0; p->mUnknown14 = 0.0f;
    FieldMarkerInitEffect(p); return p;
}
struct EffectBlendScope_t {
    void Begin(int main) { EffectBlendBegin(this, main); }
    void Draw(Entry_80146C4C *p) { fn_80197FDC(this, p); }
    void End(int main) { EffectBlendEnd(this, main); }
};
void fn_80146DC4(int index)
{
    Group_80146C00 *group = &(&lbl_8031B87C)[index];
    EffectBlendScope_t scope;
    scope.Begin(index == 0);
    for (unsigned short i = 0; i < group->mUnknown0; ++i) {
        Entry_80146C4C *p = &group->mUnknown8[i];
        if (p->mUnknown10) scope.Draw(p);
    }
    scope.End(index == 0);
}
Resource_80146E64 *fn_80146E64(int index) { return &lbl_8031B88C[index]; }
void fn_80146E78(void) { if (lbl_803EB25C) for (unsigned int i = 0; i < lbl_803EB260; ++i) fn_8014619C(&lbl_803EB25C[i]); }
int fn_80146EDC(unsigned int index) { if (lbl_803EB25C && index < lbl_803EB260) return lbl_803EB25C[index].mUnknown4; return 1; }
float fn_80146F0C(unsigned int index) { if (lbl_803EB25C && index < lbl_803EB260) return lbl_803EB25C[index].mUnknown1C; return 0.0f; }
}
/* Three bytes read by fn_800840A4. */
struct TeamRgb_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

/* Argument of fn_801476C8. */
struct Args_801476C8 {
    char mUnknown0[2];
    unsigned char mUnknown2;
    Object_8003DEC4 *mUnknown4;
};

extern "C" {
int fn_8003DEB4(void);
void fn_80083E1C(DbCursor *pObject, int a);
void fn_800840A4(DbCursor *pObject, void *pBuffer);
int fn_800A7EF4(unsigned char a);
int fn_800C8744(int team);
int fn_80188030(int a);
void fn_801D0424(void *p, float (*m)[4]);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(float (*m)[4]);
void fn_801D06D4(void *p);
void fn_801D0FB8(Point_80146FDC *pOut);

}

static Color_802DD68C lbl_802DD68C[10] = {
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

/* Eight trail colours, read by the trail draw of src/game/cu_80196F48.cpp. */
extern "C" {
Color_802DD68C lbl_802DD72C[8] = {
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

static unsigned char lbl_803EB27C = 1;
static float lbl_803EB280 = 0.45f;

/* Maps x in x0..x1 linearly onto y0..y1. */
static inline float RangeMap(float x, float x0, float x1, float y0, float y1)
{
    return (x - x0) * (y1 - y0) / (x1 - x0) + y0;
}

extern "C" {

float fn_80146F40(unsigned int index)
{
    if (lbl_803EB25C != 0 && index < lbl_803EB260) {
        return lbl_803EB25C[index].mUnknown20;
    }
    return 0.0f;
}

void fn_80146F74(Object_8003DEC4 *pObject, int index, Point_80146FDC *pOut)
{
    fn_801D04C4();
    fn_801D06D4(pObject->mUnknown908);
    fn_801D0664(pObject->mUnknown44.mUnknown52[index]);
    fn_801D0FB8(pOut);
    fn_801D0544();
}

void fn_80146FCC(void)
{
    lbl_803EB27C = 1;
}

void fn_80146FD8(void)
{
}

void fn_80146FDC(ParticleTrailSet_t *pObject)
{
    unsigned int i;

    pObject->mUnknown230 = 1.0f;
    pObject->mUnknown234 = 0;
    pObject->mUnknown238 = -1;
    pObject->mUnknown240 = lbl_802DD68C[8];
    pObject->mUnknown23C = 0;
    pObject->mUnknown554 = 1;
    pObject->mUnknown558 = 0;
    pObject->mUnknown560 = 0;
    for (i = 0; i < 4; i++) {
        Trail_80146FDC *pTrail = &pObject->mTrails[i];

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

void fn_801470F0(Object_8003DEC4 *pObject)
{
    ParticleTrailSet_t *pData = &pObject->mUnknown5188;
    unsigned int i;

    if (--pData->mUnknown55C < 0) {
        pData->mUnknown55C = 3;
        if (--pData->mUnknown554 < 0) {
            pData->mUnknown554 = 1;
        }
        fn_801D0424(pData->mUnknown260[pData->mUnknown554], pObject->mUnknown908);
        pData->mUnknown2E0[pData->mUnknown554] = *(Block_801470F0 *)pObject->mUnknown44.mUnknown48;
        (pData->mUnknown448 + pData->mUnknown554)->x = pObject->mUnknown44.mUnknown8[0];
        (pData->mUnknown448 + pData->mUnknown554)->y = pObject->mUnknown44.mUnknown8[1];
        (pData->mUnknown448 + pData->mUnknown554)->z = pObject->mUnknown44.mUnknown8[2];
        pData->mUnknown460[pData->mUnknown554] = pObject->mUnknown44.mUnknown32;
        pData->mUnknown468[pData->mUnknown554] = *(Half_801470F0 *)pObject->mUnknown280.mUnknown256.mUnknown48;
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
        pData->mUnknown240 = lbl_802DD68C[9];
    } else if (pData->mUnknown238 == -1) {
        pData->mUnknown240 = lbl_802DD68C[8];
    } else {
        pData->mUnknown240 = lbl_802DD68C[pData->mUnknown238];
    }

    if (pObject->mUnknown20 & 0x10000) {
        float count = pData->mUnknown234 + 1;

        if (count > 35.0f) {
            count = 35.0f;
        }
        pData->mUnknown234 = (unsigned int)count;
        pData->mUnknown230 = RangeMap(pData->mUnknown234, 0.0f, 35.0f, 0.05f, 1.0f);
    } else if (pData->mUnknown234 != 0) {
        pObject->mUnknown20 |= 0x10000;
        pData->mUnknown234--;
        pData->mUnknown230 = RangeMap(pData->mUnknown234, 0.0f, 35.0f, 0.05f, 1.0f);
    } else {
        pData->mUnknown234 = 0;
        pData->mUnknown230 = 0.0f;
    }

    for (i = 0; i < 4; i++) {
        Trail_80146FDC *pTrail = &pData->mTrails[i];

        if (pTrail->mCount < 8) {
            pTrail->mCount++;
        }
        fn_80146F74(pObject, pTrail->mIndex[0], &pTrail->mSource[0]);
        fn_80146F74(pObject, pTrail->mIndex[1], &pTrail->mSource[1]);
        if (--pTrail->mHead < 0) {
            pTrail->mHead = 7;
        }
        pTrail->mToggle = pTrail->mToggle == 1 ? 0 : 1;
        pTrail->mPoints[pTrail->mHead] = pTrail->mSource[pTrail->mToggle];
    }
}

void fn_80147598(Object_8003DEC4 *pObject, int bit, unsigned int slot, unsigned char flag)
{
    ParticleTrailSet_t *pData = &pObject->mUnknown5188;
    int index;

    pObject->mUnknown20 |= 1 << bit;
    index = -1;
    if (slot <= 8) {
        index = fn_80188030(slot);
    }
    pData->mUnknown238 = index;
    pData->mUnknown23C = flag;
}

void fn_801475F4(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        Object_8003DEC4 *pObject = fn_8003DEC4(i);
        ParticleTrailSet_t *pData = &pObject->mUnknown5188;
        Trail_80146FDC *pTrail;
        int j;

        pData->mUnknown230 = 1.0f;
        pData->mUnknown234 = 0;
        pData->mUnknown238 = -1;
        pData->mUnknown240 = lbl_802DD68C[8];
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

void fn_801476C8(Args_801476C8 *pArgs)
{
    DbCursor cursor;
    TeamRgb_t rgb;
    PaletteColor color;
    Object_8003DEC4 *pObject = pArgs->mUnknown4;
    int id = fn_800C8744(pArgs->mUnknown2);

    fn_80083E1C(&cursor, 0);
    fn_80084034(&cursor, id, 0);
    fn_800840A4(&cursor, &rgb);
    fn_80083F68(&cursor);
    DbColPalGetPrimaryColor(rgb.mUnknown0, &color);
    pObject->mUnknown5188.mUnknown250.mUnknown0 = color.r / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknown4 = color.g / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknown8 = color.b / 255.0f;
    pObject->mUnknown5188.mUnknown250.mUnknownC = lbl_803EB280;
}

void fn_801477F0(Object_8003DEC4 *pObject)
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

void fn_80147840(Object_8003DEC4 *pObject)
{
    pObject->mUnknown5188.mUnknown560 = 0;
    pObject->mUnknown5188.mUnknown558 = 0;
    pObject->mUnknown20 &= ~0x20000;
}

void fn_80147860(Object_8003DEC4 *pObject, float step)
{
    if (pObject->mUnknown5188.mUnknown560 == 1) {
        pObject->mUnknown5188.mUnknown564 += step;
        if (pObject->mUnknown5188.mUnknown564 >= 30.0f) {
            fn_80147840(pObject);
        }
    }
}

void fn_801478A8(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        fn_801470F0(fn_8003DEC4(i));
    }
}

unsigned char fn_801478F0(unsigned char a)
{
    unsigned char previous = lbl_803EB27C;

    lbl_803EB27C = a;
    return previous;
}

unsigned char fn_80147900(void)
{
    return lbl_803EB27C;
}

}
