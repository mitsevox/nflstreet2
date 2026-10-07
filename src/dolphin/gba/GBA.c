#include "dolphin/gba.h"

static int OnReset(BOOL final);
static void ShortCommandProc(s32 chan);

static OSResetFunctionInfo ResetFunctionInfo = { OnReset, 0x7E };
static GBASecParam SecParams[4] ATTRIBUTE_ALIGN(32);
GBAControl __GBA[4];
BOOL __GBAReset;

static void ShortCommandProc(s32 chan)
{
	GBAControl* port = &__GBA[chan];
	if (port->ret != 0) {
		return;
	}
	if ((port->input[0] != 0) || (port->input[1] != 4)) {
		port->ret = 1;
		return;
	}
	*port->status = port->input[2] & 0x3A;
}

void GBAInit(void)
{
	GBAControl* gba;
	s32 chan;

	for (chan = 0; chan < 4; ++chan) {
		gba        = &__GBA[chan];
		gba->delay = OSMicrosecondsToTicks(60);
		OSInitThreadQueue(&gba->threadQueue);
		gba->param = &SecParams[chan];
	}
	OSInitAlarm();

	DSPInit();

	__GBAReset = FALSE;
	OSRegisterResetFunction(&ResetFunctionInfo);
}

int GBAGetStatusAsync(s32 chan, u8* statusPtr)
{
	GBAControl* gba = &__GBA[chan];
	if (gba->callback) {
		return 2;
	}

	gba->output[0] = 0;
	gba->status    = statusPtr;
	gba->callback  = __GBASyncCallback;
	return __GBATransfer(chan, 1, 3, ShortCommandProc);
}

int GBAGetStatus(s32 chan, u8* statusPtr)
{
	int status = GBAGetStatusAsync(chan, statusPtr);
	return (status != 0) ? status : __GBASync(chan);
}

int GBAResetAsync(s32 chan, u8* statusPtr)
{
	GBAControl* gba = &__GBA[chan];
	if (gba->callback) {
		return 2;
	}

	gba->output[0] = 0xFF;
	gba->status    = statusPtr;
	gba->callback  = __GBASyncCallback;
	return __GBATransfer(chan, 1, 3, ShortCommandProc);
}

int GBAReset(s32 chan, u8* statusPtr)
{
	int status = GBAResetAsync(chan, statusPtr);
	return (status != 0) ? status : __GBASync(chan);
}

static int OnReset(BOOL final)
{
	__GBAReset = TRUE;
	return 1;
}
