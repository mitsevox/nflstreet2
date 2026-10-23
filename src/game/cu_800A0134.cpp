#include <math.h>
#include "game/Class_80297AB8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80148A58.h"
#include "game/Step_800C4460.h"
#include "game/Record_800B15FC.h"
#include "game/fn_800670B4.h"
#include "game/fn_80177FE0.h"
#include "game/fn_8007F828.h"
#include "game/fn_801C1F94.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/Record_800A0624.h"
#include "game/Block_8030E6E8.h"
#include "game/fn_80238174.h"
#include "game/cu_80026BB0.h"

extern "C" {
unsigned int fn_8009FFA4(void);
unsigned int fn_8009FFC4(void);
void fn_8009FF94(unsigned int);
int fn_80178320(void);
void fn_8017D7C4(const char *);
void *fn_8023816C(void *);
void fn_800A039C(Class_80297AB8 *);
int fn_800A937C(void);
int fn_800A9680(void);
void fn_800A9688(void);
int fn_800A96D0(void);
void fn_800A9478(int);
void fn_8017D678(void);
void fn_8009A6D8(void);
void fn_80120720(unsigned int);
void fn_800FB314(void);
void fn_800FB768(void);
void fn_8009E138(void);
void fn_800A615C(void);
void fn_800718A0(void);

void fn_8016EC40(void);
void fn_8003A3F4(int,int);
void fn_80148154(void);
void fn_800A61A8(void);
extern unsigned char lbl_803EA9E0;
extern void **lbl_803EA9E8;
extern float lbl_80297D94[];
extern float lbl_80297DBC[];
extern float lbl_80297DE4[];
extern float lbl_80297E0C[];
extern float lbl_80297E34[];
extern float lbl_80297E5C[];
extern Block_8030E6E8 lbl_8030E6E8;
}

extern "C" float fn_800A0134(int team,int unused,int index)
{
    float result=1.0f;
    unsigned int kind=fn_8009FFA4();
    if(team==fn_80178320()) {
        switch(kind) {
        case 1:result=lbl_80297D94[index];break;
        case 2:result=lbl_80297DBC[index];break;
        case 4:result=lbl_80297DE4[index];break;
        case 5:result=lbl_80297E0C[index];break;
        case 6:result=lbl_80297E34[index];break;
        case 7:result=lbl_80297E5C[index];break;
        }
    }
    return result;
}

extern "C" void fn_800A02B4(void)
{
    if(fn_8009FFC4()==1) {
        fn_8009FF94(3);
        if(lbl_803EA9E0)fn_8017D7C4("QB LOS Run Modif.");
    }
}

void Class_80297AB8::vfn_01()
{
    void *handle=fn_80238174(0,(void **)&lbl_803EA9E8,80,0,0x64706C79);
    fn_8023816C(handle);
    fn_802381E0(handle);
}

void Class_80297AB8::vfn_02()
{
    fn_800A039C(0);
}

void Class_80297AB8::vfn_04(float dt)
{
    if(fn_800A937C()) {
        if(!fn_800A9680())fn_800A9688();
        else if(!fn_800A96D0())fn_800A9478(0);
    } else {
        fn_8017D678();
        fn_8009A6D8();
        fn_80120720((unsigned int)dt);
        fn_800FB314();
        fn_800FB768();
        fn_8009E138();
        fn_800A615C();
        fn_800718A0();
        fn_80137B40();
        fn_8016EC40();
    }
    fn_8003A3F4(0,0);
    fn_8003A3F4(0,1);
}

void Class_80297AB8::vfn_05()
{
    fn_80148154();
    fn_80027230(lbl_803EA9E8);
    fn_80027358(-1);
    fn_800A61A8();
}


extern "C" {
unsigned char fn_80178348(void);
int fn_80178308(void);
int fn_80178360(void);
int fn_8011F354(void);
int fn_8011F1CC(void);
int fn_8011F524(void);
float fn_8011F4D4(void);
int fn_8011F37C(void);
Record_80067338 *fn_80168730(int);
void fn_8016B144(int,int);
void fn_8016B210(int,int);
void fn_8016B22C(int,signed char);
void fn_8016B248(int,Point_8017886C,Point_8017886C,int);
void fn_8016B2B8(int,float);
void fn_8016B2E8(int,unsigned char);
void fn_8016B310(int,unsigned char);
void fn_8016B32C(int,unsigned char);
void fn_8016B348(int,unsigned char);
int fn_8009E9C8(void);
void fn_8009BD2C(Object_80039F5C *,int *);
void fn_80076D4C(int);
void fn_80076D6C(int);
void fn_80076D8C(int);
void fn_800A061C(Record_800A0624 *,int *,int);
float fn_80178A2C(void);
float fn_80178A08(void);
void fn_8017CA94(unsigned short,int);
void fn_800D4888(int);
int fn_801486A0(void);
}

extern "C" void fn_800A06F4(Record_800A0624 *state,Object_8017886C *out)
{
    int team=fn_80178348();
    bool special=false,placed=false,tracked=false;
    Point_8017886C point=fn_80177FE0();
    unsigned short count=fn_800B15D4();
    int ref=0;
    if(count>1 && !fn_8011F354()) {
        fn_8016B144(team,fn_80168730(team)->mUnknown4);
        fn_8016B210(team,fn_80168730((unsigned char)(team^1))->mUnknown4);
        if(fn_8011F1CC())fn_8016B310(team,2);
        else {
            fn_8016B310(team,1);
            if(fn_8011F524())fn_8016B2E8(team,6);
            Point_8017886C to={fn_8011F4D4(),point.mY};
            fn_8016B248(team,point,to,fn_8009E9C8());
        }
        fn_8016B32C(team,fn_8011F37C());
        tracked=true;
        fn_8016B348(team,0);
    }
    for(unsigned short i=0;i<count;++i) {
        Record_800B15FC *e=fn_800B1648(i);
        switch(e->mUnknown14) {
        case 2:
            if(tracked)fn_8016B2B8(team,out->mUnknown08.mY-point.mY);
            break;
        case 3:
            state->mUnknown0=1;
            out->mUnknown18|=0x2000;
            state->mUnknown4=2;
            fn_8009BD2C(0,&ref);
            break;
        case 4:case 8:
            ref=e->mUnknown0;state->mUnknown4=1;state->mWord8=0;
            if(tracked)fn_8016B22C(team,fn_8009BCE8(&e->mUnknown0)->mIdBytes[1]);
            break;
        case 5:
            ref=e->mUnknown0;state->mUnknown4=4;special=true;
            out->mUnknown18|=0x8000;
            if(!(fabsf(e->mUnknownC-point.mX)<=4.0f))fn_8016B2E8(team,5);
            if(tracked && e->mUnknown8)fn_8016B22C(team,((Object_80039F5C *)e->mUnknown8)->mIdBytes[1]);
            break;
        case 6:
            ref=e->mUnknown0;state->mUnknown4=1;state->mWord8=0;
            fn_80076D6C(e->mUnknown0);out->mUnknown18|=0x10000;
            if(tracked) {
                Point_8017886C to={e->mUnknownC,e->mUnknown10};
                fn_8016B248(team,point,to,fn_8009E9C8());
                fn_8016B22C(team,fn_8009BCE8(&e->mUnknown0)->mIdBytes[1]);
            }
            break;
        case 7:
            ref=e->mUnknown0;state->mUnknown4=3;state->mWord8=1;state->mFloat14=e->mUnknown10;
            break;
        case 10:case 13:
            ref=e->mUnknown0;state->mUnknown4=1;state->mWord8=0;
            if(e->mUnknown14==13){out->mUnknown08.mX=e->mUnknownC;out->mUnknown08.mY=e->mUnknown10;}
            break;
        case 11:case 31:
            {out->mUnknown08.mX=e->mUnknownC;out->mUnknown08.mY=e->mUnknown10;}break;
        case 16:out->mUnknown18|=0x4000;break;
        case 17:ref=e->mUnknown0;break;
        case 18:case 55:
            state->mWord8=1;state->mUnknown4=5;state->mFloat14=e->mUnknown10;
            {out->mUnknown08.mX=e->mUnknownC;out->mUnknown08.mY=e->mUnknown10;}
            if(tracked)fn_8016B2E8(team,2);
            break;
        case 19:
            ref=e->mUnknown0;fn_80076D8C(e->mUnknown0);
            if(e->mUnknown0Bytes[2]==fn_80178360())out->mUnknown18|=0x200;
            {out->mUnknown08.mX=e->mUnknownC;out->mUnknown08.mY=e->mUnknown10;}break;
        case 20:
            ref=e->mUnknown0;out->mUnknown18|=0x400;fn_80076D8C(e->mUnknown0);
            if(tracked) {
                Point_8017886C to={e->mUnknownC,e->mUnknown10};
                fn_8016B248(team,point,to,fn_8009E9C8());fn_8016B2E8(team,3);
            }
            break;
        case 21:
            i=count;
            if(tracked) {
                Point_8017886C to={e->mUnknownC,e->mUnknown10};
                fn_8016B248(team,point,to,fn_8009E9C8());fn_8016B2E8(team,1);
            }
            break;
        case 22:
            if(fn_8009BCE8(&e->mUnknown0)){out->mUnknown08.mX=e->mUnknownC;out->mUnknown08.mY=e->mUnknown10;}
            else if((state->mUnknown4==3 || state->mUnknown4==5) && state->mWord8==1) {
                if(state->mFloat14>=e->mUnknown10 || e->mUnknown10<=fn_80178A2C()) {
                    {out->mUnknown08.mX=e->mUnknownC;out->mUnknown08.mY=e->mUnknown10;}
                } else {
                    out->mUnknown08.mX=0.0f;out->mUnknown08.mY=-e->mUnknown10;
                    if(fn_801486A0()!=2)out->mUnknown18|=4;
                    out->mUnknown18|=0x100;
                    fn_8017CA94((unsigned short)fn_80178308(),1);fn_800D4888(1);
                }
            }
            placed=true;break;
        case 24:
            if(tracked && !special && fn_8011F1CC() && fn_8009BCE8(&e->mUnknown0)) {
                fn_8016B310(team,1);fn_8016B22C(team,fn_8009BCE8(&e->mUnknown0)->mIdBytes[1]);
                Point_8017886C to={e->mUnknownC,e->mUnknown10};
                fn_8016B248(team,point,to,fn_8009E9C8());fn_8016B2E8(team,5);
            }
            break;
        case 28:
            if(!placed){out->mUnknown08.mX=e->mUnknownC;out->mUnknown08.mY=e->mUnknown10;}
            state->mUnknown10=e->mUnknown4;fn_80076D4C(e->mUnknown4);
            fn_800A061C(state,&out->mUnknown00,state->mUnknown10);
            if(tracked) {
                if(fabsf(e->mUnknownC-point.mX)>4.0f)fn_8016B2E8(team,5);
                else if(fn_8011F1CC() && !(e->mUnknown10>=point.mY))fn_8016B2E8(team,4);
            }
            break;
        case 47:case 54:out->mUnknown18|=0x20000;break;
        case 61:fn_8016B348(fn_80178308(),1);break;
        }
    }
}

extern "C" {
int fn_80177F70(void);
int fn_80177C38(void);
float fn_80178298(void);
void fn_80093C3C(int,int,int);
int fn_800D42CC(void);
int fn_801783AC(int);
int fn_801788D8(int *);
int fn_801787DC(int);
int fn_80025708(void);
}

extern "C" void fn_800A0EB8(Record_800A0624 *state,Object_8017886C *out)
{
    Object_80039F5C *ballPlayer=fn_80137B40();
    bool removed=false,process=true;
    int previous=fn_80177F70();
    Point_8017886C point=fn_80177FE0();
    if(state->mUnknown0) {
        if(fn_801486A0()==3 && fn_80178308()!=fn_80178348()) {
            out->mUnknown1D=-3;process=false;out->mUnknown18|=0x80;
        }
        if(process) {
            if((unsigned int)(previous-1)<5) {
                if((!(out->mUnknown08.mY<=fn_80178A2C()) && fabsf(out->mUnknown08.mX)<fn_80178A08()) ||
                    (ballPlayer && ballPlayer->mFlags&0x800000))out->mUnknown1D=6;
                if(!fn_80177C38()) {
                    if((fn_80178298()!=fn_80178A2C() && out->mUnknown08.mY>=fn_80178298()) || out->mUnknown1D==6) {
                        out->mUnknown04=1;out->mUnknown18|=0x1040;
                    } else if(!(out->mUnknown18&0x84)) {
                        if(previous==4) {
                            fn_80093C3C(1,4,0);out->mUnknown04=1;out->mUnknown18|=0x844;
                            if(fn_800D42CC()==2)fn_80067DB8(0x5D,0,fn_80178348(),0,0);
                            if(fn_8007F828(14)==1)out->mUnknown18|=0x80;
                            if(fn_801486A0()==4)out->mUnknown18|=0x80;
                        } else out->mUnknown04=previous+1;
                    }
                } else {
                    out->mUnknown04=1;out->mUnknown18|=0x40;
                    if(fn_8007F828(14)==1 && fn_80178348()!=fn_80178308() && out->mUnknown1D!=6)out->mUnknown18|=0x80;
                }
                if(fn_80177C38()>1) {
                    out->mUnknown18|=0x40;
                    removed=(out->mUnknown18&4)!=0;
                    out->mUnknown18&=~4;
                }
            } else if(previous==6) {
                if(out->mUnknown1D==3)out->mUnknown1D=1;
                else if(out->mUnknown08.mY>fn_80178A2C() || (ballPlayer && ballPlayer->mFlags&0x800000))out->mUnknown1D=2;
                else if(fn_800D42CC()==2)fn_80067DB8(0x5B,0,fn_80178348(),0,0);
                if(!(out->mUnknown08.mY>=-fn_80178A2C()))out->mUnknown08.mY=0.0f;
                out->mUnknown04=1;out->mUnknown18|=0xC0;
                if(fn_80177C38()==1 || fn_80177C38()==3)out->mUnknown18&=~4;
                else out->mUnknown18|=4;
            } else {
                if(!(out->mUnknown08.mY<=fn_80178A2C()) && !(fabsf(out->mUnknown08.mX)>=fn_80178A08()))out->mUnknown1D=6;
                out->mUnknown04=1;out->mUnknown18|=0x44;
            }
            if(fn_801486A0()==4 && fn_80177C38()!=0) {
                if(out->mUnknown1D==6)out->mUnknown1D=9;
                else {out->mUnknown1D=3;out->mUnknown18|=0x80;}
            }
        }
        if(out->mUnknown1D==6 || out->mUnknown1D==9) {
            out->mUnknown04=6;out->mUnknown08.mX=0.0f;
            out->mUnknown08.mY=fn_80178A2C()-5.0f;
        }
        if((previous!=6 && out->mUnknown08.mY < -fn_80178A2C()) || out->mUnknown18&0x100) {
            if(fn_801783AC(2) && !(out->mUnknown18&0x100)) {
                out->mUnknown1D=-2;out->mUnknown04=1;
                out->mUnknown18=(out->mUnknown18&~0x800)|0x84;
                int count=0;
                switch(fn_801788D8(&count)) {
                case 1:
                    if(fn_800D42CC()==2)fn_80067DB8(0x5C,0,fn_80178348(),0,0);
                    break;
                case 0:
                    if((unsigned int)(fn_801787DC(fn_80178360())+2)<(unsigned int)count)fn_80067DB8(0x5C,0,fn_80178348(),0,0);
                    else if(!fn_80025708())fn_80067DB8(0x5E,0,fn_80178360(),0,0);
                    break;
                }
            } else {
                if(previous!=6 && fn_80177C38()>1 && removed)out->mUnknown18|=4;
                if(!(out->mUnknown18&4)) {
                    float line=fn_80178A2C();out->mUnknown18|=0x100;out->mUnknown08.mY=7.0f-line;
                } else {
                    float line=fn_80178A2C();out->mUnknown18|=0x100;out->mUnknown08.mY=line-7.0f;
                }
                out->mUnknown04=1;out->mUnknown08.mX=0.0f;out->mUnknown18|=0x40;
            }
        }
    } else out->mUnknown04=previous;
    if(fn_801486A0()==3)out->mUnknown18&=~4;
}
