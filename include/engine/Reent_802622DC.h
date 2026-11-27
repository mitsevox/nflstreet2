#ifndef ENGINE_REENT_802622DC_H
#define ENGINE_REENT_802622DC_H

/* C library reentrancy state: the standard streams, locale name, random seed and exit
   registrations that vprintf.c, atexit.c, vfprintf.c and mbtowc_r.c reach through the
   pointer impure.c defines. */

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
  int mUnknown0;
  RuntimeFile_t *mStdin;
  RuntimeFile_t *mStdout;
  RuntimeFile_t *mStderr;
  char mUnknown10[32];
  int mCurrentCategory;
  const char *mLocaleName;
  char mUnknown38[32];
  unsigned int mRandNext;
  char mUnknown5C[236];
  RuntimeExitBlock_t *mExitBlock;
  RuntimeExitBlock_t mEmbeddedExitBlock;
  char mUnknown1D4[16];
  RuntimeFile_t mFiles[3];
} Reent_802622DC;

extern Reent_802622DC *_impure_ptr;

#endif
