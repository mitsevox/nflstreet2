#include "engine/cu_80227F14.h"
#include "game/Record_803EB25C.h"

/* Local access views. Preset and input identities remain unknown. */
struct Vector_80146134 { float x, y, z; };
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
struct Subrecord_80146134 { int mUnknown0; float mUnknown4, mUnknown8, mUnknownC, mUnknown10, mUnknown14; };
struct Description_801463D8 {
    Subrecord_80146134 mUnknown0;
    int mUnknown18, mUnknown1C, mUnknown20;
    float mUnknown24, mUnknown28, mUnknown2C, mUnknown30, mUnknown34, mUnknown38, mUnknown3C;
    unsigned char mUnknown40;
    char mUnknown41[3];
    float mUnknown44;
};
struct SlotDescription_80146A6C { Subrecord_80146134 mUnknown0; float mUnknown18; };
struct Slot_80146A6C { Subrecord_80146134 *mUnknown0; float mUnknown4; };
struct Entry_80146C4C {
    Subrecord_80146134 *mUnknown0;
    int mUnknown4, mUnknown8, mUnknownC;
    unsigned char mUnknown10, mUnknown11;
    char mUnknown12[2];
    float mUnknown14;
    Vector_80146134 mUnknown18, mUnknown24;
    float mUnknown30;
    unsigned char mUnknown34, mUnknown35, mUnknown36;
    char mUnknown37;
    float mUnknown38;
    char mUnknown3C[136]; /* Indexed as 8-byte slots; original capacity unknown. */
};
struct Group_80146C00 { unsigned int mUnknown0; int mUnknown4; Entry_80146C4C *mUnknown8; unsigned char mUnknownC; char mUnknownD[3]; };
struct Resource_80146E64 { void *mUnknown0; int mUnknown4, mUnknown8; unsigned char mUnknownC; char mUnknownD[91]; };

extern "C" {
struct Object_8005406C;
extern Object_8005406C *lbl_803EA554;
extern Vector_80146134 lbl_802A03D0;
extern int lbl_802DD170[];
extern char lbl_802DD584[][24];
extern Description_801463D8 lbl_802DD274;
extern Description_801463D8 lbl_802DD304;
extern Description_801463D8 lbl_802DD53C;
extern Description_801463D8 lbl_802DD34C;
extern Description_801463D8 lbl_802DD2BC;
extern Description_801463D8 lbl_802DD19C;
extern Description_801463D8 lbl_802DD1E4;
extern Description_801463D8 lbl_802DD22C;
extern Description_801463D8 lbl_802DD3DC;
extern SlotDescription_80146A6C lbl_802DD424;
extern SlotDescription_80146A6C lbl_802DD440;
extern SlotDescription_80146A6C lbl_802DD45C;
extern SlotDescription_80146A6C lbl_802DD478;
extern SlotDescription_80146A6C lbl_802DD494;
extern SlotDescription_80146A6C lbl_802DD4B0;
extern SlotDescription_80146A6C lbl_802DD4CC;
extern SlotDescription_80146A6C lbl_802DD4E8;
extern SlotDescription_80146A6C lbl_802DD504;
extern SlotDescription_80146A6C lbl_802DD520;
unsigned int fn_802372EC(int, unsigned int);
int fn_801C2FE4(const char *, const char *);
void *fn_801D2B7C(unsigned int, int, int);
void fn_801D2BD0(void *);
void fn_801D34D0(void *, unsigned int, int, int);
void fn_80197E64(void);
void fn_80197E68(void);
void fn_80197E6C(void *);
void fn_80197F84(void *);
void fn_80197FDC(void *, void *);
void fn_801981D8(void *, int);
void fn_8019831C(void *, int);
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
void fn_80198378(Entry_80146C4C *);
}

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
Subrecord_80146134 *fn_80146134(void) { return &lbl_803EB268[lbl_803EB26C++]; }
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
                range = (unsigned int)((p->mUnknown18 - p->mUnknown14) * 100.0f);
                p->mUnknown4 = 1; base = (unsigned int)(p->mUnknown14 * 100.0f);
            } else {
                range = (unsigned int)((p->mUnknown10 - p->mUnknownC) * 100.0f);
                p->mUnknown4 = 0; base = (unsigned int)(p->mUnknownC * 100.0f);
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
    Vector_80146134 v = lbl_802A03D0;
    lbl_803EB264 = (Entry_80146C4C *)fn_801D2B7C(7840, 0, 0);
    lbl_803EB268 = (Subrecord_80146134 *)fn_801D2B7C(960, 0, 0);
    lbl_803EB258 = 1;
    fn_801D34D0(lbl_803EB264, 7840, 0, 1); fn_801D34D0(lbl_803EB268, 960, 0, 1);
    for (int i = 0; i < 11; ++i) {
        lbl_8031B88C[i].mUnknown0 = owner; lbl_8031B88C[i].mUnknown4 = lbl_802DD170[i];
        lbl_8031B88C[i].mUnknownC = 0; lbl_8031B88C[i].mUnknown8 = 0;
    }
    for (int i = 0; i < 40; ++i) lbl_8031B7DC[i] = 0;
    fn_80146C00(0, ((Config_803EA554 *)lbl_803EA554)->mUnknown50 + 17);
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
    if (((Config_803EA554 *)lbl_803EA554)->mUnknown50 != 0) {
        lbl_803EB25C = (Record_803EB25C *)fn_801D2B7C(((Config_803EA554 *)lbl_803EA554)->mUnknown50 * 36, 0, 0);
        lbl_803EB260 = ((Config_803EA554 *)lbl_803EA554)->mUnknown50;
        for (unsigned int i = 0; i < ((Config_803EA554 *)lbl_803EA554)->mUnknown50 && i <= 39; ++i) {
            Input_80146150 *input = &((Config_803EA554 *)lbl_803EA554)->mUnknown54[i];
            fn_80146150(&lbl_803EB25C[i], input);
            Description_801463D8 *desc = fn_801463D8(((Config_803EA554 *)lbl_803EA554)->mUnknown24[input->mUnknown18]);
            if (desc) {
                lbl_8031B7DC[i] = fn_80146C4C(0, desc);
                fn_801D0470(fn_80228668()); fn_801D04C4(); fn_801D0558();
                int x = (int)(input->mUnknownC.x * 46603.37890625f);
                int y = (int)(input->mUnknownC.y * 46603.37890625f);
                int z = (int)((input->mUnknownC.z + 90.0f) * 46603.37890625f);
                fn_801D0ADC(-z); fn_801D09EC(-y); fn_801D08FC(-x);
                Vector_80146134 out; fn_80227C2C(&out, &v); fn_801D0544();
                lbl_8031B7DC[i]->mUnknown18 = input->mUnknown0;
                lbl_8031B7DC[i]->mUnknown24 = out;
            }
        }
    }
}
void fn_801469A0(void)
{
    fn_80197E68();
    lbl_8031B87C.mUnknown0 = 0; lbl_8031B87C.mUnknown4 = 0;
    lbl_8031B87C.mUnknown8 = 0; lbl_8031B87C.mUnknownC = 0;
    Resource_80146E64 *p = lbl_8031B88C;
    do {
        if (p->mUnknownC) { fn_80197F84(p); p->mUnknownC = 0; }
        ++p;
    } while (p <= &lbl_8031B88C[10]);
    lbl_803EB278 = 0; fn_801D2BD0(lbl_803EB264); lbl_803EB264 = 0;
    fn_801D2BD0(lbl_803EB268); lbl_803EB268 = 0; lbl_803EB26C = 0; lbl_803EB270 = 0;
    if (lbl_803EB25C) fn_801D2BD0(lbl_803EB25C);
    lbl_803EB258 = 0; lbl_803EB25C = 0; lbl_803EB260 = 0;
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
    fn_801D0470(fn_80228668()); fn_801D04C4(); fn_801D12BC(3);
    fn_80227D6C(&v, in); out->x = v.x; out->z = v.z; out->y = v.y; fn_801D0544();
}
int fn_80146BA8(Vector_80146134 *p) { return p->x > -1.0f && p->x < 1.0f && p->y > -1.0f && p->y < 1.0f; }
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
    p->mUnknown10 = 1; p->mUnknown11 = 0; p->mUnknown14 = 0.0f; p->mUnknown36 = 0; p->mUnknown35 = 0;
    fn_80198378(p); return p;
}
void fn_80146DC4(int index)
{
    char state[12]; fn_801981D8(state, index == 0);
    Group_80146C00 *group = &(&lbl_8031B87C)[index];
    for (unsigned short i = 0; i < group->mUnknown0; ++i) {
        Entry_80146C4C *p = &group->mUnknown8[i]; if (p->mUnknown10) fn_80197FDC(state, p);
    }
    fn_8019831C(state, index == 0);
}
Resource_80146E64 *fn_80146E64(int index) { return &lbl_8031B88C[index]; }
void fn_80146E78(void) { if (lbl_803EB25C) for (unsigned int i = 0; i < lbl_803EB260; ++i) fn_8014619C(&lbl_803EB25C[i]); }
int fn_80146EDC(unsigned int index) { if (lbl_803EB25C && index < lbl_803EB260) return lbl_803EB25C[index].mUnknown4; return 1; }
float fn_80146F0C(unsigned int index) { if (lbl_803EB25C && index < lbl_803EB260) return lbl_803EB25C[index].mUnknown1C; return 0.0f; }
}
