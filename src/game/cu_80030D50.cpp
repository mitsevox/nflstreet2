/* 228-byte object allocated through fn_801DCF0C by fn_80030F38; a single
   instance is kept in sObject. */
struct Object_80030D50 {
    int mUnknown0;
    float mUnknown4[3];
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    unsigned char mUnknown28[192];
    int mUnknown220;
    unsigned char mUnknown224;
};

extern "C" {
int fn_800C47C4(void);
int fn_801C657C(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *a);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(Object_80030D50 *, int *),
                void (*pRelease)(Object_80030D50 *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(Object_80030D50 *));
int fn_801DD268(int handle, int a, int b, int *pDesc);
void fn_801DD320(int handle, Object_80030D50 *pObject);
void fn_801DD3AC(int handle, Object_80030D50 *pObject, int b);
int fn_801EF390(int a, int b, int c);
void fn_801F010C(int a, int b);
int fn_801F0DB8(int a, int b);
void fn_80210814(int a, int b, int c);
int fn_80228668(void);
void fn_80228D58(Object_80030D50 *pObject);
void fn_80228E18(void);
void fn_802353D8(void *p, int flags);
void fn_80235588(void *p, int a);
void fn_802355E4(void *p);
void fn_80235630(void *p, int a);
void fn_80235740(void *p, int a);
void fn_80235764(void *p, int a);
void fn_80235C48(void *p, int a);
void fn_80235C90(void *p, int a, float b, float c, float d, float e);
void fn_80235DB8(int a);
}

static Object_80030D50 *sObject = 0;

extern "C" {
void fn_80030D50(Object_80030D50 *pObject, int *pArgs)
{
    pObject->mUnknown4[0] = 0.0f;
    pObject->mUnknown4[1] = 0.0f;
    pObject->mUnknown4[2] = 0.01f;
    pObject->mUnknown224 = 0;
    pObject->mUnknown20 = pArgs[0];
    pObject->mUnknown24 = pArgs[1];
    pObject->mUnknown220 = fn_801EF390(pObject->mUnknown20, pObject->mUnknown24, 1);
    fn_80235DB8(pObject->mUnknown220);
    fn_80235588(pObject->mUnknown28, 6);
    fn_80235630(pObject->mUnknown28, pObject->mUnknown220);
    fn_80235C48(pObject->mUnknown28, 3);
    fn_802353D8(pObject->mUnknown28, 0x400008);
}

void fn_80030DFC(Object_80030D50 *pObject)
{
    fn_802355E4(pObject->mUnknown28);
    if (pObject->mUnknown220 != 0) {
        if (fn_801F0DB8(pObject->mUnknown20, pObject->mUnknown24)) {
            fn_801F010C(pObject->mUnknown20, pObject->mUnknown24);
        }
    }
}

int fn_80030E58(Object_80030D50 *pObject)
{
    float v[3];

    if (pObject->mUnknown220 != 0 && pObject->mUnknown224 == 1) {
        fn_801D0470(fn_80228668());
        fn_801D04C4();
        v[0] = pObject->mUnknown4[0];
        v[1] = pObject->mUnknown4[1];
        v[2] = 0.0f;
        fn_801D0C58(v);
        fn_80235740(pObject->mUnknown28, fn_801C657C());
        fn_801D0470(fn_80228668());
        fn_801D0544();
        fn_80235C90(pObject->mUnknown28, fn_801C657C(), 0.25f, 0.25f, 0.75f, 1.0f);
        fn_80210814(0, 0, 0);
        fn_80235764(pObject->mUnknown28, fn_801C657C());
    }
    return 0;
}

void fn_80030F38(int handle)
{
    int desc[2];

    fn_801DCF0C(10, sizeof(Object_80030D50), 1, fn_80030D50, fn_80030DFC);
    fn_801DD0C8(handle, 10, 0, fn_80030E58);
    desc[0] = fn_800C47C4();
    desc[1] = 7;
    sObject = (Object_80030D50 *)fn_801DD268(handle, 10, 0, desc);
    fn_801DD3AC(handle, sObject, 3);
}

void fn_80030FD8(int handle)
{
    if (sObject != 0) {
        fn_801DD320(handle, sObject);
        fn_80228D58(sObject);
    }
    fn_80228E18();
    fn_801DCF8C(10);
}

void fn_80031018(const float *pValue)
{
    Object_80030D50 *pObject = sObject;

    if (pObject == 0) {
        return;
    }
    pObject->mUnknown4[0] = pValue[0];
    pObject->mUnknown4[1] = pValue[1];
    pObject->mUnknown4[2] = pValue[2];
}

void fn_80031040(unsigned char value)
{
    Object_80030D50 *pObject = sObject;

    if (pObject == 0) {
        return;
    }
    pObject->mUnknown224 = value;
}

int fn_80031054(float *pValue)
{
    Object_80030D50 *pObject = sObject;
    int result = 0;

    if (pObject->mUnknown224 != 0) {
        result = 1;
        pValue[0] = pObject->mUnknown4[0];
        pValue[1] = pObject->mUnknown4[1];
        pValue[2] = pObject->mUnknown4[2];
    }
    return result;
}
}
