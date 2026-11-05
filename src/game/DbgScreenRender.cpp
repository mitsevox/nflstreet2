/* Render callback that draws the debug text screen each frame. */
#include "engine/cu_80227F14.h"

extern "C" {
void DbgScreenDraw(void);

void DbgScreenRenderCallback(Object_80228224 *pObject)
{
    DbgScreenDraw();
}
}
