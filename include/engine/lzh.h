#ifndef ENGINE_LZH_H
#define ENGINE_LZH_H

typedef struct LZHBlock_t
{
    unsigned char *mUnknown00;
    int mUnknown04;
    int mUnknown08;
    char mUnknown0C[12];
    unsigned char mUnknown18;
} LZHBlock_t;

typedef struct LZHHuffCode_t
{
    unsigned short mUnknown00;
    short mUnknown02;
} LZHHuffCode_t;

typedef struct LZHDecodeEntry_t
{
    short mUnknown00;
    unsigned char mUnknown02;
} LZHDecodeEntry_t;

typedef struct LZHCodeSet_t
{
    LZHHuffCode_t *mpCodes;
    LZHDecodeEntry_t *mpLeaves;
    short mCount;
} LZHCodeSet_t;

#endif
