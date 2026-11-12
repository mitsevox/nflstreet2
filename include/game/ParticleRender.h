#ifndef GAME_PARTICLERENDER_H
#define GAME_PARTICLERENDER_H

#include "game/ParticleSys.h"

extern "C" {
void ParticleRenderInit(int a);
void ParticleRenderShutdown(void);
int ParticleRenderEmitter(PsysEmitter_t *pEmitter, int mode);
}

#endif
