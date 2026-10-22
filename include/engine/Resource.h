#ifndef ENGINE_RESOURCE_H
#define ENGINE_RESOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Directory or compression block entry of a resource file (8 bytes). */
typedef struct ResBlock_801F10B0 {
    unsigned int mUnk0;
    unsigned int mUnk4;
} ResBlock_801F10B0;

typedef struct ResHash_801F0A8C {
    int mType;
    int mUnk4;
    unsigned int mWidth;
} ResHash_801F0A8C;

/* Open resource file record (0xA4 bytes, pool item of Resource.c). */
typedef struct Res_801EDC2C {
    int mFile;
    char *pName;
    unsigned int mEndPad;
    unsigned int mPosition;
    unsigned short mNumWritten;
    unsigned char mUnk12;
    unsigned char mBigEndian;
    unsigned short mNumRes;
    unsigned short mAlignment;
    int mDirTag;
    int mHashCount;
    unsigned char mCompressed;
    unsigned char mUnk21;
    unsigned short mVersion;
    unsigned int mDirSize;
    unsigned int mCompSize;
    unsigned int mHashSize;
    int mDirOffset;
    int mCompOffset;
    unsigned int mHashOffset;
    /* File offset of the data area for file-backed resources; fn_801EEFAC frees it
       as an allocation for a state-3 resource. */
    unsigned int mBaseOffset;
    ResBlock_801F10B0 *pDir;
    ResHash_801F0A8C *pHash;
    unsigned int *pHashParams;
    void *pHashTable;
    void **pSlots;
    ResBlock_801F10B0 *pBlocks;
    unsigned short mState;
    unsigned short mNumLocked;
    unsigned int mDataSize;
    int mHeap;
    unsigned int mBaseAddr;
    void *pExtra;
    unsigned int mIndex;
    int mMode;
    unsigned int *pAddrs;
    volatile unsigned char *pFlags;
    char mUnk7C[8];
    int mCacheHandle;
    int *pCache;
    unsigned int mFlags;
    int mOpenCount;
    char mUnk94[0x10];
} Res_801EDC2C;

typedef void (*ResDone_801EFAD8)(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);

/* Resource.c */
unsigned int fn_801EF390(Res_801EDC2C *pRes, unsigned int index, int heap);
unsigned int fn_801EF7BC(Res_801EDC2C *pRes, unsigned int index, void *pBuffer);
unsigned int fn_801EFAD8(Res_801EDC2C *pRes, unsigned int index, int heap, void *pBuffer, int a,
                         ResDone_801EFAD8 pDone, void *pUser);
int fn_801EFF80(Res_801EDC2C *pRes, unsigned int index, void *pBuffer);
int fn_801F010C(Res_801EDC2C *pRes, unsigned int index);
unsigned int fn_801F0C50(Res_801EDC2C *pRes, unsigned int index);
int fn_801F10B0(Res_801EDC2C *pRes, unsigned int index, unsigned int *pSize, unsigned int *pOffset, int *pFile);
int fn_801F1530(void);

/* terfhash.c */
int fn_801F1538(char *pString, unsigned int length, unsigned int *pParams);
int fn_801F155C(unsigned char *pData, unsigned int length, unsigned int *pParams);

/* hash.c */
int fn_801F34C0(char *pString, int multiplier);

/* reswrite.c */
int fn_801F1B6C(Res_801EDC2C *pRes);

/* ResTracker.c */
void fn_801F23DC(unsigned int type, void *pData);

/* rescache.c */
void fn_801F2ED8(int mode);
void fn_801F2EE0(Res_801EDC2C *pRes, char *pName);
void fn_801F30CC(Res_801EDC2C *pRes);
void fn_801F3104(Res_801EDC2C *pRes);
void fn_801F318C(Res_801EDC2C *pRes, int index, int offset, void *pData, int size);

/* resloosefile.c */
int fn_801F33F0(Res_801EDC2C *pRes, unsigned int index, unsigned int *pSize);

#ifdef __cplusplus
}
#endif

#endif
