/* A texture loaded from a resource bundle entry: open (load and build), close (free) and clear. Used
   for the simple shadow texture. */
#include "game/ResTexture.h"
#include "game/ResLoad.h"

extern "C" {
int ResSetMemFlags(int value);

void ResTextureLoad(ResTexture *p)
{
    int previous = ResSetMemFlags(4);
    int data = ResLoad((void *)p->mUnknown0, p->mUnknown4, 1);

    ResSetMemFlags(previous);
    TexCreate((void *)data, &p->mTexture);
    LLTexPadToPow2(&p->mTexture);
    ResUnLoad((void *)p->mUnknown0, p->mUnknown4);
}

void ResTextureOpen(ResTexture *p, int a, int b, int c, const char *pName)
{
    p->mUnknown0 = b;
    p->mUnknown4 = c;
    ResTextureLoad(p);
    p->mUnknown28 = 1;
}

void ResTextureClose(ResTexture *p)
{
    if (ResIsLoaded((void *)p->mUnknown0, p->mUnknown4)) {
        ResUnLoad((void *)p->mUnknown0, p->mUnknown4);
    }
    TexDelete(&p->mTexture);
    ResTextureClear(p);
}

void ResTextureClear(ResTexture *p)
{
    p->mUnknown0 = 0;
    p->mUnknown4 = 0;
    p->mUnknown28 = 0;
    p->mUnknown2C = 0;
    p->mUnknown30 = 0;
    p->mUnknown38 = 0;
}
}
