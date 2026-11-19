/* Sound stream azimuth (sst3dpos.c): places one speaker slot of a stream, or all six, at an
   angle around the listener, or returns them to their speaker defaults, and sets the pan of
   the stream's voices to match. */

#include "engine/sndstrm.h"

extern "C" {

extern const unsigned char lbl_802C1F68[][6][6];
extern unsigned char lbl_802C1FF8[][6];
extern int lbl_803A772C;

/* Rounds to the nearest integer, halves away from zero. */
// FAKEMATCH: file-static rounding helper as in sstrstat.c; written in place, the pan and loop registers swap
static inline int SNDSTRMI_round(float t)
{
    if (!(t < 0.0f)) {
        return (int)(t + 0.5f);
    }
    return (int)(t - 0.5f);
}

int SNDSTRM_setazimuth(int stream, int speaker, float azimuth)
{
    // FAKEMATCH: unused stack object; reproduces the target's 8 bytes at the frame bottom
    volatile int spare[2];
    SndStreamChannel_t *channel;
    Record_803A6DF0 *record;
    Record_803A6DF0 *dst;
    unsigned short pan;
    float angle;
    int voice;
    int slot;
    int index;
    int on;
    int i;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    pan = SNDSTRMI_round(azimuth * (65536.0f / 360.0f));
    on = 0;
    channel->mPanned = 0;
    if (speaker == -1) {
        if (azimuth == -1000000.0f) {
            angle = -1000000.0f;
        } else {
            angle = azimuth;
        }
        // FAKEMATCH: per-branch loop index, slot and pan-row pointers and this store order keep the target's register choice
        for (int j = 0; j <= 5; j++) {
            SndStreamSpeaker_t *sp = &channel->mSpeakers[j];

            sp->mAzimuthOn = 0;
            sp->mAzimuth = angle;
        }
    } else {
        SndStreamSpeaker_t *sp = &channel->mSpeakers[speaker];

        if (azimuth == -1000000.0f) {
            sp->mAzimuth = -1000000.0f;
        } else {
            sp->mAzimuth = azimuth;
            on = 1;
        }
        sp->mAzimuthOn = on;
    }
    voice = fn_8026A288(channel->mVoice);
    if (voice >= 0) {
        record = &lbl_803A6C24.m1CC[voice];
        if (speaker == -1) {
            if (azimuth == -1000000.0f) {
                const unsigned char *pans = lbl_802C1F68[lbl_803A772C][record->m23 - 1];

                for (i = 0; i < record->m23; i++) {
                    index = record->m4[i];
                    lbl_803A6C24.m1CC[index].m1C = pans[i] << 8;
                    fn_80274960(index);
                }
            } else {
                const unsigned char *pans = lbl_802C1FF8[channel->mChannels - 1];

                for (i = 0; i < record->m23; i++) {
                    index = record->m4[i];
                    lbl_803A6C24.m1CC[index].m1C = pan + (pans[i] << 8);
                    fn_80274960(index);
                }
            }
        } else {
            slot = SNDSTRMIspeakerchannel[record->m23 - 1][speaker];
            index = record->m4[slot];
            dst = &lbl_803A6C24.m1CC[index];
            if (slot != -128) {
                if (azimuth == -1000000.0f) {
                    const unsigned char *pans = lbl_802C1F68[lbl_803A772C][record->m23 - 1];

                    dst->m1C = pans[slot] << 8;
                } else {
                    dst->m1C = pan;
                }
                fn_80274960(index);
            }
        }
    }
    return 0;
}

}
