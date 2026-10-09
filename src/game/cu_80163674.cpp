#include "engine/cu_80227F14.h"
#include "game/cu_801882B4.h"
#include "game/cu_80163674.h"

extern "C" {
Cache_80188688 *lbl_803EB3A4 = 0;
extern char *lbl_802EAD10[];
int fn_80027DF0(void);
int fn_801C657C(void);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D08FC(int);
void fn_801D09EC(int);
void fn_801D0ADC(int);
void fn_801D0C58(void *);
void fn_801D0D94(float, float, float);
int fn_801DCF0C(int, int, int, void (*)(Object_80163788 *, Desc_80163788 *), void (*)(Object_80163788 *));
void fn_801DCF8C(int);
int fn_801DD0C8(void *, int, int, int (*)(Object_80163788 *, int));
void fn_80234DFC(int, void *, int, int, const char *, int);
void fn_80234EA0(void *, int);
void fn_80234EEC(void *, int, void *, unsigned char);
void fn_80234F74(void *, int, void *, unsigned char, int);
void fn_802353D8(void *, int);
void fn_802353E8(void *, int);
void fn_80235588(void *, int);
void fn_802355E4(void *);
void fn_80235630(void *, int);
void fn_80235740(void *, int);
void fn_80235764(void *, int);
void fn_80235788(void *, int, int);
void fn_80235C24(void *, void *);
void fn_80235C90(void *, int, float, float, float, float);
void fn_80235D10(void *, float);
void fn_80235D74(void *, int);
int fn_80235D9C(int);
void fn_80235DB8(int);
int fn_80236B4C(int);
void fn_8024EB28(int);

void fn_80163674(Object_80163788 *pObject, Desc_80163788 *pDesc)
{
    int data = fn_801889CC(lbl_803EB3A4, pDesc->mUnknown00, pDesc->mUnknown02);
    pObject->mUnknown198 |= 1;
    if (pObject->mUnknown198 & 1) {
        pObject->mUnknown14 = data;
        fn_80235DB8(data);
        if (fn_80235D9C(pObject->mUnknown14) == 0) {
            pObject->mUnknown14 = 0;
        }
        fn_80235588(&pObject->mUnknown48, 6);
        fn_80235630(&pObject->mUnknown48, pObject->mUnknown14);
        fn_80234DFC(pObject->mUnknown14, pObject->mUnknown18, 0, 0, "UISModel", 0);
        fn_80235C24(&pObject->mUnknown48, pObject->mUnknown18);
        if (fn_80027DF0()) {
            if (pObject->mUnknown1CE == 26) {
                fn_80235D10(&pObject->mUnknown48, 15000.0f);
                fn_802353E8(&pObject->mUnknown48, 0x4000);
            } else {
                fn_80235D10(&pObject->mUnknown48, 0.0f);
            }
        } else {
            fn_80235D10(&pObject->mUnknown48, 20000.0f);
        }
    }
}

void fn_80163788(Object_80163788 *pObject, Desc_80163788 *pDesc)
{
    pObject->mUnknown04 = 0.0f;
    pObject->mUnknown08 = 0.0f;
    pObject->mUnknown0C = 0.0f;
    pObject->mUnknown1CC = pDesc->mUnknown00;
    pObject->mUnknown1CE = pDesc->mUnknown02;
    pObject->mUnknown19C = pDesc->mUnknown04;
    pObject->mUnknown1B4 = pDesc->mUnknown1C;
    pObject->mUnknown1C0 = pDesc->mUnknown28;
    pObject->mUnknown1A8 = (int)(pDesc->mUnknown10.mX * 46603.37890625f);
    pObject->mUnknown1AC = (int)(pDesc->mUnknown10.mY * 46603.37890625f);
    pObject->mUnknown1B0 = (int)(pDesc->mUnknown10.mZ * 46603.37890625f);
    pObject->mUnknown1D4 = 0;
    pObject->mUnknown1D0 = 0.0f;
    pObject->mUnknown1DC = pObject->mUnknown1DA = pObject->mUnknown1D8 = -1;
    pObject->mUnknown1DE = 0;
    pObject->mUnknown198 = 0;
    pObject->mUnknown1E4 = 255;
    fn_80188784(lbl_803EB3A4, pDesc->mUnknown00);
    fn_8018897C(lbl_803EB3A4, pDesc->mUnknown00, pDesc->mUnknown02, 0);
    fn_80163674(pObject, pDesc);
}

void fn_801638F0(Object_80163788 *pObject)
{
    if (pObject->mUnknown198 & 1) {
        fn_802355E4(&pObject->mUnknown48);
        fn_80234EA0(pObject->mUnknown18, 0);
    }
    fn_801889A4(lbl_803EB3A4, pObject->mUnknown1CC, pObject->mUnknown1CE);
    fn_801888A4(lbl_803EB3A4, pObject->mUnknown1CC);
}

int fn_80163954(Object_80163788 *pObject, int value)
{
    int context = fn_801C657C();
    fn_801D0470(fn_80228668());
    fn_801D04C4();
    fn_801D0C58(&pObject->mUnknown19C);
    fn_801D08FC(pObject->mUnknown1A8);
    fn_801D09EC(pObject->mUnknown1AC);
    fn_801D0ADC(pObject->mUnknown1B0);
    fn_801D0D94(pObject->mUnknown1C0.mX, pObject->mUnknown1C0.mY, pObject->mUnknown1C0.mZ);
    if (pObject->mUnknown198 & 1) {
        if (pObject->mUnknown1E4 == 255) {
            fn_80235740(&pObject->mUnknown48, context);
            if (pObject->mUnknown1D4) {
                fn_802353E8(&pObject->mUnknown48, 0x20000);
            }
            fn_80235788(&pObject->mUnknown48, context, fn_80236B4C(5));
        } else {
            fn_8024EB28(1);
            fn_80235C90(&pObject->mUnknown48, context, 0.5f, 0.5f, 0.5f, 0.0f);
            fn_80235740(&pObject->mUnknown48, context);
            fn_80235764(&pObject->mUnknown48, context);
            fn_802353D8(&pObject->mUnknown48, 0x100);
            fn_80235C90(&pObject->mUnknown48, context, 0.5f, 0.5f, 0.5f, 0.2f);
            fn_802353D8(&pObject->mUnknown48, 2);
            fn_80235740(&pObject->mUnknown48, context);
            fn_80235764(&pObject->mUnknown48, context);
            fn_802353E8(&pObject->mUnknown48, 0x100);
            fn_8024EB28(0);
        }
        fn_801D0470(fn_80228668());
        fn_801D0544();
    }
    return 0;
}

void fn_80163AD8(Object_80163788 *pObject, void *pData, int index, int component)
{
    if (pObject->mUnknown198 & 1) {
        State_80163AD8 *pState = &pObject->mUnknown48;
        unsigned char part = component;
        fn_80234EEC(pState, index, pData, part);
        fn_80234F74(pState->mpUnknown58, index, pData, part, 0);
    }
}

void fn_80163B44(Object_80163788 *pObject, void *pData)
{
    fn_80163AD8(pObject, pData, 4, 0);
    fn_80163AD8(pObject, pData, 5, 1);
    fn_80163AD8(pObject, pData, 3, 2);
    fn_801889A4(lbl_803EB3A4, pObject->mUnknown1D8, pObject->mUnknown1DA);
    fn_801888A4(lbl_803EB3A4, pObject->mUnknown1D8);
    pObject->mUnknown1DE &= ~1;
}

int fn_80163BCC(Object_80163788 *pObject)
{
    int result = 1;
    if (pObject->mUnknown1DE & 1) {
        void *pData = (void *)fn_801889CC(lbl_803EB3A4, pObject->mUnknown1D8, pObject->mUnknown1DA);
        if (pData) {
            fn_80163B44(pObject, pData);
        } else {
            result = 0;
        }
    }
    return result;
}

int fn_80163C30(void *pHandle, int count)
{
    int result = fn_801DCF0C(19, sizeof(Object_80163788), count, fn_80163788, fn_801638F0);
    if (pHandle) {
        result = fn_801DD0C8(pHandle, 19, 0, fn_80163954);
    }
    if (!lbl_803EB3A4) {
        Desc_80188688 desc;
        desc.mUnknown0 = 1;
        desc.mUnknown4 = 21;
        desc.mUnknown8 = 0;
        desc.mUnknown12 = lbl_802EAD10;
        lbl_803EB3A4 = fn_80188688(&desc);
        result = (int)lbl_803EB3A4;
    }
    return result;
}

void fn_80163CD0(void)
{
    fn_80228E18();
    fn_801DCF8C(19);
    fn_80188728(lbl_803EB3A4);
    lbl_803EB3A4 = 0;
}

void fn_80163D08(Object_80163788 *pObject, int value)
{
    if ((pObject->mUnknown198 & 1) && pObject->mUnknown14 && fn_80163BCC(pObject)) {
        fn_80163954(pObject, value);
    }
}

void fn_80163D64(Object_80163788 *pObject, unsigned char value)
{
    pObject->mUnknown1E4 = value;
    if (pObject->mUnknown198 & 1) {
        fn_80235D74(&pObject->mUnknown48, value >> 2);
    }
}
}
