/* Mixer pitch (smixptch.c): creates a mixer voice's resampling node on first use and sets its
   pitch, clamped to 0x40000. */

#include "engine/sndlib.h"

void MIX_setpitch(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node;
    int flag = 0;

    if (value > 0x40000) {
        value = 0x40000;
    }
    node = record->m50;
    if (node == 0) {
        record->m50 = (Node_80279D90 *)SNDMEMI_allocz(60);
        if (lbl_803B4E34.mE > 49) {
            flag = 1;
        }
        record->m50->m4 = 0;
        record->m50->m18 = 160;
        record->m50->m1A = 0;
        fn_8027A7A0(record->m50, lbl_803A6C24.m16F, flag);
        fn_80279D90(&record->m40, record->m50);
    }
    fn_8027A4C0(record->m50, value);
}
