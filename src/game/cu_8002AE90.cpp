#include <string.h>
#include "engine/cu_80227F14.h"
#include "game/fn_80238174.h"
#include "game/fn_801C3660.h"
#include "game/fn_801C68FC.h"

struct Record_8002AE90 {
    void *mpObject;
    int (*mpCallback4)(Object_80228224 *, void *);
    int (*mpCallback8)(Object_80228224 *, void *);
};
struct State_8002AE90 { Object_80228224 *mpObject; void *mpList; };
extern "C" {
void *fn_801C6A20(void *);
void *fn_801C6B4C(void *, void *);
void fn_801C6BC0(void *, Record_8002AE90 *);
void fn_801C6C0C(void *, void *);
void *fn_801C6C84(void *, void *);
int fn_801C6DCC(void *, void *, void *, Record_8002AE90 **, int (*)(Record_8002AE90 *,void *,Record_8002AE90 **));
void fn_801C36B0(Object_80228224 *, void *);
static State_8002AE90 *lbl_803EA348 = 0;

int fn_8002AE90(void *p, int a) {
    State_8002AE90 *s=(State_8002AE90 *)p;
    s->mpList=fn_801C68FC(1,0,5,12,0,0);
    s->mpObject=0;
    return 0;
}
int fn_8002AEE4(void *p,int a) {
    State_8002AE90 *s=(State_8002AE90 *)p;
    fn_801C69E4(s->mpList);
    s->mpObject=0;
    s->mpList=0;
    return 0;
}
int fn_8002AF24(State_8002AE90 *s,Record_8002AE90 *r) {
    int result=1;
    if(r->mpCallback4) result=r->mpCallback4(s->mpObject,r->mpObject);
    else fn_801C3660(s->mpObject,r->mpObject);
    return result;
}
int fn_8002AF80(State_8002AE90 *s,Record_8002AE90 *r) {
    int result=1;
    if(r->mpCallback8) result=r->mpCallback8(s->mpObject,r->mpObject);
    else {
        fn_801C36B0(s->mpObject,r->mpObject);
        if(fn_802286B4(s->mpObject)) result=0;
    }
    return result;
}
Record_8002AE90 *fn_8002AFF4(State_8002AE90 *s) {
    Record_8002AE90 *r=(Record_8002AE90 *)fn_801C6A20(s->mpList);
    r->mpCallback4=0;r->mpCallback8=0;r->mpObject=0;
    return r;
}
State_8002AE90 *fn_8002B02C(Object_80228224 *p) {
    if(!lbl_803EA348->mpObject) lbl_803EA348->mpObject=p;
    return lbl_803EA348;
}
int fn_8002B048(Record_8002AE90 *r,void *p,Record_8002AE90 **out) {
    if(r->mpObject==p) {*out=r;return 0;}
    return -1;
}
int fn_8002B068(void *p,void *q) { return 0; }
int fn_8002B070(void *p,void *data) {
    State_8002AE90 *s=(State_8002AE90 *)p;
    short count=0;
    void *r=fn_801C6B4C(s->mpList,0);
    while(r) {count++;r=fn_801C6C84(s->mpList,r);}
    *(short *)data=count;data=(char *)data+2;
    for(short remaining=count;remaining>0;remaining--) {
        r=fn_801C6B4C(s->mpList,0);
        for(short i=1;i<remaining;i++) r=fn_801C6C84(s->mpList,r);
        memcpy(data,r,12);data=(char *)data+12;
    }
    return 1;
}
int fn_8002B13C(void *p,void *data) {
    State_8002AE90 *s=(State_8002AE90 *)p;
    void *r;
    while((r=fn_801C6B4C(s->mpList,0))!=0) fn_801C6C0C(s->mpList,r);
    short count=*(short *)data;data=(char *)data+2;
    while(count>0) {
        r=fn_801C6A20(s->mpList);
        memcpy(r,data,12);data=(char *)data+12;
        fn_801C6AA4(s->mpList,r,0);count--;
    }
    return 1;
}
int fn_8002B1DC(void *p) {return 62;}
void fn_8002B1E4() {
    void *h=fn_80238174(0,(void **)&lbl_803EA348,8,0,0x7670746D);
    fn_80238234(h,fn_8002AE90,fn_8002AEE4,0,fn_8002B068);
    fn_80238248(h,fn_8002B070,fn_8002B1DC,fn_8002B13C);
    fn_802381E0(h);
}
void fn_8002B270() {
    State_8002AE90 *s=fn_8002B02C(0);
    Record_8002AE90 *r=(Record_8002AE90 *)fn_801C6B4C(s->mpList,0);
    if(r && fn_802286B4(s->mpObject)!=r->mpObject) fn_801C3660(s->mpObject,r->mpObject);
}
void fn_8002B2D0() {}
int fn_8002B2D4(Object_80228224 *p,void *obj,int (*a)(Object_80228224 *,void *),int (*b)(Object_80228224 *,void *)) {
    int changed=0;
    State_8002AE90 *s=fn_8002B02C(p);
    int result=1;
    Record_8002AE90 *r=0;
    fn_801C6DCC(s->mpList,0,obj,&r,fn_8002B048);
    Record_8002AE90 *first=(Record_8002AE90 *)fn_801C6B4C(s->mpList,0);
    if(first && first!=r) result=fn_8002AF80(s,first);
    if(result) {
        if(r) {
            if(r!=first) {changed=1;fn_801C6BC0(s->mpList,r);}
        } else {
            changed=1;r=fn_8002AFF4(s);
            r->mpCallback4=a;r->mpCallback8=b;r->mpObject=obj;
        }
        if(changed) {fn_801C6AA4(s->mpList,r,0);fn_8002AF24(s,r);}
    }
    return result;
}
int fn_8002B3DC(Object_80228224 *p,void *obj) {
    int result=1;
    State_8002AE90 *s=fn_8002B02C(p);
    Record_8002AE90 *r=0;
    fn_801C6DCC(s->mpList,0,obj,&r,fn_8002B048);
    Record_8002AE90 *first=(Record_8002AE90 *)fn_801C6B4C(s->mpList,0);
    if(r) {
        if(r==first) {
            fn_8002AF80(s,r);
            Record_8002AE90 *next=(Record_8002AE90 *)fn_801C6C84(s->mpList,r);
            if(next) fn_8002AF24(s,next);
        }
        fn_801C6C0C(s->mpList,r);
    } else result=0;
    return result;
}
int fn_8002B494(Object_80228224 *p,void *obj,void *other) {
    int result=0;
    State_8002AE90 *s=fn_8002B02C(p);
    Record_8002AE90 *r=0;
    fn_801C6DCC(s->mpList,0,obj,&r,fn_8002B048);
    Record_8002AE90 *first=(Record_8002AE90 *)fn_801C6B4C(s->mpList,0);
    if(r) {
        result=1;
        if(r==first) result=fn_8002AF80(s,first);
        if(result) {
            r->mpObject=other;
            if(r==first) result=fn_8002AF24(s,r);
        }
    }
    return result;
}
void *fn_8002B550(Object_80228224 *p) {
    State_8002AE90 *s=fn_8002B02C(p);
    void *obj=0;
    Record_8002AE90 *r=(Record_8002AE90 *)fn_801C6B4C(s->mpList,0);
    if(r) obj=r->mpObject;
    return obj;
}
void fn_8002B598() {}
int fn_8002B59C() {return 0;}
void fn_8002B5A4(int value) {}
int fn_8002B5A8() {return 1;}
}
