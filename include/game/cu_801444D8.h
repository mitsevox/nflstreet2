#ifndef GAME_CU_801444D8_H
#define GAME_CU_801444D8_H

/* Object whose three floats +0xC..+0x14 fn_80144CE0 averages into the
   emitter byte +0x35B. */
struct Source_80144CE0 {
    char mPad00[8];
    int mUnknown08;
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
    char mPad064[0x7C - 0x64];
    float mUnknown7C;
    float mUnknown80;
    float mUnknown84;
    float mUnknown88;
    char mPad08C[0xA8 - 0x8C];
    float mUnknownA8;
    float mUnknownAC;
    char mPad0B0[0xF0 - 0xB0];
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
    float mUnknown35C[4][4];
    float mUnknown39C;
    float mUnknown3A0;
    float mUnknown3A4;
    char mPad3A8[0x3B4 - 0x3A8];
    float (*mpUnknown3B4)[4][4];
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
    float (*mUnknown04)[4][4];
    float (*mUnknown08)[4][4];
    int mUnknown0C;
    int mUnknown10;
};

extern "C" {
Object_80144CE0 *fn_80144CE0(Args_80144CE0 *pArgs, int b, Source_80144CE0 *pSource);
void fn_80144E38(Object_80144CE0 *pObject);
void fn_80145EFC(int a, float *pPos, float *pRot, Source_80144CE0 *pSource);
}

#endif
