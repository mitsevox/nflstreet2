#include "game/Class_80297C60.h"
#include "game/Class_80148A58.h"
#include "game/Step_800C4460.h"
#include "game/fn_80177FE0.h"
#include "game/fn_8007F828.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/Record_800A0624.h"
#include "game/Block_8030E6E8.h"

extern "C" {
int fn_80178308(void);
unsigned char fn_80178348(void);
float fn_80178A2C(void);
float fn_80178A08(void);
int fn_80177F70(void);
int fn_801486A0(void);
int fn_80025708(void);
extern Block_8030E6E8 lbl_8030E6E8;
}

extern "C" void fn_800A1620(Object_8017886C *out)
{
    float y=fn_80177FE0().mY,finalY=out->mUnknown08.mY;
    if(fn_80178308()!=fn_80178348())y=-y;
    float distance;
    if(out->mUnknown1D==0)distance=finalY-y;
    else distance=fn_80178A2C()-y;
    if(out->mUnknown1D && !(distance>=0.0f))distance=0.0f;
    out->mUnknown14=distance;
}

extern "C" {
int fn_80178AE0(void);
int fn_801485D4(void);
extern Block_802D7C64 lbl_802D7C64[];
}

extern "C" void fn_800A1738(Object_8017886C *out)
{
    int mode=fn_80178AE0();
    if(mode!=2) {
        if(fn_80178308()==1 ? fn_80178AE0()==1 : fn_80178AE0()==0)lbl_802D7C64[0].mUnknown0=13;
        else lbl_802D7C64[0].mUnknown0=16;
        return;
    }
    switch(out->mUnknown1D) {
    case 3:
    case -3:lbl_802D7C64[0].mUnknown0=9;break;
    case -2:lbl_802D7C64[0].mUnknown0=11;break;
    case 2:
        if(fn_80178308()==fn_80178348())lbl_802D7C64[0].mUnknown0=1;
        else lbl_802D7C64[0].mUnknown0=15;
        break;
    case 6:
    case 9:
        if(fn_80178308()==fn_80178348())lbl_802D7C64[0].mUnknown0=0;
        else lbl_802D7C64[0].mUnknown0=14;
        break;
    case 0:
        if(out->mUnknown04==1) {
            if(out->mUnknown18&0x800)lbl_802D7C64[0].mUnknown0=10;
            else if(fn_80177F70()==6)lbl_802D7C64[0].mUnknown0=2;
            else if(fn_80178308()!=fn_80178348())lbl_802D7C64[0].mUnknown0=9;
            else if(out->mUnknown18&0x100)lbl_802D7C64[0].mUnknown0=9;
            else lbl_802D7C64[0].mUnknown0=3;
        } else if(out->mUnknown14>1e-7f) {
            if(out->mUnknown14>30.0f)lbl_802D7C64[0].mUnknown0=4;
            else if(out->mUnknown14>15.0f)lbl_802D7C64[0].mUnknown0=5;
            else lbl_802D7C64[0].mUnknown0=6;
        } else if((out->mUnknown18&0x18000)==0x8000)lbl_802D7C64[0].mUnknown0=12;
        else {
            Vector_80039F5C pos;
            fn_80137D58(fn_801374BC(),&pos);
            if(fn_80137B40()==fn_80039F5C(fn_80178348(),0) && pos.mX>-fn_80178A08() && pos.mX<fn_80178A08() &&
                pos.mY<fn_80177FE0().mY)lbl_802D7C64[0].mUnknown0=8;
            else lbl_802D7C64[0].mUnknown0=7;
        }
        break;
    default:lbl_802D7C64[0].mUnknown0=6;break;
    }
    if(fn_801485D4() && fn_801486A0()==2) {
        switch(lbl_802D7C64[0].mUnknown0) {
        case 4:
        case 5:
        case 6:lbl_802D7C64[0].mUnknown0=8;break;
        }
    }
}

extern "C" {
Object_8017886C *fn_800A16C8(Object_8017886C *,Object_8017886C *,unsigned char *);
void fn_800B14E4(void);
int fn_800BA6F8(void);
void fn_80094BBC(Object_8017886C *);
void fn_80178878(const Object_8017886C *);
void fn_800A14E4(Object_8017886C *,unsigned char);
int fn_800C8774(int);
void fn_80178F90(void);
void fn_800D6F08(void);
void fn_8017C1F0(Object_8017886C *);
void fn_80178CD8(int);
void fn_80177D54(void);
void fn_80177C50(int);
void fn_80177C44(int);
void fn_8009D8CC(int);
void fn_80177F88(int);
void fn_801782B0(void);
void fn_801782F4(float);
void fn_800BAAE4(void);
void fn_80173A50(Object_8017886C *);
void fn_800B2304(void);
void fn_800B9A9C(Class_80297C60 *);
void fn_801789F8(void);
void fn_8016BAAC(void);
int fn_800539F8(void);
void fn_80064EFC(int,int,int);
void fn_800AE380(void);
unsigned int fn_800B2314(void);
void fn_8009BA9C(Object_8017886C *);
void fn_8002C9A8(void *,int,int);
void fn_8017D764(void);
void fn_800A1A84(Object_8017886C *,Object_8017886C *);
void fn_8017813C(Point_8017886C);
int fn_800B2320(void);
void fn_800B2564(Object_8017886C *,Object_8017886C *);
unsigned int fn_8009D990(int);
void *fn_800B9A44(Class_80297C60 *);
void fn_800B9A6C(Class_80297C60 *,void *);
int fn_800A1470(void *);
int fn_800A1478(void *);
void fn_800A14A8(void *);
extern void *lbl_803EA368;
}

extern "C" void fn_800A1C74(Object_8017886C *result,Object_8017886C *input)
{
    unsigned char update=1;
    Object_8017886C *value=result;
    result=fn_800A16C8(result,input,&update);
    if(lbl_802D7C64[0].mUnknown5==1) {
        fn_800B14E4();lbl_802D7C64[0].mUnknown5=0;
    } else {
        if(!fn_800BA6F8()) {
            if(result==input)fn_80094BBC(value);
            if(result->mUnknown18&0x2000 || result==input)fn_80178878(result);
        }
        fn_800A14E4(result,update);
        if(result->mUnknown18&8 && result->mUnknown1D==2 && fn_801486A0()!=4 && fn_8007F828(14)==0) {
            int score=fn_800C8774(fn_80178308());
            if(score>=fn_8007F828(1)) {
                Vector_80039F5C pos={0};
                fn_80137D58(fn_801374BC(),&pos);
                fn_80067DB8(0x5E,&pos,fn_80178308(),0,0);
            }
        }
        fn_80178F90();fn_800D6F08();
        if(update==1)fn_8017C1F0(result);
        if(result->mUnknown18&0x80)fn_80178CD8(((result->mUnknown18^4)>>2)&1);
        fn_80178AE0();
        if(fn_80177F70()==6)fn_80177D54();
        if((result->mUnknown18&6)!=6) {
            if(result->mUnknown18&2) {fn_80177C50(1);fn_80177C44(0);}
            if(result->mUnknown18&4) {
                if(fn_80178AE0()==2)fn_80177C50((result->mUnknown18&0x880)==0);
                fn_8009D8CC(1);fn_80177C44(1);result->mUnknown18|=0x40;
            }
        }
        if(result->mUnknown18&0x10) {
            fn_80177C50(1);fn_80177C44(0);fn_8009D8CC(1);fn_80177C44(1);
        }
        if(result->mUnknown18&0x40 && fn_80177F70()>0 && fn_80177F70()<6) {
            fn_80177F88(1);
            float line=fn_80177FE0().mY+20.0f;
            if(!(line<=fn_80178A2C()))fn_80178A2C();
            fn_801782B0();
        }
        if(fn_80177F70()==6)fn_801782F4(fn_80178A2C());
        if(fn_800BA6F8())fn_800BAAE4();
        fn_80173A50(result);fn_800B14E4();fn_800B2304();fn_800B9A9C(lbl_803EAB84);
        fn_801789F8();fn_8016BAAC();
        if(fn_800539F8())fn_80064EFC(3,22,-1);
        fn_800AE380();
        if(result->mUnknown18&0x2000 || fn_800B2314()&1)fn_8009BA9C(result);
        else fn_8002C9A8(lbl_803EA368,3,0);
        fn_8017D764();
        if(fn_801486A0()!=15)fn_80148A58()->vfn_14();
        lbl_802D7C64[0].mUnknown4=1;
    }
}

extern "C" void fn_800A1FEC(Object_8017886C *result,Object_8017886C *value)
{
    Step_800C4460 *step;
    fn_800A1A84(result,value);
    Point_8017886C pos=result->mUnknown08;
    fn_8017813C(pos);
    if(fn_800B2320())fn_800B2564(result,value);
    if(!fn_80025708() || fn_8009D990(4)) {
        step=(Step_800C4460 *)fn_800B9A44(lbl_803EAB84);
        step->mUnknownC=45.0f;
        fn_800B9A6C(lbl_803EAB84,step);
    }
    step=(Step_800C4460 *)fn_800B9A44(lbl_803EAB84);
    step->mpCallback0=fn_800A1470;
    step->mpCallback4=fn_800A1478;
    step->mpCallback8=fn_800A14A8;
    step->mContext.mpFirst=result;step->mContext.mpSecond=value;
    fn_800B9A6C(lbl_803EAB84,step);
}

extern "C" void fn_800A21BC(void)
{
    lbl_8030E6E8.mUnknown28=17.5f;
    lbl_8030E6E8.mUnknown2C=30.0f;
    lbl_8030E6E8.mUnknown30=40.0f;
    lbl_8030E6E8.mUnknown34=1.0f;
    lbl_8030E6E8.mFloat38=20.0f;
    lbl_8030E6E8.mUnknown8B4[5]=1;
    lbl_8030E6E8.mUnknown8B4[0]=1;
    lbl_8030E6E8.mUnknown6C[1]=7;
    lbl_8030E6E8.mUnknown6C[2]=1;
    lbl_8030E6E8.mUnknown8C4=4;
}

extern "C" void fn_800A2228(void)
{
    lbl_8030E6E8.mUnknown28=20.0f;
    lbl_8030E6E8.mUnknown2C=40.0f;
    lbl_8030E6E8.mUnknown30=50.0f;
    lbl_8030E6E8.mUnknown34=1.0f;
    lbl_8030E6E8.mFloat38=20.0f;
    lbl_8030E6E8.mUnknown8B4[2]=1;
    lbl_8030E6E8.mUnknown8B4[0]=1;
    lbl_8030E6E8.mUnknown8C4=0;
}

extern "C" void fn_800A227C(void)
{
    lbl_8030E6E8.mUnknown28=17.5f;
    lbl_8030E6E8.mUnknown2C=30.0f;
    lbl_8030E6E8.mUnknown30=40.0f;
    lbl_8030E6E8.mUnknown34=1.0f;
    lbl_8030E6E8.mFloat38=20.0f;
    lbl_8030E6E8.mUnknown8B4[3]=1;
    lbl_8030E6E8.mUnknown6C[6]=28;
    lbl_8030E6E8.mUnknown6C[7]=6;
    lbl_8030E6E8.mUnknown8C4=3;
}

extern "C" void fn_800A22E4(void)
{
    lbl_8030E6E8.mUnknown28=17.5f;
    lbl_8030E6E8.mUnknown2C=30.0f;
    lbl_8030E6E8.mUnknown30=40.0f;
    lbl_8030E6E8.mUnknown34=1.0f;
    lbl_8030E6E8.mFloat38=20.0f;
    lbl_8030E6E8.mUnknown8B4[0]=1;
    lbl_8030E6E8.mUnknown8C4=1;
}
