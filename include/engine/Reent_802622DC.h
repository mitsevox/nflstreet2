#ifndef ENGINE_REENT_802622DC_H
#define ENGINE_REENT_802622DC_H

/* C library state shared by vprintf.c, the exit-registration code and vfprintf.c. */

typedef struct File_80262B5C
{
  char mUnknown0[92];
  void *mUnknown5C;
} File_80262B5C;

typedef struct Exit_80262310
{
  struct Exit_80262310 *mUnknown0;
  int mUnknown4;
  void (*mUnknown8[32]) (void);
} Exit_80262310;

typedef struct Reent_802622DC
{
  char mUnknown0[8];
  File_80262B5C *mUnknown8;
  char mUnknownC[316];
  Exit_80262310 *mUnknown148;
  Exit_80262310 mUnknown14C;
} Reent_802622DC;

extern Reent_802622DC *lbl_803EC56C;

#endif
