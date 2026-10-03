#include "game/Class_801CBC50.h"
#include "game/InGame.h"
#include "game/TimeScale.h"
#include "game/ModuleGroup_80033A5C.h"

extern "C" {
double fabs(double);
extern char lbl_8030716C[];
extern char lbl_803072C4[];
extern float lbl_803EA2C4;
extern void *lbl_803EA368;
extern void *lbl_803EAA8C;
extern void *lbl_803EAB90;
extern void *lbl_803EB688;
extern void *lbl_803EB690;

int fn_80026CC4(int a);
void fn_80026DD4(int a);
void fn_8002728C(int (*pCallback)());
char *fn_8002739C(void);
int fn_800273A4(void);
void fn_8002B598(void);
void fn_8002CBB0(void *p, int a, float c, int b);
void fn_8002CF34(void *p);
int fn_8002D060(void *p);
int fn_8002D2C0(void);
void fn_8003B6BC(int a, struct Record_8003B6BC *pRecord);
void fn_8003E1F0(void);
void fn_80043F50(void);
void fn_80057F28(void);
void fn_800582D0(void);
void fn_8005BF18(void);
void fn_80062A58(unsigned char a);
void fn_80065194(void);
void fn_800652A8(void);
int fn_8006560C(void);
void fn_8006587C(int a, int b, float c);
void fn_80066D5C(void);
void fn_80067D4C(int a, int b);
void fn_8006CA84(int a);
void fn_800726B8(void);
void fn_800728F8(void);
void fn_80072C90(int a, int b);
void fn_8007F394(int a);
void fn_8007F6F8(int a, int b);
int fn_8007F828(int a);
void fn_80085A7C(void);
void fn_80085AA0(int a, struct Record_8003B6BC *pRecord0, int b, struct Record_8003B6BC *pRecord1);
void fn_80089754(void);
void fn_8008FE5C(int a);
void fn_80099568(int a);
void fn_800A216C(int a);
void fn_800A3120(float a);
void fn_800A7F6C(void);
void fn_800A8EB8(void);
int fn_800A937C(void);
void fn_800A9478(int a);
int fn_800A9680(void);
void fn_800AB944(void *p);
void fn_800AD888(float a);
void fn_800AD910(int a, float b);
int fn_800AD9B4(void);
void fn_800AE8B4(void);
void fn_800AFD58(int a, int b, float c);
void fn_800B3AF4(float a);
void fn_800B410C(void);
void fn_800B4184(int a);
int fn_800BA6F8(void);
void fn_800BCF7C(void *p);
int fn_800C1E40(void);
void fn_800C1E50(void);
int fn_800C8704(int *pA, int *pB);
void fn_80139168(void);
void fn_8013CF98(void);
void fn_8013FC58(void);
int fn_8013FCD4();
void fn_80144EDC(float a);
void fn_80145E64(float a);
void fn_80173C2C(void);
void fn_80173D10(void);
void fn_80176C58(void);
void fn_80176C90(void);
int fn_8017CEDC(float a);
unsigned int fn_8017F584(void);
void fn_8017F664(void);
void fn_80187C0C(void);
void fn_8018A4BC(int a, unsigned int id, float value);
void fn_8018A6C4(int a, int b);
void fn_8018A710(int a, int b);
void fn_8018A740(void);
void fn_80191804(void);
void fn_80191808(void);
void fn_8019180C(void);
void fn_80194AEC(int a);
void fn_80194D20(void);
void fn_80194DB8(void);
void fn_80194E04(void);
void fn_80194F1C(int a);
void fn_80195F80(void);
void fn_80196130(void);
void fn_8019A9A0(int a, int b, float c);
int fn_801C601C(int a);
int fn_801C60BC(int a);
int fn_801C6280(int a, int b, void *pValue);
int fn_801C6458(int a, int b);
void fn_801CAF24(void);
int fn_801CBE9C(void *p, int a);
void fn_801CE82C(void);
void fn_801CE910(void);
void fn_801D6F58(void);
int fn_801E15D0(int a);
int fn_801E17D0(int a, char *p);
void fn_801E1C38(unsigned char a);
int fn_801E1CE0(unsigned char a);
float fn_801EC418(int a, int b, char *p);
int fn_801FCE10(int a, const char *pFormat, ...);
void fn_80218FC4(void *p, int a, int b, int c, int d);
void fn_8021956C(void *p, int a, int b, int c);
void fn_802285CC(void);
void fn_802345C4(struct Desc_802345C4 *pDesc, int count);
void fn_80236F34(void);
void fn_80237830(int a);
unsigned int fn_802378C8(void);
int fn_802399F8(void);
void fn_80239CEC(int a, int b);
}

/* Record copied out by fn_8003B6BC. */
struct Record_8003B6BC {
    int mUnknown[14];
};

/* Argument of fn_802345C4. */
struct Desc_802345C4 {
    int mUnknown0;
    int mUnknown4;
};

static unsigned char sUnknown803EA2F0 = 0;
/* Called by fn_8002854C when non-null. */
static void (*sCallback)() = 0;
static unsigned char sUnknown803EA2F8 = 0;
static unsigned int sUnknown803EA2FC = 0;
static unsigned char sUnknown803EA300 = 0;
static unsigned char sUnknown803EC5F4;
static int sUnknown803EC5F8;
static int sUnknown803EC5FC;
static int sUnknown803EC600;

static ModuleDependency sDependencies[] = { &gUIS, lbl_8030716C, lbl_803072C4, 0 };
InGame gInGame;

static void fn_80027FE0(int a, int b, float c)
{
    fn_80191804();
    if (b != 0x8F) {
        sUnknown803EA2FC = 0;
    }
    if (sUnknown803EC600 == 0) {
        fn_8019A9A0(a, b, c);
        if (b != 0x8F) {
            fn_800AFD58(a, b, c);
            fn_8006587C(a, b, c);
            if (!fn_8002D060(lbl_803EA368) || fn_8002D2C0()) {
                fn_8018A4BC(a, b, c);
            } else {
                fn_8002CBB0(lbl_803EA368, a, c, b);
            }
        }
    } else if (b != 0x8F) {
        if (!fn_8002D060(lbl_803EA368) || fn_8002D2C0()) {
            fn_8018A4BC(a, b, c);
        } else {
            fn_8002CBB0(lbl_803EA368, a, c, b);
        }
    }
    if (!fn_8006560C() || fn_8002D060(lbl_803EA368) || b == 0x8F) {
        fn_8006560C();
    } else {
        fn_8018A740();
    }
    if (sUnknown803EA2F0 == 1) {
        fn_800652A8();
        sUnknown803EA2F0 = 0;
    }
}

static void fn_80028244();
static void fn_800282B8();

static void fn_80028140(int a)
{
    char *p;
    int count;
    int handle;
    int i;
    int done;

    fn_80026DD4(a);
    p = fn_8002739C();
    count = fn_800273A4();
    handle = fn_801C6458(a, 0);
    fn_801E1C38(handle);
    if (fn_801E1CE0(handle)) {
        fn_801E15D0(handle);
        fn_801E17D0(handle, p);
        fn_800282B8();
        if (sUnknown803EA2F8 && fn_80026CC4(handle)) {
            done = 0;
            for (i = 0; i < count; i++) {
                float value = fabs(fn_801EC418(handle, i, p + 8));

                if (value <= 0.5f || done) {
                    continue;
                }
                done = 1;
                fn_80028244();
            }
        }
    }
}

static void fn_80028238() {}
static void fn_8002823C() {}
static void fn_80028240() {}

static void fn_80028244()
{
    fn_80072C90(0xFA, 1);
    sUnknown803EA2FC = 0;
    if (sUnknown803EA300) {
        sUnknown803EA300 = 0;
        fn_8007F6F8(9, 1);
        fn_80194DB8();
        fn_80194D20();
        fn_80194F1C(1);
    }
    fn_800282DC();
    fn_801C6280(-1, 2, (void *)fn_80026DD4);
}

static void fn_800282B8() {}

ModuleDependency *InGame::GetDependencies() { return sDependencies; }
ModuleDependency *InGame::GetLinks() { return 0; }
const char *InGame::GetName() { return "InGame"; }

void fn_800282DC()
{
    fn_80067D4C(0x84, 0);
    fn_800C1E50();
    sUnknown803EC5F4 = 0;
}

int fn_80028310()
{
    return !sUnknown803EC5F4;
}

int InGame::Init()
{
    Record_8003B6BC record0;
    Record_8003B6BC record1;
    int a;
    int b;
    int result;

    result = 0;
    sUnknown803EC5F8 = 0;
    sUnknown803EA2FC = 0;
    sUnknown803EA300 = 0;
    fn_8007F394(1);
    fn_8008FE5C(0);
    fn_80099568(1);
    fn_8013CF98();
    fn_80191808();
    fn_80066D5C();
    fn_800A216C(1);
    fn_800AE8B4();
    fn_8002B598();
    fn_801C6280(-1, 1, (void *)fn_80027FE0);
    sUnknown803EC5F4 = 1;
    fn_800C8704(&a, &b);
    fn_8003B6BC(0, &record0);
    fn_8003B6BC(1, &record1);
    fn_80085AA0(a, &record0, b, &record1);
    fn_80173C2C();
    fn_80173D10();
    fn_80176C58();
    fn_80176C90();
    fn_80139168();
    sUnknown803EC5FC = 0;
    fn_80028918(0);
    fn_8002728C(fn_8013FCD4);
    fn_801FCE10(0, "select 'PNIG' into \x82 from 'FNIG'\n", &result);
    fn_80057F28();
    if (result) {
        fn_800AD910(10, 0.0f);
    } else {
        unsigned int value = fn_8017F584();

        if (value <= 11 || value == 13) {
            fn_800AD910(1, 0.0f);
        }
    }
    fn_80187C0C();
    fn_8005BF18();
    if (!fn_800BA6F8()) {
        fn_8013FC58();
        if (!result && !fn_800C1E40()) {
            fn_800BCF7C(lbl_803EAB90);
        }
    } else {
        fn_8013FC58();
    }
    if (fn_8002892C()) {
        fn_801C6280(-1, 2, (void *)fn_80028140);
    }
    fn_80194AEC(0);
    fn_80239CEC(0x80000000, fn_802399F8() + 0x80000000);
    Desc_802345C4 desc = { 4, 14 };
    fn_802345C4(&desc, 2);
    fn_8018A6C4(1, 3);
    fn_8018A6C4(1, 0);
    fn_80067D4C(0x6A, 0);
    fn_80218FC4(lbl_803EB690, 1, 5, 0, 0);
    return sUnknown803EC5F4;
}

unsigned char InGame::fn_8002854C()
{
    int handled;
    unsigned int count;

    fn_80236F34();
    handled = 0;
    fn_8018A740();
    fn_80028238();
    fn_8002823C();
    fn_80028240();
    fn_801D6F58();
    if (sUnknown803EA2FC > 10800) {
        if (fn_8007F828(9)) {
            sUnknown803EA300 = 1;
            fn_8007F6F8(9, 0);
            fn_80194DB8();
            fn_80194D20();
            fn_80194F1C(0);
        }
    } else {
        if (sUnknown803EA300) {
            sUnknown803EA300 = 0;
            fn_8007F6F8(9, 1);
            fn_80194DB8();
            fn_80194D20();
            fn_80194F1C(1);
        }
        sUnknown803EA2FC++;
    }
    fn_80194E04();
    TimeScaleUpdate();
    if (sUnknown803EC5FC == 0) {
        sUnknown803EC5F8++;
        fn_80237830(1);
    }
    while ((count = fn_802378C8()) != 0) {
        float value = count;

        handled = 1;
        fn_800AD888(value * lbl_803EA2C4);
        fn_8017CEDC(value);
    }
    if (!handled) {
        fn_801C601C(-1);
        fn_801C60BC(-1);
    }
    fn_80065194();
    fn_8002CF34(lbl_803EA368);
    if (!fn_8002D060(lbl_803EA368)) {
        fn_80145E64(lbl_803EA2C4);
        fn_80144EDC(lbl_803EA2C4);
        fn_800A3120(lbl_803EA2C4);
    }
    fn_801CAF24();
    fn_8003E1F0();
    fn_80043F50();
    fn_800A7F6C();
    fn_800728F8();
    fn_800726B8();
    fn_80195F80();
    fn_8006CA84(1);
    fn_801CE82C();
    fn_802285CC();
    fn_80236F34();
    if (sCallback) {
        sCallback();
    }
    if (!sUnknown803EC5F4) {
        if (fn_800A937C() || fn_800A9680()) {
            fn_800A9478(1);
        }
    }
    return sUnknown803EC5F4;
}

int InGame::Shutdown()
{
    TimeScaleReset();
    fn_800A8EB8();
    if (sUnknown803EA2F8) {
        sUnknown803EA2FC = 0;
        if (sUnknown803EA300) {
            sUnknown803EA300 = 0;
            fn_8007F6F8(9, 1);
            fn_80194DB8();
            fn_80194D20();
            fn_80194F1C(1);
        }
    }
    fn_8018A710(1, 0);
    fn_8018A710(1, 3);
    fn_8021956C(lbl_803EB690, 1, 5, 0);
    Desc_802345C4 desc = { 6, 14 };
    fn_802345C4(&desc, 2);
    fn_80085A7C();
    fn_8007F394(0);
    fn_8002728C(0);
    fn_80196130();
    fn_80065194();
    fn_801CE910();
    fn_800582D0();
    fn_800AB944(lbl_803EAA8C);
    fn_80089754();
    fn_8019180C();
    fn_801C6280(-1, 2, (void *)fn_80026DD4);
    fn_8017F664();
    fn_80062A58(sUnknown803EA2F8);
    sUnknown803EA2F8 = 0;
    return 1;
}

void fn_8002885C()
{
    sUnknown803EC5FC++;
    fn_80028918(1);
    if (fn_800AD9B4() == 5) {
        fn_800B410C();
        fn_8021956C(lbl_803EB688, 3, 2, 1);
    }
}

void fn_800288B0()
{
    if (--sUnknown803EC5FC == 0) {
        fn_80028918(0);
        if (fn_800AD9B4() == 5 && sUnknown803EC5F4) {
            fn_800B3AF4(0.0f);
        } else {
            fn_800B4184(1);
        }
    }
}

void fn_80028918(int unknown)
{
    sUnknown803EC600 = unknown;
}

void fn_80028920()
{
    sUnknown803EA2F8 = 1;
}

unsigned char fn_8002892C()
{
    return sUnknown803EA2F8;
}

int fn_80028934()
{
    return sUnknown803EC5FC != 0;
}

int fn_8002894C()
{
    int result = 0;
    Class_803067B0 *p = &lbl_803067B0;

    if (fn_801CBE9C(p, 1)) {
        result = !fn_801CBE9C(p, 3);
    }
    return result;
}

int fn_800289A8()
{
    return sUnknown803EC5F8;
}
