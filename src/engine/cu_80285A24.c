/* Partial source for the range 0x80285A24-0x80285A90 (neutral file name): a thread starter and
   an empty callback whose addresses 0x8022F628-0x8022F6EC store. */

#include <dolphin/os.h>

typedef struct Struct_80285A24
{
    char mUnknown00[4];
    unsigned int mUnknown04;
    void *mUnknown08;
    char mUnknown0C[4];
    void *(*mUnknown10)(void *);
    char *mUnknown14;
} Struct_80285A24;

extern OSThread lbl_803BA580;

void fn_80285A24(Struct_80285A24 *p)
{
    if ((unsigned char)OSCreateThread(&lbl_803BA580, p->mUnknown10, p->mUnknown08, p->mUnknown14 + p->mUnknown04, p->mUnknown04, 22, 1))
        OSResumeThread(&lbl_803BA580);
}

void fn_80285A8C(void)
{
}
