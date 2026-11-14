#ifndef ENGINE_REENT_802622DC_H
#define ENGINE_REENT_802622DC_H

/* C library state shared by vprintf.c, the exit-registration code and vfprintf.c. */

typedef struct RuntimeFile_t
{
  unsigned char *mCursor;
  char mUnknown4[4];
  int mWriteRemaining;
  short mFlags;
  short mDescriptor;
  char mUnknown10[76];
  void *mUnknown5C;
} RuntimeFile_t;

typedef struct RuntimeExitBlock_t
{
  struct RuntimeExitBlock_t *mPrevious;
  int mCount;
  void (*mCallbacks[32]) (void);
} RuntimeExitBlock_t;

typedef struct Reent_802622DC
{
  char mUnknown0[8];
  RuntimeFile_t *mUnknown8;
  char mUnknownC[40];
  const char *mLocaleName;
  char mUnknown38[272];
  RuntimeExitBlock_t *mExitBlock;
  RuntimeExitBlock_t mEmbeddedExitBlock;
} Reent_802622DC;

extern Reent_802622DC *lbl_803EC56C;

#endif
