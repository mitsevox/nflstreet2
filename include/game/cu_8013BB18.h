#ifndef GAME_CU_8013BB18_H
#define GAME_CU_8013BB18_H

#include "game/Camera_8013F738.h"
#include "game/EaseVector_8013C9A4.h"
#include "game/Interp_8013CC14.h"
#include "game/Object_80039F5C.h"

/* Camera type record. lbl_802DBD24 and the replay camera's lbl_802CC83C
   have this form; lbl_802DBD7C lists both, and fn_8008CCFC passes that
   list to fn_801C34F8. */
struct Type_802DBD24 {
    void (*mUnknown00)(Camera_8013F738 *pCamera, Desc_8013C340 *pDesc);
    void (*mUnknown04)(Camera_8013F738 *pCamera);
    void (*mUnknown08)(void *p, Camera_8013F738 *pCamera);
};

/* Entry points of src/game/cu_8013BB18.cpp. */
extern "C" {
unsigned char fn_8013BB18(Camera_8013F738 *pCamera);
void fn_8013BB54(Vector_80039F5C *pVec);
void fn_8013BB70(int *pAngles);
void fn_8013BB84(Camera_8013F738 *pCamera);
void fn_8013BC4C(Camera_8013F738 *pCamera, Vector_80039F5C *pTarget, Vector_80039F5C *pOut);
void fn_8013BD98(Camera_8013F738 *pCamera, Vector_80039F5C *pOut);
void fn_8013BDC0(int kind, int ref, Vector_80039F5C *pOut);
void fn_8013BEE0(int kind, int ref, int *pAngles);
void fn_8013BF40(Camera_8013F738 *pCamera, int *pAngles);
void fn_8013C120(Camera_8013F738 *pCamera);
void fn_8013C1C8(Camera_8013F738 *pCamera);
void fn_8013C204(Camera_8013F738 *pCamera);
void fn_8013C260(Camera_8013F738 *pCamera, int *pAngles);
void fn_8013C2B4(Camera_8013F738 *pCamera, int a, int b, int c);
void fn_8013C328(Camera_8013F738 *pCamera, int kind, int ref);
void fn_8013C340(Desc_8013C340 *pDesc);
void fn_8013C384(Camera_8013F738 *pCamera, unsigned int kind, int ref, int arg);
void fn_8013C438(Camera_8013F738 *pCamera);
void fn_8013C478(Camera_8013F738 *pCamera, Vector_80039F5C *pOffset);
void fn_8013C4BC(Camera_8013F738 *pCamera, int *pAngles, int bit);
void fn_8013C540(Camera_8013F738 *pCamera, int angle);
void fn_8013C57C(Camera_8013F738 *pCamera, int angle);
void fn_8013C624(Camera_8013F738 *pCamera, int id, int a, int b);
int fn_8013C678(Camera_8013F738 *pCamera);
void fn_8013C680(Camera_8013F738 *pCamera, int on, int a, int b);
void fn_8013C6F0(Camera_8013F738 *pCamera);
void fn_8013C7C4(Camera_8013F738 *pCamera);
void fn_8013C824(Camera_8013F738 *pCamera, int msg, int arg);
int fn_8013C854(int id);
void fn_8013C868(Camera_8013F738 *pCamera, Desc_8013C340 *pDesc);
void fn_8013C90C(Camera_8013F738 *pCamera);
void fn_8013C954(void *p, Camera_8013F738 *pCamera);
void fn_8013C9A4(EaseVector_8013C9A4 *pEase, Vector_80039F5C *pBase, Vector_80039F5C *pFrom,
                 Vector_80039F5C *pTo, InterpFunc_8013CC14 update, float fromScale, float toScale,
                 float time);
void fn_8013CAA4(EaseVector_8013C9A4 *pEase, int steps);
void fn_8013CBC4(EaseVector_8013C9A4 *pEase);
void fn_8013CC14(Interp_8013CC14 *pInterp, float value);
void fn_8013CC40(Interp_8013CC14 *pInterp, InterpFunc_8013CC14 update, float target, float time);
}

#endif
