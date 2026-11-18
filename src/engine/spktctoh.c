/* Sound packet players (spktctoh.c): finds the packet player whose handle owns a voice. */

#include "engine/sndsys.h"

extern "C" {

int SNDPKTPLAYI_voicetopackethandle(int handle)
{
    int i;
    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        if (sndpps.m304[i] != 0 && fn_8026A288(sndpps.m304[i]->m0) == handle) {
            return i;
        }
    }
    return -1;
}

}
