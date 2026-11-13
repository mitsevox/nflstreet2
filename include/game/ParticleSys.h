#ifndef GAME_PARTICLESYS_H
#define GAME_PARTICLESYS_H

/* Object whose three floats +0xC..+0x14 ParticleSysSpawnEmitter averages into the
   emitter byte +0x35B. */
struct ParticleSource_t {
    char mPad00[8];
    int mUnknown08;
    float mUnknown0C;
    float mUnknown10;
    float mUnknown14;
};

struct AnimTex_t;
struct Particle_t;

/* Object returned by ParticleSysSpawnEmitter (from fn_801DEEF8), drawn by ParticleRenderEmitter
   (the callback of its descriptor _ParticleSys_EmitterDesc) and released by
   ParticleSysReleaseEmitter. */
struct PsysEmitter_t {
    char mPad000[0x3C];
    unsigned char mUnknown03C;
    char mPad03D[0x45 - 0x3D];
    unsigned char mUnknown45;
    char mPad046[2];
    unsigned short mUnknown48;
    char mPad04A[2];
    int mUnknown4C;
    int mUnknown50;
    float mUnknown54;
    char mPad058[0x60 - 0x58];
    int mUnknown60;
    char mPad064[0x7C - 0x64];
    float mUnknown7C;
    float mUnknown80;
    float mUnknown84;
    float mUnknown88;
    char mPad08C[0xA8 - 0x8C];
    float mUnknownA8;
    float mUnknownAC;
    float mUnknownB0;
    char mPad0B4[0xF0 - 0xB4];
    int mUnknown0F0;
    char mPad0F4[0x2AC - 0xF4];
    AnimTex_t *mpUnknown2AC;
    char mPad2B0[4];
    unsigned char mUnknown2B4;
    char mPad2B5[1];
    unsigned char mUnknown2B6;
    char mPad2B7[0x35A - 0x2B7];
    unsigned char mUnknown35A;
    unsigned char mUnknown35B;
    float mUnknown35C[4][4];
    float mUnknown39C;
    float mUnknown3A0;
    float mUnknown3A4;
    char mPad3A8[0x3B4 - 0x3A8];
    float (*mpUnknown3B4)[4][4];
    unsigned int mUnknown3B8;
    char mPad3BC[4];
    Particle_t **mppUnknown3C0;
    char mPad3C4[0x3C8 - 0x3C4];
    float mUnknown3C8;
    float mUnknown3CC;
    float mUnknown3D0;
};

/* Arguments block passed to ParticleSysSpawnEmitter. */
struct ParticleSpawnArgs_t {
    int mUnknown00;
    float (*mUnknown04)[4][4];
    float (*mUnknown08)[4][4];
    int mUnknown0C;
    int mUnknown10;
};

extern "C" {
AnimTex_t *ParticleSysGetAnimTex(int index);
PsysEmitter_t *ParticleSysSpawnEmitter(ParticleSpawnArgs_t *pArgs, int b, ParticleSource_t *pSource);
void ParticleSysReleaseEmitter(PsysEmitter_t *pObject);
void ParticlesSpawnAt(int a, float *pPos, float *pRot, ParticleSource_t *pSource);
}

/* One 0x24-byte record of the six-entry table written to the replay stream. */
struct ParticleSpawnRecord_t {
    int mId;
    float mPos[3];
    float mRot[4];
    ParticleSource_t *mpSource;
};

extern "C" void ParticleSysReplayRecordSpawn(ParticleSpawnRecord_t record);

#endif
