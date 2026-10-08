#include <dolphin/db.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/os.h>

extern void __DBExceptionDestination(void);

void __DBExceptionDestinationAux(void);
BOOL __DBIsExceptionMarked(__OSException exception);

DBInterface *__DBInterface = NULL;
int DBVerbose;

void DBInit(void)
{
    __DBInterface = (DBInterface *)OSPhysicalToCached(OS_DBINTERFACE_ADDR);
    __DBInterface->ExceptionDestination = (void (*)())OSCachedToPhysical(__DBExceptionDestination);
    DBVerbose = TRUE;
}

void __DBExceptionDestinationAux(void)
{
    u32 *contextAddr = (void *)0x00C0;
    OSContext *context = (OSContext *)OSPhysicalToCached(*contextAddr);

    OSReport("DBExceptionDestination\n");
    OSDumpContext(context);
    PPCHalt();
}

BOOL __DBIsExceptionMarked(__OSException exception)
{
    u32 mask = 1 << exception;

    return (BOOL)(__DBInterface->exceptionMask & mask);
}

void DBPrintf(char *format, ...) {}
