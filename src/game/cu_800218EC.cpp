#include "game/fn_8007F828.h"
#include <string.h>

/* First argument of fn_8008044C, fn_8008056C, fn_80080948, fn_800809C4,
   fn_80080D38, fn_80080E20 and fn_800811E0. The constructor sets the same five
   words as Object_8007A334 in cu_8002306C. */
struct Object_8008044C {
    Object_8008044C() : mUnknown0(0), mUnknown4(0), mUnknown8(-1), mUnknown12(-1), mUnknown16(-1) {}
    ~Object_8008044C() {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    char mUnknown20[24];
};

/* Object returned by fn_8003DEC4. */
struct Object_8003DEC4 {
    char mUnknown0[4];
    char mUnknown4[16];
    int mUnknown20;
    float mUnknown24;
    char mUnknown28[4];
    int mUnknown32;
    int mUnknown36;
    char mUnknown40[76];
    char mUnknown116[792];
    char mUnknown908[4048];
    int mUnknown4956;
    char mUnknown4960[8];
    unsigned char mUnknown4968;
};

/* Object returned by fn_801DD168. */
struct Object_801DD168 {
    char mUnknown0[4];
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[84];
    char mUnknown108[4];
};

/* Third argument of fn_801DD168. */
struct Desc_801DD168 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
};

/* Element of lbl_8037D92C, lbl_8037DAEC and lbl_8037DCAC. */
struct Record_8037D92C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
    unsigned int mUnknown24;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
};

/* Argument of fn_800B267C, fn_800B26E0 and fn_800B2A14. */
struct Object_800B267C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    int mUnknown24;
    float mUnknown28;
    char mUnknown32[4];
    float mUnknown36;
};

/* First argument of fn_801BA03C, fn_801BC7C0, fn_801BCA74 and fn_801BCCAC. */
struct Object_801BA03C {
    char mUnknown0[4];
    unsigned short mUnknown4;
    char mUnknown6[6];
};

/* Element of lbl_8036B55C. */
struct Record_8036B55C {
    char mUnknown0[4];
    Object_8003DEC4 *mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    char mUnknown10[2];
    int mUnknown12;
    char mUnknown16[408];
    Object_800B267C mUnknown424;
    char mUnknown464[44];
    float mUnknown508;
    char mUnknown512[16];
    char mUnknown528[16];
    unsigned char mUnknown544;
    unsigned char mUnknown545;
    char mUnknown546[2];
    char mUnknown548[4];
    char mUnknown552[224];
    unsigned char mUnknown776;
    char mUnknown777[7];
    void *mUnknown784;
    char mUnknown788[4];
    void *mUnknown792;
    void *mUnknown796;
    void *mUnknown800;
    void *mUnknown804;
    void *mUnknown808;
    void *mUnknown812;
    char mUnknown816[192];
    int mUnknown1008;
    char mUnknown1012[232];
    Object_801BA03C mUnknown1244;
    char mUnknown1256[1240];
    char mUnknown2496[552];
    char mUnknown3048[48];
    Object_801BA03C mUnknown3096;
    char mUnknown3108[496];
    char mUnknown3604[404];
    Object_801BA03C mUnknown4008[2];
    char mUnknown4032[2][248];
    char mUnknown4528[2][404];
};

extern "C" {
extern float lbl_803EA2C4;
extern void *lbl_803EB688;

void fn_8003AB40(Record_8036B55C *pRecord);
int fn_8003DA94(unsigned short count, int a, int b);
int fn_8003DCC0(int a);
Object_8003DEC4 *fn_8003DEC4(int index);
void fn_8003E174(int a);
void fn_8003FAC4(int a);
void fn_8003FB2C(void);
int fn_8003FBF0(Object_801DD168 *pObject, int a);
void fn_80042270(Record_8036B55C *pRecord);
void fn_800423F8(Object_8003DEC4 *pObject, void *a, void *b);
void fn_800424C0(Object_8003DEC4 *pObject, int a);
void fn_800424E8(Object_8003DEC4 *pObject, void *a, unsigned short b, void *c);
void fn_80042508(Object_8003DEC4 *pObject, int a, unsigned int b);
void fn_80042530(Object_8003DEC4 *pObject, int a);
void fn_80042928(Object_8003DEC4 *pObject);
void fn_800490A0(int index, int a, int b);
int fn_8004A1A8(Object_8003DEC4 *pObject, int a);
void fn_8008044C(Object_8008044C *pObject, void *pDesc, int tag);
void fn_8008056C(Object_8008044C *pObject);
int fn_80080948(Object_8008044C *pObject);
void fn_800809C4(Object_8008044C *pObject, int a, int b);
int fn_80080D38(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80080E20(Object_8008044C *pObject);
int fn_800811E0(Object_8008044C *pObject);
void fn_80089A84(Record_8036B55C *pRecord, unsigned int a);
void fn_8008A248(void);
void fn_8008FCB4(int a);
void fn_8008FD88(int a);
void fn_8008FE60(void);
void fn_8008FED4(void);
void fn_8009BD48(Record_8036B55C *pRecord, int a, int b, unsigned char c);
void fn_8009CDEC(Record_8036B55C *pRecord);
int fn_800ADD7C(void *pObject, unsigned int a);
int fn_800ADEFC(void *pObject, unsigned int a);
void fn_800B267C(Object_800B267C *pObject);
void fn_800B26E0(Object_800B267C *pObject);
void fn_800B2A14(Object_800B267C *pObject, unsigned char *a);
int fn_800C47C4(void);
void fn_800D7A0C(Record_8036B55C *pRecord, int a);
void fn_800EFD70(int a);
void fn_800EFDD8(void);
void fn_800EFFA0(int a, void *b, Record_8036B55C *pRecord, int c);
void fn_8015CBC8(void);
void fn_8015CC1C(void);
int fn_8015CD9C(void);
void fn_8015D060(int index, char *pBuffer, unsigned char a, int b);
void fn_8015D1CC(int index, unsigned char a);
int fn_8015D1FC(int index);
int fn_8015D2E8(Object_8003DEC4 *pObject);
void fn_80161168(void);
void fn_8016D8B0(void *pObject);
void fn_8018A8C8(int a);
void fn_8018A908(void (*pCallback)(int, float, float, float, float));
void fn_801BA03C(Object_801BA03C *pObject, void *a, float b, Record_8036B55C *pRecord);
int fn_801BC7C0(Object_801BA03C *pObject, void *a, void *b);
int fn_801BCA74(Object_801BA03C *pObject, void *a, int b, void *c, int d, int e);
int fn_801BCCAC(Object_801BA03C *pObject, void *a, int b, void *c, int d, int e);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, Record_8036B55C *pRecord, float e);
void fn_801BE420(void *a, Object_801BA03C *pObject, void *b, Record_8036B55C *pRecord, float c);
int fn_801BE648(void *a);
void fn_801CE9E0(int a);
float fn_801CFD28(int a);
int fn_801CFFF0(int a, int b, float c);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D08FC(int a);
void fn_801D0ADC(int a);
void fn_801D0C58(void *a);
void fn_801D0F80(void *a);
void fn_801D1258(int which, float (*pMatrix)[4]);
void fn_801D1288(int which, float (*pMatrix)[4]);
void fn_801D12BC(int a);
void fn_801D12EC(int a);
void fn_801D131C(int a);
Object_801DD168 *fn_801DD168(int a, int b, Desc_801DD168 *pDesc);
void fn_8021D7B8(void *a, int b, int c, int *d);
void fn_80227490(float *pOut, float *pIn, int a, int b, int c);
int fn_80228668(void);
void fn_80228AD4(float (*pMatrix)[4], float a, float b, float c, float d);
void fn_80228D58(int handle);
void fn_80234424(int a);
}

static Object_8008044C lbl_8036B4F0;
/* Matrix built by fn_80228AD4 and passed to fn_801D1258. */
static float lbl_8036B51C[4][4];
static Record_8036B55C lbl_8036B55C[14];
/* Current values; fn_800229D8 interpolates them from lbl_8037DAEC towards
   lbl_8037DCAC by the factor in lbl_8037DE6C. */
static Record_8037D92C lbl_8037D92C[14];
static Record_8037D92C lbl_8037DAEC[14];
static Record_8037D92C lbl_8037DCAC[14];
static float lbl_8037DE6C[14];

static unsigned char lbl_802F4654[14] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };

/* Number of records set up by fn_800221CC. */
static int lbl_803EBAC0 = 0;
static unsigned char lbl_803EBAC4 = 0;
/* Set by fn_80022D3C together with the indices lbl_803ECE8C and lbl_803ECE90. */
static unsigned char lbl_803EBAC5 = 0;
static unsigned char lbl_803EBAC6 = 0;
static Object_801DD168 *lbl_803EBAC8 = 0;
static int lbl_803EBACC = 4;

static int lbl_803ECE8C;
static int lbl_803ECE90;

extern "C" {
void fn_80022580(int index, int a, int b);
static void fn_800229A0(int index);

static void fn_800218EC(int index, Object_8003DEC4 *pObject)
{
    Record_8037D92C *pState = &lbl_8037D92C[index];
    Record_8036B55C *pRecord;

    memset(pState, 0, sizeof(Record_8037D92C));
    pState->mUnknown16 = 1.0f;
    pState->mUnknown24 = 72;
    pRecord = &lbl_8036B55C[index];
    memset(pRecord, 0, sizeof(Record_8036B55C));
    pRecord->mUnknown4 = pObject;
    fn_8003AB40(pRecord);
    fn_800B267C(&pRecord->mUnknown424);
    fn_8016D8B0(pRecord->mUnknown512);
    fn_8016D8B0(pRecord->mUnknown528);
    fn_8009BD48(pRecord, 3, 0, index);
    pRecord->mUnknown8 = 0;
    pRecord->mUnknown12 = 0;
    pRecord->mUnknown9 = 0;
    pRecord->mUnknown784 = pRecord->mUnknown3048;
    pRecord->mUnknown792 = pRecord->mUnknown2496;
    pRecord->mUnknown796 = &pRecord->mUnknown1244;
    pRecord->mUnknown800 = pRecord->mUnknown1256;
    pRecord->mUnknown804 = pRecord->mUnknown3604;
    pRecord->mUnknown808 = &pRecord->mUnknown3096;
    pRecord->mUnknown812 = pRecord->mUnknown3108;
    pRecord->mUnknown508 = 170.0f;
    fn_80022580(index, 82, 0);
}

static void fn_80021A0C(Record_8036B55C *pRecord, Object_8003DEC4 *pObject, float step)
{
    unsigned int i;

    if (pRecord == 0 || pObject == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (pObject->mUnknown20 & 0x20) {
            fn_801BE420(pRecord->mUnknown4528[i], &pRecord->mUnknown4008[i], pRecord->mUnknown4032[i], pRecord, step);
            fn_801BA03C(&pRecord->mUnknown4008[i], pRecord->mUnknown4032[i], step, pRecord);
            fn_80042508(pObject, fn_801BC7C0(&pRecord->mUnknown4008[i], pRecord->mUnknown4032[i], pRecord->mUnknown4528[i]), i);
        } else if (fn_800ADD7C(pObject->mUnknown116, i)) {
            fn_80042508(pObject, fn_800ADEFC(pObject->mUnknown116, i), i);
        }
    }
}

static void fn_80021B08(Record_8036B55C *pRecord, float step)
{
    Object_8003DEC4 *pObject = pRecord->mUnknown4;
    int result;

    fn_800EFFA0(0, pRecord->mUnknown3048, pRecord, 0);
    if (pObject->mUnknown20 & 0x10) {
        fn_801BE420(pRecord->mUnknown3604, &pRecord->mUnknown3096, pRecord->mUnknown3108, pRecord, step);
        fn_801BA03C(&pRecord->mUnknown3096, pRecord->mUnknown3108, step, pRecord);
        result = fn_801BC7C0(&pRecord->mUnknown3096, pRecord->mUnknown3108, pRecord->mUnknown3604);
        fn_80042530(pObject, result);
    }
    fn_80021A0C(pRecord, pObject, step);
    fn_801BE420(pRecord->mUnknown2496, &pRecord->mUnknown1244, pRecord->mUnknown1256, pRecord, step);
    fn_801BA03C(&pRecord->mUnknown1244, pRecord->mUnknown1256, step, pRecord);
    result = fn_801BC7C0(&pRecord->mUnknown1244, pRecord->mUnknown1256, pRecord->mUnknown2496);
    fn_800424C0(pObject, result);
    pRecord->mUnknown544 = fn_801BCA74(&pRecord->mUnknown1244, pRecord->mUnknown1256, result, pRecord->mUnknown548, 0xFFFF, 1);
    pRecord->mUnknown545 = fn_801BCCAC(&pRecord->mUnknown1244, pRecord->mUnknown1256, result, pRecord->mUnknown552,
                                       fn_801BE648(pRecord->mUnknown792), (pRecord->mUnknown12 & 0x200) == 0);
    fn_800424E8(pObject, pRecord->mUnknown1256, pRecord->mUnknown1244.mUnknown4, pRecord->mUnknown2496);
}

static void fn_80021C8C(float x, float y, float z, float *pOut)
{
    float limit = -(240.0f / fn_801CFD28(0x100000));
    float offset = 240.0f / fn_801CFD28(0x100000);
    float scale;

    pOut[2] = 1.0f - offset + 1.0f + 10.0f - z;
    scale = (limit - pOut[2]) / limit;
    pOut[0] = (x - 427.0f) * scale + 427.0f;
    pOut[1] = (y - 240.0f) * scale + 240.0f;
    fn_80227490(pOut, pOut, 0x400000, 0, -0x400000);
}

static void fn_80021EFC(Object_8003DEC4 *pObject);

static void fn_80021D70(int index, unsigned int step)
{
    Record_8037D92C *pState = &lbl_8037D92C[index];
    Record_8036B55C *pRecord = &lbl_8036B55C[index];
    Object_8003DEC4 *pObject = pRecord->mUnknown4;

    pObject->mUnknown24 = pState->mUnknown16 * (float)pState->mUnknown24 * (1.0f / 72.0f);
    pObject->mUnknown24 = (pObject->mUnknown24 - pState->mUnknown16) * pState->mUnknown20 + pState->mUnknown16;
    pObject->mUnknown20 |= 9;
    fn_80021B08(pRecord, step);
    if (pRecord->mUnknown545 == 0) {
        pRecord->mUnknown424.mUnknown36 = pRecord->mUnknown424.mUnknown28;
        fn_800B26E0(&pRecord->mUnknown424);
    } else {
        fn_800B2A14(&pRecord->mUnknown424, &pRecord->mUnknown544);
    }
    if (pState->mUnknown29) {
        pRecord->mUnknown424.mUnknown24 = pState->mUnknown12;
    }
    if (pState->mUnknown28) {
        pRecord->mUnknown424.mUnknown0 = pRecord->mUnknown424.mUnknown12;
        pRecord->mUnknown424.mUnknown4 = pRecord->mUnknown424.mUnknown16;
        pRecord->mUnknown424.mUnknown8 = pRecord->mUnknown424.mUnknown20;
    }
    fn_80042270(pRecord);
    fn_8009CDEC(pRecord);
    fn_80042928(pObject);
    fn_80021EFC(pObject);
    if (lbl_803EBAC5 ? index == lbl_803ECE8C : index == 0) {
        Object_801DD168 *pView = lbl_803EBAC8;

        pObject->mUnknown32 = pRecord->mUnknown776;
        fn_800423F8(pObject, pView->mUnknown4, pView->mUnknown108);
    }
}

static void fn_80021EFC(Object_8003DEC4 *pObject)
{
    fn_801D0508();
    fn_801D08FC(0x400000);
    fn_801D0ADC(-0x400000);
    fn_801D0C58(pObject->mUnknown4);
    fn_801D0ADC(pObject->mUnknown36 + 0x400000);
    fn_801D08FC(0x400000);
    fn_801D0F80(pObject->mUnknown908);
    fn_801D0544();
}

static void fn_80021F60(int index, float a, float b, float c, float d)
{
    Record_8036B55C *pRecord = &lbl_8036B55C[index];
    Object_8003DEC4 *pObject = pRecord->mUnknown4;
    float projection[4][4];
    float view[4][4];

    fn_8018A8C8(3);
    fn_801CE9E0(1);
    fn_801D0470(fn_80228668());
    fn_801D1288(2, projection);
    fn_801D1288(6, view);
    fn_801D04C4();
    fn_801D1258(2, lbl_8036B51C);
    fn_801D12BC(1);
    fn_801D131C(2);
    fn_801D12EC(6);
    fn_801D0544();
    fn_80234424(0);
    fn_8004A1A8(pObject, 1);
    if (lbl_803EBAC5 ? index == lbl_803ECE8C : index == 0) {
        if (fn_8015D2E8(pObject)) {
            fn_8003FBF0(lbl_803EBAC8, 1);
        }
    }
    fn_801D1258(2, projection);
    fn_801D1258(6, view);
    fn_801CE9E0(0);
}

static void fn_80022078(int index, float a, float b, float c, float d)
{
    unsigned int step = (unsigned int)lbl_803EA2C4;
    int i = index;

    if (lbl_803EBAC5) {
        i = lbl_803ECE90;
        if (i >= 0 && i < lbl_803EBAC0) {
            fn_80021D70(i, step);
        }
        i = lbl_803ECE8C;
    }
    if (i >= 0 && i < lbl_803EBAC0) {
        fn_80021D70(i, step);
        fn_80021F60(i, a, b, c, d);
    }
}

static void fn_8002217C(int index, int enable)
{
    Record_8036B55C *pRecord;
    Object_8003DEC4 *pObject;

    if (index < 0 || index >= lbl_803EBAC0) {
        return;
    }
    pRecord = &lbl_8036B55C[index];
    pObject = pRecord->mUnknown4;
    if (enable) {
        pObject->mUnknown20 |= 0x400;
    } else {
        pObject->mUnknown20 &= ~0x400;
    }
}

void fn_800223E4(int index, float x, float y, float z);
void fn_800224A4(int index, float angle);
void fn_80022534(int index, float scale);

void fn_800221CC(int count)
{
    int i;
    Desc_801DD168 desc;
    Object_801DD168 *pView;

    fn_8008044C(&lbl_8036B4F0, 0, 0x54415453);
    lbl_803EBAC0 = count;
    fn_80228AD4(lbl_8036B51C, 45.0f, 4.0f / 3.0f, 1.0f, 200.0f);
    fn_8008FCB4(0);
    fn_8008FE60();
    fn_800EFD70(0x21);
    fn_8003DA94(lbl_803EBAC0, 0, 1);
    fn_8003E174(0);
    for (i = 0; i < lbl_803EBAC0; i++) {
        fn_800218EC(i, fn_8003DEC4(i));
        fn_800223E4(i, 427.0f, 440.0f, 5.0f);
        fn_80022534(i, 1.0f);
        fn_800224A4(i, 0.0f);
    }
    fn_8015CBC8();
    fn_8003FAC4(0);
    desc.mUnknown0 = fn_800C47C4();
    desc.mUnknown8 = 0;
    desc.mUnknown12 = 0;
    pView = fn_801DD168(3, 0, &desc);
    lbl_803EBAC8 = pView;
    pView->mUnknown20 = (pView->mUnknown20 | 2) & ~1;
    lbl_803EBAC4 = 1;
}

void fn_80022328(void)
{
    lbl_803EBAC4 = 0;
    fn_8015CC1C();
    fn_8003DCC0(0);
    fn_800EFDD8();
    fn_8008FED4();
    fn_8008FD88(1);
    fn_8008056C(&lbl_8036B4F0);
    lbl_803EBAC8->mUnknown20 &= ~2;
    fn_80228D58((int)lbl_803EBAC8);
    lbl_803EBAC8 = 0;
    fn_8003FB2C();
}

void fn_80022398(void)
{
    fn_8018A908(fn_80022078);
}

void fn_800223C0(void)
{
    fn_8018A908(0);
}

void fn_800223E4(int index, float x, float y, float z)
{
    fn_800229A0(index);
    lbl_8037D92C[index].mUnknown0 = x;
    lbl_8037D92C[index].mUnknown4 = y;
    lbl_8037D92C[index].mUnknown8 = z;
    fn_80021C8C(x, y, z, &lbl_8036B55C[index].mUnknown424.mUnknown0);
    fn_80021C8C(x, y, z, &lbl_8036B55C[index].mUnknown424.mUnknown12);
}

void fn_8002248C(int index, unsigned char value)
{
    lbl_8037D92C[index].mUnknown28 = value;
}

void fn_800224A4(int index, float angle)
{
    int value;

    fn_800229A0(index);
    value = (int)(angle * 46603.38f);
    lbl_8037D92C[index].mUnknown12 = value;
    lbl_8036B55C[index].mUnknown424.mUnknown24 = value;
}

void fn_8002251C(int index, unsigned char value)
{
    lbl_8037D92C[index].mUnknown29 = value;
}

void fn_80022534(int index, float scale)
{
    fn_800229A0(index);
    lbl_8037D92C[index].mUnknown16 = scale;
}

void fn_80022580(int index, int a, int b)
{
    Record_8036B55C *pRecord;

    fn_8002217C(index, 0);
    pRecord = &lbl_8036B55C[index];
    if (a == 82) {
        pRecord->mUnknown1008 = 6;
    }
    fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796, pRecord->mUnknown800, a, pRecord, 1.0f);
}

void fn_800225F4(int index, unsigned int value)
{
    Record_8036B55C *pRecord = &lbl_8036B55C[index];

    if (value > 30) {
        lbl_803EBAC8->mUnknown20 |= 1;
        fn_800D7A0C(pRecord, 2);
    } else {
        lbl_803EBAC8->mUnknown20 &= ~1;
    }
    fn_80089A84(pRecord, value);
    fn_8002217C(index, 1);
}

void fn_80022760(int index, unsigned int value);

void fn_80022680(int index, int a, int b)
{
    Object_8003DEC4 *pObject = fn_8003DEC4(index);
    char buffer[28];

    fn_800809C4(&lbl_8036B4F0, a, 0);
    pObject->mUnknown4956 = a;
    pObject->mUnknown4968 = fn_80080948(&lbl_8036B4F0);
    fn_80080D38(&lbl_8036B4F0, buffer, 27);
    fn_80080E20(&lbl_8036B4F0);
    fn_80022760(index, fn_800811E0(&lbl_8036B4F0));
    if (fn_8015CD9C()) {
        fn_8015D060(index, buffer, lbl_802F4654[index], b);
    }
}

void fn_80022730(int index, int value)
{
    lbl_802F4654[index] = value;
    fn_8015D1CC(index, value);
}

void fn_80022760(int index, unsigned int value)
{
    lbl_8037D92C[index].mUnknown24 = value;
}

void fn_80022778(void)
{
    if (lbl_803EBAC4) {
        if (fn_8007F828(6) == 2) {
            fn_80228AD4(lbl_8036B51C, 45.0f, 16.0f / 9.0f, 1.0f, 200.0f);
        } else {
            fn_80228AD4(lbl_8036B51C, 45.0f, 4.0f / 3.0f, 1.0f, 200.0f);
        }
        fn_80161168();
        if (lbl_803EBAC5 && lbl_803EBAC6) {
            Object_8003DEC4 *pObject = fn_8003DEC4(lbl_803ECE90);

            if (fn_8015D1FC(lbl_803ECE90) == 0 && fn_8015D2E8(pObject)) {
                int index = lbl_803ECE8C;

                lbl_803ECE8C = lbl_803ECE90;
                lbl_803ECE90 = index;
                lbl_803EBAC6 = 0;
            }
        }
    }
}

void fn_80022870(int index, int flag, float x, float y, float z, float angle, float scale)
{
    int value;

    lbl_8037DE6C[index] = 0.0f;
    lbl_8037DAEC[index].mUnknown0 = lbl_8037D92C[index].mUnknown0;
    lbl_8037DAEC[index].mUnknown4 = lbl_8037D92C[index].mUnknown4;
    lbl_8037DAEC[index].mUnknown8 = lbl_8037D92C[index].mUnknown8;
    lbl_8037DAEC[index].mUnknown12 = lbl_8037D92C[index].mUnknown12;
    lbl_8037DAEC[index].mUnknown16 = lbl_8037D92C[index].mUnknown16;
    lbl_8037DAEC[index].mUnknown20 = lbl_8037D92C[index].mUnknown20;
    lbl_8037DCAC[index].mUnknown0 = x;
    lbl_8037DCAC[index].mUnknown4 = y;
    lbl_8037DCAC[index].mUnknown8 = z;
    lbl_8037DCAC[index].mUnknown16 = scale;
    lbl_8037DCAC[index].mUnknown12 = (int)(angle * 46603.38f);
    if (flag) {
        lbl_8037DCAC[index].mUnknown20 = 1.0f;
    } else {
        lbl_8037DCAC[index].mUnknown20 = 0.0f;
    }
    value = 16;
    fn_8021D7B8(lbl_803EB688, 0x8000002B, 1, &value);
}

static void fn_800229A0(int index)
{
    lbl_8037DE6C[index] = 1.1f;
    lbl_8037D92C[index].mUnknown20 = 1.0f;
}

int fn_800229D8(void)
{
    int moving = 0;
    int i;

    for (i = 0; i < lbl_803EBAC0; i++) {
        float t = lbl_8037DE6C[i];

        if (t <= 1.0f) {
            moving = 1;
            lbl_8037D92C[i].mUnknown0 = lbl_8037DAEC[i].mUnknown0 + (lbl_8037DCAC[i].mUnknown0 - lbl_8037DAEC[i].mUnknown0) * t;
            lbl_8037D92C[i].mUnknown4 = lbl_8037DAEC[i].mUnknown4 + (lbl_8037DCAC[i].mUnknown4 - lbl_8037DAEC[i].mUnknown4) * t;
            lbl_8037D92C[i].mUnknown8 = lbl_8037DAEC[i].mUnknown8 + (lbl_8037DCAC[i].mUnknown8 - lbl_8037DAEC[i].mUnknown8) * t;
            lbl_8037D92C[i].mUnknown16 = lbl_8037DAEC[i].mUnknown16 + (lbl_8037DCAC[i].mUnknown16 - lbl_8037DAEC[i].mUnknown16) * t;
            lbl_8037D92C[i].mUnknown20 = lbl_8037DAEC[i].mUnknown20 + (lbl_8037DCAC[i].mUnknown20 - lbl_8037DAEC[i].mUnknown20) * t;
            lbl_8037D92C[i].mUnknown12 = fn_801CFFF0(lbl_8037DAEC[i].mUnknown12, lbl_8037DCAC[i].mUnknown12, t);
            lbl_8037DE6C[i] += 0.05f;
        } else {
            lbl_8037D92C[i].mUnknown0 = lbl_8037DCAC[i].mUnknown0;
            lbl_8037D92C[i].mUnknown4 = lbl_8037DCAC[i].mUnknown4;
            lbl_8037D92C[i].mUnknown8 = lbl_8037DCAC[i].mUnknown8;
            lbl_8037D92C[i].mUnknown16 = lbl_8037DCAC[i].mUnknown16;
            lbl_8037D92C[i].mUnknown20 = lbl_8037DCAC[i].mUnknown20;
            lbl_8037D92C[i].mUnknown12 = lbl_8037DCAC[i].mUnknown12;
        }
        fn_80021C8C(lbl_8037D92C[i].mUnknown0, lbl_8037D92C[i].mUnknown4, lbl_8037D92C[i].mUnknown8,
                    &lbl_8036B55C[i].mUnknown424.mUnknown0);
        lbl_8036B55C[i].mUnknown424.mUnknown24 = lbl_8037D92C[i].mUnknown12;
    }
    return moving;
}

float fn_80022BA0(float turn)
{
    if (lbl_8037DE6C[0] > 1.0f) {
        if ((turn < 0.0f ? -turn : turn) > 0.01) {
            int delta = (int)((float)lbl_803EBACC * turn * 46603.38f);
            int angle = lbl_8036B55C[0].mUnknown424.mUnknown24 + delta;

            lbl_8036B55C[0].mUnknown424.mUnknown24 = angle;
            lbl_8037D92C[0].mUnknown12 = angle;
            if (lbl_803EBAC5) {
                lbl_8036B55C[lbl_803ECE8C].mUnknown424.mUnknown24 = angle;
                lbl_8036B55C[lbl_803ECE90].mUnknown424.mUnknown24 = lbl_8036B55C[0].mUnknown424.mUnknown24;
                lbl_8037D92C[lbl_803ECE8C].mUnknown12 = lbl_8036B55C[0].mUnknown424.mUnknown24;
                lbl_8037D92C[lbl_803ECE90].mUnknown12 = lbl_8036B55C[0].mUnknown424.mUnknown24;
            }
        }
        if (turn > 0.01) {
            turn -= 0.05;
            if (turn < 0.0f) {
                turn = 0.0f;
            }
        } else if (turn < -0.01) {
            turn += 0.05;
            if (turn > 0.0f) {
                turn = 0.0f;
            }
        }
    }
    return turn;
}

void fn_80022D0C(int index)
{
    fn_800B267C(&lbl_8036B55C[index].mUnknown424);
}

unsigned char fn_80022D3C(unsigned char enable, int a, int b)
{
    unsigned char previous = lbl_803EBAC5;

    if (previous != enable) {
        lbl_803EBAC5 = enable;
        if (enable) {
            lbl_803ECE8C = a;
            lbl_803EBAC6 = 0;
            lbl_803ECE90 = b;
        }
    }
    return previous;
}

void fn_80022D6C(void)
{
    lbl_803EBAC6 = 1;
}

int fn_80022D78(void)
{
    return lbl_803ECE90;
}

int fn_80022D80(void)
{
    return lbl_803ECE8C;
}

void fn_80022D88(void)
{
    Record_8036B55C *pFirst = &lbl_8036B55C[lbl_803ECE8C];
    Record_8036B55C *pSecond = &lbl_8036B55C[lbl_803ECE90];

    fn_80022580(lbl_803ECE8C, 214, 0);
    fn_80022580(lbl_803ECE90, 214, 0);
    fn_800225F4(lbl_803ECE8C, 2);
    fn_800225F4(lbl_803ECE90, 2);
    fn_8008A248();
    fn_801BE068(pFirst->mUnknown792, pFirst->mUnknown796, pFirst->mUnknown800, 214, pFirst, 1.0f);
    fn_801BE068(pSecond->mUnknown792, pSecond->mUnknown796, pSecond->mUnknown800, 214, pSecond, 1.0f);
}

void fn_80022E40(int a, int b)
{
    fn_800490A0(lbl_803ECE8C, a, b);
    fn_800490A0(lbl_803ECE90, a, b);
}
}
