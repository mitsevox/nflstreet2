#include "game/fn_80177FE0.h"
#include "game/Camera_8013F738.h"
#include "game/fn_8007F828.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/Team_80167A8C.h"
#include <math.h>
#include "engine/cu_80227F14.h"
#include "game/Lookup_8012078C.h"

struct Vector_8013FF84 { float mX,mY,mZ; };
struct Angles_8013FF84 { int mX,mY,mZ; };
struct View_8013FF84 { Vector_8013FF84 mUnknown0; Angles_8013FF84 mUnknownC; int mUnknown18; };
struct State_8013FF84 {
    unsigned int mUnknown0[3];
    unsigned int mUnknownC;
    int mUnknown10;
    unsigned char mUnknown14[12];
    Vector_8013FF84 mUnknown20;
    Angles_8013FF84 mUnknown2C;
    float mUnknown38;
};
struct Mode_8013FF84 {
    View_8013FF84 *mUnknown0;
    int mUnknown4;
    float mUnknown8;
    float mUnknownC[2];
    float mUnknown14[2][2];
    Vector_8013FF84 mUnknown24;
    Vector_8013FF84 mUnknown30;
    Vector_8013FF84 mUnknown3C;
    Vector_8013FF84 mUnknown48;
    Vector_8013FF84 mUnknown54;
    Vector_8013FF84 mUnknown60;
};
struct Entry_8013FF84 {
    unsigned int mUnknown0,mUnknown4;
    float mUnknown8,mUnknownC;
    Vector_8013FF84 mUnknown10;
    unsigned char mUnknown1C,mUnknown1D;
    unsigned char mUnknown1E[2];
};
struct Control_8013FF84 {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    unsigned int mUnknown4,mUnknown8,mUnknownC;
};
extern "C" Control_8013FF84 lbl_802DBEBC;
extern "C" Entry_8013FF84 lbl_802DBECC[];
extern "C" Mode_8013FF84 lbl_802DC718[];
extern "C" Angles_8013FF84 lbl_8031B6B8;
extern "C" Vector_8013FF84 lbl_8031B6AC;
static float lbl_803EB1E4 = 1.0f;
static unsigned char lbl_803EB1E8 = 0;
static float lbl_803EB1EC = 120.0f;
static View_8013FF84 *lbl_803ECA04;
static float lbl_803ECA08;
extern "C" {
void fn_8013FF28(Camera_8013F738 *, int);
unsigned int fn_802372EC(unsigned int,unsigned int);
void fn_8022765C(void *,void *,void *);
int fn_801CFDD0(float);
void fn_801C3E54(Camera_8013F738 *);
int fn_800AD9B4(void);
int fn_801784C4(void);
void fn_8013C2B4(void *,int,int,int);
void fn_8013C6F0(Camera_8013F738 *);
void fn_801CF810(void *,void *,void *,float);
void fn_8013C4BC(Camera_8013F738 *,void *,int);
void fn_80227930(void *,void *,void *,float);
void fn_801D0470(int);
void fn_801D0508(void);
void fn_801D0C58(void *);
void fn_801D0ADC(int);
void fn_801D08FC(int);
void fn_80227CC0(void *,void *);
void fn_801D0544(void);
void fn_8013FA8C(int);
int fn_801383B0(void);
void *fn_801374BC(void);
void fn_80137D58(void *,void *);
int fn_801486A0(void);
void fn_8013C478(Camera_8013F738 *,void *);
int fn_801783AC(int);
int fn_80178308(void);
void fn_8003A130(void *,float *,int);
int fn_800BA6F8(void);
int fn_800BAA24(void);
void fn_801CF910(void *,void *,void *);
int fn_80178320(void);
void fn_8013C438(Camera_8013F738 *);
void fn_8013C384(void *,int,int,int);
void fn_80067D4C(int,int);
void fn_80140DBC(Camera_8013F738 *,int);
void fn_80140EA0(Camera_8013F738 *);

void fn_8013FF84(Camera_8013F738 *camera, Vector_8013FF84 *point)
{
    if (lbl_802DBEBC.mUnknown0) {
        unsigned int index = lbl_802DBEBC.mUnknown4;
        Entry_8013FF84 *entry = &lbl_802DBECC[index];
        unsigned int ticks = ++lbl_802DBEBC.mUnknown8;
        unsigned int total = ++lbl_802DBEBC.mUnknownC;
        float scale = 1.0f;
        if (entry->mUnknown1C) scale -= (float)(total / entry->mUnknown4);
        if (ticks >= entry->mUnknown0 && total <= entry->mUnknown4) {
            Vector_8013FF84 value;
            float low = entry->mUnknown8;
            float span = (entry->mUnknownC-low)*0.01f;
            value.mX = scale*(span*(float)fn_802372EC(1,100)+low);
            value.mZ = scale*(span*(float)fn_802372EC(1,100)+low);
            value.mY = entry->mUnknown1D == 1 ? scale*(span*(float)fn_802372EC(1,100)+low) : 0.0f;
            if (value.mX < -0.3f) value.mX = -0.3f; else if (value.mX > 0.3f) value.mX = 0.3f;
            if (value.mY < -0.3f) value.mY = -0.3f; else if (value.mY > 0.3f) value.mY = 0.3f;
            if (value.mZ < -0.3f) value.mZ = -0.3f; else if (value.mZ > 0.3f) value.mZ = 0.3f;
            entry->mUnknown10 = value;
            lbl_802DBEBC.mUnknown8 = 0;
        }
        fn_8022765C(point,point,&entry->mUnknown10);
        if (lbl_802DBEBC.mUnknownC >= entry->mUnknown4) {
            lbl_802DBEBC.mUnknown8 = 0;
            if (lbl_802DBEBC.mUnknownC >= entry->mUnknown4+10) lbl_802DBEBC.mUnknown0 = 0;
        }
        fn_8013FF28(camera,2);
    }
}
void fn_80140270(Vector_8013FF84 *point, Angles_8013FF84 *angles, Vector_8013FF84 *velocity, int index, int mode)
{
    float base = lbl_802DC718[index].mUnknown8;
    float amount = velocity->mX/base*(lbl_802DC718[index].mUnknownC[1]-base);
    float length = fn_802270D4(point);
    int reset = 0;
    if (mode == 3) reset = 1;
    else if (mode == 4) length = -length;
    if (reset) {
        angles->mZ = lbl_8031B6B8.mZ;
        point->mX = lbl_8031B6AC.mX;
    } else {
        angles->mZ -= fn_801CFDD0(amount/length);
        if (mode == 4) amount = -amount;
        point->mX += amount;
        lbl_8031B6B8.mZ = angles->mZ;
        lbl_8031B6AC.mX = point->mX;
    }
}
void fn_80140360(Camera_8013F738 *camera)
{
    lbl_803ECA04 = lbl_802DC718[camera->mUnknown9C].mUnknown0;
    camera->mUnknownE0 = 0.0f;
    camera->mUnknownE4 = camera->mUnknownE5 = lbl_803EB1E8 = 0;
    camera->mUnknownE8 = 0.0f;
    camera->mUnknownDC = fn_80140DBC;
    camera->mUnknown94 |= 0x10;
    camera->mUnknownF0 = camera->mUnknownEC = 0.0f;
}
void fn_801403BC(Camera_8013F738 *camera) { camera->mUnknown94 &= ~0x10; }
void fn_801403CC(Camera_8013F738 *camera)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    camera->mUnknownE5 = lbl_803EB1E8 = 0;
    fn_801C3E54(camera);
    if (fn_800AD9B4() == 3) {
        camera->mUnknownE0 = 180.0f;
        camera->mUnknownE4 = 1;
        if (camera->mHeader.mUnknown04[0] > 0.0f) lbl_803EB1E4 = fn_801784C4() ? 1.0f : -1.0f;
        else lbl_803EB1E4 = fn_801784C4() ? -1.0f : 1.0f;
        state->mUnknown0[0] = state->mUnknown0[2] = state->mUnknown0[1] = 0;
        state->mUnknown20.mX = camera->mUnknownC4;
        state->mUnknown20.mY = camera->mUnknownC8;
        state->mUnknown20.mZ = camera->mUnknownCC;
        state->mUnknown2C.mX = camera->mUnknownD0;
        state->mUnknown2C.mY = camera->mUnknownD4;
        state->mUnknown2C.mZ = camera->mUnknownD8;
        camera->mUnknownE8 = camera->mHeader.mUnknown04[0];
        camera->mUnknownEC = camera->mHeader.mUnknown04[1];
        camera->mUnknownF0 = camera->mHeader.mUnknown04[2];
        fn_80227638(&camera->mUnknownE8,&camera->mUnknownE8,&camera->mUnknownC4);
    } else {
        fn_8013C2B4(camera,0,0,0);
        fn_8013C6F0(camera);
    }
}
unsigned char fn_80140504(Camera_8013F738 *camera)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    Vector_8013FF84 zero;
    fn_801C1F94(&zero,0,12);
    camera->mUnknownE0 += lbl_803EB1E4*6.0f;
    if (fabsf(camera->mUnknownE0-180.0f) <= 180.0f && fn_800AD9B4() != 10) {
        float blend = fabsf(camera->mUnknownE0-180.0f)*0.0055555557f;
        if (blend < 0.0f) blend = 0.0f; else if (blend > 1.0f) blend = 1.0f;
        Angles_8013FF84 angles;
        fn_801CF810(&angles,&lbl_803ECA04[1].mUnknownC,&state->mUnknown2C,blend);
        angles.mZ = (int)(camera->mUnknownE0*46603.37890625f);
        fn_8013C4BC(camera,&angles,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        Vector_8013FF84 point;
        fn_80227930(&point,&lbl_803ECA04[1],&state->mUnknown20,blend);
        float z = point.mZ;
        fn_801D0470(fn_80228668());fn_801D0508();fn_801D0C58(&zero);
        fn_801D0ADC(-(int)(camera->mUnknownE0*46603.37890625f));
        fn_801D08FC(0x400000);
        Vector_8013FF84 offset = {0.0f,0.0f,fn_802270A4(&state->mUnknown20)};
        fn_80227CC0(&point,&offset);
        fn_801D0544();
        camera->mUnknownCC = z;
        camera->mUnknownC4 = point.mX;
        camera->mUnknownC8 = point.mY;
        fn_8013C6F0(camera);
    } else {
        camera->mUnknownE4 = 0;
        fn_801C3E54(camera);
        fn_8013FA8C(1);
        camera->mUnknown94 |= 0x10;
    }
    return camera->mUnknownE4;
}
unsigned char fn_80140700(Camera_8013F738 *camera) { return camera->mUnknownE4; }
void fn_80140708(Camera_8013F738 *camera)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    Vector_8013FF84 velocity;
    if (fn_801383B0()) {
        fn_80137D58(fn_801374BC(),&velocity);
        float bound = lbl_802DC718[camera->mUnknown9C].mUnknown8;
        if (velocity.mX < -bound) velocity.mX = -bound; else if (velocity.mX > bound) velocity.mX = bound;
    } else velocity.mX = velocity.mZ = velocity.mY = 0.0f;
    fn_80177FE0();
    fn_8013FF28(camera,0);
    switch (camera->mUnknownA0) {
    case 12:
        if (fn_801486A0() == 1) {
            Angles_8013FF84 angles;
            fn_801C1F94(&angles,0,12);
            Mode_8013FF84 *mode = &lbl_802DC718[camera->mUnknown9C];
            angles.mX = (int)(mode->mUnknown48.mX * 46603.37890625f);
            angles.mY = (int)(mode->mUnknown48.mY * 46603.37890625f);
            angles.mZ = (int)(mode->mUnknown48.mZ * 46603.37890625f);
            fn_8013C478(camera,&mode->mUnknown3C);
            fn_8013C4BC(camera,&angles,5);
        }
        break;
    case 3: fn_8013FF28(camera,1);
    case 1: case 2: case 4: {
        int gameMode = fn_800AD9B4();
        Vector_8013FF84 point;
        Angles_8013FF84 angles;
        float extra = 0.0f;
        float blend = 0.0f;
        int special = camera->mUnknownA4 == 0 && gameMode == 2;
        if (state->mUnknown38 < 1.0f) {
            if (special) {
                state->mUnknown38 += 1.0f/lbl_803EB1EC;
                if (state->mUnknown38 < 0.0f) state->mUnknown38 = 0.0f;
                else if (state->mUnknown38 > 1.0f) state->mUnknown38 = 1.0f;
            } else state->mUnknown38 = 1.0f;
            fn_80227930(&point,&lbl_803ECA04[1],&state->mUnknown20,state->mUnknown38);
            fn_801CF810(&angles,&lbl_803ECA04[1].mUnknownC,&state->mUnknown2C,state->mUnknown38);
            if (special) goto apply;
        }
        if (fn_801783AC(0)) {
            fn_8003A130(&velocity,&extra,fn_80178308());
            extra -= 4.0f;
            if (extra > 0.0f) {
                blend = extra * 0.16666667f;
                if (blend < 0.0f) blend = 0.0f; else if (blend > 1.0f) blend = 1.0f;
            }
        }
        if (fn_800BA6F8() && fn_800BAA24()) blend = 0.0f;
        fn_80227930(&point,&lbl_803ECA04[1],&lbl_803ECA04[camera->mUnknownA0],blend);
        fn_801CF810(&angles,&lbl_803ECA04[1].mUnknownC,&lbl_803ECA04[camera->mUnknownA0].mUnknownC,blend);
    apply:
        if (gameMode != 2) fn_80140270(&point,&angles,&velocity,camera->mUnknown9C,camera->mUnknownA0);
        if (fn_801486A0() == 0) {
            Mode_8013FF84 *mode = &lbl_802DC718[camera->mUnknown9C];
            fn_8022765C(&point,&point,&mode->mUnknown24);
            Angles_8013FF84 offset;
            fn_801C1F94(&offset,0,12);
            offset.mX = (int)(mode->mUnknown30.mX*46603.37890625f);
            offset.mY = (int)(mode->mUnknown30.mY*46603.37890625f);
            offset.mZ = (int)(mode->mUnknown30.mZ*46603.37890625f);
            fn_801CF910(&angles,&angles,&offset);
        }
        if (fn_801486A0() == 2) {
            Mode_8013FF84 *mode = &lbl_802DC718[camera->mUnknown9C];
            fn_8022765C(&point,&point,&mode->mUnknown54);
            Angles_8013FF84 offset;
            fn_801C1F94(&offset,0,12);
            offset.mX = (int)(mode->mUnknown60.mX*46603.37890625f);
            offset.mY = (int)(mode->mUnknown60.mY*46603.37890625f);
            offset.mZ = (int)(mode->mUnknown60.mZ*46603.37890625f);
            fn_801CF910(&angles,&angles,&offset);
        } else if (!fn_8007F828(18) && !fn_800BA6F8() && fn_800AD9B4() == 3 && camera->mUnknownA0 == 1) {
            int side = fn_80178320();
            Object_80039F5C *player = fn_80039F5C(side,*fn_8012078C()->mpUnknown4);
            if (player && velocity.mY > player->mMotion.mPos.mY) {
                float adjustment = (velocity.mY-player->mMotion.mPos.mY)*0.5f;
                if (adjustment >= 0.0f) {
                    if (adjustment > 10.0f) adjustment = 10.0f;
                    point.mY -= adjustment;
                }
            }
        }
        fn_8013FF84(camera,&point);
        point.mY -= lbl_803ECA08;
        fn_8013C478(camera,&point);
        fn_8013C4BC(camera,&angles,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        break;
    }
    case 5: state->mUnknownC = 0; break;
    }
}
unsigned char fn_80140DB4(void) { return lbl_803EB1E8; }
void fn_80140DBC(Camera_8013F738 *camera, int message)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    switch (message) {
    case 3:
        if (fn_80140700(camera)) fn_80140504(camera);
        else fn_80140708(camera);
        break;
    case 1: fn_80140EA0(camera); break;
    case 2: camera->mUnknownE5 ^= 1; lbl_803EB1E8 = 1; break;
    case 5: if (camera->mUnknownE5) fn_801403CC(camera); break;
    case 6: case 7: case 8: case 9: case 10: state->mUnknownC |= 1u << message; break;
    }
}
void fn_80140EA0(Camera_8013F738 *camera)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    state->mUnknown38 = 0.0f;
    state->mUnknown10 = 0;
    state->mUnknown20.mX = camera->mUnknownC4;
    state->mUnknown20.mY = camera->mUnknownC8;
    state->mUnknown20.mZ = camera->mUnknownCC;
    state->mUnknown2C.mX = camera->mUnknownD0;
    state->mUnknown2C.mY = camera->mUnknownD4;
    state->mUnknown2C.mZ = camera->mUnknownD8;
    fn_801C3E54(camera);
    lbl_802DBEBC.mUnknown0 = 0;
    switch (camera->mUnknownA0) {
    case 1:
        if (fn_801383B0()) fn_8013C438(camera);
        if (camera->mUnknownA4 == 0 || camera->mUnknownA4 == 5) break;
        fn_8013C478(camera,&lbl_803ECA04[camera->mUnknownA0]);
        fn_8013C4BC(camera,&lbl_803ECA04[camera->mUnknownA0].mUnknownC,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        break;
    case 4:
        fn_8013C384(camera,6,0,0);
        state->mUnknown38 = 1.0f;
        break;
    case 5: state->mUnknownC = 0;
    default:
        if (fn_801383B0()) fn_8013C438(camera);
        fn_8013C478(camera,&lbl_803ECA04[camera->mUnknownA0]);
        fn_8013C4BC(camera,&lbl_803ECA04[camera->mUnknownA0].mUnknownC,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        break;
    case 10: case 11: case 12: break;
    }
    int mode = fn_801486A0();
    if (mode != 15 && mode == 1 && (unsigned int)camera->mUnknownA0 <= 2) camera->mUnknownA0 = 12;
}
int fn_80141054(int index) { return lbl_802DC718[index].mUnknown4; }
void fn_8014106C(int index, unsigned int mode, float *a, float *b)
{
    int alternate = 0;
    switch (mode) {
    case 2: case 3: case 5: alternate = 1; break;
    case 0: case 1: case 4: case 7: case 8: case 9: case 10: case 11: case 12: alternate = 0; break;
    }
    a[0] = lbl_802DC718[index].mUnknownC[0];
    a[1] = lbl_802DC718[index].mUnknownC[1];
    b[0] = lbl_802DC718[index].mUnknown14[alternate][0];
    b[1] = lbl_802DC718[index].mUnknown14[alternate][1];
}
void fn_801410F4(unsigned int index)
{
    if (!lbl_802DBEBC.mUnknown0 && fn_8007F828(10)) {
        lbl_802DBEBC.mUnknown0 = 1;
        lbl_802DBEBC.mUnknownC = 0;
        lbl_802DBEBC.mUnknown4 = index;
        lbl_802DBEBC.mUnknown8 = 100;
        fn_80067D4C(17,0);
    }
}
void fn_80141164(float amount) { lbl_803ECA08 = amount; }
}
