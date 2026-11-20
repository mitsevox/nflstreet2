/* Sound MIDI sequencer (smidi.c): plays the sound banks' MIDI sequences on the 100 Hz sound server.
   Sixteen sequence slots keep their read cursor, volume fade and per-channel controller state; 24
   note slots tie each started voice to its sequence, channel and key so note-offs, fades and stops
   can find it. */

#include "engine/sndbank.h"

/* The controller state of one MIDI channel of a sequence: azimuth, volume and pitch bend as packed
   fields, then the channel's patch. */
typedef struct SndMidiChan_t {
    unsigned int mAzimuth : 10;
    unsigned int mVolume : 7;
    unsigned int mBend : 7;
    signed int mPatch : 8;
} SndMidiChan_t;

/* One sequence slot: server ticks +0x0 and the sequence position +0x4 they drive (at tempo +0x24),
   read cursor +0x8, handle +0x10, 16.16 volume +0x14 with its fade step and target, state byte +0x28
   and the 16 channel words +0x30. */
typedef struct SndMidiSeq_t {
    unsigned int mTicks;
    unsigned int mPosition;
    unsigned char *mpData;
    unsigned char *mpLoop;
    int mHandle;
    int mVolume;
    int mFadeStep;
    int mFadeTarget;
    unsigned short m20;
    unsigned short m22;
    unsigned short mTempo;
    unsigned char m26;
    unsigned char mDelta;
    unsigned char mState;
    unsigned char unk_0x29[3];
    short m2C;
    short m2E;
    SndMidiChan_t mChans[16];
} SndMidiSeq_t;

/* One note slot: the voice handle and the sequence, channel and key that started it. */
typedef struct SndMidiNote_t {
    int mHandle;
    signed char mSeq;
    signed char mChan;
    signed char mKey;
    signed char mFlags;
} SndMidiNote_t;

typedef struct SndMidiState_t {
    SndMidiSeq_t mSeqs[16];
    SndMidiNote_t mNotes[24];
} SndMidiState_t;

extern "C" {

extern SndMidiState_t lbl_803A6E60;

int SNDvol(int handle, int vol);
void SNDSYS_entercritical(void);
void SNDSYS_leavecritical(void);
int fn_80277D88(int handle, int bend);
void fn_8026BF04(int seq);

int SNDseqstop(int handle);
int SNDmidistopall(void);
int SNDmidirestore(void);

}

void SNDI_midiserver(void);

int SNDI_midigetseqindex(int handle)
{
    int index;

    if (handle < 0) {
        return -8;
    }
    index = handle & 0x1F;
    if (index > 15) {
        return -8;
    }
    if (lbl_803A6E60.mSeqs[index].mHandle != handle) {
        return -8;
    }
    return index;
}

int SNDI_midiupdatefade(int seq)
{
    SndMidiSeq_t *s = &lbl_803A6E60.mSeqs[seq];
    int i;

    s->mVolume += s->mFadeStep;
    if (s->mFadeStep < 0) {
        if (s->mVolume <= s->mFadeTarget) {
            s->mVolume = s->mFadeTarget;
            s->mFadeStep = 0;
        }
    } else if (s->mVolume >= s->mFadeTarget) {
        s->mVolume = s->mFadeTarget;
        s->mFadeStep = 0;
    }
    if (s->mVolume < 0) {
        SNDseqstop(s->mHandle);
        return 1;
    }
    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &lbl_803A6E60.mNotes[i];

        if (note->mSeq == seq && note->mHandle > -1) {
            SNDvol(note->mHandle, s->mChans[note->mChan].mVolume * (short)(s->mVolume >> 16) >> 7);
        }
    }
    return 0;
}

int SNDI_midiseqover(int seq)
{
    int over = 1;
    int i;

    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &lbl_803A6E60.mNotes[i];

        if (note->mSeq == seq && note->mHandle >= 0 && SNDVOICEI_get(note->mHandle) >= 0) {
            over = 0;
            break;
        }
    }
    return over;
}

void SNDI_midiparsenoteoff(int seq, int chan, int key)
{
    SndMidiSeq_t *s = &lbl_803A6E60.mSeqs[seq];
    int i;

    s->mpData++;
    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &lbl_803A6E60.mNotes[i];

        if (note->mSeq == seq && note->mChan == chan && note->mKey == key && !(note->mFlags & 0x80)) {
            SNDrelease(note->mHandle);
            note->mFlags = -1;
            return;
        }
    }
}

void SNDI_midiparsepitchbend(int seq, SndMidiChan_t *chan, int channel, int lsb)
{
    SndMidiSeq_t *s = &lbl_803A6E60.mSeqs[seq];
    int value = (*s->mpData++ << 7) + lsb;
    int i;

    chan->mBend = (unsigned char)(value / 128);
    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &lbl_803A6E60.mNotes[i];

        if (note->mSeq == seq && note->mChan == channel) {
            fn_80277D88(note->mHandle, chan->mBend);
        }
    }
}

void SNDI_midiserver(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        SndMidiSeq_t *s = &lbl_803A6E60.mSeqs[i];
        unsigned int target;

        if (s->mState != 3) {
            continue;
        }
        if (s->mFadeStep != 0 && SNDI_midiupdatefade(i) != 0) {
            continue;
        }
        target = s->mTicks * s->mTempo / 100;
        s->mTicks++;
        for (; s->mPosition <= target && s->mState == 3; s->mPosition++) {
            fn_8026BF04(i);
        }
    }
}

extern "C" {

int SNDmidiinit(void)
{
    int i;

    SNDSYS_entercritical();
    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &lbl_803A6E60.mNotes[i];

        note->mChan = -1;
        note->mKey = 0;
        note->mFlags = 0;
        note->mHandle = -1;
    }
    for (i = 0; i < 16; i++) {
        SndMidiSeq_t *s = &lbl_803A6E60.mSeqs[i];

        s->mHandle = -1;
        s->mState = 0;
    }
    SNDSYS_add100hzclient(SNDI_midiserver);
    lbl_803A6C24.m1C4 = (void (*)(void))SNDmidirestore;
    SNDSYS_leavecritical();
    return 0;
}

int SNDmidirestore(void)
{
    SNDSYS_entercritical();
    SNDmidistopall();
    SNDSYS_remove100hzclient(SNDI_midiserver);
    lbl_803A6C24.m1C4 = 0;
    SNDSYS_leavecritical();
    return 0;
}

int SNDmidistopall(void)
{
    int i;

    SNDSYS_entercritical();
    for (i = 0; i < 16; i++) {
        SNDseqstop(lbl_803A6E60.mSeqs[i].mHandle);
    }
    SNDSYS_leavecritical();
    return 0;
}

int SNDseqstop(int handle)
{
    SndMidiSeq_t *s;
    int seq;
    int i;

    seq = SNDI_midigetseqindex(handle);
    if (seq < 0) {
        return seq;
    }
    s = &lbl_803A6E60.mSeqs[seq];
    if (s->mState != 0) {
        for (i = 0; i < 24; i++) {
            SndMidiNote_t *note = &lbl_803A6E60.mNotes[i];

            if (note->mSeq == seq) {
                if (note->mHandle >= 0) {
                    SNDstop(note->mHandle);
                }
                note->mChan = -1;
                note->mKey = 0;
                note->mFlags = 0;
                note->mHandle = -1;
            }
        }
        s->mHandle = -1;
        s->mState = 2;
        return 0;
    }
    return -1;
}

}
