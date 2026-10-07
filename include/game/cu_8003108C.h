#ifndef GAME_CU_8003108C_H
#define GAME_CU_8003108C_H

#include "game/cu_8002B8F8.h"

/* Event list of the replay object (src/game/cu_8003108C.cpp). */
extern "C" {
unsigned int fn_8003108C(Type_803EA368 *p, int id);
void fn_800310C0(Type_803EA368 *p, int id, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing);
int fn_800311E4(Type_803EA368 *p, int id);
int fn_8003122C(Type_803EA368 *p, int id, float *pOut);
Object_80039F5C *fn_80031294(Type_803EA368 *p, int id);
void fn_800312DC(Type_803EA368 *p);
int fn_800312FC(Type_803EA368 *p, int id);
int fn_80031328(Type_803EA368 *p, int id);
void fn_80031404(Object_80039F5C *p);
void fn_8003145C(Object_80039F5C *p, int code);
}

#endif
