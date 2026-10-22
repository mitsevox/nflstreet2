#ifndef ENGINE_CU_801CB5D4_H
#define ENGINE_CU_801CB5D4_H

#include <dolphin/card.h>

/* Single open memory-card file, cached one 8 KB sector at a time. */
typedef struct MCFile_801CB5D4 {
    unsigned char mBuffer[0x2000];
    unsigned int mSector;
    unsigned int mPos;
    int mDirty;
    int mChan;
    CARDStat mStat;
    CARDFileInfo mFileInfo;
} MCFile_801CB5D4;

#endif
