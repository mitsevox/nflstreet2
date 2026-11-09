#include "game/Block_8030E6E8.h"
#include "game/GameCamera.h"
#include "game/ResOpenDevice.h"
#include "game/LevelSurface.h"
#include "game/cu_801444D8.h"
#include "game/LevelData.h"

extern "C" {
GameCamera_t *CamGameGetCamera(int index);
int CamGameGetCurrentSlot(void);
unsigned char fn_8002FA84(void);
unsigned char fn_80140DB4(void);
int fn_801784C4(void);

extern unsigned char lbl_803EA9F8;
extern Block_8030E6E8 lbl_8030E6E8;
}

extern "C" void fn_800A233C(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.0f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[1] = 1;
    lbl_8030E6E8.mUnknown8C4 = 9;
}

extern "C" void fn_800A238C(void)
{
    lbl_8030E6E8.mUnknown28 = 15.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.3f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown6C[1] = 0;
    lbl_8030E6E8.mUnknown6C[2] = 0;
    lbl_8030E6E8.mUnknown8C4 = 7;
}

extern "C" void fn_800A23F0(void)
{
    lbl_8030E6E8.mUnknown28 = 15.0f;
    lbl_8030E6E8.mUnknown2C = 30.045f;
    lbl_8030E6E8.mUnknown30 = 40.2f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.03f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown8B4[4] = 1;
    lbl_8030E6E8.mUnknown8C4 = 2;
}

extern "C" void fn_800A244C(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.0f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown8B4[4] = 1;
    lbl_8030E6E8.mUnknown8C4 = 5;
}

extern "C" void fn_800A24A0(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.0f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown6C[1] = 0;
    lbl_8030E6E8.mUnknown6C[2] = 1;
    lbl_8030E6E8.mUnknown8C4 = 6;
}

extern "C" void fn_800A2500(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 49.7f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[3] = 1;
    lbl_8030E6E8.mUnknown6C[6] = 7;
    lbl_8030E6E8.mUnknown6C[7] = 1;
    lbl_8030E6E8.mUnknown8C4 = 10;
}

extern "C" void fn_800A2560(void)
{
    lbl_8030E6E8.mUnknown28 = 17.5f;
    lbl_8030E6E8.mUnknown2C = 30.0f;
    lbl_8030E6E8.mUnknown30 = 40.2f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[6] = 1;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown8C4 = 11;
}

extern "C" void fn_800A25BC(void)
{
    lbl_8030E6E8.mUnknown28 = 17.5f;
    lbl_8030E6E8.mUnknown2C = 30.0f;
    lbl_8030E6E8.mUnknown30 = 39.5f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown6C[1] = 7;
    lbl_8030E6E8.mUnknown6C[2] = 1;
    lbl_8030E6E8.mUnknown8C4 = 8;
}

extern "C" int fn_800A262C(void)
{
    if (CamGameGetCamera(5)->mHeader.mUnknown04[1] <= 0.5f - lbl_8030E6E8.mUnknown2C && CamGameGetCurrentSlot() == 0
        && fn_8002FA84() == 0 && fn_801784C4() == 0 && (fn_801784C4() != 0 || fn_80140DB4() == 0)) {
        lbl_803EA9F8 = 1;
        return 1;
    }
    lbl_803EA9F8 = 0;
    return 0;
}

extern "C" int fn_800A26C4(void)
{
    if (CamGameGetCamera(5)->mHeader.mUnknown04[1] > lbl_8030E6E8.mUnknown2C - 0.5f && CamGameGetCurrentSlot() == 0
        && fn_8002FA84() == 0 && fn_801784C4() != 0 && (fn_801784C4() == 0 || fn_80140DB4() == 0)) {
        lbl_803EA9F8 = 1;
        return 1;
    }
    lbl_803EA9F8 = 0;
    return 0;
}

extern "C" {
int fn_800A2760(void);
int EnvGetEVTL(void);
float EnvGetEVPL(void);
float EnvGetEVPF(void);
float EnvGetEVWD(void);
float EnvGetEVWL(void);
int EnvGetEVDS(void);
float EnvGetEVED(void);
int EnvIsENVFSet(void);
int fn_800A33B0(void);
float fn_80237260(int stream);
int MathAngleDiff(int a, int b);
void ScreenTintSetActive(int index, unsigned char value);
void ScreenTintSetMode(int index, int value);
void ScreenTintFadeTo(int index, unsigned int color, float value, unsigned int count);

extern unsigned char lbl_802D7D90[][4];
extern int lbl_802D7DC0[];

void EnvSelect(int id);
void EnvRelease(void);
void fn_800A29AC(void);
void fn_800A29D8(int mode);
void fn_800A2D2C(void);
EnvFogSettings *EnvGetFogSettings(int index);
void fn_8005406C(void);
void *fn_800C47C4(void);
void fn_801464D0(void *owner);
void fn_80146BF8(float value);
void fn_801D03D0(float *pMatrix);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0BCC(int z, int y, int x);
void fn_801D0C58(void *p);
void fn_801D0F80(float m[4][4]);
unsigned char CheatFlagsIsSet(int index);
unsigned int fn_8017F584(void);

extern LevelData_t *gLevelData;

extern char lbl_802EBFB4[];
extern Vector_80039F5C lbl_802D7C70[];
extern Vector_80039F5C lbl_802D7D00[];
extern unsigned char lbl_802D7DF0[][4];
extern unsigned char lbl_803EA9F0;
extern void *lbl_803EA9F4;
extern Callbacks_8030E6DC lbl_8030E6DC;
}

extern "C" void fn_800A2848(void)
{
    int first = fn_800A2760();

    lbl_8030E6E8.mUnknown4 = first;
    lbl_8030E6E8.mUnknown6 = first + 1;
    lbl_8030E6E8.mUnknown8 = first + 2;
    lbl_8030E6E8.mUnknownA = first + 3;
    lbl_8030E6E8.mUnknownC = first + 8;
    lbl_8030E6E8.mUnknownE = first + 9;
    lbl_8030E6E8.mUnknown40 = EnvGetEVTL();
    lbl_8030E6E8.mUnknown4C = EnvGetEVPL();
    lbl_8030E6E8.mUnknown50 = EnvGetEVPF();
    lbl_8030E6E8.mUnknown54 = (int)(EnvGetEVWD() * 46603.379f);
    lbl_8030E6E8.mUnknown58 = EnvGetEVWL();
    lbl_8030E6E8.mUnknown64 = EnvGetEVDS();
    lbl_8030E6E8.mUnknown68 = EnvGetEVED();
    lbl_8030E6E8.mUnknown3C = EnvIsENVFSet();
    switch (lbl_8030E6E8.mUnknown40) {
    case 0:
        lbl_8030E6E8.mUnknown44 = 31;
        break;
    case 1:
        lbl_8030E6E8.mUnknown44 = 45;
        break;
    case 2:
        lbl_8030E6E8.mUnknown44 = 68;
        break;
    case 3:
        lbl_8030E6E8.mUnknown44 = 95;
        break;
    }
    if (lbl_8030E6E8.mUnknown4C <= 0.01f) {
        lbl_8030E6E8.mUnknown48 = 0;
    } else if (lbl_8030E6E8.mUnknown40 == 0) {
        lbl_8030E6E8.mUnknown48 = 1;
    } else {
        lbl_8030E6E8.mUnknown48 = 2;
    }
    lbl_8030E6E8.mUnknown8BC = 0;
    lbl_8030E6E8.mUnknown5C = lbl_8030E6E8.mUnknown54;
    lbl_8030E6E8.mUnknown60 = lbl_8030E6E8.mUnknown58;
    lbl_8030E6E8.mUnknown8BD = 0;
}

extern "C" void fn_800A2B40(void)
{
    if (fn_800A33B0()) {
        float drift = fn_80237260(1) * 0.033333335f;
        drift += fn_80237260(1) * 0.033333335f;
        int turn = (int)(fn_80237260(1) * 38.0f);
        turn += (int)(fn_80237260(1) * 38.0f);
        float roll = fn_80237260(1) * 2.0f;

        if (lbl_8030E6E8.mUnknown60 < lbl_8030E6E8.mUnknown58) {
            if (roll >= 0.5f) {
                lbl_8030E6E8.mUnknown60 += drift;
            } else {
                lbl_8030E6E8.mUnknown60 -= drift;
            }
        } else if (roll < 0.5f) {
            lbl_8030E6E8.mUnknown60 += drift;
        } else {
            lbl_8030E6E8.mUnknown60 -= drift;
        }
        lbl_8030E6E8.mUnknown60 = lbl_8030E6E8.mUnknown60 < 0.0f ? 0.0f
            : (lbl_8030E6E8.mUnknown60 > 1.0f ? 1.0f : lbl_8030E6E8.mUnknown60);

        roll = fn_80237260(1) * 2.0f;
        if (lbl_8030E6E8.mUnknown5C - lbl_8030E6E8.mUnknown54 != MathAngleDiff(lbl_8030E6E8.mUnknown5C, lbl_8030E6E8.mUnknown54)) {
            if (roll >= 0.5f) {
                lbl_8030E6E8.mUnknown5C = (lbl_8030E6E8.mUnknown5C + turn) & 0xFFFFFF;
            } else {
                lbl_8030E6E8.mUnknown5C = (lbl_8030E6E8.mUnknown5C - turn) & 0xFFFFFF;
            }
        } else if (roll < 0.5f) {
            lbl_8030E6E8.mUnknown5C = (lbl_8030E6E8.mUnknown5C + turn) & 0xFFFFFF;
        } else {
            lbl_8030E6E8.mUnknown5C = (lbl_8030E6E8.mUnknown5C - turn) & 0xFFFFFF;
        }
        lbl_8030E6E8.mUnknown5C = lbl_8030E6E8.mUnknown5C < 0 ? 0
            : (lbl_8030E6E8.mUnknown5C > 0x1000000 ? 0x1000000 : lbl_8030E6E8.mUnknown5C);
    }
}

extern "C" void fn_800A2E80(int index, int count)
{
    ScreenTintSetActive(0, 1);
    ScreenTintFadeTo(0, (lbl_802D7D90[index][2] << 16) + (lbl_802D7D90[index][1] << 8) | lbl_802D7D90[index][0],
                (unsigned int)lbl_802D7D90[index][3] * (1.0f / 255.0f), count);
    ScreenTintSetMode(0, lbl_802D7DC0[index]);
}

extern "C" void fn_800A2F48(void)
{
    EnvSelect(lbl_8030E6E8.mUnknown0);
    fn_800A2848();
    fn_800A29AC();
    lbl_8030E6E8.mpUnknown8C0 = EnvGetFogSettings(lbl_8030E6E8.mUnknown0);
    lbl_8030E6DC.mpCallback0 = 0;
    lbl_8030E6DC.mpCallback4 = 0;
    lbl_8030E6DC.mpCallback8 = 0;
    lbl_8030E6E8.mVector10 = lbl_802D7C70[lbl_8030E6E8.mUnknown0];
    lbl_8030E6E8.mUnknown1C = lbl_802D7D00[lbl_8030E6E8.mUnknown0];
    lbl_803EA9F4 = ResOpenDevice(lbl_802EBFB4, 44);
    fn_8005406C();
    fn_801464D0(fn_800C47C4());
    fn_80146BF8(1.0f - lbl_8030E6E8.mpUnknown8C0->mUnknownC);
    fn_800A2D2C();
    fn_800A29D8(lbl_8030E6E8.mUnknown0);
    lbl_8030E6E8.mUnknown28 = 10.0f;
    lbl_8030E6E8.mUnknown2C = 30.0f;
    lbl_8030E6E8.mUnknown30 = 40.0f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mUnknown8C4 = 0;
    if (lbl_8030E6DC.mpCallback0 != 0) {
        lbl_8030E6DC.mpCallback0();
    }
    lbl_8030E6E8.mpUnknown8C8 = lbl_802D7DF0[lbl_8030E6E8.mUnknown0];
    fn_800A2E80(lbl_8030E6E8.mUnknown0, 1);
    EnvRelease();
    lbl_803EA9F0 = 1;
}

extern "C" void fn_800A3170(void)
{
    float m[4][4];
    Args_80144CE0 args;
    unsigned char i;

    for (i = 0; i < gLevelData->mUnknown96; i++) {
        LevelPlacement_t *pEntry = &gLevelData->mUnknown100[i];

        fn_801D03D0(m[0]);
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        fn_801D0508();
        fn_801D0C58(pEntry->mUnknown0);
        fn_801D0BCC((int)(pEntry->mUnknown0[5] * 46603.379f), (int)(pEntry->mUnknown0[4] * 46603.379f),
                    (int)(pEntry->mUnknown0[3] * 46603.379f));
        fn_801D0F80(lbl_8030E6E8.mUnknown134[i]);
        fn_801D0544();
        args.mUnknown04 = &lbl_8030E6E8.mUnknown134[i];
        args.mUnknown0C = 0;
        args.mUnknown10 = 0;
        args.mUnknown08 = &m;
        args.mUnknown00 = pEntry->mUnknown24 + 8;
        Source_80144CE0 *pSource = (Source_80144CE0 *)LevelFindArea(pEntry->mUnknown0);
        lbl_8030E6E8.mpUnknownBC[i] = fn_80144CE0(&args, 0, pSource);
    }
}

extern "C" float fn_800A32E4(void)
{
    if (CheatFlagsIsSet(27) != 0 && fn_8017F584() == 0) {
        return 10.0f;
    }
    if (CheatFlagsIsSet(26) != 0 && fn_8017F584() == 0) {
        return lbl_8030E6E8.mUnknown2C * 2.0;
    }
    return lbl_8030E6E8.mFloat38;
}
