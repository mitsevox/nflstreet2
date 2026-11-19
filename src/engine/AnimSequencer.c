/* Animation sequencer module: start-up and shut-down, and the frame rate that
   turns sequence frame times into seconds for scripted sequences of players and
   cameras. */

#include "engine/AnimSeqCamera.h"
#include "engine/SysSetLastErrorFunc.h"

extern unsigned char _AnimSequencer_ModuleActive;
extern float _AnimSequencer_fTicksPerSecond;

int AnimSequencerInit(float rate)
{
    int err = 0;

    if (_AnimSequencer_ModuleActive)
        err = 0x1D0001;
    else {
        _AnimSequencer_fTicksPerSecond = rate;
        _AnimSequencer_ModuleActive = 1;
    }
    SysSetLastErrorFunc(err);
    return err;
}

int AnimSequencerShutdown(void)
{
    int err = 0;

    if (_AnimSequencer_ModuleActive)
        _AnimSequencer_ModuleActive = 0;
    else
        err = 0x1D0002;
    SysSetLastErrorFunc(err);
    return err;
}

float AnimSequencerGetTicksPerSecond(void)
{
    return _AnimSequencer_fTicksPerSecond;
}
