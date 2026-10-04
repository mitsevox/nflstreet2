#include "game/fn_8007F828.h"
#include "game/fn_8017F584.h"
#include "game/fn_801C3660.h"
#include "game/fn_801D2B7C.h"
#include "game/Object_80228224.h"

extern "C" {
#include "engine/cu_80227F14.h"
}

/* One of the eight 56-byte records at 0x80362FC0. */
struct Record_80362FC0 {
    float mUnknown0[10];
    unsigned char mUnknown40[10];
    unsigned short mUnknown50;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
};

/* Argument of fn_80188688. */
struct Desc_80188688 {
    int mUnknown0;
    int mUnknown4;
    char *mUnknown8;
    char **mUnknown12;
};

extern "C" {
extern char lbl_80306B34[];
extern char lbl_802EBE5C[];
extern char lbl_802EBE78[];
extern char lbl_802EBE98[];
extern float lbl_803EA2C4;

double fabs(double);

void fn_80024654(void);
int fn_80027DF0(void);
int fn_8002894C(void);
int fn_80033144(void *p);
void fn_8000FCD4(int a);
void fn_80047670(int handle);
void fn_80047698(void);
void fn_800545C0(void);
void fn_800545E8(void);
void fn_80064690(void);
void fn_8006CA84(int a);
void fn_8013CF98(void);
float fn_8013D050(void);
void fn_8017CED4(unsigned int a);
void fn_8017CFAC(void);
void fn_8017F264(void);
void fn_8017F284(void);
void *fn_80188688(Desc_80188688 *pDesc);
void fn_80188728(void *p);
void fn_80188784(void *p, int a);
void fn_801888A4(void *p, int a);
void fn_8018897C(void *p, int a, int b, int c);
void fn_801889A4(void *p, int a, int b);
int fn_801889CC(void *p, int a, int b);
void fn_80188D2C(void);
int fn_801890F0(int a, int b);
void fn_80189164(int a, int b);
void fn_801891A8(void);
void fn_801897BC(void);
void fn_80189844(void);
void fn_8018A69C(int a);
void fn_8018A85C(void *p);
void fn_8018A8B0(unsigned char value);
unsigned char fn_8018A8B8(void);
void fn_8018A8C8(int a);
void fn_8018A910(void);
void fn_8018AB0C(void);
void fn_8018AB3C(void);
void fn_8018AB64(void);
void fn_8018ACBC(void);
void fn_8018AD78(void);
void fn_8018AFD0(int a);
unsigned char fn_8018AFD8(unsigned char value);
unsigned char fn_8018AFE8(void);
void fn_80191378(Object_80228224 *pObject);
void fn_80196174(Object_80228224 *pObject, int a);
void fn_80196204(void);
void fn_801A139C(void);
void fn_801A6730(void);
void *fn_801C3610(int a, int b);
void fn_801C3640(void *p);
void fn_801C3A10(void *p, float a);
void fn_801C3EA4(void *p, float a, float b, float c);
void fn_801C3ED0(void *p, int a, int b, int c);
void fn_801CD2A4(void);
void fn_801CE82C(void);
void fn_801CE910(void);
void fn_801CE9E0(int a);
int fn_801CEA08(void);
int fn_801CEA14(void);
int fn_801CEB4C(void);
int fn_801CEC74(void);
int fn_801CEC7C(void);
int fn_801CECCC(int index);
void fn_801CECDC(int a);
float fn_801CFD28(int a);
void fn_801D339C(int a);
void fn_801D342C(int a);
int fn_801DCF0C(int a, int b, int c, void (*pA)(), void (*pB)());
void fn_801DCF8C(int a);
int fn_801DCFF0(int a, int b, int c, int d, int e, int f, int g, int h);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(int, int));
void fn_801DD0E8(int handle);
int fn_801DD268(int handle, int a, int b, int c);
void fn_801DD320(int handle, int a);
int fn_802188A0(int a, int b, int c, int d, int e, int f);
void fn_802188D4(void *p, int a, int b, int c, int d, int e, int f, unsigned int g);
void fn_80218A34(void *p);
void fn_80218AA8(void *p, void (*pCallback)());
void fn_80218AB0(void *p, int (*pA)(int, int), void (*pB)(int, int));
void fn_80218ABC(void *p, void (*pCallback)());
void fn_80218AC4(void *p, void (*pCallback)());
void fn_80218ACC(void *p, void (*pCallback)());
void fn_80218AD4(void *p, int index, void (*pCallback)());
void fn_80218CB8(void *p, int a);
void fn_8021992C(void *p, int a);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_802196B4(void *p, int a, int b, int c, float *pD, unsigned char e);
void fn_80219A54(void *p, int a);
int fn_80219AF8(void *p, int a, int b, int c);
int fn_8021A020(void *p);
int fn_8021D828(void *p, int a, int b);
void fn_8021D880(void (*pCallback)());
void fn_8021DF9C(void *p);
void *fn_8021EA44(int index);
void fn_8021ED88(void *p);
void fn_8021EF6C(void (*pCallback)());
void fn_8021EFD8(void);
void fn_80220CDC(int a);
void fn_80220CFC(int a);
void fn_80220D04(void);
void fn_802212C8(void);
void fn_80222220(void);
void fn_80223460(void);
void fn_80225654(void);
void fn_802363B0(Object_80228224 *pObject);
void fn_802363E0(Object_80228224 *pObject);
int fn_80236EC0(int a);
}

static void *lbl_803EB640 = 0;
static Object_80228224 *lbl_803EB644 = 0;
static void *lbl_803EB648 = 0;
static int lbl_803EB64C = 0;
static int lbl_803EB650 = 0;
static Object_80228224 *lbl_803EB654 = 0;
static void *lbl_803EB658 = 0;
static int lbl_803EB65C = 0;
static int lbl_803EB660 = 0;
static Object_80228224 *lbl_803EB664 = 0;
static void *lbl_803EB668 = 0;
static int lbl_803EB66C = 0;
static int lbl_803EB670 = 0;
static unsigned char lbl_803EB674 = 0;
static unsigned char lbl_803EB675 = 0;
int lbl_803EB678 = 0;
static int lbl_803EB67C = -1;
static int lbl_803EB680 = 7;
unsigned char lbl_803EB684 = 1;
extern "C" {
void *lbl_803EB688 = 0;
void *lbl_803EB68C = 0;
void *lbl_803EB690 = 0;
}
int lbl_803EB694 = 0;
static char *lbl_803EB698 = lbl_802EBE5C;
char *lbl_803EB69C = lbl_802EBE98;
static int lbl_803EB6A0 = -1;

static char *lbl_80362F84[15];
static Record_80362FC0 lbl_80362FC0[8];

extern "C" {

void fn_80188E98(void) {}

void fn_80188E9C(void) {}

void fn_80188EA0(void) {}

void fn_80188EA4(void) {}

void fn_80188EA8(void) {}

void fn_80188EAC(void)
{
    fn_8021DF9C(fn_8021EA44(1));
}

void fn_80188ED4(void *p)
{
    fn_80218AB0(p, fn_801890F0, fn_80189164);
    fn_80218AC4(p, fn_802212C8);
    fn_80218AA8(p, fn_80064690);
    fn_80218ABC(p, fn_801891A8);
    fn_80218ACC(p, fn_801897BC);
    fn_80218AD4(p, 0, fn_8021EFD8);
    fn_80218AD4(p, 1, fn_8018ACBC);
    fn_80218AD4(p, 2, fn_80223460);
    fn_80218AD4(p, 3, fn_8018A910);
    fn_80218AD4(p, 4, fn_80225654);
    fn_80218AD4(p, 5, fn_8018AD78);
    fn_80218AD4(p, 6, fn_8018AB64);
    fn_80218AD4(p, 7, fn_80189844);
    fn_80218AD4(p, 8, fn_80222220);
}

int fn_80189004(int a, int b)
{
    int saved;

    fn_8018A8C8(0);
    fn_80188D2C();
    fn_801CE9E0(0);
    fn_801CD2A4();
    if (fn_80027DF0()) {
        fn_8021ED88(fn_8021EA44(1));
    }
    saved = fn_80236EC0(0);
    if (a == lbl_803EB650) {
        if (lbl_803EB688 && (lbl_803EB680 & 1)) {
            fn_8021992C(lbl_803EB688, b);
            fn_801A139C();
        }
        if (lbl_803EB690 && (lbl_803EB680 & 2)) {
            fn_8021992C(lbl_803EB690, b);
        }
        if (lbl_803EB68C && (lbl_803EB680 & 4)) {
            fn_8021992C(lbl_803EB68C, b);
        }
    }
    fn_80236EC0(saved);
    fn_801CE9E0(1);
    return 0;
}

int fn_801890F0(int a, int b)
{
    int result;

    fn_801D339C(-1);
    fn_80188784(lbl_803EB640, a);
    fn_8018897C(lbl_803EB640, a, b, 0);
    result = fn_801889CC(lbl_803EB640, a, b);
    fn_801D342C(-1);
    return result;
}

void fn_80189164(int a, int b)
{
    fn_801889A4(lbl_803EB640, a, b);
    fn_801888A4(lbl_803EB640, a);
}

void fn_801891A8(void)
{
    fn_801CE910();
}

int fn_801891C8(int a)
{
    int result = 1;

    if (lbl_803EB67C != -1) {
        result = lbl_803EB67C == a;
    }
    return result;
}

int fn_801891EC(unsigned int id)
{
    switch (id) {
    case 2:
        return 0;
    case 3:
        return 1;
    case 4:
        return 2;
    case 5:
        return 3;
    case 10:
        return 4;
    case 11:
        return 5;
    case 12:
        return 6;
    case 13:
        return 7;
    }
    return 8;
}

void fn_80189290(unsigned int index, int record)
{
    lbl_80362FC0[record].mUnknown0[index] = 0.0f;
    lbl_80362FC0[record].mUnknown40[index] = lbl_80362FC0[record].mUnknown54;
    if (index < 16) {
        lbl_80362FC0[record].mUnknown50 &= ~(1 << index);
    } else {
        lbl_80362FC0[record].mUnknown50 = 0;
    }
}

void fn_801892F0(void)
{
    unsigned int record;
    unsigned int index;

    for (record = 0; record < 8; record++) {
        for (index = 0; index < 10; index++) {
            fn_80189290(index, record);
        }
    }
}

void fn_80189344(int *pA, unsigned int *pId, float *pValue)
{
    unsigned int id = *pId;
    int a = *pA;
    float value = *pValue;
    float magnitude;

    switch (id) {
    case 0x29:
    case 0x33:
        id = 2;
        break;
    case 0x2A:
    case 0x34:
        id = 3;
        break;
    case 0x28:
    case 0x35:
        id = 4;
        break;
    case 0x27:
    case 0x36:
        id = 5;
        break;
    case 0x2F:
    case 0x3B:
        id = 10;
        break;
    case 0x30:
    case 0x3C:
        id = 11;
        break;
    case 0x31:
    case 0x3D:
        id = 12;
        break;
    case 0x32:
    case 0x3E:
        id = 13;
        break;
    case 0x8B:
        fn_80189290(a, 3);
        fn_80189290(a, 2);
        break;
    case 0x8C:
        fn_80189290(a, 0);
        fn_80189290(a, 1);
        break;
    case 0x10:
        if (value > 0.0f) {
            id = 5;
        } else {
            id = 4;
        }
        if ((value > 0.0f && lbl_80362FC0[3].mUnknown0[a] == 0.0f)
            || (value < 0.0f && lbl_80362FC0[2].mUnknown0[a] == 0.0f)) {
            value = 1.0f;
        }
        magnitude = fabs(value);
        if (magnitude < 0.5f) {
            magnitude = 0.5f;
        } else if (magnitude > 1.0f) {
            magnitude = 1.0f;
        }
        value = magnitude;
        break;
    case 0x11:
        if (value > 0.0f) {
            id = 2;
        } else {
            id = 3;
        }
        if ((value > 0.0f && lbl_80362FC0[0].mUnknown0[a] == 0.0f)
            || (value < 0.0f && lbl_80362FC0[1].mUnknown0[a] == 0.0f)) {
            value = 1.0f;
        }
        magnitude = fabs(value);
        if (magnitude < 0.5f) {
            magnitude = 0.5f;
        } else if (magnitude > 1.0f) {
            magnitude = 1.0f;
        }
        value = magnitude;
        break;
    }
    *pA = a;
    *pId = id;
    *pValue = value;
}

int fn_801895EC(int *pA, unsigned int *pId, float *pValue)
{
    unsigned short unknown0;
    unsigned short unknown1;
    int a = *pA;
    unsigned int id = *pId;
    float value = *pValue;
    unsigned int record;
    int result = 0;

    fn_80189344(&a, &id, &value);
    record = fn_801891EC(id);
    if (record < 8) {
        Record_80362FC0 *pRecord = &lbl_80362FC0[record];

        if (value > 0.0f) {
            result = pRecord->mUnknown0[a] == 0.0f;
            pRecord->mUnknown0[a] += value * pRecord->mUnknown52;
            if (pRecord->mUnknown0[a] > pRecord->mUnknown40[a]) {
                pRecord->mUnknown0[a] -= pRecord->mUnknown40[a];
                if (pRecord->mUnknown40[a] > pRecord->mUnknown53) {
                    pRecord->mUnknown40[a] -= pRecord->mUnknown55;
                    if (pRecord->mUnknown40[a] < pRecord->mUnknown53) {
                        pRecord->mUnknown40[a] = pRecord->mUnknown53;
                    }
                }
                result = 1;
            }
        } else if (pRecord->mUnknown0[a] > 0.0f) {
            fn_80189290(a, record);
            result = 1;
        }
    } else {
        result = 1;
    }
    if (id - 12 <= 1 && result == 1) {
        result = 0;
        fn_80219650(lbl_803EB688, &unknown0, &unknown1);
        if (unknown0 == 3) {
            result = unknown1 == 2;
        }
    }
    *pA = a;
    *pId = id;
    *pValue = value;
    return result;
}

void fn_801897BC(void)
{
    fn_801892F0();
}

void fn_801897DC(Object_80228224 *pObject)
{
    float near = 0.1f;
    float far = 1500.0f;

    fn_802286D8(pObject, 45.0f, fn_8013D050(), near, far);
}

void fn_80189844(void) {}

void fn_80189848(void)
{
    Desc_80228224 desc;

    desc.mUnknown0 = 5;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown16 = fn_801CEA14();
    desc.mUnknown18 = fn_801CEA08();
    if (!fn_80027DF0() && (fn_8007F828(6) == 1 || fn_801CEB4C() == 1)) {
        desc.mUnknown16 = fn_801CEC74();
        desc.mUnknown18 = fn_801CEC7C();
    }
    lbl_803EB644 = fn_80228224(&desc);
    fn_801897DC(lbl_803EB644);
    lbl_803EB644->mUnknown28 &= ~1;
    fn_8022864C(lbl_803EB644, 0.0f, 0.0f, 0.0f);
    lbl_803EB648 = fn_801C3610(0, 0);
    fn_801C3ED0(lbl_803EB648, 0, 0x800000, 0x800000);
    fn_801C3EA4(lbl_803EB648, 427.0f, 240.0f, -(240.0f / fn_801CFD28(0x100000)));
    fn_801C3660(lbl_803EB644, lbl_803EB648);
    if (fn_80027DF0()) {
        fn_801C3A10(lbl_803EB648, 1.0f);
    } else {
        fn_801C3A10(lbl_803EB648, 4.0f);
    }
    fn_80228474(lbl_803EB644, 2, fn_80191378, 31);
    lbl_803EB64C = fn_801DCFF0(1, 336, 0, 0, 0, 1, 0, -1);
    fn_801DD0C8(lbl_803EB64C, 21, 0, fn_80189004);
    fn_802286CC(lbl_803EB644, lbl_803EB64C, 0);
    lbl_803EB650 = fn_801DD268(lbl_803EB64C, 21, 0, 0);
    if (!fn_80027DF0()) {
        fn_80196174(lbl_803EB644, 0);
    }
    lbl_803EB688 = fn_801D2B7C(fn_802188A0(12, 9, 160, 7, 640, 160), 0, 0);
    fn_802188D4(lbl_803EB688, 12, 9, 160, 7, 640, 160, (unsigned int)(lbl_803EA2C4 * 16.666668f));
    fn_80188ED4(lbl_803EB688);
    fn_8018A85C(lbl_803EB688);
}

void fn_80189ADC(void)
{
    Desc_80228224 desc;

    desc.mUnknown0 = 5;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown16 = fn_801CEA14();
    desc.mUnknown18 = fn_801CEA08();
    if (!fn_80027DF0() && (fn_8007F828(6) == 1 || fn_801CEB4C() == 1)) {
        desc.mUnknown16 = fn_801CEC74();
        desc.mUnknown18 = fn_801CEC7C();
    }
    lbl_803EB654 = fn_80228224(&desc);
    fn_801897DC(lbl_803EB654);
    lbl_803EB654->mUnknown28 &= ~1;
    fn_8022864C(lbl_803EB654, 0.0f, 0.0f, 0.0f);
    lbl_803EB658 = fn_801C3610(0, 0);
    fn_801C3ED0(lbl_803EB658, 0, 0x800000, 0x800000);
    fn_801C3EA4(lbl_803EB658, 320.0f, 240.0f, -(240.0f / fn_801CFD28(0x100000)));
    fn_801C3660(lbl_803EB654, lbl_803EB658);
    fn_801C3A10(lbl_803EB658, 4.0f);
    lbl_803EB65C = fn_801DCFF0(1, 336, 0, 0, 0, 1, 0, -1);
    fn_801DD0C8(lbl_803EB65C, 21, 0, fn_80189004);
    fn_802286CC(lbl_803EB654, lbl_803EB65C, 0);
    lbl_803EB660 = fn_801DD268(lbl_803EB65C, 21, 0, 0);
    lbl_803EB690 = fn_801D2B7C(fn_802188A0(6, 9, 64, 1, 128, 128), 0, 0);
    fn_802188D4(lbl_803EB690, 6, 9, 64, 1, 128, 128, (unsigned int)(lbl_803EA2C4 * 16.666668f));
    fn_80188ED4(lbl_803EB690);
    fn_8018A85C(lbl_803EB690);
}

void fn_80189D20(void)
{
    Desc_80228224 desc;

    desc.mUnknown0 = 5;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown16 = fn_801CEA14();
    desc.mUnknown18 = fn_801CEA08();
    if (!fn_80027DF0() && (fn_8007F828(6) == 1 || fn_801CEB4C() == 1)) {
        desc.mUnknown16 = fn_801CEC74();
        desc.mUnknown18 = fn_801CEC7C();
    }
    lbl_803EB664 = fn_80228224(&desc);
    fn_801897DC(lbl_803EB664);
    lbl_803EB664->mUnknown28 &= ~1;
    fn_8022864C(lbl_803EB664, 0.0f, 0.0f, 0.0f);
    lbl_803EB668 = fn_801C3610(0, 0);
    fn_801C3ED0(lbl_803EB668, 0, 0x800000, 0x800000);
    fn_801C3EA4(lbl_803EB668, 320.0f, 240.0f, -(240.0f / fn_801CFD28(0x100000)));
    fn_801C3660(lbl_803EB664, lbl_803EB668);
    fn_801C3A10(lbl_803EB668, 4.0f);
    lbl_803EB66C = fn_801DCFF0(1, 336, 0, 0, 0, 1, 0, -1);
    fn_801DD0C8(lbl_803EB66C, 21, 0, fn_80189004);
    fn_802286CC(lbl_803EB664, lbl_803EB66C, 0);
    lbl_803EB670 = fn_801DD268(lbl_803EB66C, 21, 0, 0);
    lbl_803EB68C = fn_801D2B7C(fn_802188A0(6, 9, 64, 1, 128, 128), 0, 0);
    fn_802188D4(lbl_803EB68C, 6, 9, 64, 1, 128, 128, (unsigned int)(lbl_803EA2C4 * 16.666668f));
    fn_80188ED4(lbl_803EB68C);
    fn_8018A85C(lbl_803EB68C);
}

void fn_80189F64(void) {}

void fn_80189F68(void)
{
    Desc_80188688 desc;
    int i;
    int flag = fn_80033144(lbl_80306B34);
    int result = 0;

    lbl_803EB680 = 0;
    fn_8021D880(fn_80188EA0);
    fn_801DCF0C(21, 20, 4, fn_80188EA4, fn_80188EA8);
    desc.mUnknown0 = 1;
    desc.mUnknown4 = 15;
    desc.mUnknown8 = lbl_803EB698;
    fn_801A6730();
    fn_8021EF6C(fn_80189F64);
    if (!flag) {
        fn_80188E98();
    }
    if (fn_8002894C()) {
        for (i = 0; i < 15; i++) {
            lbl_80362F84[i] = 0;
        }
        lbl_80362F84[1] = lbl_802EBE78;
        desc.mUnknown12 = lbl_80362F84;
    } else if (flag) {
        for (i = 0; i < 15; i++) {
            lbl_80362F84[i] = 0;
        }
        lbl_80362F84[1] = lbl_802EBE78;
        desc.mUnknown12 = lbl_80362F84;
    } else {
        desc.mUnknown12 = 0;
    }
    lbl_803EB640 = fn_80188688(&desc);
    if (!fn_80027DF0()) {
        fn_8013CF98();
    }
    fn_80189ADC();
    if (fn_80027DF0()) {
        fn_80189D20();
    }
    fn_80189848();
    fn_8018AB0C();
    if (fn_80027DF0() && !flag) {
        fn_801D339C(-1);
        fn_801D342C(-1);
    }
    result = fn_801890F0(14, 0);
    fn_80218CB8(lbl_803EB688, result);
    if (fn_80027DF0()) {
        if (!flag) {
            fn_8018A69C(0);
            fn_8018A69C(1);
            fn_8018A69C(5);
            fn_8018A69C(6);
            fn_8018A69C(7);
            fn_8018A69C(8);
            fn_8018A69C(11);
            fn_8018A69C(12);
            fn_8018A69C(13);
            fn_802363B0(lbl_803EB644);
        }
        fn_8018AFD8(1);
    } else if (fn_8002894C()) {
        fn_8017F584();
        fn_80047670(lbl_803EB64C);
        fn_8017CED4((unsigned int)(lbl_803EA2C4 * 16.666668f));
        fn_8018AFD8(0);
        fn_800545C0();
        fn_8017F264();
    }
    fn_80220D04();
    {
        unsigned char record;
        unsigned char index;

        for (record = 0; record < 8; record++) {
            for (index = 0; index < 10; index++) {
                lbl_80362FC0[record].mUnknown0[index] = 0.0f;
                lbl_80362FC0[record].mUnknown40[index] = 100;
            }
            lbl_80362FC0[record].mUnknown55 = 15;
            lbl_80362FC0[record].mUnknown54 = 100;
            lbl_80362FC0[record].mUnknown53 = 23;
            lbl_80362FC0[record].mUnknown52 = 5;
            lbl_80362FC0[record].mUnknown50 = 0;
        }
    }
}

void fn_8018A274(void)
{
    fn_80188E9C();
    fn_80218A34(lbl_803EB688);
    fn_801D2BD0(lbl_803EB688);
    lbl_803EB688 = 0;
    if (!fn_80027DF0()) {
        fn_80196204();
    }
    fn_802284EC(lbl_803EB644, fn_80191378);
    fn_801DD320(lbl_803EB64C, lbl_803EB650);
    fn_80228D58(lbl_803EB650);
    fn_80228E18();
    lbl_803EB650 = 0;
    fn_801DD0E8(lbl_803EB64C);
    lbl_803EB64C = 0;
    fn_801C3640(lbl_803EB648);
    lbl_803EB648 = 0;
    fn_802283FC(lbl_803EB644);
    lbl_803EB644 = 0;
}

void fn_8018A314(void)
{
    fn_80218A34(lbl_803EB690);
    fn_801D2BD0(lbl_803EB690);
    lbl_803EB690 = 0;
    fn_801DD320(lbl_803EB65C, lbl_803EB660);
    fn_80228D58(lbl_803EB660);
    fn_80228E18();
    lbl_803EB660 = 0;
    fn_801DD0E8(lbl_803EB65C);
    lbl_803EB65C = 0;
    fn_801C3640(lbl_803EB658);
    lbl_803EB658 = 0;
    fn_802283FC(lbl_803EB654);
    lbl_803EB654 = 0;
}

void fn_8018A390(void)
{
    fn_80218A34(lbl_803EB68C);
    fn_801D2BD0(lbl_803EB68C);
    lbl_803EB68C = 0;
    fn_801DD320(lbl_803EB66C, lbl_803EB670);
    fn_80228D58(lbl_803EB670);
    fn_80228E18();
    lbl_803EB670 = 0;
    fn_801DD0E8(lbl_803EB66C);
    lbl_803EB66C = 0;
    fn_801C3640(lbl_803EB668);
    lbl_803EB668 = 0;
    fn_802283FC(lbl_803EB664);
    lbl_803EB664 = 0;
}

void fn_8018A40C(void)
{
    int flag = fn_80033144(lbl_80306B34);

    if (fn_80027DF0()) {
        if (!flag) {
            fn_802363E0(lbl_803EB644);
        }
    } else if (fn_8002894C()) {
        fn_80047698();
        fn_8017CFAC();
        fn_800545E8();
        fn_8017F284();
    }
    if (fn_80027DF0()) {
        fn_8018A390();
    }
    fn_8018A314();
    fn_8018A274();
    fn_80188EAC();
    fn_8018AB3C();
    fn_80188728(lbl_803EB640);
    lbl_803EB640 = 0;
    fn_801DCF8C(21);
}

void fn_8018A4B4(int a)
{
    lbl_803EB6A0 = a;
}

void fn_8018A4BC(int a, unsigned int id, float value)
{
    unsigned short unknown0 = 0;
    unsigned short unknown1 = 0;

    if (fn_801891C8(a)) {
        lbl_803EB6A0 = a;
        switch (id) {
        case 8:
            id = 6;
            break;
        case 6:
            id = 8;
            break;
        case 0x39:
            id = 0x37;
            break;
        case 0x37:
            id = 0x39;
            break;
        }
        if (id == 8) {
            if (value == 1.0f && fn_8018AFE8()) {
                fn_80219650(lbl_803EB688, &unknown0, &unknown1);
                if (fn_8021D828(lbl_803EB688, unknown0, unknown1) && fn_8021A020(lbl_803EB688)) {
                    int result;

                    fn_80219A54(lbl_803EB688, 1);
                    result = fn_80219AF8(lbl_803EB688, unknown0, unknown1, 5);
                    if (result) {
                        fn_8018AFD0(result);
                    }
                }
            }
            if (value == 0.0f) {
                fn_8018AFD0(0);
            }
        }
        if (fn_801895EC(&a, &id, &value)) {
            if ((id == 7 || id == 0) && fn_80027DF0()) {
                fn_8000FCD4(a);
            }
            fn_802196B4(lbl_803EB688, a, id, 1, &value, lbl_803EB674);
        }
    }
    if (fn_8018A8B8()) {
        fn_802196B4(lbl_803EB688, -1, 20, 1, &value, 1);
        fn_8018A8B0(0);
    }
}

void fn_8018A69C(int a)
{
    fn_80188784(lbl_803EB640, a);
}

void fn_8018A6C4(int a, int b)
{
    fn_80188784(lbl_803EB640, a);
    fn_8018897C(lbl_803EB640, a, b, 0);
}

void fn_8018A710(int a, int b)
{
    fn_801889A4(lbl_803EB640, a, b);
}

void fn_8018A740(void)
{
    if (lbl_803EB688) {
        fn_80219A54(lbl_803EB688, 1);
    }
    if (lbl_803EB68C) {
        fn_80219A54(lbl_803EB68C, 1);
    }
    if (lbl_803EB690) {
        fn_80219A54(lbl_803EB690, 1);
    }
}

void fn_8018A798(int a)
{
    lbl_803EB67C = a;
}

int fn_8018A7A0(void)
{
    int value = lbl_803EB67C;

    lbl_803EB67C = -1;
    return value;
}

void fn_8018A7B0(void)
{
    if (!fn_8022863C()) {
        if (fn_80027DF0()) {
            fn_80024654();
        }
        fn_802285CC();
        fn_8006CA84(1);
        fn_801CE82C();
    }
}

void fn_8018A7F8(Object_80228224 *pObject, int mode)
{
    float aspect = 4.0f / 3.0f;

    switch (mode) {
    case 0:
        break;
    case 1:
    case 2:
        aspect = 16.0f / 9.0f;
        break;
    }
    fn_802286D8(pObject, 45.0f, aspect, 0.1f, 1500.0f);
}

Object_80228224 *fn_8018A854(void)
{
    return lbl_803EB644;
}

void fn_8018A85C(void *p)
{
    if (p == lbl_803EB688) {
        lbl_803EB680 |= 1;
    } else if (p == lbl_803EB690) {
        lbl_803EB680 |= 2;
    } else if (p == lbl_803EB68C) {
        lbl_803EB680 |= 4;
    }
}

void fn_8018A8B0(unsigned char value)
{
    lbl_803EB675 = value;
}

unsigned char fn_8018A8B8(void)
{
    return lbl_803EB675;
}

void fn_8018A8C0(unsigned char value)
{
    lbl_803EB674 = value;
}

void fn_8018A8C8(int a)
{
    fn_80220CDC(a);
    fn_80220CFC(a);
    fn_801CECDC(fn_801CECCC(14));
}
}
