/* Sound stream volume (sstvol.c): sets the volume of one speaker slot of a stream, or of all
   six, stopping any fade in progress, and passes it to the stream's voices. It also holds the
   table that maps a voice's channel count and a speaker slot to the voice channel playing it. */

#include "engine/sndstrm.h"

extern "C" {

const signed char lbl_802B79A0[6][6] = {
    { 0, -128, -128, -128, -128, -128 },
    { -128, 0, 1, -128, -128, -128 },
    { -128, -128, -128, -128, -128, -128 },
    { -128, 0, 1, 2, 3, -128 },
    { -128, -128, -128, -128, -128, -128 },
    { 1, 0, 2, 3, 4, 5 },
};

int SNDSTRM_setvol(int stream, int speaker, float vol)
{
    SndStreamChannel_t *channel;
    SndStreamSpeaker_t *sp;
    Record_803A6DF0 *record;
    Record_803A6DF0 *dst;
    int voice;
    int slot;
    int index;
    int changed;
    int i;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    if (speaker == -1) {
        for (i = 0; i <= 5; i++) {
            sp = &channel->mSpeakers[i];
            sp->mVolume = vol;
            if (sp->mStep != 0.0f) {
                if (&sp->mFader == lbl_803A763C) {
                    lbl_803A763C = sp->mFader.mpNext;
                }
                if (sp->mFader.mpPrev != 0) {
                    sp->mFader.mpPrev->mpNext = sp->mFader.mpNext;
                }
                if (sp->mFader.mpNext != 0) {
                    sp->mFader.mpNext->mpPrev = sp->mFader.mpPrev;
                }
                sp->mStep = 0.0f;
            }
        }
    } else {
        sp = &channel->mSpeakers[speaker];
        sp->mVolume = vol;
        if (sp->mStep != 0.0f) {
            if (&sp->mFader == lbl_803A763C) {
                lbl_803A763C = sp->mFader.mpNext;
            }
            if (sp->mFader.mpPrev != 0) {
                sp->mFader.mpPrev->mpNext = sp->mFader.mpNext;
            }
            if (sp->mFader.mpNext != 0) {
                sp->mFader.mpNext->mpPrev = sp->mFader.mpPrev;
            }
            sp->mStep = 0.0f;
        }
    }
    voice = fn_8026A288(channel->mVoice);
    if (voice >= 0) {
        if (speaker == -1) {
            record = &lbl_803A6C24.m1CC[voice];
            changed = 0;
            for (i = 0; i < record->m23; i++) {
                dst = lbl_803A6C24.m1CC + record->m4[i];
                if (dst->m38 != vol) {
                    changed = 1;
                    dst->m38 = vol;
                    dst->m48 = vol * lbl_80300028;
                    fn_802747D8(record->m4[i]);
                }
            }
            if (changed) {
                for (i = 0; i < lbl_8030002C; i++) {
                    fn_80271BD4(voice, i);
                }
            }
        } else {
            record = &lbl_803A6C24.m1CC[voice];
            slot = lbl_802B79A0[record->m23 - 1][speaker];
            if (slot != -128) {
                index = record->m4[slot];
                dst = &lbl_803A6C24.m1CC[index];
                dst->m30 = 0.0f;
                if (dst->m38 != vol) {
                    dst->m38 = vol;
                    dst->m48 = vol * lbl_80300028;
                    fn_802747D8(index);
                    for (i = 0; i < lbl_8030002C; i++) {
                        fn_80271BD4(voice, i);
                    }
                }
            }
        }
    }
    return 0;
}

}
