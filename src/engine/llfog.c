/* Distance fog: keeps the fog type, start and end distances, colour and
   on/off switch, and programs GX fog from them and the current viewport's
   near and far planes, or turns GX fog off. */

#include <dolphin/gx/GXPixel.h>
#include "engine/viewporttypes.h"

static Viewport_t *_LLFog_pViewport = 0;
static float _LLFog_fStart = 10.0f;
static float _LLFog_fEnd = 100.0f;
static GXColor _LLFog_Color = { 0xC0, 0xC0, 0xC0, 0x00 };
static unsigned char _LLFog_bEnable = 0;
static int _LLFog_iType;

static void _LLFogUpdate(void);

void LLFogSetViewport(Viewport_t *pViewport)
{
    _LLFog_pViewport = pViewport;
}

void LLFogSetType(int type)
{
    _LLFog_iType = type;
    _LLFogUpdate();
}

void LLFogSetRange(float start, float end)
{
    _LLFog_fStart = start;
    _LLFog_fEnd = end;
    _LLFogUpdate();
}

void LLFogSetColor(int r, int g, int b)
{
    _LLFog_Color.r = r;
    _LLFog_Color.g = g;
    _LLFog_Color.b = b;
}

static void _LLFogUpdate(void)
{
    Viewport_t *pViewport;

    if (_LLFog_bEnable != 0 && (pViewport = _LLFog_pViewport) != 0) {
        GXSetFog(_LLFog_iType, _LLFog_fStart, _LLFog_fEnd, pViewport->mUnknown232, pViewport->mUnknown236, _LLFog_Color);
    } else {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, _LLFog_Color);
    }
}

int LLFogEnable(int enable)
{
    if (_LLFog_bEnable != enable) {
        _LLFog_bEnable = enable;
        _LLFogUpdate();
        return _LLFog_bEnable == 0;
    }
    return enable;
}

void LLFogSetDensity(float density)
{
}
