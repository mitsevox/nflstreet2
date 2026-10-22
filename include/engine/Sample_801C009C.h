#ifndef ENGINE_SAMPLE_801C009C_H
#define ENGINE_SAMPLE_801C009C_H

/* Sample record returned by fn_801C009C/fn_801C00F8: three floats, then 15
   curves whose +0xC key pointers fn_801C02EC relocates. Kept apart from
   engine/cu_801BFFA8.h so that game callers with their own bank view can
   share it. */
typedef struct Curve_801C02EC {
    unsigned char mUnknown0[4];
    float mUnknown4;
    float mUnknown8;
    void *mpKeys;
} Curve_801C02EC;

typedef struct Sample_801C009C {
    float mUnknown0[3];
    Curve_801C02EC mCurves[15];
} Sample_801C009C;

#endif
