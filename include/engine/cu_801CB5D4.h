#ifndef ENGINE_CU_801CB5D4_H
#define ENGINE_CU_801CB5D4_H


/* Layouts of the Nintendo SDK CARDFileInfo and CARDStat records (dolphin/card.h does not
   compile under the engine_c profile, so the fields used here are restated). */
typedef void (*CARDCallback_801CB5D4)(int chan, int result);

typedef struct CARDFileInfo_801CB5D4 {
    int chan;
    int fileNo;
    int offset;
    int length;
    unsigned short iBlock;
} CARDFileInfo_801CB5D4;

typedef struct CARDStat_801CB5D4 {
    char fileName[32];
    unsigned int length;
    unsigned int time;
    unsigned char gameName[4];
    unsigned char company[2];
    unsigned char bannerFormat;
    unsigned int iconAddr;
    unsigned short iconFormat;
    unsigned short iconSpeed;
    unsigned int commentAddr;
    unsigned int offsetBanner;
    unsigned int offsetBannerTlut;
    unsigned int offsetIcon[8];
    unsigned int offsetIconTlut;
    unsigned int offsetData;
} CARDStat_801CB5D4;

/* Single open memory-card file, cached one 8 KB sector at a time. */
typedef struct MCFile_801CB5D4 {
    unsigned char mBuffer[0x2000];
    unsigned int mSector;
    unsigned int mPos;
    int mDirty;
    int mChan;
    CARDStat_801CB5D4 mStat;
    CARDFileInfo_801CB5D4 mFileInfo;
} MCFile_801CB5D4;

void CARDInit(void);
int CARDCheck(int chan);
int CARDDelete(int chan, const char *fileName);
int CARDCreate(int chan, const char *fileName, unsigned int size, CARDFileInfo_801CB5D4 *fileInfo);
int CARDFreeBlocks(int chan, int *byteNotUsed, int *filesNotUsed);
int CARDGetStatus(int chan, int fileNo, CARDStat_801CB5D4 *stat);
int CARDSetStatus(int chan, int fileNo, CARDStat_801CB5D4 *stat);
int CARDRead(CARDFileInfo_801CB5D4 *fileInfo, void *buf, int length, int offset);
int CARDWrite(CARDFileInfo_801CB5D4 *fileInfo, const void *buf, int length, int offset);
int CARDUnmount(int chan);

#endif
