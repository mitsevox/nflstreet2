#include <string.h>
#include "game/Callees_801D57E0.h"
#include "game/fn_801C3284.h"
#include "game/fn_801EF390.h"
#include "game/Object_8020E52C.h"
#include "game/cu_80193CEC.h"

struct Header_80193D48 {
    char mUnknown0[4];
    unsigned short mUnknown4;
};

/* Object returned by fn_801EF390. */
struct Resource_80193D48 {
    char mUnknown0[0x14];
    Header_80193D48 *mpUnknown14;
};

extern "C" {

int fn_801D6AC8(int type);
unsigned int fn_80029838(int type);

/* Copies the text after the last '-' of the comment; returns 1 when the
   comment has no '-'. */
int fn_80193CEC(char *pOut, int unused, Comment_80193CEC *pComment)
{
    char *p = strrchr(pComment->mUnknown20, '-');

    if (p == 0) {
        return 1;
    }
    fn_801C3284(pOut, p + 1, 17);
    return 0;
}

void fn_80193D44(void)
{
}

void fn_80193D48(void *pData, int index, unsigned char **pOptional, unsigned int *pOut)
{
    Resource_80193D48 *pResource = (Resource_80193D48 *)fn_801EF390(pData, index, 1);
    Object_8020E560 *pEntry;

    fn_8020E2B0(pResource);
    pEntry = fn_8020E560(pResource, pResource->mpUnknown14->mUnknown4);
    *pOut = pEntry->mUnknown8;
    if (pOptional) {
        *pOptional = pEntry->mpUnknownC;
    } else {
        fn_801F010C(pData, index);
    }
}

/* For each of the three save types, counts its first slot whose
   fn_801D6B74 flag is clear and adds that type's fn_80029838 size. */
void fn_80193DC4(int *pFiles, int *pBlocks)
{
    int files = *pFiles;
    int blocks = *pBlocks;
    int count = 0;
    int size = 0;
    int type;
    int i;

    for (type = 1; type <= 3; type++) {
        for (i = 0; i < fn_801D6AC8(type); i++) {
            unsigned char flag;

            fn_801D6B74((signed char)i, type, 0, 0, 0, 0, &flag);
            if (!flag) {
                count++;
                size += fn_80029838(type);
                break;
            }
        }
    }
    files += count;
    blocks += size;
    *pFiles = files;
    *pBlocks = blocks;
}
}
