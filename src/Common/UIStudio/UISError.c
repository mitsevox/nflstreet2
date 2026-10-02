#include "UIStudio/UIStudio.h"

UISRuntimeErrorFncT *RuntimeErrorFnc = NULL;

void UISRegisterRuntimeErrorFnc(UISRuntimeErrorFncT *pRuntimeErrorFnc)
{
    RuntimeErrorFnc = pRuntimeErrorFnc;
}
