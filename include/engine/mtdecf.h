#ifndef ENGINE_MTDECF_H
#define ENGINE_MTDECF_H

/* 3432-byte MT decoder state used by src/engine/mtdecf.cpp (the MT unpack
   filter constructors in src/engine/supmutf.c, src/engine/supmutlf.c and src/engine/supmutpf.c
   allocate it with fn_8027C020(3432)). Partial layout: +0xC-+0x683 are not accessed by the
   reconstructed functions. */
typedef struct Codec_8027CF9C {
    unsigned char *m0;
    int m4;
    int m8;
    unsigned char mUnknownC[0x678];
    float m684[432];
    int mD44;
    unsigned char *mD48;
    float *mD4C;
    short mD50;
    short mD52;
    int mD54;
    int mD58;
    int mD5C;
    int mD60;
    int mD64;
} Codec_8027CF9C;

typedef struct Format_8027D284 {
    int m0;
    int m4;
    int m8;
} Format_8027D284;

#ifdef __cplusplus
extern "C" {
#endif

Codec_8027CF9C *fn_8027CF9C(void *memory);
int fn_8027CFCC(Codec_8027CF9C *p, unsigned char *data, int size, int count);
int CodecReadSamples(Codec_8027CF9C *p, float **dst, int count);
Format_8027D284 fn_8027D284(Codec_8027CF9C *p);
void fn_8027D2C4(Codec_8027CF9C *p, Format_8027D284 *format, int flags);
void fn_8027D2E0(Codec_8027CF9C *p, int mode);

#ifdef __cplusplus
}
#endif

#endif
