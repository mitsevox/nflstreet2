#ifndef GAME_FN_80163E94_H
#define GAME_FN_80163E94_H

#include "game/fn_800670B4.h"

struct Object_80039F5C;

extern "C" {
Entry_8006719C *fn_80163E94(Object_800670B4 *pObject, unsigned int index, const char **ppNames);
int fn_801642DC(Object_800670B4 *pObject, unsigned char index);
int fn_80164384(Object_800670B4 *pObject, unsigned char index);
void fn_80164430(Object_800670B4 *pObject, unsigned char index, unsigned char *pA, unsigned char *pB);
Object_80039F5C *fn_8016444C(Object_800670B4 *pObject);
void fn_801644A0(Object_80039F5C *p);
}

#endif
