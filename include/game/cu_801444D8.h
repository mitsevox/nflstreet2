#ifndef GAME_CU_801444D8_H
#define GAME_CU_801444D8_H

#include <dolphin/mtx.h>

/* Object whose three floats +0xC..+0x14 fn_80144CE0 averages into the
   emitter byte +0x35B. */
struct Source_80144CE0 {
    char mPad00[0xC];
    float mUnknown0C;
    float mUnknown10;
    float mUnknown14;
};

struct Texture_80196564;
struct Particle_80196564;

/* Object returned by fn_80144CE0 (from fn_801DEEF8), drawn by fn_80196564
   (the callback of its descriptor lbl_802DCFF8) and released by
   fn_80144E38. */
struct Object_80144CE0 {
    char mPad000[0x3C];
    unsigned char mUnknown03C;
    char mPad03D[0x45 - 0x3D];
    unsigned char mUnknown45;
    char mPad046[2];
    unsigned short mUnknown48;
    char mPad04A[0x60 - 0x4A];
    int mUnknown60;
    char mPad064[0xF0 - 0x64];
    int mUnknown0F0;
    char mPad0F4[0x2AC - 0xF4];
    Texture_80196564 *mpUnknown2AC;
    char mPad2B0[4];
    unsigned char mUnknown2B4;
    char mPad2B5[1];
    unsigned char mUnknown2B6;
    char mPad2B7[0x35A - 0x2B7];
    unsigned char mUnknown35A;
    unsigned char mUnknown35B;
    Mtx44 mUnknown35C;
    char mPad39C[0x3B4 - 0x39C];
    Mtx44 *mpUnknown3B4;
    unsigned int mUnknown3B8;
    char mPad3BC[4];
    Particle_80196564 **mppUnknown3C0;
    char mPad3C4[0x3C8 - 0x3C4];
    float mUnknown3C8;
    float mUnknown3CC;
    float mUnknown3D0;
};

/* Arguments block passed to fn_80144CE0. */
struct Args_80144CE0 {
    int mUnknown00;
    Mtx44 *mUnknown04;
    Mtx44 *mUnknown08;
    int mUnknown0C;
    int mUnknown10;
};

extern "C" {
Object_80144CE0 *fn_80144CE0(Args_80144CE0 *pArgs, int b, Source_80144CE0 *pSource);
void fn_80144E38(Object_80144CE0 *pObject);
void fn_80145EFC(int a, float *pPos, float *pRot, Source_80144CE0 *pSource);
}

#endif
