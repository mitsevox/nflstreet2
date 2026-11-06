#ifndef GAME_POSSESSION_H
#define GAME_POSSESSION_H

#include "game/Point2.h"

struct Object_80039F5C;

extern "C" {
void PossCalcBallSpot(Object_80039F5C *p, void *pBall, Point2_t *pOut, int a);
int PossCheckBallOut(void *pBall, Point2_t *pPos);
}

#endif
