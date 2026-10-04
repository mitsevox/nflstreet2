#include "engine/cu_80227F14.h"
#include "game/Class_801CBC50.h"
#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/cu_80003F10.h"
#include "game/cu_80026BB0.h"
#include "game/cu_8007C9D4.h"
#include "game/fn_8003B6BC.h"
#include "game/fn_8007F828.h"
#include "game/fn_8017F584.h"
#include "game/fn_80191804.h"
#include "game/fn_80218FC4.h"

extern "C" {
extern char lbl_80306B34[];
extern float lbl_803EA2C4;
extern void *lbl_803EB688;
extern void *lbl_803EB690;

int fn_80003F30(void);
void fn_80010150(int a);
int fn_80010194(void);
void fn_80011600(int a, int b, int c);
void fn_80014294(int a, int b);
void fn_8001442C(void);
void fn_80015D28(int a);
int fn_80015F2C(void);
void fn_8001B228(void);
void fn_80022778(void);
void fn_800244E4(void);
void fn_80024560(void);
void fn_80024608(void);
int fn_80033124(void *p);
void fn_8003E1F0(void);
int fn_8005FC7C(void);
int fn_800602E8(void);
int fn_80061AD4(void);
int fn_80061CAC(void);
void fn_80062A58(unsigned char a);
int fn_80066D74(unsigned int id, int a, int b, int c, int d, int e);
void fn_80066DC8(unsigned int id, int a);
void fn_8006CA84(int a);
void fn_8006EC24(void);
void fn_80072AA8(void);
void fn_80072C90(int a, int b);
void fn_800731D0(int a);
void fn_8007F328(int a);
void fn_8007F374(void);
void fn_8009418C(void);
void fn_8013CF98(void);
void fn_8015CDA4(void);
void fn_801801E8(int a);
void fn_80186EF4(void);
void fn_80187C0C(void);
void fn_80187FDC(void);
void fn_8018807C(int a);
void fn_80188E14(void);
void fn_80188E8C(void);
void fn_8018A4BC(int a, unsigned int id, float value);
void fn_8018A740(void);
void fn_80194E04(void);
int fn_801C601C(int a);
int fn_801C60BC(int a);
int fn_801C6280(int a, int b, void *pValue);
void fn_801C3A3C(float a);
void fn_801CAF24(void);
int fn_801CBEF4(void *p, int a, int b);
void fn_801CE82C(void);
void fn_801CE910(void);
int fn_801CEB4C(void);
void fn_801D6F58(void);
void fn_801F2798(const char *pText);
void fn_8021956C(void *p, int a, int b, int c);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_8021D7B8(void *a, int b, int c, int *d);
int fn_802294F4(void);
int fn_80229554(void);
void fn_802297B0(void);
int fn_80232FD4(Record_8003B6BC *pRecord0, Record_8003B6BC *pRecord1);
}

static unsigned char sUnknown803EA2D8 = 0;
static unsigned char sUnknown803EA2D9 = 0;
static unsigned int sUnknown803EA2DC = 0;
static unsigned char sUnknown803EA2E0 = 0;
static FELoopCallback sCallback = 0;
static void *sDependencies[] = { 0 };
static unsigned char sUnknown803EA2EC = 0;
static unsigned int sUnknown803EC5EC;
static unsigned char sUnknown803EC5F0;

FELoop gFELoop;

static void fn_800273AC()
{
    Arg_80218FC4 arg;
    void *p;

    fn_801801E8(1);
    p = lbl_803EB688;
    arg.mUnknown0 = 0;
    if (sUnknown803EA2EC) {
        arg.mUnknown4 = 100;
    } else {
        arg.mUnknown4 = 101;
    }
    fn_80218FC4(p, 0, 2, 2, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_8002742C()
{
    Arg_80218FC4 arg;
    void *p;

    fn_801801E8(1);
    p = lbl_803EB688;
    arg.mUnknown0 = 0;
    arg.mUnknown4 = 100;
    fn_80218FC4(p, 0, 2, 2, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_80027494()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = 1;
    fn_80010150(8);
    fn_80218FC4(lbl_803EB688, 11, 1, 1, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_800274F4()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = 1;
    fn_80010150(6);
    fn_80218FC4(lbl_803EB688, 8, 2, 1, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_80027554()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = fn_800602E8() ? 401 : 1;
    fn_80010150(7);
    fn_80218FC4(lbl_803EB688, 12, 0, 1, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_800275C4()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = 123;
    fn_80010150(7);
    fn_80218FC4(lbl_803EB688, 12, 0, 1, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_80027624()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = 604;
    fn_80010150(7);
    fn_80218FC4(lbl_803EB688, 12, 0, 1, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_80027684()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = 1;
    fn_80010150(11);
    fn_80218FC4(lbl_803EB688, 7, 17, 1, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_800276E4()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = 700;
    fn_80010150(9);
    fn_80218FC4(lbl_803EB688, 13, 0, 1, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_80027744()
{
    Arg_80218FC4 arg;

    fn_80027E3C();
    arg.mUnknown0 = 1;
    arg.mUnknown4 = 109;
    fn_80218FC4(lbl_803EB688, 0, 2, 2, &arg);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
}

static void fn_800277A8(int mode)
{
    fn_80027E18(0);
    switch (mode) {
    case 3:
    case 4:
    case 5:
    case 13:
        break;
    case 9:
        fn_800276E4();
        break;
    case 6:
        fn_800274F4();
        break;
    case 0:
        fn_8002742C();
        break;
    case 2:
        fn_80027744();
        break;
    case 8:
        fn_80027494();
        break;
    case 7:
        fn_8005FC7C();
        fn_80027554();
        break;
    case 10:
        fn_80061AD4();
        if (fn_80061CAC()) {
            fn_80027624();
        } else {
            fn_800275C4();
        }
        break;
    case 11:
        fn_80027684();
        break;
    default:
        if (fn_80003F18()) {
            fn_80003F10(0);
        }
        fn_800273AC();
        break;
    }
    fn_80027E34(0);
}

static void fn_800278B8(int a, int b, float c)
{
    if (b == 0x46) {
        sUnknown803EC5F0 = 0;
    }
    fn_80191804(a, b, c);
    if (!gFMCAPPORT.IsBusy()) {
        fn_8018A4BC(a, b, c);
    }
    fn_8018A740();
    if (b != 0x8F) {
        fn_80062A58(0);
        sUnknown803EA2DC = 0;
    }
}

static void fn_80027950()
{
    fn_801C6280(-1, 1, (void *)fn_800278B8);
    fn_800271A4();
    fn_8007F374();
    fn_80024560();
    fn_8007F328(0);
    fn_8006EC24();
    fn_80072AA8();
    fn_801C6280(-1, 1, 0);
}

void FELoop::fn_800279AC()
{
    fn_801F2798("FELoopBootStart");
    fn_80027950();
    fn_80187FDC();
    if (fn_8007F828(6) == 1 || fn_801CEB4C() == 1) {
        fn_801C3A3C(4.0f / 3.0f);
    } else {
        fn_8013CF98();
    }
    fn_80186EF4();
    fn_800244E4();
    fn_801F2798("FELoopBootFinish");
}

void fn_80027A20()
{
    if (sUnknown803EC5F0) {
        Record_8003B6BC record0;
        Record_8003B6BC record1;

        sUnknown803EC5F0 = 0;
        fn_8001B228();
        fn_800731D0(1);
        fn_8003B6BC(0, &record0);
        fn_800731D0(1);
        fn_8003B6BC(1, &record1);
        fn_800731D0(1);
        fn_80232FD4(&record0, &record1);
        fn_800731D0(1);
        fn_8007CA28();
        fn_8021956C(lbl_803EB690, 1, 5, 1);
        fn_800731D0(1);
        fn_801CBEF4(&lbl_803067B0, 2, 12);
    }
}

void fn_80027AD8(int a, int b, int c, int d, int e, int f)
{
    fn_80010150(a);
    if (b == -1 && c == -1) {
        fn_80011600(-1, -1, 0);
    } else {
        fn_80011600(b, c, 1);
    }
    fn_80014294(d, e);
    fn_80015D28(f);
}

ModuleDependency *FELoop::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *FELoop::GetLinks() { return 0; }
const char *FELoop::GetName() { return "FELoop"; }

int FELoop::Init()
{
    fn_8018807C(0);
    fn_801C6280(-1, 1, (void *)fn_800278B8);
    fn_800271A4();
    fn_80066D74(0x31544250, 2, 4, 0, 0, 1);
    fn_80066D74(0x31444250, 1, 4, 0, 0, 0);
    sUnknown803EC5F0 = 1;
    fn_80187C0C();
    if (sUnknown803EA2D9 == 1) {
        if (sUnknown803EA2D8 != 3) {
            fn_802297B0();
        }
    } else if (fn_802294F4() == 1) {
        fn_802297B0();
        fn_80027E3C();
    }
    sUnknown803EC5EC = fn_8017F584();
    fn_80188E14();
    fn_800277A8(sUnknown803EC5EC);
    sUnknown803EA2DC = 0;
    sUnknown803EA2E0 = 0;
    return 1;
}

unsigned char FELoop::fn_80027C58()
{
    unsigned short a;
    unsigned short b;
    int flag = 1;

    fn_80024608();
    fn_8018A740();
    fn_801D6F58();
    fn_801C601C(-1);
    fn_801C60BC(-1);
    fn_80022778();
    fn_8003E1F0();
    fn_8015CDA4();
    gFMCAPPORT.Update();
    fn_80219650(lbl_803EB688, &a, &b);
    if (a == 0 && b == 7) {
        fn_8001442C();
    }
    fn_80194E04();
    if (flag) {
        fn_802285CC();
        fn_801CAF24();
        fn_8006CA84(1);
        fn_801CE82C();
        if (sCallback) {
            sCallback();
        }
        if (fn_80010194() || fn_80015F2C()) {
            if (++sUnknown803EA2DC > (int)(60.0f / lbl_803EA2C4) * 75) {
                fn_8021D7B8(lbl_803EB688, 0x80000038, 0, 0);
                fn_80072C90(0xFA, 1);
                sUnknown803EA2E0 = 1;
            }
        }
    }
    return sUnknown803EC5F0;
}

int FELoop::Shutdown()
{
    fn_80188E8C();
    fn_801CE910();
    fn_80066DC8(0x31544250, 0);
    fn_80066DC8(0x31444250, 0);
    fn_8009418C();
    fn_801C6280(-1, 1, 0);
    sUnknown803EA2DC = 0;
    sUnknown803EA2E0 = 0;
    return 1;
}

int fn_80027DF0()
{
    return fn_80033124(lbl_80306B34);
}

void fn_80027E18(unsigned char value)
{
    if (sUnknown803EA2EC) {
        sUnknown803EA2D9 = value;
    } else {
        sUnknown803EA2D9 = 0;
    }
}

void fn_80027E34(unsigned char value)
{
    sUnknown803EA2D8 = value;
}

void fn_80027E3C()
{
    fn_80027E18(0);
    if (fn_802294F4() == 1) {
        if (fn_8007CAE4()) {
            fn_8007CAB4();
        }
        fn_80229554();
    }
    sUnknown803EC5EC = fn_8017F584();
}

void fn_80027E88(unsigned char value)
{
    sUnknown803EA2EC = value;
}

unsigned char fn_80027E90()
{
    return sUnknown803EA2EC;
}

void fn_80027E98(FELoopCallback pCallback)
{
    sCallback = pCallback;
}

void fn_80027EA0()
{
    sUnknown803EA2DC = 0;
}

unsigned char fn_80027EAC()
{
    return sUnknown803EA2E0;
}

void fn_80027EB4()
{
    if (sUnknown803EC5F0) {
        fn_80003F30();
    }
}
