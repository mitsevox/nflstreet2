/* UI Studio error reporting (EA file name UISError.c): registers the game's runtime
   error callback and holds the runtime error message table. */

#include "UIStudio/UIStudio.h"

UISRuntimeErrorFncT *RuntimeErrorFnc = NULL;
char *UISErrorMessages[] = {
    "Error: Out of bounds array access.",
    "Error: Invalid Controller ID.",
};

void UISRegisterRuntimeErrorFnc(UISRuntimeErrorFncT *pFnc)
{
    RuntimeErrorFnc = pFnc;
}
