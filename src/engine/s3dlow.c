/* 3D sound position (s3dlow.c): sets the azimuth (clamped to -0x4000..0x3FFF) and the distance
   offset of every voice of a sound handle and updates their pan. */

#include "engine/sndsys.h"

extern "C" {

int SND3dpos(int id, int offset, int value)
{
    int handle;
    int index;
    int clamped;
    Record_803A6DF0 *record;

    if (value < -0x4000) {
        clamped = -0x4000;
    } else if (value > 0x3FFF) {
        clamped = 0x3FFF;
    } else {
        clamped = value;
    }
    handle = fn_8026A288(id);
    if (handle >= 0) {
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            record = &lbl_803A6C24.m1CC[index];
            if (record->m23 == 1) {
                record->m1E = clamped;
                record->m1C = record->m4C + offset + record->m50;
                if (lbl_803A772C == 0) {
                    record->m1C = 0;
                }
                fn_80274960(index);
            }
        }
    }
    return handle;
}

}
