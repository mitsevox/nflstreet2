#ifndef GAME_PASSICONTEX_H
#define GAME_PASSICONTEX_H

#include "game/cu_80159F10.h"

extern "C" {
void PassIconTexLoad(void);
void PassIconTexFree(void);
void PassIconTexDraw(Instance_80159F10 *pInstance);
}

#endif
