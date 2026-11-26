/* UI Studio error reporting (EA file name UISError.c): registers the game's runtime
   error callback. */

#include "UIStudio/UIStudio.h"

UISRuntimeErrorFncT *RuntimeErrorFnc = NULL;

void fn_8021D880(UISRuntimeErrorFncT *pFnc)
{
    RuntimeErrorFnc = pFnc;
}
