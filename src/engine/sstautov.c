/* Sound stream automatic volume (sstautov.c): fades all six speaker slots of a stream to a new
   volume over a time, through faders linked on the stream fader list, and the fader callback
   that steps a slot's volume and applies it to the stream's voice. */

#include "engine/sndstrm.h"

namespace Snd {

void StreamFader(void *context)
{
    SndStreamSpeaker_t *sp;
    SndStreamChannel_t *channel;
    Record_803A6DF0 *record;
    Record_803A6DF0 *dst;
    int voice;
    int slot;
    int index;
    int i;
    float vol;
    int offset;
    SndStreamFader_t *fader;

    sp = (SndStreamSpeaker_t *)context;
    sp->mVolume += sp->mStep;
    if (!(sp->mStep >= 0.0f)) {
        if (!(sp->mVolume > sp->mTarget)) {
            sp->mVolume = sp->mTarget;
            sp->mStep = 0.0f;
        }
    } else if (!(sp->mVolume < sp->mTarget)) {
        sp->mVolume = sp->mTarget;
        sp->mStep = 0.0f;
    }
    offset = sp->mIndex * sizeof(SndStreamSpeaker_t) + 316;
    channel = (SndStreamChannel_t *)((char *)sp - offset);
    voice = fn_8026A288(channel->mVoice);
    if (voice >= 0) {
        record = &lbl_803A6C24.m1CC[voice];
        slot = lbl_802B79A0[record->m23 - 1][sp->mIndex];
        if (slot != -128) {
            index = record->m4[slot];
            dst = &lbl_803A6C24.m1CC[index];
            vol = sp->mVolume;
            dst->m38 = vol;
            dst->m48 = vol * lbl_80300028;
            fn_802747D8(index);
            for (i = 0; i < lbl_8030002C; i++) {
                fn_80271BD4(voice, i);
            }
        }
    }
    if (sp->mStep == 0.0f) {
        fader = &sp->mFader;
        if (fader == lbl_803A763C) {
            lbl_803A763C = fader->mpNext;
        }
        if (fader->mpPrev != 0) {
            fader->mpPrev->mpNext = fader->mpNext;
        }
        if (fader->mpNext != 0) {
            fader->mpNext->mpPrev = fader->mpPrev;
        }
    }
}

}

extern "C" {

int SNDSTRM_autovol(int stream, int time, int vol)
{
    SndStreamChannel_t *channel;
    SndStreamSpeaker_t *sp;
    float target;
    int i;
    SndStreamFader_t *fader;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    target = (float)vol * (1.0f / 127.0f);
    if (time <= 0) {
        return SNDSTRM_setvol(stream, -1, target);
    }
    for (i = 0; i <= 5; i++) {
        sp = &channel->mSpeakers[i];
        if (sp->mStep != 0.0f) {
            fader = &sp->mFader;
            if (fader == lbl_803A763C) {
                lbl_803A763C = fader->mpNext;
            }
            if (fader->mpPrev != 0) {
                fader->mpPrev->mpNext = fader->mpNext;
            }
            if (fader->mpNext != 0) {
                fader->mpNext->mpPrev = fader->mpPrev;
            }
        }
        sp->mTarget = target;
        sp->mStep = (target - sp->mVolume) * lbl_803A7644 / (float)time;
        if (sp->mStep != 0.0f) {
            sp->mFader.mpCallback = Snd::StreamFader;
            sp->mFader.mpContext = sp;
            fader = &sp->mFader;
            fader->mpNext = lbl_803A763C;
            fader->mpPrev = 0;
            if (lbl_803A763C != 0) {
                lbl_803A763C->mpPrev = fader;
            }
            lbl_803A763C = fader;
        }
    }
    return 0;
}

}
