#ifndef GAME_PASSICONTEX_H
#define GAME_PASSICONTEX_H

#include "game/PassIconObj.h"

extern "C" {
void PassIconTexLoad(void);
void PassIconTexFree(void);
void PassIconTexDraw(PassIconObj_t *pInstance);
}

#endif
