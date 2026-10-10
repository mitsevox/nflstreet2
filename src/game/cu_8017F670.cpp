#include "game/cu_80181330.h"

struct Block_80054E08;
struct Block_8017F868;

extern "C" {
/* Position abbreviations of the 14 roster slots: QB, RB, two WR, three OL,
   two DL, two LB and three DB. */
extern const char *lbl_802EA214[14];

int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int fn_80054E08(unsigned int id, Block_80054E08 *pBlock, int unused, int *pResult);
int fn_8017F868(unsigned int id, Block_8017F868 *pBlock, int unused, int *pResult);

void fn_8017F670(int slot, char *pText)
{
    fn_801C2E18(pText, lbl_802EA214[slot]);
}

int fn_8017F6A8(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 3:
        return fn_8017F868(id, (Block_8017F868 *)pArgs, unused, pResult);
    case 2:
        return fn_80054E08(id, (Block_80054E08 *)pArgs, unused, pResult);
    case 5:
        return 0;
    }
    return 0;
}
}
