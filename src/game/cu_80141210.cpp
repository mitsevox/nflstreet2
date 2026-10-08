#include "game/Camera_8013F738.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Object_80039F5C.h"
#include "game/cu_8008E978.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_800AD9B4.h"
#include "engine/cu_80227F14.h"

/* Views established by this caller's accesses. Their original identities
   and the contents of the opaque spans remain unknown. */
struct Curve_801C5278 { unsigned char mUnknown0[4]; float mUnknown4, mUnknown8; unsigned char mUnknownC[4]; };
struct Sample_801C009C { float mUnknown0[3]; Curve_801C5278 mUnknownC[15]; };
struct Settings_800963EC { unsigned char mUnknown0[0x300]; float mUnknown300; };
struct Entry_801411B4 { float mUnknown0; unsigned char mUnknown4[4]; unsigned char mUnknown8; };
struct State_80141210 { unsigned char mUnknown0[16]; int mUnknown10,mUnknown14; };
struct Angles_80141210 { int mX,mY,mZ; };
struct View_802DCEB0 { Vector_80039F5C mUnknown0; Angles_80141210 mUnknownC; int mUnknown18; };

extern "C" {
extern View_802DCEB0 lbl_802DCEB0[];
extern View_802DCEB0 lbl_802DCF58;
float fn_801BFFA0(void);
Sample_801C009C *fn_801C00F8(Actor_801C009C *);
Sample_801C009C *fn_801C009C(Actor_801C009C *,int,unsigned short,unsigned short);
float fn_801C5278(float,Curve_801C5278 *,int);
void fn_801D04C4(void); void fn_801D0558(void); void fn_801D0544(void); void fn_801D0508(void);
void fn_801D0F80(float (*)[4]); void fn_801D06D4(float (*)[4]); void fn_801D0ADC(int);
void fn_801EBBA4(float *,Vector_80039F5C *,int);
void fn_801EB660(float *,float *,float *);
void fn_801EB814(float (*)[4],float *);
void fn_8022765C(void *,void *,void *);
float fn_80227120(void *); float fn_80227704(void *,void *);
void fn_80227264(void *,void *,float);
void fn_80227C2C(void *,void *);
void fn_80227384(void *,void *,int);
void fn_80227490(void *,void *,int,int,int);
int fn_801CFE40(float,float); float fn_80260B1C(float);
void fn_8014116C(float,float,float,Vector_80039F5C *,State_80141210 *,Actor_801C009C *);
void fn_8014118C(Angles_80141210 *,State_80141210 *,Actor_801C009C *,int,int,int);
Entry_801411B4 *fn_801411B4(Camera_8013F738 *);
int fn_80027DF0(void);
void fn_801C3990(Camera_8013F738 *,float,float);
void fn_8013C478(Camera_8013F738 *,void *);
void fn_8013C4BC(Camera_8013F738 *,void *,int);
void fn_8013C6F0(Camera_8013F738 *);
Settings_800963EC *fn_800963EC(Character_80093BCC *);
int fn_801784C4(void);
Camera_8013F738 *fn_8013FA04(int);
void fn_801C3EA4(Camera_8013F738 *,float,float,float);
void fn_801C3ED0(Camera_8013F738 *,int,int,int);
void fn_8013C384(void *,int,int,int);
float fn_800BD190(void *); float fn_800AB9EC(void *);
void fn_80142228(Camera_8013F738 *);
}

static unsigned char lbl_803EB1F0 = 0;

extern "C" void fn_80141210(Camera_8013F738 *camera, Actor_801C009C *actor, Selection_80141210 *selection, float time)
{
    float t = time / fn_801BFFA0();
    float matrix[4][4];
    fn_801D04C4(); fn_801D0558(); fn_801D0F80(matrix); fn_801D0544();
    if (!selection->mUnknown0) return;
    Sample_801C009C *sample;
    if (selection->mUnknown4.mWord == -1 || selection->mUnknown8.mWord == -1)
        sample = fn_801C00F8(actor);
    else sample = fn_801C009C(actor,1,selection->mUnknown4.mParts[1],selection->mUnknown8.mParts[1]);
    if (!sample) return;
    Vector_80039F5C base, offset, position, look, up, direction, projection;
    base.mX = sample->mUnknown0[0]; base.mY = -sample->mUnknown0[2]; base.mZ = sample->mUnknown0[1];
    offset.mX = fn_801C5278(t,&sample->mUnknownC[9],0);
    offset.mY = -fn_801C5278(t,&sample->mUnknownC[10],0);
    offset.mZ = fn_801C5278(t,&sample->mUnknownC[11],0);
    offset.mX *= camera->mUnknownF4; offset.mY *= camera->mUnknownF4; offset.mZ *= camera->mUnknownF4;
    Angles_80141210 rotation;
    rotation.mX = (int)(fn_801C5278(t,&sample->mUnknownC[12],0)*46603.37890625f);
    rotation.mY = (int)(-fn_801C5278(t,&sample->mUnknownC[14],0)*46603.37890625f);
    rotation.mZ = (int)(fn_801C5278(t,&sample->mUnknownC[13],0)*46603.37890625f);
    float qx[4],qy[4],qz[4],q[4]; Vector_80039F5C axis;
    fn_801C1F94(q,0,16); q[3] = 1.0f;
    axis.mX=1.0f; axis.mY=0.0f; axis.mZ=0.0f; fn_801EBBA4(qx,&axis,rotation.mX);
    axis.mX=0.0f; axis.mY=1.0f; axis.mZ=0.0f; fn_801EBBA4(qy,&axis,rotation.mY);
    axis.mX=0.0f; axis.mY=0.0f; axis.mZ=1.0f; fn_801EBBA4(qz,&axis,rotation.mZ);
    fn_801EB660(q,qy,qz); fn_801EB660(q,q,qx); fn_801EB814(matrix,q);
    position.mX=fn_801C5278(t,&sample->mUnknownC[0],0);
    position.mY=-fn_801C5278(t,&sample->mUnknownC[2],0);
    position.mZ=fn_801C5278(t,&sample->mUnknownC[1],0);
    position.mX*=camera->mUnknownF4; position.mY*=camera->mUnknownF4; position.mZ*=camera->mUnknownF4;
    up.mX=fn_801C5278(t,&sample->mUnknownC[6],0);
    up.mY=-fn_801C5278(t,&sample->mUnknownC[8],0);
    up.mZ=fn_801C5278(t,&sample->mUnknownC[7],0);
    up.mX*=camera->mUnknownF4; up.mY*=camera->mUnknownF4; up.mZ*=camera->mUnknownF4;
    fn_802276B4(&up,&up,&position);
    look.mX=fn_801C5278(t,&sample->mUnknownC[3],0);
    look.mY=-fn_801C5278(t,&sample->mUnknownC[5],0);
    look.mZ=fn_801C5278(t,&sample->mUnknownC[4],0);
    look.mX*=camera->mUnknownF4; look.mY*=camera->mUnknownF4; look.mZ*=camera->mUnknownF4;
    fn_802276B4(&direction,&position,&look); fn_802276B4(&look,&look,&position);
    if (fn_80227120(&look)<0.0001f) { look.mX=0.0f; look.mY=1.0f; look.mZ=0.0f; }
    if (fn_80227120(&up)<0.0001f) { up.mX=0.0f; up.mY=0.0f; up.mZ=1.0f; }
    fn_801D04C4(); fn_801D06D4(matrix);
    fn_802276B4(&position,&position,&base); fn_80227C2C(&position,&position);
    fn_8022765C(&position,&position,&base); fn_8022765C(&position,&position,&offset);
    fn_80227C2C(&up,&up); fn_80227C2C(&look,&look); fn_801D0544();
    float dot = fn_80227704(&up,&look); float length = fn_80227120(&look);
    fn_80227264(&projection,&look,dot/length); fn_802276B4(&up,&up,&projection);
    State_80141210 *state=reinterpret_cast<State_80141210 *>(camera->mPadF8);
    position.mX-=actor->mUnknown18->mUnknown34; position.mY+=actor->mUnknown18->mUnknown3C;
    fn_80227384(&position,&position,state->mUnknown14-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_80227384(&look,&look,state->mUnknown14-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_80227384(&up,&up,state->mUnknown14-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_80227384(&direction,&direction,state->mUnknown14-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_801D0508(); fn_801D0ADC(0x400000); fn_80227C2C(&direction,&direction); fn_801D0544();
    Angles_80141210 angles;
    angles.mY=0;
    angles.mZ=fn_801CFE40(direction.mY,direction.mX);
    angles.mX=fn_801CFE40(-direction.mZ,fn_80260B1C(direction.mX*direction.mX+direction.mY*direction.mY));
    fn_80227490(&up,&up,-angles.mZ,0,0); fn_80227490(&up,&up,0,0,-angles.mX);
    angles.mY=fn_801CFE40(up.mZ,up.mX)-0x400000;
    Vector_80039F5C result; Angles_80141210 resultAngles;
    fn_8014116C(position.mX,position.mY,position.mZ,&result,state,actor);
    fn_8014118C(&resultAngles,state,actor,angles.mX,angles.mY,angles.mZ);
    if (lbl_803EB1F0 && fn_80027DF0()==0) fn_801C3990(camera,35.28518295288086f,camera->mHeader.mUnknown24);
    else fn_801C3990(camera,36.77341842651367f,camera->mHeader.mUnknown24);
    fn_8013C478(camera,&result); fn_8013C4BC(camera,&resultAngles,5); fn_8013C6F0(camera); fn_80142228(camera);
}

extern "C" void fn_80141920(Camera_8013F738 *camera, Actor_801C009C *actor, int mirror, float time)
{
    State_80141210 *state=reinterpret_cast<State_80141210 *>(camera->mPadF8);
    Playback_80096DA8 *playback=fn_80096DA8(state->mUnknown10);
    float t=time/fn_801BFFA0();
    Sample_801C009C *sample=fn_801C009C(actor,playback->mUnknown14.mParts[1],playback->mUnknown18.mParts[1],playback->mUnknown1C.mParts[1]);
    if (!sample) return;
    playback->mUnknown20=(sample->mUnknownC[0].mUnknown8-sample->mUnknownC[0].mUnknown4)*fn_801BFFA0();
    Vector_80039F5C base,offset,position,up,look,projection;
    base.mX=sample->mUnknown0[0]; base.mY=-sample->mUnknown0[2]; base.mZ=sample->mUnknown0[1];
    offset.mX=fn_801C5278(t,&sample->mUnknownC[11],0);
    offset.mY=-fn_801C5278(t,&sample->mUnknownC[9],0);
    offset.mZ=fn_801C5278(t,&sample->mUnknownC[10],0);
    Angles_80141210 rotation;
    rotation.mX=(int)(fn_801C5278(t,&sample->mUnknownC[12],0)*46603.37890625f);
    rotation.mY=(int)(-fn_801C5278(t,&sample->mUnknownC[14],0)*46603.37890625f);
    rotation.mZ=(int)(fn_801C5278(t,&sample->mUnknownC[13],0)*46603.37890625f);
    float q[4],qx[4],qy[4],qz[4],matrix[4][4]; Vector_80039F5C axis;
    fn_801C1F94(q,0,16); q[3]=1.0f;
    axis.mX=1.0f; axis.mY=0.0f; axis.mZ=0.0f; fn_801EBBA4(qx,&axis,rotation.mX);
    axis.mX=0.0f; axis.mY=1.0f; axis.mZ=0.0f; fn_801EBBA4(qy,&axis,rotation.mY);
    axis.mX=0.0f; axis.mY=0.0f; axis.mZ=1.0f; fn_801EBBA4(qz,&axis,rotation.mZ);
    fn_801EB660(q,qy,qz); fn_801EB660(q,q,qx); fn_801EB814(matrix,q);
    fn_801D04C4(); fn_801D06D4(matrix); if (mirror) fn_801D0ADC(0x800000); fn_801D0F80(matrix); fn_801D0544();
    position.mX=fn_801C5278(t,&sample->mUnknownC[0],0);
    position.mY=-fn_801C5278(t,&sample->mUnknownC[2],0);
    position.mZ=fn_801C5278(t,&sample->mUnknownC[1],0);
    up.mX=fn_801C5278(t,&sample->mUnknownC[6],0);
    up.mY=-fn_801C5278(t,&sample->mUnknownC[8],0);
    up.mZ=fn_801C5278(t,&sample->mUnknownC[7],0);
    fn_802276B4(&up,&up,&position);
    look.mX=fn_801C5278(t,&sample->mUnknownC[3],0);
    look.mY=-fn_801C5278(t,&sample->mUnknownC[5],0);
    look.mZ=fn_801C5278(t,&sample->mUnknownC[4],0);
    fn_802276B4(&look,&look,&position);
    if (fn_80227120(&look)<0.0001f) { look.mX=0.0f; look.mY=1.0f; look.mZ=0.0f; }
    if (fn_80227120(&up)<0.0001f) { up.mX=0.0f; up.mY=0.0f; up.mZ=1.0f; }
    fn_801D04C4(); fn_801D06D4(matrix);
    fn_802276B4(&position,&position,&base); fn_80227C2C(&position,&position);
    fn_8022765C(&position,&position,&base); fn_8022765C(&position,&position,&offset);
    fn_80227C2C(&up,&up); fn_80227C2C(&look,&look); fn_801D0544();
    float dot=fn_80227704(&up,&look); float length=fn_80227120(&look);
    fn_80227264(&projection,&look,dot/length); fn_802276B4(&up,&up,&projection);
    Angles_80141210 angles;
    angles.mZ=fn_801CFE40(look.mY,look.mX)-0x400000;
    fn_80227490(&look,&look,-angles.mZ,0,0);
    angles.mX=fn_801CFE40(look.mZ,look.mY);
    fn_80227490(&up,&up,-angles.mZ,0,0); fn_80227490(&up,&up,0,0,-angles.mX);
    angles.mY=fn_801CFE40(up.mZ,up.mX)-0x400000;
    Vector_80039F5C result; Angles_80141210 resultAngles;
    fn_8014116C(position.mX,position.mY,position.mZ,&result,state,actor);
    fn_8014118C(&resultAngles,state,actor,angles.mX,angles.mY,angles.mZ);
    if (lbl_803EB1F0 && fn_80027DF0()==0) fn_801C3990(camera,35.28518295288086f,camera->mHeader.mUnknown24);
    else fn_801C3990(camera,36.77341842651367f,camera->mHeader.mUnknown24);
    fn_8013C478(camera,&result); fn_8013C4BC(camera,&resultAngles,5); fn_8013C6F0(camera); fn_80142228(camera);
}

extern "C" void fn_80141E8C(Camera_8013F738 *camera)
{
    switch (camera->mUnknownA0) {
    case 10: {
        Entry_801411B4 *entry=fn_801411B4(camera);
        if (entry) {
            Character_80093BCC *character=fn_80093BCC(entry->mUnknown8);
            Actor_801C009C *actor=fn_80093BAC(character->mUnknown0,character->mUnknown4);
            Settings_800963EC *settings=fn_800963EC(character);
            if (actor->mUnknown8&0x200) camera->mUnknownF4=1.0f;
            else camera->mUnknownF4=settings->mUnknown300;
            fn_80141210(camera,actor,&character->mUnknownE0,entry->mUnknown0);
        }
        break;
    }
    case 11: {
        State_80141210 *state=reinterpret_cast<State_80141210 *>(camera->mPadF8);
        Playback_80096DA8 *playback=fn_80096DA8(state->mUnknown10);
        int mirror=0;
        if (playback->mUnknown0!=-1 && playback->mUnknown10==2) {
            if ((playback->mUnknownC&0x10) && fn_801784C4()!=0) mirror=1;
            Actor_801C009C *actor=fn_80096DCC(playback->mUnknown0,playback->mUnknown4);
            fn_80141920(camera,actor,mirror,playback->mUnknown24);
        }
    }
    }
}
extern "C" void fn_80141FA0(Camera_8013F738 *camera)
{
    State_80141210 *state=reinterpret_cast<State_80141210 *>(camera->mPadF8);
    if (camera->mUnknownA0<=5) {
        fn_8013C478(camera,&lbl_802DCEB0[camera->mUnknownA0].mUnknown0);
        fn_8013C4BC(camera,&lbl_802DCEB0[camera->mUnknownA0].mUnknownC,lbl_802DCEB0[camera->mUnknownA0].mUnknown18);
    }
    switch(camera->mUnknownA0) {
    case 7:
        fn_8013C478(camera,&lbl_802DCF58.mUnknown0);
        fn_8013C4BC(camera,&lbl_802DCF58.mUnknownC,lbl_802DCF58.mUnknown18);
        break;
    case 10: {
        Entry_801411B4 *entry=fn_801411B4(camera);
        if (entry) {
            Character_80093BCC *character=fn_80093BCC(entry->mUnknown8);
            Actor_801C009C *actor=fn_80093BAC(character->mUnknown0,character->mUnknown4);
            state->mUnknown14=character->mUnknown14->mUnknown1C0;
            fn_80141210(camera,actor,&character->mUnknownE0,entry->mUnknown0);
        }
        break;
    }
    case 11: {
        Playback_80096DA8 *playback=fn_80096DA8(state->mUnknown10);
        int mirror=0;
        if (playback->mUnknown0!=-1 && playback->mUnknown10==2) {
            if ((playback->mUnknownC&0x10) && fn_801784C4()!=0) mirror=1;
            Actor_801C009C *actor=fn_80096DCC(playback->mUnknown0,playback->mUnknown4);
            fn_80141920(camera,actor,mirror,playback->mUnknown24);
        }
        break;
    }
    }
}
extern "C" void fn_80142110(Camera_8013F738 *camera,int event,int argument)
{
    switch(event) {
    case 4:
        if (argument!=-1) {
            Camera_8013F738 *other=fn_8013FA04(argument);
            fn_801C3EA4(camera,other->mHeader.mUnknown04[0],other->mHeader.mUnknown04[1],other->mHeader.mUnknown04[2]);
            fn_801C3ED0(camera,other->mHeader.mUnknown14,other->mHeader.mUnknown18,other->mHeader.mUnknown1C);
            fn_8013C384(camera,0,0,0);
        }
        break;
    case 3: fn_80141E8C(camera); break;
    case 1: fn_80141FA0(camera); break;
    }
}
extern "C" void fn_801421C4(Camera_8013F738 *camera)
{
    camera->mUnknownDC=reinterpret_cast<void (*)(Camera_8013F738 *,int)>(fn_80142110);
    int *angles=reinterpret_cast<int *>(&camera->mUnknown74);
    angles[3]=0xCCCCC;
    camera->mUnknown5C=0.2f; camera->mUnknown68=0.1f;
    angles[0]=0x199999;
    camera->mUnknown64=0.2f; camera->mUnknown60=0.2f;
    camera->mUnknown70=0.1f; camera->mUnknown6C=0.1f;
    angles[2]=0x199999; angles[1]=0x199999;
    camera->mUnknown88=0xCCCCC; camera->mUnknown84=0xCCCCC;
}
extern "C" void fn_80142224(Camera_8013F738 *) {}
extern "C" void fn_80142228(Camera_8013F738 *camera)
{
    float value=0.08f;
    if (camera->mUnknownA0!=11) {
        if (fn_800AD9B4()==1) value=fn_800BD190(lbl_803EAB90);
        else if (fn_800AD9B4()==7) value=fn_800AB9EC(lbl_803EAA8C);
    }
    if (camera->mUnknown28)
        fn_802286D8(static_cast<Object_80228224 *>(camera->mUnknown28),camera->mHeader.mUnknown20,camera->mHeader.mUnknown24,value,750.0f);
}
extern "C" void fn_801422C0(unsigned char value) { lbl_803EB1F0=value; }
