#ifndef ENGINE_SNDSTRM_H
#define ENGINE_SNDSTRM_H

/* Declarations shared by the sound stream files of 0x8026D200-0x80270D6C: the stream
   channel and request records and the stream, voice and system calls they make. */

#include "engine/slinklst.h"
#include "engine/cu_802714A8.h"
#include "engine/sndvoice.h"

/* One queued stream request: linked on its channel's request list. */
typedef struct SndStreamRequest_t {
    SndLinkNode_t mLink;
    unsigned char unk_0x8[4];
    int mId;
    unsigned int mDataRate;
    unsigned int unk_0x14;
    unsigned int unk_0x18;
    unsigned int unk_0x1C;
    int mHold;
    unsigned char mActive;
    unsigned char unk_0x25[3];
} SndStreamRequest_t;

/* A volume fade in progress: linked on the stream fader list and called on every service. */
typedef struct SndStreamFader_t SndStreamFader_t;

struct SndStreamFader_t {
    SndStreamFader_t *mpNext;
    SndStreamFader_t *mpPrev;
    void (*mpCallback)(void *context);
    void *mpContext;
};

/* The azimuth and volume state of one speaker slot of a stream channel. */
typedef struct SndStreamSpeaker_t {
    float mAzimuth;
    unsigned char mAzimuthOn;
    unsigned char mIndex;
    unsigned char unk_0x6[2];
    float mVolume;
    SndStreamFader_t mFader;
    float mTarget;
    float mStep;
} SndStreamSpeaker_t;

/* One stream channel, found through the channel table by its index. */
typedef struct SndStreamChannel_t {
    void *mpTap;
    int mVoice;
    int mBuffer;
    unsigned char unk_0xC[6];
    unsigned char mPanned;
    unsigned char unk_0x13;
    unsigned short mPlayRate;
    unsigned char mChannels;
    unsigned char unk_0x17;
    unsigned short mQueueRate;
    unsigned char unk_0x1A[0xD6];
    unsigned char mDryLevel;
    unsigned char unk_0xF1[7];
    short mPitchMult;
    short mTimeMult;
    unsigned char unk_0xFC[4];
    short mLowPass;
    short mHighPass;
    float *mpFxLevels;
    unsigned char unk_0x108[0x18];
    SndLinkList_t mRequests;
    SndLinkList_t mFreeRequests;
    SndStreamRequest_t *mpCurrent;
    SndStreamSpeaker_t mSpeakers[6];
} SndStreamChannel_t;

/* Filled by SNDSTRM_requeststatus. */
typedef struct SndStreamRequestStatus_t {
    int mState;
    int unk_0x4;
    int unk_0x8;
    int unk_0xC;
} SndStreamRequestStatus_t;

/* Filled by SNDSTRM_status. */
typedef struct SndStreamStatus_t {
    int mRequests;
    int mFirstId;
    int mBuffered;
} SndStreamStatus_t;

#ifdef __cplusplus
extern "C" {
#endif

extern int lbl_8030002C;
extern float lbl_80300028;
extern SndStreamFader_t *SNDSYSI_timerclients;
extern float lbl_803A7644;
extern const signed char lbl_802B79A0[6][6];

int SNDSTRM_setvol(int stream, int speaker, float vol);

SndStreamChannel_t *fn_8026D610(int index);
int fn_8026DE00(void *opts, int a, int b, void *data, int c, int d, int tap);

void SNDSYS_entercritical(void);
void SNDSYS_leavecritical(void);
int SNDCTRL_drylevel(int voice, int level);
int SNDpitchmult(int voice, int mult);
int fn_80270D6C(int voice, int mult);
int fn_80274F5C(int index);
void fn_802747D8(int index);
int fn_80271BD4(int index, int slot);
int fn_80278070(int voice, int bus, int level);
int fn_802781A8(int voice);
int SNDCTRL_highpass(int voice, int value);
int SNDPKTPLAY_overhead(int count);
int SNDCTRL_lowpass(int voice, int value);
int SNDPKTPLAY_framesoutstanding(int index);
void fn_801F6C04(void *tap, int level);
int fn_801F75C4(void *tap);
int fn_801F685C(int numRequests, int numFilters, int numTaps);

#ifdef __cplusplus
}
#endif

SndStreamRequest_t *SNDSTRMI_getrequestptr(int id);

#endif
