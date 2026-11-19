#ifndef ENGINE_VOXDATHEADER_H
#define ENGINE_VOXDATHEADER_H

typedef struct VoxDatHeader_t {
    unsigned int mUnknown0;
    unsigned char mUnknown4[4];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[6];
    unsigned short mUnknown10;
    unsigned char mUnknown12;
} VoxDatHeader_t;

#ifdef __cplusplus
extern "C" {
#endif

void fn_801AFABC(VoxDatHeader_t *p, int *a, int *b);

#ifdef __cplusplus
}
#endif

#endif
