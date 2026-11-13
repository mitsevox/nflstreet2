#ifndef ENGINE_ANIMSEQCAMSAMPLE_H
#define ENGINE_ANIMSEQCAMSAMPLE_H

#include "engine/CurveList.h"

/* Sample record returned by AnimSeqCamFindCamera/AnimSeqCamFindFirstCamera: three floats, then 15
   curves whose +0xC key pointers AnimSeqncrRelocateSeqFile relocates. Kept apart from
   engine/AnimSeqCamera.h so that game callers with their own bank view can
   share it. */
typedef struct AnimSeqCamSample_t {
    float mUnknown0[3];
    CurveList_t mCurves[15];
} AnimSeqCamSample_t;

#endif
