/* UI Studio error reporting (EA file name UISError.c): registers the game's runtime
   error callback. */

#include "UIStudio/UIStudio.h"

UISRuntimeErrorFncT *RuntimeErrorFnc = NULL;

void UISRegisterRuntimeErrorFnc(UISRuntimeErrorFncT *pFnc)
{
    RuntimeErrorFnc = pFnc;
}
