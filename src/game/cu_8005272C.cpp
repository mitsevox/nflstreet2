#include <string.h>

#include "game/Object_80040818.h"
#include "game/cu_80041210.h"
#include "game/cu_80067C10.h"
#include "game/fn_802270D4.h"
#include "game/fn_801D2B7C.h"

struct Data_8005272C {
    Object_80040818 *mUnknown0;
    float mUnknown4;
    char mUnknown8[32];
    char mUnknown40[32];
};

struct Data_800528E8 {
    Object_80040818 *mUnknown0;
    Object_80040818 *mUnknown4;
    Object_80040818 *mUnknown8;
    int mUnknown12;
    int mUnknown16;
};

extern "C" {
int fn_80040F10(void);
void fn_8004D498(int handle);
int fn_8004D4B0(int handle, const char *pName);
int fn_8004D508(int handle, const char *pName);
int fn_8004D5B8(int handle, const char *pKey, char *pText, int size);
float fn_8004D624(int handle, const char *pKey);
int fn_8004D84C(int handle);
void fn_8004D860(int handle, int value);
int fn_80052678(Object_80040818 *pObject);
int fn_801784C4(void);
void fn_801EC048(float *pOut, float *pA, float *pB, float t);
void fn_80227264(void *pOut, void *pV, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);

extern float lbl_803EA2C4;

void fn_8005272C(int handle, Object_80041904 *pObject);
int fn_800527FC(Object_80041904 *pObject, int a, int mode);
void fn_800528E8(int handle, Object_80041904 *pObject);
int fn_800529CC(Object_80041904 *pObject, Object_80040818 *pOwner, int mode);
}

extern "C" {

void fn_8005272C(int handle, Object_80041904 *pObject)
{
    Data_8005272C *pData = (Data_8005272C *)fn_801D2B7C(sizeof(Data_8005272C), 0, 0);
    pObject->mUnknown420 = pData;
    int saved = fn_8004D84C(handle);
    fn_8004D508(handle, "pathnode");
    fn_8004D5B8(handle, "nextnode", pData->mUnknown40, 32);
    pData->mUnknown4 = fn_8004D624(handle, "speed");
    fn_8004D498(handle);
    fn_8004D4B0(handle, "object");
    fn_8004D5B8(handle, "name", pData->mUnknown8, 32);
    fn_8004D860(handle, saved);
    pData->mUnknown0 = 0;
}

int fn_800527FC(Object_80041904 *pObject, int a, int mode)
{
    Data_8005272C *pData = (Data_8005272C *)pObject->mUnknown420;
    int i;
    if (mode == 0) {
        for (i = 0; i < fn_80040F10(); i++) {
            Object_80041904 *pOther = fn_80041904(i);
            if (pOther->mUnknown188 == 3 && strcmp(((Data_8005272C *)pOther->mUnknown420)->mUnknown8, pData->mUnknown40) == 0) {
                pData->mUnknown0 = fn_80040F18(i);
            }
        }
    } else if (mode != 3 && pData->mUnknown0 == 0) {
        for (i = 0; i < fn_80040F10(); i++) {
            Object_80041904 *pOther = fn_80041904(i);
            if (pOther->mUnknown188 == 3 && strcmp(((Data_8005272C *)pOther->mUnknown420)->mUnknown8, pData->mUnknown40) == 0) {
                pData->mUnknown0 = fn_80040F18(i);
            }
        }
    }
    return 1;
}

void fn_800528E8(int handle, Object_80041904 *pObject)
{
    char name[32];
    int i;
    Data_800528E8 *pData = (Data_800528E8 *)fn_801D2B7C(sizeof(Data_800528E8), 0, 0);
    pObject->mUnknown420 = pData;
    int saved = fn_8004D84C(handle);
    fn_8004D508(handle, "pathnode");
    fn_8004D5B8(handle, "name", name, 32);
    for (i = 0; i < fn_80040F10(); i++) {
        Object_80041904 *pOther = fn_80041904(i);
        if (pOther->mUnknown188 == 3 && strcmp(((Data_8005272C *)pOther->mUnknown420)->mUnknown8, name) == 0) {
            pData->mUnknown8 = fn_80040F18(i);
        }
    }
    fn_8004D860(handle, saved);
    pData->mUnknown12 = 0;
    pData->mUnknown0 = 0;
    pData->mUnknown4 = 0;
}

int fn_800529CC(Object_80041904 *pObject, Object_80040818 *pOwner, int mode)
{
    Vector_80039F5C pos;
    Data_800528E8 *pData = (Data_800528E8 *)pObject->mUnknown420;
    Data_8005272C *pNode;
    int done = 0;

    pos.mX = pObject->mUnknown8;
    pos.mY = pObject->mUnknown12;
    pos.mZ = pObject->mUnknown16;
    if (fn_801784C4()) {
        pos.mX = -pos.mX;
        pos.mY = -pos.mY;
    }
    if (mode == 0 || mode == 3) {
        return 1;
    }
    if (pData->mUnknown12 <= 0) {
        if (pData->mUnknown4) {
            pData->mUnknown0 = pData->mUnknown4;
        } else {
            pData->mUnknown0 = pData->mUnknown8;
            Object_80041904 *pMover = pOwner->mUnknown472;
            float *pVelocity = &pMover->mUnknown48;
            pVelocity[2] = 0.0f;
            pVelocity[1] = 0.0f;
            pMover->mUnknown48 = 0.0f;
        }
        pNode = (Data_8005272C *)pData->mUnknown0->mUnknown472->mUnknown420;
        pData->mUnknown4 = pNode->mUnknown0;
        if (!pData->mUnknown4) {
            pData->mUnknown0 = pData->mUnknown8;
            Object_80041904 *pMover = pOwner->mUnknown472;
            float *pVelocity = &pMover->mUnknown48;
            pVelocity[2] = 0.0f;
            pVelocity[1] = 0.0f;
            pMover->mUnknown48 = 0.0f;
            pNode = (Data_8005272C *)pData->mUnknown0->mUnknown472->mUnknown420;
            pData->mUnknown4 = pNode->mUnknown0;
        }
        float step[3];
        float *pFrom = &pData->mUnknown0->mUnknown472->mUnknown8;
        fn_802276B4(step, &pData->mUnknown4->mUnknown472->mUnknown8, pFrom);
        pOwner->mUnknown472->mUnknown8 = pFrom[0];
        pOwner->mUnknown472->mUnknown12 = pFrom[1];
        pOwner->mUnknown472->mUnknown16 = pFrom[2];
        float time = fn_802270D4(step) / pNode->mUnknown4;
        float rate = lbl_803EA2C4 * 60.0f;
        pData->mUnknown16 = pData->mUnknown12 = (int)(time * rate);
        fn_80227264(step, step, 1.0f / (float)pData->mUnknown12);
        pOwner->mUnknown472->mUnknown48 = step[0];
        pOwner->mUnknown472->mUnknown52 = step[1];
        pOwner->mUnknown472->mUnknown56 = step[2];
        pOwner->mRot.mX = pData->mUnknown0->mRot.mX;
        pOwner->mRot.mY = pData->mUnknown0->mRot.mY;
        pOwner->mRot.mZ = pData->mUnknown0->mRot.mZ;
        pOwner->mRot.mW = pData->mUnknown0->mRot.mW;
    } else {
        pData->mUnknown12--;
        float t = (float)pData->mUnknown12 / (float)pData->mUnknown16;
        Object_80041904 *pMover = pOwner->mUnknown472;
        fn_8022765C(&pMover->mUnknown8, &pMover->mUnknown8, &pMover->mUnknown48);
        fn_801EC048(&pOwner->mUnknown472->mUnknown96, &pData->mUnknown0->mUnknown472->mUnknown96,
                    &pData->mUnknown4->mUnknown472->mUnknown96, t);
        pNode = (Data_8005272C *)pData->mUnknown0->mUnknown472->mUnknown420;
    }
    if (!done && pObject->mUnknown308 != 0 && fn_80041928() % 9 == pObject->mUnknown310) {
        int index = fn_80052678(pOwner);
        fn_80067DB8(pObject->mUnknown308, &pos, 2, (int)pNode, index);
    }
    return 1;
}
}
