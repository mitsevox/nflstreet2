/* Render callback that draws the debug text screen each frame. */
#include "engine/viewport.h"

extern "C" {
void DbgScreenDraw(void);

void DbgScreenRenderCallback(Viewport_t *pObject)
{
    DbgScreenDraw();
}
}
