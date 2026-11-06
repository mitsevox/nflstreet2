/* Callbacks the memory card manager uses for NFL Street 2 saves: the save name taken from a save
   comment, the save icon image from icons.dat, and the files and blocks a new save of each type
   needs. */
#include <string.h>
#include "game/Callees_801D57E0.h"
#include "game/fn_801C3284.h"
#include "game/fn_801EF390.h"
#include "engine/texfile.h"
#include "game/MemCardCallbacks.h"

struct IconResourceHeader {
    char mUnknown0[4];
    unsigned short mUnknown4;
};

/* Object returned by fn_801EF390. */
struct IconResource {
    char mUnknown0[0x14];
    IconResourceHeader *mpUnknown14;
};

extern "C" {

int fn_801D6AC8(int type);
unsigned int fn_80029838(int type);

/* Copies the text after the last '-' of the comment; returns 1 when the
   comment has no '-'. */
int MemCardGetNameFromComment(char *pOut, int unused, MemCardComment *pComment)
{
    char *p = strrchr(pComment->mUnknown20, '-');

    if (p == 0) {
        return 1;
    }
    fn_801C3284(pOut, p + 1, 17);
    return 0;
}

void MemCardNullCallback(void)
{
}

void MemCardGetIcon(void *pData, int index, unsigned char **pOptional, unsigned int *pOut)
{
    IconResource *pResource = (IconResource *)fn_801EF390(pData, index, 1);
    TexFileImage_t *pEntry;

    TexMipmapRelocate(pResource);
    pEntry = TexGetTextureByIndex(pResource, pResource->mpUnknown14->mUnknown4);
    *pOut = pEntry->mUnknown8;
    if (pOptional) {
        *pOptional = pEntry->mpUnknownC;
    } else {
        fn_801F010C(pData, index);
    }
}

/* For each of the three save types, counts its first slot whose
   fn_801D6B74 flag is clear and adds that type's fn_80029838 size. */
void MemCardGetNewSaveSpace(int *pFiles, int *pBlocks)
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
