/* Shared context values for in-game player speech: how the score stands for the team that had the
   ball at the snap, how far apart the teams are, which voice category a speaking player falls into,
   and whether either team is in a gamebreaker. Speech triggers pass these to the speech system so
   it can pick a fitting line. */

#include "game/Object_80039F5C.h"
#include "game/StyleTracker.h"

extern "C" {
int fn_800A8444(int team);
int fn_800A8468(int team);
int fn_80177F70(void);
int fn_801787DC(int team);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
int fn_801788D8(int *pValue);

void SpchIGGetScoreSituation(int *pResult)
{
    int limit = 0;

    *pResult = 8;
    switch (fn_801788D8(&limit)) {
    case 0:
    case 2: {
        unsigned short own = fn_801787DC(fn_80178348());
        unsigned short other = fn_801787DC(fn_80178360());
        unsigned short gap = own - other < 0 ? other - own : own - other;
        if (own == other) {
            if (own > 13) {
                *pResult |= 4;
            }
        } else if (own > other) {
            *pResult |= 2;
            if (gap > 23) {
                *pResult |= 0x20;
            } else if (gap > 15) {
                *pResult |= 0x40;
            } else if (gap > 7) {
                *pResult |= 0x80;
            }
        } else {
            *pResult |= 1;
            if (gap > 23) {
                *pResult |= 0x100;
            } else if (gap > 15) {
                *pResult |= 0x200;
            } else if (gap > 7) {
                *pResult |= 0x400;
            }
        }
        if (fn_80177F70() == 6) {
            if (own + 2 >= (unsigned int)limit && own < (unsigned int)limit) {
                *pResult |= 0x10;
            }
        } else {
            if (own + 6 >= (unsigned int)limit && own < (unsigned int)limit) {
                *pResult |= 0x10;
            }
        }
        break;
    }
    case 1: {
        int own = StyleTrackerGetTotal(fn_80178348());
        int other = StyleTrackerGetTotal(fn_80178360());

        if (own == other) {
            if (own > 99999) {
                *pResult |= 4;
            }
        } else if (own > other) {
            *pResult |= 2;
            if (own - other > 23) {
                *pResult |= 0x20;
            } else if (own - other > 15) {
                *pResult |= 0x40;
            } else if (own - other > 7) {
                *pResult |= 0x80;
            }
        } else {
            *pResult |= 1;
            if (other - own > 23) {
                *pResult |= 0x100;
            } else if (other - own > 15) {
                *pResult |= 0x200;
            } else if (other - own > 7) {
                *pResult |= 0x400;
            }
        }
        if (own + 50000 >= limit && own < limit) {
            *pResult |= 0x10;
        }
        break;
    }
    }
}

void SpchIGGetScoreMargin(int *pResult)
{
    int limit = 0;

    *pResult = 8;
    switch (fn_801788D8(&limit)) {
    case 0:
    case 2: {
        unsigned short own = fn_801787DC(fn_80178348());
        unsigned short other = fn_801787DC(fn_80178360());
        unsigned short gap = own < other ? other - own : own - other;

        if (gap > 23) {
            *pResult |= 4;
        } else if (gap > 15) {
            *pResult |= 1;
        } else if (gap > 7) {
            *pResult |= 2;
        }
        if (fn_80177F70() == 6) {
            if (own + 2 >= (unsigned int)limit && own < (unsigned int)limit) {
                *pResult |= 0x10;
            }
        } else {
            if (own + 6 >= (unsigned int)limit && own < (unsigned int)limit) {
                *pResult |= 0x10;
            }
        }
        break;
    }
    case 1: {
        unsigned short own = StyleTrackerGetTotal(fn_80178348());
        unsigned short other = StyleTrackerGetTotal(fn_80178360());
        unsigned short gap = own < other ? other - own : own - other;

        if (gap > 49999) {
            *pResult |= 2;
        }
        break;
    }
    }
}

void SpchIGGetPlayerCategory(int *pResult, int ref)
{
    Object_80039F5C *pPlayer = fn_8009BCE8(&ref);

    *pResult = 0;
    if (pPlayer) {
        if (pPlayer->mUnknown2912 <= 3) {
            *pResult = 1;
        } else if (pPlayer->mUnknown2920 == 2 || pPlayer->mUnknown2920 == 3) {
            *pResult = 2;
        } else {
            *pResult = 4;
        }
    }
}

void SpchIGGetTargetCategory(int *pResult, int ref)
{
    Object_80039F5C *pPlayer = fn_8009BCE8(&ref);

    *pResult = 0;
    if (pPlayer) {
        if (pPlayer->mUnknown2912 <= 3) {
            *pResult = 4;
        } else if (pPlayer->mUnknown2920 == 2 || pPlayer->mUnknown2920 == 3) {
            *pResult = 1;
        } else {
            *pResult = 2;
        }
    } else {
        *pResult = 8;
    }
}

void SpchIGGetGamebreakerState(int *pResult)
{
    *pResult = 0;
    if (fn_800A8444(fn_80178308())) {
        *pResult |= 1;
    }
    if (fn_800A8444(fn_80178320())) {
        *pResult |= 2;
    }
    if (fn_800A8468(fn_80178320()) || fn_800A8468(fn_80178308())) {
        *pResult |= 8;
    }
    if (*pResult) {
        *pResult |= 4;
    }
}
}
