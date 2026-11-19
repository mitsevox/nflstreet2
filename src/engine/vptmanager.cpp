/* Viewport manager: the camera stack of the game viewport (push, pop, replace, current camera) and its saved state, plus the market-camera stubs. */

#include <string.h>
#include "engine/viewport.h"
#include "game/fn_80238174.h"
#include "game/CamAddCameraToViewport.h"
#include "engine/dslist.h"

struct VptManagerStackEntry_t {
    void *mpObject;
    int (*mpCallback4)(Viewport_t *, void *);
    int (*mpCallback8)(Viewport_t *, void *);
};
struct VptManagerStack_t { Viewport_t *mpObject; void *mpList; };
extern "C" {
void *DSNewListNode(void *);
void *DSGetListNode(void *, void *);
void DSRemoveListNode(void *, VptManagerStackEntry_t *);
void DSDelListNode(void *, void *);
void *DSNextListNode(void *, void *);
int DSSearchList(void *, void *, void *, VptManagerStackEntry_t **, int (*)(VptManagerStackEntry_t *,void *,VptManagerStackEntry_t **));
void CamRemoveCameraFromViewport(Viewport_t *, void *);
static VptManagerStack_t *_VptManager_pStack = 0;

int _VptManagerCreateStack(void *p, int a) {
    VptManagerStack_t *s=(VptManagerStack_t *)p;
    s->mpList=DSNewList(1,0,5,12,0,0);
    s->mpObject=0;
    return 0;
}
int _VptManagerDestroyStack(void *p,int a) {
    VptManagerStack_t *s=(VptManagerStack_t *)p;
    DSDelList(s->mpList);
    s->mpObject=0;
    s->mpList=0;
    return 0;
}
int _VptManagerAttach(VptManagerStack_t *s,VptManagerStackEntry_t *r) {
    int result=1;
    if(r->mpCallback4) result=r->mpCallback4(s->mpObject,r->mpObject);
    else CamAddCameraToViewport(s->mpObject,r->mpObject);
    return result;
}
int _VptManagerDetach(VptManagerStack_t *s,VptManagerStackEntry_t *r) {
    int result=1;
    if(r->mpCallback8) result=r->mpCallback8(s->mpObject,r->mpObject);
    else {
        CamRemoveCameraFromViewport(s->mpObject,r->mpObject);
        if(VptGetCamera(s->mpObject)) result=0;
    }
    return result;
}
VptManagerStackEntry_t *_VptManagerNewStackEntry(VptManagerStack_t *s) {
    VptManagerStackEntry_t *r=(VptManagerStackEntry_t *)DSNewListNode(s->mpList);
    r->mpCallback4=0;r->mpCallback8=0;r->mpObject=0;
    return r;
}
VptManagerStack_t *_VptManagerGetStack(Viewport_t *p) {
    if(!_VptManager_pStack->mpObject) _VptManager_pStack->mpObject=p;
    return _VptManager_pStack;
}
int _VptManagerFindStackEntry(VptManagerStackEntry_t *r,void *p,VptManagerStackEntry_t **out) {
    if(r->mpObject==p) {*out=r;return 0;}
    return -1;
}
int _VptManagerCompare(void *p,void *q) { return 0; }
int _VptManagerSave(void *p,void *data) {
    VptManagerStack_t *s=(VptManagerStack_t *)p;
    short count=0;
    void *r=DSGetListNode(s->mpList,0);
    while(r) {count++;r=DSNextListNode(s->mpList,r);}
    *(short *)data=count;data=(char *)data+2;
    for(short remaining=count;remaining>0;remaining--) {
        r=DSGetListNode(s->mpList,0);
        for(short i=1;i<remaining;i++) r=DSNextListNode(s->mpList,r);
        memcpy(data,r,12);data=(char *)data+12;
    }
    return 1;
}
int _VptManagerLoad(void *p,void *data) {
    VptManagerStack_t *s=(VptManagerStack_t *)p;
    void *r;
    while((r=DSGetListNode(s->mpList,0))!=0) DSDelListNode(s->mpList,r);
    short count=*(short *)data;data=(char *)data+2;
    while(count>0) {
        r=DSNewListNode(s->mpList);
        memcpy(r,data,12);data=(char *)data+12;
        DSAddListNode(s->mpList,r,0);count--;
    }
    return 1;
}
int _VptManagerGetSaveSize(void *p) {return 62;}
void VptManagerInit() {
    void *h=fn_80238174(0,(void **)&_VptManager_pStack,8,0,0x7670746D);
    fn_80238234(h,_VptManagerCreateStack,_VptManagerDestroyStack,0,_VptManagerCompare);
    fn_80238248(h,_VptManagerSave,_VptManagerGetSaveSize,_VptManagerLoad);
    fn_802381E0(h);
}
void VptManagerRestoreCamera() {
    VptManagerStack_t *s=_VptManagerGetStack(0);
    VptManagerStackEntry_t *r=(VptManagerStackEntry_t *)DSGetListNode(s->mpList,0);
    if(r && VptGetCamera(s->mpObject)!=r->mpObject) CamAddCameraToViewport(s->mpObject,r->mpObject);
}
void VptManagerShutdown() {}
int VptManagerPushCamera(Viewport_t *p,void *obj,int (*a)(Viewport_t *,void *),int (*b)(Viewport_t *,void *)) {
    int changed=0;
    VptManagerStack_t *s=_VptManagerGetStack(p);
    int result=1;
    VptManagerStackEntry_t *r=0;
    DSSearchList(s->mpList,0,obj,&r,_VptManagerFindStackEntry);
    VptManagerStackEntry_t *first=(VptManagerStackEntry_t *)DSGetListNode(s->mpList,0);
    if(first && first!=r) result=_VptManagerDetach(s,first);
    if(result) {
        if(r) {
            if(r!=first) {changed=1;DSRemoveListNode(s->mpList,r);}
        } else {
            changed=1;r=_VptManagerNewStackEntry(s);
            r->mpCallback4=a;r->mpCallback8=b;r->mpObject=obj;
        }
        if(changed) {DSAddListNode(s->mpList,r,0);_VptManagerAttach(s,r);}
    }
    return result;
}
int VptManagerPopCamera(Viewport_t *p,void *obj) {
    int result=1;
    VptManagerStack_t *s=_VptManagerGetStack(p);
    VptManagerStackEntry_t *r=0;
    DSSearchList(s->mpList,0,obj,&r,_VptManagerFindStackEntry);
    VptManagerStackEntry_t *first=(VptManagerStackEntry_t *)DSGetListNode(s->mpList,0);
    if(r) {
        if(r==first) {
            _VptManagerDetach(s,r);
            VptManagerStackEntry_t *next=(VptManagerStackEntry_t *)DSNextListNode(s->mpList,r);
            if(next) _VptManagerAttach(s,next);
        }
        DSDelListNode(s->mpList,r);
    } else result=0;
    return result;
}
int VptManagerReplaceCamera(Viewport_t *p,void *obj,void *other) {
    int result=0;
    VptManagerStack_t *s=_VptManagerGetStack(p);
    VptManagerStackEntry_t *r=0;
    DSSearchList(s->mpList,0,obj,&r,_VptManagerFindStackEntry);
    VptManagerStackEntry_t *first=(VptManagerStackEntry_t *)DSGetListNode(s->mpList,0);
    if(r) {
        result=1;
        if(r==first) result=_VptManagerDetach(s,first);
        if(result) {
            r->mpObject=other;
            if(r==first) result=_VptManagerAttach(s,r);
        }
    }
    return result;
}
void *VptManagerGetCurrentCamera(Viewport_t *p) {
    VptManagerStack_t *s=_VptManagerGetStack(p);
    void *obj=0;
    VptManagerStackEntry_t *r=(VptManagerStackEntry_t *)DSGetListNode(s->mpList,0);
    if(r) obj=r->mpObject;
    return obj;
}
void VptManagerMarketCamInit() {}
int VptManagerIsMarketCamOn() {return 0;}
void VptManagerSetPassIcons(int value) {}
int VptManagerGetPassIcons() {return 1;}
}
