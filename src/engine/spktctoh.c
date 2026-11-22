/* Sound packet players (spktctoh.c): finds the packet player whose handle owns a voice. */

#include "engine/sndsys.h"

extern "C" {

int SNDPKTPLAYI_voicetopackethandle(int handle)
{
    int i;
    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        if (sndpps.mPlayers[i] != 0 && SNDVOICEI_get(sndpps.mPlayers[i]->mVoiceHandle) == handle) {
            return i;
        }
    }
    return -1;
}

}
