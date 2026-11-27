#ifndef GAME_PARAMS_80092E54_H
#define GAME_PARAMS_80092E54_H

struct Object_80039F5C;
struct Ball_t;

struct CamCurveSelection_t { unsigned char mUnknown0; unsigned char mUnknown1[3]; union { int mWord; unsigned short mParts[2]; } mUnknown4,mUnknown8; };

/* 236-byte request that GamebreakerSceneRequestLoad, GameEndLoadScene and QuarterEndLoadClip build on
   the stack and pass to AnmsStartScene; AnmsStartScene and AnmsRequestScene copy it
   into the leading fields of a free Character_80093BCC. */
struct Params_80092E54 {
    int mUnknown0,mUnknown4;
    int mUnknown8,mUnknownC,mUnknown10;
    Object_80039F5C *mUnknown14[24];
    Ball_t *mUnknown74[24];
    int mUnknownD4;
    union { int mWord; unsigned short mParts[2]; } mUnknownD8;
    unsigned char mUnknownDC[4];
    CamCurveSelection_t mUnknownE0;
};

extern "C" int AnmsStartScene(Params_80092E54 *pParams, void *pBuffer, int size);

#endif
