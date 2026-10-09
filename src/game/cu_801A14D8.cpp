#include "engine/cu_80227F14.h"
#include "game/Init_8004A040.h"
#include "game/Object_8003DEC4.h"

#include <dolphin/gx/GXVert.h>

/* Per-player draw slot (0x30 bytes), one of the fourteen entries of
   lbl_80365AB4 handed out by fn_801A3284 and filled by fn_801A3C40. */
struct Slot_801A3284 {
    Object_8003DEC4 *mpUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    void *mpUnknown12;
    Light_8003DEC4 *mpUnknown16;
    void *mpUnknown20;
    void *mpUnknown24;
    void *mpUnknown28;
    void *mpUnknown32;
    void *mpUnknown36[2];
    unsigned char mUnknown44;
    char mUnknown45[3];
};

/* Four colour bytes passed by value to fn_8024FB58. */
struct Color_8024FB58 {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct Vector_801A1650 {
    float x;
    float y;
    float z;
};

/* Model data returned by fn_8015E2FC; +0x18 is passed to fn_80210214. */
struct Model_8015E2FC {
    char mUnknown0[24];
    void *mpUnknown24;
};

/* Object returned by fn_8003E0C8 for the player: +0x310 points to its
   uniform record, whose first byte is a kind. */
struct Owner_801A2EC8 {
    char mUnknown0[784];
    unsigned char *mpUnknown784;
};

/* Eight-byte light reference passed to fn_8020F78C and fn_802345BC. */
struct Ref_803EB81C {
    int mUnknown0;
    void *mpUnknown4;
};

extern "C" {
extern Light_8020F2C4 lbl_80365D54;
extern char lbl_80365D88[16];
extern char lbl_80365D98[];
extern Slot_801A3284 lbl_80365AB4[14];
extern Object_80228224 *lbl_803ECC00;
extern unsigned int lbl_803ECC04;
extern int lbl_803ECC08;
extern int lbl_803ECC0C;
extern int lbl_803ECC10;
extern unsigned char lbl_803EB7E8;
extern float lbl_803EB7EC;
extern unsigned char lbl_803EB7F0;
extern unsigned int lbl_803EB7F4;
extern float lbl_803EB800;
extern float lbl_803EB804;
extern float lbl_803EB808;
extern float lbl_803EB80C;
extern void (*lbl_803EB810)(Object_8003DEC4 *pPlayer);
extern Object_8003DEC4 *lbl_803EB814;
extern unsigned char lbl_803EB818;
extern Ref_803EB81C lbl_803EB81C[1];
extern unsigned char lbl_803EB824;
extern unsigned char lbl_803EB825;
extern float lbl_803EA2C4;
extern float lbl_802F29B0[3];
extern float lbl_802F29BC[3];
extern float lbl_802F29C8[];
extern int lbl_802F2934[];
extern unsigned char lbl_802F3468[30];

int fn_8002894C(void);
int fn_80027DF0(void);
void *fn_80028BB4(void);
int fn_8003DEB4(void);
Owner_801A2EC8 *fn_8003E0C8(Object_8003DEC4 *pPlayer);
float fn_80042F54(float x, float hi, float vhi, float lo, float vlo);
int fn_80049D04(int index);
unsigned char fn_80049D1C(int index);
int fn_8004A238(void);
int fn_80054D24(int flag);
int fn_800A2624(void);
void fn_800A3B58(Owner_801A2EC8 *pOwner, int a, int b);
int fn_800ADDD8(Element_80041BF8 *pElements, int index);
unsigned int fn_800B823C(int index);
void fn_800C2150(Object_8003DEC4 *pPlayer, Block_800C2788 *pBlock, int a);
void fn_800C2884(Object_8003DEC4 *pPlayer, Block_800C2EC0 *pBlock, int a);
float fn_800D3F2C(int index);
void fn_801442FC(void *p);
int fn_80144310(void *p, Source_80144310 *pSource, void *pOut, Vector_801A1650 *pScale);
void fn_80147860(Object_8003DEC4 *pPlayer, float f);
int fn_8015CD9C(void);
unsigned char fn_8015D2E8(Object_8003DEC4 *pPlayer);
void fn_8015D32C(Object_8003DEC4 *pPlayer, Vector_801A1650 *pPos);
void fn_8015D3B0(Object_8003DEC4 *pPlayer);
void *fn_8015E2FC(int a, int b, int c);
int fn_8015E440(int a, int b);
void fn_8015E73C(void);
void fn_8015E908(int a);
void fn_8015E9F4(int a, int *p);
void fn_8015EB4C(int a, int b);
void fn_8015EC74(int a, int b);
void fn_8015ED9C(int a, int b);
void fn_8015F3FC(int a);
void fn_8015F82C(int id, Object_8003DEC4 *pPlayer, void (*pCallback)(Object_8003DEC4 *));
void fn_8015FFA8(void *a, void *b);
void *fn_80160C08(void);
Desc_802347EC *fn_8016102C(int player);
void fn_80161498(void);
int fn_8017F584(void);
void fn_8019723C(Object_80146094 *p);
void fn_801A1400(Object_8003DEC4 *pPlayer);
void *fn_801A4AE4(int player);
void fn_801A4C1C(Desc_802347EC *pDescs, void *pEntries);
void *fn_801C1F94(void *pDst, int value, int size);
char *fn_801C2EF0(char *pDst, const char *pSrc, int n);
void fn_801C657C(void);
void fn_801D0470(void);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(void *pMatrix);
void fn_801D06D4(void *pMatrix);
void fn_801D09EC(int a);
void fn_801D0C58(float *p);
void fn_801D0CFC(float scale);
void fn_801D0D94(float x, float y, float z);
void fn_801D0F80(float (*pMatrix)[4]);
int fn_801D2BB0(int a, void *p, int b, int c);
void fn_801D2BD0(int handle);
void fn_801DD3AC(void *a, Object_8003DEC4 *pPlayer, int b);
void fn_801EF7BC(void *a, int b, int c);
void fn_801F010C(void *a, int b);
void *fn_801F0C50(void *a, int b);
void fn_8020F28C(Light_8020F2C4 *p);
void fn_8020F2C4(void *pDst, void *pSrc);
void fn_8020F78C(Light_8020F2C4 *p, Ref_803EB81C *pRef);
void fn_8020F89C(Light_8020F2C4 *p);
void fn_8020F8E0(Light_8020F2C4 *p);
void fn_8020F92C(Light_8020F2C4 *p);
void fn_80210214(void *p, void *q);
void fn_80210388(void);
void fn_80210654(Light_8020F2C4 *p);
void fn_80210724(Joints_8003DEC4 *p);
void fn_80210814(int a, int b, int c);
void fn_80210BA4(void *p);
void fn_80210BD8(int a);
void fn_80210CC4(float a, float b);
void fn_802113C0(int a, int b);
void fn_80211E08(void *p, int handle);
void fn_80211EFC(void *p);
void fn_80211FF0(void);
void fn_80212018(const char *pName, void *p);
int fn_802120E4(void *p, unsigned int color);
int fn_80212124(void *p, unsigned int color, int a);
void fn_80214554(void *p, int a, int b);
void fn_802145B0(void *p);
void fn_802145F4(void *p);
int fn_80214600(void *p);
int fn_802149E8(float *p, int a);
void fn_80214A7C(void *p);
void fn_80214AC8(void);
void fn_80214B20(void);
void fn_80214B6C(Light_8020F2C4 *pDst, Light_8020F2C4 *pSrc);
void fn_80214CB4(void);
void fn_80227930(Vector_801A1650 *pOut, float *pA, float *pB, float t);
void fn_802336C4(void *p, void *q, int a);
void fn_80233728(void *p);
void fn_80233760(void *p, short *pValues, int count);
void fn_802337D4(void *pModel, Joints_8003DEC4 *pJoints, void *pPose, unsigned int mask);
void fn_80233850(void *pModel, Joints_8003DEC4 *pJoints, void *pPose, unsigned int mask, unsigned char *pFlags);
void fn_80233BB8(Joints_8003DEC4 *p, int a, int b);
void fn_80233BD8(Joints_8003DEC4 *p);
void fn_80233BE0(void);
void fn_80233CBC(void *p, int index, int value);
void fn_802341AC(void);
void fn_802341B8(void);
void fn_802341C4(Lod_802341C4 *p);
void fn_802341E8(Lod_802341C4 *p);
void fn_80234424(int a);
void fn_802345BC(Ref_803EB81C *p);
void fn_8023465C(void *p, void *pModel, Desc_802347EC *pDescs);
void fn_8023472C(void *p, int a, int b, Desc_802347EC *pA, Desc_802347EC *pB, int c);
void fn_8023488C(void *p, int a);
void fn_802348AC(void *p);
void fn_8023491C(void *p, int a);
void fn_80234994(void *p);
void fn_802349B8(void *p, int a);
void fn_80234A14(Part_8003DEC4 *p, int a);
void fn_80234A30(Part_8003DEC4 *p, int a);
void fn_80234A90(Part_8003DEC4 *p);
void fn_80234A94(Part_8003DEC4 *p, void *pModel);
void fn_80234AD8(Part_8003DEC4 *p, void *pModel);
void fn_80234BF4(int a, Part_8003DEC4 *p, int b);
void fn_80234CA4(Part_8003DEC4 *p, Joints_8003DEC4 *pJoints);
void fn_80234CAC(Part_8003DEC4 *p, void *q);
void fn_80234CF0(Part_8003DEC4 *p, int a, void *q);
void fn_80234DC0(Part_8003DEC4 *p, int a);
int fn_80236B98(int a, float r, float g, float b);
void fn_80236C10(int a, Vector_801A1650 *pScale, void *p);
int fn_80236EC0(int a);
void fn_8024CB90(int attr, int type);
void fn_8024D418(void);
void fn_8024D450(int fmt, int attr, int cnt, int type, int frac);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024E908(int type, int fmt, int count);
void fn_8024EB28(int a);
void fn_8024FB58(int chan, Color_8024FB58 color);
void fn_8024FC48(int n);
void fn_8024FC84(int chan, int enable, int amb, int mat, int lights, int diff, int attn);
void fn_80251604(int a, int b);
void fn_80251A58(int comp0, int ref0, int op, int comp1, int ref1);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_80252034(int type, int src, int dst, int op);
void fn_802520E0(int enable, int func, int update);
void fn_80252114(int a);
void fn_8025251C(float (*pMatrix)[4], int id);
void fn_802525BC(int id);
void fn_802525F0(float (*pMatrix)[4], int id, int type);

int fn_801A1C10(Object_8003DEC4 *pPlayer);
void fn_801A1D80(Object_8003DEC4 *pPlayer, int flag);
int fn_801A201C(Object_8003DEC4 *pPlayer);
void fn_801A209C(Object_8003DEC4 *pPlayer, float *pPos, float (*pMatrix)[4], Object_80146094 *pTrail,
                 int index, void *pModel, void **ppModels, unsigned int lod);
void fn_801A32AC(int id, float sx, float sy, float tx, float ty);
void fn_801A3300(Object_8003DEC4 *pPlayer, float *pA, float *pB);
void fn_801A34A4(Object_8003DEC4 *pPlayer);
void fn_801A4690(int index);
void fn_801A46BC(void);

void fn_801A14D8(void)
{
    void *p = fn_801F0C50(fn_80160C08(), 0);

    lbl_803ECC10 = fn_801D2BB0(fn_8002894C() ? 0x40 : 1, p, 2, 0);
    fn_801EF7BC(fn_80160C08(), 0, lbl_803ECC10);
    fn_80211E08(lbl_80365D98, lbl_803ECC10);
    lbl_803ECC08 = fn_802120E4(lbl_80365D98, 0xFF000000);
    lbl_803ECC0C = fn_80212124(lbl_80365D98, 0xFF000000, 0);
}

void fn_801A1578(void)
{
    fn_80211EFC(lbl_80365D98);
    fn_801D2BD0(lbl_803ECC10);
    if (fn_80027DF0()) {
        fn_801F010C(fn_80160C08(), 0);
        fn_80161498();
    }
}

void fn_801A15C4(Object_80228224 *pObject)
{
    unsigned int i;

    fn_802145F4(lbl_80365D88);
    fn_8020F89C(&lbl_80365D54);
    for (i = 0; i < lbl_803ECC04; i++) {
        Object_8003DEC4 *pPlayer = fn_8003DEC4(i);

        if (pPlayer->mUnknown20 & 8) {
            continue;
        }
        if (pPlayer->mUnknown20 & 0x20000) {
            fn_801DD3AC(fn_80028BB4(), pPlayer, 11);
        }
    }
}

/* Light colour of the player: the team colour faded towards the colour of
   its current light source over fifteen frames, scaled by the flash
   colour while one runs. Returns the light from fn_80236B98. */
int fn_801A1650(Object_8003DEC4 *pPlayer)
{
    Object_80146094 *pData = &pPlayer->mUnknown5188;
    float r = 1.0f;
    float g = r;
    float b = r;
    int flash = 0;
    Source_80144310 *pSource;
    int light;
    char block[16];
    Vector_801A1650 scale;
    Vector_801A1650 color;

    if (pPlayer->mUnknown20 & 0x20000) {
        flash = pData->mUnknown564 == 12.0f;
    }
    pSource = pPlayer->mUnknown972;
    if (pSource) {
        if (pSource->mUnknown12[0] != pData->mUnknown580 || pSource->mUnknown12[1] != pData->mUnknown584 ||
            pSource->mUnknown12[2] != pData->mUnknown588) {
            float t = pData->mUnknown5A0;

            pData->mUnknown590 = (pData->mUnknown580 - pData->mUnknown590) * (1.0f / 15.0f) * t + pData->mUnknown590;
            pData->mUnknown594 = (pData->mUnknown584 - pData->mUnknown594) * (1.0f / 15.0f) * t + pData->mUnknown594;
            pData->mUnknown598 = (pData->mUnknown588 - pData->mUnknown598) * (1.0f / 15.0f) * t + pData->mUnknown598;
            pData->mUnknown580 = pPlayer->mUnknown972->mUnknown12[0];
            pData->mUnknown584 = pPlayer->mUnknown972->mUnknown12[1];
            pData->mUnknown588 = pPlayer->mUnknown972->mUnknown12[2];
            pData->mUnknown5A0 = 0;
        }
        if (pData->mUnknown5A0 < 15) {
            float t = pData->mUnknown5A0++;

            b = (pData->mUnknown588 - pData->mUnknown598) * (1.0f / 15.0f) * t + pData->mUnknown598;
            r = (pData->mUnknown580 - pData->mUnknown590) * (1.0f / 15.0f) * t + pData->mUnknown590;
            g = (pData->mUnknown584 - pData->mUnknown594) * (1.0f / 15.0f) * t + pData->mUnknown594;
        } else {
            r = pData->mUnknown580;
            g = pData->mUnknown584;
            b = pData->mUnknown588;
        }
    }
    if (pData->mUnknown5A4) {
        if (pData->mUnknown5A8 < 30) {
            float s = 2.0f - (float)pData->mUnknown5A8++ * (1.0f / 30.0f);

            r *= pData->mUnknown56C * s;
            g *= pData->mUnknown570 * s;
            b *= pData->mUnknown574 * s;
        } else {
            pData->mUnknown5A8 = 0;
            pData->mUnknown5A4 = 0;
        }
    } else if (pData->mUnknown568 == 1) {
        r *= pData->mUnknown56C;
        g *= pData->mUnknown570;
        b *= pData->mUnknown574;
    }
    if (flash) {
        fn_80227930(&color, lbl_802F29B0, lbl_802F29BC, fn_800D3F2C(pPlayer->mUnknown4968));
        r = color.x;
        g = color.y;
        b = color.z;
    }
    light = fn_80236B98(1, r, g, b);
    if (fn_80144310(pPlayer->mUnknown4960, pPlayer->mUnknown972, block, &scale)) {
        scale.x *= r;
        scale.y *= g;
        scale.z *= b;
        fn_80236C10(0, &scale, block);
    }
    return light;
}

void fn_801A1978(Object_8003DEC4 *pPlayer, unsigned int flags)
{
    Color_8024FB58 color = {255};
    float depth;
    int light;

    color.g = 255;
    color.b = 255;
    color.a = 255;
    fn_80210388();
    if (pPlayer->mUnknown20 & 8) {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * lbl_803EB808;
    } else {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * lbl_803EB800;
    }
    light = fn_801A1650(pPlayer);
    fn_8024FB58(0, color);
    fn_8024FB58(4, color);
    fn_8024FC48(1);
    fn_8024FC84(0, 1, 0, 0, light, 2, 2);
    fn_8024FC84(2, 0, 0, 0, light, 0, 2);
    fn_80251A58(7, 0, 0, 7, 0);
    fn_8024EB28(1);
    fn_80210BD8(1);
    fn_80234BF4(0, &pPlayer->mUnknown1164[0], 0);
    light = fn_801A1C10(pPlayer);
    fn_80234BF4(0, &pPlayer->mUnknown1164[2], 0);
    fn_80234BF4(0, &pPlayer->mUnknown1164[3], 0);
    fn_80210CC4(0.0f, depth);
    fn_80234BF4(0, &pPlayer->mUnknown1164[7], 0);
    fn_80251A58(4, 0, 0, 7, 0);
    fn_80210BD8(2);
    fn_801A1D80(pPlayer, light);
    fn_80234BF4(0, &pPlayer->mUnknown1164[11], 0);
    fn_80234BF4(0, &pPlayer->mUnknown1164[9], 0);
    if (!fn_80049D04(pPlayer->mUnknown4971)) {
        fn_80210BD8(1);
    }
    if (pPlayer->mUnknown20 & 8) {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * lbl_803EB80C;
    } else {
        depth = 1.0f - pPlayer->mUnknown4216.mUnknown16 * lbl_803EB804;
    }
    fn_80210CC4(0.0f, depth);
    fn_80234BF4(0, &pPlayer->mUnknown1164[6], 0);
    if (!fn_80049D04(pPlayer->mUnknown4971)) {
        fn_80210BD8(2);
    }
    fn_80234BF4(0, &pPlayer->mUnknown1164[1], 0);
    fn_80234BF4(0, &pPlayer->mUnknown1164[8], 0);
    fn_80210BD8(1);
    fn_80210CC4(0.0f, 1.0f);
    fn_8024EB28(0);
}

int fn_801A1C10(Object_8003DEC4 *pPlayer)
{
    int result = 0;
    Slot_801A3284 *pSlot = pPlayer->mUnknown1160;

    if (pSlot->mUnknown8 == 0) {
        float a[2];
        float b[2];

        if (pSlot->mUnknown4 & 8) {
            result = fn_801A201C(pPlayer);
        }
        if (result) {
            fn_80210654(&lbl_80365D54);
        } else {
            fn_80210654(&pSlot->mpUnknown16->mUnknown16);
        }
        fn_80210BA4(pPlayer->mUnknown4044);
        fn_80210724(&pPlayer->mUnknown4064[1]);
        fn_80210BD8(1);
        fn_8024EB28(0);
        fn_801A3300(pPlayer, a, b);
        fn_801A32AC(30, 1.0f, 1.0f, b[0], b[1]);
        fn_8024DCE4(0, 1, 4, 30, 0, 125);
        fn_802113C0(2, 0);
        fn_801A32AC(30, 1.0f, 1.0f, a[0], a[1]);
        fn_8024DCE4(0, 1, 4, 30, 0, 125);
        fn_802113C0(3, 0);
        fn_8024DCE4(0, 1, 4, 60, 0, 125);
        fn_802113C0(1, 0);
    } else {
        fn_80234BF4(0, &pPlayer->mUnknown1164[4], 0);
    }
    return result;
}

void fn_801A1D80(Object_8003DEC4 *pPlayer, int flag)
{
    if (flag) {
        fn_80210654(&lbl_80365D54);
        fn_80210BA4(pPlayer->mUnknown4044);
        fn_80210724(&pPlayer->mUnknown4064[1]);
        fn_802113C0(4, 0);
    } else {
        fn_80234BF4(0, &pPlayer->mUnknown1164[5], 0);
    }
}

/* Draws the recorded trail poses of the player with fading alpha. */
void fn_801A1DEC(Object_8003DEC4 *pPlayer, Slot_801A3284 *pSlot, unsigned int count)
{
    Color_8024FB58 color = {255};
    unsigned int i = 0;
    Vector_801A1650 v;
    int light;
    int index;

    color.g = 255;
    color.b = 255;
    color.a = 255;
    fn_80227930(&v, lbl_802F29B0, lbl_802F29BC, fn_800D3F2C(pPlayer->mUnknown4968));
    light = fn_80236B98(1, v.x, v.y, v.z);
    fn_8024FB58(0, color);
    fn_8024FC48(1);
    fn_8024FC84(0, 1, 0, 0, light, 2, 2);
    fn_8024FC84(2, 0, 0, 0, light, 0, 2);
    fn_80210BD8(2);
    fn_80251A58(4, 0, 0, 7, 0);
    fn_8024EB28(1);
    index = pPlayer->mUnknown5188.mUnknown554;
    for (i = 0; i < pPlayer->mUnknown5188.mUnknown558; i++) {
        color.a = (pPlayer->mUnknown5188.mUnknown558 - i) * 51 + 25;
        fn_8024FB58(4, color);
        if (i < count) {
            fn_801A209C(pPlayer, 0, pPlayer->mUnknown5188.mUnknown260[index], &pPlayer->mUnknown5188, index,
                        pSlot->mpUnknown12, pSlot->mpUnknown36, pSlot->mUnknown8);
            fn_80234BF4(0, &pPlayer->mUnknown1164[0], 0);
            fn_801A1C10(pPlayer);
            fn_80234BF4(0, &pPlayer->mUnknown1164[7], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[2], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[3], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[9], 0);
            fn_80234BF4(0, &pPlayer->mUnknown1164[6], 0);
        }
        index++;
        index &= 1;
    }
    fn_80147860(pPlayer, lbl_803EA2C4);
    fn_80210BD8(1);
    fn_80210CC4(0.0f, 1.0f);
    fn_8024EB28(0);
}

int fn_801A201C(Object_8003DEC4 *pPlayer)
{
    int result = 0;

    if (fn_80214600(lbl_80365D88) > 0xCE3 && fn_802149E8(pPlayer->mUnknown820, pPlayer->mUnknown816) > 0) {
        result = 1;
        fn_80214A7C(lbl_80365D88);
        fn_80214B6C(&pPlayer->mUnknown1024[0].mUnknown16, &lbl_80365D54);
        fn_80214CB4();
        fn_80214B20();
        fn_80214AC8();
    }
    return result;
}

void fn_801A209C(Object_8003DEC4 *pPlayer, float *pPos, float (*pMatrix)[4], Object_80146094 *pTrail,
                 int index, void *pModel, void **ppModels, unsigned int lod)
{
    float scale = 1.5f;
    short *pPose;
    unsigned int i;
    unsigned int j;

    if (pTrail) {
        pPose = (short *)&pTrail->mUnknown2E0[index];
    } else {
        pPose = pPlayer->mUnknown44.mUnknown48;
    }
    fn_801D04C4();
    fn_801D0664(pMatrix);
    fn_801D0CFC(pPlayer->mUnknown24);
    if (pPos) {
        fn_801D0D94(pPos[0], pPos[1], pPos[2]);
    }
    fn_801D04C4();
    fn_80233BE0();
    if (!(pPlayer->mUnknown20 & 0x2000)) {
        if (pTrail) {
            fn_801D0C58(&pTrail->mUnknown448[index].x);
            fn_801D09EC(pTrail->mUnknown460[index]);
        } else {
            fn_801D0C58(pPlayer->mUnknown44.mUnknown8);
            fn_801D09EC(pPlayer->mUnknown44.mUnknown32);
        }
    }
    if (pPlayer->mUnknown20 & 0x4000) {
        fn_80233850(pPlayer->mUnknown1164[0].mpUnknown12, &pPlayer->mUnknown4064[0], pPose, 0xE0000000,
                    lbl_802F3468);
    } else {
        fn_802337D4(pPlayer->mUnknown1164[0].mpUnknown12, &pPlayer->mUnknown4064[0], pPose, 0xE0000000);
    }
    fn_802337D4(pPlayer->mUnknown1164[4].mpUnknown12, &pPlayer->mUnknown4064[1], pPose, 0xE0000000);
    if (fn_80054D24(0x20) && !fn_8017F584()) {
        for (i = 1; i < pPlayer->mUnknown1164[4].mpUnknown12->mpUnknown12->mUnknown4; i++) {
            if (pPlayer->mUnknown1164[4].mpUnknown12->mpUnknown12->mpUnknown0[i][0] == 13) {
                for (j = 0; j < 12; j++) {
                    if (j != 3 && j != 7 && j != 11) {
                        pPlayer->mUnknown4064[1].mpUnknown0[i][j] *= scale;
                    }
                }
            }
        }
    }
    (void)pMatrix;
    (void)ppModels;
    (void)lod;
    fn_801D0544();
}

unsigned int fn_801A28E8(Object_8003DEC4 *pPlayer)
{
    unsigned int flags = 0;
    unsigned int state = pPlayer->mUnknown4216.mUnknown20;

    if ((state & 0x3F) || (lbl_803EB7E8 && (state & 0x2000))) {
        if (!(pPlayer->mUnknown20 & 8)) {
            flags = 1;
        }
    } else if (state & 0xF0000) {
        flags |= 2;
    }
    if (!(pPlayer->mUnknown20 & 1)) {
        flags |= 1;
    }
    if (!fn_8004A238()) {
        flags |= 1;
    }
    if (flags & 1) {
        pPlayer->mUnknown20 |= 0x200;
    } else {
        pPlayer->mUnknown20 &= ~0x200;
    }
    return flags;
}

void fn_801A299C(Part_8003DEC4 *pPart, int a, Joints_8003DEC4 *pJoints, void *pContext)
{
    fn_80234A30(pPart, a);
    fn_80234CA4(pPart, pJoints);
    fn_80234CF0(pPart, 0, pContext);
    fn_80234DC0(pPart, 10);
}

void fn_801A29F8(Part_8003DEC4 *pPart, void *pContext, Object_8003DEC4 *pPlayer)
{
    fn_80234A30(pPart, 0);
    fn_80234CA4(pPart, &pPlayer->mUnknown4064[1]);
    fn_80234CF0(pPart, 0, pContext);
    fn_80234DC0(pPart, 10);
    fn_8023491C(&pPlayer->mUnknown816, 0x40);
    fn_80234CAC(pPart, &pPlayer->mUnknown816);
    fn_802349B8(&pPlayer->mUnknown816, 12);
    pPlayer->mUnknown830 = 0x24;
}

/* Sets the two light blocks of the player from its team lights, with the
   53 FMCAPPORT weights converted to 4.12 fixed point. */
void fn_801A2A88(Object_8003DEC4 *pPlayer, int unused)
{
    short values[53];
    int a;
    int b;
    int i;

    fn_801C1F94(values, 0, sizeof(values));
    if (pPlayer->mUnknown992 == 0xFFFF) {
        fn_8015FFA8(fn_8015E2FC(6, 0, 0), fn_8015E2FC(5, 0, 0));
        fn_8015FFA8(fn_8015E2FC(6, 0, 1), fn_8015E2FC(5, 0, 1));
        fn_8020F2C4(fn_8015E2FC(4, 0, 0), fn_8015E2FC(6, 0, 0));
        fn_8020F2C4(fn_8015E2FC(4, 0, 1), fn_8015E2FC(6, 0, 1));
        for (i = 0; i < 53; i++) {
            values[i] = pPlayer->mUnknown4976.mValues[i] * 4096.0f;
        }
        values[pPlayer->mUnknown4972 + 1] = 0x1000;
        if (fn_80049D1C(pPlayer->mUnknown4971)) {
            values[6] = 0x1000;
        }
    } else {
        fn_8015E73C();
        fn_8015FFA8(fn_8015E2FC(4, 0, 0), fn_8015E2FC(5, 0, 0));
        fn_8015FFA8(fn_8015E2FC(4, 0, 1), fn_8015E2FC(5, 0, 1));
        values[1] = 0x1000;
        values[pPlayer->mUnknown4972 + 2] = 0x1000;
        if (fn_80049D1C(pPlayer->mUnknown4971)) {
            values[7] = 0x1000;
        }
    }
    fn_802336C4(&pPlayer->mUnknown1024[0], fn_8015E2FC(6, 0, 0), lbl_803EB7F4);
    fn_802336C4(&pPlayer->mUnknown1024[1], fn_8015E2FC(6, 0, 1), lbl_803EB7F4 >> 1);
    if (pPlayer->mUnknown992 == 0xFFFF) {
        fn_80233760(&pPlayer->mUnknown1024[0], values, 53);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 53);
    } else {
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        fn_8020F2C4(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(4, 0, 0));
        fn_8020F2C4(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(4, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        fn_80233760(&pPlayer->mUnknown1024[0], values, 37);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 37);
    }
    a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
    b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
    if (pPlayer->mUnknown992 != 0xFFFF) {
        fn_8015E908(pPlayer->mUnknown4970);
    }
    fn_8020F2C4(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
    fn_8020F2C4(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
    pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
    pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
    fn_8020F78C(&pPlayer->mUnknown1024[0].mUnknown16, lbl_803EB81C);
    fn_8020F78C(&pPlayer->mUnknown1024[1].mUnknown16, lbl_803EB81C);
    fn_801A4690(0);
    fn_8015F3FC(0);
    if (lbl_80365D54.mUnknown0 == 0) {
        fn_8020F2C4(&lbl_80365D54, &pPlayer->mUnknown1024[0].mUnknown16);
        fn_8020F8E0(&lbl_80365D54);
        fn_80214554(lbl_80365D88, 0x7404, 0x20);
    }
    fn_8015E9F4(pPlayer->mUnknown4970, &pPlayer->mUnknown996);
    fn_8015EB4C(pPlayer->mUnknown4970, pPlayer->mUnknown1004);
    fn_8015EC74(pPlayer->mUnknown4970, pPlayer->mUnknown1008);
    fn_801A46BC();
}

void fn_801A2E90(Object_8003DEC4 *pPlayer)
{
    fn_80233728(&pPlayer->mUnknown1024[0]);
    fn_80233728(&pPlayer->mUnknown1024[1]);
}

void fn_801A2EC8(Object_8003DEC4 *pPlayer, Slot_801A3284 *pSlot)
{
    unsigned int i;

    fn_80234A94(&pPlayer->mUnknown1164[0], pSlot->mpUnknown12);
    fn_80234CA4(&pPlayer->mUnknown1164[0], &pPlayer->mUnknown4064[0]);
    fn_80234AD8(&pPlayer->mUnknown1164[4], pSlot->mpUnknown16);
    fn_80234CA4(&pPlayer->mUnknown1164[4], &pPlayer->mUnknown4064[1]);
    fn_80234AD8(&pPlayer->mUnknown1164[5], pSlot->mpUnknown16);
    fn_80234CA4(&pPlayer->mUnknown1164[5], &pPlayer->mUnknown4064[1]);
    if ((pPlayer->mUnknown20 & 0x10) && pSlot->mUnknown8 == 0) {
        if (!(pPlayer->mUnknown20 & 8) && pPlayer->mUnknown820) {
            if (*fn_8003E0C8(pPlayer)->mpUnknown784 == 0x32) {
                pPlayer->mUnknown820[pPlayer->mUnknown4972 + 2] = -1.0f;
            } else if (pPlayer->mUnknown20 & 0x40000) {
                float f = pPlayer->mUnknown820[1];

                pPlayer->mUnknown820[1] = 0.0f;
                pPlayer->mUnknown820[pPlayer->mUnknown4972 + 2] = f + -1.0f;
            }
        }
        fn_80234CAC(&pPlayer->mUnknown1164[4], &pPlayer->mUnknown816);
        fn_80234A14(&pPlayer->mUnknown1164[4], 1);
        fn_80234CAC(&pPlayer->mUnknown1164[5], &pPlayer->mUnknown816);
        fn_80234A14(&pPlayer->mUnknown1164[5], 1);
    } else {
        fn_80234CAC(&pPlayer->mUnknown1164[4], 0);
        fn_80234CAC(&pPlayer->mUnknown1164[5], 0);
    }
    fn_80234A94(&pPlayer->mUnknown1164[6], pSlot->mpUnknown20);
    fn_80234CA4(&pPlayer->mUnknown1164[6], &pPlayer->mUnknown4064[2]);
    fn_80234A94(&pPlayer->mUnknown1164[7], pSlot->mpUnknown24);
    fn_80234A94(&pPlayer->mUnknown1164[8], pSlot->mpUnknown24);
    fn_80234CA4(&pPlayer->mUnknown1164[7], &pPlayer->mUnknown4064[3]);
    fn_80234CA4(&pPlayer->mUnknown1164[8], &pPlayer->mUnknown4064[3]);
    fn_80234A94(&pPlayer->mUnknown1164[9], pSlot->mpUnknown28);
    fn_80234CA4(&pPlayer->mUnknown1164[9], &pPlayer->mUnknown4064[4]);
    fn_80234A94(&pPlayer->mUnknown1164[11], pSlot->mpUnknown32);
    fn_80234CA4(&pPlayer->mUnknown1164[11], &pPlayer->mUnknown4064[5]);
    fn_80234A94(&pPlayer->mUnknown1164[1], pSlot->mpUnknown12);
    fn_80234CA4(&pPlayer->mUnknown1164[1], &pPlayer->mUnknown4064[0]);
    for (i = 0; i < 2; i++) {
        int part;
        int key;

        if (i == 0) {
            part = 2;
            key = 12;
        } else {
            part = 3;
            key = 13;
        }
        if (pPlayer->mUnknown116[i].mUnknown0 == 1 && pSlot->mUnknown8 == 0) {
            fn_80234A94(&pPlayer->mUnknown1164[part], pSlot->mpUnknown36[i]);
            fn_80234CA4(&pPlayer->mUnknown1164[part], &pPlayer->mUnknown4136[i]);
            fn_80233CBC(&pPlayer->mUnknown1164[part].mUnknown20, key, 0);
        } else {
            fn_80234A94(&pPlayer->mUnknown1164[part], pSlot->mpUnknown12);
            fn_80234CA4(&pPlayer->mUnknown1164[part], &pPlayer->mUnknown4064[0]);
            if (pSlot->mUnknown8 <= 1) {
                fn_80233CBC(&pPlayer->mUnknown1164[part].mUnknown20, key, fn_800ADDD8(pPlayer->mUnknown116, i));
            } else {
                fn_80233CBC(&pPlayer->mUnknown1164[part].mUnknown20, key, 0);
            }
        }
    }
}

void fn_801A31F0(Object_8003DEC4 *pPlayer)
{
    pPlayer->mUnknown4216.mUnknown24 = pPlayer->mUnknown1020;
    pPlayer->mUnknown4216.mpUnknown32 = &pPlayer->mUnknown908;
    pPlayer->mUnknown4216.mpUnknown28 = lbl_802F29C8;
    pPlayer->mUnknown4216.mUnknown36 = 0;
    fn_802341C4(&pPlayer->mUnknown4216);
}

void fn_801A323C(void)
{
    fn_80234424(0);
}

void fn_801A3260(Object_8003DEC4 *pPlayer)
{
    fn_802341E8(&pPlayer->mUnknown4216);
}

void fn_801A3284(Object_8003DEC4 *pPlayer)
{
    pPlayer->mUnknown1160 = &lbl_80365AB4[lbl_803ECC04];
    lbl_80365AB4[lbl_803ECC04].mpUnknown0 = pPlayer;
    lbl_803ECC04++;
}

void fn_801A32AC(int id, float sx, float sy, float tx, float ty)
{
    float m[4][4];

    m[0][0] = sx;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = tx;
    m[1][0] = 0.0f;
    m[1][1] = sy;
    m[1][2] = 0.0f;
    m[1][3] = ty;
    fn_802525F0(m, id, 1);
}

/* Texture offsets of the two eyes from the head angles of the pose. */
void fn_801A3300(Object_8003DEC4 *pPlayer, float *pA, float *pB)
{
    if (pPlayer->mUnknown20 & 0x80) {
        pB[0] = fn_80042F54((pPlayer->mUnknown44.mUnknown48[87] << 8) * (360.0f / 16777216.0f), 45.619f, -0.03f,
                            -45.619f, 0.03f);
        pA[0] = fn_80042F54((pPlayer->mUnknown44.mUnknown48[84] << 8) * (360.0f / 16777216.0f), 45.619f, -0.03f,
                            -45.619f, 0.03f);
        pB[1] = -fn_80042F54((pPlayer->mUnknown44.mUnknown48[88] << 8) * (360.0f / 16777216.0f), 47.028f, -0.1f,
                             -47.028f, 0.1f);
        pA[1] = -fn_80042F54((pPlayer->mUnknown44.mUnknown48[85] << 8) * (360.0f / 16777216.0f), 47.028f, -0.1f,
                             -47.028f, 0.1f);
    } else {
        pB[0] = 0.0f;
        pA[0] = 0.0f;
        pB[1] = 0.0f;
        pA[1] = 0.0f;
    }
}

void fn_801A34A4(Object_8003DEC4 *pPlayer)
{
    lbl_803EB818 = 1;
}

void fn_801A34B0(int a, int b, int c, int d)
{
    fn_802341AC();
    lbl_803ECC04 = 0;
    fn_8020F28C(&lbl_80365D54);
    fn_801A14D8();
    fn_801C1F94(lbl_802F3468, 0, sizeof(lbl_802F3468));
    lbl_802F3468[15] = 1;
    lbl_802F3468[21] = 1;
}

void fn_801A3514(void)
{
    lbl_803EB7F0 = 0;
}

void fn_801A3520(void)
{
    fn_802341B8();
    fn_8020F92C(&lbl_80365D54);
    lbl_80365D54.mUnknown0 = 0;
    fn_802145B0(lbl_80365D88);
    fn_801A1578();
    if (lbl_803ECC00) {
        fn_802284EC(lbl_803ECC00, fn_801A15C4);
        lbl_803ECC00 = 0;
    }
}

void fn_801A3588(Object_8003DEC4 *pPlayer, Creation_8003D378 *pInit)
{
    Model_8015E2FC *pModel;
    unsigned int i;

    pPlayer->mUnknown984 = 0;
    pPlayer->mUnknown988 = 0;
    pPlayer->mUnknown4968 = pInit->mUnknown57;
    pPlayer->mUnknown4969 = pInit->mUnknown58;
    pPlayer->mUnknown1016 = pInit->mUnknown34;
    pPlayer->mUnknown992 = pInit->mUnknown1C;
    pPlayer->mUnknown996 = pInit->mUnknown20.mUnknown0;
    pPlayer->mUnknown1000 = pInit->mUnknown20.mUnknown4;
    pPlayer->mUnknown1008 = pInit->mUnknown2C;
    pPlayer->mUnknown1004 = pInit->mUnknown28;
    pPlayer->mUnknown1012 = pInit->mUnknown30;
    pPlayer->mUnknown4971 = pInit->mUnknown5A;
    pPlayer->mUnknown4970 = pInit->mUnknown59;
    pPlayer->mUnknown4972 = pInit->mUnknown5B;
    fn_801442FC(pPlayer->mUnknown4960);
    pPlayer->mUnknown4976 = pInit->mUnknown5C;
    fn_801C2EF0(pPlayer->mUnknown4184, pInit->mUnknown38, 31);
    pPlayer->mUnknown1020 = fn_8015E440(0, pPlayer->mUnknown1016);
    pPlayer->mUnknown4060 = fn_8016102C(pInit->mUnknown5A);
    pModel = (Model_8015E2FC *)fn_8015E2FC(0, pPlayer->mUnknown1016, 0);
    fn_801A2A88(pPlayer, pInit->mInit.mUnknown04);
    fn_801A4690(0);
    fn_8015ED9C(pPlayer->mUnknown4970, pPlayer->mUnknown1012);
    fn_801A46BC();
    pPlayer->mUnknown976 |= 0x10;
    fn_801A3284(pPlayer);
    fn_80233BB8(&pPlayer->mUnknown4064[0], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[1], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[2], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[3], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[4], 0, 0);
    fn_80233BB8(&pPlayer->mUnknown4064[5], 0, 0);
    fn_80211FF0();
    fn_80212018("platex", fn_801A4AE4(pPlayer->mUnknown4971));
    fn_8023488C(pPlayer->mUnknown4044, 0x38);
    fn_80210214(pPlayer->mUnknown4044, pModel->mpUnknown24);
    fn_8023465C(pPlayer->mUnknown4044, pModel, fn_8016102C(pPlayer->mUnknown4971));
    fn_8023472C(pPlayer->mUnknown4044, 0x11, 1, &fn_8016102C(pPlayer->mUnknown4971)[25],
                &fn_8016102C(pPlayer->mUnknown4971)[25], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x12, 1, &fn_8016102C(pPlayer->mUnknown4971)[25],
                &fn_8016102C(pPlayer->mUnknown4971)[25], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1A, 1, &fn_8016102C(pPlayer->mUnknown4971)[26],
                &fn_8016102C(pPlayer->mUnknown4971)[26], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1B, 1, &fn_8016102C(pPlayer->mUnknown4971)[26],
                &fn_8016102C(pPlayer->mUnknown4971)[26], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x15, 1, &fn_8016102C(pPlayer->mUnknown4971)[27],
                &fn_8016102C(pPlayer->mUnknown4971)[27], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x16, 1, &fn_8016102C(pPlayer->mUnknown4971)[27],
                &fn_8016102C(pPlayer->mUnknown4971)[27], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1E, 1, &fn_8016102C(pPlayer->mUnknown4971)[28],
                &fn_8016102C(pPlayer->mUnknown4971)[28], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1F, 1, &fn_8016102C(pPlayer->mUnknown4971)[28],
                &fn_8016102C(pPlayer->mUnknown4971)[28], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x14, 1, &fn_8016102C(pPlayer->mUnknown4971)[29],
                &fn_8016102C(pPlayer->mUnknown4971)[29], 0);
    fn_8023472C(pPlayer->mUnknown4044, 0x1D, 1, &fn_8016102C(pPlayer->mUnknown4971)[30],
                &fn_8016102C(pPlayer->mUnknown4971)[30], 0);
    fn_801A4C1C(fn_8016102C(pPlayer->mUnknown4971), 0);
    fn_80211FF0();
    fn_801A299C(&pPlayer->mUnknown1164[0], 0, &pPlayer->mUnknown4064[0], pPlayer->mUnknown4044);
    fn_801A29F8(&pPlayer->mUnknown1164[4], pPlayer->mUnknown4044, pPlayer);
    fn_801A299C(&pPlayer->mUnknown1164[5], 0, &pPlayer->mUnknown4064[1], pPlayer->mUnknown4044);
    fn_801A299C(&pPlayer->mUnknown1164[6], 0, &pPlayer->mUnknown4064[2], pPlayer->mUnknown4044);
    fn_801A299C(&pPlayer->mUnknown1164[7], 0, &pPlayer->mUnknown4064[3], pPlayer->mUnknown4044);
    fn_801A299C(&pPlayer->mUnknown1164[8], 0, &pPlayer->mUnknown4064[3], pPlayer->mUnknown4044);
    fn_801A299C(&pPlayer->mUnknown1164[9], 0, &pPlayer->mUnknown4064[4], pPlayer->mUnknown4044);
    fn_801A299C(&pPlayer->mUnknown1164[1], 0, &pPlayer->mUnknown4064[0], pPlayer->mUnknown4044);
    fn_801A299C(&pPlayer->mUnknown1164[11], 0, &pPlayer->mUnknown4064[5], pPlayer->mUnknown4044);
    for (i = 0; i < 2; i++) {
        fn_80233BB8(&pPlayer->mUnknown4136[i], 0, 0);
        fn_801A299C(&pPlayer->mUnknown1164[2 + i], 0, &pPlayer->mUnknown4136[i], pPlayer->mUnknown4044);
    }
    fn_801A31F0(pPlayer);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 5, lbl_802F2934[5]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 7, lbl_802F2934[7]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 8, lbl_802F2934[8]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 9, lbl_802F2934[9]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 10, lbl_802F2934[10]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 11, lbl_802F2934[11]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 14, lbl_802F2934[14]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 15, lbl_802F2934[15]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 16, lbl_802F2934[16]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 17, lbl_802F2934[17]);
    fn_80233CBC(&pPlayer->mUnknown1164[0].mUnknown20, 18, lbl_802F2934[18]);
    fn_80233CBC(&pPlayer->mUnknown1164[4].mUnknown20, 1, lbl_802F2934[1]);
    fn_80233CBC(&pPlayer->mUnknown1164[4].mUnknown20, 2, lbl_802F2934[2]);
    fn_80233CBC(&pPlayer->mUnknown1164[4].mUnknown20, 3, lbl_802F2934[3]);
    fn_80233CBC(&pPlayer->mUnknown1164[5].mUnknown20, 4, lbl_802F2934[4]);
    fn_80233CBC(&pPlayer->mUnknown1164[6].mUnknown20, 0, lbl_802F2934[0]);
    fn_80233CBC(&pPlayer->mUnknown1164[7].mUnknown20, 27, 0);
    fn_80233CBC(&pPlayer->mUnknown1164[9].mUnknown20, 28, 0);
    fn_80233CBC(&pPlayer->mUnknown1164[11].mUnknown20, 29, 0);
    fn_80233CBC(&pPlayer->mUnknown1164[11].mUnknown20, 30, 0);
}

void fn_801A3C40(Object_8003DEC4 *pPlayer)
{
    Slot_801A3284 *pSlot = pPlayer->mUnknown1160;
    unsigned int flags;
    unsigned int lod;

    if (!lbl_803EB7F0) {
        fn_801A323C();
        lbl_803EB7F0 = 1;
    }
    flags = fn_801A28E8(pPlayer);
    fn_801C657C();
    fn_80228668();
    fn_801D0470();
    lod = pPlayer->mUnknown4216.mUnknown0;
    if ((pPlayer->mUnknown20 & 8) || (pPlayer->mUnknown20 & 0x400)) {
        lod = 0;
    }
    if (!(pPlayer->mUnknown20 & 8) && fn_800A2624()) {
        lod = 1;
    }
    if (pPlayer->mUnknown4216.mUnknown12 > lbl_803EB7EC) {
        flags |= 4;
    }
    if (lod <= 1) {
        pSlot->mpUnknown16 = &pPlayer->mUnknown1024[lod];
        if (lod == 0) {
            flags |= 8;
        }
    } else {
        pSlot->mpUnknown16 = 0;
    }
    if (pPlayer->mUnknown976 & 0x10) {
        fn_801A1400(pPlayer);
        pPlayer->mUnknown976 &= ~0x10;
    }
    pSlot->mpUnknown0 = pPlayer;
    pSlot->mpUnknown12 = fn_8015E2FC(0, pPlayer->mUnknown1016, lod);
    pSlot->mpUnknown20 = fn_8015E2FC(3, pPlayer->mUnknown4970, lod);
    pSlot->mpUnknown24 = fn_8015E2FC(7, pPlayer->mUnknown4970, lod);
    pSlot->mpUnknown28 = fn_8015E2FC(8, pPlayer->mUnknown4970, lod);
    pSlot->mpUnknown36[0] = fn_8015E2FC(1, pPlayer->mUnknown1016, 0);
    pSlot->mpUnknown36[1] = fn_8015E2FC(2, pPlayer->mUnknown1016, 0);
    pSlot->mpUnknown32 = fn_8015E2FC(9, pPlayer->mUnknown4970, 0);
    pSlot->mUnknown8 = lod;
    pSlot->mUnknown4 = flags;
    pSlot->mUnknown44 = (pPlayer->mUnknown20 >> 17) & 1;
    if (!(flags & 1)) {
        if ((pPlayer->mUnknown20 & 8) && !fn_8015D2E8(pPlayer)) {
            return;
        }
        if (lbl_803EB824 == 1) {
            fn_800A3B58(fn_8003E0C8(pPlayer), 1, lbl_803EB825);
            lbl_803EB824 = 0;
        }
        fn_801A2EC8(pPlayer, pSlot);
        if (fn_8015CD9C()) {
            Vector_801A1650 pos;

            fn_8015D3B0(pPlayer);
            fn_8015D32C(pPlayer, &pos);
            fn_801A209C(pPlayer, &pos.x, pPlayer->mUnknown908, 0, 0, pSlot->mpUnknown12, pSlot->mpUnknown36,
                        pSlot->mUnknown8);
        } else {
            fn_801A209C(pPlayer, 0, pPlayer->mUnknown908, 0, 0, pSlot->mpUnknown12, pSlot->mpUnknown36,
                        pSlot->mUnknown8);
        }
        fn_801A1978(pPlayer, pSlot->mUnknown4);
        if (pPlayer->mUnknown20 & 0x20000) {
            int count = 2;

            if (fn_800B823C(0) > 1 || fn_800B823C(1) > 1) {
                count = 0;
            }
            pSlot->mUnknown8 = 1;
            pSlot->mpUnknown12 = fn_8015E2FC(0, pPlayer->mUnknown1016, 1);
            pSlot->mpUnknown20 = fn_8015E2FC(3, pPlayer->mUnknown4970, pSlot->mUnknown8);
            fn_801A2EC8(pPlayer, pSlot);
            fn_801A1DEC(pPlayer, pSlot, count);
        }
    } else {
        fn_800C2150(pPlayer, &pPlayer->mUnknown280, 0);
    }
}

void fn_801A3F48(Object_8003DEC4 *pPlayer)
{
    unsigned int i;

    fn_801A2E90(pPlayer);
    fn_80234994(&pPlayer->mUnknown816);
    fn_802348AC(pPlayer->mUnknown4044);
    fn_80233BD8(&pPlayer->mUnknown4064[0]);
    fn_80233BD8(&pPlayer->mUnknown4064[1]);
    fn_80233BD8(&pPlayer->mUnknown4064[2]);
    fn_80233BD8(&pPlayer->mUnknown4064[3]);
    fn_80233BD8(&pPlayer->mUnknown4064[4]);
    fn_80233BD8(&pPlayer->mUnknown4064[5]);
    for (i = 0; i < 2; i++) {
        fn_80233BD8(&pPlayer->mUnknown4136[i]);
    }
    for (i = 0; i < 12; i++) {
        fn_80234A90(&pPlayer->mUnknown1164[i]);
    }
    fn_801A3260(pPlayer);
}

/* Draws the shadow quads of all players. */
void fn_801A3FFC(void)
{
    unsigned int i;
    int old;
    float m[4][4];

    fn_80210388();
    i = 0;
    old = fn_80236EC0(1);
    fn_8024EB28(0);
    fn_80252034(1, 4, 5, 5);
    fn_80252114(0);
    fn_802520E0(1, 3, 0);
    fn_80210CC4(0.01f, 0.01f);
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024CB90(11, 1);
    fn_8024D450(0, 11, 1, 5, 0);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
    fn_8024CB90(13, 1);
    fn_8024D450(0, 13, 1, 4, 0);
    fn_80251604(0, 0);
    fn_8024DF64(1);
    fn_8024DCE4(0, 1, 4, 60, 0, 125);
    fn_80251CC4(1);
    fn_80251B28(0, 0, 0, 4);
    fn_80210814(0, lbl_803ECC08, lbl_803ECC0C);
    fn_801D0F80(m);
    fn_8025251C(m, 0);
    fn_802525BC(0);
    for (; i < fn_8003DEB4(); i++) {
        Object_8003DEC4 *pPlayer = fn_8003DEC4(i);
        Projection_8003BA10 *pShadow = &pPlayer->mUnknown4256;

        if (pShadow->mUnknown673) {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
            int j;

            fn_8024E908(0xA0, 0, 4);
            r = pShadow->mColor[0] * 255.0f;
            g = pShadow->mColor[1] * 255.0f;
            b = pShadow->mColor[2] * 255.0f;
            a = pShadow->mColor[3] * 255.0f;
            for (j = 0; j < 4; j++) {
                GXPosition3f32(pShadow->mPoints[j][0], pShadow->mPoints[j][1], pShadow->mPoints[j][2]);
                GXColor4u8(r, g, b, a);
                GXTexCoord2f32(pShadow->mPairs[j].mX, pShadow->mPairs[j].mY);
            }
        }
    }
    fn_80210CC4(0.0f, 1.0f);
    fn_802520E0(1, 3, 1);
    fn_80236EC0(old);
}

/* Draws the clipped shadow polygons of all players. */
void fn_801A42D4(void)
{
    unsigned int i;
    int old;
    float m[4][4];

    fn_80210388();
    i = 0;
    old = fn_80236EC0(1);
    fn_8024EB28(0);
    fn_80252034(1, 4, 5, 5);
    fn_80252114(0);
    fn_802520E0(1, 3, 0);
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024CB90(11, 1);
    fn_8024D450(0, 11, 1, 5, 0);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
    fn_8024CB90(13, 1);
    fn_8024D450(0, 13, 1, 4, 0);
    fn_80251604(0, 0);
    fn_8024DF64(1);
    fn_8024DCE4(0, 1, 4, 60, 0, 125);
    fn_80251CC4(1);
    fn_80251B28(0, 0, 0, 4);
    fn_80210814(0, lbl_803ECC08, lbl_803ECC0C);
    fn_801D0F80(m);
    fn_8025251C(m, 0);
    fn_802525BC(0);
    for (; i < fn_8003DEB4(); i++) {
        Projection_8003BA10 *pShadow = &fn_8003DEC4(i)->mUnknown4256;
        unsigned char k;

        if (!pShadow->mUnknown673) {
            continue;
        }
        for (k = 0; k < pShadow->mUnknown672; k++) {
            Clip_8003BFCC *pClip = &pShadow->mRecords[k];
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
            int j;

            fn_8024E908(0xA0, 0, pClip->mCount);
            r = pShadow->mColor[0] * 255.0f;
            g = pShadow->mColor[1] * 255.0f;
            b = pShadow->mColor[2] * 255.0f;
            a = pShadow->mColor[3] * 255.0f;
            for (j = 0; j < pClip->mCount; j++) {
                GXPosition3f32(pClip->mPoints[j][0], pClip->mPoints[j][1], pClip->mPoints[j][2]);
                GXColor4u8(r, g, b, a);
                GXTexCoord2f32(pClip->mPairs[j].mX, pClip->mPairs[j].mY);
            }
        }
    }
    fn_80210CC4(0.0f, 1.0f);
    fn_802520E0(1, 3, 1);
    fn_80236EC0(old);
}

void fn_801A45CC(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        Object_8003DEC4 *pPlayer = fn_8003DEC4(i);

        if (pPlayer->mUnknown1160->mUnknown4 & 1) {
            continue;
        }
        if ((pPlayer->mUnknown20 & 8) && !fn_8015D2E8(pPlayer)) {
            continue;
        }
        if (pPlayer->mUnknown20 & 0x10000) {
            fn_8019723C(&pPlayer->mUnknown5188);
        }
    }
}

void fn_801A4650(Object_80228224 *pObject)
{
    lbl_803ECC00 = pObject;
    fn_80228474(pObject, 2, fn_801A15C4, 0);
}

void fn_801A4688(unsigned char enable)
{
    lbl_803EB7E8 = enable;
}

void fn_801A4690(int index)
{
    fn_802345BC(&lbl_803EB81C[index]);
}

void fn_801A46BC(void)
{
    fn_802345BC(0);
}

void fn_801A46E0(Object_8003DEC4 *pPlayer, int id, void (*pCallback)(Object_8003DEC4 *pPlayer))
{
    lbl_803EB810 = pCallback;
    lbl_803EB818 = 0;
    lbl_803EB814 = pPlayer;
    pPlayer->mUnknown992 = id;
    fn_8015F82C(id, pPlayer, fn_801A34A4);
}

void fn_801A472C(void)
{
    Object_8003DEC4 *pPlayer;
    short values[53];
    int a;
    int b;
    int i;

    if (!lbl_803EB814 || !lbl_803EB818) {
        return;
    }
    fn_801C1F94(values, 0, sizeof(values));
    pPlayer = lbl_803EB814;
    if (pPlayer->mUnknown992 == 0xFFFF) {
        fn_8015FFA8(fn_8015E2FC(6, 0, 0), fn_8015E2FC(5, 0, 0));
        fn_8015FFA8(fn_8015E2FC(6, 0, 1), fn_8015E2FC(5, 0, 1));
        for (i = 0; i < 53; i++) {
            values[i] = pPlayer->mUnknown4976.mValues[i] * 4096.0f;
        }
        values[pPlayer->mUnknown4972 + 1] = 0x1000;
        if (fn_80049D1C(pPlayer->mUnknown4971)) {
            values[6] = 0x1000;
        }
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        fn_8020F2C4(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(6, pPlayer->mUnknown4970, 0));
        fn_8020F2C4(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(6, pPlayer->mUnknown4970, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        fn_80233760(&pPlayer->mUnknown1024[0], values, 53);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 53);
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        fn_8020F2C4(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
        fn_8020F2C4(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        fn_8020F78C(&pPlayer->mUnknown1024[0].mUnknown16, lbl_803EB81C);
        fn_8020F78C(&pPlayer->mUnknown1024[1].mUnknown16, lbl_803EB81C);
        fn_801A4690(0);
        fn_801A46BC();
    } else {
        fn_8015FFA8(fn_8015E2FC(4, 0, 0), fn_8015E2FC(5, 0, 0));
        fn_8015FFA8(fn_8015E2FC(4, 0, 1), fn_8015E2FC(5, 0, 1));
        a = pPlayer->mUnknown1024[0].mUnknown16.mUnknown28;
        b = pPlayer->mUnknown1024[1].mUnknown16.mUnknown28;
        fn_8020F2C4(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(4, pPlayer->mUnknown4970, 0));
        fn_8020F2C4(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(4, pPlayer->mUnknown4970, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        values[1] = 0x1000;
        values[pPlayer->mUnknown4972 + 2] = 0x1000;
        if (fn_80049D1C(pPlayer->mUnknown4971)) {
            values[7] = 0x1000;
        }
        fn_80233760(&pPlayer->mUnknown1024[0], values, 37);
        fn_80233760(&pPlayer->mUnknown1024[1], values, 37);
        fn_8015E908(pPlayer->mUnknown1016);
        fn_8020F2C4(&pPlayer->mUnknown1024[0].mUnknown16, fn_8015E2FC(5, 0, 0));
        fn_8020F2C4(&pPlayer->mUnknown1024[1].mUnknown16, fn_8015E2FC(5, 0, 1));
        pPlayer->mUnknown1024[0].mUnknown16.mUnknown28 = a;
        pPlayer->mUnknown1024[1].mUnknown16.mUnknown28 = b;
        fn_8020F78C(&pPlayer->mUnknown1024[0].mUnknown16, lbl_803EB81C);
        fn_8020F78C(&pPlayer->mUnknown1024[1].mUnknown16, lbl_803EB81C);
        fn_801A4690(0);
        fn_8015F3FC(0);
        fn_801A46BC();
    }
    lbl_803EB810(pPlayer);
    lbl_803EB818 = 0;
    lbl_803EB810 = 0;
    lbl_803EB814 = 0;
}
}
