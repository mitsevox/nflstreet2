#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801FCE10.h"
#include "game/fn_8017F584.h"
#include "game/fn_801C1F94.h"
#include <string.h>

struct TextChoices_802DDC20 {
    unsigned char mCount;
    char mUnknown1[3];
    const char *mpText[5];
};

extern "C" {
extern int lbl_8031BE04[14][3];
extern unsigned char lbl_8031BEAC[54];
extern int lbl_803ECA24[2];
extern unsigned char lbl_803EB2B4;
extern TextChoices_802DDC20 lbl_802DDC20[];
void fn_800B4DE4(QueryCursor cursor, int index, void *pOut);
void fn_800B4900(QueryCursor cursor, int index, short *pRatings, void *pOut);
void fn_800B4798(short *pRatings, int team, unsigned char index, void *pContext);
void fn_800B5150(Object_80039F5C *p);
void fn_8003AE24(Object_80039F5C *p);
int fn_800C8704(int *pFirst, int *pSecond);
int fn_800C8744(int team);
int fn_800D41F8(int team);
unsigned short fn_800D3EB0(int team, int index);
int fn_8022B414(int handle, unsigned int tag, int *pValue);
int fn_8022B7A4(int handle, unsigned int tag, int *pValue);
int fn_801C2D88(char *pText, int capacity, const char *pFormat, ...);
char *fn_801C2EF0(char *pText, const char *pSource, unsigned int capacity);
int fn_802372EC(int first, int last);
int fn_801486A0(void);
void fn_8017767C(void);
void fn_80177F88(int value);
int fn_800A2178(void);
void fn_80178CD8(int value);
int fn_80178308(void);
int fn_80178348(void);
void fn_8017833C(int team);

int fn_80149014(void)
{
    return fn_8017F584() == 11;
}

void fn_80149040(Object_80039F5C *p)
{
    QueryCursor cursor = {0,0,-1,0};
    fn_801FCE10(0,"declare \x8A cursor for select * from 'AGLP' where ('DIGP' = \x84)\n",&cursor,p->mUnknown2908);
    fn_800B4DE4(cursor,0,&p->mUnknown2900);
    p->mUnknown508 = *(float *)p->mUnknown2904;
    fn_800B4900(cursor,0,p->mRatings,p->mUnknown3020);
    fn_800B4798(p->mRatings,p->mIdBytes[2],p->mIdBytes[1],&p->mUnknown2900);
    if(cursor.mUnknown0)fn_801FCFA0(&cursor);
    fn_8003AE24(p);
    fn_800B5150(p);
}

void fn_80149154(Class_80148A58 *p, const int *pKinds)
{
    fn_801C1F94(lbl_8031BE04,0,168);
    fn_801C1F94(lbl_8031BEAC,0,54);
    fn_800C8704(&lbl_803ECA24[0],&lbl_803ECA24[1]);
    for(unsigned char k=0;pKinds[k]!=0;k++) {
        for(unsigned char i=0;i<14;i++) {
            unsigned char team=i/7,index=i%7;
            Object_80039F5C *player=fn_80039F5C(team,index);
            if(player->mUnknown9[2]) {
                unsigned int count=p->vfn_25(team,index);
                if(count<=2 && p->vfn_26(team,index,player,pKinds[k])) {
                    lbl_8031BEAC[k]++;
                    lbl_8031BE04[i][count]=pKinds[k];
                }
            }
        }
    }
}

void fn_801492C4(Class_80148A58 *p,const int *pKinds)
{
    fn_801C1F94(lbl_8031BE04,0,168);
    fn_801C1F94(lbl_8031BEAC,0,54);
    fn_800C8704(&lbl_803ECA24[0],&lbl_803ECA24[1]);
    for(unsigned char k=0;pKinds[k]!=0;k++) {
        for(unsigned char team=0;team<2;team++) {
            unsigned int count=p->vfn_25(0,team);
            if(count<=2 && p->vfn_32(team,pKinds[k])) {
                lbl_8031BEAC[k]++;
                lbl_8031BE04[team][count]=pKinds[k];
            }
        }
    }
}

void fn_801493E0(Class_80148A58 *p,int team,unsigned char index,char *text,unsigned char capacity)
{
    *text=0;
    for(unsigned char i=0;i<3 && lbl_8031BE04[team*7+index][i];i++) {
        const char *name=p->vfn_29(lbl_8031BE04[team*7+index][i]);
        unsigned char length=strlen(name);
        if(i)length+=2;
        if(capacity>length) {
            if(i) {
                text[0]=',';text[1]=' ';text+=2;capacity-=2;length-=2;
            }
            fn_801C2EF0(text,name,capacity);
            text+=length;
            capacity-=length;
        }
    }
}

void fn_80149518(Class_80148A58 *p,int team,int column,char *text,int capacity)
{
    fn_801C2D88(text,capacity,p->vfn_29(lbl_8031BE04[team][column]));
}

unsigned char fn_80149588(Class_80148A58 *,int team,int index)
{
    unsigned char row=team*7+index,count=0;
    while(count<3 && lbl_8031BE04[row][count])count++;
    return count;
}

int fn_801495E0(Class_80148A58 *p,int team,int index,Object_80039F5C *player,int kind)
{
    int result=0;
    switch(kind) {
    case 1:result=p->vfn_31(1,team,index,player,1,0);break;
    case 2:result=p->vfn_31(2,team,index,player,0,0);break;
    case 3:result=p->vfn_31(3,team,index,player,10,0);break;
    case 4:result=p->vfn_31(4,team,index,player,2,0);break;
    case 5:result=p->vfn_31(5,team,index,player,2,0);break;
    case 6:result=p->vfn_31(6,team,index,player,1,0);break;
    case 7:result=p->vfn_31(7,team,index,player,3,0);break;
    case 8:result=p->vfn_31(8,team,index,player,1,1);break;
    case 9:
        result=p->vfn_31(9,team,index,player,2,1);
        if(result && p->vfn_28(8))result=0;
        break;
    case 10:result=p->vfn_25(team,index)==0;break;
    case 11:result=p->vfn_31(11,team,index,player,3,0);break;
    case 12:result=p->vfn_31(12,team,index,player,0,0);break;
    case 13:result=p->vfn_31(13,team,index,player,1,0);break;
    case 14:result=p->vfn_31(14,team,index,player,1,0);break;
    case 15:result=p->vfn_31(15,team,index,player,1,0);break;
    }
    return result;
}

int fn_801498EC(Class_80148A58 *,int team,int index,int value)
{
    unsigned char row=team*7+index;
    int found=0;
    for(unsigned char i=0;i<3;i++)if(lbl_8031BE04[row][i]==value)found=1;
    return found;
}

const char *fn_8014993C(Class_80148A58 *,int kind)
{
    unsigned char index=0;
    if(lbl_802DDC20[kind].mCount>1)index=fn_802372EC(0,lbl_802DDC20[kind].mCount);
    return lbl_802DDC20[kind].mpText[index];
}

unsigned char fn_80149998(Class_80148A58 *,int index)
{
    return lbl_8031BEAC[index];
}

int fn_801499A8(Class_80148A58 *,int kind,int team,int index,Object_80039F5C *pPlayer)
{
    int result=0;
    unsigned short id=pPlayer->mUnknown2908;
    int value;
    switch(kind) {
    case 1:case 9:fn_8022B414(id,0x61746467,&result);break;
    case 2:
        fn_8022B414(id,0x64747567,&result);
        fn_8022B414(id,0x64746167,&value);result+=value;break;
    case 3:
        fn_8022B414(id,0x74627567,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x61737374,&value);
        result+=value*10;break;
    case 4:
        fn_8022B7A4(lbl_803ECA24[team],0x68647374,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x68777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x68737374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x68327374,&value);result+=value;break;
    case 5:
        fn_8022B7A4(lbl_803ECA24[team],0x6A737374,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x6A777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x73737374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x73327374,&value);result+=value;break;
    case 6:fn_8022B414(id,0x72666C67,&result);break;
    case 7:
        fn_8022B7A4(lbl_803ECA24[team],0x68777374,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x6A777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x70777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x63777374,&value);result+=value;break;
    case 8:
        fn_8022B414(id,0x64747567,&result);
        fn_8022B414(id,0x64746167,&value);result+=value;
        fn_8022B414(id,0x61746467,&value);result+=value;
        fn_8022B414(id,0x66666C67,&value);result+=value;
        fn_8022B414(id,0x6E696167,&value);result+=value;break;
    case 10:break;
    case 11:fn_8022B414(id,0x75667567,&result);break;
    case 12:result=fn_800D41F8(team);break;
    case 13:
        fn_8022B414(id,0x72666C67,&result);
        fn_8022B414(id,0x6E696167,&value);result+=value;break;
    case 14:fn_8022B414(id,0x6B736C67,&result);break;
    case 15:fn_8022B414(id,0x6E696167,&result);break;
    }
    return result;
}

int fn_80149DA4(Class_80148A58 *p,int kind,int team,int index,Object_80039F5C *player,int threshold,int mode)
{
    int value=p->vfn_30(kind,team,index,player);
    int count;
    switch(fn_801486A0()) {
    case 1:count=4;break;
    case 0:count=6;break;
    default:count=7;break;
    }
    int best=0,found=0,result=0;
    for(unsigned char t=0;t<2;t++) {
        for(unsigned char i=0;i<(unsigned int)count;i++) {
            Object_80039F5C *other=fn_80039F5C(t,i);
            if(other->mUnknown9[2]) {
                if(!found) {
                    best=p->vfn_30(kind,t,i,other);found=1;
                } else {
                    int next=p->vfn_30(kind,t,i,other);
                    if((mode==0 && next>best) || (mode==1 && next<best))best=next;
                }
            }
        }
    }
    if((mode==0 && best>threshold) || (mode==1 && best<threshold))result=value==best;
    return result;
}

int fn_80149F40(Class_80148A58 *p,int team,int kind)
{
    int result=0;
    if(kind!=21 && p->vfn_27(0,team,8))return 0;
    switch(kind) {
    case 1:result=p->vfn_34(1,team,1,0);break;
    case 2:result=p->vfn_34(2,team,1,0);break;
    case 3:result=p->vfn_34(3,team,10,0);break;
    case 4:result=p->vfn_34(4,team,4,0);break;
    case 5:result=p->vfn_34(5,team,2,0);break;
    case 6:result=p->vfn_34(6,team,1,0);break;
    case 7:result=p->vfn_34(7,team,3,0);break;
    case 8:result=p->vfn_33(8,team)==0;break;
    case 9:
        if(!p->vfn_28(8) && p->vfn_34(9,team,100,1))result=1;
        break;
    case 10:result=p->vfn_25(0,team)==0;break;
    case 11:result=p->vfn_34(11,team,3,0);break;
    case 12:result=p->vfn_34(12,team,1,0);break;
    case 13:result=p->vfn_34(13,team,1,0);break;
    case 14:result=p->vfn_34(14,team,1,0);break;
    case 15:result=p->vfn_34(15,team,1,0);break;
    }
    return result;
}

int fn_8014A1B8(Class_80148A58 *p,int kind,int team)
{
    int result=0,value;
    int handle=fn_800C8744(team);
    switch(kind) {
    case 1:case 9:result=p->vfn_24(team,0x61746467);break;
    case 2:
        fn_8022B7A4(handle,0x74727374,&result);
        fn_8022B7A4(handle,0x74507374,&value);result+=value;
        fn_8022B7A4(handle,0x64647374,&value);result+=value;break;
    case 3: {
        int a=fn_800D3EB0(team,30),b=fn_800D3EB0(team,31);
        int c=fn_800D3EB0(team,29);result=a+b+c;break;
    }
    case 4: {
        int a=fn_800D3EB0(team,57),b=fn_800D3EB0(team,63);result=a+b;break;
    }
    case 5: {
        int a=fn_800D3EB0(team,34),b=fn_800D3EB0(team,46);
        int c=fn_800D3EB0(team,42);result=a+b+c;break;
    }
    case 6:fn_8022B7A4(handle,0x72667374,&result);break;
    case 7: {
        int a=fn_800D3EB0(team,63),b=fn_800D3EB0(team,11);
        int c=fn_800D3EB0(team,42),d=fn_800D3EB0(team,113);
        int e=fn_800D3EB0(team,110);result=a+b+c+d+e;break;
    }
    case 8:
        fn_8022B7A4(handle,0x74727374,&value);result+=value;
        fn_8022B7A4(handle,0x74507374,&value);result+=value;
        fn_8022B7A4(handle,0x64647374,&value);result+=value;
        fn_8022B7A4(handle,0x69707374,&value);result+=value;
        result+=p->vfn_24(team,0x61746467);
        result+=p->vfn_24(team,0x72666C67);break;
    case 10:break;
    case 11:
        fn_8022B7A4(handle,0x75667374,&value);result+=value*5;
        fn_8022B7A4(handle,0x70447374,&value);result+=value;break;
    case 12:result=fn_800D41F8(team);break;
    case 13:
        fn_8022B7A4(handle,0x69447374,&result);
        result+=p->vfn_24(team,0x72666C67);break;
    case 14: {
        int a=fn_800D3EB0(team,77),b=fn_800D3EB0(team,103);result=a+b;break;
    }
    case 15: {
        int a=fn_800D3EB0(team,74),b=fn_800D3EB0(team,75);
        int c=fn_800D3EB0(team,105);result=a+b+c;break;
    }
    }
    return result;
}

int fn_8014A5B4(Class_80148A58 *p,int kind,int team,int threshold,int mode)
{
    int value=p->vfn_33(kind,team);
    int other=(team+1)&1;
    int result=1;
    if((mode==0 && value<p->vfn_33(kind,other)) || (mode==1 && value>p->vfn_33(kind,other)))result=0;
    if((mode==0 && value<threshold) || (mode==1 && value>threshold))result=0;
    return result;
}

void fn_8014A6A0(const int *pValues,int *pOrder,unsigned int count)
{
    int has0=0,has2=0,has3=0,has1=0,has4=0,has5=0,has6=0;
    for(unsigned char i=0;i<count;i++) {
        if(pOrder[0]==pValues[i])has0=1;
        else if(pOrder[2]==pValues[i])has2=1;
        else if(pOrder[3]==pValues[i])has3=1;
        else if(pOrder[1]==pValues[i])has1=1;
        else if(pOrder[4]==pValues[i])has4=1;
        else if(pOrder[5]==pValues[i])has5=1;
        else if(pOrder[6]==pValues[i])has6=1;
    }
    int temp;
    if(!has0) {
        if(has1) {temp=pOrder[0];pOrder[0]=pOrder[1];pOrder[1]=temp;has1=0;}
        else if(has4) {temp=pOrder[0];pOrder[0]=pOrder[4];pOrder[4]=temp;has4=0;}
        else if(has5) {temp=pOrder[0];pOrder[0]=pOrder[5];pOrder[5]=temp;has5=0;}
        else if(has6) {temp=pOrder[0];pOrder[0]=pOrder[6];pOrder[6]=temp;has6=0;}
    }
    if(!has2) {
        if(has1) {temp=pOrder[2];pOrder[2]=pOrder[1];pOrder[1]=temp;has1=0;}
        else if(has6) {temp=pOrder[2];pOrder[2]=pOrder[6];pOrder[6]=temp;has6=0;}
        else if(has4) {temp=pOrder[2];pOrder[2]=pOrder[4];pOrder[4]=temp;has4=0;}
        else if(has5) {temp=pOrder[2];pOrder[2]=pOrder[5];pOrder[5]=temp;has5=0;}
    }
    if(!has3) {
        if(has1) {temp=pOrder[3];pOrder[3]=pOrder[1];pOrder[1]=temp;}
        else if(has6) {temp=pOrder[3];pOrder[3]=pOrder[6];pOrder[6]=temp;}
        else if(has4) {temp=pOrder[3];pOrder[3]=pOrder[4];pOrder[4]=temp;}
        else if(has5) {temp=pOrder[3];pOrder[3]=pOrder[5];pOrder[5]=temp;}
    }
}

void fn_8014A8D8(const int *pValues,int *pOrder,unsigned int count)
{
    int has11=0,has13=0,has9=0,has10=0,has7=0,has12=0,has8=0;
    for(unsigned char i=0;i<count;i++) {
        if(pOrder[11]==pValues[i])has11=1;
        else if(pOrder[13]==pValues[i])has13=1;
        else if(pOrder[9]==pValues[i])has9=1;
        else if(pOrder[10]==pValues[i])has10=1;
        else if(pOrder[7]==pValues[i])has7=1;
        else if(pOrder[12]==pValues[i])has12=1;
        else if(pOrder[8]==pValues[i])has8=1;
    }
    int temp;
    if(!has11) {
        if(has12) {temp=pOrder[11];pOrder[11]=pOrder[12];pOrder[12]=temp;has12=0;}
        else if(has9) {temp=pOrder[11];pOrder[11]=pOrder[9];pOrder[9]=temp;has9=0;}
        else if(has10) {temp=pOrder[11];pOrder[11]=pOrder[10];pOrder[10]=temp;has10=0;}
        else if(has7) {temp=pOrder[11];pOrder[11]=pOrder[7];pOrder[7]=temp;has7=0;}
        else if(has8) {temp=pOrder[11];pOrder[11]=pOrder[8];pOrder[8]=temp;has8=0;}
    }
    if(!has13) {
        if(has12) {temp=pOrder[13];pOrder[13]=pOrder[12];pOrder[12]=temp;}
        else if(has9) {temp=pOrder[13];pOrder[13]=pOrder[9];pOrder[9]=temp;}
        else if(has10) {temp=pOrder[13];pOrder[13]=pOrder[10];pOrder[10]=temp;}
        else if(has7) {temp=pOrder[13];pOrder[13]=pOrder[7];pOrder[7]=temp;}
        else if(has8) {temp=pOrder[13];pOrder[13]=pOrder[8];pOrder[8]=temp;}
    }
}

int fn_8014AACC(void) {return 1;}
unsigned char fn_8014AAD4(void) {return lbl_803EB2B4;}
int fn_8014AADC(void) {return 120;}
void fn_8014AAE4(void)
{
    fn_8017767C();
    fn_80177F88(1);
    if(fn_800A2178()==0 || fn_800A2178()==11)fn_80178CD8(1);
    int team=fn_80178308();
    if(team!=fn_80178348()) {
        fn_8017833C(fn_80178348());
        fn_80178CD8(1);
    }
}
int fn_8014AB58(void) {return 0x7FFFFFFF;}
}
