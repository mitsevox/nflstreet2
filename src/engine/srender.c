/* Sound render mode (srender.c): finds the next output render mode, from the cursor *mode on, whose
   capability bits (config +0x46 table) fit the patch header flags; advances the cursor past it. */

#include "engine/sndsys.h"

extern "C" {

int SNDI_validrendermode(int *mode, SndPatchHeader_t *header)
{
    int result = 0;
    unsigned int flags;
    unsigned int caps;

    while (*mode < lbl_803A6C24.m1C.m28) {
        flags = header->m18;
        result = lbl_803A6C24.m1C.m2A[*mode] & 0x70C;
        if ((flags & 0x70C) == 0 || (result &= flags) != 0) {
            caps = lbl_803A6C24.m1C.m2A[*mode] & 0x60;
            if ((flags & 0x60) != 0) {
                caps &= flags;
                result |= caps;
                if (caps == 0) {
                    result = 0;
                }
            } else {
                result |= caps;
            }
            if (result != 0) {
                (*mode)++;
                return result;
            }
        }
        (*mode)++;
    }
    return result;
}

}
