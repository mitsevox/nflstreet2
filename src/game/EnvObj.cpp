/* The environment (stadium) object: creates the environment draw objects, attaches the stadium
   model and fades its ten elements. */
#include "engine/viewport.h"
#include "game/ResLoad.h"

struct EnvObj {
    char mUnknown0[4];
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    char mUnknown10[8];
    void *mpUnknown18;
    int mUnknown1C;
    int mUnknown20;
    char mUnknown24[0x6C0];
    unsigned char mUnknown6E4[10][192];
    unsigned char mUnknownE64[48];
};

struct EnvObjOverlay {
    char mUnknown0[0x14];
    EnvObj *mpUnknown14;
};

extern "C" {
void *fn_800A336C(void);
int fn_800A3374(void);
int fn_80146EDC(unsigned int index);
float fn_80146F0C(unsigned int index);
float fn_80146F40(unsigned int index);
void EnvLayersInit(EnvObj *pObject);
void EnvLayersFree(EnvObj *pObject);
int EnvDrawOverlay(void *pObject);
int EnvDraw(void *pObject);
int ObjNewType_(int a, int size, int c, void (*pInit)(void *), void (*pRelease)(void *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(void *));
int ObjNewInList(int handle, int a, int b, int *pDesc);
void ObjRemoveFromList(int handle, void *pItem);
void ObjSetPriority(int handle, void *pItem, int b);
void fn_80234DCC(int a, void *p, const char *pName, int b);
void fn_80234EA0(void *p, int a);
void fn_80235C90(void *p, int a, float b, float c, float d, float e);
void fn_80235DB8(int a);
}

static EnvObj *_EnvObj_pMain = 0;
static EnvObjOverlay *_EnvObj_pOverlay = 0;

extern "C" {
void EnvObjAttachModel(void)
{
    void *pData = fn_800A336C();
    int index = fn_800A3374();
    int handle = ResLoad(pData, index, 1);
    EnvObj *pObject;

    fn_80235DB8(handle);
    pObject = _EnvObj_pMain;
    pObject->mpUnknown18 = pData;
    pObject->mUnknown1C = index;
    pObject->mUnknown20 = handle;
    fn_80234DCC(handle, pObject->mUnknownE64, "Environment", 1);
}

int EnvObjDrawMain(void *pObject)
{
    EnvDraw(pObject);
    return 0;
}

int EnvObjDrawOverlay(void *pObject)
{
    EnvDrawOverlay(pObject);
    return 0;
}

void EnvObjAddObjType(int handle)
{
    EnvObj *pObject;

    ObjNewType_(6, sizeof(EnvObj), 1, 0, 0);
    ObjNewType_(25, sizeof(EnvObjOverlay), 1, 0, 0);
    ObjSetListObjFunc(handle, 6, 0, EnvObjDrawMain);
    _EnvObj_pMain = (EnvObj *)ObjNewInList(handle, 6, 0, 0);
    ObjSetListObjFunc(handle, 25, 0, EnvObjDrawOverlay);
    _EnvObj_pOverlay = (EnvObjOverlay *)ObjNewInList(handle, 25, 0, 0);
    ObjSetPriority(handle, _EnvObj_pMain, 4);
    _EnvObj_pOverlay->mpUnknown14 = _EnvObj_pMain;
    ObjSetPriority(handle, _EnvObj_pOverlay, 12);
    EnvObjAttachModel();
    pObject = _EnvObj_pMain;
    pObject->mUnknownC = pObject->mUnknown8 = pObject->mUnknown4 = 0.0f;
    EnvLayersInit(pObject);
}

void EnvObjRemoveObjType(int handle)
{
    EnvLayersFree(_EnvObj_pMain);
    fn_80234EA0(_EnvObj_pMain->mUnknownE64, 1);
    ResUnLoad(_EnvObj_pMain->mpUnknown18, _EnvObj_pMain->mUnknown1C);
    ObjRemoveFromList(handle, _EnvObj_pMain);
    VptTrashObject((int)_EnvObj_pMain);
    ObjRemoveFromList(handle, _EnvObj_pOverlay);
    VptTrashObject((int)_EnvObj_pOverlay);
    VptFlushObjectTrashSync();
    ObjDelType(6);
    _EnvObj_pMain = 0;
    ObjDelType(25);
    _EnvObj_pOverlay = 0;
}

void EnvObjUpdateFades(void)
{
    unsigned int i;
    void *pElement;
    float a;
    float b;
    int state;
    float value;

    for (i = 0; i < 10; i++) {
        pElement = _EnvObj_pMain->mUnknown6E4[i];
        a = fn_80146F0C(i);
        b = fn_80146F40(i);
        state = fn_80146EDC(i);
        if (a == b) {
            if (state == 1) {
                value = 0.5f;
            } else {
                value = 1.0f;
            }
        } else if (state == 1) {
            value = a * -0.5f / b + 1.0f;
        } else {
            value = a * 0.5f / b + 0.5f;
        }
        fn_80235C90(pElement, 0, 1.0f, 1.0f, 1.0f, value * 0.5f);
    }
}
}
