/* Forwards audio voice data and compares scaled values across related voices. */

#include "engine/voicequery.h"
#include "engine/sndvoice.h"
#include "engine/cu_802714A8.h"

int AudioVoiceForwardData(int key, int value, void *data, int offset)
{
    return fn_8026E160(key, value, (unsigned char *)data + offset, 0, 1);
}

int AudioVoiceGetMaxMetric(int id)
{
    int handle;
    int index;
    int best;
    int value;
    int metric;
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
                metric = (record->m14 - value) * 100 / record->m20;
                if (record->m8E > 16) {
                    metric = (metric << 12) / record->m8E;
                    metric = (metric << 12) / record->m6E;
                } else {
                    metric = 0x7FFFFFFF;
                }
                if (metric > best) {
                    best = metric;
                }
            }
        }
    }
    return best;
}
