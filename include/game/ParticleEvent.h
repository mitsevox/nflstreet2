#ifndef GAME_PARTICLE_EVENT_H
#define GAME_PARTICLE_EVENT_H

#include "game/ParticleSys.h"

struct Object_80039F5C;

/* One 0x60-byte entry of the pool at _Particles_pEventPool. */
struct ParticleEvent_t {
    int mType;
    unsigned char mUnknown04;
    float (*mUnknown08)[4][4];
    Object_80039F5C *mUnknown0C;
    void *mUnknown10;
    int mUnknown14;
    PsysEmitter_t *mUnknown18;
    int mUnknown1C;
    float mUnknown20[4][4];
};

extern "C" {
void ParticleEventFootstep(ParticleEvent_t *pEvent);
void ParticleEventAttached(ParticleEvent_t *pEvent);
void ParticleEventBodyTrail(ParticleEvent_t *pEvent);
void ParticleEventBodyImpact(ParticleEvent_t *pEvent);
void ParticleEventBallBounce(ParticleEvent_t *pEvent);
}

#endif
