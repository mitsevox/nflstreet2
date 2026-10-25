/* Partial source for the inferred grouping 0x802898FC-0x80289A20 (neutral file name). */

#include "engine/cu_802714A8.h"

int fn_8026A288(int handle);
int fn_8026C910(int handle, int *index);
int fn_8026E160(int a, int b, int c, int d, int e);
int fn_80274EAC(int index);

int fn_802898FC(int a, int b, int c, int d)
{
    return fn_8026E160(a, b, c + d, 0, 1);
}

int fn_80289928(int id)
{
    int handle;
    int index;
    int best;
    int value;
    int level;
    Record_803A6DF0 *record;

    handle = fn_8026A288(id);
    best = -7;
    if (handle >= 0) {
        index = -1;
        while (fn_8026C910(handle, &index)) {
            record = &lbl_803A6C24.m1CC[index];
            if (record->m18 > 0) {
                value = -7;
            } else {
                value = fn_80274EAC(index);
            }
            if (value >= 0) {
                level = (record->m14 - value) * 100 / record->m20;
                if (record->m8E > 16) {
                    level = (level << 12) / record->m8E;
                    level = (level << 12) / record->m6E;
                } else {
                    level = 0x7FFFFFFF;
                }
                if (level > best) {
                    best = level;
                }
            }
        }
    }
    return best;
}