/* Tagged patch playback (stagpat.c): plays a sound bank patch whose timbres are tagged with key and
   velocity ranges, starting one voice per timbre that covers the requested key and velocity and
   grouping the voices under a fresh group key so they can later be released together. */

#include "engine/sndbank.h"

extern "C" {

int randrange(int range);
int SNDover(int handle);
int SNDI_validrendermode(int *mode, Struct_80270E04 *header);
int SNDVOICEI_alloc(int count, int priority, int *handle, int rate, int format);
int SNDI_pantoazimuth(int pan);
extern const unsigned char lbl_802C1F68[][6][6];

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

int SNDBANKI_playtimbre(int bank_index, int patch_index, BankVer_t *bank, SndPlayOpts_t *opts, Struct_80270E04 *tag,
                        int key, int velocity, int detune)
{
    Record_803A6DF0 *rec;
    Record_803A6DF0 *ch;
    const unsigned char *table;
    float level;
    int rate;
    int format;
    int result = -9;
    int cursor = 0;
    int found = 0;
    int render;
    int voice;
    int pan;
    int volume;
    int send;
    int azimuth;
    int index;
    int i;

    pan = (signed char)opts->m1;
    send = (signed char)opts->m5;
    // FAKEMATCH: found is never set (success leaves by break), as in SNDPKTPLAY_start
    while (!found && (render = SNDI_validrendermode(&cursor, tag)) != 0) {
        SNDPLATFORM_getvoicerange(render, &rate, &format);
        voice = SNDVOICEI_alloc(tag->m3, tag->mC, &result, rate, format);
        if (voice < 0) {
            continue;
        }
        rec = &lbl_803A6C24.m1CC[voice];
        azimuth = tag->m11;
        if (tag->m12 != 0) {
            azimuth += randrange(tag->m12);
            if (azimuth < 0) {
                azimuth = 0;
            } else if (azimuth > 127) {
                azimuth = 127;
            }
        }
        rec->m4C = SNDI_pantoazimuth(azimuth);
        rec->m88 = tag->m4;
        rec->m88 -= (tag->mD - key) * 100;
        if (detune != 0) {
            rec->m88 += detune;
        }
        if (tag->m6 != 0) {
            rec->m88 += randrange(tag->m6);
        }
        rec->m78 = tag->m24;
        volume = tag->m14;
        if (tag->m15 != 0) {
            volume += randrange(tag->m15);
        }
        if (volume > 127) {
            volume = 127;
        }
        if (volume < 0) {
            volume = 0;
        }
        rec->m86 = tag->m10 * 100;
        rec->m68 = pan;
        volume = volume * velocity / 127;
        rec->m70 = tag->m28;
        rec->m40 = tag->m1A << 16;
        rec->m44 = rec->m70->m0;
        if (rec->m44 < 0) {
            rec->m44 = 0x7FFFFFFF;
        }
        rec->m3C = ((rec->m70->m4 << 16) - rec->m40) / rec->m44;
        rec->m80 = tag->m30;
        rec->m6A = tag->m1D;
        rec->m84 = tag->m54;
        if (tag->m1C != 0) {
            rec->m6B = iSNDrandom() % tag->m1C;
        } else {
            rec->m6B = 0;
        }
        if (tag->m1E != 0) {
            rec->m6C = iSNDrandom() % tag->m1D;
        } else {
            rec->m6C = 0;
        }
        rec->m6E = opts->mE;
        rec->m8A = 0;
        rec->m8C = opts->mC;
        iSNDcalcpitch(voice);
        rec->m4[7] = bank_index;
        rec->m4[6] = patch_index;
        rec->m18 = tag->m60;
        rec->m14 = tag->m58;
        rec->m20 = tag->m56;
        rec->m22 = tag->m13;
        rec->m23 = tag->m3;
        level = (signed char)opts->m0 * (1.0f / 127.0f);
        for (i = 0; i < tag->m3; i++) {
            rec->m50[i] = tag->mBC[i] - lbl_803A6C24.m1D8[tag->m3 - 1][i];
            index = rec->m4[i];
            ch = &lbl_803A6C24.m1CC[index];
            ch->m24 = render;
            ch->m2B = volume;
            ch->m38 = level;
            ch->m5F = opts->m4;
            ch->m30 = 0.0f;
            ch->m74 = tag->m20;
            ch->m5C = tag->mF;
            ch->m5D = 0;
            ch->m5E = tag->mE;
            ch->m40 = rec->m40;
            ch->m44 = rec->m44;
            ch->m3C = rec->m3C;
            ch->m70 = rec->m70;
            ch->m69 = tag->m1B;
            ch->m6B = rec->m6B;
            ch->m7C = tag->m2C;
            fn_80278598(index);
            if (i == 5) {
                ch->m4E = 1;
            } else {
                ch->m4E = 0;
            }
        }
        if (tag->m3 == 1) {
            rec->m1C = rec->m4C + opts->m8;
            rec->m1C += rec->m50[0];
            rec->m1E = opts->mA;
        } else {
            table = lbl_802C1F68[lbl_803A772C][tag->m3 - 1];
            for (i = 0; i < tag->m3; i++) {
                ch = &lbl_803A6C24.m1CC[rec->m4[i]];
                ch->m1C = table[i] << 8;
                ch->m1E = 0;
                ch->m1C += rec->m50[i];
            }
        }
        rec->m60 = send;
        for (i = 0; i < lbl_8030002C; i++) {
            rec->m64[i] = send * (1.0f / 127.0f);
        }
        if (SNDPLATFORM_playtimbre((Header_80273DF8 *)tag, (int)bank, voice, opts->mE, opts->m14, opts->m16) >= 0) {
            break;
        }
        for (i = 0; i < tag->m3; i++) {
            SNDVOICEI_free(lbl_803A6C24.m1CC[voice].m4[i]);
        }
        result = -9;
    }
    return result;
}

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
    int key;
    int velocity;
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
    key = (signed char)opts->m2;
    velocity = (signed char)opts->m3;
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
        if (velocity >= tag.m8 && velocity <= tag.m9 && key >= tag.mA && key <= tag.mB) {
            result = SNDBANKI_playtimbre(bank_index, patch_index, bank, opts, &tag, key, velocity, random);
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

}
