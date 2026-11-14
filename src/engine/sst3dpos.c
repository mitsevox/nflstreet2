/* Sound stream azimuth (sst3dpos.c): places one speaker slot of a stream, or all six, at an
   angle around the listener, or returns them to their speaker defaults, and sets the pan of
   the stream's voices to match. */

#include "engine/sndstrm.h"

extern "C" {

extern unsigned char lbl_802C1F62[][6][6];
extern unsigned char lbl_802C1FF2[][6];
extern int lbl_803A772C;

int SNDSTRM_setazimuth(int stream, int speaker, float azimuth)
{
    SndStreamChannel_t *channel;
    SndStreamSpeaker_t *sp;
    Record_803A6DF0 *record;
    Record_803A6DF0 *dst;
    unsigned char *pans;
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
    angle = azimuth * (65536.0f / 360.0f);
    if (!(angle < 0.0f)) {
        pan = (int)(angle + 0.5f);
    } else {
        pan = (int)(angle - 0.5f);
    }
    on = 0;
    channel->mPanned = 0;
    if (speaker == -1) {
        if (azimuth == -1000000.0f) {
            angle = -1000000.0f;
        } else {
            angle = azimuth;
        }
        for (i = 0; i <= 5; i++) {
            channel->mSpeakers[i].mAzimuth = angle;
            channel->mSpeakers[i].mAzimuthOn = on;
        }
    } else {
        sp = &channel->mSpeakers[speaker];
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
                pans = lbl_802C1F62[lbl_803A772C][record->m23];
                for (i = 0; i < record->m23; i++) {
                    dst = lbl_803A6C24.m1CC + record->m4[i];
                    dst->m1C = pans[i] << 8;
                    fn_80274960(record->m4[i]);
                }
            } else {
                pans = lbl_802C1FF2[channel->mChannels];
                for (i = 0; i < record->m23; i++) {
                    dst = lbl_803A6C24.m1CC + record->m4[i];
                    dst->m1C = pan + (pans[i] << 8);
                    fn_80274960(record->m4[i]);
                }
            }
        } else {
            slot = lbl_802B79A0[record->m23 - 1][speaker];
            index = record->m4[slot];
            dst = &lbl_803A6C24.m1CC[index];
            if (slot != -128) {
                if (azimuth == -1000000.0f) {
                    dst->m1C = lbl_802C1F62[lbl_803A772C][record->m23][slot] << 8;
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
