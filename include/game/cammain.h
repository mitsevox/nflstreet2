#ifndef GAME_CAMMAIN_H
#define GAME_CAMMAIN_H

#include "game/GameCamera.h"
#include "game/CamEaseVec.h"
#include "game/CamInterp.h"
#include "game/Object_80039F5C.h"

/* Camera type record. _CamMain_Type and the replay camera's lbl_802CC83C
   have this form; _CamMainTypeDefs lists both, and Cam::Init passes that
   list to CamInit. */
struct CamTypeDef_t {
    void (*mUnknown00)(GameCamera_t *pCamera, CameraDesc_t *pDesc);
    void (*mUnknown04)(GameCamera_t *pCamera);
    void (*mUnknown08)(void *p, GameCamera_t *pCamera);
};

/* Camera mode record: slot +0 is called by CamMainInit with (camera, desc),
   slot +4 by CamMainUninit with the camera. */
struct CamMode_t {
    void (*mUnknown00)(GameCamera_t *pCamera, CameraDesc_t *pDesc);
    void (*mUnknown04)(GameCamera_t *pCamera);
    int mUnknown08;
};

/* Entry points of src/game/cammain.cpp. */
extern "C" {
unsigned char CamMainIsFlipped(GameCamera_t *pCamera);
void CamMainFlipPos(Vector_80039F5C *pVec);
void CamMainFlipOrient(int *pAngles);
void _CamMainProcessFollow(GameCamera_t *pCamera);
void _CamMainCalcFollowPos(GameCamera_t *pCamera, Vector_80039F5C *pTarget, Vector_80039F5C *pOut);
void _CamMainGetCameraPos(GameCamera_t *pCamera, Vector_80039F5C *pOut);
void _CamMainGetFocusPos(int kind, int ref, Vector_80039F5C *pOut);
void _CamMainGetFocusOrient(int kind, int ref, int *pAngles);
void _CamMainGetAngleToFocus(GameCamera_t *pCamera, int *pAngles);
void _CamMainBaseInit(GameCamera_t *pCamera);
void _CamMainBaseUninit(GameCamera_t *pCamera);
void _CamMainBaseProcess(GameCamera_t *pCamera);
void _CamMainBaseMoveAngle(GameCamera_t *pCamera, int *pAngles);
void CamMainProcess(GameCamera_t *pCamera, int a, int b, int c);
void CamMainSetFocus(GameCamera_t *pCamera, int kind, int ref);
void CamMainInitDesc(CameraDesc_t *pDesc);
void CamMainFollow(GameCamera_t *pCamera, unsigned int kind, int ref, int arg);
void CamMainFollowBall(GameCamera_t *pCamera);
void CamMainSetOffset(GameCamera_t *pCamera, Vector_80039F5C *pOffset);
void CamMainSetAngle(GameCamera_t *pCamera, int *pAngles, int bit);
void CamMainRotate(GameCamera_t *pCamera, int angle);
void CamMainPitch(GameCamera_t *pCamera, int angle);
void CamMainSetMode(GameCamera_t *pCamera, int id, int a, int b);
int CamMainGetMode(GameCamera_t *pCamera);
void CamMainSetActive(GameCamera_t *pCamera, int on, int a, int b);
void CamMainWarpToDest(GameCamera_t *pCamera);
void CamMainStop(GameCamera_t *pCamera);
void CamMainMsg(GameCamera_t *pCamera, int msg, int arg);
int CamMainGetBaseType(int id);
void CamMainInit(GameCamera_t *pCamera, CameraDesc_t *pDesc);
void CamMainUninit(GameCamera_t *pCamera);
void CamMainUpdate(void *p, GameCamera_t *pCamera);
void CamEaseVecStart(CamEaseVec_t *pEase, Vector_80039F5C *pBase, Vector_80039F5C *pFrom,
                 Vector_80039F5C *pTo, CamInterpFunc_t update, float fromScale, float toScale,
                 float time);
void CamEaseVecUpdate(CamEaseVec_t *pEase, int steps);
void CamEaseVecFlip(CamEaseVec_t *pEase);
void CamInterpInit(CamInterp_t *pInterp, float value);
void CamInterpSetTarget(CamInterp_t *pInterp, float target, CamInterpFunc_t update, float time);
}

#endif
