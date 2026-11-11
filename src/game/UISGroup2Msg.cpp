/* UIStudio message routing for screen group 2 (the replay menu and the debug window), and the roster-slot position abbreviation formatter. */
#include "game/cu_80181330.h"

struct ReplayScreenArgs_t;
struct DebugWindowMsg_t;

extern "C" {
/* Position abbreviations of the 14 roster slots: QB, RB, two WR, three OL,
   two DL, two LB and three DB. */
extern const char *lbl_802EA214[14];

int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int ReplayScreenHandleMessage(unsigned int id, ReplayScreenArgs_t *pBlock, int unused, int *pResult);
int DebugWindowHandleMsg(unsigned int id, DebugWindowMsg_t *pBlock, int unused, int *pResult);

void PositionAbbrevFormat(int slot, char *pText)
{
    fn_801C2E18(pText, lbl_802EA214[slot]);
}

int UISGroup2HandleMsg(int group, unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 3:
        return DebugWindowHandleMsg(id, (DebugWindowMsg_t *)pArgs, unused, pResult);
    case 2:
        return ReplayScreenHandleMessage(id, (ReplayScreenArgs_t *)pArgs, unused, pResult);
    case 5:
        return 0;
    }
    return 0;
}
}
