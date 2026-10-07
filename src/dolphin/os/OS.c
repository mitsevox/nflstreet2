#include "dolphin/os.h"
#include "__os.h"
#include <dolphin/hw_regs.h>
#include <dolphin/exi.h>
#include <dolphin/si.h>
#include <dolphin/base/PPCArch.h>
#include "dolphin/db.h"

typedef struct BI2Debug {
    u8 _opaque0[0xC];
    u32 debugFlag;
    u8 _opaque10[0x14];
    u32 padSpec;
} BI2Debug;

void ClearArena(void);
static const char* __OSVersion =
    "<< Dolphin SDK - OS\trelease build: Apr 17 2003 12:33:06 (0x2301) >>";

extern char _db_stack_end[];

#define OS_BI2_DEBUG_ADDRESS 0x800000F4
#define DEBUGFLAG_ADDR 0x800030E8
#define OS_DEBUG_ADDRESS_2 0x800030E9
#define OS_CURRENTCONTEXT_PADDR 0x00C0

extern void __OSFPRInit(void);
extern void __OSPSInit(void);

volatile u16 __OSDeviceCode : (OS_BASE_CACHED | 0x30E6);
static DVDDriveInfo DriveInfo ATTRIBUTE_ALIGN(32);
static DVDCommandBlock DriveBlock;

static OSBootInfo* BootInfo;
static u32* BI2DebugFlag;
static u32* BI2DebugFlagHolder;
__declspec(weak) BOOL __OSIsGcam = FALSE;
static f64 ZeroF;
static f32 ZeroPS[2];
static BOOL AreWeInitialized = FALSE;
static __OSExceptionHandler* OSExceptionTable;
OSTime __OSStartTime;
BOOL __OSInIPL;

extern u8 __ArenaHi[];
extern u8 __ArenaLo[];
extern u32 __DVDLongFileNameFlag;
extern u32 __PADSpec;

#define OS_EXCEPTIONTABLE_ADDR 0x3000
#define OS_DBJUMPPOINT_ADDR 0x60

#define OS_CACHED_REGION_PREFIX 0x8000
#define OS_BI2_DEBUG_ADDRESS 0x800000F4
#define OS_BI2_DEBUGFLAG_OFFSET 0xC
#define PAD3_BUTTON_ADDR 0x800030E4
#define OS_DVD_DEVICECODE 0x800030E6
#define DEBUGFLAG_ADDR 0x800030E8
#define OS_DEBUG_ADDRESS_2 0x800030E9
#define DB_EXCEPTIONRET_OFFSET 0xC
#define DB_EXCEPTIONDEST_OFFSET 0x8
#define MSR_RI_BIT 0x1E

void OSDefaultExceptionHandler(__OSException exception, OSContext* context);
extern BOOL __DBIsExceptionMarked(__OSException);
static void OSExceptionInit(void);

u32 OSGetConsoleType()
{
    if (BootInfo == NULL || BootInfo->consoleType == 0)
    {
        return OS_CONSOLE_ARTHUR;
    }
    return BootInfo->consoleType;
}

void* __OSSavedRegionStart;
void* __OSSavedRegionEnd;

extern u32 BOOT_REGION_START : 0x812FDFF0;
extern u32 BOOT_REGION_END : 0x812FDFEC;

void ClearArena(void)
{
    if ((u32)(OSGetResetCode() + 0x80000000) != 0U)
    {
        __OSSavedRegionStart = 0U;
        __OSSavedRegionEnd = 0U;
        memset(OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }
    __OSSavedRegionStart = (void*)BOOT_REGION_START;
    __OSSavedRegionEnd = (void*)BOOT_REGION_END;
    if (BOOT_REGION_START == 0U)
    {
        memset(OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }

    if ((u32)OSGetArenaLo() < (u32)__OSSavedRegionStart)
    {
        if ((u32)OSGetArenaHi() <= (u32)__OSSavedRegionStart)
        {
            memset(OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
            return;
        }
        memset(OSGetArenaLo(), 0U, (u32)__OSSavedRegionStart - (u32)OSGetArenaLo());
        if ((u32)OSGetArenaHi() > (u32)__OSSavedRegionEnd)
        {
            memset(__OSSavedRegionEnd, 0, (u32)OSGetArenaHi() - (u32)__OSSavedRegionEnd);
        }
    }
}

static void InquiryCallback(s32 result, DVDCommandBlock* block)
{
    switch (block->state)
    {
    case 0:
        __OSDeviceCode = (u16)(0x8000 | DriveInfo.deviceCode);
        break;
    default:
        __OSDeviceCode = 1;
        break;
    }
}

void OSInit(void)
{

    BI2Debug* DebugInfo;
    void* debugArenaLo;
    u32 inputConsoleType;
    u32 tdev;

    if ((BOOL)AreWeInitialized == FALSE)
    {
        AreWeInitialized = TRUE;

        __OSStartTime = __OSGetSystemTime();
        OSDisableInterrupts();

        PPCMtmmcr0(0);
        PPCMtmmcr1(0);
        PPCMtpmc1(0);
        PPCMtpmc2(0);
        PPCMtpmc3(0);
        PPCMtpmc4(0);
        PPCDisableSpeculation();
        PPCSetFpNonIEEEMode();

        BI2DebugFlag = 0;
        BootInfo = (OSBootInfo*)OS_BASE_CACHED;

        __DVDLongFileNameFlag =
            (u32)0;

        DebugInfo = (BI2Debug*)*((u32*)OS_BI2_DEBUG_ADDRESS);

        if (DebugInfo != NULL)
        {
            BI2DebugFlag = &DebugInfo->debugFlag;
            __PADSpec = (u32)DebugInfo->padSpec;
            *((u8*)DEBUGFLAG_ADDR) = (u8)*BI2DebugFlag;
            *((u8*)OS_DEBUG_ADDRESS_2) = (u8)__PADSpec;
        }
        else if (BootInfo->arenaHi)
        {
            BI2DebugFlagHolder =
                (u32*)*((u8*)DEBUGFLAG_ADDR);
            BI2DebugFlag = (u32*)&BI2DebugFlagHolder;
            __PADSpec = (u32) * ((u8*)OS_DEBUG_ADDRESS_2);
        }

        __DVDLongFileNameFlag = 1;

        OSSetArenaLo((BootInfo->arenaLo == NULL) ? __ArenaLo : BootInfo->arenaLo);

        if ((BootInfo->arenaLo == NULL) && (BI2DebugFlag != 0) && (*BI2DebugFlag < 2))
        {
            debugArenaLo = (char*)(((u32)_db_stack_end + 0x1f) & ~0x1f);
            OSSetArenaLo(debugArenaLo);
        }

        OSSetArenaHi((BootInfo->arenaHi == NULL) ? __ArenaHi : BootInfo->arenaHi);

        OSExceptionInit();
        __OSInitSystemCall();
        OSInitAlarm();
        __OSModuleInit();
        __OSInterruptInit();
        __OSSetInterruptHandler(__OS_INTERRUPT_PI_RSW, (void*)__OSResetSWInterruptHandler);
        __OSContextInit();
        __OSCacheInit();
        EXIInit();
        SIInit();
        __OSInitSram();
        __OSThreadInit();
        __OSInitAudioSystem();
        PPCMthid2(PPCMfhid2() & 0xBFFFFFFF);
        if ((BOOL)__OSInIPL == FALSE)
        {
            __OSInitMemoryProtection();
        }

        OSReport("\nDolphin OS\n");
        OSReport("Kernel built : %s %s\n", "Apr 17 2003", "12:33:06");
        OSReport("Console Type : ");

        if (BootInfo == NULL || (inputConsoleType = BootInfo->consoleType) == 0)
        {
            inputConsoleType = OS_CONSOLE_ARTHUR;
        }
        else
        {
            inputConsoleType = BootInfo->consoleType;
        }

        switch (inputConsoleType & 0xF0000000)
        {
        case OS_CONSOLE_RETAIL:
            OSReport("Retail %d\n", inputConsoleType);
            break;
        case OS_CONSOLE_DEVELOPMENT:
        case OS_CONSOLE_TDEV:

            switch (inputConsoleType & 0x0FFFFFFF)
            {
            case OS_CONSOLE_EMULATOR:
                OSReport("Mac Emulator\n");
                break;
            case OS_CONSOLE_PC_EMULATOR:
                OSReport("PC Emulator\n");
                break;
            case OS_CONSOLE_ARTHUR:
                OSReport("EPPC Arthur\n");
                break;
            case OS_CONSOLE_MINNOW:
                OSReport("EPPC Minnow\n");
                break;
            default:
                tdev = (u32)inputConsoleType & 0x0FFFFFFF;
                OSReport("Development HW%d (%08x)\n", tdev - 3, inputConsoleType);
                break;
            }
            break;
        default:
            OSReport("%08x\n", inputConsoleType);
            break;
        }

        OSReport("Memory %d MB\n", (u32)BootInfo->memorySize >> 0x14U);

        OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());

        OSRegisterVersion(__OSVersion);

        if (BI2DebugFlag && ((*BI2DebugFlag) >= 2))
        {
            EnableMetroTRKInterrupts();
        }

        ClearArena();
        OSEnableInterrupts();

        if ((BOOL)__OSInIPL == FALSE)
        {
            DVDInit();
            if ((BOOL)__OSIsGcam)
            {
                __OSDeviceCode = 0x9000;
                return;
            }
            DCInvalidateRange(&DriveInfo, sizeof(DriveInfo));
            DVDInquiryAsync(&DriveBlock, &DriveInfo, InquiryCallback);
        }
    }
}

static u32 __OSExceptionLocations[] = {
    0x00000100, 0x00000200, 0x00000300, 0x00000400, 0x00000500, 0x00000600, 0x00000700, 0x00000800,
    0x00000900, 0x00000C00, 0x00000D00, 0x00000F00, 0x00001300, 0x00001400, 0x00001700,
};

void __OSEVStart(void);
void __OSEVEnd(void);
void __OSEVSetNumber(void);
void __OSExceptionVector(void);

void __DBVECTOR(void);
void __OSDBINTSTART(void);
void __OSDBINTEND(void);
void __OSDBJUMPSTART(void);
void __OSDBJUMPEND(void);

#define NOP 0x60000000

__OSExceptionHandler __OSSetExceptionHandler(__OSException exception, __OSExceptionHandler handler);

static void OSExceptionInit(void)
{
    __OSException exception;
    void* destAddr;

    u32* opCodeAddr;
    u32 oldOpCode;

    u8* handlerStart;
    u32 handlerSize;

    opCodeAddr = (u32*)__OSEVSetNumber;
    oldOpCode = *opCodeAddr;
    handlerStart = (u8*)__OSEVStart;
    handlerSize = (u32)((u8*)__OSEVEnd - (u8*)__OSEVStart);

    destAddr = (void*)OSPhysicalToCached(OS_DBJUMPPOINT_ADDR);
    if (*(u32*)destAddr == 0)
    {
        DBPrintf("Installing OSDBIntegrator\n");
        memcpy(destAddr, (void*)__OSDBINTSTART, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
        DCFlushRangeNoSync(destAddr, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
        __sync();
        ICInvalidateRange(destAddr, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
    }

    for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++)
    {
        if (BI2DebugFlag && (*BI2DebugFlag >= 2) && __DBIsExceptionMarked(exception))
        {

            DBPrintf(">>> OSINIT: exception %d commandeered by TRK\n", exception);
            continue;
        }

        *opCodeAddr = oldOpCode | exception;

        if (__DBIsExceptionMarked(exception))
        {
            DBPrintf(">>> OSINIT: exception %d vectored to debugger\n", exception);
            memcpy((void*)__DBVECTOR, (void*)__OSDBJUMPSTART,
                   (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART);
        }
        else
        {

            u32* ops = (u32*)__DBVECTOR;
            int cb;

            for (cb = 0; cb < (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART; cb += sizeof(u32))
            {
                *ops++ = NOP;
            }
        }

        destAddr = (void*)OSPhysicalToCached(__OSExceptionLocations[(u32)exception]);
        memcpy(destAddr, handlerStart, handlerSize);
        DCFlushRangeNoSync(destAddr, handlerSize);
        __sync();
        ICInvalidateRange(destAddr, handlerSize);
    }

    OSExceptionTable = OSPhysicalToCached(OS_EXCEPTIONTABLE_ADDR);

    for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++)
    {
        __OSSetExceptionHandler(exception, OSDefaultExceptionHandler);
    }

    *opCodeAddr = oldOpCode;

    DBPrintf("Exceptions initialized...\n");
}

__OSExceptionHandler __OSSetExceptionHandler(__OSException exception, __OSExceptionHandler handler)
{
    __OSExceptionHandler oldHandler;
    oldHandler = OSExceptionTable[exception];
    OSExceptionTable[exception] = handler;
    return oldHandler;
}

__OSExceptionHandler __OSGetExceptionHandler(__OSException exception)
{
    return OSExceptionTable[exception];
}

void __OSUnhandledException(__OSException exception, OSContext* context, u32 dsisr, u32 dar);

#define DI_CONFIG_IDX 0x9
#define DI_CONFIG_CONFIG_MASK 0xFF
u32 __OSGetDIConfig(void)
{
    return (__DIRegs[DI_CONFIG_IDX] & DI_CONFIG_CONFIG_MASK);
}

void OSRegisterVersion(const char* id)
{
    OSReport("%s\n", id);
}
