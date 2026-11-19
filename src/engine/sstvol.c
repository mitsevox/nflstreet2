/* Sound stream volume (sstvol.c): sets the volume of one speaker slot of a stream, or of all
   six, stopping any fade in progress, and passes it to the stream's voices. It also holds the
   table that maps a voice's channel count and a speaker slot to the voice channel playing it. */

#include "engine/sndstrm.h"

extern "C" {

const signed char SNDSTRMIspeakerchannel[6][6] = {
    { 0, -128, -128, -128, -128, -128 },
    { -128, 0, 1, -128, -128, -128 },
    { -128, -128, -128, -128, -128, -128 },
    { -128, 0, 1, 2, 3, -128 },
    { -128, -128, -128, -128, -128, -128 },
    { 1, 0, 2, 3, 4, 5 },
};

/* Sets one speaker slot's volume and stops its fade if one is running. */
// FAKEMATCH: the shared per-slot step is an inline helper; written in place, the slot address folds the 0x13C offset in a different order
static inline void _SNDSTRM_setspeakervol(SndStreamSpeaker_t *sp, float vol)
{
    sp->mVolume = vol;
    if (sp->mStep != 0.0f) {
        Snd::gVariableTimerList.Remove(&sp->mFader);
        sp->mStep = 0.0f;
    }
}

int SNDSTRM_setvol(int stream, int speaker, float vol)
{
    // FAKEMATCH: unused stack object; reproduces the target's 8 bytes at the frame bottom
    volatile int spare[2];
    SndStreamChannel_t *channel;
    Record_803A6DF0 *record;
    Record_803A6DF0 *dst;
    int voice;
    int slot;
    int index;
    int changed;
    int i = 0;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    if (speaker == -1) {
        for (i = 0; i <= 5; i++) {
            _SNDSTRM_setspeakervol(&channel->mSpeakers[i], vol);
        }
    } else {
        _SNDSTRM_setspeakervol(&channel->mSpeakers[speaker], vol);
    }
    voice = fn_8026A288(channel->mVoice);
    if (voice >= 0) {
        if (speaker == -1) {
            record = &lbl_803A6C24.m1CC[voice];
            changed = 0;
            for (i = 0; i < record->m23; i++) {
                index = record->m4[i];
                dst = lbl_803A6C24.m1CC + index;
                if (dst->m38 != vol) {
                    changed = 1;
                    dst->m38 = vol;
                    dst->m48 = vol * lbl_80300028;
                    fn_802747D8(index);
                }
            }
            if (changed) {
                for (i = 0; i < lbl_8030002C; i++) {
                    SNDPLATFORM_setfxlevel(voice, i);
                }
            }
        } else {
            // FAKEMATCH: a second record pointer for the single-slot path keeps it apart from the all-slot one in register allocation
            Record_803A6DF0 *rec = &lbl_803A6C24.m1CC[voice];

            slot = SNDSTRMIspeakerchannel[rec->m23 - 1][speaker];
            if (slot != -128) {
                index = rec->m4[slot];
                dst = &lbl_803A6C24.m1CC[index];
                dst->m30 = 0.0f;
                if (dst->m38 != vol) {
                    dst->m38 = vol;
                    dst->m48 = vol * lbl_80300028;
                    fn_802747D8(index);
                    for (i = 0; i < lbl_8030002C; i++) {
                        SNDPLATFORM_setfxlevel(voice, i);
                    }
                }
            }
        }
    }
    return 0;
}

}
