/* Finds the next sound output mode that meets a patch's playback requirements. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"

extern "C" {

int SNDI_validrendermode(int *modeCursor, const SNDIPATCHHEADER *header)
{
    int result = 0;
    // FAKEMATCH: reuse the index for the first mask and keep the branch-local cursor reloads.
    int index = *modeCursor;

    while (index < lbl_803A6C24.m1C.m28) {
        int patchFlags;
        int caps;
        int request;
        int candidate = index;
        index = header->m18;
        patchFlags = index;
        index &= 0x70C;
        result = lbl_803A6C24.m1C.m2A[candidate] & 0x70C;
        if (index != 0 && (result &= patchFlags) == 0) {
            index = *(volatile int *)modeCursor;
            goto advance;
        }

        index = *(volatile int *)modeCursor;
        request = patchFlags & 0x60;
        caps = lbl_803A6C24.m1C.m2A[index];
        caps &= 0x60;
        if (request != 0) {
            caps &= patchFlags;
            result |= caps;
            if (caps == 0) {
                result = 0;
                goto advance;
            }
        } else {
            result |= caps;
        }

        if (result != 0) {
            *modeCursor = index + 1;
            return result;
        }

advance:
        *modeCursor = ++index;
    }

    return result;
}

}
