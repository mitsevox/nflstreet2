#ifndef ENGINE_ANIMSEQCAMSAMPLE_H
#define ENGINE_ANIMSEQCAMSAMPLE_H

/* Sample record returned by AnimSeqCamFindCamera/AnimSeqCamFindFirstCamera: three floats, then 15
   curves whose +0xC key pointers AnimSeqncrRelocateSeqFile relocates. Kept apart from
   engine/AnimSeqCamera.h so that game callers with their own bank view can
   share it. */
typedef struct AnimSeqCamCurve_t {
    unsigned char mUnknown0[4];
    float mUnknown4;
    float mUnknown8;
    void *mpKeys;
} AnimSeqCamCurve_t;

typedef struct AnimSeqCamSample_t {
    float mUnknown0[3];
    AnimSeqCamCurve_t mCurves[15];
} AnimSeqCamSample_t;

#endif
