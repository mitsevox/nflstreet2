#ifndef GAME_CU_8013BB18_H
#define GAME_CU_8013BB18_H

#include "game/GameCamera.h"
#include "game/EaseVector_8013C9A4.h"
#include "game/Interp_8013CC14.h"
#include "game/Object_80039F5C.h"

/* Camera type record. lbl_802DBD24 and the replay camera's lbl_802CC83C
   have this form; lbl_802DBD7C lists both, and fn_8008CCFC passes that
   list to CamInit. */
struct Type_802DBD24 {
    void (*mUnknown00)(GameCamera_t *pCamera, CameraDesc_t *pDesc);
    void (*mUnknown04)(GameCamera_t *pCamera);
    void (*mUnknown08)(void *p, GameCamera_t *pCamera);
};

/* Camera mode record: slot +0 is called by fn_8013C868 with (camera, desc),
   slot +4 by fn_8013C90C with the camera. */
struct Mode_8013FD8C {
    void (*mUnknown00)(GameCamera_t *pCamera, CameraDesc_t *pDesc);
    void (*mUnknown04)(GameCamera_t *pCamera);
    int mUnknown08;
};

/* Entry points of src/game/cu_8013BB18.cpp. */
extern "C" {
unsigned char fn_8013BB18(GameCamera_t *pCamera);
void fn_8013BB54(Vector_80039F5C *pVec);
void fn_8013BB70(int *pAngles);
void fn_8013BB84(GameCamera_t *pCamera);
void fn_8013BC4C(GameCamera_t *pCamera, Vector_80039F5C *pTarget, Vector_80039F5C *pOut);
void fn_8013BD98(GameCamera_t *pCamera, Vector_80039F5C *pOut);
void fn_8013BDC0(int kind, int ref, Vector_80039F5C *pOut);
void fn_8013BEE0(int kind, int ref, int *pAngles);
void fn_8013BF40(GameCamera_t *pCamera, int *pAngles);
void fn_8013C120(GameCamera_t *pCamera);
void fn_8013C1C8(GameCamera_t *pCamera);
void fn_8013C204(GameCamera_t *pCamera);
void fn_8013C260(GameCamera_t *pCamera, int *pAngles);
void fn_8013C2B4(GameCamera_t *pCamera, int a, int b, int c);
void fn_8013C328(GameCamera_t *pCamera, int kind, int ref);
void fn_8013C340(CameraDesc_t *pDesc);
void fn_8013C384(GameCamera_t *pCamera, unsigned int kind, int ref, int arg);
void fn_8013C438(GameCamera_t *pCamera);
void fn_8013C478(GameCamera_t *pCamera, Vector_80039F5C *pOffset);
void fn_8013C4BC(GameCamera_t *pCamera, int *pAngles, int bit);
void fn_8013C540(GameCamera_t *pCamera, int angle);
void fn_8013C57C(GameCamera_t *pCamera, int angle);
void fn_8013C624(GameCamera_t *pCamera, int id, int a, int b);
int fn_8013C678(GameCamera_t *pCamera);
void fn_8013C680(GameCamera_t *pCamera, int on, int a, int b);
void fn_8013C6F0(GameCamera_t *pCamera);
void fn_8013C7C4(GameCamera_t *pCamera);
void fn_8013C824(GameCamera_t *pCamera, int msg, int arg);
int fn_8013C854(int id);
void fn_8013C868(GameCamera_t *pCamera, CameraDesc_t *pDesc);
void fn_8013C90C(GameCamera_t *pCamera);
void fn_8013C954(void *p, GameCamera_t *pCamera);
void fn_8013C9A4(EaseVector_8013C9A4 *pEase, Vector_80039F5C *pBase, Vector_80039F5C *pFrom,
                 Vector_80039F5C *pTo, InterpFunc_8013CC14 update, float fromScale, float toScale,
                 float time);
void fn_8013CAA4(EaseVector_8013C9A4 *pEase, int steps);
void fn_8013CBC4(EaseVector_8013C9A4 *pEase);
void fn_8013CC14(Interp_8013CC14 *pInterp, float value);
void fn_8013CC40(Interp_8013CC14 *pInterp, InterpFunc_8013CC14 update, float target, float time);
}

#endif
