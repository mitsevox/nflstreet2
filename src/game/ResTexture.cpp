/* A texture loaded from a resource bundle entry: open (load and build), close (free) and clear. Used
   for the simple shadow texture. */
#include "game/ResTexture.h"
#include "game/fn_801EF390.h"

extern "C" {
int fn_801F1520(int value);

void ResTextureLoad(ResTexture *p)
{
    int previous = fn_801F1520(4);
    int data = fn_801EF390((void *)p->mUnknown0, p->mUnknown4, 1);

    fn_801F1520(previous);
    TexCreate((void *)data, &p->mTexture);
    fn_8020E7EC(&p->mTexture);
    fn_801F010C((void *)p->mUnknown0, p->mUnknown4);
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
    if (fn_801F0DB8((void *)p->mUnknown0, p->mUnknown4)) {
        fn_801F010C((void *)p->mUnknown0, p->mUnknown4);
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
