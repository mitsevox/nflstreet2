#ifndef ENGINE_LLRENDER_H
#define ENGINE_LLRENDER_H

typedef struct RenderBin_t {
    unsigned char mUnk0[0x24];
    unsigned char mActive;
    int mUnk28;
    int mUnk2C;
    int mUnk30;
    struct RenderBin_t *mpNext;
    int mUnk38;
    int mUnk3C;
    void *mpMark;
    int mUnk44;
    int mUnk48;
    unsigned char mUnk4C[0x30];
} RenderBin_t;

#endif
