#ifndef ENGINE_VIEWPORT_H
#define ENGINE_VIEWPORT_H

#include "engine/viewporttypes.h"

/* Argument of VptInit. */
typedef struct VptInitBlock_t {
    int mUnknown0;            /* element count of the 248-byte object pool */
    int mUnknown4;            /* element count of the 16-byte callback pool */
    unsigned short mUnknown8; /* passed to fn_801DCFF0 when nonzero */
    unsigned char mUnknown10;
    unsigned char mUnknown11;
} VptInitBlock_t;

typedef void (*VptCallbackFuncT)(Viewport_t *pObject);

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/viewport.c */
int VptInit(VptInitBlock_t *pInit);
int VptShutdown(void);
Viewport_t *VptOpen(ViewportDesc_t *pDesc);
int VptClose(Viewport_t *pObject);
int VptSetCallback(Viewport_t *pObject, int event, VptCallbackFuncT fn, int key);
void VptRemoveCallback(Viewport_t *pObject, VptCallbackFuncT fn);
void VptUpdateCamera(Viewport_t *pObject);
void VptProcessObjectList(Viewport_t *pObject);
void VptProcessViewports(void);
int VptIsProcessing(void);
Viewport_t *VptGetCurrentViewport(void);
void VptSetEraseColor(Viewport_t *pObject, float a, float b, float c);
void VptSetPos(Viewport_t *pObject, float a, float b);
int VptGetMatrixStack(void);
void VptSaveMatrix(Viewport_t *pObject);
void VptSetCamera(Viewport_t *pObject, VptCameraFuncT fn, void *arg);
void *VptGetCamera(Viewport_t *pObject);
void VptRemoveCamera(Viewport_t *pObject);
void VptSetObjectList(Viewport_t *pObject, int handle, int b);
void VptSetPerspective(Viewport_t *pObject, float fovy, float aspect, float n, float f);
void VptSetZScale(Viewport_t *pObject, float a);

/* src/engine/llviewpt.c */
int VptLLInit(VptInitBlock_t *pInit);
int VptLLShutdown(void);
int VptLLOpen(ViewportDesc_t *pDesc, Viewport_t *pObject);
int VptLLClose(Viewport_t *pObject);
void VptViewport(float m[4][4], float x, float y, float w, float h, float d);
void VptFrustum(float m[4][4], float l, float r, float b, float t, float n, float f, float s);
void VptOrtho(float m[4][4], float l, float r, float b, float t, float n, float f);
void VptPerspective(float m[4][4], float fovy, float aspect, float n, float f);
void VptSetUpRender(Viewport_t *pObject);
void VptTrashObject(int handle);
void VptFlushObjectTrash(void);
void VptFlushObjectTrashSync(void);

#ifdef __cplusplus
}
#endif

#endif
