/* Pass icons: the button icons drawn above each eligible receiver while the player
   chooses a pass. One small object per receiver is kept in the object list and drawn
   at the receiver's position, scaled by its distance from the camera along the field. */

#include "game/PassIconObj.h"
#include "game/PassIconTex.h"
#include <math.h>
#include "engine/viewport.h"
#include "game/GameCamera.h"
#include "game/Object_80039F5C.h"

struct PassIconObjDesc_t {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
};

extern "C" {
int VptManagerGetPassIcons(void);
int PauseIsOpen(void);
int CamGameGetCurrentSlot(void);
GameCamera_t *CamGameGetCamera(int index);
int PassIconsAreShown(void);
int PassIconGetPosition(int index, Vector_80039F5C *pOut);
int PassIconsWereShown(void);
float fn_80178A44(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D08FC(int a);
void fn_801D0ADC(int a);
void fn_801D0C58(void *a);
void fn_801D0CFC(float a);
int ObjNewType_(int a, int b, int c, void (*pA)(PassIconObj_t *, const PassIconObjDesc_t *), void (*pB)(void));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(PassIconObj_t *));
int ObjNewInList(int handle, int a, int b, PassIconObjDesc_t *pInit);
void ObjRemoveFromList(int handle, int a);
void ObjSetPriority(int handle, int a, int b);
}

static unsigned char _PassIconObj_bEnabled;

extern "C" void PassIconObjInit(PassIconObj_t *pInstance, const PassIconObjDesc_t *pInit)
{
    pInstance->mUnknown04.mX = 0.0f;
    pInstance->mUnknown04.mY = 0.0f;
    pInstance->mUnknown04.mZ = 0.01f;
    pInstance->mUnknown14 = pInit->mUnknown0;
    pInstance->mUnknown18 = pInit->mUnknown4;
    pInstance->mUnknown1C = pInit->mUnknown8;
    PassIconObjSetPalette(pInstance, 2);
}

extern "C" void PassIconObjFree(void) {}

extern "C" int PassIconObjDraw(PassIconObj_t *pInstance)
{
    if ((PassIconsAreShown() == 1 || PassIconsWereShown() == 1) && _PassIconObj_bEnabled == 1 && PauseIsOpen() == 0) {
        Vector_80039F5C *pPos = &pInstance->mUnknown04;
        if (PassIconGetPosition(pInstance->mUnknown1C, pPos) == 1) {
            GameCamera_t *pCamera;
            float scale = 1.0f;
            Vector_80039F5C pos;

            pCamera = CamGameGetCamera(CamGameGetCurrentSlot());
            scale = fabsf(pInstance->mUnknown04.mY - pCamera->mHeader.mUnknown04[1]) / (fn_80178A44() * 2.0f) * 2.0f + 0.3f;
            fn_801D0470(VptGetMatrixStack());
            fn_801D04C4();
            pos = *pPos;
            pos.mZ += scale * 0.5;
            fn_801D0C58(&pos);
            fn_801D0ADC(-pCamera->mHeader.mUnknown14[2]);
            fn_801D08FC(0xC00000 - pCamera->mHeader.mUnknown14[0]);
            pInstance->mUnknown20 = PassIconsAreShown() ? 1.0f : 0.4f;
            fn_801D0CFC(scale);
            PassIconTexDraw(pInstance);
            fn_801D0470(VptGetMatrixStack());
            fn_801D0544();
        }
    }
    return 0;
}

extern "C" void PassIconObjSetEnabled(int value)
{
    if (VptManagerGetPassIcons()) {
        _PassIconObj_bEnabled = value;
    } else {
        _PassIconObj_bEnabled = 0;
    }
}

extern "C" void PassIconObjRegister(void *pOwner)
{
    ObjNewType_(12, 36, 3, PassIconObjInit, PassIconObjFree);
    ObjSetListObjFunc((int)pOwner, 12, 0, PassIconObjDraw);
    PassIconTexLoad();
    _PassIconObj_bEnabled = 1;
}

extern "C" void PassIconObjUnregister(void)
{
    VptFlushObjectTrashSync();
    PassIconTexFree();
    ObjDelType(12);
}

extern "C" PassIconObj_t *PassIconObjNew(void *pOwner, unsigned char c, int a, int b)
{
    PassIconObjDesc_t init;
    PassIconObj_t *pItem;

    init.mUnknown0 = a;
    init.mUnknown4 = b;
    init.mUnknown8 = c;
    pItem = (PassIconObj_t *)ObjNewInList((int)pOwner, 12, 0, &init);
    ObjSetPriority((int)pOwner, (int)pItem, 11);
    return pItem;
}

extern "C" void PassIconObjDelete(void *pOwner, PassIconObj_t *pItem)
{
    if (pItem != 0) {
        ObjRemoveFromList((int)pOwner, (int)pItem);
        VptTrashObject((int)pItem);
    }
}

extern "C" void PassIconObjSetPalette(PassIconObj_t *pInstance, unsigned char value)
{
    pInstance->mUnknown1D = value;
}
