#ifndef GAME_PARTICLERENDER_H
#define GAME_PARTICLERENDER_H

#include "game/cu_801444D8.h"

extern "C" {
void ParticleRenderInit(int a);
void ParticleRenderShutdown(void);
int ParticleRenderEmitter(Object_80144CE0 *pEmitter, int mode);
}

#endif
