#include "game/fn_80177FE0.h"
#include "game/GameCamera.h"
#include "game/GameOptions.h"
#include <string.h>
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/PlayBookTeam.h"
#include <math.h>
#include "engine/viewport.h"
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
void CamPresetSetEaseRates(GameCamera_t *, int);
unsigned int fn_802372EC(unsigned int,unsigned int);
void fn_8022765C(void *,void *,void *);
int fn_801CFDD0(float);
void CamFreeClearVelocity(GameCamera_t *);
int fn_800AD9B4(void);
int fn_801784C4(void);
void CamMainProcess(void *,int,int,int);
void CamMainWarpToDest(GameCamera_t *);
void Orient3Lerp(void *,void *,void *,float);
void CamMainSetAngle(GameCamera_t *,void *,int);
void fn_80227930(void *,void *,void *,float);
void fn_801D0470(int);
void fn_801D0508(void);
void fn_801D0C58(void *);
void fn_801D0ADC(int);
void fn_801D08FC(int);
void fn_80227CC0(void *,void *);
void fn_801D0544(void);
void CamGameSetModeAll(int);
int BallsExist(void);
void *BallGetCurrent(void);
void BallGetPosition(void *,void *);
int fn_801486A0(void);
void CamMainSetOffset(GameCamera_t *,void *);
int fn_801783AC(int);
int fn_80178308(void);
void PlyrFindNearest(void *,float *,int);
int fn_800BA6F8(void);
int fn_800BAA24(void);
void Orient3Add(void *,void *,void *);
int fn_80178320(void);
void CamMainFollowBall(GameCamera_t *);
void CamMainFollow(void *,int,int,int);
void AudmonEventPost(int,int);
void fn_80140DBC(GameCamera_t *,int,int);
void fn_80140EA0(GameCamera_t *);

void fn_8013FF84(GameCamera_t *camera, Vector_8013FF84 *point)
{
    unsigned int index = lbl_802DBEBC.mUnknown4;
    if (lbl_802DBEBC.mUnknown0) {
        unsigned int ticks = ++lbl_802DBEBC.mUnknown8;
        unsigned int total = ++lbl_802DBEBC.mUnknownC;
        float scale = 1.0f;
        if (lbl_802DBECC[index].mUnknown1C) scale -= (float)(total / lbl_802DBECC[index].mUnknown4);
        if (ticks >= lbl_802DBECC[index].mUnknown0 && total <= lbl_802DBECC[index].mUnknown4) {
            Vector_8013FF84 value;
            float low = lbl_802DBECC[index].mUnknown8;
            float range = lbl_802DBECC[index].mUnknownC-low;
            value.mX = scale*(low+range*((float)fn_802372EC(1,100)*0.01f));
            value.mZ = scale*(low+range*((float)fn_802372EC(1,100)*0.01f));
            value.mY = lbl_802DBECC[index].mUnknown1D == 1 ? scale*(low+range*((float)fn_802372EC(1,100)*0.01f)) : 0.0f;
            value.mX = value.mX < -0.3f ? -0.3f : (value.mX > 0.3f ? 0.3f : value.mX);
            value.mY = value.mY < -0.3f ? -0.3f : (value.mY > 0.3f ? 0.3f : value.mY);
            value.mZ = value.mZ < -0.3f ? -0.3f : (value.mZ > 0.3f ? 0.3f : value.mZ);
            Vector_8013FF84 *dst = &lbl_802DBECC[index].mUnknown10;
            dst->mX = value.mX;
            dst->mY = value.mY;
            dst->mZ = value.mZ;
            lbl_802DBEBC.mUnknown8 = 0;
        }
        fn_8022765C(point,point,&lbl_802DBECC[index].mUnknown10);
        if (lbl_802DBEBC.mUnknownC >= lbl_802DBECC[index].mUnknown4) {
            lbl_802DBEBC.mUnknown8 = 0;
            if (lbl_802DBEBC.mUnknownC >= lbl_802DBECC[index].mUnknown4+10) lbl_802DBEBC.mUnknown0 = 0;
        }
        CamPresetSetEaseRates(camera,2);
    }
}
void fn_80140270(Vector_8013FF84 *point, Angles_8013FF84 *angles, Vector_8013FF84 *velocity, int index, int mode)
{
    float base = lbl_802DC718[index].mUnknown8;
    float amount = velocity->mX/base*(lbl_802DC718[index].mUnknownC[1]-base);
    float length = fn_802270D4(point);
    int reset = 0;
    switch (mode) {
    case 4: length = -length; break;
    case 3: reset = 1; break;
    }
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
void fn_80140360(GameCamera_t *camera)
{
    lbl_803ECA04 = lbl_802DC718[camera->mUnknown9C].mUnknown0;
    camera->mUnknownE0 = 0.0f;
    camera->mUnknownE4 = 0;
    camera->mUnknownE5 = 0;
    lbl_803EB1E8 = 0;
    camera->mUnknownF0 = 0.0f;
    camera->mUnknownEC = 0.0f;
    camera->mUnknownE8 = 0.0f;
    camera->mUnknownDC = fn_80140DBC;
    camera->mUnknown94 |= 0x10;
}
void fn_801403BC(GameCamera_t *camera) { camera->mUnknown94 &= ~0x10; }
void fn_801403CC(GameCamera_t *camera)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    camera->mUnknownE5 = 0;
    lbl_803EB1E8 = 0;
    CamFreeClearVelocity(camera);
    if (fn_800AD9B4() == 3) {
        camera->mUnknownE0 = 180.0f;
        camera->mUnknownE4 = 1;
        if (camera->mHeader.mUnknown04[0] > 0.0f) {
            if (fn_801784C4()) lbl_803EB1E4 = 1.0f; else lbl_803EB1E4 = -1.0f;
        } else {
            if (fn_801784C4()) lbl_803EB1E4 = -1.0f; else lbl_803EB1E4 = 1.0f;
        }
        state->mUnknown0[2] = 0;
        state->mUnknown0[1] = 0;
        state->mUnknown0[0] = 0;
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
        CamMainProcess(camera,0,0,0);
        CamMainWarpToDest(camera);
    }
}
unsigned char fn_80140504(GameCamera_t *camera)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    Angles_8013FF84 angles;
    Vector_8013FF84 offset;
    Vector_8013FF84 point;
    Vector_8013FF84 zero = {0.0f, 0.0f, 0.0f};
    float blend = 0.0f;
    camera->mUnknownE0 += lbl_803EB1E4*6.0f;
    if (fabsf(camera->mUnknownE0-180.0f) <= 180.0f && fn_800AD9B4() != 10) {
        blend = fabsf(camera->mUnknownE0-180.0f)*0.0055555557f;
        blend = blend < 0.0f ? 0.0f : (blend > 1.0f ? 1.0f : blend);
        Orient3Lerp(&angles,&lbl_803ECA04[1].mUnknownC,&state->mUnknown2C,blend);
        angles.mZ = (int)(camera->mUnknownE0*46603.37890625f);
        CamMainSetAngle(camera,&angles,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        fn_80227930(&point,&lbl_803ECA04[1],&state->mUnknown20,blend);
        float z = point.mZ;
        fn_801D0470(VptGetMatrixStack());fn_801D0508();fn_801D0C58(&zero);
        fn_801D0ADC(-(int)(camera->mUnknownE0*46603.37890625f));
        fn_801D08FC(0x400000);
        offset.mY = offset.mX = 0.0f;
        offset.mZ = fn_802270A4(&state->mUnknown20);
        fn_80227CC0(&point,&offset);
        fn_801D0544();
        camera->mUnknownCC = z;
        camera->mUnknownC4 = point.mX;
        camera->mUnknownC8 = point.mY;
        CamMainWarpToDest(camera);
    } else {
        camera->mUnknownE4 = 0;
        CamFreeClearVelocity(camera);
        CamGameSetModeAll(1);
        camera->mUnknown94 |= 0x10;
    }
    return camera->mUnknownE4;
}
unsigned char fn_80140700(GameCamera_t *camera) { return camera->mUnknownE4; }
/* Converts a vector of degrees to the 24-bit integer angle units. */
#define ANGLES_FROM_DEGREES(dst, degrees) \
    { \
        Angles_8013FF84 angles_ = {0, 0, 0}; \
        angles_.mX = (int)((degrees).mX*46603.37890625f); \
        angles_.mY = (int)((degrees).mY*46603.37890625f); \
        angles_.mZ = (int)((degrees).mZ*46603.37890625f); \
        (dst) = angles_; \
    }
void fn_80140708(GameCamera_t *camera)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    Vector_8013FF84 point;
    Vector_8013FF84 velocity;
    Angles_8013FF84 angles;
    Angles_8013FF84 offset;
    if (BallsExist()) {
        BallGetPosition(BallGetCurrent(),&velocity);
        float bound = lbl_802DC718[camera->mUnknown9C].mUnknown8;
        velocity.mX = velocity.mX < -bound ? -bound : (velocity.mX > bound ? bound : velocity.mX);
    } else velocity.mX = velocity.mZ = velocity.mY = 0.0f;
    fn_80177FE0();
    CamPresetSetEaseRates(camera,0);
    switch (camera->mUnknownA0) {
    case 12:
        if (fn_801486A0() == 1) {
            ANGLES_FROM_DEGREES(offset, lbl_802DC718[camera->mUnknown9C].mUnknown48);
            CamMainSetOffset(camera,&lbl_802DC718[camera->mUnknown9C].mUnknown3C);
            CamMainSetAngle(camera,&offset,5);
        }
        break;
    case 3: CamPresetSetEaseRates(camera,1);
    case 1: case 2: case 4: {
        int gameMode = fn_800AD9B4();
        float extra = 0.0f;
        float blend = 0.0f;
        if (camera->mUnknownA4 == 0 && gameMode == 2) {
            if (state->mUnknown38 < 1.0f) {
                state->mUnknown38 += 1.0f/lbl_803EB1EC;
                state->mUnknown38 = state->mUnknown38 < 0.0f ? 0.0f : (state->mUnknown38 > 1.0f ? 1.0f : state->mUnknown38);
                fn_80227930(&point,&lbl_803ECA04[1],&state->mUnknown20,state->mUnknown38);
                Orient3Lerp(&angles,&lbl_803ECA04[1].mUnknownC,&state->mUnknown2C,state->mUnknown38);
                goto apply;
            }
        } else if (state->mUnknown38 < 1.0f) {
            state->mUnknown38 = 1.0f;
            fn_80227930(&point,&lbl_803ECA04[1],&state->mUnknown20,state->mUnknown38);
            Orient3Lerp(&angles,&lbl_803ECA04[1].mUnknownC,&state->mUnknown2C,state->mUnknown38);
        }
        if (fn_801783AC(0)) {
            PlyrFindNearest(&velocity,&extra,fn_80178308());
            extra -= 4.0f;
            if (extra > 0.0f) {
                blend = extra*0.16666667f;
                blend = blend < 0.0f ? 0.0f : (blend > 1.0f ? 1.0f : blend);
            }
        }
        if (fn_800BA6F8() && fn_800BAA24()) blend = 0.0f;
        fn_80227930(&point,&lbl_803ECA04[1],&lbl_803ECA04[camera->mUnknownA0],blend);
        Orient3Lerp(&angles,&lbl_803ECA04[1].mUnknownC,&lbl_803ECA04[camera->mUnknownA0].mUnknownC,blend);
    apply:
        if (gameMode != 2) fn_80140270(&point,&angles,&velocity,camera->mUnknown9C,camera->mUnknownA0);
        if (fn_801486A0() == 0) {
            fn_8022765C(&point,&point,&lbl_802DC718[camera->mUnknown9C].mUnknown24);
            ANGLES_FROM_DEGREES(offset, lbl_802DC718[camera->mUnknown9C].mUnknown30);
            Orient3Add(&angles,&angles,&offset);
        }
        if (fn_801486A0() == 2) {
            fn_8022765C(&point,&point,&lbl_802DC718[camera->mUnknown9C].mUnknown54);
            ANGLES_FROM_DEGREES(offset, lbl_802DC718[camera->mUnknown9C].mUnknown60);
            Orient3Add(&angles,&angles,&offset);
        } else if (!GameOptionsGet(18) && !fn_800BA6F8() && fn_800AD9B4() == 3 && camera->mUnknownA0 == 1) {
            int side = fn_80178320();
            Object_80039F5C *player = PlyrGet(side,*fn_8012078C()->mpUnknown4);
            if (player && velocity.mY > player->mMotion.mPos.mY) {
                float adjustment = (velocity.mY-player->mMotion.mPos.mY)*0.5f;
                point.mY -= adjustment < 0.0f ? 0.0f : (adjustment > 10.0f ? 10.0f : adjustment);
            }
        }
        fn_8013FF84(camera,&point);
        point.mY -= lbl_803ECA08;
        CamMainSetOffset(camera,&point);
        CamMainSetAngle(camera,&angles,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        break;
    }
    case 5: state->mUnknownC = 0; break;
    }
}
unsigned char fn_80140DB4(void) { return lbl_803EB1E8; }
void fn_80140DBC(GameCamera_t *camera, int message, int)
{
    State_8013FF84 *state = (State_8013FF84 *)&camera->mPadF8;
    switch (message) {
    case 3:
        if (fn_80140700(camera)) fn_80140504(camera);
        else fn_80140708(camera);
        break;
    case 1: fn_80140EA0(camera); break;
    case 2: camera->mUnknownE5 ^= 1; lbl_803EB1E8 = 1; break;
    case 0: case 4: case 11: break;
    case 5: if (camera->mUnknownE5) fn_801403CC(camera); break;
    case 6: case 7: case 8: case 9: case 10: state->mUnknownC |= 1u << message; break;
    }
}
void fn_80140EA0(GameCamera_t *camera)
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
    CamFreeClearVelocity(camera);
    lbl_802DBEBC.mUnknown0 = 0;
    switch (camera->mUnknownA0) {
    case 1:
        if (BallsExist()) CamMainFollowBall(camera);
        if (camera->mUnknownA4 == 0 || camera->mUnknownA4 == 5) break;
        CamMainSetOffset(camera,&lbl_803ECA04[camera->mUnknownA0]);
        CamMainSetAngle(camera,&lbl_803ECA04[camera->mUnknownA0].mUnknownC,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        break;
    case 4:
        CamMainFollow(camera,6,0,0);
        state->mUnknown38 = 1.0f;
        break;
    case 5: state->mUnknownC = 0;
    case 2:
    default:
        if (BallsExist()) CamMainFollowBall(camera);
        CamMainSetOffset(camera,&lbl_803ECA04[camera->mUnknownA0]);
        CamMainSetAngle(camera,&lbl_803ECA04[camera->mUnknownA0].mUnknownC,lbl_803ECA04[camera->mUnknownA0].mUnknown18);
        break;
    case 10: case 11: case 12: break;
    }
    int mode = fn_801486A0();
    if (mode != 15) {
        if (mode == 1 && (unsigned int)camera->mUnknownA0 <= 2) camera->mUnknownA0 = 12;
    }
}
int fn_80141054(int index) { return lbl_802DC718[index].mUnknown4; }
void fn_8014106C(int index, unsigned int mode, float *a, float *b)
{
    int alternate = 0;
    switch (mode) {
    case 0: case 1: case 4: case 7: case 8: case 9: case 10: case 11: case 12: alternate = 0; break;
    case 2: case 3: case 5: alternate = 1; break;
    }
    float *pa = lbl_802DC718[index].mUnknownC;
    float *pb = lbl_802DC718[index].mUnknown14[alternate];
    a[0] = pa[0];
    a[1] = pa[1];
    b[0] = pb[0];
    b[1] = pb[1];
}
void fn_801410F4(unsigned int index)
{
    if (!lbl_802DBEBC.mUnknown0 && GameOptionsGet(10)) {
        lbl_802DBEBC.mUnknown0 = 1;
        lbl_802DBEBC.mUnknown4 = index;
        lbl_802DBEBC.mUnknown8 = 100;
        lbl_802DBEBC.mUnknownC = 0;
        AudmonEventPost(17,0);
    }
}
void fn_80141164(float amount) { lbl_803ECA08 = amount; }
}
