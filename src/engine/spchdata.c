/* Speech library globals: the code-less data file of the play-by-play speech library. It holds
   the callbacks, event and bank tables, allocator and timing state that the speech files share. */

#include "engine/spchlib.h"
#include "engine/spchevnt.h"

extern "C" {

SpchExtVecs_t gExtVecs = { 0, 0, 0 };

SpchAllocator *gSPCH_Allocator = 0;
int gSPCH_Initialized = 0;
VoxBankSlot_t *gVoxBanks = 0;
int gUniqueBankHandle = 0;
int gNumBanks = 0;
int gBankCount = 0;
int (*gSPCH_AddEvent)(int, int, ...) = 0;
int gClearCycle = 1;

SpchCallbacks_t gCallbacks;
VoxDatSlot_t gEventDats[8];
VoxEventQueue_t gVoxEvents;
VoxInGameSlot_t gVoxInGame[8];
int gFilterSetting[8];

int gGameNum;
int gDataRate;
int gPreLoadTicks;
unsigned int gLastTick;
unsigned short gLastSubTick;
}
