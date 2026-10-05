#include <math.h>
#include <string.h>
#include "game/Class_802A56E8.h"
#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800785C0.h"
#include "game/Object_8017886C.h"
#include "game/Record_800B15FC.h"
#include "game/cu_8003EC04.h"
#include "game/cu_80067C10.h"
#include "game/cu_8007C9D4.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8007F828.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"
#include "game/fn_8017F584.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

class Class_802A5630 : public Class_802A56E8 {
public:
    virtual int vfn_01();
    virtual int vfn_02();
    virtual int vfn_04(int team);
    virtual int vfn_06();
    virtual int vfn_07(int team);
};

struct Segment_ScrmState {
    Point_8017886C mA;
    Point_8017886C mB;
};

/* Returned by fn_801787D0; the layout is that read by fn_8016F6A4. */
struct Info_ScrmState {
    float mUnknown00;
    float mUnknown04;
    float mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    short mUnknown14;
    float mUnknown18;
    int mUnknown1C;
};

/* The 'scru' block allocated by fn_801779D8; lbl_803EB444 points to it. */
struct ScrmState {
    int mUnknown00;
    float mUnknown04;
    float mUnknown08;
    Point_8017886C mUnknown0C;
    Point_8017886C mUnknown14;
    Point_8017886C mUnknown1C;
    Point_8017886C mUnknown24;
    int mUnknown2C;
    int mUnknown30;
    unsigned int mUnknown34;
    unsigned char mUnknown38;
    unsigned char mUnknown39;
    unsigned char mUnknown3A;
    unsigned char mUnknown3B;
    short mUnknown3C;
    short mUnknown3E;
    int mUnknown40;
    int mUnknown44;
    unsigned char mUnknown48;
    Info_ScrmState mUnknown4C;
    Object_8017886C mUnknown6C;
    float mUnknown8C;
    float mUnknown90;
    float mUnknown94;
    float mUnknown98;
    float mUnknown9C;
    float mUnknownA0;
    float mUnknownA4;
    float mUnknownA8;
    float mUnknownAC;
    unsigned char mUnknownB0;
    unsigned char mUnknownB1;
    unsigned short mUnknownB2;
    Segment_ScrmState mUnknownB4[50];
    float mUnknown3D4;
    Class_802A56E8 *mUnknown3D8;
    int mUnknown3DC;
    unsigned char mUnknown3E0;
};

/* A stat value saved by fn_8017926C before its first change in a play. The
   entry after the last one has mKind == -1. */
struct Entry_80361F88 {
    int mTag;
    int mHandle;
    int mValue;
    signed char mKind;
};

struct Record_80054130 {
    char mUnknown00[0x3C];
};

struct Object_80054130 {
    char mUnknown00[0x8B];
    unsigned char mUnknown8B;
    Record_80054130 *mUnknown8C;
};

/* Per-team stat values read back in fn_8017C4B8. */
struct Baseline_802E9ADC {
    int mTp;
    int mSp;
    int mFs;
};

extern "C" {
extern Baseline_802E9ADC lbl_802E9ADC[2];
extern void *lbl_803EA368;

int fn_80025708(void);
void fn_800310C0(void *p, int a, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing);
Set_8003EE6C *fn_8003A078(void);
void fn_8003A090(void);
void fn_800535FC(void);
Object_80054130 *fn_80054130(void);
void fn_800541AC(Record_80054130 *pRecord, Point_8017886C *pA, Point_8017886C *pB);
void fn_8006F0B8(int a);
void fn_8007B684(int id);
void fn_8007B6D4(void);
int fn_8007B974(void);
void fn_80093C3C(int index, short value, Object_80039F5C *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
float fn_800A32B4(void);
float fn_800A32C0(void);
float fn_800A32CC(void);
float fn_800A32D8(void);
float fn_800A32E4(void);
int fn_800A3444(void);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800AD910(int a, float b);
void fn_800B1584(int a, int b);
void fn_800B2314(void);
int fn_800B65A0(int team);
int fn_800BA6F8(void);
Point_8017886C fn_800BA7A0(void);
int fn_800BAAB8(void);
int fn_800C8704(int *pA, int *pB);
int fn_800C8744(int team);
void fn_800C87CC(int team, int value);
void fn_800C9FC0(int a);
int fn_800D0B90(Object_80039F5C *p);
int fn_800D41F8(int team);
void fn_800D421C(int team, int value);
int fn_800D42CC(void);
void fn_800D5F1C(Object_80039F5C *p, int a, int b);
void fn_8011DF90(void);
void fn_8011F574(void);
void fn_80120618(void);
void fn_8013FAC0(void);
void fn_8013FB44(void);
Set_8003EE6C *fn_801442F0(void);
int fn_801486A0(void);
int fn_801650DC(Record_80067338 *pRecord);
void fn_8016F7F8(void);
int fn_8016FAD8(float *pOut);
void fn_801732D0(void);
void fn_80173320(void);
void fn_80173324(unsigned int value);
void fn_80173D10(void);
void fn_80173EE0(int type, short a, short b, int c, int d);
int fn_801740A8(void);
void fn_8017417C(void);
void fn_80176984(void);
void fn_80176CC8(int type, short a, int b, int c);
void fn_80176E34(int a, int b, int c, int d);
int fn_8017F60C(void);
int fn_801BE648(void *p);
void fn_8022B2CC(int handle, int tag, int value);
int fn_8022B414(int handle, int tag, int *pValue);
int fn_8022B580(int handle, int tag, int value);
int fn_8022B7A4(int handle, int tag, int *pValue);
int fn_8022B8C8(int handle, int tag, int value);
void fn_8022BAB4(int handle, int a, int b, int c);
void fn_8022BD30(int handle, int a, int b);
void *fn_8023816C(void *pHandle);
}

extern "C" {
unsigned int fn_80176F18(const Point_8017886C *p);
void fn_8017710C(void);
Point_8017886C fn_801772F4(Point_8017886C point);
void fn_801779D8(void);
void fn_80177B54(void);
void fn_80177B7C(int a);
void fn_80177BCC(float value);
int fn_80177C38(void);
void fn_80177C44(int value);
void fn_80177C50(int a);
void fn_80177D54(void);
void fn_80177D78(void);
void fn_80177D88(int a);
void fn_80177E6C(int a, int flip);
int fn_80177F70(void);
int fn_80177F7C(void);
void fn_80177F88(int value);
void fn_80177FD4(int value);
Point_8017886C fn_80177FE0(void);
Point_8017886C fn_80177FFC(int team);
Point_8017886C fn_80178070(void);
Point_8017886C fn_8017808C(void);
void fn_801780A8(Point_8017886C pos);
void fn_8017813C(Point_8017886C pos);
int fn_80178194(void);
void fn_80178264(Point_8017886C pos);
Point_8017886C fn_8017827C(void);
float fn_80178298(void);
float fn_801782A4(void);
void fn_801782B0(void);
void fn_801782F4(float line);
unsigned char IsShortOfLineToGain(float range, unsigned char *pWithinRange);
int fn_80178308(void);
int fn_80178320(void);
void fn_8017833C(int value);
int fn_80178348(void);
void fn_80178354(int value);
int fn_80178360(void);
void fn_80178370(void);
int fn_801783AC(int bit);
void fn_801783D0(int bit, int on);
void fn_8017840C(void);
int fn_801784C4(void);
int fn_801784E8(void);
int fn_80178508(Point_8017886C *pPos, float *pOut, int skipFlags);
void fn_80178718(Object_80039F5C *p);
Object_80039F5C *fn_8017876C(void);
unsigned char fn_80178794(void);
int fn_801787A0(void);
Info_ScrmState *fn_801787D0(void);
int fn_801787DC(int team);
void fn_801787FC(int team, short value);
int fn_8017881C(int a);
void fn_8017885C(void);
void fn_80178878(const Object_8017886C *p);
int RoundToNearestInt(float value);
int fn_801788D8(int *pValue);
void fn_801789F8(void);
void fn_801789FC(float value);
float fn_80178A08(void);
void fn_80178A14(float value);
void fn_80178A20(float value);
float fn_80178A2C(void);
void fn_80178A38(float value);
float fn_80178A44(void);
void fn_80178A50(float value);
float fn_80178A5C(void);
float fn_80178A68(Point_8017886C *pPos);
int fn_80178AE0(void);
void fn_80178B1C(int a);
void fn_80178B5C(void);
int fn_80178BA4(int a);
int fn_80178BE4(int a);
int fn_80178C24(void);
int fn_80178C60(void);
int fn_80178C9C(void);
void fn_80178CD8(int a);
unsigned int fn_80178D18(int team);
int fn_80178D70(int team);
unsigned int fn_80178DC8(void);
int fn_80178E10(void);
int fn_80178E4C(void);
void fn_80178E88(float v);
unsigned short fn_80178E94(void);
int fn_80178EA0(int a);
int fn_80178EE0(int a);
void fn_80178F20(Class_802A56E8 *pRule);
void fn_80178F90(void);
float fn_80178FCC(int team);
void fn_801790D0(int team, float a, float b);
int fn_80179138(void);
void fn_80179144(int a);
void fn_80179150(void);
void fn_8017916C(void);
int fn_80179244(void);
void fn_8017926C(int handle, int tag, int value, int kind);
int fn_8017932C(int id);
int fn_80179358(int id);
void fn_8017937C(int id, int tag, int value);
void fn_80179430(int handle, int tag, int value);
void fn_801794B4(int id, int tag, int value);
void fn_801794F0(int team, int tag, int value);
void fn_8017952C(int id, int a, float b, float c);
void fn_80179594(int id, float a, float b);
void fn_801795EC(int id, float from, float to);
void fn_801796C8(int id, float from, float catchY, float to, float time);
void fn_80179874(int id, float from, float to, float time);
void fn_80179A54(int id, float from, float to);
void fn_80179AF0(int id, float from, float to, int flag, float spot);
void fn_80179C74(int id, float from, float to);
void fn_80179D98(int id, float from, float to);
void fn_80179EBC(int ref);
int fn_80179F2C(unsigned char *pFlag);
int fn_8017B83C(void);
void fn_8017BD70(Object_8017886C *pResult, int kind, unsigned char flag);
void fn_8017C1EC(void);
void fn_8017C1F0(Object_8017886C *pResult);
void fn_8017C25C(int value);
void fn_8017C298(unsigned short team, short value);
void fn_8017C2F0(unsigned short team);
void fn_8017C344(unsigned short team, int play);
void fn_8017C3E4(unsigned short team, short yards, int handle);
void fn_8017C4B8(void);
void fn_8017C5A0(unsigned short team, int value);
void fn_8017C5CC(unsigned short team, int value);
void fn_8017C5F8(unsigned short team, int value);
void fn_8017C648(unsigned short team, int value);
void fn_8017C674(unsigned short team, int value);
void fn_8017C6A0(unsigned short team, int value);
void fn_8017C6CC(unsigned short team, int value, int also);
void fn_8017C724(unsigned short team, int value);
void fn_8017C750(unsigned short team, int value, int also);
void fn_8017C7A8(unsigned short team, int value);
void fn_8017C7D4(unsigned short team, int value);
void fn_8017C800(unsigned short team, int value);
void fn_8017C82C(unsigned short team, int value);
void fn_8017C858(unsigned short team, int value);
void fn_8017C884(unsigned short team, int value);
void fn_8017C8B0(unsigned short team, int value);
void fn_8017C8DC(unsigned short team, int value);
void fn_8017C908(unsigned short team, int value);
void fn_8017C934(unsigned short team, int value);
void fn_8017C960(unsigned short team, int value);
void fn_8017C98C(unsigned short team, int value);
void fn_8017C9B8(unsigned short team, int value);
void fn_8017C9E4(unsigned short team, int value);
void fn_8017CA10(unsigned short team, int value);
void fn_8017CA3C(unsigned short team, int value);
void fn_8017CA68(unsigned short team, int value);
void fn_8017CA94(unsigned short team, int value);
void fn_8017CAC0(void (*pCallback)(int kind, int a, int b));
}

static unsigned char lbl_803EB440 = 0;
static ScrmState *lbl_803EB444 = 0;
static float lbl_803EB448 = 1.0f;
static float lbl_803EB44C = 0.33f;
static void (*lbl_803EB450)(int kind, int a, int b) = 0;
static unsigned char lbl_803EB454 = 0;
static int lbl_803EB458 = 0;

static Class_802A56E8 lbl_803ECB24;
static Class_802A5630 lbl_803ECB28;
static Object_8017886C *lbl_803ECB34;

static Entry_80361F88 lbl_80361F88[0x61];

static inline void Negate(Point_8017886C &v)
{
    v.mX = -v.mX;
    v.mY = -v.mY;
}

extern "C" unsigned int fn_80176F18(const Point_8017886C *p)
{
    unsigned int result = 0;
    unsigned char i;

    for (i = 0; i < lbl_803EB444->mUnknownB1; i++) {
        Point_8017886C a = lbl_803EB444->mUnknownB4[i].mA;
        Point_8017886C b = lbl_803EB444->mUnknownB4[i].mB;

        if (fn_801784C4()) {
            Negate(a);
            Negate(b);
        }
        if (fabs(p->mX - a.mX) < lbl_803EB448 && fabs(p->mX - b.mX) < lbl_803EB448) {
            if (a.mY > b.mY) {
                if (p->mY >= b.mY && p->mY <= a.mY) {
                    if (p->mX > 0.0f) {
                        result |= 1;
                    } else {
                        result |= 2;
                    }
                }
            } else {
                if (p->mY >= a.mY && p->mY <= b.mY) {
                    if (p->mX > 0.0f) {
                        result |= 1;
                    } else {
                        result |= 2;
                    }
                }
            }
        }
        if (fabs(p->mY - a.mY) < lbl_803EB448 && fabs(p->mY - b.mY) < lbl_803EB448) {
            if (a.mX > b.mX) {
                if (p->mX >= b.mX && p->mX <= a.mX) {
                    if (p->mY > 0.0f) {
                        result |= 4;
                    } else {
                        result |= 8;
                    }
                }
            } else {
                if (p->mX >= a.mX && p->mX <= b.mX) {
                    if (p->mY > 0.0f) {
                        result |= 4;
                    } else {
                        result |= 8;
                    }
                }
            }
        }
    }
    return result;
}

extern "C" void fn_8017710C(void)
{
    unsigned char count = 0;

    if (fn_80054130()) {
        unsigned char i;
        unsigned char total = fn_80054130()->mUnknown8B;
        Record_80054130 *pRecord = fn_80054130()->mUnknown8C;

        for (i = 0; i < total; i++, pRecord++) {
            Point_8017886C a;
            Point_8017886C b;

            fn_800541AC(pRecord, &a, &b);
            if (fn_801784C4()) {
                Negate(a);
                Negate(b);
            }
            if ((fabs(a.mX - fn_80178A08()) < lbl_803EB44C && fabs(b.mX - fn_80178A08()) < lbl_803EB44C)
                || (fabs(a.mX + fn_80178A08()) < lbl_803EB44C && fabs(b.mX + fn_80178A08()) < lbl_803EB44C)
                || (fabs(a.mY - fn_80178A44()) < lbl_803EB44C && fabs(b.mY - fn_80178A44()) < lbl_803EB44C)
                || (fabs(a.mY + fn_80178A44()) < lbl_803EB44C && fabs(b.mY + fn_80178A44()) < lbl_803EB44C)) {
                lbl_803EB444->mUnknownB4[count].mA = a;
                lbl_803EB444->mUnknownB4[count].mB = b;
                count++;
            }
        }
    }
    lbl_803EB444->mUnknownB1 = count;
}

extern "C" Point_8017886C fn_801772F4(Point_8017886C point)
{
    Point_8017886C result;

    if (fn_800BA6F8()) {
        result = fn_800BA7A0();
    } else {
        result = point;
    }
    result.mX = CLAMP(result.mX, -fn_80178A5C(), fn_80178A5C());
    result.mY = CLAMP(result.mY, 0.16f - fn_80178A2C(), fn_80178A2C() - 0.16f);
    return result;
}

int Class_802A56E8::vfn_01()
{
    return fn_8007F828(1);
}

int Class_802A56E8::vfn_02()
{
    unsigned short score0 = fn_801787DC(0);
    unsigned short score1 = fn_801787DC(1);
    unsigned int limit = vfn_01();
    int result;

    if (score0 > score1 && score0 >= limit) {
        result = 0;
    } else if (score0 < score1 && score1 >= limit) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}

void Class_802A56E8::vfn_03(int team)
{
    if (fn_80025708()) {
        fn_8009D8CC(4);
        fn_8009D964(4, 0);
    } else {
        int value = 0;

        switch (fn_801788D8(&value)) {
        case 0:
            fn_801787FC(team, (short)value);
            fn_800C87CC(team, value);
            break;
        case 1:
            fn_800D421C(team, value);
            break;
        }
    }
}

int Class_802A56E8::vfn_04(int team)
{
    int result = 0;
    unsigned int limit = vfn_01();

    if (fn_80177F70() != 6) {
        if (fn_80178308() == team && limit - fn_801787DC(team) <= 8) {
            result = 1;
        }
    } else {
        if (fn_80178308() == team && limit - fn_801787DC(team) <= 2) {
            result = 1;
        }
    }
    return result;
}

int Class_802A56E8::vfn_05(int team)
{
    return vfn_04(team ^ 1);
}

int Class_802A56E8::vfn_06()
{
    return 0;
}

int Class_802A56E8::vfn_07(int team)
{
    return fn_801787DC(team);
}

int Class_802A56E8::vfn_08()
{
    return 0;
}

int Class_802A56E8::vfn_21()
{
    return 0;
}

int Class_802A56E8::vfn_09()
{
    return 900;
}

void Class_802A56E8::vfn_10()
{
    Object_8017886C *p = fn_8017886C();

    fn_80177FD4(fn_80177F70());
    fn_80177F88(p->mUnknown04);
    fn_801780A8(p->mUnknown08);
}

int Class_802A56E8::vfn_13()
{
    return 7;
}

int Class_802A56E8::vfn_14()
{
    int result = 1;

    if (fn_80025708()) {
        result = fn_800785C0()->mUnknown1B0 == 0;
    }
    return result;
}

int Class_802A56E8::vfn_15()
{
    int result = 1;

    if (fn_80025708()) {
        result = fn_800785C0()->mUnknown1B4 == 0;
    }
    return result;
}

void Class_802A56E8::vfn_11(int team)
{
    Object_8017886C info;

    fn_80179150();
    fn_801787FC(0, 0);
    fn_801787FC(1, 0);
    fn_8017885C();
    memset(&info, 0, sizeof(info));
    fn_80178878(&info);
    fn_80177F88(1);
    lbl_803EB444->mUnknownB2 = 0;
    if (team != 2) {
        fn_8017833C(team);
        fn_80178354(team);
    }
}

int Class_802A56E8::vfn_12()
{
    return 1;
}


void Class_802A56E8::vfn_19()
{
    int mode = fn_800AD9B4();

    if (mode == 4 || mode == 7) {
        return;
    }
    if (mode == 5 && fn_8017F60C()) {
        return;
    }
    if (fn_801486A0() || fn_80177C38() || fn_801783AC(3)) {
        Record_800B15FC *p = fn_800B15FC();
        Object_80039F5C *pPlayer;

        p->mUnknown14 = 2;
        p->mUnknown10 = p->mUnknownC = 0.0f;
        fn_800B1508();
        fn_800A8954(0x16, fn_80178308(), 0);
        fn_800535FC();
        pPlayer = fn_80137B40();
        if (pPlayer && fn_801BE648(pPlayer->mpUnknown792) == 0xED) {
            fn_800D5F1C(pPlayer, fn_800D0B90(pPlayer), 0xFF);
        }
        fn_800AD910(4, 0.0f);
    }
}

int Class_802A5630::vfn_01()
{
    return fn_8007F828(2);
}

int Class_802A5630::vfn_02()
{
    return fn_800D42CC();
}

int Class_802A5630::vfn_04(int team)
{
    int result = 0;
    unsigned int limit = vfn_01();

    if (fn_80177F70() != 6 && limit - fn_800D41F8(team) <= 50000) {
        result = 1;
    }
    return result;
}

int Class_802A5630::vfn_06()
{
    return 1;
}

int Class_802A5630::vfn_07(int team)
{
    return fn_800D41F8(team);
}

extern "C" void fn_801779D8(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB444, sizeof(ScrmState), 0, 0x73637275);
    ScrmState *pState = (ScrmState *)fn_8023816C(pHandle);

    int resume = 0;

    fn_8017F584();
    if (resume) {
        fn_801FCE10(0, "select 'SRSG' into \x89 from 'NIBG'\n", pState);
    }
    pState->mUnknown08 = 0.0f;
    pState->mUnknown0C.mX = 0.0f;
    pState->mUnknown0C.mY = 0.0f;
    pState->mUnknownB0 = pState->mUnknown38 = fn_8007CB6C(2);
    if (fn_80025708()) {
        pState->mUnknown3C = fn_800785C0()->mUnknown1AC;
        pState->mUnknown3E = fn_800785C0()->mUnknown1A8;
        fn_801FCE10(0, "update 'FNIG' set 'CSAG' = \x82 and 'CSHG' = \x82\n", pState->mUnknown3E, pState->mUnknown3C);
        pState->mUnknown30 = fn_800785C0()->mUnknown1C1;
    } else {
        pState->mUnknown30 = 1;
        pState->mUnknown3C = 0;
        pState->mUnknown3E = 0;
    }
    pState->mUnknown04 = 0.0f;
    pState->mUnknown14.mX = 0.0f;
    pState->mUnknown00 = 0;
    pState->mUnknown14.mY = 0.0f;
    pState->mUnknown2C = 1;
    pState->mUnknown3B = 0;
    pState->mUnknownB2 = 0;
    pState->mUnknownB1 = 0;
    if (!fn_80027DF0()) {
        fn_8007B684(fn_800A3444());
        if (fn_8007B974() == 1) {
            pState->mUnknown39 = 1;
        } else {
            pState->mUnknown39 = 0;
        }
        fn_8007B6D4();
    } else {
        pState->mUnknown39 = 0;
    }
    pState->mUnknown3D4 = 7.0f;
    pState->mUnknownA0 = 0.0f;
    pState->mUnknownA4 = 0.0f;
    pState->mUnknownA8 = 0.0f;
    pState->mUnknownAC = 0.0f;
    fn_802381E0(pHandle);
    fn_80178F20(0);
    fn_801732D0();
    fn_80179150();
}

extern "C" void fn_80177B54(void)
{
    fn_80173320();
    lbl_803EB444 = 0;
}


extern "C" void fn_80177B7C(int a)
{
    fn_800C9FC0(a);
    lbl_803EB444->mUnknown3D8->vfn_11(a);
}


extern "C" void fn_80177BCC(float value)
{
    fn_8016F7F8();
    fn_80173324(value);
    fn_80176984();
}

static inline void FlipSides(void)
{
    ScrmState *s = lbl_803EB444;
    s->mUnknown0C.mX = -s->mUnknown0C.mX;
    s->mUnknown0C.mY = -s->mUnknown0C.mY;
    s->mUnknown14.mX = -s->mUnknown14.mX;
    s->mUnknown14.mY = -s->mUnknown14.mY;
    s->mUnknown1C.mX = -s->mUnknown1C.mX;
    s->mUnknown1C.mY = -s->mUnknown1C.mY;
    s->mUnknown08 = -s->mUnknown08;
    s->mUnknown04 = -s->mUnknown04;
    s->mUnknown24.mX = -s->mUnknown24.mX;
    s->mUnknown24.mY = -s->mUnknown24.mY;
}

extern "C" int fn_80177C38(void)
{
    return lbl_803EB444->mUnknown00;
}

extern "C" void fn_80177C44(int value)
{
    lbl_803EB444->mUnknown00 = value;
}

extern "C" void fn_80177C50(int a)
{
    switch (fn_801486A0()) {
    case 3:
        lbl_803EB444->mUnknown00++;
        fn_8017833C(lbl_803EB444->mUnknown38 ^ 1);
        fn_800B1584(0x1E, 0);
        fn_8011DF90();
        break;
    case 0:
        lbl_803EB444->mUnknown00++;
        fn_8017833C(lbl_803EB444->mUnknown38 ^ 1);
        fn_8011DF90();
        fn_80178370();
        break;
    case 1:
        break;
    default:
        fn_80120618();
        fn_8011F574();
        if (++lbl_803EB444->mUnknown00 > 3) {
            lbl_803EB444->mUnknown00 = 2;
        }
        fn_8017833C(lbl_803EB444->mUnknown38 ^ 1);
        fn_80177D88(a);
        fn_8011DF90();
        fn_801783D0(2, 0);
        lbl_803EB444->mUnknownB2++;
        break;
    }
}

extern "C" void fn_80177D54(void)
{
    lbl_803EB440 = fn_801784C4();
}

extern "C" void fn_80177D78(void)
{
    lbl_803EB444->mUnknown39 = lbl_803EB440;
}

extern "C" void fn_80177D88(int a)
{
    if (lbl_803EB444->mUnknown40 == 0 || (fn_800B65A0(0) == 0xFF && fn_800B65A0(1) == 0xFF)) {
        fn_80177E6C(a, 1);
    } else {
        FlipSides();
    }
}

extern "C" void fn_80177E6C(int a, int flip)
{
    if (flip) {
        FlipSides();
    }
    fn_8003A090();
    fn_80138270();
    fn_8003F60C(fn_8003A078());
    fn_8003F60C(fn_801442F0());
    fn_8003F60C(fn_80138264());
    fn_8013FAC0();
    if (lbl_803EB444->mUnknown39 == 0) {
        lbl_803EB444->mUnknown39 = 1;
    } else {
        lbl_803EB444->mUnknown39 = 0;
    }
    fn_800B1584(0x1E, 0);
    if (a) {
        fn_8013FB44();
    }
}

extern "C" int fn_80177F70(void)
{
    return lbl_803EB444->mUnknown30;
}

extern "C" int fn_80177F7C(void)
{
    return lbl_803EB444->mUnknown2C;
}

extern "C" void fn_80177F88(int value)
{
    if (fn_800BA6F8()) {
        lbl_803EB444->mUnknown30 = fn_800BAAB8();
    } else {
        lbl_803EB444->mUnknown30 = value;
    }
}

extern "C" void fn_80177FD4(int value)
{
    lbl_803EB444->mUnknown2C = value;
}

extern "C" Point_8017886C fn_80177FE0(void)
{
    return lbl_803EB444->mUnknown0C;
}

extern "C" Point_8017886C fn_80177FFC(int team)
{
    Point_8017886C pos;
    pos = fn_80177FE0();
    pos.mY += fn_80178FCC(team);
    return pos;
}

extern "C" Point_8017886C fn_80178070(void)
{
    return lbl_803EB444->mUnknown14;
}

extern "C" Point_8017886C fn_8017808C(void)
{
    return lbl_803EB444->mUnknown1C;
}

extern "C" void fn_801780A8(Point_8017886C pos)
{
    lbl_803EB444->mUnknown14 = lbl_803EB444->mUnknown0C;
    lbl_803EB444->mUnknown0C = fn_801772F4(pos);
    lbl_803EB444->mUnknown1C = fn_801772F4(pos);
}

extern "C" void fn_8017813C(Point_8017886C pos)
{
    lbl_803EB444->mUnknown1C = fn_801772F4(pos);
}

extern "C" int fn_80178194(void)
{
    float line = fn_80178298();
    if (line >= fn_80178A2C()) {
        return -1;
    }
    Point_8017886C pos;
    pos = fn_80177FE0();
    return ((char)fn_80178A2C() - (char)pos.mY) - ((char)fn_80178A2C() - (char)line);
}

extern "C" void fn_80178264(Point_8017886C pos)
{
    lbl_803EB444->mUnknown24 = pos;
}

extern "C" Point_8017886C fn_8017827C(void)
{
    return lbl_803EB444->mUnknown24;
}

extern "C" float fn_80178298(void)
{
    return lbl_803EB444->mUnknown08;
}

extern "C" float fn_801782A4(void)
{
    return lbl_803EB444->mUnknown04;
}

extern "C" void fn_801782B0(void)
{
    float line = -lbl_803EB444->mUnknown90;
    while (line <= lbl_803EB444->mUnknown0C.mY) {
        line += lbl_803EB444->mUnknown9C;
    }
    lbl_803EB444->mUnknown04 = lbl_803EB444->mUnknown08;
    lbl_803EB444->mUnknown08 = line;
}

extern "C" void fn_801782F4(float line)
{
    lbl_803EB444->mUnknown04 = lbl_803EB444->mUnknown08;
    lbl_803EB444->mUnknown08 = line;
}

extern "C" unsigned char IsShortOfLineToGain(float range, unsigned char *pWithinRange)
{
    unsigned char isShort = 0;
    float distance;

    *pWithinRange = 0;
    distance = lbl_803EB444->mUnknown0C.mY - lbl_803EB444->mUnknown08;
    if (distance < 0.0f) {
        isShort = 1;
        distance = -distance;
    }
    if (distance < range) {
        *pWithinRange = 1;
    }
    return isShort;
}

extern "C" int fn_80178308(void)
{
    int result = 0;
    if (lbl_803EB444 != 0) {
        result = lbl_803EB444->mUnknown38;
    }
    return result;
}

extern "C" int fn_80178320(void)
{
    int result = 0;
    if (lbl_803EB444 != 0) {
        result = lbl_803EB444->mUnknown38 ^ 1;
    }
    return result;
}

extern "C" void fn_8017833C(int value)
{
    lbl_803EB444->mUnknown38 = value;
}

extern "C" int fn_80178348(void)
{
    return lbl_803EB444->mUnknownB0;
}

extern "C" void fn_80178354(int value)
{
    lbl_803EB444->mUnknownB0 = value;
}

extern "C" int fn_80178360(void)
{
    return lbl_803EB444->mUnknownB0 ^ 1;
}

extern "C" void fn_80178370(void)
{
    lbl_803EB444->mUnknown3D8->vfn_19();
}

extern "C" int fn_801783AC(int bit)
{
    return (lbl_803EB444->mUnknown34 & (1 << bit)) != 0;
}

extern "C" void fn_801783D0(int bit, int on)
{
    if (on == 1) {
        lbl_803EB444->mUnknown34 |= 1 << bit;
    } else {
        lbl_803EB444->mUnknown34 &= ~(1 << bit);
    }
}

extern "C" void fn_8017840C(void)
{
    int i;
    int saved11 = fn_801783AC(0x11);
    int saved15 = fn_801783AC(0x15);
    for (i = 0; i <= 0x18; i++) {
        fn_801783D0(i, 0);
    }
    fn_801783D0(0x15, saved15);
    if (fn_80177F70() == 0) {
        fn_801783D0(0x11, saved11);
    }
    fn_801783D0(2, 1);
    fn_80177C44(0);
    lbl_803EB444->mUnknown44 = 0;
    lbl_803EB444->mUnknown48 = 0;
    lbl_803EB444->mUnknown3A = lbl_803EB444->mUnknown39;
    lbl_803EB444->mUnknownB0 = lbl_803EB444->mUnknown38;
}

extern "C" int fn_801784C4(void)
{
    if (lbl_803EB444 != 0) {
        return lbl_803EB444->mUnknown39 == 1;
    }
    return 0;
}

extern "C" int fn_801784E8(void)
{
    return lbl_803EB444->mUnknown3A != lbl_803EB444->mUnknown39;
}

extern "C" int fn_80178508(Point_8017886C *pPos, float *pOut, int skipFlags)
{
    float dist = 0.0f;
    int result = 2;
    int flags = 0;
    float ax;
    float ay;

    if (!skipFlags) {
        flags = fn_80176F18(pPos);
    }
    ax = fabsf(pPos->mX);
    ay = fabsf(pPos->mY);
    if (ay > fn_80178A2C()) {
        result = pPos->mY > 0.0f;
        dist = ay - fn_80178A2C();
        if (ay > fn_80178A44()) {
            if (pPos->mY > 0.0f && !(flags & 4)) {
                result = 4;
                dist = ay - fn_80178A44();
            }
            if (pPos->mY <= 0.0f && !(flags & 8)) {
                result = 4;
                dist = ay - fn_80178A44();
            }
        }
        if (ax > fn_80178A08()) {
            if (pPos->mX > 0.0f && !(flags & 1)) {
                result = 4;
                dist = MAX(dist, ax - fn_80178A08());
            }
            if (pPos->mX <= 0.0f && !(flags & 2)) {
                result = 4;
                dist = MAX(dist, ax - fn_80178A08());
            }
        }
    } else if (ax > fn_80178A08()) {
        if (pPos->mX > 0.0f && !(flags & 1)) {
            result = 3;
            dist = ax - fn_80178A08();
        }
        if (pPos->mX <= 0.0f && !(flags & 2)) {
            result = 3;
            dist = ax - fn_80178A08();
        }
    }
    if (pOut) {
        *pOut = dist;
    }
    return result;
}

extern "C" void fn_80178718(Object_80039F5C *p)
{
    fn_8009BD2C(p, &lbl_803EB444->mUnknown44);
    if (p) {
        lbl_803EB444->mUnknown48 = p->mUnknown1160.mUnknown52;
    } else {
        lbl_803EB444->mUnknown48 = 0;
    }
}

extern "C" Object_80039F5C *fn_8017876C(void)
{
    return fn_8009BCE8(&lbl_803EB444->mUnknown44);
}

extern "C" unsigned char fn_80178794(void)
{
    return lbl_803EB444->mUnknown48;
}

extern "C" int fn_801787A0(void)
{
    if (fn_800AD9B4() == 3) {
        return 0;
    }
    return 1;
}

extern "C" Info_ScrmState *fn_801787D0(void)
{
    return &lbl_803EB444->mUnknown4C;
}

extern "C" int fn_801787DC(int team)
{
    if (team == 1) {
        return lbl_803EB444->mUnknown3E;
    }
    return lbl_803EB444->mUnknown3C;
}

extern "C" void fn_801787FC(int team, short value)
{
    if (team == 1) {
        lbl_803EB444->mUnknown3E = value;
    } else {
        lbl_803EB444->mUnknown3C = value;
    }
}

extern "C" int fn_8017881C(int a)
{
    return lbl_803EB444->mUnknown3D8->vfn_07(a);
}

extern "C" void fn_8017885C(void)
{
    lbl_803EB444->mUnknown40 = 0;
}

extern "C" Object_8017886C *fn_8017886C(void)
{
    return &lbl_803EB444->mUnknown6C;
}

extern "C" void fn_80178878(const Object_8017886C *p)
{
    lbl_803EB444->mUnknown6C = *p;
}

extern "C" int RoundToNearestInt(float value)
{
    if (value > 0.0f) {
        return (int)(value + 0.5f);
    }
    return (int)(value - 0.5f);
}

extern "C" int fn_801788D8(int *pValue)
{
    int result = lbl_803EB444->mUnknown3D8->vfn_06();
    *pValue = lbl_803EB444->mUnknown3D8->vfn_01();
    return result;
}

void Class_802A56E8::vfn_20(int flip)
{
    Point_8017886C pos = { 0.0f, 0.0f };
    lbl_803EB444->mUnknown40 = 1;
    if (flip) {
        pos.mY = lbl_803EB444->mUnknown3D4 - fn_80178A2C();
        fn_801780A8(pos);
        fn_801782B0();
    } else {
        pos.mY = fn_80178A2C() - lbl_803EB444->mUnknown3D4;
        fn_801780A8(pos);
        fn_801782B0();
    }
    fn_80177F88(1);
}

extern "C" void fn_801789F8(void)
{
}

extern "C" void fn_801789FC(float value)
{
    lbl_803EB444->mUnknown8C = value;
}

extern "C" float fn_80178A08(void)
{
    return lbl_803EB444->mUnknown8C;
}

extern "C" void fn_80178A14(float value)
{
    lbl_803EB444->mUnknown90 = value;
}

extern "C" void fn_80178A20(float value)
{
    lbl_803EB444->mUnknown9C = value;
}

extern "C" float fn_80178A2C(void)
{
    return lbl_803EB444->mUnknown90;
}

extern "C" void fn_80178A38(float value)
{
    lbl_803EB444->mUnknown94 = value;
}

extern "C" float fn_80178A44(void)
{
    return lbl_803EB444->mUnknown94;
}

extern "C" void fn_80178A50(float value)
{
    lbl_803EB444->mUnknown98 = value;
}

extern "C" float fn_80178A5C(void)
{
    return lbl_803EB444->mUnknown98;
}

extern "C" float fn_80178A68(Point_8017886C *pPos)
{
    return fn_80178A08() - fabsf(pPos->mX) < fn_80178A44() - fabsf(pPos->mY)
               ? fn_80178A08() - fabsf(pPos->mX)
               : fn_80178A44() - fabsf(pPos->mY);
}

extern "C" int fn_80178AE0(void)
{
    return lbl_803EB444->mUnknown3D8->vfn_02();
}

extern "C" void fn_80178B1C(int a)
{
    lbl_803EB444->mUnknown3D8->vfn_03(a);
}

extern "C" void fn_80178B5C(void)
{
    fn_801789FC(fn_800A32B4());
    fn_80178A14(fn_800A32C0());
    fn_80178A38(fn_800A32CC());
    fn_80178A50(fn_800A32D8());
    fn_80178A20(fn_800A32E4());
    fn_8017710C();
}

extern "C" int fn_80178BA4(int a)
{
    return lbl_803EB444->mUnknown3D8->vfn_04(a);
}

extern "C" int fn_80178BE4(int a)
{
    return lbl_803EB444->mUnknown3D8->vfn_05(a);
}

extern "C" int fn_80178C24(void)
{
    return lbl_803EB444->mUnknown3D8->vfn_08();
}

extern "C" int fn_80178C60(void)
{
    return lbl_803EB444->mUnknown3D8->vfn_09();
}

extern "C" int fn_80178C9C(void)
{
    return lbl_803EB444->mUnknown3D8->vfn_12();
}

extern "C" void fn_80178CD8(int a)
{
    lbl_803EB444->mUnknown3D8->vfn_20(a);
}

extern "C" unsigned int fn_80178D18(int team)
{
    Class_80148A58 *p = fn_80148A58();
    if (p != 0) {
        return p->vfn_04(team);
    }
    return 7;
}

extern "C" int fn_80178D70(int team)
{
    Class_80148A58 *p = fn_80148A58();
    if (p != 0) {
        return p->vfn_05(team);
    }
    return 7;
}

extern "C" unsigned int fn_80178DC8(void)
{
    Class_80148A58 *p = fn_80148A58();
    if (p != 0) {
        return p->vfn_06();
    }
    return 7;
}

extern "C" int fn_80178E10(void)
{
    return lbl_803EB444->mUnknown3D8->vfn_14();
}

extern "C" int fn_80178E4C(void)
{
    return lbl_803EB444->mUnknown3D8->vfn_15();
}

extern "C" void fn_80178E88(float v)
{
    lbl_803EB444->mUnknown3D4 = v;
}

extern "C" unsigned short fn_80178E94(void)
{
    return lbl_803EB444->mUnknownB2;
}

extern "C" int fn_80178EA0(int a)
{
    return lbl_803EB444->mUnknown3D8->vfn_17(a);
}

extern "C" int fn_80178EE0(int a)
{
    return lbl_803EB444->mUnknown3D8->vfn_18(a);
}

extern "C" void fn_80178F20(Class_802A56E8 *pRule)
{
    if (pRule == 0) {
        switch (fn_8007F828(14)) {
        case 0:
            lbl_803EB444->mUnknown3D8 = &lbl_803ECB24;
            break;
        case 1:
            lbl_803EB444->mUnknown3D8 = &lbl_803ECB28;
            break;
        case 2:
            lbl_803EB444->mUnknown3D8 = &lbl_803ECB24;
            break;
        default:
            lbl_803EB444->mUnknown3D8 = &lbl_803ECB24;
            break;
        }
    } else {
        lbl_803EB444->mUnknown3D8 = pRule;
    }
}

extern "C" void fn_80178F90(void)
{
    lbl_803EB444->mUnknown3D8->vfn_10();
}

extern "C" float fn_80178FCC(int team)
{
    float limit;

    if (team == fn_80178308()) {
        limit = lbl_803EB444->mUnknownA0;
        if (fn_80178A2C() + fn_80177FE0().mY < limit) {
            limit = -fn_80178A2C() + fn_80177FE0().mY;
        }
        if (limit < lbl_803EB444->mUnknownA4) {
            limit = lbl_803EB444->mUnknownA4;
        }
    } else {
        limit = lbl_803EB444->mUnknownA8;
        if (fn_80178298() - fn_80177FE0().mY < limit) {
            limit = fn_80178298() - fn_80177FE0().mY;
        }
        if (limit < lbl_803EB444->mUnknownAC) {
            limit = lbl_803EB444->mUnknownAC;
        }
    }
    return limit;
}

extern "C" void fn_801790D0(int team, float a, float b)
{
    if (team == fn_80178308()) {
        lbl_803EB444->mUnknownA0 = a;
        lbl_803EB444->mUnknownA4 = b;
    } else {
        lbl_803EB444->mUnknownA8 = a;
        lbl_803EB444->mUnknownAC = b;
    }
}

extern "C" int fn_80179138(void)
{
    return lbl_803EB444->mUnknown3DC;
}

extern "C" void fn_80179144(int a)
{
    lbl_803EB444->mUnknown3DC = a;
}

extern "C" void fn_80179150(void)
{
    lbl_803EB444->mUnknown3E0 = 0;
    lbl_803EB444->mUnknown3DC = 0;
}

extern "C" void fn_8017916C(void)
{
    int kind = lbl_803EB444->mUnknown3DC;

    if (kind == 1 || kind == 2) {
        float offset;
        Point_8017886C pos;
        Object_80137ABC *pBall;
        Vector_80039F5C ballPos;

        if (kind == 1) {
            offset = 5.0f;
        } else {
            offset = 10.0f;
        }
        pos.mX = 0.0f;
        pos.mY = fn_80178A2C() - offset;
        fn_801780A8(pos);
        pBall = fn_801374BC();
        fn_8013791C(pBall, 6, 0);
        ballPos.mX = pos.mX;
        ballPos.mY = pos.mY;
        ballPos.mZ = 0.0f;
        fn_80137D74(pBall, &ballPos);
        lbl_803EB444->mUnknown3E0 = 1;
    }
}

extern "C" int fn_80179244(void)
{
    return fn_801650DC(fn_8016871C(fn_80178348()));
}

extern "C" void fn_8017926C(int handle, int tag, int value, int kind)
{
    int i;
    int isNew = 1;

    lbl_80361F88[lbl_803EB458].mKind = -1;
    for (i = 0; i < lbl_803EB458; i++) {
        if (lbl_80361F88[i].mHandle == handle && lbl_80361F88[i].mKind == kind && lbl_80361F88[i].mTag == tag) {
            isNew = 0;
        }
    }
    if (isNew && lbl_803EB458 < 0x60) {
        lbl_80361F88[lbl_803EB458].mKind = kind;
        lbl_80361F88[lbl_803EB458].mValue = value;
        lbl_80361F88[lbl_803EB458].mHandle = handle;
        lbl_80361F88[lbl_803EB458].mTag = tag;
        lbl_803EB458++;
        lbl_80361F88[lbl_803EB458].mKind = -1;
    }
}

extern "C" int fn_8017932C(int id)
{
    return fn_80039F5C(id >> 8 & 0xFF, id >> 16 & 0xFF)->mUnknown2908;
}

extern "C" int fn_80179358(int id)
{
    return fn_800C8744(id >> 8 & 0xFF);
}

extern "C" void fn_8017937C(int id, int tag, int value)
{
    unsigned int mode = fn_8017F584();
    int handle = fn_8017932C(id);
    int old;
    int result = fn_8022B414(handle, tag, &old);

    if (result == 0 || result == 0x84) {
        if (mode != 1) {
            fn_8017926C(handle, tag, old, 1);
        }
        if (fn_8022B580(handle, tag, value) == 0) {
            int check;
            if (fn_8022B414(handle, tag, &check) == 0) {
                fn_80179358(id);
            }
        }
    }
}

extern "C" void fn_80179430(int handle, int tag, int value)
{
    int old;
    int result = fn_8022B7A4(handle, tag, &old);

    if (result == 0 || result == 0x84) {
        fn_8017926C(handle, tag, old, 0);
        if (fn_8022B8C8(handle, tag, value) == 0) {
            int check;
            fn_8022B7A4(handle, tag, &check);
        }
    }
}

extern "C" void fn_801794B4(int id, int tag, int value)
{
    fn_80179430(fn_80179358(id), tag, value);
}

extern "C" void fn_801794F0(int team, int tag, int value)
{
    fn_80179430(fn_800C8744(team), tag, value);
}

extern "C" void fn_8017952C(int id, int a, float b, float c)
{
    fn_8022BAB4(fn_80179358(id), a, (int)b, (int)c);
}

extern "C" void fn_80179594(int id, float a, float b)
{
    fn_8022BD30(fn_80179358(id), (int)a, (int)b);
}

extern "C" void fn_801795EC(int id, float from, float to)
{
    int total = 0;
    int yards;

    if (to > fn_80178A2C()) {
        to = fn_80178A2C();
    }
    fn_8022B414(fn_8017932C(id), 0x61796167, &total);
    yards = (int)(to - from);
    if (yards + total > 0x7FF) {
        yards = 0x7FF - total;
    } else if (yards + total < -0x7FF) {
        yards = -0x7FF - total;
    }
    fn_8017937C(id, 0x61796167, yards);
    fn_8017937C(id, 0x4E6C6167, (int)(to - from));
}

extern "C" void fn_801796C8(int id, float from, float catchY, float to, float time)
{
    int total = 0;
    int yards;
    int gain;

    if (to > fn_80178A2C()) {
        to = fn_80178A2C();
    }
    fn_8017937C(id, 0x61636367, 1);
    fn_8022B414(fn_8017932C(id), 0x61796367, &total);
    yards = (int)(to - from);
    if (yards + total > 0x3FF) {
        yards = 0x3FF - total;
    } else if (yards + total < -0x3FF) {
        yards = -0x3FF - total;
    }
    fn_8017937C(id, 0x61796367, yards);
    gain = (int)(to - from);
    fn_8017937C(id, 0x4C726367, gain);
    if (catchY < fn_80178A2C()) {
        fn_8017937C(id, 0x63796367, (int)(to - catchY));
    }
    fn_801794B4(id, 0x706F7374, gain);
    fn_801794B4(id, 0x796F7374, gain);
    fn_801794B4(id, 0x79547374, gain);
    fn_8017952C(id, 1, time, gain);
}

extern "C" void fn_80179874(int id, float from, float to, float time)
{
    int total = 0;
    int gain;
    int yards;

    fn_8022B414(fn_8017932C(id), 0x61797567, &total);
    if (to < -fn_80178A2C()) {
        to = -fn_80178A2C();
    }
    gain = (int)(to - from);
    yards = gain;
    if (yards + total > 0x3FF) {
        yards = 0x3FF - total;
    } else if (yards + total < -0x3FF) {
        yards = -0x3FF - total;
    }
    fn_8017937C(id, 0x74617567, 1);
    fn_801794B4(id, 0x61727374, 1);
    fn_8017937C(id, 0x61797567, yards);
    fn_8017937C(id, 0x4E6C7567, gain);
    fn_801794B4(id, 0x726F7374, gain);
    fn_801794B4(id, 0x796F7374, gain);
    fn_801794B4(id, 0x79547374, gain);
    if (gain > 19) {
        fn_8017937C(id, 0x79327567, 1);
    }
    if (fn_80177F7C() != 6) {
        fn_80173EE0(1, (int)from, gain, id, 0);
    }
    fn_80179594(id, time, (int)(to - from));
}

extern "C" void fn_80179A54(int id, float from, float to)
{
    int yards = (int)(to - from);

    fn_8017937C(id, 0x79697367, yards);
    fn_8017937C(id, 0x526C7367, yards);
    if (fn_80177F7C() != 6) {
        fn_80173EE0(4, (int)from, yards, id, 0);
    }
}

extern "C" void fn_80179AF0(int id, float from, float to, int flag, float spot)
{
    int yards;

    if (spot < -fn_80178A2C()) {
        spot = -fn_80178A2C();
    }
    to = to < -fn_80178A2C() ? -fn_80178A2C() : to;
    yards = (int)(from - spot);
    fn_8017937C(id, 0x4E6C7067, yards);
    fn_8017937C(id, 0x61797067, yards);
    fn_801794B4(id, 0x64507374, yards);
    if (to <= -30.0f && to > -fn_80178A2C() && flag == 0) {
        fn_8017937C(id, 0x74707067, 1);
    }
    if (to <= -fn_80178A2C() && flag == 0) {
        fn_8017937C(id, 0x62747067, 1);
        to = 20.0f - fn_80178A2C();
    }
    fn_8017937C(id, 0x796E7067, (int)(from - to));
}

extern "C" void fn_80179C74(int id, float from, float to)
{
    int yards;

    fn_8017937C(id, 0x61707267, 1);
    yards = (int)(to - from);
    fn_8017937C(id, 0x79707267, yards);
    fn_8017937C(id, 0x4C707267, yards);
    fn_801794B4(id, 0x72707374, yards);
    fn_801794B4(id, 0x79747374, yards);
    fn_801794B4(id, 0x79547374, yards);
    if (to >= fn_80178A2C()) {
        fn_80173EE0(7, (int)from, yards, id, 0);
        fn_8017937C(id, 0x74707267, 1);
        fn_80176CC8(7, yards, id, 0);
    }
}

extern "C" void fn_80179D98(int id, float from, float to)
{
    int yards;

    fn_8017937C(id, 0x616B7267, 1);
    yards = (int)(to - from);
    fn_8017937C(id, 0x796B7267, yards);
    fn_8017937C(id, 0x4C6B7267, yards);
    fn_801794B4(id, 0x726B7374, yards);
    fn_801794B4(id, 0x79747374, yards);
    fn_801794B4(id, 0x79547374, yards);
    if (to >= fn_80178A2C()) {
        fn_80173EE0(6, (int)from, yards, id, 0);
        fn_8017937C(id, 0x746B7267, 1);
        fn_80176CC8(6, yards, id, 0);
    }
}

extern "C" void fn_80179EBC(int ref)
{
    int other = fn_8009BCE8(&ref)->mUnknown1044;

    if (other != 0) {
        Object_80039F5C *p = fn_8009BCE8(&other);
        if (p->mUnknown1044 == ref && other == p->mId) {
            fn_8017937C(other, 0x61736F67, 1);
        }
    }
}

extern "C" int fn_80179F2C(unsigned char *pOut)
{
    int result;
    int carrier;
    unsigned char flips;
    int flipped;
    int kicked;
    int mode;
    int state;
    int id;
    int receiver;
    int kicker;
    float toGo;
    float startY;
    float ballY;
    float markY;
    float catchY;
    float catchX;
    float sideX;
    int caught;
    int kickTeam;
    int kickOut;
    int recovered;
    int muffed;
    int dpFlag;
    int returned;
    int rdFlag;
    int taFlag;
    unsigned short count;
    unsigned short i;
    unsigned char turnovers;
    int lateral;
    int scored;
    int zeroFlagA;
    int zeroFlagB;

    markY = 0.0f;
    startY = 0.0f;
    ballY = 0.0f;
    toGo = 0.0f;
    mode = fn_80177F7C();
    flips = 0;
    id = 0;
    carrier = 0;
    receiver = 0;
    kicker = 0;
    result = 0;
    kickOut = 0;
    muffed = 0;
    dpFlag = 0;
    recovered = 0;
    flipped = 0;
    returned = 0;
    rdFlag = 0;
    taFlag = 0;
    state = 0;
    caught = 0;
    lateral = 0;
    kicked = 0;
    count = fn_800B15D4();
    scored = 0;
    catchY = 0.0f;
    catchX = 0.0f;
    sideX = 0.0f;
    zeroFlagA = 0;
    zeroFlagB = 0;
    turnovers = 0;
    kickTeam = 0xFF;

    for (i = 0; i < count; i++) {
        Record_800B15FC *pRecord = fn_800B1648(i);

        switch (pRecord->mUnknown14) {
        case 3: {
            int who = pRecord->mUnknown0;

            markY = pRecord->mUnknown10;
            fn_8009BD2C(0, &id);
            state = 0;
            fn_801794B4(who, 0x6E737374, 1);
            startY = markY;
            ballY = markY;
            if (mode != 6 && ballY > 30.0f && !fn_801740A8()) {
                fn_8017417C();
                fn_8017C2F0(pRecord->mUnknown4);
            }
            break;
        }
        case 30:
            turnovers++;
            flips++;
            fn_80173D10();
            startY = -startY;
            markY = -markY;
            ballY = -ballY;
            catchY = -catchY;
            if (!returned) {
                flipped = 1;
            } else {
                returned = 0;
                flipped = 0;
            }
            break;
        case 4:
            id = pRecord->mUnknown0;
            state = 0x61797567;
            break;
        case 5:
            if (fn_801783AC(13)) {
                carrier = id = pRecord->mUnknown0;
                if (!taFlag) {
                    fn_8017937C(carrier, 0x74616167, 1);
                    fn_801794B4(id, 0x61707374, 1);
                    state = 0x61796167;
                    result = 1;
                    taFlag = 1;
                }
            }
            break;
        case 43:
        case 51:
            i = count;
        case 28:
            if (fn_8009BCE8(&pRecord->mUnknown4)) {
                receiver = pRecord->mUnknown4;
                fn_8017937C(receiver, 0x61746467, 1);
                if (pRecord->mUnknown8) {
                    fn_801794B4(receiver, 0x74757374, 1);
                    if (pRecord->mUnknown16) {
                        fn_801794B4(receiver, 0x70647374, 1);
                    }
                }
                if (pRecord->mUnknown10 < -fn_80178A2C() && !fn_80177F70()) {
                    fn_8017937C(receiver, 0x61736C67, 1);
                }
                if (pRecord->mUnknown10 < startY && turnovers == 0 && mode != 0) {
                    int handled = 0;

                    if (fn_80179244() && (fn_8009BCE8(&pRecord->mUnknown0)->mFlags & 0x10000000) &&
                        !fn_801783AC(13)) {
                        Object_80039F5C *p = fn_8009BCE8(&receiver);

                        fn_80093C3C(1, 5, fn_8009BCE8(&receiver));
                        fn_800310C0(lbl_803EA368, 0x16, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                        if (!scored) {
                            fn_8017937C(receiver, 0x6B736C67, 1);
                            fn_801794B4(receiver, 0x6B737374, 1);
                            fn_8017937C(pRecord->mUnknown0, 0x61736167, 1);
                            if (pRecord->mUnknown8) {
                                fn_801794B4(receiver, 0x73757374, 1);
                            }
                            scored = 1;
                            fn_80179EBC(receiver);
                        }
                        handled = 1;
                        result = 1;
                        fn_80067DB8(0x63, 0, fn_80178320(), 0, 0);
                        fn_8006F0B8(1);
                        fn_801794B4(pRecord->mUnknown0, 0x706F7374, (int)(pRecord->mUnknown10 - startY));
                        fn_801794B4(pRecord->mUnknown0, 0x796F7374, (int)(pRecord->mUnknown10 - startY));
                        fn_801794B4(pRecord->mUnknown0, 0x79547374, (int)(pRecord->mUnknown10 - startY));
                        if (mode != 6) {
                            fn_80173EE0(12, startY, pRecord->mUnknown10 - startY, id, 0);
                        }
                        state = 0;
                    }
                    if (!handled) {
                        fn_80093C3C(1, 13, fn_8009BCE8(&receiver));
                        fn_80067DB8(0x63, 0, fn_80178320(), 0, 0);
                        fn_8006F0B8(2);
                        fn_8017937C(receiver, 0x6C746467, 1);
                    }
                }
            }
        case 31:
            ballY = pRecord->mUnknown10;
            break;
        case 39:
            i = count;
        case 22:
            ballY = pRecord->mUnknown10;
            if (state == 0x61796167) {
                if (mode != 6) {
                    fn_80173EE0(0, startY, 0, carrier, 0);
                }
                fn_8017952C(carrier, 0, pRecord->mUnknownC, 0.0f);
            }
            if (state == 0x61797067 && mode != 0) {
                fn_80179AF0(kicker, startY, ballY, kicked, ballY);
            }
            break;
        case 41:
        case 45:
        case 49:
            i = count;
            if (pRecord->mUnknown14 == 45) {
                carrier = pRecord->mUnknown0;
            }
        case 21:
            fn_8017952C(carrier, 0, pRecord->mUnknownC, 0.0f);
            state = 0;
            if (mode != 6) {
                fn_80173EE0(0, startY, 0, carrier, 0);
                if (dpFlag) {
                    fn_80067DB8(0x63, 0, fn_80178320(), 0, 0);
                }
            }
            break;
        case 24:
            if (flips == 1 && id == kicker) {
                flips = 0;
            }
            if (state == 0x61797567) {
                sideX = pRecord->mUnknownC;
            }
            break;
        case 2:
            i = count;
            break;
        case 47:
            ballY = pRecord->mUnknown10;
            i = count;
        case 6:
            fn_8017937C(id, 0x6D636167, 1);
            fn_801794B4(id, 0x63707374, 1);
            caught = 1;
            state = 0x61796367;
            id = pRecord->mUnknown0;
            catchX = pRecord->mUnknownC;
            catchY = pRecord->mUnknown10;
            break;
        case 20:
            state = 0x79697367;
            fn_80093C3C(1, 3, fn_8009BCE8(&pRecord->mUnknown0));
            returned = 1;
            fn_8017937C(id, 0x6E696167, 1);
            fn_801794B4(id, 0x61677374, 1);
            fn_801794B4(id, 0x69707374, 1);
            fn_8017952C(carrier, 0, pRecord->mUnknownC, 0.0f);
            id = pRecord->mUnknown0;
            fn_8017937C(id, 0x6E697367, 1);
            fn_801794B4(id, 0x61747374, 1);
            fn_801794B4(id, 0x69447374, 1);
            markY = pRecord->mUnknown10;
            if (lbl_803EB450) {
                lbl_803EB450(6, fn_8017932C(id), 0);
            }
            break;
        case 18:
            if ((id & 0xFF)) {
                if (pRecord->mUnknown0 && !scored && fn_80179244() &&
                    (fn_8009BCE8(&id)->mFlags & 0x10000000) && pRecord->mUnknown10 < startY &&
                    !fn_801783AC(13)) {
                    recovered = 1;
                }
                if ((id & 0xFF)) {
                    switch (state) {
                    case 0x61797567:
                        if (!recovered) {
                            result = 2;
                            fn_80179874(id, startY, pRecord->mUnknown10, sideX);
                        }
                        break;
                    case 0x61796367:
                        fn_801795EC(carrier, startY, pRecord->mUnknown10);
                        fn_801796C8(id, startY, catchY, pRecord->mUnknown10, catchX);
                        break;
                    case 0x796B7267:
                        if (ballY < -fn_80178A2C()) {
                            fn_8017937C(kicker, 0x62746B67, 1);
                        } else if (!zeroFlagA) {
                            fn_80179D98(id, markY, pRecord->mUnknown10);
                        }
                        break;
                    case 0x79707267:
                        if (mode != 0 && !lateral) {
                            fn_80179AF0(kicker, startY, pRecord->mUnknown10, kicked, markY);
                            lateral = 1;
                        }
                        if (pRecord->mUnknown10 > -fn_80178A2C() && !zeroFlagA) {
                            fn_80179C74(id, markY, pRecord->mUnknown10);
                        }
                        break;
                    case 0x61797067:
                    case 0x79697367:
                        break;
                    }
                    fn_8017937C(id, 0x75667567, 1);
                    fn_801794B4(id, 0x75667374, 1);
                }
            }
            state = 0;
            markY = pRecord->mUnknown10;
            if (pRecord->mUnknown0) {
                fn_8017937C(pRecord->mUnknown0, 0x66666C67, 1);
                fn_801794B4(pRecord->mUnknown0, 0x66667374, 1);
                if ((id & 0xFF) && recovered == 1) {
                    fn_8017937C(pRecord->mUnknown0, 0x6B736C67, 1);
                    fn_801794B4(pRecord->mUnknown0, 0x6B737374, 1);
                    fn_8017937C(id, 0x61736167, 1);
                    if (pRecord->mUnknown4) {
                        fn_801794B4(pRecord->mUnknown0, 0x73757374, 1);
                    }
                    scored = 1;
                    fn_80179EBC(pRecord->mUnknown0);
                }
            }
            break;
        case 19:
            if ((id & 0xFF) && flips && flipped) {
                if (muffed) {
                    fn_8017937C(id, 0x75667567, 1);
                    fn_801794B4(id, 0x75667374, 1);
                }
                if (!kicked) {
                    fn_801794B4(id, 0x6C667374, 1);
                    fn_801794B4(id, 0x61677374, 1);
                } else {
                    fn_801794B4(kicker, 0x61677374, 1);
                }
                fn_801794B4(pRecord->mUnknown0, 0x61747374, 1);
                if (flips & 1) {
                    fn_80093C3C(1, 7, fn_8009BCE8(&pRecord->mUnknown0));
                } else {
                    fn_80093C3C(1, 6, fn_8009BCE8(&pRecord->mUnknown0));
                }
            }
            kicked = 0;
            if (flips && flipped) {
                fn_8017937C(pRecord->mUnknown0, 0x72666C67, 1);
                fn_801794B4(pRecord->mUnknown0, 0x72667374, 1);
                if (lbl_803EB450) {
                    lbl_803EB450(7, fn_8017932C(pRecord->mUnknown0), 0);
                }
                state = 0x79666C67;
            } else if (!muffed) {
                state = 0x79666C67;
            }
            flipped = 0;
            muffed = 0;
            id = pRecord->mUnknown0;
            markY = pRecord->mUnknown10;
            break;
        case 8:
            if (fn_8009BCE8(&id)->mIdBytes[2] != fn_8009BCE8(&pRecord->mUnknown0)->mIdBytes[2]) {
                fn_8017937C(id, 0x75667567, 1);
                fn_801794B4(id, 0x75667374, 1);
                fn_801794B4(id, 0x6C667374, 1);
                fn_801794B4(id, 0x61677374, 1);
                fn_8017937C(pRecord->mUnknown0, 0x72666C67, 1);
                fn_801794B4(pRecord->mUnknown0, 0x72667374, 1);
                fn_801794B4(pRecord->mUnknown0, 0x61747374, 1);
                if (lbl_803EB450) {
                    lbl_803EB450(6, fn_8017932C(pRecord->mUnknown0), 0);
                }
                state = 0x79666C67;
            } else if (state != 0x79697367 && state != 0x61796367 && state != 0x79666C67) {
                state = 0x61797567;
            }
            id = pRecord->mUnknown0;
            break;
        case 32:
            if (pRecord->mUnknown4 == 7) {
                sideX = fn_80178A08();
            } else {
                sideX = -fn_80178A08();
            }
            break;
        case 14:
            result = 3;
            state = 0;
            id = kicker = pRecord->mUnknown0;
            toGo = fn_80178A44() - pRecord->mUnknown10;
            if (startY > 30.0f && !fn_801740A8()) {
                fn_8017417C();
                fn_8017C2F0(fn_8009BCE8(&kicker)->mId >> 8 & 0xFF);
            }
            fn_8017937C(kicker, 0x61666B67, 1);
            break;
        case 17:
            id = pRecord->mUnknown0;
            fn_8017937C(id, 0x6C626C67, 1);
            kicked = 1;
            if (state == 0x61797067) {
                state = 0;
                fn_80179AF0(kicker, startY, startY, 1, startY);
                fn_8017937C(kicker, 0x6C627067, 1);
            } else {
                fn_8017937C(kicker, 0x62666B67, 1);
            }
            break;
        case 9:
            id = kicker = pRecord->mUnknown0;
            if (mode != 0) {
                fn_8017937C(kicker, 0x74617067, 1);
                fn_801794B4(kicker, 0x75707374, 1);
            }
            state = 0x61797067;
            result = 3;
            break;
        case 12:
            id = kicker = pRecord->mUnknown0;
            kickTeam = id >> 8 & 0xFF;
            fn_8017937C(id, 0x6B6E6B67, 1);
            state = 1;
            break;
        case 11:
            ballY = pRecord->mUnknown10;
            if (state == 0x61797067 && mode != 0) {
                fn_80179AF0(kicker, startY, ballY, kicked, ballY);
                state = 0;
            }
            break;
        case 55:
            muffed = 1;
            id = pRecord->mUnknown0;
            ballY = pRecord->mUnknown10;
            if (state == 0x61797067 && mode != 0) {
                fn_80179AF0(kicker, startY, ballY, kicked, ballY);
                lateral = 1;
            }
            state = 0x79707267;
            markY = pRecord->mUnknown10;
            break;
        case 10:
            id = pRecord->mUnknown0;
            markY = pRecord->mUnknown10;
            if (zeroFlagA) {
                ballY = markY;
            }
            state = 0x79707267;
            break;
        case 13:
            id = pRecord->mUnknown0;
            markY = pRecord->mUnknown10;
            if (kickTeam == (id >> 8 & 0xFF)) {
                kickOut = 1;
            }
            state = 0x796B7267;
            break;
        case 7:
        case 15:
        case 16:
        case 25:
        case 40:
        case 42:
        case 44:
        case 46:
        case 48:
        case 50:
        case 52:
        case 53:
        case 54:
        case 56:
        case 61:
            break;
        case 33:
            fn_801794B4(pRecord->mUnknown0, 0x68717374, 1);
            break;
        case 34:
            fn_801794B4(pRecord->mUnknown0, 0x6B717374, 1);
            break;
        case 35:
            fn_8017937C(pRecord->mUnknown0, 0x64706467, 1);
            dpFlag = 1;
            fn_801794B4(pRecord->mUnknown0, 0x64707374, 1);
            break;
        case 36: {
            Record_800B15FC *pNext = fn_800B1648(i + 1);

            if (!((pNext->mUnknown14 == 6 || pNext->mUnknown14 == 36) && pNext->mUnknown0 == pRecord->mUnknown0) &&
                !rdFlag) {
                fn_8017937C(pRecord->mUnknown0, 0x72646367, 1);
                rdFlag = 1;
                fn_801794B4(pRecord->mUnknown0, 0x70447374, 1);
            }
            if (pRecord->mUnknown4 == 1) {
                fn_80067DB8(0x63, 0, fn_80178320(), 0, 0);
            }
            break;
        }
        case 37:
            if (!zeroFlagB && mode != 0 && turnovers == 0) {
                fn_8017937C(pRecord->mUnknown0, 0x61706F67, 1);
            }
            break;
        case 38:
            fn_8017937C(pRecord->mUnknown0, 0x74627567, 1);
            break;
        case 57:
            fn_801794B4(pRecord->mUnknown0, 0x6A737374, 1);
            if (pRecord->mUnknown4) {
                fn_801794B4(pRecord->mUnknown0, 0x6F667374, 1);
            }
            if (pRecord->mUnknown8 == 4) {
                fn_801794B4(pRecord->mUnknown0, 0x6A777374, 1);
            }
            break;
        case 58:
            fn_801794B4(pRecord->mUnknown0, 0x61737374, 1);
            break;
        case 59:
            fn_801794B4(pRecord->mUnknown0, 0x68647374, 1);
            break;
        case 60:
            if (!scored) {
                fn_8017937C(pRecord->mUnknown0, 0x6B736C67, 1);
                fn_801794B4(pRecord->mUnknown0, 0x6B737374, 1);
                fn_8017937C(pRecord->mUnknown8, 0x61736167, 1);
                if (pRecord->mUnknown4) {
                    fn_801794B4(pRecord->mUnknown0, 0x73757374, 1);
                }
                scored = 1;
            }
            break;
        }
    }

    fn_80093C3C(6, fn_8009BCE8(&id) ? fn_8009BCE8(&id)->mIdBytes[2] << 8 | fn_8009BCE8(&id)->mIdBytes[1] : 0xFF, 0);

    switch (state) {
    case 0x61797567:
        result = 2;
        fn_80179874(id, startY, ballY, sideX);
        if (fn_8016FAD8(&toGo)) {
            fn_8017937C(id, 0x68797567, (int)(ballY - toGo));
        }
        if (ballY > fn_80178A2C() && mode != 6) {
            fn_8017937C(id, 0x64747567, 1);
            fn_801794B4(id, 0x74727374, 1);
            fn_80176CC8(1, ballY - startY, id, 0);
            if (lbl_803EB450) {
                lbl_803EB450(1, fn_8017932C(id), 0);
            }
        }
        break;
    case 0x61796367: {
        float endY;

        fn_801795EC(carrier, startY, ballY);
        fn_801796C8(id, startY, catchY, ballY, catchX);
        if (ballY > fn_80178A2C()) {
            endY = fn_80178A2C();
        } else {
            endY = ballY;
        }
        if (mode != 6) {
            fn_80173EE0(0, startY, endY - startY, carrier, id);
        }
        if ((ballY >= fn_80178A2C() || (fn_8009BCE8(&id)->mFlags & 0x800000)) && mode != 6) {
            fn_8017937C(carrier, 0x64746167, 1);
            fn_8017937C(id, 0x64746367, 1);
            fn_801794B4(carrier, 0x74507374, 1);
            fn_80176CC8(0, fn_80178A2C() - startY, carrier, id);
            if (lbl_803EB450) {
                lbl_803EB450(0, fn_8017932C(id), 0);
            }
        }
        break;
    }
    case 0x79697367:
        fn_80179A54(id, markY, ballY);
        if (ballY > fn_80178A2C() && mode != 6) {
            if (fn_801486A0() != 3) {
                fn_8017937C(id, 0x74697367, 1);
                fn_801794B4(id, 0x72697374, 1);
                fn_801794B4(id, 0x64647374, 1);
            }
            fn_80176CC8(4, ballY - markY, id, 0);
            if (lbl_803EB450) {
                lbl_803EB450(2, fn_8017932C(id), 0);
            }
        }
        break;
    case 0x796B7267:
        if (ballY < -fn_80178A2C()) {
            fn_8017937C(kicker, 0x62746B67, 1);
        } else if (!zeroFlagA && !kickOut) {
            fn_80179D98(id, markY, ballY);
        }
        break;
    case 0x79707267:
        if (mode != 0 && !lateral) {
            fn_80179AF0(kicker, startY, ballY, kicked, markY);
        }
        if (ballY > -fn_80178A2C() && !zeroFlagA) {
            fn_80179C74(id, markY, ballY);
        }
        break;
    case 0x79666C67:
        if (flips & 1) {
            float gain = ballY - markY;
            int yards;

            if (mode != 6) {
                fn_80173EE0(3, markY, gain, id, 0);
            }
            yards = (int)gain;
            fn_8017937C(id, 0x79666C67, yards);
            if (ballY > fn_80178A2C() && mode != 6) {
                fn_8017937C(id, 0x74666C67, 1);
                fn_801794B4(id, 0x64647374, 1);
                fn_80176CC8(3, yards, id, 0);
                if (lbl_803EB450) {
                    lbl_803EB450(2, fn_8017932C(id), 0);
                }
            }
        } else if (ballY > fn_80178A2C() && mode != 6) {
            fn_8017937C(id, 0x64747567, 1);
            fn_801794B4(id, 0x74727374, 1);
            fn_80176CC8(3, ballY - markY, id, 0);
            if (lbl_803EB450) {
                lbl_803EB450(1, fn_8017932C(id), 0);
            }
        }
        break;
    case 1:
        if (ballY < -fn_80178A2C()) {
            fn_8017937C(kicker, 0x62746B67, 1);
        }
        break;
    }

    if (carrier) {
        if (caught == 1) {
            fn_8017937C(carrier, 0x63636167, 1);
        } else {
            fn_8022B2CC(fn_8017932C(carrier), 0x63636167, 0);
        }
    }
    *pOut = caught;
    return result;
}

extern "C" int fn_8017B83C(void)
{
    unsigned char flag = 0;
    int reported = 0;
    int result;
    int passer;
    signed char team;
    int sameTeam;
    int carrier;
    float yards;
    int kind;
    int tackler;
    unsigned short count;
    unsigned short i;

    fn_80179F2C(&flag);
    fn_8009BD2C(0, &passer);
    team = 2;
    fn_80177F7C();
    sameTeam = 0;
    carrier = 0;
    result = 0;
    yards = 0.0f;
    kind = 0;
    count = fn_800B15D4();
    tackler = 0;

    for (i = 0; i < count; i++) {
        Record_800B15FC *pRecord = fn_800B1648(i);

        switch (pRecord->mUnknown14) {
        case 3:
            yards = pRecord->mUnknown10;
            kind = 0;
            fn_8009BD2C(0, &carrier);
            break;
        case 30:
            yards = -yards;
            break;
        case 4:
            carrier = pRecord->mUnknown0;
            kind = 0x61797567;
            break;
        case 5:
            passer = carrier = pRecord->mUnknown0;
            kind = 0x61796167;
            result = 1;
            break;
        case 22:
            if (lbl_803EB454) {
                i = count;
            }
        case 28:
            yards = pRecord->mUnknown10;
            break;
        case 2:
            i = count;
            fn_80173D10();
            break;
        case 6:
            carrier = pRecord->mUnknown0;
            kind = 0x61796367;
            break;
        case 20:
            fn_80093C3C(1, 3, fn_8009BCE8(&pRecord->mUnknown0));
            kind = 0x79697367;
            carrier = pRecord->mUnknown0;
            break;
        case 18:
            if (team == 2) {
                team = pRecord->mUnknown0Bytes[2] ^ 1;
            }
            break;
        case 19:
            carrier = pRecord->mUnknown0;
            kind = 0x79666C67;
            sameTeam = team == (carrier >> 8 & 0xFF);
            break;
        case 8:
            carrier = pRecord->mUnknown0;
            if (kind != 0x79697367 && kind != 0x61796367 && kind != 0x79666C67) {
                kind = 0x61797567;
            }
            break;
        case 9:
        case 14:
            tackler = pRecord->mUnknown0;
            fn_8017937C(tackler, 0x61656B67, 1);
            result = 3;
        case 21:
        case 55:
            kind = 0;
            break;
        case 15:
            fn_8017937C(tackler, 0x6D656B67, 1);
            reported = 1;
            fn_80176E34(5, 1, tackler, 0);
            break;
        case 16:
            fn_80176E34(10, 1, tackler, 0);
            reported = 1;
            break;
        case 17:
            carrier = pRecord->mUnknown0;
            fn_8017937C(carrier, 0x6C626C67, 1);
            if (kind == 0x61797067) {
                fn_8017937C(tackler, 0x6C627067, 1);
            } else {
                fn_8017937C(tackler, 0x62656B67, 1);
            }
            break;
        }
    }

    fn_80093C3C(6,
                fn_8009BCE8(&carrier) ? fn_8009BCE8(&carrier)->mIdBytes[2] << 8 |
                                            fn_8009BCE8(&carrier)->mIdBytes[1]
                                      : 0xFF,
                0);

    switch (kind) {
    case 0x61797567:
        result = 2;
        if (yards >= fn_80178A2C()) {
            fn_8017937C(carrier, 0x70327567, 1);
            reported = 1;
            fn_80176E34(1, 0, carrier, 0);
        }
        break;
    case 0x61796367:
        if (yards >= fn_80178A2C() || (fn_8009BCE8(&carrier)->mFlags & 0x800000)) {
            fn_8017937C(carrier, 0x70326367, 1);
            reported = 1;
            fn_80176E34(0, 0, passer, carrier);
        }
        break;
    case 0x79666C67:
        if (sameTeam && yards >= fn_80178A2C()) {
            fn_8017937C(carrier, 0x70327567, 1);
            reported = 1;
            fn_80176E34(1, 0, carrier, 0);
        }
        break;
    case 0x79697367:
    case 0x796B7267:
    case 0x79707267:
        break;
    }

    if (!reported) {
        fn_80176E34(11, 0, carrier, 0);
    }

    if (lbl_803EB450) {
        int mode = fn_80179138();
        int event = 11;
        int number = fn_8017932C(carrier);

        if (mode == 1) {
            event = 3;
        } else if (mode == 2) {
            event = 4;
        }
        lbl_803EB450(event, number, reported);
    }
    return result;
}

extern "C" void fn_8017BD70(Object_8017886C *pResult, int kind, unsigned char flag)
{
    int offense;
    int defense;
    float spot;
    unsigned int down;
    int toGo;
    int gained;

    fn_800B2314();
    offense = fn_80178348();
    defense = fn_80178360();
    if (pResult->mUnknown04 != 6) {
        spot = pResult->mUnknown08.mY;
    } else {
        spot = fn_80178A2C();
    }
    down = fn_80177F7C();
    toGo = (int)(fn_80178298() - fn_80178070().mY);
    gained = (int)(spot - fn_80178070().mY);

    if (kind == 1 || kind == 2) {
        switch (down) {
        case 1:
            fn_801794F0(offense, 0x6C317374, 1);
            if (kind == 1) {
                fn_801794F0(offense, 0x70317374, 1);
            } else if (kind == 2) {
                fn_801794F0(offense, 0x72317374, 1);
            }
            fn_801794F0(offense, 0x79317374, gained);
            break;
        case 2:
            if (kind == 1) {
                fn_801794F0(offense, 0x70327374, 1);
            } else if (kind == 2) {
                fn_801794F0(offense, 0x72327374, 1);
            }
            break;
        case 3:
            fn_801794F0(offense, 0x64337374, 1);
            if (toGo <= 9) {
                if (toGo <= 3) {
                    fn_801794F0(offense, 0x79333374, 1);
                } else {
                    fn_801794F0(offense, 0x79343374, 1);
                }
            } else {
                fn_801794F0(offense, 0x79313374, 1);
            }
            if (kind == 1) {
                fn_801794F0(offense, 0x70337374, 1);
            } else if (kind == 2) {
                fn_801794F0(offense, 0x72337374, 1);
            }
            break;
        case 4:
            fn_801794F0(offense, 0x64347374, 1);
            if (kind == 1) {
                fn_801794F0(offense, 0x70347374, 1);
            } else if (kind == 2) {
                fn_801794F0(offense, 0x72347374, 1);
            }
            break;
        }

        if ((pResult->mUnknown04 == 1 || pResult->mUnknown04 == 6) && !(pResult->mUnknown18 & 4) &&
            (fn_80177C38() & 1) == 0) {
            switch (down) {
            case 1:
            case 2:
                break;
            case 3:
                fn_801794F0(offense, 0x63337374, 1);
                if (toGo <= 9) {
                    if (toGo <= 3) {
                        fn_801794F0(offense, 0x63333374, 1);
                    } else {
                        fn_801794F0(offense, 0x63343374, 1);
                    }
                } else {
                    fn_801794F0(offense, 0x63313374, 1);
                }
                break;
            case 4:
                fn_801794F0(offense, 0x63347374, 1);
                break;
            }
            if (down >= 1 && down <= 5 && pResult->mUnknown04 != 6) {
                fn_801794F0(offense, 0x64317374, 1);
                if (!flag) {
                    fn_801794F0(offense, 0x66727374, 1);
                }
            }
        }

        if (down == 6 && kind != 3) {
            fn_801794F0(offense, 0x61327374, 1);
            if (pResult->mUnknown1D == 2) {
                fn_801794F0(offense, 0x63327374, 1);
            }
        }

        if ((pResult->mUnknown18 & 0x800) && lbl_803EB450) {
            lbl_803EB450(8, 0x7FFF, 0);
        }

        if (fn_8016871C((unsigned char)defense)->mUnknown14 == 31) {
            fn_801794F0(defense, 0x7A627374, 1);
        }
    }

    if (pResult->mUnknown1D == -2) {
        fn_801794F0(fn_80178320(), 0x74737374, 1);
        if (pResult->mUnknown00 == 0) {
            fn_80176CC8(9, 0, (fn_80178320() & 0xFF) << 8 | 1, 0);
            if (lbl_803EB450) {
                lbl_803EB450(5, 0x7FFF, 0);
            }
        } else {
            fn_80176CC8(9, 0, pResult->mUnknown00, 0);
            if (lbl_803EB450) {
                lbl_803EB450(5, fn_8017932C(pResult->mUnknown00), 0);
            }
        }
        fn_80173D10();
    }
}

extern "C" void fn_8017C1EC(void)
{
}

extern "C" void fn_8017C1F0(Object_8017886C *pResult)
{
    unsigned char flag = 0;
    int kind;

    lbl_803ECB34 = pResult;
    fn_8017C4B8();
    fn_8017C1EC();
    lbl_803EB454 = 0;
    if (fn_80177F7C() != 6) {
        kind = fn_80179F2C(&flag);
    } else {
        kind = fn_8017B83C();
    }
    fn_8017BD70(pResult, kind, flag);
}

extern "C" void fn_8017C25C(int value)
{
    fn_801794F0(fn_80178308(), 0x74707374, value);
}

extern "C" void fn_8017C298(unsigned short team, short value)
{
    if (team <= 1) {
        fn_801794F0(team, 0x73707374, 1);
        fn_801794F0(team, 0x66737374, value);
    }
}

extern "C" void fn_8017C2F0(unsigned short team)
{
    if (team <= 1) {
        fn_801794F0(team, 0x7A6F7374, 1);
        fn_801794F0(team ^ 1, 0x72647374, 1);
    }
}

extern "C" void fn_8017C344(unsigned short team, int play)
{
    if (team <= 1) {
        switch (play) {
        case 0:
        case 1:
            fn_801794F0(team, 0x746F7374, 1);
            fn_801794F0(team ^ 1, 0x74647374, 1);
            break;
        case 5:
            fn_801794F0(team, 0x666F7374, 1);
            fn_801794F0(team ^ 1, 0x66647374, 1);
            break;
        }
    }
}

extern "C" void fn_8017C3E4(unsigned short team, short yards, int handle)
{
    if (team <= 1) {
        short spot;
        int mode;

        fn_801794F0(team, 0x65707374, 1);
        fn_801794F0(team, 0x79507374, yards);
        if (team == (unsigned short)fn_80178308() && (unsigned short)fn_80178348() == team) {
            yards = -yards;
        }
        spot = (short)fn_80177FE0().mY;
        mode = fn_80177F70();
        if (mode != 0 && mode != 6) {
            fn_80173EE0(8, spot, yards, handle, 0);
        }
    }
}

extern "C" void fn_8017C4B8(void)
{
    lbl_80361F88[0].mKind = -1;
    lbl_803EB458 = 0;
    if (fn_8017F584() != 1) {
        int home;
        int away;

        fn_800C8704(&home, &away);
        lbl_802E9ADC[0].mTp = 0;
        lbl_802E9ADC[0].mSp = 0;
        lbl_802E9ADC[0].mFs = 0;
        lbl_802E9ADC[1].mTp = 0;
        lbl_802E9ADC[1].mSp = 0;
        lbl_802E9ADC[1].mFs = 0;
        fn_8022B7A4(home, 0x74707374, &lbl_802E9ADC[0].mTp);
        fn_8022B7A4(home, 0x73707374, &lbl_802E9ADC[0].mSp);
        fn_8022B7A4(home, 0x66737374, &lbl_802E9ADC[0].mFs);
        fn_8022B7A4(away, 0x74707374, &lbl_802E9ADC[1].mTp);
        fn_8022B7A4(away, 0x73707374, &lbl_802E9ADC[1].mSp);
        fn_8022B7A4(away, 0x66737374, &lbl_802E9ADC[1].mFs);
    }
}

extern "C" void fn_8017C5A0(unsigned short team, int value)
{
    fn_801794F0(team, 0x50747374, value);
}

extern "C" void fn_8017C5CC(unsigned short team, int value)
{
    fn_801794F0(team, 0x62737374, value);
}

extern "C" void fn_8017C5F8(unsigned short team, int value)
{
    fn_801794F0(team, 0x7A707374, value);
    fn_801794F0(team, 0x4F707374, value);
}

extern "C" void fn_8017C648(unsigned short team, int value)
{
    fn_801794F0(team, 0x70737374, value);
}

extern "C" void fn_8017C674(unsigned short team, int value)
{
    fn_801794F0(team, 0x63757374, value);
}

extern "C" void fn_8017C6A0(unsigned short team, int value)
{
    fn_801794F0(team, 0x70777374, value);
}

extern "C" void fn_8017C6CC(unsigned short team, int value, int also)
{
    if (also) {
        fn_801794F0(team, 0x73327374, value);
    }
    fn_801794F0(team, 0x73737374, value);
}

extern "C" void fn_8017C724(unsigned short team, int value)
{
    fn_801794F0(team, 0x64737374, value);
}

extern "C" void fn_8017C750(unsigned short team, int value, int also)
{
    if (also) {
        fn_801794F0(team, 0x68327374, value);
    }
    fn_801794F0(team, 0x68737374, value);
}

extern "C" void fn_8017C7A8(unsigned short team, int value)
{
    fn_801794F0(team, 0x68777374, value);
}

extern "C" void fn_8017C7D4(unsigned short team, int value)
{
    fn_801794F0(team, 0x69737374, value);
}

extern "C" void fn_8017C800(unsigned short team, int value)
{
    fn_801794F0(team, 0x53637374, value);
}

extern "C" void fn_8017C82C(unsigned short team, int value)
{
    fn_801794F0(team, 0x55637374, value);
}

extern "C" void fn_8017C858(unsigned short team, int value)
{
    fn_801794F0(team, 0x74767374, value);
}

extern "C" void fn_8017C884(unsigned short team, int value)
{
    fn_801794F0(team, 0x43637374, value);
}

extern "C" void fn_8017C8B0(unsigned short team, int value)
{
    fn_801794F0(team, 0x676F7374, value);
}

extern "C" void fn_8017C8DC(unsigned short team, int value)
{
    fn_801794F0(team, 0x74537374, value);
}

extern "C" void fn_8017C908(unsigned short team, int value)
{
    fn_801794F0(team, 0x43737374, value);
}

extern "C" void fn_8017C934(unsigned short team, int value)
{
    fn_801794F0(team, 0x76737374, value);
}

extern "C" void fn_8017C960(unsigned short team, int value)
{
    fn_801794F0(team, 0x74777374, value);
}

extern "C" void fn_8017C98C(unsigned short team, int value)
{
    fn_801794F0(team, 0x50637374, value);
}

extern "C" void fn_8017C9B8(unsigned short team, int value)
{
    fn_801794F0(team, 0x69757374, value);
}

extern "C" void fn_8017C9E4(unsigned short team, int value)
{
    fn_801794F0(team, 0x63777374, value);
}

extern "C" void fn_8017CA10(unsigned short team, int value)
{
    fn_801794F0(team, 0x77777374, value);
}

extern "C" void fn_8017CA3C(unsigned short team, int value)
{
    fn_801794B4(team, 0x73687374, value);
}

extern "C" void fn_8017CA68(unsigned short team, int value)
{
    fn_801794F0(team, 0x6C627374, value);
}

extern "C" void fn_8017CA94(unsigned short team, int value)
{
    fn_801794F0(team, 0x61677374, value);
}

extern "C" void fn_8017CAC0(void (*pCallback)(int kind, int a, int b))
{
    lbl_803EB450 = pCallback;
}
