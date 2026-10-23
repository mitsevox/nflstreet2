#include <math.h>
#include "game/Record_8011F4F8.h"
#include "game/fn_801248D4.h"
#include "game/Object_80039F5C.h"
#include "game/Class_80297CE8.h"
#include "game/Object_8017886C.h"
#include "game/State_800FDA58.h"
#include "game/Command_800CEE74.h"
#include "game/Message_800F01CC.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Lookup_8012078C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_801CFE40(float,float);
int fn_801CFFD0(int,int);
float fn_801CFB94(int);
float fn_80260B1C(float);
void fn_80227538(Point_8017886C *,int,float);
void fn_80227690(void *,void *,void *);
void fn_802271A4(Point_8017886C *,Point_8017886C *);
void fn_80227248(Point_8017886C *,Point_8017886C *,float);
float fn_802276E8(Point_8017886C *,Point_8017886C *);
void fn_8022732C(void *,void *,float);
void fn_80227904(Point_8017886C *,void *,void *,float);
float fn_80237260(int);
Point_8017886C fn_80177FFC(int);
Point_8017886C fn_80177FE0(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801783AC(int);
unsigned int fn_80178D18(int);
unsigned int fn_80178D70(int);
int fn_80177F70(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
float fn_80178A5C(void);
int fn_801486A0(void);
void fn_800FE41C(Object_80039F5C *,Object_80039F5C *,Point_8017886C *);
void fn_800FE430(Object_80039F5C *,Object_80039F5C *,Point_8017886C *);
void fn_800FF598(State_800FDA58 *,Object_80039F5C *,Point_8017886C *,int,float);

float fn_8016D9F4(Object_80039F5C *,float,float);
int fn_8012CAAC(Object_80039F5C *);
int fn_8012CAA4(Object_80039F5C *);
void fn_8012CD4C(Object_80039F5C *,Vector_80039F5C *);
float fn_8012CD60(Object_80039F5C *,float);
void fn_80103F80(Object_80137ABC *,Vector_80039F5C *,Vector_80039F5C *,int,Vector_80039F5C *,Object_80039F5C *,float,float);
void fn_80104328(Object_80039F5C *,unsigned char,int *,Vector_80039F5C *,int *);
float fn_80103DD8(Object_80039F5C *,Object_80039F5C *,short *,float);
int fn_8011E9B4(Object_80039F5C *);
int fn_800A7F1C(unsigned char);
unsigned int fn_80100B0C(void);
int fn_80168E00(int,int,unsigned char *);
void fn_8009BD2C(Object_80039F5C *,int *);
void fn_8012430C(float *,int,Object_80039F5C *);
unsigned char fn_801243E0(float *,int);
float fn_801242E0(float *,unsigned int);
unsigned short fn_801BE648(void *p);
int fn_801BE068(void *,void *,void *,unsigned short,void *,float);
void fn_801BE67C(void *,void *,void *,void *);
int fn_8010A2DC(Object_80039F5C *, int, short);
void fn_8010CEB8(Object_80039F5C *,int);
void fn_800C89F0(Object_80039F5C *,int,int,int,float);
void fn_8009D284(Object_80039F5C *,Object_80039F5C *);
extern float lbl_803EA2C4;
extern float lbl_803ECB08,lbl_803EAE84;
extern float lbl_803EAEA4,lbl_803EAEA8,lbl_803EAEAC,lbl_803EAEB0;
extern float lbl_803EAEB4,lbl_803EAEB8,lbl_803EAEBC;
extern unsigned short lbl_803EAE76;
extern float lbl_803EAE78,lbl_803EAE7C;
extern unsigned int lbl_803EAE80;
extern unsigned char lbl_803EAEA0;

void fn_800FE444(Object_80039F5C *p,int angle,Point_8017886C *point,float length)
{
    Point_8017886C delta;
    fn_80227690(&delta,point,&p->mMotion.mPos);
    fn_802270A4(&delta);
    int to = fn_801CFE40(delta.mY,delta.mX);
    int difference = fn_801CFFD0(to,angle);
    if (difference > 0x400000) {
        int limited = (angle - 0x400000) & 0xFFFFFF;
        if (fn_801CFFD0(to,limited) <= 0x3FFFFF) limited = (angle+0x400000)&0xFFFFFF;
        fn_80227538(&delta,limited,length);
    } else {
        fn_80227538(&delta,(angle-0x800000)&0xFFFFFF,((float)difference+(float)difference)*length*0.0000002384185791015625f);
    }
    fn_80227638(point,point,&delta);
}

void fn_800FE564(Object_80039F5C *p,Object_80039F5C *other,Object_80039F5C *target,float limit)
{
    Point_8017886C a,b,av,bv;
    fn_800FE41C(p,other,&a);
    fn_800FE41C(other,p,&b);
    State_800FDA58 *state=(State_800FDA58 *)&p->mUnknown336;
    if (fn_8022781C(&a,&b)>=limit) return;
    fn_800FE430(p,target,&av);
    bv.mX=other->mMotion.mUnknown40;bv.mY=other->mMotion.mUnknown44;
    float base=p->mpState->mId==7?0.5f:2.0f;
    float radius;
    if (base+fn_802270A4(&bv)/lbl_803ECB08 >5.5f) radius=5.5f;
    else radius=base+fn_802270A4(&bv)/lbl_803ECB08;
    if (p->mMotion.mUnknown28!=0.0f && other->mMotion.mUnknown28!=0.0f) {
        radius-=lbl_803EAE78*fn_801CFB94(fn_801CFFD0(p->mMotion.mUnknown32,other->mMotion.mUnknown32));
        if (!(radius>=lbl_803EAE7C)) radius=lbl_803EAE7C;
    }
    float dx=bv.mX-av.mX,dy=bv.mY-av.mY;
    float px=b.mX-a.mX,py=b.mY-a.mY;
    if (!(dx>=0.0000001f)&&!(dx<=-0.0000001f)) dx=0.0f;
    if (!(dy>=0.0000001f)&&!(dy<=-0.0000001f)) dy=0.0f;
    if(dx==0.0f && dy==0.0f)return;
    float aa=dx*dx+dy*dy,bb=px*dx+py*dy;
    float disc=bb*bb-aa*((px*px+py*py-radius*radius)*4.0f);
    if(disc<0.0000001f)return;
    float root=fn_80260B1C(disc);
    if(!(aa>=0.0000001f))aa=0.0000001f;
    float t=(-bb-root)/(aa+aa),second=(-bb+root)/(aa+aa);
    if(!(t>=0.0f) && !(second<0.0f)) t=0.0f;
    float distance=fn_8022781C(&p->mMotion.mPos,&other->mMotion.mPos);
    if(t<0.0f)return;
    if(!(t<state->mUnknown40)) {
        if(t!=state->mUnknown40 || distance>=state->mUnknown44)return;
    }
    fn_80227248(&av,&av,t);fn_80227638(&a,&a,&av);
    fn_80227248(&bv,&bv,t);fn_80227638(&b,&b,&bv);
    if(fn_8022781C(&a,&b)>=radius+0.0000001f)return;
    Point_8017886C delta;
    fn_80227690(&delta,&a,&b);
    state->mUnknown40=t;state->mUnknown44=distance;
    if(!(t<=180.0f))state->mUnknown40=180.0f;
    fn_802271A4(&state->mUnknown32,&delta);
}

void fn_800FE910(Object_80039F5C *p,Point_8017886C *point,float *value,float *distance,float *time)
{
    float d=fn_8022781C(point,&p->mMotion.mPos);*distance=d;
    if(!(d<=15.0f))d=15.0f;*distance=d;
    if(!(*value<=0.0000001f)) {
        float t=d/(lbl_803ECB08 * *value);
        if(!(t<=180.0f))t=180.0f;
        *time=t;
    }
}

void fn_800FE9B4(Object_80039F5C *p,Point_8017886C *point,float *speed)
{
    State_800FDA58 *s=(State_800FDA58 *)&p->mUnknown336;
    if (--s->mUnknown0>0)return;
    float distance,time;
    fn_800FE910(p,point,speed,&distance,&time);
    s->mUnknown0=lbl_803EAE76;
    s->mUnknown40=180.0f;s->mUnknown44=1000.0f;s->mUnknown32.mX=s->mUnknown32.mY=0.0f;
    if(*speed==0.0f)return;
    if(p->mpState->mId==7) {
        Point_8017886C goal=fn_80177FFC(p->mIdBytes[2]);
        if(!(fabsf(p->mMotion.mPos.mY-goal.mY)>=1.5f)) {
            s->mUnknown40=0.0f;
            fn_80227538(&s->mUnknown32,p->mIdBytes[2]==fn_80178308()?0xC00000:0x400000,1.0f);
        }
    }
    if(s->mUnknown40==180.0f) {
        for(int team=0;team<=1;++team) {
            int n=fn_80178D18((unsigned char)team);
            for(int i=0;i<n;++i) {
                Object_80039F5C *other=fn_80039F5C(team,(unsigned short)i);
                if(other!=p)fn_800FE564(p,other,(Object_80039F5C *)point,distance);
            }
        }
    }
}

void fn_800FEB60(Object_80039F5C *p,Point_8017886C *point,float *speed)
{
    float distance,time;fn_800FE910(p,point,speed,&distance,&time);
    State_800FDA58 *s=(State_800FDA58 *)&p->mUnknown336;
    if(s->mUnknown40>=time)return;
    Point_8017886C direction,normal,projected,side,delta;
    fn_80227690(&direction,point,&p->mMotion.mPos);fn_802271A4(&direction,&direction);
    float parallel=s->mUnknown40>=4.5454545f?2.5f/s->mUnknown40:0.55f;
    float perpendicular=s->mUnknown40>=6.1538463f?4.0f/s->mUnknown40:0.65f;
    fn_802271A4(&normal,&s->mUnknown32);
    fn_80227248(&projected,&direction,fn_802276E8(&normal,&direction));
    fn_80227690(&side,&normal,&projected);
    fn_80227248(&projected,&projected,parallel);
    fn_802271A4(&side,&side);fn_80227248(&side,&side,perpendicular);
    fn_80227638(&direction,&direction,&projected);fn_80227638(&direction,&direction,&side);
    fn_80227690(&delta,point,&p->mMotion.mPos);
    int a=fn_801CFE40(delta.mY,delta.mX),b=fn_801CFE40(direction.mY,direction.mX);
    fn_801CFFD0(a,b);fn_801CFFD0(p->mMotion.mUnknown32,b);
    if(!(fn_802270A4(&direction)>=1.0f))fn_802270A4(&direction);
    float factor=!(fn_802270A4(&direction)>=1.0f)?fn_802270A4(&direction):1.0f;
    *speed*=factor;
    fn_80227248(&direction,&direction,distance);fn_80227638(point,&p->mMotion.mPos,&direction);
}

float fn_800FEDBC(State_800FDA58 *s,Object_80039F5C *p,float distance)
{
    Point_8017886C goal=fn_80177FFC(p->mIdBytes[2]);
    int mode=fn_800AD9B4();
    unsigned int minimum=(unsigned int)p->mRatings[4];
    if(minimum<lbl_803EAE80)minimum=lbl_803EAE80;
    if((unsigned int)(s->mUnknown2-1)<2)return s->mUnknown24;
    float desired=s->mUnknown20Float;
    if(mode!=1 && mode!=9 && !(distance<=20.0f))desired=0.72f;
    if(lbl_803EABA4->fn_800C0414()==3 && p->mIdBytes[2]==fn_80178308())desired=1.0f;
    if(!(distance<=4.0f)) {
        if(mode!=2)goto adjust;
        if(fn_801783AC(21))desired=0.72f;
    }
    if(mode==2 && !(fabsf(s->mUnknown8-goal.mX)<=8.0f))desired=1.0f;
adjust:
    if(mode==1)desired=0.5f;
    float difference=desired-s->mUnknown24;
    if(difference<-0.01f)difference=-0.01f;
    else if(!(difference<=0.05f))difference=0.05f;
    s->mUnknown24+=difference;
    float result=s->mUnknown24;
    if(!(distance>=3.0f)) {
        float lower=(float)minimum*0.000549019664f;
        result=result*0.333333343f*distance;
        if(!(result>=lower))result=lower;
    }
    return result;
}

int fn_800FEFD4(Object_80039F5C *p)
{
    Point_8017886C point;
    point.mX=(float)(signed char)p->mpState->mUnknown1*0.25f;
    point.mY=(float)(signed char)p->mpState->mUnknown2*0.5f;
    fn_800FF598((State_800FDA58 *)&p->mUnknown336,p,&point,p->mpState->mUnknown3[0]<<16,-1.0f);
    return 0;
}

int fn_800FF094(Object_80039F5C *p)
{
    int mode=fn_800AD9B4(),special=mode==4;
    State_800FDA58 *s=(State_800FDA58 *)&p->mUnknown336;
    Point_8017886C point={s->mUnknown8,s->mUnknown12},delta;
    fn_800FE444(p,s->mUnknown16,&point,s->mUnknown28);
    float distance=fn_8022781C(&s->mUnknown8,&p->mMotion.mPos);
    float speed=fn_800FEDBC(s,p,distance);
    switch(s->mUnknown2) {
    case 0:
        if(--s->mUnknown0<1) {
            s->mUnknown0=0;fn_800FE9B4(p,&point,&s->mUnknown24);fn_800FEB60(p,&point,&s->mUnknown24);
            fn_80227690(&delta,&point,&p->mMotion.mPos);fn_801CFE40(delta.mY,delta.mX);s->mUnknown2=3;
        }
        break;
    case 1:case 2:
        if(p->mFlags&4) {
            p->mFlags&=~4;p->mMotion.mUnknown28=0.0f;s->mUnknown2=s->mUnknown3Byte;s->mUnknown3Byte=0;
        } else if(fn_801BE648(p->mpUnknown792)!=100) {
            s->mUnknown2=s->mUnknown3Byte;s->mUnknown3Byte=0;
        } else {
            p->mUnknown512.mUnknown14=s->mUnknown2==2?7:6;
            p->mUnknown512.mUnknown0=s->mUnknown2==2?1.5f:1.0f;
            p->mUnknown512.mUnknown4=p->mUnknown512.mUnknown8=s->mUnknown4;
        }
        break;
    case 3:
        if(!(distance<=3.0f)) {
            fn_800FE9B4(p,&point,&s->mUnknown24);fn_800FEB60(p,&point,&s->mUnknown24);speed=s->mUnknown24;
        } else if(special && p->mUnknown560.mFlags.mBytes[0]) {
            s->mUnknown8=p->mMotion.mPos.mX;s->mUnknown12=p->mMotion.mPos.mY;
        }
        if(distance>=(special?lbl_803EAE84:0.05f)) {
            fn_80227690(&delta,&point,&p->mMotion.mPos);
            int angle=fn_801CFE40(delta.mY,delta.mX);
            if(speed==1.0f)p->mUnknown512.mUnknown15=1;
            p->mUnknown512.mUnknown14=fn_80137C48(p)?1:9;
            p->mUnknown512.mUnknown0=speed;p->mUnknown512.mUnknown4=p->mUnknown512.mUnknown8=angle;
        } else {p->mMotion.mUnknown28=0.0f;s->mUnknown2=4;}
        break;
    case 4:
        if(!special && fn_801CFFD0(s->mUnknown16,p->mMotion.mFacing)>0xB60B) {
            if(fn_801CFFD0(p->mMotion.mFacing,s->mUnknown16)>0x155554) {
                float ylimit=p->mIdBytes[2]==fn_80178308()?8.0f:2.0f;
                s->mUnknown4=s->mUnknown16;p->mFlags&=~4;
                if(mode==4 || !fn_80177F70() || !(fabsf(fn_80177FFC(p->mIdBytes[2]).mY-p->mMotion.mPos.mY)<=ylimit)) {
                    s->mUnknown2=1;p->mUnknown512.mUnknown14=6;p->mUnknown512.mUnknown0=1.0f;
                } else {s->mUnknown2=2;p->mUnknown512.mUnknown14=7;p->mUnknown512.mUnknown0=1.5f;}
                p->mUnknown512.mUnknown4=p->mUnknown512.mUnknown8=s->mUnknown16;s->mUnknown3Byte=6;
                break;
            }
            if(((unsigned char *)p->mpState)[4]!=87) {
                p->mUnknown512.mUnknown14=3;p->mUnknown512.mUnknown0=0.0f;
                p->mUnknown512.mUnknown4=p->mUnknown512.mUnknown8=s->mUnknown16;break;
            }
        }
        s->mUnknown2=5;break;
    case 5:
        if(distance<0.05f || special) {p->mMotion.mUnknown28=0.0f;s->mUnknown2=6;}
        else {
            fn_80227690(&delta,&point,&p->mMotion.mPos);
            p->mUnknown512.mUnknown4=fn_801CFE40(delta.mY,delta.mX);
            p->mUnknown512.mUnknown14=3;p->mUnknown512.mUnknown0=speed;p->mUnknown512.mUnknown8=s->mUnknown16;
        }
        break;
    }
    return s->mUnknown2==6;
}

void fn_800FF598(State_800FDA58 *s,Object_80039F5C *p,Point_8017886C *point,int angle,float value)
{
    s->mUnknown0=0;s->mUnknown8=point->mX;s->mUnknown12=point->mY;
    s->mUnknown20Float=0.56f;s->mUnknown16=angle;s->mUnknown24=p->mMotion.mUnknown28/lbl_803ECB08;
    if(value==-1.0f) {
        if(!(fn_8022781C(&p->mMotion.mPos,point)<3.0f)) {
            Point_8017886C delta;fn_80227690(&delta,point,&p->mMotion.mPos);
            if(fn_801CFFD0(fn_801CFE40(delta.mY,delta.mX),angle)<0x3C71C8) {
                float random=fn_80237260(0);value=random+random+2.0f;
            } else value=0.0f;
        } else value=0.0f;
    }
    s->mUnknown28=value;s->mUnknown3Byte=0;s->mUnknown40=s->mUnknown32.mY=s->mUnknown32.mX=0.0f;
    s->mUnknown4=0;s->mUnknown2=0;
    p->mUnknown512.mUnknown14=1;p->mUnknown512.mUnknown4=p->mUnknown512.mUnknown8=p->mMotion.mFacing;
    p->mUnknown512.mUnknown0=s->mUnknown24;
}

void fn_800FF6D8(Object_80039F5C *p)
{
    State_800FDA58 *s=(State_800FDA58 *)&p->mUnknown336;
    p->mMotion.mPos.mX=s->mUnknown8;p->mMotion.mPos.mY=s->mUnknown12;
    p->mMotion.mFacing=s->mUnknown16;p->mpUnknown796->mUnknown8=s->mUnknown16;
    p->mMotion.mUnknown28=0.0f;s->mUnknown0=0;s->mUnknown40=0.0f;s->mUnknown4=0;s->mUnknown2=5;s->mUnknown3Byte=0;
    s->mUnknown20Float=s->mUnknown24=s->mUnknown28=s->mUnknown32.mX=s->mUnknown32.mY=0.0f;
    p->mUnknown512.mUnknown14=0;
    fn_801BE068(p->mpUnknown792,p->mpUnknown796,p->mpUnknown800,74,p,1.0f);
    fn_801BE67C(p->mpUnknown792,p->mpUnknown796,p->mpUnknown800,p);
    p->mUnknown9[0]=1;
}

int fn_800FF7F4(Object_80039F5C *p)
{
    fn_8010A2DC(p,0,-1);
    int result=p->mUnknown560.mUnknown53!=0;
    if(result) {
        p->mUnknown512.mUnknown14=1;p->mUnknown512.mUnknown0=0.0f;
        p->mUnknown512.mUnknown4=p->mUnknown512.mUnknown8=p->mMotion.mFacing;
    }
    return result;
}

void fn_800FF868(Object_80039F5C *p,State_800FFDFC *,Object_80039F5C *other)
{
    Point_8017886C delta;fn_80227690(&delta,&other->mMotion.mPos,&p->mMotion.mPos);
    fn_800C89F0(p,fn_801CFE40(delta.mY,delta.mX)&0xFFFFFF,1,0,0.5f);fn_8009D284(p,other);
}

void fn_800FF8FC(Object_80039F5C *p,float *out)
{
    out[0]=(float)(signed char)p->mpState->mUnknown1*0.0625f;
    out[1]=(float)(signed char)p->mpState->mUnknown2*0.0625f;
    if(fn_801486A0()==2) {
        Vector_80039F5C ball;fn_80137D58(fn_801374BC(),&ball);
        if(!(p->mMotion.mPos.mX<=ball.mX+2.0f))out[0]=fabsf(out[0]);
        else if(p->mMotion.mPos.mX<ball.mX-2.0f || fn_802372EC(0,100)>49)out[0]=-fabsf(out[0]);
        else out[0]=fabsf(out[0]);
    }
}

int fn_800FFA10(Object_80039F5C *p,Object_80039F5C *other)
{
    State_80039F5C *state=other->mpState;
    if(state->mId==18)return 0;
    if(state->mId==1) {
        if(!(fn_8022781C(&p->mMotion.mPos,&other->mMotion.mPos)>9.0f) && p->mMotion.mPos.mY<=other->mMotion.mPos.mY)return 1;
        if(fn_801486A0()==2 && !fn_801783AC(20))return 1;
        Message_800F01CC message;fn_801C1F94(&message,0,4);message.mId=33;fn_800F053C(0,p->mpState,&message,p);return 0;
    }
    if(state->mId==25 && state->mUnknown2==9) {
        Message_800F01CC message;fn_801C1F94(&message,0,4);
        if(state->mUnknown1==p->mIdBytes[1])fn_8010CEB8(p,9);
        else {message.mId=33;fn_800F053C(0,p->mpState,&message,p);}
        return 0;
    }
    return 1;
}

void fn_800FFB4C(Object_80039F5C *p,Object_80039F5C *other,float *value,Point_8017886C *out)
{
    float factor;
    if(*value<=0.0f) {
        factor=((fn_80178A08()+p->mMotion.mPos.mX-1.0f)*2.0f)/(4.5f-1.0f)-1.0f;
        if(factor<-1.0f)factor=-1.0f;
        else if(!(factor<=1.0f))factor=1.0f;
    } else {
        factor=((fn_80178A08()-p->mMotion.mPos.mX-1.0f)*2.0f)/(4.5f-1.0f)-1.0f;
        if(!(factor>=-1.0f))factor=-1.0f;
        else if(!(factor<=1.0f))factor=1.0f;
    }
    Point_8017886C delta={value[0],value[1]};delta.mX*=factor;
    if(fn_801CFFD0(other->mMotion.mUnknown32,0x400000)>0x200000) {
        if(!(delta.mY>=0.0f)) {
            delta.mY*=3.0f;if(!(delta.mY>=-3.0f))delta.mY=-3.0f;
        }
    } else {
        float d=3.0f-fabsf(p->mMotion.mPos.mX-other->mMotion.mPos.mX);
        if(!(d>=0.0f))d=0.0f;
        delta.mY*=d*0.333333343f*4.0f+1.0f;
    }
    fn_80227638(out,&other->mMotion.mPos,&delta);
}

void fn_800FFD2C(Object_80039F5C *p,Point_8017886C *point)
{
    fn_80137B40();Point_8017886C delta;fn_80227690(&delta,point,&p->mMotion.mPos);
    int angle=fn_801CFE40(delta.mY,delta.mX);
    float speed=(fn_802270A4(&delta)-0.3f)*0.5f;
    if(speed<0.0f)speed=0.0f;else if(!(speed<=1.0f))speed=1.0f;
    p->mUnknown512.mUnknown4=p->mUnknown512.mUnknown8=angle;p->mUnknown512.mUnknown14=1;p->mUnknown512.mUnknown0=speed;
    if(!(speed<=0.72f))p->mUnknown512.mUnknown15=1;
}



int fn_80100024(Object_80039F5C *p,int angle,int mode)
{
    unsigned char filter[3]={2,10,11};
    if(!(p->mFlags&0x4000) && mode==2) {
        Vector_80039F5C point;point.mZ=0.0f;
        fn_80227538((Point_8017886C *)&point,angle,lbl_803EAEA4);
        fn_80227638(&point,&point,&p->mMotion.mPos);
        if(!fn_801248D4(p,&p->mMotion.mPos,&point,0,0.0f,1.0f,(Filter_801248D4 *)filter,0))return 0;
    }
    return 1;
}

void fn_8010016C(Object_80039F5C *p,Point_8017886C *point,Object_80039F5C *other,float speed)
{
    float chance=(float)other->mRatings[6]*0.00392156886f;
    if(lbl_803EAEA0 && fn_80237260(0)>=chance)return;
    Point_8017886C middle,delta;
    fn_80227904(&middle,&p->mMotion.mPos,point,0.5f);
    fn_80227690(&delta,point,&other->mMotion.mPos);
    float time=fn_802270A4(&delta)/speed;
    float best=3.4028235e38f;int replace=0;
    int team=fn_80178320();unsigned int n=fn_80178D70(team);
    for(unsigned int i=0;i<n;++i) {
        Object_80039F5C *candidate=fn_80039F5C(team,(unsigned short)i);
        if(fn_8011E9B4(candidate) || candidate->mFlags&0x800)continue;
        Point_8017886C pos={candidate->mMotion.mPos.mX,candidate->mMotion.mPos.mY},future=pos;
        fn_80227690(&delta,point,&pos);float now=fn_802270A4(&delta);
        fn_8022732C(&future,&candidate->mMotion.mUnknown40,time);
        fn_80227690(&delta,point,&future);float later=fn_802270A4(&delta);
        if(!(later<=now))later=now;
        if(!(later>=best)) {
            fn_80227690(&delta,&middle,&pos);replace=now<fn_802270A4(&delta);best=later;
        }
    }
    if(replace)*point=middle;
}

int fn_80100370(Object_80137ABC *ball,Object_80039F5C *p,Vector_80039F5C *out,float value)
{
    Vector_80039F5C velocity={p->mMotion.mUnknown40,p->mMotion.mUnknown44,p->mMotion.mUnknown48};
    Vector_80039F5C pos=p->mMotion.mPos,ballPos;
    State_80039F5C *queue=p->mpState,*state=p->mpState;
    int angle=p->mMotion.mUnknown32;
    float speed=p->mMotion.mUnknown28;
    fn_80137D58(ball,&ballPos);
    if(state->mId==19)speed=fn_8016D9F4(p,1.0f,1.0f);
    else if(state->mId==20) {
        if((unsigned int)(state->mUnknown2-8)<2)angle=fn_8012CAAC(p);else angle=fn_8012CAA4(p);
        fn_8012CD4C(p,&pos);speed=fn_8012CD60(p,0.5f);fn_80227538((Point_8017886C *)&velocity,angle,speed);
    } else if(state->mId==52 && (unsigned int)(state->mUnknown1-4)<2) {
        pos.mY+=3.0f;speed=fn_8016D9F4(p,1.0f,0.72f);fn_80227538((Point_8017886C *)&velocity,angle,speed);
    }
    Vector_80039F5C localPos=pos,localVelocity=velocity;
    fn_80103F80(ball,&localPos,&localVelocity,angle,out,p,speed,value);
    int id=p->mpState->mId;
    if(id==51 || id==52 || id==10 || id==58)return 0;
    if(fn_800F06F4(0,queue,19,0xFFFF)==0xFFFF && fn_800F06F4(0,queue,20,0xFFFF)==0xFFFF)return 0;
    unsigned int index=fn_800F06F4(0,queue,21,0xFFFF);
    if(index==0xFFFF || index<=1)return 0;
    if((unsigned int)(queue[index].mId-19)>1 && queue[index].mId!=51) {
        do {--index;} while((unsigned int)(queue[index].mId-19)>1 && queue[index].mId!=51);
    }
    if(!index)return 0;
    float steps=(float)(int)(fn_8022781C(out,&ballPos)/value);
    int count=(int)steps;
    fn_80104328(p,(unsigned char)(index-1),&count,&pos,&angle);
    float shortened=(float)count;
    if(!(shortened<steps))return 0;
    if(state->mId==20)speed=fn_8012CD60(p,1.0f-shortened/steps);
    else speed=fn_8016D9F4(p,1.0f-shortened/steps,1.0f);
    fn_80227538((Point_8017886C *)&velocity,angle,speed);
    localPos=pos;localVelocity=velocity;
    fn_80103F80(ball,&localPos,&localVelocity,angle,out,p,speed,value);
    return 1;
}

void fn_801007A4(Object_80137ABC *ball,Object_80039F5C *p,Object_80039F5C *other,Vector_80039F5C *out,unsigned char *kind,float value)
{
    int id=*kind;
    if(id==1 || id==7) {
        if(fn_80100370(ball,other,out,value))return;
        *kind=*kind==1?0:6;return;
    }
    if(id!=0 && id!=4 && id!=6) {out->mX=out->mY=out->mZ=0.0f;return;}
    Vector_80039F5C velocity={other->mMotion.mUnknown40,other->mMotion.mUnknown44,other->mMotion.mUnknown48};
    Vector_80039F5C pos=other->mMotion.mPos;
    State_80039F5C *state=other->mpState;
    float speed=other->mMotion.mUnknown28;
    if(state->mId==19) {
        int left=fn_801CFFD0(other->mMotion.mUnknown32,0x800000),right=fn_801CFFD0(other->mMotion.mUnknown32,0);
        if(!(pos.mY>=p->mMotion.mPos.mY-2.0f) && (left<=0x271C70 || right<0x271C71)) {
            speed=fn_8016D9F4(other,1.0f,1.0f);fn_80227538((Point_8017886C *)&velocity,other->mMotion.mUnknown32,speed);
            if(left>0x271C70)pos.mX+=3.0f;else pos.mX-=3.0f;
        }
    } else if(state->mId==51) {
        if(fn_800F06F4(0,state,19,0xFFFF)!=0xFFFF && !(pos.mY<p->mMotion.mPos.mY)) {
            pos.mY+=2.5f;speed=fn_8016D9F4(other,1.0f,1.0f);fn_80227538((Point_8017886C *)&velocity,other->mMotion.mUnknown32,speed);
        }
    } else if(state->mId==52 && (unsigned int)(state->mUnknown1-4)<2) {
        pos.mY+=3.0f;speed=fn_8016D9F4(other,1.0f,1.0f);fn_80227538((Point_8017886C *)&velocity,other->mMotion.mUnknown32,speed);
    }
    Vector_80039F5C localPos=pos,localVelocity=velocity;
    fn_80103F80(ball,&localPos,&localVelocity,other->mMotion.mUnknown32,out,other,speed,value);
}

void fn_80100AA0(Object_80039F5C *p,int,float *a,float *b)
{
    float rating=1.0f-(float)p->mRatings[6]*0.00392156886f;
    *a=1.0f-lbl_803EAEA8*rating;*b=1.0f-lbl_803EAEAC*rating;
}

void fn_80100B34(Object_80039F5C *p,float *out,float *maximum,float a,float b,float c)
{
    if(out && maximum) {
        *maximum=c*(((1.0f-b)*0.2f)+(a+((1.0f-(float)p->mRatings[6]*0.00392156886f)*0.3f+0.05f)))*lbl_803EAEB0;
        *out=fn_80237260(0)* *maximum;
    }
}

void fn_80100BF8(Object_80039F5C *p,Vector_80039F5C *point,Point_8017886C *offset,float,float factor,float skill)
{
    float error=0.0f,amount=0.0f,maximum=0.0f;
    if(fn_800A7F1C(p->mIdBytes[2])==2)return;
    Vector_80039F5C delta;
    fn_802276B4(&delta,point,&p->mMotion.mPos);
    float distance=fn_802270A4(&delta);
    float length=factor*(lbl_803EAEB8-lbl_803EAEB4)+lbl_803EAEB4;
    float ratio=distance/length;
    length*=((float)fn_802372EC(0,7)*0.01f+1.0f);
    if(!(ratio<=0.9f)) {
        error=0.05f;
        if(!(ratio<=1.0f)) {
            error+=0.1f;
            length*=1.0f-(fn_80237260(0)*error)*lbl_803EAEBC;
            distance=length;
            fn_80227538((Point_8017886C *)&delta,fn_801CFE40(delta.mY,delta.mX),length);
            fn_80227638(point,&delta,&p->mMotion.mPos);
        }
    }
    fn_80100B34(p,&amount,&maximum,error,skill,distance);
    fn_80227538((Point_8017886C *)&delta,fn_80100B0C(),amount);
    Point_8017886C combined,unused;
    fn_80227638(&combined,&delta,offset);fn_80227690(&unused,point,offset);
    if(!(fn_802270A4(&combined)<=maximum) && !(amount<=fn_802270A4(offset))) {
        fn_80227538((Point_8017886C *)&delta,fn_801CFE40(combined.mY,combined.mX),maximum);
        fn_80227690(&delta,&delta,offset);
    }
    fn_80227638(point,&delta,point);
    fn_80227690(&delta,point,&p->mMotion.mPos);
    if(fn_802270A4(&delta)>length || !(ratio<=1.0f)) {
        fn_80227538((Point_8017886C *)point,fn_801CFE40(delta.mY,delta.mX),length);
        fn_80227638(point,point,&p->mMotion.mPos);
    }
}

Object_80039F5C *fn_80100EA0(Object_80039F5C *p,int angle)
{
    Object_80039F5C *players[3];float xmin=100.0f,ymin=100.0f,xmax=-100.0f,ymax=-100.0f;
    for(unsigned char i=0;i<3;++i) {
        unsigned char active;
        unsigned int index=fn_80168E00(p->mIdBytes[2],i,&active);
        if(index==255 || !active)players[i]=0;
        else {
            Object_80039F5C *other=fn_80039F5C(p->mIdBytes[2],(unsigned short)index);players[i]=other;
            float x=other->mMotion.mPos.mX,y=other->mMotion.mPos.mY;
            if(!(x>=xmin))xmin=x;if(!(y>=ymin))ymin=y;if(!(x<=xmax))xmax=x;if(!(y<=ymax))ymax=y;
        }
    }
    Point_8017886C center={(xmax-xmin)*0.5f+xmin,(ymax-ymin)*0.5f+ymin};
    int best=0x800000;Object_80039F5C *result=0;
    for(unsigned char i=0;i<3;++i)if(players[i]) {
        Point_8017886C delta;fn_80227690(&delta,&players[i]->mMotion.mPos,&center);
        int difference=fn_801CFFD0(angle,fn_801CFE40(delta.mY,delta.mX));
        if(difference<best) {result=players[i];best=difference;}
    }
    return result;
}

void fn_80101064(Object_80039F5C *p)
{
    int team=fn_80178320(),n=fn_80178D18(team);
    for(unsigned int i=0;(int)i<n;++i) {
        Object_80039F5C *other=fn_80039F5C(team,(unsigned char)i);
        Point_8017886C delta;fn_80227690(&delta,&other->mMotion.mPos,&p->mMotion.mPos);
        if(!(fn_802270A4(&delta)>=2.5f)) {
            Record_800B15FC *record=fn_800B15FC();fn_8009BD2C(other,&record->mUnknown0);
            record->mUnknownC=p->mMotion.mPos.mX;record->mUnknown10=p->mMotion.mPos.mY;record->mUnknown14=33;
            fn_800B1508();return;
        }
    }
}

void fn_80101130(Object_80039F5C *p,Object_80039F5C *other,unsigned short *out)
{
    float values[8];fn_8012430C(values,3,p);
    unsigned char best=fn_801243E0(values,-1);
    int motionAngle=p->mMotion.mUnknown32;
    Lookup_8012078C *lookup=fn_8012078C();
    Object_80039F5C *receiver=fn_80039F5C(fn_80178320(),lookup->mpUnknown4[1]);
    Point_8017886C delta;fn_80227690(&delta,&other->mMotion.mPos,&p->mMotion.mPos);
    unsigned int octant=((unsigned int)fn_801CFE40(delta.mY,delta.mX)+0x100000)>>21&7;
    int diff=fn_801CFFD0(motionAngle,0x400000);
    int chosen=(values[best]==0.0f || values[(best+1)&7]==0.0f || values[(best+7)&7]==0.0f) &&
        (values[octant]>=3.0f || values[(octant+1)&7]>=4.0f || !(values[(octant+7)&7]<4.0f)) && diff<0x4AAAAB;
    if(!chosen) {
        float a=fn_80178A5C(),b=fn_80178A08(),c=fn_80178A5C();
        float x=p->mMotion.mPos.mX;
        float d=fn_80178A5C(),e=fn_80178A08(),f=fn_80178A5C();
        float x2=p->mMotion.mPos.mX;
        float left=fn_801242E0(values,0),right=fn_801242E0(values,4);
        chosen=((x2<-((e-f)*0.25f+d) && left>right*1.45f) || (x>(b-c)*0.25f+a && !(right<=left*1.45f))) && diff<0xE38E3;
        if(!chosen) {
            Point_8017886C goal=fn_80177FE0();
            if(goal.mY<=p->mMotion.mPos.mY)return;
            *out=12;return;
        }
    }
    if((((unsigned int)motionAngle+0x100000)>>21&7)!=2)return;
    if(p->mMotion.mPos.mY<=receiver->mMotion.mPos.mY)return;
    if(fn_80178A2C()-15.0f<=p->mMotion.mPos.mY)return;
    *out=5;
}

void fn_80101408(Object_80039F5C *p,Point_8017886C *point,unsigned int *angle)
{
    if(point && angle) {
        point->mX=fn_80178A08()+14.0f;
        point->mY=fn_80177FE0().mY+10.0f;
        if(!(p->mMotion.mPos.mX>=0.0f))point->mX=-point->mX;
        fn_80227690(point,point,&p->mMotion.mPos);
        *angle=(fn_801CFE40(point->mY,point->mX)-p->mMotion.mFacing)&0xFFFFFF;
    }
}

void fn_801014C8(Object_80039F5C *p,Point_8017886C *point,unsigned int *angle)
{
    if(point && angle) {
        Point_8017886C target;target.mX=0.0f;
        target.mY=(fn_80178A2C()+fn_80178A44())*0.5f;
        fn_80227690(point,&target,&p->mMotion.mPos);
        *angle=(fn_801CFE40(point->mY,point->mX)-p->mMotion.mFacing)&0xFFFFFF;
    }
}

void fn_80101568(Object_80039F5C *p,unsigned char *kind,Point_8017886C *point,unsigned int *angle)
{
    Vector_80039F5C target={0.0f,0.0f,0.0f};
    if(point && angle && kind) {
        Object_80137ABC *ball=fn_80137C48(p);
        State_800FDA58 *state=(State_800FDA58 *)&p->mUnknown336;
        Record_8011F4F8 *record=fn_8011F4F8(state->mUnknown3Byte);
        Object_80039F5C *other=fn_80039F5C(p->mIdBytes[2],(unsigned char)record->mUnknownA[0]);
        float speed;
        if(!state->mUnknown0Bytes[0])speed=fn_80103DD8(p,other,&record->mUnknown8,0.9f);
        else speed=lbl_803EA2C4*0.3f;
        if(!ball) {target.mX=other->mMotion.mPos.mX;target.mY=other->mMotion.mPos.mY;}
        else fn_801007A4(ball,p,other,&target,kind,speed);
        fn_80227690(point,&target,&p->mMotion.mPos);fn_801CFE40(point->mY,point->mX);
        *angle=(fn_801CFE40(point->mY,point->mX)-p->mMotion.mFacing)&0xFFFFFF;
        if(*angle>0x1000000)*angle-=0x1000000;
    }
}

void fn_801016A4(Object_80039F5C *p,unsigned char *kind,Point_8017886C *point,unsigned int *angle)
{
    if(!p || !kind || !point || !angle)return;
    *angle=0;point->mX=point->mY=0.0f;
    switch(*kind) {
    case 2:case 5:*angle=0;return;
    case 3:fn_80101408(p,point,angle);return;
    case 8:fn_801014C8(p,point,angle);return;
    case 0:case 1:case 4:case 6:case 7:fn_80101568(p,kind,point,angle);return;
    }
}

void fn_8010176C(Object_80039F5C *p,int mode,Point_8017886C *point)
{
    if(!p)return;
    if(mode==4) {p->mUnknown1008.mUnknown1=fn_801BE648(p->mpUnknown792)==69?10:1;return;}
    if(mode==2) {p->mUnknown1008.mUnknown1=3;return;}
    if(mode==5) {p->mUnknown1008.mUnknown1=4;return;}
    State_800FDA58 *state=(State_800FDA58 *)&p->mUnknown336;
    Record_8011F4F8 *record=fn_8011F4F8(state->mUnknown3Byte);
    Object_80039F5C *other=0;
    if(record && (unsigned char)record->mUnknownA[0]!=15)other=fn_80039F5C(p->mIdBytes[2],(unsigned char)record->mUnknownA[0]);
    float distance;
    if(other) {
        Point_8017886C goal=fn_80177FE0();
        if(!(other->mMotion.mPos.mY>=goal.mY+24.0f) && fn_802270A4(point)<32.0f)distance=24.0f;
        else distance=fn_802270A4(point);
    } else distance=fn_802270A4(point);
    p->mUnknown1008.mUnknown1=distance<=24.0f?5:1;
}

}
