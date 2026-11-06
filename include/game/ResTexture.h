#ifndef GAME_RESTEXTURE_H
#define GAME_RESTEXTURE_H

#include "engine/texture.h"

struct ResTexture {
    int mUnknown0;
    int mUnknown4;
    Texture_t mTexture;
    unsigned char mUnknown28;
    int mUnknown2C;
    int mUnknown30;
    char mUnknown34[4];
    long long mUnknown38;
};

extern "C" {
void ResTextureLoad(ResTexture *p);
void ResTextureOpen(ResTexture *p, int a, int b, int c, const char *pName);
void ResTextureClose(ResTexture *p);
void ResTextureClear(ResTexture *p);
}

#endif
