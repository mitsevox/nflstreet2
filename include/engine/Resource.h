#ifndef ENGINE_RESOURCE_H
#define ENGINE_RESOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Directory or compression block entry of a resource file (8 bytes). */
typedef struct ResBlockEntry_t {
    unsigned int mOffsetOrCodec;
    unsigned int mSize;
} ResBlockEntry_t;

typedef struct ResHashHeader_t {
    int mType;
    int mParamSize;
    unsigned int mWidth;
} ResHashHeader_t;

/* Open resource file record (0xA4 bytes, pool item of Resource.c). */
typedef struct ResFile_t {
    int mFile;
    char *pName;
    unsigned int mEndPad;
    unsigned int mPosition;
    unsigned short mNumWritten;
    unsigned char unk_0x12;
    unsigned char mBigEndian;
    unsigned short mNumRes;
    unsigned short mAlignment;
    int mDirTag;
    int mHashTag;
    unsigned char mCompressed;
    unsigned char unk_0x21;
    unsigned short mVersion;
    unsigned int mDirSize;
    unsigned int mCompSize;
    unsigned int mHashSize;
    int mDirOffset;
    int mCompOffset;
    unsigned int mHashOffset;
    /* File offset of the data area for file-backed resources; ResClose frees it
       as an allocation for a state-3 resource. */
    unsigned int mBaseOffset;
    ResBlockEntry_t *pDir;
    ResHashHeader_t *pHash;
    unsigned int *pHashParams;
    void *pHashTable;
    void **pSlots;
    ResBlockEntry_t *pBlocks;
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
    char unk_0x7C[8];
    int mCacheHandle;
    int *pCache;
    unsigned int mFlags;
    int mOpenCount;
    unsigned int mMinDelay;
    unsigned int mMinSize;
    unsigned int mMaxDelay;
    unsigned int mMaxSize;
} ResFile_t;

typedef struct ResTrackOpenInfo_t {
    char *pName;
    char mMode;
} ResTrackOpenInfo_t;

typedef struct ResTrackLoadInfo_t {
    ResFile_t *pRes;
    int mIndex;
    int mOffset;
    int mDiskSize;
    int mFullSize;
    unsigned char mAsync;
    char mMode;
} ResTrackLoadInfo_t;

typedef void (*ResDoneCallback_t)(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);

/* Resource.c */
unsigned int ResLoad(ResFile_t *pRes, unsigned int index, int heap);
unsigned int ResLoadToBuffer(ResFile_t *pRes, unsigned int index, void *pBuffer);
unsigned int ResLoadAsyncToBuffer(ResFile_t *pRes, unsigned int index, int heap, void *pBuffer, int a,
                         ResDoneCallback_t pDone, void *pUser);
int ResCopyToBuffer(ResFile_t *pRes, unsigned int index, void *pBuffer);
int ResUnLoad(ResFile_t *pRes, unsigned int index);
unsigned int ResGetSize(ResFile_t *pRes, unsigned int index);
int ResGetStreamInfo(ResFile_t *pRes, unsigned int index, unsigned int *pSize, unsigned int *pOffset, int *pFile);
int ResGetMemAllocFlags(void);

/* terfhash.c */
int ProcHashHSH1(char *pString, unsigned int length, unsigned int *pParams);
int ProcHashHSH2(unsigned char *pData, unsigned int length, unsigned int *pParams);

/* hash.c */
int HashString(char *pString, int multiplier);

/* reswrite.c */
int fn_801F1B6C(ResFile_t *pRes);

/* ResTracker.c */
void ResTrackResource(unsigned int type, void *pData);

/* rescache.c */
void fn_801F2ED8(int mode);
void fn_801F2EE0(ResFile_t *pRes, char *pName);
void fn_801F30CC(ResFile_t *pRes);
void fn_801F3104(ResFile_t *pRes);
void fn_801F318C(ResFile_t *pRes, int index, int offset, void *pData, int size);

/* resloosefile.c */
int ResLooseFileGetSize(ResFile_t *pRes, unsigned int index, unsigned int *pSize);

#ifdef __cplusplus
}
#endif

#endif
