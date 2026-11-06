#include "game/Object_80039F5C.h"
#include "game/GameModules.h"
#include "game/FELoop.h"
#include "game/Ball.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801D2B7C.h"
#include "game/AnimFileFormat.h"
#include "engine/animemot.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_80040818.h"
#include "game/BigObjInst.h"
#include "game/cu_801444D8.h"
#include "game/AudmonEvent.h"
#include "game/cu_8003108C.h"

struct Entry_802D71D8 {
    int mId;
    union {
        int mUnknown4;
        struct {unsigned char mUnknown4Bytes[3];unsigned char mUnknown7;};
    };
    void *mHandle;
};
struct Record_8008FF28 {
    char mUnknown0[4];
    unsigned short mUnknown4;
};
struct Object_8008FF28 {
    char mUnknown0[20];
    int mUnknown20;
};

extern "C" {
extern void (*lbl_80297D68[11])(Object_80039F5C *);
extern Entry_802D71D8 lbl_802D71D8[];
extern AnimFileConfig_t lbl_802D713C;
extern AnimFileConfig_t lbl_802D70D0;
extern void *lbl_803EA8B0;
extern void *lbl_803EC91C;
extern void *lbl_803EC920;
extern const char lbl_802EBDBC[];
extern float gPlyrMoveSideSpeed;
extern float gPlyrMoveBackSpeed;
int PlayerMoveAnimCheckReverse(Object_80039F5C *, unsigned short);
int MathAngleDiff(int, int);
int fn_801BB608(void *, void *);
int fn_801BB638(int, void *);
int fn_801BB65C(int, void *);
int AnimSeqGetOpcodeParameter(void);
int fn_801BB994(int id);
void AnimCacheInit(int, int);
void AnimCacheSetUpObjectType(int, int, int);
void AnimFrameCacheSetCustomFunc(void (*)(AnimFileFormat_t *,int,unsigned char *,unsigned int,unsigned int,int));
void AnimFrameCacheClearCustomFunc(void);
void *AnimFrameCacheCreate(int, int);
void AnimFrameCacheDestroy(void *);
void AnimExtnReadMotion(AnimFileFormat_t *,int,unsigned char *,unsigned int,unsigned int,int);
void AnimExtnFreeFile(AnimFileFormat_t *);
int AnimInit(unsigned int mode);
int AnimSequencerInit(float rate);
void fn_801CC7FC(void *);
void fn_801CC820(void *, int);
void fn_801CC8AC(void *, int);
void AnimSetUserOpcodeCallbacks(int (*)(void *,int,unsigned int), int (*)(void *,int,unsigned int));
void AnimFileSetCustomRelocateFunc(void (*)(AnimFileFormat_t *));
void fn_801BAEA4(void (*)(AnimFileFormat_t *));
void fn_801F0F18(int);
void *fn_801BB570(int, int, int, int);
void fn_801BB480(void);
int AnimSequencerShutdown(void);
int AnimShutdown(void);
void fn_801BF2B0(int);
int fn_801BDF90(int count);
int fn_801BDFF8(void);
void AnimCacheShutdown(void);
int fn_801BF384(void);
void fn_8004AD3C(void *);
void *fn_801D2BB0(int, int, int, int);
int fn_801F0C50(void *, int);

extern int lbl_802D7154[];
extern int lbl_802D71CC[];
extern float lbl_803EA8B4,lbl_803EA8B8;
BigObjInst *fn_800400C4(Block_80170E64 *);
int fn_801BA5A8(AnimHeader_t *,Record_800D81C8 *,unsigned short,int);
int fn_801BA6B0(Record_800D81C8 *);
void fn_800518E0(Object_80039F5C *);
void fn_800C8688(Object_80039F5C *,Object_80039F5C *,int,int);
int fn_800C8694(Object_80039F5C *);
void fn_800ADBFC(Object_80039F5C *,int);
void fn_800ADD00(Object_80039F5C *);
void fn_800ADD04(Object_80039F5C *);
void fn_800AE0B8(Object_80039F5C *);
int fn_800DBAF0(Object_80039F5C *);
void fn_800D7A0C(Object_80039F5C *,int);
void fn_8009D00C(void *,int *);
void fn_80042380(Object_8003DEC4 *,int,float *,int *);
void QuatFromEuler(Quat_801EB488 *,int,int,int);
void fn_800943D8(void);
void fn_80147840(Object_8003DEC4 *);
void PlayerMoveClear(Object_80039F5C *);
void fn_800A9B54(unsigned int,Object_80039F5C *);
void fn_80028DF8(float,float);
float fn_8009C630(Object_80039F5C *,unsigned int);
int fn_8008EBBC(void *, int, unsigned int);
int fn_8008F78C(void *, int, unsigned int);
}

extern "C" void fn_8008E978(Object_80039F5C *p)
{
    lbl_80297D68[p->mUnknown512.mUnknown14](p);
}

extern "C" void fn_8008E9B0(Object_80039F5C *p)
{
    unsigned short key=fn_801BE648(p->mpUnknown792);
    PlyrMoveCmd_t *current=&p->mUnknown512;
    PlyrMoveCmd_t *next=&p->mUnknown528;
    int difference=MathAngleDiff(current->mUnknown4,current->mUnknown8);
    if(difference<=0x2E38E2 || current->mUnknown0==0.0f) {
        key=74; next->mUnknown14=1;
        next->mUnknown4=current->mUnknown4;
        next->mUnknown8=current->mUnknown8;
        next->mUnknown0=current->mUnknown0;
    } else if(difference<=0x56C16B && !(p->mUnknown492>gPlyrMoveSideSpeed)) {
        key=160;
        float speed=gPlyrMoveSideSpeed*0.18f/gPlyrMoveSideSpeed;
        next->mUnknown0=current->mUnknown0>=speed?current->mUnknown0:speed;
        next->mUnknown14=current->mUnknown14;
        next->mUnknown4=current->mUnknown4;
    } else if(difference>0x56C16B && !(p->mUnknown492>gPlyrMoveBackSpeed)) {
        key=74;next->mUnknown0=current->mUnknown0;
        next->mUnknown14=current->mUnknown14;
        next->mUnknown4=current->mUnknown4;
    } else {
        next->mUnknown14=1;
        next->mUnknown4=current->mUnknown4;
        next->mUnknown8=current->mUnknown8;
        next->mUnknown0=current->mUnknown0;
    }
    if(!PlayerMoveAnimCheckReverse(p,key) && fn_801BE648(p->mpUnknown792)!=key)
        fn_801BE068(p->mpUnknown792,p->mpUnknown796,p->mpUnknown800,key,1.0f,p);
}

extern "C" void fn_8008EB18(int id,int flag,void *data)
{
    int i=0;
    while(lbl_802D71D8[i].mId!=-1 && lbl_802D71D8[i].mId!=id) ++i;
    if(lbl_802D71D8[i].mId==id) fn_801BB608(lbl_802D71D8[i].mHandle,data);
    else if(flag) fn_801BB65C(id,data);
    else fn_801BB638(id,data);
}

extern "C" int fn_8008EBBC(void *object,int event,unsigned int key)
{
    Object_80039F5C *p=(Object_80039F5C *)object;
    BigObjInst *placed=(BigObjInst *)object;
    int mode=0;
    if(!FELoopIsMainFEActive() && object==fn_800400C4(BallGetModel(BallGetCurrent()))) return 1;
    void *collection;
    if(event>=0xD000 && event<=0xD005) collection=placed->mUnknown428->mUnknown1300;
    else collection=p->mpUnknown792;
    unsigned int active=fn_801BE648(collection);
    if(key==active || key==0xFFFF || event==0xC01A) {
        switch(event) {
        case 0xC000:case 0xC027:
            p->mUnknown9[0]=(unsigned char)AnimSeqGetOpcodeParameter();return 1;
        case 0xC001:p->mFlags|=0x100800;return 1;
        case 0xC002:p->mFlags&=~0x10800;return 1;
        case 0xC003:p->mFlags|=0x1000;return 1;
        case 0xC004:p->mFlags|=4;return 1;
        case 0xC005:case 0xC009:case 0xC00A:case 0xC01D:return 1;
        case 0xC006:p->mFlags|=1;return 1;
        case 0xC007:p->mFlags|=0x40;return 1;
        case 0xC008:p->mFlags|=0x80;return 1;
        case 0xC00B:p->mFlags|=0x100;return 1;
        case 0xC00C:p->mFlags|=0x40000;return 1;
        case 0xC00D:
            p->mUnknown1240.mUnknown0=(short)AnimSeqGetOpcodeParameter();
            p->mUnknown1240.mUnknown2=(signed char)AnimSeqGetOpcodeParameter();
            if(p->mUnknown1240.mUnknown2==7) {
                fn_800518E0(p);AudmonEventPostId(46,&p->mMotion.mPos,p->mId,0,0,0);
            } else {
                fn_800C8688(p,0,p->mUnknown1240.mUnknown0,0);
                if(fn_800C8694(p) && p->mpState->mId==16) p->mFlags|=0x10000;
            }
            return 1;
        case 0xC00E:
            if(AnimSeqGetOpcodeParameter()==2) p->mFlags&=~8;else p->mFlags|=8;return 1;
        case 0xC00F:
            if(AnimSeqGetOpcodeParameter()==2) p->mFlags|=0x80000;else p->mFlags&=~0x80000;return 1;
        case 0xC010: {
            int index=fn_801BA5A8(p->mpUnknown796,p->mpUnknown800,10,0);
            if(index==0xFFFF) index=fn_801BA5A8(p->mpUnknown796,p->mpUnknown800,(unsigned short)key,0);
            if(index!=0xFFFF) mode=fn_801BA6B0(&p->mpUnknown800[index]);
            fn_800ADBFC(p,mode);return 1;
        }
        case 0xC011:fn_800ADD04(p);return 1;
        case 0xC012:AnimSeqGetOpcodeParameter();AnimSeqGetOpcodeParameter();AnimSeqGetOpcodeParameter();return 1;
        case 0xC013:fn_800AE0B8(p);return 1;
        case 0xC014:p->mUnknown1240.mUnknown3=(unsigned char)AnimSeqGetOpcodeParameter();return 1;
        case 0xC015: {
            int selection=2;
            int index=fn_801BA5A8(p->mpUnknown796,p->mpUnknown800,(unsigned short)key,0);
            mode=fn_801BA6B0(&p->mpUnknown800[index]);
            if(AnimSeqGetOpcodeParameter()==2) selection=1;
            if(mode) selection=selection==2?1:2;
            if(!fn_800DBAF0(p)) fn_800D7A0C(p,selection);
            return 1;
        }
        case 0xC016:case 0xC01B:case 0xC021:case 0xD004:
            AnimSeqGetOpcodeParameter();return 1;
        case 0xC017: {
            int index=fn_801BA5A8(p->mpUnknown796,p->mpUnknown800,(unsigned short)key,0);
            if(index!=0xFFFF) mode=fn_801BA6B0(&p->mpUnknown800[index]);
            else mode=p->mUnknown776==1;
            int selection=AnimSeqGetOpcodeParameter();int *record;
            switch(selection) {
            case 1:record=&p->mUnknown16;break;
            case 2:record=mode?&p->mUnknown200:&p->mUnknown108;break;
            default:record=mode?&p->mUnknown108:&p->mUnknown200;break;
            }
            fn_8009D00C(p,record);return 1;
        }
        case 0xC018:p->mFlags|=0x2000;return 1;
        case 0xC019:fn_800ADD00(p);return 1;
        case 0xC01A:fn_801BA5A8(p->mpUnknown796,p->mpUnknown800,(unsigned short)key,0);return 1;
        case 0xC01C: {
            short bone=(short)(AnimSeqGetOpcodeParameter()-1);
            short effect=(short)(AnimSeqGetOpcodeParameter()-1);
            float position[4];int angles[3];Quat_801EB488 rotation;
            fn_80042380((Object_8003DEC4 *)p->mpUnknown4,lbl_802D7154[bone],position,angles);
            QuatFromEuler(&rotation,angles[2],angles[1],angles[0]);
            ParticlesSpawnAt(lbl_802D71CC[effect],position,&rotation.mX,0);
            return 1;
        }
        case 0xC01E:
            fn_801BA5A8(p->mpUnknown796,p->mpUnknown800,(unsigned short)key,0);
            fn_8003145C(p,AnimSeqGetOpcodeParameter());return 1;
        case 0xC01F:
            if(AnimSeqGetOpcodeParameter()==1) AudmonEventPostId(43,&p->mMotion.mPos,p->mId,0,0,0);
            else AudmonEventPostId(35,&p->mMotion.mPos,p->mId,(int)p,(int)p,0);
            return 1;
        case 0xC020:fn_800943D8();return 1;
        case 0xC022:fn_80147840((Object_8003DEC4 *)p->mpUnknown4);return 1;
        case 0xC023:if(AnimSeqGetOpcodeParameter()==1) PlayerMoveClear(p);return 1;
        case 0xC024: {
            unsigned int effect=(unsigned int)AnimSeqGetOpcodeParameter()-1;
            if(effect<=26) fn_800A9B54(effect,p);return 1;
        }
        case 0xC026: {
            unsigned int time=AnimSeqGetOpcodeParameter();unsigned int scale=AnimSeqGetOpcodeParameter();
            fn_80028DF8((float)time*0.001f,(float)scale*0.1f);return 1;
        }
        case 0xC028:p->mFlags|=0x40000000;return 1;
        case 0xD000:placed->mUnknown428->mUnknown1708|=1;return 1;
        case 0xD001:placed->mUnknown424=AnimSeqGetOpcodeParameter();return 1;
        case 0xD002:placed->mUnknown428->mUnknown1708|=8;return 1;
        case 0xD003: {
            int value=AnimSeqGetOpcodeParameter();Object_80040818 *owner=fn_80040F18(placed->mUnknown4);
            if(value) owner->mUnknown232_31=1;else owner->mUnknown232_31=0;return 1;
        }
        case 0xD005:placed->mUnknown428->mUnknown1708|=0x20;return 1;
        default:return 0;
        }
    }
    switch(event) {
    case 0xC003:
        if(p->mIdBytes[3]==1 && (key==69 || key==178) && !(fn_8009C630(p,key)<=lbl_803EA8B8))
            p->mFlags|=0x1000;
        return 1;
    case 0xC009:return 1;
    case 0xC010:fn_800ADBFC(0,0);return 1;
    case 0xC011:fn_800ADD04(0);return 1;
    case 0xC012:AnimSeqGetOpcodeParameter();AnimSeqGetOpcodeParameter();AnimSeqGetOpcodeParameter();return 1;
    case 0xC013:fn_800AE0B8(p);return 1;
    case 0xC018:
        if(p->mIdBytes[3]==1 && (key==69 || key==178) && !(fn_8009C630(p,key)<=lbl_803EA8B4))
            p->mFlags|=0x2000;
        return 1;
    case 0xC019:fn_800ADD00(0);return 1;
    case 0xC01F:case 0xC023:case 0xD004:AnimSeqGetOpcodeParameter();return 1;
    }
    return fn_8008F78C(object,event,key);
}

extern "C" int fn_8008F78C(void *,int event,unsigned int)
{
    int handled=0;
    switch(event) {
    case 0xC010:case 0xC012:case 0xC019:
        AnimSeqGetOpcodeParameter();
    case 0xC009:case 0xC00D:case 0xC011:case 0xC026:
        AnimSeqGetOpcodeParameter();
    case 0xC000:case 0xC00E:case 0xC00F:case 0xC014:case 0xC015:case 0xC016:
    case 0xC017:case 0xC01A:case 0xC01B:case 0xC01E:case 0xC01F:
    case 0xC021:case 0xC022:case 0xC023:case 0xC024:case 0xC025:case 0xC027:
    case 0xD004:
        AnimSeqGetOpcodeParameter();
    case 0xC001:case 0xC002:case 0xC003:case 0xC004:case 0xC005:case 0xC006:
    case 0xC007:case 0xC008:case 0xC00A:case 0xC00B:case 0xC00C:case 0xC018:
    case 0xC01C:case 0xC01D:case 0xC020:case 0xC028:
    case 0xD000:case 0xD001:case 0xD002:case 0xD003:case 0xD005:
        handled=1;
    }
    return handled;
}

extern "C" void fn_8008F940(void)
{
    AnimCacheInit(1,11);
    AnimCacheSetUpObjectType(1,248,1250);
}
extern "C" void fn_8008F978(void)
{
    AnimFrameCacheSetCustomFunc(AnimExtnReadMotion);
    lbl_803EC91C=AnimFrameCacheCreate(256,178);
    lbl_803EC920=AnimFrameCacheCreate(20,178);
}
extern "C" void fn_8008F9C0(void)
{
    AnimFrameCacheDestroy(lbl_803EC91C);
    AnimFrameCacheDestroy(lbl_803EC920);
    AnimFrameCacheClearCustomFunc();
}
extern "C" void fn_8008F9F0(int flag)
{
    fn_8008EB18(65,flag,lbl_803EC91C);
    fn_8008EB18(66,flag,lbl_803EC91C);
    fn_8008EB18(67,flag,lbl_803EC91C);
    fn_8008EB18(68,flag,lbl_803EC91C);
    fn_8008EB18(69,flag,lbl_803EC91C);
    fn_8008EB18(70,flag,lbl_803EC91C);
    fn_8008EB18(74,flag,lbl_803EC91C);
    fn_8008EB18(82,flag,lbl_803EC91C);
    fn_8008EB18(75,flag,lbl_803EC91C);
}
extern "C" void fn_8008FAA8(void)
{
    void *archive=fn_801EEB44(lbl_802EBDBC,44);
    int size=0,largest=0;
    for(int i=0;lbl_802D71D8[i].mId!=-1;++i) {
        int amount=fn_801F0C50(archive,lbl_802D71D8[i].mId);
        if(lbl_802D71D8[i].mUnknown4) {
            if(amount<=largest) amount/=5;
            else {int previous=largest;largest=amount;amount=largest/5+(largest-previous);}
        }
        size+=amount+512;
    }
    fn_801EEFAC(archive);
    lbl_803EA8B0=fn_801D2BB0(1,size,2,0);
}
extern "C" void fn_8008FBA0(void)
{
    AnimInit(1);AnimSequencerInit(60.0f);
    AnimData *pModule=&gAnimData;
    fn_801CC7FC(pModule);fn_801CC820(pModule,0);
    lbl_802D713C.mpArchive=pModule->GetArchive();
    AnimSetUserOpcodeCallbacks(fn_8008EBBC,fn_8008F78C);
    AnimFileSetCustomRelocateFunc(AnimExtnRelocateFile);fn_801BAEA4(AnimExtnFreeFile);
    fn_801BB2D8(&lbl_802D713C);fn_801F0F18(0);
    if(lbl_803EA8B0) {fn_801D2BD0(lbl_803EA8B0);lbl_803EA8B0=0;}
    for(int i=0;lbl_802D71D8[i].mId!=-1;++i)
        lbl_802D71D8[i].mHandle=fn_801BB570(lbl_802D71D8[i].mId,1,2,lbl_802D71D8[i].mUnknown7);
    fn_801BB480();AnimSequencerShutdown();AnimShutdown();fn_801CC8AC(&gAnimData,0);
}
extern "C" void fn_8008FCB4(int flag)
{
    if(flag) lbl_802D713C.mpArchive=gAnimData.GetArchive();
    else lbl_802D70D0.mpArchive=gAnimData.GetArchive();
    AnimInit(1);AnimSequencerInit(60.0f);
    AnimSetUserOpcodeCallbacks(fn_8008EBBC,fn_8008F78C);
    AnimFileSetCustomRelocateFunc(AnimExtnRelocateFile);fn_801BAEA4(AnimExtnFreeFile);
    fn_8008F978();fn_801BF2B0(4);
    if(flag) fn_801BB2D8(&lbl_802D713C);else fn_801BB2D8(&lbl_802D70D0);
    fn_801BDF90(11);fn_8008F940();
}
extern "C" void fn_8008FD88(void)
{
    fn_801BDFF8();AnimCacheShutdown();fn_8008F9C0();fn_801BB480();
    fn_801BF384();AnimShutdown();AnimSequencerShutdown();
}
extern "C" void fn_8008FDC0(void)
{
    fn_8008EB18(81,0,0);fn_8008EB18(64,0,lbl_803EC91C);
    fn_8008EB18(72,0,lbl_803EC91C);fn_8008EB18(73,0,lbl_803EC91C);
    fn_8008EB18(78,0,0);fn_8008EB18(79,0,0);fn_8008EB18(80,0,0);
    fn_8008F9F0(0);fn_8004AD3C(lbl_803EC920);
}
extern "C" void fn_8008FE5C(void) {}
extern "C" void fn_8008FE60(void)
{
    fn_801BB638(71,0);fn_801BB638(81,0);fn_801BB638(76,0);
    fn_801BB638(77,0);fn_801BB638(80,0);fn_801BB638(83,0);
    fn_8008EB18(72,0,lbl_803EC91C);
}
extern "C" void fn_8008FED4(void)
{
    fn_801BB994(71);fn_801BB994(81);fn_801BB994(76);
    fn_801BB994(77);fn_801BB994(80);fn_801BB994(83);fn_801BB994(72);
}
extern "C" int fn_8008FF28(Object_8008FF28 *p,Record_8008FF28 *record)
{
    return record->mUnknown4?p->mUnknown20:0;
}
