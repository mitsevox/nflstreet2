#include <string.h>

#include "game/cu_80041210.h"
#include "game/fn_801D2B7C.h"

struct Data_8005272C {
    int mUnknown0;
    float mUnknown4;
    char mUnknown8[32];
    char mUnknown40[32];
};

struct Data_800528E8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
};

extern "C" {
int fn_80040F10(void);
int fn_80040F18(int index);
void fn_8004D498(int handle);
int fn_8004D4B0(int handle, const char *pName);
int fn_8004D508(int handle, const char *pName);
int fn_8004D5B8(int handle, const char *pKey, char *pText, int size);
float fn_8004D624(int handle, const char *pKey);
int fn_8004D84C(int handle);
void fn_8004D860(int handle, int value);

void fn_8005272C(int handle, Object_80041904 *pObject);
int fn_800527FC(Object_80041904 *pObject, int a, int mode);
void fn_800528E8(int handle, Object_80041904 *pObject);
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

}
