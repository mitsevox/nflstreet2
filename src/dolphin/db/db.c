/* Dolphin debug interface and exception reporting for the game. */
#include <dolphin/db.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/os.h>

extern void __DBExceptionDestination(void);

void __DBExceptionDestinationAux(void);
BOOL __DBIsExceptionMarked(__OSException exception);

u8 DBStack[0x1000];
u8 *DBStackEnd = DBStack + (sizeof(DBStack) - 8);
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

asm void __DBExceptionDestination(void)
{
    nofralloc
    mfmsr r3
    ori r3, r3, 0x30
    mtmsr r3
    b __DBExceptionDestinationAux
}

BOOL __DBIsExceptionMarked(__OSException exception)
{
    u32 mask = 1 << exception;

    return (BOOL)(__DBInterface->exceptionMask & mask);
}

void DBPrintf(char *format, ...) {}
