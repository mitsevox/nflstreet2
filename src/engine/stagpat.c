/* Tagged patch playback (stagpat.c): plays a sound bank patch whose timbres are tagged with key and
   velocity ranges, starting one voice per timbre that covers the requested key and velocity and
   grouping the voices under a fresh group key so they can later be released together. */

#include "engine/sndbank.h"

extern "C" {

int randrange(int range);
int SNDover(int handle);
int fn_80270518(int a, int b, BankVer_t *bank, SndPlayOpts_t *opts, Struct_80270E04 *tag, int velocity, int key,
                int random);

unsigned char SNDBANKI_findfreekey(void)
{
    static unsigned char freekey = 0;
    int i;

retry:
    if (++freekey == 0) {
        ++freekey;
    }
    for (i = 0; i < lbl_803A6C24.m16C; i++) {
        Record_803A6DF0 *v = &lbl_803A6C24.m1CC[i];

        if (v->m6D != 0 && v->m26 == freekey) {
            goto retry;
        }
    }
    return freekey;
}

#if defined(DECOMP_COMPARE)
int SNDBANKI_playpatch(BankVer_t *bank, void *patch, int bank_index, int patch_index, SndPlayOpts_t *opts)
{
    Struct_80270E04 tag;
    int handles[12];
    Record_803A6DF0 *v = 0;
    int count = 0;
    int started = 0;
    int random = 0;
    int result = -9;
    int more;
    int velocity;
    int key;
    int group;
    int total;
    int i;
    int index;

    if (patch == 0) {
        return -8;
    }
    if (bank == 0) {
        bank = (BankVer_t *)patch;
    }
    velocity = (signed char)opts->m2;
    key = (signed char)opts->m3;
    patch = (char *)patch + 4;
    group = SNDBANKI_findfreekey();
    do {
        more = fn_80270E04((char **)&patch, &tag);
        if (started == 0) {
            if (tag.m0 != 0) {
                random = randrange(tag.m0);
            }
            started = 1;
        }
        if (key >= tag.m8 && key <= tag.m9 && velocity >= tag.mA && velocity <= tag.mB) {
            result = fn_80270518(bank_index, patch_index, bank, opts, &tag, velocity, key, random);
            if (result < 0) {
                goto fail;
            }
            handles[count++] = result;
            fn_8026A40C(&tag, 1);
        }
    } while (more != 0);

    total = count;
    count = 0;
    for (i = 0; i < total; i++) {
        if (SNDover(handles[i]) == 0) {
            handles[count++] = handles[i];
        }
    }
    if (count == 0) {
        goto fail;
    }
    if (count == 1) {
        index = SNDVOICEI_get(handles[0]);
        if (index >= 0) {
            v = &lbl_803A6C24.m1CC[index];
            v->m26 = 0;
            v->m27 = 0;
        }
    } else {
        for (i = 0; i < count; i++) {
            index = SNDVOICEI_get(handles[i]);
            if (index >= 0) {
                v = &lbl_803A6C24.m1CC[index];
                v->m26 = group;
                v->m27 = 0;
            }
        }
        v->m27 = 1;
    }
    return result;

fail:
    for (i = 0; i < count; i++) {
        SNDstop(handles[i]);
    }
    return result;
}
#endif

}
