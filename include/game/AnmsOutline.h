#ifndef GAME_ANMSOUTLINE_H
#define GAME_ANMSOUTLINE_H

#include "game/Object_80039F5C.h"

extern "C" {
unsigned int AnmsGetOutlineCount(void);
Vector_80039F5C *AnmsGetOutlinePoint(int index);
}

#endif
