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
    unsigned char unk_0x7C0[4];
} SndMidiState_t;

extern "C" {

extern SndMidiState_t sndms;

int SNDvol(int handle, int vol);
void SNDSYS_entercritical(void);
void SNDSYS_leavecritical(void);
int SNDpitchbend(int handle, int value);
int SND3dpos(int handle, unsigned short azimuth, int elevation);
int SNDI_pantoazimuth(int pan);

int SNDseqstop(int handle);
int SNDmidistopall(void);
int SNDmidirestore(void);

}

/* The sequence and note slots. */
SndMidiState_t sndms;

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
    if (sndms.mSeqs[index].mHandle != handle) {
        return -8;
    }
    return index;
}

int SNDI_midiupdatefade(int seq)
{
    SndMidiSeq_t *s = &sndms.mSeqs[seq];
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
        SndMidiNote_t *note = &sndms.mNotes[i];

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
        SndMidiNote_t *note = &sndms.mNotes[i];

        if (note->mSeq == seq && note->mHandle >= 0 && SNDVOICEI_get(note->mHandle) >= 0) {
            over = 0;
            break;
        }
    }
    return over;
}

void SNDI_midiparsenoteon(int seq, SndMidiChan_t *chan, int channel, int key)
{
    static int lastnote = 0;
    SndMidiSeq_t *s = &sndms.mSeqs[seq];
    SndMidiNote_t *note = 0;
    SndPlayOpts_t opts;
    int found = 0;
    int last;
    int bank;
    int patch;
    int pan;
    int i;

    i = ++lastnote;
    for (last = i + 24; i < last; i++) {
        lastnote = i % 24;
        note = &sndms.mNotes[lastnote];
        if (SNDVOICEI_get(note->mHandle) < 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        SNDplaysetdef(&opts);
        pan = s->m20;
        opts.m0 = chan->mVolume * (short)(s->mVolume >> 16) >> 7;
        opts.m3 = *s->mpData;
        opts.m8 = (chan->mAzimuth << 6) + pan;
        opts.mC = s->m22;
        opts.m1 = chan->mBend;
        if (channel == 9 && s->m2E >= 0) {
            opts.m2 = 60;
            bank = s->m2E;
            patch = key;
        } else {
            bank = s->m2C;
            opts.m2 = key;
            patch = chan->mPatch;
        }
        note->mHandle = SNDBANK_play(bank, patch, &opts);
        note->mFlags = *s->mpData++;
        if (note->mHandle >= 0) {
            note->mSeq = seq;
            note->mChan = channel;
            note->mKey = key;
        }
    } else {
        s->mpData++;
    }
}

void SNDI_midiparsenoteoff(int seq, int chan, int key)
{
    SndMidiSeq_t *s = &sndms.mSeqs[seq];
    int i;

    s->mpData++;
    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &sndms.mNotes[i];

        if (note->mSeq == seq && note->mChan == chan && note->mKey == key && !(note->mFlags & 0x80)) {
            SNDrelease(note->mHandle);
            note->mFlags = -1;
            return;
        }
    }
}

void SNDI_midiparsecontrol(int seq, SndMidiChan_t *chan, int channel, int control)
{
    SndMidiSeq_t *s = &sndms.mSeqs[seq];
    int i;

    if (control == 20) {
        s->mpData++;
        s->mpLoop = s->mpData;
    } else if (control == 30) {
        if (s->m26 > 126) {
            s->m26 = *s->mpData;
        }
        if (s->m26 != 0) {
            s->m26--;
            s->mpData = s->mpLoop;
        } else {
            s->mpData++;
        }
    } else if (control == 7) {
        chan->mVolume = *s->mpData++;
        for (i = 0; i < 24; i++) {
            SndMidiNote_t *note = &sndms.mNotes[i];

            if (note->mSeq == seq && note->mChan == channel) {
                SNDvol(note->mHandle, chan->mVolume * (short)(s->mVolume >> 16) >> 7);
            }
        }
    } else if (control == 10) {
        chan->mAzimuth = SNDI_pantoazimuth(*s->mpData++) >> 6;
        for (i = 0; i < 24; i++) {
            SndMidiNote_t *note = &sndms.mNotes[i];

            if (note->mSeq == seq && note->mChan == channel) {
                int azimuth = (chan->mAzimuth << 6) + s->m20;

                SND3dpos(note->mHandle, azimuth, 0);
            }
        }
    } else {
        s->mpData++;
    }
}

void SNDI_midiparsepitchbend(int seq, SndMidiChan_t *chan, int channel, int lsb)
{
    SndMidiSeq_t *s = &sndms.mSeqs[seq];
    int value = (*s->mpData++ << 7) + lsb;
    int i;

    chan->mBend = (unsigned char)(value / 128);
    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &sndms.mNotes[i];

        if (note->mSeq == seq && note->mChan == channel) {
            SNDpitchbend(note->mHandle, chan->mBend);
        }
    }
}

void SNDI_midiprocesstick(int seq)
{
    SndMidiSeq_t *s = &sndms.mSeqs[seq];
    int delta;
    int status;
    int data;

    delta = *s->mpData++;
    s->mDelta--;
    status = *s->mpData++;
    data = *s->mpData++;
    s->mpData -= 3;
    if ((status & 0xF0) == 0xF0 && data == 0x2F) {
        if (SNDI_midiseqover(seq) != 0) {
            SNDseqstop(s->mHandle);
        }
        return;
    }
    if (s->mDelta != 0) {
        return;
    }
    do {
        int status;
        int event;
        int channel;
        SndMidiChan_t *chan;

        delta = *s->mpData++;
        status = *s->mpData++;
        data = *s->mpData++;
        event = status & 0xF0;
        channel = status & 0xF;
        chan = &s->mChans[channel];
        switch (event) {
        case 0x90:
            SNDI_midiparsenoteon(seq, chan, channel, data);
            break;
        case 0x80:
            SNDI_midiparsenoteoff(seq, channel, data);
            break;
        case 0xB0:
            SNDI_midiparsecontrol(seq, chan, channel, data);
            break;
        case 0xC0:
            chan->mPatch = data;
            break;
        case 0xE0:
            SNDI_midiparsepitchbend(seq, chan, channel, data);
            break;
        case 0xF0:
            if (data == 0x2F) {
                if (SNDI_midiseqover(seq) != 0) {
                    SNDseqstop(s->mHandle);
                } else {
                    delta = 1;
                    s->mpData -= 3;
                    s->mDelta++;
                }
            }
            break;
        }
    } while (delta == 0 && s->mState == 3);
    s->mDelta = delta;
}

void SNDI_midiserver(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        SndMidiSeq_t *s = &sndms.mSeqs[i];
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
            SNDI_midiprocesstick(i);
        }
    }
}

extern "C" {

int SNDmidiinit(void)
{
    int i;

    SNDSYS_entercritical();
    for (i = 0; i < 24; i++) {
        SndMidiNote_t *note = &sndms.mNotes[i];

        note->mChan = -1;
        note->mKey = 0;
        note->mFlags = 0;
        note->mHandle = -1;
    }
    for (i = 0; i < 16; i++) {
        SndMidiSeq_t *s = &sndms.mSeqs[i];

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
        SNDseqstop(sndms.mSeqs[i].mHandle);
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
    s = &sndms.mSeqs[seq];
    if (s->mState != 0) {
        for (i = 0; i < 24; i++) {
            SndMidiNote_t *note = &sndms.mNotes[i];

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
