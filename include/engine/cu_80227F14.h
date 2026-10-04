#ifndef ENGINE_CU_80227F14_H
#define ENGINE_CU_80227F14_H

#include "game/Object_80228224.h"

/* Argument of fn_802280B0. */
typedef struct Init_802280B0 {
    int mUnknown0;            /* element count of the 248-byte object pool */
    int mUnknown4;            /* element count of the 16-byte callback pool */
    unsigned short mUnknown8; /* passed to fn_801DCFF0 when nonzero */
    unsigned char mUnknown10;
    unsigned char mUnknown11;
} Init_802280B0;

typedef void (*Callback_80228474)(Object_80228224 *pObject);

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/cu_80227F14.c */
int fn_802280B0(Init_802280B0 *pInit);
int fn_80228194(void);
Object_80228224 *fn_80228224(Desc_80228224 *pDesc);
int fn_802283FC(Object_80228224 *pObject);
int fn_80228474(Object_80228224 *pObject, int event, Callback_80228474 fn, int key);
void fn_802284EC(Object_80228224 *pObject, Callback_80228474 fn);
void fn_80228530(Object_80228224 *pObject);
void fn_80228594(Object_80228224 *pObject);
void fn_802285CC(void);
int fn_8022863C(void);
Object_80228224 *fn_80228644(void);
void fn_8022864C(Object_80228224 *pObject, float a, float b, float c);
void fn_8022865C(Object_80228224 *pObject, float a, float b);
int fn_80228668(void);
void fn_80228670(Object_80228224 *pObject);
void fn_802286A8(Object_80228224 *pObject, Callback_80228224 fn, void *arg);
void *fn_802286B4(Object_80228224 *pObject);
void fn_802286BC(Object_80228224 *pObject);
void fn_802286CC(Object_80228224 *pObject, int handle, int b);
void fn_802286D8(Object_80228224 *pObject, float fovy, float aspect, float n, float f);
void fn_80228780(Object_80228224 *pObject, float a);
void fn_802287D4(Object_80228224 *pObject);

/* src/engine/cu_802288F8.c */
int fn_802288F8(Init_802280B0 *pInit);
int fn_80228948(void);
int fn_80228978(Desc_80228224 *pDesc, Object_80228224 *pObject);
int fn_80228980(Object_80228224 *pObject);
void fn_80228988(float m[4][4], float x, float y, float w, float h, float d);
void fn_802289FC(float m[4][4], float l, float r, float b, float t, float n, float f, float s);
void fn_80228A34(float m[4][4], float l, float r, float b, float t, float n, float f);
void fn_80228AD4(float m[4][4], float fovy, float aspect, float n, float f);
void fn_80228B74(Object_80228224 *pObject);
void fn_80228D58(int handle);
void fn_80228DD4(void);
void fn_80228E18(void);

#ifdef __cplusplus
}
#endif

#endif
