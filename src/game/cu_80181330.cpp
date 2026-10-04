#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/PaletteColor.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/fn_8021D7B8.h"

/* One entry of the screen stack lbl_80362B14. */
struct StackEntry_80362B14 {
    int mUnknown0;
    Class_80184190 *mpScreen;
};

/* Texts and values shown by the current screen. */
struct State_80362A84 {
    char mName0[21];
    char mName1[21];
    char mName2[21];
    int mUnknown64;
    int mUnknown68;
    int mUnknown72;
    int mUnknown76;
    int mUnknown80;
    int mUnknown84;
    int mUnknown88;
    unsigned char mUnknown92;
    int mUnknown96;
    int mValues[10];
    int mUnknown140;
};

/* Constants returned by fn_80183734. */
struct Layout_802EA9E0 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    unsigned char mUnknown24;
};

extern "C" {
extern void *lbl_803EB688;

Class_80184190 *fn_800053D0(void);
Class_80184190 *fn_800088C8(void);
void fn_8000890C(int value);
int fn_80008914(void);
int fn_8000891C(void);
void fn_80008924(void);
int fn_800089C0(void);
int fn_800089D8(void);
void fn_800089E0(int a);
Class_80184190 *fn_8000EB3C(void);
int fn_8000EB5C(void);
int fn_8000EB80(void);
void fn_8000EBA4(int a);
int fn_8000EC14(void);
int fn_8000EC38(void);
void fn_80022398(void);
void fn_800223C0(void);
void fn_800223E4(int index, float x, float y, float z);
void fn_800224A4(int index, float angle);
void fn_80022534(int index, float scale);
void fn_80022580(int index, int a, int b);
void fn_800225F4(int index, unsigned int value);
void fn_80022730(int index, int a);
void fn_80022870(int index, float x, float y, float z, float angle, float scale, int flag);
int fn_800229D8(void);
float fn_80022BA0(float a);
void fn_80022D0C(int a);
unsigned char fn_80022D3C(unsigned char enable, int a, int b);
void fn_80029CE0(int a, int b);
void fn_8005F29C(void);
void fn_80077F24(void);
int fn_80078B94(void);
void fn_80078BB8(int a);
int fn_8007A43C(Object_8007A334 *pObject);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
void fn_8007BA48(Object_8007A334 *pObject);
void fn_8007BB04(Object_8007A334 *pObject);
int fn_8007BB84(Object_8007A334 *pCursor, int a, int b, int *pResult);
void fn_8007BE20(Object_8007A334 *pCursor, char *pBuffer, int size);
int fn_8007BF14(int a);
int fn_8007C690(Object_8007A334 *pCursor, short *pOut);
void fn_80080B08(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80080BEC(Object_8008044C *pObject, char *pBuffer, int size);
void fn_800816C4(Object_8008044C *pObject, int a, int *pValues);
void fn_8008174C(Object_8008044C *pObject, short *pValues);
void fn_80082534(int a, int b);
void fn_80082558(int a, int b);
int fn_8008775C(void);
void fn_80087880(int a);
void fn_8017F670(int a, char *pText);
int fn_8017FB54(int a, int b);
void fn_8017FB64(int value, int *pQuotient, int *pRemainder);
int fn_8017FB88(void);
int fn_801801B4(void);
int fn_80186B38(int a);
void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor);
int fn_80188DF0(int a);
int fn_8018BD9C(int a);
int fn_8018BDFC(int a, int b, int c, int *pD);
void fn_8018BF10(int a, int b);
void fn_8018BF3C(void);
void fn_8018C008(int *pA, int *pB, int c);
void fn_8018C044(int a, int b);
void fn_8018C064(int a, int b);
void fn_8018C48C(int tag);
int fn_8018D23C(int a);
int fn_8018D720(int a);
int fn_8018D890(int a, int b);
void fn_8018D8EC(int a, int b);
void fn_8018D918(void);
void fn_8018DE40(int *pA, int *pB, int c);
void fn_8018DE7C(int a, int b);
void fn_8018DE9C(int a, int b);
int fn_8018E3DC(int a);
void fn_8018E428(int a, int b);
int fn_8018E4B4(void);
void fn_8018E7A0(int index, int value);
void fn_8018E8B0(int a, int b, int c);
void fn_8018EF6C(int a);
int fn_8018F228(int a);
void fn_8018F41C(int a);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_801C302C(const char *s1, const char *s2, int n);
unsigned int fn_801C3180(const char *pText);
void *fn_8021EA44(int index);
unsigned int fn_80225F88(void *a, int b, int c, const char *pText);
int fn_8022F384(int a);
int fn_8022F4BC(void);
}

static int lbl_803EB548 = 6;
static unsigned char lbl_803EB54C = 0;
static int lbl_803EB550 = 0;
static int lbl_803EB554 = 0;
static int lbl_803EB558 = 0;
static signed char lbl_803EB55C = 0;
static int lbl_803EB560 = 0;
static int lbl_803EB564 = 0;
static int lbl_803EB568 = 0;
static int lbl_803EB56C = -1;
static int lbl_803EB570 = 0;
static int lbl_803EB574 = 0;
static int lbl_803EB578 = 0;
static unsigned char lbl_803EB57C = 0;
static int lbl_803EB580 = -1;
static int lbl_803EB584 = -1;
static unsigned char lbl_803EB588 = 0;
static unsigned char lbl_803EB589 = 0;
static unsigned char lbl_803EB58A = 0;
static unsigned char lbl_803EB58B = 0;
static unsigned char lbl_803EB58C = 0;
static unsigned char lbl_803EB58D = 0;

static Entry_80182CC8 lbl_802EA988[2] = {
    {0, 0, "Edit Team", 1, 0, 0, 0},
    {1, 0, "Edit Player", 1, 0, 0, 0},
};
static Layout_802EA9E0 lbl_802EA9E0 = {525.0f, 415.0f, 8.2f, 353.0f, 1.0f, 15, 1};
static int lbl_802EA9FC[10] = {6, 4, 7, 0, 3, 2, 1, 5, 8, 9};
static char lbl_802EAA24[28] = "";

extern Object_8007A334 lbl_80362A2C;
extern Object_8008044C lbl_80362A58;
static State_80362A84 lbl_80362A84;
static StackEntry_80362B14 lbl_80362B14[8];
static char lbl_80362B54[28];
static unsigned char lbl_80362B70[10];

extern Class_802A6BB0 lbl_803ECB60;
static Class_802A6BB0 *lbl_803ECB64;
static int lbl_803ECB68;
static unsigned char lbl_803ECB6C[3];
static unsigned char lbl_803ECB70[3];
static int lbl_803ECB74;
static int lbl_803ECB78;
static int lbl_803ECB7C;

/* Functions of this file referenced before their definitions. */
extern "C" {
void fn_8018196C(void);
void fn_801826FC(unsigned char *pOut);
Object_8007A334 *fn_80182DBC(void);
Object_8008044C *fn_80182DC8(void);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_80182E64(int a);
void fn_80182E70(int a);
void fn_80182E7C(int a);
void fn_80182E88(int a, int b);
void fn_80182E9C(int a);
void fn_80182EC4(unsigned char a);
void fn_8018300C(void);
void fn_801831A4(void);
void fn_801831E8(unsigned char a);
void fn_801831F8(int a);
void fn_80183368(int mode, int value);
void fn_801834DC(void);
int fn_801835A0(void);
void fn_801835C0(int a);
Layout_802EA9E0 *fn_80183734(void);
int fn_80183948(void);
int fn_80183950(void);
int fn_80183968(void);
int fn_8018397C(void);
}

inline Class_802A6BB0 *Class_80184190::vfn_06()
{
    return 0;
}

/* Class of the instance returned by fn_801841AC; vtable 0x802A6B10. */
class Class_802A6B10 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual int vfn_07() { return 2; }
    virtual Entry_80182CC8 *vfn_08() { return lbl_802EA988; }

    char mUnknown4[4];
};

static inline Class_802A6B10 *fn_801841AC();

extern "C" {

void fn_80181330(void)
{
    switch (lbl_803EB548) {
    case 4:
        lbl_803ECB7C = fn_8018E3DC(lbl_803EB55C);
        fn_8018C008(&lbl_803ECB74, &lbl_803ECB78, fn_8022F4BC());
        break;
    case 3:
        lbl_803ECB7C = fn_8018E3DC(lbl_803EB55C);
        break;
    case 5:
        lbl_803ECB7C = 0;
        break;
    case 0:
    case 2:
        lbl_803ECB7C = fn_80078B94();
        break;
    default:
        lbl_803ECB7C = fn_80078B94();
        fn_8018DE40(&lbl_803ECB74, &lbl_803ECB78, fn_8022F4BC());
        break;
    }
}

void fn_801813F4(void)
{
    switch (lbl_803EB548) {
    case 4:
        fn_8018C044(lbl_803ECB74, lbl_803ECB78);
        break;
    case 0:
    case 2:
    case 3:
    case 5:
        break;
    default:
        fn_8018DE7C(lbl_803ECB74, lbl_803ECB78);
        break;
    }
}

void fn_80181458(void)
{
    if (fn_8018397C()) {
        fn_80082558(lbl_803ECB68, lbl_803EB55C);
        return;
    }
    if (fn_80183950()) {
        fn_8018C064(lbl_803ECB74, lbl_803ECB78);
    } else {
        fn_8018DE9C(lbl_803ECB74, lbl_803ECB78);
    }
    fn_8018196C();
    fn_8000890C(lbl_803ECB7C);
    if (!fn_80183950()) {
        fn_80078BB8(lbl_803ECB7C);
    }
    fn_80008924();
}

void fn_801814E0(Class_80184190 *pScreen)
{
    lbl_803EB550++;
    lbl_80362B14[lbl_803EB550].mpScreen = pScreen;
    lbl_80362B14[lbl_803EB550].mUnknown0 = 0;
}

void fn_8018150C(Class_80184190 *pScreen)
{
    lbl_803EB550 = 0;
    lbl_80362B14[lbl_803EB550].mUnknown0 = 0;
    lbl_80362B14[lbl_803EB550].mpScreen = pScreen;
}

void fn_8018152C(void)
{
    lbl_80362B14[lbl_803EB550].mpScreen = 0;
    lbl_803EB550--;
}

Class_80184190 *fn_80181554(void)
{
    return lbl_80362B14[lbl_803EB550].mpScreen;
}

int fn_80181570(void)
{
    return lbl_80362B14[lbl_803EB550].mUnknown0;
}

void fn_80181588(int value)
{
    lbl_80362B14[lbl_803EB550].mUnknown0 = value;
}

int fn_801815A0(int value)
{
    int i;

    for (i = 0; i < 10; i++) {
        if (lbl_802EA9FC[i] == value) {
            break;
        }
    }
    return i;
}

void fn_801815D8(int a, int *pCount, int *pValue)
{
    fn_80181554()->vfn_01(a, pCount, pValue);
    lbl_803EB558 = *pCount;
    fn_80181588(*pValue);
    lbl_803ECB64 = fn_80181554()->vfn_06();
    if (lbl_803ECB64 == 0) {
        lbl_803ECB64 = &lbl_803ECB60;
    }
}

void fn_80181670(int a, int *pCount, int *pValue)
{
    char buffer[24];

    lbl_803EB550 = -1;
    switch (a) {
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x78:
        switch (lbl_803EB548) {
        case 0:
        case 3:
            fn_801814E0(fn_800053D0());
            break;
        case 5:
            fn_801814E0(fn_800088C8());
            break;
        default:
            fn_801814E0(fn_801841AC());
            break;
        }
        break;
    case 0x384:
        fn_801814E0(fn_8000EB3C());
        break;
    }
    *pValue = 0;
    fn_801815D8(1, pCount, pValue);
    fn_80182E88(4, fn_80084158(fn_80182DBC()));
    if (fn_80084438(fn_80182DBC())) {
        fn_80182E9C(-1);
    } else {
        fn_80182E9C(0);
    }
    fn_80182EC4(0);
    lbl_80362A84.mUnknown96 = -1;
    lbl_803ECB6C[0] = fn_800841AC(fn_80182DBC());
    lbl_803ECB6C[1] = fn_800841D8(fn_80182DBC());
    lbl_803ECB6C[2] = fn_80084204(fn_80182DBC());
    fn_80188CBC(0, 4, fn_80084158(fn_80182DBC()), 172, lbl_803ECB6C);
    lbl_803EB580 = fn_80084158(fn_80182DBC());
    lbl_803EB584 = 0;
    fn_80083F88(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
    if (!fn_8018397C()) {
        if (fn_80183950()) {
            fn_8000890C(fn_8018E3DC(lbl_803EB55C));
        } else {
            fn_8000890C(fn_80078B94());
        }
    }
}

void fn_80181828(int a)
{
    if (lbl_803EB58C) {
        fn_80183368(lbl_803EB548, lbl_803ECB68);
        lbl_803EB58C = 1;
    }
    if (!fn_801835A0()) {
        switch (a) {
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x78:
        case 0x195:
            fn_80183368(1, 0x3FF);
            lbl_803EB58C = 1;
            break;
        case 0x384:
            fn_80183368(2, 0x3FF);
            lbl_803EB58C = 1;
            break;
        }
    }
    switch (a) {
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x78:
    case 0x195:
        if (fn_8018397C()) {
            fn_801835C0(0x71);
        } else {
            fn_801835C0(0x70);
        }
        break;
    case 0x384:
        fn_801835C0(0x384);
        lbl_803EB58C = 1;
        break;
    }
    fn_80181330();
    fn_80022D0C(0);
    fn_801831A4();
    fn_8018300C();
    fn_80182E64(0xFF);
    fn_80182E70(-1);
    fn_80182E7C(-1);
    fn_801831E8(0);
}

void fn_8018196C(void)
{
    Desc_8008044C desc;
    int status;

    fn_8008056C(&lbl_80362A58);
    if (fn_80183950()) {
        fn_8018C48C(0x54415453);
        if (fn_8018BD9C(lbl_803EB55C)) {
            lbl_803ECB68 = fn_8018BDFC(lbl_803EB55C, 0, 0, &status);
        }
    } else if (fn_8018397C()) {
        fn_80082558(lbl_803ECB68, lbl_803EB55C);
    } else {
        fn_8018C48C(0x54415453);
        if (fn_8018D720(lbl_803EB55C)) {
            lbl_803ECB68 = fn_8018D890(lbl_803EB55C, 0);
        }
    }
    fn_80084034(&lbl_80362A2C, lbl_803ECB68, 0);
    desc.mUnknown8 = lbl_803ECB68;
    desc.mUnknown4 = 1;
    desc.mUnknown0 = 1;
    fn_8008044C(&lbl_80362A58, &desc, 0x54415453);
}

void fn_80181A88(void)
{
    int busy = gFMCAPPORT.IsBusy();

    if (!busy) {
        fn_80027E98(0);
        fn_801834DC();
        lbl_803EB58C = busy;
        lbl_803EB58D = busy;
    }
}

void fn_80181AD4(unsigned char a)
{
    void *pResult = 0;
    int done = 0;

    fn_80181554()->vfn_02(lbl_803EB554, 1, &pResult);
    lbl_80362B14[lbl_803EB550].mpScreen = 0;
    lbl_803EB588 = done;
    if (!a) {
        switch (lbl_803EB548) {
        case 0:
        case 3:
            if (!fn_801801B4()) {
                done = 1;
            }
            break;
        case 2:
            break;
        case 5:
            fn_80082558(lbl_803ECB68, lbl_803EB55C);
            break;
        default:
            fn_8018196C();
            break;
        }
        gFMCAPPORT.ClearEntries();
    }
    fn_801813F4();
    fn_801835C0(-1);
    if (fn_80183950() || lbl_803EB58C) {
        fn_80027E98(fn_80181A88);
        lbl_803EB58D = 1;
    }
    if (done) {
        fn_80029CE0(2, fn_8022F384(fn_8022F4BC()));
    }
}

void fn_80181C10(int a, int *pCount, int *pValue)
{
    void *pResult = 0;
    int back = a == 0;
    int result = fn_80181554()->vfn_02(lbl_803EB554, back, &pResult);

    if (result == -1) {
        if (!back) {
            lbl_803EB588 = 1;
        }
        fn_8018152C();
    } else if (result == 1) {
        fn_801814E0((Class_80184190 *)pResult);
    } else if (result == -2) {
        if (!back) {
            lbl_803EB588 = 1;
        }
        fn_8018152C();
        fn_8018152C();
    } else {
        result = 1;
        fn_8018150C((Class_80184190 *)pResult);
    }
    *pValue = fn_80181570();
    fn_801831F8(-1);
    fn_801815D8(result, pCount, pValue);
}

void fn_80181CF8(int a, int *pId)
{
    fn_80181554()->vfn_04(a, pId);
}

void fn_80181D48(Entry_80182CC8 *pEntry, int id)
{
    pEntry->mId = id;
    pEntry->mUnknown36 = id;
    pEntry->mUnknown4 = 0;
    pEntry->mUnknown40 = 0;
    pEntry->mUnknown30 = 1;
    pEntry->mUnknown32 = 0xC0000;
    pEntry->mUnknown41 = 0;
    fn_801C3284(pEntry->mName, "NO TEXT!", 22);
}

void fn_80181DA8(int a, int *pResult, Arg_8018399C text0, Arg_8018399C text1, Arg_8018399C text2)
{
    Params_80005284 *p0 = text0.pParams;
    Params_80005284 *p1 = text1.pParams;
    Params_80005284 *p2 = text2.pParams;
    Entry_80182CC8 entry;

    lbl_803EB554 = a;
    fn_80181D48(&entry, a);
    fn_80181554()->vfn_03(a);
    fn_80181554()->vfn_05(a, &entry);
    if (entry.mUnknown36 < 0 || entry.mUnknown36 >= lbl_803EB558) {
        entry.mUnknown36 = 0;
    }
    fn_80181588(entry.mUnknown36);
    fn_801C3284(p0->mpText, lbl_80362A84.mName0, p0->mLength + 1);
    fn_801C3284(p1->mpText, lbl_80362A84.mName1, p1->mLength + 1);
    fn_801C3284(p2->mpText, lbl_80362A84.mName2, p2->mLength + 1);
    *pResult = lbl_803EB550;
}

}


extern "C" {

void fn_80181EAC(int a, int *pA, int *pB, int *pC)
{
    State_80362A84 *pState = &lbl_80362A84;
    unsigned char colors[3];

    *pA = (pState->mUnknown80 << 16) | pState->mUnknown84;
    *pB = pState->mUnknown88;
    *pC = pState->mUnknown92;
    fn_801826FC(colors);
    lbl_803ECB6C[0] = fn_800841AC(fn_80182DBC());
    lbl_803ECB6C[1] = fn_800841D8(fn_80182DBC());
    lbl_803ECB6C[2] = fn_80084204(fn_80182DBC());
    fn_801826FC(colors);
    fn_80188CBC(0, pState->mUnknown80, pState->mUnknown84, 172, colors);
    lbl_803EB580 = *pA;
    lbl_803EB584 = *pB;
}

void fn_80181F60(int a, int *pValues, int *pResult, Arg_8018399C text0, Arg_8018399C text1,
                 Arg_8018399C text2)
{
    Params_80005284 *p0 = text0.pParams;
    Params_80005284 *p1 = text1.pParams;
    Params_80005284 *p2 = text2.pParams;
    int i;

    if (lbl_803EB554 == a) {
        for (i = 0; i < 10; i++) {
            pValues[fn_801815A0(i)] = lbl_80362A84.mValues[i];
        }
        if ((unsigned int)lbl_80362A84.mUnknown64 < 14) {
            fn_8017F670(lbl_80362A84.mUnknown64, p0->mpText);
            fn_801C2D88(p1->mpText, p1->mLength + 1, "%d ft %d in", lbl_80362A84.mUnknown68 / 12,
                        lbl_80362A84.mUnknown68 % 12);
            fn_801C2D88(p2->mpText, p2->mLength + 1, "%d lbs", lbl_80362A84.mUnknown72);
        } else {
            fn_801C3284(p0->mpText, "", p0->mLength + 1);
            fn_801C3284(p1->mpText, "", p1->mLength + 1);
            fn_801C3284(p2->mpText, "", p2->mLength + 1);
        }
        *pResult = 1;
    }
}

void fn_801820A0(int a, int *p1, int *p2, int *p3, Arg_8018399C text, int *p5, int *p6, int *p7,
                 int *p8)
{
    Params_80005284 *p4 = text.pParams;
    Entry_80182CC8 entry;

    fn_80181D48(&entry, a);
    fn_80181554()->vfn_05(a, &entry);
    *p1 = entry.mUnknown30;
    *p2 = entry.mUnknown4;
    *p7 = entry.mUnknown40;
    *p8 = entry.mUnknown41;
    if (lbl_803EB550 == 0) {
        *p3 = 1;
    } else {
        *p3 = 0;
    }
    *p5 = 0;
    *p6 = 0;
    fn_801C3284(p4->mpText, entry.mName, p4->mLength + 1);
}

void fn_80182170(int a, int *pB, int *pC)
{
    int value = 0;

    lbl_803ECB64->vfn_01(a, &value);
    fn_8017FB64(value, pB, pC);
}

void fn_801821D8(int a, int b, int c)
{
    int value = fn_8017FB54(b, c);

    lbl_803ECB64->vfn_02(a, 0, value);
    lbl_803EB588 = 1;
}

void fn_8018223C(int a)
{
    lbl_803ECB64->vfn_02(a, 1, -1);
}

void fn_80182280(int a)
{
    lbl_803ECB64->vfn_04(a, 0, lbl_803EB560);
    if (lbl_803EB564 != lbl_803EB560) {
        lbl_803EB588 = 1;
    }
}

void fn_801822DC(int a)
{
    lbl_803ECB64->vfn_04(a, 1, -1);
}

void fn_80182320(int a, int b, Arg_8018399C text)
{

    switch (b) {
    case 3:
        if (--lbl_803EB560 < 0) {
            lbl_803EB560 = lbl_803EB568 - 1;
        }
        break;
    case 1:
        if (++lbl_803EB560 >= lbl_803EB568) {
            lbl_803EB560 = 0;
        }
        break;
    case -1:
        lbl_803EB560 = 0;
        lbl_803EB568 = 0;
        lbl_803ECB64->vfn_03(a, &lbl_803EB560, &lbl_803EB568);
        lbl_803EB564 = lbl_803EB560;
        break;
    }
    lbl_803ECB64->vfn_05(a, lbl_803EB560, text);
}

void fn_8018241C(int a, int b, int c, int *pOut, Arg_8018399C text0, Arg_8018399C text1,
                 Arg_8018399C text2)
{
    int x;
    int y;

    lbl_803ECB64->vfn_06(a, b, c, &x, &y, text0, text1, text2);
    *pOut = y;
    lbl_803EB574 = y;
    lbl_803EB570 = y;
    lbl_803EB578 = x;
}

int fn_801824BC(int a, int b, Arg_8018399C text)
{
    int result = lbl_803ECB64->vfn_07(a, b, text);

    if (result) {
        lbl_803EB570 = b;
    }
    return result;
}

void fn_80182520(int a)
{
    lbl_803ECB64->vfn_08(a, 0, lbl_803EB570);
    if (lbl_803EB574 != lbl_803EB570) {
        lbl_803EB588 = 1;
    }
}

void fn_8018257C(int a)
{
    lbl_803ECB64->vfn_08(a, 1, -1);
}

void fn_801825C0(int a, int *pResult, Arg_8018399C text)
{
    lbl_803ECB64->vfn_09(a, pResult, text);
}

void fn_8018260C(int a, Arg_8018399C text)
{
    lbl_803ECB64->vfn_10(a, text);
    lbl_803EB588 = 1;
}

void fn_8018265C(int a, int *pOut)
{
    unsigned char indices[3];
    PaletteColor color;

    fn_801826FC(indices);
    fn_8007A068(indices[0], &color);
    *pOut++ = color.r;
    *pOut++ = color.g;
    *pOut++ = color.b;
    fn_8007A068(indices[1], &color);
    *pOut++ = color.r;
    *pOut++ = color.g;
    *pOut++ = color.b;
    fn_8007A068(indices[2], &color);
    *pOut++ = color.r;
    *pOut++ = color.g;
    *pOut = color.b;
}

void fn_801826FC(unsigned char *pOut)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (lbl_803ECB70[i]) {
            pOut[i] = fn_8017FB88();
        } else {
            pOut[i] = lbl_803ECB6C[i];
        }
    }
}

void fn_8018275C(int *pCount, Arg_8018399C *pList)
{
    int i;

    *pCount = 0;
    for (i = 0; i < 10; i++) {
        fn_801C3284(pList[i].pParams->mpText, "", pList[i].pParams->mLength);
    }
    if (fn_800089D8() != 0x7FFF) {
        Info_80307908 info;
        Object_8007A334 query;
        char buffer[32];
        int type;
        int seen;

        fn_8007BA48(&query);
        seen = 0;
        fn_800809C4(fn_80182DC8(), fn_800089D8(), 0);
        fn_800817CC(fn_80182DC8(), &info);
        for (i = 0; i < 14; i++) {
            type = fn_8007BF14(i);
            fn_8007BB84(&query, type, info.mValues[i], 0);
            if (fn_8007C690(&query, 0)) {
                if ((type != 6 || !seen) && *pCount < 10) {
                    fn_8007BE20(&query, buffer, 32);
                    fn_801C3284(pList[*pCount].pParams->mpText, buffer, pList[*pCount].pParams->mLength);
                    (*pCount)++;
                }
                if (type == 6) {
                    seen = 1;
                }
            }
        }
        fn_8007BB04(&query);
    }
}

void fn_801828E0(int a, int *pFlag, Arg_8018399C text, int *pOut)
{
    Params_80005284 *pParams = text.pParams;

    *pFlag = lbl_803EB589;
    if (lbl_803EB589) {
        fn_801C3284(pParams->mpText, lbl_80362B54, pParams->mLength);
    } else {
        fn_801C3284(pParams->mpText, "", pParams->mLength);
    }
    *pOut = lbl_803EB58B;
}

unsigned char fn_80182954(int index)
{
    return lbl_80362B70[index];
}

void fn_80182964(void)
{
    if (fn_80183950()) {
        if (fn_80183948() == 3) {
            fn_8018EF6C(lbl_803ECB68);
            fn_8018E7A0(lbl_803EB55C, 0);
        }
        fn_8018E428(lbl_803EB55C, fn_80008914());
        fn_8018BF10(lbl_803EB55C, lbl_803ECB68);
    } else if (fn_8018397C()) {
        fn_80082534(lbl_803ECB68, lbl_803EB55C);
    } else if (fn_80183948() != 2) {
        fn_8018D8EC(lbl_803EB55C, lbl_803ECB68);
        if (fn_80078B94() != fn_80008914()) {
            fn_80078BB8(fn_80008914());
        }
    }
    if (fn_80183950() || fn_80183968()) {
        gFMCAPPORT.Start();
    }
}

void fn_80182A60(void)
{
    fn_80181458();
}

}

void Class_802A6BB0::vfn_01(int a, int *pResult)
{
}

void Class_802A6BB0::vfn_02(int a, int b, int c)
{
}

void Class_802A6BB0::vfn_03(int a, int *pB, int *pC)
{
}

void Class_802A6BB0::vfn_04(int a, int b, int c)
{
}

void Class_802A6BB0::vfn_05(int a, int b, Arg_8018399C text)
{
}

void Class_802A6BB0::vfn_06(int a, int b, int c, int *pD, int *pE, Arg_8018399C textF, Arg_8018399C textG,
                            Arg_8018399C textH)
{
}

int Class_802A6BB0::vfn_07(int a, int b, Arg_8018399C text)
{
    return 0;
}

void Class_802A6BB0::vfn_08(int a, int b, int c)
{
}

void Class_802A6BB0::vfn_09(int a, int *pResult, Arg_8018399C text)
{
}

void Class_802A6BB0::vfn_10(int a, Arg_8018399C text)
{
}

void Class_802A6B10::vfn_01(int a, int *pCount, int *pValue)
{
    Class_802A6B60::vfn_01(a, pCount, pValue);
    fn_801835C0(0x70);
}

int Class_802A6B10::vfn_02(int a, int b, void **ppResult)
{
    int result;

    Class_802A6B60::vfn_02(a, b, ppResult);
    result = -1;
    if (b == 0) {
        result = 1;
        switch (a) {
        case 0:
            *ppResult = fn_800053D0();
            break;
        case 1:
            *ppResult = fn_800088C8();
            break;
        }
    }
    return result;
}

void Class_802A6B60::vfn_01(int a, int *pCount, int *pValue)
{
    *pCount = vfn_07();
}

int Class_802A6B60::vfn_02(int a, int b, void **ppResult)
{
    fn_80182E04("");
    *ppResult = 0;
    return -1;
}

void Class_802A6B60::vfn_03(int id)
{
    Entry_80182CC8 *pEntries = vfn_08();
    int count = vfn_07();
    int i;

    for (i = 0; i < count; i++) {
        if (pEntries[i].mId == id) {
            break;
        }
    }
    if (i >= count) {
        i = 0;
    }
    fn_80182E04(pEntries[i].mName);
}

void Class_802A6B60::vfn_04(int index, int *pId)
{
    *pId = vfn_08()[index].mId;
}

void Class_802A6B60::vfn_05(int id, Entry_80182CC8 *pEntry)
{
    Entry_80182CC8 *pEntries = vfn_08();
    int count = vfn_07();
    int i;

    for (i = 0; i < count; i++) {
        if (pEntries[i].mId == id) {
            break;
        }
    }
    if (i >= count) {
        i = 0;
    }
    pEntry->mUnknown30 = pEntries[i].mUnknown30;
    pEntry->mUnknown4 = pEntries[i].mUnknown4;
    pEntry->mUnknown32 = pEntries[i].mUnknown32 | 0xC0000;
    pEntry->mId = pEntries[i].mId;
    pEntry->mUnknown36 = i;
    pEntry->mUnknown40 = 0;
    fn_801C3284(pEntry->mName, pEntries[i].mName, 22);
}

extern "C" {

Object_8007A334 *fn_80182DBC(void)
{
    return &lbl_80362A2C;
}

Object_8008044C *fn_80182DC8(void)
{
    return &lbl_80362A58;
}

void fn_80182DD4(const char *pText)
{
    fn_801C3284(lbl_80362A84.mName0, pText, 21);
}

void fn_80182E04(const char *pText)
{
    fn_801C3284(lbl_80362A84.mName1, pText, 21);
}

void fn_80182E34(char *pText)
{
    fn_801C3284(lbl_80362A84.mName2, pText, 21);
}

void fn_80182E64(int a)
{
    lbl_80362A84.mUnknown64 = a;
}

void fn_80182E70(int a)
{
    lbl_80362A84.mUnknown68 = a;
}

void fn_80182E7C(int a)
{
    lbl_80362A84.mUnknown72 = a;
}

void fn_80182E88(int a, int b)
{
    lbl_80362A84.mUnknown80 = a;
    lbl_80362A84.mUnknown84 = b;
}

void fn_80182E9C(int a)
{
    lbl_80362A84.mUnknown88 = fn_80188DF0(a);
}

void fn_80182EC4(unsigned char a)
{
    lbl_80362A84.mUnknown92 = a;
}

void fn_80182ED0(void)
{
    fn_80081788(fn_80182DC8(), lbl_80362A84.mValues);
}

void fn_80182EFC(void)
{
    int i;

    for (i = 9; i >= 0; i--) {
        lbl_80362A84.mValues[i] = 0;
    }
}

void fn_80182F24(int a)
{
    fn_800816C4(fn_80182DC8(), a, lbl_80362A84.mValues);
}

void fn_80182F60(int index, int delta)
{
    short values[10];
    int value;

    fn_8008174C(fn_80182DC8(), values);
    value = values[index] + delta;
    lbl_80362A84.mValues[index] = value > 0 ? (value > 99 ? 99 : value) : 1;
}

void fn_80182FD4(int a, unsigned char value)
{
    lbl_80362B70[fn_801815A0(a)] = value;
}

void fn_8018300C(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        lbl_80362B70[i] = 0;
    }
}

void fn_80183034(const char *pText)
{
    static Params_80005284 sText;

    if (pText) {
        if (fn_801C302C(pText, lbl_802EAA24, 28)) {
            Arg_8018399C args[2];

            fn_801C2EF0(lbl_802EAA24, pText, 28);
            args[0].i = 1;
            sText.mUnknown0 = 0;
            sText.mLength = 27;
            sText.mpText = lbl_802EAA24;
            args[1].pParams = &sText;
            fn_8021D7B8(lbl_803EB688, 0x80000088, 2, args);
        }
    } else {
        Arg_8018399C args[2];

        fn_801C2EF0(lbl_802EAA24, "", 28);
        args[0].i = 0;
        sText.mUnknown0 = 0;
        sText.mLength = 27;
        sText.mpText = lbl_802EAA24;
        args[1].pParams = &sText;
        fn_8021D7B8(lbl_803EB688, 0x80000088, 2, args);
    }
}

void fn_80183130(int a)
{
    int row;

    lbl_803EB589 = 1;
    row = fn_8007A43C((Object_8007A334 *)fn_80182DC8());
    fn_800809C4(fn_80182DC8(), a, 0);
    fn_80080B08(fn_80182DC8(), lbl_80362B54, 28);
    fn_8007A600((Object_8007A334 *)fn_80182DC8(), row);
    fn_80183034(lbl_80362B54);
}

void fn_801831A4(void)
{
    lbl_803EB589 = 0;
    fn_801C3284(lbl_80362B54, "", 28);
    fn_80183034(0);
}

void fn_801831E8(unsigned char a)
{
    lbl_803EB58B = a;
}

void fn_801831F0(unsigned char a)
{
    lbl_803EB58A = a;
}

void fn_801831F8(int a)
{
    lbl_80362A84.mUnknown96 = fn_80188DF0(a);
}

int fn_80183220(void)
{
    return lbl_803EB570;
}

int fn_80183228(void)
{
    return lbl_803EB574;
}

int fn_80183230(void)
{
    return lbl_803EB578;
}

int fn_80183238(int index)
{
    return lbl_802EA9FC[index];
}

void fn_8018324C(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        lbl_803ECB70[i] = 0;
    }
}

void fn_8018326C(int index)
{
    fn_8018324C();
    lbl_803ECB70[index] = 1;
}

void fn_801832A4(void)
{
    lbl_803EB588 = 1;
}

void fn_801832B0(char *pText, int size)
{
    void *pFont = fn_8021EA44(1);
    unsigned int limit;
    unsigned int width;

    fn_80080BEC(fn_80182DC8(), pText, size);
    limit = fn_80225F88(pFont, 2, 3, "WWWWWWWWWW");
    width = fn_80225F88(pFont, 2, 3, pText);
    if (fn_801C3180(pText) > 20 || width > limit) {
        fn_80080B08(fn_80182DC8(), pText, size);
    }
}

int fn_80183354(void)
{
    return lbl_803EB55C;
}

int fn_80183360(void)
{
    return lbl_803ECB68;
}

void fn_80183368(int mode, int value)
{
    Desc_8008044C desc;
    int status;

    lbl_803EB548 = mode;
    lbl_803EB55C = fn_8022F384(fn_8022F4BC());
    lbl_803EB54C = 1;
    lbl_803EB58C = 0;
    lbl_803EB588 = 0;
    switch (lbl_803EB548) {
    case 4:
        lbl_803ECB68 = fn_8018BDFC(lbl_803EB55C, 0, 0, &status);
        break;
    case 3:
        lbl_803ECB68 = fn_8018E4B4();
        fn_801832A4();
        break;
    case 5:
        fn_80082558(value, lbl_803EB55C);
        lbl_803ECB68 = value;
        break;
    case 0:
        lbl_803ECB68 = fn_8018D23C(lbl_803EB55C);
        fn_801832A4();
        break;
    case 2:
        lbl_803ECB68 = fn_8008775C();
        break;
    default:
        if (fn_8018D720(lbl_803EB55C)) {
            lbl_803ECB68 = fn_8018D890(lbl_803EB55C, 0);
        }
        break;
    }
    fn_80083E40(&lbl_80362A2C, 0, 0x54415453);
    fn_80084034(&lbl_80362A2C, lbl_803ECB68, 0);
    desc.mUnknown8 = lbl_803ECB68;
    desc.mUnknown4 = 1;
    desc.mUnknown0 = 1;
    fn_8008044C(&lbl_80362A58, &desc, 0x54415453);
    fn_8021EA44(1);
    fn_80008924();
}

void fn_801834DC(void)
{
    if (lbl_803EB54C) {
        fn_80083F68(&lbl_80362A2C);
        fn_8008056C(&lbl_80362A58);
        if (fn_80183950()) {
            fn_8018C48C(0x54415453);
            if (fn_801801B4() == 1 && fn_80183948() == 3) {
                fn_8005F29C();
            }
        } else if (!fn_8018397C()) {
            if (lbl_803EB548 == 2) {
                fn_80087880(lbl_803ECB68);
            } else {
                fn_8018C48C(0x54415453);
            }
        }
        fn_80077F24();
        lbl_803EB548 = 6;
        lbl_803EB54C = 0;
    }
    lbl_803EB58D = 0;
}

int fn_801835A0(void)
{
    int result = 0;

    if (lbl_803EB54C) {
        result = lbl_803EB58D == 0;
    }
    return result;
}

void fn_801835C0(int a)
{
    lbl_803EB56C = a;
}

void fn_801835C8(void)
{
    fn_80022398();
    fn_80022D3C(1, 0, 1);
    fn_80022D0C(0);
    fn_80022D0C(1);
    fn_80022580(0, 0xD6, 0);
    fn_80022580(1, 0xD6, 0);
    fn_800225F4(0, 2);
    fn_800225F4(1, 2);
    fn_800223E4(0, fn_80183734()->mUnknown0, fn_80183734()->mUnknown4, fn_80183734()->mUnknown8);
    fn_800223E4(1, fn_80183734()->mUnknown0, fn_80183734()->mUnknown4, fn_80183734()->mUnknown8);
    fn_80022534(0, fn_80183734()->mUnknown16);
    fn_80022534(1, fn_80183734()->mUnknown16);
    fn_80022730(0, fn_80183734()->mUnknown20);
    fn_80022730(1, fn_80183734()->mUnknown20);
    fn_800224A4(0, 0.0f);
    fn_800224A4(1, 0.0f);
}

void fn_80183704(void)
{
    fn_80022D3C(0, 0, 1);
    fn_800223C0();
}

Layout_802EA9E0 *fn_80183734(void)
{
    return &lbl_802EA9E0;
}

void fn_80183740(Layout_802EA9E0 *pOffset)
{
    if (!pOffset) {
        fn_80022870(0, fn_80183734()->mUnknown0, fn_80183734()->mUnknown4, fn_80183734()->mUnknown8,
                    fn_80183734()->mUnknown12, fn_80183734()->mUnknown16, fn_80183734()->mUnknown24);
        fn_80022870(1, fn_80183734()->mUnknown0, fn_80183734()->mUnknown4, fn_80183734()->mUnknown8,
                    fn_80183734()->mUnknown12, fn_80183734()->mUnknown16, fn_80183734()->mUnknown24);
        fn_800225F4(0, 2);
        fn_800225F4(1, 2);
    } else {
        fn_80022870(0, fn_80183734()->mUnknown0 + pOffset->mUnknown0,
                    fn_80183734()->mUnknown4 + pOffset->mUnknown4,
                    fn_80183734()->mUnknown8 + pOffset->mUnknown8,
                    fn_80183734()->mUnknown12 + pOffset->mUnknown12,
                    fn_80183734()->mUnknown16 + pOffset->mUnknown16, pOffset->mUnknown24);
        fn_80022870(1, fn_80183734()->mUnknown0 + pOffset->mUnknown0,
                    fn_80183734()->mUnknown4 + pOffset->mUnknown4,
                    fn_80183734()->mUnknown8 + pOffset->mUnknown8,
                    fn_80183734()->mUnknown12 + pOffset->mUnknown12,
                    fn_80183734()->mUnknown16 + pOffset->mUnknown16, pOffset->mUnknown24);
    }
}

void fn_80183920(int mode, int value)
{
    lbl_803EB548 = mode;
    lbl_803ECB68 = value;
    lbl_803EB58C = 1;
}

void fn_80183934(void)
{
    lbl_803EB58C = 0;
    lbl_803EB548 = 6;
}

int fn_80183948(void)
{
    return lbl_803EB548;
}

int fn_80183950(void)
{
    return lbl_803EB548 == 3 || lbl_803EB548 == 4;
}

int fn_80183968(void)
{
    return lbl_803EB548 == 0 || lbl_803EB548 == 1;
}

int fn_8018397C(void)
{
    return lbl_803EB548 == 5;
}

void fn_80183990(void)
{
    lbl_803EB57C = 1;
}

}

extern "C" {

int fn_8018399C(unsigned int id, Arg_8018399C *pArgs, int unused, Arg_8018399C *pResult)
{
    switch (id) {
    case 0x1E:
        fn_80181670(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0xC6:
        fn_80181828(pArgs[0].i);
        break;
    case 0xC7:
        fn_80181AD4(pArgs[0].i);
        break;
    case 0x20:
        fn_80181C10(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x1F:
        fn_80181CF8(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x16:
        fn_80181DA8(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3], pArgs[4]);
        break;
    case 0x94:
        fn_80181EAC(pArgs[0].i, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x95:
        fn_80181F60(pArgs[0].i, &pArgs[1].pi[pArgs[1].pi[0] + 1], pArgs[2].pi, pArgs[3], pArgs[4], pArgs[5]);
        break;
    case 0x15:
        fn_801820A0(pArgs[0].i, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi, pArgs[4], pArgs[5].pi, pArgs[6].pi,
                    pArgs[7].pi, pArgs[8].pi);
        break;
    case 0x138:
        fn_8000EBA4(pArgs[0].i);
        break;
    case 0x17:
        fn_80182170(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x18:
        fn_801821D8(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0xCA:
        fn_8018223C(pArgs[0].i);
        break;
    case 0x19:
        fn_80182320(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x1A:
        fn_80182280(pArgs[0].i);
        break;
    case 0xC8:
        fn_801822DC(pArgs[0].i);
        break;
    case 0x1C:
        fn_8018241C(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].pi, pArgs[4], pArgs[5], pArgs[6]);
        break;
    case 0x1D:
        pResult->i = fn_801824BC(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x1B:
        fn_80182520(pArgs[0].i);
        break;
    case 0xC9:
        fn_8018257C(pArgs[0].i);
        break;
    case 0x9D:
        fn_801825C0(pArgs[0].i, pArgs[1].pi, pArgs[2]);
        break;
    case 0x9E:
        fn_8018260C(pArgs[0].i, pArgs[1]);
        break;
    case 0xCC:
        pResult->i = fn_800229D8();
        break;
    case 0x128:
        if (lbl_803EB56C == 0x384 || lbl_803EB56C == 0x71) {
            pResult->f = fn_80022BA0(pArgs[0].f);
        }
        break;
    case 0x10A:
        switch (lbl_803EB548) {
        case 2:
            pResult->i = fn_8000EB5C();
            *pArgs[0].pi = fn_8000EB80();
            break;
        case 5:
            pResult->i = -1;
            *pArgs[0].pi = 0;
            break;
        default:
            pResult->i = fn_80008914() - fn_8000891C();
            *pArgs[0].pi = fn_800089C0();
            break;
        }
        break;
    case 0x115: {
        int index = pArgs[1].pi[0] + 1;

        fn_8018265C(pArgs[0].i, &pArgs[1].pi[index]);
        break;
    }
    case 0x117: {
        int index = pArgs[1].pi[0] + 1;

        fn_8018275C(pArgs[0].pi, (Arg_8018399C *)&pArgs[1].pi[index]);
        break;
    }
    case 0x116:
        fn_801828E0(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3].pi);
        break;
    case 0x118:
        pResult->i = fn_80182954(pArgs[0].i);
        break;
    case 0x11A:
        fn_80182964();
        break;
    case 0x124:
        pResult->i = 0;
        if (lbl_803EB54C) {
            if (lbl_803EB56C == 0x384) {
                pResult->i = fn_8000EC14();
            } else {
                pResult->i = lbl_803EB588;
            }
        }
        break;
    case 0x18F:
        pResult->i = 0;
        if (lbl_803EB548 == 0 || lbl_803EB548 == 3) {
            fn_801C3284(pArgs[0].pParams->mpText, "Exit and lose changes?", pArgs[0].pParams->mLength);
        } else {
            fn_801C3284(pArgs[0].pParams->mpText, "", pArgs[0].pParams->mLength);
            pResult->i = 1;
        }
        break;
    case 0x126:
        if (pArgs[0].i == 7) {
            pResult->i = fn_8018BD9C(fn_8022F384(fn_8022F4BC()));
        } else if (pArgs[0].i == 6) {
            pResult->i = fn_8018D720(fn_8022F384(fn_8022F4BC()));
        } else if (pArgs[0].i == 8) {
            pResult->i = fn_8018F228(fn_8022F384(fn_8022F4BC())) != 0x3FF;
        }
        break;
    case 0x125:
        if (pArgs[0].i == 7) {
            fn_8018BF3C();
        } else if (pArgs[0].i == 6) {
            int team;

            fn_8018D918();
            team = fn_80186B38(fn_8022F4BC());
            if (fn_8018BD9C(team)) {
                fn_8018E8B0(team, 1, 0);
            }
        } else if (pArgs[0].i == 8) {
            fn_8018F41C(fn_8022F384(fn_8022F4BC()));
        }
        break;
    case 0xF0:
        pResult->i = lbl_803EB58A;
        break;
    case 0xF1:
        fn_80182A60();
        break;
    case 0x12F:
        fn_80022534(0, 0.0f);
        fn_80022534(1, 0.0f);
        break;
    case 0x92:
        pResult->i = lbl_803EB56C;
        break;
    case 0x197:
        fn_80029CE0(2, fn_8022F384(fn_8022F4BC()));
        break;
    case 0x19A:
        pResult->i = lbl_803EB57C;
        break;
    case 0x19B:
        fn_800089E0(pArgs[0].i);
        lbl_803EB57C = 0;
        break;
    case 0x19E:
        *pArgs[0].pi = -1;
        *pArgs[1].pi = -1;
        if (lbl_803EB548 == 2) {
            *pArgs[0].pi = fn_8000EC38();
        }
        break;
    case 0x19F:
        pResult->i = fn_80183950();
        break;
    case 0x127:
        break;
    default:
        return 0;
    }
    return 1;
}

}

Object_8007A334 lbl_80362A2C;
Object_8008044C lbl_80362A58;
Class_802A6BB0 lbl_803ECB60;

static inline Class_802A6B10 *fn_801841AC()
{
    static Class_802A6B10 sInstance;
    return &sInstance;
}
