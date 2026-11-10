/* UI Studio model object: the front-end screen object that shows a 3D model.
   Its action function creates the model from the screen's descriptor, draws it
   faded with the current UI colour alpha, stores a percentage value the screen
   sends to it, and releases it; the init and shutdown calls create and free the model pool. */
#include "engine/viewport.h"
#include "game/UISModel.h"
#include "game/UISModelObj.h"

struct UISModelVec3_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

struct UISModelDesc_t {
    short mUnknown0;
    short mUnknown2;
    UISModelVec3_t mUnknown4;
    UISModelVec3_t mUnknown16;
    UISModelVec3_t mUnknown28;
    UISModelVec3_t mUnknown40;
};

struct UISModelObj_t {
    short mUnknown0;
    short mUnknown2;
    UISModelVec3_t mUnknown4;
    UISModelVec3_t mUnknown16;
    UISModelVec3_t mUnknown28;
    UISModelVec3_t mUnknown40;
    UISModel_t *mpUnknown52;
};

struct UISColor_t {
    char mUnknown0[12];
    float mUnknown12;
};

extern "C" {
UISModel_t *ObjNew(int type, int flags, UISModelDesc_t *pDesc);
UISColor_t *fn_8021CA3C(void);
void UISGameSetDrawMode(int a);
void fn_801CE9E0(int a);
void fn_801CE95C(void);

void UISModelObjCreate(UISModelObj_t *p);
void UISModelObjDraw(UISModelObj_t *p, int *pFlag);
void UISModelObjDestroy(UISModelObj_t *p);
void UISModelObjNotify(UISModelObj_t *p, int a, int b);
void UISModelObjAction(UISModelObj_t *p, unsigned int message, int a, int *pArgs);

unsigned char _UISModelObj_bInit = 0;

void UISModelObjCreate(UISModelObj_t *p)
{
    UISModelDesc_t desc;

    desc.mUnknown0 = p->mUnknown0;
    desc.mUnknown2 = p->mUnknown2;
    desc.mUnknown4 = p->mUnknown4;
    desc.mUnknown16 = p->mUnknown16;
    desc.mUnknown28 = p->mUnknown28;
    desc.mUnknown40 = p->mUnknown40;
    p->mpUnknown52 = ObjNew(19, 0, &desc);
}

void UISModelObjDraw(UISModelObj_t *p, int *pFlag)
{
    UISColor_t *pObject = fn_8021CA3C();

    UISGameSetDrawMode(4);
    fn_801CE9E0(1);
    if (pFlag != 0 && *pFlag == 0) {
        fn_801CE95C();
        *pFlag = 1;
    }
    UISModelSetDrawMode(p->mpUnknown52, (unsigned char)(pObject->mUnknown12 * 255.0f));
    UISModelDrawReady(p->mpUnknown52, 1);
    fn_801CE9E0(0);
}

void UISModelObjDestroy(UISModelObj_t *p)
{
    VptTrashObject((int)p->mpUnknown52);
}

void UISModelObjNotify(UISModelObj_t *p, int a, int b)
{
}

int UISModelObjInit(void)
{
    int result = UISModelRegister(0, 40);
    _UISModelObj_bInit = 1;
    return result;
}

void UISModelObjShutdown(void)
{
    UISModelUnregister();
    _UISModelObj_bInit = 0;
}

void UISModelObjAction(UISModelObj_t *p, unsigned int message, int a, int *pArgs)
{
    if (p->mUnknown0 != 9) {
        switch (message) {
        case -1:
            UISModelObjCreate(p);
            break;
        case -2:
            UISModelObjDraw(p, pArgs);
            break;
        case -3:
            UISModelObjDestroy(p);
            break;
        case 0:
            UISModelObjNotify(p, pArgs[0], pArgs[1]);
            break;
        case 4:
            p->mpUnknown52->mUnknown1D0 = pArgs[0] * 0.01f;
            p->mpUnknown52->mUnknown1D4 = 1;
            break;
        }
    }
}
}
