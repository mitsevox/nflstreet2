/* Sound output map (soutputmap.cpp): sets how many output channels the mixer and stream loops run over;
   the count can only be changed before the sound system has started. */

#include "engine/sndsys.h"
#include "engine/sndlib.h"

extern "C" {

int SNDsetoutputchannels(int count)
{
    if (lbl_803A6C24.m168 == 0) {
        lbl_8030002C = count;
    }
    return 0;
}

}
