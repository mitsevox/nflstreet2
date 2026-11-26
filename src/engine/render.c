/* Movie frame output: remembers where on screen the movie is drawn and copies each decoded
   frame into the frame buffer. */

#include "engine/render.h"
#include "engine/llglib.h"

extern void GlibSwapBuffers(void);
extern int GlibGetFrame(void);
extern int GlibGetFrameBufferAddr(int a);
extern void YUV_convert(unsigned char **ppPlanes, int x, int y, int pitch, int width, int height, int frameBuffer);
extern void YUV_convert_noscale(unsigned char **ppPlanes, int x, int y, int pitch, int width, int height, int frameBuffer);

/* Where and how the movie is drawn, set by yuvrenderinit. */
static int paintindex;
static int screenx;
static int screeny;
static int videowidth;
static int videoheight;
static int rendermode;
static int rendermethod;

void yuvrenderrestore(void)
{
}

void yuvrenderinit(int x, int y, int width, int height, int unknown4, int unused)
{
    yuvrenderrestore();
    paintindex = -1;
    screenx = x;
    screeny = y;
    videowidth = width;
    videoheight = height;
    rendermode = unknown4;
    rendermethod = 2;
}

void yuvrenderDoubleYLines(unsigned char **ppPlanes)
{
    int pitch;
    int frameBuffer;

    GlibSwapBuffers();
    pitch = (GlibGetScreenWidth() + 15) & 0xFFF0;
    frameBuffer = GlibGetFrameBufferAddr((unsigned char)GlibGetFrame());
    YUV_convert(ppPlanes, screenx, screeny, pitch, videowidth, videoheight, frameBuffer);
}

void yuvrenderVP6YLines(unsigned char **ppPlanes)
{
    int pitch;
    int frameBuffer;

    GlibSwapBuffers();
    pitch = (GlibGetScreenWidth() + 15) & 0xFFF0;
    frameBuffer = GlibGetFrameBufferAddr((unsigned char)GlibGetFrame());
    YUV_convert_noscale(ppPlanes, screenx, screeny, pitch, videowidth, videoheight, frameBuffer);
}
