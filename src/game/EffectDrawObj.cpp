/* Keeps one object in the object list whose draw step draws the first group of
   in-game visual effects. */

#include "engine/viewport.h"

extern "C" {
void fn_80146DC4(int a);
int ObjNewType_(int a, int size, int c, void (*pInit)(void *), void (*pRelease)(void *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(void *));
int ObjNewInList(int handle, int a, int b, int *pDesc);
void ObjRemoveFromList(int handle, int item);
void ObjSetPriority(int handle, int item, int a);
}

static unsigned char _EffectDrawObj_bEnabled = 1;
static int _EffectDrawObj_pObject;

extern "C" {
int EffectDrawObjDraw(void *pItem)
{
    if (_EffectDrawObj_bEnabled != 0) {
        fn_80146DC4(0);
    }
    return 0;
}

void EffectDrawObjCreate(int handle)
{
    ObjNewType_(26, 20, 1, 0, 0);
    ObjSetListObjFunc(handle, 26, 0, EffectDrawObjDraw);
    _EffectDrawObj_pObject = ObjNewInList(handle, 26, 0, 0);
    ObjSetPriority(handle, _EffectDrawObj_pObject, 13);
}

void EffectDrawObjDestroy(int handle)
{
    ObjRemoveFromList(handle, _EffectDrawObj_pObject);
    VptTrashObject(_EffectDrawObj_pObject);
    VptFlushObjectTrashSync();
    ObjDelType(26);
    _EffectDrawObj_pObject = 0;
}
}
